---
slug: biweekly-108-en
date: 2026-08-03
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 108] 20260803

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 108th issue of the biweekly report.

Regarding the recent development progress of XiangShan, the frontend continues to optimize timing; the backend fixes some bugs in V2 and calibrates the topdown counter; the memory and cache implement a dual-channel TileLink bus and optimize the LSU; XSAI updates the AME version and fixes several bugs.

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
| Commit               | a97570144  |
| Date                 | 2026/07/30 |
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
| 400.perlbench       | 51.92  | 52.22  | 410.bwaves         | 121.09 | 105.65 |
| 401.bzip2           | 30.04  | 30.58  | 416.gamess         | 58.30  | 55.84  |
| 403.gcc             | 56.24  | 39.91  | 433.milc           | 71.21  | 68.92  |
| 429.mcf             | 71.32  | 63.98  | 434.zeusmp         | 78.07  | 67.87  |
| 445.gobmk           | 39.95  | 40.49  | 435.gromacs        | 38.27  | 35.16  |
| 456.hmmer           | 55.24  | 67.00  | 436.cactusADM      | 80.70  | 93.11  |
| 458.sjeng           | 39.44  | 40.73  | 437.leslie3d       | 60.88  | 61.17  |
| 462.libquantum      | 138.63 | 305.37 | 444.namd           | 43.07  | 45.22  |
| 464.h264ref         | 69.80  | 74.93  | 447.dealII         | 74.36  | 74.52  |
| 471.omnetpp         | 43.60  | 42.84  | 450.soplex         | 60.07  | 71.35  |
| 473.astar           | 32.74  | 32.28  | 453.povray         | 76.41  | 72.29  |
| 483.xalancbmk       | 83.75  | 93.51  | 454.Calculix       | 42.73  | 40.73  |
| GEOMEAN             | 54.11  | 57.60  | 459.GemsFDTD       | 72.22  | 73.41  |
|                     |        |        | 465.tonto          | 54.18  | 37.50  |
|                     |        |        | 470.lbm            | 128.82 | 146.74 |
|                     |        |        | 481.wrf            | 61.76  | 45.03  |
|                     |        |        | 482.sphinx3        | 61.01  | 63.57  |
|                     |        |        | GEOMEAN            | 66.11  | 63.57  |

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
