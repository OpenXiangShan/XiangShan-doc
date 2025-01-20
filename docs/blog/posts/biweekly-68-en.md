---
slug: biweekly-68-en
date: 2025-01-20
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 68】20250120

Welcome to XiangShan biweekly column, this is the 68th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Power**
    - Added the option to separately gate the two clocks of the dual-port SRAM, with the default setting being not to gate them separately ([#4125](https://github.com/OpenXiangShan/XiangShan/pull/4125))

### Backend

- **Bug Fixes**
    - Fixed an issue where `xTIP` (clock interrupt pending bit) failed to update, causing erroneous interrupts ([#4157](https://github.com/OpenXiangShan/XiangShan/pull/4157)).
    - Fixed a boundary condition where `rob` failed to flush entries during a redirect ([#4153](https://github.com/OpenXiangShan/XiangShan/pull/4153)).
    - Added initialization for the `htimedelta` CSR to prevent errors from software reading uninitialized values ([#4145](https://github.com/OpenXiangShan/XiangShan/pull/4145)).
    - Fixed missing output connections for `mnret` signals ([#4194](https://github.com/OpenXiangShan/XiangShan/pull/4194)).
    - Added missing permission checks for the AIA extension ([#4166](https://github.com/OpenXiangShan/XiangShan/pull/4166)).
    - Refactored CSR access exceptions, dividing responsibilities among multiple modules ([#4146](https://github.com/OpenXiangShan/XiangShan/pull/4146)).
    - Fixed an issue where snapshot selection failed under extreme conditions during redirection ([#4197](https://github.com/OpenXiangShan/XiangShan/pull/4197)).
    - Fixed incorrect masking in unordered reduction instructions ([#4197](https://github.com/OpenXiangShan/XiangShan/pull/4197)).
    - Fixed incorrect data selection for `f16` in reduction instructions ([#4181](https://github.com/OpenXiangShan/XiangShan/pull/4181)).

- **Debug Module**
    - Added `hartReset` functionality, allowing selected cores to be restarted during multi-core debugging ([#4134](https://github.com/OpenXiangShan/XiangShan/pull/4134)).

- **Tools**
    - Added synthesizable three-level classification Top-Down counters ([#4122](https://github.com/OpenXiangShan/XiangShan/pull/4122)).
    - Introduced two custom CSR registers, `mcorepwd` and `mflushpwd`, to control power ([#4164](https://github.com/OpenXiangShan/XiangShan/pull/4164)).

### MemBlock and cache

- **Features**
    - Add support for uncache buffer merging new requests ([#4154](https://github.com/OpenXiangShan/XiangShan/pull/4154))

- **CHI Bus**
    - Added support for the new Snoop transaction SnpQuery in Issue E.b ([CoupledL2 #323](https://github.com/OpenXiangShan/CoupledL2/pull/323))
    - Added code isolation for different CHI versions ([CoupledL2 #333](https://github.com/OpenXiangShan/CoupledL2/pull/333)), ([CoupledL2 #315](https://github.com/OpenXiangShan/CoupledL2/pull/315))
    - Added support for DataCheck and Poison for UC situations, and corrected their initialization options ([CoupledL2 #329](https://github.com/OpenXiangShan/CoupledL2/pull/329)), ([CoupledL2 #335](https://github.com/OpenXiangShan/CoupledL2/pull/335)), ([CoupledL2 #337](https://github.com/OpenXiangShan/CoupledL2/pull/337))

- **Prefetch**
    - Added CSR register control for L2 Cache prefetch ([CoupledL2 #324](https://github.com/OpenXiangShan/CoupledL2/pull/324))


- **Bug fixes**
    - Fixed two bugs in PageCache and itlbRepeater causing X-state propagation ([#4174](https://github.com/OpenXiangShan/XiangShan/pull/4174)), ([#4195](https://github.com/OpenXiangShan/XiangShan/pull/4195))
    - Fixed the bug of MMU stuck when MissQueue is full under high pressure ([#4191](https://github.com/OpenXiangShan/XiangShan/pull/4191)), ([#4202](https://github.com/OpenXiangShan/XiangShan/pull/4202))
    - Fixed a bug in StoreQueue where a vector store instruction was not flushed successfully ([#4139](https://github.com/OpenXiangShan/XiangShan/pull/4139))
    - Fixed issue where SnpStash did not probe L1 under specific conditions ([CoupledL2 #326](https://github.com/OpenXiangShan/CoupledL2/pull/326))
    - Fixed a series of WriteEvictOrEvict related bugs ([CoupledL2 #311](https://github.com/OpenXiangShan/CoupledL2/pull/311)), ([CoupledL2 #316](https://github.com/OpenXiangShan/CoupledL2/pull/316)), ([CoupledL2 #327](https://github.com/OpenXiangShan/CoupledL2/pull/327))
    - Fixed a series of CMO related bugs ([CoupledL2 #317](https://github.com/OpenXiangShan/CoupledL2/pull/317)), ([CoupledL2 #325](https://github.com/OpenXiangShan/CoupledL2/pull/325))
    - Fixed CCID incorrect assignment issue ([CoupledL2 #330](https://github.com/OpenXiangShan/CoupledL2/pull/330))


- **PPA Optimizations**
    - Timing
        - Changed some key signals in the Load Unit to be directly output from registers ([#4144](https://github.com/OpenXiangShan/XiangShan/pull/4144))
        - Optimized the data write-back generation logic in the Load Unit ([#4167](https://github.com/OpenXiangShan/XiangShan/pull/4167))
        - Optimized the critical path of the SRAM exit to register gating signals in the L2 Cache ([CoupledL2 #321](https://github.com/OpenXiangShan/CoupledL2/pull/321))

    - Area
        - Reduced the number of LQReplay entries, and when the LQReplay occupancy reaches a certain threshold, the IQ will dispatch the oldest load ([#4183](https://github.com/OpenXiangShan/XiangShan/pull/4183))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 718a93f from January 6** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

Note: The performance evaluation code version for this biweekly are the same as the last biweekly, and will be updated with the latest scores in the next biweekly on February 3rd.

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.70  | 410.bwaves        | 66.96  |
| 401.bzip2         | 25.54  | 416.gamess        | 40.91  |
| 403.gcc           | 46.68  | 433.milc          | 45.37  |
| 429.mcf           | 58.12  | 434.zeusmp        | 52.23  |
| 445.gobmk         | 30.35  | 435.gromacs       | 33.70  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.19  |
| 458.sjeng         | 30.38  | 437.leslie3d      | 46.16  |
| 462.libquantum    | 122.52 | 444.namd          | 28.91  |
| 464.h264ref       | 56.63  | 447.dealII        | 73.40  |
| 471.omnetpp       | 39.51  | 450.soplex        | 52.24  |
| 473.astar         | 29.23  | 453.povray        | 53.39  |
| 483.xalancbmk     | 72.11  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.15  | 459.GemsFDTD      | 36.94  |
|                   |        | 465.tonto         | 36.71  |
|                   |        | 470.lbm           | 91.19  |
|                   |        | 481.wrf           | 40.63  |
|                   |        | 482.sphinx3       | 48.59  |
|                   |        | **GEOMEAN**       | 44.62  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao
