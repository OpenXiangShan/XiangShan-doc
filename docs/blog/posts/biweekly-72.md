---
slug: biweekly-72
date: 2025-03-17
categories:
  - Biweekly
---

# 【香山双周报 72】20250317 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 72 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - IFU 修复 uncache 区域总线返回 corrupt 的处理 ([#4301](https://github.com/OpenXiangShan/XiangShan/pull/4301))

### 后端流水线

- Bug 修复
    - 修复复位时 CSR difftest 框架错误比对的问题 ([#4419](https://github.com/OpenXiangShan/XiangShan/pull/4419))
    - 修复 CSR 读指令访问 xireg 时未按序处理的问题 ([#4393](https://github.com/OpenXiangShan/XiangShan/pull/4393))
    - 修复 JumpUnit 中高位地址截断异常产生时未正常发出重定向信号的问题 ([#4392](https://github.com/OpenXiangShan/XiangShan/pull/4392))
    - 特定场景下同步释放 JTAG 的 reset 信号 ([#4414](https://github.com/OpenXiangShan/XiangShan/pull/4414))
    - 修复 Trigger 中，在特定匹配模式下 pc 与 tdat2 匹配出错的问题 ([#4346](https://github.com/OpenXiangShan/XiangShan/pull/4346))
    - 修复 AMOCAS 指令重命名出错导致卡死的问题 ([#4382](https://github.com/OpenXiangShan/XiangShan/pull/4382))
    - 修复 CSR 读指令访问 Vtype 时未按序处理的问题 ([#4354](https://github.com/OpenXiangShan/XiangShan/pull/4354))


- 时序/面积优化
    - 去除只读 CSR 寄存器输出作为写数据输入驱动的冗余逻辑 ([#4412](https://github.com/OpenXiangShan/XiangShan/pull/4412))

- RVA23 Profile
    - 集成新版 ChiselAIA(高级中断架构) 并合入主线 ([#4378](https://github.com/OpenXiangShan/XiangShan/pull/4378))

### 访存与缓存

- RVA23 Profile
  - 添加了 L2 Cache 刷新操作 ([CoupledL2 #348](https://github.com/OpenXiangShan/CoupledL2/pull/348))

- Bug 修复
    - 修复非对齐访存在违例检测和写回唤醒上有关的一系列问题 ([#4333](https://github.com/OpenXiangShan/XiangShan/pull/4333))、([#4359](https://github.com/OpenXiangShan/XiangShan/pull/4359))、([#4369](https://github.com/OpenXiangShan/XiangShan/pull/4369))、([#4426](https://github.com/OpenXiangShan/XiangShan/pull/4426))
    - 修复多核场景下，difftest 不支持向量 load 指令结果检查的 bug ([#4361](https://github.com/OpenXiangShan/XiangShan/pull/4361))
    - 修复预取请求错误进入 load RAR queue 导致的功能和性能 bug ([#4367](https://github.com/OpenXiangShan/XiangShan/pull/4367))
    - 修复 Dcache 发生 ECC 或 data error 时的处理逻辑 ([#4345](https://github.com/OpenXiangShan/XiangShan/pull/4345))、([#4394](https://github.com/OpenXiangShan/XiangShan/pull/4394))
    - 修复多种虚实地址转换模式混杂导致的例外地址错误的 bug ([#4349](https://github.com/OpenXiangShan/XiangShan/pull/4349))
    - 修复 MMU 中，与 TLB 压缩、地址截断、异常处理相关的一系列问题 ([#4396](https://github.com/OpenXiangShan/XiangShan/pull/4396))、([#4404](https://github.com/OpenXiangShan/XiangShan/pull/4404))、([#4406](https://github.com/OpenXiangShan/XiangShan/pull/4406))、([#4407](https://github.com/OpenXiangShan/XiangShan/pull/4407))
    - 修复 L2 Cache 中与 CMO 事务相关 bug ([CoupledL2 #382](https://github.com/OpenXiangShan/CoupledL2/pull/382))、([CoupledL2 #378](https://github.com/OpenXiangShan/CoupledL2/pull/378))
    - 修复 L2 Cache 出现嵌套事务时，目录命中/缺失相关逻辑；对于 ProbeAck/ProbeAckData 事务，更新 MSHR 中状态 ([CoupledL2 #374](https://github.com/OpenXiangShan/CoupledL2/pull/382))、([CoupledL2 #377](https://github.com/OpenXiangShan/CoupledL2/pull/378))
  
  

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
