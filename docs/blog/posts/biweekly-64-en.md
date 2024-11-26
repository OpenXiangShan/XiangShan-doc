---
slug: biweekly-64-en
date: 2024-11-25
categories:
  - Biweekly-en
---

# 【XiangShan Biweekly 64】20241125

Welcome to XiangShan biweekly column, this is the 64th issue of our biweekly column. Through this column, we will regularly introduce the progress of XiangShan, hoping to learn and improve together with you.

Recently,

<!-- more -->
## Recent developments

### Frontend

- **Bug Fixes**
    - Fixed BPU `s2_fire` assignment ([#3850](https://github.com/OpenXiangShan/XiangShan/pull/3850))
    - Fixed incorrect `xtval` value when `xstatus.FS` is disabled and C extension FP instructions raise exceptions ([#3859](https://github.com/OpenXiangShan/XiangShan/pull/3859))
    - Disallowed sequential instruction fetching across MMIO/non-MMIO boundaries ([#3873](https://github.com/OpenXiangShan/XiangShan/pull/3873))
    - Fixed incorrect `gpaddr` when H extension instruction fetch causes a Guest Page Fault ([#3795](https://github.com/OpenXiangShan/XiangShan/pull/3795))
    - Fixed incorrect `xtval` value for remaining 16b space instructions exceptions after implementing Zcb ([#3886](https://github.com/OpenXiangShan/XiangShan/pull/3886))

- **Features**
    - Re-fetch instructions from L2 when L1 ICache detects an ECC error ([#3899](https://github.com/OpenXiangShan/XiangShan/pull/3899))

- **Power**
    - Optimized BPU dynamic clock gating efficiency ([#3579](https://github.com/OpenXiangShan/XiangShan/pull/3579), [#3670](https://github.com/OpenXiangShan/XiangShan/pull/3670))
    - Added SRAM clock gating, reducing front-end power consumption by 10% ([#3889](https://github.com/OpenXiangShan/XiangShan/pull/3889))

### Backend

- **Bug Fixes**
    - Fixed issues related to Debug mode:
        - Fixed an issue where `dret` did not clear virtual privilege flags when return to machine mode ([#3898](https://github.com/OpenXiangShan/XiangShan/pull/3898)).
        - Fixed incorrect updates of `vstval` when memory access triggers a breakpoint exception ([#3875](https://github.com/OpenXiangShan/XiangShan/pull/3875)).
    - Fixed implementation issues with `fround` and `fcvtmod.w.d` instructions ([#3816](https://github.com/OpenXiangShan/XiangShan/pull/3816)).
    - Fixed the issue where `vnclip` immediate values were treated as signed instead of unsigned ([#3894](https://github.com/OpenXiangShan/XiangShan/pull/3894)).
    - Fixed vector and integer confusion in `vlbusytable` ([#3909](https://github.com/OpenXiangShan/XiangShan/pull/3909)).
    - Fixed the issue where the `critical-error` signal passed too early, causing difftest mismatches ([#3885](https://github.com/OpenXiangShan/XiangShan/pull/3885)).
    - Fixed the issue where `flh/fsh` instructions did not raise illegal instruction exceptions when `fs` was off ([#3841](https://github.com/OpenXiangShan/XiangShan/pull/3841)).
    - Fixed the issue where `aes64ks1i` reserved bits did not raise illegal instruction exceptions ([#3845](https://github.com/OpenXiangShan/XiangShan/pull/3845)).
    - Fixed numerous mismatches between NEMU simulator and RTL ([#669](https://github.com/OpenXiangShan/NEMU/pull/669), [#667](https://github.com/OpenXiangShan/NEMU/pull/667), [#666](https://github.com/OpenXiangShan/NEMU/pull/666), [#665](https://github.com/OpenXiangShan/NEMU/pull/665), [#664](https://github.com/OpenXiangShan/NEMU/pull/664)).

- **Timing/Area Optimization**
    - Completed a new dispatch algorithm without a dispatch queue; performance evaluation is ongoing.
    - Evaluated performance after reducing the number of floating-point multiply-add pipelines.

- **RVA23 Profile**
    - Completed remaining fields in `dcsr` for Debug Module, including `stopcount`, `stoptime`, `nmip`, `certig`, and `extcause` design.
    - Added support for entering Debug mode upon `critical-error` ([#3786](https://github.com/OpenXiangShan/XiangShan/pull/3786)).
    - Improved support for `smrnmi`/`dbltrp` extensions in Spike ([#3870](https://github.com/OpenXiangShan/XiangShan/pull/3870)).

- **Tools**
    - Injected commit ID information of the RTL version used during compilation into Verilog code ([#3818](https://github.com/OpenXiangShan/XiangShan/pull/3818)).

### MemBlock and cache

- **RVA23 Profile**
    - Implemented first version of RTL code to support uncache outstanding, working on refining self-test cases and testing them （[#3900](https://github.com/OpenXiangShan/XiangShan/pull/3900)）
    - Added hardware fault injection instructions for verifying Dcache ECC in RTL and NEMU（[#3923](https://github.com/OpenXiangShan/XiangShan/pull/3923)）, testing in local [AM](https://github.com/OpenXiangShan/nexus-am) environment.
    - Completed support for pointer masking (Ssnpm + Smnpm + Smmpm) extensions in RTL and NEMU, code being optimised for merge into master（[XiangShan #3921](https://github.com/OpenXiangShan/XiangShan/pull/3921), [NEMU #677](https://github.com/OpenXiangShan/NEMU/pull/677)）

- **Bug fixes**
    - Fix a bug that NEMU generates a logical error for GVPNi in G-stage translation for hypervisor extension, causing the physical address of root page table to be miscalculated（[NEMU #673](https://github.com/OpenXiangShan/NEMU/pull/673)）
    - Fix a bug in gpaddr generation logic when guest page fault occurs in instruction fetch（[#3871](https://github.com/OpenXiangShan/XiangShan/pull/3871)）
    - Fix enqMask generation logic when a load instruction enqueues LoadQueueReplay for the first time and needs to be redirected （[#3884](https://github.com/OpenXiangShan/XiangShan/pull/3884)）

- **PPA Optimizations**
  - Timing: Optimized the critical path of ECC check in MemBlock, improving timing violation from -54ps to -40ps ([#3908](https://github.com/OpenXiangShan/XiangShan/pull/3908))
  - Area:
    - Optimise area redundancy caused by multiple copies of registers in L1 TLB, reducing L1 TLB area by ~24% after optimisation([#3903](https://github.com/OpenXiangShan/XiangShan/pull/3903))
    - Maintained the DCache capacity while changing from 8-way to 4-way ([#3849](https://github.com/OpenXiangShan/XiangShan/pull/3849))
    - Merged `tagArray` and `eccArray` in the Directory ([#3902](https://github.com/OpenXiangShan/XiangShan/pull/3902))
    - Removed redundant signals/logic in MemBlock to optimize area ([#3560](https://github.com/OpenXiangShan/XiangShan/pull/3560))
  - Power: Added power gating to DCache SRAM, reducing total MemBlock power consumption by 23.38% ([#3824](https://github.com/OpenXiangShan/XiangShan/pull/3824))


## RTL Evaluation

We used SimPoint for program sampling and created checkpoint images based on our custom Checkpoint format, with a **SimPoint clustering coverage of 100%**. SPEC CPU2006 was compiled using gcc12 with O3 optimization enabled, the jemalloc memory library, and the `-ffp-contraction` option for SPECfp 2006 set to fast. The instruction set used was RV64GCB. We ran SPEC CPU2006 checkpoints on the XiangShan processor **commit f12520c from November 22** (**configured with 64KB L1 ICache, 64KB L1 DCache, 1MB L2, and 16MB L3, and a 3ld2st LSU**) in a simulation environment. DRAMsim3 was used to simulate DDR4-3200 memory latency with a CPU running at 3GHz. Below are the estimated SPEC CPU2006 scores:

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.09  | 410.bwaves        | 66.01  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.43  |
| 403.gcc           | 47.23  | 433.milc          | 45.26  |
| 429.mcf           | 58.81  | 434.zeusmp        | 56.88  |
| 445.gobmk         | 30.26  | 435.gromacs       | 37.45  |
| 456.hmmer         | 40.79  | 436.cactusADM     | 49.19  |
| 458.sjeng         | 30.27  | 437.leslie3d      | 45.32  |
| 462.libquantum    | 124.42 | 444.namd          | 34.65  |
| 464.h264ref       | 57.74  | 447.dealII        | 74.48  |
| 471.omnetpp       | 40.03  | 450.soplex        | 54.65  |
| 473.astar         | 29.06  | 453.povray        | 55.00  |
| 483.xalancbmk     | 74.23  | 454.Calculix      | 18.33  |
| **GEOMEAN**       | 44.64  | 459.GemsFDTD      | 40.22  |
|                   |        | 465.tonto         | 38.16  |
|                   |        | 470.lbm           | 102.48 |
|                   |        | 481.wrf           | 43.22  |
|                   |        | 482.sphinx3       | 53.24  |
|                   |        | **GEOMEAN**       | 47.48  |

**Scores are estimated with SimPoint checkpoints of SPEC CPU2006, which might deviate from real chip!**

## Afterthought

XiangShan Open Source Processor is under agile development, new features and new optimisations are continuously added, we will regularly synchronise our open source progress through the XiangShan biweekly column. Thank you for your attention, and welcome to communicate with us in the background!

In the late stage of XiangShan Kunminghu architecture development, XiangShan's performance will be announced once a month. Please look forward to it.

## Related links

* XiangShan technical discussion QQ group: 879550595
* XiangShan technical discussion website: https://github.com/OpenXiangShan/XiangShan/discussions
* XiangShan Documentation: https://xiangshan-doc.readthedocs.io/
* OpenLLC: https://github.com/OpenXiangShan/OpenLLC

Editors: Li Yanqin, Lin Zhida, Man Yang, Liu Zehao, Feng Haoyuan, Ma Yuexiao

Reviewer: XiangShan Publicity Team
