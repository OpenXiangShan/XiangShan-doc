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

- **RVA23 Profile**

- **CHI Bus**
    - Added support for the new Snoop transaction SnpQuery in Issue E.b ([CoupledL2 #323](https://github.com/OpenXiangShan/CoupledL2/pull/323))
    - Added code isolation for different CHI versions ([CoupledL2 #333](https://github.com/OpenXiangShan/CoupledL2/pull/333)), ([CoupledL2 #315](https://github.com/OpenXiangShan/CoupledL2/pull/315))
    - Added support for DataCheck and Poison for UC situations, and corrected their initialization options ([CoupledL2 #329](https://github.com/OpenXiangShan/CoupledL2/pull/329)), ([CoupledL2 #335](https://github.com/OpenXiangShan/CoupledL2/pull/335)), ([CoupledL2 #337](https://github.com/OpenXiangShan/CoupledL2/pull/337))

- **Prefetch**
    - Added CSR register control for L2 Cache prefetch ([CoupledL2 #324](https://github.com/OpenXiangShan/CoupledL2/pull/324))


- **Bug fixes**
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

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 80%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 9cd76b2 from January 17** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.15  | 410.bwaves        | 65.59  |
| 401.bzip2         | 26.51  | 416.gamess        | 40.64  |
| 403.gcc           | 47.06  | 433.milc          | 46.76  |
| 429.mcf           | 60.09  | 434.zeusmp        | 51.84  |
| 445.gobmk         | 30.40  | 435.gromacs       | 32.88  |
| 456.hmmer         | 41.51  | 436.cactusADM     | 46.27  |
| 458.sjeng         | 30.88  | 437.leslie3d      | 47.09  |
| 462.libquantum    | 122.82 | 444.namd          | 29.23  |
| 464.h264ref       | 57.24  | 447.dealII        | 70.14  |
| 471.omnetpp       | 38.93  | 450.soplex        | 52.85  |
| 473.astar         | 31.07  | 453.povray        | 53.44  |
| 483.xalancbmk     | 72.45  | 454.Calculix      | 16.42  |
| **GEOMEAN**       | 44.68  | 459.GemsFDTD      | 35.52  |
|                   |        | 465.tonto         | 36.44  |
|                   |        | 470.lbm           | 91.43  |
|                   |        | 481.wrf           | 39.76  |
|                   |        | 482.sphinx3       | 48.53  |
|                   |        | **GEOMEAN**       | 44.38  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao
