核内访存子系统整体设计
===========

![整体流水线](../images/lsu/ls-pipe.png)  

香山处理器(雁栖湖架构)核内的访存子系统如上图所示. 其中包含
两条 [load 流水线](./load流水线设计.md)和两条 [store 流水线](./store流水线设计.md). [load queue](load-queue.md) 和 [store queue](./store-queue.md) 负责维护访存指令的顺序信息. load queue 会在 load 指令在一级缓存中缺失时负责监听后续的重填结果并执行写回操作. store queue 负责在指令提交之前暂存 store 的数据, 并为 store 向 load 的前递提供数据. 

在 store 指令提交之后, store queue 会将其中的数据搬运到 [committed store buffer](./committed-store-buffer.md). committed store buffer 会以缓存行为单位对 store 的写请求进行合并, 在接近满的时候将合并后的多个 store 写请求一并写入到一级数据缓存中.

[一级数据缓存](./一级数据缓存.md)对核内访存组件暴露两个位宽为64的读端口和一个与一级数据缓存行宽度相同的写端口, 以及一个与一级数据缓存行宽度相同的数据重填端口.

store 向 load 的前递, TLB 缺失的处理等机制, 将在[访存机制介绍](./访存相关机制介绍.md)处详细解释.