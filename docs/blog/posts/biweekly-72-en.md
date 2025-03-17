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

<<<<<<< HEAD
- **Bug fixes**
    - Fix a series of issues related to misaligned load / store violation detection and writeback wakeup logic ([#4333](https://github.com/OpenXiangShan/XiangShan/pull/4333)), ([#4359](https://github.com/OpenXiangShan/XiangShan/pull/4359)), ([#4369](https://github.com/OpenXiangShan/XiangShan/pull/4369)), ([#4426](https://github.com/OpenXiangShan/XiangShan/pull/4426))
    - Fix the bug in multi-core scenarios where difftest does not support checking the results of vector load instructions ([#4361](https://github.com/OpenXiangShan/XiangShan/pull/4361))
    - Fix the functional and performance bug caused by prefetch requests erroneously entering the load RAR queue ([#4367](https://github.com/OpenXiangShan/XiangShan/pull/4367))
    - Fix the handling logic when the Dcache encounters ECC or data errors ([#4345](https://github.com/OpenXiangShan/XiangShan/pull/4345)), ([#4394](https://github.com/OpenXiangShan/XiangShan/pull/4394))
    - Fix the bug of exception address errors caused by mixing multiple virtual and physical address translation modes ([#4349](https://github.com/OpenXiangShan/XiangShan/pull/4349))
    - Fix a series of issues in the MMU related to TLB compression, address truncation, and exception handling ([#4396](https://github.com/OpenXiangShan/XiangShan/pull/4396)), ([#4404](https://github.com/OpenXiangShan/XiangShan/pull/4404)), ([#4406](https://github.com/OpenXiangShan/XiangShan/pull/4406)), ([#4407](https://github.com/OpenXiangShan/XiangShan/pull/4407))
=======
- **RVA23 Profile**
  - Added L2 Cache refresh operation ([CoupledL2 #348](https://github.com/OpenXiangShan/CoupledL2/pull/348))

- **Bug fixes**
  - Fixed the problem with L1 DCache error address selection ([#4394](https://github.com/OpenXiangShan/XiangShan/pull/4394))
  - Fixed the issue of incorrect assignment of the enable signal in L1 DCache error handling ([#4345](https://github.com/OpenXiangShan/XiangShan/pull/4345))
  - Fixed the bugs caused by L1 DCache prefetch requests entering the RAR queue ([#4367](https://github.com/OpenXiangShan/XiangShan/pull/4367))
  - Fixed the bug related to CMO transactions in L2 Cache ([CoupledL2 #382](https://github.com/OpenXiangShan/CoupledL2/pull/382)), ([CoupledL2 #378](https://github.com/OpenXiangShan/CoupledL2/pull/378))
  - Fixed the logic issues related to directory hit/miss in L2 Cache during nested transactions; for ProbeAck/ProbeAckData transactions, updated the state in the MSHR ([CoupledL2 #374](https://github.com/OpenXiangShan/CoupledL2/pull/382)), ([CoupledL2 #377](https://github.com/OpenXiangShan/CoupledL2/pull/378))

- **PPA Optimizations**
>>>>>>> e9bc457 (docs(biweek-72): add RAS and coupledL2)

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit a60d667 from December 6** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.10  | 410.bwaves        | 67.07  |
| 401.bzip2         | 25.53  | 416.gamess        | 42.95  |
| 403.gcc           | 47.17  | 433.milc          | 45.29  |
| 429.mcf           | 58.86  | 434.zeusmp        | 56.75  |
| 445.gobmk         | 30.30  | 435.gromacs       | 37.44  |
| 456.hmmer         | 40.79  | 436.cactusADM     | 49.30  |
| 458.sjeng         | 30.22  | 437.leslie3d      | 45.29  |
| 462.libquantum    | 124.56 | 444.namd          | 34.65  |
| 464.h264ref       | 57.72  | 447.dealII        | 74.37  |
| 471.omnetpp       | 40.11  | 450.soplex        | 54.63  |
| 473.astar         | 29.14  | 453.povray        | 54.95  |
| 483.xalancbmk     | 73.25  | 454.Calculix      | 18.33  |
| **GEOMEAN**       | 44.61  | 459.GemsFDTD      | 40.22  |
|                   |        | 465.tonto         | 37.99  |
|                   |        | 470.lbm           | 102.47 |
|                   |        | 481.wrf           | 43.22  |
|                   |        | 482.sphinx3       | 53.26  |
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
