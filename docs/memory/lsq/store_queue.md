# Store Queue

本章介绍香山处理器南湖架构 store queue 的设计.

南湖架构的 store queue 是一个 64 项循环队列. 其每周期至多: 
* 从 dispatch 处接收 4 条指令
* 从 store addr 流水线接收 2 条指令的地址和控制信息
* 从 store data 流水线接收 2 条指令的数据
* 将 2 条指令的数据写入 committed store buffer
* 为 2 条load流水线提供 store 到 load 前递结果

## Store Queue 每项的内容

Store Queue 每项包含以下的信息:

* 物理地址
* 虚拟地址
* 数据
* 数据有效 mask
* 状态位
    * allocated
    * addrvalid
    * datavalid
    * committed
    * (mmio) pending
    * mmio

状态位|说明
-|-
allocated|该项已经被 dispatch 分配
addrvalid|store 指令已经拿到所需的地址
datavalid|store 指令已经拿到所需的数据
committed|store 指令已经提交
mmio|该 store 指令访问 mmio 地址空间
pending|该 store 指令访问 mmio 地址空间, 执行被推迟. 正在等待指令成为 ROB 中最后一条指令

## store queue 分配和 enqueue

store 指令进入 store queue 实际分两步完成: enqPtr 的提前分配和 store queue 的实际写入. 此处 store 的处理流程与 load 类似, 参见 [load queue enqueue](./load_queue.md#load-queue-enqueue)一节.

## issuePtr

`issuePtr` 指示在此 sqIdx 之前的 store 指令数据和地址均已就绪. store queue 对外提供这个指针来辅助保留站调度那些依赖于前导 store 指令的 load 指令. issuePtr 是一个非精确的指针(尽量精确, 但不强求).

## store 更新 store queue

### store addr

一条 store 指令会在 sta 流水线的 store stage 1 / stage 2 更新 store queue. 其中, store stage 1 更新地址和绝大多数状态位. 如果没有 TLB miss 等问题的话, 设置 `addrvalid` flag. stage 2 更新 `mmio` 和 `pending` 两个 flag. 其中, 在 stage 2 才更新 `mmio` 和 `pending` flag 的原因是 PMA 检查指令是否位于 MMIO 区域的时序紧张.

### store data

在保留站发出的 store data 会被立即写入 store queue. 写入的同时会设置 `datavalid` flag.  

<!-- ### 特例

* (1) For an mmio instruction with exceptions, we need to mark it as addrvalid (in this way it will trigger an exception when it reaches ROB's head) instead of pending to avoid sending them to lower level.
* (2) For an mmio instruction without exceptions, we mark it as pending. When the instruction reaches ROB's head, StoreQueue sends it to uncache channel. Upon receiving the response, StoreQueue writes back the instruction through arbiter with store units. It will later commit as normal. -->

## store 提交相关机制

rob 在指令提交后, 根据 store 指令提交的数量产生 `scommit` 信号, 通知 store queue 这些数量的 store 指令已经成功提交. 由于 store queue 与 ROB 间隔较远. store queue 实际使用 scommit 更新内部状态是在 ROB 处进行指令 commit 的两拍之后. 

store queue 会将已经 commit 的指令 `committed` flag 更新为 true 以表示其已经提交, 可以被写入 sbuffer 中.

## store 写入 sbuffer

已经被提交的 store 指令不会被取消, 并且会按顺序被从 store queue 中读出写入 sbuffer.

随着 store queue 的不断增大, 从 store queue 中读出数据的时间也变得越来越长. 同时, sbuffer 在接受来自 store queue 写入的数据的过程中需要做检查, 这个检查的逻辑很长(参见 [sbuffer](../lsq/committed_store_buffer.md#) 中有关 sbuffer 写入的描述). 为了时序考虑, 南湖架构会用一整个周期的时间来从 store queue 中读出数据. 在下一个 cycle, store queue 才会尝试将前一个周期读出的数据写入 sbuffer 中.

在 store data 被写入 sbuffer 之前(意味着 sbuffer 可以提供 store to load 前递结果), store queue 中的这一项一直会保持有效状态, 来保证 store to load 前递能正确拿到 store 结果.

## store to load forward query

在 load 指令进行 store to load forward query 时, sbuffer 会向 load 指令提供在这条指令之前, 但未写入 sbuffer 的 store 的 data. 在当前的[前递机制](../mechanism.md#store-to-load-forward)下, 来自 store queue 的前递采用虚地址前递, 实地址检查.

### 产生前递结果

<!-- Compare deqPtr (deqPtr) and forward.sqIdx, we have two cases:

* (1) if they have the same flag, we need to check range(tail, sqIdx)
* (2) if they have different flags, we need to check range(tail, LoadQueueSize) and range(0, sqIdx) -->

用于前递的**数据**产生流程如下: 使用实地址查询, 产生实地址匹配命中向量. 随后, 使用命中向量从 store queue 中生成各个 byte 的前递结果. 前递数据将会在前递请求产生的下一拍被反馈到 load 流水线中.

### addr valid data invalid

在前递逻辑尝试将 store 的数据传递到后续的 load 中时, 可能会出现 store 的地址就绪但是数据未就绪的情况. 前递逻辑会在检查到这种情况时通知向 load pipeline stage1 反馈结果, 由[load 流水线中的相关逻辑](../fu/load_pipeline.md#store-data-invalid)负责后续处理.

### 前递正确性检查

为了确保使用虚拟地址产生的前递结果是正确的结果, store queue 会进行虚地址前递相关检查: 一旦在前递时发现虚实地址的匹配结果不同, 如果结果不一致, 则将不一致信息反馈到 load 流水线. 由 load 流水线进行[前递错误的处理](../fu/load_pipeline.md#forward-failure).

## 指令重定向相关机制

与 load queue 类似. 参见 [load queue 中的重定向逻辑](../lsq/load_queue.md#redirect).

## MMIO (uncached 访存)

store queue 的 MMIO 访存机制与 load queue 的 [MMIO 访存](../lsq/load_queue.md#mmio-uncached-%E8%AE%BF%E5%AD%98) 基本一致.

## flush store queue

store queue 本身不含 flush 逻辑, 但是 store queue 会对外输出空满信号. 在需要 flush store queue 时, sbuffer 会进入刷新状态, 向 dcache 写入其中的所有数据, 直到 store queue 和 sbuffer 都不含有效数据为止. 在这一过程中, store queue 会不断将其中已经提交 store 指令的数据写入到 sbuffer 中.
