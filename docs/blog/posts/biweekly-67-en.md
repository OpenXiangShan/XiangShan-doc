---
slug: biweekly-67-en
date: 2025-01-06
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 67】20250106

Welcome to XiangShan biweekly column, this is the 67th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- **Area**

### Backend

- **Bug Fixes**
    - Fixed an issue where CSR instructions failed to raise address translation exceptions ([#4118](https://github.com/OpenXiangShan/XiangShan/pull/4118)).
    - Fixed read/write dependency issues for the `LCOFI` bit in the `hideleg` register ([#4070](https://github.com/OpenXiangShan/XiangShan/pull/4070)), with corresponding fixes in NEMU ([NEMU #733](https://github.com/OpenXiangShan/NEMU/pull/733)).
    - Fixed an issue where CSR did not correctly respond to flush signals after being partially pipelined ([#4079](https://github.com/OpenXiangShan/XiangShan/pull/4079)).
    - Fixed an error in updating the `time` register in user mode ([#4132](https://github.com/OpenXiangShan/XiangShan/pull/4132)).
    - Fixed incorrect behavior when fusing `lui` and `fld` instructions with the zero register as the destination ([#4131](https://github.com/OpenXiangShan/XiangShan/pull/4131)).
    - Fixed incorrect fusion of Hint-type instructions ([#4108](https://github.com/OpenXiangShan/XiangShan/pull/4108)).
    - NEMU fixed an issue with the incorrect priority of SGEI interrupts ([#733](https://github.com/OpenXiangShan/NEMU/pull/733)).

- **Timing/Area Optimization**
    - Split the floating-point/vector register file into 4 blocks ([#4088](https://github.com/OpenXiangShan/XiangShan/pull/4088)).
    - Fixed timing issues with dequeue refresh pipelines and vector exceptions in ROB ([#4075](https://github.com/OpenXiangShan/XiangShan/pull/4075)).
    - Changed the vector complex decoder signal to be directly output by instruction encoding ([#4066](https://github.com/OpenXiangShan/XiangShan/pull/4066)).
    - Added registers for read/write addresses and data output from CSR to frontend/memory ([#4119](https://github.com/OpenXiangShan/XiangShan/pull/4119)).

- **Tool**
    - Added Top-Down backend-related hardware performance counting events ([#4122](https://github.com/OpenXiangShan/XiangShan/pull/4122)).

### MemBlock and cache

- **RVA23 Profile**

- **Bug fixes**
  - Fixed a series of nested bugs related to `SnpOnce*`/`SnpStash*` ([CoupledL2 #306](https://github.com/OpenXiangShan/CoupledL2/pull/306)), ([CoupledL2 #308](https://github.com/OpenXiangShan/CoupledL2/pull/308)), ([CoupledL2 #309](https://github.com/OpenXiangShan/CoupledL2/pull/309))  
  - Fixed a bug where the replacement algorithm retry signal did not last for two cycles when MCP2 was enabled ([CoupledL2 #303](https://github.com/OpenXiangShan/CoupledL2/pull/303))  

- **Prefetch**
  - Added physical memory range checks to BOP ([#4115](https://github.com/OpenXiangShan/XiangShan/pull/4115))  

- **PPA Optimizations**
  - Removed duplicate signals in `MainPipe` ([#4117](https://github.com/OpenXiangShan/XiangShan/pull/4117))  
  - Reduced the number of `LoadQueueReplay` entries, resulting in a 2.85% area reduction and a 1.59% power reduction ([#4082](https://github.com/OpenXiangShan/XiangShan/pull/4082))  

- **Tool**
  - OpenLLC now supports Top-Down analysis ([#4113](https://github.com/OpenXiangShan/XiangShan/pull/4113))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 718a93f from January 6** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

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

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao

Reviewer: XiangShan Publicity Team
