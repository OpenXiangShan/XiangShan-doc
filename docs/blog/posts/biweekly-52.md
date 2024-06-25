---
slug: biweekly-52
date: 2024-05-27
categories:
  - Biweekly
---

# 【香山双周报 52】20240527期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 52 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端整合门控相关优化并交付评估，后端修复多类 bug，访存模块发布新版 Cache 子模块验证框架 tl-test-new。本期还更新了昆明湖架构近期性能。

<!-- more -->
## 近期进展

### 前端

* 完成 BPU、FTQ、FTB 等模块的门控优化，并整合门控相关优化交付物理后端评估
* 完成 ICache 低功耗优化、ITTAGE 低功耗优化的评估
* 修复主线 ICache fence.i 处理逻辑

### 后端流水线

* 修复若干向量浮点拆分引入的 bug（[#2992](https://github.com/OpenXiangShan/XiangShan/pull/2992)）
* 修复 store 访存指令分派策略失效的问题（[#2993](https://github.com/OpenXiangShan/XiangShan/pull/2993)）
* 修复 VType walk 导致的 x 态传播和功能错误问题（[#3001](https://github.com/OpenXiangShan/XiangShan/pull/3001)）
* 修复若干合并向量访存后产生的 bug（[#3008](https://github.com/OpenXiangShan/XiangShan/pull/3008)）
* 实现新版浮点指令分派策略（[#3007](https://github.com/OpenXiangShan/XiangShan/pull/3007)）

### 访存与缓存

* CHI 总线
    * 发布新版 Cache 子模块验证框架 tl-test-new，支持自动化端口对齐，支持更大压力的多核测试激励（[OpenXiangShan/tl-test-new](https://github.com/OpenXiangShan/tl-test-new)）
    * 修复L2 && L3 双核场景的bug，以及L2 SinkC DataBuf相关的bug
* H 扩展
    * 在 NEMU 上补充 CSR 寄存器，实现 Zicntr、Zihpm 等扩展
    * 修复 NEMU H 扩展 CSR 权限检查的 bug
* 向量访存
    * 开发分支 vlsu-240315 跑通全部 riscv-vector-test 和 rvv-bench 测试用例
* 性能优化
    * 实现 MSHR 多端口优化
    * TP meta 和 L2 data空间硬划分对性能提升较小，尝试采用 DRRIP 对 TP meta 的替换进行调优
    * 在 L2 上实现 TUBINS 替换算法，相较 DRRIP 性能提升 0.1%
    * 在 L2 RTL 上实现 Hawkeye 替换，正在测试性能并修复性能 bug
* 功耗优化
    * 完成 LoadQueueRAR / RAW 有关的模块级门控

## 评估
我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的 `-ffp-contraction` 选项为 `fast`，指令集为 RV64GCB。我们使用 **5月23日 2b16f0c2c 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld3st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006   | @ 3GHz | SPECfp 2006   | @ 3GHz |
| :------------- | :----: | :------------ | :----: |
| 400.perlbench  | 26.61  | 410.bwaves    | 79.73  |
| 401.bzip2      | 25.61  | 416.gamess    | 43.72  |
| 403.gcc        | 47.55  | 433.milc      | 43.12  |
| 429.mcf        | 59.00  | 434.zeusmp    | 54.90  |
| 445.gobmk      | 30.39  | 435.gromacs   | 35.48  |
| 456.hmmer      | 39.14  | 436.cactusADM | 44.94  |
| 458.sjeng      | 30.05  | 437.leslie3d  | 43.79  |
| 462.libquantum | 124.41 | 444.namd      | 31.31  |
| 464.h264ref    | 56.88  | 447.dealII    | 73.67  |
| 471.omnetpp    | 40.89  | 450.soplex    | 54.61  |
| 473.astar      | 29.66  | 453.povray    | 55.78  |
| 483.xalancbmk  | 74.04  | 454.Calculix  | 19.86  |
| **GEOMEAN**    | 44.47  | 459.GemsFDTD  | 37.75  |
|                |        | 465.tonto     | 33.73  |
|                |        | 470.lbm       | 95.85  |
|                |        | 481.wrf       | 40.26  |
|                |        | 482.sphinx3   | 42.24  |
|                |        | **GEOMEAN**   | 45.72  |

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
