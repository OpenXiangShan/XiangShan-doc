---
slug: biweekly-60
date: 2024-09-30
categories:
  - Biweekly
---
# 【香山双周报 60】20240930 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 60 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端修复了 FTB 多路命中的处理，后端支持了虚拟中断注入，访存和缓存部分添加向量 vstart、trigger 的支持。本期还更新了昆明湖架构近期性能。

<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 适配 write addr 和 read addr 不允许相同的双端口 SRAM ([#3671](https://github.com/OpenXiangShan/XiangShan/pull/3671), [#3606](https://github.com/OpenXiangShan/XiangShan/pull/3606))
    - 删除 reset_vector 打拍，保证为异步复位 ([#3669](https://github.com/OpenXiangShan/XiangShan/pull/3669))
    - 修复 FTB 多路命中的处理 ([#3641](https://github.com/OpenXiangShan/XiangShan/pull/3641))
    - 修复 BPU s3 级对 fallThroughErr 的处理 ([#3636](https://github.com/OpenXiangShan/XiangShan/pull/3636))
    - 修复 BPU 在 FTB 未命中时的全局历史维护 ([#3635](https://github.com/OpenXiangShan/XiangShan/pull/3635))


### 后端流水线

- Bug 修复
    - 持续推进功能 Bug 修复，共修复 30 余例，以下是部分 PR：
    - 修复 H 拓展功能 Bug: ([#3685](https://github.com/OpenXiangShan/XiangShan/pull/3685), [#3660](https://github.com/OpenXiangShan/XiangShan/pull/3660), [#3657](https://github.com/OpenXiangShan/XiangShan/pull/3657), [#3624](https://github.com/OpenXiangShan/XiangShan/pull/3624), [#3580](https://github.com/OpenXiangShan/XiangShan/pull/3580), [#3575](https://github.com/OpenXiangShan/XiangShan/pull/3575), [#3569](https://github.com/OpenXiangShan/XiangShan/pull/3569), [#3561](https://github.com/OpenXiangShan/XiangShan/pull/3561), [#3553](https://github.com/OpenXiangShan/XiangShan/pull/3553))
    - 修复特权级功能 Bug: ([#3634](https://github.com/OpenXiangShan/XiangShan/pull/3634), [#3620](https://github.com/OpenXiangShan/XiangShan/pull/3620), [#3647](https://github.com/OpenXiangShan/XiangShan/pull/3647), [#3665](https://github.com/OpenXiangShan/XiangShan/pull/3665), [#3644](https://github.com/OpenXiangShan/XiangShan/pull/3644), [#3640](https://github.com/OpenXiangShan/XiangShan/pull/3640), [#3577](https://github.com/OpenXiangShan/XiangShan/pull/3577), [#3557](https://github.com/OpenXiangShan/XiangShan/pull/3557), [#3534](https://github.com/OpenXiangShan/XiangShan/pull/3534))
    - 修复 V 拓展功能 Bug: ([#3664](https://github.com/OpenXiangShan/XiangShan/pull/3664), [#3658](https://github.com/OpenXiangShan/XiangShan/pull/3658), [#3643](https://github.com/OpenXiangShan/XiangShan/pull/3643), [#3607](https://github.com/OpenXiangShan/XiangShan/pull/3607))
    - 修复 Debug 拓展功能 Bug：([#3585](https://github.com/OpenXiangShan/XiangShan/pull/3585), [#3683](https://github.com/OpenXiangShan/XiangShan/pull/3683))
    - 修复 AIA 拓展功能 Bug: ([#3612](https://github.com/OpenXiangShan/XiangShan/pull/3612), [#3547](https://github.com/OpenXiangShan/XiangShan/pull/3547))
    - 修复核内异步复位和接 X 态的 Bug：([#3669](https://github.com/OpenXiangShan/XiangShan/pull/3669), [#3668](https://github.com/OpenXiangShan/XiangShan/pull/3668), [#3667](https://github.com/OpenXiangShan/XiangShan/pull/3667))

- 时序/功耗优化
    - 持续推进时序功耗优化，目前后端模块内最大违例 -40ps, 跨模块端口违例 -70ps, 门控率 97.34%
    - 优化 load/store queue allocNumber 逻辑，由加法器实现改为 7 选 1 逻辑 ([#3531](https://github.com/OpenXiangShan/XiangShan/pull/3531))
    - 添加 IQ 和 rob 部分寄存器门控 ([#3602](https://github.com/OpenXiangShan/XiangShan/pull/3602), [#3583](https://github.com/OpenXiangShan/XiangShan/pull/3583))

- RVA23 Profile
    - H 拓展支持在 Guest-Page-Fault 时更新 mtinst/htinst ([#3604](https://github.com/OpenXiangShan/XiangShan/pull/3604))
    - 支持虚拟中断注入 ([#3496](https://github.com/OpenXiangShan/XiangShan/pull/3496))

### 访存与缓存

- CHI 总线
  - 完成 CHI2AXI 转接桥 OpenNCB 实现
  - 成功进行 CHI-SoC 集成测试，相关代码正在合入主线；测试发现大幅性能下降问题（相较 T L 版本），正在定位原因

- RVA23 Profile
  - 缓存操作指令扩展（Zicboz / Zicbom）修复若干 CSR 与非法指令检查问题，使其满足手册要求
  - 编写并进行 CBO.INVAL 指令功能测试
  - 添加向量 vstart、trigger 的支持，完善向量访存 fault-only-first 指令的实现 ([#3690](https://github.com/OpenXiangShan/XiangShan/pull/3690))

- 性能
  - TP：完成 TP 迭代优化设计
  - Store：基于 memset pattern 做性能优化，主要包括提高 sbuffer 利用率以及实现基于 SPB 的预取器 ([#3632](https://github.com/OpenXiangShan/XiangShan/pull/3632))

- Bug 修复
  - 修复 CoupledL2 DCT 中 meta clients 更新问题 ([#3648](https://github.com/OpenXiangShan/XiangShan/pull/3648))
  - 修复一系列 CoupledL2 中与仲裁和请求嵌套相关的 Bug ([#3621](https://github.com/OpenXiangShan/XiangShan/pull/3621)), ([#3637](https://github.com/OpenXiangShan/XiangShan/pull/3637))
  - 修复高位地址截断导致的异常判断错误问题、修复异常地址未被正确写入 *tval 寄存器的 Bug ([#3629](https://github.com/OpenXiangShan/XiangShan/pull/3629)), ([#3639](https://github.com/OpenXiangShan/XiangShan/pull/3639)), ([#3674](https://github.com/OpenXiangShan/XiangShan/pull/3674))

- 时序 & 面积优化
  - MemBlock 时序：优化 Dcache TagArray 相关的关键路径
  - CHI-CoupledL2 时序：优化 PCredit 的管理和仲裁逻辑
  - RVA23 时序：修复由 CMO 扩展引入的 MemBlock 与 L2 间端口时序问题，相关代码正在合入主线
  - L2 MCP2 约束：检查所有相关信号并修复了若干违例情况 ([#3633](https://github.com/OpenXiangShan/XiangShan/pull/3633))

- 工具
  - 成功搭建 TL-Test-new + NoC 测试框架
  - 添加 CHI 版本 HPM 性能计数器，重构、更新 HPM 代码 ([#3631](https://github.com/OpenXiangShan/XiangShan/pull/3631))


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
