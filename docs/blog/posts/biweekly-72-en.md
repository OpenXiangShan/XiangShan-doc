---
slug: biweekly-72-en
date: 2025-03-17
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 72】20250317

Welcome to XiangShan biweekly column, this is the 72nd issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - IFU fixed bus return corrupt on uncached region handling ([#4301](https://github.com/OpenXiangShan/XiangShan/pull/4301))

### Backend

- **Bug Fixes**
    - Fixed an issue where the CSR difftest framework incorrectly compared values during reset ([#4419](https://github.com/OpenXiangShan/XiangShan/pull/4419)).  
    - Fixed an issue where CSR read instructions did not process `xireg` in order ([#4393](https://github.com/OpenXiangShan/XiangShan/pull/4393)).  
    - Fixed an issue in `JumpUnit` where high-address truncation errors did not correctly trigger a redirect signal ([#4392](https://github.com/OpenXiangShan/XiangShan/pull/4392)).  
    - Synchronized the release of the JTAG reset signal in specific scenarios ([#4414](https://github.com/OpenXiangShan/XiangShan/pull/4414)).  
    - Fixed an issue in `Trigger` where `pc` and `tdat2` mismatched under specific comparison modes ([#4346](https://github.com/OpenXiangShan/XiangShan/pull/4346)).  
    - Fixed an issue where `AMOCAS` instructions caused stalls due to incorrect renaming ([#4382](https://github.com/OpenXiangShan/XiangShan/pull/4382)).  
    - Fixed an issue where CSR read instructions did not process `VTYPE` in order ([#4354](https://github.com/OpenXiangShan/XiangShan/pull/4354)).  

- **Timing/Area Optimization**
    - Removed redundant logic that used read-only CSR registers as write data inputs ([#4412](https://github.com/OpenXiangShan/XiangShan/pull/4412)).  

- **RVA23 Profile**
    - Integrated and merged the new ChiselAIA (Advanced Interrupt Architecture) into the master ([#4378](https://github.com/OpenXiangShan/XiangShan/pull/4378)).

### MemBlock and cache

- **RVA23 Profile**
  - Added L2 Cache refresh operation ([CoupledL2 #348](https://github.com/OpenXiangShan/CoupledL2/pull/348))

- **Bug fixes**
    - Fix a series of issues related to misaligned load / store violation detection and writeback wakeup logic ([#4333](https://github.com/OpenXiangShan/XiangShan/pull/4333)), ([#4359](https://github.com/OpenXiangShan/XiangShan/pull/4359)), ([#4369](https://github.com/OpenXiangShan/XiangShan/pull/4369)), ([#4426](https://github.com/OpenXiangShan/XiangShan/pull/4426))
    - Fix the bug in multi-core scenarios where difftest does not support checking the results of vector load instructions ([#4361](https://github.com/OpenXiangShan/XiangShan/pull/4361))
    - Fix the functional and performance bug caused by prefetch requests erroneously entering the load RAR queue ([#4367](https://github.com/OpenXiangShan/XiangShan/pull/4367))
    - Fix the handling logic when the Dcache encounters ECC or data errors ([#4345](https://github.com/OpenXiangShan/XiangShan/pull/4345)), ([#4394](https://github.com/OpenXiangShan/XiangShan/pull/4394))
    - Fix the bug of exception address errors caused by mixing multiple virtual and physical address translation modes ([#4349](https://github.com/OpenXiangShan/XiangShan/pull/4349))
    - Fix a series of issues in the MMU related to TLB compression, address truncation, and exception handling ([#4396](https://github.com/OpenXiangShan/XiangShan/pull/4396)), ([#4404](https://github.com/OpenXiangShan/XiangShan/pull/4404)), ([#4406](https://github.com/OpenXiangShan/XiangShan/pull/4406)), ([#4407](https://github.com/OpenXiangShan/XiangShan/pull/4407))
    - Fixed the bug related to CMO transactions in L2 Cache ([CoupledL2 #382](https://github.com/OpenXiangShan/CoupledL2/pull/382)), ([CoupledL2 #378](https://github.com/OpenXiangShan/CoupledL2/pull/378))
    - Fixed the logic issues related to directory hit/miss in L2 Cache during nested transactions; for ProbeAck/ProbeAckData transactions, updated the state in the MSHR ([CoupledL2 #374](https://github.com/OpenXiangShan/CoupledL2/pull/382)), ([CoupledL2 #377](https://github.com/OpenXiangShan/CoupledL2/pull/378))


## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 9245b52 from March 14** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 66.89  |
| 401.bzip2         | 25.50  | 416.gamess        | 40.89  |
| 403.gcc           | 46.72  | 433.milc          | 45.25  |
| 429.mcf           | 58.13  | 434.zeusmp        | 52.10  |
| 445.gobmk         | 30.26  | 435.gromacs       | 33.65  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.16  |
| 458.sjeng         | 30.53  | 437.leslie3d      | 46.01  |
| 462.libquantum    | 122.50 | 444.namd          | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII        | 73.43  |
| 471.omnetpp       | 39.37  | 450.soplex        | 51.99  |
| 473.astar         | 29.23  | 453.povray        | 53.44  |
| 483.xalancbmk     | 72.03  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.15  | 459.GemsFDTD      | 37.18  |
|                   |        | 465.tonto         | 36.67  |
|                   |        | 470.lbm           | 91.24  |
|                   |        | 481.wrf           | 40.62  |
|                   |        | 482.sphinx3       | 48.57  |
|                   |        | **GEOMEAN**       | 44.60  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao
