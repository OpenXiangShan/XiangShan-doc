---
slug: biweekly-61-en
date: 2024-10-14
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 61】20241014

Welcome to XiangShan biweekly column, this is the 61th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed a bug where the `gpaddr` was incorrectly dropped due to a cross-page instruction fetching ([#3719](https://github.com/OpenXiangShan/XiangShan/pull/3719))
    - Fixed an issue where arithmetic instructions in the Zcb extension were incorrectly identified as illegal instructions ([#3721](https://github.com/OpenXiangShan/XiangShan/pull/3721) OpenXiangShan/rocket-chip [#14](https://github.com/OpenXiangShan/rocket-chip/pull/14))

### Backend

- **Bug Fixes**
    - Continued advancing bug fixes, with critical and severe bugs converging in the current version:
    - Fixed the vtype recovery error in consecutive redirects ([#3705](https://github.com/OpenXiangShan/XiangShan/pull/3705))
    - Fixed a series of read/write and permission check errors in CSR registers ([#3717](https://github.com/OpenXiangShan/XiangShan/pull/3717), [#3701](https://github.com/OpenXiangShan/XiangShan/pull/3701), [#3700](https://github.com/OpenXiangShan/XiangShan/pull/3700), [#3703](https://github.com/OpenXiangShan/XiangShan/pull/3703))
    - Fixed the error where RTL did not correctly guide the update of `mip.LCOFIP` in NEMU ([#3710](https://github.com/OpenXiangShan/XiangShan/pull/3710), [#572](https://github.com/OpenXiangShan/XiangShan/pull/572))
    - Fixed vector memory access exception handling errors ([#3722](https://github.com/OpenXiangShan/XiangShan/pull/3722), [#3720](https://github.com/OpenXiangShan/XiangShan/pull/3720), [#3714](https://github.com/OpenXiangShan/XiangShan/pull/3714), [#3704](https://github.com/OpenXiangShan/XiangShan/pull/3704), [#3702](https://github.com/OpenXiangShan/XiangShan/pull/3702), [#3695](https://github.com/OpenXiangShan/XiangShan/pull/3695))
    - Fixed the issue where `vfslide1up/down` did not trigger an illegal instruction exception when `mstatus.FS` was off ([#3696](https://github.com/OpenXiangShan/XiangShan/pull/3696))

- **Timing/Power Optimization**
    - Plan to restructure the LoadDependency design: by reworking the `ldcancel` dependency chain cancel logic, optimize the timing within the issue queue, and aim to increase issue queue capacity.

- **RVA23 Profile**
    - Debug extension supports `mcontrol6`, deprecating `mcontrol` to enable hardware breakpoint debugging for the H extension ([#3693](https://github.com/OpenXiangShan/XiangShan/pull/3693))
    - Smrnmi extension: provides two types of NMI interrupts and offers interrupt line interfaces ([#3691](https://github.com/OpenXiangShan/XiangShan/pull/3691))

### MemBlock and cache


- **CHI Bus**
  - OpenLLC: Performance degradation occurred when CHI-L3 was connected to the SoC, and the issue was traced to the concurrency of the bridge
  - CHI Bridge: OpenNCB supports concurrency of more than 15 memory requests; under the OpenNCB + CMN600 framework, it supports up to 45 concurrent memory requests in a dual-core scenario

- **RVA23 Profile**
 - Continuing to improve support for vector vstart, trigger, and the implementation of vector load & store first-only-first instructions, as well as fixing a number of bugs. These have been merged into master ([#3690](https://github.com/OpenXiangShan/XiangShan/pull/3690))

- **Bug fixes**
  - Fix handling logic of guest page fault on prefetch requests, and situations when redirect after gpf ([#3697](https://github.com/OpenXiangShan/XiangShan/pull/3697)).
  - Fix bug where non-aligned requests did not successfully write gpaddr to htval or mtval2 register ([#3699](https://github.com/OpenXiangShan/XiangShan/pull/3699))
  - Fix bug with unaligned AMO instructions on NEMU

- **PPA Optimizations**
  - Optimise TLB physical placement and critical paths releated to TagArray in MemBlock, internal timing violation optimised to -47ps
  - Adjusted CoupledL2 port constraints, L2 internal timing violations optimised to about -60ps

- **Tool**
  - Performance Counters: Coupled L2 HPM integrated into XiangShan CSR, with optimized output format ([#3708](https://github.com/OpenXiangShan/XiangShan/pull/3708))
  - CHIron (CHI Log): Completed the design and implementation of the binary format, improving record file size and parsing speed

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC06 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPEC06FP set to fast. The instruction set used was RV64GCB. We ran SPEC06 checkpoints on the XiangShan processor **version 75dea01 from October 12** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.87  | 410.bwaves        | 75.03  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.49  |
| 403.gcc           | 46.48  | 433.milc          | 43.59  |
| 429.mcf           | 57.44  | 434.zeusmp        | 56.84  |
| 445.gobmk         | 30.16  | 435.gromacs       | 37.40  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 48.59  |
| 458.sjeng         | 30.23  | 437.leslie3d      | 43.70  |
| 462.libquantum    | 125.15 | 444.namd          | 34.69  |
| 464.h264ref       | 57.82  | 447.dealII        | 74.58  |
| 471.omnetpp       | 39.69  | 450.soplex        | 54.58  |
| 473.astar         | 29.00  | 453.povray        | 56.00  |
| 483.xalancbmk     | 74.77  | 454.Calculix      | 18.32  |
| **GEOMEAN**       | 44.47  | 459.GemsFDTD      | 37.98  |
|                   |        | 465.tonto         | 38.18  |
|                   |        | 470.lbm           | 102.01 |
|                   |        | 481.wrf           | 42.59  |
|                   |        | 482.sphinx3       | 52.55  |
|                   |        | **GEOMEAN**       | 47.40  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao

Reviewer: XiangShan Publicity Team
