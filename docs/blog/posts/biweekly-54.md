---
slug: biweekly-54
date: 2024-06-24
categories:
  - Biweekly
---

# 【香山双周报 54】20240624期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 54 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

从本期开始，我们将在香山文档上同步更新双周报，欢迎各位关注！

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端初步完成 ittage 新方案短期改进，后端修复向量执行单元部分 bug，CHI-L3 基本框架设计完成，向量访存修复部分性能 bug，着手支持 Sv48。本期还更新了昆明湖架构近期性能。

<!-- more -->
## 近期进展

### 前端

* 修复 load replay redirect 请求导致前端FTQ死锁bug（[#3086](https://github.com/OpenXiangShan/XiangShan/pull/3086)）
* 初步完成 ittage 新方案的短期改进，降低功耗和面积（[#3092](https://github.com/OpenXiangShan/XiangShan/pull/3092)）
* 修复 ICache 的 X 态问题（[#3051](https://github.com/OpenXiangShan/XiangShan/pull/3051)、[#3079](https://github.com/OpenXiangShan/XiangShan/pull/3079)）

### 后端流水线

* 修复一系列向量指令拆分和异常处理的 bug（[#3091](https://github.com/OpenXiangShan/XiangShan/pull/3091)）
* 修复向量执行单元的 ImmInfo 在 og2 没有打一拍的错误（[#3089](https://github.com/OpenXiangShan/XiangShan/pull/3089)）
* 优化访存 IQ 的响应信号时序（[#3088](https://github.com/OpenXiangShan/XiangShan/pull/3088)）
* 使用 ExuVec 替代 ExuOH，并强制拉低不需要的比特，优化 BypassNetwork 时序（[#3083](https://github.com/OpenXiangShan/XiangShan/pull/3083)）

### 访存与缓存

* CHI 总线
    * 新版 CHI-L3 完成基本框架和请求处理流程设计，计划上下游接口均为 CHI 协议
    * 完成 DummyLLC 的 RTL 实现
    * 实现 Non-data error 在 CHI、TileLink 总线上的传递和在 LSU 中的处理机制
    * tl_test_new/ST test 修复因修改时序引入功能 bug
    * 修复 RTL 和验证环境在 multi-bank 时的 bug，目前双核及四核 multi-bankTLTest 均已测试通过
    * 关键路径违例从 -110ps 优化到 -32ps
* H 扩展
    * 修复一系列 bug ([#3096](https://github.com/OpenXiangShan/XiangShan/pull/3096)、[#3078](https://github.com/OpenXiangShan/XiangShan/pull/3078)、[#3077](https://github.com/OpenXiangShan/XiangShan/pull/3077))
    * 着手开展 H 扩展性能测试
* 向量访存
    * 修复 SQ 中向量 Segment 指令异常提交逻辑
    * 修复 inactive 向量 store 在 storeQueue 中导致 load 重复进入 LoadReplayQueue 而卡死的问题
    * 目前不生成 segment 指令的 libquantum 分数 41.08/GHz，h264 向量化性能倒退 2.4/GHz
    * 关键路径违例优化至 -63ps
* 功能新增
    * 确定 Sv48 在 MMU 上的设计方案，L1 TLB 完成 Sv48 的改动并实现可配置开关
* 性能优化
    * TP meta on L2 选用 RRIP 替换，利用 Trace-drive TL-Test 进行设计调优
    * TP on L3 经测试在 SPEC Int 有 0.17 分提升，总分有 0.09 的提升
    * Tubins 替换经参数调优，在 L2 中性能分数比 plru 提升 0.11%
    * DRRIP 发现一个 set dueling 采样 bug，经修复在 mcf 上性能有较大提升
    * 正在尝试实现 CHROME 替换算法
* PPA 优化
    * CHI-CoupledL2 内部关键路径违例优化至 -28ps，关键路径逻辑级数到 30 级以内
    * MemBlock 门控修改合入主线（[#3017](https://github.com/OpenXiangShan/XiangShan/pull/3017)）

## 评估
我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用jemalloc内存库，设置SPEC06FP的-ffp-contraction选项为fast，指令集为RV64GCB。我们使用 **6 月 14 日 87c5d21d6 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld3st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006   | @ 3GHz | SPECfp 2006   | @ 3GHz |
| :------------- | :----: | :------------ | :----: |
| 400.perlbench  | 36.50  | 410.bwaves    | 76.87  |
| 401.bzip2      | 25.58  | 416.gamess    | 44.09  |
| 403.gcc        | 41.28  | 433.milc      | 42.94  |
| 429.mcf        | 59.05  | 434.zeusmp    | 60.51  |
| 445.gobmk      | 30.38  | 435.gromacs   | 38.93  |
| 456.hmmer      | 39.34  | 436.cactusADM | 47.76  |
| 458.sjeng      | 30.00  | 437.leslie3d  | 46.59  |
| 462.libquantum | 125.54 | 444.namd      | 35.60  |
| 464.h264ref    | 56.87  | 447.dealII    | 74.60  |
| 471.omnetpp    | 41.23  | 450.soplex    | 54.91  |
| 473.astar      | 29.61  | 453.povray    | 56.54  |
| 483.xalancbmk  | 74.06  | 454.Calculix  | 18.04  |
| **GEOMEAN**    | 44.00  | 459.GemsFDTD  | 37.73  |
|                |        | 465.tonto     | 34.80  |
|                |        | 470.lbm       | 102.24 |
|                |        | 481.wrf       | 43.55  |
|                |        | 482.sphinx3   | 50.46  |
|                |        | **GEOMEAN**   | 47.63  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

**News**: 从本期开始，我们将在香山文档上同步更新双周报，欢迎各位关注。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/


编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
