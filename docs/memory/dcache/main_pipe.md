# Main Pipeline

NanHu 架构使用 Main Pipeline (dcache 主流水线) 处理 store, probe, 原子指令和替换操作. Main Pipeline 负责所有需要争用 writeback queue 向下层 cache 发起请求/写回数据的指令的执行.

!!! info
    相比上一代雁栖湖架构, 南湖架构将 refill 操作从 Main Pipeline 中独立成单独的流水线. 其他的操作并没有从 Main Pipeline 中剥离, 原因是处理多条流水线间冲突/资源争用的成本超过了拆分流水线的性能收益.

## MainPipe 各级流水线的功能

### Stage 0

* 仲裁传入的 Main Pipeline 请求选出优先级最高者
* 根据请求信息判断请求所需的资源是否就位
* 发出 tag, meta 读请求

### Stage 1

* 获得 tag, meta 读请求的结果
* 进行 tag 匹配检查, 判断是否命中
* 如果需要替换, 获得 PLRU 提供的替换选择结果
* 根据读出的 meta 进行权限检查
* 提前判断是否需要执行 miss queue 访问

### Stage 2

* 获得读 data 的结果, 与要写入的数据拼合
* 如果 miss, 尝试将这次请求信息写入 miss queue

<!-- miss queue 的写入时序很紧张, 这一流水级让写入 miss queue 尽早开始来减轻其对时序的影响-->

### Stage 3

* 根据操作的结果, 更新 meta, data, tag
* 如果指令需要向下层 cache 发起访问/写回数据, 则在这一级生成 writeback queue 访问请求, 并尝试写 writeback queue
* 在 release 操作生效并更新 meta 时, 在这一级向 load queue 给出 release 信号来进行违例判断
* 对于原子指令的特殊支持
    * AMO 指令在这一级停留两拍, 先在这一流水级完成 AMO 指令的运算操作, 再将结果写回到 dcache
    * LR/SC 指令会在这里设置/检查其 reservation set
    queue

<!-- ## 指令执行流程 -->

<!-- !!! todo -->
<!-- 分不同种类的请求(store/probe/replace/atom)说明指令在 mainpipe 中的执行流程 -->

## MainPipe 争用和阻塞

Main Pipeline 的争用存在以下优先级:

1. probe_req
1. replace_req
1. store_req
1. atomic_req

一个请求只有在其所请求的资源全部就绪, 不存在 *set 冲突*, 且没有比它优先级更高的请求的情况下才会被接受. 来自 committed store buffer 的写请求由于时序原因, 拥有单独的检查逻辑.

<!-- ### set 冲突回避 -->

<!-- *set 冲突* 是指: TODO -->


<!-- ## MainPipe 中的错误处理 -->

<!-- !!! todo -->