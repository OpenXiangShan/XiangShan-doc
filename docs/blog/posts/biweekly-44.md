---
slug: biweekly-44
date: 2024-01-22
categories:
  - Biweekly
---

# 【香山双周报 44】20240122 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 44 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发接近尾声，各组完成验证文档初版，并持续推进面积和时序的优化，前端修复一处 bug，后端优化了部分流水线，访存实现 FDP 新版代码并即将完成向量访存单元完整测试，缓存完成斜相联可选配置并开始性能探索。本期还更新了昆明湖架构近期性能与物理布局。

<!-- more -->
## 近期进展

### 前端

* 修复 ICache fencei bug（[#2660](https://github.com/OpenXiangShan/XiangShan/pull/2660) ）
* 完成 ITTAGE meta 宽度缩减的优化（[#2592](https://github.com/OpenXiangShan/XiangShan/pull/2592)）

### 后端流水线

* 实现整数乘法的推测唤醒（[#2629](https://github.com/OpenXiangShan/XiangShan/pull/2629)）
* 优化重命名快照的生成策略，提升快照生成性能
* DataPath 读操作数优化，src1 可以用 src0 读口发读请求，立即数在 DataPath 第一拍提取（[#2656](https://github.com/OpenXiangShan/XiangShan/pull/2656)）

### 访存单元

* FDP (Feedback Directed Prefetch) 新版实现，目前有正向收益，正在调试预取策略表和阈值
* 定位到 Stream 预取在 bwaves 上性能异常的原因
* DCache L2 Hint 提前唤醒方案设计完成
* 向量访存单元测试调试接近尾声

### 缓存系统

* skew associative 成为 L3 上的可选配置
* 调研不同缓存压缩算法的实现方式以及压缩效率
* 继续进行四核 litmus-test 验证

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率 100%。SPEC 使用 gcc 12 进行编译，优化选项为 O3，指令集是 RV64GCB，内存库采用了 jemalloc 库。**我们使用 12 月 26 日 951a412 版本的香山处理器（缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元开启 3ld3st 流水线），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟**。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006 | @ 3GHz | SPECfp 2006 | @ 3GHz |
| :-- | --: | :-- | --: |
| 400.perlbench | 36.65 | 410.bwaves | 55.37 |
| 401.bzip2 | 24.28 | 416.gamess | 43.77 |
| 403.gcc | 47.69 | 433.milc | 35.82 |
| 429.mcf | 57.85 | 434.zeusmp | 44.43 |
| 445.gobmk | 31.71 | 435.gromacs | 30.39 |
| 456.hmmer | 39.57 | 436.cactusADM | 46.22 |
| 458.sjeng | 31.50 | 437.leslie3d | 39.51 |
| 462.libquantum | 125.49 | 444.namd | 37.45 |
| 464.h264ref | 57.38 | 447.dealII | 73.55 |
| 471.omnetpp | 42.24 | 450.soplex | 55.74 |
| 473.astar | 30.74 | 453.povray | 55.86 |
| 483.xalancbmk | 75.54 | 454.Calculix | 16.49 |
| **GEOMEAN** | **44.98** | 459.GemsFDTD | 34.22 |
|  |  | 465.tonto | 34.24 |
|  |  | 470.lbm | 85.61 |
|  |  | 481.wrf | 39.58 |
|  |  | 482.sphinx3 | 57.07 |
|  |  | **GEOMEAN** | **43.39** |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

香山处理器昆明湖架构近期物理布局图如下，红、蓝、绿、粉四色分别对应昆明湖 Frontend、Backend、Memblock、L2Cache 四个模块。

![昆明湖架构物理布局图](./figs/biweekly-44/floorplan.png)

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

香山昆明湖架构研发接近尾声，性能会每月底公布一次，敬请期待。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
