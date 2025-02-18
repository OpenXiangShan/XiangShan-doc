---
slug: biweekly-70
date: 2025-02-17
categories:
  - Biweekly
---

# 【香山双周报 70】20250217 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 70 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端修复重定向时 RAS 判断 Call/Ret 的条件问题，后端修复向量无序规约求和中 fflags 标志位生成出错的问题，访存和缓存修复与 cbo 指令相关的冲刷、异常处理和违例检查等一系列 Bug。本期还更新了昆明湖架构近期性能。


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复重定向时 RAS 判断 Call/Ret 的条件问题 ([#4232](https://github.com/OpenXiangShan/XiangShan/pull/4232))
    - 预译码增加对 JALR target 的独立检查 ([#4234](https://github.com/OpenXiangShan/XiangShan/pull/4234))
    - 预译码增加对 JALR 位置的检查 ([#4269](https://github.com/OpenXiangShan/XiangShan/pull/4269))

- 时序
    - ICache miss 通路上 MSHR 选择提前 ([#4173](https://github.com/OpenXiangShan/XiangShan/pull/4173))
    - ITTAGE region table 读取提前 ([#4216](https://github.com/OpenXiangShan/XiangShan/pull/4216))
    - 去除一些时序不好的 Clock Gating ([#4223](https://github.com/OpenXiangShan/XiangShan/pull/4223))

### 后端流水线

- Bug 修复
    - 修复部分指令信息在硬件性能计数器丢失的问题 ([#4257](https://github.com/OpenXiangShan/XiangShan/pull/4257))
    - 修复 scountovf 寄存器读取时未受 counteren 控制的问题 ([#4267](https://github.com/OpenXiangShan/XiangShan/pull/4267))
    - 修复写 mcontrol6 寄存器的 dmode 字段时未考虑 chain 的影响 ([#4256](https://github.com/OpenXiangShan/XiangShan/pull/4256))
    - 修复向量无序规约求和中 fflags 标志位生成出错的问题 ([#4244](https://github.com/OpenXiangShan/XiangShan/pull/4244))

- RVA23 Profile
    - 支持低功耗轮询拓展 (zawrs) ([#4211](https://github.com/OpenXiangShan/XiangShan/pull/4211))

### 访存与缓存

- CHI 总线
    - 在 CoupledL2 以及 OpenLLC + OpenNCB 的 SoC 中已经支持 Issue C ([CoupledL2 #333](https://github.com/OpenXiangShan/CoupledL2/pull/333))、([OpenLLC #47](https://github.com/OpenXiangShan/OpenLLC/pull/47))、([OpenNCB #3](https://github.com/OpenXiangShan/OpenNCB/pull/3))

- Bug 修复
    - 修复 Uncache 合并和 load replay 相关的两处 Bug ([#4268](https://github.com/OpenXiangShan/XiangShan/pull/4268))、([#4275](https://github.com/OpenXiangShan/XiangShan/pull/4275))
    - 修复虚拟化 onlyStage1 或 onlyStage2 场景下的 corner case，以及 MMU 的 X 态传播问题 ([#4252](https://github.com/OpenXiangShan/XiangShan/pull/4252))、([#4253](https://github.com/OpenXiangShan/XiangShan/pull/4253))、([#4266](https://github.com/OpenXiangShan/XiangShan/pull/4266))
    - 修复与 cbo 指令相关的冲刷、异常处理和违例检查等一系列 Bug ([#4262](https://github.com/OpenXiangShan/XiangShan/pull/4262))
    - 修复 cas 请求发生 miss 后，未向 MSHR 传递 amo_cmp 的 Bug ([#4272](https://github.com/OpenXiangShan/XiangShan/pull/4272))
    - 修复非对齐访存的异常处理、违例检查和错误唤醒相关的四处 Bug ([#4227](https://github.com/OpenXiangShan/XiangShan/pull/4227))、([#4228](https://github.com/OpenXiangShan/XiangShan/pull/4228))、([#4239](https://github.com/OpenXiangShan/XiangShan/pull/4239))、([#4263](https://github.com/OpenXiangShan/XiangShan/pull/4263))
    - 修复 PMA 配置缺失和预取指令权限检查的两处 Bug ([#4226](https://github.com/OpenXiangShan/XiangShan/pull/4226))、([#4235](https://github.com/OpenXiangShan/XiangShan/pull/4235))
    - 修复 WriteEvictOrEvict 回复状态不符合手册标准的 Bug ([CoupledL2 #352](https://github.com/OpenXiangShan/CoupledL2/pull/352))
    - 修复 SnqQuery 嵌套 Evict 时，SnqQuery 回复状态不符合一致性要求的 Bug ([CoupledL2 #353](https://github.com/OpenXiangShan/CoupledL2/pull/353))
    - 修复一系列 DataCheck、Poison 相关 Bug ([CoupledL2 #335](https://github.com/OpenXiangShan/CoupledL2/pull/335))、([CoupledL2 #337](https://github.com/OpenXiangShan/CoupledL2/pull/337))、([CoupledL2 #339](https://github.com/OpenXiangShan/CoupledL2/pull/339))


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **2 月 14 日 7f475a2 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 66.62  |
| 401.bzip2         | 25.55  | 416.gamess        | 40.91  |
| 403.gcc           | 46.67  | 433.milc          | 45.21  |
| 429.mcf           | 58.13  | 434.zeusmp        | 51.96  |
| 445.gobmk         | 30.34  | 435.gromacs       | 33.61  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.26  |
| 458.sjeng         | 30.50  | 437.leslie3d      | 46.10  |
| 462.libquantum    | 122.57 | 444.namd          | 28.91  |
| 464.h264ref       | 56.66  | 447.dealII        | 73.69  |
| 471.omnetpp       | 39.35  | 450.soplex        | 52.00  |
| 473.astar         | 29.24  | 453.povray        | 53.42  |
| 483.xalancbmk     | 72.01  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.17  | 459.GemsFDTD      | 36.01  |
|                   |        | 465.tonto         | 36.74  |
|                   |        | 470.lbm           | 91.18  |
|                   |        | 481.wrf           | 40.62  |
|                   |        | 482.sphinx3       | 48.61  |
|                   |        | **GEOMEAN**       | 44.52  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
