---
slug: biweekly-74-en
date: 2025-04-14
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 74】20250414

Welcome to XiangShan biweekly column, this is the 74th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed an issue with SC dual-port SRAM reading and writing to the same address ([#4445](https://github.com/OpenXiangShan/XiangShan/pull/4445))
    - Fixed an issue with incorrect usage of the SRAM Template ([#4485](https://github.com/OpenXiangShan/XiangShan/pull/4485))

### Backend

- **Bug Fixes**
    - Fixed an issue where modifying `hstatus.VGEIN` caused incorrect `vstopi` comparison ([#4517](https://github.com/OpenXiangShan/XiangShan/pull/4517)).
    - Fixed incorrect selection in `vstopi` when SEI and LCOFI interrupts are mixed ([#4533](https://github.com/OpenXiangShan/XiangShan/pull/4533)).
    - Fixed an issue where `IMSIC` incorrectly triggered illegal exceptions to CSR ([#4546](https://github.com/OpenXiangShan/XiangShan/pull/4546)).
    - Fixed a decoding error caused by `vtypegen` operating before `vsetvl` completion ([#4535](https://github.com/OpenXiangShan/XiangShan/pull/4535)).
    - Removed overly strict assertion related to the `Svinval` extension in ROB ([#4519](https://github.com/OpenXiangShan/XiangShan/pull/4519)).

- **RVA23 Profile**
    - Re-integrated Chisel AIA ([#4509](https://github.com/OpenXiangShan/XiangShan/pull/4509)).
    - Support configuring the timeout for the WFI instruction ([#4491](https://github.com/OpenXiangShan/XiangShan/pull/4491)).

### MemBlock and cache

- **Bug fixes**
    - Fix bug where a misaligned request accessing the uncache space did not correctly raise an unaligned exception ([#4526](https://github.com/OpenXiangShan/XiangShan/pull/4526))
    - Fix a bug in the synchronization of the store queue pointer update ([#4531](https://github.com/OpenXiangShan/XiangShan/pull/4531))
    - Fix a bug in the custom CSR control logic related to prefetching ([#4534](https://github.com/OpenXiangShan/XiangShan/pull/4534))
    - Fix several bugs in exception handling during the page table walk in MMU ([#4510](https://github.com/OpenXiangShan/XiangShan/pull/4510)), ([#4524](https://github.com/OpenXiangShan/XiangShan/pull/4524)), ([#4525](https://github.com/OpenXiangShan/XiangShan/pull/4525)), ([#4540](https://github.com/OpenXiangShan/XiangShan/pull/4540))
    - Fix two bugs related to hfence and flush ([#4539](https://github.com/OpenXiangShan/XiangShan/pull/4539)), ([#4541](https://github.com/OpenXiangShan/XiangShan/pull/4541))
    - Fix a bug where an incorrect ppn is generated when a PageCache napot entry is hit ([#4527](https://github.com/OpenXiangShan/XiangShan/pull/4527))
    - Fix parameterization of Temporal Prefetcher ([CoupledL2 #391](https://github.com/OpenXiangShan/CoupledL2/pull/391)), ([HuanCun #187](https://github.com/OpenXiangShan/HuanCun/pull/187))

- **CHI Bus**
    - Set the Non-secure field to Secure by default ([CoupledL2 #398](https://github.com/OpenXiangShan/CoupledL2/pull/398))

- **Tools**
    - Add CHIron CLog.B (CHI transaction logger) feature ([OpenLLC #55](https://github.com/OpenXiangShan/OpenLLC/pull/55))


- **PPA Optimizations**
    - Fix the enqueuing logic of the storeMisalignBuffer to optimize timing ([#4493](https://github.com/OpenXiangShan/XiangShan/pull/4493))

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
