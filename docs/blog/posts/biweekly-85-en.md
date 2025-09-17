---
slug: biweekly-85-en
date: 2025-09-01
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 85] 20250915

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 85th issue of the biweekly report.

In this biweekly report, we are excited to announce the release of the XiangShan Compiler Collection (XSCC). Built on the LLVM framework, XSCC is a high-performance compiler optimized for open-source high-performance RISC-V processor XiangShan. It focuses on microarchitecture-level performance enhancement strategies such as memory access optimization, branch prediction improvement, loop unrolling, and automatic vectorization. Currently, XSCC 1.0 is developed based on LLVM 19.1.0.

This release is the XSCC v1.0 binary distribution package, providing a cross-compiler for RISC-V (generating riscv64 target code). It can run on hosts with Ubuntu 22.04 or above (x86_64), with glibc as the default C standard library. The distribution package can be downloaded from the GitHub Releases page: <https://github.com/OpenXiangShan/xscc/releases>.

From this issue onwards, we will include performance data of SPEC 2006 compiled with XSCC for your reference.

In the past two weeks, the V3 frontend refactoring is nearly complete, with each BPU adapted to the new frontend framework, and corresponding modifications made to the backend. The memory access and cache team mainly fixed some bugs in V2 while developing new tools.

<!-- more -->

## Recent Developments

### Frontend

