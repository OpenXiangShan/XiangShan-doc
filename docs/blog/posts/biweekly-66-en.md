---
slug: biweekly-66-en
date: 2024-12-23
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 66】20241223

Welcome to XiangShan biweekly column, this is the 66th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- **Area**

### Backend

- **Bug Fixes**
    - Fixed an issue where some vector instructions failed to set `vs dirty` ([#4024](https://github.com/OpenXiangShan/XiangShan/pull/4024)).
    - Fixed incorrect `vlmax` configuration when `LMUL` is less than 1 ([#4028](https://github.com/OpenXiangShan/XiangShan/pull/4028)).
    - Fixed an issue in `rocket-chip` where vector mask instructions did not preserve `vm = 0` ([#3918](https://github.com/OpenXiangShan/XiangShan/pull/3918)).
    - Fixed snapshot selection and walk refresh errors when `rob` is full ([#4049](https://github.com/OpenXiangShan/XiangShan/pull/4049)).
    - Fixed an issue where writing `sdt` incorrectly cleared `sie` when `menvcfg.DTE` was disabled ([#4064](https://github.com/OpenXiangShan/XiangShan/pull/4064)).
    - Fixed errors in calculating the trap PC for certain interrupts processed in VS mode ([#4054](https://github.com/OpenXiangShan/XiangShan/pull/4054)).
    - Fixed FS/VS dirty synchronization logic in NEMU ([#720](https://github.com/OpenXiangShan/NEMU/pull/720)).
    - Fixed a series of issues related to LCOFI interrupts in NEMU ([#733](https://github.com/OpenXiangShan/NEMU/pull/733), [#729](https://github.com/OpenXiangShan/NEMU/pull/729)).

- **Area Optimization**
    - Backend area has been reduced by 25%.
    - Encoded `exuOH` in IQ as `UInt` type to reduce storage space ([#4033](https://github.com/OpenXiangShan/XiangShan/pull/4033)).
    - Fixed the large area issue in VFMA/FMA ([#4069](https://github.com/OpenXiangShan/XiangShan/pull/4069)).
    - Added an optional parameter to functional units for controlling the copying of source operands ([#4063](https://github.com/OpenXiangShan/XiangShan/pull/4063)).
    - Incorporated previously completed PPA optimization points, including new dispatch logic, new TargeMem, and reducing four scalar floating-point units to three ([#4049](https://github.com/OpenXiangShan/XiangShan/pull/4049)).

- **Timing Optimization**
    - Modified `rob` selection logic to accurately select from dequeue groups ([#4067](https://github.com/OpenXiangShan/XiangShan/pull/4067)).
    - Updated the complex vector decoder to output 6 `uop` per cycle in order ([#4025](https://github.com/OpenXiangShan/XiangShan/pull/4025)).
    - Added `newestTarget` bypass to store one copy instead of one for each read port ([#4049](https://github.com/OpenXiangShan/XiangShan/pull/4049)).

- **RVA23 Profile**
    - Trace extension has been merged into the XiangShan master ([#3843](https://github.com/OpenXiangShan/XiangShan/pull/3843)).

### MemBlock and cache

- **CHI Bus**
  - Improve the concurrency of the CHI-AXI bridge ([#4008](https://github.com/OpenXiangShan/XiangShan/pull/4008))

- **RVA23 Profile**
  - CMO: Add a test environment for `cbo.inval` instruction on `tl-test-new`, with dual-core testing ([tl-test-new #45](https://github.com/OpenXiangShan/tl-test-new/pull/45))

- **Bug fixes**

- **PPA Optimizations**
  - **Timing**: Optimize critical path in StoreQueue ([#3988](https://github.com/OpenXiangShan/XiangShan/pull/3988))
  - **Area**: Remove redundant registers in VirtualLoadQueue ([#4061](https://github.com/OpenXiangShan/XiangShan/pull/4061)); Remove redundant CacheOpDecoder in DCache ([#4050](https://github.com/OpenXiangShan/XiangShan/pull/4050))
  - **Power Consumption**: Trim LSQ and optimize MemBlock power consumption ([#4059](https://github.com/OpenXiangShan/XiangShan/pull/4059)); Single-core shutdown for smoke testing

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

Reviewer: XiangShan Publicity Team
