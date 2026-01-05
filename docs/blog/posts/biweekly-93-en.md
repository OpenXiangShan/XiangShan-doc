---
slug: biweekly-93-en
date: 2026-01-05
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 93] 20260105

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan.

This is the 93rd issue of the biweekly report.

In the last issue of the biweekly report in 2025, we are excited to announce the performance evaluation results of the current Kunminghu V3 architecture on SPEC CPU2006 for the first time! Since the performance regression of Kunminghu V3 started in August this year, a total of 11 performance regressions have been completed. These 11 performance regressions witness the process of the XiangShan team working together to rapidly develop and iterate on the design. The initial version of Kunminghu V3 scored only 3.717 points/GHz in the SPEC 2006 test. Now, in the latest performance regression, V3 has reached 16.081 points/GHz, surpassing the score of V2. V3 has also replaced V2 as the new mainline of the XiangShan repository!

![Performance Regression Results for XiangShan Kunminghu](./figs/performance-regression.png)

During this process, ~~the frontend undoubtedly took the biggest blame~~ the most significant change is the brand-new frontend of V3. The new frontend has greatly improved instruction bandwidth, now capable of predicting up to 8 branches and providing 32 instructions per cycle. Meanwhile, the backend and memory subsystem have also increased their throughput capabilities, including increasing from 6 to 8 issue ports and adjusting the sizes of various queues.

It is worth noting that the performance data curve of V3 vividly reflects the agile development philosophy of the XiangShan team. Unlike traditional waterfall development processes, the development of V3 is not a one-time delivery of all code, but rather a result of rapid iteration and continuous evolution based on the initial code. We believe that this new philosophy will bring a new development paradigm to the industry and will certainly help Kunminghu V3 reach new heights, further enhancing the performance benchmark of open-source processors.

We appreciate your companionship and support for XiangShan, and we look forward to your continued attention to the subsequent progress of Kunminghu V3!

