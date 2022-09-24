# 二级 TLB

L2 TLB 是更大容量的页表缓存，但同时也包含了 Page Table Walker 单元，负责 Hardware Page Table Walk。

## 结构设计

L2 TLB 包含四个主要单元：

1. Page Cache：缓存页表，Sv39 的 3 层页表全部且分开缓存，可以一拍完成 3 层信息的查询
2. Page Walker：查询内存中的前两级页表，本质为状态机
3. Last Level Page Walker：查询内存中的最后一级页表
4. Miss Queue：缓存查询 Page Cache 和 Last Level Page Walker 的 miss 的请求
5. Prefetcher：预取器

从 一级 TLB 来的请求会先访问 Page Cache，如果命中，会直接返回给一级 TLB，如果缺失，会进入 Page Walker，Last Level Page Walker 或者 Miss Queue。
通过 Page Walker 和 Last Level Page Walker 可以遍历页表；通过 Miss Queue 等待资源，以便再次访问 Page Cache。访问页表结束后，可以直接返回给一级 TLB。
预取器会监控 Page Cache 的查询结果，产生预取请求，预取的结果会存到 Page Cache 中，不会返回给一级 TLB。

## Page Cache

Page Cache 是“名副其实”的 L2 TLB，具有更大的缓存容量，缓存了 3 层页表且分开缓存，因此可以一拍访问 3 层页表。根据虚拟地址判断是否命中，获得最靠近叶子节点的结果。
Page Cache 只存储有效的页表项，因访存宽度为 512 bits，即 8 项页表，所以 Page Cache 一项含有 8 个页表（1个虚拟页号，8个物理页号，8个权限位）。

Page Cache 的访问分四拍，第一拍发送读信号，第二拍得到读结果并缓存一拍，第三拍判断是否命中，并且进行 ECC 校验，第四拍返回结果。
如果 ECC 校验出错，不会向核内发送例外或中断信号，而是无效掉当前项，并返回 miss 结果，重新进行 Page Walk。
Page Cache 返回它所能提供的信息，包括：

1. 叶子节点（包括 4KB 页表和大页）是否命中以及命中的页表，返回给一级 TLB
2. 命中项是否是预取器预取得到的，返回给预取器使用
3. 前两级页表是否命中和命中结果，返回给 Page Walker 或 Last Level Page Walker 使用

## Page Walker

Page Walker 是一个状态机，根据虚拟地址访问页表，访问规则与 RV 手册中相似，直到：

1. 访问到 2MB 的节点，返回给 Last Level Page Walker，由 Last Level Page Walker 进行最后一级页表的访问
2. 访问叶子节点，为大页（SuperPage），返回给一级 TLB
3. 访问到非法节点，页表项的 v 位为 false 等

Page Walker 访存的结果会存到 Page Cache 中。
Page Walker 同时只能够处理一个请求，并且最多只访问前两级页表，访存能力较弱，原因在 Last Level Page Walker 节说明。

## Last Level Page Walker

Last Level Page Walker 为了提高 L2 TLB 的访存能力而存在。Last Level Page Walker 不合并重复的请求，而是记录下来，共享访存结果，避免重复访问内存。
Last Level Page Walker 接收来自 Page Cache 的 miss 请求，以及 Page Walk 的结果，访问最后一级的页表。
来自 Page Cache 的请求，如果只差最后一级页表，那么可以访存内存，否则，需要再次访问 Page Cache，直到得到最后一级页表的地址。
来自 Page Walker 的请求，由于已经得到前两级页表，只差最后一级页表，因此可以访问内存。

Last Level Page Walker 和 Page Walker 分工合作，共同完成 Page Table Walk 的全流程。为了提高访存的并行度，Last Level Page Walker 为请求配置不同的 id，同时拥有多个 inflight 的请求。但是不同请求的前两级（1GB、2MB）可能相同，并且考虑到前两级的 miss 概率比最后一级页表低，因此不考虑提高前两级页表的访问并行度，只设一个 Page Walk，降低设计的复杂度。

## Miss Queue

Miss Queue 的本质是一个缓冲队列，起到等待资源的作用。Miss Queue 可以接收来自 Page Cache 或 Last Level Page Walker 的请求，等待再次访问 Page Cache。

## Prefetch

目前采用 NextLine 预取算法，当 miss 或者 hit 但命中项为预取项时，产生下一个预取请求。
预取请求访问 Page Cache，因为 Page Walker 的访存能力弱，如果预取请求发生 miss，预取请求并不会进入 Page Walker 或 Miss Queue，而是被直接丢弃。如果预取请求只差最后一节页表，可以访问 Last Level Page Walker。
预取结果存到 Page Cache 中，不返回给一级 TLB。
