---
slug: biweekly-49
date: 2024-04-15
categories:
  - Biweekly
---

# 【香山双周报 49】20240415期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 49 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端优化了 FTB 并重构了 ICache；后端修复了浮点性能严重下滑的问题；访存组 H 扩展成功合入香山主线，修复大量 VLSU 重构 bug；缓存组修复初版 CHI-CoupledL2 若干 bug，四核缓存子系统成功通过 TL-Test 的 9 个 seed 共 9 亿拍测试。本期还更新了昆明湖架构近期性能。

<!-- more -->
## 近期进展

### 前端
- FTQ 折叠历史相关存储面积裁剪（[#2856](https://github.com/OpenXiangShan/XiangShan/pull/2856)）
- FTB 功耗优化，实现根据阈值控制 FTB 的开关（[#2863](https://github.com/OpenXiangShan/XiangShan/pull/2863)）
- 修复 ICache 预取中 p1_vaddr、p2_vaddr 的初始化问题（[#2843](https://github.com/OpenXiangShan/XiangShan/pull/2843)）
- 重构 ICache 以实现功耗优化，目前正在时序调优


### 后端流水线
- 修复浮点发射队列间唤醒通路的连接，修复后浮点性能提升约 32.38%（[#2830](https://github.com/OpenXiangShan/XiangShan/pull/2830)）
- 修复 vfcvt FU 在标量指令支持上未判定输入为 CanonicalNAN 的情况（[#2855](https://github.com/OpenXiangShan/XiangShan/pull/2855)）
- 修复由分 Bank ROB 暴露出的 walk 指针设置错误、vfdatasource 错误等 bug（[#2877](https://github.com/OpenXiangShan/XiangShan/pull/2877)）

### 访存单元
- H 扩展通过 CI 测试，已合入香山主线（[#2852](https://github.com/OpenXiangShan/XiangShan/pull/2852)）
- 向量访存重构后，大量 bug 被修复，目前已打通 unit-stride 通路；VLSU 异常处理接近完成
- Evict on refill 特性完成性能和时序评估
- 初步完成 LQRAW 和 LQReplay 的门控编码；部分完成 LSQ 的面积裁剪

### 缓存系统
- CHI-CoupledL2 初版 RTL 若干 bug 修复，在 CHI VIP 的 VCS 环境中成功启动被动模式 TL-Test
- 分析采用 MultiCyclePath2 的 L2 时序结果，并做进一步优化
- 修复 TL-Test bug，四核缓存子系统成功通过 TL-Test 的 9 个 seed 共 9 亿拍测试
- 在 L2 上实现缓存数据压缩算法，并评估 L2 容量增减对 SPEC 的性能影响
- 完成 Temperal 预取器的 meta 迁移到 L2 并共享缓存数据空间

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 80%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的 `-ffp-contraction` 选项为 `fast`，指令集为 RV64GCB。我们使用 **4月3日 1d97d643e 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 2ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006   | @ 3GHz | SPECfp 2006   | @ 3GHz |
| :------------- | :----: | :------------ | :----: |
| 400.perlbench  | 35.11  | 410.bwaves    | 43.13  |
| 401.bzip2      | 25.09  | 416.gamess    | 42.84  |
| 403.gcc        | 48.05  | 433.milc      | 33.89  |
| 429.mcf        | 58.91  | 434.zeusmp    | 42.95  |
| 445.gobmk      | 31.56  | 435.gromacs   | 29.52  |
| 456.hmmer      | 32.61  | 436.cactusADM | 38.33  |
| 458.sjeng      | 31.82  | 437.leslie3d  | 39.89  |
| 462.libquantum | 130.84 | 444.namd      | 37.04  |
| 464.h264ref    | 51.89  | 447.dealII    | 67.19  |
| 471.omnetpp    | 41.19  | 450.soplex    | 56.09  |
| 473.astar      | 32.00  | 453.povray    | 52.27  |
| 483.xalancbmk  | 73.56  | 454.Calculix  | 16.46  |
| **GEOMEAN**    | 44.08  | 459.GemsFDTD  | 34.65  |
|                |        | 465.tonto     | 33.29  |
|                |        | 470.lbm       | 86.96  |
|                |        | 481.wrf       | 37.28  |
|                |        | 482.sphinx3   | 55.38  |
|                |        | **GEOMEAN**   | 41.35  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/


编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
