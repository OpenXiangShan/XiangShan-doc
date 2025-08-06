---
slug: biweekly-82-en
date: 2025-08-04
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 82】20250804

Welcome to XiangShan biweekly column, this is the 82nd issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have started designing V3. In addition, the fronted fixed issue where parity check might use invalid results when ICache requests cross lines, the backend fixed the issue of incorrect bit width calculation for variables such as the total number of instruction commit and the total number of walk in VTypeBuffer under specific parameters, and the memory and cache subsystem fixed a bug where vector segment instructions failed to correctly report ECC errors. This update also includes the latest performance improvements of the Kunminghu architecture.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed the issue where Svpbmt NC fetch did not set the corresponding tag on the L1-L2 bus ([#4898](https://github.com/OpenXiangShan/XiangShan/pull/4898))
    - Fixed the issue with Svpbmt NC fetch state machine flushing ([#4903](https://github.com/OpenXiangShan/XiangShan/pull/4903))
    - Fixed the issue where Svpbmt NC fetch would still enqueue to IBuffer after flushing ([#4922](https://github.com/OpenXiangShan/XiangShan/pull/4922))

- **V3 Feature**
    - Generation of half-aligned prediction blocks, with corresponding support in uBTB and mBTB; removal of cross-page prediction; added write buffer for SRAM read-write conflicts with read priority; changed branch predictor history to use path history ([#4896](https://github.com/OpenXiangShan/XiangShan/pull/4896))

### Backend

- **Bug Fixes**
  - Fix the issue where the `xcontext` CSR was not reset properly ([#4915](https://github.com/OpenXiangShan/XiangShan/pull/4915))
  - Fix missing exception priority configuration for software check exceptions ([#4923](https://github.com/OpenXiangShan/XiangShan/pull/4923))

- **V3 Feature**
  - Increase issue width to 8, update issue queue configurations, and add more ALU units ([#4845](https://github.com/OpenXiangShan/XiangShan/pull/4845))
  - Support speculative wakeup and cancellation for variable-latency functional units ([#4845](https://github.com/OpenXiangShan/XiangShan/pull/4845))
  - Support speculative wakeup and cancellation for load instructions ([#4845](https://github.com/OpenXiangShan/XiangShan/pull/4845))

### MemBlock and cache

- **Bug fixes**
  - Fix the condition for identifying Napot pages: only pages with the lower 4 bits of PPN equal to 4'b1000 are allowed to cover a 64KB range ([#4828](https://github.com/OpenXiangShan/XiangShan/pull/4828)), ([#4900](https://github.com/OpenXiangShan/XiangShan/pull/4900))
  - Fix a bug in the vpn matching logic during gpf handling and gpaddr retrieval, where NAPOT page attributes were not properly considered ([#4911](https://github.com/OpenXiangShan/XiangShan/pull/4911))
  - Fix a bug where the top two bits of vaddr were incorrectly truncated, which could result in incorrect upper bits in gpaddr when written back to CSR in certain scenarios ([#4913](https://github.com/OpenXiangShan/XiangShan/pull/4913))
  - Fix the generation logic related to DCache bus errors to prevent propagation of X states ([#4899](https://github.com/OpenXiangShan/XiangShan/pull/4899))
  - Set the initial value of memBackType in DCache MSHR to correctly indicate whether the request to L2 Cache targets memory or uncache ([#4907](https://github.com/OpenXiangShan/XiangShan/pull/4907))
  - Fix a bug where the high bits of vaddr were truncated in vector segment instructions, causing false exception reports ([#4892](https://github.com/OpenXiangShan/XiangShan/pull/4892))
  - Fix some stuck bugs during vector misalignment handling ([#4914](https://github.com/OpenXiangShan/XiangShan/pull/4914))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 99d41d3 from August 1** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.91  | 410.bwaves        | 67.24  |
| 401.bzip2         | 25.51  | 416.gamess        | 41.00  |
| 403.gcc           | 47.95  | 433.milc          | 44.95  |
| 429.mcf           | 60.20  | 434.zeusmp        | 51.71  |
| 445.gobmk         | 30.69  | 435.gromacs       | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.65  | 437.leslie3d      | 47.77  |
| 462.libquantum    | 122.65 | 444.namd          | 28.87  |
| 464.h264ref       | 56.63  | 447.dealII        | 73.15  |
| 471.omnetpp       | 41.49  | 450.soplex        | 52.54  |
| 473.astar         | 29.35  | 453.povray        | 53.48  |
| 483.xalancbmk     | 72.73  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.70  | 459.GemsFDTD      | 40.45  |
|                   |        | 465.tonto         | 36.66  |
|                   |        | 470.lbm           | 91.96  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.97  |

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
