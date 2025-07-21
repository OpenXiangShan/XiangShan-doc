---
slug: biweekly-81
date: 2025-07-21
categories:
  - Biweekly
---

# 【香山双周报 81】20250721 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 81 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 面积

### 后端流水线

- Bug 修复

- 时序/面积优化

- RVA23 Profile

### 访存与缓存

- RVA23 Profile

- Bug 修复
    - L2 Cache 对实时设备相关事务保留最大 QoS ([CoupledL2 #423](https://github.com/OpenXiangShan/CoupledL2/pull/423))
    - 修复 RefillBuffer 到 DataStorage 的数据 X 态错误传播问题 ([CoupledL2 #426](https://github.com/OpenXiangShan/CoupledL2/pull/426))

- PPA 优化


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **7 月 17 日 a193669 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.89  | 410.bwaves        | 67.24  |
| 401.bzip2         | 25.51  | 416.gamess        | 41.00  |
| 403.gcc           | 47.91  | 433.milc          | 44.95  |
| 429.mcf           | 60.17  | 434.zeusmp        | 51.71  |
| 445.gobmk         | 30.71  | 435.gromacs       | 33.65  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.65  | 437.leslie3d      | 47.77  |
| 462.libquantum    | 122.65 | 444.namd          | 28.88  |
| 464.h264ref       | 56.62  | 447.dealII        | 73.21  |
| 471.omnetpp       | 41.49  | 450.soplex        | 52.55  |
| 473.astar         | 29.35  | 453.povray        | 53.48  |
| 483.xalancbmk     | 72.75  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.70  | 459.GemsFDTD      | 40.45  |
|                   |        | 465.tonto         | 36.68  |
|                   |        | 470.lbm           | 91.96  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.12  |
|                   |        | **GEOMEAN**       | 44.98  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
- 香山文档：https://xiangshan-doc.readthedocs.io/
- 香山用户手册：https://docs.xiangshan.cc/projects/user-guide/
- 香山设计文档：https://docs.xiangshan.cc/projects/design/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