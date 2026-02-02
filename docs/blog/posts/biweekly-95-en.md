---
slug: biweekly-95-en
date: 2026-02-02
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 95] 20260202

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 95th issue of the biweekly report.

In terms of XiangShan development, the frontend team is wrapping up the 1-taken 1-fetch architecture while exploring the 2-taken 2-fetch architecture; the backend team continues to advance the design of the vector unit and refactor multiple modules; the memory access team has fixed several bugs and is continuing to explore prefetching and MDP.

<!-- more -->

## Accelerate! Accelerate!!
As we all know, processor simulation is very computationally intensive. The complete performance regression of XiangShan uses a total of 1169 checkpoints. When simulating with Verilator, we usually compile versions with 8 or 16 threads to improve simulation speed. Even so, some checkpoints still take tens of hours to run.

With the increasing scale of V3, the simulation speed has dropped to about 1/3 of V2's speed, which exacerbates the already slow performance regression. More critically, V3 is currently undergoing rapid performance iterations, and the demand for performance regression is greater than ever. Optimizing performance without data is like driving blindfolded.

To address the simulation speed issue, we first identified the cause of the performance degradation when using Verilator. Through comparative analysis, we found that a significant part of the slowdown in V3's simulation speed was due to the upgrade to Chisel 7. Simply put, Chisel 7 changed the way Mux1H is generated, leading Verilator to produce lookup tables instead of array accesses. A detailed analysis can be found in this [issue](https://github.com/verilator/verilator/issues/6760). This fix can bring a 100% speed improvement, and the related fix has already been merged into the Verilator mainline.

