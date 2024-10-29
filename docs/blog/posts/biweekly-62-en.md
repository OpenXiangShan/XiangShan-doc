---
slug: biweekly-62-en
date: 2024-10-28
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 62】20241028

Welcome to XiangShan biweekly column, this is the 62th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently, various teams working on Kunminghu have continued to advance optimizations in area, timing, and power consumption. In addition, the frontend fixed Mux1H on the data path of ECC to Bus Error Unit, the backend is merging VS/S/M Mode Double Trap Extension (Ss/mdbltrp) into master, and the memory and cache subsystem fixed handling logic of vector exceptions. This update also includes the latest performance improvements of the Kunminghu architecture.

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed Mux1H on the data path of ECC to Bus Error Unit ([#3784](https://github.com/OpenXiangShan/XiangShan/pull/3784))

- **Timing**
    - Optimization of timing from FTQ to FDIP prefetch ([#3499](https://github.com/OpenXiangShan/XiangShan/pull/3499))
    - Removed io.flush from the prefetch critical path ([#3542](https://github.com/OpenXiangShan/XiangShan/pull/3542))
    - Optimized timing from s2_finish to prefetch ([#3545](https://github.com/OpenXiangShan/XiangShan/pull/3545))

- **Code Style**
    - Enabled scalafmt auto-formatting and added automatic checks in CI ([#3370](https://github.com/OpenXiangShan/XiangShan/pull/3370))
    - Removed unused imports and manually formatted some lines not handled well by scalafmt ([#3791](https://github.com/OpenXiangShan/XiangShan/pull/3791))

### Backend

- **Bug Fixes**
    - Fixed issues with inconsistent GPA retrieval for the H extension and Misalign memory access-related TLB issues ([#3681](https://github.com/OpenXiangShan/XiangShan/pull/3681), [#3679](https://github.com/OpenXiangShan/XiangShan/pull/3679))
    - Fixed `isEnqExcp` setting to zero for vector memory access exceptions when there is an older exception during write-back ([#3778](https://github.com/OpenXiangShan/XiangShan/pull/3778))
    - Fixed incorrect `xtval` updates for `ebreak` instruction-triggered breakpoint exceptions and compressed instruction illegal exceptions ([#3769](https://github.com/OpenXiangShan/XiangShan/pull/3769), [#3762](https://github.com/OpenXiangShan/XiangShan/pull/3762)), with corresponding updates in NEMU ([#599](https://github.com/OpenXiangShan/XiangShan/pull/599))
    - Fixed trigger-related issues for vector memory access ([#3772](https://github.com/OpenXiangShan/XiangShan/pull/3772), [#3745](https://github.com/OpenXiangShan/XiangShan/pull/3745))
    - Fixed errors due to separated storage for CSR exceptions ([#3771](https://github.com/OpenXiangShan/XiangShan/pull/3771))
    - Fixed inconsistency between xcause interrupt selection strategy and `xtopi` ([#3753](https://github.com/OpenXiangShan/XiangShan/pull/3753))
    - Fixed behavior discrepancies between NEMU and RTL for certain instructions setting `xstatus.FS=Dirty` ([#606](https://github.com/OpenXiangShan/XiangShan/pull/606), [#605](https://github.com/OpenXiangShan/XiangShan/pull/605), [#598](https://github.com/OpenXiangShan/XiangShan/pull/598), [#595](https://github.com/OpenXiangShan/XiangShan/pull/595), [#591](https://github.com/OpenXiangShan/XiangShan/pull/591), [#588](https://github.com/OpenXiangShan/XiangShan/pull/588))
    - Fixed Misalign memory access-related TLB issues ([#3731](https://github.com/OpenXiangShan/XiangShan/pull/3731))

- **Timing/Power Optimization**
    - Improved timing for wakeup, cancel, and memory access dependencies ([#3737](https://github.com/OpenXiangShan/XiangShan/pull/3737))
    - Evaluated backend area optimization points and potential benefits.

- **RVA23 Profile**
    - **Counter Overflow and Mode-Based Filtering Extension (Sscofpmf):** Added RTL guidance for NEMU overflow updates, enabled privilege-based filtering in RTL ([#3771](https://github.com/OpenXiangShan/XiangShan/pull/3771)), and completed `mhpmevent` implementation along with corresponding updates in NEMU ([#574](https://github.com/OpenXiangShan/XiangShan/pull/574))
    - **VS/S/M Mode Double Trap Extension (Ss/mdbltrp):** Merging into master ([#3789](https://github.com/OpenXiangShan/XiangShan/pull/3789))
    - Implemented trigger support for A extension in NEMU ([#592](https://github.com/OpenXiangShan/XiangShan/pull/592))

### MemBlock and cache

- **CHI Bus**
    - CHI-L3: Merge OpenLLC + OpenNCB into the main branch (Configuration: KunminghuV2Config) ([#3672](https://github.com/OpenXiangShan/XiangShan/pull/3672))

- **Bug fixes**
    - Fix a bug that caused stuck when two consecutive MMIO stores both triggered a non-data error exception ([#3728](https://github.com/OpenXiangShan/XiangShan/pull/3728))
    - Fix a bug that lost virtualisation information after splitting a non-aligned HLV (hypervisor load) instruction ([#3759](https://github.com/OpenXiangShan/XiangShan/pull/3759))
    - Fix a bug where StoreQueue incorrectly commits an unaligned instruction before it has finished executing ([#3758](https://github.com/OpenXiangShan/XiangShan/pull/3758))
    - Fix handling logic of vector exceptions. We should ensure that vector load/store instructions retain the earliest in-order exception after out-of-order execution ([#3733](https://github.com/OpenXiangShan/XiangShan/pull/3733))
    - Fix stuck problem caused by vector load/store unit failing to receive new uop issues ([#3741](https://github.com/OpenXiangShan/XiangShan/pull/3741))

- **PPA Optimizations**
    - MemBlock internal and port timings continue to be optimised, with internal violations optimised to -45ps. Recent optimisations include removing the critical path in dcache from s2tag to dataArray, optimising timing of MemBlock's CMO requests to L2 cache, optimising loadunit write-back port selection logic and the exception writeback logic for unaligned access memory, etc. ([#3748](https://github.com/OpenXiangShan/XiangShan/pull/3748))
    - Adding clock gating to DCache SRAM which reduced internal memory power by 51%.

- **Tool**
    - CHIron: Implemented storage of CHI Log information in binary format, achieving a 6x faster parsing speed and reducing file space usage by 83% compared to text format
    - TL-test-new: Added CI process for OpenLLC, supporting MMIO testing
    - L2 HPM (Performance Counter): Adjusted connections based on physical design requirements ([#3747](https://github.com/OpenXiangShan/XiangShan/pull/3747))

## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **version b3c3582 from October 26** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.85  | 410.bwaves        | 75.02  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.49  |
| 403.gcc           | 46.49  | 433.milc          | 43.61  |
| 429.mcf           | 57.50  | 434.zeusmp        | 56.80  |
| 445.gobmk         | 30.18  | 435.gromacs       | 37.38  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 48.77  |
| 458.sjeng         | 30.18  | 437.leslie3d      | 43.82  |
| 462.libquantum    | 125.07 | 444.namd          | 34.69  |
| 464.h264ref       | 57.81  | 447.dealII        | 74.53  |
| 471.omnetpp       | 40.01  | 450.soplex        | 54.54  |
| 473.astar         | 29.00  | 453.povray        | 55.93  |
| 483.xalancbmk     | 74.74  | 454.Calculix      | 18.32  |
| **GEOMEAN**       | 44.49  | 459.GemsFDTD      | 37.82  |
|                   |        | 465.tonto         | 38.21  |
|                   |        | 470.lbm           | 102.05 |
|                   |        | 481.wrf           | 42.68  |
|                   |        | 482.sphinx3       | 52.71  |
|                   |        | **GEOMEAN**       | 47.42  |

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
