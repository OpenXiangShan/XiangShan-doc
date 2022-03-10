# 乱序访存机制

这一章介绍香山处理器中实现乱序访存的关键机制.

## Load Hit

在一条 load 指令命中时, 这条 load 指令从保留站中发出后会经历 3 个 stage:

* Stage 0: 计算地址, 读 TLB, 读 dcache tag
* Stage 1: 读 dcache data
* Stage 2: 获得读结果，选择并写回

在 stage 2 之后, 还会有一个额外的 stage 处理 stage 2 来不及完成的状态的更新. 关于各个阶段执行操作的细节, 参见 [load 流水线](./fu/load_pipline.md) 的详细介绍.

## Sta and Std

store 指令的 address 计算部分在从保留站中发出后会经历 4 个 stage, 详细参见 [sta 流水线](./fu/store_pipeline.md#Sta-Pipeline):

* Stage 0: 计算地址, 读 TLB
* Stage 1: addr 和其他控制信息写入 store queue, 开始违例检查
* Stage 2: 违例检查
* Stage 3: 违例检查, 允许 store 指令提交

store 指令的 data 计算部分在从保留站中发射后, 会直接从保留站中将数据搬运到 store queue, 参见 [std 流水线](./fu/store_pipeline.md#Std-Pipeline).

各个阶段执行操作的细节, 参见 [load 流水线](./fu/load_pipline.md) 的详细介绍.

## Load Miss 的处理

参见 [Load Miss](./fu/load_pipline.md#Load-Miss).

## Replay From RS

这一节介绍 load 指令和 sta 操作从保留站重发(replay)的机制.

以 load 指令为例. 在一些事件发生时, 我们将从保留站中重发这些 load 指令:

* TLB miss
* L1 DCache MSHR full
* DCache bank conflict
* 前递时发现地址匹配但数据未就绪 (Data invalid)

这些事件的共同特点是:

* 发生频率不高(相比于正常的访存指令)
* 这些事件发生时访存指令无法正常执行 
* 在一段时间后再执行相同的访存指令, 这些事件不会发生
    * 例如, TLB miss 事件会在 PTW 完成 TLB 重填之后消失

从保留站重发机制的作用是让这些指令在保留栈中稍作等待, 在一定的周期之后重新执行. 这一机制的实现如下: 一条指令从访存 RS 中发射之后仍然需要保留在 RS 中, 访存指令在离开流水线时向 RS 反馈是否需要从保留站重发. 需要从保留站重发的指令会在 RS 中继续等待在一定时间间隔之后重新发射.

目前, load 流水线中有两个向保留站反馈是否需要重发指令的端口. 这两个端口分别位于 load stage 1 (feedbackFast) 和 load stage 3 (feedbackSlow) . 在 load stage 0 和 load stage 1 可以被检查出的需要重发的指令会通过 load stage 1 的 feedbackFast 端口将重发请求反馈到保留站. 在 load stage 2 才能被检查出的重发请求将在 load stage 3 的 feedbackSlow 端口反馈到保留站. 两个端口的设计是为了让保留站能更早地重发一些需要重发的指令.
    
在 feedbackFast 端口产生重发请求后, 对应的指令不会在流水线里继续流动. 亦即, feedbackSlow 端口不会产生这条指令的反馈.

store addr (sta) 流水线只设置了一个反馈端口. 在 store stage 1, store 流水线就会向保留站报告是否需要重发这条指令.

除了是否要进行指令重发的信息, 重发反馈端口还包括以下信息：

* 使用保留站 index（rsIdx）索引要重发的指令在保留站中的位置
* 使用 sourceType 域区分不同的重发原因shi yong quan
* 为 load 发现之前的 store 地址就绪但数据未就绪的情况, 提供了反馈这条 store sqIdx 的接口

!!! note
    这一机制可能在下一版设计中发生变动.

## Store To Load Forward

Store 到 Load 的前递 (Store To Load Forward, STLF) 是指在 store 指令的数据被写入到数据缓存之前, 后续访问相同地址 load 指令从核内的访存队列和缓冲区获得这条 store 指令数据的操作.

store 到 load 的前递操作被分配到三级流水执行。在前递操作期间前递逻辑会并行检查 committed store buffer 和 store queue 中是否存在当前 load 需要的数据。如果存在，则将这些数据合并到这一次 load 的结果中。

### 虚地址前递

为了时序考虑，使用虚地址进行前递，实地址检查来进行前递。

基本思路
需要恢复

TODO：图

虚地址前递的数据通路如下：load 流水线的 stage 0 会根据指令的 sqIdx，生成数据前递所使用的 mask。在 load 流水线的 stage 1，虚拟地址和 mask 被发送到 store queue 和 committed store buffer 进行前递查询。在 load 流水线的 stage 2，store queue 和 committed store buffer 产生前递查询结果，这些结果会和 dcache 读出的结果合并。

虚地址前递的控制通路如下：

检查发现错误后，触发回滚并刷新 committed store buffer。这样的操作会将引发错误的虚地址从 store queue 和 committed store buffer 中排除出去。

> 作为对比，实地址前递的流程如下： load 流水线的 stage 0 会根据指令的 sqIdx，生成数据前递所使用的 mask。在 load 流水线的 stage 1，TLB 反馈回物理地址，此物理地址和 mask 被发送到 store queue 和 committed store buffer 进行前递查询。在 load 流水线的 stage 2，store queue 和 committed store buffer 产生前递查询结果，这些结果会和 dcache 读出的结果合并。控制和数据通路均遵循这一流程。

### 实地址检查

### 前递结果的保存

如果 DCache miss, 保留 forward 结果。 Forward 的结果（mask 和 data）会被写入到 load queue 中。后续 dcache refill 结果时，load queue 会负责合并 refill 上来的数据和 forward 的结果，最终生成完整的 load 结果。

### 前递相关的性能优化

dcache miss 但前递完全命中时的优化

时序考虑：来不及将这种指令标成命中状态

交给 load queue 去做处理

load queue 会立刻发现这样的指令不需要等待 dcache refill 的结果。这样的指令可以被直接选取并写回。

## Store Load Violation 

store-load 违例检查和恢复

### 违例检查流程

在 store 指令到达 stage 1 时开始进行 load 违例检查. 如果在检查过程中发现了 load 违例, 则触发 load 违例的 store 不会在 ROB 中被标记为*可以提交*的状态. 同时, 回滚操作会立刻被触发, 无需等待触发 load 违例的 store 指令提交.

### 违例检查失败恢复

## Load Load Violation

load-load 违例检查和恢复

TODO

### 违例检查流程

### 违例检查失败恢复

### 违例检查资源争用

## load 写回端口的争用

南湖架构提供了两个 load 写回端口。这个端口负责将 load 的结果写回到保留站，寄存器堆，并通知 ROB 指令已经完成执行。load 流水线的 stage 2 和 load queue 都可以使用这个端口写回结果。两者会争抢这一端口的使用权。

正常情况下，流水线中的 load 指令拥有更高的优先级。

## 需要从保留站重发的事件

部分事件发生时, 访存指令无法正常完成, 需要从保留站重新发射这条访存指令. TLB miss, bank conflict 等都可能导致这样的重发. 参见 load 流水线 和 store 流水线部分.
