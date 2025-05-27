---
slug: biweekly-77-en
date: 2025-05-26
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 77】20250526

Welcome to XiangShan biweekly column, this is the 77th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption. In addition, the frontend fixed ICache performance counter, the backend fixed functional issues caused by out-of-order reads of `xtopi`/`xtopei` registers, and the memory and cache subsystem added handling logic for bus errors on Uncache Store.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed ICache performance counter ([#4725](https://github.com/OpenXiangShan/XiangShan/pull/4725))

### Backend

* **Bug Fixes**

  * Aligned the implementation of `xcontext` and `xstateen` CSRs with the latest privileged specification ([#4696](https://github.com/OpenXiangShan/XiangShan/pull/4696), [#4676](https://github.com/OpenXiangShan/XiangShan/pull/4676)).
  * Fixed functional issues caused by out-of-order reads of `xtopi`/`xtopei` registers ([#4698](https://github.com/OpenXiangShan/XiangShan/pull/4698)).
  * Added missing permission checks in accordance with the latest privileged specification ([#4672](https://github.com/OpenXiangShan/XiangShan/pull/4672)).
  * Fixed sign extension errors of the program counter under the `sv48x4` mode ([#4728](https://github.com/OpenXiangShan/XiangShan/pull/4728)).

### MemBlock and cache

- **Features**
  - L2 Cache supports NS; the MPAM NS bit is bound to a configurable NS bit ([CoupledL2 #412](https://github.com/OpenXiangShan/CoupledL2/pull/412), [#414](https://github.com/OpenXiangShan/CoupledL2/pull/414))
  - Added WFI safe-protection mechanism to ensure no outstanding L2 requests before the CPU core enters WFI state ([#4691](https://github.com/OpenXiangShan/XiangShan/pull/4691))

- **Bug fixes**
  - Added handling logic for bus errors on Uncache Store ([#4717](https://github.com/OpenXiangShan/XiangShan/pull/4717))
  - Fixed bug where a misaligned vector store incorrectly wrote data to sbuffer when exception happened ([#4731](https://github.com/OpenXiangShan/XiangShan/pull/4731))
  - Fixed bug in page-fault determination for the CBO instruction ([#4702](https://github.com/OpenXiangShan/XiangShan/pull/4702))
  - Fixed store–load forwarding data error caused by an incorrect forwarding mask for CMO instructions ([#4730](https://github.com/OpenXiangShan/XiangShan/pull/4730))
  - Fixed CPU stuck caused by incorrect redirect handling of vector instructions in the storequeue ([#4711](https://github.com/OpenXiangShan/XiangShan/pull/4711))
  - Fixed performance bug where huge pages in TLB should have hit but were falsely reported as missing in certain scenarios ([#4694](https://github.com/OpenXiangShan/XiangShan/pull/4694))
  - Fixed bug where SC/AMO instructions failed to report an access fault when the target address lacked atomic permissions ([#4724](https://github.com/OpenXiangShan/XiangShan/pull/4724))
  - Fixed bugs related to ECC error injection handling ([#4718](https://github.com/OpenXiangShan/XiangShan/pull/4718))

- **PPA Optimizations**
  - L2 Cache supports non-blocking RXDAT and RXRSP ([CoupledL2 #397](https://github.com/OpenXiangShan/CoupledL2/pull/397))
  - Adjusted BOP latency to match the CHI version of the L2 Cache ([CoupledL2 #413](https://github.com/OpenXiangShan/CoupledL2/pull/413))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit f9d8efe from May 8** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

**Note: The performance evaluation code version for this biweekly are the same as the last biweekly, and will be updated with the latest scores in the next biweekly.**

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.93  | 410.bwaves        | 66.86  |
| 401.bzip2         | 25.51  | 416.gamess        | 40.90  |
| 403.gcc           | 47.91  | 433.milc          | 45.17  |
| 429.mcf           | 59.57  | 434.zeusmp        | 52.09  |
| 445.gobmk         | 30.32  | 435.gromacs       | 33.66  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.52  | 437.leslie3d      | 45.90  |
| 462.libquantum    | 122.43 | 444.namd          | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII        | 73.57  |
| 471.omnetpp       | 41.45  | 450.soplex        | 52.64  |
| 473.astar         | 29.30  | 453.povray        | 53.39  |
| 483.xalancbmk     | 72.95  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.59  | 459.GemsFDTD      | 35.68  |
|                   |        | 465.tonto         | 36.69  |
|                   |        | 470.lbm           | 91.19  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.54  |

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
