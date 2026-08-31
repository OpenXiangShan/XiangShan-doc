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

- Bug fixes
  - Fix canonical-address checks for frontend PCs and add related simulation tests ([#6340](https://github.com/OpenXiangShan/XiangShan/pull/6340))
  - Add the `notCfiTaken` signal to the IFU redirect `canTrain` condition ([#6398](https://github.com/OpenXiangShan/XiangShan/pull/6398))
  - Flush pending write requests when resetting TAGE useful counters to prevent stale requests from overwriting the reset results ([#6377](https://github.com/OpenXiangShan/XiangShan/pull/6377))
  - Prevent TAGE from rereading the prediction table when using the base prediction ([#6356](https://github.com/OpenXiangShan/XiangShan/pull/6356))
  - Prevent a spurious `s3_override` when both BPU S1 and S3 predict not taken ([#6417](https://github.com/OpenXiangShan/XiangShan/pull/6417))
  - Update BTB replacement state on training accesses instead of prediction accesses ([#6348](https://github.com/OpenXiangShan/XiangShan/pull/6348))
- Performance optimizations
  - Maintain `UseAltOnNa` based on predictor-table training state to reduce branch aliasing and register overhead ([#6328](https://github.com/OpenXiangShan/XiangShan/pull/6328))
  - Train the uBTB through both the resolve and fast-train paths to reduce extra bubbles after a misprediction redirect ([#6237](https://github.com/OpenXiangShan/XiangShan/pull/6237))
- PPA optimizations
  - Precompute `t0_firstMispredictMask` to improve the timing of the FTQ-to-BPU train-cache write path ([#6375](https://github.com/OpenXiangShan/XiangShan/pull/6375))
  - Move the pre-decode and `maybeRvc` logic and register ICache data to improve the timing of the IFU/ICache instruction-alignment path ([#6220](https://github.com/OpenXiangShan/XiangShan/pull/6220))
- Code refactoring
  - Move `vtype` generation from Decode to the IBuffer so each instruction carries its corresponding `vtype` and `specvtype` ([#6376](https://github.com/OpenXiangShan/XiangShan/pull/6376))
  - Use a PNR pointer to determine 2-prefetch and 2-fetch eligibility instead of a fixed distance from the BPU pointer ([#6378](https://github.com/OpenXiangShan/XiangShan/pull/6378))

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
