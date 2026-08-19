---
slug: biweekly-109-en
date: 2026-08-19
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 109] Infrastructure Joins the XiangShan Biweekly!

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 109th issue of the biweekly report.

This issue features a special section on infrastructure, focusing on the agile chip development platform built by the XiangShan team around hardware description languages, functional verification, and performance exploration. Starting with this issue, the biweekly report will also include updates on infrastructure development.

Regarding the recent development progress of XiangShan, the frontend continues to fix bugs and optimize critical-path timing; the backend adds features such as pointer-masking extensions and expands TopDown analysis; the memory and cache subsystem integrates the L2 CDP prefetcher and fixes several bugs; XSAI supports multi-precision transposed loads and improves multi-channel DiffTest and MMA debugging capabilities.

<!-- more -->

## Infrastructure: Agile Chip Development Platform

The XiangShan team proposes an “iceberg model” for open-source chip R&D. Instead of treating PPA (Performance, Power, Area) as the sole design objective, the team has developed a methodology that jointly considers PPA and agility (time, cost, and complexity). This approach values both the chip results above the waterline and the development infrastructure beneath it. The team builds the agile platform around three pillars—hardware description language (HDL), functional verification, and performance exploration—to shorten the cycle of design simulation and debugging.

![aPPA](./figs/biweekly-109/aPPA.png)

On HDL, XiangShan uses the Chisel hardware construction language to describe processor designs. To address the multicore dedup problem in elaboration, long compile times, and missing intermediate signals, the team works on the Chisel compilation path, exploring multicore RTL reuse, faster compilation, and intermediate-signal retention to improve construction speed, usability, and reliability.

On functional verification, the team built DiffTest, a differential-testing framework that compares the design under test (XiangShan) with a reference model (NEMU). By comparing architectural state instruction by instruction, DiffTest quickly finds and localizes functional bugs. Recent work includes:

- FPGA-accelerated verification: FPGA acceleration of DUT simulation, differentially tested against a software reference model. The team has delivered an FPGA DiffTest solution for Kunminghu v2 System-level test (ST), supporting complex workloads such as Linux and SPECCPU. It can capture waveforms for millions of cycles before the failing instruction, currently runs at 5–10 MHz, and is more than 1,000× faster than software simulation.
- Multicore verification algorithms: To reduce false positives in existing multicore DiffTest, the team refined checking of multicore memory-access events and supports fine-grained checks based on the RVWMO memory model. The work has been adapted to Yanqihu and is being brought onto the Kunminghu v3 mainline.

On performance exploration, the team evaluates performance with workloads such as SPECCPU. These workloads are long-running and usually require lengthy boot and warmup, so simulating from scratch is expensive. The team therefore optimizes sampling/checkpointing and simulation tools:

- NEMU ISA simulator: a software reference implementation of the RVA23 Profile. It supports workload execution, sampling and checkpointing, and differential testing, and continues functional alignment and performance work around hypervisor, vector, and AIA.
- XS-GEM5 architectural simulator: an open-source, industrial-grade architectural simulator with full RVA23 support. Performance versus XiangShan on SPEC 06/17 is under 5%. It supports architecture exploration and evaluation of optimization strategies.
- Sampling and checkpointing: supports saving architectural state at SimPoint sample points so simulation can jump quickly into the target phase. The team has established checkpoint generation, state restore, and result-validation flows for both single-core and multicore, covering SPEC CPU2006/2017/2026, RVA23, vector, and hypervisor.
- GSIM simulator: a FIRRTL-based RTL simulator that fully supports XiangShan’s verification tools, including DiffTest. Single-threaded GSIM is substantially faster than single-threaded Verilator and comparable to multi-threaded Verilator while using far fewer server resources. Process-level parallelism enables fast, checkpoint-based performance evaluation.

Related code is open source:

