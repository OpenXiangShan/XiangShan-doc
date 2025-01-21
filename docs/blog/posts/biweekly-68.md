---
slug: biweekly-68
date: 2025-01-20
categories:
  - Biweekly
---

# 【香山双周报 68】20250120 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 68 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，后端修复边界条件下，rob 发生重定向时没有成功刷新 rob 表项的问题，访存和缓存修复重压场景下 MissQueue 满导致 MMU 卡死的 Bug。

<!-- more -->

## 近期进展

### 前端

- 功耗
    - 添加双端口 SRAM 两个 clock 分别门控的选项，默认不分别门控 ([#4125](https://github.com/OpenXiangShan/XiangShan/pull/4125))

### 后端流水线

- Bug 修复
    - 修复 xTIP (时钟中断等待位) 更新失败，导致错误产生中断的问题 ([#4157](https://github.com/OpenXiangShan/XiangShan/pull/4157))
    - 修复边界条件下，rob 发生重定向时没有成功刷新 rob 表项的问题 ([#4153](https://github.com/OpenXiangShan/XiangShan/pull/4153))
    - 添加对 htimedelta csr 初始化，以防止软件读取采用未初始化信息造成错误 ([#4145](https://github.com/OpenXiangShan/XiangShan/pull/4145))
    - 修复 mnret 部分输出信号未连线的问题 ([#4194](https://github.com/OpenXiangShan/XiangShan/pull/4194))
    - 添加 AIA 拓展遗漏的权限检查 ([#4166](https://github.com/OpenXiangShan/XiangShan/pull/4166))
    - 整理对 CSR 的访问异常，分类为多个模块共同完成 ([#4146](https://github.com/OpenXiangShan/XiangShan/pull/4146))
    - 修复重定向时快照选择在极端情况出错的问题 ([#4197](https://github.com/OpenXiangShan/XiangShan/pull/4197))
    - 修复 unorder reduction 指令掩码错误问题 ([#4197](https://github.com/OpenXiangShan/XiangShan/pull/4197))
    - 修复 reduction 指令 f16 数据选择错误问题 ([#4181](https://github.com/OpenXiangShan/XiangShan/pull/4181))

- Debug Module
    - 新增 hartReset 功能，在多核调试下，允许重启指定核 ([#4134](https://github.com/OpenXiangShan/XiangShan/pull/4134))

- 工具
    - 支持硬件可综合的三级分类 Top-Down 计数器 ([#4122](https://github.com/OpenXiangShan/XiangShan/pull/4122))
    - 添加 mcorepwr/mflushpwr 两个自定义 CSR 寄存器以控制功耗 ([#4164](https://github.com/OpenXiangShan/XiangShan/pull/4164))

### 访存与缓存

- 功能
    - 添加对 uncache buffer 支持新请求合并的功能 ([#4154](https://github.com/OpenXiangShan/XiangShan/pull/4154))

- CHI 总线
    - 添加对 Issue E.b 中新增 Snoop 事务 SnpQuery 的支持 ([CoupledL2 #323](https://github.com/OpenXiangShan/CoupledL2/pull/323))
    - 添加对不同 CHI 版本的代码隔离 ([CoupledL2 #333](https://github.com/OpenXiangShan/CoupledL2/pull/333))、([CoupledL2 #315](https://github.com/OpenXiangShan/CoupledL2/pull/315))
    - 添加 DataCheck 与 Poison 对于 UC 情况的支持，并修正其初始化选项 ([CoupledL2 #329](https://github.com/OpenXiangShan/CoupledL2/pull/329))、([CoupledL2 #335](https://github.com/OpenXiangShan/CoupledL2/pull/335))、([CoupledL2 #337](https://github.com/OpenXiangShan/CoupledL2/pull/337))

- 预取
    - 添加 L2 Cache 预取的 CSR 寄存器控制 ([CoupledL2 #324](https://github.com/OpenXiangShan/CoupledL2/pull/324))


- Bug 修复
    - 修复 PageCache 和 itlbRepeater 中 X 态传播的两处 Bug ([#4174](https://github.com/OpenXiangShan/XiangShan/pull/4174))、([#4195](https://github.com/OpenXiangShan/XiangShan/pull/4195))
    - 修复重压场景下 MissQueue 满导致 MMU 卡死的 Bug ([#4191](https://github.com/OpenXiangShan/XiangShan/pull/4191))、([#4202](https://github.com/OpenXiangShan/XiangShan/pull/4202))
    - 修复 StoreQueue 中，向量 store 没有被 flush 的 Bug ([#4139](https://github.com/OpenXiangShan/XiangShan/pull/4139))
    - 修复 SnpStash 在特定情况下未 probe L1 的错误问题 ([CoupledL2 #326](https://github.com/OpenXiangShan/CoupledL2/pull/326))
    - 修复一系列 WriteEvictOrEvict 相关错误 ([CoupledL2 #311](https://github.com/OpenXiangShan/CoupledL2/pull/311))、([CoupledL2 #316](https://github.com/OpenXiangShan/CoupledL2/pull/316))、([CoupledL2 #327](https://github.com/OpenXiangShan/CoupledL2/pull/327))
    - 修复一系列 CMO 相关错误 ([CoupledL2 #317](https://github.com/OpenXiangShan/CoupledL2/pull/317))、([CoupledL2 #325](https://github.com/OpenXiangShan/CoupledL2/pull/325))
    - 修复 CCID 错误赋值问题 ([CoupledL2 #330](https://github.com/OpenXiangShan/CoupledL2/pull/330))

- PPA 优化
    - 时序
        - Load Unit 中部分关键信号改为由寄存器直出 ([#4144](https://github.com/OpenXiangShan/XiangShan/pull/4144))
        - 优化 Load Unit 写回数据生成逻辑 ([#4167](https://github.com/OpenXiangShan/XiangShan/pull/4167))
        - 优化 L2 Cache 中 SRAM 出口到寄存器门控信号的关键路径 ([CoupledL2 #321](https://github.com/OpenXiangShan/CoupledL2/pull/321))

    - 面积
        - 缩减 LQReplay 项数，在 LQReplay 占用率达到一定阈值时让 IQ 发射最老的 load ([#4183](https://github.com/OpenXiangShan/XiangShan/pull/4183))

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **1 月 6 日 718a93f 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

注：本次双周报的性能评估代码版本与上次双周报相同，将会在 2 月 3 日发布下次双周报时更新最新分数。

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

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组