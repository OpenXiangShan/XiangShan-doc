---
slug: biweekly-92-en
date: 2025-12-22
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 92] 20251222

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan.

This is the 92nd issue of the biweekly report.

The final performance regression of XiangShan V2 has been successfully completed! Unknowingly, we have completed a total of 46 biweekly performance regression tests. These 46 regressions not only record the performance evolution of XiangShan V2, but also serve as a strong testament to the vigorous development and continuous progress of the XiangShan processor.

![Performance Regression Results for XiangShan V2](./figs/performance-regression.png)

Over the past four years, the XiangShan processor has gradually evolved from a campus course project into an industrial-grade processor. From the starting point "Yanqi Lake", to "Nanhu", which achieved industrial delivery for the first time and has been used in multiple projects, and then to "Kunming Lake V2", the current highest-performance open-source processor core - the evolution of these three generations of XiangShan not only embodies the efforts of every team member but also relies on the continuous attention and strong support from community partners. Here, we express our sincere gratitude to everyone!

Now, it is time to bid farewell to XiangShan V2 and welcome XiangShan V3! V3 will have more powerful performance than V2, which also means greater challenges. It is an uncharted territory for the XiangShan team, and every step we take is writing new history. However, we firmly believe that through the new concept and method of "open source", we can move forward together with the entire community and further enhance the performance benchmark of open-source processors.

Thank you for your companionship and support for XiangShan, and we look forward to your continued attention to the subsequent progress of XiangShan V3!

