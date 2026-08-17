---
slug: biweekly-40
date: 2023-11-27
categories:
  - Biweekly
---

# 【香山双周报 40】20231127 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 40 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发接近尾声，各组持续推进面积和时序的优化，后端实现更加激进的 load 推测快速唤醒，向量访存模块在 MinimalConfig 下完成初步功能验证，缓存中探索 L3 新替换算法，在硬件仿真加速器上实现了新的调试功能。本期还更新了昆明湖架构近期性能与物理布局。

<!-- more -->
## 近期进展

### 前端

* 完成前端 FTQ 面积压缩方案修正
* 完成 FTB 和 ICache 的 sram 规格拆分（[#2493](https://github.com/OpenXiangShan/XiangShan/pull/2493)，[#2497](https://github.com/OpenXiangShan/XiangShan/pull/2497)）

### 后端流水线

* BusyTable 支持 load 推测快速唤醒（[#2502](https://github.com/OpenXiangShan/XiangShan/pull/2502)）
* IssueQueue 时序优化，出队后并行 flush 和 load cancel（[#2494](https://github.com/OpenXiangShan/XiangShan/pull/2494)）
* 降低 IQ entry 位宽，删除重复项，减少立即数占用（[#2500](https://github.com/OpenXiangShan/XiangShan/pull/2500)）
* 优化 IQ 入队唤醒时序，将入队唤醒放在 EnqEntry 完成（[#2499](https://github.com/OpenXiangShan/XiangShan/pull/2499)）

### 访存单元

* 持续推进时序优化，MemBlock 内部违例减小至 -30ps 左右（[#2501](https://github.com/OpenXiangShan/XiangShan/pull/2501)）
* 新 features（实现紧耦合 L1-L2 总线和关键字优先）已跑通 CI 等基本测试
* MinimalConfig 下的 VLSU 跑通 riscv-vector-tests 全部测试用例
* 正在 HybridUnit 上添加向量访存通路
* 实现硬件仿真加速器上 Squash 出错现场重放功能

### 缓存系统

* 继续进行跨模块时序优化，修改多处 L1D-L2 以及 L1I-L2 的时序违例路径
* 将 archdb 验证工具移植到硬件仿真加速器上，进行单核及多核功能验证，修复几处 bug
* L3 新替换算法进行性能测试，有一定性能倒退，正在分析原因

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率 100%。SPEC 使用 gcc 12 进行编译，优化选项为 O3，指令集是 RV64GCB，其中 Xalancbmk 使用了 jemalloc 库。**我们使用 11 月 14 日 2072875 版本的香山处理器（缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟**。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006 | @ 3GHz | SPECfp 2006 | @ 3GHz |
| :-- | --: | :-- | --: |
| 400.perlbench | 36.86 | 410.bwaves | 67.06 |
| 401.bzip2 | 23.46 | 416.gamess | 43.72 |
| 403.gcc | 49.55 | 433.milc | 31.48 |
| 429.mcf | 53.92 | 434.zeusmp | 48.85 |
| 445.gobmk | 31.29 | 435.gromacs | 31.48 |
| 456.hmmer | 32.42 | 436.cactusADM | 37.92 |
| 458.sjeng | 31.17 | 437.leslie3d | 39.51 |
| 462.libquantum | 121.69 | 444.namd | 37.07 |
| 464.h264ref | 51.03 | 447.dealII | 57.51 |
| 471.omnetpp | 36.44 | 450.soplex | 54.43 |
| 473.astar | 29.39 | 453.povray | 53.58 |
| 483.xalancbmk | 55.34 | 454.Calculix | 15.21 |
| **GEOMEAN** | **41.60** | 459.GemsFDTD | 40.71 |
|  |  | 465.tonto | 31.70 |
|  |  | 470.lbm | 91.92 |
|  |  | 481.wrf | 37.73 |
|  |  | 482.sphinx3 | 57.25 |
|  |  | **GEOMEAN** | **42.67** |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

香山处理器昆明湖架构近期物理布局图如下，红、蓝、绿、粉四色分别对应昆明湖 Frontend、Backend、Memblock、L2Cache 四个模块。

![昆明湖架构物理布局图](./figs/biweekly-40/floorplan.png)

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

香山昆明湖架构研发接近尾声，性能会每月底公布一次，敬请期待。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
