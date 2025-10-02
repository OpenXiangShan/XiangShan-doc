---
slug: biweekly-85
date: 2025-09-01
categories:
  - Biweekly
---

# 【香山双周报 85】20250915 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 85 期双周报。

在本次双周报中，我们非常高兴地向大家宣布，香山要有属于自己的编译器了！香山编译器（XiangShan Compiler Collection, XSCC） 是一款基于香山开源高性能 RISC-V 处理器研发的高性能编译器，依托 LLVM 框架开发，专注于访存优化、分支预测改进、循环展开与自动矢量化等微架构级性能提升策略。目前，XSCC 1.0 基于 LLVM 19.1.0 开发。

本次发布为 XSCC v1.0 二进制发行包，提供面向 RISC‑V 的交叉编译器（生成 riscv64 目标代码）。可在 Ubuntu 22.04 以上版本的主机 (x86_64) 运行，默认配套的 C 标准库为 glibc。在 GitHub Releases 页面可下载该发行包：https://github.com/OpenXiangShan/xscc/releases。

在过去的两周，前端 V3 重构基本完成，各个 BPU 适配新的前端框架，后端也做了对应修改。访存与缓存主要修复了 V2 的一些 bug，同时开发了一些新的工具。

从本期双周报开始，我们将在性能评估部分加入使用 XSCC 编译的 SPEC 2006 性能数据，供大家参考。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 支持 resolve 更新 BPU（[#4962](https://github.com/OpenXiangShan/XiangShan/pull/4962)）
  - 支持 ICache 动态取指块大小，节省功耗，同时为 64B 取指块做准备（[#4999](https://github.com/OpenXiangShan/XiangShan/pull/4999)）
  - 优化 mbtb、abtb 替换算法，采用 SRAM 实现的 PLRU 以节省面积（[#4964](https://github.com/OpenXiangShan/XiangShan/pull/4964)）
  - 实现 ITTAGE 接入 V3 BPU（[#5000](https://github.com/OpenXiangShan/XiangShan/pull/5000)，[#5020](https://github.com/OpenXiangShan/XiangShan/pull/5020)）
  - 优化 PHR 更新机制（[#4995](https://github.com/OpenXiangShan/XiangShan/pull/4995)）
  - TAGE-SC 持续开发中，暂未合入（[#5001](https://github.com/OpenXiangShan/XiangShan/pull/5001)）
- Bug 修复
  - 修复 resolve 更新触发的一些 bug
    - 修复 IFU 处理跨预测块的、被预测为分支指令的非分支指令时重定向错误的问题（与 [#4962](https://github.com/OpenXiangShan/XiangShan/pull/4962) 一起合入）
    - 协助修复后端 branchUnit 计算分支目标地址错误的问题（与 [#4962](https://github.com/OpenXiangShan/XiangShan/pull/4962) 一起合入）
    - 修复 ubtb 更新条件错误导致多路命中的问题（[#5004](https://github.com/OpenXiangShan/XiangShan/pull/5004)，[#5008](https://github.com/OpenXiangShan/XiangShan/pull/5008)）
    - 修复 IBuffer 错误传递 identifiedCfi 的问题（[#5019](https://github.com/OpenXiangShan/XiangShan/pull/5019)）
- 模型探索
  - 分析 TAGE 实现，修复两个存在性能问题的方向，实现和 CBP 对齐
- 代码质量
  - 重构 IFU、IBuffer 使用 V3 前端参数系统（[#4975](https://github.com/OpenXiangShan/XiangShan/pull/4975)，[#5013](https://github.com/OpenXiangShan/XiangShan/pull/5013)）
  - 简化 mbtb 参数（[#4987](https://github.com/OpenXiangShan/XiangShan/pull/4987)）

### 后端

- Bug 修复
  - 后端应提供 FTQ 项的起始 PC（[#5017](https://github.com/OpenXiangShan/XiangShan/pull/5017)）
  - 修复 isRVC 传输逻辑以适应新的 FTQ 设计（[#5003](https://github.com/OpenXiangShan/XiangShan/pull/5003)）

### 访存与缓存

- RTL新特性
  - （V2）在 CoupledL2 的 MMIOBridge 中，将 clint 的地址范围从 xstilewrap 的映射中排除并重新配置，以集成私有的 clint ip（[CoupledL2 #429](https://github.com/OpenXiangShan/CoupledL2/pull/429)）
  - MMU、LoadUnit、StoreQueue、L2 等模块重构持续推进中
  - 重构 NEMU 的访存部分，包括代码整理以及增加 V3 新特性
- Bug 修复
  - （V2）修复了 ITLB 在特定周期收到 PWT 响应时卡死的问题（[#4983](https://github.com/OpenXiangShan/XiangShan/pull/4983)）
  - （V2）在 LLTLB 处理 jmp_bitmap_check 请求时初始化 first_s2xlate_fault 信号，以避免 L2TLB 同时处理 allStage 与 noS2xlate 请求时发生问题（[#4996](https://github.com/OpenXiangShan/XiangShan/pull/4996)）
  - （V2）修复了 prefetch hit 计数器实现错误，导致统计得到的预取命中数目大于预取请求数目的问题（[#5005](https://github.com/OpenXiangShan/XiangShan/pull/5005)）
  - （V2）修复了 VSegment 中非对齐访存拆分时地址生成错误的问题（[#5006](https://github.com/OpenXiangShan/XiangShan/pull/5006)）
  - （V2）修复了 LLPTW 中非必要的位图检查逻辑（[#5018](https://github.com/OpenXiangShan/XiangShan/pull/5018)）
- 工具
  - tl-test-new 支持 anvil 模式下的噪声生成（[tl-test-new #80](https://github.com/OpenXiangShan/tl-test-new/pull/80)）
  - 为 CoupledL2 的 TestTop 添加生成二进制格式 CHI log 的功能，用于压缩日志文件大小（[CoupledL2 #410](http://github.com/OpenXiangShan/CoupledL2/pull/410)）

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.89  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.96  | 433.milc         | 45.10  |
| 429.mcf           | 59.97  | 434.zeusmp       | 51.83  |
| 445.gobmk         | 30.63  | 435.gromacs      | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.94  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.63  |
| 471.omnetpp       | 41.50  | 450.soplex       | 52.48  |
| 473.astar         | 29.30  | 453.povray       | 53.49  |
| 483.xalancbmk     | 72.79  | 454.Calculix     | 16.38  |
| GEOMEAN           | 44.67  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 49.13  |
|                   |        | GEOMEAN          | 44.97  |

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
| commit    | b2daf0a    |
| 日期      | 2025/08/29 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | TileLink   |
| 内存延迟  | DDR4-3200  |

使用 XSCC 编译的 SPEC 2006 性能数据如下所示：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 36.33  | 410.bwaves       | 68.97  |
| 401.bzip2         | 25.74  | 416.gamess       | 44.43  |
| 403.gcc           | 35.70  | 433.milc         | 68.07  |
| 429.mcf           | 61.14  | 434.zeusmp       | 51.66  |
| 445.gobmk         | 30.81  | 435.gromacs      | 30.72  |
| 456.hmmer         | 46.74  | 436.cactusADM    | 66.66  |
| 458.sjeng         | 32.19  | 437.leslie3d     | 49.47  |
| 462.libquantum    | 268.14 | 444.namd         | 34.47  |
| 464.h264ref       | 61.02  | 447.dealII       | 80.67  |
| 471.omnetpp       | 36.09  | 450.soplex       | 52.26  |
| 473.astar         | 28.41  | 453.povray       | 55.62  |
| 483.xalancbmk     | 78.27  | 454.Calculix     | 33.00  |
| GEOMEAN           | 47.25  | 459.GemsFDTD     | 53.37  |
|                   |        | 465.tonto        | 29.55  |
|                   |        | 470.lbm          | 121.32 |
|                   |        | 481.wrf          | 36.72  |
|                   |        | 482.sphinx3      | 51.93  |
|                   |        | GEOMEAN          | 50.97  |

编译参数如下所示：

|          |                        |
| -------- | ---------------------- |
| 编译器   | XSCC 1.0               |
| 编译优化 | O3                     |
| 内存库   | jemalloc               |
| -march   | rv64gc_zba_zbb_zbs_zbc |
| 其他参数 | -ffast-math, -flto     |

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
