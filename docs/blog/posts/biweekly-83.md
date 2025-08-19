---
slug: biweekly-83
date: 2025-08-18
categories:
  - Biweekly
---

# 【香山双周报 83】20250818 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 83 期双周报。

在过去的两周，前端继续进行 V3 的 RTL 开发，同时在模型上探索分支预测的设计。后端与访存缓存修复了一系列功能 bug。后端还进行了 V3 开发的准备工作，主要包含一些代码清理和前后端接口重构。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 初步支持 IFU 2-fetch；优化时序（[#4917](https://github.com/OpenXiangShan/XiangShan/pull/4917)）
  - 合入 BPU V3 第四部分（[#4946](https://github.com/OpenXiangShan/XiangShan/pull/4946)）
    - 移植 V2 RAS
    - 移植 V2 ITTAGE（初稿）
    - 支持 WriteBuffer 多端口访问；接入到 ABTB 及 MBTB
    - 修复 PHR 推测更新逻辑；增加 PHR 历史 difftest
- Bug 修复
  - 正确设置 ICache TileLink 总线的 MemBackType、Alias 域（[#4943](https://github.com/OpenXiangShan/XiangShan/pull/4943)，部分移植自 V2 [#4898](https://github.com/OpenXiangShan/XiangShan/pull/4898)）
- 模型探索
  - 探索 TAGE-SC 可落地方案
  - 分析 2-taken 性能
- 代码质量
  - 迁移 ICache 到新参数系统（[#4934](https://github.com/OpenXiangShan/XiangShan/pull/4934)）
  - 清理 BPU 过时代码和相关参数（[#4946](https://github.com/OpenXiangShan/XiangShan/pull/4946)）

### 后端

- RTL 新特性
  - 更改后段内部分 Bundle 的命名格式（[#4921](https://github.com/OpenXiangShan/XiangShan/pull/4921)，[#4937](https://github.com/OpenXiangShan/XiangShan/pull/4937)）
  - 允许 FTQ 中最后一项的指令进行压缩（[#4931](https://github.com/OpenXiangShan/XiangShan/pull/4931)）
  - 在后端中检查 BJU 的跳转目标预测（[#4932](https://github.com/OpenXiangShan/XiangShan/pull/4932)）
- Bug 修复
  - （V2）修复 PMA 寄存器输出的命名问题（[#4929](https://github.com/OpenXiangShan/XiangShan/pull/4929)）
  - （V2）调整 PMA 寄存器的基地址（[#4940](https://github.com/OpenXiangShan/XiangShan/pull/4940)）
  - （V2）修复 load 快速唤醒 `vsetvli` 指令产生错误的问题（[#4941](https://github.com/OpenXiangShan/XiangShan/pull/4941)）

### 访存与缓存

- Bug 修复
  - （V2）修复了 PageTableCache 中触发 `jmp_bitmap_check` 的逻辑（[#4935](https://github.com/OpenXiangShan/XiangShan/pull/4935)）
  - 修复了 NEMU 在发生 hardware-error exception 时未正确设置 GVA 的问题（[NEMU #921](https://github.com/OpenXiangShan/NEMU/pull/921)）
  - 修复了 NEMU 使用 MPRV 时未检查 NMIE 的问题。当 NMIE = 0 时，MPRV 应被视为清除（[NEMU #920](https://github.com/OpenXiangShan/NEMU/pull/920)）
- 工具
  - 修复了 CHIron 的一系列问题

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.95  | 433.milc         | 45.09  |
| 429.mcf           | 60.19  | 434.zeusmp       | 51.78  |
| 445.gobmk         | 30.62  | 435.gromacs      | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII       | 73.27  |
| 471.omnetpp       | 41.35  | 450.soplex       | 52.50  |
| 473.astar         | 29.30  | 453.povray       | 53.49  |
| 483.xalancbmk     | 72.76  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.66  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.73  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.63  |
|                   |        | 482.sphinx3      | 49.10  |
|                   |        | GEOMEAN          | 44.94  |

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
| commit    | ef913a6    |
| 日期      | 2025/08/14 |
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
