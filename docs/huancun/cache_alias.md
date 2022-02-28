# Cache别名问题

由于在NanHu架构中，DCache和ICache都是采用128KB的8路组相联结构，cache索引和块偏移所占bit数已经超过了页偏移(4K页的页偏移为12 bits)，由此引入了cache别名问题：当两个虚页映射到同一个物理页时，两个虚页的别名位(alias bits)很有可能是不一样的，如果不做额外处理的话，通过VIPT索引(Virtual Index Ptysical Tag)后这两个虚页会位于cache不同的set，导致同一个物理页在cache中缓存了两份，造成一些一致性错误。

![](../figs/huancun_cache_alias-1.jpg)

为了让L1 Cache继续沿用VIPT，XiangShan的缓存系统采用硬件方式解决cache别名问题。具体的解决方式是由L2 Cache保证一个物理块在上层的一个VIPT cache中最多只有一种别名位。

下面举一个例子说明L2如何解决cache别名问题。如下图所示，DCache中有有一个虚地址为0x0000的块，虚地址0x0000和0x1000映射到了同一个物理地址，且这两个地址的别名是不一样的；此时DCache向L2 Acquire了地址为0x1000的块，并在Acquire请求的user域中记录了别名(0x1)，L2在读目录后发现请求命中，但是Acquire的别名(0x1)和L2记录的DCache在该物理地址的别名(0x0)不同，于是L2会发起一个Probe子请求，并在Probe的data域中记录要probe下来的别名(0x0)；Probe子请求完成后，L2再将这个块返回给DCache，并将L2 client directory中的别名改为(0x1)。

![](../figs/huancun_cache_alias-2.jpg)