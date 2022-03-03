# Load Queue

本章介绍香山处理器南湖架构 load queue 的设计.

南湖架构的 load queue 是一个 80 项循环队列. 其每周期至多: 

* 从 dispatch 处接收 4 条指令
* 从 load 流水线接收 2 条指令的结果, 以更新其内部的状态
* 从 dcache 接收 miss refill 结果, 更新 load queue 中全部等待此次 refill 的指令的状态
* 写回 2 条 miss 的 load 指令. 这些指令已经取得了 refill 的数据, 会与正常的访存流水线争用两个写回端口

一级数据缓存 refill 时，会将一整个 cacheline 的所有数据反馈给 load queue, 所有在 load queue 中等待这一 cacheline 数据的指令都会得到数据.

## Load Queue 每项的内容

Load Queue 每项包含以下的信息:

* 物理地址
* 虚拟地址 (debug)
* 重填数据项
* 状态位
    * allocated
    * datavalid
    * writebacked (completed)
    * released
    * error
    * miss
    * (mmio) pending
* trigger 使用的状态位

TODO: 解释

## load queue 分配和 enqueue

load 指令进入 load queue 实际分两步完成: enqPtr 的提前分配和 load queue 的实际写入. 

> TODO: 提前分配的目的

enqPtr 的提前分配使得指令可以更早地获得自身的 lqIdx.

### enqPtr 的提前分配

TODO

### load queue 实际写入

Currently, LoadQueue only allows enqueue when #emptyEntries > EnqWidth

## 流水线中的 load 指令更新 load queue

Most load instructions writeback to regfile at the same time.

However,

* (1) For an mmio instruction with exceptions, it writes back to ROB immediately.
* (2) For an mmio instruction without exceptions, it does not write back. The mmio instruction will be sent to lower level when it reaches ROB's head. After uncache response, it will write back through arbiter with loadUnit.
* (3) For cache misses, it is marked miss and sent to dcache later. After cache refills, it will write back through arbiter with loadUnit.

### load stage 2 的更新

这一 stage, dcache 和前递返回结果. 写入的内容包括:

* 关键控制信号
* 物理地址
* 前递结果
* trigger 检查结果

此时会被更新的状态标志位包括:

* datavalid
* writebacked
* miss
* pending
* released

### load stage 3 的更新

这一 stage, 部分在上个周期来不及完成的检查返回结果. load queue 会使用这些结果来更新其状态.

dcacheRequireReplay 事件会将 miss 和 datavalid flag 更新为 false. 这标志着这条指令会从保留站重发, 而不是在 load queue 中等待 refill 将其唤醒. 这一操作与 load 指令流水线中 stage 3 的保留站反馈操作同步发生. 参见 load pipeline 部分 (TODO).

## load refill 相关机制

TODO

## load 写回相关机制

写回 load 的选择分奇偶两部分进行, 较老的指令优先被选择. 每周期至多选出两条指令被写回.

load queue 选择写回的指令有两种: 

* 已经完成的 mmio load 指令
* 此前 miss, 现在已经从 dcache 取得 refill 回来的数据结果的 load 指令

> 正常命中 dcache 的 load 会直接从流水线写回. 参见 load pipline 部分 (TODO).

实际写回操作在写回选择的下一拍发生. load queue 会根据选择结果读出对应指令的信息, 根据指令要求完成结果裁剪, 最后争用 load 写回端口将结果写回. load 被成功写回后, writebacked flag 会被更新成 false.

## load 提交相关机制

rob 在指令提交后, 根据 load 指令提交的数量产生 lcommit 信号, 通知 load queue 这些数量的 load 指令已经成功提交.

由于 load queue 与 ROB 间隔较远. load queue 实际使用 lcommit 更新内部状态是在 ROB 处进行指令 commit 的两拍之后. load queue 会将已经 commit 的指令 allocated flag 更新为 false 以表示其完成. 同时根据提交的 load 的数量(lcommit) 更新队列尾指针 deqPtr.

## 指令重定向相关机制

重定向到达 load queue 之后:

* Cycle1:
    * 根据 robIdx 找出所有错误路径上的指令. 被刷掉的指令 allocated 被设置成 false.
* Cycle2:
    * 根据上一拍查找的结果, 统计有多少指令需要被取消, 更新 enqPtr

