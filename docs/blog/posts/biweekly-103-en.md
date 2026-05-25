---
slug: biweekly-103-en
date: 2026-05-25
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 103] 20260525

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 103rd issue of the biweekly report.

The development of X200, SpacemiT's third-generation high-performance RISC-V processor core derived from XiangShan Kunming Lake V2, has been completed. Based on a conventional cloud-computing processor core, X200 has been specifically optimized for cloud-side Agent applications and flagship end-device Agent applications. Its SPECint 2006 performance reaches 16.0 points/GHz, and its single-core frequency can reach 3.3GHz. Compared with X100, its performance per core has improved by more than 100%, reaching 50 SPECint 2006 points/Core.

Even more encouraging than the fact that X200 builds on Kunming Lake V2 is that the full XiangShan open-source infrastructure was used throughout X200's development. This is the part below the surface that supports X200 on its path toward production readiness. These open-source toolchains greatly accelerated X200's development on top of XiangShan and provided strong assurance for its quality.

As for recent XiangShan development, the frontend is implementing 2-fetch while optimizing timing; the backend and memory teams fixed several functional bugs and continued advancing the new L2 design; XSAI added FP8 support for the matrix unit while also improving code quality and evaluation tools.

<!-- more -->

## Recent Developments

### Frontend

- RTL features
  - Implemented an initial 2-prefetch scheme ([#5775](https://github.com/OpenXiangShan/XiangShan/pull/5775))
- Bug fixes
  - (V2) Collaborated with the backend team to fix incorrect updates to the `xepc` and `xtval` registers when an exception occurs after `satp` is updated ([#5860](https://github.com/OpenXiangShan/XiangShan/pull/5860))
  - Fixed incorrect exception tagging when the IFU handles exceptions caused by cross-page instructions ([#5874](https://github.com/OpenXiangShan/XiangShan/pull/5874))
- PPA optimizations
  - Used SRAM to store the TAGE useful counters to save area ([#5852](https://github.com/OpenXiangShan/XiangShan/pull/5852))
  - Adjusted the pipeline stage partitioning for MBTB attribute handling at the top level of the BPU to improve timing ([#5842](https://github.com/OpenXiangShan/XiangShan/pull/5842))
- Code quality
  - Removed a potentially misleading parameter in MBTB ([#5891](https://github.com/OpenXiangShan/XiangShan/pull/5891))

### Backend

- Bug fixes
  - (V2) Collaborated with the frontend team to fix incorrect updates to the `xepc` and `xtval` registers when an exception occurs after `satp` is updated ([#5860](https://github.com/OpenXiangShan/XiangShan/pull/5860))
  - (V2) Fixed the issue where every jump instruction execution would trigger a redirect ([#5867](https://github.com/OpenXiangShan/XiangShan/pull/5867))
  - (V2) Added an initial value for `mtvec` ([#5862](https://github.com/OpenXiangShan/XiangShan/pull/5862))

### MemBlock and Cache

- RTL features
  - Implemented store-load forwarding in the DCache MSHR ([#5870](https://github.com/OpenXiangShan/XiangShan/pull/5870))
  - Continued advancing the new L2 design
- Bug fixes
  - Fixed the issue where the PPN truncation bits were incorrectly used to index CFS in L2TLB ([#5858](https://github.com/OpenXiangShan/XiangShan/pull/5858))
  - Fixed StoreQueue behavior when handling memory accesses that cross 16-byte boundaries ([#5855](https://github.com/OpenXiangShan/XiangShan/pull/5855))

### XSAI

- RTL features
  - The matrix unit supports FP8 precision ([XSAI #61](https://github.com/OpenXiangShan/XSAI/pull/61))
  - Evaluating 8-channel memory access for the matrix unit
  - Working with the backend team to implement BF16 scalar and vector support
- Bug fixes
  - Fixed a scheduling error in CUTE ([XSAI #62](https://github.com/OpenXiangShan/XSAI/pull/62))
- Code quality
  - Added Makefile tracking for changes in CUTE code ([XSAI #63](https://github.com/OpenXiangShan/XSAI/pull/63))
  - Accelerated firmware compilation ([xsai-env #4](https://github.com/OurCompArchGroup/xsai-env/pull/4))
- Evaluation tools
  - Parallel checkpoint simulation ([xsai-env #11](https://github.com/OurCompArchGroup/xsai-env/pull/11))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | f65a4e6c3  |
| Date                 | 2026/05/07 |
| L1 ICache            | 64KB       |
| L1 DCache            | 64KB       |
| L2 Cache             | 1MB        |
| L3 Cache             | 16MB       |
| LSU                  | 3ld2st     |
| Bus protocol         | CHI        |
| Memory configuration | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.42  | 47.53  | 410.bwaves         | 85.27  | 89.88  |
| 401.bzip2           | 27.43  | 28.28  | 416.gamess         | 57.05  | 53.23  |
| 403.gcc             | 55.26  | 38.88  | 433.milc           | 64.93  | 64.04  |
| 429.mcf             | 61.00  | 55.47  | 434.zeusmp         | 71.27  | 64.66  |
| 445.gobmk           | 38.94  | 40.10  | 435.gromacs        | 37.20  | 34.38  |
| 456.hmmer           | 54.38  | 64.72  | 436.cactusADM      | 76.13  | 87.68  |
| 458.sjeng           | 38.87  | 39.48  | 437.leslie3d       | 56.26  | 56.36  |
| 462.libquantum      | 136.67 | 294.84 | 444.namd           | 43.23  | 45.23  |
| 464.h264ref         | 63.46  | 71.99  | 447.dealII         | 64.25  | 68.39  |
| 471.omnetpp         | 41.07  | 39.47  | 450.soplex         | 52.12  | 63.93  |
| 473.astar           | 30.42  | 29.63  | 453.povray         | 73.34  | 65.77  |
| 483.xalancbmk       | 75.83  | 84.61  | 454.Calculix       | 43.74  | 39.61  |
| GEOMEAN             | 50.90  | 54.07  | 459.GemsFDTD       | 63.50  | 63.95  |
|                     |        |        | 465.tonto          | 52.59  | 35.01  |
|                     |        |        | 470.lbm            | 125.82 | 133.04 |
|                     |        |        | 481.wrf            | 54.96  | 41.58  |
|                     |        |        | 482.sphinx3        | 59.39  | 62.42  |
|                     |        |        | GEOMEAN            | 61.07  | 59.18  |

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

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Jiru Sun, Yanjun Li
