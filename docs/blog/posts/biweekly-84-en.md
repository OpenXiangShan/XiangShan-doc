---
slug: biweekly-84-en
date: 2025-09-01
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 84] 20250901

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 84th issue of the biweekly report.

In this issue, we are very pleased to share some news. Lanxin Computing has successfully launched Linux on an 8-core SoC built on the recently delivered Kunminghu V2 IP core, completing 8-core consistency verification. In the next phase, we will continue to work closely with Lanxin Computing to carry out 32-core consistency verification and performance optimization.

Over the past two weeks, the frontend team has continued V3 development, with the first phase of refactoring nearing completion. The backend and memory/cache teams have steadily advanced V3 exploration and code refactoring, while also fixing a series of V2 bugs.

From this issue onwards, we will periodically include timing, area, and power consumption data for the XiangShan processor for your reference.

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Optimize IFU instruction marking and cross-block instruction concatenation logic ([#4961](https://github.com/OpenXiangShan/XiangShan/pull/4961))
    - Use the latter 2B of the instruction to mark it (`pc + 2` for 4B instructions or `pc` for 2B instructions)
    - When a single 4B instruction crosses the boundry of the fetch block, cache it in IFU and wait for next fetch request to do concatenation, instead of reading extra 2B from ICache
  - Optimize FTQ redirect logic: When a redirection request flushes an FTQ slot to empty, write new entry into that empty slot instead of allocating a new one ([#4939](https://github.com/OpenXiangShan/XiangShan/pull/4939))
  - Drop cross-page fetch support in ICache and IFU ([#4909](https://github.com/OpenXiangShan/XiangShan/pull/4909), [#4989](https://github.com/OpenXiangShan/XiangShan/pull/4989))
  - Optimize mBTB multi-hit handling logic ([#4984](https://github.com/OpenXiangShan/XiangShan/pull/4984))
  - TAGE, ITTAGE, branch resolve update, etc. are under ongoing development, we'll see them soon
- Bug fix
  - (V2) Fix X-state propagation issue caused by SRAM read/write conflicts in FTB ([#4971](https://github.com/OpenXiangShan/XiangShan/pull/4971))
  - Fix X-state propagation issues caused by BPU prediction starting before SRAM initialization ([#4968](https://github.com/OpenXiangShan/XiangShan/pull/4968))
  - Fix uBTB training not-taken branches ([#4977](https://github.com/OpenXiangShan/XiangShan/pull/4977))
- Model exploration
  - Debug SC implementable solutions
  - Adjust PHR implementation to avoid simulation performance degradation
- Code quality
  - Refactor IFU code

### Backend

- RTL feature
  - Fix the source of standard uop's number of write back registers（[#4944](https://github.com/OpenXiangShan/XiangShan/pull/4944)）
- Bug fix
  - (V2) Add software check exception caused by Zicfilp to exception priority（[#4923](https://github.com/OpenXiangShan/XiangShan/pull/4923)）
  - (V2) Fix DPC register related issues（[#4979](https://github.com/OpenXiangShan/XiangShan/pull/4979)）

### MemBlock and Cache

- RTL feature
  - Move L2 directory updates from MainPipe stage 3 to stage 4
  - The refactoring of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - (V2) Adjust the `fullva` port width of the TLB request to pass the full virtual address for its check ([#4954](https://github.com/OpenXiangShan/XiangShan/pull/4954))
  - (V2) Fix the mismatch of reference and DUT when execute segment fault only first instruction, which should be written back to the `vl` CSR ([#4956](https://github.com/OpenXiangShan/XiangShan/pull/4956))
  - (V2) Fix X-state propagation in PTW caused by using uninitialized `stage1Hit` signal in Mux ([#4916](https://github.com/OpenXiangShan/XiangShan/pull/4916))

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.90  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.50  | 416.gamess       | 41.01  |
| 403.gcc           | 47.89  | 433.milc         | 45.10  |
| 429.mcf           | 60.18  | 434.zeusmp       | 51.83  |
| 445.gobmk         | 30.48  | 435.gromacs      | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.87  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.63  |
| 471.omnetpp       | 41.50  | 450.soplex       | 52.48  |
| 473.astar         | 29.30  | 453.povray       | 53.49  |
| 483.xalancbmk     | 72.79  | 454.Calculix     | 16.38  |
| GEOMEAN           | 44.66  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.78  |
|                   |        | 482.sphinx3      | 49.13  |
|                   |        | GEOMEAN          | 44.97  |

We use SimPoint to sample programs and create checkpoints images based on our custom format. The coverage of SimPoint clustering reaches 100%. Note that the above scores are estimated based on program segments rather than a complete SPEC CPU2006 evaluation, which may deviate from the actual performance of real chips.

Compilation parameters are as follows:

|                    |          |
| ------------------ | -------- |
| Compiler           | gcc12    |
| Optimization level | O3       |
| Memory library     | jemalloc |
| -march             | RV64GCB  |
| -ffp-contraction   | fast     |

Processor and SoC parameters are as follows:

|                |            |
| -------------- | ---------- |
| Commit         | b2daf0a    |
| Date           | 08/29/2025 |
| L1 ICache      | 64KB       |
| L1 DCache      | 64KB       |
| L2 Cache       | 1MB        |
| L3 Cache       | 16MB       |
| LSU            | 3ld2st     |
| Bus protocol   | TileLink   |
| Memory latency | DDR4-3200  |

## Power and Area

|                      | Frequency (GHz) | Cell Area (mm2) | FP Area (mm2) | Power (W) |
| -------------------- | --------------- | --------------- | ------------- | --------- |
| Frontend             | 2.8             | 0.18            | 0.28          | 0.39      |
| Backend              | 2.8             | 0.37            | 0.57          | 0.68      |
| Memblock             | 2.8             | 0.30            | 0.46          | 0.47      |
| L2 (512KB)           | 2.8             | 0.39            | 0.55          | 0.11      |
| XiangShan (Hierachy) | 2.8             | 1.24            | 1.86          | 1.65      |
| XiangShan (Flatten)  | 2.7             | 1.23            | 1.73          | 1.63      |

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
