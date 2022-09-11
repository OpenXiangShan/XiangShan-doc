# 一级 TLB

## 基础介绍

TLB（Translation Lookaside Buffer）负责进行地址翻译。
香山支持手册中规定的 Sv39 模式，暂不支持其他几种模式。虚拟地址长度为 39 位，物理地址长度为 36 位，可参数化修改。
虚存是否开启由当前特权级（如M mode 或 S Mode等）和 Satp 寄存器等共同决定，这一判断在 TLB 内部完成，对 TLB 外透明，因此在 TLB 外的模块看来，所有的地址都经过的 TLB 的地址转换。

## 组织形式

核内进行访存之前，包括前端取指和后端访存两部分，都需要由 TLB 进行地址翻译。因物理距离较远，并且为了避免相互污染，前端的 ITLB（instruction TLB）和后端访存的 DTLB（Data TLB）是两个的 TLB。ITLB 采用全相联模式，32 项普通页（NormalPage）负责 4KB 页，8 项大页（SuperPage）负责 2MB 和 1GB 的地址转换。DTLB 采用混合模式，64 项普通页直接相联负责 4KB 页，16 项大页全相联负责全部大小的页，采用伪 LRU 替换策略。普通页部分提供容量，但灵活性低，易冲突；大页部分灵活性强，但容量小。因此将普通页部分作为大页部分的 Victim，回填时，先回填大页部分，大页部分驱逐的项写到普通页部分（仅限 4KB 页）。

访存拥有 2 个 Load 流水线，2 个 Store 流水线，为了时序考虑，它们需要一个单独的 TLB。同时为了性能考虑，这些 TLB 的内容需要保持一致，类似于相互预取。因此，这 4 个 DTLB 采用“外置”的替换算法模块，以保证内容的一致。

## 阻塞与非阻塞

前端取指对 ITLB 的需求为阻塞式访问，即当 TLB miss 时，TLB 不立即返回 miss 结果，而是进行 Page Table Walk 取回页表项后返回。
而后端访存对 DTLB 的需求为非阻塞式访问，即当 TLB miss 时，TLB 也需要立即返回结果，无论是 miss 还是 hit。
Yanqihu 架构和 Nanhu 架构中，TLB本体为非阻塞式访问，前端取指的阻塞式访问由前端模块完成 replay，TLB 不存储请求的信息。

新版架构预告：TLB 可以对每个请求端口的阻塞形式进行参数化配置，静态选择阻塞还是非阻塞，一个模块可以同时适应前后端的需求。

## Sfence.vma 与 ASID

Sfence.vma 指令执行时，会先清空 Store Buffer 的全部内容（写回到 DCache 中），之后发出刷新信号到 MMU 的各个部分。刷新信号是单向的，只会持续一拍，没有返回信号。指令最后会刷新整个流水线，从取指开始重新执行。
Sfence.vma会取消所有 inflight 的请求，包括 Repeater 和 Filter，以及 L2 TLB中的 inflight 请求，并且根据地址和 ASID 刷新 TLB 和 L2TLB 中的缓存的页表。
全相联部分根据是否命中进行刷新，组相联（直接相联）部分，根据 index 直接刷新。

Yanqihu 架构不支持 ASID（Address Space IDentifier），Nanhu 架构添加了对 ASID 的支持，长度为16，可以参数化配置。
所有 inflight 请求都不携带 ASID 信息，这源于以下几个方面：

1. 一般情况下，inflight 请求的 ASID 都与 Satp 的 ASID 域相同
2. 切换 ASID 时，inflight 请求都是“推测”访问的，是近似“无用”的

综合这两个原因，当切换 ASID 时，也将所有的 inflight 全部取消，并且 inflight 不必携带 ASID 信息。

## 更新 A/D 位

根据手册，页表的 A（Access）和 D（Dirty）位将会需要更新，香山采用报 page fault 例外的方法，由软件进行更新。