---
slug: biweekly-112-en
date: 2026-09-30
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 112] 20260930

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 112th issue of the biweekly report.

<!-- more -->

## Recent Developments

### Frontend

- Bug fixes
  - Fix the issue where history generated after a redirect could not participate in CommonHR prediction, allowing the first CommonHR prediction after a redirect to use the newly generated history ([#6617](https://github.com/OpenXiangShan/XiangShan/pull/6617))
  - Fix canonical PC checks in the frontend and extend the high-bit and exception handling paths for instruction-fetch addresses, covering Sv39 and Sv48 address modes ([#6272](https://github.com/OpenXiangShan/XiangShan/pull/6272))
- Timing optimizations
  - Move the uBTB hit check to T1 and remove the T1-to-T0 forwarding path to shorten the critical BPU path ([#6489](https://github.com/OpenXiangShan/XiangShan/pull/6489))

### Backend

### MemBlock and Cache

### XSAI

- Code quality
  - Switch CI nightly random regression to the RVA23 non-vector SPEC checkpoint pool ([XSAI #130](https://github.com/OpenXiangShan/XSAI/pull/130))
- Debugging tools
  - Add a joint CUTE-L2 test top and provide write-request observation interfaces ([CUTE #40](https://github.com/OpenXiangShan/CUTE/pull/40), [CUTE #41](https://github.com/OpenXiangShan/CUTE/pull/41))
  - Improve NEMU's CUTE controller-mode callbacks and matrix synchronization support ([NEMU #1225](https://github.com/OpenXiangShan/NEMU/pull/1225))
  - Fix the layout mismatch between AME event structures in DiffTest batch mode and NEMU ([difftest #962](https://github.com/OpenXiangShan/difftest/pull/962))
  - Fix `coreid` and PC sampling in CUTE DiffTest events ([CUTE #42](https://github.com/OpenXiangShan/CUTE/pull/42))
  - Restrict comparisons for NEMU matrix load results to avoid false positives caused by unwritten regions ([NEMU #1217](https://github.com/OpenXiangShan/NEMU/pull/1217))
  - Add checks in NEMU for missing synchronization before matrix memory accesses and reads from undefined matrix-register regions ([NEMU #1212](https://github.com/OpenXiangShan/NEMU/pull/1212), [NEMU #1224](https://github.com/OpenXiangShan/NEMU/pull/1224))

### Infra

### XS-GEM5

- Simulator alignment
  - Add 3-cycle delay to vector memory writeback ([XS-GEM5 #1155](https://github.com/OpenXiangShan/GEM5/pull/1155))
  - Align pre-decode ([XS-GEM5 #1150](https://github.com/OpenXiangShan/GEM5/pull/1150))
  - Align ibuffer bypass behavior for vset instructions ([XS-GEM5 #1135](https://github.com/OpenXiangShan/GEM5/pull/1135))
  - Support cache hit under block ([XS-GEM5 #1164](https://github.com/OpenXiangShan/GEM5/pull/1164))
  - Align floating-point division latency ([XS-GEM5 #1167](https://github.com/OpenXiangShan/GEM5/pull/1167))
  - Align vector IQ configuration ([XS-GEM5 #1179](https://github.com/OpenXiangShan/GEM5/pull/1179))
- New feature exploration
  - New pointer prefetch algorithm LLDP ([XS-GEM5 #1158](https://github.com/OpenXiangShan/GEM5/pull/1158))
  - Move tage prediction from s3 to s2 ([XS-GEM5 #1165](https://github.com/OpenXiangShan/GEM5/pull/1165))
  - safe-iq watermark ([XS-GEM5 #1175](https://github.com/OpenXiangShan/GEM5/pull/1175))
- Infrastructure
  - Implementation of the cbo.zero instruction ([XS-GEM5 #1153](https://github.com/OpenXiangShan/GEM5/pull/1153))
  - Improvements and documentation for se mode ([XS-GEM5 #1154](https://github.com/OpenXiangShan/GEM5/pull/1154))
  - Support more se-mode workloads ([XS-GEM5 #1156](https://github.com/OpenXiangShan/GEM5/pull/1156))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | 0eea07ed9  |
| Date                 | 2026/09/11 |
| L1 ICache            | 64 KB      |
| L1 DCache            | 64 KB      |
| L2 Cache             | 2 MB       |
| L3 Cache             | 32 MB      |
| LSU                  | 3ld2st     |
| Bus protocol         | CHI        |
| Memory configuration | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        | 56.40  | 54.24  | 410.bwaves          | 126.11 | 112.18 |
| 401.bzip2            | 30.49  | 31.20  | 416.gamess          | 59.54  | 56.55  |
| 403.gcc              | 61.93  | 42.58  | 433.milc            | 76.56  | 73.10  |
| 429.mcf              | 77.90  | 64.10  | 434.zeusmp          | 79.58  | 70.77  |
| 445.gobmk            | 44.90  | 44.46  | 435.gromacs         | 41.68  | 36.92  |
| 456.hmmer            | 54.74  | 67.53  | 436.cactusADM       | 86.33  | 94.33  |
| 458.sjeng            | 43.73  | 43.69  | 437.leslie3d        | 66.56  | 64.63  |
| 462.libquantum       | 164.48 | 382.99 | 444.namd            | 44.46  | 45.48  |
| 464.h264ref          | 69.46  | 76.01  | 447.dealII          | 66.08  | 81.12  |
| 471.omnetpp          | 56.40  | 56.29  | 450.soplex          | 65.94  | 79.40  |
| 473.astar            | 34.28  | 33.67  | 453.povray          | 79.62  | 74.37  |
| 483.xalancbmk        | 89.19  | 107.78 | 454.calculix        | 42.15  | 41.17  |
| GEOMEAN              | 58.94  | 62.57  | 459.GemsFDTD        | 80.02  | 76.96  |
|                      |        |        | 465.tonto           | 55.04  | 37.92  |
|                      |        |        | 470.lbm             | 128.56 | 149.77 |
|                      |        |        | 481.wrf             | 59.50  | 45.14  |
|                      |        |        | 482.sphinx3         | 62.02  | 64.63  |
|                      |        |        | GEOMEAN             | 68.19  | 65.95  |

Compilation parameters are as follows:

| Parameters                  | GCC16                         | XSCC                |
| --------------------------- | ----------------------------- | ------------------- |
| Compiler                    | gcc16                         | xscc                |
| Optimization level          | O3                            | O3                  |
| Memory library              | jemalloc                      | jemalloc            |
| ISA configuration           | RVA23-based (vector disabled) | RV64GCB             |
| -ffp-contract               | fast                          | fast                |
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
