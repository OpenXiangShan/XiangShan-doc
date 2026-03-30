---
slug: biweekly-99
date: 2026-03-30
categories:
  - Biweekly
---

# 【香山双周报 99】20260330 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 99 期双周报。

昆明湖 V2 已经回片！目前正在进行紧张刺激的测试工作，更多的信息将在后续披露，敬请期待！

关于香山近期开发进展，前端修复了一些 BPU 的性能 bug，后端优化了部分模块的时序，访存继续进行模块的重构与测试。

<!-- more -->

## 前端 TAGE 分配策略 bug 定位与修复

不久前，某关注香山进展的神秘团队向我们反馈了一个性能 bug。他们在 FPGA 上运行昆明湖 V3 时发现， V3 的性能甚至不如 V2。经过简单的定位，在 libquantum 这个测试程序中，V3 的分支预测准确率随着运行时间的增加有着显著的下降，从而导致 IPC 下降。

收到这个反馈后，我们立即展开了复现与定位。~~其实最先怀疑的是环境问题，因为 V3 在我们的切片性能评估流程中一切正常，但最终证明各项配置均正确~~。这一现象在 FPGA 上执行 30 分钟后才较为显著，但 FPGA 上调试手段有限。然而，如果要在仿真环境中运行，需要至少一个月才能复现。因此，我们最终决定在 Palladium 上进行复现，折算过来需要运行约一天左右。

一天后，我们成功复现了这个问题，下图是 libquantum 测试程序中 IPC 随时间的变化曲线，可以看到 IPC 在运行一段时间后有明显的下降。

![IPC](./figs/biweekly-98/before_ipc.png)

而在众多性能计数器中，我们发现了 allocate_failure 这个计数器，它的变化趋势竟然与 IPC 的变化趋势高度相关！这个计数器统计了TAGE表项分配失败的次数，按照设计预期不应当有这么多。

![allocate_failure](./figs/biweekly-98/before_allocate.png)

