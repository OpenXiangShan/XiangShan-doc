# Request Buffer设计

为了避免多个并发请求同时在cache中被处理时产生资源竞争和相互干扰，huancun以set为粒度对请求进行阻塞，
相同优先级(共A、B、C三种优先级)且同一个set的请求不能同时进入MSHR。为了降低这种阻塞策略给cache带来的
性能损失，我们设计了Request Buffer来缓冲被阻塞的请求，从而能让后续不同set的请求非阻塞的进入MSHR。

考虑到CPU中Tilelink总线请求数量A>>B, A>>C的特性，Requeset Buffer只缓冲A通道的请求，这样可以在
提升性能的同时降低硬件实现复杂度。

Request Buffer的设计类似于CPU中的保留站/发射队列，当新请求无法进入MSHR时便会尝试进入Request Buffer，
若buffer中有空项则请求便会被分配到对应位置，同时记录下该请求在等待哪个MSHR释放(代码中的`wait_table`)。
MSHR释放时会广播其MSHR id到buffer中，buffer中和该MSHR有依赖关系的项就可以被‘唤醒’。

当buffer中存在多个相同set的请求时，为了保证这些请求能以FIFO的顺序离开buffer，buffer内部
还维护了一个**依赖矩阵**`buffer_dep_mask`，该矩阵记录着buffer内部项之间的依赖关系，
`buffer_dep_mask[i][j]`为1表示位于`i`位置的请求和位于`j`位置的请求都是同一set的，且位于`i`位置
的请求比位于`j`位置的请求后到，因此当外部MSHR释放时请求`j`应当先离开buffer。

