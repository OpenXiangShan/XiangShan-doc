---
slug: biweekly-73-en
date: 2025-03-31
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 73】20250331

Welcome to XiangShan biweekly column, this is the 73rd issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption.

Additionally, we have also made public the repository for the **XiangShan Open Source Processor User Guide**: [https://github.com/OpenXiangShan/XiangShan-User-Guide](https://github.com/OpenXiangShan/XiangShan-User-Guide) and its corresponding webpage: [https://docs.xiangshan.cc/projects/user-guide/](https://docs.xiangshan.cc/projects/user-guide/), as well as the repository for the **XiangShan Open Source Processor Design Document**: [https://github.com/OpenXiangShan/XiangShan-Design-Doc](https://github.com/OpenXiangShan/XiangShan-Design-Doc) and its corresponding webpage: [https://docs.xiangshan.cc/projects/design/](https://docs.xiangshan.cc/projects/design/). We welcome everyone to read and ask questions.

<!-- more -->

## Recent developments

### Frontend

- **Bug Fixes**

  - Fixed instruction prefetch pipeline handling of high address exceptions ([#4423](https://github.com/OpenXiangShan/XiangShan/pull/4423))

- **Timing/Area Optimizations**
  - A series of SRAM partitioning ([#4468](https://github.com/OpenXiangShan/XiangShan/pull/4468)), ([#4360](https://github.com/OpenXiangShan/XiangShan/pull/4360)), ([#4485](https://github.com/OpenXiangShan/XiangShan/pull/4485))

### Backend

- **Bug Fixes**
  - Fixed an issue where instruction fusion was not blocked when a trigger fired and an exception occurred ([#4439](https://github.com/OpenXiangShan/XiangShan/pull/4439)).
  - Further fixed stalls caused by the `amocas.q` instruction ([#4435](https://github.com/OpenXiangShan/XiangShan/pull/4435)).
  - Fixed the FusionDecoder incorrectly outputting valid fusion information when disabled ([#4456](https://github.com/OpenXiangShan/XiangShan/pull/4456)).
  - Fixed an issue where non-register interrupt pending status was not properly synchronized in the difftest framework after reset ([#4449](https://github.com/OpenXiangShan/XiangShan/pull/4449)).
  - Fixed various issues related to the ChiselAIA integration ([#4449](https://github.com/OpenXiangShan/XiangShan/pull/4449)).

### MemBlock and cache

- **Bug fixes**

  - Fix a series of bugs in the MMU related to high-address checking, exception handling, and Svnapot extension ([#4422](https://github.com/OpenXiangShan/XiangShan/pull/4422)), ([#4448](https://github.com/OpenXiangShan/XiangShan/pull/4448)), ([#4453](https://github.com/OpenXiangShan/XiangShan/pull/4453)), ([#4454](https://github.com/OpenXiangShan/XiangShan/pull/4454)), ([#4455](https://github.com/OpenXiangShan/XiangShan/pull/4455)), ([#4471](https://github.com/OpenXiangShan/XiangShan/pull/4471)), ([#4472](https://github.com/OpenXiangShan/XiangShan/pull/4472)), ([#4473](https://github.com/OpenXiangShan/XiangShan/pull/4473))
  - Fix the bug in NEMU for multi-core ref when virtualization is enabled ([NEMU #835](https://github.com/OpenXiangShan/NEMU/pull/835))
  - Fix several bugs in scenarios combining uncache, misaligned accesses, and exceptions ([#4426](https://github.com/OpenXiangShan/XiangShan/pull/4426)), ([#4441](https://github.com/OpenXiangShan/XiangShan/pull/4441)), ([#4442](https://github.com/OpenXiangShan/XiangShan/pull/4442))
  - Fix the bug in NEMU where atomic instructions and misaligned memory accesses did not trigger exceptions when PBMT changed memory attributes from cacheable to IO/NC ([NEMU #833](https://github.com/OpenXiangShan/NEMU/pull/833))
  - Fix several consistency issues in CoupledL2 that violated the CHI protocol ([CoupledL2 #390](https://github.com/OpenXiangShan/CoupledL2/pull/390)), ([CoupledL2 #392](https://github.com/OpenXiangShan/CoupledL2/pull/392)), ([CoupledL2 #395](https://github.com/OpenXiangShan/CoupledL2/pull/395))
  - Add check for the WFI (Wait For Interrupt) state before the L2 Cache exits the coherency ([CoupledL2 #385](https://github.com/OpenXiangShan/CoupledL2/pull/385))
  - Fix several issues related to the handling of the RespErr field in the CHI protocol ([CoupledL2 #384](https://github.com/OpenXiangShan/CoupledL2/pull/384)), ([CoupledL2 #394](https://github.com/OpenXiangShan/CoupledL2/pull/394))

- Timing/Area Optimizations
  - Adjust L2 Cache SRAM (tag) specifications ([CoupledL2 #388](https://github.com/OpenXiangShan/CoupledL2/pull/388)); add SRAM control interface ([CoupledL2 #389](https://github.com/OpenXiangShan/CoupledL2/pull/389))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 0e64db5 from March 28** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

**Note: The performance evaluation code version for this biweekly are the same as the last biweekly, and will be updated with the latest scores in the next biweekly.**

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.85  | 410.bwaves       | 66.93  |
| 401.bzip2         | 25.49  | 416.gamess       | 40.90  |
| 403.gcc           | 46.64  | 433.milc         | 45.30  |
| 429.mcf           | 58.07  | 434.zeusmp       | 51.77  |
| 445.gobmk         | 30.25  | 435.gromacs      | 33.65  |
| 456.hmmer         | 41.60  | 436.cactusADM    | 46.21  |
| 458.sjeng         | 30.39  | 437.leslie3d     | 45.99  |
| 462.libquantum    | 122.51 | 444.namd         | 28.88  |
| 464.h264ref       | 56.56  | 447.dealII       | 73.41  |
| 471.omnetpp       | 39.51  | 450.soplex       | 51.98  |
| 473.astar         | 29.22  | 453.povray       | 53.43  |
| 483.xalancbmk     | 71.97  | 454.Calculix     | 16.37  |
| **GEOMEAN**       | 44.13  | 459.GemsFDTD     | 36.38  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.22  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 48.59  |
|                   |        | **GEOMEAN**      | 44.53  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
- XiangShan Documentation: https://xiangshan-doc.readthedocs.io/
- XiangShan User Guide: https://docs.xiangshan.cc/projects/user-guide/
- XiangShan Design Doc: https://docs.xiangshan.cc/projects/design/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao
