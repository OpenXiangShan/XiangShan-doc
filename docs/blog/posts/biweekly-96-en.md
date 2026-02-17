---
slug: biweekly-96-en
date: 2026-02-16
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 96] 20260216

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 96th issue of the biweekly report.

Happy Chinese New Year! Welcome to our biweekly column during the Spring Festival, and we wish you in the new year:

- Frontend has the precise prediction like a unicorn, and career opportunities are never misjudged;
- The pipeline runs like a thousand horses, everything goes smoothly and in parallel;
- The memory subsystem is as vigorous as a dragon horse, and the happy data is inexhaustible;
- The memory access path is like a vast grassland, and the happy address is always mapped in the heart;
- The cache hierarchy is as warm as spring, and every precious memory is within reach;
- The bus bandwidth is like a thousand-mile horse, and the good luck signal arrives immediately at your side!

We also shared the wonderful review of the tutorial hosted by XiangShan team at HPCA 2026. Please visit <https://tutorial.xiangshan.cc/hpca26/> to review the content of this tutorial and get the slides. The next tutorial will be held at ISCA 2026 in Raleigh, North Carolina, USA in late June, and we look forward to seeing you again!

Regarding the recent development progress of XiangShan, ~~the XiangShan team is also having a happy Chinese New Year.~~ For the limited details, please see the recent progress section.

<!-- more -->

## Tutorial @ HPCA 2026

XiangShan successfully held a tutorial at HPCA 2026! We are very happy to meet everyone in Sydney, and we thank every participant and friend who cares about XiangShan's development!

![Group Photo](./figs/hpca2026-tutorial/group.jpg)

We continuously optimize the tutorial content based on the hosting effect and everyone's feedback, hoping to provide new friends with a clearer, more comprehensive, and in-depth introduction while also bringing new gains to old friends. The highlights in this tutorial include:

- The latest in-development KMH-V3 microarchitecture design philosophy, insights and design details.
- A new, independent introduction to our MinJie (agile) development toolchain.
- Invited talks from our partners, on:
  - XSCC, a high-performance compiler optimized for RISC-V and XiangShan, and

    ![XSCC on-site report](./figs/hpca2026-tutorial/xscc.jpg)
  - Baiyang, a high-performance open-source DDR controller IP.

    Unfortunately, the original speaker could not attend the event due to visa issues, so a member of the XiangShan team introduced it instead. We will continue to communicate with Baiyang team and look forward to inviting their member for a more in-depth introduction at the next tutorial!
- A more thorough and easy-to-use hands-on part based on code-server and jupyter notebook. We encourage everyone to use the docker environment and precompiled assets provided in <https://github.com/OpenXiangShan/bootcamp>.

![Agenda](./figs/hpca2026-tutorial/agenda.jpg)

During the coffee break, we had in-depth communication with excellent scholars from all over the world. We cherish the opportunity to communicate with everyone face-to-face, which can help everyone better understand the design of XiangShan microarchitecture and the use of agile toolchain, and make XiangShan a better infrastructure for academic research and industrial applications; on the other hand, it can also help us better understand everyone's feedback and innovative ideas, and continuously improve our design and toolchain. Thanks to every friend who participated in the communication! For those who could not attend, please feel free to communicate with us through <all@xiangshan.cc> mailing list, Github Issues, technical discussion QQ group, etc.

![Coffee Break](./figs/hpca2026-tutorial/chat.jpg)

## Recent Developments

### Frontend

In the past two weeks, due to several team members attending HPCA 2026 and the Spring Festival holiday, there are no new PRs merged into the mainline. The ongoing/awaiting review progress includes:

