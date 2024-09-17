---
slug: biweekly-59-en
date: 2024-09-16
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 59】20240916

Welcome to XiangShan biweekly column, this is the 59th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently,

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - template ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

### Backend

- **Bug Fixes**
    - Continuously advancing function bug fixes, with over 30 issues resolved. Here are some of the PRs:
    - Fixed H-extension function bugs ([#3580](https://github.com/OpenXiangShan/XiangShan/pull/3580), [#3575](https://github.com/OpenXiangShan/XiangShan/pull/3575), [#3569](https://github.com/OpenXiangShan/XiangShan/pull/3569), [#3561](https://github.com/OpenXiangShan/XiangShan/pull/3561), [#3553](https://github.com/OpenXiangShan/XiangShan/pull/3553), [#3551](https://github.com/OpenXiangShan/XiangShan/pull/3551), [#3528](https://github.com/OpenXiangShan/XiangShan/pull/3528), [#3525](https://github.com/OpenXiangShan/XiangShan/pull/3525), [#3524](https://github.com/OpenXiangShan/XiangShan/pull/3524), [#3523](https://github.com/OpenXiangShan/XiangShan/pull/3523), [#3512](https://github.com/OpenXiangShan/XiangShan/pull/3512), [#3510](https://github.com/OpenXiangShan/XiangShan/pull/3510), [#3502](https://github.com/OpenXiangShan/XiangShan/pull/3502))
    - Fixed privilege level function bugs ([#3558](https://github.com/OpenXiangShan/XiangShan/pull/3558), [#3557](https://github.com/OpenXiangShan/XiangShan/pull/3557), [#3534](https://github.com/OpenXiangShan/XiangShan/pull/3534), [#3515](https://github.com/OpenXiangShan/XiangShan/pull/3515), [#3496](https://github.com/OpenXiangShan/XiangShan/pull/3496), [#3486](https://github.com/OpenXiangShan/XiangShan/pull/3486), [#3469](https://github.com/OpenXiangShan/XiangShan/pull/3469), [#3434](https://github.com/OpenXiangShan/XiangShan/pull/3434), [#3547](https://github.com/OpenXiangShan/XiangShan/pull/3547))
    - Fixed Debug extension function bugs ([#3538](https://github.com/OpenXiangShan/XiangShan/pull/3538), [#3536](https://github.com/OpenXiangShan/XiangShan/pull/3536), [#3472](https://github.com/OpenXiangShan/XiangShan/pull/3472))
    - Fixed V-extension function bugs ([#3535](https://github.com/OpenXiangShan/XiangShan/pull/3535), [#3495](https://github.com/OpenXiangShan/XiangShan/pull/3495), [#3494](https://github.com/OpenXiangShan/XiangShan/pull/3494))

- **Timing Optimization**
    - Added OG2 to vector memory access ([#3482](https://github.com/OpenXiangShan/XiangShan/pull/3482))
    - Optimized the logic for Rab state machine transitioning to idle ([#3517](https://github.com/OpenXiangShan/XiangShan/pull/3517))
    - Added an adder to optimize the target calculation timing in the branch calculation module and removed redundant judgment logic ([#3520](https://github.com/OpenXiangShan/XiangShan/pull/3520))
    - Reduced the enqueue number of the memory access issue queue from 2 to 1 to alleviate timing pressure ([#3471](https://github.com/OpenXiangShan/XiangShan/pull/3471))

- **RVA23 Profile**
    - Supported The Resumable Non-Maskable Interrupt (Smrnmi) extension ([#3480](https://github.com/OpenXiangShan/XiangShan/pull/3480))
    - Added CMO instruction extensions (Zicbom, Zicboz) including privilege checks and related CSR support ([#3559](https://github.com/OpenXiangShan/XiangShan/pull/3559))
    - Supported The Additional Floating-Point instructions extension (Zfa) ([#3439](https://github.com/OpenXiangShan/XiangShan/pull/3439))

### MemBlock and cache


- **CHI Bus**
    - Completed CHI2AXI bridge design (OpenNCB), set up CoupledL2-OpenLLC-OpenNCB test framework
    - - Add non-data error handling logic, return DECERR when accessing non-existing peripheral ([#3458](https://github.com/OpenXiangShan/XiangShan/pull/3458))

- **RVA23 Profile**
    - Completed the design of CMO extension requirements for CSR modifications and instruction exception conditions, and implemented the related CSR register and instruction exception checks on NEMU
    - Completed code implementation of svpbmt extension enable signal PBMTE ([#3521](https://github.com/OpenXiangShan/XiangShan/pull/3521))

- **Performance**
    - TP meta on L2: Relevant code has been migrated to a newer master version. A significant drop in TP prefetch count has occurred, currently under repair
    - Adds a new performance regression test in CI to automatically test SPEC06 performance scores every Friday ([#3533](https://github.com/OpenXiangShan/XiangShan/pull/3533)).

- Bug fixes
    - Fixed hardcoding issue in TP, implemented correct support for sv48([#3487](https://github.com/OpenXiangShan/XiangShan/commit/e1d5ffc2d93873b72146e78c8f6a904926de8590))
    - Fixed a performance bug in L2 Cache where mergeA causes prefetch delays (pending performance evaluation)
    - Fix PCredit arbitration related bugs that lead to PCredit lost or duplicate distribution ([#3513](https://github.com/OpenXiangShan/XiangShan/pull/3513), [#3552](https://github.com/OpenXiangShan/XiangShan/pull/3552))
    - Fix exception handling generation and arbitration logic of L2TLB ([#3453](https://github.com/OpenXiangShan/XiangShan/pull/3453), [#3588](https://github.com/OpenXiangShan/XiangShan/pull/3588))

- **PPA Optimizations**
    - Timing: Completed the splitting of the L2 Cache tagArray, optimizing the critical path timing within the L2 Cache module
    - Area: fix redundant signals in MemBlock, mainly including exceptionVec and fuType, etc. ([#3560](https://github.com/OpenXiangShan/XiangShan/pull/3560))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC06 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPEC06FP set to fast. The instruction set used was RV64GCB. We ran SPEC06 checkpoints on the XiangShan processor **version 42b6cdf from September 5** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.84  | 410.bwaves        | 77.28  |
| 401.bzip2         | 25.52  | 416.gamess        | 43.52  |
| 403.gcc           | 48.49  | 433.milc          | 42.48  |
| 429.mcf           | 58.95  | 434.zeusmp        | 56.99  |
| 445.gobmk         | 30.20  | 435.gromacs       | 37.38  |
| 456.hmmer         | 41.30  | 436.cactusADM     | 48.45  |
| 458.sjeng         | 30.12  | 437.leslie3d      | 43.67  |
| 462.libquantum    | 127.52 | 444.namd          | 34.30  |
| 464.h264ref       | 57.81  | 447.dealII        | 74.82  |
| 471.omnetpp       | 41.79  | 450.soplex        | 54.49  |
| 473.astar         | 29.17  | 453.povray        | 55.61  |
| 483.xalancbmk     | 75.84  | 454.Calculix      | 18.21  |
| **GEOMEAN**       | 45.09  | 459.GemsFDTD      | 37.24  |
|                   |        | 465.tonto         | 36.21  |
|                   |        | 470.lbm           | 101.29 |
|                   |        | 481.wrf           | 43.52  |
|                   |        | 482.sphinx3       | 51.32  |
|                   |        | **GEOMEAN**       | 47.12  |

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
