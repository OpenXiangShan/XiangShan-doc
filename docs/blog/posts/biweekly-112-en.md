---
slug: biweekly-112-en
date: 2026-09-30
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 112] 20260930

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 112th issue of the biweekly report.

Regarding the recent development progress of XiangShan, the frontend fixed issues in CommonHR history and instruction-fetch address checks and optimized uBTB timing; the backend added a unified vector floating-point functional unit and scalar floating-point source operands, while fixing issues related to vector state, CBO, and DiffTest; the memory and cache subsystem integrated ZhuJiang NoC, fixed multiple vector-memory, StoreQueue, exception-handling, and coherence issues, and optimized memory-dependence tracking and timing; XSAI improved matrix debugging support across CUTE, NEMU, and DiffTest; infrastructure updates enhanced FPGA DiffTest, the NEMU reference model, test workloads, sampling and checkpointing, and GSIM; XS-GEM5 continued model alignment and exploration for vector memory access, prefetching, branch prediction, and execution queues.

RISC-V Summit China 2026 will take place from October 18 to 20, 2026, at the Shenzhen Convention and Exhibition Center (Futian). The XiangShan team will present the latest microarchitecture developments and host a XiangShan tutorial at the summit. We look forward to seeing you in Shenzhen!

<!-- more -->

## Recent Developments

### Frontend

