---
slug: biweekly-65-en
date: 2024-12-09
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 65】20241209

Welcome to XiangShan biweekly column, this is the 65th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption. In addition, the frontend fixed incorrect flushing of iTLB in certain situations, the backend fixed calculation errors in scalar/vector half-precision floating-point extensions (Zfh/Zvfh) functional units, and the memory and cache subsystem fixed the bug that a TLB corresponding item is replaced during guest page fault processing. This update also includes the latest performance improvements of the Kunminghu architecture.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed the issue where all instructions were marked as fault when crossing MMIO/non-MMIO boundaries ([#3963](https://github.com/OpenXiangShan/XiangShan/pull/3963))
    - Fixed incorrect flushing of iTLB in certain situations ([#3996](https://github.com/OpenXiangShan/XiangShan/pull/3996))

- **Area**
    - Split and reduced higher bits of ITTAGE target addresses ([#3935](https://github.com/OpenXiangShan/XiangShan/pull/3935))

### Backend

- **Bug Fixes**
    - Fixed calculation errors in scalar/vector half-precision floating-point extensions (Zfh/Zvfh) functional units ([#3939](https://github.com/OpenXiangShan/XiangShan/pull/3939), [#3932](https://github.com/OpenXiangShan/XiangShan/pull/3932)).
    - Fixed incorrect behavior of `menvcfg.DTE` controlling `xstatus.SDT` read/write ([#3981](https://github.com/OpenXiangShan/XiangShan/pull/3981), [#3955](https://github.com/OpenXiangShan/XiangShan/pull/3955)).
    - Fixed an issue where `old vd` was incorrectly eliminated when `vstart` was 0 ([#3948](https://github.com/OpenXiangShan/XiangShan/pull/3948)).
    - Fixed synchronization issues between CSR and IMSIC access ([#3989](https://github.com/OpenXiangShan/XiangShan/pull/3989)).
    - Fixed read/write issues with custom PMA CSR registers ([#3966](https://github.com/OpenXiangShan/XiangShan/pull/3966)).
    - Fixed incorrect vector exception information being set during interrupts ([#3990](https://github.com/OpenXiangShan/XiangShan/pull/3990)).
    - Fixed an issue where some vector instructions incorrectly set `vs.dirty` ([#3965](https://github.com/OpenXiangShan/XiangShan/pull/3965)).
    - Fixed a bug in the interrupt delegation mode of NEMU：([#708](https://github.com/OpenXiangShan/NEMU/pull/708))
    - Removed the restriction in XiangShan where accessing S-mode custom CSRs in VS mode results in an illegal instruction. The access to custom content will now be controlled by the Smstateen extension：([#3978](https://github.com/OpenXiangShan/XiangShan/pull/3978))，NEMU has also completed the corresponding modification and fixed the CSR permission checks when the Smstateen extension is enabled：（[#692](https://github.com/OpenXiangShan/NEMU/pull/692)）

- **Timing/Area Optimization**
    - Moved the vector exception detection module from 6 simple decoders into a single complex decoder ([#3961](https://github.com/OpenXiangShan/XiangShan/pull/3961)).
    - Optimized AIA interrupt priority selection logic and fixed CSR timing ([#3946](https://github.com/OpenXiangShan/XiangShan/pull/3946)).

- **RVA23 Profile**
    - NEMU supports the Atomic Compare-and-Swap (Zacas) extension（[#709](https://github.com/OpenXiangShan/NEMU/pull/709)）, the Zacas extension is being merged into the XiangShan mainline([#3958](https://github.com/OpenXiangShan/XiangShan/pull/3958))
    - Added supported instruction base and extension information to the parameter list and device tree ([#3986](https://github.com/OpenXiangShan/XiangShan/pull/3986), [#3953](https://github.com/OpenXiangShan/XiangShan/pull/3953)).

### MemBlock and cache

- **RVA23 Profile**
  - CMO: Add custom CMO operations to the TileLink bus and complete the processing path for CMO operations between L1 DCache and L2 ([#3968](https://github.com/OpenXiangShan/XiangShan/pull/3968))
  - RAS:
    - The implementation of ECC fault injection instructions in L1 DCache has been completed and validated through self-test cases, with ECC enabled by default ([#3925](https://github.com/OpenXiangShan/XiangShan/pull/3925))
    - The implementation of L2 Cache ECC (error detection) has been completed. L2 Cache and OpenLLC (CHI version) now support Poison and DataCheck ([#3808](https://github.com/OpenXiangShan/XiangShan/pull/3808))
  - Svpbmt: Code implementation of Svpbmt and outstanding uncache load / stores completed, and already merged into master ([#3900](https://github.com/OpenXiangShan/XiangShan/pull/3900))
  - Zicclsm: Refactored misaligned hardware path and completed the support for vector misalign requests. Already finished the code and is prepared to be merged into master ([#3994](https://github.com/OpenXiangShan/XiangShan/pull/3994))

- **Bug fixes**
  - Fix the bug that a TLB corresponding item is replaced during guest page fault processing ([#3964](https://github.com/OpenXiangShan/XiangShan/pull/3964), [#3985](https://github.com/OpenXiangShan/XiangShan/pull/3985))
  - Fix the bug that a vset instruction cannot handle interrupts during flushPipe, setting vset instructions not to respond to interrupts ([#3991](https://github.com/OpenXiangShan/XiangShan/pull/3991))
  - Fix error when NEMU handles cross-page address translation ([NEMU #710](https://github.com/OpenXiangShan/NEMU/pull/710))

- **PPA Optimizations**
  - Timing: Optimize the hit path selection logic of DCache and improve the timing paths related to CMO operations ([#3988](https://github.com/OpenXiangShan/XiangShan/pull/3988))
  - Area：
    - Remove redundant combinational logic from LoadQueueReplay/StoreQueue ([#3976](https://github.com/OpenXiangShan/XiangShan/pull/3976))
    - MMU area reduction: Trim the number of entries in the MMU page cache from 2k to 1k, and performance has slightly decreased ([#4003](https://github.com/OpenXiangShan/XiangShan/pull/4003))
  - Power: Complete the RTL code for single-core power-off and currently testing the single-core power-off process

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit a60d667 from December 6** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.10  | 410.bwaves        | 67.07  |
| 401.bzip2         | 25.53  | 416.gamess        | 42.95  |
| 403.gcc           | 47.17  | 433.milc          | 45.29  |
| 429.mcf           | 58.86  | 434.zeusmp        | 56.75  |
| 445.gobmk         | 30.30  | 435.gromacs       | 37.44  |
| 456.hmmer         | 40.79  | 436.cactusADM     | 49.30  |
| 458.sjeng         | 30.22  | 437.leslie3d      | 45.29  |
| 462.libquantum    | 124.56 | 444.namd          | 34.65  |
| 464.h264ref       | 57.72  | 447.dealII        | 74.37  |
| 471.omnetpp       | 40.11  | 450.soplex        | 54.63  |
| 473.astar         | 29.14  | 453.povray        | 54.95  |
| 483.xalancbmk     | 73.25  | 454.Calculix      | 18.33  |
| **GEOMEAN**       | 44.61  | 459.GemsFDTD      | 40.22  |
|                   |        | 465.tonto         | 37.99  |
|                   |        | 470.lbm           | 102.47 |
|                   |        | 481.wrf           | 43.22  |
|                   |        | 482.sphinx3       | 53.26  |
|                   |        | **GEOMEAN**       | 47.48  |

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
