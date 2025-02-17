---
slug: biweekly-70
date: 2025-02-17
categories:
  - Biweekly
---

# 【香山双周报 70】20250217 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 70 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 面积

### 后端流水线

- Bug 修复
    - 修复部分指令信息在硬件性能计数器丢失的问题 ([#4257](https://github.com/OpenXiangShan/XiangShan/pull/4257))
    - 修复 scountovf 寄存器读取时未受 counteren 控制的问题 ([#4267](https://github.com/OpenXiangShan/XiangShan/pull/4267))
    - 修复写 mcontrol6 寄存器的 dmode 字段时未考虑 chain 的影响 ([#4256](https://github.com/OpenXiangShan/XiangShan/pull/4256))
    - 修复向量无序规约求和中 fflags 标志位生成出错的问题 ([#4244](https://github.com/OpenXiangShan/XiangShan/pull/4244))

- RVA23 Profile
    - 支持低功耗轮询拓展 (zawrs) ([#4211](https://github.com/OpenXiangShan/XiangShan/pull/4211))

### 访存与缓存

- RVA23 Profile

- CHI 总线
    - 在 CoupledL2 以及 OpenLLC + OpenNCB 的 SoC 中已经支持 Issue C ([CoupledL2 #333](https://github.com/OpenXiangShan/CoupledL2/pull/333))、([OpenLLC #47](https://github.com/OpenXiangShan/OpenLLC/pull/47))、([OpenNCB #3](https://github.com/OpenXiangShan/OpenNCB/pull/3))

- Bug 修复
    - 修复 WriteEvictOrEvict 回复状态不符合手册标准的 bug ([CoupledL2 #352](https://github.com/OpenXiangShan/CoupledL2/pull/352))
    - 修复 SnqQuery 嵌套 Evict 时，SnqQuery 回复状态不符合一致性要求的 bug ([CoupledL2 #353](https://github.com/OpenXiangShan/CoupledL2/pull/353))
    - 修复一系列 DataCheck、Poison 相关 bug ([CoupledL2 #335](https://github.com/OpenXiangShan/CoupledL2/pull/335))、([CoupledL2 #337](https://github.com/OpenXiangShan/CoupledL2/pull/337))、([CoupledL2 #339](https://github.com/OpenXiangShan/CoupledL2/pull/339))


- PPA 优化
    - 时序
        - 调整 loadqueue RAR 和 store misalign buffer 的入队逻辑 ([#4207](https://github.com/OpenXiangShan/XiangShan/pull/4207))
        - 调整 Dcache missqueue 的取消逻辑以及 mainpipe tag / meta 的读使能逻辑 ([#4208](https://github.com/OpenXiangShan/XiangShan/pull/4208))




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