---
slug: biweekly-79-en
date: 2025-06-23
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 79】20250623

Welcome to XiangShan biweekly column, this is the 79th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- **Area**

### Backend

- **Bug Fixes**
    - Fixed incorrect update of `xstatus.VS` when a vector memory access instruction raises an exception ([#4817](https://github.com/OpenXiangShan/XiangShan/pull/4817))
    - Fixed incorrect reads of AIA-related CSRs ([#4802](https://github.com/OpenXiangShan/XiangShan/pull/4802))
    - Fixed issue where the NMI pending bit (`nmip`) was not properly cleared ([#4825](https://github.com/OpenXiangShan/XiangShan/pull/4825))
    - Fixed cluster-wide broadcast storm caused by external trigger in the Debug Module ([#4801](https://github.com/OpenXiangShan/XiangShan/pull/4801))

### MemBlock and cache

- **RVA23 Profile**

- **Bug fixes**

- **PPA Optimizations**

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit f9d8efe from May 8** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.93  | 410.bwaves        | 66.86  |
| 401.bzip2         | 25.51  | 416.gamess        | 40.90  |
| 403.gcc           | 47.91  | 433.milc          | 45.17  |
| 429.mcf           | 59.57  | 434.zeusmp        | 52.09  |
| 445.gobmk         | 30.32  | 435.gromacs       | 33.66  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.52  | 437.leslie3d      | 45.90  |
| 462.libquantum    | 122.43 | 444.namd          | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII        | 73.57  |
| 471.omnetpp       | 41.45  | 450.soplex        | 52.64  |
| 473.astar         | 29.30  | 453.povray        | 53.39  |
| 483.xalancbmk     | 72.95  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.59  | 459.GemsFDTD      | 35.68  |
|                   |        | 465.tonto         | 36.69  |
|                   |        | 470.lbm           | 91.19  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.54  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
- XiangShan Documentation: https://xiangshan-doc.readthedocs.io/
- XiangShan User Guide: https://docs.xiangshan.cc/projects/user-guide/
- XiangShan Design Doc: https://docs.xiangshan.cc/projects/design/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao