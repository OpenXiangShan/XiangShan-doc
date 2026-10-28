---
slug: biweekly-114-en
date: 2026-10-28
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 114] 20261028

Welcome to the XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 114th issue of the biweekly report.

RISC-V Summit China 2026 was successfully held from October 18 to 20 at the Shenzhen Convention and Exhibition Center (Futian). Researcher Bao Yungang, Deputy Director of the Institute of Computing Technology, Chinese Academy of Sciences, and Chief Scientist of the Beijing Institute of Open Source Chip, delivered a talk at the XiangShan Ruyi Ecosystem Conference titled "RISC-V: A 12-Year Journey of Understanding and a 10-Year Outlook on Trends (2015-2035)" (translated from the Chinese title). He reviewed the development of RISC-V, discussed industry trends through 2035, and shared his perspectives on the evolution of open-source chip technology and the industry.

![Bao Yungang presenting at the XiangShan Ruyi Ecosystem Conference](./figs/biweekly-114/rvsc1.jpg)

During the summit, the XiangShan team hosted the XiangShan Processor Session, featuring presentations on the evolution of XiangShan's high-performance architecture and industrial-grade validation practices. All presentation slides from the session are now publicly available in [Talks-and-Publications](https://github.com/OpenXiangShan/Talks-and-Publications).

![Team photo](./figs/biweekly-114/rvsc2.jpg)

Recent XiangShan development includes frontend fixes for address sign extension, ICache ECC checks, and exception propagation; backend support for `mnret` and `dret` in the new decoder and an increase in the default ROB capacity to 160 entries; banked CoupledL2 SRAMs and a custom L1–L2 interconnect, alongside fixes for StoreQueue forwarding and fault-address reporting; and an independent asynchronous CUTE clock domain, improved multi-channel memory access scheduling and matrix register writes, and enhanced matrix verification and debugging tools in XSAI. Infrastructure updates strengthen FPGA DiffTest parallel checking and trace recording/replay, improve Kunminghu V2 reference-model integration, fix vector-store exception handling, and optimize store checking.

<!-- more -->

## Recent Developments

### Frontend

- Bug fixes
  - (V2) Preserve the true PC guard bit through the BPU, IFU, and RAS paths, fixing incorrect sign extension of VS Bare / Sv48x4 addresses that could produce invalid fetch addresses and corrupt `mepc` after RAS recovery ([#6720](https://github.com/OpenXiangShan/XiangShan/pull/6720))
  - Pass the actual fetch-block end offset to ICache data ECC checks, fixing incorrect bank selection caused by using the request-valid signal as the offset ([#6635](https://github.com/OpenXiangShan/XiangShan/pull/6635))
  - Propagate ICache ITLB/PMP and TileLink exceptions separately for each fetch request, fixing exception propagation for the second fetch request and accumulating refill exceptions per request ([#6414](https://github.com/OpenXiangShan/XiangShan/pull/6414))

### Backend

- Bug fixes
  - (V3) Add the missing decode tables and micro-op mappings for Smrnmi's `mnret` and Sdext's `dret` instructions in the new decoder ([#6692](https://github.com/OpenXiangShan/XiangShan/pull/6692))
- Performance optimizations
  - (V3) Increase the default ROB capacity from 144 to 160 entries ([#6730](https://github.com/OpenXiangShan/XiangShan/pull/6730))

### MemBlock and Cache

- RTL features
  - Add set-banked Directory/Data SRAMs, hint-queue backpressure, and prefetch-admission throttling to CoupledL2, and integrate them into XiangShan ([XSCache #36](https://github.com/OpenXiangShan/XSCache/pull/36), [#6738](https://github.com/OpenXiangShan/XiangShan/pull/6738))
  - Replace the generic L1–L2 interconnect with CustomL1L2Fabric and add miss tracking, resource reservation, and a cancellable speculative A-channel buffer to shorten the DCache-to-L2 request path ([#6713](https://github.com/OpenXiangShan/XiangShan/pull/6713))
- Bug fixes
  - Compare virtual- and physical-address match masks over the same StoreQueue candidate domain and replay on disagreement, fixing loads forwarding stale store data under address aliasing ([#6693](https://github.com/OpenXiangShan/XiangShan/pull/6693))
  - Carry the TLB's pointer-masked address through subsequent StoreUnit stages so store and CBO faults report the correct address in `mtval`/`stval` ([#6742](https://github.com/OpenXiangShan/XiangShan/pull/6742))

### XSAI

- RTL features
  - Support an independent asynchronous clock domain for CUTE ([CUTE #44](https://github.com/OpenXiangShan/CUTE/pull/44), [XSAI #135](https://github.com/OpenXiangShan/XSAI/pull/135))
  - Optimize CUTE multi-channel memory access scheduling and matrix register writes, with corresponding DiffTest updates ([CUTE #46](https://github.com/OpenXiangShan/CUTE/pull/46), [difftest #991](https://github.com/OpenXiangShan/difftest/pull/991), [XSAI #136](https://github.com/OpenXiangShan/XSAI/pull/136))
- Bug fixes
  - Fix HintQueue capacity reservation and retry handling in XSAICache, and restore the global enable control for matrix prefetching ([XSAICache #10](https://github.com/OpenXiangShan/XSAICache/pull/10))
- Debugging tools
  - Speed up NEMU matrix register hash computation ([NEMU #1248](https://github.com/OpenXiangShan/NEMU/pull/1248))
  - Enable DiffTest Delta transfers for matrix CSR and configuration states ([difftest #985](https://github.com/OpenXiangShan/difftest/pull/985), [XSAI #134](https://github.com/OpenXiangShan/XSAI/pull/134))
  - Fix incomplete memory restoration when rolling back NEMU matrix stores ([NEMU #1251](https://github.com/OpenXiangShan/NEMU/pull/1251))
  - Fix duplicate event recording and skipped events under backpressure in DiffTest Replay ([difftest #990](https://github.com/OpenXiangShan/difftest/pull/990))
  - Optimize memory management, data copying, and compute kernels in the DiffTest MMA verification backend ([difftest #994](https://github.com/OpenXiangShan/difftest/pull/994), [difftest #996](https://github.com/OpenXiangShan/difftest/pull/996), [difftest #999](https://github.com/OpenXiangShan/difftest/pull/999), [difftest #1000](https://github.com/OpenXiangShan/difftest/pull/1000), [difftest #1001](https://github.com/OpenXiangShan/difftest/pull/1001), [difftest #1002](https://github.com/OpenXiangShan/difftest/pull/1002))
  - Improve initialization of optional source code and test dependencies in xsai-env ([xsai-env #1](https://github.com/OpenXiangShan/xsai-env/pull/1), [xsai-env #2](https://github.com/OpenXiangShan/xsai-env/pull/2))
- Code quality
  - Refactor NEMU matrix memory access interfaces to separate event dispatch from physical memory access ([NEMU #1249](https://github.com/OpenXiangShan/NEMU/pull/1249))

### Infra

- FPGA DiffTest
  - Add dynamically switchable FAST/SLOW reference execution modes and fork-based parallel checking for single-core XDMA configurations. SLOW workers fully check the DUT, validate results in segment order, and can take over when FAST execution diverges ([difftest #980](https://github.com/OpenXiangShan/difftest/pull/980), [NEMU #1247](https://github.com/OpenXiangShan/NEMU/pull/1247))
  - Support recording and standalone replay of single-core REF-driving traces, capturing the DUT windows that drive the reference model in SLOW, FAST, and FORK modes, with plain and ZSTD-compressed storage ([difftest #981](https://github.com/OpenXiangShan/difftest/pull/981))
  - Add BOOM DiffTest configuration and FPGA board-interface support, adapt initial-commit comparison and timeout handling, share CPU-side AXI width definitions, and connect memory and MMIO interfaces to DDR and UART16550 respectively ([difftest #998](https://github.com/OpenXiangShan/difftest/pull/998), [env-scripts #192](https://github.com/OpenXiangShan/env-scripts/pull/192), [rocket-chip #46](https://github.com/OpenXiangShan/rocket-chip/pull/46))
- NEMU Reference Model
  - Add mainline Kunminghu V2 configurations for single-core and dual-core REF/debug REF and standalone execution, integrate the reference models into CI builds and releases, separate V2/V3 behavior differences through individual feature options, and share fixes for HLVX permissions, LR atomic-access permissions, double traps, and vector-store state handling ([NEMU #1246](https://github.com/OpenXiangShan/NEMU/pull/1246))
  - Fix lost first-page writes when non-segment, unit-stride vector stores fault across a page boundary, preserving completed partial writes and their DiffTest store records on both mainline and the Kunminghu V2 branch ([NEMU #1240](https://github.com/OpenXiangShan/NEMU/pull/1240), [NEMU #1241](https://github.com/OpenXiangShan/NEMU/pull/1241))
  - Optimize StoreHash software CRC checking by replacing nibble-wise table lookups with 64-bit word folding, reducing per-record checking overhead ([NEMU #1252](https://github.com/OpenXiangShan/NEMU/pull/1252))
  - Organize NEMU configurations into shared base, processor-version, and feature layers to reduce duplication, and add `make config-check` to validate composition, dependencies, and effective values ([NEMU #1259](https://github.com/OpenXiangShan/NEMU/pull/1259))
  - Expand guest memory in the diff-spike configuration to 32 GiB and synchronize reference-model memory size during initialization, fixing SPEC checkpoint loading failures caused by images exceeding memory capacity ([NEMU #1267](https://github.com/OpenXiangShan/NEMU/pull/1267))
- Test Workloads, Sampling and Checkpointing
  - Add a BOOM v4 DiffTest platform device tree describing ISA, memory, and peripherals, with `DEFAULT_DTB=boom` selecting the platform for Linux workload builds ([workload-builder #81](https://github.com/OpenXiangShan/workload-builder/pull/81))
- Development and Debugging Tools
  - Carry descriptive metadata across module boundaries for HPM events, document TL/CHI L2 events, and provide an `hpm.csv` export utility ([Utility #157](https://github.com/OpenXiangShan/Utility/pull/157), [CoupledL2 #527](https://github.com/OpenXiangShan/CoupledL2/pull/527))
  - Fix C++11 build compatibility in shared checkers and REF-driving trace recording code, restoring the existing `libdifftest.so` build flow ([difftest #1003](https://github.com/OpenXiangShan/difftest/pull/1003))
- GSIM Simulator
  - Add FST simulation waveform generation with controls for enabling dumps, output paths, array size limits, and next-state signal filtering to aid simulation debugging ([gsim #109](https://github.com/OpenXiangShan/gsim/pull/109))
  - Support `%b` binary-format output, fixing assertion failures triggered by Chisel `Binary` formatting ([gsim #142](https://github.com/OpenXiangShan/gsim/pull/142))

### XS-GEM5

- Simulator Alignment
  - Align active-region qualification in the XsStream prefetcher ([XS-GEM5 #1223](https://github.com/OpenXiangShan/GEM5/pull/1223))
  - Enable per-thread MBTB victim caches and fix invalidation on shared MBTB writes ([XS-GEM5 #1235](https://github.com/OpenXiangShan/GEM5/pull/1235), [XS-GEM5 #1236](https://github.com/OpenXiangShan/GEM5/pull/1236))
- New Feature Exploration
  - Add MLP-aware SMT fetch policies and rework the BlockStall policy ([XS-GEM5 #1180](https://github.com/OpenXiangShan/GEM5/pull/1180)) [Thanks to our colleagues from Alibaba for their contribution]
  - Add middle-end resource partitioning for SpMT ([XS-GEM5 #1231](https://github.com/OpenXiangShan/GEM5/pull/1231)) [Thanks to our colleagues from Alibaba for their contribution]
  - Add Hybrid CROB support ([XS-GEM5 #1189](https://github.com/OpenXiangShan/GEM5/pull/1189))
- Bug Fixes
  - Fix uninitialized memory access sizes during delayed translation ([XS-GEM5 #1214](https://github.com/OpenXiangShan/GEM5/pull/1214))
  - Fix load replay states incorrectly set on store/AMO send failures ([XS-GEM5 #1241](https://github.com/OpenXiangShan/GEM5/pull/1241)) [Thanks to our colleagues from Alibaba for their contribution]
  - Fix SMT LSQ DynamicBorrowing donor detection ([XS-GEM5 #1257](https://github.com/OpenXiangShan/GEM5/pull/1257)) [Thanks to our colleagues from Alibaba for their contribution]
  - Fix decode efficiency and L2 TLB L0 miss statistics ([XS-GEM5 #1215](https://github.com/OpenXiangShan/GEM5/pull/1215))
- Infrastructure
  - Support RISC-V Zimop instructions ([XS-GEM5 #1224](https://github.com/OpenXiangShan/GEM5/pull/1224))
  - Improve trace-mode regressions and TRACERTL/NEMU trace support ([XS-GEM5 #1210](https://github.com/OpenXiangShan/GEM5/pull/1210), [XS-GEM5 #1211](https://github.com/OpenXiangShan/GEM5/pull/1211), [XS-GEM5 #1227](https://github.com/OpenXiangShan/GEM5/pull/1227))
  - Restore macOS builds and add manual smoke CI ([XS-GEM5 #1228](https://github.com/OpenXiangShan/GEM5/pull/1228))
  - Improve weekly performance regressions and PR Quick Check ([XS-GEM5 #1233](https://github.com/OpenXiangShan/GEM5/pull/1233), [XS-GEM5 #1237](https://github.com/OpenXiangShan/GEM5/pull/1237))

## Performance Evaluation

<!-- TODO: Confirm the processor/SoC and full compiler configurations. -->
<!-- Sources: cr261023-f85a1f71d-DefaultConfig/score-spec06-rva23-novec-gcc16-1.0c.txt and score-spec06-rv64gcb-xscc-1.0c.txt; multiply the original per-GHz scores by 3 and display two decimal places. -->

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | f85a1f71d  |
| Date                 | 2026/10/23 |
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
| 400.perlbench        | 57.53  | 60.40  | 410.bwaves          | 146.72 | 150.20 |
| 401.bzip2            | 30.95  | 32.28  | 416.gamess          | 61.81  | 57.66  |
| 403.gcc              | 64.24  | 62.22  | 433.milc            | 77.21  | 74.60  |
| 429.mcf              | 84.00  | 79.38  | 434.zeusmp          | 78.97  | 78.48  |
| 445.gobmk            | 45.78  | 44.21  | 435.gromacs         | 43.31  | 42.56  |
| 456.hmmer            | 55.18  | 67.22  | 436.cactusADM       | 89.34  | 95.97  |
| 458.sjeng            | 45.02  | 46.60  | 437.leslie3d        | 68.38  | 67.27  |
| 462.libquantum       | 167.32 | 381.31 | 444.namd            | 47.58  | 48.50  |
| 464.h264ref          | 69.68  | 73.92  | 447.dealII          | 85.14  | 163.77 |
| 471.omnetpp          | 59.22  | 60.62  | 450.soplex          | 69.18  | 80.89  |
| 473.astar            | 34.86  | 33.78  | 453.povray          | 79.90  | 69.32  |
| 483.xalancbmk        | 91.13  | 136.41 | 454.calculix        | 47.76  | 47.60  |
| GEOMEAN              | 60.48  | 68.41  | 459.GemsFDTD        | 82.64  | 82.59  |
|                      |        |        | 465.tonto           | 60.73  | 51.96  |
|                      |        |        | 470.lbm             | 128.11 | 151.49 |
|                      |        |        | 481.wrf             | 62.47  | 61.18  |
|                      |        |        | 482.sphinx3         | 68.15  | 98.99  |
|                      |        |        | GEOMEAN             | 72.56  | 76.95  |

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
