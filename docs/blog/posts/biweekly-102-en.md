---
slug: biweekly-102-en
date: 2026-05-11
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 102] 20260511

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 102nd issue of the biweekly report.

The design document of Kunming Lake V3 has been gradually released, and we welcome everyone to read and discuss it with us! Currently, the new design document includes two modules: ICache and BPU. The design documents for other modules will be released as development progresses. The design document is still available at <https://docs.xiangshan.cc/projects/design/zh-cn/>. If you are interested in the design document of Kunming Lake V2, you can switch branches at the bottom right corner of the webpage to view it.

As for recent XiangShan core development, the frontend optimized branch predictor timing, while backend and memory teams fixed bugs and continued module refactoring and testing.

<!-- more -->

## Recent Developments

### Frontend

- RTL features
  - Implemented the initial version of 2-prefetch ([#5775](https://github.com/OpenXiangShan/XiangShan/pull/5775))
- Bug fixes
  - (V2) Collaborated with the backend team to fix the issue of incorrect xepc and xtval register updates when an exception occurs after satp update ([#5860](https://github.com/OpenXiangShan/XiangShan/pull/5860))
  - Fixed the issue of incorrect exception tagging when IFU handles cross-page instructions ([#5874](https://github.com/OpenXiangShan/XiangShan/pull/5874))
- PPA optimizations
  - Used SRAM to save TAGE useful counter to save area ([#5852](https://github.com/OpenXiangShan/XiangShan/pull/5852))
  - Adjusted the pipeline stages of BPU handling mbtb attribute to improve timing ([#5842](https://github.com/OpenXiangShan/XiangShan/pull/5842))
- Code quality
  - Removed a potentially misleading parameter in MBTB ([#5891](https://github.com/OpenXiangShan/XiangShan/pull/5891))

### Backend

- RTL New Features
  - (V2) Make commit stuck critical error check configurable by CSR ([#5806](https://github.com/OpenXiangShan/XiangShan/pull/5806))
  - Add switch to disable dispatch balance opt ([#5815](https://github.com/OpenXiangShan/XiangShan/pull/5815))
  - Resolve the false positive issue caused by insufficient main pipeline resources ([#5803](https://github.com/OpenXiangShan/XiangShan/pull/5803))
- PPA optimizations
  - Optimize dispatch policy to improve performance ([#5801](https://github.com/OpenXiangShan/XiangShan/pull/5801))
- Bug fixes
  - fix indirect csr RegOut ([(V2) #5823](https://github.com/OpenXiangShan/XiangShan/pull/5823), [5833](https://github.com/OpenXiangShan/XiangShan/pull/5833))

### MemBlock and Cache

- RTL New Features
  - Implemented store-load forwarding in DCache mshr ([#5870](https://github.com/OpenXiangShan/XiangShan/pull/5870))
  - Refactoring of L2 is continuously progressing
- Bug Fixes
  - Fix the issue of incorrect use of PPN truncation bit to index cfs in L2TLB ([#5858](https://github.com/OpenXiangShan/XiangShan/pull/5858))
  - Fix the behavior of StoreQueue when handling cross 16-byte accesses ([#5855](https://github.com/OpenXiangShan/XiangShan/pull/5855))

### XSAI

- RTL New Features
  - The matrix unit supports FP8 precision ([XSAI #61](https://github.com/OpenXiangShan/XSAI/pull/61))
  - Evaluating 8-channel cache access for the matrix unit
  - Co-developing BF16 scalar and vector support with the backend team
- Bug Fixes
  - Fixed a scheduling error in CUTE ([XSAI #62](https://github.com/OpenXiangShan/XSAI/pull/62))
- Code Quality
  - Added Makefile tracking for CUTE code changes ([XSAI #63](https://github.com/OpenXiangShan/XSAI/pull/63))
  - Accelerated firmware compilation ([xsai-env #4](https://github.com/OurCompArchGroup/xsai-env/pull/4))
- Evaluation Tools
  - Parallel checkpoint simulation ([xsai-env #11](https://github.com/OurCompArchGroup/xsai-env/pull/11))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | 82d2669b2  |
| Date                 | 2026/04/23 |
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
| 400.perlbench       | 48.55  | 47.58  | 410.bwaves         | 85.31  | 90.03  |
| 401.bzip2           | 27.44  | 28.26  | 416.gamess         | 57.05  | 53.20  |
| 403.gcc             | 55.18  | 39.57  | 433.milc           | 64.74  | 64.04  |
| 429.mcf             | 61.07  | 55.44  | 434.zeusmp         | 71.39  | 64.13  |
| 445.gobmk           | 38.93  | 40.08  | 435.gromacs        | 37.20  | 34.38  |
| 456.hmmer           | 54.39  | 64.70  | 436.cactusADM      | 76.02  | 87.74  |
| 458.sjeng           | 38.89  | 39.43  | 437.leslie3d       | 56.29  | 56.46  |
| 462.libquantum      | 136.76 | 294.79 | 444.namd           | 43.21  | 45.23  |
| 464.h264ref         | 63.44  | 72.03  | 447.dealII         | 64.12  | 68.46  |
| 471.omnetpp         | 41.05  | 39.51  | 450.soplex         | 52.08  | 64.00  |
| 473.astar           | 30.46  | 29.66  | 453.povray         | 73.34  | 66.37  |
| 483.xalancbmk       | 75.80  | 84.53  | 454.Calculix       | 43.80  | 39.68  |
| GEOMEAN             | 50.92  | 54.14  | 459.GemsFDTD       | 63.55  | 64.27  |
|                     |        |        | 465.tonto          | 52.57  | 35.04  |
|                     |        |        | 470.lbm            | 125.76 | 133.04 |
|                     |        |        | 481.wrf            | 54.94  | 41.59  |
|                     |        |        | 482.sphinx3        | 59.37  | 62.42  |
|                     |        |        | GEOMEAN            | 61.05  | 59.23  |

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
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Jiru Sun, Yanjun Li
