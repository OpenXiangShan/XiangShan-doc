---
slug: biweekly-81-en
date: 2025-07-21
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 81】20250721

Welcome to XiangShan biweekly column, this is the 81st issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have started designing V3. In addition, the fronted fixed issue where parity check might use invalid results when ICache requests cross lines, the backend fixed the issue of incorrect bit width calculation for variables such as the total number of instruction commit and the total number of walk in VTypeBuffer under specific parameters, and the memory and cache subsystem fixed a bug where vector segment instructions failed to correctly report ECC errors. This update also includes the latest performance improvements of the Kunminghu architecture.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- **V3 Feature**

### Backend

- **Bug Fixes**

- **V3 Feature**

### MemBlock and cache

- **Bug fixes**
    - L2 Cache maintains maximum QoS for real-time device-related transactions ([CoupledL2 #423](https://github.com/OpenXiangShan/CoupledL2/pull/423))
    - Resolve the X-state error propagation from the RefillBuffer to the DataStorage ([CoupledL2 #426](https://github.com/OpenXiangShan/CoupledL2/pull/426))

- **V3 Feature**

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit c25dcc6 from July 3** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 67.02  |
| 401.bzip2         | 25.50  | 416.gamess        | 40.99  |
| 403.gcc           | 47.90  | 433.milc          | 44.69  |
| 429.mcf           | 60.13  | 434.zeusmp        | 51.57  |
| 445.gobmk         | 30.70  | 435.gromacs       | 33.63  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.65  | 437.leslie3d      | 46.68  |
| 462.libquantum    | 105.08 | 444.namd          | 28.87  |
| 464.h264ref       | 56.60  | 447.dealII        | 72.19  |
| 471.omnetpp       | 41.52  | 450.soplex        | 52.33  |
| 473.astar         | 29.35  | 453.povray        | 53.46  |
| 483.xalancbmk     | 72.11  | 454.Calculix      | 16.37  |
| **GEOMEAN**       | 44.09  | 459.GemsFDTD      | 39.64  |
|                   |        | 465.tonto         | 36.12  |
|                   |        | 470.lbm           | 85.79  |
|                   |        | 481.wrf           | 40.30  |
|                   |        | 482.sphinx3       | 48.48  |
|                   |        | **GEOMEAN**       | 44.50  |

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
