---
slug: biweekly-104
date: 2026-06-08
categories:
  - Biweekly
---

# 【香山双周报 104】20260608 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 104 期双周报。

RISC-V 欧洲峰会正在举行！香山团队在峰会上有多个 talk，包括新的 Verilog 中间表示 Wolvrix 和可综合参考模型等。我们还首次举办了万众一芯的 workshop，为大家分享我们在敏捷验证和 AI 验证方面的探索与实践。

![万众一心 workshop](./figs/biweekly-104/unity_chip.jpg)

关于香山近期开发进展，前端继续优化时序，同时降低了重定向延迟；后端实现了一些新特性与指令集扩展；访存修复了一些 bug，同时优化了 L2 的时序；XSAI 优化了代码结构，同时推进了 HBL2 对 CHI 的支持。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 提前读取重定向请求对应的 FTQ 项，优化时序的同时降低重定向延迟（[#5990](https://github.com/OpenXiangShan/XiangShan/pull/5990)）
- Bug 修复
  - 修复 UBTB 优化时序过程中引入的、将被覆盖的项作为命中项导致预测错误的问题（[#6009](https://github.com/OpenXiangShan/XiangShan/pull/6009)）
- PPA 优化
  - 优化 IBuffer 入队逻辑时序（[#5946](https://github.com/OpenXiangShan/XiangShan/pull/5946)）

### 后端

- RTL 新特性
  - 使用稀疏向量（SparseVec）作为异常向量的存储结构 ([#5738](https://github.com/OpenXiangShan/XiangShan/pull/5738))
  - Sdtrig 扩展支持 tdata3 ([#5983](https://github.com/OpenXiangShan/XiangShan/pull/5983))

### 访存与缓存

- Bug 修复
  - 修复了跨 16 字节 store 时与 fullOverlap 有关的问题（[#6003](https://github.com/OpenXiangShan/XiangShan/pull/6003)）
- PPA 优化
  - 将 L2 的预取请求队列按 slice 拆分，减少不同 slice 间的阻塞（[XSCache #13](https://github.com/OpenXiangShan/XSCache/pull/13)）
- 代码重构
  - 将预取从 loadUnit 移动到 mainPipe（[#5997](https://github.com/OpenXiangShan/XiangShan/pull/5997)）

### XSAI

- RTL 新特性
  - 添加用于关闭 mxfp8 等带缩放因子数据类型的选项，在关闭这些数据类型后，处理缩放因子的模块将不会被实例化（[CUTE #13](https://github.com/OpenXiangShan/CUTE/pull/13)）
  - 为 CUTE 添加一系列矩阵性能事件（[CUTE #18](https://github.com/OpenXiangShan/CUTE/pull/18)）
  - 正在推进 HBL2 对 CHI 总线协议的支持
- Bug 修复
  - 修复 XSAI V2R2A 的性能事件编号，与昆明湖 V2R2 的事件编号对齐（[XSAI #70](https://github.com/OpenXiangShan/XSAI/pull/70)）
  - 修复矩阵功能单元异常未被 ROB 处理的问题（[XSAI #71](https://github.com/OpenXiangShan/XSAI/pull/71)）
- 代码重构
  - 重构 CUTE 调度（[CUTE #14](https://github.com/OpenXiangShan/CUTE/pull/14)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | dcc1d2689  |
| 日期      | 2026/05/21 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 2MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.42  | 47.53  | 410.bwaves         | 85.27  | 89.88  |
| 401.bzip2           | 27.43  | 28.28  | 416.gamess         | 57.05  | 53.23  |
| 403.gcc             | 55.26  | 38.88  | 433.milc           | 64.93  | 64.04  |
| 429.mcf             | 61.00  | 55.47  | 434.zeusmp         | 71.27  | 64.66  |
| 445.gobmk           | 38.94  | 40.10  | 435.gromacs        | 37.20  | 34.38  |
| 456.hmmer           | 54.38  | 64.72  | 436.cactusADM      | 76.13  | 87.68  |
| 458.sjeng           | 38.87  | 39.48  | 437.leslie3d       | 56.26  | 56.36  |
| 462.libquantum      | 136.67 | 294.84 | 444.namd           | 43.23  | 45.23  |
| 464.h264ref         | 63.46  | 71.99  | 447.dealII         | 64.25  | 68.39  |
| 471.omnetpp         | 41.07  | 39.47  | 450.soplex         | 52.12  | 63.93  |
| 473.astar           | 30.42  | 29.63  | 453.povray         | 73.34  | 65.77  |
| 483.xalancbmk       | 75.83  | 84.61  | 454.Calculix       | 43.74  | 39.61  |
| GEOMEAN             | 50.90  | 54.07  | 459.GemsFDTD       | 63.50  | 63.95  |
|                     |        |        | 465.tonto          | 52.59  | 35.01  |
|                     |        |        | 470.lbm            | 125.82 | 133.04 |
|                     |        |        | 481.wrf            | 54.96  | 41.58  |
|                     |        |        | 482.sphinx3        | 59.39  | 62.42  |
|                     |        |        | GEOMEAN            | 61.07  | 59.18  |

编译参数如下所示：

| 参数             | GCC15       | XSCC                |
| ---------------- | ----------- | ------------------- |
| 编译器           | gcc15       | xscc                |
| 编译优化         | O3          | O3                  |
| 内存库           | jemalloc    | jemalloc            |
| -march           | RV64GCB     | RV64GCB             |
| -ffp-contraction | fast        | fast                |
| 链接优化         | -flto       | -flto               |
| 浮点优化         | -ffast-math | -ffast-math         |
| -mcpu            | -           | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、孙际儒、李衍君
