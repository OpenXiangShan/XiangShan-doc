---
slug: biweekly-67
date: 2025-01-06
categories:
  - Biweekly
---

# 【香山双周报 67】20250106 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 67 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 面积

### 后端流水线

- Bug 修复
    - 修复 CSR 指令未能报出地址翻译异常的问题 ([#4118](https://github.com/OpenXiangShan/XiangShan/pull/4118))
    - 修复 hideleg 寄存器中 LCOFI 的读写依赖问题 ([#4070](https://github.com/OpenXiangShan/XiangShan/pull/4070))，NEMU 也进行相应修复 ([NEMU #733](https://github.com/OpenXiangShan/NEMU/pull/733))
    - 修复 CSR 改为部分可流水后未能正确相应冲刷流水信号的问题 ([#4079](https://github.com/OpenXiangShan/XiangShan/pull/4079))
    - 修复在用户模式 time 寄存器更新出错 ([#4132](https://github.com/OpenXiangShan/XiangShan/pull/4132))
    - 修复 lui/fld 指令融合在目的寄存器是零寄存器时行为出错 ([#4131](https://github.com/OpenXiangShan/XiangShan/pull/4131))
    - 修复 Hint 类指令错误融合的问题 ([#4108](https://github.com/OpenXiangShan/XiangShan/pull/4108))
    - NEMU 修复 SGEI 中断优先级异常问题 ([#733](https://github.com/OpenXiangShan/NEMU/pull/733))

- 时序/面积优化
    - 将浮点/向量 Regfile 改为分4块 ([#4088](https://github.com/OpenXiangShan/XiangShan/pull/4088))
    - 修复 rob 中出队刷新流水线以及向量异常时序问题 ([#4075](https://github.com/OpenXiangShan/XiangShan/pull/4075))
    - 将判断向量复杂译码判断信号改为由指令编码直出 ([#4066](https://github.com/OpenXiangShan/XiangShan/pull/4066))
    - 将 CSR 输出到前端/访存的读写地址/数据打拍 ([#4119](https://github.com/OpenXiangShan/XiangShan/pull/4119))

- 工具 
    - 添加 Top-Down 后端相关硬件性能计数事件（[#4122](https://github.com/OpenXiangShan/XiangShan/pull/4122)）

### 访存与缓存

- RVA23 Profile

- Bug 修复
  - 修复一系列 SnpOnce*/SnpStash* 相关的嵌套 bug ([CoupledL2 #306](https://github.com/OpenXiangShan/CoupledL2/pull/306))、([CoupledL2 #308](https://github.com/OpenXiangShan/CoupledL2/pull/308))、([CoupledL2 #309](https://github.com/OpenXiangShan/CoupledL2/pull/309))
  - 修复 MCP2 打开的情况下，替换算法 retry 信号没有维持 2 拍的 bug ([CoupledL2 #303](https://github.com/OpenXiangShan/CoupledL2/pull/303))

- 预取
  - BOP 添加物理内存范围检查 ([#4115](https://github.com/OpenXiangShan/XiangShan/pull/4115))

- PPA 优化
  - 删除 MainPipe 中重复信号 ([#4117](https://github.com/OpenXiangShan/XiangShan/pull/4117))
  - 减少 LoadQueueReplay 项数，面积减小 2.85%，功耗降低 1.59% ([#4082](https://github.com/OpenXiangShan/XiangShan/pull/4082))

- 工具
  - OpenLLC 支持 Top-Down ([#4113](https://github.com/OpenXiangShan/XiangShan/pull/4113))


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **12 月 06 日 a60d667 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.10  | 410.bwaves        | 67.07  |
| 401.bzip2         | 25.53  | 416.gamess        | 42.95  |
| 403.gcc           | 47.17  | 433.milc          | 45.29  |
| 429.mcf           | 58.86  | 434.zeusmp        | 56.75  |
| 445.gobmk         | 30.30  | 435.gromacs       | 37.44  |
| 456.hmmer         | 40.79  | 436.cactusADM     | 49.30  |
| 458.sjeng         | 30.22  | 437.leslie3d      | 45.29  |
| 462.libquantum    | 124.56 | 444.namd          | 34.65  |
| 464.h264ref       | 57.72  | 447.dealII        | 74.37  |
| 471.omnetpp       | 40.11  | 450.soplex        | 54.63  |
| 473.astar         | 29.14  | 453.povray        | 54.95  |
| 483.xalancbmk     | 73.25  | 454.Calculix      | 18.33  |
| **GEOMEAN**       | 44.61  | 459.GemsFDTD      | 40.22  |
|                   |        | 465.tonto         | 37.99  |
|                   |        | 470.lbm           | 102.47 |
|                   |        | 481.wrf           | 43.22  |
|                   |        | 482.sphinx3       | 53.26  |
|                   |        | **GEOMEAN**       | 47.48  |

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
