---
slug: biweekly-113-en
date: 2026-10-14
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 113] 20261014

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 113th issue of the biweekly report.

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
  - (V3) Update yunsuan to select the CVT64Narrow shift bias by the destination floating-point format, fixing incorrect FP32-to-FP16 subnormal conversions ([#6689](https://github.com/OpenXiangShan/XiangShan/pull/6689))
- Performance Optimizations
  - (V3) Add early wakeup and bypass paths from FMA, FMUL, and loads to FMA's third source operand (`src2`), allowing multiplication to start before the addend is ready, with replay handling for canceled loads ([#6679](https://github.com/OpenXiangShan/XiangShan/pull/6679))
- Code Refactoring
  - (V3) Remove the unused F2vCfg, vector writeback ports, and related type definitions and writeback-counting logic from FEX0 ([#6651](https://github.com/OpenXiangShan/XiangShan/pull/6651))
- Tool Updates
  - (V2) Update the NEMU reference model version in ready-to-run ([#6620](https://github.com/OpenXiangShan/XiangShan/pull/6620))

### MemBlock and Cache

- RTL Features
  - Add DPI-C PteHelper-backed `softTLB`/`softPTW` simulation translation paths with two-stage address translation support for evaluating the MMU translation performance upper bound ([#6115](https://github.com/OpenXiangShan/XiangShan/pull/6115))

- Bug Fixes
  - Gate cached TLB and page-table global attributes with `PTE.V` to prevent invalid-PTE fault entries from surviving ASID-specific `SFENCE.VMA` or incorrectly matching other ASIDs ([#6695](https://github.com/OpenXiangShan/XiangShan/pull/6695))
  - (V2) When the same load triggers concurrent RAR and RAW violations, prioritize the RAW rollback that re-fetches the current instruction to prevent the RAR rollback from masking the RAW violation and causing incorrect load data ([#6677](https://github.com/OpenXiangShan/XiangShan/pull/6677))

### XSAI

- RTL features
  - Integrate a matrix-guided L2 prefetcher ([XSAI #124](https://github.com/OpenXiangShan/XSAI/pull/124), [XSAICache #7](https://github.com/OpenXiangShan/XSAICache/pull/7))
  - Implement a standalone transpose load engine with double-group buffering to support multi-channel transpose loads ([CUTE #43](https://github.com/OpenXiangShan/CUTE/pull/43), [XSAI #132](https://github.com/OpenXiangShan/XSAI/pull/132))
- Bug fixes
  - Synchronize bug fixes from KMH-V2 ([XSAI #131](https://github.com/OpenXiangShan/XSAI/pull/131), [XSAICache #9](https://github.com/OpenXiangShan/XSAICache/pull/9))
- Debugging tools
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
  - Fix full-width `bits()` slices of signed values retaining C++ sign-extension bits by generating masks according to FIRRTL's unsigned-result semantics, preventing incorrect concatenation results, and add a regression covering all 32 five-bit input values ([gsim #141](https://github.com/OpenXiangShan/gsim/pull/141))

### XS-GEM5

- Simulator alignment
  - Align the configuration for offloading low-accuracy L2 prefetches ([XS-GEM5 #1183](https://github.com/OpenXiangShan/GEM5/pull/1183))
  - Align same-cache-line SBuffer store-miss merging behavior ([XS-GEM5 #1171](https://github.com/OpenXiangShan/GEM5/pull/1171))
- Bug fixes
  - Fix vector load register overflow causing a rename panic ([XS-GEM5 #1185](https://github.com/OpenXiangShan/GEM5/pull/1185))
  - Support 32-bit UARTLite MMIO accesses ([XS-GEM5 #1199](https://github.com/OpenXiangShan/GEM5/pull/1199))
- Infrastructure
  - Update the weekly performance regression configuration ([XS-GEM5 #1188](https://github.com/OpenXiangShan/GEM5/pull/1188))
  - Add Clang `gem5.fast` build checks ([XS-GEM5 #1209](https://github.com/OpenXiangShan/GEM5/pull/1209))
  - Improve the Chinese repository report generation flow ([XS-GEM5 #1204](https://github.com/OpenXiangShan/GEM5/pull/1204), [XS-GEM5 #1212](https://github.com/OpenXiangShan/GEM5/pull/1212))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               |            |
| Date                 |            |
| L1 ICache            |            |
| L1 DCache            |            |
| L2 Cache             |            |
| L3 Cache             |            |
| LSU                  |            |
| Bus protocol         |            |
| Memory configuration |            |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        |        |        | 410.bwaves          |        |        |
| 401.bzip2            |        |        | 416.gamess          |        |        |
| 403.gcc              |        |        | 433.milc            |        |        |
| 429.mcf              |        |        | 434.zeusmp          |        |        |
| 445.gobmk            |        |        | 435.gromacs         |        |        |
| 456.hmmer            |        |        | 436.cactusADM       |        |        |
| 458.sjeng            |        |        | 437.leslie3d        |        |        |
| 462.libquantum       |        |        | 444.namd            |        |        |
| 464.h264ref          |        |        | 447.dealII          |        |        |
| 471.omnetpp          |        |        | 450.soplex          |        |        |
| 473.astar            |        |        | 453.povray          |        |        |
| 483.xalancbmk        |        |        | 454.calculix        |        |        |
| GEOMEAN              |        |        | 459.GemsFDTD        |        |        |
|                      |        |        | 465.tonto           |        |        |
|                      |        |        | 470.lbm             |        |        |
|                      |        |        | 481.wrf             |        |        |
|                      |        |        | 482.sphinx3         |        |        |
|                      |        |        | GEOMEAN             |        |        |

Compilation parameters are as follows:

| Parameters                  | GCC16                         | XSCC                |
| --------------------------- | ----------------------------- | ------------------- |
| Compiler                    |                               |                     |
| Optimization level          |                               |                     |
| Memory library              |                               |                     |
| ISA configuration           |                               |                     |
| -ffp-contract               |                               |                     |
| Linker optimization         |                               |                     |
| Floating-point optimization |                               |                     |
| -mcpu                       |                               |                     |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors:
