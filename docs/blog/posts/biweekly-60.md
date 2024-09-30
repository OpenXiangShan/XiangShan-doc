---
slug: biweekly-60
date: 2024-09-30
categories:
  - Biweekly
---
# 【香山双周报 60】20240930 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 60 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，

<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复一个 Bug ([#bug](https://github.com/OpenXiangShan/XiangShan/pull/bug))

### 后端流水线

- Bug 修复
    - 持续推进功能 Bug 修复，共修复 ？？ 余例，以下是部分 PR：

- 时序优化

- RVA23 Profile

### 访存与缓存

- CHI 总线

- RVA23 Profile

- 性能

- Bug 修复

- 时序 & 面积优化


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **9 月 27 日 18560912f 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.94  | 410.bwaves        | 75.43  |
| 401.bzip2         | 25.57  | 416.gamess        | 44.04  |
| 403.gcc           | 46.57  | 433.milc          | 43.41  |
| 429.mcf           | 57.44  | 434.zeusmp        | 57.57  |
| 445.gobmk         | 30.19  | 435.gromacs       | 37.43  |
| 456.hmmer         | 41.45  | 436.cactusADM     | 48.71  |
| 458.sjeng         | 30.26  | 437.leslie3d      | 44.15  |
| 462.libquantum    | 125.11 | 444.namd          | 34.79  |
| 464.h264ref       | 57.91  | 447.dealII        | 75.53  |
| 471.omnetpp       | 39.88  | 450.soplex        | 54.70  |
| 473.astar         | 29.07  | 453.povray        | 56.33  |
| 483.xalancbmk     | 74.70  | 454.Calculix      | 18.34  |
| **GEOMEAN**       | 44.58  | 459.GemsFDTD      | 38.17  |
|                   |        | 465.tonto         | 38.59  |
|                   |        | 470.lbm           | 102.05 |
|                   |        | 481.wrf           | 44.27  |
|                   |        | 482.sphinx3       | 53.03  |
|                   |        | **GEOMEAN**       | 47.76  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
