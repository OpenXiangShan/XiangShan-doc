# 数据存储和组织方式

本章介绍 huancun 中数据存储与组织方式。

存储体的 IO 是与各个通道控制模块直接连接的，MSHR 不直接对存储体进行操作，而是通过向通道控制模块发送 Task，以其为代理读取或写入数据。存储体的 IO 如下图所示：

```scala
  val io = new Bundle {
    /** 接收上游 Probe 来的数据，写入 */
    val sinkC_adr = Decoupled(new BankedStoreInnerAddress(params)).flip
    val sinkC_dat = new BankedStoreInnerPoison(params).flip
    
    /** 接收下游 Grant 来的数据，写入 */
    val sinkD_adr = Decoupled(new BankedStoreOuterAddress(params)).flip
    val sinkD_dat = new BankedStoreOuterPoison(params).flip
    
    /** 向下游发送 Release 的数据和 Probe 的数据，读取 */
    val sourceC_adr = Decoupled(new BankedStoreOuterAddress(params)).flip
    val sourceC_dat = new BankedStoreOuterDecoded(params)
   
    /** SourceD 对 BS 的操作复杂，既要读取也要写入，这是由于工程将很多逻辑都写在 SourceD 中了*/
    /** 面向 SourceD 的读口 */
    val sourceD_radr = Decoupled(new BankedStoreInnerAddress(params)).flip
    val sourceD_rdat = new BankedStoreInnerDecoded(params)
		/** 面向 SourceD 的写口 */
    val sourceD_wadr = Decoupled(new BankedStoreInnerAddress(params)).flip
    val sourceD_wdat = new BankedStoreInnerPoison(params).flip
  }
```

## （下面内容搬了 non-blocking-cache-sifive 的语雀解读，后续修改）

#### 为了理解 BankedStore 的处理逻辑，就不得不首先理清各个通道是如何与其交互的：


- SinkC：
  - 收到通道中 ProbeAck 后，把数据存到 BS 中，并反馈 io.resp
  - 收到通道中 Release 后，不存数据到 BS，直接反馈 io.req



- SinkD：
  - 收到通道中 Grant 后，把数据存到 BS 中，并反馈 io.resp
  - 这边写 BS 的逻辑有点奇怪，引用师兄注释：

>   // banked store
>   // 总感觉这边有点问题啊？
>   // 为啥不是first就要valid呢？
>   // 当不是first时，要和不看d是否valid吗？就直接写吗？这也不太对吧？
>   // 我感觉这个是假设了message都是连续拍的吧？这个不一定能保证的吧？
>   io.bs_adr.valid := cache && (!first || (d.valid && grant_safe))

- SourceC
  - 收到 io.req 请求后，向下游响应 Probe 或给 Release，去查 BS，然后把结果放到 C 通道中



- SourceD
  - 收到上游的 Put 请求后，把数据存到 BS 中
  - 收到 xxx给上游发 Grant，需要读取 BS



#### 分析清楚之后，我们来看 BankedStore 内部的逻辑



图片.jpg



1. BankStore 主体是一个分 Bank 的 SRAM，这里的 Bank 与 Way 完全不是一个东西，之所以搞成 Bank 是为了支持一定的并行读写
   - 目前是定死的 4 个 Bank



2. 核心的逻辑
   - 将通道的读写请求抽象成 req，最终得到面向 Bank 的读写请求，因此如果有多个通道需要读写且分在了不同的 Bank 中，就能实现一定的并行化
   - 对每一个 Bank，通道的请求按照优先级排序访问
     - sinkC > sourceC > sinkD > sourceDw > sourceDr
   - 对于读请求，需要将读出来的各个 Bank 的内容拼合一下返回结果



关于 req 的抽象，代码注释如下：

