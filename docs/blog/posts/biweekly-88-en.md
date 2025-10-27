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
  - Remove identifiedCfi ([#5025](https://github.com/OpenXiangShan/XiangShan/pull/5025))
  - Merge V3 SC skeleton ([#5062](https://github.com/OpenXiangShan/XiangShan/pull/5062), [#5097](https://github.com/OpenXiangShan/XiangShan/pull/5097))
  - Support WriteBuffer multi-port write ([#5081](https://github.com/OpenXiangShan/XiangShan/pull/5081))
  - Optimize V3 ITTAGE, use WriteBuffer, support resolve training ([#5099](https://github.com/OpenXiangShan/XiangShan/pull/5099))
- Bug Fix
  - Fix the issue of cfiPosition field when BPU fallthrough prediction ([#5058](https://github.com/OpenXiangShan/XiangShan/pull/5058))
  - Fix several typos in TAGE ([#5086](https://github.com/OpenXiangShan/XiangShan/pull/5086), [#5090](https://github.com/OpenXiangShan/XiangShan/pull/5090))
  - Fix several typos in MBTB ([#5096](https://github.com/OpenXiangShan/XiangShan/pull/5096))
  - Fix the issue of meta SRAM read-write conflict caused by FTQ resolve queue not being flushed by redirect ([#5085](https://github.com/OpenXiangShan/XiangShan/pull/5085), [#5104](https://github.com/OpenXiangShan/XiangShan/pull/5104))
  - Remove newest target logic in FTQ-backend interface ([#5101](https://github.com/OpenXiangShan/XiangShan/pull/5101))
  - Fix the issue of ICache WayLookup read-write conflict assertion condition ([#5082](https://github.com/OpenXiangShan/XiangShan/pull/5082))
  - Fix the issue that Direct branches are corrected by IFU, causing the backend failed to mark as mispredicted and BPU cannot be trained ([#5103](https://github.com/OpenXiangShan/XiangShan/pull/5103))
- Code quality improvements
  - Refactor BPU first taken branch selection logic, using CompareMatrix class ([#5075](https://github.com/OpenXiangShan/XiangShan/pull/5075))
  - Fix the issue that FTQ resolve queue branch index calculation starts from 1 ([#5092](https://github.com/OpenXiangShan/XiangShan/pull/5092))
  - Refactor IFU MMIO fetch handling logic ([#5021](https://github.com/OpenXiangShan/XiangShan/pull/5021))
  - Refactor IFU redirect port, moving arbitration logic from FTQ to IFU ([#5064](https://github.com/OpenXiangShan/XiangShan/pull/5064))
- Debugging tools
  - Add BpTrace and related analysis scripts ([#5091](https://github.com/OpenXiangShan/XiangShan/pull/5091))

### Backend

- Bug Fix
  - Fix the issue when ROB compress close, fusion which cross two ftq cannot be compressed ([#5079](https://github.com/OpenXiangShan/XiangShan/pull/5079))
- RTL new features
  - Optimize the timing of vialuf in NewMgu
- Code quality improvements
  - Add jalr/jal/auipc implementation to ALU ([#5078](https://github.com/OpenXiangShan/XiangShan/pull/5078))

### MemBlock and Cache

- Bug Fix
  - （V2）Fix incorrect TLB level refill during exceptions, which caused large pages to be recorded as small pages（[#5087](https://github.com/OpenXiangShan/XiangShan/pull/5087)）
  - （V2）fix bitmap check result wakeup l0BitmapReg logic（[#5073](https://github.com/OpenXiangShan/XiangShan/pull/5073)）
  - Move NEMU's PMEMBASE to higher address to prevent conflicts with mmap mappings that use the MAP_FIXED mode. Future work may further eliminate the dependency on MAP_FIXED（[NEMU #930](https://github.com/OpenXiangShan/NEMU/pull/930)）
- Timing optimization
  - Split the data SRAM of CoupledL2 into 4 parts to meet the new physical design backend requirements  ([CoupledL2 #432](https://github.com/OpenXiangShan/CoupledL2/pull/432))
  - The timing fix of old MMU, LoadQueueReplay, etc. is on going
- RTL new features
  - The refactoring of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
  - L1 Acquire gets the way information to save the cost of reading the directory to obtain the number of way during Release. Fixing bugs

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
