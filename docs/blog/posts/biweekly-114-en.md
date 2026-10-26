---
slug: biweekly-114-en
date: 2026-10-28
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 114] 20261028

Welcome to the XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 114th issue of the biweekly report.

<!-- TODO: Summarize the development highlights for this issue. -->

<!-- more -->

## Recent Developments

### Frontend

- TODO

### Backend

- TODO

### MemBlock and Cache

- TODO

### XSAI

- TODO

### Infra

- FPGA DiffTest
  - Add dynamically switchable FAST/SLOW reference execution modes and fork-based parallel checking for single-core XDMA configurations. SLOW workers fully check the DUT, validate results in segment order, and can take over when FAST execution diverges ([difftest #980](https://github.com/OpenXiangShan/difftest/pull/980), [NEMU #1247](https://github.com/OpenXiangShan/NEMU/pull/1247))
  - Support recording and standalone replay of single-core REF-driving traces, capturing the DUT windows that drive the reference model in SLOW, FAST, and FORK modes, with plain and ZSTD-compressed storage ([difftest #981](https://github.com/OpenXiangShan/difftest/pull/981))
- NEMU Reference Model
  - Add mainline Kunminghu V2 configurations for single-core and dual-core REF/debug REF and standalone execution, integrate the reference models into CI builds and releases, separate V2/V3 behavior differences through individual feature options, and share fixes for HLVX permissions, LR atomic-access permissions, double traps, and vector-store state handling ([NEMU #1246](https://github.com/OpenXiangShan/NEMU/pull/1246))
  - Fix lost first-page writes when non-segment, unit-stride vector stores fault across a page boundary, preserving completed partial writes and their DiffTest store records on both mainline and the Kunminghu V2 branch ([NEMU #1240](https://github.com/OpenXiangShan/NEMU/pull/1240), [NEMU #1241](https://github.com/OpenXiangShan/NEMU/pull/1241))
  - Optimize StoreHash software CRC checking by replacing nibble-wise table lookups with 64-bit word folding, reducing per-record checking overhead ([NEMU #1252](https://github.com/OpenXiangShan/NEMU/pull/1252))

### XS-GEM5

- TODO

## Performance Evaluation

<!-- TODO: Confirm the processor/SoC and compiler configurations, then fill in the commit, evaluation date, and performance scores. -->

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | TBD        |
| Date                 | TBD        |
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
| 400.perlbench        | TBD    | TBD    | 410.bwaves          | TBD    | TBD    |
| 401.bzip2            | TBD    | TBD    | 416.gamess          | TBD    | TBD    |
| 403.gcc              | TBD    | TBD    | 433.milc            | TBD    | TBD    |
| 429.mcf              | TBD    | TBD    | 434.zeusmp          | TBD    | TBD    |
| 445.gobmk            | TBD    | TBD    | 435.gromacs         | TBD    | TBD    |
| 456.hmmer            | TBD    | TBD    | 436.cactusADM       | TBD    | TBD    |
| 458.sjeng            | TBD    | TBD    | 437.leslie3d        | TBD    | TBD    |
| 462.libquantum       | TBD    | TBD    | 444.namd            | TBD    | TBD    |
| 464.h264ref          | TBD    | TBD    | 447.dealII          | TBD    | TBD    |
| 471.omnetpp          | TBD    | TBD    | 450.soplex          | TBD    | TBD    |
| 473.astar            | TBD    | TBD    | 453.povray          | TBD    | TBD    |
| 483.xalancbmk        | TBD    | TBD    | 454.calculix        | TBD    | TBD    |
| GEOMEAN              | TBD    | TBD    | 459.GemsFDTD        | TBD    | TBD    |
|                      |        |        | 465.tonto           | TBD    | TBD    |
|                      |        |        | 470.lbm             | TBD    | TBD    |
|                      |        |        | 481.wrf             | TBD    | TBD    |
|                      |        |        | 482.sphinx3         | TBD    | TBD    |
|                      |        |        | GEOMEAN             | TBD    | TBD    |

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
