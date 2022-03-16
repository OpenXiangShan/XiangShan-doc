# 物理地址保护

物理地址保护，分为 PMP（Physical Memory Protection）和 PMA（Physical Memory Attribute）两部分。
Yanqihu 架构支持硬写的 PMA 检查，但不支持 PMP 检查。Nanhu 结构添加了对 PMP 的支持，同时也支持软件可读可写的 PMA 实现。

PMP 的实现遵循 RV 手册规定，默认为 16 项，可参数化调整（但需要是 8 的倍数）。出于时序考虑，采用分布&复制式实现方法，在 CSR 单元中的 PMP 寄存器负责 CSRRW 等指令；在前端取指、后端访存、Page Walker处都拥有一份 PMP 寄存器的拷贝，通过拉取 CSR 写信号保证和 CSR 单元中 PMP 寄存器的一致。

PMA 的实现采用了类 PMP 的方式，利用了 PMP Configure 寄存器的两个保留位，设为 atomic 和 cachable，分别为：是否支持原子操作和是否可缓存。PMP 寄存器根据手册，没有初始值（默认为空）。而PMA 寄存器默认拥有初始值，需手动设置与平台地址属性一致。PMA 寄存器利用了 M 态 CSR 保留寄存器地址空间，16项，可参数化配置。

PMP 和 PMA 检查并行查询，如果违反其中一个权限，即为非法操作。核内所有的物理地址访问都需要进行物理地址权限检查，包括在 ITLB 和 DTLB 检查之后，以及 Page Walker 访存之前。根据手册，Page Fault 的优先级高于 Access Fault，但是当 Page Walker 出现 Access Fault 时，页表项为非法，此时会同时出现 Page Fault 和 Access Fault 一起出现的特殊情况，香山选择报 Access Fault，或与手册不符。

按照手册规定，PMP 和 PMA 的检查应该为动态检查，即需要经过 TLB 翻译之后，使用翻译后的物理地址进行物理地址权限检查。但出于时序考虑，DTLB 普通页部分的检查结果提前查询好存入 TLB 项中，为此需要提升 PMP 和 PMA 的粒度为 4KB。

DMA 等外设访问内存时，也需要进行物理地址检查，因此实现了 Memory-mapped 版的 PMA，供 DMA 等外设使用。