# 指令缓存（Instruction Cache）文档
![icache](../figs/frontend/ICache.png)

这一章描述香山处理器指令缓存的实现。

## 控制逻辑

<!-- 指令缓存的主控制逻辑模块MainPipe的内部逻辑示意图： -->

指令缓存的主控制逻辑模块MainPipe由3级流水线构成：
- 在`s0` 阶段从FTQ发送过包含两个cacheline的取指令请求，其中包含了每个请求是否有效的信号（不跨行的指令packet止只会发送一个cacheline的读请求），同时MainPipe一方面会把请求地址提取为缓存组索引（set index）发送给指令Cache的[存储部分](#mem)，另一方面，这些请求会被发送给ITLB进行[指令地址翻译](#tlb)
- 在`s1` 阶段，存储SRAM返回一个组（Cache Set）一共N个路(Cache Way)的cacheline元数据和数据。同时ITLB返回请求对应的物理地址。接下来主控制逻辑截取物理地址并和N个路的Cache tag进行匹配，生成缓存命中（Cache hit）和缓存缺失（Cache miss）两种结果。另外还会根据替换算法的状态信息选出需要替换的cacheline。
- 在`s2`阶段，hit的请求直接返回数据给IFU。而当发生miss的时候需要暂停流水线，并将请求发送给缺失处理单元MissUnit。等到MissUnit充填完成并返回数据之后将数据返回给IFU。
- 在`s2`阶段还会把ITLB翻译得到的物理地址发送给PMP模块进行访问权限的查询，如果权限错误会触发指令访问例外(Instruction Access Fault)

<h2 id=itlb>指令地址翻译</h2>

由于指令缓存采用的是VIPT（Virtual Index Physical Tag）的缓存方式，因此需要在地址tag比较之前先将虚拟地址翻译为物理地址。控制流水线的`s0`阶段，两个cachline请求的虚拟地址会同时发送到ITLB的查询端口，同时这一个时钟周期内ITLB返回虚地址是否命中的信号。命中则会在下一拍返回对应的物理地址。不命中则控制逻辑会阻塞MainPipe流水线，等待直到ITLB重填结束返回物理地址。

## 缓存miss处理

发生miss的请求会被移交给MissUnit向下游L2 Cache发送Tilelink `Aquire` 请求，等到MissUnit收到对应数据的 `Grant` 请求之后，如果需要替换cacheline，MissUnit则会向ReplacePipe发送Release请求，ReplacePipe会重新读一遍SRAM得到数据，然后发送给ReleaseUnit发起向L2 Cache的`Release` 请求。最后MissUnit重填写SRAM，等到重填结束后返回数据给MainPipe，MainPipe再把数据返回给IFU。

miss的cacheline可能发生在两个请求中的任何一个，因此MissUnit里设置了两个处理miss的missEntry项来提高并发度。

## 例外的处理
在ICache产生的例外主要包括两种：ITLB报告的指令缺页例外（Instruction Page Fault）和ITLB和PMP报告的访问例外（Access Fault）。MainPipe会把例外信息直接报告给IFU，而请求的数据被视为无效。

<h2 id=imem>存储部分</h2>

指令Cache的存储逻辑主要分为了Meta SRAM（存储每个cacheline的tag以及一致性状态）和Data SRAM（存储每个cacheline的内容）。内部支持了奇偶校验码用以进行数据的校验，当校验发生错误的时候会给报总线错误并产生中断。Meta/Data SRAM内部都分了奇偶bank，虚地址空间中相邻的两个cacheline会被分别划分到不同的bank来实现两个cacheline的读取。


## 一致性支持

香山南湖架构的指令Cache实现了Tilelink定义的一致性协议。主要是通过增加了一条额外的流水线ReplacePipe来处理Probe和Release请求。


指令缓存的ReplacePipe由4级流水线构成：
- 在`r0` 阶段接收从ProbeUnit发送过来的Probe请求和从MissUnit发送过来的Release请求，同时也会发起对Meta/Data SRAM的读取。因为这里的请求包含了虚拟地址和实际的物理地址，所以不需要做地址翻译。
- 在`r1` 阶段，ReplacePipe和MainPipe一样用物理地址对SRAM返回的一个Set的N路cacheline做地址匹配，产生hit和miss两种信号，这个信号仅仅对于Probe有效，因为Release的请求必须在Cache里。
- 在`r2`阶段，hit的Probe请求将被invalid掉，同时会把这个请求发送给ReleaseUnit向L2发送`ProbrResponse`请求，这个cacheline的权限转变为toN。miss的请求不会做invalid，并且会发送给ReleaseUnit向L2报告权限转变为NToN（指令Cache里没有Probe要求的数据）。Release请求也会被发送到ReleaseUnit向L2发送`ReleaseData`。且只有Release请求被允许进入`r3`
- 在`r3`阶段，ReplacePipe向MissUnit报告被替换出去的块已经往下Release了，通知MissUnit可以进行重填。
