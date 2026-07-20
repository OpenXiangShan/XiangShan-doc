---
slug: biweekly-107-en
date: 2026-07-20
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 107] 20260720

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 107th issue of the biweekly report.

The XiangShan tutorial at ISCA 2026 was held ~~not so~~ smoothly! Although some students could not present on site due to visa issues, we quickly arranged backup speakers and ultimately ensured that the tutorial was completed with high quality. Special thanks to everyone who follows XiangShan's development!

Regarding the recent development progress of XiangShan, the frontend added support for the 2-fetch feature; the memory subsystem optimized DCache, Sbuffer, and the prefetchers; XSAI supported new matrix memory access modes and updated the instruction extension.

<!-- more -->

## Tutorial and Conference Highlights

- A group photo to kick things off. Only the lucky person on the far left received their visa two days before the conference started; the other faculty members and students attended using existing visas.
  ![Group photo](./figs/biweekly-106/group.jpg)
- XSAI made its debut in a tutorial and attracted broad attention.
  ![XSAI talk](./figs/biweekly-106/xsai.jpg)
  ![Q&A discussion](./figs/biweekly-106/qa.jpg)
- Unity Chip paper presentation
  ![Unity Chip paper](./figs/biweekly-106/uc.jpg)

## Recent Developments

### Frontend

- RTL features
  - Support IFU predecode training for BPU ([#6112](https://github.com/OpenXiangShan/XiangShan/pull/6112))
  - Preliminary support for 2-fetch (processing two fetch blocks in a single cycle) ([#5996](https://github.com/OpenXiangShan/XiangShan/pull/5996))
- Bug fixes
  - Fix the FTQ trainCache flush condition ([#6147](https://github.com/OpenXiangShan/XiangShan/pull/6147))
  - Fix the issue where IFU UncacheUnit handling instruction fetches in PBMT.IO regions did not wait for instruction commit, leading to speculative instruction fetches ([#6144](https://github.com/OpenXiangShan/XiangShan/pull/6144))

### Backend

- Bug fixes
  - (V2) Fix PMP bug: non-dmode can't access memory of debug ([#6095](https://github.com/OpenXiangShan/XiangShan/pull/6095))

### MemBlock and Cache

- RTL features
  - Split the data SRAM of DCache into 32x2B ([#6118](https://github.com/OpenXiangShan/XiangShan/pull/6118))
  - Optimize the addressing of DCache through hash function ([#6166](https://github.com/OpenXiangShan/XiangShan/pull/6166))
- Bug fixes
  - Fix the set dueling logic error in the CoupledL2 drrip replacement algorithm ([XSCache #20](https://github.com/OpenXiangShan/XSCache/pull/20))
- Performance optimizations
  - Optimized the request merging logic of Sbuffer ([#6117](https://github.com/OpenXiangShan/XiangShan/pull/6117))
  - Optimized l1 prefetcher training ([#5544](https://github.com/OpenXiangShan/XiangShan/pull/5544), [XSCache #18](https://github.com/OpenXiangShan/XSCache/pull/18))
  - Limit prefetch requests based on the pressure of CoupledL2 MSHR ([XSCache #21](https://github.com/OpenXiangShan/XSCache/pull/21))
- Timing optimizations
  - Defer the update of sent_vec in l1 prefetcher to pf fire ([#6102](https://github.com/OpenXiangShan/XiangShan/pull/6102))
  - Use age matrix in loadQueueRAW to select the oldest entry ([#6120](https://github.com/OpenXiangShan/XiangShan/pull/6120))
- Code quality
  - Move the parameterized configuration related to the prefetcher to Parameter.scala ([#5382](https://github.com/OpenXiangShan/XiangShan/pull/5382))

### XSAI

- Bug fixes
  - Fixed the issue where MMA instructions missed illegal-instruction exceptions when `mtilen` was too large ([XSAI #79](https://github.com/OpenXiangShan/XSAI/pull/79))
- RTL features
  - Support fine-grained matrix memory access and transposed memory access for 8-bit elements ([CUTE #19](https://github.com/OpenXiangShan/CUTE/pull/19))
  - Update the instruction extension to XSAI proposal 12 ([XSAI #68](https://github.com/OpenXiangShan/XSAI/pull/68))
- Code quality
  - Refactor CUTE FPE code, split files, and remove symbolic links ([XSAI #81](https://github.com/OpenXiangShan/XSAI/pull/81))
- Debugging tools
  - Revert C++17 constructs in DiffTest to C++11 to improve compatibility ([XSAI #75](https://github.com/OpenXiangShan/XSAI/pull/75))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | 59ef4ea7d  |
| Date                 | 2026/07/03 |
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
| 400.perlbench       | 51.19  | 50.90  | 410.bwaves         | 116.08 | 104.81 |
| 401.bzip2           | 29.85  | 30.51  | 416.gamess         | 58.05  | 55.30  |
| 403.gcc             | 56.10  | 40.67  | 433.milc           | 70.32  | 69.31  |
| 429.mcf             | 70.05  | 62.69  | 434.zeusmp         | 77.83  | 67.38  |
| 445.gobmk           | 40.11  | 41.89  | 435.gromacs        | 38.20  | 34.94  |
| 456.hmmer           | 55.33  | 67.72  | 436.cactusADM      | 80.45  | 92.49  |
| 458.sjeng           | 40.66  | 41.54  | 437.leslie3d       | 60.27  | 60.78  |
| 462.libquantum      | 138.14 | 307.82 | 444.namd           | 43.31  | 45.56  |
| 464.h264ref         | 70.11  | 75.34  | 447.dealII         | 74.19  | 74.80  |
| 471.omnetpp         | 43.74  | 43.17  | 450.soplex         | 59.17  | 71.65  |
| 473.astar           | 33.73  | 33.05  | 453.povray         | 76.48  | 69.48  |
| 483.xalancbmk       | 83.35  | 92.95  | 454.Calculix       | 42.84  | 40.82  |
| GEOMEAN             | 54.22  | 57.95  | 459.GemsFDTD       | 68.28  | 65.83  |
|                     |        |        | 465.tonto          | 53.95  | 37.31  |
|                     |        |        | 470.lbm            | 128.22 | 146.35 |
|                     |        |        | 481.wrf            | 61.43  | 44.92  |
|                     |        |        | 482.sphinx3        | 61.15  | 63.82  |
|                     |        |        | GEOMEAN            | 65.52  | 62.92  |

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
