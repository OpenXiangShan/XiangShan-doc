---
slug: biweekly-63-en
date: 2024-11-11
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 63】20241111

Welcome to XiangShan biweekly column, this is the 63th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently,

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- **Timing**

- **Code Style**

### Backend

- **Bug Fixes**

- **Timing/Power Optimization**

- **RVA23 Profile**

### MemBlock and cache

- **CHI Bus**

- **Bug fixes**

- **PPA Optimizations**

- **Tool**

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **version b3c3582 from October 26** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.85  | 410.bwaves        | 75.02  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.49  |
| 403.gcc           | 46.49  | 433.milc          | 43.61  |
| 429.mcf           | 57.50  | 434.zeusmp        | 56.80  |
| 445.gobmk         | 30.18  | 435.gromacs       | 37.38  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 48.77  |
| 458.sjeng         | 30.18  | 437.leslie3d      | 43.82  |
| 462.libquantum    | 125.07 | 444.namd          | 34.69  |
| 464.h264ref       | 57.81  | 447.dealII        | 74.53  |
| 471.omnetpp       | 40.01  | 450.soplex        | 54.54  |
| 473.astar         | 29.00  | 453.povray        | 55.93  |
| 483.xalancbmk     | 74.74  | 454.Calculix      | 18.32  |
| **GEOMEAN**       | 44.49  | 459.GemsFDTD      | 37.82  |
|                   |        | 465.tonto         | 38.21  |
|                   |        | 470.lbm           | 102.05 |
|                   |        | 481.wrf           | 42.68  |
|                   |        | 482.sphinx3       | 52.71  |
|                   |        | **GEOMEAN**       | 47.42  |

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
