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
* trigger 使用的状态位

状态位|说明
-|-
allocated|该项已经被 dispatch 分配
datavalid|load 指令已经拿到所需的数据
writebacked|load 指令结果已经写回到寄存器堆并通知 ROB, RS
miss|load 指令未命中 dcache, 正在等待 dcache refill
pending|该 load 指令访问 mmio 地址空间, 执行被推迟. 正在等待指令成为 ROB 中最后一条指令
released|load 指令访问的 cacheline 已经被 dcache 释放 (release)
error|load 指令在执行过程中检测到错误

## Load Queue Enqueue

load 指令进入 load queue 实际分两步完成: enqPtr 的提前分配和 load queue 的实际写入. 

提前分配的原因是 dispatch 模块距离 MemBlock 太远, 将 load
queue 处产生的 `enqPtr` 送到 dispatch 做为 `lqIdx` 需要面临很长的延迟. 南湖架构在 dispatch 附近维护 enqPtr 的提前分配逻辑, 由提前分配逻辑负责提供指令的 `lqIdx`.

### enqPtr 的提前分配

!!! todo
    参见 dispatch 部分, `lqIdx` / `sqIdx` 的[提前分配](../../backend/dispatch.md). 

### Load Queue 实际写入

在 load queue 被实际写入时, load queue 本身的 `enqPtr` 会根据写入 load queue 的指令数量被更新. 出于时序考虑, load queue 只会在 load queue 中 `空项数 >= enq指令数` 的情况下接受 dispatch 分派的指令. 

## Update Load Queue

这一小节描述流水线中的 load 指令更新 load queue 这一过程. 在一条指令在 load 流水线的执行过程中, 可以在多个阶段更新 load queue 的状态.  

### Load Stage 2

在这一阶段, dcache 和前递返回结果, 并将以下内容写入到 load queue 中:

* 关键控制信号
* 物理地址
* 前递结果
* trigger 检查结果

此时会被更新的状态标志位包括: `datavalid`, `writebacked`, `miss`, `pending`, `released`

### Load Stage 3

在这一阶段, 部分上个周期来不及完成的检查返回结果, load queue 会使用这些结果来更新其状态. 例如 `dcacheRequireReplay` 事件(dcache 请求从指令从保留站中重发)一旦触发, 会将 `miss` 和 `datavalid` flag 更新为 false. 这标志着这条指令会从保留站重发, 而不是在 load queue 中等待 refill 将其唤醒. 这一操作与 load 指令流水线中 stage 3 的保留站反馈操作同步发生.

!!! info
    load 流水线中 [load miss](../fu/load_pipeline.md#load-miss) 的处理部分也涉及了 load queue 更新的相关信息

### 特例: MMIO 指令



## Load Refill

若一条 load 指令成功被分配 dcache MSHR, 后续其将在 load queue 中侦听 dcache refill 的结果. 一次 refill 会将数据传递到所有等待这一 cacheline 的 load queue 项. 这些项的数据状态被标识为有效, 随后可以被写回. 如果指令此前已经进行了 store 到 load 的前递, load queue 负责在 refill 时合并前递结果, 参见[Store 到 Load 的前递](../mechanism.md#store-to-load-forward)一节. 下面的示意图展示了一次 dcache refill 前后 load queue 中各项的变化. 

!!! todo
    更新图的描述

![before-refill](../../figs/memblock/before-refill.png)  

![after-refill](../../figs/memblock/after-refill.png)  

在 load queue 拿到 dcache refill 回来的数据后, 就可以开始**从 load queue 写回 miss 的 load 指令**. load queue 为这种指令的写回操作提供了两个端口. 在每个周期, load queue 会分别从奇偶两列中选出最老的已经完成了 refill 但还没写回的指令, 在下一个周期将其通过写回端口写回(出于时序考虑, 写回指令的选择和实际写回放在了前后两个周期来执行). load queue 会和 load 流水线中正常执行的 load 指令争用写回端口. 当 load 流水线中的指令试图写回时, 来自 load queue 的写回请求被阻塞.

## load 指令的完成

load 指令的完成指 load 取得结果, 写回 rob 和 rf 的操作. 写回 ROB 和 RF 的 load 的选择分奇偶两部分进行, 较老的指令优先被选择. 每周期至多选出两条指令被写回. load queue 选择写回的指令有两种: 

* 已经完成的 mmio load 指令
* 此前 miss, 现在已经从 dcache 取得 refill 回来的数据结果的 load 指令

!!! info
    正常命中 dcache 的 load 会直接从流水线写回. 参见 [load pipeline](../fu/load_pipeline.md#stage-2) 部分.

实际写回操作在写回选择的下一拍发生. load queue 会根据选择结果读出对应指令的信息, 根据指令要求完成结果裁剪, 最后争用 load 写回端口将结果写回. load 被成功写回后, `writebacked` flag 会被更新成 false.

!!! note
    注意区分 load 指令写回到 load queue 和 load 从 load queue 写回到 rob 和 rf. 两者是不同的操作.

## load 提交相关机制

rob 在指令提交后, 根据 load 指令提交的数量产生 `lcommit` 信号, 通知 load queue 这些数量的 load 指令已经成功提交.

由于 load queue 与 ROB 间隔较远. load queue 实际使用 `lcommit` 更新内部状态是在 ROB 处进行指令 commit 的两拍之后. load queue 会将已经 commit 的指令 `allocated` flag 更新为 false 以表示其完成. 同时根据提交的 load 的数量(lcommit) 更新队列尾指针 `deqPtr`.

## 指令重定向相关机制

重定向到达 load queue 之后会在 2 拍内更新 load queue 的状态:

* Cycle1: 根据 robIdx 找出所有错误路径上的指令. 被刷掉的指令 allocated 被设置成 false.
* Cycle2: 根据上一拍查找的结果, 统计有多少指令需要被取消, 更新 enqPtr

在目前的设计下, 跳转指令触发重定向后, dispatch queue 中仍然可能有有效的 load 指令需要进入 load queue. 在 cycle2 进行 enqPtr 更新时, 在重定向更新 load queue 期间进入 load queue 的指令是否需要取消会被单独统计. 

<!-- TODO: Cycle2 指令 enq 的处理 -->

<!-- ### 队列指针维护 -->


## store - load 违例检查相关机制

在 store addr 操作向 store queue 中写入地址的同时 (store addr pipeline stage 1), 它也会在 load queue 中搜索物理地址相同但程序序在 store 之后的 load 指令. 如果这些 load 指令已经被执行并产生了错误的结果(即触发 store - load 违例), 则 load queue 会发出重定向请求: 处理器会从这条 load 指令开始, 从取指开始重新执行后续的指令.

对于每条 store 指令, 它的 store - load 违例检查共计需要三个周期. 每个周期执行的操作如下:

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

在地址检查阶段发生 exception 的 mmio 指令会在 Load Stage 2 立即将异常信息写回到 ROB 并更新 load queue. 这样的 mmio 指令不会进行 uncached 访存操作.

不带 exception 的 mmio 指令会在 Load Stage 2 更新 load queue, 将 load queue 中的这条指令标记为等待执行的 mmio 指令. 但其不会将 ROB 中的指令标识为已写回的状态. 当这条指令到达 ROB 的队尾后, ROB 会通知 load queue, 由 load queue 向下发出 uncached 访存请求. uncached 访存请求由一个状态机维护. 在 uncached 访存完成之后, mmio load 如同 miss 的 load 一样, 将数据从 load queue 写回.

<!-- 
## 异常处理和 trigger

TODO -->
