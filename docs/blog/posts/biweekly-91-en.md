---
slug: biweekly-91-en
date: 2025-12-08
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 91] 20251208

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan.

This is the 91st issue of the biweekly report.

The final performance regression of XiangShan V2 has been successfully completed! Unknowingly, we have completed a total of 46 biweekly performance regression tests. These 46 regressions not only record the performance evolution of XiangShan V2, but also serve as a strong testament to the vigorous development and continuous progress of the XiangShan processor.

![Performance Regression Results for XiangShan Kunminghu V2](./figs/performance-regression-v2.png)

Over the past four years, the XiangShan processor has gradually evolved from a campus course project into an industrial-grade processor. From the starting point "Yanqi Lake", to "Nanhu", which achieved industrial delivery for the first time and has been used in multiple projects, and then to "Kunming Lake V2", the current highest-performance open-source processor core - the evolution of these three generations of XiangShan not only embodies the efforts of every team member but also relies on the continuous attention and strong support from community partners. Here, we express our sincere gratitude to everyone!

Now, it is time to bid farewell to XiangShan V2 and welcome XiangShan V3! V3 will have more powerful performance than V2, which also means greater challenges. It is an uncharted territory for the XiangShan team, and every step we take is writing new history. However, we firmly believe that through the new concept and method of "open source", we can move forward together with the entire community and further enhance the performance benchmark of open-source processors.

Thank you for your companionship and support for XiangShan, and we look forward to your continued attention to the subsequent progress of XiangShan V3!

In terms of XiangShan development, the frontend has fixed ~~countless~~ BPU-related performance bugs ~~performance is finally close to the pre-refactoring level~~, and added performance counters for better performance analysis. The backend and memory system have fixed several bugs in V2 and further optimized timing. In terms of V3, the backend continues to advance the design of the new vector unit, and the memory system has carried out module refactoring and testing, as well as prefetch performance exploration.

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
  - implementating the new design of V3 vector unit
- Bug fixes
  - Fix CSR wake-up related issues ([#5259](https://github.com/OpenXiangShan/XiangShan/pull/5259))
  - Fix uncertain wake-up issues in floating-point division and square root during pipeline flush ([YunSuan #5131](https://github.com/OpenXiangShan/YunSuan/pull/192))
  - Focusing on bugs with register file read arbitration and wake-up performance
- Timing optimization
  - Remove a clock gate in BypassNetwork ([#5291](https://github.com/OpenXiangShan/XiangShan/pull/5291/files))

### MemBlock and Cache

- RTL new features
  - (V2) Disable hardware error generated by LoadUnit ecc ([#5285](https://github.com/OpenXiangShan/XiangShan/pull/5285))
  - Move IntBuffer for beu into L2Top for partition ([#5110](https://github.com/OpenXiangShan/XiangShan/pull/5110))
  - The refactoring and testing of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - (V2) Fix the corner case of misalign store ([#5233](https://github.com/OpenXiangShan/XiangShan/pull/5233))
  - (V2) Fix the logic where tilelink error generate exception ([#5269](https://github.com/OpenXiangShan/XiangShan/pull/5269))
  - (V2) Fix the priority of misalign exception ([#5270](https://github.com/OpenXiangShan/XiangShan/pull/5270))
  - Fix the incorrect TLB level refill when has exception ([#5087](https://github.com/OpenXiangShan/XiangShan/pull/5087))
  - Fix bitmap check result wakeup l0BitmapReg logic ([#5073](https://github.com/OpenXiangShan/XiangShan/pull/5073))
  - Disable address matching when hfence.vvma or sfence.vma when v = 1 ([#5114](https://github.com/OpenXiangShan/XiangShan/pull/5114))
  - Fix writeback bundle connections in LoadMissalighBuffer
- Performance Optimizations
  - Sent strean prefetch only once to L1DCache ([#5224](https://github.com/OpenXiangShan/XiangShan/pull/5224))
- Timing
  - (V2) Remove some RegEnable in TLBStorage to avoid clockgating ([#5229](https://github.com/OpenXiangShan/XiangShan/pull/5229))
  - (V2) Adjuct misaligned replay logic in StoreUnit ([#5207](https://github.com/OpenXiangShan/XiangShan/pull/5207))
  - (V2) Decouple the valid for vsta and vstd in VSplit ([#5208](https://github.com/OpenXiangShan/XiangShan/pull/5208))
  - (V2) Remove the ICG caused by need_gpa in TLB ([#5230](https://github.com/OpenXiangShan/XiangShan/pull/5230))
  - (V2) Fix critical path from Dir error to GrantBuffer in CoupledL2 ([CoupledL2 #448](https://github.com/OpenXiangShan/CoupledL2/pull/448))
  - (V2) Optimize the timing of StoreQueueData, MainPipe and MissQueue
  - Optimize the timing of pmp check，bitmap and PTW
- Code quality improvements
  - Rename the intermediate variables to improve readability
- Build Tools
  - Disable the behavior of chisel7 to place assertion files in different layers ([OpenLLC #71](https://github.com/OpenXiangShan/OpenLLC/pull/71))
- Debugging tools
  - Support L2ToL1Hint checking in tl-test-new ([tl-test-new #82](https://github.com/OpenXiangShan/tl-test-new/pull/82))

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
