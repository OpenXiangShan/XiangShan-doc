---
slug: biweekly-116-en
date: 2026-11-25
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 116] 20261125

Welcome to the XiangShan biweekly column! Through this column, we regularly share XiangShan development progress. This is the 116th issue.

Recent XiangShan development fixes fault addresses for virtualized instruction fetches and spurious ICache ECC errors in the frontend, and adds interrupt, exception and instruction-count triggers to the Kunminghu V3 backend. Memory changes bring TSO to cacheable accesses on Kunminghu V2 and fix stalls in page walks and load/store replay. XSAI can now store matrix registers to memory and check matrix operations across multiple cores more efficiently. Infrastructure adds RISC-V architectural smoke tests to the regression suite and shares one emulator build across workloads in each performance run. XS-GEM5 improves its two-thread memory model and adds instruction-level dispatch profiling.

<!-- more -->

## Recent Developments

### Frontend

- Bug fixes
  - Correct the guest physical address reported on instruction guest-page faults. On Kunminghu V3, query the ITLB with the start of the first fetch block and use the address it returns. On V2, preserve the address of the faulting VS-stage non-leaf PTE ([#6870](https://github.com/OpenXiangShan/XiangShan/pull/6870), [#6911](https://github.com/OpenXiangShan/XiangShan/pull/6911))
  - Use the minimum instruction length of 2 bytes for ICache ITLB and PMP checks to prevent false page faults on fetches at the end of the canonical address range on Kunminghu V2 and V3 ([#6945](https://github.com/OpenXiangShan/XiangShan/pull/6945), [#6947](https://github.com/OpenXiangShan/XiangShan/pull/6947))
  - Check ICache tag and data ECC only for valid fetch requests so an idle second slot cannot raise a spurious bus error ([#6871](https://github.com/OpenXiangShan/XiangShan/pull/6871))
  - Reconstruct the high bit of ITTAGE targets according to the fetch address mode, fixing indirect-jump predictions between the upper and lower canonical address ranges and extending unsigned guest physical addresses correctly in VS Bare mode ([#6986](https://github.com/OpenXiangShan/XiangShan/pull/6986))

### Backend

- RTL features
  - Add interrupt (`itrigger`) and exception (`etrigger`) triggers to Kunminghu V3, support the instruction-count trigger (`icount`) in slot 0, and align the trigger types advertised by the Spike reference model ([#6942](https://github.com/OpenXiangShan/XiangShan/pull/6942), [riscv-isa-sim #103](https://github.com/OpenXiangShan/riscv-isa-sim/pull/103))
- Bug fixes
  - Carry the valid bit and ROB index through each CSR read writeback stage so a redirect can cancel a wrong-path read before writeback ([#6853](https://github.com/OpenXiangShan/XiangShan/pull/6853))
  - Preserve the original ID when `hvictl` injects a VS interrupt so `vscause` and the vectored trap address use the same interrupt ID ([#6793](https://github.com/OpenXiangShan/XiangShan/pull/6793))
  - Delay decode restart by one cycle after a `vsetvl`-family flush so younger vector instructions see the cleared `vstart` at commit and avoid a spurious illegal-instruction exception ([#6983](https://github.com/OpenXiangShan/XiangShan/pull/6983))
  - Refetch when a CSR write changes whether a breakpoint is enabled at the current privilege level so fetch triggers use the updated setting ([#6865](https://github.com/OpenXiangShan/XiangShan/pull/6865))
  - Preserve the compressed-instruction flag on jump-unit redirects so the pipeline can identify the compressed jump that triggered the redirect ([#6917](https://github.com/OpenXiangShan/XiangShan/pull/6917))
- PPA optimizations
  - Share enqueue head-data selection across entries in each ROB bank to reduce replicated selection logic ([#6930](https://github.com/OpenXiangShan/XiangShan/pull/6930))
- Code quality
  - Store the commit type, functional-unit type and operation type separately in the ROB so exception and vector memory handling can read just those fields. Keep the full micro-op for debugging and verification ([#6937](https://github.com/OpenXiangShan/XiangShan/pull/6937))
- Debugging tools
  - Include floating-point issue-queue occupancy, issue and cancellation in top-down analysis to identify ROB-head stalls caused by issue cancellation ([#6709](https://github.com/OpenXiangShan/XiangShan/pull/6709))
  - Add an optional independent cold-reset input to the Bus Error Unit so recorded errors remain available after a warm reset ([#6740](https://github.com/OpenXiangShan/XiangShan/pull/6740))

### MemBlock and Cache

- RTL features
  - Add the supervisor CSR `stsoctl` to enable TSO for cacheable accesses on Kunminghu V2, with RVWMO selected at reset. TSO requires load-load violation checking to remain enabled and drains the SBuffer in FIFO order. Software must execute `fence rw,rw` after enabling TSO and before disabling it ([#6940](https://github.com/OpenXiangShan/XiangShan/pull/6940), [#6962](https://github.com/OpenXiangShan/XiangShan/pull/6962))
  - Skip page-faulting PTEs on L2 TLB refill and clear L1 TLB page-fault entries after use by default. Software can control this L1 TLB behavior through `smblockctl`, and NEMU models the same bit ([#6928](https://github.com/OpenXiangShan/XiangShan/pull/6928), [NEMU #1285](https://github.com/OpenXiangShan/NEMU/pull/1285))
- Address translation bug fixes
  - Ignore the global bit when caching an invalid PTE so cached faults stay local to their address space and an ASID-specific `sfence.vma` can clear a stale fault ([#6698](https://github.com/OpenXiangShan/XiangShan/pull/6698))
  - Clear stale page-walk state on a first-stage translation hit so an out-of-range guest physical address raises the correct fault. Preserve a duplicate request’s wait state when a second-stage walk response and a matching memory request arrive in the same cycle ([#6898](https://github.com/OpenXiangShan/XiangShan/pull/6898), [#7002](https://github.com/OpenXiangShan/XiangShan/pull/7002))
  - Match waiting requests against the pages covered by a first-stage walk response and clear all conflicting entries on an L1 TLB multi-hit to prevent repeated replays after overlapping refills ([#6973](https://github.com/OpenXiangShan/XiangShan/pull/6973), [#6978](https://github.com/OpenXiangShan/XiangShan/pull/6978))
  - Pause new L2 TLB requests when either instruction or data translations have gone too long without a response, allowing outstanding requests to complete ([#7018](https://github.com/OpenXiangShan/XiangShan/pull/7018))
- Load/store pipelines bug fixes
  - Prevent stores crossing a 16-byte boundary from inheriting stale whole-line write or prefetch flags, and keep forwarding protection for the second page of a split store until it leaves the StoreQueue so a younger load cannot read stale data ([#6770](https://github.com/OpenXiangShan/XiangShan/pull/6770), [#6822](https://github.com/OpenXiangShan/XiangShan/pull/6822))
  - Latch data and error flags while a non-cacheable load awaits writeback on V3 so reuse of the request ID cannot overwrite them. Flush buffered non-cacheable loads on redirect on V2 to prevent wrong-path writeback ([#6773](https://github.com/OpenXiangShan/XiangShan/pull/6773), [#6873](https://github.com/OpenXiangShan/XiangShan/pull/6873))
  - Defer load replay after a guest-page fault until the load reaches the ROB head, and select the older scalar or vector store when both contend for the address path so an access waiting for a guest physical address cannot block older instructions ([#6989](https://github.com/OpenXiangShan/XiangShan/pull/6989), [#6992](https://github.com/OpenXiangShan/XiangShan/pull/6992))
  - Select the kill signal from the active user of the shared DTLB port and cancel a first-stage prefetch when an atomic operation takes over so the prefetch cannot use the wrong physical address ([#6970](https://github.com/OpenXiangShan/XiangShan/pull/6970), [#6994](https://github.com/OpenXiangShan/XiangShan/pull/6994))
  - Record the matching byte address in `mtval` when a unit-stride vector memory access hits a breakpoint so the debugger can locate the affected element ([#6882](https://github.com/OpenXiangShan/XiangShan/pull/6882))
  - Latch the selected channel while a cache-management request awaits acceptance on Kunminghu V3 so backpressure cannot route it to the wrong channel. Fix the V2 StoreQueue MMIO and cache-management state machines so an error response cannot restart a request and `cbo.zero` completion releases the pending state ([#6907](https://github.com/OpenXiangShan/XiangShan/pull/6907), [#6991](https://github.com/OpenXiangShan/XiangShan/pull/6991))
- Cache and coherence bug fixes
  - Block probes to the same block and alias as soon as the L1 DCache receives the first refill beat so a probe cannot overtake a partially received refill ([#6931](https://github.com/OpenXiangShan/XiangShan/pull/6931))
  - Preserve the carry when counting CHI transmit-queue reservations in CoupledL2 so four in-flight reservations cannot be counted as zero ([XSCache #58](https://github.com/OpenXiangShan/XSCache/pull/58))
- Oceanus L2 development
  - Add optional L2 hit fast paths, disabled by default, register directory SRAM requests and responses, and look up each request in the replacement CAM before arbitration to shorten the selection path ([XSCache #56](https://github.com/OpenXiangShan/XSCache/pull/56), [XSCache #67](https://github.com/OpenXiangShan/XSCache/pull/67), [XSCache #73](https://github.com/OpenXiangShan/XSCache/pull/73), [XSCache #74](https://github.com/OpenXiangShan/XSCache/pull/74))
  - Lock the selected way for each allocating replacement, release a hit way once its tag and metadata are ready, and fix directory writebacks selecting the wrong way and release requests stalling ([XSCache #59](https://github.com/OpenXiangShan/XSCache/pull/59), [XSCache #60](https://github.com/OpenXiangShan/XSCache/pull/60), [XSCache #79](https://github.com/OpenXiangShan/XSCache/pull/79))
  - Defer conflicting snoops until prefill state commits and exclude the requester from read and MakeUnique snoops when its alias matches to prevent self-invalidation ([XSCache #68](https://github.com/OpenXiangShan/XSCache/pull/68), [XSCache #72](https://github.com/OpenXiangShan/XSCache/pull/72))
  - Register L2 data SRAM inputs for two cycles so each requester receives its read data in the cycle the response is valid ([XSCache #76](https://github.com/OpenXiangShan/XSCache/pull/76))

### XSAI

- RTL features
  - Support ordinary, transposed and whole-register stores from CUTE’s A and B matrix registers to memory and track TR stores in DiffTest; ordinary A and B loads can use either TR loader ([CUTE #55](https://github.com/OpenXiangShan/CUTE/pull/55), [difftest #1044](https://github.com/OpenXiangShan/difftest/pull/1044), [XSAI #177](https://github.com/OpenXiangShan/XSAI/pull/177))
  - Support a four-core ZhuJiang topology and align CHI node IDs with native endpoints ([XSAI #178](https://github.com/OpenXiangShan/XSAI/pull/178))
  - Support an optional independent ZhuJiang NoC clock domain, completing native asynchronous sockets, clock-domain crossings and sideband connections ([XSAICache #18](https://github.com/OpenXiangShan/XSAICache/pull/18), [XSAI #179](https://github.com/OpenXiangShan/XSAI/pull/179), [XSAI #180](https://github.com/OpenXiangShan/XSAI/pull/180))
- Bug fixes
  - Synchronize Kunminghu V2 bug fixes ([XSAI #176](https://github.com/OpenXiangShan/XSAI/pull/176), [XSAI #181](https://github.com/OpenXiangShan/XSAI/pull/181))
  - Fix source node IDs on outgoing requests, responses and data of the decoupled CoupledL2 CHI interface ([XSAICache #17](https://github.com/OpenXiangShan/XSAICache/pull/17))
- Debugging tools
  - Optimize CPU reference-model MMA checks by reusing decoded floating-point operands and improving auto-vectorization ([difftest #1038](https://github.com/OpenXiangShan/difftest/pull/1038))
  - Move asynchronous CPU MMA checks into a worker process with a shared thread pool to process requests from multiple DUT cores in parallel while preserving per-core result ordering ([difftest #1050](https://github.com/OpenXiangShan/difftest/pull/1050))
  - Reduce unnecessary software ROB scans in matrix DiffTest ([difftest #1047](https://github.com/OpenXiangShan/difftest/pull/1047), [difftest #1049](https://github.com/OpenXiangShan/difftest/pull/1049))
  - Enable row copies and the AVX2 transpose path for matrix memory accesses in shared NEMU references to speed up load/store verification ([NEMU #1284](https://github.com/OpenXiangShan/NEMU/pull/1284))
  - Fix rounding-mode reporting for floating-point MMA control events in NEMU ([NEMU #1311](https://github.com/OpenXiangShan/NEMU/pull/1311)) (thanks to community contributor [@Aharrypotter](https://github.com/Aharrypotter))
  - Support batched local XDMA FIFO reads to reduce FPGA DiffTest communication overhead ([difftest #1048](https://github.com/OpenXiangShan/difftest/pull/1048), [dma_ip_drivers #3](https://github.com/klin02/dma_ip_drivers/pull/3))
  - Connect the L2-only test top on the matrix-cache test branch and use a CHI subordinate-node model to respond directly to L2 requests for standalone trace replay in VCS ([XSAICache #16](https://github.com/OpenXiangShan/XSAICache/pull/16), [tl-test-new #105](https://github.com/OpenXiangShan/tl-test-new/pull/105))
  - Add end-of-trace readback checks to VCS matrix-cache test traces and recheck data after cache-line eviction ([tl-test-new #106](https://github.com/OpenXiangShan/tl-test-new/pull/106))
- Code quality
  - Support configurable SMP, CPU and hart counts in multicore firmware, and update the environment’s multicore ZhuJiang RTL revision ([xsai-env #3](https://github.com/OpenXiangShan/xsai-env/pull/3), [xsai-env #5](https://github.com/OpenXiangShan/xsai-env/pull/5))

### Infra

- Regression testing and simulation
  - Add 643 RISC-V architectural smoke tests to the basic EMU regression and run them in parallel across 29 instruction-set extension groups ([#6805](https://github.com/OpenXiangShan/XiangShan/pull/6805))
  - Build the emulator once per nightly or weekly performance run so every workload measures the same revision ([#6893](https://github.com/OpenXiangShan/XiangShan/pull/6893))
  - Add `--stuck-check` to EMU to sample each core’s retired-instruction count periodically and detect a simulation whose clock advances after retirement has stalled ([difftest #1043](https://github.com/OpenXiangShan/difftest/pull/1043))
  - Report DCache refills to DiffTest separately on each memory channel so simultaneous refills are checked before a later store updates reference memory ([#6987](https://github.com/OpenXiangShan/XiangShan/pull/6987))
  - Separate image decompression from RAM loading in DiffTest to load ELF files from gzip or zstd streams and detect truncated images. Integrate the updated loader into Kunminghu V2 ([difftest #1042](https://github.com/OpenXiangShan/difftest/pull/1042), [#6966](https://github.com/OpenXiangShan/XiangShan/pull/6966))
  - Finish outstanding checks on executed instructions when FPGA DiffTest reaches its instruction limit in FORK mode, then return the original stop reason to the host ([difftest #1037](https://github.com/OpenXiangShan/difftest/pull/1037))
  - Set the default reference checkpoint interval in FPGA DiffTest FORK mode to 1 second, enlarge the shared XDMA packet pool, and integrate the changes into MinJie ([difftest #1034](https://github.com/OpenXiangShan/difftest/pull/1034), [minjie-playground #48](https://github.com/OpenXiangShan/minjie-playground/pull/48))
  - Use the XiangShan-maintained Chisel 7.16.0-xiangshan-1 by default in Rocket Chip, Utility and DiffTest, while retaining the upstream Chisel build option ([rocket-chip #47](https://github.com/OpenXiangShan/rocket-chip/pull/47), [Utility #166](https://github.com/OpenXiangShan/Utility/pull/166), [difftest #1045](https://github.com/OpenXiangShan/difftest/pull/1045))
  - Fix lost interrupts under backpressure in the ChiselAIA IMSIC by arbitrating writes across interrupt files and holding a pending MSI while the FIFO is full. Integrate the fix into Kunminghu V2 ([ChiselAIA #55](https://github.com/OpenXiangShan/ChiselAIA/pull/55), [#6933](https://github.com/OpenXiangShan/XiangShan/pull/6933))
- NEMU reference model
  - Report the base of the second page when a scalar load or store crosses into a non-canonical page, matching the fault address reported by RTL ([NEMU #1257](https://github.com/OpenXiangShan/NEMU/pull/1257), [NEMU #1258](https://github.com/OpenXiangShan/NEMU/pull/1258))
  - Invalidate cached translations separately for host, VS and G stages. Flush decoded instruction blocks after translation invalidation or a direct trap so subsequent fetches use the current mappings and permissions ([NEMU #1297](https://github.com/OpenXiangShan/NEMU/pull/1297), [NEMU #1300](https://github.com/OpenXiangShan/NEMU/pull/1300), [NEMU #1304](https://github.com/OpenXiangShan/NEMU/pull/1304))
  - Clear the local LR/SC reservation when a cache-block operation touches the reservation set, preventing a later store-conditional from succeeding incorrectly ([NEMU #1295](https://github.com/OpenXiangShan/NEMU/pull/1295))
  - Mark VS Dirty after successful zero-length vector gathers, slides and mask logical operations to match the state at hardware commit ([NEMU #1286](https://github.com/OpenXiangShan/NEMU/pull/1286))
- GSIM simulator
  - Route GSIM assertion failures through DiffTest so LightSSS can wake its child process to generate a waveform ([gsim #154](https://github.com/OpenXiangShan/gsim/pull/154), [difftest #1035](https://github.com/OpenXiangShan/difftest/pull/1035))
  - Collect FST fields after resolving signal ownership so intermediate signals shared across simulation nodes appear in waveforms, and add `--trace-fst-max-width` to filter arrays by total bit width ([gsim #153](https://github.com/OpenXiangShan/gsim/pull/153), [gsim #160](https://github.com/OpenXiangShan/gsim/pull/160))
  - Fix alias substitution in nested dynamic array indices and code generation for top-level vector I/O accessors ([gsim #157](https://github.com/OpenXiangShan/gsim/pull/157), [gsim #162](https://github.com/OpenXiangShan/gsim/pull/162))

### XS-GEM5

- New feature exploration
  - Partition memory-queue and StoreBuffer capacity and per-cycle SQ-to-StoreBuffer bandwidth between the two threads in the SpMT model to limit contention ([XS-GEM5 #1277](https://github.com/OpenXiangShan/GEM5/pull/1277))
  - Let SMS select the prefetch level dynamically in the Ideal KMH-V3 configuration, using per-offset confidence and the triggering access to choose L2 or L3 and suppressing low-confidence prefetches ([XS-GEM5 #1318](https://github.com/OpenXiangShan/GEM5/pull/1318))
  - Add teacher–student learning to the physical and virtual BOP prefetchers so the student retains useful offsets across learning phases and uses them for prefetches once its coverage reaches the threshold ([XS-GEM5 #1319](https://github.com/OpenXiangShan/GEM5/pull/1319))
  - Use the fetch block’s start PC for PairTAGE tag comparisons, limit how far ahead a second taken block can be queued, and reset confidence when the pairing changes ([XS-GEM5 #1342](https://github.com/OpenXiangShan/GEM5/pull/1342))
- Model alignment and fixes
  - Cache the final guest-virtual to host-physical mapping in the L1 TLB during two-stage translation, keep intermediate results in L2 and the walker, and align L2 page-cache capacity and PTEs per entry with KMH-V3 RTL ([XS-GEM5 #1310](https://github.com/OpenXiangShan/GEM5/pull/1310), [XS-GEM5 #1323](https://github.com/OpenXiangShan/GEM5/pull/1323))
  - Align integer, floating-point and load issue-queue capacities with KMH-V3 RTL, estimate integer division latency from renamed operands, and use result timing for early wakeup of instructions that depend on integer or floating-point divides ([XS-GEM5 #1312](https://github.com/OpenXiangShan/GEM5/pull/1312), [XS-GEM5 #1324](https://github.com/OpenXiangShan/GEM5/pull/1324), [XS-GEM5 #1327](https://github.com/OpenXiangShan/GEM5/pull/1327))
  - Use the target actually selected by ITTAGE or RAS for third-stage fast training, and allow a later fall-through prediction to override an earlier taken prediction ([XS-GEM5 #1329](https://github.com/OpenXiangShan/GEM5/pull/1329), [XS-GEM5 #1333](https://github.com/OpenXiangShan/GEM5/pull/1333))
  - Exclude the SRAM select bit from the MainBTB set index so each SRAM can use its full set range ([XS-GEM5 #1344](https://github.com/OpenXiangShan/GEM5/pull/1344))
  - Notify sibling SMT threads when a local L1 write becomes visible so they can detect and replay loads that violate same-address read ordering ([XS-GEM5 #1346](https://github.com/OpenXiangShan/GEM5/pull/1346))
- Debugging tools
  - Add dispatch-time instruction profiling (DIP) to attribute wrong-path and refetch slots to the instruction that caused each redirect. DIP can generate CSV and Markdown reports alongside retirement-side TEA and is enabled by default for the single-thread classic-memory configuration ([XS-GEM5 #1311](https://github.com/OpenXiangShan/GEM5/pull/1311), [XS-GEM5 #1335](https://github.com/OpenXiangShan/GEM5/pull/1335))
  - Improve multi-hart differential checking in the classic memory model by distinguishing cache data from local store forwarding for each byte of a scalar load and checking both the destination register and updated memory for atomic operations ([XS-GEM5 #1356](https://github.com/OpenXiangShan/GEM5/pull/1356), [XS-GEM5 #1357](https://github.com/OpenXiangShan/GEM5/pull/1357))
  - Align the interrupt source and target privilege level between the simulator and its differential reference so both enter the same trap handler ([XS-GEM5 #1307](https://github.com/OpenXiangShan/GEM5/pull/1307))
- Infrastructure
  - Terminate the corresponding remote simulation process group when a distributed performance run loses its SSH connection, freeing workers after cancellation ([XS-GEM5 #1360](https://github.com/OpenXiangShan/GEM5/pull/1360))

## Performance Evaluation

Processor and SoC configuration

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit | `8b15f0652` |
| Date | 2026/11/13 |
| L1 ICache | 64 KB |
| L1 DCache | 64 KB |
| L2 Cache | 2 MB |
| L3 Cache | 32 MB |
| LSU | 3ld2st |
| Bus protocol | CHI E.b |
| Memory configuration | DDR4-3200 |

SPEC CPU2006 scores

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        | 57.95  | 61.55  | 410.bwaves          | 146.16 | 148.79 |
| 401.bzip2            | 31.13  | 32.48  | 416.gamess          | 61.92  | 57.83  |
| 403.gcc              | 64.38  | 62.64  | 433.milc            | 77.20  | 75.76  |
| 429.mcf              | 84.47  | 80.40  | 434.zeusmp          | 78.98  | 78.42  |
| 445.gobmk            | 47.24  | 45.42  | 435.gromacs         | 43.41  | 42.68  |
| 456.hmmer            | 55.27  | 67.38  | 436.cactusADM       | 89.30  | 95.89  |
| 458.sjeng            | 45.59  | 46.90  | 437.leslie3d        | 68.40  | 67.34  |
| 462.libquantum       | 167.97 | 382.01 | 444.namd            | 47.71  | 48.64  |
| 464.h264ref          | 70.29  | 74.06  | 447.dealII          | 86.24  | 168.68 |
| 471.omnetpp          | 59.25  | 60.66  | 450.soplex          | 70.56  | 81.47  |
| 473.astar            | 35.66  | 34.26  | 453.povray          | 84.37  | 72.64  |
| 483.xalancbmk        | 92.74  | 138.14 | 454.calculix        | 48.09  | 48.13  |
| GEOMEAN              | 61.09  | 69.05  | 459.GemsFDTD        | 82.97  | 83.30  |
|                      |        |        | 465.tonto           | 79.58  | 64.84  |
|                      |        |        | 470.lbm             | 128.13 | 151.49 |
|                      |        |        | 481.wrf             | 62.53  | 61.24  |
|                      |        |        | 482.sphinx3         | 68.88  | 100.23 |
|                      |        |        | GEOMEAN             | 74.21  | 78.56  |

Compiler configuration

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

The scores in this section are estimates from SimPoint-sampled program segments saved in XiangShan’s checkpoint format. A full SPEC CPU2006 evaluation or a measurement on silicon can yield different results.

## Related Links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Yanjun Li, Jinhong Zeng, Zechen Yang, Hanle Zhang, Kunlin You, Xin Li, Tianze Wu, Yiming Yan
