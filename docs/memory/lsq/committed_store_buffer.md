# Committed Store Buffer

雁栖湖架构的 Committed Store Buffer 中最多可以存放16项以  cacheline 为单位组织的数据. Committed Store Buffer 每周期至多:

* 接收2条 SQ 写入的 store 指令
* 向数据缓存写一个 cacheline

Committed Store Buffer 以 cacheline 为粒度合并 store 的写请求. 当容量超过设定好的阈值时, Committed Store Buffer 会执行换出操作, 使用 PLRU 选出要写入数据缓存的 cacheline, 并将其写入数据缓存.



