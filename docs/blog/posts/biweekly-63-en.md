---
slug: biweekly-63-en
date: 2024-11-11
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 63】20241111

Welcome to XiangShan biweekly column, this is the 63th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption. In addition, the frontend added reset for FTB pred_data register, the backend merged VS/S/M Mode Double Trap Extension (Ss/mdbltrp) into master, and the memory and cache subsystem fixed the bug in CMO.clean/flush operations when there is an L1 miss and an L2 hit. This update also includes the latest performance improvements of the Kunminghu architecture.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Added reset for FTB pred_data register ([#3628](https://github.com/OpenXiangShan/XiangShan/pull/3628)).
    - Prevent prefetch when backend redirects with exceptions ([#3787](https://github.com/OpenXiangShan/XiangShan/pull/3787)).

- **Performance**
    - Indirect jumps that never change target do not use the ITTAGE indirect predictor ([#3718](https://github.com/OpenXiangShan/XiangShan/pull/3718)).

- **Power**
    - No updates when FTB is disabled ([#3543](https://github.com/OpenXiangShan/XiangShan/pull/3543)).


### Backend

- **Bug Fixes**
    - Fixed issues related to Debug mode:
        - Fixed an issue where an extra instruction was committed after a redirect when stepping ([#3828](https://github.com/OpenXiangShan/XiangShan/pull/3828))
        - Fixed the issue where the debug interrupt could not respond when `nmie` was 0 ([#3826](https://github.com/OpenXiangShan/XiangShan/pull/3826))
        - Fixed incorrect `mtval` updates when an atomic access triggered a breakpoint exception in trigger mode ([#3803](https://github.com/OpenXiangShan/XiangShan/pull/3803))
    - Fixed incomplete assignment in the `mip` register ([#3827](https://github.com/OpenXiangShan/XiangShan/pull/3827))
    - Fixed the issue where the XStrap instruction did not correctly halt simulation ([#3848](https://github.com/OpenXiangShan/XiangShan/pull/3848)), with corresponding updates in NEMU ([#639](https://github.com/OpenXiangShan/NEMU/pull/639))
    - Fixed an issue where the correct privilege level was not entered after virtual interrupt injection ([#3812](https://github.com/OpenXiangShan/XiangShan/pull/3812))
    - NEMU fixed issues such as incorrect decoding, failing to trigger illegal instruction exceptions ([#646](https://github.com/OpenXiangShan/NEMU/pull/646), [#628](https://github.com/OpenXiangShan/NEMU/pull/628), [#645](https://github.com/OpenXiangShan/NEMU/pull/645))

- **Timing/Area Optimization**
    - Eliminated the `old vd` operand when reading the `vl` state ([#3847](https://github.com/OpenXiangShan/XiangShan/pull/3847))
    - Removed redundant parameter variables in ROB entries ([#3833](https://github.com/OpenXiangShan/XiangShan/pull/3833))

- **RVA23 Profile**
    - **VS/S/M Mode Double Trap Extension (Ss/mdbltrp):** Merged into master ([#3789](https://github.com/OpenXiangShan/XiangShan/pull/3789))
    - Added support for critical-error checks and entering the critical-error state ([#3793](https://github.com/OpenXiangShan/XiangShan/pull/3793), [#3835](https://github.com/OpenXiangShan/XiangShan/pull/3835))
    - Initial support for Pause Hint Extension (Zihintpause) ([#3823](https://github.com/OpenXiangShan/XiangShan/pull/3823))
    - **Scalar/Vector Half-Precision Floating-Point Extension:** Merged into master ([#3840](https://github.com/OpenXiangShan/XiangShan/pull/3840))
    - NEMU supports icount/itrigger checks when acting as REF ([#614](https://github.com/OpenXiangShan/NEMU/pull/614))

### MemBlock and cache

- **CHI Bus**
    - By increasing the concurrency of the CHI bridge to align with the TL version, the performance of the SPEC CPU2006 libquantum benchmark improves; however, performance for other benchmarks still shows significant regression
    - Completed integration of OpenLLC (CHI-based L3 Cache), and OpenNCB (CHI-to-AXI bridge) with XiangShan, already merged into master ([#3672](https://github.com/OpenXiangShan/XiangShan/pull/3672))

- **Bug fixes**
    - Fix the bug in CMO.clean/flush operations when there is an L1 miss and an L2 hit ([#3814](https://github.com/OpenXiangShan/XiangShan/pull/3814))
    - Fix a bug that mcause is set wrongly when non-aligned load / store instructions access mmio space ([NEMU #650](https://github.com/OpenXiangShan/NEMU/pull/650))
    - Fix a bug that gpaddr written to *tval is wrong when guest page fault occurs in unaligned load / store instructions ([#3809](https://github.com/OpenXiangShan/XiangShan/pull/3809)), ([#3822](https://github.com/OpenXiangShan/XiangShan/pull/3822))
    - Fix a bug that gpaddr written to *tval is truncated when guest page fault occurs in instruction fetch ([#3795](https://github.com/OpenXiangShan/XiangShan/pull/3795))

- **PPA Optimizations**
    - Discuss a series of area optimisation points in MemBlock, including queue entries reduction, redundant logic removal, functional unit merging, and so on.

- **Tool**
    - TL-Test verification framework: Add a test environment for CMO in tl-test-new, enabling the execution of CMO transactions on tl-test-new ([#3804](https://github.com/OpenXiangShan/XiangShan/pull/3804))
    - Add PC and RobIdx information to DiffTest store event to aid in debugging ([difftest #499](https://github.com/OpenXiangShan/difftest/pull/499))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit fbdb359 from November 8** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.17  | 410.bwaves        | 76.73  |
| 401.bzip2         | 25.55  | 416.gamess        | 43.51  |
| 403.gcc           | 47.25  | 433.milc          | 44.07  |
| 429.mcf           | 58.61  | 434.zeusmp        | 56.96  |
| 445.gobmk         | 30.29  | 435.gromacs       | 37.46  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 49.48  |
| 458.sjeng         | 30.27  | 437.leslie3d      | 44.93  |
| 462.libquantum    | 124.52 | 444.namd          | 34.73  |
| 464.h264ref       | 57.82  | 447.dealII        | 75.09  |
| 471.omnetpp       | 39.74  | 450.soplex        | 54.54  |
| 473.astar         | 29.00  | 453.povray        | 56.03  |
| 483.xalancbmk     | 74.59  | 454.Calculix      | 18.35  |
| **GEOMEAN**       | 44.64  | 459.GemsFDTD      | 37.94  |
|                   |        | 465.tonto         | 38.21  |
|                   |        | 470.lbm           | 102.06 |
|                   |        | 481.wrf           | 43.45  |
|                   |        | 482.sphinx3       | 53.21  |
|                   |        | **GEOMEAN**       | 47.75  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/
* OpenLLC: https://github.com/OpenXiangShan/OpenLLC

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao

Reviewer: XiangShan Publicity Team