In terms of XiangShan development, the frontend has fixed some BPU-related performance bugs and added numerous performance counters for better performance analysis. The backend continues to advance the design of the new vector unit. The memory subsystem has fixed several bugs in V2 and is continuing with V3 module refactoring and infrastructure construction.

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Implement MBTB replacer to only touch branches with taken prediction, allowing useless branches to be replaced from MBTB first ([#5414](https://github.com/OpenXiangShan/XiangShan/pull/5414))
  - Implement banked ITTAGE SRAM to reduce read-write conflicts ([#5430](https://github.com/OpenXiangShan/XiangShan/pull/5430))
  - Implement TAGE to store provider information into metaQueue to reduce reads during updates, thereby reducing read-write conflicts ([#5400](https://github.com/OpenXiangShan/XiangShan/pull/5400))
- Bug Fix
  - Fix issue of incorrect read-write conflict conditions in ITTAGE SRAM ([#5392](https://github.com/OpenXiangShan/XiangShan/pull/5392))
  - Fix issue of other predictors being trained repeatedly when TAGE training is blocked ([#5399](https://github.com/OpenXiangShan/XiangShan/pull/5399))
- Timing/Area optimization
  - Fix timing issues of WriteBuffer write ports in MBTB and TAGE ([#5418](https://github.com/OpenXiangShan/XiangShan/pull/5418), [#5433](https://github.com/OpenXiangShan/XiangShan/pull/5433))
  - Fix timing issues caused by large bit-width and poor selection of ABTB SRAM ([#5417](https://github.com/OpenXiangShan/XiangShan/pull/5417))
- Code quality improvements
  - Rewrite parts of the Frontend top-level module that do not conform to the style guide and fix IDE warnings ([#5395](https://github.com/OpenXiangShan/XiangShan/pull/5395))
  - Rewrite index selection logic of ABTB and UBTB using AddrField class ([#5397](https://github.com/OpenXiangShan/XiangShan/pull/5397))
  - Clean up unused code in ABTB ([#5456](https://github.com/OpenXiangShan/XiangShan/pull/5456))
- Debugging tools
  - Add MicroTAGE Trace ([#5388](https://github.com/OpenXiangShan/XiangShan/pull/5388))
  - Add ICache Trace ([#5452](https://github.com/OpenXiangShan/XiangShan/pull/5452))
  - Add numerous performance counters ([#5442](https://github.com/OpenXiangShan/XiangShan/pull/5442), [#5443](https://github.com/OpenXiangShan/XiangShan/pull/5443), [#5289](https://github.com/OpenXiangShan/XiangShan/pull/5289))

### Backend

- RTL new features
  - implementating the new design of V3 vector unit
- Bug fixes
  - Fix backend TopDown interface connection issues ([#5340](https://github.com/OpenXiangShan/XiangShan/pull/5340))
  - Modify the value of mvendorid ([#5367](https://github.com/OpenXiangShan/XiangShan/pull/5367))
  - Fix Dispatch pipeline stall cycle counting issue ([#5398](https://github.com/OpenXiangShan/XiangShan/pull/5398))
- Code optimizations
  - Make the connection of srcLoadDependencyUpdate more readable ([#5404](https://
- Others
  - Update the list of backend code owners ([#5342](https://github.com/OpenXiangShan/XiangShan/pull/5342))

- RTL new features
  - Advancing the new design implementation of the V3 vector unit
  - (V3) Modify the value of mvendorid ([#5427](https://github.com/OpenXiangShan/XiangShan/pull/5427))
  - (V3) Refactor the vimac64b module, implement the vimac gold model, and add corresponding interfaces to VecSimTop ([YunSuan #193](https://github.com/OpenXiangShan/YunSuan/pull/193))
- Bug fixes
  - (V3) Fix RAS action issue during commit ([#5421](https://github.com/OpenXiangShan/XiangShan/pull/5421))
  - (V2/V3) Fix priority issue causing illegal instruction exception when reading vl/vlenb in CSR read instructions ([#5420](https://github.com/OpenXiangShan/XiangShan/pull/5420), [#5422](https://github.com/OpenXiangShan/XiangShan/pull/5422))
  - (V3) Use basicDebugEn signal in diffVl debug interface ([#5465](https://github.com/OpenXiangShan/XiangShan/pull/5465))
  - (V2) Upgrade NEMU config to fix vfredusum issue ([#5434](https://github.com/OpenXiangShan/XiangShan/pull/5434))
- Timing
  - (V3) Reduce one-cycle delay in redirect ([#5378](https://github.com/OpenXiangShan/XiangShan/pull/5378))
  - (V3) Move the selection of oldestExuRedirect from ctrlblock to intRegion ([#5462](https://github.com/OpenXiangShan/XiangShan/pull/5462))
  - (V3) Separate targetPc into trap and xret paths to optimize timing, handling exceptions and CSR FunctionUnit writebacks respectively ([#5475](https://github.com/OpenXiangShan/XiangShan/pull/5475))
- Code optimizations
  - (V3) Remove some dead code ([#5405](https://github.com/OpenXiangShan/XiangShan/pull/5405), [#5324](https://github.com/OpenXiangShan/XiangShan/pull/5324))
  - (V3) Remove some code connecting with 0.U width ([#5413](https://github.com/OpenXiangShan/XiangShan/pull/5413))
  - (V3) Switch to using CSRs.scala file to keep track of CSR addresses ([#5440](https://github.com/OpenXiangShan/XiangShan/pull/5440))
  - (V3) Configure vl src separately in each parameter class in backend for easier maintenance ([#5368](https://github.com/OpenXiangShan/XiangShan/pull/5368))
- Others

### MemBlock and Cache

- RTL new features
  - The refactoring and testing of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - Modify the pipe parameter of Pipeline to true in PerfetcgWrapper ([#5275](https://github.com/OpenXiangShan/XiangShan/pull/5275/files))
  - Fix the error of multi-writeback when storeMisalignBuffer is full ([#5415](https://github.com/OpenXiangShan/XiangShan/pull/5415))
  - Remove redundant BEU range exclusion in L2 ([CoupledL2 #457](https://github.com/OpenXiangShan/CoupledL2/pull/457))
  - Sync the pr in V2 to V3
- Code refactoring
  - Remove fdpMonitor and fix some statistics bugs ([#5272](https://github.com/OpenXiangShan/XiangShan/pull/5272))
- Debugging tools
  - Continuous improvement of CHI infrastructure CHIron
  - Develop a verification tool CHI Test for the new version of L2 Cache. Continuous progressing

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 36.71  | 410.bwaves       | 73.92  |
| 401.bzip2         | 27.45  | 416.gamess       | 54.70  |
| 403.gcc           | 42.71  | 433.milc         | 45.12  |
| 429.mcf           | 59.65  | 434.zeusmp       | 60.17  |
| 445.gobmk         | 35.10  | 435.gromacs      | 38.47  |
| 456.hmmer         | 44.18  | 436.cactusADM    | 54.20  |
| 458.sjeng         | 32.30  | 437.leslie3d     | 52.85  |
| 462.libquantum    | 107.84 | 444.namd         | 37.91  |
| 464.h264ref       | 61.89  | 447.dealII       | 61.38  |
| 471.omnetpp       | 43.56  | 450.soplex       | 54.62  |
| 473.astar         | 30.43  | 453.povray       | 56.90  |
| 483.xalancbmk     | 75.89  | 454.Calculix     | 19.18  |
| GEOMEAN           | 45.85  | 459.GemsFDTD     | 44.14  |
|                   |        | 465.tonto        | 36.35  |
|                   |        | 470.lbm          | 93.88  |
|                   |        | 481.wrf          | 48.77  |
|                   |        | 482.sphinx3      | 56.20  |
|                   |        | GEOMEAN          | 49.72  |

We use SimPoint to sample programs and create checkpoints images based on our custom format. The coverage of SimPoint clustering reaches 100%. Note that the above scores are estimated based on program segments rather than a complete SPEC CPU2006 evaluation, which may deviate from the actual performance of real chips.

Compilation parameters are as follows:

|                    |          |
| ------------------ | -------- |
| Compiler           | gcc12    |
| Optimization level | O3       |
| Memory library     | jemalloc |
| -march             | RV64GCB  |
| -ffp-contraction   | fast     |

Processor and SoC parameters are as follows:

|                |            |
| -------------- | ---------- |
| Commit         | 64e7bff7f  |
| Date           | 12/19/2025 |
| L1 ICache      | 64KB       |
| L1 DCache      | 64KB       |
| L2 Cache       | 1MB        |
| L3 Cache       | 16MB       |
| LSU            | 3ld2st     |
| Bus protocol   | TileLink   |
| Memory latency | DDR4-3200  |

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
