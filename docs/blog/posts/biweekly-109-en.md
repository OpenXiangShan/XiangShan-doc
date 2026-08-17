---
slug: biweekly-109-en
date: 2026-08-18
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 109] 20260818

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 109th issue of the biweekly report.

Regarding the recent development progress of XiangShan, the frontend; the backend; in terms of memory access and caching, ; XSAI.

<!-- more -->

## Recent Developments

### Frontend

- Bug fixes
  - Fix incorrect IFU instruction counting when an exception occurs ([#6301](https://github.com/OpenXiangShan/XiangShan/pull/6301))
  - Fix the priority of read-write conflicts in the write buffer ([#6315](https://github.com/OpenXiangShan/XiangShan/pull/6315))
  - Use not-taken branches to train the corresponding counters ([#6305](https://github.com/OpenXiangShan/XiangShan/pull/6305))
- PPA optimizations
  - Use `attribute` instead of `valid` in the main BTB ([#6350](https://github.com/OpenXiangShan/XiangShan/pull/6350))
  - Optimize timing at the 2-fetch interface between FTQ and ICache ([#6281](https://github.com/OpenXiangShan/XiangShan/pull/6281))
  - Fix the update timing of the PHR S1 and S3 pipelines ([#6263](https://github.com/OpenXiangShan/XiangShan/pull/6263))
  - Optimize ABTB update timing ([#6326](https://github.com/OpenXiangShan/XiangShan/pull/6326))
  - Optimize the timing of final taken-branch computation in BPU S3 ([#6324](https://github.com/OpenXiangShan/XiangShan/pull/6324))

### Backend

- RTL features
  - (V2) Allow writes to `PMM` fields in `mseccfg`, `xenvcfg`, and `hstatus`, and allow configuration of `xenvcfg.CBIE`, enabling the Smmpm, Smnpm, and Ssnpm pointer-masking extensions and `cbo.inval` behavior ([#6269](https://github.com/OpenXiangShan/XiangShan/pull/6269))
- Bug fixes
  - (V3) Fix a `vl` rename free-list leak: a `vl`-writing instruction that survives a redirect could exhaust physical registers and permanently stall Rename ([#6246](https://github.com/OpenXiangShan/XiangShan/pull/6246))
- Debugging tools
  - (V3) Extend TopDown analysis with ROB-head-based out-of-order-window bottleneck attribution across execution readiness, issue delay/cancellation, not-issued, memory, and resource bottlenecks ([#6173](https://github.com/OpenXiangShan/XiangShan/pull/6173))

### MemBlock and Cache

- RTL features
  - Implement and integrate the L2 CDP prefetcher ([XSCache #15](https://github.com/OpenXiangShan/XSCache/pull/15), [XiangShan #6341](https://github.com/OpenXiangShan/XiangShan/pull/6341))
- Bug fixes
  - Fix the DCache latency-flag index calculation ([XiangShan #6339](https://github.com/OpenXiangShan/XiangShan/pull/6339))
  - Fix TLB-miss handling for cross-page unaligned stores ([XiangShan #6332](https://github.com/OpenXiangShan/XiangShan/pull/6332))
  - Fix illegal issue replay feedback for unaligned stores ([XiangShan #6322](https://github.com/OpenXiangShan/XiangShan/pull/6322))
  - [V2] Fix out-of-order StoreQueue read-pointer updates ([XiangShan #6353](https://github.com/OpenXiangShan/XiangShan/pull/6353))
  - [V2] Fix dropped-request and Directory MultiHit error reporting in coupledL2 ([CoupledL2 #523](https://github.com/OpenXiangShan/CoupledL2/pull/523), [XiangShan #6345](https://github.com/OpenXiangShan/XiangShan/pull/6345))
  - [V2] Propagate non-leaf-PTE metadata for vector loads ([XiangShan #6344](https://github.com/OpenXiangShan/XiangShan/pull/6344))
  - [V2] Fix X propagation from invalid prefetch-filter state ([XiangShan #6342](https://github.com/OpenXiangShan/XiangShan/pull/6342))
  - [V2] Preserve vector-store replay metadata ([XiangShan #6338](https://github.com/OpenXiangShan/XiangShan/pull/6338))
  - [V2] Fix hangs in cross-page unaligned vector stores ([XiangShan #6337](https://github.com/OpenXiangShan/XiangShan/pull/6337))
  - [V2] Fix StoreQueue address-state updates on TLB misses ([XiangShan #6334](https://github.com/OpenXiangShan/XiangShan/pull/6334))
  - [V2] Fix ordering of unaligned vector elements within one uop ([XiangShan #6323](https://github.com/OpenXiangShan/XiangShan/pull/6323))
  - [V2] Increase the CHI async-bridge queue depth from 4 to 8 ([XiangShan #6306](https://github.com/OpenXiangShan/XiangShan/pull/6306))

### XSAI

- RTL features
  - Support e8/e16/e32 multi-precision transposed loads for tile registers ([CUTE #35](https://github.com/OpenXiangShan/CUTE/pull/35))
- Bug fixes
  - Fix DiffTest support for multi-channel CUTE and optimize area ([XSAI #93](https://github.com/OpenXiangShan/XSAI/pull/93), [CUTE #33](https://github.com/OpenXiangShan/CUTE/pull/33))
- Debugging tools
  - Implement MMA batching in DiffTest to reduce kernel launches ([difftest #920](https://github.com/OpenXiangShan/difftest/pull/920))
  - Implement backpressure to prevent unbounded queue growth when the MMA backend has insufficient throughput ([difftest #923](https://github.com/OpenXiangShan/difftest/pull/923))

### Basic Design

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | ff4720da4  |
| Date                 | 2026/08/17 |
| L1 ICache            | 64KB       |
| L1 DCache            | 64KB       |
| L2 Cache             | 2MB        |
| L3 Cache             | 16MB       |
| LSU                  | 3ld2st     |
| Bus protocol         | CHI        |
| Memory configuration | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 52.73  |        | 410.bwaves         | 120.79 |        |
| 401.bzip2           | 30.01  |        | 416.gamess         | 58.36  |        |
| 403.gcc             | 57.23  |        | 433.milc           | 71.04  |        |
| 429.mcf             | 73.02  |        | 434.zeusmp         | 78.12  |        |
| 445.gobmk           | 39.94  |        | 435.gromacs        | 38.27  |        |
| 456.hmmer           | 55.34  |        | 436.cactusADM      | 80.63  |        |
| 458.sjeng           | 39.49  |        | 437.leslie3d       | 60.95  |        |
| 462.libquantum      | 138.67 |        | 444.namd           | 42.98  |        |
| 464.h264ref         | 70.17  |        | 447.dealII         | 74.57  |        |
| 471.omnetpp         | 48.87  |        | 450.soplex         | 60.27  |        |
| 473.astar           | 32.78  |        | 453.povray         | 76.58  |        |
| 483.xalancbmk       | 83.08  |        | 454.Calculix       | 42.77  |        |
| GEOMEAN             | 54.89  |        | 459.GemsFDTD       | 71.73  |        |
|                     |        |        | 465.tonto          | 54.23  |        |
|                     |        |        | 470.lbm            | 128.82 |        |
|                     |        |        | 481.wrf            | 61.79  |        |
|                     |        |        | 482.sphinx3        | 61.20  |        |
|                     |        |        | GEOMEAN            | 66.12  |        |

Compilation parameters are as follows:

| Parameters                  | GCC15       | XSCC                |
| --------------------------- | ----------- | ------------------- |
| Compiler                    | gcc15       | xscc                |
| Optimization level          | O3          | O3                  |
| Memory library              | jemalloc    | jemalloc            |
| -march                      | RV64GCB     | RV64GCB             |
| -ffp-contraction            | fast        | fast                |
| Linker optimization         | -flto       | -flto               |
| Floating-point optimization | -ffast-math | -ffast-math         |
| -mcpu                       | -           | xiangshan-kunminghu |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Yanjun Li, Jinhong Zeng, Zechen Yang, Hanle Zhang, Kunlin You, Yiming Yan
