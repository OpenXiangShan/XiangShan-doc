---
slug: biweekly-100-en
date: 2026-04-13
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 100] 20260413

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 100th issue of the biweekly report.

Starting with this issue, the biweekly will also report on progress for [XiangShan AI (XSAI)](https://github.com/OpenXiangShan/XSAI). XSAI is a unified general-purpose-and-inference AI processor implemented on the open-source, high-performance RISC-V XiangShan processor; the approach was presented at the 2025 RISC-V China Summit. XSAI is the XiangShan team’s exploration of unified general-purpose-and-inference AI chips on top of its existing RISC-V CPU ecosystem, and a practical application of XiangShan’s agile development methodology. The Beijing Institute of Open Source Chip, together with the Microprocessor Research Center and the Advanced Computer Systems Research Center at the Institute of Computing Technology, Chinese Academy of Sciences, jointly participate in XSAI development. In 2026, XSAI will gradually release instruction extension manuals, architecture documentation, and user manuals, open-source the development toolchain, and add material on the XSAI unified general-and-inference processor to the XiangShan tutorial series.

XSAI is currently developed on Kunming Lake V2R2, under the name Kunming Lake V2R2A. The final V2R2A will add bf16/fp8 vector extensions and bf16/fp8/int8 matrix extensions on top of V2R2, together with high-bandwidth L2 cache, for demonstration purposes. The XSAI group has recently run preliminary tests aimed at validating XSAI’s general-purpose and AI compute capabilities. This issue reports those test results to readers of the biweekly.

<!-- more -->

## Recent Developments

### Frontend

- RTL features
  - Use more precise sumAboveThreshold logic for SC ([#5716](https://github.com/OpenXiangShan/XiangShan/pull/5716))
  - Enable SC Global table ([#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756))
- Bug fixes
  - Fix the issue where metadata of the history register is updated incorrectly when an override from the advanced predictor occurs ([#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756))
- PPA optimizations
  - Expose SRAMTemplate resetState to the interface, allowing BPU to determine if SRAM is ready to receive requests ([#5735](https://github.com/OpenXiangShan/XiangShan/pull/5735)，[Utility#141](https://github.com/OpenXiangShan/Utility/pull/141))
  - More timing fixes are under evaluation
- Code quality
  - Refactor the parameter related to SC table indexing ([#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756))
- Debugging tools
  - Make Topdown Accurate Again! Collaboratively rewrite the Top-Down performance counters with the backend team ([#5564](https://github.com/OpenXiangShan/XiangShan/pull/5564))
  - Fix the issue where the condition for the BPU top-level `train_stall` counter is always false ([#5734](https://github.com/OpenXiangShan/XiangShan/pull/5734))

### Backend

- RTL New Features
- Increased the size of the integer RegCache to 24 to support a 6-ALU configuration ([#5613](https://github.com/OpenXiangShan/XiangShan/pull/5613))
- Modified `vsetvl x0, x0` to ensure that reserved cases behave consistently with Spike ([#5744](https://github.com/OpenXiangShan/XiangShan/pull/5744))
- Bug Fixes
- Preserved `dpc` during debug re-entry following a critical error ([#5730](https://github.com/OpenXiangShan/XiangShan/pull/5730))
- Synchronized fixes for debug-related bugs in V2 ([#5754](https://github.com/OpenXiangShan/XiangShan/pull/5754))
- Fixed issues related to `Mcontrol6`/`Tdata1` ([#5722](https://github.com/OpenXiangShan/XiangShan/pull/5722))
- Fixed `mis_pred` and `total_flush` metrics within the TopDown analysis ([#5762](https://github.com/OpenXiangShan/XiangShan/pull/5762))
- Fixed the driver for `psrcVl` in the Bypass stage, changing it to `pdestVl` ([#5743](https://github.com/OpenXiangShan/XiangShan/pull/5743))
- Timing Optimizations
- Optimized timing for the Rename stage ([#5685](https://github.com/OpenXiangShan/XiangShan/pull/5685))
- Code Quality
- Renamed `halt` to `wfi` ([#4512](https://github.com/OpenXiangShan/XiangShan/pull/4512))

### MemBlock and Cache

- RTL new features
  - Refactoring and testing of MMU, L2, and other modules are continuously progressing
  - Merge the new LoadUnit and StoreQueue into mainline and fix several related issues ([#5548](https://github.com/OpenXiangShan/XiangShan/pull/5548))
- Bug fixes
  - (V2) Fix the issue where Store MMIO does not mark ROB ([#5640](https://github.com/OpenXiangShan/XiangShan/pull/5640))
  - (V2) Fix the revoke logic of MisalignBuffer ([#5674](https://github.com/OpenXiangShan/XiangShan/pull/5674))
  - (V2) Fix the forward order hazard in Uncache module when mem_acquire is not fired ([#5630](https://github.com/OpenXiangShan/XiangShan/pull/5630))
  - (V2) Use a separate signal in L1Prefetcher to RegEnable PC ([#5720](https://github.com/OpenXiangShan/XiangShan/pull/5720))
  - Fix the exception type raised for misaligned accesses to MMIO regions ([#5700](https://github.com/OpenXiangShan/XiangShan/pull/5700))
- Timing fixes
  - Fix several MemBlock timing issues ([#5697](https://github.com/OpenXiangShan/XiangShan/pull/5697))

### XSAI

We used SPEC CPU 2006 to evaluate XSAI’s general-purpose compute capability. The checkpoints, processor parameters, and SoC parameters for this run match those in XiangShan Biweekly 91.

| SPECint 2006 est. | V2R2A@3GHz | V2R2@3GHz | SPECfp 2006 est. | V2R2A@3GHz | V2R2@3GHz |
| :---------------- | :--------: | :-------: | :--------------- | :--------: | :-------: |
| 400.perlbench     |   36.03    |   36.18   | 410.bwaves       |   67.35    |   66.73   |
| 401.bzip2         |   25.75    |   25.46   | 416.gamess       |   40.61    |   40.99   |
| 403.gcc           |   48.15    |   48.00   | 433.milc         |   44.38    |   45.12   |
| 429.mcf           |   63.26    |   60.63   | 434.zeusmp       |   51.65    |   51.61   |
| 445.gobmk         |   30.30    |   30.32   | 435.gromacs      |   33.50    |   33.60   |
| 456.hmmer         |   41.35    |   41.62   | 436.cactusADM    |   46.06    |   46.19   |
| 458.sjeng         |   30.25    |   30.24   | 437.leslie3d     |   48.31    |   47.97   |
| 462.libquantum    |   126.54   |  122.43   | 444.namd         |   28.82    |   28.86   |
| 464.h264ref       |   56.49    |   56.58   | 447.dealII       |   73.37    |   73.55   |
| 471.omnetpp       |   42.32    |   41.77   | 450.soplex       |   52.85    |   52.50   |
| 473.astar         |   29.23    |   29.19   | 453.povray       |   53.05    |   53.46   |
| 483.xalancbmk     |   71.39    |   72.84   | 454.Calculix     |   16.35    |   16.37   |
| GEOMEAN           |   44.92    |   44.66   | 459.GemsFDTD     |   38.31    |   38.60   |
|                   |            |           | 465.tonto        |   36.65    |   36.66   |
|                   |            |           | 470.lbm          |   91.30    |   91.94   |
|                   |            |           | 481.wrf          |   40.25    |   40.70   |
|                   |            |           | 482.sphinx3      |   48.88    |   49.13   |
|                   |            |           | GEOMEAN          |   44.72    |   44.85   |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

> **Takeaway:** The 3GHz V2R2A frequency is only a simulation setting, chosen to match V2R2 simulation and check that XSAI changes do not cause large performance regressions. We expect XSAI silicon to run below 3GHz. For general-purpose workloads, differences mainly come from the high-bandwidth L2 design and changes to the cache replacement policy. Overall, these results suggest XSAI’s changes do not materially affect XiangShan’s baseline general-purpose behavior or performance.

For AI inference, we ran Llama-2 15M on an XCVU19p FPGA using a trimmed V2R2A. XSAI ran at 50MHz, matrix int8 throughput is 4 TOPS/GHz, memory DDR4-2400 MHz. Measured Prefill and Decode throughput were 343.61 tok/s and 36.24 tok/s respectively; outputs matched expectations.

![XSAI FPGA test](./figs/biweekly-100/XSAI-fpga.png)

> **Takeaway:** Memory frequency is close to what we expect post-silicon, but the XSAI clock is far below silicon targets—so in that sense the results are optimistic. Conversely, V2R2A was heavily trimmed to fit XCVU19p, which hurts performance—so in that sense the results are pessimistic. Treat this as a functional prototype only: it shows XSAI can support large-model inference in principle.

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters     | Options    |
| -------------- | ---------- |
| Commit         | 87d03b2cc  |
| Date           | 2026/03/24 |
| L1 ICache      | 64KB       |
| L1 DCache      | 64KB       |
| L2 Cache       | 1MB        |
| L3 Cache       | 16MB       |
| LSU            | 3ld2st     |
| Bus protocol   | CHI        |
| Memory latency | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.54  | 47.50  | 410.bwaves         | 85.76  | 90.75  |
| 401.bzip2           | 27.41  | 28.22  | 416.gamess         | 56.92  | 53.01  |
| 403.gcc             | 55.42  | 38.93  | 433.milc           | 64.88  | 63.62  |
| 429.mcf             | 59.81  | 54.32  | 434.zeusmp         | 70.31  | 64.42  |
| 445.gobmk           | 39.25  | 40.59  | 435.gromacs        | 36.39  | 34.26  |
| 456.hmmer           | 53.63  | 63.65  | 436.cactusADM      | 75.77  | 86.49  |
| 458.sjeng           | 39.50  | 39.74  | 437.leslie3d       | 56.50  | 52.29  |
| 462.libquantum      | 135.53 | 294.09 | 444.namd           | 42.58  | 44.54  |
| 464.h264ref         | 62.93  | 71.26  | 447.dealII         | 64.88  | 69.53  |
| 471.omnetpp         | 41.18  | 39.38  | 450.soplex         | 49.79  | 60.47  |
| 473.astar           | 31.04  | 30.22  | 453.povray         | 73.02  | 66.48  |
| 483.xalancbmk       | 74.59  | 84.30  | 454.Calculix       | 43.93  | 39.70  |
| GEOMEAN             | 50.84  | 53.98  | 459.GemsFDTD       | 64.37  | 64.29  |
|                     |        |        | 465.tonto          | 52.49  | 34.91  |
|                     |        |        | 470.lbm            | 126.77 | 132.75 |
|                     |        |        | 481.wrf            | 55.04  | 41.52  |
|                     |        |        | 482.sphinx3        | 58.62  | 61.20  |
|                     |        |        | GEOMEAN            | 60.79  | 58.63  |

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

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
