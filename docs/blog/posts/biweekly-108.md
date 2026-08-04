---
slug: biweekly-108
date: 2026-08-03
categories:
  - Biweekly
---

# 【香山双周报 108】20260803 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 108 期双周报。

关于香山近期开发进展，前端修复了多个模块的时序问题，并修复了一些由社区发现的 bug；后端修复了多个 CSR、调试模式和性能事件相关的 bug，并同步了 V2 的修复到 V3；访存与缓存方面，支持了预分配 StoreQueue、LoadQueueReplay 快速唤醒和双端口 L1-L2 TileLink 总线，并修复了多个 bug；XSAI 修复了 load/store whole C 指令的控制信号，并支持可配置的 CUTE 多通道访存。

<!-- more -->

## 近期进展

### 前端

- PPA 优化
  - 优化 ICache DataArray 读使能相关信号时序（[#6221](https://github.com/OpenXiangShan/XiangShan/pull/6221)）
  - 优化 IFU 指令边界计算逻辑及 ICache miss 路径时序（[#6219](https://github.com/OpenXiangShan/XiangShan/pull/6219)）
  - 使用控制流指令（分支、跳转）的 position 代替其 offset，减少关键路径上无谓的加减法运算（[#6253](https://github.com/OpenXiangShan/XiangShan/pull/6253)）

### 后端

- 功能验证与依赖更新（V2）
  - 更新 ready-to-run 中的 NEMU 引用，以同步近期的验证支持（[#6252](https://github.com/OpenXiangShan/XiangShan/pull/6252)、[#6266](https://github.com/OpenXiangShan/XiangShan/pull/6266)）
- Bug 修复（V2）
  - 修复调试模式下双重陷阱不应触发 `criticalError` 的问题（[#6224](https://github.com/OpenXiangShan/XiangShan/pull/6224)）
  - 修复 `s_EX_DT` 应由 `sstatus.SDT` 控制的问题（[#6256](https://github.com/OpenXiangShan/XiangShan/pull/6256)）
  - 使用同步后的 CPU 复位信号复位 trace 流水线（[#6257](https://github.com/OpenXiangShan/XiangShan/pull/6257)）
  - 修复 NMI 与异常同时发生时错误陷入 HS/VS 事件的问题（[#6258](https://github.com/OpenXiangShan/XiangShan/pull/6258)）
- 性能分析（V2）
  - 校正 TopDown 分析中内存停顿的归因：根据具体的内存压力信号区分 load 与 store 停顿（[#6179](https://github.com/OpenXiangShan/XiangShan/pull/6179)）

### 访存与缓存

- RTL 新特性
  - 新增一个 DCache 节点以实现双通道的 TileLink 总线（[#6178](https://github.com/OpenXiangShan/XiangShan/pull/6178)）
  - 实现了 Zabha 扩展（[#6248](https://github.com/OpenXiangShan/XiangShan/pull/6248)）
- Bug 修复
  - 拒绝无效的 TLB 更新以及非物理地址 store 的唤醒操作（[#6275](https://github.com/OpenXiangShan/XiangShan/pull/6275)）
- 性能优化
  - 优化了严格 StoreSet 预测（[#6286](https://github.com/OpenXiangShan/XiangShan/pull/6286)）
  - 在 loadUnit 中添加对 RRBankConflict 仲裁器的支持（[#6242](https://github.com/OpenXiangShan/XiangShan/pull/6242)）

### XSAI

- RTL 新特性
  - AME 版本更新至 XSAI AME proposal 14（[XSAI #77](https://github.com/OpenXiangShan/XSAI/pull/77)）
  - ZhuJiang LLC 的集成支持（[XSAI #91](https://github.com/OpenXiangShan/XSAI/pull/91)）
- Bug 修复
  - 修复了 mcsr 的别名 CSR 读写错误（[XSAI #98](https://github.com/OpenXiangShan/XSAI/pull/98)）
  - 修复 AmuCtrlBuffer 的 redirect 逻辑，与 ROB 对齐（[XSAI #99](https://github.com/OpenXiangShan/XSAI/pull/99)）
  - 修复 AmuCtrlBuffer 内部 PriorityEncoder 的未定义行为（[XSAI #100](https://github.com/OpenXiangShan/XSAI/pull/100)）
  - 修复 LSQ 对于缓冲溢出的过于严格的断言检查（[XSAI #101](https://github.com/OpenXiangShan/XSAI/pull/101)）
  - 修复 mfence 指令未阻塞后续指令导致的死锁（[XSAI #102](https://github.com/OpenXiangShan/XSAI/pull/102)）
- 代码质量
  - CUTE 提供 msync 数量配置接口（[XSAI #95](https://github.com/OpenXiangShan/XSAI/pull/95)）（[CUTE #34](https://github.com/OpenXiangShan/CUTE/pull/34)）
  - 移除冗余的 mtilem/n/k 重置逻辑（[XSAI #97](https://github.com/OpenXiangShan/XSAI/pull/97)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 538ef487c  |
| 日期      | 2026/07/16 |
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
| 400.perlbench       | 51.60  | 50.69  | 410.bwaves         | 117.89 | 105.06 |
| 401.bzip2           | 29.70  | 30.32  | 416.gamess         | 58.32  | 55.79  |
| 403.gcc             | 56.22  | 40.24  | 433.milc           | 70.45  | 68.03  |
| 429.mcf             | 69.66  | 62.60  | 434.zeusmp         | 77.94  | 68.08  |
| 445.gobmk           | 39.88  | 40.41  | 435.gromacs        | 38.26  | 35.16  |
| 456.hmmer           | 55.26  | 66.99  | 436.cactusADM      | 80.28  | 92.71  |
| 458.sjeng           | 39.49  | 40.79  | 437.leslie3d       | 60.26  | 60.56  |
| 462.libquantum      | 138.31 | 308.74 | 444.namd           | 42.98  | 45.22  |
| 464.h264ref         | 69.77  | 75.31  | 447.dealII         | 73.92  | 73.54  |
| 471.omnetpp         | 43.46  | 42.85  | 450.soplex         | 59.74  | 70.99  |
| 473.astar           | 32.60  | 32.11  | 453.povray         | 76.38  | 70.16  |
| 483.xalancbmk       | 83.46  | 93.14  | 454.Calculix       | 42.71  | 40.68  |
| GEOMEAN             | 53.86  | 57.38  | 459.GemsFDTD       | 74.24  | 78.50  |
|                     |        |        | 465.tonto          | 54.03  | 37.61  |
|                     |        |        | 470.lbm            | 128.16 | 146.27 |
|                     |        |        | 481.wrf            | 62.22  | 44.89  |
|                     |        |        | 482.sphinx3        | 60.91  | 63.62  |
|                     |        |        | GEOMEAN            | 65.94  | 63.51  |

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
