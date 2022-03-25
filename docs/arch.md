# 香山处理器整体架构设计

香山处理器是乱序六发射结构设计，目前支持 RV64GCBK 扩展（具体指令集字符串为 `RV64IMAFDC_zba_zbb_zbc_zbs_zbkb_zbkc_zbkx_zknd_zkne_zknh_zksed_zksh_svinval` ）。香山处理器前端流水线包括分支预测单元、取指单元、指令缓冲等单元，顺序取指。后端包括译码、重命名、重定序缓冲、保留站、整型/浮点寄存器堆、整型/浮点运算单元。我们将访存子系统分离开，包括两条 load 流水线，两条 store addr 流水线，两条 store data 流水线，以及独立的 load 队列和 store 队列，store buffer 等。缓存包括 ICache、DCache、L2/L3 Cache (HuanCun)、TLB 和预取器等模块。各部分在流水线中的位置以及参数配置可以从下图中获得。

![香山架构图](./figs/nanhu.png)

具体结构设计详见对应章节的介绍。
