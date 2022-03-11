# 原子指令的实现

本章介绍香山处理器南湖架构的原子指令处理流程。

!!! note
    原子指令的处理流程在下个版本可能发生变动

## 原子指令的执行流程

南湖架构的原子指令由一个单独的状态机负责控制执行. 一条原子指令会经历以下状态:

* s_invalid: 状态机空闲
* s_tlb: 原子指令发出 TLB 查询请求
* s_pm: 完成 TLB 查询和地址例外检查
* s_flush_sbuffer_req: 发出 sbuffer/sq flush 请求
* s_flush_sbuffer_resp: 等待 sbuffer/sq flush 请求完成
* s_cache_req: 向 dcache 发起原子指令操作
* s_cache_resp: 等待 dcache 返回原子指令结果
* s_finish: 结果写回

对于 store 指令, 只有在它的 addr 和 data 都就绪时, 处理流程才会开始.

## dcache 对原子指令的支持

目前, 香山(南湖架构)的所有原子指令都是在 dcache 处理的. dcache 使用主流水线(MainPipe)执行原子指令. MainPipe 若发现原子指令 miss, 则会向 MissQueue 发起请求. MissQueue 从 l2 cache 取得数据后, 再执行原子指令. 若原子指令执行时 MissQueue 满, 则不断尝试重发原子指令, 直到 MissQueue 接收原子指令的 miss 重填请求为止. dcache 内部使用一个一项的 `AtomicsReplayEntry` 来负责原子指令的调度.

### 对于 lr/sc 的特殊支持

RISC-V spec 定义了 constrained LR/SC loops (参见 Volume I: RISC-V Unprivileged ISA: 8.3 Eventual Success of Store-Conditional Instructions). 受到 Rocket 的启发, 香山提供了类似的机制来处理 constrained LR/SC loops.

在 lr 指令执行之后, 处理器会依次进入以下三种状态:

1. 阻塞对当前核当前 cacheline 的所有 probe 请求并阻塞后续 lr 的执行, 持续一段时间 (`lrscCycles` - `LRSCBackOff` cycles)
1. 持续阻塞后续 lr 的执行, 但允许对这一 cacheline 的 probe 请求执行, 持续一段时间 (`LRSCBackOff` cycles)
1. 恢复到正常状态

对于香山(南湖), 在 `lrscCycles` - `LRSCBackOff` 周期内, constrained LR/SC loop (最多 16 条指令) 一定能执行完. 在这段时间内, 对 LR 所设置的 reservation set 中地址的 probe 操作将会被阻塞. 当前 hart 能不被打扰的执行一个成功的 SC. 随后的 `LRSCBackOff` 周期内后续的 lr 不会执行, 来防止两个核同时执行 lr, 结果两者都不能接受 probe 请求, 两者都拿不到权限从而卡死的情况. 加入这个退避阶段后, 来自其他核的 probe 请求可以取得 cacheline 的权限.

### 对于 amo 指令的支持

dcache 会在 mainpipe 中进行 amo 指令所定义的运算操作. 参见 [dcache mainpipe](../dcache/dcache.md) (TODO) 部分. 

## 原子指令的例外处理

地址检查机制检查到例外时, 原子指令状态机会直接从 `s_pm` 进入 `s_finish`, 不会触发 store queue 和 sbuffer 刷新操作, 不会产生实际访存请求. dcache 不会感知到原子指令.

## 调试相关

原子指令的 trigger 仅支持使用 vaddr 触发.