---
slug: biweekly-57
date: 2024-08-19
categories:
  - Biweekly
---
# 【香山双周报 57】20240819 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 57 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

WIP：这里要补充一行概述

<!-- more -->

## 近期进展

### 前端

修复重构 IFU 异常处理部分代码引入的 32b 指令跨页异常 Bug，同时修复了此处南湖遗留的 Bug

RVA23 支持新增：Zicbop `prefetch.i` 指令，Svpbmt 扩展的前端支持

ITTAGE 预测器更新使用的信息从 Checkpoint 机制（保存在 FTQ 中）改为更新时读

RAS 预测器推测栈溢出由不处理溢出改为阻塞 BPU 流水

### 后端流水线

- Bug 修复
    - 持续推进功能 bug 修复，共修复60余例，以下是部分pr：
    - 修复v拓展功能 bug ([#3384](https://github.com/OpenXiangShan/XiangShan/pull/3384), [#3384](https://github.com/OpenXiangShan/XiangShan/pull/3384), [#3358](https://github.com/OpenXiangShan/XiangShan/pull/3358), [#3296](https://github.com/OpenXiangShan/XiangShan/pull/3296), [#3284](https://github.com/OpenXiangShan/XiangShan/pull/3284), [#3399](https://github.com/OpenXiangShan/XiangShan/pull/3399), [#3391](https://github.com/OpenXiangShan/XiangShan/pull/3391))
    - 修复特权级功能 bug ([#3379](https://github.com/OpenXiangShan/XiangShan/pull/3379), [#3360](https://github.com/OpenXiangShan/XiangShan/pull/3360), [#3353](https://github.com/OpenXiangShan/XiangShan/pull/3353), [#3338](https://github.com/OpenXiangShan/XiangShan/pull/3338), [#3327](https://github.com/OpenXiangShan/XiangShan/pull/3327), [#3314](https://github.com/OpenXiangShan/XiangShan/pull/3314), [#3324](https://github.com/OpenXiangShan/XiangShan/pull/3324), [#3301](https://github.com/OpenXiangShan/XiangShan/pull/3301), [#3300](https://github.com/OpenXiangShan/XiangShan/pull/3300))
    - 修复H拓展功能 bug ([#3397](https://github.com/OpenXiangShan/XiangShan/pull/3397), [#3385](https://github.com/OpenXiangShan/XiangShan/pull/3385), [#3378](https://github.com/OpenXiangShan/XiangShan/pull/3378), [#3375](https://github.com/OpenXiangShan/XiangShan/pull/3375), [#3357](https://github.com/OpenXiangShan/XiangShan/pull/3357), [#3343](https://github.com/OpenXiangShan/XiangShan/pull/3343), [#3342](https://github.com/OpenXiangShan/XiangShan/pull/3342), [#3331](https://github.com/OpenXiangShan/XiangShan/pull/3331), [#3317](https://github.com/OpenXiangShan/XiangShan/pull/3317), [#3308](https://github.com/OpenXiangShan/XiangShan/pull/3308), [#3305](https://github.com/OpenXiangShan/XiangShan/pull/3305), [#3298](https://github.com/OpenXiangShan/XiangShan/pull/3298))
- 时序优化
    - 优化传递到前端 Ibuf 的 ready 信号逻辑 ([#3293](https://github.com/OpenXiangShan/XiangShan/pull/3293))
    - 优化 Ibuf bypass 的读指针以及输出逻辑 ([#3344](https://github.com/OpenXiangShan/XiangShan/pull/3344))
    - 移除 loadCancel 到发射队列和 BusyTable 中的部分伪路径 ([#3374](https://github.com/OpenXiangShan/XiangShan/pull/3374))([#3382](https://github.com/OpenXiangShan/XiangShan/pull/3382), [#3364](https://github.com/OpenXiangShan/XiangShan/pull/3364))
- 寄存器堆 cache
    - 完成寄存器堆 cache 设计，已合入主线:寄存器读端口从15减少到10，整数性能对比base提升1.5% ([#3290](https://github.com/OpenXiangShan/XiangShan/pull/3290))
- Difftest 框架
    - FCSR/PC 加入 Difftest 对比框架, 修复向量和浮点相关CSR对比机制 ([#3359](https://github.com/OpenXiangShan/XiangShan/pull/3359), [#3294](https://github.com/OpenXiangShan/XiangShan/pull/3294))
- RVA23
    - 支持 Zimop/Zcmop ([3409](https://github.com/OpenXiangShan/XiangShan/pull/3409))
    - Sstvala/Shvstvala 通过冒烟用例测试
    - Zfa/Zfhmin/Zvfhmin 实现完成，正在测试
### 访存与缓存

#### CHI 总线

CHI-L3（OpenLLC）完成代码设计，接入香山系统测试，构建 CHI-L2+OpenLLC+DummyLLC(CHI2AXI) SoC，跑通单核 CoreMark 以及 Linux-hello

在 OpenLLC 中添加对 CHI 的 CMO 指令的支持

制定 CHI2AXI 转接桥的设计方案，开始进行 RTL 设计

#### 功能
完成 RVA23 CMO 代码设计，接入支持 CMO 请求的 OpenLLC 的 TL-Test 框架进行测试，能正确运行单条 CMO 请求

#### 性能
TP meta on L2 添加 TP metaBuffer，用于缓存有效的 TP meta，缓解 TP meta 与 L2 数据的负面竞争；添加基于访存频率的 TP 开关，在访存密集时关闭 TP

L2 Tubins 替换算法经测试，性能分数相较 DRRIP 替换算法有 0.15% 的提升

L3 Chrome 替换算法在通过单元测试框架 trace 激励的测试与参数调优后，在 mcf 上命中率提升 27%，但在部分 checkpoint 上命中率下降；对 EQ 空间压缩进行进一步探索

#### 工具
TL-Test 框架迭代，可将 TL Log 解析成为 trace（TL Trace），作为测试激励

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **8 月 12 日 9d9be651a 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006      | @ 3GHz | SPECfp 2006       | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 33.52  | 410.bwaves        | 76.87  |
| 401.bzip2         | 24.96  | 416.gamess        | 43.36  |
| 403.gcc           | 47.68  | 433.milc          | 42.66  |
| 429.mcf           | 58.82  | 434.zeusmp        | 59.14  |
| 445.gobmk         | 30.03  | 435.gromacs       | 37.84  |
| 456.hmmer         | 40.26  | 436.cactusADM     | 47.84  |
| 458.sjeng         | 29.72  | 437.leslie3d      | 45.73  |
| 462.libquantum    | 126.91 | 444.namd          | 34.32  |
| 464.h264ref       | 56.48  | 447.dealII        | 74.12  |
| 471.omnetpp       | 41.12  | 450.soplex        | 54.53  |
| 473.astar         | 28.96  | 453.povray        | 55.70  |
| 483.xalancbmk     | 75.09  | 454.Calculix      | 18.14  |
| **GEOMEAN**       | 44.09  | 459.GemsFDTD      | 36.91  |
|                   |        | 465.tonto         | 35.73  |
|                   |        | 470.lbm           | 101.20 |
|                   |        | 481.wrf           | 42.14  |
|                   |        | 482.sphinx3       | 51.49  |
|                   |        | **GEOMEAN**       | 47.16  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
