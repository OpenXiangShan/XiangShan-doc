---
slug: biweekly-65-en
date: 2024-12-09
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 65】20241209

Welcome to XiangShan biweekly column, this is the 65th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently,

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - test ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- **Features**

- **Power**

### Backend

- **Bug Fixes**

- **Timing/Area Optimization**

- **RVA23 Profile**

- **Tools**

### MemBlock and cache

- **RVA23 Profile**

- **Bug fixes**

- **PPA Optimizations**

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit f12520c from November 22** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.09  | 410.bwaves        | 66.01  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.43  |
| 403.gcc           | 47.23  | 433.milc          | 45.26  |
| 429.mcf           | 58.81  | 434.zeusmp        | 56.88  |
| 445.gobmk         | 30.26  | 435.gromacs       | 37.45  |
| 456.hmmer         | 40.79  | 436.cactusADM     | 49.19  |
| 458.sjeng         | 30.27  | 437.leslie3d      | 45.32  |
| 462.libquantum    | 124.42 | 444.namd          | 34.65  |
| 464.h264ref       | 57.74  | 447.dealII        | 74.48  |
| 471.omnetpp       | 40.03  | 450.soplex        | 54.65  |
| 473.astar         | 29.06  | 453.povray        | 55.00  |
| 483.xalancbmk     | 74.23  | 454.Calculix      | 18.33  |
| **GEOMEAN**       | 44.64  | 459.GemsFDTD      | 40.22  |
|                   |        | 465.tonto         | 38.16  |
|                   |        | 470.lbm           | 102.48 |
|                   |        | 481.wrf           | 43.22  |
|                   |        | 482.sphinx3       | 53.24  |
|                   |        | **GEOMEAN**       | 47.48  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao

Reviewer: XiangShan Publicity Team
