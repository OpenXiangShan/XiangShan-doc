---
slug: biweekly-62-en
date: 2024-10-28
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 62】20241028

Welcome to XiangShan biweekly column, this is the 62th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently,

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

### Backend

- **Bug Fixes**

- **Timing/Power Optimization**

- **RVA23 Profile**

### MemBlock and cache

- **CHI Bus**
  - CHI-L3: Merge OpenLLC + OpenNCB into the main branch (Configuration: KunminghuV2Config) ([#3672](https://github.com/OpenXiangShan/XiangShan/pull/3672))

- **Bug fixes**
  - Fix a bug that caused stuck when two consecutive MMIO stores both triggered a non-data error exception ([#3728](https://github.com/OpenXiangShan/XiangShan/pull/3728))
  - Fix a bug that lost virtualisation information after splitting a non-aligned HLV (hypervisor load) instruction ([#3759](https://github.com/OpenXiangShan/XiangShan/pull/3759))
  - Fix a bug where storequeue incorrectly commits an unaligned instruction before it has finished executing ([#3758](https://github.com/OpenXiangShan/XiangShan/pull/3758))
  - Fix handling logic of vector exceptions. We should ensure that vector load/store instructions retain the earliest in-order exception after out-of-order execution ([#3733](https://github.com/OpenXiangShan/XiangShan/pull/3733))
  - Fix stuck problem caused by vector load/store unit incorrectly failing to receive new uop issues ([#3741](https://github.com/OpenXiangShan/XiangShan/pull/3741))

- **PPA Optimizations**
  - MemBlock internal and port timings continue to be optimised, with internal violations optimised to -45ps. Recent optimisations include removing the critical path in dcache from s2tag to dataArray, optimising timing of MemBlock's CMO requests to L2 cache, optimising loadunit write-back port selection logic and the exception writeback logic for unaligned access memory, etc. ([#3748](https://github.com/OpenXiangShan/XiangShan/pull/3748))
  - Adding clock gating to DCache SRAM which reduced internal memory power by 51%.

- **Tool**
  - CHIron: Implemented storage of CHI Log information in binary format, achieving a 6x faster parsing speed and reducing file space usage by 83% compared to text format
  - TL-test-new: Added CI process for OpenLLC, supporting MMIO testing
  - L2 HPM (Performance Counter): Adjusted connections based on physical design requirements ([#3747](https://github.com/OpenXiangShan/XiangShan/pull/3747))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC06 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPEC06FP set to fast. The instruction set used was RV64GCB. We ran SPEC06 checkpoints on the XiangShan processor **version 75dea01 from October 12** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.87  | 410.bwaves        | 75.03  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.49  |
| 403.gcc           | 46.48  | 433.milc          | 43.59  |
| 429.mcf           | 57.44  | 434.zeusmp        | 56.84  |
| 445.gobmk         | 30.16  | 435.gromacs       | 37.40  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 48.59  |
| 458.sjeng         | 30.23  | 437.leslie3d      | 43.70  |
| 462.libquantum    | 125.15 | 444.namd          | 34.69  |
| 464.h264ref       | 57.82  | 447.dealII        | 74.58  |
| 471.omnetpp       | 39.69  | 450.soplex        | 54.58  |
| 473.astar         | 29.00  | 453.povray        | 56.00  |
| 483.xalancbmk     | 74.77  | 454.Calculix      | 18.32  |
| **GEOMEAN**       | 44.47  | 459.GemsFDTD      | 37.98  |
|                   |        | 465.tonto         | 38.18  |
|                   |        | 470.lbm           | 102.01 |
|                   |        | 481.wrf           | 42.59  |
|                   |        | 482.sphinx3       | 52.55  |
|                   |        | **GEOMEAN**       | 47.40  |

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
