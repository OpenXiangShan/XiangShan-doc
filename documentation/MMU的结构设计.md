# 香山处理器MMU的设计

为了实现进程隔离，每个进程都会有自己的地址空间，使用的地址都是虚拟地址。MMU也就是Memory Management Unit，在处理器中主要负责将虚拟地址翻译成物理地址，然后用这个物理地址去访存。同时也会进行权限检查，比如是否可写，可执行。
香山处理器支持Sv39分页机制，主要特点是虚拟地址长度为39位，低12比特是页内偏移，中间的27比特分为三段，也就是三层页表，这意味着遍历页表三次内存访问，因此我们也需要对页表做缓存，这就是MMU的主要工作。

![Sv39三级页表示意图](https://cdn.nlark.com/yuque/0/2021/png/1658967/1626503550336-9f4df369-d685-4e68-84d4-eda244d6d3a6.png#clientId=u66e3bb9e-7a90-4&from=paste&height=242&id=ua481a289&margin=%5Bobject%20Object%5D&name=image.png&originHeight=257&originWidth=478&originalType=binary&ratio=1&size=31021&status=done&style=none&taskId=ue5f903d9-3229-419e-896b-c92dd866bf0&width=451.00001525878906)

香山的MMU主要分为三部分，和流水线紧耦合的分别位于前端和后端的ITLB和DTLB，需要考虑流水线的需求，考虑时序问题，比如拆成两拍等操作。当ITLB和DTLB如果miss，会发送请求L2 TLB，当L2 TLB也miss，就会使用Hardware Page Table Walker去访问内存中的页表内容。L2 TLB主要考虑是如何提高并行度和过滤重复的请求。

![MMU在处理器中的位置](https://cdn.nlark.com/yuque/0/2021/png/1658967/1626503648761-b19e0ba2-5b36-494d-8994-58fe6ed95057.png#clientId=u66e3bb9e-7a90-4&from=paste&height=208&id=u40c78e7d&margin=%5Bobject%20Object%5D&name=image.png&originHeight=306&originWidth=586&originalType=binary&ratio=1&size=53410&status=done&style=none&taskId=u2006d23f-5e8f-46ce-950c-6e5b68c2357&width=398.0000305175781)

香山的ITLB和DTLB都是全相联的组织结构，有32项的普通页和4项的大页，ITLB采用伪LRU替换策略，DTLB因为有4路访问，使用LRU的成本比较高，因此采用随即替换策略，同时TLB目前支持PMA，当填充TLB时，会查询PMA，并将结果写入TLB中。如右图所示，查询TLB时，部分内容负责权限检查，部分内容负责地址翻译。

![TLB的存储内容](https://cdn.nlark.com/yuque/0/2021/png/1658967/1626503711666-d419af9a-7b78-49d8-8da9-71909b862f35.png#clientId=u66e3bb9e-7a90-4&from=paste&height=270&id=u57bcd254&margin=%5Bobject%20Object%5D&name=image.png&originHeight=301&originWidth=601&originalType=binary&ratio=1&size=34331&status=done&style=none&taskId=ubae1105d-683a-43af-ba3d-68171a6b503&width=539.5000305175781)

L2 TLB是更大的页表缓存，由ITLB和DTLB共享。具体结构如右图所示，同时为了加快页表访问，将页表的三层都做了缓存，因此在这里把它们统一称为page table caches。因为PTW的访存并不密集，也为了避免污染DCache，PTW直接访问L2 Cache进行访存，另外也可以获得256位的访存带宽，一次可以访问4个页表。所以我们的page table cache每一行也有四项，把这个带宽利用上。yanqihu版本中，L2 TLB一次只能处理一个请求。

![L2TLB的总体结构](https://cdn.nlark.com/yuque/0/2021/png/1658967/1626503773548-75bde6ae-dcd4-442e-9026-20040e36fdc9.png#clientId=u66e3bb9e-7a90-4&from=paste&height=345&id=uacd0afa2&margin=%5Bobject%20Object%5D&name=image.png&originHeight=478&originWidth=514&originalType=binary&ratio=1&size=58974&status=done&style=none&taskId=ud0c91d0f-87b3-4a12-b579-9b36e4b57f5&width=371.0000305175781)

备注：具体在代码中，L2TLB目前被命名为PTW，需要注意不要混淆。
TLB和L2 TLB因为有比较长的物理距离，就会导致比较长的线延迟，因此就需要在中间加拍，普通的加拍，把它称为Repeater。

![Repeater](https://cdn.nlark.com/yuque/0/2021/png/1658967/1626503997929-9299ff27-159e-4736-81df-668eccb9bc49.png#clientId=u66e3bb9e-7a90-4&from=paste&height=271&id=ua133d393&margin=%5Bobject%20Object%5D&name=image.png&originHeight=321&originWidth=398&originalType=binary&ratio=1&size=20888&status=done&style=none&taskId=u08a6d1b3-6794-4e8d-9dad-4904418291d&width=336.0000305175781)

**新版本预告**：
在新版本中，我们着重增加了L2TLB的并行度，并将Repeater升级可以捕捉所有请求并带有过滤功能的Filter，另外，我们还将尝试增加针对MMU的预取和合并机制。
