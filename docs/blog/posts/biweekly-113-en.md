---
slug: biweekly-113-en
date: 2026-10-14
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 113] 20261014

Welcome to the XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 113th issue of the biweekly report.

Regarding the recent development progress of XiangShan, the frontend added VictimBTB to reuse evicted MainBTB entries for branch prediction; the backend implemented a hybrid compressed ROB (CROB), optimized early wakeup and bypass for FMA, and fixed issues in floating-point conversions and instruction legality checks; the memory and cache subsystem added softTLB/softPTW simulation paths supporting two-stage address translation and fixed issues with TLB global attributes and rollback on memory access violations; XSAI integrated a matrix-guided L2 prefetcher and a standalone transpose load engine, while improving matrix debugging and hash comparison; infrastructure updates enhanced FPGA DiffTest, NEMU, Palladium, and AI-assisted debugging tools and fixed GSIM code generation issues; XS-GEM5 advanced model alignment for L2 prefetching and SBuffer behavior, fixed out-of-bounds register access during vector loads, and improved MMIO support, performance regression testing, and build checks.

During RISC-V Summit China 2026, the XiangShan Processor Session will be held on October 18. The session will feature presentations on the evolution of XiangShan's high-performance architecture and industrial-grade validation practices, the application of the UCAgent intelligent agent to XiangShan processors, and a hybrid RISC-V security verification platform for XiangShan processors.

Following the processor session, the XiangShan Developer Conference and XiangShan Ecosystem Conference will both be held on October 20. The XiangShan Developer Conference (09:00–12:30) will focus on technical co-development and sharing, featuring a review of the community’s annual development achievements, recognition of outstanding contributors, an SMT enterprise technology seminar, and the first presentation of the full-stack architectural evolution of the third-generation Kunminghu processor core IP. The XiangShan Ecosystem Conference (13:30–17:30) will focus on collaborative ecosystem building, with presentations on XiangShan and Ruyi technologies, in-depth discussions of foundational RISC-V + AI technologies, AI-themed talks, the launch of an open-source chip community, and a ceremony marking the launch of the Ruyi community co-construction initiative. Ecosystem partners and developers are welcome to follow the event updates and join us in person.

<!-- more -->

## Recent Developments

### Frontend

