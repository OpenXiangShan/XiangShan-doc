---
slug: biweekly-106-en
date: 2026-07-06
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 106] 20260706

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 106th issue of the biweekly report.

The RISC-V Summit Europe has successfully concluded! Professor Bao Yungang, Deputy Director of the Institute of Computing Technology, Chinese Academy of Sciences, and Chief Scientist of the Beijing Open Source Chip Research Institute, shared his [experience](https://mp.weixin.qq.com/s/sqesKwSbE1oDy3cL0ei1ZQ) at the summit and provided insights into the future prospects of RISC-V development. We welcome everyone to engage in discussions with us!

Regarding the recent development progress of XiangShan, the frontend continues to optimize timing; the backend and memory access have fixed some functional bugs while optimizing DCache and Sbuffer performance; XSAI has supported the BF16 extension, and HBL2 has implemented PutFullData for TL-TL and TL-CHI.

<!-- more -->

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
  - Optimized l1 prefetcher training ([#5544](https://github.com/OpenXiangShan/XiangShan/pull/5544))
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
| Commit               | 8c4daa743  |
| Date                 | 2026/06/18 |
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
| 400.perlbench       | 50.55  | 49.66  | 410.bwaves         | 104.21 | 95.87  |
| 401.bzip2           | 28.61  | 29.56  | 416.gamess         | 57.76  | 54.82  |
| 403.gcc             | 57.06  | 40.22  | 433.milc           | 69.94  | 68.81  |
| 429.mcf             | 71.47  | 62.54  | 434.zeusmp         | 74.95  | 67.02  |
| 445.gobmk           | 39.90  | 40.89  | 435.gromacs        | 37.90  | 34.82  |
| 456.hmmer           | 54.84  | 65.42  | 436.cactusADM      | 80.64  | 91.86  |
| 458.sjeng           | 39.36  | 40.48  | 437.leslie3d       | 59.90  | 59.70  |
| 462.libquantum      | 141.89 | 312.28 | 444.namd           | 43.55  | 45.46  |
| 464.h264ref         | 66.56  | 72.86  | 447.dealII         | 69.14  | 74.72  |
| 471.omnetpp         | 43.55  | 42.80  | 450.soplex         | 58.74  | 69.98  |
| 473.astar           | 32.92  | 32.64  | 453.povray         | 76.71  | 70.42  |
| 483.xalancbmk       | 81.13  | 92.62  | 454.Calculix       | 44.54  | 40.60  |
| GEOMEAN             | 53.57  | 57.00  | 459.GemsFDTD       | 69.93  | 70.40  |
|                     |        |        | 465.tonto          | 54.49  | 37.22  |
|                     |        |        | 470.lbm            | 128.45 | 148.55 |
|                     |        |        | 481.wrf            | 56.39  | 42.33  |
|                     |        |        | 482.sphinx3        | 60.94  | 63.63  |
|                     |        |        | GEOMEAN            | 64.55  | 62.40  |

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
