Load Queue
===========

雁栖湖架构的 load queue 是一个64项循环队列. 其每周期至多: 
* 从 dispatch 处接收6条指令
* 从 load 流水线接收2条指令的结果
* 写回2条 miss 的 load 指令. 这些指令已经取得了 refill 的数据, 会与正常的访存流水线争用两个写回端口

一级数据缓存 refill 时，会将一整个 cacheline 的所有数据反馈给 load queue, 所有在 load queue 中等待这一 cacheline 数据的指令都会得到数据.

