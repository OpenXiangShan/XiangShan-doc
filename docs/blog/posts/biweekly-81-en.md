---
slug: biweekly-81-en
date: 2025-07-21
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 81】20250721

Welcome to XiangShan biweekly column, this is the 81st issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have started designing V3. In addition, the fronted fixed the logic that checks whether the previous MMIO instruction was successfully committed before fetching a new MMIO instruction, the backend fixed the issue where RAB fails to correctly walk and reallocate physical registers when a move instruction triggers an exception, and the memory and cache subsystem fixed a series of bugs related to misaligned vector loads / stores. This update also includes the latest performance improvements of the Kunminghu architecture.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed the logic that checks whether the previous MMIO instruction was successfully committed before fetching a new MMIO instruction ([#4881](https://github.com/OpenXiangShan/XiangShan/pull/4881))

### Backend

- **Bug Fixes**
  * Fixed the issue where RAB fails to correctly walk and reallocate physical registers when a move instruction triggers an exception ([#4874](https://github.com/OpenXiangShan/XiangShan/pull/4874))
  * Fixed the missing exception check for the `vm` bit in certain instructions (vadc/vsbc) in NEMU ([NEMU #914](https://github.com/OpenXiangShan/NEMU/pull/914))

### MemBlock and cache

- **Bug fixes**
    - Fixed a series of bugs related to misaligned vector loads / stores ([#4869](https://github.com/OpenXiangShan/XiangShan/pull/4869)), ([#4876](https://github.com/OpenXiangShan/XiangShan/pull/4876)), ([#4877](https://github.com/OpenXiangShan/XiangShan/pull/4877)), ([#4889](https://github.com/OpenXiangShan/XiangShan/pull/4889))
    - Fixed a bug where VBOP prefetcher failed to pass the isPrefetch signal to TLB ([#4886](https://github.com/OpenXiangShan/XiangShan/pull/4886))
    - L2 Cache maintains maximum QoS for real-time device-related transactions ([CoupledL2 #423](https://github.com/OpenXiangShan/CoupledL2/pull/423))
    - Resolve the X-state error propagation from the RefillBuffer to the DataStorage ([CoupledL2 #426](https://github.com/OpenXiangShan/CoupledL2/pull/426))

- **V3 Feature**
    - L1 DCache now supports using a hash of higher virtual address bits as index ([#4810](https://github.com/OpenXiangShan/XiangShan/pull/4810))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit a193669 from July 17** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.89  | 410.bwaves        | 67.24  |
| 401.bzip2         | 25.51  | 416.gamess        | 41.00  |
| 403.gcc           | 47.91  | 433.milc          | 44.95  |
| 429.mcf           | 60.17  | 434.zeusmp        | 51.71  |
| 445.gobmk         | 30.71  | 435.gromacs       | 33.65  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.65  | 437.leslie3d      | 47.77  |
| 462.libquantum    | 122.65 | 444.namd          | 28.88  |
| 464.h264ref       | 56.62  | 447.dealII        | 73.21  |
| 471.omnetpp       | 41.49  | 450.soplex        | 52.55  |
| 473.astar         | 29.35  | 453.povray        | 53.48  |
| 483.xalancbmk     | 72.75  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.70  | 459.GemsFDTD      | 40.45  |
|                   |        | 465.tonto         | 36.68  |
|                   |        | 470.lbm           | 91.96  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.12  |
|                   |        | **GEOMEAN**       | 44.98  |

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
