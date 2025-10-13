---
slug: biweekly-87-en
date: 2025-10-13
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 87] 202510-13

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 87th issue of the biweekly report.

We are very pleased to share two pieces of news with you.

On September 20, the XiangShan team won the first Open Source Contribution Award from the CCF Architecture Committee. This collective award holds special significance for the XiangShan team—it represents recognition and support from our academic peers for the open-source processor and the team itself, laying the foundation for XiangShan to have a broad impact. The XiangShan team will continue to move forward, step by step, striving to keep XiangShan alive for 30 years!

On September 22, Innosilicon released the "Fenghua 3" full-featured GPU. The "Fenghua 3" GPU successfully integrated the XiangShan "Nanhu" processor IP core, which is performance-competitive with the ARM Cortex-A76, as its high-performance on-chip main control CPU. This integration marks a new phase in the industrial application of open-source high-performance CPU IPs and signifies that RISC-V can carve out a path different from the traditional ARM model.

We believe that open-source chips do not equate to low performance or low quality. Open source will profoundly change the cost structure of chip development, providing a new paradigm for chip design in the industry.

In the past two weeks, the frontend has fixed functional and performance bugs caused by the integration of the new BPU, while continuing performance exploration and tuning. The memory access and cache teams have fixed some bugs and refactored some code to advance the development of V3.

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
  - Fix a branch prediction performance bug by checking the target when both the prediction and the actual execution are taken ([#5027](https://github.com/OpenXiangShan/XiangShan/pull/5027))
  - Fix a bug in the gate logic of the NMI register ([#5067](https://github.com/OpenXiangShan/XiangShan/pull/5067))
  - Fix a bug where errors occurred when fusion instructions followed by branch instructions after disabling ROB compression ([#5074](https://github.com/OpenXiangShan/XiangShan/pull/5074))
  - (V2) Fix a bug where prefetch instructions should not respond to load triggers ([#5059](https://github.com/OpenXiangShan/XiangShan/pull/5059))
- Timing optimization
  - Split the backend's first-level submodules to facilitate physical design partitioning ([#5032](https://github.com/OpenXiangShan/XiangShan/pull/5032))
- New RTL features
  - Complete Trace Control Interface support for APB and AXI buses
  - Split the SRAM sink into SMEM mode (writing to memory via AXI) and SRAM mode (with a dedicated FIFO buffer built into the component)
  - Design branch_map logic and synchronize packet and trap packet processing
  - Add performance counters to count the number of bypassable ALUs between any two transmit queues
- Code quality improvements
  - Remove some dead code ([#5071](https://github.com/OpenXiangShan/XiangShan/pull/5071))

### MemBlock and Cache

- Bug Fix
  - (V2) Fix the issue in FDP where the counter filter capacity is insufficient and needs to be increased by 1 ([#5030](https://github.com/OpenXiangShan/XiangShan/pull/5030))
  - (V2) Fix the issue that LoadUnit did not re-access data during fast replay was performed to avoid memory consistency issues  ([#4965](https://github.com/OpenXiangShan/XiangShan/pull/4965))
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
