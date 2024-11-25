---
slug: biweekly-64
date: 2024-11-25
categories:
  - Biweekly
---

# 【香山双周报 64】20241125 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 64 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - bug ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 性能

- 功耗

### 后端流水线

- Bug 修复

- 时序/面积优化

- RVA23 Profile

### 访存与缓存

- CHI 总线

- Bug 修复

- PPA 优化

- 工具



## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **11 月 08 日 fbdb359 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.17  | 410.bwaves        | 76.73  |
| 401.bzip2         | 25.55  | 416.gamess        | 43.51  |
| 403.gcc           | 47.25  | 433.milc          | 44.07  |
| 429.mcf           | 58.61  | 434.zeusmp        | 56.96  |
| 445.gobmk         | 30.29  | 435.gromacs       | 37.46  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 49.48  |
| 458.sjeng         | 30.27  | 437.leslie3d      | 44.93  |
| 462.libquantum    | 124.52 | 444.namd          | 34.73  |
| 464.h264ref       | 57.82  | 447.dealII        | 75.09  |
| 471.omnetpp       | 39.74  | 450.soplex        | 54.54  |
| 473.astar         | 29.00  | 453.povray        | 56.03  |
| 483.xalancbmk     | 74.59  | 454.Calculix      | 18.35  |
| **GEOMEAN**       | 44.64  | 459.GemsFDTD      | 37.94  |
|                   |        | 465.tonto         | 38.21  |
|                   |        | 470.lbm           | 102.06 |
|                   |        | 481.wrf           | 43.45  |
|                   |        | 482.sphinx3       | 53.21  |
|                   |        | **GEOMEAN**       | 47.75  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/
* OpenLLC 的 github 仓库地址为: https://github.com/OpenXiangShan/OpenLLC

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
