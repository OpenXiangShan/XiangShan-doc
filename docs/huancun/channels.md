# Tilelink 各通道控制

本章将介绍 huancun 中各个通道控制模块的结构。阅读前请提前熟悉 TileLink 总线协议。

通道控制模块分为 Sink 模块和 Source 模块，其中，

* Sink 模块接收 TileLink 总线上的的主动请求和被动响应。对于主动请求（SinkA，SinkB，SinkC），将该请求转换为 huancun 内部请求发送给 MSHR Alloc 模块或者 Request Buffer，对于被动响应，将该响应经过处理后回馈给对应的 MSHR（SinkD，SinkE）

* Source 模块接收 MSHR 的内部请求，经过处理和包装发送到 TileLink 总线上（SourceA，SourceB，SourceC，SourceD，SourceE）

另外，部分模块还会额外接收从 MSHR 发来的 Task，完成一些相关任务。

## SinkA



## SinkB



## SinkC



## SinkD



## SinkE



## SourceA



## SourceB



## SourceC



## SourceD



## SourceE

