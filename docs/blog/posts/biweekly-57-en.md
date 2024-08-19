---
slug: biweekly-57
date: 2024-08-19
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 57】20240819

Welcome to XiangShan biweekly column, this is the 57th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

WIP: Here's an overview line to add

<!-- more -->
## Recent developments

### Frontend

Fixed the cross-page exception bug introduced during the code refactoring for IFU exception handling, and also fixed a legacy bug here from Nanhu micro-architechture.

Support for RVA23: `prefetch.i` instruction from the Zicbop extension, and frontend support for the Svpbmt extension.

Changed the ITTAGE predictor updating mechanism from checkpointing (stored in the FTQ) to reading again when updating.

The RAS predictor now blocks the BPU pipeline to handle speculative queue overflow, instead of ignoring the overflow.

### Backend

### MemBlock and cache


#### CHI Bus

CHI-L3 (OpenLLC) completed the code design and was integrated into the Xiangshan system test. The CHI-L2+OpenLLC+DummyLLC (CHI2AXI) SoC was built, successfully running single-core CoreMark and Linux-hello.

Support for CHI's CMO instructions was added to OpenLLC.

The design plan for the CHI2AXI bridge was formulated, and RTL design began.

#### Features
Completed the RVA23 CMO code design and integrated it with the OpenLLC TL-Test framework that supports CMO requests, successfully running single CMO requests.

#### Performance
Added a TP metaBuffer on L2 TP meta to cache valid TP meta, alleviating negative competition between TP meta and L2 data; introduced a TP switch based on access frequency, turning off TP during high memory access.

The L2 Tubins replacement algorithm was tested and showed a performance increase of 0.15% compared to the DRRIP replacement algorithm.

The L3 Chrome replacement algorithm, after unit test framework trace stimulation testing and parameter tuning, showed a 27% hit rate increase on mcf but a decrease at some checkpoints; further exploration of EQ space compression was conducted.

#### Tools
The TL-Test framework iteration now can parse TL Logs into traces (TL Trace), serving as a test stimulus.

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC06 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPEC06FP set to fast. The instruction set used was RV64GCB. We ran SPEC06 fragments on the XiangShan processor **version 9d9be651a from August 12** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPECCPU 2006 scores:

| SPECint 2006      | @ 3GHz | SPECfp 2006       | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 33.52  | 410.bwaves        | 76.87  |
| 401.bzip2         | 24.96  | 416.gamess        | 43.36  |
| 403.gcc           | 47.68  | 433.milc          | 42.66  |
| 429.mcf           | 58.82  | 434.zeusmp        | 59.14  |
| 445.gobmk         | 30.03  | 435.gromacs       | 37.84  |
| 456.hmmer         | 40.26  | 436.cactusADM     | 47.84  |
| 458.sjeng         | 29.72  | 437.leslie3d      | 45.73  |
| 462.libquantum    | 126.91 | 444.namd          | 34.32  |
| 464.h264ref       | 56.48  | 447.dealII        | 74.12  |
| 471.omnetpp       | 41.12  | 450.soplex        | 54.53  |
| 473.astar         | 28.96  | 453.povray        | 55.70  |
| 483.xalancbmk     | 75.09  | 454.Calculix      | 18.14  |
| **GEOMEAN**       | 44.09  | 459.GemsFDTD      | 36.91  |
|                   |        | 465.tonto         | 35.73  |
|                   |        | 470.lbm           | 101.20 |
|                   |        | 481.wrf           | 42.14  |
|                   |        | 482.sphinx3       | 51.49  |
|                   |        | **GEOMEAN**       | 47.16  |

**The scores above are evaluated based on program fragments, not a full SPEC CPU 2006 evaluation, and may differ from the actual performance of the real chip!**

## Afterthought 

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao

Reviewer: XiangShan Publicity Team
