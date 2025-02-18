---
slug: biweekly-70-en
date: 2025-02-17
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 70】20250217

Welcome to XiangShan biweekly column, this is the 70th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed the Call/Ret condition judgment in RAS during redirection ([#4232](https://github.com/OpenXiangShan/XiangShan/pull/4232))
    - Added independent check for JALR target in pre-decode ([#4234](https://github.com/OpenXiangShan/XiangShan/pull/4234))
    - Added JALR position check in pre-decode ([#4269](https://github.com/OpenXiangShan/XiangShan/pull/4269))

- **Timing**
    - Advanced MSHR selection on ICache miss path for 1 cycle ([#4173](https://github.com/OpenXiangShan/XiangShan/pull/4173))
    - Advanced ITTAGE region table read for 1 cycle ([#4216](https://github.com/OpenXiangShan/XiangShan/pull/4216))
    - Removed some Clock Gating with poor timing ([#4223](https://github.com/OpenXiangShan/XiangShan/pull/4223))

### Backend

- **Bug Fixes**
    - Fixed an issue where some instruction information was lost in hardware performance counters ([#4257](https://github.com/OpenXiangShan/XiangShan/pull/4257)).
    - Fixed an issue where the `scountovf` register was not controlled by `counteren` during reads ([#4267](https://github.com/OpenXiangShan/XiangShan/pull/4267)).
    - Fixed an issue where writing to the `mcontrol6` register’s `dmode` field did not account for trigger chaining ([#4256](https://github.com/OpenXiangShan/XiangShan/pull/4256)).
    - Fixed incorrect `fflags` generation in unordered vector reduction sum operations ([#4244](https://github.com/OpenXiangShan/XiangShan/pull/4244)).

- **RVA23 Profile**
    - Added support for the Wait-on-reservation-set instructions extension (Zawrs) ([#4211](https://github.com/OpenXiangShan/XiangShan/pull/4211)).

### MemBlock and cache

- **RVA23 Profile**

- **CHI Bus**
    - Issue C is now supported in CoupledL2 and SoC with OpenLLC + OpenNCB ([CoupledL2 #333](https://github.com/OpenXiangShan/CoupledL2/pull/333)), ([OpenLLC #47](https://github.com/OpenXiangShan/OpenLLC/pull/47)), ([OpenNCB #3](https://github.com/OpenXiangShan/OpenNCB/pull/3)).
    - Completed modifications for low power policy control and submitted a PR, currently refining the code ([#4236](https://github.com/OpenXiangShan/XiangShan/pull/4236)), ([CoupledL2 #348](https://github.com/OpenXiangShan/CoupledL2/pull/348)).

- **Bug fixes**
    - Fixed two bugs related to uncache merge and uncache load replay ([#4268](https://github.com/OpenXiangShan/XiangShan/pull/4268)), ([#4275](https://github.com/OpenXiangShan/XiangShan/pull/4275)).
    - Resolved corner cases in virtualization scenarios with onlyStage1 or onlyStage2, and addressed X-state propagation issues in MMU ([#4252](https://github.com/OpenXiangShan/XiangShan/pull/4252)), ([#4253](https://github.com/OpenXiangShan/XiangShan/pull/4253)), ([#4266](https://github.com/OpenXiangShan/XiangShan/pull/4266)).
    - Fixed multiple bugs related to cbo instructions, including flushing, exception handling, and violation checks ([#4262](https://github.com/OpenXiangShan/XiangShan/pull/4262)).
    - Patched a bug where amo_cmp was not passed to MSHR after a CAS request missed ([#4272](https://github.com/OpenXiangShan/XiangShan/pull/4272)).
    - Resolved four bugs in unaligned memory access, including exception handling, violation checks, and false wakeups ([#4227](https://github.com/OpenXiangShan/XiangShan/pull/4227)), ([#4228](https://github.com/OpenXiangShan/XiangShan/pull/4228)), ([#4239](https://github.com/OpenXiangShan/XiangShan/pull/4239)), ([#4263](https://github.com/OpenXiangShan/XiangShan/pull/4263)).
    - Fixed two bugs of PMA: missing PMA configuration and prefetch instruction permission checks ([#4226](https://github.com/OpenXiangShan/XiangShan/pull/4226)), ([#4235](https://github.com/OpenXiangShan/XiangShan/pull/4235)).
    - Fixed a bug where the WriteEvictOrEvict response state did not comply with the manual standard ([CoupledL2 #352](https://github.com/OpenXiangShan/CoupledL2/pull/352)).
    - Fixed a bug where the SnqQuery response state did not meet consistency requirements when SnqQuery was nested within Evict ([CoupledL2 #353](https://github.com/OpenXiangShan/CoupledL2/pull/353)).
    - Fixed a series of bugs related to DataCheck and Poison ([CoupledL2 #335](https://github.com/OpenXiangShan/CoupledL2/pull/335)), ([CoupledL2 #337](https://github.com/OpenXiangShan/CoupledL2/pull/337)), ([CoupledL2 #339](https://github.com/OpenXiangShan/CoupledL2/pull/339)).


## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 7f475a2 from February 14** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 66.62  |
| 401.bzip2         | 25.55  | 416.gamess        | 40.91  |
| 403.gcc           | 46.67  | 433.milc          | 45.21  |
| 429.mcf           | 58.13  | 434.zeusmp        | 51.96  |
| 445.gobmk         | 30.34  | 435.gromacs       | 33.61  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.26  |
| 458.sjeng         | 30.50  | 437.leslie3d      | 46.10  |
| 462.libquantum    | 122.57 | 444.namd          | 28.91  |
| 464.h264ref       | 56.66  | 447.dealII        | 73.69  |
| 471.omnetpp       | 39.35  | 450.soplex        | 52.00  |
| 473.astar         | 29.24  | 453.povray        | 53.42  |
| 483.xalancbmk     | 72.01  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.17  | 459.GemsFDTD      | 36.01  |
|                   |        | 465.tonto         | 36.74  |
|                   |        | 470.lbm           | 91.18  |
|                   |        | 481.wrf           | 40.62  |
|                   |        | 482.sphinx3       | 48.61  |
|                   |        | **GEOMEAN**       | 44.52  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao
