---
slug: biweekly-111-en
date: 2026-09-16
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 111] 20260916

Welcome to the XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 111th issue of the biweekly report.

Regarding the recent development progress of XiangShan, the frontend added BPU S2 override, increased its runahead distance, and fixed an ICache replacement-policy bug; the backend expanded support for vector widening, narrowing, multiply-add, and division, and fixed decoding, bypass, and floating-point bugs; in memory access and caching, F-POP and teacher-student BOP prefetchers were integrated, while LoadQueueReplay gained early wakeup and pipeline optimizations; XSAI added matrix prefetch descriptors to CUTE memory requests, fixed a prefetch livelock, and improved AME DiffTest checks; infrastructure updates improved FPGA DiffTest workflows, optimized the NEMU reference model, expanded test workloads, and fixed GSIM simulation bugs; XS-GEM5 continued aligning Sbuffer, vector writeback, and BPU behavior, and optimized SMT pipeline policies and LSQ contention logic.

<!-- more -->

## Recent Developments

### Frontend

- RTL features
  - Add BPU S2 override to correct S1 predictions earlier using fast results from MainBTB and the TAGE provider, and refactor AheadBTB to support this flow ([#6423](https://github.com/OpenXiangShan/XiangShan/pull/6423))
- Bug fixes
  - Add a second set of touch ports to the ICache replacement logic, fixing missing PLRU state updates for the second fetch block in 2-fetch mode ([#6416](https://github.com/OpenXiangShan/XiangShan/pull/6416))
- Performance optimizations
  - Unify the BPU runahead distance and ICache WayLookup depth, increasing the default runahead distance from 8 to 32 so the prefetch pipeline can fully populate WayLookup ([#6425](https://github.com/OpenXiangShan/XiangShan/pull/6425))
- PPA optimizations
  - Limit comparisons for entry changes on `hitWritten` in the MainBTB WriteBuffer to the relevant bits, reducing comparison logic ([#5898](https://github.com/OpenXiangShan/XiangShan/pull/5898))
  - Compare only the necessary lower address bits when checking MainBTB targets against the S1 prediction, reducing redundant comparison logic ([#6431](https://github.com/OpenXiangShan/XiangShan/pull/6431))

### Backend

- RTL features
  - Execute scalar Zfa `fli.h`, `fli.s`, and `fli.d` through the I2F unit, with scalar NaN boxing for the results ([#6441](https://github.com/OpenXiangShan/XiangShan/pull/6441))
  - Decode `vsetvli`, `vsetivli`, and `vsetvl` as illegal instructions when `mstatus.VS` is disabled ([#6459](https://github.com/OpenXiangShan/XiangShan/pull/6459))
  - Introduce initial support for the new VCVTWrapper ([#6473](https://github.com/OpenXiangShan/XiangShan/pull/6473))
  - Support vector integer widening and narrowing instructions, including the Exu, MGU, and VIAlu data paths ([#6490](https://github.com/OpenXiangShan/XiangShan/pull/6490))
  - Support widening and 2-to-1 narrowing vector conversions; narrowing instructions can read two source registers and write one complete register ([#6493](https://github.com/OpenXiangShan/XiangShan/pull/6493))
  - Add a VFMA unit to the new vector backend and complete its pipeline metadata and registers ([#6503](https://github.com/OpenXiangShan/XiangShan/pull/6503))
  - Support vector integer division (VIDiv) with latency-based early wakeup ([#6510](https://github.com/OpenXiangShan/XiangShan/pull/6510))
  - Restore conditional support for the Smmtt extension and its `mfence` instruction decoding ([#6538](https://github.com/OpenXiangShan/XiangShan/pull/6538))
  - Support vector floating-point division and square root, including non-fixed-latency issue, wakeup, and writeback paths ([#6552](https://github.com/OpenXiangShan/XiangShan/pull/6552))
- Bug fixes
  - Use the dedicated `pdestVl` when updating the VL RAT in DiffTest, avoiding an incorrect generic destination register index ([#6440](https://github.com/OpenXiangShan/XiangShan/pull/6440))
  - Add `is0FlushNext` to correctly clear an is0 entry pending flush in IssuePipe ([#6458](https://github.com/OpenXiangShan/XiangShan/pull/6458))
  - Fix illegal `vtype` handling so that `vtype[10]` is not incorrectly passed to `vl` when the instruction is treated as `vsetivli` ([#6465](https://github.com/OpenXiangShan/XiangShan/pull/6465))
  - Sign-extend the immediates of `VMSGTU.VI`, `VMSLEU.VI`, and `VSADDU.VI` ([#6469](https://github.com/OpenXiangShan/XiangShan/pull/6469))
  - Fix vector Exu source selection so that bypass data is used only in stage 0 ([#6470](https://github.com/OpenXiangShan/XiangShan/pull/6470))
  - Use VF opcodes instead of FP opcodes for vector floating-point instructions ([#6491](https://github.com/OpenXiangShan/XiangShan/pull/6491))
  - Add the `vmax` source VecDataSplit at ex1 ([#6492](https://github.com/OpenXiangShan/XiangShan/pull/6492))
  - Allow `vfwcvt` to execute with SEW=8 by adding the corresponding FP16 conversion opcode ([#6494](https://github.com/OpenXiangShan/XiangShan/pull/6494))
  - Fix the VMove mask when `vm` is 1 and write complete results for whole-register moves ([#6495](https://github.com/OpenXiangShan/XiangShan/pull/6495))
  - Fix JAL/JALR link and jump uop decoding, rename dependencies, and jump-type tracking ([#6496](https://github.com/OpenXiangShan/XiangShan/pull/6496))
  - Add `VFREC7.V` and `VFRSQRT7.V` to the fflags write-enable table ([#6506](https://github.com/OpenXiangShan/XiangShan/pull/6506))
  - Fix bypass handling for ready and non-register sources ([#6508](https://github.com/OpenXiangShan/XiangShan/pull/6508))
  - Align the ROD encoding ([#6509](https://github.com/OpenXiangShan/XiangShan/pull/6509))
  - Fix the fflags output of the I2F unit ([#6519](https://github.com/OpenXiangShan/XiangShan/pull/6519))
  - Hold and prioritize LCOFIP during CSR read-modify-write to prevent local counter-overflow requests from being lost ([#6522](https://github.com/OpenXiangShan/XiangShan/pull/6522), [#6551](https://github.com/OpenXiangShan/XiangShan/pull/6551))
  - Correct NaN-boxing checks for FMA addends ([#6532](https://github.com/OpenXiangShan/XiangShan/pull/6532))
  - Add proper FP boxing for VMove floating-point results ([#6564](https://github.com/OpenXiangShan/XiangShan/pull/6564))
- Timing optimization
  - Register uop fire, exception, and uopBits in DecodeStage to shorten the decode critical path ([#6466](https://github.com/OpenXiangShan/XiangShan/pull/6466))
- Refactoring and cleanup
  - Unify LatDecoder opcode inputs, adding support for VMove and Stu opcodes as well as uncertain latency configurations ([#6445](https://github.com/OpenXiangShan/XiangShan/pull/6445))
  - Initialize new VIMac support, remove the old VIMacU, and use `splitToVecN` consistently ([#6471](https://github.com/OpenXiangShan/XiangShan/pull/6471))
  - Remove FusionDecoder's dependency on DecodeUnit and the redundant `instructions.scala` ([#6477](https://github.com/OpenXiangShan/XiangShan/pull/6477))
  - Remove unused vector ALU code and rename vialuf to vialu ([#6478](https://github.com/OpenXiangShan/XiangShan/pull/6478))
  - Clean up outdated vector and memory code and correct `vecInactive` handling for continuous stores ([#6479](https://github.com/OpenXiangShan/XiangShan/pull/6479))
  - Remove the old VFMA/VFAlu wrappers and set the corresponding configuration `fuGen` fields to null ([#6530](https://github.com/OpenXiangShan/XiangShan/pull/6530))
  - Remove the unused VPUCtrlSignals ([#6531](https://github.com/OpenXiangShan/XiangShan/pull/6531))
  - Pass the extension list to decode fields so decode tables are generated for the enabled ISA extensions ([#6537](https://github.com/OpenXiangShan/XiangShan/pull/6537))
  - Remove unused classes and methods from the vector backend ([#6562](https://github.com/OpenXiangShan/XiangShan/pull/6562))
  - Remove the obsolete nonzero state and related interfaces from the VL busy table ([#6563](https://github.com/OpenXiangShan/XiangShan/pull/6563))
  - Move vector source-operand swapping to after register reads and handle it uniformly in Exu ([#6565](https://github.com/OpenXiangShan/XiangShan/pull/6565))
- Tool update
  - Update the NEMU reference used by ready-to-run, including the RV64 `mstatus` initialization and SimPoint profiling fixes and optimizations ([#6472](https://github.com/OpenXiangShan/XiangShan/pull/6472))

### MemBlock and Cache

- RTL features
  - Add latency-based early wakeup for LoadQueueReplay ([#6510](https://github.com/OpenXiangShan/XiangShan/pull/6510))
  - Integrate the F-POP L2 prefetcher into XiangShan ([XSCache #24](https://github.com/OpenXiangShan/XSCache/pull/24), [#6255](https://github.com/OpenXiangShan/XiangShan/pull/6255))
  - Add a student coverage learner to the BOP prefetcher ([XSCache #29](https://github.com/OpenXiangShan/XSCache/pull/29), [#6435](https://github.com/OpenXiangShan/XiangShan/pull/6435))
- Bug fixes
  - Fix delayed-wakeup handling for unaligned head replays in LoadQueueReplay ([#6480](https://github.com/OpenXiangShan/XiangShan/pull/6480))
  - Fix an unexpected `uncacheMove` caused by inactive vector elements in StoreQueue ([#6474](https://github.com/OpenXiangShan/XiangShan/pull/6474))
  - Preserve head TLB metadata during unaligned LoadUnit replays ([#6457](https://github.com/OpenXiangShan/XiangShan/pull/6457))
  - Fix exception generation in AtomicsUnit ([#6316](https://github.com/OpenXiangShan/XiangShan/pull/6316))
  - (V2) Use PMM-normalized virtual addresses for LoadUnit and StoreUnit triggers ([#6311](https://github.com/OpenXiangShan/XiangShan/pull/6311))
  - (V2) Support partial replay for unit-stride stores ([#6434](https://github.com/OpenXiangShan/XiangShan/pull/6434))
  - (V2) Widen the vector-memory exception `gpaddr` to XLEN ([#6432](https://github.com/OpenXiangShan/XiangShan/pull/6432))
- Timing optimization
  - Shorten the LoadQueueReplay pipeline from three stages to two, and optimize DCache, Uncache, TLB-hint, and replay-arbitration paths ([#6422](https://github.com/OpenXiangShan/XiangShan/pull/6422))

### XSAI

- RTL features
  - Propagate matrix prefetch descriptors with CUTE memory requests ([CUTE #39](https://github.com/OpenXiangShan/CUTE/pull/39))
- Bug fixes
  - Sync bug fixes from Kunminghu V2 ([XSAI #123](https://github.com/OpenXiangShan/XSAI/pull/123), [XSAI #129](https://github.com/OpenXiangShan/XSAI/pull/129))
  - Fix a prefetch RequestBuffer livelock ([XSAI #126](https://github.com/OpenXiangShan/XSAI/pull/126), [XSAICache #8](https://github.com/OpenXiangShan/XSAICache/pull/8))
- Code quality
  - Update the nightly regression checkpoint pools and pin matrix jobs to node runners ([XSAI #120](https://github.com/OpenXiangShan/XSAI/pull/120), [XSAI #122](https://github.com/OpenXiangShan/XSAI/pull/122))
- Debugging tools
  - Improve AME DiffTest handling of `mrelease` retirement and ordering against older `mstore` instructions ([XSAI #121](https://github.com/OpenXiangShan/XSAI/pull/121), [difftest #953](https://github.com/OpenXiangShan/difftest/pull/953), [XSAI #128](https://github.com/OpenXiangShan/XSAI/pull/128), [difftest #958](https://github.com/OpenXiangShan/difftest/pull/958))
  - Record the correct instruction PC on AME error paths ([XSAI #121](https://github.com/OpenXiangShan/XSAI/pull/121), [difftest #955](https://github.com/OpenXiangShan/difftest/pull/955))
  - Optimize floating-point MMACC in NEMU and improve instruction semantic checks ([NEMU #1189](https://github.com/OpenXiangShan/NEMU/pull/1189), [NEMU #1197](https://github.com/OpenXiangShan/NEMU/pull/1197), [NEMU #1200](https://github.com/OpenXiangShan/NEMU/pull/1200))

### Infra

- FPGA DiffTest
  - Harden the FPGA run workflow with cross-host command coordination between Runtime and Host, and improve device-state checks and cleanup after each run ([env-scripts #167](https://github.com/OpenXiangShan/env-scripts/pull/167), [env-scripts #168](https://github.com/OpenXiangShan/env-scripts/pull/168), [minjie-playground #31](https://github.com/OpenXiangShan/minjie-playground/pull/31))
  - Add probes for XiangShan DiffTrapEvent and restore DiffTest signal naming so designated signals can be captured by ILA through XMR paths ([env-scripts #165](https://github.com/OpenXiangShan/env-scripts/pull/165), [difftest #959](https://github.com/OpenXiangShan/difftest/pull/959))
  - Add asynchronous CDC constraints between the XDMA pre-PERST clock and the PCIe reference clock ([env-scripts #169](https://github.com/OpenXiangShan/env-scripts/pull/169))
  - Fix shallow copying of DiffState during Replay snapshot restoration, avoiding copies of queues, sets, and other transient state with separate ownership ([difftest #957](https://github.com/OpenXiangShan/difftest/pull/957))
- NEMU reference model
  - Avoid unnecessary `v0` reads in unmasked vector memory operations ([NEMU #1155](https://github.com/OpenXiangShan/NEMU/pull/1155))
  - Trim the execution boundary for single-instruction shared REF runs and skip redundant CSR shadow preparation when CSR state is unchanged ([NEMU #1136](https://github.com/OpenXiangShan/NEMU/pull/1136), [NEMU #1027](https://github.com/OpenXiangShan/NEMU/pull/1027))
  - Cache identity effective-address state and streamline PTE reads in shared REF page-table walks while preserving permission and exception checks ([NEMU #1011](https://github.com/OpenXiangShan/NEMU/pull/1011), [NEMU #1138](https://github.com/OpenXiangShan/NEMU/pull/1138))
  - Skip repeated basic-block boundary polling when profiling and checkpointing are inactive ([NEMU #1137](https://github.com/OpenXiangShan/NEMU/pull/1137))
- Sampling and Checkpointing
  - Add seven RVA23 Linux RocksDB workloads covering mixed reads and writes, random transactions, and time-series operations ([workload-builder #66](https://github.com/OpenXiangShan/workload-builder/pull/66))
  - Support offline Geekbench 5/6 Preview runs ([workload-builder #62](https://github.com/OpenXiangShan/workload-builder/pull/62))
  - Prevent the Linux `hello` message address from being incorrectly relaxed to a `gp`-relative address, and report output failures correctly ([workload-builder #67](https://github.com/OpenXiangShan/workload-builder/pull/67))
  - Integrate jemalloc into SPEC CPU2017/2026, fix the SPEC2017 multi-command run scripts, and consistently use jemalloc across SPEC workloads ([workload-builder #56](https://github.com/OpenXiangShan/workload-builder/pull/56), [workload-builder #68](https://github.com/OpenXiangShan/workload-builder/pull/68))
  - Consolidate workload build and run support for QEMU's `nemu` machine, including its DTS, firmware output, and run scripts ([workload-builder #60](https://github.com/OpenXiangShan/workload-builder/pull/60))
  - Derive single-hart firmware, kernel, and checkpoint addresses from the selected DTS's DRAM base and CLINT address to produce images matching the target platform ([workload-builder #55](https://github.com/OpenXiangShan/workload-builder/pull/55))
  - Trace profiling instruction-count variation to the DTS random seed; fixing `rng-seed` across profiles stabilizes the sampled instruction counts ([workload-builder #57](https://github.com/OpenXiangShan/workload-builder/pull/57))
  - Align workload-builder DTS ISA declarations with the XiangShan platform and update the core's ISA extension parameters ([workload-builder #59](https://github.com/OpenXiangShan/workload-builder/pull/59), [XiangShan #6463](https://github.com/OpenXiangShan/XiangShan/pull/6463))
  - Dynamically generate matching DTS files at build time from the `nemu_board` configuration, unifying FPGA, QEMU, and NEMU device-tree profiles ([workload-builder #71](https://github.com/OpenXiangShan/workload-builder/pull/71))
- GSIM simulator
  - Define dynamic right-shift overshifts: unsigned values return zero and signed values receive sign fill, avoiding C++ undefined behavior that caused DiffTest failures ([gsim #128](https://github.com/OpenXiangShan/gsim/pull/128))
  - Fix signed right-shift constant propagation using the destination instead of the source operand, which incorrectly folded right shifts of negative values to zero ([gsim #129](https://github.com/OpenXiangShan/gsim/pull/129))
  - Fix signed constant slicing during node splitting: use floor division to preserve sign extension for negative arithmetic shifts and reinterpret bit selections as unsigned ([gsim #130](https://github.com/OpenXiangShan/gsim/pull/130))
  - Correct an off-by-one upper-slice boundary in concatenated-constant equality optimization, slicing according to the concatenation layout ([gsim #131](https://github.com/OpenXiangShan/gsim/pull/131))
  - Guard dynamic vector indices so out-of-range reads return deterministic zero and out-of-range writes become no-ops, eliminating undefined memory access ([gsim #132](https://github.com/OpenXiangShan/gsim/pull/132))

### XS-GEM5

- Simulator alignment
  - Sbuffer behavior alignment ([XS-GEM5 #1140](https://github.com/OpenXiangShan/GEM5/pull/1140))
  - Vector instruction writeback behavior alignment ([XS-GEM5 #1113](https://github.com/OpenXiangShan/GEM5/pull/1113))
  - IQ alignment ([XS-GEM5 #1127](https://github.com/OpenXiangShan/GEM5/pull/1127))
  - Floating-point division behavior alignment ([XS-GEM5 #1116](https://github.com/OpenXiangShan/GEM5/pull/1116))
  - BPU behavior alignment ([XS-GEM5 #1122](https://github.com/OpenXiangShan/GEM5/pull/1122))
- Code quality
  - Vector code cleanup ([XS-GEM5 #1075](https://github.com/OpenXiangShan/GEM5/pull/1075))
- New feature exploration
  - SMT: Fetch blocking and pipeline flush policy optimization ([XS-GEM5 #1124](https://github.com/OpenXiangShan/GEM5/pull/1124)) [Thanks to our colleagues from Alibaba for their contribution]
  - SMT: Optimize LSQ contention logic under SMT ([XS-GEM5 #1094](https://github.com/OpenXiangShan/GEM5/pull/1094)) [Thanks to our colleagues from ZTE for their contribution]
- Infrastructure
  - AMO instruction bug fix ([XS-GEM5 #1098](https://github.com/OpenXiangShan/GEM5/pull/1098)) [Thanks to our colleagues from Alibaba for their contribution]
  - New instruction implementation ([XS-GEM5 #1118](https://github.com/OpenXiangShan/GEM5/pull/1118)) [Thanks to our colleagues from Alibaba for their contribution]
  - CI maintenance: standardize the NEMU version used ([XS-GEM5 #1105](https://github.com/OpenXiangShan/GEM5/pull/1105))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | 0eea07ed9  |
| Date                 | 2026/09/11 |
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
| 400.perlbench        | 56.40  | 54.24  | 410.bwaves          | 126.11 | 112.18 |
| 401.bzip2            | 30.49  | 31.20  | 416.gamess          | 59.54  | 56.55  |
| 403.gcc              | 61.93  | 42.58  | 433.milc            | 76.56  | 73.10  |
| 429.mcf              | 77.90  | 64.10  | 434.zeusmp          | 79.58  | 70.77  |
| 445.gobmk            | 44.90  | 44.46  | 435.gromacs         | 41.68  | 36.92  |
| 456.hmmer            | 54.74  | 67.53  | 436.cactusADM       | 86.33  | 94.33  |
| 458.sjeng            | 43.73  | 43.69  | 437.leslie3d        | 66.56  | 64.63  |
| 462.libquantum       | 164.48 | 382.99 | 444.namd            | 44.46  | 45.48  |
| 464.h264ref          | 69.46  | 76.01  | 447.dealII          | 66.08  | 81.12  |
| 471.omnetpp          | 56.40  | 56.29  | 450.soplex          | 65.94  | 79.40  |
| 473.astar            | 34.28  | 33.67  | 453.povray          | 79.62  | 74.37  |
| 483.xalancbmk        | 89.19  | 107.78 | 454.calculix        | 42.15  | 41.17  |
| GEOMEAN              | 58.94  | 62.57  | 459.GemsFDTD        | 80.02  | 76.96  |
|                      |        |        | 465.tonto           | 55.04  | 37.92  |
|                      |        |        | 470.lbm             | 128.56 | 149.77 |
|                      |        |        | 481.wrf             | 59.50  | 45.14  |
|                      |        |        | 482.sphinx3         | 62.02  | 64.63  |
|                      |        |        | GEOMEAN             | 68.19  | 65.95  |

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

Editors: Yanjun Li, Jinhong Zeng, Zechen Yang, Hanle Zhang, Kunlin You, Hao Zhen, Yiming Yan
