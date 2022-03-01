# Store Pipeline

香山处理器(雁栖湖架构)包含两条 store addr (sta) 流水线, 每条 store addr 流水线分成4个流水级. 前两个流水级负责将 store 的控制信息和地址传递给 store queue, 后两个流水级负责等待访存依赖检查完成.

![storepipe](../../figs/memblock/store-pipeline.png)  

## sta 流水线的划分

各级流水线的划分如下:

Stage 0
* 计算虚拟地址
* 虚拟地址送入 TLB

Stage 1
* TLB 生成物理地址
* 物理地址送入 store queue
* 开始进行访存依赖检查 

Stage 2
* 访存依赖检查

Stage 3
* 完成访存依赖检查 
* 通知 ROB 可以提交指令

## std 流水线的划分

TODO

## Store 的执行流程

TODO
