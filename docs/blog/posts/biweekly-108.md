---
slug: biweekly-108
date: 2026-08-03
categories:
  - Biweekly
---

# 【香山双周报 108】20260803 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 108 期双周报。

7 月 21 日，著名计算机专家毛德操老师到访开芯院，并为大家带来了题为《人工智能与处理器芯片》的讲座。

![毛德操老师讲座](./figs/biweekly-108/talk.jpg)

毛老师与香山的缘分不止于此，他还撰写过《RISC-V CPU 芯片设计：香山源代码剖析》。这本书是毛老师在76岁（2021年），自己 1 个人，时常工作近 10 小时/天，花费 3.5 年的时间著作而成。成书时，毛老师已经79岁。

香山的核心团队也与毛老师进行了深入交流，听取毛老师多年来对产业界的深刻见解和宝贵经验。毛老师能够认同香山的设计理念，这让我们感到非常荣幸，我们也将继续努力，将香山越做越好，成为开源处理器领域的标杆。

关于香山近期开发进展，前端继续优化时序；后端修复了 V2 的一些 bug，同时校准了 topdown 计数器；访存与缓存实现了双通道 TileLink 总线，并对 LSU 进行了优化；XSAI 更新了 AME 版本，同时修复了若干 bug。

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
| commit    | a97570144  |
| 日期      | 2026/07/30 |
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
| 400.perlbench       | 51.92  | 52.22  | 410.bwaves         | 121.09 | 105.65 |
| 401.bzip2           | 30.04  | 30.58  | 416.gamess         | 58.30  | 55.84  |
| 403.gcc             | 56.24  | 39.91  | 433.milc           | 71.21  | 68.92  |
| 429.mcf             | 71.32  | 63.98  | 434.zeusmp         | 78.07  | 67.87  |
| 445.gobmk           | 39.95  | 40.49  | 435.gromacs        | 38.27  | 35.16  |
| 456.hmmer           | 55.24  | 67.00  | 436.cactusADM      | 80.70  | 93.11  |
| 458.sjeng           | 39.44  | 40.73  | 437.leslie3d       | 60.88  | 61.17  |
| 462.libquantum      | 138.63 | 305.37 | 444.namd           | 43.07  | 45.22  |
| 464.h264ref         | 69.80  | 74.93  | 447.dealII         | 74.36  | 74.52  |
| 471.omnetpp         | 43.60  | 42.84  | 450.soplex         | 60.07  | 71.35  |
| 473.astar           | 32.74  | 32.28  | 453.povray         | 76.41  | 72.29  |
| 483.xalancbmk       | 83.75  | 93.51  | 454.Calculix       | 42.73  | 40.73  |
| GEOMEAN             | 54.11  | 57.60  | 459.GemsFDTD       | 72.22  | 73.41  |
|                     |        |        | 465.tonto          | 54.18  | 37.50  |
|                     |        |        | 470.lbm            | 128.82 | 146.74 |
|                     |        |        | 481.wrf            | 61.76  | 45.03  |
|                     |        |        | 482.sphinx3        | 61.01  | 63.57  |
|                     |        |        | GEOMEAN            | 66.11  | 63.57  |

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
