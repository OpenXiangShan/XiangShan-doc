---
slug: biweekly-94-en
date: 2026-01-19
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 94] 20260119

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 94th issue of the biweekly report.

This is the first issue of the biweekly report in 2026! In the past year of 2025, the XiangShan team has made solid progress and achieved multiple important milestones with high quality:

- First industrial application. The second-generation XiangShan Nanhu has been integrated as the main control CPU into the latest generation chips by Moore Threads and Chipown Technology, with Moore Threads shipping tens of thousands of units; the third-generation XiangShan Kunminghu has completed product-level delivery for the first batch of SoC chips, with two companies completing SoC chip tape-out in October and November respectively, and will have tape-in in Q1 2026.
- Won the first Open Source Contribution Award from the CCF Architecture Committee of the China Computer Federation
- The "XiangShan" open-source processor core was selected as one of the representative scientific research achievements of the Chinese Academy of Sciences in 2025 and was included in the New Year message of CAS President Hou Jianguo
- Presented tutorials at top conferences such as ISCA, HPCA, MICRO, introducing the latest progress of XiangShan to the world
- Multiple tools have been developed and papers published at top international conferences, such as GSIM (DAC25), DiffTest-H (MICRO25), TraceRTL (HPCA26), UCAgent, etc.
- Several papers based on XiangShan evaluations have been published in top international conferences
- Verification work has been continuously improved, successfully passing multiple milestone tests such as 8-core consistency verification and booting GUI OpenEuler
- Kunminghu V3 became the new default branch, with the latest performance surpassing Kunminghu V2
- Hosted community events such as RISC-V Hackathon and Documentation Bug Hunt, and had enthusiastic exchanges with friends around the world who care about the progress of XiangShan at the second XiangShan Open Source Community Conference
- XiangShan Compiler (XSCC) released, XiangShan now has its own compiler
- The AI intelligent agent UCAgent from the "One Chip for All" team was released, successfully hosting the first open-source chip hackathon

A new year means a new beginning. In 2026, XiangShan will continue to implement the new concept of "open source", continuously promote the iterative development of Kunminghu V3 and the construction of the open source community. We sincerely thank everyone for their companionship and support for XiangShan!

In terms of XiangShan development, the new front-end of 1-taken and 1-fetch has been basically completed; the back-end continues to advance the design and implementation of the new vector unit while refactoring existing code; the memory system continues to refactor modules such as MMU, LoadUnit, StoreQueue, L2, and fixes some bugs.

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Improve bias and path table of SC predictor ([#5458](https://github.com/OpenXiangShan/XiangShan/pull/5458))
  - Use the counter accumulation mechanism of WriteBuffer in TAGE ([#5470](https://github.com/OpenXiangShan/XiangShan/pull/5470))
  - Store set and bank index of ABTB into metadata, remove extra s4-level pc saved at the top level of BPU ([#5494](https://github.com/OpenXiangShan/XiangShan/pull/5494))
  - Support enabling/disabling auto re-fetch on ICache parity error ([#5501](https://github.com/OpenXiangShan/XiangShan/pull/5501))
- Bug Fix
  - Fix a typo in MBTB replacer ([#5540](https://github.com/OpenXiangShan/XiangShan/pull/5540))
  - Fix the condition for TAGE to update using metadata ([#5461](https://github.com/OpenXiangShan/XiangShan/pull/5461))
  - Fix the issue of GHR losing updates when FTQ is stalled ([#5469](https://github.com/OpenXiangShan/XiangShan/pull/5469))
  - Fix the issue of RAS incorrectly updating metadata when FTQ is stalled ([#5481](https://github.com/OpenXiangShan/XiangShan/pull/5481))
  - Fix the replacement selection logic of WriteBuffer when setIdx hits ([#5526](https://github.com/OpenXiangShan/XiangShan/pull/5526))
  - Fix the issue of IFU speculative fetch in MMIO space ([#5459](https://github.com/OpenXiangShan/XiangShan/pull/5459))
- Timing/Area optimization
  - Disable the auto re-fetch mechanism on ICache parity error to optimize timing ([#5501](https://github.com/OpenXiangShan/XiangShan/pull/5501))
- Code quality improvements
  - Refactor SaturateCounter utility class ([#5363](https://github.com/OpenXiangShan/XiangShan/pull/5363))
  - Refactor BPU metadata classes ([#5486](https://github.com/OpenXiangShan/XiangShan/pull/5486))
  - Decouple ABTB and UTAGE ([#5500](https://github.com/OpenXiangShan/XiangShan/pull/5500))
- Debugging tools
  - Add MBTB trace ([#5466](https://github.com/OpenXiangShan/XiangShan/pull/5466))

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
  - The refactoring and testing of MDP, MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - (v2) Fix the missing wire connections for lqIdx and sqIdx in the exception buffer enqueue logic ([#5512](https://github.com/OpenXiangShan/XiangShan/pull/5512))
  - (V2) Fix missing consideration of SnpPreferUniqueFwd in SnpXFwd logic ([CoupledL2 #460](https://github.com/OpenXiangShan/CoupledL2/pull/460))
  - (V2) Fix l2Error_s3 generation logic in MainPipe ([CoupledL2 #463](https://github.com/OpenXiangShan/CoupledL2/pull/463))
- Debugging tools
  - Continuous improvement of CHI infrastructure CHIron
  - Develop a verification tool CHI Test for the new version of L2 Cache. Continuous progressing

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 38.38  | 410.bwaves       | 73.28  |
| 401.bzip2         | 27.53  | 416.gamess       | 55.10  |
| 403.gcc           | 48.17  | 433.milc         | 46.08  |
| 429.mcf           | 60.25  | 434.zeusmp       | 60.34  |
| 445.gobmk         | 37.30  | 435.gromacs      | 38.58  |
| 456.hmmer         | 44.20  | 436.cactusADM    | 54.30  |
| 458.sjeng         | 34.49  | 437.leslie3d     | 53.87  |
| 462.libquantum    | 127.76 | 444.namd         | 38.02  |
| 464.h264ref       | 63.36  | 447.dealII       | 62.95  |
| 471.omnetpp       | 43.19  | 450.soplex       | 54.69  |
| 473.astar         | 30.68  | 453.povray       | 61.24  |
| 483.xalancbmk     | 81.47  | 454.Calculix     | 19.40  |
| GEOMEAN           | 48.07  | 459.GemsFDTD     | 44.60  |
|                   |        | 465.tonto        | 36.34  |
|                   |        | 470.lbm          | 104.91 |
|                   |        | 481.wrf          | 48.88  |
|                   |        | 482.sphinx3      | 56.16  |
|                   |        | GEOMEAN          | 50.55  |

Compilation parameters are as follows:

| Parameters         | Options  |
| ------------------ | -------- |
| Compiler           | gcc12    |
| Optimization level | O3       |
| Memory library     | jemalloc |
| -march             | RV64GCB  |
| -ffp-contraction   | fast     |

Processor and SoC parameters are as follows:

| Parameters     | Options    |
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

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
