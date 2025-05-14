---
slug: biweekly-76-en
date: 2025-05-12
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 76】20250512

Welcome to XiangShan biweekly column, this is the 76th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption. In addition, the backend has fixed a number of bugs related to interrupt handling, and the memory and cache  have fixed many bugs related to StoreQueue, Uncache, and misalignment. This update also includes the latest performance improvements of the Kunminghu architecture.

<!-- more -->
## Recent developments

### Frontend

Nothing

### Backend

* **Bug Fixes**

  * Fixed the read/write permission issue for the LCOFI (Local Counter Overflow Interrupt) bit (bit 13) in `xvip`/`xvien` registers ([#4648](https://github.com/OpenXiangShan/XiangShan/pull/4648)).
  * Fixed incorrect access control of `sireg` and `vsireg` by `xstateen` ([#4649](https://github.com/OpenXiangShan/XiangShan/pull/4649)).
  * Fixed an issue where virtual interrupt injection was not gated by `mnstatus.nmie` ([#4645](https://github.com/OpenXiangShan/XiangShan/pull/4645)).
  * Fixed WFI instructions not being woken up by non-maskable interrupts ([#4645](https://github.com/OpenXiangShan/XiangShan/pull/4645)).
  * Fixed incorrect updates to the `tval` register in scenarios where interrupts, CSR-related exceptions, and redirects occurred simultaneously ([#4671](https://github.com/OpenXiangShan/XiangShan/pull/4671)).
  * Fixed incorrect `mcause` updates during interrupt double-trap scenarios ([#4671](https://github.com/OpenXiangShan/XiangShan/pull/4671)).
  * Fixed an issue where `tval` failed to update correctly if EX\_II/EX\_VI exceptions occurred both in the original instruction and again in the interrupt handler ([#4671](https://github.com/OpenXiangShan/XiangShan/pull/4671)).

* **Others**

  * Added version information to the simulation output ([#4626](https://github.com/OpenXiangShan/XiangShan/pull/4626)).


### MemBlock and cache

- **Bug fixes**
  * Fixed the dequeue logic in StoreQueue when a uncache store causes an exception ([#4641](https://github.com/OpenXiangShan/XiangShan/pull/4641))
  * Change UncacheBuffer’s store and load to enqueue based on robIdx arbitration to prevent dependency deadlock ([#4628](https://github.com/OpenXiangShan/XiangShan/pull/4628))
  * Fixed bug where, for unaligned memory accesses crossing a page boundary that trigger an exception on the new page, the written *tval still takes the address of the previous page ([#4673](https://github.com/OpenXiangShan/XiangShan/pull/4673))
  * For unaligned memory-access instructions, perform a rollback when the RAW queue is full to avoid stalling ([#4674](https://github.com/OpenXiangShan/XiangShan/pull/4674))
  * Fixed a bug in StoreQueue when a CBO instruction raises an exception ([#4663](https://github.com/OpenXiangShan/XiangShan/pull/4663))
  * Fixed bugs in the genVpn function that didn’t account for different virtualization stages and didn’t handle large-page VPN concatenation correctly ([#4647](https://github.com/OpenXiangShan/XiangShan/pull/4647))
  * Fixed a bug where PPNs were generated incorrectly when using virtualization allStage while both VS-Stage and G-Stage are huge pages ([#4648](https://github.com/OpenXiangShan/XiangShan/pull/4648))
  * Fixed the hit-matching logic in the MMU for some napot scenarios ([#4659](https://github.com/OpenXiangShan/XiangShan/pull/4659))
  * Fixed bug in StoreQueue where vector exception flags could incorrectly trigger a timeout assert ([#4660](https://github.com/OpenXiangShan/XiangShan/pull/4660))

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