However, even with a 100% speed increase, V3's simulation speed is still only 60% of V2's. To further improve simulation speed, we introduced [GSIM](https://github.com/OpenXiangShan/gsim), a simulator developed by the XiangShan team. To be precise, GSIM does not actually speed up simulation; the single-threaded GSIM simulation speed is slightly worse than 16-thread Verilator and slightly better than 8-thread Verilator. Although the speed has not improved, the parallelism has increased by 10 times, which means we can now perform 10 times the number of performance regressions with the same computational resources.

To further utilize existing servers, team members L and X recently developed a XiangShan-specific job scheduling system based on GitHub called [perf trigger](https://github.com/OpenXiangShan/XiangShan/actions/workflows/perf-trigger.yml). This youthful version of the LSF system can leverage all servers while centrally managing all simulation configurations and results. Perf trigger has successfully managed multiple performance regression jobs. Although there are sometimes some instability issues~~such as GitHub Runners automatically restarting at 4 AM due to network issues, limited bandwidth, and server maintenance~~, perf trigger has received high praise throughout the XiangShan team.

## Recent Developments

### Frontend

- RTL feature
  - Use LRU replacement algorithm for MBTB and update it with accurate prediction results from TAGE-SC to keep useful branches in MBTB as much as possible ([#5525](https://github.com/OpenXiangShan/XiangShan/pull/5525))
  - Implement SC BW table ([#5528](https://github.com/OpenXiangShan/XiangShan/pull/5528))
  - Support RAS to provide prediction results in S1 ([#5366](https://github.com/OpenXiangShan/XiangShan/pull/5366))
- Bug Fix
  - Add reset for BPU training pipeline control signals to avoid X state ([#5539](https://github.com/OpenXiangShan/XiangShan/pull/5539))
  - Fix the issue of signed saturating counter over/underflow ([#5545](https://github.com/OpenXiangShan/XiangShan/pull/5545))
  - Fix the issue of signed saturating counter isWeakPositive method ([#5551](https://github.com/OpenXiangShan/XiangShan/pull/5551))
- Timing/Area optimization
  - Remove the restriction of not reading SRAM across pages in MBTB to avoid timing issues caused by read valid and write ready timing paths being chained together ([#5541](https://github.com/OpenXiangShan/XiangShan/pull/5541))
- Debugging tools
  - Fix some performance counter conditions ([#5536](https://github.com/OpenXiangShan/XiangShan/pull/5536), [#5568](https://github.com/OpenXiangShan/XiangShan/pull/5568))

### Backend

- RTL new features
  - Refactor the multiplier unit ([#5514](https://github.com/OpenXiangShan/XiangShan/pull/5514))
  - Split int Regfile into 4 banks to reduce read conflicts ([#5438](https://github.com/OpenXiangShan/XiangShan/pull/5438))
- Timing/Area optimization
  - Memory unit redirection is no longer written back through flushpipe and replayInst (slow redirect), but unified through memviolation (fast redirect) ([#5491](https://github.com/OpenXiangShan/XiangShan/pull/5491))
  - Adjust the timing of TopDown ([#5451](https://github.com/OpenXiangShan/XiangShan/pull/5451))
- Code optimizations
  - Remove dead code isXret ([#5483](https://github.com/OpenXiangShan/XiangShan/pull/5483))
  - Use case class Imm for configuration on immediates instead of directly using UInt ([#5523](https://github.com/OpenXiangShan/XiangShan/pull/5523))
  - Remove some useless code related to IssueQueue ([#5519](https://github.com/OpenXiangShan/XiangShan/pull/5519))
  - Remove unnecessary conditional checks outside assertions in Regfile ([#5505](https://github.com/OpenXiangShan/XiangShan/pull/5505))
- Performance analysis tools
  - Add backend V2 configuration parameter BackendV2Config for performance comparison ([#5476](https://github.com/OpenXiangShan/XiangShan/pull/5476))

### MemBlock and Cache

- RTL new features
  - The refactoring and testing of MDP, MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - Fixed the timeout judgment logic in Sbuffer, with the timeout threshold configured via SMBLOCKCTL in CSR (#5573: https://github.com/OpenXiangShan/XiangShan/pull/5573)
- Debugging tools
  - Continuous improvement of CHI infrastructure CHIron
  - Develop a verification tool CHI Test for the new version of L2 Cache. Continuous progressing

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 38.59  | 410.bwaves       | 73.45  |
| 401.bzip2         | 27.13  | 416.gamess       | 54.67  |
| 403.gcc           | 47.59  | 433.milc         | 50.97  |
| 429.mcf           | 58.76  | 434.zeusmp       | 60.65  |
| 445.gobmk         | 37.31  | 435.gromacs      | 38.47  |
| 456.hmmer         | 43.58  | 436.cactusADM    | 53.99  |
| 458.sjeng         | 34.16  | 437.leslie3d     | 54.47  |
| 462.libquantum    | 132.86 | 444.namd         | 37.28  |
| 464.h264ref       | 62.77  | 447.dealII       | 64.50  |
| 471.omnetpp       | 42.60  | 450.soplex       | 54.20  |
| 473.astar         | 30.43  | 453.povray       | 61.69  |
| 483.xalancbmk     | 80.75  | 454.Calculix     | 19.39  |
| GEOMEAN           | 47.79  | 459.GemsFDTD     | 47.03  |
|                   |        | 465.tonto        | 36.23  |
|                   |        | 470.lbm          | 105.07 |
|                   |        | 481.wrf          | 48.84  |
|                   |        | 482.sphinx3      | 55.21  |
|                   |        | GEOMEAN          | 50.97  |

Compilation parameters are as follows:

| Parameters         | Options  |
| ------------------ | -------- |
| Compiler           | gcc12    |
| Optimization level | O3       |
| Memory library     | jemalloc |
| -march             | RV64GCB  |
| -ffp-contraction   | fast     |

Processor and SoC parameters are as follows:

| Parameters     | Options    |
| -------------- | ---------- |
| Commit         | fd1e37f95  |
| Date           | 01/16/2026 |
| L1 ICache      | 64KB       |
| L1 DCache      | 64KB       |
| L2 Cache       | 1MB        |
| L3 Cache       | 16MB       |
| LSU            | 3ld2st     |
| Bus protocol   | CHI        |
| Memory latency | DDR4-3200  |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
