# Request Buffer 设计

为了避免多个并发请求同时在 Cache 中被处理时产生资源竞争和相互干扰，huancun 以 Set 为粒度对请求进行阻塞，
相同优先级（共 A、B、C 三种优先级）且同一个 Set 的请求不能同时进入 MSHR。为了降低这种阻塞策略给 Cache 带来的性能损失，我们设计了 Request Buffer 来缓冲被阻塞的请求，从而能让后续不同 Set 的请求非阻塞的进入 MSHR。

考虑到 CPU 中 Tilelink 总线请求数量 A>>B、A>>C 的特性，Requeset Buffer 只缓冲 A 通道的请求，这样可以在
提升性能的同时降低硬件实现复杂度。

Request Buffer 的设计类似于 CPU 中的保留站/发射队列，当新请求无法进入 MSHR 时便会尝试进入 Request Buffer，若 Buffer 中有空项则请求便会被分配到对应位置，同时记录下该请求在等待哪个 MSHR 释放（代码中的`wait_table`）。MSHR 释放时会广播其 MSHR id 到 Request Buffer 中，Buffer 中和该 MSHR 有依赖关系的项就可以被 "唤醒"。

当 Request Buffer 中存在多个相同 Set 的请求时，为了保证这些请求能以 FIFO 的顺序离开 Buffer，Buffer 内部
还维护了一个**依赖矩阵** `buffer_dep_mask`，该矩阵记录着 Buffer 内部项之间的依赖关系，
`buffer_dep_mask[i][j]` 为 1 表示位于 `i` 位置的请求和位于 `j` 位置的请求都是同一 Set 的，且位于 `i` 位置
的请求比位于 `j` 位置的请求后到，因此当外部 MSHR 释放时请求 `j` 应当先离开 Buffer。



# Refill Buffer 设计 <a name="refill_buffer"></a>

为了减少 Cache Miss的延迟，huancun 使用 Refill Buffer 来缓冲从下层 Cache 或 Memory 中 Refill 的数据，
这样 Refill 的数据不需要先写入 SRAM 就可以直接返回给上层 Cache。



# MSHR Alloc (MSHR分配模块) <a name="alloc"></a>

根据 Tilelink 手册规范，为了避免系统中出现死锁，高优先级的请求要能够打断低优先级的请求先执行，
因此 huancun 设计了 N 个(N >= 1)abc MSHR，1 个 b MSHR，1 个 c MSHR。

在没有 Set 冲突的情况下，所有请求都在 abc MSHR 中挑选一个空项进入；
当新到达的高优先级请求与 MSHR 中已有的低优先级请求发生冲突时，高优先级请求会进入专用 MSHR。
例如：b 请求与 abc MSHR 中的 a 请求 Set 冲突，则新的 b 请求会被分配进 b MSHR，
若 c 请求与 abc/b MSHR 中的 a/b 请求发生冲突，则新的 c 请求会被分配进 c MSHR。



# ProbeHelper

由于 huancun 采用了 inclusive-directory non-inclusive data 的设计，当 Client Directory 由于
容量有限而无法存放新的 Cache block (e.g. blockA) 时，需要本级 Cache 向上级发送 Probe 请求，将上级的一个
Cache Block (e.g. blockB) probe下来，再将新的 Cache Block(blockA) 对应状态存入 Client Directory中。

为了简化单个 MSHR 的处理流程，我们设计了 ProbeHelper 来监听 Client Directory 的读取结果，如果发现
了容量冲突，则由 ProbeHelper 生成一个伪造的 B 请求，将目标块从上层 Probe 下来。
这样单个 MSHR 中便不需要考虑 Client Directoy 的容量冲突问题，简化了设计。
