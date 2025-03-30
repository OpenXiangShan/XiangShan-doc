---
slug: biweekly-73
date: 2025-03-31
categories:
  - Biweekly
---

# 【香山双周报 73】20250331 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 73 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。

此外，我们还公开了 《香山开源处理器用户手册》 的仓库： https://github.com/OpenXiangShan/XiangShan-User-Guide 和对应网页： https://docs.xiangshan.cc/projects/user-guide/ ，以及 《香山开源处理器设计文档》 的仓库： https://github.com/OpenXiangShan/XiangShan-Design-Doc 和对应网页： https://docs.xiangshan.cc/projects/design/ ，欢迎大家阅读和提问。

<!-- more -->

## 近期进展

### 前端

- Bug 修复

### 后端流水线

- Bug 修复
  - 修复 trigger 触发以及异常产生时，指令融合未被停止的问题 ([#4439](https://github.com/OpenXiangShan/XiangShan/pull/4439))
  - 进一步修复 amocas.q 指令卡死的问题 ([#4435](https://github.com/OpenXiangShan/XiangShan/pull/4435))
  - 修复指令融合译码单元在被无效时，仍然输出有效融合信息的问题 ([#4456](https://github.com/OpenXiangShan/XiangShan/pull/4456))
  - 修复 reset 后，non-reg 中断等待 difftest 框架同步错误的问题 ([#4449](https://github.com/OpenXiangShan/XiangShan/pull/4449))
  - 修复 chiselAIA 系列问题 ([#4449](https://github.com/OpenXiangShan/XiangShan/pull/4449))


### 访存与缓存

- RVA23 Profile
  

- Bug 修复
  - 修复若干 CoupledL2 违背 CHI 协议的一致性问题 ([CoupledL2 #390](https://github.com/OpenXiangShan/CoupledL2/pull/390))、([CoupledL2 #392](https://github.com/OpenXiangShan/CoupledL2/pull/392))、([CoupledL2 #395](https://github.com/OpenXiangShan/CoupledL2/pull/395))
  - 添加 L2 Cache 退出维护一致性状态前对 WFI(Wait For Interrupt) 状态的检查 ([CoupledL2 #385](https://github.com/OpenXiangShan/CoupledL2/pull/385))
  - 修复若干 CHI 协议中 RespErr 字段处理的相关问题 ([CoupledL2 #384](https://github.com/OpenXiangShan/CoupledL2/pull/384))、([CoupledL2 #394](https://github.com/OpenXiangShan/CoupledL2/pull/394))
  
- 时序/面积优化
  - 调整 L2 Cache SRAM(tag) 规格 ([CoupledL2 #388](https://github.com/OpenXiangShan/CoupledL2/pull/388))；添加 SRAM 控制接口 ([CoupledL2 #389](https://github.com/OpenXiangShan/CoupledL2/pull/389))

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **3 月 14 日 9245b52 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

**注：本次双周报的性能评估代码版本与上次双周报相同，将会在下次双周报时更新最新分数。**

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 66.89  |
| 401.bzip2         | 25.50  | 416.gamess        | 40.89  |
| 403.gcc           | 46.72  | 433.milc          | 45.25  |
| 429.mcf           | 58.13  | 434.zeusmp        | 52.10  |
| 445.gobmk         | 30.26  | 435.gromacs       | 33.65  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.16  |
| 458.sjeng         | 30.53  | 437.leslie3d      | 46.01  |
| 462.libquantum    | 122.50 | 444.namd          | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII        | 73.43  |
| 471.omnetpp       | 39.37  | 450.soplex        | 51.99  |
| 473.astar         | 29.23  | 453.povray        | 53.44  |
| 483.xalancbmk     | 72.03  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.15  | 459.GemsFDTD      | 37.18  |
|                   |        | 465.tonto         | 36.67  |
|                   |        | 470.lbm           | 91.24  |
|                   |        | 481.wrf           | 40.62  |
|                   |        | 482.sphinx3       | 48.57  |
|                   |        | **GEOMEAN**       | 44.60  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/
* 香山用户手册：https://docs.xiangshan.cc/projects/user-guide/
* 香山设计文档：https://docs.xiangshan.cc/projects/design/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
