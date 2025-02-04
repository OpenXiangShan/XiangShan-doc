---
slug: biweekly-69-en
date: 2025-02-03
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 69】20250203

Happy Chinese New Year! Welcome to XiangShan biweekly column, this is the 69th issue of our biweekly column.

This update mainly includes the latest performance improvements of the Kunminghu architecture.

<!-- more -->

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 977ac3b from January 27** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.90  | 410.bwaves        | 66.62  |
| 401.bzip2         | 25.54  | 416.gamess        | 40.90  |
| 403.gcc           | 46.66  | 433.milc          | 45.20  |
| 429.mcf           | 58.10  | 434.zeusmp        | 51.96  |
| 445.gobmk         | 30.35  | 435.gromacs       | 33.61  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.26  |
| 458.sjeng         | 30.48  | 437.leslie3d      | 46.09  |
| 462.libquantum    | 122.57 | 444.namd          | 28.91  |
| 464.h264ref       | 56.65  | 447.dealII        | 73.47  |
| 471.omnetpp       | 39.43  | 450.soplex        | 52.01  |
| 473.astar         | 29.23  | 453.povray        | 53.41  |
| 483.xalancbmk     | 72.04  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.17  | 459.GemsFDTD      | 36.02  |
|                   |        | 465.tonto         | 36.74  |
|                   |        | 470.lbm           | 91.18  |
|                   |        | 481.wrf           | 40.62  |
|                   |        | 482.sphinx3       | 48.57  |
|                   |        | **GEOMEAN**       | 44.51  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao
