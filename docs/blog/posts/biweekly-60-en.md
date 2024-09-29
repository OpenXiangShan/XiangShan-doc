---
slug: biweekly-59-en
date: 2024-09-16
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 59】20240916

Welcome to XiangShan biweekly column, this is the 59th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently,

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed a bug ([#bug](https://github.com/OpenXiangShan/XiangShan/pull/bug))

### Backend

- **Bug Fixes**
    - Continuously advancing function bug fixes, with over ?? issues resolved. Here are some of the PRs:

- **Timing Optimization**

- **RVA23 Profile**

### MemBlock and cache


- **CHI Bus**

- **RVA23 Profile**

- **Performance**

- **Bug fixes**

- **PPA Optimizations**

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC06 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPEC06FP set to fast. The instruction set used was RV64GCB. We ran SPEC06 checkpoints on the XiangShan processor **version 42b6cdf from September 5** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.84  | 410.bwaves        | 77.28  |
| 401.bzip2         | 25.52  | 416.gamess        | 43.52  |
| 403.gcc           | 48.49  | 433.milc          | 42.48  |
| 429.mcf           | 58.95  | 434.zeusmp        | 56.99  |
| 445.gobmk         | 30.20  | 435.gromacs       | 37.38  |
| 456.hmmer         | 41.30  | 436.cactusADM     | 48.45  |
| 458.sjeng         | 30.12  | 437.leslie3d      | 43.67  |
| 462.libquantum    | 127.52 | 444.namd          | 34.30  |
| 464.h264ref       | 57.81  | 447.dealII        | 74.82  |
| 471.omnetpp       | 41.79  | 450.soplex        | 54.49  |
| 473.astar         | 29.17  | 453.povray        | 55.61  |
| 483.xalancbmk     | 75.84  | 454.Calculix      | 18.21  |
| **GEOMEAN**       | 45.09  | 459.GemsFDTD      | 37.24  |
|                   |        | 465.tonto         | 36.21  |
|                   |        | 470.lbm           | 101.29 |
|                   |        | 481.wrf           | 43.52  |
|                   |        | 482.sphinx3       | 51.32  |
|                   |        | **GEOMEAN**       | 47.12  |

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