```scala
  def req[T <: BankedStoreAddress](b: DecoupledIO[T], write: Bool, d: UInt): Request = {
    val beatBytes = if (b.bits.inner) innerBytes else outerBytes
    val ports = beatBytes / params.micro.writeBytes  // 一次读写需要占用的 Bank 数
    // 这边建议单独给一个变量 logicalWay=numBanks/ports, bankBits 就是逻辑 way 的 Index 位宽
    val bankBits = log2Ceil(numBanks / ports)
    // 假设 ports = 4, writeBytes = 8, 相当于一个 Beat 写 4 个 Bank
    // words 为 {d[63:0], d[127:64], d[191:128], d[255:192]}
    // 相当于把要写的内容分散到 Bank 上
    val words = Seq.tabulate(ports) { i =>
      val data = d((i + 1) * 8 * params.micro.writeBytes - 1, i * 8 * params.micro.writeBytes)
      data
    }
    // ------------------------
    // | way |    set    |beat|
    // ------------------------
    //    3       10       1       for L2 512KB
    //    3       11       1       for L3   1MB
    val a = Cat(b.bits.way, b.bits.set, b.bits.beat)  // 地址编码是按照这个来的
    val m = b.bits.mask
    val out = Wire(new Request)

    // select 是根据地址编码，来获得要访问的逻辑 way，独热形式
    val select = UIntToOH(a(bankBits-1, 0), numBanks/ports)
    val ready  = Cat(Seq.tabulate(numBanks/ports) { i => !(out.bankSum((i+1)*ports-1, i*ports) & m).orR } .reverse)
    b.ready := ready(a(bankBits-1, 0))

    out.wen      := write
    // 除去逻辑 way 位宽后, 剩下的地址就是 BS Index 了
    out.index    := a >> bankBits
    // FillInterleaved(2, "b1 0 0 0".U) equivalent to "b11 00 00 00".U
    // 相当于把逻辑 way 的选通信号，复制到该逻辑 way 的所有 port 上, 再处理一下 mask
    // 最终出来的是 Bank 的读写选通信号, 独热形式
    out.bankSel  := Mux(b.valid, FillInterleaved(ports, select) & Fill(numBanks/ports, m), UInt(0))
    // 如果是 noop, 什么都不做, 否则给出要读写 Bank 的 ready 情况
    out.bankEn   := Mux(b.bits.noop, UInt(0), out.bankSel & FillInterleaved(ports, ready))
    out.data     := Vec(Seq.fill(numBanks/ports) { words }.flatten)

    out
  }
```


####  下面还有一个重点就是，这些 req 的优先级关系为何是这样定义的？

```
  // These constraints apply on the port priorities:
  //  sourceC > sinkD     outgoing Release > incoming Grant      (we start eviction+refill concurrently)
  //  sinkC > sourceC     incoming ProbeAck > outgoing ProbeAck  (we delay probeack writeback by 1 cycle for QoR)
  //  sinkC > sourceDr    incoming ProbeAck > SourceD read       (we delay probeack writeback by 1 cycle for QoR)
  //  sourceDw > sourceDr modified data visible on next cycle    (needed to ensure SourceD forward progress)
  //  sinkC > sourceC     inner ProbeAck > outer ProbeAck        (make wormhole routing possible [not yet implemented])
  //  sinkC&D > sourceD*  beat arrival > beat read|update        (make wormhole routing possible [not yet implemented])

  // Combining these restrictions yields a priority scheme of:
  //  sinkC > sourceC > sinkD > sourceDw > sourceDr
  //          ^^^^^^^^^^^^^^^ outer interface

  // Requests have different port widths, but we don't want to allow cutting in line.
  // Suppose we have requests A > B > C requesting ports --A-, --BB, ---C.
  // The correct arbitration is to allow --A- only, not --AC.
  // Obviously --A-, BB--, ---C should still be resolved to BBAC.
```




备忘

| 信号名           | 含义                                                       | 设置方式 | 典型值      |
| ---------------- | ---------------------------------------------------------- | -------- | ----------- |
| innerBytes       | TileLink 总线进口 Beat 宽度                                | 被动     | 32          |
| outerBytes       | TileLink 总线出口 Beat 宽度                                | 被动     | 32          |
| portFactor       | 端口倍数<br />用于减少并行读写时的 Bank 冲突               | 主动     |             |
| blockBytes       | 一个 CacheLine 的宽度                                      | 主动     | 64          |
| sizeBytes        | Cache 总容量                                               | 被动     | 512 * 1024  |
| beatBytes        | TileLink 通道 Beat 宽度                                    | 被动     | 32          |
| blockBeats       | 一个 CacheLine 传输的 Beat 数                              | 被动     | 1           |
| rowBytes         | BS 中一个 row 的宽度<br />= portFactor * max(beatBytes)    | 被动     | 128         |
| rowEntries       | BS 中 Set 数量                                             | 被动     | 4096 / 8192 |
| rowBits          | BS 的 Index 的宽度                                         | 被动     | 12          |
| writeBytes       | 物理上一个 Bank 的读写宽度<br />用于分 Bank 时减少物理压力 | 主动     | 32 / 8      |
| numBanks         | 一个 row 分成的 Bank 数                                    | 被动     | 4           |
| codeBits         | 一个 Bank 的位宽                                           | 被动     | 256         |
| ports            | 一次总线读写需要占用的 Bank 数                             | 被动     | 1           |
| numBanks / ports | 一个 row 能被分成的逻辑 way 数                             | 被动     | 4           |
| bankBits         | 逻辑 way 的 Index 位宽                                     | 被动     | 2           |