- RTL Features
  - (V3) Add a fully associative VictimBTB to retain evicted MainBTB branch entries and use them for prediction, with in-place training and duplicate-entry invalidation, and adapt the SC prediction and training paths ([#6587](https://github.com/OpenXiangShan/XiangShan/pull/6587))

### Backend

- RTL Features
  - (V3) Implement a hybrid compressed ROB (CROB) with ordinary compression and high-density compression for simple ALU instructions, adapting ordered retirement and DiffTest StoreEvent/ArchEvent handling to two-slot ROB entries ([#6648](https://github.com/OpenXiangShan/XiangShan/pull/6648))
- Bug Fixes
  - (V3) Reserve the FEX0 output slot for floating-point conversions targeting `x0`, ensuring resource occupancy is tracked even when no register is written ([#6649](https://github.com/OpenXiangShan/XiangShan/pull/6649))
  - (V3) Raise an illegal-instruction exception for `aes64ks1i` when its round-number immediate `rnum > 10`, and remove related dead decode logic ([#6687](https://github.com/OpenXiangShan/XiangShan/pull/6687))
  - (V3) Update yunsuan to select the CVT64Narrow shift bias based on the destination floating-point format, fixing incorrect FP32-to-FP16 subnormal conversions ([#6689](https://github.com/OpenXiangShan/XiangShan/pull/6689))
- Performance Optimizations
  - (V3) Add early wakeup and bypass paths from FMA, FMUL, and loads to FMA's third source operand (`src2`), allowing multiplication to start before the addend is ready, with replay handling for canceled loads ([#6679](https://github.com/OpenXiangShan/XiangShan/pull/6679))
- Code Refactoring
  - (V3) Remove the unused F2vCfg, vector writeback ports, and related type definitions and writeback-counting logic from FEX0 ([#6651](https://github.com/OpenXiangShan/XiangShan/pull/6651))
- Tool Updates
  - (V2) Update the NEMU reference model version in ready-to-run ([#6620](https://github.com/OpenXiangShan/XiangShan/pull/6620))

### MemBlock and Cache

- RTL Features
  - (V3) Add `softTLB`/`softPTW` simulation paths using DPI-C PteHelper, with support for two-stage address translation, to evaluate the upper bound on MMU translation performance ([#6115](https://github.com/OpenXiangShan/XiangShan/pull/6115))
- Bug Fixes
  - (V3) Gate the global attributes in the TLB and page-table cache with `PTE.V` to prevent fault entries for invalid PTEs from surviving ASID-specific `SFENCE.VMA` operations or incorrectly matching other ASIDs ([#6695](https://github.com/OpenXiangShan/XiangShan/pull/6695))
  - (V2) When the same load triggers concurrent RAR and RAW violations, prioritize the RAW rollback that re-fetches the current instruction to prevent the RAR rollback from masking the RAW violation and causing incorrect load data ([#6677](https://github.com/OpenXiangShan/XiangShan/pull/6677))

### XSAI

- RTL Features
  - Integrate a matrix-guided L2 prefetcher ([XSAI #124](https://github.com/OpenXiangShan/XSAI/pull/124), [XSAICache #7](https://github.com/OpenXiangShan/XSAICache/pull/7))
  - Implement a standalone transpose load engine with double-group buffering to support multi-channel transpose loads ([CUTE #43](https://github.com/OpenXiangShan/CUTE/pull/43), [XSAI #132](https://github.com/OpenXiangShan/XSAI/pull/132))
- Bug Fixes
  - Synchronize bug fixes from KMH-V2 ([XSAI #131](https://github.com/OpenXiangShan/XSAI/pull/131), [XSAICache #9](https://github.com/OpenXiangShan/XSAICache/pull/9))
- Debugging Tools
  - Fix the matrix completion event stride in DiffTest under MinimalMatrixConfig ([difftest #976](https://github.com/OpenXiangShan/difftest/pull/976))
  - Fix stale CSR values exported by NEMU after implicit state updates ([NEMU #1237](https://github.com/OpenXiangShan/NEMU/pull/1237))
  - Fix NEMU's handling of large zstd image reads ([NEMU #1239](https://github.com/OpenXiangShan/NEMU/pull/1239))
  - Support hash comparison of matrix register contents ([CUTE #45](https://github.com/OpenXiangShan/CUTE/pull/45), [difftest #978](https://github.com/OpenXiangShan/difftest/pull/978), [NEMU #1238](https://github.com/OpenXiangShan/NEMU/pull/1238), [XSAI #133](https://github.com/OpenXiangShan/XSAI/pull/133))

### Infra

- FPGA DiffTest
  - Add CRC-64 store hash checking for FPGA DiffTest, compressing store events into an ordered summary per core and Squash window and checking the corresponding store queue in NEMU to reduce verification data transfer ([difftest #973](https://github.com/OpenXiangShan/difftest/pull/973), [NEMU #1231](https://github.com/OpenXiangShan/NEMU/pull/1231))
  - Add an optional host backend for FPGA platform-specific transport, supporting register access, workload loading, and DiffTest packet reception through a common transport interface shared with XDMA ([difftest #954](https://github.com/OpenXiangShan/difftest/pull/954))
- NEMU Reference Model
  - Fix duplicate writes during store-log restoration by rolling back only records whose instruction counts exceed the restore point, preventing incorrect boundary-record writes and duplicate store-checking events ([NEMU #1250](https://github.com/OpenXiangShan/NEMU/pull/1250))
- Development and Debugging Tools
  - Improve the Palladium (PLDM) build and release flow, fix issues with disabled DiffTest, clock gating, and DPI library linking, add the `pldm-lib` target for software-only library rebuilds, and document runtime and waveform debugging ([difftest #982](https://github.com/OpenXiangShan/difftest/pull/982))
  - Improve the XiangShan AI-assisted debugging skill with single-case reproduction and evidence-driven root-cause analysis, add guidance for FSDB trimming, format conversion, and point-in-time waveform analysis, and standardize the documentation in English ([minjie-playground #39](https://github.com/OpenXiangShan/minjie-playground/pull/39), [minjie-playground #40](https://github.com/OpenXiangShan/minjie-playground/pull/40))
  - Simplify the DiffTest AI development workflow documentation while retaining plan and progress-log requirements, removing prescribed file paths and the requirement to use a specific confirmation tool ([difftest #984](https://github.com/OpenXiangShan/difftest/pull/984))
- GSIM Simulator
  - Support dynamic-index writes when splitting one-dimensional arrays with up to 4096 elements, fix code generation instability caused by dependency construction and traversal order, and fix `DEBUG=1` builds ([gsim #138](https://github.com/OpenXiangShan/gsim/pull/138))
  - Fix full-width `bits()` slices of signed values that incorrectly retain C++ sign-extension bits by generating masks according to FIRRTL's unsigned-result semantics, preventing incorrect concatenation results, and add a regression test covering all 32 five-bit input values ([gsim #141](https://github.com/OpenXiangShan/gsim/pull/141))

### XS-GEM5

- Simulator Alignment
  - Align the configuration for offloading low-accuracy L2 prefetches ([XS-GEM5 #1183](https://github.com/OpenXiangShan/GEM5/pull/1183))
  - Align same-cache-line SBuffer store-miss merging behavior ([XS-GEM5 #1171](https://github.com/OpenXiangShan/GEM5/pull/1171))
- Bug Fixes
  - Fix a rename panic caused by out-of-bounds register access during vector loads ([XS-GEM5 #1185](https://github.com/OpenXiangShan/GEM5/pull/1185))
  - Support 32-bit UARTLite MMIO accesses ([XS-GEM5 #1199](https://github.com/OpenXiangShan/GEM5/pull/1199))
- Infrastructure
  - Update the weekly performance regression configuration ([XS-GEM5 #1188](https://github.com/OpenXiangShan/GEM5/pull/1188))
  - Add Clang `gem5.fast` build checks ([XS-GEM5 #1209](https://github.com/OpenXiangShan/GEM5/pull/1209))
  - Improve the workflow for generating daily repository reports in Chinese ([XS-GEM5 #1204](https://github.com/OpenXiangShan/GEM5/pull/1204), [XS-GEM5 #1212](https://github.com/OpenXiangShan/GEM5/pull/1212))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | 244af70c1  |
| Date                 | 2026/10/09 |
| L1 ICache            | 64 KB      |
| L1 DCache            | 64 KB      |
| L2 Cache             | 2 MB       |
| L3 Cache             | 32 MB      |
| LSU                  | 3ld2st     |
| Bus protocol         | CHI        |
| Memory configuration | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        | 57.26  | 59.16  | 410.bwaves          | 142.94 | 148.07 |
| 401.bzip2            | 30.50  | 32.49  | 416.gamess          | 61.09  | 57.56  |
| 403.gcc              | 62.17  | 44.57  | 433.milc            | 76.24  | 86.48  |
| 429.mcf              | 78.05  | 70.32  | 434.zeusmp          | 78.10  | 79.78  |
| 445.gobmk            | 45.44  | 44.31  | 435.gromacs         | 42.71  | 39.24  |
| 456.hmmer            | 54.81  | 68.29  | 436.cactusADM       | 88.79  | 94.21  |
| 458.sjeng            | 43.17  | 46.04  | 437.leslie3d        | 66.80  | 68.43  |
| 462.libquantum       | 167.36 | 380.91 | 444.namd            | 47.33  | 48.38  |
| 464.h264ref          | 69.39  | 73.54  | 447.dealII          | 68.47  | 104.83 |
| 471.omnetpp          | 56.25  | 56.73  | 450.soplex          | 66.90  | 80.62  |
| 473.astar            | 34.26  | 33.91  | 453.povray          | 80.45  | 73.88  |
| 483.xalancbmk        | 88.29  | 118.65 | 454.calculix        | 46.61  | 43.31  |
| GEOMEAN              | 59.06  | 64.69  | 459.GemsFDTD        | 80.98  | 81.83  |
|                      |        |        | 465.tonto           | 59.80  | 46.98  |
|                      |        |        | 470.lbm             | 127.54 | 153.93 |
|                      |        |        | 481.wrf             | 61.18  | 63.67  |
|                      |        |        | 482.sphinx3         | 65.33  | 64.67  |
|                      |        |        | GEOMEAN             | 70.53  | 72.99  |

Compilation parameters are as follows:

| Parameters                  | GCC16                         | XSCC                |
| --------------------------- | ----------------------------- | ------------------- |
| Compiler                    | gcc16                         | xscc                |
| Optimization level          | O3                            | O3                  |
| Memory library              | jemalloc                      | jemalloc            |
| ISA configuration           | RVA23-based (vector disabled) | RV64GCB             |
| -ffp-contract               | fast                          | fast                |
| Linker optimization         | -flto                         | -flto               |
| Floating-point optimization | -ffast-math                   | -ffast-math         |
| -mcpu                       | -                             | xiangshan-kunminghu |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Yanjun Li, Jinhong Zeng, Zechen Yang, Hanle Zhang, Kunlin You, Xin Li, Yiming Yan
