---
slug: biweekly-47
date: 2024-03-18
categories:
  - Biweekly
---

# 【香山双周报 47】20240318 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 47 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发接近尾声，各组持续推进面积、时序、功耗的优化。此外，前端实现了动态关闭 FTB，后端完成 Rob 分 bank 读设计和单元性能评估，访存继续推进向量访存调优，缓存完成以 trace 作为激励输入的 TL-Test 框架。本期还更新了昆明湖架构近期性能。

<!-- more -->
## 近期进展

### 前端

* 前端各子模块继续优化门控覆盖率，当前达 96.39%，（[#2789](https://github.com/OpenXiangShan/XiangShan/pull/2789)、[#2790](https://github.com/OpenXiangShan/XiangShan/pull/2790)、[#2791](https://github.com/OpenXiangShan/XiangShan/pull/2791)）
* 实现 uFTB 长期命中时关闭 FTB 的低功耗设计（[#2792](https://github.com/OpenXiangShan/XiangShan/pull/2792)）
* 实现前端 ICache、FTQ、FTB 模块内部的 sram 规格拆分

### 后端流水线

* 去除一个分支运算单元，修改相应的派遣算法（[#2784](https://github.com/OpenXiangShan/XiangShan/pull/2784)）
* 访存单元性能评估，将 store 运算单元由三个减为两个（[#2758](https://github.com/OpenXiangShan/XiangShan/pull/2758)）
* 完成 Rob 分 bank 读设计，每周期可以提交 1-8 条 Rob 项，优化时序
* 进一步提升后端静态门控时钟覆盖率至 96.07%

### 访存单元

* 向量访存 hmmer bugs 部分修复和性能调优，添加提前唤醒逻辑优化策略；开展其面积优化工作，目前降低约 35.75% 面积
* 继续推进访存模块面积优化，目前达 95.53%（[#2678](https://github.com/OpenXiangShan/XiangShan/pull/2678)）
* 初步完成访存模块的静态门控覆盖率优化，已达目标 95%（[#2743](https://github.com/OpenXiangShan/XiangShan/pull/2743)）

### 缓存系统

* 将 L2 的 Data SRAM 改为 Multicycle Path 2，对整体性能影响较小
* 对 L2 SRAM 实现门控 enable，优化功耗
* 推进 CHI 总线改造，实现 CoupledL2 主流水线和 MSHR 部分的代码
* 完成以 trace 作为激励输入的 TL-Test 框架，用时仅需运行完整香山的 1/10，得到的 L3 命中率结果与香山接近
* 基本实现 Temporal 预取数据压缩功能，正在测试性能数据
* 改造 L3 MSHR 流水线，便于实现缓存压缩

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率 30%。SPEC 使用 gcc 12 进行编译，优化选项为 O3，指令集是 RV64GCB。**我们使用 3 月 12 日 31c545125 版本的香山处理器（缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为默认的 2ld2st 流水线），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟**。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006 | @ 3GHz | SPECfp 2006 | @ 3GHz |
| :-- | --: | :-- | --: |
| 400.perlbench | 38.94 | 410.bwaves | 80.69 |
| 401.bzip2 | 25.41 | 416.gamess | 44.63 |
| 403.gcc | 47.05 | 433.milc | 26.88 |
| 429.mcf | 62.73 | 434.zeusmp | 46.13 |
| 445.gobmk | 29.56 | 435.gromacs | 34.79 |
| 456.hmmer | 32.67 | 436.cactusADM | 38.54 |
| 458.sjeng | 30.73 | 437.leslie3d | 48.89 |
| 462.libquantum | 133.02 | 444.namd | 38.44 |
| 464.h264ref | 52.08 | 447.dealII | 86.15 |
| 471.omnetpp | 36.04 | 450.soplex | 52.96 |
| 473.astar | 49.22 | 453.povray | 52.57 |
| 483.xalancbmk | 50.86 | 454.Calculix | 18.76 |
| **GEOMEAN** | **44.10** | 459.GemsFDTD | 43.07 |
|  |  | 465.tonto | 30.47 |
|  |  | 470.lbm | 96.13 |
|  |  | 481.wrf | 30.43 |
|  |  | 482.sphinx3 | 57.25 |
|  |  | **GEOMEAN** | **44.65** |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

香山昆明湖架构研发接近尾声，性能会每月底公布一次，敬请期待。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