In terms of XiangShan development, the frontend has fixed ~~countless~~ BPU-related performance bugs ~~performance is finally close to the pre-refactoring level~~, and added performance counters for better performance analysis. The backend and memory system have fixed several bugs in V2 and further optimized timing. In terms of V3, the backend continues to advance the design of the new vector unit, and the memory system has carried out module refactoring and testing, as well as prefetch performance exploration.

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Reduce SRAM write requests when TAGE counters are saturated, thereby reducing stall caused by SRAM port conflicts ([#5309](https://github.com/OpenXiangShan/XiangShan/pull/5309))
  - Align TAGE prediction selection logic with GEM5 ([#5377](https://github.com/OpenXiangShan/XiangShan/pull/5377))
  - Implement SC bias table ([#5234](https://github.com/OpenXiangShan/XiangShan/pull/5234))
  - Implement ITTAGE prediction for call-type branches ([#5311](https://github.com/OpenXiangShan/XiangShan/pull/5311))
- Bug Fix
  - Fix the misuse issue caused by unclear naming between branch address (cfiPc) and prediction block address (startPc) in BPU training ([#5317](https://github.com/OpenXiangShan/XiangShan/pull/5317))
  - Fix UBTB training pipeline hit condition to avoid incorrect replacer updates ([#5326](https://github.com/OpenXiangShan/XiangShan/pull/5326))
  - Fix TAGE folded history signal width typo ([#5325](https://github.com/OpenXiangShan/XiangShan/pull/5325))
  - Fix TAGE cfiPc typo ([#5345](https://github.com/OpenXiangShan/XiangShan/pull/5345))
  - Fix some RAS typos and enable RAS ([#5321](https://github.com/OpenXiangShan/XiangShan/pull/5321))
  - Fix FTQ resolveQueue bpu enqueue flush logic error issue ([#5344](https://github.com/OpenXiangShan/XiangShan/pull/5344))
- Timing/Area optimization
  - Move TAGE BaseTable into MBTB to synchronize counter allocation with MBTB entries, reducing redundant storage ([#5349](https://github.com/OpenXiangShan/XiangShan/pull/5349))
- Code quality improvements
  - Unify the naming of pc-related signals within BPU ([#5318](https://github.com/OpenXiangShan/XiangShan/pull/5318))
  - Add some utility methods to batch generate performance counters with similar prefixes ([#5298](https://github.com/OpenXiangShan/XiangShan/pull/5298))
- Debugging tools
  - Add and fix a large number of performance counters in various modules ([#5320](https://github.com/OpenXiangShan/XiangShan/pull/5320), [#5265](https://github.com/OpenXiangShan/XiangShan/pull/5265), [#5319](https://github.com/OpenXiangShan/XiangShan/pull/5319), [#5332](https://github.com/OpenXiangShan/XiangShan/pull/5332), [#5339](https://github.com/OpenXiangShan/XiangShan/pull/5339), [#5347](https://github.com/OpenXiangShan/XiangShan/pull/5347), [#5353](https://github.com/OpenXiangShan/XiangShan/pull/5353), [#5370](https://github.com/OpenXiangShan/XiangShan/pull/5370), [#5383](https://github.com/OpenXiangShan/XiangShan/pull/5383), [#5372](https://github.com/OpenXiangShan/XiangShan/pull/5372))
  - Optimize the branch real address calculation logic of TAGE Trace, considering compressed instructions ([#5355](https://github.com/OpenXiangShan/XiangShan/pull/5355))

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

### MemBlock and Cache

- RTL new features
  - (V2) Support disabling ClockGate in CoupledL2 via parameters ([CoupledL2 #451](https://github.com/OpenXiangShan/CoupledL2/pull/451))
  - (V2) Parameterize TIMERange in MMIOBridge of CoupledL2 ([CoupledL2 #453](https://github.com/OpenXiangShan/CoupledL2/pull/451))
  - The refactoring and testing of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - (V2) Fix the incorrect wakeup of load requests in LoadQueueReplay ([#5327](https://github.com/OpenXiangShan/XiangShan/pull/5327))
  - (V2) Fix the wlineflag not delayed one cycle in LoadQueueRAW ([#5352](https://github.com/OpenXiangShan/XiangShan/pull/5352))
  - (V2) Fix the depth of L1StreamPrefetcher ([#5365](https://github.com/OpenXiangShan/XiangShan/pull/5365))
  - (V2) Remove some RegNext(hartid) in L2Top and MemBlock ([#5408](https://github.com/OpenXiangShan/XiangShan/pull/5408))
  - (V2) Fix the wrong DataCheck logic in TXDAT ([CoupledL2 #455](https://github.com/OpenXiangShan/CoupledL2/pull/455))
  - (V2) Fix the compilation error of l2MissMatch IO ([CoupledL2 #456](https://github.com/OpenXiangShan/CoupledL2/pull/456))
- Performance Optimizations
  - (V2) Increase the capacity of uncachebuffer from 4 to 16 ([#5364](https://github.com/OpenXiangShan/XiangShan/pull/5364))
  - Add PerfCCT support for LoadUnit ([#5286](https://github.com/OpenXiangShan/XiangShan/pull/5286))
- Timing
  - (V2) Adjust the arbtration sequence for s0 source in LoadUnit ([#5300](https://github.com/OpenXiangShan/XiangShan/pull/5300))
  - (V2) Optimize the timing of VSegmentUnit and exceptionBuffer ([#5330](https://github.com/OpenXiangShan/XiangShan/pull/5330), [#5292](https://github.com/OpenXiangShan/XiangShan/pull/5292))
  - (V2) Remove IO port for store prefetch in Sbuffer ([#5329](https://github.com/OpenXiangShan/XiangShan/pull/5329))
  - (V2) Remove unnecessary Mux in MemBlock when generating paddr for TLB ([#5331](https://github.com/OpenXiangShan/XiangShan/pull/5331))
  - (V2) Replace BitmapCache from register to SRAM ([#5346](https://github.com/OpenXiangShan/XiangShan/pull/5346))
- Debugging tools
  - Support outputting performance counters in tl-test-new ([tl-test-new #84](https://github.com/OpenXiangShan/tl-test-new/pull/84))
  - Support outputting detailed information when check_paddr fails in NEMU ([NEMU #867](https://github.com/OpenXiangShan/NEMU/pull/867))
  - Continuous improvement of CHI infrastructure CHIron
  - Develop a verification tool CHI Test for the new version of L2 Cache. Continuous progressing
  - Refine the prefetch statistics in L2 Topdown Monitor ([CoupledL2 #452](https://github.com/OpenXiangShan/CoupledL2/pull/452))

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 36.18  | 410.bwaves       | 66.73  |
| 401.bzip2         | 25.46  | 416.gamess       | 40.99  |
| 403.gcc           | 48.00  | 433.milc         | 45.12  |
| 429.mcf           | 60.63  | 434.zeusmp       | 51.61  |
| 445.gobmk         | 30.32  | 435.gromacs      | 33.60  |
| 456.hmmer         | 41.62  | 436.cactusADM    | 46.19  |
| 458.sjeng         | 30.24  | 437.leslie3d     | 47.97  |
| 462.libquantum    | 122.43 | 444.namd         | 28.86  |
| 464.h264ref       | 56.58  | 447.dealII       | 73.55  |
| 471.omnetpp       | 41.77  | 450.soplex       | 52.50  |
| 473.astar         | 29.19  | 453.povray       | 53.46  |
| 483.xalancbmk     | 72.84  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.66  | 459.GemsFDTD     | 38.60  |
|                   |        | 465.tonto        | 36.66  |
|                   |        | 470.lbm          | 91.94  |
|                   |        | 481.wrf          | 40.70  |
|                   |        | 482.sphinx3      | 49.13  |
|                   |        | GEOMEAN          | 44.85  |

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
| Commit         | f9daf7c15  |
| Date           | 12/08/2025 |
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