- RTL feature
  - Support resolve update BPU ([#4962](https://github.com/OpenXiangShan/XiangShan/pull/4962))
  - Support dynamic fetch block size in ICache to save power and prepare for 64B fetch block ([#4999](https://github.com/OpenXiangShan/XiangShan/pull/4999))
  - Optimize mbtb and abtb replacement algorithm, using SRAM-based PLRU to save area ([#4964](https://github.com/OpenXiangShan/XiangShan/pull/4964))
  - Implement ITTAGE in V3 BPU ([#5000](https://github.com/OpenXiangShan/XiangShan/pull/5000), [#5020](https://github.com/OpenXiangShan/XiangShan/pull/5020))
  - Optimize PHR update mechanism ([#4995](https://github.com/OpenXiangShan/XiangShan/pull/4995))
  - TAGE-SC development is ongoing, not merged yet ([#5001](https://github.com/OpenXiangShan/XiangShan/pull/5001))
- Bug fix
  - Fix some bugs triggered by resolve update
    - Fix the incorrect IFU redirection of a cross-fetch-block non-cfi (control-flow instruction) predicted as cfi (Merged with [#4962](https://github.com/OpenXiangShan/XiangShan/pull/4962))
    - Assist in fixing the backend branchUnit's incorrect branch target address calculation (Merged with [#4962](https://github.com/OpenXiangShan/XiangShan/pull/4962))
    - Fix ubtb multi-hit issue caused by wrong update condition ([#5004](https://github.com/OpenXiangShan/XiangShan/pull/5004), [#5008](https://github.com/OpenXiangShan/XiangShan/pull/5008))
    - Fix IBuffer's incorrect passing of identifiedCfi ([#5019](https://github.com/OpenXiangShan/XiangShan/pull/5019))
- Model exploration
  - Analyze the TAGE implementation, fix two performance issues, now align with CBP
- Code quality
  - Refactor IFU and IBuffer to use V3 frontend parameter system ([#4975](https://github.com/OpenXiangShan/XiangShan/pull/4975), [#5013](https://github.com/OpenXiangShan/XiangShan/pull/5013))
  - Simplify mbtb parameters ([#4987](https://github.com/OpenXiangShan/XiangShan/pull/4987))

### Backend

- Bug Fix
  - Backend should provide start pc of the FTQ entry.（[#5017](https://github.com/OpenXiangShan/XiangShan/pull/5017)）
  - Fix isRVC transfer logic for new ftqoffset （[#5003](https://github.com/OpenXiangShan/XiangShan/pull/5003)）

### MemBlock and Cache

- RTL feature
  - (V2) In the MMIOBridge of CoupledL2, the CLINT address range has been excluded from xstilewrap’s mapping and reconfigured to integrate a private CLINT IP ([CoupledL2 #429](https://github.com/OpenXiangShan/CoupledL2/pull/429))
  - The refactoring of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
  - Refactored the memory access unit of NEMU, including code cleanup and the addition of new V3 features
- Bug fix
  - (V2) Fix an issue where ITLB freeze when receiving PWT response in particular cycles ([#4983](https://github.com/OpenXiangShan/XiangShan/pull/4983))
  - (V2) Add first_s2xlate_fault init when LLPTW handle jmp_bitmap_check reques to prevent issues when L2TLB handles both allStage and noS2xlate requests in same time ([#4996](https://github.com/OpenXiangShan/XiangShan/pull/4996))
  - (V2) Fix the implementation error of prefetch hit counter that caused the recorded number of prefetch hits to exceed the number of prefetch requests ([#5005](https://github.com/OpenXiangShan/XiangShan/pull/5005))
  - (V2) Fix address generation error during misaligned memory access splitting in VSegment ([#5006](https://github.com/OpenXiangShan/XiangShan/pull/5006))
  - (V2) Fix unnecessary bitmap check logic in LLPTW ([#0518](https://github.com/OpenXiangShan/XiangShan/commit/143ba1cb97fa43bdbd199b34deae21bd52c9adfe))
- Tools
  - Support noise generation for anvil mode in tl-test-new ([tl-test-new #80](https://github.com/OpenXiangShan/tl-test-new/pull/80))
  - Support generating binary-format CHI logs in CoupledL2’s TestTop to reduce log file size ([CoupledL2 #410](http://github.com/OpenXiangShan/CoupledL2/pull/410))

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.89  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.96  | 433.milc         | 45.10  |
| 429.mcf           | 59.97  | 434.zeusmp       | 51.83  |
| 445.gobmk         | 30.63  | 435.gromacs      | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.94  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.63  |
| 471.omnetpp       | 41.50  | 450.soplex       | 52.48  |
| 473.astar         | 29.30  | 453.povray       | 53.49  |
| 483.xalancbmk     | 72.79  | 454.Calculix     | 16.38  |
| GEOMEAN           | 44.67  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.64  |
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

The SPEC 2006 performance data compiled with XSCC is as follows:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 36.33  | 410.bwaves       | 68.97  |
| 401.bzip2         | 25.74  | 416.gamess       | 44.43  |
| 403.gcc           | 35.70  | 433.milc         | 68.07  |
| 429.mcf           | 61.14  | 434.zeusmp       | 51.66  |
| 445.gobmk         | 30.81  | 435.gromacs      | 30.72  |
| 456.hmmer         | 46.74  | 436.cactusADM    | 66.66  |
| 458.sjeng         | 32.19  | 437.leslie3d     | 49.47  |
| 462.libquantum    | 268.14 | 444.namd         | 34.47  |
| 464.h264ref       | 61.02  | 447.dealII       | 80.67  |
| 471.omnetpp       | 36.09  | 450.soplex       | 52.26  |
| 473.astar         | 28.41  | 453.povray       | 55.62  |
| 483.xalancbmk     | 78.27  | 454.Calculix     | 33.00  |
| GEOMEAN           | 47.25  | 459.GemsFDTD     | 53.37  |
|                   |        | 465.tonto        | 29.55  |
|                   |        | 470.lbm          | 121.32 |
|                   |        | 481.wrf          | 36.72  |
|                   |        | 482.sphinx3      | 51.93  |
|                   |        | GEOMEAN          | 50.97  |

Compilation parameters are as follows:

|                    |                        |
| ------------------ | ---------------------- |
| Compiler           | XSCC 1.0               |
| Optimization level | O3                     |
| Memory library     | jemalloc               |
| -march             | rv64gc_zba_zbb_zbs_zbc |
| Other Parameters   | -ffast-math, -flto     |

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
