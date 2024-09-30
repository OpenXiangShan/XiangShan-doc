---
slug: biweekly-60-en
date: 2024-09-30
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 60】20240930

Welcome to XiangShan biweekly column, this is the 60th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently,

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed a bug ([#bug](https://github.com/OpenXiangShan/XiangShan/pull/bug))

### Backend

- **Bug Fixes**
    - Continuously advancing function bug fixes, with over ?? issues resolved. Here are some of the PRs:

- **Timing Optimization**

- **RVA23 Profile**

### MemBlock and cache


- **CHI Bus**
  - Complete the CHI2AXI bridge OpenNCB implementation
  - The CHI-SoC integration test was successfully conducted, and the relevant code is being merged into the master branch. A significant performance degradation issue (compared to the TL version) was discovered during testing, and the cause is currently being investigated

- **RVA23 Profile**
  - Fixed several CSR and illegal instruction check issues for the cache management instruction extensions (Zicboz / Zicbom) to ensure compliance with the manual requirements
  - Develop and perform functionality testing for the CBO.INVAL instruction
  - Add support of vector vstart and trigger, and improve the implementation of first-only-first instructions. ([#3690](https://github.com/OpenXiangShan/XiangShan/pull/3690))

- **Performance**
  - TP: Completed iterative optimization design for TP
  - Store: Do performance optimisation based on memset pattern, mainly including improved sbuffer utilisation and implementing SPB-based prefetcher ([#3632](https://github.com/OpenXiangShan/XiangShan/pull/3632))

- **Bug fixes**
  - Fixed the issue of meta clients update in CoupledL2 DCT ([#3648](https://github.com/OpenXiangShan/XiangShan/pull/3648))
  - Fix a serious of bugs related to arbitration and nested request in CoupledL2 ([#3621](https://github.com/OpenXiangShan/XiangShan/pull/3621)), ([#3637](https://github.com/OpenXiangShan/XiangShan/pull/3637))
  - Fixed exception judgement error caused by high address truncation, and also fixed the bug that exception address was not correctly written to *tval register ([#3629](https://github.com/OpenXiangShan/XiangShan/pull/3629)), ([#3639](https://github.com/OpenXiangShan/XiangShan/pull/3639)), ([#3674](https://github.com/OpenXiangShan/XiangShan/pull/3674))

- **PPA Optimizations**
  - MemBlock Timing: Optimise dcache critical paths mainly related to tagarray
  - CHI-CoupledL2 Timing: Optimise management and arbitration logic of PCredit
  - RVA23 Timing: Fixed the timing issue between MemBlock and L2 introduced by the CMO extension, and the relevant code is being merged into the master branch
  - L2 MCP2 Constraints: Checked all relevant signals and fixed several violation cases ([#3633](https://github.com/OpenXiangShan/XiangShan/pull/3633))

- **Tool**
  - Successfully set up the TL-Test-new + CMN testing framework
  - Added CHI version HPM performance counters, refactored, and updated the HPM code ([#3631](https://github.com/OpenXiangShan/XiangShan/pull/3631))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC06 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPEC06FP set to fast. The instruction set used was RV64GCB. We ran SPEC06 checkpoints on the XiangShan processor **version 18560912f from September 27** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.94  | 410.bwaves        | 75.43  |
| 401.bzip2         | 25.57  | 416.gamess        | 44.04  |
| 403.gcc           | 46.57  | 433.milc          | 43.41  |
| 429.mcf           | 57.44  | 434.zeusmp        | 57.57  |
| 445.gobmk         | 30.19  | 435.gromacs       | 37.43  |
| 456.hmmer         | 41.45  | 436.cactusADM     | 48.71  |
| 458.sjeng         | 30.26  | 437.leslie3d      | 44.15  |
| 462.libquantum    | 125.11 | 444.namd          | 34.79  |
| 464.h264ref       | 57.91  | 447.dealII        | 75.53  |
| 471.omnetpp       | 39.88  | 450.soplex        | 54.70  |
| 473.astar         | 29.07  | 453.povray        | 56.33  |
| 483.xalancbmk     | 74.70  | 454.Calculix      | 18.34  |
| **GEOMEAN**       | 44.58  | 459.GemsFDTD      | 38.17  |
|                   |        | 465.tonto         | 38.59  |
|                   |        | 470.lbm           | 102.05 |
|                   |        | 481.wrf           | 44.27  |
|                   |        | 482.sphinx3       | 53.03  |
|                   |        | **GEOMEAN**       | 47.76  |

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
