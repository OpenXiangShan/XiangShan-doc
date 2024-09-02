---
slug: biweekly-58-en
date: 2024-09-02
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 58】20240902

Welcome to XiangShan biweekly column, this is the 58th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently: WIP

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - A ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **RVA23 Profile**
    - B ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **Area & Power**
    - C ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

### Backend

- **Bug Fixes**
    - A ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **Timing Optimization**
    - B ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **Reg Cache**
    - C ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **Difftest**
    - D ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **RVA23 Profile**
    - E ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

### MemBlock and cache


- **CHI Bus**
    - A ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **RVA23 Profile**
    - B ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **Performance**
    - C ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **Tools**
    - D ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- **Timing Optimizations**
    - E ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC06 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPEC06FP set to fast. The instruction set used was RV64GCB. We ran SPEC06 fragments on the XiangShan processor **version 49162c9 from August 24** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPECCPU 2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------: | :----: | :---------------- | :----: |
| 400.perlbench     | 33.66  | 410.bwaves        | 76.67  |
| 401.bzip2         | 24.99  | 416.gamess        | 43.33  |
| 403.gcc           | 47.90  | 433.milc          | 42.42  |
| 429.mcf           | 58.75  | 434.zeusmp        | 59.01  |
| 445.gobmk         | 30.17  | 435.gromacs       | 37.87  |
| 456.hmmer         | 40.28  | 436.cactusADM     | 47.68  |
| 458.sjeng         | 29.72  | 437.leslie3d      | 46.13  |
| 462.libquantum    | 127.00 | 444.namd          | 34.34  |
| 464.h264ref       | 56.62  | 447.dealII        | 73.80  |
| 471.omnetpp       | 41.22  | 450.soplex        | 54.63  |
| 473.astar         | 29.09  | 453.povray        | 55.70  |
| 483.xalancbmk     | 75.13  | 454.Calculix      | 18.15  |
| **GEOMEAN**       | 44.18  | 459.GemsFDTD      | 37.00  |
|                   |        | 465.tonto         | 35.73  |
|                   |        | 470.lbm           | 101.16 |
|                   |        | 481.wrf           | 42.20  |
|                   |        | 482.sphinx3       | 51.45  |
|                   |        | **GEOMEAN**       | 47.15  |

**The scores above are estimated based on SimPoint checkpoints, not a full SPEC CPU 2006 estimation, and may differ from the actual performance of the real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao

Reviewer: XiangShan Publicity Team
