---
slug: biweekly-84-en
date: 2025-09-01
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 84] 20250901

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 84th issue of the biweekly report.

<!-- In the last two weeks, frontend continues V3 RTL development, while exploring BP design in simulator. Backend and memory subsystem fix some bugs in V2. In the meantime, backend makes some preparations for V3 RTL development, mainly including some code clean-up and fontend-backend IO refactor. -->

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
  - Fix uBTB training non-jump branches ([#4977](https://github.com/OpenXiangShan/XiangShan/pull/4977))
- Model exploration
  - Debug SC implementable solutions
  - Adjust PHR implementation to avoid simulation performance degradation
- Code quality
  - Refactor IFU code

### Backend

- RTL feature
  - fix the source of standard uop's number of write back registers（[#4944](https://github.com/OpenXiangShan/XiangShan/pull/4944)）
- Bug fix
  - (V2) add software check exception caused by Zicfilp to exception priority（[#4923](https://github.com/OpenXiangShan/XiangShan/pull/4923)）
  - (V2) fix DPC register related issues（[#4979](https://github.com/OpenXiangShan/XiangShan/pull/4979)）


### MemBlock and Cache

- RTL feature
  - L2 directory updates moved from mainpipe stage 3 to stage 4
  - The refactoring of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - Adjust the fullva bit width of the tlb req to pass the complete vaddr for the virtual address check ([#4954](https://github.com/OpenXiangShan/XiangShan/pull/4954))
  - Fix the mismatch of reference and dut when execute segment fault only first instruction, which should be written back to the vl CSR ([#4956](https://github.com/OpenXiangShan/XiangShan/pull/4956))
  - Fix X-prop in PTW caused by using uninitialized stage1Hit signal in Mux ([#4916](https://github.com/OpenXiangShan/XiangShan/pull/4916))

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.95  | 433.milc         | 45.09  |
| 429.mcf           | 60.19  | 434.zeusmp       | 51.78  |
| 445.gobmk         | 30.62  | 435.gromacs      | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII       | 73.27  |
| 471.omnetpp       | 41.35  | 450.soplex       | 52.50  |
| 473.astar         | 29.30  | 453.povray       | 53.49  |
| 483.xalancbmk     | 72.76  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.66  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.73  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.63  |
|                   |        | 482.sphinx3      | 49.10  |
|                   |        | GEOMEAN          | 44.94  |

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
| Commit         | ef913a6    |
| Date           | 08/14/2025 |
| L1 ICache      | 64KB       |
| L1 DCache      | 64KB       |
| L2 Cache       | 1MB        |
| L3 Cache       | 16MB       |
| LSU            | 3ld2st     |
| Bus protocol   | TileLink   |
| Memory latency | DDR4-3200  |

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
