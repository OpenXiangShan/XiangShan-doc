---
slug: biweekly-80-en
date: 2025-07-07
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 80】20250707

Welcome to XiangShan biweekly column, this is the 80th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fix issue where parity check might use invalid results when ICache requests cross lines ([#4814](https://github.com/OpenXiangShan/XiangShan/pull/4814))

- **V3 Feature**
    - BPU top-level pipeline, new uBTB, Ahead BTB ([#4851](https://github.com/OpenXiangShan/XiangShan/pull/4851))
    - IFU removes predecode checks from the critical path ([#4849](https://github.com/OpenXiangShan/XiangShan/pull/4849))

### Backend

- **Bug Fixes**
    - Fixed the issue where the selection conditions and selected data of xtopi are out of sync ([#4836](https://github.com/OpenXiangShan/XiangShan/pull/4836))
    - Fixed the issue of incorrect bit width calculation for variables such as the total number of instruction commit and the total number of walk in VTypeBuffer under specific parameters ([#4850](https://github.com/OpenXiangShan/XiangShan/pull/4850))

- **V3 Feature**
    - Increased the types of ROB compressible instructions ([#4114](https://github.com/OpenXiangShan/XiangShan/pull/4114))
    - Modified the mechanism for the backend to notify the frontend ftq when committing ([#4114](https://github.com/OpenXiangShan/XiangShan/pull/4114))

### MemBlock and cache

- **Bug fixes**
    - Fixed a bug where vector segment instructions failed to correctly report ECC errors ([#4831](https://github.com/OpenXiangShan/XiangShan/pull/4831))
    - Aligned the agnostic behavior of the vleff instruction between RTL and NEMU ([#4820](https://github.com/OpenXiangShan/XiangShan/pull/4820)), ([NEMU #906](https://github.com/OpenXiangShan/NEMU/pull/906))
    - Fixed a bug where the extra_meta_resp signal was incorrectly overwritten when a DCache request was blocked in the s1 stage ([#4842](https://github.com/OpenXiangShan/XiangShan/pull/4842))
    - Fixed a bug where a flushed misaligned memory instruction was mistakenly enqueued into the misaligned buffer ([#4840](https://github.com/OpenXiangShan/XiangShan/pull/4840))
    - Ensured the flush signal to the sbuffer remains asserted until the vector segment unit completes the flush operation ([#4853](https://github.com/OpenXiangShan/XiangShan/pull/4853))
    - Fixed incorrect exception reporting when the second request of a split misaligned vector instruction triggered an exception ([#4854](https://github.com/OpenXiangShan/XiangShan/pull/4854))
    - Fixed X-propagation in Dcache mainpipe caused by missing requests ([#4856](https://github.com/OpenXiangShan/XiangShan/pull/4856))
    - Fixed incorrect gpaddr calculation when a vector unit-stride instruction triggers a guest page fault ([#4865](https://github.com/OpenXiangShan/XiangShan/pull/4865))
    - Fixed the issue where linkActive is de-asserted before syscozck==0 after powerdown (leaving coherence state) ([CoupledL2 #422](https://github.com/OpenXiangShan/CoupledL2/pull/422))
    - Fixed the incorrect assertion timing of the exitcoDone signal after reset ([CoupledL2 #424](https://github.com/OpenXiangShan/CoupledL2/pull/424))

- **V3 Feature**
    - Refactored the L1 prefetch framework, including parameterization and decoupling, etc. ([#4790](https://github.com/OpenXiangShan/XiangShan/pull/4790))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit c25dcc6 from July 3** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 67.02  |
| 401.bzip2         | 25.50  | 416.gamess        | 40.99  |
| 403.gcc           | 47.90  | 433.milc          | 44.69  |
| 429.mcf           | 60.13  | 434.zeusmp        | 51.57  |
| 445.gobmk         | 30.70  | 435.gromacs       | 33.63  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.65  | 437.leslie3d      | 46.68  |
| 462.libquantum    | 105.08 | 444.namd          | 28.87  |
| 464.h264ref       | 56.60  | 447.dealII        | 72.19  |
| 471.omnetpp       | 41.52  | 450.soplex        | 52.33  |
| 473.astar         | 29.35  | 453.povray        | 53.46  |
| 483.xalancbmk     | 72.11  | 454.Calculix      | 16.37  |
| **GEOMEAN**       | 44.09  | 459.GemsFDTD      | 39.64  |
|                   |        | 465.tonto         | 36.12  |
|                   |        | 470.lbm           | 85.79  |
|                   |        | 481.wrf           | 40.30  |
|                   |        | 482.sphinx3       | 48.48  |
|                   |        | **GEOMEAN**       | 44.50  |

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
