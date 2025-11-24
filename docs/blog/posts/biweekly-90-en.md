---
slug: biweekly-90-en
date: 2025-11-24
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 90] 20251124

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. We look forward to your contribution.

This is the 90th issue of the biweekly report.

XiangShan development-wise, the frontend team continued to fix performance bugs caused by BPU refactoring~~hoping that performance can reach pre-refactoring levels by the next biweekly report~~. The backend team is steadily advancing bug fixes and new feature development. The MemBlock team is continuously pushing forward with the V3 refactoring and testing of various modules, fixing some V2 functional bugs, optimizing timing, and improving code quality.

<!-- more -->

## Development Bonus
The dual-core Kunming Lake V2 successfully booted GUI OpenEuler 24.03 on FPGA at 50MHz! We also successfully ran LibreOffice and had a passionate game of DOOM! This marks a milestone in XiangShan's verification work and gives us greater confidence.

Due to the low frequency of the FPGA, the boot is a bit slow, so please be patient~

(Due to GitHub limitations, please watch on the official WeChat public account)

~~Please ignore the image quality issue, this is an extremely artistic shaky camera~~

## Recent Developments

### Frontend

- RTL feature
  - Support Hardware Error exception introduced in RISC-V Privileged Spec v1.13 ([#4770](https://github.com/OpenXiangShan/XiangShan/pull/4770))
  - Enable UBTB fast training ([#5145](https://github.com/OpenXiangShan/XiangShan/pull/5145))
  - Remove takenCnt and valid fields of UBTB ([#5157](https://github.com/OpenXiangShan/XiangShan/pull/5157))
  - Implement globalTable for SC predictor ([#5150](https://github.com/OpenXiangShan/XiangShan/pull/5150))
  - Support PHR tracking branch target ([#5169](https://github.com/OpenXiangShan/XiangShan/pull/5169))
  - ABTB override fast predict, MicroTAGE and other new performance features are being explored
  - Decoupled BPU train and commit path refactoring are in progress
- Bug Fix
  - Fix the X-state propagation issue caused by ABTB and MBTB SRAM read data not being latched ([#5153](https://github.com/OpenXiangShan/XiangShan/pull/5153))
  - Fix the issue related to ABTB training conditions ([#5160](https://github.com/OpenXiangShan/XiangShan/pull/5160))
  - Fix the issue of non-one-hot waymask in MBTB multi-hit flush logic ([#5181](https://github.com/OpenXiangShan/XiangShan/pull/5181))
  - Fix the issue of incorrect set index calculation for TAGE BaseTable and MBTB ([#5155](https://github.com/OpenXiangShan/XiangShan/pull/5155))
  - Fix the issue related to mismatch of PHR pointer metadata ([#5139](https://github.com/OpenXiangShan/XiangShan/pull/5139))
  - Fix the issue related to WriteBuffer write port wiring ([#5143](https://github.com/OpenXiangShan/XiangShan/pull/5143))
  - Fix the issue where IBuffer still records exceptions when the number of enqueued entries is 0 ([#5147](https://github.com/OpenXiangShan/XiangShan/pull/5147))
- Timing optimization
  - (V2) Replace the dual-port SRAM of FTQ with registers ([#5142](https://github.com/OpenXiangShan/XiangShan/pull/5142))
- Area optimization
  - Support ICache WayLookup to only store the first exception encountered after power-on/redirection ([#4959](https://github.com/OpenXiangShan/XiangShan/pull/4959), [#5165](https://github.com/OpenXiangShan/XiangShan/pull/5165))
- Code quality improvements
  - Refactor the fast training interface of s1 predictors ([#5144](https://github.com/OpenXiangShan/XiangShan/pull/5144))
  - Refactor MBTB alignBank and fix the issue of incorrect bank index calculation ([#5159](https://github.com/OpenXiangShan/XiangShan/pull/5159))

### Backend

- RTL new features
  - Implementing the new design of V3 vector unit is in progress
  - Adding valid flags for each traceGroup and tracking support for the mstatus register in the top-level debug module ([#5146](https://github.com/OpenXiangShan/XiangShan/pull/5146))
- Bug fixes
  - Fixing issues related to nmi register gating ([#5067](https://github.com/OpenXiangShan/XiangShan/pull/5067)[#5215](https://github.com/OpenXiangShan/XiangShan/pull/5215))
  - Rejecting out-of-order reads of xip-type CSRs ([#5131](https://github.com/OpenXiangShan/XiangShan/pull/5131))
  - Fixing incorrect dependencies on oldVd, ROB compression, and other issues
- Code quality improvements
  - Optimizing the code quality of the V3 backend, removing some redundant code, modifying some code styles, and performing some renaming ([#5135](https://github.com/OpenXiangShan/XiangShan/pull/5135))
- Timing optimization
  - Advancing the evaluation and optimization of vector reduction, Regfile, and other units

### MemBlock and Cache

- RTL new features
  - (V2) Add pmu perfevents for TLB ([#5205](https://github.com/OpenXiangShan/XiangShan/pull/5205))
  - (V2) Add some perfevents in CoupledL2 ([CoupledL2 #437](https://github.com/OpenXiangShan/CoupledL2/pull/437), [CoupledL2 #441](https://github.com/OpenXiangShan/CoupledL2/pull/441))
  - Add berti prefetcher ([#5049](https://github.com/OpenXiangShan/XiangShan/pull/5049))
  - Adjust the interface of issue and writeback in MemBlock ([#5167](https://github.com/OpenXiangShan/XiangShan/pull/5167))
  - The refactoring and testing of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
- Bug fix
  - (V2) Fix the issue where PMM was not disabled when MXR was active ([#4997](https://github.com/OpenXiangShan/XiangShan/pull/4997))
  - (V2) Fix the issue of timing mismatch of corrupt when DCache forwarding ([#5228](https://github.com/OpenXiangShan/XiangShan/pull/5228))
  - (V2) Add enable bit to determine whether checking KeyID ([#5241](https://github.com/OpenXiangShan/XiangShan/pull/5241))
  - (V2) Fix the issue in CoupledL2 where SnpUnique was incorrectly decoded as SnpPreferUnique ([CoupledL2 #438](https://github.com/OpenXiangShan/CoupledL2/pull/438))
  - (V2) Add l-credit manager in CoupledL2 to fix performance ([CoupledL2 #433](https://github.com/OpenXiangShan/CoupledL2/pull/433))
- Timing
  - (V2) Simplify the CMO req in RXSNP in CoupledL2 and pipeline RXSNP and RXDAT ([CoupledL2 #436](https://github.com/OpenXiangShan/CoupledL2/pull/436)) 

## Performance Evaluation

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.82  | 410.bwaves       | 67.23  |
| 401.bzip2         | 25.40  | 416.gamess       | 40.96  |
| 403.gcc           | 47.81  | 433.milc         | 45.06  |
| 429.mcf           | 60.26  | 434.zeusmp       | 51.80  |
| 445.gobmk         | 30.24  | 435.gromacs      | 33.58  |
| 456.hmmer         | 41.60  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.35  | 437.leslie3d     | 47.88  |
| 462.libquantum    | 122.66 | 444.namd         | 28.86  |
| 464.h264ref       | 56.55  | 447.dealII       | 73.57  |
| 471.omnetpp       | 41.43  | 450.soplex       | 52.49  |
| 473.astar         | 29.12  | 453.povray       | 53.44  |
| 483.xalancbmk     | 72.71  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.54  | 459.GemsFDTD     | 39.73  |
|                   |        | 465.tonto        | 36.65  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.65  |
|                   |        | 482.sphinx3      | 49.09  |
|                   |        | GEOMEAN          | 44.94  |

We use SimPoint to sample programs and create checkpoints images based on our custom format. The coverage of SimPoint clustering reaches 100%. Note that the above scores are estimated based on program segments rather than a complete SPEC CPU2006 evaluation, which may deviate from the actual performance of real chips.

Compilation parameters are as follows:

|                    |          |
| ------------------ | -------- |
| Compiler           | gcc12    |
| Optimization level | O3       |
| Memory library     | jemalloc |
| -march             | RV64GCB  |
| -ffp-contraction   | fast     |

Processor and SoC parameters are as follows:

|                |            |
| -------------- | ---------- |
| Commit         | 1e9f1b4    |
| Date           | 11/07/2025 |
| L1 ICache      | 64KB       |
| L1 DCache      | 64KB       |
| L2 Cache       | 1MB        |
| L3 Cache       | 16MB       |
| LSU            | 3ld2st     |
| Bus protocol   | TileLink   |
| Memory latency | DDR4-3200  |

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
