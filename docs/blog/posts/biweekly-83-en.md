---
slug: biweekly-83-en
date: 2025-08-18
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 83] 20250818

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 83rd issue of the biweekly report.

<!-- more -->
## Recent developments

### Frontend

### Backend

- Bug Fixes
  - Fixed the naming issue of PMA register output ([#4929](https://github.com/OpenXiangShan/XiangShan/pull/4929))
  - Adjusted the base address of PMA registers ([#4940](https://github.com/OpenXiangShan/XiangShan/pull/4940))
  - Fixed the issue with load fast wake-up where `vsetvli` instruction generates errors ([#4941](https://github.com/OpenXiangShan/XiangShan/pull/4941))

- V3 Feature
  - Changed the naming format of some bundles in the backend ([#4921](https://github.com/OpenXiangShan/XiangShan/pull/4921)), ([#4937](https://github.com/OpenXiangShan/XiangShan/pull/4937))
  - Allowed the last instruction in FTQ to be compressed ([#4931](https://github.com/OpenXiangShan/XiangShan/pull/4931))
  - Checked BJU's predicted jump target in the backend ([#4932](https://github.com/OpenXiangShan/XiangShan/pull/4932))

### MemBlock and cache

## RTL Evaluation

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

We use SimPoint to sample programs and create checkpoints images based on our custom format. The coverage of SimPoint clustering reaches 100%[^1].

Compilation parameters are as follows:

|                    |          |
| ------------------ | -------- |
| Instruction set    | RV64GCB  |
| Compiler           | gcc12    |
| Optimization level | O3       |
| Memory library     | jemalloc |
| -ffp-contraction   | fast     |

Processor and SoC parameters are as follows:

|                |           |
| -------------- | --------- |
| Commit         | ef913a6   |
| L1 ICache      | 64KB      |
| L1 DCache      | 64KB      |
| L2 Cache       | 1MB       |
| L3 Cache       | 16MB      |
| LSU            | 3ld2st    |
| Bus protocol   | TileLink  |
| Memory latency | DDR4-3200 |

[^1]：The above scores are estimated based on program segments rather than a complete SPEC CPU2006 evaluation, which may deviate from the actual performance of real chips.

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
