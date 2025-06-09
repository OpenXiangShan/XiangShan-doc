---
slug: biweekly-78-en
date: 2025-06-09
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 78】20250609

Welcome to XiangShan biweekly column, this is the 78th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- **Area**

### Backend

* **Bug Fixes**

  * Fixed an issue where asynchronous updates to the `xtopi` CSR caused difftest mismatches: temporarily skipped `xtopi` in difftest comparison ([#4742](https://github.com/OpenXiangShan/XiangShan/pull/4742))
  * Fixed a problem where `sstateenx` was not correctly generated as a Verilog module ([#4723](https://github.com/OpenXiangShan/XiangShan/pull/4723))
  * Moved the core-side trace collection of `xret` instructions from the commit stage to the rename stage ([#4736](https://github.com/OpenXiangShan/XiangShan/pull/4736))

* **Tooling**
  * Added support for using a custom `HINT` instruction as a debug trigger in FPGA simulation ([#4776](https://github.com/OpenXiangShan/XiangShan/pull/4776))

### MemBlock and cache

- **RVA23 Profile**

- **Bug fixes**

- **PPA Optimizations**

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 2272661 from June 6** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.89  | 410.bwaves        | 66.98  |
| 401.bzip2         | 25.51  | 416.gamess        | 40.91  |
| 403.gcc           | 47.90  | 433.milc          | 45.05  |
| 429.mcf           | 60.24  | 434.zeusmp        | 51.65  |
| 445.gobmk         | 30.43  | 435.gromacs       | 33.66  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.20  |
| 458.sjeng         | 30.46  | 437.leslie3d      | 47.95  |
| 462.libquantum    | 122.63 | 444.namd          | 28.87  |
| 464.h264ref       | 56.59  | 447.dealII        | 73.03  |
| 471.omnetpp       | 41.38  | 450.soplex        | 52.52  |
| 473.astar         | 29.36  | 453.povray        | 53.40  |
| 483.xalancbmk     | 72.54  | 454.Calculix      | 16.37  |
| **GEOMEAN**       | 44.62  | 459.GemsFDTD      | 39.16  |
|                   |        | 465.tonto         | 36.65  |
|                   |        | 470.lbm           | 91.98  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.87  |

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