---
slug: biweekly-83-en
date: 2025-08-18
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 83】20250818

Welcome to XiangShan biweekly column, this is the 82nd issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

<!-- more -->
## Recent developments

### Frontend

### Backend

- **Bug Fixes**
  - Fixed the naming issue of PMA register output ([#4929](https://github.com/OpenXiangShan/XiangShan/pull/4929))
  - Adjusted the base address of PMA registers ([#4940](https://github.com/OpenXiangShan/XiangShan/pull/4940))
  - Fixed the issue with load fast wake-up where `vsetvli` instruction generates errors ([#4941](https://github.com/OpenXiangShan/XiangShan/pull/4941))

- **V3 Feature**
  - Changed the naming format of some bundles in the backend ([#4921](https://github.com/OpenXiangShan/XiangShan/pull/4921)), ([#4937](https://github.com/OpenXiangShan/XiangShan/pull/4937))
  - Allowed the last instruction in FTQ to be compressed ([#4931](https://github.com/OpenXiangShan/XiangShan/pull/4931))
  - Checked BJU's predicted jump target in the backend ([#4932](https://github.com/OpenXiangShan/XiangShan/pull/4932))

### MemBlock and cache

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit 99d41d3 from August 1** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU, TileLink bus protocol**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

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

Editors:
