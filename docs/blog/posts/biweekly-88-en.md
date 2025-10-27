---
slug: biweekly-88-en
date: 2025-10-27
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 88] 20251027

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 88th issue of the biweekly report.

In the past two weeks, ~~the XiangShan Team had a great National Day Holiday~~the frontend team continued to fix performance bugs caused by the V3 BPU refactoring. The backend team organized existing code and continued to promote V3 development. The memory and cache team fixed several V2 bugs while conducting code refactoring work to prepare for V3 development.

We also have an announcement to make: the XiangShan Team will be giving a tutorial at the MICRO 2025 conference on October 19th. We are very much looking forward to seeing everyone in Seoul!

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Enable override mechanism of s3 accurate predictor group in V3 BPU (only BaseTable is enabled for TAGE, RAS is not enabled) ([#5057](https://github.com/OpenXiangShan/XiangShan/pull/5057))
  - Add 2-fetch interface support for IBuffer ([#5098](https://github.com/OpenXiangShan/XiangShan/pull/5098))
  - Rewrite ABTB fast training interface ([#5070](https://github.com/OpenXiangShan/XiangShan/pull/5070))
- Bug Fix
  - Fix the issue of MBTB misfiltering branches at the beginning of the fetch block ([#5113](https://github.com/OpenXiangShan/XiangShan/pull/5113))
  - Fix SC training logic related issues ([#5118](https://github.com/OpenXiangShan/XiangShan/pull/5118))
  - Fix RAS stack size parameter calculation related issues ([#5132](https://github.com/OpenXiangShan/XiangShan/pull/5132))
  - Fix WriteBuffer write index typo ([#5134](https://github.com/OpenXiangShan/XiangShan/pull/5134))
  - Fix the issue where invalid entries in the FTQ resolve queue are marked as flushed, causing BPU training loss ([#5107](https://github.com/OpenXiangShan/XiangShan/pull/5107))
  - Fix assertion condition error in IFU ([#5122](https://github.com/OpenXiangShan/XiangShan/pull/5122))
- Timing optimization
  - (V2) Replace the dual-port SRAM of TageBTable and SCTable with single-port SRAM ([#5094](https://github.com/OpenXiangShan/XiangShan/pull/5094))
  - Modify instruction boundary calculation logic, changing from calculating after IFU fetches instruction data to pre-calculating during ICache refill; shorten IFU pipeline stage ([#5108](https://github.com/OpenXiangShan/XiangShan/pull/5108))
- Area optimization
  - Support IBuffer to only store the first exception encountered after power-on/redirection ([#5095](https://github.com/OpenXiangShan/XiangShan/pull/5095))
- Code quality improvements
  - Remove V2 brType type, unify to use V3 BranchAttribute ([#5076](https://github.com/OpenXiangShan/XiangShan/pull/5076))
- Debugging tools
  - Add some BPU performance counters ([#5112](https://github.com/OpenXiangShan/XiangShan/pull/5112))

### Backend

- Bug Fix
  - Fix the issue when ROB compress close, fusion which cross two ftq cannot be compressed ([#5079](https://github.com/OpenXiangShan/XiangShan/pull/5079))
- RTL new features
  - Optimize the timing of vialuf in NewMgu
- Code quality improvements
  - Add jalr/jal/auipc implementation to ALU ([#5078](https://github.com/OpenXiangShan/XiangShan/pull/5078))

### MemBlock and Cache

- RTL new features
  - (V2) Add topdown interface for late prefetch in CoupledL2 ([CoupledL2 #411](https://github.com/OpenXiangShan/CoupledL2/pull/411))
  - (V2) Add csr control of delay latency for training L2 prefetch in CoupledL2 ([CoupledL2 #434](https://github.com/OpenXiangShan/CoupledL2/pull/434))
  - (V2) Add Berti prefetch and refactored prefetch related TopDownMonitor([CoupledL2 #435](https://github.com/OpenXiangShan/CoupledL2/pull/435))
  - (V2) Add api for checking L2 prefetch and Berti prefetch ([Utility #128](https://github.com/OpenXiangShan/Utility/pull/128))
  - The refactoring of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Tools
  - Complete the functions of CHIron

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.87  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.87  | 433.milc         | 45.07  |
| 429.mcf           | 60.18  | 434.zeusmp       | 51.83  |
| 445.gobmk         | 30.62  | 435.gromacs      | 33.65  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.87  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.82  |
| 471.omnetpp       | 41.41  | 450.soplex       | 52.48  |
| 473.astar         | 29.30  | 453.povray       | 53.50  |
| 483.xalancbmk     | 72.81  | 454.Calculix     | 16.38  |
| GEOMEAN           | 44.66  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 49.13  |
|                   |        | GEOMEAN          | 44.96  |

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
| Commit         | defcc01    |
| Date           | 10/10/2025 |
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
