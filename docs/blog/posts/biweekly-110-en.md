---
slug: biweekly-110-en
date: 2026-09-01
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 110] 20260901

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 110th issue of the biweekly report.

<!-- more -->

## Recent Developments

### Frontend

### Backend

### MemBlock and Cache

### XSAI

### Infra

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options |
| -------------------- | ------- |
| Commit               |         |
| Date                 |         |
| L1 ICache            |         |
| L1 DCache            |         |
| L2 Cache             |         |
| L3 Cache             |         |
| LSU                  |         |
| Bus protocol         |         |
| Memory configuration |         |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC15 | XSCC | SPECfp 2006 @ 3GHz | GCC15 | XSCC |
| :------------------ | :---: | :--: | :----------------- | :---: | :--: |
| 400.perlbench       |       |      | 410.bwaves         |       |      |
| 401.bzip2           |       |      | 416.gamess         |       |      |
| 403.gcc             |       |      | 433.milc           |       |      |
| 429.mcf             |       |      | 434.zeusmp         |       |      |
| 445.gobmk           |       |      | 435.gromacs        |       |      |
| 456.hmmer           |       |      | 436.cactusADM      |       |      |
| 458.sjeng           |       |      | 437.leslie3d       |       |      |
| 462.libquantum      |       |      | 444.namd           |       |      |
| 464.h264ref         |       |      | 447.dealII         |       |      |
| 471.omnetpp         |       |      | 450.soplex         |       |      |
| 473.astar           |       |      | 453.povray         |       |      |
| 483.xalancbmk       |       |      | 454.Calculix       |       |      |
| GEOMEAN             |       |      | 459.GemsFDTD       |       |      |
|                     |       |      | 465.tonto          |       |      |
|                     |       |      | 470.lbm            |       |      |
|                     |       |      | 481.wrf            |       |      |
|                     |       |      | 482.sphinx3        |       |      |
|                     |       |      | GEOMEAN            |       |      |

Compilation parameters are as follows:

| Parameters                  | GCC15 | XSCC |
| --------------------------- | ----- | ---- |
| Compiler                    |       |      |
| Optimization level          |       |      |
| Memory library              |       |      |
| -march                      |       |      |
| -ffp-contraction            |       |      |
| Linker optimization         |       |      |
| Floating-point optimization |       |      |
| -mcpu                       |       |      |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Yanjun Li, Jinhong Zeng, Zechen Yang, Hanle Zhang, Kunlin You, Yiming Yan
