# Refill Pipe

NanHu 架构相比于 YanqiHu 架构添加了专门的回填流水线 Refill Pipe. 对于 load 或 store 的 miss 请求, 在进入 Miss Queue 之前会选择出替换路, 在拿到 L2 返回的数据后就可以发送到 Refill Pipe, 因此只需要一拍即可将回填数据写入 DCache, 而无需再访问一遍 DCache.

##  Refill Pipe 和 Main Pipe 的读写冲突问题

Refill Pipe 和 Main Pipe 都会对 DCache 进行写操作, 其中 Refill Pipe 一拍完成, 而 Main Pipe 要经过读 tag, 读 data 等共四级流水才将数据写入 DCache. 为了保证在 Main Pipe 中前后读写数据的一致性, 即读和写不会被 Refill Pipe 的写操作打断, Refill Pipe 在下述情况下会被阻塞而暂时不能写入 DCache:

* Refill Pipe 的请求和 Main Pipe 的 Stage 1 存在 set 冲突;
* Refill Pipe 的请求和 Main Pipe 的 Stage 2 / Stage 3 存在 set 冲突且有相同的路使能信号 `way_en`.

其中 Main Pipe 会在 Stage 1 完成 tag 比较并得出 `way_en`, 但是由于时序比较紧张, 这里放松了 Main Pipe Stage 1 对 Refill Pipe 的阻塞策略, 只根据 set 阻塞即可.