注意 enqPtr 的更新是在 cycle2, cycle1的 还在正常 enq, 这些指令是否需要取消会被单独统计.

TODO: Cycle2 指令 enq 的处理

### 队列指针维护


## store - load 违例检查相关机制

When store writes its addr to store queue (store addr pipeline stage 1), it searches LoadQueue for younger load instructions with the same load physical address. They loaded wrong data and need re-execution.

* Cycle 0: Store Writeback
    * Generate match vector for store address with rangeMask(stPtr, enqPtr).
    * Besides, load instructions in LoadUnit_S1 and S2 are also checked.
* Cycle 1: Redirect Generation
    * There're three possible types of violations, up to 6 possible redirect requests.
    * Choose the oldest load (part 1). (4 + 2) -> (1 + 2)
* Cycle 2: Redirect Fire
    * Choose the oldest load (part 2). (3 -> 1)
    * Prepare redirect request according to the detected violation.
    * Fire redirect request (if valid)

```
 stage 0:        lq l1 wb     l1 wb lq
                 |  |  |      |  |  |  (paddr match)
 stage 1:        lq l1 wb     l1 wb lq
                 |  |  |      |  |  |
                 |  |------------|  |
                 |        |         |
 stage 2:        lq      l1wb       lq
                 |        |         |
                 --------------------
                          |
                      rollback req
```

### 违例恢复

如果检查出存在违例, 且触发违例的指令尚未被其他来源的重定向请求取消, 则发出重定向请求, 并更新访存违例预测器. st-ld 违例发出的重定向请求与分支预测错误的重定向请求处理方式相似, 不需要等待指令到达 ROB 队尾才向前端发出重定向请求.

## load - load 违例检查相关机制

When load arrives load_s1, it searches LoadQueue for younger load instructions with the same load physical address. If younger load has been released (or observed), the younger load needs to be re-execed.

为了实现上述的检查, load queue 包含以下机制fa l se:

* release 更新 load queue 中的对应项
* load 在执行时检查之后的 load
* 如果发现之后的 load 拿到了更老的结果 (即已经被 release), 从这条 load 开始重新执行

### release 更新 load queue 中的对应项

dcache 会向 load queue 发送 release 信号来标识 dcache 已经失去了对某一 cacheline 的读权限. dcache release 信号产生标志着 dcache 会将这一拍之后对相同 cacheline 的 load 全部标记为 miss, 直到 dcache 重新获得这一行的权限为止. 参见 dcache mainpipe 部分. 

> Future Work: 目前所有的 release 操作都会产生 dcache release 信号. 这里可以进行细化, TtoB 不需要产生 dcache release 信号

为时序考虑, dcache release 信号到达 load queue 加了拍. dcache 和 huancun (l2 cache) 的设计保证了在 dcache release 信号产生后(意味着 dcache 放弃对一个 cacheline 的读权限)的至少 3 个周期之内, dcache 不会重新获得对对应行的读权限. 在此基础上, load - load 违例检查发生的时机有以下几种情况:

TODO: ld-ld 违例图(从 github 上拿下来)

### load 指令查询之后的 load 指令是否已经被 release

在 load pipeline stage 1 开始查询

使用虚地址查询

会与 release 更新 load queue 中的对应项争用 load paddr cam 端口, release 更新 load queue 有更高的优先级. 如果争用不到资源, 则标记这条指令, 将其立刻从保留站重发.

### 违例恢复

For now, if re-exec it found to be needed in load_s1, we mark the older load as replayInst, the two loads will be replayed if the older load becomes the head of rob. When dcache releases a line, mark all writebacked entrys in load queue with the same line paddr as released.

## MMIO (uncached 访存)

States:

* (1) writeback from store units: mark as pending
* (2) when they reach ROB's head, they can be sent to uncache channel
* (3) response from uncache channel: mark as datavalid
* (4) writeback to ROB (and other units): mark as writebacked
* (5) ROB commits the instruction: same as normal instructions

## 异常处理和 trigger

TODO

## 性能计数器

计数器名称|描述
-|-
rollback|-
mmioCycle|-
mmio_Cnt|-
refill|-
writeback_success|-
writeback_blocked|-
ltq_1_4_valid|-
ltq_2_4_valid|-
ltq_3_4_valid|-
ltq_4_4_valid|-