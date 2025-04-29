---
slug: biweekly-75-en
date: 2025-04-28
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 75】20250428

Welcome to XiangShan biweekly column, this is the 75th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- **Area**

### Backend

- **Bug Fixes**
    - Fixed an issue where the highest priority result selection for the `xtopi` CSR was incorrect ([#4571](https://github.com/OpenXiangShan/XiangShan/pull/4571)).
    - Filtered out read-only CSRs from `regOut` ([#4412](https://github.com/OpenXiangShan/XiangShan/pull/4412)).
    - Fixed an issue where instructions in `singlestep` mode did not stop before entering the exception handler ([#4629](https://github.com/OpenXiangShan/XiangShan/pull/4629)).
    - Fixed an issue where the WFI timeout counter overflowed when WFI was configured to wait indefinitely, incorrectly causing a critical error ([#4623](https://github.com/OpenXiangShan/XiangShan/pull/4623)).
    - Fixed an issue where RNMI interrupts failed to wake up WFI instructions ([#4645](https://github.com/OpenXiangShan/XiangShan/pull/4645)).
    - Enabled the CPU clock upon receiving a debug halt request ([#4583](https://github.com/OpenXiangShan/XiangShan/pull/4583)).
    - Fixed incorrect trace parameter settings ([#4561](https://github.com/OpenXiangShan/XiangShan/pull/4561)).
    - Fixed `imsic` incorrectly triggering illegal exceptions ([#4546](https://github.com/OpenXiangShan/XiangShan/pull/4546)).
    - Fixed `xiselect` minimum range settings ([#4594](https://github.com/OpenXiangShan/XiangShan/pull/4594)).
    - Fixed an issue where younger vector memory exceptions incorrectly overwrote older exceptions ([#4570](https://github.com/OpenXiangShan/XiangShan/pull/4570)).
    - Fixed PC high bit calculation errors during difftest ([#4632](https://github.com/OpenXiangShan/XiangShan/pull/4632)).
    - Fixed an overflow issue of the ROB commit pointer in extreme cases ([#4642](https://github.com/OpenXiangShan/XiangShan/pull/4642)).

### MemBlock and cache

- **Bug fixes**
  - Fixed a deadlock bug in the simulation environment when using AXI4Memory with continuous writes of burst=1 ([#4611](https://github.com/OpenXiangShan/XiangShan/pull/4611))
  - Fixed several bugs in StoreQueue related to the dequeue logic for uncache stores ([#4641](https://github.com/OpenXiangShan/XiangShan/pull/4641))
  - Fixed a bug in cbo.zero where RAW violation checks were not performed at cacheline granularity ([#4592](https://github.com/OpenXiangShan/XiangShan/pull/4592))
  - Fixed a bug where misaligned loads erroneously triggered RAR/RAW violation checks during replay ([#4580](https://github.com/OpenXiangShan/XiangShan/pull/4580))
  - Fixed a bug in certain corner cases where ECC errors were not reported correctly ([#4572](https://github.com/OpenXiangShan/XiangShan/pull/4572))
  - Fixed a bug in vector EMUL<1 misaligned unit-stride instructions where element index calculation was wrong, causing incorrect exception information ([#4593](https://github.com/OpenXiangShan/XiangShan/pull/4593))
  - Prevent software prefetch instructions from generating uncache-address accesses, avoiding false-positive exceptions ([#4636](https://github.com/OpenXiangShan/XiangShan/pull/4636))
  - Fixed a deadlock bug in DCache under intensive same-set access scenarios ([#4622](https://github.com/OpenXiangShan/XiangShan/pull/4622))
  - Changed MMIO-path exceptions to be reported as Hardware Errors instead of Access Faults ([#4619](https://github.com/OpenXiangShan/XiangShan/pull/4619))
  - Fixed several bugs in PTW and LLPTW modules related to exception handling during MMU page-table walks ([#4586](https://github.com/OpenXiangShan/XiangShan/pull/4586)), ([#4596](https://github.com/OpenXiangShan/XiangShan/pull/4596)), ([#4597](https://github.com/OpenXiangShan/XiangShan/pull/4597))
  - Fixed two bugs in L1 TLB related to the virtualization extensions ([#4587](https://github.com/OpenXiangShan/XiangShan/pull/4587)), ([#4588](https://github.com/OpenXiangShan/XiangShan/pull/4588))
  - Fix handling logic for tag verification errors in the L2 Cache ([CoupledL2 #399](https://github.com/OpenXiangShan/CoupledL2/pull/399))
  - Fix bug where the TX linkactive channel is not deactivated when exiting coherency in the L2 Cache ([CoupledL2 #407](https://github.com/OpenXiangShan/CoupledL2/pull/407))

- **PPA Optimizations**
  - Optimized the redundant enqueue logic of the uncacheBuffer in the LoadQueue to improve timing ([#4603](https://github.com/OpenXiangShan/XiangShan/pull/4603))
  - Adjust tag and data SRAM specifications in the L2 Cache ([CoupledL2 #402](https://github.com/OpenXiangShan/CoupledL2/pull/402)), ([CoupledL2 #405](https://github.com/OpenXiangShan/CoupledL2/pull/405))

- **Tools**
  - Add support for multiple time input formats in CLog.B ([OpenLLC #62](https://github.com/OpenXiangShan/OpenLLC/pull/62))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 6683fc4 from April 25** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.90  | 410.bwaves        | 66.86  |
| 401.bzip2         | 25.51  | 416.gamess        | 40.88  |
| 403.gcc           | 47.87  | 433.milc          | 45.17  |
| 429.mcf           | 59.56  | 434.zeusmp        | 52.09  |
| 445.gobmk         | 30.31  | 435.gromacs       | 33.66  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.52  | 437.leslie3d      | 45.90  |
| 462.libquantum    | 122.43 | 444.namd          | 28.88  |
| 464.h264ref       | 56.58  | 447.dealII        | 73.57  |
| 471.omnetpp       | 41.42  | 450.soplex        | 52.63  |
| 473.astar         | 29.30  | 453.povray        | 53.39  |
| 483.xalancbmk     | 72.95  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.58  | 459.GemsFDTD      | 35.68  |
|                   |        | 465.tonto         | 36.68  |
|                   |        | 470.lbm           | 91.19  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.54  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao