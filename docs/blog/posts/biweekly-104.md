---
slug: biweekly-104
date: 2026-06-08
categories:
  - Biweekly
---

# 【香山双周报 104】20260608 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 104 期双周报。

最近我们在 GitHub 上收到了很多 issue！我们欢迎每一位关注香山的开发者与我们交流反馈，无论是 bug 报告、功能建议还是使用香山时需要的问题，我们都会及时回复。在本次双周报中，我们与大家分享了一个非常有趣的 issue，通过这个 issue，我们修复了四个 bug。

关于香山近期开发进展，前端在修复了一些 bug，同时继续优化时序；后端实现了新的扩展，并修复了一些 bug；访存将 L2 扩容到了 2MB，同时优化了 PPA 和代码风格；XSAI 实现了 C 矩阵访存模块的重叠执行，并修复了一些 bug。

<!-- more -->

## 开发花絮

近期我们在 GitHub 上收到了一个 [issue #5910](https://github.com/OpenXiangShan/XiangShan/issues/5910)，~~（其实我们收到了很多，但是这个的分析过程格外有趣）~~。TA 指出，在一条 RVI 指令跨过页边界，两页都位于 MMIO 空间，前一页可执行，后一页不可执行时，difftest 会报错。

```plaintext
RTL : mtval=0x1dfaf000, mepc=0x1dfaf000, mcause=0x1 (instruction access fault)
NEMU: mtval=0x1dfadffe, mepc=0x1dfadffe, mcause=0x1 (instruction access fault)
```

起初我们怀疑这是一个 NEMU 和 RTL 未对齐产生的问题，因为如指令集手册所述：IAF 异常的 `mtval` 是引起异常的访存片段的虚拟地址。在此例中，由于总线的对齐访问要求，IFU 将一次取指拆分为两次访存，第一次访存的 `0x1dfadffe-0x1dfadfff` 两字节处于可执行区域，无异常；第二次访存的 `0x1dfaf000` 两字节处于不可执行区域，产生 IAF 异常，因此 `mtval` 应该是第二次访存的起始地址 `0x1dfaf000`，这与 NEMU 的行为不一致。因此将该 issue 转交给了 NEMU 团队进行分析。

与此同时，我们仔细检查了波形，注意到 IFU 在读取 `0x1dfadffe-0x1dfadfff` 时实际上读到了 `0x0`，这是一条非法的 RVC 指令，而不是预期中的半条合法的 RVI 指令，这可能是 workload 使能 PMP 的时机有误引起的缓存一致性问题，因为 NEMU 不具有 cache 模型，在这种情况下的 difftest 报错是符合预期的。实际上 RTL 的行为是：在 `0x1dfadffe` 处检查到了一条非法 RVC 指令，而 NEMU 则触发到了一个 IAF。

——但这样看，RTL 应该报告 `mtval=0x0, mepc=0x1dfadffe, mcause=0x2 (illegal instruction)`，与实际行为不一致，也就是还存在别的问题。

在我们感到困惑时，我们内部的验证团队反馈了一个很相似的 bug：紧贴页边界的 RVC 指令被跳过执行了。这是一次沟通不畅导致的问题：InstrUncache 单元在设计时仅检查了地址的低位来判断是否跨页，并不会判断指令长度，因此当 RVC 指令的起始地址位于页边界前的最后一条指令时，InstrUncache 会将其标注为 `incomplete`，这样做的目的是希望复用 IFU 内已有的预译码单元，如果 IFU 预译码发现指令实际已经完整（是 RVC 指令），就应该忽略 InstrUncache 的标注，正常发送到后端执行。但由于沟通问题，IFU 在设计时直接将 InstrUncache 的 `incomplete` 标志作为事实上的指令不完整来处理，导致了上述问题的发生。于 [#5959](https://github.com/OpenXiangShan/XiangShan/pull/5959) 修复了这个问题。

将 #5910 的情况代入新 bug 的分析，RTL 虽然在 `0x1dfadffe` 处检查到了一条非法 RVC 指令，但没有正确将其发送到后端，因此处理器尝试执行下一条，也就是 `0x1dfaf000` 处的指令，发现了 IAF 异常，进而得到了我们观察到的 mtval 和 mepc 值。

至此，我们觉得 bug 已经完全修复了，由于 issue 中提供的 workload 存在缓存一致性问题无法使用，我们自行构造了一个测试用例来验证修复的有效性。但负责的同学不是很熟悉 PMP 的配置流程，~~偷了个懒~~使用 Svpbmt 扩展提供的机制利用页表项来控制 `MMIO`/`X` 属性。在理论上来讲，除了 access fault（物理地址无执行权限）变成 page fault（虚拟地址无执行权限）以外，两者的处理流程和现象应该是一致的。

——然而实际情况让人大跌眼镜，用 Pbmt 配置了第一页 `Pbmt=IO, X=1`，第二页 `Pbmt=IO, X=0` 时，RTL 正确的报告了 `mtval=0x1dfaf000, mepc=0x1dfadffe, mcause=0x1` 的异常，通过了 difftest 检查，前面两个 bug 仿佛从没存在过。

于是我们再次检查了波形，发现尽管将 Pbmt 配置为 IO，RTL 上还是将其作为 cacheable 空间进行了处理，IFU 相关通路完全没有工作，而是由 ICache 提供了正确的响应。检查了 Pbmt 相关通路后，我们发现 Pbmt.PMA 常量的位宽未被显式指定，进而导致 Chisel 自动推断得到的 `s1_itlbPbmt` 寄存器位宽不正确，导致了 `Pbmt=IO`（`2'b10`）被存储为了 `1'b0`，从而作为 `Pbmt=PMA`（`2'b00`）处理了。这个 bug 源自于一年前的一次重构，彼时负责同学觉得 `RegInit(..., init=Pbmt.PMA)` 相比 `RegInit(..., init=0.U(Pbmt.width.W))` 更好看，于是顺手就改了，没想到竟然引入了一个如此隐蔽的 bug。这也暴露出我们的测试套件对于 RVA23 引入的新功能（此处特指 Svpbmt 扩展）的覆盖存在不足。于 [#5962](https://github.com/OpenXiangShan/XiangShan/pull/5962) 修复了这个问题，后续我们也会继续提高测试套件质量。

至此，我们~~再次~~觉得 bug 已经完全修复了，但重新运行新构造的测试用例时仍然报告了一个 difftest 错误：

```plaintext
RTL : mtval=0x1dfaf000, mepc=0x1dfaf000, mcause=0xc (instruction page fault)
NEMU: mtval=0x1dfaf000, mepc=0x1dfadffe, mcause=0xc (instruction page fault)
```

——~~这 mepc 怎么还是不对啊😡~~

总之我们再再次检查了波形，发现 IFU 在处理异常时会忽略其 MMIO 标记（这是符合预期的，反正 ICache 做的 PMP/ITLB 检查已经挂了，直接丢给后端处理就好了，再区分是否 MMIO 没什么意义），因此对于这种一半异常的指令，IFU 内的数据通路会用类似于跨 MMIO-cacheable 边界的指令拼接和元数据选择逻辑来处理。然而不幸的是，这些逻辑是 V3 新加的，设计有点问题且从来没有想过验证过。因此 IFU 实际上丢弃了前一页的元数据，直接按后一页的元数据进行了处理，因此 IFU 实际上认为自己在处理 `0x1dfaf000` 处的指令时遇到了异常，而不是 `0x1dfadffe` 处的指令，最终导致后端计算得到的 mepc 有误。于 [#5985](https://github.com/OpenXiangShan/XiangShan/pull/5985) 修复了这个问题。

至此，我们~~再再次~~觉得 bug 已经完全修复了，这次终于真正通过了测试用例。我们也验证了其余不同属性的组合（例如，两页都可以执行，但 MMIO 属性不一致：第一页 `Pbmt=PMA, X=1`，第二页 `Pbmt=IO, X=1`）都能得到正确的结果。

## 近期进展

### 前端

- RTL 新特性
  - 支持当 BPU 长期预测正确时，丢弃 resolve 请求，从而在降低 BPU 读冲突的同时减少功耗（[#5759](https://github.com/OpenXiangShan/XiangShan/pull/5759)）
- Bug 修复
  - 从后端直接获得排空状态，修复特定情况下 MMIO 取指卡死的问题（[#5787](https://github.com/OpenXiangShan/XiangShan/pull/5787)）
  - 修复 IFU 处理紧贴页边界的 RVC 指令时未正确发送到后端的问题（[#5959](https://github.com/OpenXiangShan/XiangShan/pull/5959)）
  - 修复 ICache `s1_itlbPbmt` 寄存器位宽不正确的问题（[#5962](https://github.com/OpenXiangShan/XiangShan/pull/5962)）
  - 修复 IFU 在处理跨过 MMIO-cacheable 边界的 RVI 指令时，指令拼接及元数据选择有误的问题（[#5985](https://github.com/OpenXiangShan/XiangShan/pull/5985)）
- PPA 优化
  - 调整 UBTB、ABTB、UTAGE 预测流水中 tag 比较、寄存器读等相关逻辑，优化时序（[#5686](https://github.com/OpenXiangShan/XiangShan/pull/5686)）
  - 调整 MBTB 训练流水中 replacer 相关逻辑，优化时序（[#5897](https://github.com/OpenXiangShan/XiangShan/pull/5897)，[#5944](https://github.com/OpenXiangShan/XiangShan/pull/5944)）
  - 调整 TAGE 训练流水，优化时序（[#5890](https://github.com/OpenXiangShan/XiangShan/pull/5890)）
  - 调整 SC 预测流水中计数器和的计算逻辑，优化时序（[#5911](https://github.com/OpenXiangShan/XiangShan/pull/5911)）
  - 调整 SC 训练流水中写回使能计算逻辑，优化时序（[#5923](https://github.com/OpenXiangShan/XiangShan/pull/5923)）
  - 调整 CommonHR 在重定向时计算折叠历史相关逻辑，优化时序（[#5975](https://github.com/OpenXiangShan/XiangShan/pull/5975)）
  - 调整 PHR S1 流水级中计算折叠历史相关逻辑，优化时序（[#5892](https://github.com/OpenXiangShan/XiangShan/pull/5892)）
  - 在 IFU 中使用并行或逻辑代替优先编码器，优化时序（[#5937](https://github.com/OpenXiangShan/XiangShan/pull/5937)）
- 代码质量
  - 使用隐式传参简化 ITTAGE 表的参数传递（[#5924](https://github.com/OpenXiangShan/XiangShan/pull/5924)）

### 后端

- RTL 新特性
  - 支持 smcdeleg/ssccfg 扩展（[#5841](https://github.com/OpenXiangShan/XiangShan/pull/5841)）
- Bug 修复
  - 当后端排空时，返回空状态到 FTQ（[#5787](https://github.com/OpenXiangShan/XiangShan/pull/5787)）
  - 修改 CSR 以支持 debug spec 1.0（[#5952](https://github.com/OpenXiangShan/XiangShan/pull/5952)）
  - （V2）stepie 应该控制 hvictl 注入中断（[#5926](https://github.com/OpenXiangShan/XiangShan/pull/5926)）

### 访存与缓存

- RTL 新特性
  - 将 CoupledL2 的容量增大到 2MB（[#5969](https://github.com/OpenXiangShan/XiangShan/pull/5969)）
- Bug 修复
  - 修复了 unalignQueue 在跨页存储操作出队后未能正确清除队列条目的问题（[#5913](https://github.com/OpenXiangShan/XiangShan/pull/5913)）
  - 为发往 L2 的预取请求添加握手信号以避免无故丢失预取请求（[#5989](https://github.com/OpenXiangShan/XiangShan/pull/5989)）
- PPA 优化
  - 在 DCache 重填过程中仅在替换块为脏时才读取数据，而不是每次都读取数据（[#5956](https://github.com/OpenXiangShan/XiangShan/pull/5956)）
  - 优化了 CoupledL2 的时序，2MB 容量下时序违例从 -130 ps 优化至 -40 ps，最大逻辑级数从 44 级优化至 24 级（[XSCache #4](https://github.com/OpenXiangShan/XSCache/pull/4)）
  - 修复了 CoupledL2 发往 MemBlock 的提前唤醒信号的准确性，并添加了统计准确性的性能计数器（[XSCache #5](https://github.com/OpenXiangShan/XSCache/pull/5), [#5993](https://github.com/OpenXiangShan/XiangShan/pull/5993)）
- 代码重构
  - 新建 XSCache 仓库，并将原 CoupledL2 与 OpenLLC 仓库的代码迁移到 XSCache 仓库中，以解决循环依赖和代码重复等问题（[#5938](https://github.com/OpenXiangShan/XiangShan/pull/5938)，[XSCache #7](https://github.com/OpenXiangShan/XSCache/pull/7)）
  - 移除了 XSCache 对 L2 与 L3 之间 Tilelink 总线协议的支持，仅保留对 CHI 总线协议的支持（[XSCache #6](https://github.com/OpenXiangShan/XSCache/pull/6)）
- 调试工具
  - 添加 pfLateHitType 和 Berti 监控器（[#5964](https://github.com/OpenXiangShan/XiangShan/pull/5964)）

### XSAI

- RTL 新特性
  - 拆分 C 矩阵访存模块的 load 与 store，使两种指令能够重叠执行（[CUTE #11](https://github.com/OpenXiangShan/CUTE/pull/11)）
- Bug 修复
  - 修复 XSAI 向 XSAI DiffTest 传递的错误常量（[XSAI #65](https://github.com/OpenXiangShan/XSAI/pull/65)）
  - 修复 HBL2 的 A 通道 Put Matrix 被 C 通道打断的错误（[XSAI #64](https://github.com/OpenXiangShan/XSAI/pull/64)）
- 代码质量
  - 加速 XSAI FIR elaboration，使 XSAI 生成 Verilog 的速度提高到原来的 4.75 倍（[CUTE #12](https://github.com/OpenXiangShan/CUTE/pull/12)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | dcc1d2689  |
| 日期      | 2026/05/21 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 2MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.42  | 47.53  | 410.bwaves         | 85.27  | 89.88  |
| 401.bzip2           | 27.43  | 28.28  | 416.gamess         | 57.05  | 53.23  |
| 403.gcc             | 55.26  | 38.88  | 433.milc           | 64.93  | 64.04  |
| 429.mcf             | 61.00  | 55.47  | 434.zeusmp         | 71.27  | 64.66  |
| 445.gobmk           | 38.94  | 40.10  | 435.gromacs        | 37.20  | 34.38  |
| 456.hmmer           | 54.38  | 64.72  | 436.cactusADM      | 76.13  | 87.68  |
| 458.sjeng           | 38.87  | 39.48  | 437.leslie3d       | 56.26  | 56.36  |
| 462.libquantum      | 136.67 | 294.84 | 444.namd           | 43.23  | 45.23  |
| 464.h264ref         | 63.46  | 71.99  | 447.dealII         | 64.25  | 68.39  |
| 471.omnetpp         | 41.07  | 39.47  | 450.soplex         | 52.12  | 63.93  |
| 473.astar           | 30.42  | 29.63  | 453.povray         | 73.34  | 65.77  |
| 483.xalancbmk       | 75.83  | 84.61  | 454.Calculix       | 43.74  | 39.61  |
| GEOMEAN             | 50.90  | 54.07  | 459.GemsFDTD       | 63.50  | 63.95  |
|                     |        |        | 465.tonto          | 52.59  | 35.01  |
|                     |        |        | 470.lbm            | 125.82 | 133.04 |
|                     |        |        | 481.wrf            | 54.96  | 41.58  |
|                     |        |        | 482.sphinx3        | 59.39  | 62.42  |
|                     |        |        | GEOMEAN            | 61.07  | 59.18  |

编译参数如下所示：

| 参数             | GCC15       | XSCC                |
| ---------------- | ----------- | ------------------- |
| 编译器           | gcc15       | xscc                |
| 编译优化         | O3          | O3                  |
| 内存库           | jemalloc    | jemalloc            |
| -march           | RV64GCB     | RV64GCB             |
| -ffp-contraction | fast        | fast                |
| 链接优化         | -flto       | -flto               |
| 浮点优化         | -ffast-math | -ffast-math         |
| -mcpu            | -           | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、孙际儒、李衍君
