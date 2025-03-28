---
slug: biweekly-73-en
date: 2025-03-31
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 73】20250331

Welcome to XiangShan biweekly column, this is the 73nd issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption. 

Additionally, we have also made public the repository for the **XiangShan Open Source Processor User Guide**: [https://github.com/OpenXiangShan/XiangShan-User-Guide](https://github.com/OpenXiangShan/XiangShan-User-Guide) and its corresponding webpage: [https://docs.xiangshan.cc/projects/user-guide/](https://docs.xiangshan.cc/projects/user-guide/), as well as the repository for the **XiangShan Open Source Processor Design Document**: [https://github.com/OpenXiangShan/XiangShan-Design-Doc](https://github.com/OpenXiangShan/XiangShan-Design-Doc) and its corresponding webpage: [https://docs.xiangshan.cc/projects/design/](https://docs.xiangshan.cc/projects/design/). We welcome everyone to read and ask questions.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**


### Backend

- **Bug Fixes**


- **Timing/Area Optimization**


### MemBlock and cache

- **RVA23 Profile**

- **Bug fixes**
  - Fix several consistency issues in CoupledL2 that violated the CHI protocol ([CoupledL2 #390](https://github.com/OpenXiangShan/CoupledL2/pull/390)), ([CoupledL2 #392](https://github.com/OpenXiangShan/CoupledL2/pull/392)), ([CoupledL2 #395](https://github.com/OpenXiangShan/CoupledL2/pull/395))
  - Add check for the WFI (Wait For Interrupt) state before the L2 Cache exits the coherency ([CoupledL2 #385](https://github.com/OpenXiangShan/CoupledL2/pull/385))
  - Fix several issues related to the handling of the RespErr field in the CHI protocol ([CoupledL2 #384](https://github.com/OpenXiangShan/CoupledL2/pull/384))、([CoupledL2 #394](https://github.com/OpenXiangShan/CoupledL2/pull/394))

- Timing/Area Optimizations
  - Adjust L2 Cache SRAM (tag) specifications ([CoupledL2 #388](https://github.com/OpenXiangShan/CoupledL2/pull/388)); add SRAM control interface ([CoupledL2 #389](https://github.com/OpenXiangShan/CoupledL2/pull/389))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 9245b52 from March 14** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

**Note: The performance evaluation code version for this biweekly are the same as the last biweekly, and will be updated with the latest scores in the next biweekly.**

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 66.89  |
| 401.bzip2         | 25.50  | 416.gamess        | 40.89  |
| 403.gcc           | 46.72  | 433.milc          | 45.25  |
| 429.mcf           | 58.13  | 434.zeusmp        | 52.10  |
| 445.gobmk         | 30.26  | 435.gromacs       | 33.65  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.16  |
| 458.sjeng         | 30.53  | 437.leslie3d      | 46.01  |
| 462.libquantum    | 122.50 | 444.namd          | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII        | 73.43  |
| 471.omnetpp       | 39.37  | 450.soplex        | 51.99  |
| 473.astar         | 29.23  | 453.povray        | 53.44  |
| 483.xalancbmk     | 72.03  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.15  | 459.GemsFDTD      | 37.18  |
|                   |        | 465.tonto         | 36.67  |
|                   |        | 470.lbm           | 91.24  |
|                   |        | 481.wrf           | 40.62  |
|                   |        | 482.sphinx3       | 48.57  |
|                   |        | **GEOMEAN**       | 44.60  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/
* XiangShan User Guide: https://docs.xiangshan.cc/projects/user-guide/
* XiangShan Design Doc: https://docs.xiangshan.cc/projects/design/

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao
