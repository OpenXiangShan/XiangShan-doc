---
slug: biweekly-90-en
date: 2025-11-24
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 90] 20251124

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 90th issue of the biweekly report.

In terms of XiangShan development, the frontend has implemented some new performance features in V3, while fixing multiple performance bugs caused by BPU refactoring~~hoping that the performance can reach the pre-refactoring level (x2) by the next biweekly report~~. The backend is advancing the design of the new vector unit in V3, while fixing some legacy bugs in V2. The MemBlock has added the berti prefetcher, while continuing to promote code refactoring in various modules and fixing some V2 functional bugs.

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Support BPU training backpressure Ftq Resolve Queue to avoid training data loss during read-write conflicts ([#5148](https://github.com/OpenXiangShan/XiangShan/pull/5148))
  - Modify PHR hashing logic ([#5209](https://github.com/OpenXiangShan/XiangShan/pull/5209))
- Bug Fix
  - Fix the issue where ABTB output invalidated when pipeline stalled ([#5197](https://github.com/OpenXiangShan/XiangShan/pull/5197))
  - Fix several issues in TAGE table and enable the table ([#5156](https://github.com/OpenXiangShan/XiangShan/pull/5156))
  - Fix assertion fail caused by non-one-hot training index in ITTAGE ([#5184](https://github.com/OpenXiangShan/XiangShan/pull/5184))
  - Fix the issue where FTQ ResolveQueue was not properly flushed upon redirect ([#5149](https://github.com/OpenXiangShan/XiangShan/pull/5149), [#5238](https://github.com/OpenXiangShan/XiangShan/pull/5238))
  - Fix the issue where FTQ ResolveQueue entries stayed too long causing BPU new prediction results to overwrite original FTQ entries, leading to incorrect BPU training ([#5225](https://github.com/OpenXiangShan/XiangShan/pull/5225))
  - Fix the issue of incorrect bit-width of FTQ bpTrainStallCnt ([#5201](https://github.com/OpenXiangShan/XiangShan/pull/5201))
- Timing/Area optimization
  - Remove redundant holdRead parameter in SRAMTemplate of ICache Meta/DataArray, optimizing both timing and area ([#5186](https://github.com/OpenXiangShan/XiangShan/pull/5186))
- Code quality improvements
  - Remove redundant ipmp/itlb ports after removing cross-page instruction fetch support ([#5213](https://github.com/OpenXiangShan/XiangShan/pull/5213))
  - Refactor TAGE BaseTable alignBank, fixing bank index calculation issue in the process ([#5162](https://github.com/OpenXiangShan/XiangShan/pull/5162))
- Debugging tools
  - Add Tage Trace DB ([#5219](https://github.com/OpenXiangShan/XiangShan/pull/5219))
  - Add many performance counters ([#5187](https://github.com/OpenXiangShan/XiangShan/pull/5187))

### Backend

- RTL new features
  - Implementing the new design of V3 vector unit is in progress
  - Adding valid flags for each traceGroup and tracking support for the mstatus register in the top-level debug module ([#5146](https://github.com/OpenXiangShan/XiangShan/pull/5146))
- Bug fixes
  - Fixing issues related to nmi register gating ([#5067](https://github.com/OpenXiangShan/XiangShan/pull/5067)[#5215](https://github.com/OpenXiangShan/XiangShan/pull/5215))
  - Rejecting out-of-order reads of xip-type CSRs ([#5131](https://github.com/OpenXiangShan/XiangShan/pull/5131))
  - Fixing incorrect dependencies on oldVd, ROB compression, and other issues
- Code quality improvements
  - Optimizing the code quality of the V3 backend, removing some redundant code, modifying some code styles, and performing some renaming ([#5135](https://github.com/OpenXiangShan/XiangShan/pull/5135))
- Timing optimization
  - Advancing the evaluation and optimization of vector reduction, Regfile, and other units

### MemBlock and Cache

- RTL new features
  - (V2) Add pmu perfevents for TLB ([#5205](https://github.com/OpenXiangShan/XiangShan/pull/5205))
  - (V2) Add some perfevents in CoupledL2 ([CoupledL2 #437](https://github.com/OpenXiangShan/CoupledL2/pull/437), [CoupledL2 #441](https://github.com/OpenXiangShan/CoupledL2/pull/441))
  - Add berti prefetcher ([#5049](https://github.com/OpenXiangShan/XiangShan/pull/5049))
  - Adjust the interface of issue and writeback in MemBlock ([#5167](https://github.com/OpenXiangShan/XiangShan/pull/5167))
  - The refactoring and testing of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - (V2) Fix the issue where PMM was not disabled when MXR was active ([#4997](https://github.com/OpenXiangShan/XiangShan/pull/4997))
  - (V2) Fix the issue of timing mismatch of corrupt when DCache forwarding ([#5228](https://github.com/OpenXiangShan/XiangShan/pull/5228))
  - (V2) Add enable bit to determine whether checking KeyID ([#5241](https://github.com/OpenXiangShan/XiangShan/pull/5241))
  - (V2) Fix the issue in CoupledL2 where SnpUnique was incorrectly decoded as SnpPreferUnique ([CoupledL2 #438](https://github.com/OpenXiangShan/CoupledL2/pull/438))
  - (V2) Add l-credit manager in CoupledL2 to fix performance ([CoupledL2 #433](https://github.com/OpenXiangShan/CoupledL2/pull/433))
- Timing
  - (V2) Simplify the CMO req in RXSNP in CoupledL2 and pipeline RXSNP and RXDAT ([CoupledL2 #436](https://github.com/OpenXiangShan/CoupledL2/pull/436)) 

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 36.13  | 410.bwaves       | 67.28  |
| 401.bzip2         | 25.39  | 416.gamess       | 40.98  |
| 403.gcc           | 47.97  | 433.milc         | 45.01  |
| 429.mcf           | 60.54  | 434.zeusmp       | 51.85  |
| 445.gobmk         | 30.29  | 435.gromacs      | 33.58  |
| 456.hmmer         | 41.60  | 436.cactusADM    | 46.22  |
| 458.sjeng         | 30.21  | 437.leslie3d     | 48.02  |
| 462.libquantum    | 122.60 | 444.namd         | 28.86  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.54  |
| 471.omnetpp       | 41.73  | 450.soplex       | 52.53  |
| 473.astar         | 29.14  | 453.povray       | 53.41  |
| 483.xalancbmk     | 72.80  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.62  | 459.GemsFDTD     | 38.92  |
|                   |        | 465.tonto        | 36.69  |
|                   |        | 470.lbm          | 91.96  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 49.10  |
|                   |        | GEOMEAN          | 44.90  |

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
| Commit         | d0adbd4    |
| Date           | 11/21/2025 |
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
