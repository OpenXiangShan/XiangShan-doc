---
slug: biweekly-58-en
date: 2024-09-02
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 58】20240902

Welcome to XiangShan biweekly column, this is the 58th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently: WIP

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed a design flaw related to software prefetching transitions in the prefetchPipe s1 level state machine. ([#3433](https://github.com/OpenXiangShan/XiangShan/pull/3433))
    - Fixed the frontend Topdown simulation counters and hardware PMU.  ([#3437](https://github.com/OpenXiangShan/XiangShan/pull/3437))

### Backend

- **Bug Fixes**
    - Continued progress on bug fixes, with a total of XX bugs fixed. Below are some of the PRs:
    - Fixed bugs related to the H extension ([#3450](https://github.com/OpenXiangShan/XiangShan/pull/3450), [#3447](https://github.com/OpenXiangShan/XiangShan/pull/3447), [#3442](https://github.com/OpenXiangShan/XiangShan/pull/3442), [#3428](https://github.com/OpenXiangShan/XiangShan/pull/3428), [#3427](https://github.com/OpenXiangShan/XiangShan/pull/3427), [#3423](https://github.com/OpenXiangShan/XiangShan/pull/3423), [#3420](https://github.com/OpenXiangShan/XiangShan/pull/3420), [#3397](https://github.com/OpenXiangShan/XiangShan/pull/3397), [#3385](https://github.com/OpenXiangShan/XiangShan/pull/3385))
    - Fixed bugs related to the Debug extension ([#3441](https://github.com/OpenXiangShan/XiangShan/pull/3441), [#3422](https://github.com/OpenXiangShan/XiangShan/pull/3422), [#3418](https://github.com/OpenXiangShan/XiangShan/pull/3418), [#3395](https://github.com/OpenXiangShan/XiangShan/pull/3395))
    - Fixed bugs related to the V extension ([#3430](https://github.com/OpenXiangShan/XiangShan/pull/3430), [#3384](https://github.com/OpenXiangShan/XiangShan/pull/3384))

- **Timing Optimization**
    - Continued progress on timing optimization, with internal timing violations improved by -50ps, now -15ps away from the target.
    - Removed some `loadCancel` signals in the DataPath ([#3457](https://github.com/OpenXiangShan/XiangShan/pull/3457)).
    - Changed the writeback signal of `v0` and `vl` register files to direct register output ([#3387](https://github.com/OpenXiangShan/XiangShan/pull/3387)).

- **RVA23 Profile**
    - The Additional Floating-Point instructions extension (Zfa) is being merged into the master ([#3439](https://github.com/OpenXiangShan/XiangShan/pull/3439)).
    - Support for Minimal Half-Precision Floating Point extension (Zfhmin) ([#3421](https://github.com/OpenXiangShan/XiangShan/pull/3421)).
    - Support for Sstval/Shvstval (saving the corresponding instruction encoding in the tval CSR during illegal instruction exceptions) ([#3407](https://github.com/OpenXiangShan/XiangShan/pull/3407)).
    - The Resumable Non-Maskable Interrupt (Smrnmi) extension is being merged into the mainline.

### MemBlock and cache


- **CHI Bus**
    - Conducting functional design and code implementation for the CHI to AXI4 bridge
    - Adds a switch for CHI asynchronous bridge and CLINT asynchronous bridge, which is parameterized by SoCParameters. ([#3459](https://github.com/OpenXiangShan/XiangShan/pull/3459))

- **RVA23 Profile**
    - CMO Implementation: Fixed several bugs and successfully passed simple XiangShan system instruction tests. Merged CMO instruction extensions Zicbom into master（[#3426](https://github.com/OpenXiangShan/XiangShan/pull/3426)）
    - Software prefetching (Zicbop) extension: optimises timing related to software instruction prefetching ([#3425](https://github.com/OpenXiangShan/XiangShan/pull/3425)).
    - 48-bit virtual memory management (Sv48) extension: fixes bugs related to 48-bit physical addresses, now passes the 48-bit physical address self-test use case ([#3424](https://github.com/OpenXiangShan/XiangShan/pull/3424)).

- **Performance**
    - TP meta on L2 migration to new master, conduct performance evaluation
    - A series of performance bugs caused by frequent failures to seize the load issue queue have been discovered and are being analysed and fixed.

- Bug fixes
    - Fixed a bug where LoadReplayQueue could not be queued, resulting in loss of load instructions ([#3436](https://github.com/OpenXiangShan/XiangShan/pull/3436)).
    - Add AXI4Error peripheral to enable SoC to recognise illegal address and return non-data error to CPU in simulation environment. And also fix the bug of mtval update error in store access fault ([#3458](https://github.com/OpenXiangShan/XiangShan/pull/3458))
    - Fix bugs related to vector access with unaligned addresses, currently only scalar load & store instructions can handle unaligned requests in hardware, vector load & store instructions still need to report exceptions to be handled by software ([#3460](https://github.com/OpenXiangShan/XiangShan/pull/3460)), ([#3462](https://github.com/OpenXiangShan/XiangShan/pull/3462))

- **PPA Optimizations**
    - On the L2 Cache, using SRAM to build a Queue and splitting the data SRAM. Timing evaluation is normal, and area has been optimized, but increase in power consumption is significant
    - Continuing to fix the critical path in MemBlock, mainly by simplifying the DCache MSHR queuing logic, optimising the path for LDU s0, and breaking the ready cascade logic for long pipelines (vector address generation modules). Ready to merge into master ([#3467](https://github.com/OpenXiangShan/XiangShan/pull/3467))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC06 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPEC06FP set to fast. The instruction set used was RV64GCB. We ran SPEC06 fragments on the XiangShan processor **version 49162c9 from August 24** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPECCPU 2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 33.66  | 410.bwaves        | 76.67  |
| 401.bzip2         | 24.99  | 416.gamess        | 43.33  |
| 403.gcc           | 47.90  | 433.milc          | 42.42  |
| 429.mcf           | 58.75  | 434.zeusmp        | 59.01  |
| 445.gobmk         | 30.17  | 435.gromacs       | 37.87  |
| 456.hmmer         | 40.28  | 436.cactusADM     | 47.68  |
| 458.sjeng         | 29.72  | 437.leslie3d      | 46.13  |
| 462.libquantum    | 127.00 | 444.namd          | 34.34  |
| 464.h264ref       | 56.62  | 447.dealII        | 73.80  |
| 471.omnetpp       | 41.22  | 450.soplex        | 54.63  |
| 473.astar         | 29.09  | 453.povray        | 55.70  |
| 483.xalancbmk     | 75.13  | 454.Calculix      | 18.15  |
| **GEOMEAN**       | 44.18  | 459.GemsFDTD      | 37.00  |
|                   |        | 465.tonto         | 35.73  |
|                   |        | 470.lbm           | 101.16 |
|                   |        | 481.wrf           | 42.20  |
|                   |        | 482.sphinx3       | 51.45  |
|                   |        | **GEOMEAN**       | 47.15  |

**The scores above are estimated based on SimPoint checkpoints, not a full SPEC CPU 2006 estimation, and may differ from the actual performance of the real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao

Reviewer: XiangShan Publicity Team
