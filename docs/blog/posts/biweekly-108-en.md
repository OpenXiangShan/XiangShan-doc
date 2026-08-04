---
slug: biweekly-108-en
date: 2026-08-03
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 108] 20260803

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 108th issue of the biweekly report.

Regarding the recent development progress of XiangShan, the frontend has fixed timing issues in multiple modules and resolved some bugs reported by the community; the backend has fixed several bugs related to CSR, debug mode, and performance events, and synchronized V2 fixes to V3; in terms of memory access and caching, support for pre-allocated StoreQueue, LoadQueueReplay fast wakeup, and dual-port L1-L2 TileLink bus has been added, along with multiple bug fixes; XSAI has fixed control signals for load/store whole C instructions and added support for configurable multi-channel memory access in CUTE.

<!-- more -->

## Recent Developments

### Frontend

- PPA optimizations
  - Optimize the timing of signals related to the ICache DataArray read enable ([#6221](https://github.com/OpenXiangShan/XiangShan/pull/6221))
  - Optimize the IFU instruction-boundary calculation logic and the timing of the ICache miss path ([#6219](https://github.com/OpenXiangShan/XiangShan/pull/6219))
  - Use the positions of control-flow instructions (branches and jumps) instead of their offsets to reduce unnecessary additions and subtractions on the critical path ([#6253](https://github.com/OpenXiangShan/XiangShan/pull/6253))

### Backend

- Verification and dependency updates (V2)
  - Update the NEMU reference in ready-to-run to synchronize recent verification support ([#6252](https://github.com/OpenXiangShan/XiangShan/pull/6252), [#6266](https://github.com/OpenXiangShan/XiangShan/pull/6266))
- Bug fixes (V2)
  - Prevent double traps from triggering `criticalError` in debug mode ([#6224](https://github.com/OpenXiangShan/XiangShan/pull/6224))
  - Fix `s_EX_DT` to be controlled by `sstatus.SDT` ([#6256](https://github.com/OpenXiangShan/XiangShan/pull/6256))
  - Reset the trace pipeline with the synchronized CPU reset signal ([#6257](https://github.com/OpenXiangShan/XiangShan/pull/6257))
  - Fix incorrect trapping to HS/VS events when an NMI and an exception occur simultaneously ([#6258](https://github.com/OpenXiangShan/XiangShan/pull/6258))
- Performance analysis (V2)
  - Correct memory-stall attribution in TopDown analysis by distinguishing load and store stalls using concrete memory-pressure signals ([#6179](https://github.com/OpenXiangShan/XiangShan/pull/6179))

### MemBlock and Cache

- RTL features
  - Add one more dcache node to support two buses of TileLink ([#6178](https://github.com/OpenXiangShan/XiangShan/pull/6178))
  - Add support for Zabha extension ([#6248](https://github.com/OpenXiangShan/XiangShan/pull/6248))
- Bug fixes
  - Reject stale TLB updates and nonphysical store wakeups ([#6275](https://github.com/OpenXiangShan/XiangShan/pull/6275))
- Performance optimizations
  - Refine strict StoreSet prediction ([#6286](https://github.com/OpenXiangShan/XiangShan/pull/6286))
  - Add support of RRBankConflict arbiter in loadUnit ([#6242](https://github.com/OpenXiangShan/XiangShan/pull/6242))

### XSAI

- RTL features
  - Update the AME version to XSAI AME proposal 14 ([XSAI #77](https://github.com/OpenXiangShan/XSAI/pull/77))
  - Integrate ZhuJiang LLC ([XSAI #91](https://github.com/OpenXiangShan/XSAI/pull/91))
- Bug fixes
  - Fix read and write errors for mcsr alias CSRs ([XSAI #98](https://github.com/OpenXiangShan/XSAI/pull/98))
  - Fix the redirect logic in AmuCtrlBuffer to align with the ROB ([XSAI #99](https://github.com/OpenXiangShan/XSAI/pull/99))
  - Fix undefined behavior of the PriorityEncoder inside AmuCtrlBuffer ([XSAI #100](https://github.com/OpenXiangShan/XSAI/pull/100))
  - Relax overly strict assertion checks for buffer overflow in the LSQ ([XSAI #101](https://github.com/OpenXiangShan/XSAI/pull/101))
  - Fix a deadlock caused by `mfence` not blocking subsequent instructions ([XSAI #102](https://github.com/OpenXiangShan/XSAI/pull/102))
- Code quality
  - Provide a configurable msync count interface in CUTE ([XSAI #95](https://github.com/OpenXiangShan/XSAI/pull/95), [CUTE #34](https://github.com/OpenXiangShan/CUTE/pull/34))
  - Remove redundant mtilem/n/k reset logic ([XSAI #97](https://github.com/OpenXiangShan/XSAI/pull/97))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | 538ef487c  |
| Date                 | 2026/07/16 |
| L1 ICache            | 64KB       |
| L1 DCache            | 64KB       |
| L2 Cache             | 2MB        |
| L3 Cache             | 16MB       |
| LSU                  | 3ld2st     |
| Bus protocol         | CHI        |
| Memory configuration | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 51.60  | 50.69  | 410.bwaves         | 117.89 | 105.06 |
| 401.bzip2           | 29.70  | 30.32  | 416.gamess         | 58.32  | 55.79  |
| 403.gcc             | 56.22  | 40.24  | 433.milc           | 70.45  | 68.03  |
| 429.mcf             | 69.66  | 62.60  | 434.zeusmp         | 77.94  | 68.08  |
| 445.gobmk           | 39.88  | 40.41  | 435.gromacs        | 38.26  | 35.16  |
| 456.hmmer           | 55.26  | 66.99  | 436.cactusADM      | 80.28  | 92.71  |
| 458.sjeng           | 39.49  | 40.79  | 437.leslie3d       | 60.26  | 60.56  |
| 462.libquantum      | 138.31 | 308.74 | 444.namd           | 42.98  | 45.22  |
| 464.h264ref         | 69.77  | 75.31  | 447.dealII         | 73.92  | 73.54  |
| 471.omnetpp         | 43.46  | 42.85  | 450.soplex         | 59.74  | 70.99  |
| 473.astar           | 32.60  | 32.11  | 453.povray         | 76.38  | 70.16  |
| 483.xalancbmk       | 83.46  | 93.14  | 454.Calculix       | 42.71  | 40.68  |
| GEOMEAN             | 53.86  | 57.38  | 459.GemsFDTD       | 74.24  | 78.50  |
|                     |        |        | 465.tonto          | 54.03  | 37.61  |
|                     |        |        | 470.lbm            | 128.16 | 146.27 |
|                     |        |        | 481.wrf            | 62.22  | 44.89  |
|                     |        |        | 482.sphinx3        | 60.91  | 63.62  |
|                     |        |        | GEOMEAN            | 65.94  | 63.51  |

Compilation parameters are as follows:

| Parameters                  | GCC15       | XSCC                |
| --------------------------- | ----------- | ------------------- |
| Compiler                    | gcc15       | xscc                |
| Optimization level          | O3          | O3                  |
| Memory library              | jemalloc    | jemalloc            |
| -march                      | RV64GCB     | RV64GCB             |
| -ffp-contraction            | fast        | fast                |
| Linker optimization         | -flto       | -flto               |
| Floating-point optimization | -ffast-math | -ffast-math         |
| -mcpu                       | -           | xiangshan-kunminghu |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Jiru Sun, Yanjun Li
