---
slug: biweekly-115-en
date: 2026-11-11
draft: true
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 115] 20261111

Welcome to the XiangShan biweekly column! Through this column, we regularly share XiangShan development progress. This is the 115th issue.

Recent XiangShan development unifies software instruction-prefetch scheduling, improves TAGE training and fixes branch prediction; restores out-of-order CSR reads and corrects CBO decoding and commit types; fixes memory rollback, forwarding and coherence while advancing Oceanus development; and improves minimal XSAI matrix configurations, the NoLLC memory bridge, matrix datapaths and verification. Infrastructure updates extend remote FPGA DiffTest, BOOM support, checkpoint handling and GSIM waveforms. ACT4 contribution tools support privileged test-asset generation and review, advance H-extension tests, and report upstream tool issues. XS-GEM5 advances value prediction, SMT resource allocation and performance-analysis tools.

<!-- more -->

## Recent Developments

### Frontend

- RTL features
  - Add FtqPrefetchQueue to buffer and schedule software instruction prefetches alongside FDIP, reducing dropped same-cycle requests and FDIP blocking while combining prefetch requests when banks do not conflict ([#6691](https://github.com/OpenXiangShan/XiangShan/pull/6691))
- Bug fixes
  - Fix MainBTB allocation incorrectly suppressed by hidden VBTB hits, and update conditional-branch target payloads only for taken branches to avoid recording sequential PCs as targets ([#6750](https://github.com/OpenXiangShan/XiangShan/pull/6750))
  - Hold SC prediction responses with DataHoldBypass, preventing training re-reads from overwriting prediction data during S1 stalls ([#6764](https://github.com/OpenXiangShan/XiangShan/pull/6764))
  - Explicitly zero-initialize ITTAGE allocation controls, fixing stale allocation state in GSIM that could cause spurious target-region writes and incorrect allocation counts ([#6837](https://github.com/OpenXiangShan/XiangShan/pull/6837))
- Performance optimizations
  - Include folded history in TAGE bank indexing so different histories can access entries across banks, and retain alternate-predictor metadata to reduce SRAM re-read conflicts when training correct predictions ([#6771](https://github.com/OpenXiangShan/XiangShan/pull/6771), [#6800](https://github.com/OpenXiangShan/XiangShan/pull/6800))
- PPA optimizations
  - Precompute per-branch S2/S3 override conditions and taken candidates for both TAGE outcomes, shortening next-PC logic after late-arriving signals ([#6753](https://github.com/OpenXiangShan/XiangShan/pull/6753))
- Debugging tools
  - Correct S1 prediction-source and S2 override performance counters, and add clearer compile-time checks for address fields and frontend address-width constraints ([#6777](https://github.com/OpenXiangShan/XiangShan/pull/6777), [#6846](https://github.com/OpenXiangShan/XiangShan/pull/6846))

### Backend

- RTL features
  - Restore out-of-order execution of CSR reads in the new decoder, handle zero-source CSR set/clear and immediate forms consistently, and complete special decoding for VL/VLENB ([#6779](https://github.com/OpenXiangShan/XiangShan/pull/6779))
- Bug fixes
  - Select the complete opcode when CBIE converts `cbo.inval` to flush, avoiding an OR operation that incorrectly decoded it as `cbo.zero`, and classify CBO commits as STORE ([#6754](https://github.com/OpenXiangShan/XiangShan/pull/6754), [#6847](https://github.com/OpenXiangShan/XiangShan/pull/6847))
- Debugging tools
  - Preserve decoded remaining writeback counts for both halves of CROB entries in backend debug configurations to aid compressed-commit debugging ([#6749](https://github.com/OpenXiangShan/XiangShan/pull/6749))

### MemBlock and Cache

- RTL features
  - Update software-prefetch handling across the LSU, Rename and Dispatch so requests terminate in LoadUnit S2 without contributing to CROB writeback counts or producing normal load writeback and wakeup ([#6735](https://github.com/OpenXiangShan/XiangShan/pull/6735))
  - On the Oceanus development branch, align Data/Tag/Meta organization and DRRIP replacement with CoupledL2, adding SRAM/CAM replacement-state implementations and release parameters ([XSCache #45](https://github.com/OpenXiangShan/XSCache/pull/45))
- Bug fixes
  - Prioritize rollback that re-executes the current instruction when one ROB entry raises both RAR and RAW violations, preserving the required RAW replay ([#6678](https://github.com/OpenXiangShan/XiangShan/pull/6678))
  - Exclude retired MDP targets so StoreQueue pointer wraparound cannot leave loads waiting indefinitely for an STA, and fix forwarding masks for misaligned accesses crossing 16-byte boundaries ([#6714](https://github.com/OpenXiangShan/XiangShan/pull/6714), [#6718](https://github.com/OpenXiangShan/XiangShan/pull/6718))
  - Wait for the current `cbo.zero` request to enter the store-data queue before draining Sbuffer, preventing an older store dequeue from advancing the CBO state machine early ([#6762](https://github.com/OpenXiangShan/XiangShan/pull/6762))
  - Reject store merges into MSHRs for speculative load misses once the interconnect has taken ownership of their Acquire requests, preventing insufficient write permission and stale data on subsequent loads ([#6842](https://github.com/OpenXiangShan/XiangShan/pull/6842))
  - Use initialized round-robin arbitration for CoupledL2 L1 hints and integrate the change into XiangShan, preventing prolonged blocking of hints from some slices ([XSCache #46](https://github.com/OpenXiangShan/XSCache/pull/46), [XSCache #48](https://github.com/OpenXiangShan/XSCache/pull/48), [#6803](https://github.com/OpenXiangShan/XiangShan/pull/6803))

### XSAI

- RTL features
  - Make the INT8 MMA datapath configurable, add TinyMatrixConfig retaining BF16/FP8, and adjust cache sizes in minimal configurations ([CUTEFPE #5](https://github.com/OpenXiangShan/CUTEFPE/pull/5), [CUTE #47](https://github.com/OpenXiangShan/CUTE/pull/47), [XSAI #154](https://github.com/OpenXiangShan/XSAI/pull/154), [XSAI #155](https://github.com/OpenXiangShan/XSAI/pull/155), [XSAI #157](https://github.com/OpenXiangShan/XSAI/pull/157), [XSAI #164](https://github.com/OpenXiangShan/XSAI/pull/164))
  - Support a single-core L2-to-memory path bypassing the LLC, optimize bridge writes, and select NoLLC for TinyMatrixConfig ([XSAI #165](https://github.com/OpenXiangShan/XSAI/pull/165), [XSAI #168](https://github.com/OpenXiangShan/XSAI/pull/168), [XSAI #169](https://github.com/OpenXiangShan/XSAI/pull/169))
- Bug fixes
  - Synchronize Kunminghu V2 bug fixes ([XSAI #171](https://github.com/OpenXiangShan/XSAI/pull/171))
  - Fix L2 victim-state updates for nested snoops during PutFullData replacement ([XSAICache #14](https://github.com/OpenXiangShan/XSAICache/pull/14))
  - Prevent the Palladium commit watchdog from treating legal WFI waits as stalls ([XSAI #147](https://github.com/OpenXiangShan/XSAI/pull/147))
- Debugging tools
  - Complete memory interfaces and DiffTest probes for FPGA matrix configurations, and simplify per-core AMU/msync control probes ([XSAI #160](https://github.com/OpenXiangShan/XSAI/pull/160), [XSAI #161](https://github.com/OpenXiangShan/XSAI/pull/161), [XSAI #166](https://github.com/OpenXiangShan/XSAI/pull/166))
  - Separate matrix writeback from completion events, adapt writeback widths, and report only final K-sweep results ([CUTE #50](https://github.com/OpenXiangShan/CUTE/pull/50), [CUTE #51](https://github.com/OpenXiangShan/CUTE/pull/51), [CUTE #52](https://github.com/OpenXiangShan/CUTE/pull/52), [difftest #1025](https://github.com/OpenXiangShan/difftest/pull/1025), [XSAI #163](https://github.com/OpenXiangShan/XSAI/pull/163), [XSAI #167](https://github.com/OpenXiangShan/XSAI/pull/167), [XSAI #170](https://github.com/OpenXiangShan/XSAI/pull/170))
  - Use CRC32C for matrix-load and zeroing checks, and compact DiffTest event metadata ([NEMU #1280](https://github.com/OpenXiangShan/NEMU/pull/1280), [difftest #1028](https://github.com/OpenXiangShan/difftest/pull/1028), [difftest #1029](https://github.com/OpenXiangShan/difftest/pull/1029), [CUTE #53](https://github.com/OpenXiangShan/CUTE/pull/53), [XSAI #172](https://github.com/OpenXiangShan/XSAI/pull/172), [XSAI #173](https://github.com/OpenXiangShan/XSAI/pull/173))
  - Support Replay rollback and restoration of matrix asynchronous checker state ([NEMU #1255](https://github.com/OpenXiangShan/NEMU/pull/1255), [difftest #987](https://github.com/OpenXiangShan/difftest/pull/987))
  - Support LightSSS with the DiffTest CUDA backend ([difftest #1017](https://github.com/OpenXiangShan/difftest/pull/1017))
  - Fix MMA checking and register-layout handling for zero-size and partial-tile matrices ([difftest #1012](https://github.com/OpenXiangShan/difftest/pull/1012), [difftest #1013](https://github.com/OpenXiangShan/difftest/pull/1013))
  - Fix INT8 MMA saturation in the DiffTest CPU/CUDA reference models ([difftest #1008](https://github.com/OpenXiangShan/difftest/pull/1008))
  - Complete pending asynchronous MMA checks before program exit to avoid missing errors ([difftest #1031](https://github.com/OpenXiangShan/difftest/pull/1031))
  - Correct NEMU matrix-access interface arguments and enable the access fast path in shared references ([NEMU #1274](https://github.com/OpenXiangShan/NEMU/pull/1274), [NEMU #1275](https://github.com/OpenXiangShan/NEMU/pull/1275))
  - Optimize buffer reuse, CPU computation, and GPU computation and comparison in the DiffTest MMA reference model ([difftest #1014](https://github.com/OpenXiangShan/difftest/pull/1014), [difftest #1016](https://github.com/OpenXiangShan/difftest/pull/1016), [difftest #1018](https://github.com/OpenXiangShan/difftest/pull/1018), [difftest #1019](https://github.com/OpenXiangShan/difftest/pull/1019), [difftest #1021](https://github.com/OpenXiangShan/difftest/pull/1021), [difftest #1022](https://github.com/OpenXiangShan/difftest/pull/1022), [difftest #1023](https://github.com/OpenXiangShan/difftest/pull/1023))
  - Extend matrix-cache VCS trace replay, MMIO tests, and backpressure coverage cases on the test branch ([XSAICache #13](https://github.com/OpenXiangShan/XSAICache/pull/13), [XSAICache #15](https://github.com/OpenXiangShan/XSAICache/pull/15), [tl-test-new #102](https://github.com/OpenXiangShan/tl-test-new/pull/102), [tl-test-new #103](https://github.com/OpenXiangShan/tl-test-new/pull/103), [tl-test-new #104](https://github.com/OpenXiangShan/tl-test-new/pull/104))
  - Fix DUT/REF state layouts and reference-model selection for configurations without matrix extensions ([XSAI #151](https://github.com/OpenXiangShan/XSAI/pull/151), [XSAI #153](https://github.com/OpenXiangShan/XSAI/pull/153))
- Code quality
  - Size CUTEFPE multipliers, significand registers, and alignment-shift logic for enabled precisions ([CUTEFPE #6](https://github.com/OpenXiangShan/CUTEFPE/pull/6), [CUTEFPE #7](https://github.com/OpenXiangShan/CUTEFPE/pull/7), [CUTE #48](https://github.com/OpenXiangShan/CUTE/pull/48), [CUTE #49](https://github.com/OpenXiangShan/CUTE/pull/49), [XSAI #156](https://github.com/OpenXiangShan/XSAI/pull/156), [XSAI #159](https://github.com/OpenXiangShan/XSAI/pull/159))
  - Remove redundant resets from CUTE and VFEXP2 pipeline payloads ([CUTE #54](https://github.com/OpenXiangShan/CUTE/pull/54), [YunSuan #229](https://github.com/OpenXiangShan/YunSuan/pull/229), [XSAI #174](https://github.com/OpenXiangShan/XSAI/pull/174))
  - Adapt the YunSuan vector-conversion interface and tie off inputs for unsupported MXFP conversion ([XSAI #175](https://github.com/OpenXiangShan/XSAI/pull/175))
  - Improve nightly checkpoint and performance-workload scheduling, and adjust dual-core EMU test configurations ([XSAI #149](https://github.com/OpenXiangShan/XSAI/pull/149), [XSAI #162](https://github.com/OpenXiangShan/XSAI/pull/162))

### Infra

- FPGA DiffTest
  - Add queues between Delta and Batch and on CPU AXI R/B responses to isolate combinational timing paths, and update MinJie integration ([difftest #1004](https://github.com/OpenXiangShan/difftest/pull/1004), [minjie-playground #47](https://github.com/OpenXiangShan/minjie-playground/pull/47))
  - Fix fork REF shutdown after the final endpoint succeeds by continuing child retirement and providing bounded XDMA timeout retries while final checks drain ([difftest #1010](https://github.com/OpenXiangShan/difftest/pull/1010))
  - Add a remote XDMA board relay so references can run on a compute host, with session management and cleanup, and coalesce register-write requests to reduce transport latency ([difftest #1011](https://github.com/OpenXiangShan/difftest/pull/1011), [difftest #1020](https://github.com/OpenXiangShan/difftest/pull/1020), [env-scripts #193](https://github.com/OpenXiangShan/env-scripts/pull/193), [env-scripts #194](https://github.com/OpenXiangShan/env-scripts/pull/194), [minjie-playground #41](https://github.com/OpenXiangShan/minjie-playground/pull/41))
  - Add `--ila-size` to bound DUT progress relative to the prefix accepted by SLOW checking for ILA capture windows; configure the CPU operating clock and timing target separately while keeping the UART clock fixed ([difftest #1026](https://github.com/OpenXiangShan/difftest/pull/1026), [env-scripts #185](https://github.com/OpenXiangShan/env-scripts/pull/185))
  - Integrate BOOM RTL generation, release and FPGA DiffTest flows into MinJie, and update shared-reference and fast/fork configuration selection ([minjie-playground #42](https://github.com/OpenXiangShan/minjie-playground/pull/42), [minjie-playground #43](https://github.com/OpenXiangShan/minjie-playground/pull/43), [minjie-playground #44](https://github.com/OpenXiangShan/minjie-playground/pull/44))
- NEMU Reference Model
  - Preserve HVICTL-injected interrupt IDs, preventing incorrect `vscause` translation and vectored trap entry selection ([NEMU #1272](https://github.com/OpenXiangShan/NEMU/pull/1272), [NEMU #1279](https://github.com/OpenXiangShan/NEMU/pull/1279))
  - Mark VS Dirty for successfully completed zero-length vector loads while retaining their no-memory-access behavior ([NEMU #1277](https://github.com/OpenXiangShan/NEMU/pull/1277), [NEMU #1278](https://github.com/OpenXiangShan/NEMU/pull/1278))
  - Add a NutShell FastRef profile; update Kunminghu V2 ready-to-run to use dedicated reference profiles and shared FAST HostTLB support ([NEMU #1273](https://github.com/OpenXiangShan/NEMU/pull/1273), [#6792](https://github.com/OpenXiangShan/XiangShan/pull/6792))
- Workloads and Checkpoints
  - Add dedicated Linux, device-tree and SPEC CPU2006 configurations for BOOM with compiler output constrained to supported instructions, and add a GCC16 SPEC06 build configuration with dynamic LMUL ([workload-builder #83](https://github.com/OpenXiangShan/workload-builder/pull/83), [workload-builder #84](https://github.com/OpenXiangShan/workload-builder/pull/84))
  - Zero-fill freed initramfs pages in Linux to avoid allocating memory for unused nonzero pages during checkpoint restoration ([workload-builder #85](https://github.com/OpenXiangShan/workload-builder/pull/85))
- Development and Debugging Tools
  - Reorganize performance profiles and update the XSCC checkpoint pool, enable XSCC/SPEC17 fuzzing with slow-checkpoint filtering, tolerate non-UTF-8 simulator logs, and defer dispatch when available memory is insufficient ([env-scripts #190](https://github.com/OpenXiangShan/env-scripts/pull/190), [#6758](https://github.com/OpenXiangShan/XiangShan/pull/6758), [env-scripts #195](https://github.com/OpenXiangShan/env-scripts/pull/195), [env-scripts #196](https://github.com/OpenXiangShan/env-scripts/pull/196))
  - Allow DiffTest to be disabled in manual performance regressions with nodiff marked in result directories, and add a Python CI runner manager for creating, scaling and managing runner groups ([#6804](https://github.com/OpenXiangShan/XiangShan/pull/6804), [env-scripts #191](https://github.com/OpenXiangShan/env-scripts/pull/191))
- GSIM Simulator
  - Integrate GSIM FST waveforms and LightSSS into DiffTest for automatic CI failure waveforms, and move cycle scheduling into simulator backends to prevent mismatched input/output sampling ([difftest #867](https://github.com/OpenXiangShan/difftest/pull/867), [#6802](https://github.com/OpenXiangShan/XiangShan/pull/6802), [difftest #1030](https://github.com/OpenXiangShan/difftest/pull/1030))
  - Suppress duplicate FST value changes to reduce waveform overhead, and fix Nix build dependencies and header installation with waveform support ([gsim #150](https://github.com/OpenXiangShan/gsim/pull/150), [gsim #151](https://github.com/OpenXiangShan/gsim/pull/151))

### ACT4 Test Asset Contribution Tools

- Framework and AI assistance
  - [ACT4](https://github.com/riscv/riscv-arch-test) is a new framework for RISC-V Architectural Certification Tests (ACTs). It selects tests based on the target processor's extensions and parameters, uses the Sail reference model to calculate expected results, and generates self-checking test programs for users to run on the processor. Mappings among the Certification Test Plan (CTP), normative rules and coverpoints, together with functional coverage, make the relationship between specification requirements and tested behavior traceable.
  - [UCAgent](https://github.com/XS-MLVP/UCAgent) (UnityChip Verification Agent) is an LLM-based AI agent for hardware verification. Its staged workflows, checkers, and execution and waveform evidence support design analysis, verification planning, test generation, coverage analysis and debugging. Built on the native ACT4 toolchain, its [ACT4 plugin](https://github.com/XS-MLVP/UCAgent/tree/main/plugins/ACT4) supports automated generation of privileged test assets as well as review, repair and revalidation of existing assets.
- Test assets and upstream feedback
  - The plugin has helped generate part of the Hypervisor (H) extension's CSR test generators and coverage assets; the related [H-extension PR](https://github.com/riscv/riscv-arch-test/pull/2383) remains under upstream review.
  - Development uncovered a UDB constraint that disallowed zero guest external interrupts ([UDB #2626](https://github.com/riscv/riscv-unified-db/issues/2626)) and led to a submitted QEMU [patch](https://patchwork.ozlabs.org/project/qemu-devel/patch/20260925-riscv-hgatp-warl-v2-1-2aa9aa7718cd@bosc.ac.cn/) for `hgatp` WARL legalization. A separate QEMU issue involving reserved bits exposed through `vsstatus` and an incorrect RV32 SD summary bit has yet to be submitted. Other related issues identified during review already have upstream fixes ([QEMU d29412c](https://github.com/qemu/qemu/commit/d29412cca54899ba87d5ea5d61e8bad7643b15f0), [QEMU 9b6fc2a](https://github.com/qemu/qemu/commit/9b6fc2a75102ff1713deb1d86bca90ebdf9594fc), [Spike 5d4f1c3](https://github.com/riscv-software-src/riscv-isa-sim/commit/5d4f1c33f753e252a0a895682557d6e4f0f6a982), [Whisper 1513205](https://github.com/tenstorrent/whisper/commit/1513205e0d74433cecd1a483656122ded5f22dc3)).

### XS-GEM5

- New Feature Exploration
  - Add late value-prediction interfaces and EgDiff to predict load results after operands become available ([XS-GEM5 #1186](https://github.com/OpenXiangShan/GEM5/pull/1186))
  - Tune default ROB, LQ and SQ dynamic-borrowing configurations for SMT based on parameter sweeps and extend their configuration interfaces ([XS-GEM5 #1283](https://github.com/OpenXiangShan/GEM5/pull/1283)) [Thanks to our colleagues from Alibaba for their contribution]
  - Add optional decode fusion compaction to refill decode slots across Fetch bundles ([XS-GEM5 #1184](https://github.com/OpenXiangShan/GEM5/pull/1184))
- Bug fixes
  - Fix TraceRTL control-flow fault recovery and EStride in-flight tracking after squashes ([XS-GEM5 #1251](https://github.com/OpenXiangShan/GEM5/pull/1251), [XS-GEM5 #1245](https://github.com/OpenXiangShan/GEM5/pull/1245))
  - Fix memory ordering between SBuffer and loads, and adjust L2 latency configurations ([XS-GEM5 #1243](https://github.com/OpenXiangShan/GEM5/pull/1243))
  - Fix virtualized PTW request coalescing, Nextline configuration propagation and SV48 two-stage translation initialization ([XS-GEM5 #1240](https://github.com/OpenXiangShan/GEM5/pull/1240), [XS-GEM5 #1247](https://github.com/OpenXiangShan/GEM5/pull/1247), [XS-GEM5 #1266](https://github.com/OpenXiangShan/GEM5/pull/1266))
  - Fix CDP detection of L2 prefetch request sources ([XS-GEM5 #1258](https://github.com/OpenXiangShan/GEM5/pull/1258))
  - Support `vwsll.vi`, fix source-register mapping for the first vector slide-up micro-op, and align FS/SD Dirty state for scalar floating-point and virtualized execution ([XS-GEM5 #1280](https://github.com/OpenXiangShan/GEM5/pull/1280), [XS-GEM5 #1281](https://github.com/OpenXiangShan/GEM5/pull/1281))
  - Filter resolve results with the oldest same-cycle squash boundary to prevent wrong-path results from re-entering the BPU training queue ([XS-GEM5 #1282](https://github.com/OpenXiangShan/GEM5/pull/1282))
- Debugging tools
  - Add optional TEA time-proportional event analysis and visualization exports, and track committed instruction bytes for fetch blocks ([XS-GEM5 #1255](https://github.com/OpenXiangShan/GEM5/pull/1255), [XS-GEM5 #1291](https://github.com/OpenXiangShan/GEM5/pull/1291))
- Infrastructure
  - Add RISC-V Sstc timer extension support ([XS-GEM5 #1250](https://github.com/OpenXiangShan/GEM5/pull/1250))
  - Update checkpoint configurations for H-extension and weekly XSCC regressions ([XS-GEM5 #1252](https://github.com/OpenXiangShan/GEM5/pull/1252), [XS-GEM5 #1274](https://github.com/OpenXiangShan/GEM5/pull/1274))
  - Add Google Workload Traces and CBP traces to CI, support selectable manual weekly jobs, and correct TEA configuration for Ruby multi-core CI ([XS-GEM5 #1272](https://github.com/OpenXiangShan/GEM5/pull/1272), [XS-GEM5 #1300](https://github.com/OpenXiangShan/GEM5/pull/1300), [XS-GEM5 #1269](https://github.com/OpenXiangShan/GEM5/pull/1269))

## Performance Evaluation

Performance data comes from [Weekly Regression](https://github.com/OpenXiangShan/XiangShan/actions/runs/42199436965), started on November 6, 2026, testing DefaultConfig / a253c1163 (commit date: November 5, 2026). GCC16 and XSCC completed 1094/1094 and 1099/1099 checkpoints respectively, with no failed workloads.


Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | a253c1163  |
| Date                 | 2026/11/05 |
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
| 400.perlbench        | 57.59  | 61.40  | 410.bwaves          | 146.16 | 148.79 |
| 401.bzip2            | 31.13  | 32.49  | 416.gamess          | 61.92  | 57.81  |
| 403.gcc              | 64.39  | 62.49  | 433.milc            | 77.20  | 75.81  |
| 429.mcf              | 84.44  | 80.40  | 434.zeusmp          | 78.98  | 78.42  |
| 445.gobmk            | 46.88  | 45.32  | 435.gromacs         | 43.41  | 42.68  |
| 456.hmmer            | 55.27  | 67.39  | 436.cactusADM       | 89.25  | 95.89  |
| 458.sjeng            | 45.14  | 46.48  | 437.leslie3d        | 68.40  | 67.34  |
| 462.libquantum       | 167.97 | 382.02 | 444.namd            | 47.71  | 48.63  |
| 464.h264ref          | 70.26  | 74.06  | 447.dealII          | 86.29  | 168.64 |
| 471.omnetpp          | 59.27  | 60.55  | 450.soplex          | 70.55  | 81.49  |
| 473.astar            | 35.67  | 34.25  | 453.povray          | 80.42  | 68.63  |
| 483.xalancbmk        | 92.60  | 136.98 | 454.calculix        | 48.12  | 48.15  |
| GEOMEAN              | 60.96  | 68.90  | 459.GemsFDTD        | 82.97  | 83.21  |
|                      |        |        | 465.tonto           | 79.48  | 64.71  |
|                      |        |        | 470.lbm             | 128.13 | 151.49 |
|                      |        |        | 481.wrf             | 62.60  | 61.24  |
|                      |        |        | 482.sphinx3         | 68.96  | 100.22  |
|                      |        |        | GEOMEAN             | 74.01  | 78.29  |

Compilation parameters are as follows:

| Parameters | GCC16 | XSCC |
| --- | --- | --- |
| Compiler | gcc16 | xscc |
| Optimization level | O3 | O3 |
| Memory library | jemalloc | jemalloc |
| ISA configuration | RVA23-based (vector disabled) | RV64GCB |
| -ffp-contract | Integer: off; floating-point: fast | fast |
| Linker optimization | -flto | -flto |
| Floating-point optimization | -ffast-math (except povray) | -ffast-math |
| -mcpu | - | xiangshan-kunminghu |

The GCC16 configuration also includes -static, -fno-strict-aliasing, -fno-tree-vectorize and -fno-tree-loop-vectorize; language- and benchmark-specific options follow the build configuration archived with the checkpoint pool. At the editor's request, XSCC compilation parameters are carried over from issue 114; the full build metadata for this checkpoint set has not been independently reverified.

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Yanjun Li, Jinhong Zeng, Zechen Yang, Hanle Zhang, Kunlin You, Xin Li, Yiming Yan
