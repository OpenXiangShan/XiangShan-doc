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

- Bug fixes
  - Fix the issue where the ITTAGE predictor used the alternative prediction target when the alternative prediction was invalid, leading to incorrect counter updates ([#6167](https://github.com/OpenXiangShan/XiangShan/pull/6167))
  - Fix the issue where FTQ did not correctly handle backendExceptionPtr when cleaning up V2 legacy code, causing exceptions to not be reported correctly when jumping to virtual addresses that violate the Sv39/48 specification ([#6235](https://github.com/OpenXiangShan/XiangShan/pull/6235))
  - Fix the issue where IFU incorrectly calculated the offset and redirect target when handling a single RVI instruction crossing a page boundary in an MMIO region, leading to incorrect xtval/xepc values and fetching skipping part of the instruction data ([#6213](https://github.com/OpenXiangShan/XiangShan/pull/6213))
- PPA optimizations
  - Decouple the FTQ resolveQueue enqueue logic from the redirect flush logic to avoid an overly long timing path caused by chaining the two ([#6239](https://github.com/OpenXiangShan/XiangShan/pull/6239))
  - Remove the ICache wayLookup bypass logic to avoid the SRAM2SRAM timing path from metaArray to dataArray ([#6044](https://github.com/OpenXiangShan/XiangShan/pull/6044))
  - Postpone the ICache parity check logic to avoid an overly long timing path caused by performing the check immediately after the dataArray SRAM output ([#5733](https://github.com/OpenXiangShan/XiangShan/pull/5733))
- Debugging tools
  - Add several rolling counters to analyze how performance metrics change over time ([#6193](https://github.com/OpenXiangShan/XiangShan/pull/6193))

### Backend

- Bug fixes
  - (V2) Fix the reset values of `mstatus.MDT` and `mnstatus.NMIE`, the behavior of writes of 0 to `mnstatus.NMIE`, and the `m/siprios` mask logic ([#6100](https://github.com/OpenXiangShan/XiangShan/pull/6100))
  - (V3) Sync the fixes related to `mstatus.MDT` and `mnstatus.NMIE` ([#6223](https://github.com/OpenXiangShan/XiangShan/pull/6223))
  - (V2) Fix CSR behavior for RISC-V Debug Spec 1.0, including the trigger version, `dcsr.NMIP` updates, and `dcsr.CAUSE` priority ([#6104](https://github.com/OpenXiangShan/XiangShan/pull/6104))
  - (V2) Fix the VSEI priority-index mapping in `vstopi` ([#6131](https://github.com/OpenXiangShan/XiangShan/pull/6131))
- Debugging tools
  - (V2) Add `cpu_cycle` and `ref_cpu_cycle` performance events, and add async bridging for the system-counter path ([#6180](https://github.com/OpenXiangShan/XiangShan/pull/6180))
  - (V2) Fix the accounting condition for the `frontend_stall_cycle` performance event and add `backend_stall_cycle` accounting ([#6121](https://github.com/OpenXiangShan/XiangShan/pull/6121))
- Code synchronization
  - (V3) Cherry-pick recent V2 backend fixes to V3, including CSR, interrupt, PMP/PMA, debug-mode, and performance-event fixes ([#6243](https://github.com/OpenXiangShan/XiangShan/pull/6243))

### MemBlock and Cache

- RTL features
  - Add support for pre-allocated StoreQueue entries ([#5834](https://github.com/OpenXiangShan/XiangShan/pull/5834))
  - Add fast wakeup support in LoadQueueReplay for C_MA and C_FF ([#6092](https://github.com/OpenXiangShan/XiangShan/pull/6092))
  - Change the L1-L2 TileLink bus to dual-port to reduce blocking between the two cache levels ([XSCache #16](https://github.com/OpenXiangShan/XSCache/pull/16))
- Bug fixes
  - Fix incorrect s3 hit-metadata updates when LoadPipe is killed in s2 ([#6185](https://github.com/OpenXiangShan/XiangShan/pull/6185))
  - Fix the empty-check logic for Sbuffer CMO drain ([#6183](https://github.com/OpenXiangShan/XiangShan/pull/6183))
  - Fix the `nMaxPrefetchEntry` logic in MissQueue ([#6197](https://github.com/OpenXiangShan/XiangShan/pull/6197))
  - Fix `cbo.zero` writes to Sbuffer ([#6228](https://github.com/OpenXiangShan/XiangShan/pull/6228))
  - Remove an incorrect XSError from MissQueue ([#6241](https://github.com/OpenXiangShan/XiangShan/pull/6241))

### XSAI

- Bug fixes
  - Fix the control signals for load/store whole C instructions ([XSAI #86](https://github.com/OpenXiangShan/XSAI/pull/86))
- RTL features
  - Support configurable multi-channel memory access in CUTE ([XSAI #83](https://github.com/OpenXiangShan/XSAI/pull/83))
  - Replace coupledL2/huancun/openLLC with the XSAICache repository for the cache system ([XSAI #85](https://github.com/OpenXiangShan/XSAI/pull/85))
- Code quality
  - Add switches to control recently added debug output in CUTE ([CUTE #24](https://github.com/OpenXiangShan/CUTE/pull/24), [CUTE #27](https://github.com/OpenXiangShan/CUTE/pull/27))
- Debugging tools
  - Analyze the lifecycle of a uop using traces ([XSAI #84](https://github.com/OpenXiangShan/XSAI/pull/84))

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
