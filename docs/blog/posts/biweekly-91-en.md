---
slug: biweekly-91-en
date: 2025-12-08
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 91] 20251208

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 91st issue of the biweekly report.

In terms of XiangShan development, the frontend has implemented some new performance features in V3, while fixing multiple performance bugs caused by BPU refactoring~~hoping that the performance can reach the pre-refactoring level (x2) by the next biweekly report~~. The backend is advancing the design of the new vector unit in V3, while fixing some legacy bugs in V2. The MemBlock has added the berti prefetcher, while continuing to promote code refactoring in various modules and fixing some V2 functional bugs.

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Implement UTAGE predictor as the direction predictor of the S1 predictor group, providing more accurate direction prediction than UBTB and ABTB ([#5194](https://github.com/OpenXiangShan/XiangShan/pull/5194))
  - Support comparison of branch positions predicted by UBTB and ABTB, selecting the prior prediction result ([#5243](https://github.com/OpenXiangShan/XiangShan/pull/5243))
  - Support MBTB not training fallThrough type branches to reduce capacity waste ([#5245](https://github.com/OpenXiangShan/XiangShan/pull/5245))
  - Support MBTB correcting indirect type branch targets ([#5226](https://github.com/OpenXiangShan/XiangShan/pull/5226))
  - Modify MBTB replacer setIdx selection position ([#5260](https://github.com/OpenXiangShan/XiangShan/pull/5260))
  - Align TAGE parameters with GEM5 ([#5261](https://github.com/OpenXiangShan/XiangShan/pull/5261))
  - Modify TAGE setIdx and bankIdx selection positions ([#5294](https://github.com/OpenXiangShan/XiangShan/pull/5294))
  - Modify PHR Shamt parameter ([#5315](https://github.com/OpenXiangShan/XiangShan/pull/5315))
  - Support updating RAS through the commit path ([#5196](https://github.com/OpenXiangShan/XiangShan/pull/5196))
- Bug Fix
  - Fix ABTB counter update logic ([#5266](https://github.com/OpenXiangShan/XiangShan/pull/5266))
  - Fix MBTB internalBank write/write conflict issue ([#5255](https://github.com/OpenXiangShan/XiangShan/pull/5255))
  - Fix MBTB replacer update logic error issue ([#5302](https://github.com/OpenXiangShan/XiangShan/pull/5302))
  - Fix TAGE counter initial value ([#5252](https://github.com/OpenXiangShan/XiangShan/pull/5252))
  - Fix TAGE allocation logic ([#5254](https://github.com/OpenXiangShan/XiangShan/pull/5254))
  - Fix ITTAGE training data misaligned issue ([#5244](https://github.com/OpenXiangShan/XiangShan/pull/5244))
  - Fix FTQ ResolveQueue flush conflicts between BPU and Redirect ([#5273](https://github.com/OpenXiangShan/XiangShan/pull/5273))
  - Fix SRAMTemplate compile-time warning ([#5276](https://github.com/OpenXiangShan/XiangShan/pull/5276))
- Timing/Area optimization
  - (V2) Register iPMP read results to fix timing issues after increasing PMP entries ([#5242](https://github.com/OpenXiangShan/XiangShan/pull/5242))
- Code quality improvements
  - Remove redundant parameters in UBTB ([#5262](https://github.com/OpenXiangShan/XiangShan/pull/5262))
  - Refactor ICache Meta/DataArray to fix incomplete parameterization support ([#5232](https://github.com/OpenXiangShan/XiangShan/pull/5232))
  - Add AddrField tool to simplify address-related index calculation logic, increase compile-time logs for easier debugging, and fix some typos in TAGE ([#5274](https://github.com/OpenXiangShan/XiangShan/pull/5274), [#5295](https://github.com/OpenXiangShan/XiangShan/pull/5295), [#5306](https://github.com/OpenXiangShan/XiangShan/pull/5306))
- Debugging tools
  - Fix TAGE condTrace tool parameter usage error issue ([#5251](https://github.com/OpenXiangShan/XiangShan/pull/5251))
  - Reduce redundant output of TAGE condTrace tool ([#5247](https://github.com/OpenXiangShan/XiangShan/pull/5247))
  - Add performance counters related to TAGE bank conflicts ([#5303](https://github.com/OpenXiangShan/XiangShan/pull/5303))
  - Add nameSuffix parameter to WriteBuffer to improve debug information readability ([#5277](https://github.com/OpenXiangShan/XiangShan/pull/5277), [#5310](https://github.com/OpenXiangShan/XiangShan/pull/5310))
  - Fix typo in predictionSource performance counter register enable signal ([#5271](https://github.com/OpenXiangShan/XiangShan/pull/5271))
  - Add FTQ PerfQueue for branch prediction performance analysis ([#5304](https://github.com/OpenXiangShan/XiangShan/pull/5304))

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
