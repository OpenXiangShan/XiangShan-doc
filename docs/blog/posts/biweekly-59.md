---
slug: biweekly-59
date: 2024-09-16
categories:
  - Biweekly
---
# 【香山双周报 59】20240916 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 59 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，

<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - template ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

### 后端流水线

- Bug 修复
    - 持续推进功能 Bug 修复，共修复 30 余例，以下是部分 PR：
    - 修复 H 拓展功能 Bug ([#3580](https://github.com/OpenXiangShan/XiangShan/pull/3580), [#3575](https://github.com/OpenXiangShan/XiangShan/pull/3575), [#3569](https://github.com/OpenXiangShan/XiangShan/pull/3569), [#3561](https://github.com/OpenXiangShan/XiangShan/pull/3561), [#3553](https://github.com/OpenXiangShan/XiangShan/pull/3553), [#3551](https://github.com/OpenXiangShan/XiangShan/pull/3551), [#3528](https://github.com/OpenXiangShan/XiangShan/pull/3528), [#3525](https://github.com/OpenXiangShan/XiangShan/pull/3525), [#3524](https://github.com/OpenXiangShan/XiangShan/pull/3524), [#3523](https://github.com/OpenXiangShan/XiangShan/pull/3523), [#3512](https://github.com/OpenXiangShan/XiangShan/pull/3512), [#3510](https://github.com/OpenXiangShan/XiangShan/pull/3510), [#3502](https://github.com/OpenXiangShan/XiangShan/pull/3502))
    - 修复特权级功能 Bug ([#3558](https://github.com/OpenXiangShan/XiangShan/pull/3558), [#3557](https://github.com/OpenXiangShan/XiangShan/pull/3557), [#3534](https://github.com/OpenXiangShan/XiangShan/pull/3534), [#3515](https://github.com/OpenXiangShan/XiangShan/pull/3515), [#3496](https://github.com/OpenXiangShan/XiangShan/pull/3496), [#3486](https://github.com/OpenXiangShan/XiangShan/pull/3486), [#3469](https://github.com/OpenXiangShan/XiangShan/pull/3469), [#3434](https://github.com/OpenXiangShan/XiangShan/pull/3434),
    [#3547](https://github.com/OpenXiangShan/XiangShan/pull/3547))
    - 修复 Debug 拓展功能 Bug ([#3538](https://github.com/OpenXiangShan/XiangShan/pull/3538), [#3536](https://github.com/OpenXiangShan/XiangShan/pull/3536), [#3472](https://github.com/OpenXiangShan/XiangShan/pull/3472))
    - 修复 V 拓展功能 Bug ([#3535](https://github.com/OpenXiangShan/XiangShan/pull/3535), [#3495](https://github.com/OpenXiangShan/XiangShan/pull/3495), [#3494](https://github.com/OpenXiangShan/XiangShan/pull/3494))

- 时序优化
    - 向量访存添加 OG2 ([#3482](https://github.com/OpenXiangShan/XiangShan/pull/3482))
    - 优化 Rab 状态机转移至 idle 逻辑 ([#3517](https://github.com/OpenXiangShan/XiangShan/pull/3517))
    - 增加加法器以优化分支计算模块计算 target 时序，删除冗余判断逻辑 ([#3520](https://github.com/OpenXiangShan/XiangShan/pull/3520))
    - 将访存 issue queue 入队数从 2 降为 1, 缓解时序压力 ([#3471](https://github.com/OpenXiangShan/XiangShan/pull/3471))

- RVA23 Profile
    - 支持可恢复非屏蔽中断 (Smrnmi) 拓展 ([#3480](https://github.com/OpenXiangShan/XiangShan/pull/3480))
    - 添加 CMO 指令拓展（Zicbom,Zicboz）拓展权限检查及 CSR 相关支持 ([#3559](https://github.com/OpenXiangShan/XiangShan/pull/3559))
    - 支持加载常数和特殊偏序比较拓展 (Zfa)([#3439](https://github.com/OpenXiangShan/XiangShan/pull/3439))

### 访存与缓存

- CHI 总线
    - 完成 CHI2AXI 转接桥设计（OpenNCB），搭建 CoupledL2-OpenLLC-OpenNCB 测试框架
    - 添加 non-data error 的处理流程，访问不存在外设时将返回 DECERR ([#3458](https://github.com/OpenXiangShan/XiangShan/pull/3458))

- RVA23 Profile
    - 完成 CMO 扩展对 CSR 的修改要求与指令异常条件的整理，NEMU 上实现相关的 CSR 寄存器与指令异常检查
    - 完成 svpbmt 扩展使能信号 PBMTE 的代码实现 ([#3521](https://github.com/OpenXiangShan/XiangShan/pull/3521))

- 性能
    - TP meta on L2：相关代码完成到较新 master 的迁移，出现 TP 预取数量大幅下降现象，修复中
    - CI 新增性能回归测试，会在每周五自动测试 SPEC06 的性能分数 ([#3533](https://github.com/OpenXiangShan/XiangShan/pull/3533))

- Bug 修复
    - TP 修复 hardcoding 问题，实现对 sv48 的正确支持 ([#3487](https://github.com/OpenXiangShan/XiangShan/commit/e1d5ffc2d93873b72146e78c8f6a904926de8590))
    - 修复 L2 Cache 中 mergeA 导致预取不及时的性能 bug（待性能评估）
    - 修复 PCredit 仲裁相关，导致 PCredit 丢失或重复分发的 bug ([#3513](https://github.com/OpenXiangShan/XiangShan/pull/3513)、[#3552](https://github.com/OpenXiangShan/XiangShan/pull/3552))
    - 修复 L2TLB 返回的异常处理生成和仲裁逻辑 ([#3453](https://github.com/OpenXiangShan/XiangShan/pull/3453)、[#3588](https://github.com/OpenXiangShan/XiangShan/pull/3588))


- 时序 & 面积优化
    - 时序：完成对 L2 Cache tagArray 的拆分，L2 Cache 模块内部关键路径时序优化至 -40ps
    - 面积：整理、裁剪 MemBlock 中的冗余信号，主要包括 exceptionVec 和 fuType 等 ([#3560](https://github.com/OpenXiangShan/XiangShan/pull/3560))

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **9 月 5 日 42b6cdf 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.84  | 410.bwaves        | 77.28  |
| 401.bzip2         | 25.52  | 416.gamess        | 43.52  |
| 403.gcc           | 48.49  | 433.milc          | 42.48  |
| 429.mcf           | 58.95  | 434.zeusmp        | 56.99  |
| 445.gobmk         | 30.20  | 435.gromacs       | 37.38  |
| 456.hmmer         | 41.30  | 436.cactusADM     | 48.45  |
| 458.sjeng         | 30.12  | 437.leslie3d      | 43.67  |
| 462.libquantum    | 127.52 | 444.namd          | 34.30  |
| 464.h264ref       | 57.81  | 447.dealII        | 74.82  |
| 471.omnetpp       | 41.79  | 450.soplex        | 54.49  |
| 473.astar         | 29.17  | 453.povray        | 55.61  |
| 483.xalancbmk     | 75.84  | 454.Calculix      | 18.21  |
| **GEOMEAN**       | 45.09  | 459.GemsFDTD      | 37.24  |
|                   |        | 465.tonto         | 36.21  |
|                   |        | 470.lbm           | 101.29 |
|                   |        | 481.wrf           | 43.52  |
|                   |        | 482.sphinx3       | 51.32  |
|                   |        | **GEOMEAN**       | 47.12  |

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
