---
slug: biweekly-114
date: 2026-10-28
categories:
  - Biweekly
---

# 【香山双周报 114】20261028 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 114 期双周报。

<!-- TODO: 补充本期开发进展概述。 -->

<!-- more -->

## 近期进展

### 前端

- TODO

### 后端

- TODO

### 访存与缓存

- TODO

### XSAI

- TODO

### 基础设施

- FPGA DiffTest
  - 新增可动态切换的 FAST/SLOW 参考执行模式，并在单核 XDMA 配置下支持基于 fork 的并行检查，由 SLOW 进程完整检查 DUT、按段确认结果，并在 FAST 执行分歧时接替（[difftest #980](https://github.com/OpenXiangShan/difftest/pull/980)、[NEMU #1247](https://github.com/OpenXiangShan/NEMU/pull/1247)）
  - 支持单核 REF-driving trace 的录制与独立回放，记录 SLOW、FAST 和 FORK 模式下驱动参考模型的 DUT 窗口，支持普通及 ZSTD 压缩格式（[difftest #981](https://github.com/OpenXiangShan/difftest/pull/981)）
- NEMU 参考模型
  - 在主线新增昆明湖 V2 单核、双核 REF、调试 REF 及独立运行配置，将参考模型纳入 CI 构建与发布，并以独立功能配置区分 V2/V3 行为差异，同步 HLVX 权限、LR 原子访问权限、双重陷阱及向量存储状态等公共修复（[NEMU #1246](https://github.com/OpenXiangShan/NEMU/pull/1246)）
  - 修复非 segment、单位步长向量存储跨页遇到异常时首个页面写入丢失的问题，保留已完成的部分写入及对应 DiffTest 存储记录，并同步至主线和昆明湖 V2 分支（[NEMU #1240](https://github.com/OpenXiangShan/NEMU/pull/1240)、[NEMU #1241](https://github.com/OpenXiangShan/NEMU/pull/1241)）
  - 优化 StoreHash 的 CRC 软件校验，将逐半字节查表改为按 64 位字折叠计算，降低存储记录校验开销（[NEMU #1252](https://github.com/OpenXiangShan/NEMU/pull/1252)）

### XS-GEM5

- TODO

## 性能评估

<!-- TODO: 核对处理器、SoC 及编译参数配置，补充 commit、评估日期与性能数据。 -->

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | TBD        |
| 日期      | TBD        |
| L1 ICache | 64 KB      |
| L1 DCache | 64 KB      |
| L2 Cache  | 2 MB       |
| L3 Cache  | 32 MB      |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        | TBD    | TBD    | 410.bwaves          | TBD    | TBD    |
| 401.bzip2            | TBD    | TBD    | 416.gamess          | TBD    | TBD    |
| 403.gcc              | TBD    | TBD    | 433.milc            | TBD    | TBD    |
| 429.mcf              | TBD    | TBD    | 434.zeusmp          | TBD    | TBD    |
| 445.gobmk            | TBD    | TBD    | 435.gromacs         | TBD    | TBD    |
| 456.hmmer            | TBD    | TBD    | 436.cactusADM       | TBD    | TBD    |
| 458.sjeng            | TBD    | TBD    | 437.leslie3d        | TBD    | TBD    |
| 462.libquantum       | TBD    | TBD    | 444.namd            | TBD    | TBD    |
| 464.h264ref          | TBD    | TBD    | 447.dealII          | TBD    | TBD    |
| 471.omnetpp          | TBD    | TBD    | 450.soplex          | TBD    | TBD    |
| 473.astar            | TBD    | TBD    | 453.povray          | TBD    | TBD    |
| 483.xalancbmk        | TBD    | TBD    | 454.calculix        | TBD    | TBD    |
| GEOMEAN              | TBD    | TBD    | 459.GemsFDTD        | TBD    | TBD    |
|                      |        |        | 465.tonto           | TBD    | TBD    |
|                      |        |        | 470.lbm             | TBD    | TBD    |
|                      |        |        | 481.wrf             | TBD    | TBD    |
|                      |        |        | 482.sphinx3         | TBD    | TBD    |
|                      |        |        | GEOMEAN             | TBD    | TBD    |

编译参数如下所示：

| 参数          | GCC16                      | XSCC                |
| ------------- | -------------------------- | ------------------- |
| 编译器        | gcc16                      | xscc                |
| 编译优化      | O3                         | O3                  |
| 内存库        | jemalloc                   | jemalloc            |
| 指令集配置    | 基于 RVA23（禁用向量扩展） | RV64GCB             |
| -ffp-contract | fast                       | fast                |
| 链接优化      | -flto                      | -flto               |
| 浮点优化      | -ffast-math                | -ffast-math         |
| -mcpu         | -                          | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，SimPoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、李昕、燕翼鸣
