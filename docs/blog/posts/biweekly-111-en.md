---
slug: biweekly-111-en
date: 2026-09-16
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 111] 20260916

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 111th issue of the biweekly report.

<!-- more -->

## Recent Developments

### Frontend

### Backend

### MemBlock and Cache

### XSAI

### Infra

### XS-GEM5

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | 53a957667  |
| Date                 | 2026/08/21 |
| L1 ICache            | 64KB       |
| L1 DCache            | 64KB       |
| L2 Cache             | 2MB        |
| L3 Cache             | 16MB       |
| LSU                  | 3ld2st     |
| Bus protocol         | CHI        |
| Memory configuration | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC16  |  XSCC  | SPECfp 2006 @ 3GHz | GCC16  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 55.02  | 53.33  | 410.bwaves         | 123.07 | 105.77 |
| 401.bzip2           | 29.89  | 30.60  | 416.gamess         | 58.70  | 55.81  |
| 403.gcc             | 58.27  | 41.61  | 433.milc           | 71.84  | 68.77  |
| 429.mcf             | 72.01  | 62.81  | 434.zeusmp         | 77.33  | 67.78  |
| 445.gobmk           | 43.70  | 42.34  | 435.gromacs        | 40.04  | 35.10  |
| 456.hmmer           | 54.59  | 67.12  | 436.cactusADM      | 85.01  | 93.51  |
| 458.sjeng           | 41.66  | 41.74  | 437.leslie3d       | 61.20  | 61.31  |
| 462.libquantum      | 138.17 | 305.05 | 444.namd           | 44.25  | 45.26  |
| 464.h264ref         | 69.92  | 75.51  | 447.dealII         | 64.71  | 79.14  |
| 471.omnetpp         | 48.18  | 47.76  | 450.soplex         | 59.78  | 72.28  |
| 473.astar           | 33.06  | 32.50  | 453.povray         | 78.25  | 73.65  |
| 483.xalancbmk       | 85.35  | 92.62  | 454.Calculix       | 41.80  | 40.77  |
| GEOMEAN             | 55.75  | 58.70  | 459.GemsFDTD       | 74.41  | 73.41  |
|                     |        |        | 465.tonto          | 55.70  | 37.80  |
|                     |        |        | 470.lbm            | 127.10 | 146.69 |
|                     |        |        | 481.wrf            | 58.65  | 44.97  |
|                     |        |        | 482.sphinx3        | 61.39  | 64.02  |
|                     |        |        | GEOMEAN            | 66.14  | 63.98  |

Compilation parameters are as follows:

| Parameters                  | GCC16                         | XSCC                |
| --------------------------- | ----------------------------- | ------------------- |
| Compiler                    | gcc16                         | xscc                |
| Optimization level          | O3                            | O3                  |
| Memory library              | jemalloc                      | jemalloc            |
| ISA configuration           | RVA23-based (vector disabled) | RV64GCB             |
| -ffp-contraction            | fast                          | fast                |
| Linker optimization         | -flto                         | -flto               |
| Floating-point optimization | -ffast-math                   | -ffast-math         |
| -mcpu                       | -                             | xiangshan-kunminghu |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Yanjun Li, Jinhong Zeng, Zechen Yang, Hanle Zhang, Kunlin You, Hao Zhen, Yiming Yan