- MinJie development platform: <https://github.com/OpenXiangShan/minjie-playground>
- DiffTest simulation framework: <https://github.com/OpenXiangShan/difftest>
- FPGA platform scripts: <https://github.com/OpenXiangShan/env-scripts>
- NEMU ISA simulator: <https://github.com/OpenXiangShan/NEMU>
- XS-GEM5 architectural simulator: <https://github.com/OpenXiangShan/GEM5>
- Workload build framework: <https://github.com/OpenXiangShan/workload-builder>
- GSIM simulator: <https://github.com/OpenXiangShan/gsim>

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
  - (V3) Implement and integrate the L2 CDP prefetcher ([XSCache #15](https://github.com/OpenXiangShan/XSCache/pull/15), [#6341](https://github.com/OpenXiangShan/XiangShan/pull/6341))
- Bug fixes
  - (V3) Fix the DCache latency-flag index calculation ([#6339](https://github.com/OpenXiangShan/XiangShan/pull/6339))
  - (V3) Fix TLB-miss handling for cross-page unaligned stores ([#6332](https://github.com/OpenXiangShan/XiangShan/pull/6332))
  - (V3) Fix illegal issue replay feedback for unaligned stores ([#6322](https://github.com/OpenXiangShan/XiangShan/pull/6322))
  - (V2) Fix out-of-order StoreQueue read-pointer updates ([#6353](https://github.com/OpenXiangShan/XiangShan/pull/6353))
  - (V2) Fix dropped-request and Directory MultiHit error reporting in coupledL2 ([CoupledL2 #523](https://github.com/OpenXiangShan/CoupledL2/pull/523), [#6345](https://github.com/OpenXiangShan/XiangShan/pull/6345))
  - (V2) Propagate non-leaf-PTE metadata for vector loads ([#6344](https://github.com/OpenXiangShan/XiangShan/pull/6344))
  - (V2) Fix X propagation from invalid prefetch-filter state ([#6342](https://github.com/OpenXiangShan/XiangShan/pull/6342))
  - (V2) Preserve vector-store replay metadata ([#6338](https://github.com/OpenXiangShan/XiangShan/pull/6338))
  - (V2) Fix hangs in cross-page unaligned vector stores ([#6337](https://github.com/OpenXiangShan/XiangShan/pull/6337))
  - (V2) Fix StoreQueue address-state updates on TLB misses ([#6334](https://github.com/OpenXiangShan/XiangShan/pull/6334))
  - (V2) Fix ordering of unaligned vector elements within one uop ([#6323](https://github.com/OpenXiangShan/XiangShan/pull/6323))
  - (V2) Increase the CHI async-bridge queue depth from 4 to 8 ([#6306](https://github.com/OpenXiangShan/XiangShan/pull/6306))

### XSAI

- RTL features
  - Support e8/e16/e32 multi-precision transposed loads for tile registers ([CUTE #35](https://github.com/OpenXiangShan/CUTE/pull/35))
- Bug fixes
  - Fix DiffTest support for multi-channel CUTE and optimize area ([XSAI #93](https://github.com/OpenXiangShan/XSAI/pull/93), [CUTE #33](https://github.com/OpenXiangShan/CUTE/pull/33))
- Debugging tools
  - Implement MMA batching in DiffTest to reduce kernel launches ([difftest #920](https://github.com/OpenXiangShan/difftest/pull/920))
  - Implement backpressure to prevent unbounded queue growth when the MMA backend has insufficient throughput ([difftest #923](https://github.com/OpenXiangShan/difftest/pull/923))

### Infra

- Chisel HDL
  - Cache CDE parameter queries for XSTile, reducing Chisel-to-Verilog compile time by 33% ([#6336](https://github.com/OpenXiangShan/XiangShan/pull/6336))
- FPGA DiffTest
  - Support specific FPGA platforms and adapt partitioning, ILA, and related flows ([env-scripts #150](https://github.com/OpenXiangShan/env-scripts/pull/150))
  - Automatically capture and upload waveforms via ILA at the failing instruction on FPGA ([difftest #932](https://github.com/OpenXiangShan/difftest/pull/932))
  - Support cross-machine UART control for FPGA ([env-scripts #153](https://github.com/OpenXiangShan/env-scripts/pull/153), [difftest #933](https://github.com/OpenXiangShan/difftest/pull/933))
- NEMU Reference Model
  - Fix CLINT `mtime` write detection ([NEMU #1141](https://github.com/OpenXiangShan/NEMU/pull/1141))
  - Fix time correction for consecutive `mtime` writes ([NEMU #1143](https://github.com/OpenXiangShan/NEMU/pull/1143))
  - Fix `mstatus.MPRV` address calculation ([NEMU #1144](https://github.com/OpenXiangShan/NEMU/pull/1144))
  - Add RVH CI performance-regression tests ([NEMU #1148](https://github.com/OpenXiangShan/NEMU/pull/1148))
  - Fix external-interrupt handling in REF mode ([NEMU #1148](https://github.com/OpenXiangShan/NEMU/pull/1148))
  - Improve Spike DiffTest configuration ([NEMU #1152](https://github.com/OpenXiangShan/NEMU/pull/1152))
- Multicore Checkpoints
  - Enhance the multicore checkpoint flow ([minjie-playground #23](https://github.com/OpenXiangShan/minjie-playground/pull/23))
  - Complete multicore ISA configuration ([workload-builder #45](https://github.com/OpenXiangShan/workload-builder/pull/45))
  - Support dual-core SPEC2017 memory configuration ([workload-builder #46](https://github.com/OpenXiangShan/workload-builder/pull/46))
  - Align NEMU/OpenSBI configuration ([workload-builder #49](https://github.com/OpenXiangShan/workload-builder/pull/49))
- GSIM Simulator
  - Fix node-name conflicts when the same extmodule definition has multiple instances ([gsim #112](https://github.com/OpenXiangShan/gsim/pull/112))
  - Fix scheduling and propagation order of extmodule async-reset outputs ([gsim #113](https://github.com/OpenXiangShan/gsim/pull/113))
  - Fix `OP_ADD` operand-slice out-of-bounds ([gsim #114](https://github.com/OpenXiangShan/gsim/pull/114))
  - Upgrade nixpkgs to nixos-26.05 and switch to the default LLVM version ([gsim #115](https://github.com/OpenXiangShan/gsim/pull/115))
  - Auto-detect and link allocators such as jemalloc, with manual selection via `MALLOC` ([gsim #116](https://github.com/OpenXiangShan/gsim/pull/116))
  - Add PGO support for GSIM itself ([gsim #117](https://github.com/OpenXiangShan/gsim/pull/117))
  - Add a portable `gsim-static` static-build target ([gsim #118](https://github.com/OpenXiangShan/gsim/pull/118))

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
| 400.perlbench       | 52.73  | 53.14  | 410.bwaves         | 120.79 | 106.04 |
| 401.bzip2           | 30.01  | 30.58  | 416.gamess         | 58.36  | 55.82  |
| 403.gcc             | 57.23  | 41.40  | 433.milc           | 71.04  | 68.89  |
| 429.mcf             | 73.02  | 62.64  | 434.zeusmp         | 78.12  | 68.21  |
| 445.gobmk           | 39.94  | 40.43  | 435.gromacs        | 38.27  | 35.15  |
| 456.hmmer           | 55.34  | 67.13  | 436.cactusADM      | 80.63  | 93.32  |
| 458.sjeng           | 39.49  | 40.78  | 437.leslie3d       | 60.95  | 61.11  |
| 462.libquantum      | 138.67 | 305.56 | 444.namd           | 42.98  | 45.25  |
| 464.h264ref         | 70.17  | 75.21  | 447.dealII         | 74.57  | 74.85  |
| 471.omnetpp         | 48.87  | 47.57  | 450.soplex         | 60.27  | 72.04  |
| 473.astar           | 32.78  | 32.44  | 453.povray         | 76.58  | 69.26  |
| 483.xalancbmk       | 83.08  | 101.98 | 454.Calculix       | 42.77  | 40.73  |
| GEOMEAN             | 54.89  | 58.74  | 459.GemsFDTD       | 71.73  | 73.38  |
|                     |        |        | 465.tonto          | 54.23  | 37.83  |
|                     |        |        | 470.lbm            | 128.82 | 146.69 |
|                     |        |        | 481.wrf            | 61.79  | 45.04  |
|                     |        |        | 482.sphinx3        | 61.20  | 63.66  |
|                     |        |        | GEOMEAN            | 66.12  | 63.53  |

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