经过定位，我们发现TAGE的分配条件有误，会导致已有表项无法被替换，从而导致新的分支训练不进TAGE。具体代码修改可以参考这个 [PR](https://github.com/OpenXiangShan/XiangShan/pull/5677)。修改后的 IPC 与 allocate_failure 的趋势如下图所示。

![IPC](./figs/biweekly-98/after_ipc.png)

![allocate_failure](./figs/biweekly-98/after_allocate.png)

多么漂亮的两个曲线！我们非常感谢这个神秘团队的持续关注与积极反馈，也欢迎更多关注香山的朋友与我们一起将香山越做越好。

## 近期进展

### 前端

- RTL 新特性
  - 实现 SC Backward 表（[#5528](https://github.com/OpenXiangShan/XiangShan/pull/5528)）
- Bug 修复
  - （V2）修复 IFU 处理 MMIO 空间取指，取指地址+32B 跨过页边界，仅后一页出现异常时，向后端发送全0指令的问题（[#5687](https://github.com/OpenXiangShan/XiangShan/pull/5687)）
- 代码质量
  - 重构分支历史寄存器（[#5528](https://github.com/OpenXiangShan/XiangShan/pull/5528)）
- 调试工具
  - 修复 Utility 中性能计数器编译问题（[#5740](https://github.com/OpenXiangShan/XiangShan/pull/5740)）

### 后端

- Bug 修复
  - 修复 commitInstrBranch 并添加 branch_jump 性能计数器（[#5705](https://github.com/OpenXiangShan/XiangShan/pull/#5705)）
- 时序优化
  - 移除从 commonOutBundle 引出的的 dataSource 信号，去除冗余依赖（[#5704](https://github.com/OpenXiangShan/XiangShan/pull/#5704)）
- 代码质量
  - 移除 CSR 单元内的无用寄存器（[#5681](https://github.com/OpenXiangShan/XiangShan/pull/#5681)）

### 访存与缓存

- RTL 新特性
  - MMU、L2 等模块重构与测试持续推进中
  - 新版 LoadUnit 与 StoreQueue 合入主线并修复若干相关的问题（[#5548](https://github.com/OpenXiangShan/XiangShan/pull/5548)）
- Bug 修复
  - （V2）修复了 Store MMIO 没有标记 Rob 的问题（[#5640](https://github.com/OpenXiangShan/XiangShan/pull/5640)）
  - （V2）修复了 MisalignBuffer 的撤销逻辑（[#5674](https://github.com/OpenXiangShan/XiangShan/pull/5674)）
  - （V2）修复了 Uncache 模块中 mem_acquire 未触发时的前递顺序冒险问题（[#5630](https://github.com/OpenXiangShan/XiangShan/pull/5630)）
  - （V2）在 L1Prefetcher 中使用单独的信号来控制 RegEnable PC（[#5720](https://github.com/OpenXiangShan/XiangShan/pull/5720)）
  - 修复了非对齐访问 MMIO 区域时发出的异常类型（[#5700](https://github.com/OpenXiangShan/XiangShan/pull/5700)）
- 时序修复
  - 修复了 MemBlock 若干时序问题（[#5697](https://github.com/OpenXiangShan/XiangShan/pull/5697)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 316946d28  |
| 日期      | 2026/02/11 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存延迟  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | GCC12  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  | GCC12  |
| :------------------ | :----: | :----: | :----: | :----------------- | :----: | :----: | :----: |
| 400.perlbench       | 47.62  | 46.95  | 43.70  | 410.bwaves         | 85.89  | 90.63  | 73.26  |
| 401.bzip2           | 27.11  | 27.84  | 27.45  | 416.gamess         | 56.09  | 52.32  | 55.07  |
| 403.gcc             | 51.16  | 37.45  | 48.58  | 433.milc           | 64.67  | 63.51  | 49.06  |
| 429.mcf             | 59.41  | 53.82  | 58.20  | 434.zeusmp         | 69.51  | 63.50  | 60.53  |
| 445.gobmk           | 35.73  | 36.86  | 37.72  | 435.gromacs        | 36.26  | 34.10  | 38.51  |
| 456.hmmer           | 52.74  | 62.74  | 42.84  | 436.cactusADM      | 75.29  | 86.48  | 53.73  |
| 458.sjeng           | 36.53  | 37.26  | 35.81  | 437.leslie3d       | 56.49  | 56.52  | 54.49  |
| 462.libquantum      | 135.14 | 293.38 | 133.96 | 444.namd           | 42.50  | 44.39  | 37.52  |
| 464.h264ref         | 62.14  | 70.50  | 62.67  | 447.dealII         | 63.78  | 68.00  | 65.01  |
| 471.omnetpp         | 40.96  | 39.01  | 43.05  | 450.soplex         | 48.91  | 57.65  | 52.82  |
| 473.astar           | 30.86  | 29.89  | 30.11  | 453.povray         | 72.61  | 66.92  | 61.73  |
| 483.xalancbmk       | 74.28  | 83.06  | 79.61  | 454.Calculix       | 44.12  | 39.19  | 19.43  |
| GEOMEAN             | 49.43  | 52.66  | 48.51  | 459.GemsFDTD       | 64.03  | 64.56  | 46.22  |
|                     |        |        |        | 465.tonto          | 51.74  | 34.81  | 36.76  |
|                     |        |        |        | 470.lbm            | 126.79 | 132.72 | 105.02 |
|                     |        |        |        | 481.wrf            | 55.19  | 41.29  | 48.79  |
|                     |        |        |        | 482.sphinx3        | 58.53  | 60.81  | 55.06  |
|                     |        |        |        | GEOMEAN            | 60.46  | 58.46  | 50.81  |

编译参数如下所示：

| 参数             | GCC12    | GCC15       | XSCC                |
| ---------------- | -------- | ----------- | ------------------- |
| 编译器           | gcc12    | gcc15       | xscc                |
| 编译优化         | O3       | O3          | O3                  |
| 内存库           | jemalloc | jemalloc    | jemalloc            |
| -march           | RV64GCB  | RV64GCB     | RV64GCB             |
| -ffp-contraction | fast     | fast        | fast                |
| 链接优化         | -        | -flto       | -flto               |
| 浮点优化         | -        | -ffast-math | -ffast-math         |
| -mcpu            | -        | -           | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
