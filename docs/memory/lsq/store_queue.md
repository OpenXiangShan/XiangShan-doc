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

TODO: 解释

## store queue 分配和 enqueue

store 指令进入 store queue 实际分两步完成: enqPtr 的提前分配和 store queue 的实际写入. 此处 store 的处理流程与 load 类似, 参见 [load queue enqueue](./load_queue.md#load-queue-enqueue)一节.

## issuePtr

`issuePtr`指示在此 sqIdx 之前的 store 指令数据和地址均已就绪. store queue 对外提供这个指针来辅助保留站调度那些依赖于前导 store 指令的 load 指令.

issuePtr 是一个非精确的指针(尽量精确, 但不强求). issuePtr 的更新: TODO

## store 写回到 store queue

### store addr

一条 store 指令会在 sta 流水线的 store stage 1 / stage 2 更新 store queue. 其中, store stage 1 更新地址和绝大多数状态位. 如果没有 TLB miss 等问题的话, 设置 addrvalid flag. stage 2 更新 mmio 和 pending 两个 flag.

!!! note
    在 stage 2 才更新 mmio 和 pending flag 的原因是 PMA 检查指令是否位于 MMIO 区域的时序紧张.

### store data

在保留站发出的 store data 会被立即写入 store queue. 写入的同时会设置 datavalid flag.  

### 特例

* (1) For an mmio instruction with exceptions, we need to mark it as addrvalid (in this way it will trigger an exception when it reaches ROB's head) instead of pending to avoid sending them to lower level.
* (2) For an mmio instruction without exceptions, we mark it as pending. When the instruction reaches ROB's head, StoreQueue sends it to uncache channel. Upon receiving the response, StoreQueue writes back the instruction through arbiter with store units. It will later commit as normal.

## store 提交相关机制

rob 在指令提交后, 根据 load 指令提交的数量产生 scommit 信号, 通知 store queue 这些数量的 store 指令已经成功提交. 由于 store queue 与 ROB 间隔较远. store queue 实际使用 scommit 更新内部状态是在 ROB 处进行指令 commit 的两拍之后. 

store queue 会将已经 commit 的指令 committed flag 更新为 true 以表示其已经提交, 可以被写入 sbuffer 中.

## store 写入 sbuffer

committed stores will not be cancelled and can be sent to lower level. store queue 会将已经提交的 store 顺序读出写入 sbuffer.

As store queue grows larger and larger, time needed to read data from data module keeps growing higher. Now we give data read a whole cycle. 在下一个 cycle, store queue 才会尝试将前一个周期读出的 data 写入 sbuffer 中.

!!! note
    sbuffer 在接受来自 store queue 写入的数据的过程中需要做检查. 这个检查的逻辑很长, 需要单独的一拍(参见 sbuffer TODO). 这也是为什么我们要将读出数据和写入 sbuffer 拆成两拍的原因.

在 store data 被写入 sbuffer 之前, store queue 中的这一项一直会保持有效状态, 来保证 store to load 前递能正确拿到 store 结果.

## store to load forward query

    * Check store queue for instructions that is older than the load.
    * The response will be valid at the next cycle after req.

### 产生前递结果

Compare deqPtr (deqPtr) and forward.sqIdx, we have two cases:

* (1) if they have the same flag, we need to check range(tail, sqIdx)
* (2) if they have different flags, we need to check range(tail, LoadQueueSize) and range(0, sqIdx)

使用实地址查询, 产生命中向量

使用命中向量从 store queue 中生成各个 byte 的前递结果.

### addr valid data invalid

检查到时通知 load pipeline stage1, 后续处理参见 load 流水线部分(TODO).

### 虚地址前递支持

关于虚地址前递机制的说明, 参见 load 流水线部分(TODO).

虚实地址做一样的检查比对结果

如果结果不一致, 将不一致信息反馈到 load 流水线

## 指令重定向相关机制

与 load queue 类似. 参见 load queue (TODO)

## MMIO (uncached 访存)

store queue 的 MMIO 访存机制与 load queue 的 MMIO 访存 (TODO) 基本一致.

## flush store queue

store queue 本身不含 flush 逻辑, 但是 store queue 会对外输出空满信号. 在需要 flush store queue 时, sbuffer 会进入刷新状态, 向 dcache 写入其中的所有数据, 直到 store queue 和 sbuffer 都不含有效数据为止. 在这一过程中, store queue 会不断将其中已经提交 store 指令的数据写入到 sbuffer 中.

## 硬件性能计数器

计数器名称|描述
-|-
mmioCycle|-
mmioCnt|-
mmio_wb_success|-
mmio_wb_blocked|-
stq_1_4_valid|-
stq_2_4_valid|-
stq_3_4_valid|-
stq_4_4_valid|-