- Bug fixes
  - Fix the training condition of SC which does not check whether MBTB is hit, and leads to training with invalid data ([#5601](https://github.com/OpenXiangShan/XiangShan/pull/5601))
  - Fix the issue that saturate counters in MBTB baseTable are not updated when the branch is correctly predicted ([#5602](https://github.com/OpenXiangShan/XiangShan/pull/5602))
- Timing/Area optimization
  - In the early development of the V3 frontend, the main focus was on the functional implementation and performance tuning of the BPU rewrite to the region-BTB structure. As the functionality gradually stabilized in the recent month, intensive timing evaluation work was conducted. ~~As expected, it was a huge failure, with logic levels reaching three digits.~~ The issues were mainly concentrated on insufficient consideration of pipeline stage division and the use of inappropriate Scala magic for quick implementation, etc.. We have conducted multiple rounds of analysis and fixes for these issues. Some of the fixes for modules such as MBTB, TAGE, ICache were introduced in the previous two biweekly reports. The ongoing work in the past two weeks includes:
    - Adjusting BPU s2 pipeline stage, with some information from MBTB given to TAGE earlier ([#5614](https://github.com/OpenXiangShan/XiangShan/pull/5614))
    - Adjusting the pipeline stage of MBTB position comparison logic ([#5603](https://github.com/OpenXiangShan/XiangShan/pull/5603))
    - Adjusting the pipeline stage of UTAGE history information ([#5517](https://github.com/OpenXiangShan/XiangShan/pull/5517))
    - Fixing some serial logic inside SC (no PR for the moment)
    - Adjusting the pipeline stage of ICache parity check logic (no PR for the moment)
    - Further evaluation and fixes are ongoing

### Backend

- No progress for the moment

### MemBlock and Cache

- RTL new features
  - The refactoring and testing of MMU, LoadUnit, StoreQueue, L2, etc. is ongoing
  - Support MDP of StoreSet and fix some bugs ([#5576](https://github.com/OpenXiangShan/XiangShan/pull/5576))
- Bug fix
  - Fix bug that ICG is invalid when disable mbist in CoupledL2 ([CoupledL2 #470](https://github.com/OpenXiangShan/CoupledL2/pull/470))
- Debugging tools
  - Develop a verification tool CHI Test for the new version of L2 Cache. Continuous progressing

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters     | Options    |
| -------------- | ---------- |
| Commit         | 316946d28  |
| Date           | 02/11/2026 |
| L1 ICache      | 64KB       |
| L1 DCache      | 64KB       |
| L2 Cache       | 1MB        |
| L3 Cache       | 16MB       |
| LSU            | 3ld2st     |
| Bus protocol   | CHI        |
| Memory latency | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | GCC12  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  | GCC12  |
| :------------------ | :----: | :----: | :----: | :----------------- | :----: | :----: | :----: |
| 400.perlbench       | 47.31  | 46.45  | 43.61  | 410.bwaves         | 85.75  | 90.56  | 73.28  |
| 401.bzip2           | 27.00  | 27.83  | 27.51  | 416.gamess         | 56.09  | 52.50  | 54.94  |
| 403.gcc             | 50.77  | 37.33  | 51.30  | 433.milc           | 64.70  | 63.73  | 49.28  |
| 429.mcf             | 59.77  | 54.36  | 60.69  | 434.zeusmp         | 69.45  | 63.50  | 60.37  |
| 445.gobmk           | 35.62  | 36.59  | 37.44  | 435.gromacs        | 36.43  | 34.17  | 38.56  |
| 456.hmmer           | 53.68  | 63.60  | 43.52  | 436.cactusADM      | 75.62  | 86.54  | 53.69  |
| 458.sjeng           | 35.34  | 36.40  | 34.82  | 437.leslie3d       | 56.57  | 56.81  | 54.45  |
| 462.libquantum      | 135.53 | 285.26 | 133.21 | 444.namd           | 42.06  | 44.19  | 37.42  |
| 464.h264ref         | 62.41  | 71.27  | 63.01  | 447.dealII         | 63.32  | 67.16  | 64.28  |
| 471.omnetpp         | 40.88  | 39.25  | 43.04  | 450.soplex         | 49.19  | 57.92  | 53.33  |
| 473.astar           | 31.19  | 30.28  | 30.34  | 453.povray         | 72.39  | 66.59  | 61.60  |
| 483.xalancbmk       | 74.54  | 84.92  | 80.96  | 454.Calculix       | 44.18  | 39.20  | 19.43  |
| GEOMEAN             | 49.39  | 52.67  | 48.92  | 459.GemsFDTD       | 64.84  | 64.68  | 46.68  |
|                     |        |        |        | 465.tonto          | 51.71  | 34.73  | 36.69  |
|                     |        |        |        | 470.lbm            | 126.78 | 132.83 | 104.98 |
|                     |        |        |        | 481.wrf            | 55.25  | 41.58  | 48.68  |
|                     |        |        |        | 482.sphinx3        | 58.51  | 61.17  | 55.05  |
|                     |        |        |        | GEOMEAN            | 60.48  | 58.50  | 50.80  |


Compilation parameters are as follows:

| Parameters                  | GCC12    | GCC15       | XSCC                |
| --------------------------- | -------- | ----------- | ------------------- |
| Compiler                    | gcc12    | gcc15       | xscc                |
| Optimization level          | O3       | O3          | O3                  |
| Memory library              | jemalloc | jemalloc    | jemalloc            |
| -march                      | RV64GCB  | RV64GCB     | RV64GCB             |
| -ffp-contraction            | fast     | fast        | fast                |
| Linker optimization         | -        | -flto       | -flto               |
| Floating-point optimization | -        | -ffast-math | -ffast-math         |
| -mcpu                       | -        | -           | xiangshan-kunminghu |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://xiangshan-doc.readthedocs.io/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Junjie Yu, Yanjun Li
