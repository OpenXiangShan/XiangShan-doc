---
slug: biweekly-86
date: 2025-09-29
categories:
  - Biweekly
---

# 【香山双周报 86】20250929 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 85 期双周报。

在本次双周报中，我们非常高兴地向大家宣布，香山要有属于自己的编译器了！香山编译器（XiangShan Compiler Collection, XSCC） 是一款基于香山开源高性能 RISC-V 处理器研发的高性能编译器，依托 LLVM 框架开发，专注于访存优化、分支预测改进、循环展开与自动矢量化等微架构级性能提升策略。目前，XSCC 1.0 基于 LLVM 19.1.0 开发。

本次发布为 XSCC v1.0 二进制发行包，提供面向 RISC‑V 的交叉编译器（生成 riscv64 目标代码）。可在 Ubuntu 22.04 以上版本的主机 (x86_64) 运行，默认配套的 C 标准库为 glibc。在 GitHub Releases 页面可下载该发行包：https://github.com/OpenXiangShan/xscc/releases。

在过去的两周，前端 V3 重构基本完成，各个 BPU 适配新的前端框架，后端也做了对应修改。后端主要在推进向量单元的性能优化。访存与缓存主要修复了 V2 的一些 bug，同时开发了一些新的工具。

从本期双周报开始，我们将在性能评估部分加入使用 XSCC 编译的 SPEC 2006 性能数据，供大家参考。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 优化 BPU 训练机制，采用一个 resolve 项内第一条误预测的分支进行训练，丢弃后续分支的训练信息（[#5023](https://github.com/OpenXiangShan/XiangShan/pull/5023)，[#5037](https://github.com/OpenXiangShan/XiangShan/pull/5037)，[#5041](https://github.com/OpenXiangShan/XiangShan/pull/5041)）
  - 支持使用 s3 精确预测器的结果训练 s1 快速预测器，因精确预测器尚未就绪，暂未启用（[#4970](https://github.com/OpenXiangShan/XiangShan/pull/4970)）
  - 增加 abtb 的路数到 8 路，和 mbtb 默认配置一致（[#5042](https://github.com/OpenXiangShan/XiangShan/pull/5042)）
  - 合入 TAGE，因 override 机制存在一些问题，暂未启用（[#5001](https://github.com/OpenXiangShan/XiangShan/pull/5001)）
  - 支持 TAGE WriteBuffer 多路写入（[#5044](https://github.com/OpenXiangShan/XiangShan/pull/5044)，[#5056](https://github.com/OpenXiangShan/XiangShan/pull/5056)）
  - 增加 resolve 项内存储的分支数到 8 条（[#5050](https://github.com/OpenXiangShan/XiangShan/pull/5050)）
  - 支持 64B 取指（[#5014](https://github.com/OpenXiangShan/XiangShan/pull/5014)）
  - 移除 ICache 主流水 s2 流水级，简化设计，为后续功能做准备（[#5053](https://github.com/OpenXiangShan/XiangShan/pull/5053)）
  - 放松 IBuffer 入队条件，减少阻塞（[#5036](https://github.com/OpenXiangShan/XiangShan/pull/5036)）
- Bug 修复
  - 修复 abtb X 态传播的问题（[#5028](https://github.com/OpenXiangShan/XiangShan/pull/5028)）
  - 修复 mbtb 预测出跨页取指块的问题，V3 ICache/IFU 去除了跨页取指的支持，需要 BPU 保证不给出跨页预测（[#5060](https://github.com/OpenXiangShan/XiangShan/pull/5060)）
  - 修复 TAGE X 态传播的问题（[#5043](https://github.com/OpenXiangShan/XiangShan/pull/5043)）
  - 修复 V2 RAS 接入 V3 FTQ 时没有处理 IFU 重定向的问题，以及后端重定向的 rasAction 没有正确赋值的问题（[#5040](https://github.com/OpenXiangShan/XiangShan/pull/5040)）
  - 修复 Ftq backendException 写条件错拍的问题（[#5016](https://github.com/OpenXiangShan/XiangShan/pull/5016)，[#5035](https://github.com/OpenXiangShan/XiangShan/pull/5035)）
  - 修复 IFU 指令 offset 计算错误的问题（[#5012](https://github.com/OpenXiangShan/XiangShan/pull/5012)）
  - 修复 IFU s1 流水级冲刷条件错误、ICache WayLookup 和主流水 s1 流水级未被 BPU s3 override 冲刷的问题（[#5054](https://github.com/OpenXiangShan/XiangShan/pull/5054)），[#5055](https://github.com/OpenXiangShan/XiangShan/pull/5055)，[#5072](https://github.com/OpenXiangShan/XiangShan/pull/5072)）
- 模型探索
  - 整理 TAGE PHR 相关 commit，性能有改善（[GEM5#524](https://github.com/OpenXiangShan/GEM5/pull/524)）
  - 调整 SC 落地改造方案，适配 updateThreshold 和 weight Table
- 代码质量
  - 重构 BPU S3 预测生成逻辑，将 takenMask 的生成从 TAGE 移动到 BPU 顶层，使模块功能划分更加清晰（[#5045](https://github.com/OpenXiangShan/XiangShan/pull/5045)）
  - 重构 IFU 指令边界计算逻辑（[#5012](https://github.com/OpenXiangShan/XiangShan/pull/5012)）

### 后端

- Bug 修复
  - 通过当预测和实际都被采用时检查目标修复分支预测性能bug（[#5027](https://github.com/OpenXiangShan/XiangShan/pull/5027)）
  - 修复nmi寄存器的gate逻辑的bug（[#5031](https://github.com/OpenXiangShan/XiangShan/pull/5031)）
  - 修复预取指令不应响应load trigger的bug（[#5059](https://github.com/OpenXiangShan/XiangShan/pull/5059)）
  - 修复关闭rob压缩后融合指令后跟分支指令时出错的bug（[#5074](https://github.com/OpenXiangShan/XiangShan/pull/5074)）
- 时序优化
  - 重新划分后端一级子模块，便于物理设计划分（[#5032](https://github.com/OpenXiangShan/XiangShan/pull/5032)）
- RTL新特性
  - 完成Trace Control Interface对APB总线与AXI总线的支持
  - 拆分SRAM Sink拆为SMEM模式（通过AXI写入内存）和SRAM模式（组件内置专用的FIFO Buffer）
  - 进行branch_map逻辑设计，同步packet和trap packet的设计
  - 增加性能计数器统计任意两个发射队列之间可旁路ALU的数量
- 代码质量
  - 移除部分死代码（[#5071](https://github.com/OpenXiangShan/XiangShan/pull/5071)）

### 访存与缓存

- Bug 修复
  - 修复 FDP 中 counter filter 容量不够需要加 1 的问题（[#5030](https://github.com/OpenXiangShan/XiangShan/pull/5030)）
  - 修复了 LoadUnit 在 fast replay 时没有重新访问数据的问题，以避免产生内存一致性问题（[#4965](https://github.com/OpenXiangShan/XiangShan/pull/4965)）
- 时序优化
  - 将 CoupledL2 的数据 SRAM 拆分改为 4份，以适应新的物理设计后端要求（[CoupledL2 #432](https://github.com/OpenXiangShan/CoupledL2/pull/432)）
  - 旧版 MMU 时序修复进行中
  - 分析往期版本的 LoadQueueReplay 时序，找到时序退化点
- RTL 新特性
  - MMU、LoadUnit、StoreQueue、L2 等模块重构持续推进中
  - L1 Acquire 时获取路信息以在 Release 时省去读目录获得路数的过程。正在修复 Bug

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.90  | 433.milc         | 50.44  |
| 429.mcf           | 60.18  | 434.zeusmp       | 51.83  |
| 445.gobmk         | 30.63  | 435.gromacs      | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.87  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.77  |
| 471.omnetpp       | 41.50  | 450.soplex       | 52.48  |
| 473.astar         | 29.30  | 453.povray       | 53.49  |
| 483.xalancbmk     | 72.79  | 454.Calculix     | 16.38  |
| GEOMEAN           | 44.67  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 49.13  |
|                   |        | GEOMEAN          | 45.26  |

我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

编译参数如下所示：

|                  |          |
| ---------------- | -------- |
| 编译器           | gcc12    |
| 编译优化         | O3       |
| 内存库           | jemalloc |
| -march           | RV64GCB  |
| -ffp-contraction | fast     |

处理器及 SoC 参数如下所示：

|           |            |
| --------- | ---------- |
| commit    | 324b389    |
| 日期      | 2025/09/25 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | TileLink   |
| 内存延迟  | DDR4-3200  |

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
