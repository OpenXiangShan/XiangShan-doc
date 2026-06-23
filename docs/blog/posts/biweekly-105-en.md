---
slug: biweekly-105-en
date: 2026-06-23
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 105] 20260623

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 105th issue of the biweekly report.

We are very excited to share with you an important component in the "XiangShan" + "Ruyi" ecosystem: RuyiSDK! This is a one-stop development resource management platform for RISC-V architecture, which integrates toolchains, simulators, runtime environments, and debugging tools based on the ruyi package manager and IDE plugin system, providing full-process development support. The platform has built a comprehensive matrix of RISC-V development boards and operating system support, providing developers with a more convenient operating experience and serving as an important infrastructure for promoting RISC-V development and ecosystem construction.

You can get more information through the following links:

- RuyiSDK official website: <https://ruyisdk.org/>
- RuyiSDK developer community: <https://ruyisdk.cn/>

RISC-V European Summit is ongoing! The XiangShan team has multiple talks and posters at the summit, and the detailed schedule can be found [here](https://mp.weixin.qq.com/s/gNpOxypE4UKLWLr2H103Yg).

In the opening report of the RISC-V International, CEO Andrea Gallo introduced the application of XiangShan in high-performance server scenarios.

![Andrea Gallo introducing the application of XiangShan in high-performance server scenarios](./figs/biweekly-104/riscv-international.jpg)

Deputy Director of the Institute of Computing Technology, Chinese Academy of Sciences, and Chief Scientist of Beijing Open Source Chip Research Institute, Researcher Bao Yungang gave a report titled "XiangShan Practice: The Path to Industrial Deployment of Open-Source High-Performance RISC-V Processor", introducing the industrial deployment path of XiangShan.

![Researcher Bao Yungang introducing the industrial deployment path of XiangShan](./figs/biweekly-104/xiangshan-1.jpg)

![XiangShan family](./figs/biweekly-104/xiangshan-2.jpg)

We also held the workshop of Unity Chip for the first time, sharing with everyone the exploration and practice of software-native open-source chip intelligent crowdsourcing verification.

![Unity Chip workshop](./figs/biweekly-104/unity_chip.jpg)

Regarding the recent development progress of XiangShan, the frontend continues to optimize timing while reducing redirect latency; the backend implements some new features and instruction set extensions; the memory subsystem fixes some bugs while optimizing L2 timing; XSAI optimizes code structure while advancing HBL2 support for CHI.

<!-- more -->

## Recent Developments

### Frontend

- PPA optimizations
  - Optimize UTAGE training and prediction timing ([#5517](https://github.com/OpenXiangShan/XiangShan/pull/5517))
  - Optimize SC counter accumulation timing ([#5999](https://github.com/OpenXiangShan/XiangShan/pull/5999))
  - Optimize history register timing ([#6076](https://github.com/OpenXiangShan/XiangShan/pull/6076))
  - Optimize BPU pc-related path timing ([#5945](https://github.com/OpenXiangShan/XiangShan/pull/5945))
  - Optimize IBuffer enqueue logic timing ([#6047](https://github.com/OpenXiangShan/XiangShan/pull/6047))
- Code quality
  - Refactor BPU Replacer to simplify redundant logic ([#6008](https://github.com/OpenXiangShan/XiangShan/pull/6008))
  - Refactor MBTB TargetFix to be parameterized and switchable, aligning it with UBTB/ABTB ([#6007](https://github.com/OpenXiangShan/XiangShan/pull/6007))
- Debugging tools
  - Fix FTQ perfQueue-related performance counter logic ([#6101](https://github.com/OpenXiangShan/XiangShan/pull/6101))

### Backend

- RTL features
  - Use sparse vector (SparseVec) for the structure of exception vector ([#5738](https://github.com/OpenXiangShan/XiangShan/pull/5738))
  - Sdtrig extension support tdata3 ([#5983](https://github.com/OpenXiangShan/XiangShan/pull/5983))

### MemBlock and Cache

- Bug Fixes
  - Fix the issue where cbo executes before instruction commit ([#6081](https://github.com/OpenXiangShan/XiangShan/pull/6081))
  - Fix the performance counters of loadUnit ([#5939](https://github.com/OpenXiangShan/XiangShan/pull/5939))
  - Add pointer exceed assert ([#5795](https://github.com/OpenXiangShan/XiangShan/pull/5795))
- Performance Optimizations
  - Implemente parallel enqueue for DCache MissQueue, allowing up to 4 miss_req per cycle ([#5887](https://github.com/OpenXiangShan/XiangShan/pull/5887))
  - Optimize Sbuffer request merging logic ([#6117](https://github.com/OpenXiangShan/XiangShan/pull/6117))
- Timing Optimizations
  - Fix the timing of Memblock ([#5963](https://github.com/OpenXiangShan/XiangShan/pull/5963))

### XSAI

- RTL features
  - Support the RISC-V BF16 extension ([XSAI #72](https://github.com/OpenXiangShan/XSAI/pull/72))
  - Switch scaling factor storage to XiangShan's SRAMTemplate for consistency with XiangShan ([CUTE #20](https://github.com/OpenXiangShan/CUTE/pull/20))
  - Implement PutFullData for TL-TL and TL-CHI ([HBL2 #3](https://github.com/OpenXiangShan/HBL2/pull/3))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | 8c4daa743  |
| Date                 | 2026/06/18 |
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
| 400.perlbench       | 50.55  | 49.66  | 410.bwaves         | 104.21 | 95.87  |
| 401.bzip2           | 28.61  | 29.56  | 416.gamess         | 57.76  | 54.82  |
| 403.gcc             | 57.06  | 40.22  | 433.milc           | 69.94  | 68.81  |
| 429.mcf             | 71.47  | 62.54  | 434.zeusmp         | 74.95  | 67.02  |
| 445.gobmk           | 39.90  | 40.89  | 435.gromacs        | 37.90  | 34.82  |
| 456.hmmer           | 54.84  | 65.42  | 436.cactusADM      | 80.64  | 91.86  |
| 458.sjeng           | 39.36  | 40.48  | 437.leslie3d       | 59.90  | 59.70  |
| 462.libquantum      | 141.89 | 312.28 | 444.namd           | 43.55  | 45.46  |
| 464.h264ref         | 66.56  | 72.86  | 447.dealII         | 69.14  | 74.72  |
| 471.omnetpp         | 43.55  | 42.80  | 450.soplex         | 58.74  | 69.98  |
| 473.astar           | 32.92  | 32.64  | 453.povray         | 76.71  | 70.42  |
| 483.xalancbmk       | 81.13  | 92.62  | 454.Calculix       | 44.54  | 40.60  |
| GEOMEAN             | 53.57  | 57.00  | 459.GemsFDTD       | 69.93  | 70.40  |
|                     |        |        | 465.tonto          | 54.49  | 37.22  |
|                     |        |        | 470.lbm            | 128.45 | 148.55 |
|                     |        |        | 481.wrf            | 56.39  | 42.33  |
|                     |        |        | 482.sphinx3        | 60.94  | 63.63  |
|                     |        |        | GEOMEAN            | 64.55  | 62.40  |

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

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Jiru Sun, Yanjun Li
