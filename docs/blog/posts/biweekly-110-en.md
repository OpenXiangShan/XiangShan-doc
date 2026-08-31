---
slug: biweekly-110-en
date: 2026-09-01
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 110] 20260901

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 110th issue of the biweekly report.

<!-- more -->

## Recent Developments

### Frontend

- Bug fixes
  - Fix canonical-address checks for frontend PCs and add related simulation tests ([#6340](https://github.com/OpenXiangShan/XiangShan/pull/6340))
  - Add the `notCfiTaken` signal to the IFU redirect `canTrain` condition ([#6398](https://github.com/OpenXiangShan/XiangShan/pull/6398))
  - Flush pending write requests when resetting TAGE useful counters to prevent stale requests from overwriting the reset results ([#6377](https://github.com/OpenXiangShan/XiangShan/pull/6377))
  - Prevent TAGE from rereading the prediction table when using the base prediction ([#6356](https://github.com/OpenXiangShan/XiangShan/pull/6356))
  - Prevent a spurious `s3_override` when both BPU S1 and S3 predict not taken ([#6417](https://github.com/OpenXiangShan/XiangShan/pull/6417))
  - Update BTB replacement state on training accesses instead of prediction accesses ([#6348](https://github.com/OpenXiangShan/XiangShan/pull/6348))
- Performance optimizations
  - Maintain `UseAltOnNa` based on predictor-table training state to reduce branch aliasing and register overhead ([#6328](https://github.com/OpenXiangShan/XiangShan/pull/6328))
  - Train the uBTB through both the resolve and fast-train paths to reduce extra bubbles after a misprediction redirect ([#6237](https://github.com/OpenXiangShan/XiangShan/pull/6237))
- PPA optimizations
  - Precompute `t0_firstMispredictMask` to improve the timing of the FTQ-to-BPU train-cache write path ([#6375](https://github.com/OpenXiangShan/XiangShan/pull/6375))
  - Move the pre-decode and `maybeRvc` logic and register ICache data to improve the timing of the IFU/ICache instruction-alignment path ([#6220](https://github.com/OpenXiangShan/XiangShan/pull/6220))
- Code refactoring
  - Move `vtype` generation from Decode to the IBuffer so each instruction carries its corresponding `vtype` and `specvtype` ([#6376](https://github.com/OpenXiangShan/XiangShan/pull/6376))
  - Use a PNR pointer to determine 2-prefetch and 2-fetch eligibility instead of a fixed distance from the BPU pointer ([#6378](https://github.com/OpenXiangShan/XiangShan/pull/6378))

### Backend

### MemBlock and Cache

- RTL features
  - Increase the configured openLLC capacity to 32 MB ([#6401](https://github.com/OpenXiangShan/XiangShan/pull/6401))
  - Implement and integrate a dedicated L3 stash prefetch path, including the L1-side bridge, CHI StashOnceShared requests, and openLLC stash-refill handling ([XSCache #25](https://github.com/OpenXiangShan/XSCache/pull/25), [#6274](https://github.com/OpenXiangShan/XiangShan/pull/6274))
  - Add performance counters for TLBs, request filters, page-table walkers, and L2TLB completion paths, and correct the PageCache hit conditions ([#6383](https://github.com/OpenXiangShan/XiangShan/pull/6383))
  - Add an F-POP L2 prefetch feedback controller that adjusts prefetchers using hit, latency, pollution, and contention feedback ([XSCache #24](https://github.com/OpenXiangShan/XSCache/pull/24))
- Bug fixes
  - Align the CSR-change TLB flush latency between the frontend and MemBlock to prevent old-epoch PTW requests from crossing the flush boundary ([#6421](https://github.com/OpenXiangShan/XiangShan/pull/6421))
  - Fix the L3 prefetch receive-port generation condition and check normal MSHR TxnIDs against the stash-reserved space before encoding ([XSCache #28](https://github.com/OpenXiangShan/XSCache/pull/28))
  - Fix a deadlock in which a non-oldest cross-page unaligned store injects a tail request and continuously blocks the oldest request ([#6382](https://github.com/OpenXiangShan/XiangShan/pull/6382))
  - Complete the prefetch request-enable vector so request enables remain synchronized across six prefetchers ([XSCache #27](https://github.com/OpenXiangShan/XSCache/pull/27))
  - Allow secondary-miss merging only when the MissEntry request is valid ([#6308](https://github.com/OpenXiangShan/XiangShan/pull/6308))
  - (V2) Kill an unfinished hardware-prefetch request when VSegment takes over DCache load port 0 ([#6389](https://github.com/OpenXiangShan/XiangShan/pull/6389))
- Timing Optimizations
  - Change DCache WritebackQueue release arbitration from round-robin to lowest-index-first ([#6379](https://github.com/OpenXiangShan/XiangShan/pull/6379))

### XSAI

- Bug fixes
  - Fix the MLCT transposed data layout and C MatrixReg read addresses for MSC/MSCT ([XSAI #106](https://github.com/OpenXiangShan/XSAI/pull/106), [CUTE #38](https://github.com/OpenXiangShan/CUTE/pull/38))
  - Fix misdecoding of `msetcfg`/`mgetcfg` ([XSAI #107](https://github.com/OpenXiangShan/XSAI/pull/107))
  - Fix state desynchronization between matrix memory-access `AccessAckData` responses and HintQueue ([XSAI #110](https://github.com/OpenXiangShan/XSAI/pull/110), [XSAICache #6](https://github.com/OpenXiangShan/XSAICache/pull/6))
  - Fix missed wakeups for delayed Mx operand writebacks that could permanently block MLS instructions ([XSAI #111](https://github.com/OpenXiangShan/XSAI/pull/111))
- Code quality
  - Remove unused matrix commit and scheduler feedback interfaces ([XSAI #113](https://github.com/OpenXiangShan/XSAI/pull/113))
  - Optimize CI: parallelize EMU and nightly regressions ([XSAI #114](https://github.com/OpenXiangShan/XSAI/pull/114), [XSAI #116](https://github.com/OpenXiangShan/XSAI/pull/116))
- Debugging tools
  - Add AME `mcfg` state comparison to DiffTest ([XSAI #107](https://github.com/OpenXiangShan/XSAI/pull/107), [difftest #944](https://github.com/OpenXiangShan/difftest/pull/944), [NEMU #1172](https://github.com/OpenXiangShan/NEMU/pull/1172))
  - Support 16-byte store checker events ([XSAI #112](https://github.com/OpenXiangShan/XSAI/pull/112))
  - Handle MMA operand retrieval failures and improve AMU event diagnostics ([difftest #926](https://github.com/OpenXiangShan/difftest/pull/926), [difftest #927](https://github.com/OpenXiangShan/difftest/pull/927))

### Infra

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options |
| -------------------- | ------- |
| Commit               |         |
| Date                 |         |
| L1 ICache            |         |
| L1 DCache            |         |
| L2 Cache             |         |
| L3 Cache             |         |
| LSU                  |         |
| Bus protocol         |         |
| Memory configuration |         |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC15 | XSCC | SPECfp 2006 @ 3GHz | GCC15 | XSCC |
| :------------------ | :---: | :--: | :----------------- | :---: | :--: |
| 400.perlbench       |       |      | 410.bwaves         |       |      |
| 401.bzip2           |       |      | 416.gamess         |       |      |
| 403.gcc             |       |      | 433.milc           |       |      |
| 429.mcf             |       |      | 434.zeusmp         |       |      |
| 445.gobmk           |       |      | 435.gromacs        |       |      |
| 456.hmmer           |       |      | 436.cactusADM      |       |      |
| 458.sjeng           |       |      | 437.leslie3d       |       |      |
| 462.libquantum      |       |      | 444.namd           |       |      |
| 464.h264ref         |       |      | 447.dealII         |       |      |
| 471.omnetpp         |       |      | 450.soplex         |       |      |
| 473.astar           |       |      | 453.povray         |       |      |
| 483.xalancbmk       |       |      | 454.Calculix       |       |      |
| GEOMEAN             |       |      | 459.GemsFDTD       |       |      |
|                     |       |      | 465.tonto          |       |      |
|                     |       |      | 470.lbm            |       |      |
|                     |       |      | 481.wrf            |       |      |
|                     |       |      | 482.sphinx3        |       |      |
|                     |       |      | GEOMEAN            |       |      |

Compilation parameters are as follows:

| Parameters                  | GCC15 | XSCC |
| --------------------------- | ----- | ---- |
| Compiler                    |       |      |
| Optimization level          |       |      |
| Memory library              |       |      |
| -march                      |       |      |
| -ffp-contraction            |       |      |
| Linker optimization         |       |      |
| Floating-point optimization |       |      |
| -mcpu                       |       |      |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Yanjun Li, Jinhong Zeng, Zechen Yang, Hanle Zhang, Kunlin You, Yiming Yan
