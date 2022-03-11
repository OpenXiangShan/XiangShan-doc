# Main Pipeline

NanHu 架构使用 Main Pipeline (dcache 主流水线) 处理 store, probe, 原子指令和替换操作.

!!! todo
    相比雁栖湖架构的变化

## MainPipe 各级流水线的功能

!!! todo
    1111

## 指令执行流程

!!! todo
    分不同种类的请求(store/probe/replace/atom)说明指令在 mainpipe 中的执行流程

## MainPipe 争用和阻塞

!!! todo
    介绍 Mainpipe 争用的优先级设计, set 阻塞设计, 以及相关的时序考虑

## MainPipe 中的错误处理

!!! todo
    看心情

## 补充

!!! todo
    这里介绍一些时序相关的设计细节, 包括: 写 MSHR 的时序考虑, WBQ 相关的操作为何都集中在主流水线