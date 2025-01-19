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
