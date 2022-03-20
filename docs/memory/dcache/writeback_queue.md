# Writeback Queue

NanHu 架构的 DCache 中用到 18 项的写回队列, 负责通过 TL-C 的 C 通道向 L2 Cache 释放替换块 (Release), 或者对 Probe 请求做出应答 (ProbeAck), 且支持 Release 和 ProbeAck 之间相互合并以减少请求数目并优化时序.

## Writeback Queue 入队

为了时序考虑, 在 wbq 满的时候无论新请求是否能被合并都会被拒绝; 而当 wbq 不满的时候所有请求都会被接收, 此时或者为新请求分配空项, 或者将新请求合并到已有的 Writeback Entry 中, 后面在[状态维护](#writeback-queue-状态维护)部分将会看到 Writeback Entry 任何时候都可以合并进新的 Release 或 ProbeAck 请求. 因此 NanHu 架构中判断写回队列能否入队只需要看队列有没有空项即可, 大大缩短了入队的逻辑延迟.

## Writeback Queue 状态维护

每一项 Writeback Entry 有如下 4 种状态:

状态|说明
-|-
`s_invalid`|该 Writeback Entry 为空项
`s_sleep`|准备发送 Release 请求, 但暂时 sleep 并等待 refill 请求唤醒[^sleep]
`s_release_req`|正在发送 Release 或者 ProbeAck 请求
`s_release_resp`|等待 ReleaseAck 请求

[^sleep] **关于 `s_sleep` 状态的说明**: 为了性能考虑, 我们不希望替换块被过早地无效掉, 以免在向下访问 L2 / L3 的时间里核内又访问了替换块, 导致乒乓效应, 产生新的不必要的 miss 请求. 因此, 替换请求先后进入 Main Pipe 和 Writeback Queue 并不是真的要把替换块无效掉, 而是先把替换块的数据读出来, 并暂时放在写回队列中 sleep. 在替换请求 sleep 期间, 其他请求还是可以正常访问 DCache 中的替换块, 只要把对替换块的写同步一份到写回队列中即可. 当回填块拿上来以后, 就可以唤醒写回队列里 sleep 的块了, 写回队列开始向下 Release 替换块, 同时 Miss Queue 请求 Refill Pipe 完成回填, 回填的同时替换块就会被覆盖掉了.

不考虑请求合并的话, Writeback Entry 处理 ProbeAck 和处理 Release 的流程如下:

1. ProbeAck: `s_invalid` -> `s_release_req` -> `s_invalid`

2. Release: `s_invalid` -> `s_sleep` -> `s_release_req` -> `s_release_resp` -> `s_invalid`

如果有可以合并的请求, 其处理流程会稍复杂一些:

3. Release 合并 ProbeAck: 在上述 Release 处理流程中任何一个阶段都有可能收到相同地址的 ProbeAck: 如果是在 `s_sleep` 阶段则直接将 Release 请求变为 ProbeAck 请求; 如果是在 `s_release_req` 阶段, 且 Release 请求还没有完成握手, 也可以直接将 Release
变为 ProbeAck; 如果是在 `s_release_req` 阶段, 但是 Release 请求已经完成了至少一次握手, 那么说明 ProbeAck 请求来得太晚, 这时会置上 `release_later` 位, 并把 ProbeAck 相关信息记录下来, 在 Release 全部处理完后再处理 ProbeAck.

4. ProbeAck 合并 Release: 由于这部分内容非常细碎, 就不做更详细的介绍了, 具体内容可以参考 `src/main/scala/xiangshan/cache/dcache/mainpipe/WritebackQueue.scala` 的代码. 主要的思想就是能合并就合并, 尽量少做一次 Release, 如果 Release 来得太晚就置 `release_later` 位稍后再做处理.

## 阻塞 Miss Queue 请求

TileLink 手册对并发事务的限制要求如果 master 有 pending Grant (即还没有发送 GrantAck), 则不能发送相同地址的 Release. 因此所有 miss 请求在进入 Miss Queue 时如果发现和 Writeback Queue 中某一项有相同地址, 则该 miss 请求会被阻塞.
