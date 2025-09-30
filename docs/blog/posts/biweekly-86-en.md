---
slug: biweekly-86-en
date: 2025-09-29
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 86] 20250929

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 85th issue of the biweekly report.

In this biweekly report, we are excited to announce the release of the XiangShan Compiler Collection (XSCC). Built on the LLVM framework, XSCC is a high-performance compiler optimized for open-source high-performance RISC-V processor XiangShan. It focuses on microarchitecture-level performance enhancement strategies such as memory access optimization, branch prediction improvement, loop unrolling, and automatic vectorization. Currently, XSCC 1.0 is developed based on LLVM 19.1.0.

This release is the XSCC v1.0 binary distribution package, providing a cross-compiler for RISC-V (generating riscv64 target code). It can run on hosts with Ubuntu 22.04 or above (x86_64), with glibc as the default C standard library. The distribution package can be downloaded from the GitHub Releases page: <https://github.com/OpenXiangShan/xscc/releases>.

From this issue onwards, we will include performance data of SPEC 2006 compiled with XSCC for your reference.

In the past two weeks, the V3 frontend refactoring is nearly complete, with each BPU adapted to the new frontend framework, and corresponding modifications made to the backend. The memory access and cache team mainly fixed some bugs in V2 while developing new tools.

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Optimize BPU training mechanism by training the first mispredicted branch in a resolve entry, drop subsequent branches ([#5023](https://github.com/OpenXiangShan/XiangShan/pull/5023), [#5037](https://github.com/OpenXiangShan/XiangShan/pull/5037), [#5041](https://github.com/OpenXiangShan/XiangShan/pull/5041))
  - Support training s1 fast predictor with results from s3 accurate predictor, not enabled yet as accurate predictor is not ready ([#4970](https://github.com/OpenXiangShan/XiangShan/pull/4970))
  - Increase abtb ways to 8, consistent with mbtb default configuration ([#5042](https://github.com/OpenXiangShan/XiangShan/pull/5042))
  - Merge TAGE, not enabled yet due to some issues with override mechanism ([#5001](https://github.com/OpenXiangShan/XiangShan/pull/5001))
  - Support multi-way write in TAGE WriteBuffer ([#5044](https://github.com/OpenXiangShan/XiangShan/pull/5044))
  - Increase number of branches stored in a resolve entry to 8 ([#5050](https://github.com/OpenXiangShan/XiangShan/pull/5050))
  - Support 64B fetch ([#5014](https://github.com/OpenXiangShan/XiangShan/pull/5014))
  - Remove ICache MainPipe s2 stage to simplify design and prepare for future features ([#5053](https://github.com/OpenXiangShan/XiangShan/pull/5053))
  - Relax IBuffer enqueue conditions to reduce stalls ([#5036](https://github.com/OpenXiangShan/XiangShan/pull/5036))
- Bug fix
  - Fix abtb X-propagation issue ([#5028](https://github.com/OpenXiangShan/XiangShan/pull/5028))
  - Fix issue that mbtb predicting cross-page fetch blocks, V3 ICache/IFU removed support for cross-page fetch, BPU needs to ensure no cross-page prediction ([#5060](https://github.com/OpenXiangShan/XiangShan/pull/5060))
  - Fix TAGE X-propagation issue ([#5043](https://github.com/OpenXiangShan/XiangShan/pull/5043))
  - Fix issue that V2 RAS integration with V3 FTQ not handling IFU redirect, and rasAction in backend redirect not being correctly assigned ([#5040](https://github.com/OpenXiangShan/XiangShan/pull/5040))
  - Fix Ftq backendException write condition fault ([#5016](https://github.com/OpenXiangShan/XiangShan/pull/5016), [#5035](https://github.com/OpenXiangShan/XiangShan/pull/5035))
  - Fix IFU instruction offset calculation error ([#5012](https://github.com/OpenXiangShan/XiangShan/pull/5012))
  - Fix IFU s1 stage flush condition error, fix issue that ICache WayLookup and MainPipe s1 stage not being flushed by BPU s3 override ([#5054](https://github.com/OpenXiangShan/XiangShan/pull/5054), [#5055](https://github.com/OpenXiangShan/XiangShan/pull/5055), [#5072](https://github.com/OpenXiangShan/XiangShan/pull/5072))
- Model exploration
  - Organize TAGE PHR related commits, performance improved ([GEM5 #524](https://github.com/OpenXiangShan/GEM5/pull/524))
  - Adjust SC implementable solution to adapt to updateThreshold and weight Table
- Code quality
  - Refactor BPU S3 prediction generation logic by moving takenMask generation from TAGE to BPU top level for clearer module functionality division ([#5045](https://github.com/OpenXiangShan/XiangShan/pull/5045))
  - Refactor IFU instruction boundary calculation logic ([#5012](https://github.com/OpenXiangShan/XiangShan/pull/5012))

### Backend

- Bug Fix
  - Backend should provide start pc of the FTQ entry.（[#5017](https://github.com/OpenXiangShan/XiangShan/pull/5017)）
  - Fix isRVC transfer logic for new ftqoffset （[#5003](https://github.com/OpenXiangShan/XiangShan/pull/5003)）

### MemBlock and Cache

- Bug Fix
  - Fix the issue in FDP where the counter filter capacity is insufficient and needs to be increased by 1 ([#5030](https://github.com/OpenXiangShan/XiangShan/pull/5030))
  - Fix the issue that LoadUnit did not re-access data during fast replay was performed to avoid memory consistency issues  ([#4965](https://github.com/OpenXiangShan/XiangShan/pull/4965))
- Timing optimization
  - Split the data SRAM of CoupledL2 into 4 parts to meet the new physical design backend requirements  ([CoupledL2 #432](https://github.com/OpenXiangShan/CoupledL2/pull/432))
  - Old MMU timing fixes is on going
  - Analyze the timing of LoadQueueReplay in previous versions to find the timing degradation point
- RTL new features
  - The refactoring of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
  - L1 Acquire gets the way information to save the cost of reading the directory to obtain the number of way during Release. Fixing bugs

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.90  | 433.milc         | 50.44  |
| 429.mcf           | 60.18  | 434.zeusmp       | 51.83  |
| 445.gobmk         | 30.63  | 435.gromacs      | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.87  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.77  |
| 471.omnetpp       | 41.50  | 450.soplex       | 52.48  |
| 473.astar         | 29.30  | 453.povray       | 53.49  |
| 483.xalancbmk     | 72.79  | 454.Calculix     | 16.38  |
| GEOMEAN           | 44.67  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 49.13  |
|                   |        | GEOMEAN          | 45.26  |

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
| Commit         | 324b389    |
| Date           | 09/25/2025 |
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
