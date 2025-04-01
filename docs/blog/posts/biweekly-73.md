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
  - 修复指令预取流水线对于高位地址异常的处理 ([#4423](https://github.com/OpenXiangShan/XiangShan/pull/4423))

- 时序/面积优化
  - 一系列 SRAM 拆分 ([#4468](https://github.com/OpenXiangShan/XiangShan/pull/4468)) 、 ([#4360](https://github.com/OpenXiangShan/XiangShan/pull/4360))、 ([#4485](https://github.com/OpenXiangShan/XiangShan/pull/4485))

### 后端流水线

- Bug 修复
  - 修复 trigger 触发以及异常产生时，指令融合未被停止的问题 ([#4439](https://github.com/OpenXiangShan/XiangShan/pull/4439))
  - 进一步修复 amocas.q 指令卡死的问题 ([#4435](https://github.com/OpenXiangShan/XiangShan/pull/4435))
  - 修复指令融合译码单元在被无效时，仍然输出有效融合信息的问题 ([#4456](https://github.com/OpenXiangShan/XiangShan/pull/4456))
  - 修复 reset 后，non-reg 中断等待 difftest 框架同步错误的问题 ([#4449](https://github.com/OpenXiangShan/XiangShan/pull/4449))
  - 修复 chiselAIA 系列问题 ([#4449](https://github.com/OpenXiangShan/XiangShan/pull/4449))


### 访存与缓存

- Bug 修复
  - 修复 MMU 中，与高位地址检查、异常处理、Svnapot 扩展相关的一系列问题 ([#4422](https://github.com/OpenXiangShan/XiangShan/pull/4422))、([#4448](https://github.com/OpenXiangShan/XiangShan/pull/4448))、([#4453](https://github.com/OpenXiangShan/XiangShan/pull/4453))、([#4454](https://github.com/OpenXiangShan/XiangShan/pull/4454))、([#4455](https://github.com/OpenXiangShan/XiangShan/pull/4455))、([#4471](https://github.com/OpenXiangShan/XiangShan/pull/4471))、([#4472](https://github.com/OpenXiangShan/XiangShan/pull/4472))、([#4473](https://github.com/OpenXiangShan/XiangShan/pull/4473))
  - 修复 NEMU 作为多核 ref 时，开启虚拟化场景下的 bug ([NEMU #835](https://github.com/OpenXiangShan/NEMU/pull/835))
  - 修复若干 Uncache、非对齐、异常混合场景的 bug ([#4426](https://github.com/OpenXiangShan/XiangShan/pull/4426))、([#4441](https://github.com/OpenXiangShan/XiangShan/pull/4441))、([#4442](https://github.com/OpenXiangShan/XiangShan/pull/4442))
  - 修复 NEMU 在 PBMT 将内存属性由 cacheable 覆盖为 IO/NC 时，原子指令和非对齐访存没有报异常的 bug ([NEMU #833](https://github.com/OpenXiangShan/NEMU/pull/833))
  - 修复若干 CoupledL2 违背 CHI 协议的一致性问题 ([CoupledL2 #390](https://github.com/OpenXiangShan/CoupledL2/pull/390))、([CoupledL2 #392](https://github.com/OpenXiangShan/CoupledL2/pull/392))、([CoupledL2 #395](https://github.com/OpenXiangShan/CoupledL2/pull/395))
  - 添加 L2 Cache 退出维护一致性状态前对 WFI(Wait For Interrupt) 状态的检查 ([CoupledL2 #385](https://github.com/OpenXiangShan/CoupledL2/pull/385))
  - 修复若干 CHI 协议中 RespErr 字段处理的相关问题 ([CoupledL2 #384](https://github.com/OpenXiangShan/CoupledL2/pull/384))、([CoupledL2 #394](https://github.com/OpenXiangShan/CoupledL2/pull/394))

- 时序/面积优化
  - 调整 L2 Cache SRAM(tag) 规格 ([CoupledL2 #388](https://github.com/OpenXiangShan/CoupledL2/pull/388))；添加 SRAM 控制接口 ([CoupledL2 #389](https://github.com/OpenXiangShan/CoupledL2/pull/389))

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **3 月 28 日 0e64db5 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

**注：本次双周报的性能评估代码版本与上次双周报相同，将会在下次双周报时更新最新分数。**

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.85  | 410.bwaves        | 66.93  |
| 401.bzip2         | 25.49  | 416.gamess        | 40.90  |
| 403.gcc           | 46.64  | 433.milc          | 45.30  |
| 429.mcf           | 58.07  | 434.zeusmp        | 51.77  |
| 445.gobmk         | 30.25  | 435.gromacs       | 33.65  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.21  |
| 458.sjeng         | 30.39  | 437.leslie3d      | 45.99  |
| 462.libquantum    | 122.51 | 444.namd          | 28.88  |
| 464.h264ref       | 56.56  | 447.dealII        | 73.41  |
| 471.omnetpp       | 39.51  | 450.soplex        | 51.98  |
| 473.astar         | 29.22  | 453.povray        | 53.43  |
| 483.xalancbmk     | 71.97  | 454.Calculix      | 16.37  |
| **GEOMEAN**       | 44.13  | 459.GemsFDTD      | 36.38  |
|                   |        | 465.tonto         | 36.72  |
|                   |        | 470.lbm           | 91.22  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 48.59  |
|                   |        | **GEOMEAN**       | 44.53  |

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
