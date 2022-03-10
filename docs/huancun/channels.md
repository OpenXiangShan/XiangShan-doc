# Tilelink 各通道控制

本章将介绍 huancun 中各个通道控制模块的结构。阅读前请提前熟悉 TileLink 总线协议。

通道控制模块分为 Sink 模块和 Source 模块，其中，

* Sink 模块接收 TileLink 总线上的的主动请求和被动响应。对于主动请求（SinkA，SinkB，SinkC），将该请求转换为 huancun 内部请求发送给 MSHR Alloc 模块或者 Request Buffer，对于被动响应，将该响应经过处理后回馈给对应的 MSHR（SinkD，SinkE）

* Source 模块接收 MSHR 的内部请求，经过处理和包装发送到 TileLink 总线上（SourceA，SourceB，SourceC，SourceD，SourceE）

另外，部分模块还会额外接收从 MSHR 发来的 Task，完成一些相关任务。



## SinkA

SinkA 把从 A 通道接收到的请求转发给 MSHR Alloc，如果不带数据则直接转发；如果有数据（如 PutData 等）则需要存进 PutBuffer。数据的各个 Beat 以一个数组的形式存进 PutBuffer 中的空闲项，并把该空闲项索引一并转发给 MSHR Alloc。

存入 PutBuffer 的数据会被 SourceD 或者 SourceA 所使用。当该 Put 请求在 Cache 中 Hit 时，由 SourceD 负责将其写入 DataStorage 中；当 Miss 时，由 SourceA 负责直接转发到下一级 Cache 或内存。

当接收一个新请求时，A 通道会因为 MSHR Alloc 不 ready 或者 PutBuffer 为满（当有数据时）而阻塞；一旦接收一个带数据的请求后，不会阻塞其后续 Beat 的接收。

【图片】



## SinkB

SinkB 把从 B 通道接收到的请求转发给 MSHR Alloc，除此之外无任何逻辑。



## SinkC

SinkC 接收上层释放权限或数据的请求，包括 Client 主动释放的 Release/ReleaseData 以及被动释放的应答 ProbeAck/ProbeAckData，将请求转发给 MSHR Alloc。

关于 ReleaseData/ProbeAckData 的处理，和 SinkA 对 PutData 请求的处理流程是相似的。 SinkC 维护一个 Buffer，数据的各个 Beat 以数组的形式存进 Buffer 中的空闲项，将该索引转发给 MSHR Alloc。SinkC 接收来自 MSHR 的 Task 以处理 Buffer 中的数据，Task 分为三种类型，分别是

* Save：将 Buffer 中的数据项存进 DataStorage
* Through：将 Buffer 中的数据项经过包装直接 Release 到下层 Cache 或内存
* Drop：丢弃 Buffer 中的数据项

当接收到 Task 时，SinkC 进入 Busy 状态，不接收后续任务直到该 Task 处理完成。如果该 Task 需要处理的若干数据 Beat 仍未收到时，会进行阻塞（由 beatValsThrough/beatValsSave 控制）。

【图片】



## SinkD

SinkD 接收 D 通道的 Grant/GrantData 和 ReleaseAck 响应，用 Source 域查询 MSHR 得到 set 和 way，在收到第一个或最后一个 Beat 的时候返回 Resp 信号给 MSHR。对于有数据的响应，会将 Grant 上来的数据同时发给 DataStorage 和 [RefillBuffer](misc.md).



## SinkE

接收 E 通道的 GrantAck，发送 Resp 给 MSHR，除此之外无任何逻辑。



## SourceA

接收来自 MSHR 的 Acquire 和 Put 请求，从 A 通道转发出去。对于 Put 请求，会向 SourceA 中的 PutBuffer 读取数据然后再向下转发。



## SourceB

SourceB 接收来自 MSHR 的 Task，通过 B 通道发送 Probe 请求。SourceB 在内部会维护一个状态寄存器 workVec，workVec 的每一 bit 对应一个支持 Probe 的 Client，当 workVec 为空时可以接收来自 MSHR 的请求，把所有需要 Probe 的 Client 在 workVec 寄存器中标记上；标记上以后依次向这些 Client 发送 Probe，同时依次清除掉标记位。



## SourceC



## SourceD



#### 旁路检查

对于同一个请求，SourceD 的优先级一定是最低的，DataStorage 中对每个通道优先级的制定其实就是按照同一个请求的任务优先级来定的。然而，由于 MSHR 在向 SourceD 发请求完成之前就会释放，DataStorage 里的优先级规则便会被破坏。对于 Acquire 请求，收到 GrantAck 就释放，但 Client 的 GrantAck 可以在收到 Grant first 的时候就给，那么在 Grant last 之前，MSHR 收到了 GrantAck 就释放了。对于 Get 请求，不需要 GrantAck，只要 SourceD 发出去了，MSHR 就释放。在这些提前释放的情况下，Get 和 Acquire 可能还正在 SourceD 读数据时，下一个同 Set 的请求就过来了，并发出了对这个 Set 的写操作，从正确性上来讲，肯定是前面的读要先做，但 SourceD 在 DataStorage 的优先级又是最低的，因此解决方案是要把 SourceD 的 Set/Way 拉出来，跟要写的通道做个比较，如果 Set/Way 相同，则阻塞它们，让 SourceD 先做。



## SourceE

接收来自 MSHR 的请求，从 E 通道发送 GrantAck。
