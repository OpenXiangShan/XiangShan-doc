---
slug: biweekly-58
date: 2024-09-02
categories:
  - Biweekly
---
# 【香山双周报 58】20240902 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 58 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期：WIP

<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - A ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- RVA23 Profile
    - B ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- 面积&功耗
    - C ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))


### 后端流水线

- Bug 修复
    - A ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- 时序优化
    - B ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- 寄存器堆 Cache
    - C ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- Difftest 框架
    - D ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- RVA23 Profile
    - E ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

### 访存与缓存

- CHI 总线
    - A ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- RVA23 Profile
    - B ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- 性能
    - C ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- 工具
    - D ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

- 时序优化
    - E ([#404](https://github.com/OpenXiangShan/XiangShan/pull/404))

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **8 月 24 日 49162c9 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------: | :----: | :---------------- | :----: |
| 400.perlbench     | 33.66  | 410.bwaves        | 76.67  |
| 401.bzip2         | 24.99  | 416.gamess        | 43.33  |
| 403.gcc           | 47.90  | 433.milc          | 42.42  |
| 429.mcf           | 58.75  | 434.zeusmp        | 59.01  |
| 445.gobmk         | 30.17  | 435.gromacs       | 37.87  |
| 456.hmmer         | 40.28  | 436.cactusADM     | 47.68  |
| 458.sjeng         | 29.72  | 437.leslie3d      | 46.13  |
| 462.libquantum    | 127.00 | 444.namd          | 34.34  |
| 464.h264ref       | 56.62  | 447.dealII        | 73.80  |
| 471.omnetpp       | 41.22  | 450.soplex        | 54.63  |
| 473.astar         | 29.09  | 453.povray        | 55.70  |
| 483.xalancbmk     | 75.13  | 454.Calculix      | 18.15  |
| **GEOMEAN**       | 44.18  | 459.GemsFDTD      | 37.00  |
|                   |        | 465.tonto         | 35.73  |
|                   |        | 470.lbm           | 101.16 |
|                   |        | 481.wrf           | 42.20  |
|                   |        | 482.sphinx3       | 51.45  |
|                   |        | **GEOMEAN**       | 47.15  |

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
