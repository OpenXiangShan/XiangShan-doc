---
slug: biweekly-38
date: 2023-10-30
categories:
  - Biweekly
---

# 【香山双周报 38】20231030 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 38 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发稳步推进，前端着手于面积优化，后端完成了部分模块的时序优化和模块迁移并推进了向量模块的开发，访存向量初版代码合入新后端，缓存调试了部分性能 bug。此次我们还新增了性能评估板块，用于记录近期趋于稳定的昆明湖性能。

<!-- more -->
## 近期进展

### 前端

* 实现重定向抢拍的设计修改，减少给 FTQ 带来的面积影响（[#2420](https://github.com/OpenXiangShan/XiangShan/pull/2420)）
* 通过折叠相邻项解决了 TAGE BaseTable 无法正确替换为 SRAM 的问题，减少 TAGE 面积（[#2408](https://github.com/OpenXiangShan/XiangShan/pull/2408)）
* 修复 Cache 指令占用的 CSR 编码区域和 ECC 使能重叠的问题，增加人工注入 ECC 错误的机制（[#2401](https://github.com/OpenXiangShan/XiangShan/pull/2401)）

### 后端流水线

* IQ 和 Scheduler 时序优化，IQ 内部时序已基本达到要求
* Debug module 迁移至昆明湖完成
* 重定向时保留仍有用的 snapshot 重命名快照（[#2400](https://github.com/OpenXiangShan/XiangShan/pull/2400)）
* 添加 i2v 模块，通过 OPIVX、OPMVX 等指令测试

### 访存单元

* 发现 Memset 性能异常并定位原因
* 部分修复 BOP 虚地址预取合并 master 后的性能异常（[#2382](https://github.com/OpenXiangShan/XiangShan/pull/2382)）
* 实现 StoreQueue 数据合并的优化
* 完成向量访存初版代码并合入新后端，移植 riscv-vector-tests 测试集并开始 VLSU 测试，目前已跑通第一条向量 Load 指令

### 缓存系统

* 在新版 master 代码上对 Hint 优化进行性能测试，发现性能异常并定位原因
* 在优化 LLC 替换算法过程中修复了 tl-test 模块测试和 CoupledL2 的两处 bug
* 配置四核香山的 litmus test，生成测试用例，正在调试一致性相关的 bug

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率 100%。SPEC 使用 gcc 12 进行编译，优化选项为 O3，指令集是 RV64GCB，其中 Xalancbmk 使用了 jemalloc 库。**我们使用 10 月 21 日 c157cf7 版本的香山处理器（缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟**。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006 | @ 3GHz | SPECfp 2006 | @ 3GHz |
| :-- | --: | :-- | --: |
| 400.perlbench | 36.89 | 410.bwaves | 65.37 |
| 401.bzip2 | 23.06 | 416.gamess | 43.55 |
| 403.gcc | 49.23 | 433.milc | 31.42 |
| 429.mcf | 53.39 | 434.zeusmp | 46.75 |
| 445.gobmk | 30.57 | 435.gromacs | 31.42 |
| 456.hmmer | 32.44 | 436.cactusADM | 37.85 |
| 458.sjeng | 30.68 | 437.leslie3d | 39.55 |
| 462.libquantum | 121.71 | 444.namd | 37.03 |
| 464.h264ref | 50.95 | 447.dealII | 57.32 |
| 471.omnetpp | 36.53 | 450.soplex | 54.05 |
| 473.astar | 28.06 | 453.povray | 53.24 |
| 483.xalancbmk | 55.16 | 454.Calculix | 15.20 |
| **GEOMEAN** | **41.19** | 459.GemsFDTD | 40.23 |
|  |  | 465.tonto | 31.61 |
|  |  | 470.lbm | 91.90 |
|  |  | 481.wrf | 37.67 |
|  |  | 482.sphinx3 | 57.14 |
|  |  | **GEOMEAN** | **42.38** |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
