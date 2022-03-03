# 原子指令的实现

本章介绍香山处理器南湖架构的原子指令处理流程。

<!-- > 注意：原子指令的处理流程在下个版本可能发生变动 -->

## 原子指令的执行流程

南湖架构的原子指令由一个单独的状态机负责控制执行.

一条原子指令会经历以下状态

* s_invalid
* s_tlb
* s_pm
* s_flush_sbuffer_req
* s_flush_sbuffer_resp
* s_cache_req 
* s_cache_resp
* s_finish

对于 store 指令, 只有在它的 addr 和 data 都就绪时, 处理流程才会开始. (TODO)

## dcache 对原子指令的支持

目前, 香山(南湖架构)的所有原子指令都是在 dcache 处理的.

<!-- 这就意味着, 当一个核要执行原子指令时, 它所属的 dcache 会先去获取所需的权限. -->

原子指令 miss 的处理流程

### 对于 lr/sc 的特殊支持
jin x
lr/sc 的要求(TODO: 展开描述):

* 分配保留区
* 在一定条件下需要保证 lr 成功

在 lr 分配的保留区会经历以下阶段

* 独占, 阻止对这个区域的 probe
* 防止后续的 lr, 但允许 probe
* 超时, 清空

如果 lr 后续还有 lr, 在第二阶段之后会直接再次进入独占状态. 不会出现两条指令的独占状态前后衔接的情况. 此时对应的地址可以被 probe.

### 对于 amo 指令的支持

dcache 会在 mainpipe 中进行 amo 指令所定义的运算操作. 参见 dcache mainpipe 部分. 

## 原子指令的例外处理

地址检查机制检查到例外时, 直接从 s_pm 进入 s_finish, 不会刷新 sq, sbuffer, 不会产生实际访存请求. dcache 不会感知到原子指令.

## 原子指令的 trigger 支持

TODO