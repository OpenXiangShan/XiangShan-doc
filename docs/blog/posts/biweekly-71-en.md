---
slug: biweekly-71-en
date: 2025-03-03
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 71】20250303

Welcome to XiangShan biweekly column, this is the 71st issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption. In addition, the frontend modified RAS overflow behavior to avoid potential deadlocks, the backend enabled out-of-order execution for more `CSRR` read instructions, and the memory and cache subsystem fixed legacy issues related to exception detection and writeback wakeup on misaligned accesses.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Modified RAS overflow behavior to avoid potential deadlocks ([#4317](https://github.com/OpenXiangShan/XiangShan/pull/4317))

### Backend

- **Bug Fixes**
    - Fixed an issue where `xtval` and `epc` were incorrectly updated when adjacent interrupts/exceptions were triggered ([#4307](https://github.com/OpenXiangShan/XiangShan/pull/4307)).
    - Fixed an inconsistency in updating backup information for the `mhpmevent` register ([#4321](https://github.com/OpenXiangShan/XiangShan/pull/4321)).
    - Fixed an issue where MMIO accesses to the `debugmodule` incorrectly excluded the `debugmodule` address space ([#4324](https://github.com/OpenXiangShan/XiangShan/pull/4324)).
    - Removed redundant modules from the new dispatch design and eliminated unused hardware performance counter interfaces ([#4288](https://github.com/OpenXiangShan/XiangShan/pull/4288)).
    - Fixed an issue in the Spike simulator where `vsatp` writes were not restricted based on `hgatp.mode` ([Spike #86](https://github.com/OpenXiangShan/riscv-isa-sim/pull/86)).

- **Performance Optimizations**
    - Added support for `vlbusytable` to eliminate `oldvd` in the new dispatch module ([#4198](https://github.com/OpenXiangShan/XiangShan/pull/4198)).
    - Enabled out-of-order execution for more `CSRR` read instructions ([#4128](https://github.com/OpenXiangShan/XiangShan/pull/4128)).

### MemBlock and cache

- **Bug Fixes**
    - Fix legacy issues related to exception detection and writeback wakeup on misaligned accesses ([#4333](https://github.com/OpenXiangShan/XiangShan/pull/4333))
    - Fix bug where uncache requests did not raise an exception when the address was misaligned ([#4304](https://github.com/OpenXiangShan/XiangShan/pull/4304))
    - Fix bug where incorrect uncache flush handling caused a deadlock ([#4300](https://github.com/OpenXiangShan/XiangShan/pull/4300))
    - Fix bug where the LR instruction prematurely released blocking on subsequent LR instructions ([#4337](https://github.com/OpenXiangShan/XiangShan/pull/4337))

- **RVA23 Profile**
    - RAS
        - Set ECC error check to trigger the NMI_31 interrupt ([#4335](https://github.com/OpenXiangShan/XiangShan/pull/4335))
        - Fix bug where ECC fault injection instruction caused multiple DCache hits ([#4285](https://github.com/OpenXiangShan/XiangShan/pull/4285))
        - Fix bug where an invalid DCache MSHR forwarded corrupt signal to LDU ([#4292](https://github.com/OpenXiangShan/XiangShan/pull/4292))
        - Add a series of missing error handling in the L2 Cache ([CoupledL2 #355](https://github.com/OpenXiangShan/CoupledL2/pull/355), [CoupledL2 #357](https://github.com/OpenXiangShan/CoupledL2/pull/357), [CoupledL2 #368](https://github.com/OpenXiangShan/CoupledL2/pull/368))

- **CHI Bus**
    - Add handling for blocking CMO transactions by Snoop ([CoupledL2 #370](https://github.com/OpenXiangShan/CoupledL2/pull/370))
    - Fix a series of nested issues related to Snoop ([CoupledL2 #351](https://github.com/OpenXiangShan/CoupledL2/pull/351), [CoupledL2 #358](https://github.com/OpenXiangShan/CoupledL2/pull/358), [CoupledL2 #369](https://github.com/OpenXiangShan/CoupledL2/pull/369))
    - Add basic support for CHI Issue C version ([#4298](https://github.com/OpenXiangShan/XiangShan/pull/4298))


## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 7f475a2 from February 14** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

**Note: The performance evaluation code version for this biweekly are the same as the last biweekly, and will be updated with the latest scores in the next biweekly.**

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
