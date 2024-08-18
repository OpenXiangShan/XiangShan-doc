---
slug: biweekly-57
date: 2024-08-19
categories:
  - Biweekly
---
# 【香山双周报 57】20240819 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 57 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

WIP：这里要补充一行概述

<!-- more -->

## 近期进展

### 前端

### 后端流水线

### 访存与缓存

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用jemalloc内存库，设置SPEC06FP的-ffp-contraction选项为fast，指令集为RV64GCB。我们使用 **8 月 12 日 9d9be651a 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006      | @ 3GHz | SPECfp 2006       | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 33.52  | 410.bwaves        | 76.87  |
| 401.bzip2         | 24.96  | 416.gamess        | 43.36  |
| 403.gcc           | 47.68  | 433.milc          | 42.66  |
| 429.mcf           | 58.82  | 434.zeusmp        | 59.14  |
| 445.gobmk         | 30.03  | 435.gromacs       | 37.84  |
| 456.hmmer         | 40.26  | 436.cactusADM     | 47.84  |
| 458.sjeng         | 29.72  | 437.leslie3d      | 45.73  |
| 462.libquantum    | 126.91 | 444.namd          | 34.32  |
| 464.h264ref       | 56.48  | 447.dealII        | 74.12  |
| 471.omnetpp       | 41.12  | 450.soplex        | 54.53  |
| 473.astar         | 28.96  | 453.povray        | 55.70  |
| 483.xalancbmk     | 75.09  | 454.Calculix      | 18.14  |
| **GEOMEAN**       | 44.09  | 459.GemsFDTD      | 36.91  |
|                   |        | 465.tonto         | 35.73  |
|                   |        | 470.lbm           | 101.20 |
|                   |        | 481.wrf           | 42.14  |
|                   |        | 482.sphinx3       | 51.49  |
|                   |        | **GEOMEAN**       | 47.16  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
