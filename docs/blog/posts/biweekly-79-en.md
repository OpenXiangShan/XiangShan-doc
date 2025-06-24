---
slug: biweekly-79-en
date: 2025-06-23
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 79】20250623

Welcome to XiangShan biweekly column, this is the 79th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption. In addition, the backend fixed incorrect update of `xstatus.VS` when a vector memory access instruction raises an exception, and the memory and cache subsystem fixed performance degradation after context switch caused by ineffective global bit setting in page tables.

<!-- more -->
## Recent developments

### Frontend

Nothing

### Backend

- **Bug Fixes**
    - Fixed incorrect update of `xstatus.VS` when a vector memory access instruction raises an exception ([#4817](https://github.com/OpenXiangShan/XiangShan/pull/4817))
    - Fixed incorrect reads of AIA-related CSRs ([#4802](https://github.com/OpenXiangShan/XiangShan/pull/4802))
    - Fixed issue where the NMI pending bit (`nmip`) was not properly cleared ([#4825](https://github.com/OpenXiangShan/XiangShan/pull/4825))
    - Fixed cluster-wide broadcast storm caused by external trigger in the Debug Module ([#4801](https://github.com/OpenXiangShan/XiangShan/pull/4801))

### MemBlock and cache

- **Bug fixes**
    - Fixed the hang caused by the MSHR incorrectly waiting for cache replacement when an NDERR occurs ([CoupledL2 #418](https://github.com/OpenXiangShan/CoupledL2/pull/418))
    - Fixed a deadlock bug in LLPTW caused by a corner case when handling both virtualized and non-virtualized requests ([#4829](https://github.com/OpenXiangShan/XiangShan/pull/4829))
    - Fixed performance degradation after context switch caused by ineffective global bit setting in page tables ([#4811](https://github.com/OpenXiangShan/XiangShan/pull/4811))
    - Refactored and distinguished storemisalignbuffernack behavior under scalar/vector modes when the smb is full ([#4807](https://github.com/OpenXiangShan/XiangShan/pull/4807))
    - Disabled misaligned exceptions for vector memory access (vector currently does not support MMIO) ([#4792](https://github.com/OpenXiangShan/XiangShan/pull/4792))
    - Fixed missing hardware error exceptions for vector segment load/store to MMIO ([#4800](https://github.com/OpenXiangShan/XiangShan/pull/4800)), ([#4799](https://github.com/OpenXiangShan/XiangShan/pull/4799))
    - Fixed an assertion issue caused by incorrect LLPTW FSM transitions under virtualization ([#4788](https://github.com/OpenXiangShan/XiangShan/pull/4788))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 2272661 from June 6** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

**Note: The performance evaluation code version for this biweekly are the same as the last biweekly, and will be updated with the latest scores in the next biweekly.**

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

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Liu Weiding, Ma Yuexiao