- Bug fixes
  - Fix the issue where history generated after a redirect could not participate in CommonHR prediction, allowing the first CommonHR prediction after a redirect to use the newly generated history ([#6617](https://github.com/OpenXiangShan/XiangShan/pull/6617))
  - Fix canonical PC checks in the frontend and extend the high-bit and exception handling paths for instruction-fetch addresses, covering Sv39 and Sv48 address modes ([#6272](https://github.com/OpenXiangShan/XiangShan/pull/6272))
- Timing optimizations
  - Move the uBTB hit check to T1 and remove the T1-to-T0 forwarding path to shorten the critical BPU path ([#6489](https://github.com/OpenXiangShan/XiangShan/pull/6489))

### Backend

- RTL Features
  - (V3) Merge VFALU and VFMul into a unified VFMac functional unit supporting vector floating-point add/subtract, multiply, and fused multiply-add/subtract, with unified configuration and latency decoding ([#6573](https://github.com/OpenXiangShan/XiangShan/pull/6573))
  - (V3) Support scalar floating-point source operands for vector floating-point instructions by connecting the VecRegion and FltRegion register-read, bypass, wakeup, and replay paths ([#6615](https://github.com/OpenXiangShan/XiangShan/pull/6615))
- Bug Fixes
  - (V2) Fix vector store helper uops incorrectly marking `mstatus.VS` and `mstatus.SD` Dirty, while preserving the required state update for nonzero `vstart` ([#6570](https://github.com/OpenXiangShan/XiangShan/pull/6570))
  - (V3) Set the decoded `numWb` of CBO instructions to 2 so it matches the two writeback paths through StdUnit and StoreQueue ([#6583](https://github.com/OpenXiangShan/XiangShan/pull/6583))
  - (V3) Source the DiffTest VL from rename-side physical-register state, remove the DiffTest-only VL path from the CSR ROB commit bundle, and connect it only in basic-debug configurations ([#6591](https://github.com/OpenXiangShan/XiangShan/pull/6591))
  - (V2) Flush the pipeline whenever a nonzero `vstart` value is written, preventing subsequent vector instructions from using stale state ([#6613](https://github.com/OpenXiangShan/XiangShan/pull/6613))
- Code Refactoring
  - (V3) Replace the integer Rename MEFreeList with StdFreeList, preserve the initial physical-register mapping, and disable the arch-free-list completeness check that does not apply with move elimination ([#6593](https://github.com/OpenXiangShan/XiangShan/pull/6593))

### MemBlock and Cache

- RTL Features
  - Integrate ZhuJiang NoC into XiangShan ([XSCache #14](https://github.com/OpenXiangShan/XSCache/pull/14), [#6122](https://github.com/OpenXiangShan/XiangShan/pull/6122))
- Bug Fixes
  - Prioritize the ROB-head request after detecting a stall to fix replay deadlocks caused by DCache/TLB replacement ping-pong during cross-16B loads and stores ([#6590](https://github.com/OpenXiangShan/XiangShan/pull/6590))
  - Correct the two-writeback count for CBO instructions and the StoreQueue stall conditions for following stores ([#6583](https://github.com/OpenXiangShan/XiangShan/pull/6583))
  - Update the L2 Directory DRRIP policy-selection counter PSEL only when the refill does not require a retry ([XSCache #35](https://github.com/OpenXiangShan/XSCache/pull/35))
  - (V2) Include delayed S3 DCache errors in the final vector-load exception state to prevent lost exceptions and incorrect replays ([#6633](https://github.com/OpenXiangShan/XiangShan/pull/6633))
  - (V2) Initialize the Sbuffer forwarding tag-match registers to prevent unknown values from propagating on the first forward after reset ([#6579](https://github.com/OpenXiangShan/XiangShan/pull/6579))
  - (V2) Buffer concurrent L2 ECC errors and bump the submodule to integrate this fix together with MSHR/MMIOBridge error-response propagation fixes ([CoupledL2 #529](https://github.com/OpenXiangShan/CoupledL2/pull/529), [#6578](https://github.com/OpenXiangShan/XiangShan/pull/6578))
  - (V2) Validate full virtual addresses for both the first and last accessed bytes, report the correct fault address, and separate it from the memory-trigger match address ([#6558](https://github.com/OpenXiangShan/XiangShan/pull/6558))
  - (V2) Pass the correct vector-store access size to the TLB so full virtual-address checks cover the accessed bytes ([#6559](https://github.com/OpenXiangShan/XiangShan/pull/6559))
  - (V2) Preserve access faults and hardware errors carried through the LoadUnit pipeline after an NC load returns ([#6521](https://github.com/OpenXiangShan/XiangShan/pull/6521))
  - (V2) Generate the appropriate exceptions for `denied/corrupt` errors when StoreQueue receives a CMO response ([#6554](https://github.com/OpenXiangShan/XiangShan/pull/6554))
  - (V2) Use separate flush levels for queue recovery and exception buffers on vector-memory exceptions, preserving stores that must drain while clearing stale fault addresses ([#6548](https://github.com/OpenXiangShan/XiangShan/pull/6548))
  - (V2) Prevent VMergeBuffer from incorrectly adding the unit-stride offset to `gpaddr` on G-stage faults during VS page-table walks ([#6514](https://github.com/OpenXiangShan/XiangShan/pull/6514))
  - (V2) Align VSegmentUnit trigger results with the latched address to prevent missed triggers or matches based on stale addresses ([#6513](https://github.com/OpenXiangShan/XiangShan/pull/6513))
  - (V2) Prevent scalar stores requiring replay from writing back or updating StoreQueue prematurely, and avoid advancing the read pointer twice for the same split store ([#6507](https://github.com/OpenXiangShan/XiangShan/pull/6507))
  - (V2) Complete NC/MMIO `cbo.zero` through the StoreQueue MMIO state machine to fix ROB hangs ([#6485](https://github.com/OpenXiangShan/XiangShan/pull/6485))
- Timing Optimizations
  - Refactor memory-dependence tracking around SQ pointers, pipeline LSQ/VSQ dequeue and recovery logic, and optimize Load/Store, PTW, and prefetch-arbitration paths ([#6556](https://github.com/OpenXiangShan/XiangShan/pull/6556))

### XSAI

- Code quality
  - Switch CI nightly random regression to the RVA23 non-vector SPEC checkpoint pool ([XSAI #130](https://github.com/OpenXiangShan/XSAI/pull/130))
- Debugging tools
  - Add a joint CUTE-L2 test top and provide write-request observation interfaces ([CUTE #40](https://github.com/OpenXiangShan/CUTE/pull/40), [CUTE #41](https://github.com/OpenXiangShan/CUTE/pull/41))
  - Improve NEMU's CUTE controller-mode callbacks and matrix synchronization support ([NEMU #1225](https://github.com/OpenXiangShan/NEMU/pull/1225))
  - Fix the layout mismatch between AME event structures in DiffTest batch mode and NEMU ([difftest #962](https://github.com/OpenXiangShan/difftest/pull/962))
  - Fix `coreid` and PC sampling in CUTE DiffTest events ([CUTE #42](https://github.com/OpenXiangShan/CUTE/pull/42))
  - Restrict comparisons for NEMU matrix load results to avoid false positives caused by unwritten regions ([NEMU #1217](https://github.com/OpenXiangShan/NEMU/pull/1217))
  - Add checks in NEMU for missing synchronization before matrix memory accesses and reads from undefined matrix-register regions ([NEMU #1212](https://github.com/OpenXiangShan/NEMU/pull/1212), [NEMU #1224](https://github.com/OpenXiangShan/NEMU/pull/1224))

### Infra

- FPGA DiffTest
  - Add optional GBus transport support to FPGA DiffTest, improve FPGA-side integration, host runtime integration, and the build flow, and fix incorrect XDMA endpoint instantiation in GBus configurations ([env-scripts #163](https://github.com/OpenXiangShan/env-scripts/pull/163), [env-scripts #177](https://github.com/OpenXiangShan/env-scripts/pull/177))
  - Fix IOTrace Zstd decompression dropping the last partially read chunk at EOF, and retain only the bytes actually produced by decompression to prevent replay from exhausting records prematurely ([difftest #972](https://github.com/OpenXiangShan/difftest/pull/972))
- NEMU Reference Model
  - Fix skipped RVH final TLB fills when exception injection is disabled, restoring the translation cache for normal execution and reducing repeated G-stage address translations ([NEMU #1218](https://github.com/OpenXiangShan/NEMU/pull/1218))
  - Optimize register export from the shared reference model under GCC/x86-64 by using a more efficient `memmove` path to reduce state-copying overhead ([NEMU #1219](https://github.com/OpenXiangShan/NEMU/pull/1219))
  - Fix CSR dirty-state tracking in the shared reference model so exported CSR snapshots are refreshed correctly after CSR writes and `mret`/`sret` ([NEMU #1220](https://github.com/OpenXiangShan/NEMU/pull/1220))
  - Align CSR configuration with NutShell by making `mseccfg` optional, omitting unimplemented counter and protection CSRs, and keeping counter-enable bits writable when Zicntr is disabled so OpenSBI can emulate timer accesses ([NEMU #1221](https://github.com/OpenXiangShan/NEMU/pull/1221), [NEMU #1222](https://github.com/OpenXiangShan/NEMU/pull/1222), [NEMU #1223](https://github.com/OpenXiangShan/NEMU/pull/1223))
  - Fix Clang build failures caused by `-Werror` treating warnings about feature combinations on some host CPUs as errors ([NEMU #1227](https://github.com/OpenXiangShan/NEMU/pull/1227))
  - Update the XiangShan Spike reference model to a newer upstream implementation, align its ISA extensions, PMP layout, and reset state with NEMU, and add support for building a standalone executable ([riscv-isa-sim #97](https://github.com/OpenXiangShan/riscv-isa-sim/pull/97), [riscv-isa-sim #99](https://github.com/OpenXiangShan/riscv-isa-sim/pull/99), [riscv-isa-sim #101](https://github.com/OpenXiangShan/riscv-isa-sim/pull/101))
- Test Workloads, Sampling and Checkpointing
  - Improve NutShell RV64IMAC workload support with device-tree profiles and SPEC CPU2006 compiler configurations, and support building Linux images and matching checkpoint restorers ([workload-builder #76](https://github.com/OpenXiangShan/workload-builder/pull/76), [workload-builder #77](https://github.com/OpenXiangShan/workload-builder/pull/77), [workload-builder #78](https://github.com/OpenXiangShan/workload-builder/pull/78), [LibCheckpointAlpha #14](https://github.com/OpenXiangShan/LibCheckpointAlpha/pull/14))
  - Correct custom trap instruction encoding in `nemu-trap`, `nemu-exec`, and Linux `hello` so control codes and exit status are passed correctly through `a0` ([workload-builder #75](https://github.com/OpenXiangShan/workload-builder/pull/75))
  - Align single-hart profiling control flows for SPEC CPU2006 and CPU2017, allowing `PROFILING=0` to disable profiling-start markers while preserving workload exit-status reporting ([workload-builder #79](https://github.com/OpenXiangShan/workload-builder/pull/79))
  - Extend performance regression flows to run workloads from image lists and configure warmup instruction counts, maximum instruction counts, and maximum cycle counts ([env-scripts #172](https://github.com/OpenXiangShan/env-scripts/pull/172), [XiangShan #6600](https://github.com/OpenXiangShan/XiangShan/pull/6600))
  - Fix `nemu_trap` incorrectly disabling Host timer interrupts during virtualized profiling by disabling only the Guest virtual supervisor timer interrupt, preserving Host scheduling ([NEMU #1230](https://github.com/OpenXiangShan/NEMU/pull/1230))
  - Extend the memory range in NEMU's sampling and checkpointing configuration to the 8 TiB address space, aligning it with the default XiangShan configuration ([NEMU #1234](https://github.com/OpenXiangShan/NEMU/pull/1234))
- GSIM Simulator
  - Fix element-width handling in code generation for aggregate array assignments by converting each element to the destination width and restricting when `memcpy` can be used, preventing narrow elements from incorrectly retaining high bits ([gsim #134](https://github.com/OpenXiangShan/gsim/pull/134))
  - Relax compiler version requirements to accept Clang 19 and newer, and improve `clang++` selection and version-check diagnostics ([gsim #136](https://github.com/OpenXiangShan/gsim/pull/136))
  - Fix code generation issues involving widths and signed arithmetic: preserve member semantics when widening aggregates, define signed subtraction wraparound, normalize input-port writes that require narrowing, and avoid undefined behavior in signed `% -1` operations ([gsim #137](https://github.com/OpenXiangShan/gsim/pull/137))

### XS-GEM5

- Simulator alignment
  - Set the delay from vector memory completion to IEW writeback to 3 cycles ([XS-GEM5 #1155](https://github.com/OpenXiangShan/GEM5/pull/1155))
  - Align pre-decode ([XS-GEM5 #1150](https://github.com/OpenXiangShan/GEM5/pull/1150))
  - Align ibuffer bypass behavior for vset instructions ([XS-GEM5 #1135](https://github.com/OpenXiangShan/GEM5/pull/1135))
  - Support cache hit under block ([XS-GEM5 #1164](https://github.com/OpenXiangShan/GEM5/pull/1164))
  - Align floating-point division latency ([XS-GEM5 #1167](https://github.com/OpenXiangShan/GEM5/pull/1167))
  - Align vector IQ configuration ([XS-GEM5 #1179](https://github.com/OpenXiangShan/GEM5/pull/1179))
- New feature exploration
  - New pointer prefetch algorithm LLDP ([XS-GEM5 #1158](https://github.com/OpenXiangShan/GEM5/pull/1158))
  - Make MBTB and TAGE prediction results available in S2 instead of S3 ([XS-GEM5 #1165](https://github.com/OpenXiangShan/GEM5/pull/1165))
  - Add a per-IQ watermark policy to reserve issue-queue capacity for each SMT thread ([XS-GEM5 #1175](https://github.com/OpenXiangShan/GEM5/pull/1175))
- Infrastructure
  - Implement the `cbo.zero` instruction ([XS-GEM5 #1153](https://github.com/OpenXiangShan/GEM5/pull/1153))
  - Improve SE mode and its documentation ([XS-GEM5 #1154](https://github.com/OpenXiangShan/GEM5/pull/1154))
  - Support more SE-mode workloads ([XS-GEM5 #1156](https://github.com/OpenXiangShan/GEM5/pull/1156))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | aa6b52033  |
| Date                 | 2026/09/24 |
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
| 400.perlbench        | 57.27  | 59.16  | 410.bwaves          | 124.81 | 136.74 |
| 401.bzip2            | 30.50  | 32.49  | 416.gamess          | 60.13  | 56.82  |
| 403.gcc              | 62.21  | 44.57  | 433.milc            | 76.13  | 85.77  |
| 429.mcf              | 78.05  | 70.32  | 434.zeusmp          | 77.92  | 79.49  |
| 445.gobmk            | 45.44  | 44.31  | 435.gromacs         | 41.91  | 38.34  |
| 456.hmmer            | 54.81  | 68.30  | 436.cactusADM       | 86.71  | 90.97  |
| 458.sjeng            | 43.17  | 46.14  | 437.leslie3d        | 66.54  | 67.58  |
| 462.libquantum       | 168.06 | 380.90 | 444.namd            | 44.70  | 45.82  |
| 464.h264ref          | 69.48  | 73.54  | 447.dealII          | 65.07  | 97.13  |
| 471.omnetpp          | 56.13  | 56.73  | 450.soplex          | 66.57  | 80.45  |
| 473.astar            | 34.26  | 33.91  | 453.povray          | 79.31  | 72.48  |
| 483.xalancbmk        | 88.29  | 118.65 | 454.calculix        | 41.90  | 37.91  |
| GEOMEAN              | 59.08  | 64.70  | 459.GemsFDTD        | 80.37  | 82.58  |
|                      |        |        | 465.tonto           | 55.67  | 44.40  |
|                      |        |        | 470.lbm             | 126.33 | 153.29 |
|                      |        |        | 481.wrf             | 60.76  | 63.23  |
|                      |        |        | 482.sphinx3         | 61.06  | 63.76  |
|                      |        |        | GEOMEAN             | 68.09  | 70.74  |

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
