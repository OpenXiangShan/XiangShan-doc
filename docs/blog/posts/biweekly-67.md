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
  - 完成 Svnapot（支持 2 的幂次大小页的地址翻译）扩展的实现并合入主线 ([#4107](https://github.com/OpenXiangShan/XiangShan/pull/4107))

- Bug 修复
  - 修复 UncacheBuffer 有空项时仍无法入队导致卡死的 bug ([#4096](https://github.com/OpenXiangShan/XiangShan/pull/4096))
  - 修复内存返回数据与异常检查错拍导致误报 guest page fault 的 bug ([#4090](https://github.com/OpenXiangShan/XiangShan/pull/4090))
  - 修复若干向量有关的 bug，主要包括非对齐、异常处理和部分边界条件等 ([#4084](https://github.com/OpenXiangShan/XiangShan/pull/4084))、([#4085](https://github.com/OpenXiangShan/XiangShan/pull/4085))、([#4086](https://github.com/OpenXiangShan/XiangShan/pull/4086))、([#4101](https://github.com/OpenXiangShan/XiangShan/pull/4101))、([#4103](https://github.com/OpenXiangShan/XiangShan/pull/4103))
  - 修复 LoadUnit 中，因 fast replay 导致的死锁问题 ([#4102](https://github.com/OpenXiangShan/XiangShan/pull/4102))
  - 修复一系列 SnpOnce*/SnpStash* 相关的嵌套 bug ([CoupledL2 #306](https://github.com/OpenXiangShan/CoupledL2/pull/306))、([CoupledL2 #308](https://github.com/OpenXiangShan/CoupledL2/pull/308))、([CoupledL2 #309](https://github.com/OpenXiangShan/CoupledL2/pull/309))
  - 修复 MCP2 打开的情况下，替换算法 retry 信号没有维持 2 拍的 bug ([CoupledL2 #303](https://github.com/OpenXiangShan/CoupledL2/pull/303))

- 预取
  - 修复 VBOP 预取访问 TLB 时 PMP / PMA 检查的连线错误 ([CoupledL2 #312](https://github.com/OpenXiangShan/CoupledL2/pull/312))

- PPA 优化
  - 删除 MainPipe 中重复信号 ([#4117](https://github.com/OpenXiangShan/XiangShan/pull/4117))
  - 减少 LoadQueueReplay 项数，面积减小 2.85%，功耗降低 1.59% ([#4082](https://github.com/OpenXiangShan/XiangShan/pull/4082))

- 工具
  - OpenLLC 支持 Top-Down 性能分析 ([#4113](https://github.com/OpenXiangShan/XiangShan/pull/4113))


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **1 月 6 日 718a93f 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.70  | 410.bwaves        | 66.96  |
| 401.bzip2         | 25.54  | 416.gamess        | 40.91  |
| 403.gcc           | 46.68  | 433.milc          | 45.37  |
| 429.mcf           | 58.12  | 434.zeusmp        | 52.23  |
| 445.gobmk         | 30.35  | 435.gromacs       | 33.70  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.19  |
| 458.sjeng         | 30.38  | 437.leslie3d      | 46.16  |
| 462.libquantum    | 122.52 | 444.namd          | 28.91  |
| 464.h264ref       | 56.63  | 447.dealII        | 73.40  |
| 471.omnetpp       | 39.51  | 450.soplex        | 52.24  |
| 473.astar         | 29.23  | 453.povray        | 53.39  |
| 483.xalancbmk     | 72.11  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.15  | 459.GemsFDTD      | 36.94  |
|                   |        | 465.tonto         | 36.71  |
|                   |        | 470.lbm           | 91.19  |
|                   |        | 481.wrf           | 40.63  |
|                   |        | 482.sphinx3       | 48.59  |
|                   |        | **GEOMEAN**       | 44.62  |

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
