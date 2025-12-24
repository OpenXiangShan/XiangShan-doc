---
slug: biweekly-92
date: 2025-12-22
categories:
  - Biweekly
---

# 【香山双周报 92】20251222 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。

本次是第 92 期双周报。

在 2025 年的最后一期双周报里，我们将首次公布目前昆明湖 V3 架构在 SPEC CPU2006 上的性能评估结果！昆明湖 V3 自今年 8 月启动性能回归以来，已经完成了 11 次性能回归。这 11 次性能回归见证了香山团队齐心协力，对设计进行快速开发迭代的过程。昆明湖 V3 的最初版本在 SPEC 2006 测试中只有 3.717 分/GHz。现在，在最新一次性能回归中，V3 已经达到了 16.081 分/GHz，超过了 V2 的分数。V3 也已替代 V2 成为了香山仓库的新主线！

![Performance Regression Results for XiangShan Kunminghu](./figs/performance-regression.png)

在这一过程中，~~前端毫无疑问背了最大的锅~~最大的变化是 V3 的全新前端。新的前端大幅提高了指令带宽，现在每周期最多可预测 8 条分支、提供 32 条指令。同时，后端与访存也相应拉大了吞吐能力，包括从 6 发射提升至 8 发射、调整各个队列大小等。

值得注意的是，V3 性能数据的变化曲线，正是香山团队敏捷开发理念的生动体现。和传统瀑布式开发流程不同，V3 的开发并非一蹴而就、一次性交付全部代码，而是在初始代码的基础上快速迭代、持续演进的结果。我们相信，这一新的理念将为业界带来新的开发范式，也一定能够推动昆明湖 V3 迈上新的台阶，进一步提升开源处理器的性能标杆。

感谢大家对香山的陪伴与支持，也期待您继续关注昆明湖 V3 的后续进展！

香山开发方面，前端修复了一些 BPU 相关的性能 bug，同时添加了大量性能计数器，以便更好地进行性能分析。后端继续推进新向量单元的设计。访存修复了 V2 的数个 bug，同时继续进行了 V3 模块重构与基础设施搭建。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 减少 TAGE 计数器饱和时的 SRAM 写请求，从而减少 SRAM 端口冲突导致的阻塞（[#5309](https://github.com/OpenXiangShan/XiangShan/pull/5309)）
  - 对齐 TAGE 预测生成逻辑和 GEM5 一致（[#5377](https://github.com/OpenXiangShan/XiangShan/pull/5377)）
  - 实现 SC bias 表（[#5234](https://github.com/OpenXiangShan/XiangShan/pull/5234)）
  - 实现 ITTAGE 预测 call 类型分支（[#5311](https://github.com/OpenXiangShan/XiangShan/pull/5311)）
- Bug 修复
  - 修复 BPU 训练中，分支地址（cfiPc）和预测块地址（startPc）命名不明确导致的混用误用问题（[#5317](https://github.com/OpenXiangShan/XiangShan/pull/5317)）
  - 修复 UBTB 训练流水级命中判断条件，避免错误更新 replacer（[#5326](https://github.com/OpenXiangShan/XiangShan/pull/5326)）
  - 修复 TAGE 折叠历史信号的宽度笔误（[#5325](https://github.com/OpenXiangShan/XiangShan/pull/5325)）
  - 修复 TAGE cfiPc 笔误（[#5345](https://github.com/OpenXiangShan/XiangShan/pull/5345)）
  - 修复 RAS 一些笔误，启用 RAS（[#5321](https://github.com/OpenXiangShan/XiangShan/pull/5321)）
  - 修复 FTQ resolveQueue bpu enqueue 冲刷逻辑错误的问题（[#5344](https://github.com/OpenXiangShan/XiangShan/pull/5344)）
- 时序/面积优化
  - 将 TAGE BaseTable 挪到 MBTB 中，使计数器的分配和 MBTB 项同步，减少冗余存储（[#5349](https://github.com/OpenXiangShan/XiangShan/pull/5349)）
- 代码质量
  - 统一 BPU 内 pc 相关信号的命名（[#5318](https://github.com/OpenXiangShan/XiangShan/pull/5318)）
  - 新增一些 utility 方法以批量生成具有相似前缀的性能计数器（[#5298](https://github.com/OpenXiangShan/XiangShan/pull/5298)）
- 调试工具
  - 各模块新增和修复大量性能计数器（[#5320](https://github.com/OpenXiangShan/XiangShan/pull/5320)，[#5265](https://github.com/OpenXiangShan/XiangShan/pull/5265)，[#5319](https://github.com/OpenXiangShan/XiangShan/pull/5319)，[#5332](https://github.com/OpenXiangShan/XiangShan/pull/5332)，[#5339](https://github.com/OpenXiangShan/XiangShan/pull/5339)，[#5347](https://github.com/OpenXiangShan/XiangShan/pull/5347)，[#5353](https://github.com/OpenXiangShan/XiangShan/pull/5353)，[#5370](https://github.com/OpenXiangShan/XiangShan/pull/5370)，[#5383](https://github.com/OpenXiangShan/XiangShan/pull/5383)，[#5372](https://github.com/OpenXiangShan/XiangShan/pull/5372)）
  - 优化 TAGE Trace 的分支实际地址计算逻辑，考虑压缩指令（[#5355](https://github.com/OpenXiangShan/XiangShan/pull/5355)）

### 后端

- RTL 新特性
  - 正在推进 V3 向量单元的新设计实现
- Bug 修复
  - 修复后端 TopDown 接口连接问题（[#5340](https://github.com/OpenXiangShan/XiangShan/pull/5340)）
  - 修改 mvendorid 的值（[#5367](https://github.com/OpenXiangShan/XiangShan/pull/5367)）
  - 修复 Dispatch 的流水线阻塞周期统计问题（[#5398](https://github.com/OpenXiangShan/XiangShan/pull/5398)）
- 代码优化
  - 让 srcLoadDependencyUpdate 的连接更易读（[#5404](https://github.com/OpenXiangShan/XiangShan/pull/5404)）
- 其他
  - 更新后端的代码维护者名单（[#5342](https://github.com/OpenXiangShan/XiangShan/pull/5342)）

### 访存与缓存

- RTL 新特性
  - （V2）支持在 CoupledL2 中通过参数关闭 ClockGate（[CoupledL2 #451](https://github.com/OpenXiangShan/CoupledL2/pull/451)）
  - （V2）将 CoupledL2 MMIOBridge 的 TIMERange 参数化（[CoupledL2 #453](https://github.com/OpenXiangShan/CoupledL2/pull/451)）
  - MMU、LoadUnit、StoreQueue、L2 等模块重构与测试持续推进中
- Bug 修复
  - （V2）修复了 LoadQueueReplay 中 load 请求无法被正确唤醒的问题（[#5327](https://github.com/OpenXiangShan/XiangShan/pull/5327)）
  - （V2）修复了 LoadQueueRAW 中 storeIn.wlineflag 没有延迟一周期的问题（[#5352](https://github.com/OpenXiangShan/XiangShan/pull/5352)）
  - （V2）修复了 L1StreamPrefetcher 的深度（[#5365](https://github.com/OpenXiangShan/XiangShan/pull/5365)）
  - （V2）移除了 L2Top 与 MemBlock 中部分 RegNext(hartid)（[#5408](https://github.com/OpenXiangShan/XiangShan/pull/5408)）
  - （V2）修复了 TXDAT 中错误的 DataCheck 逻辑（[CoupledL2 #455](https://github.com/OpenXiangShan/CoupledL2/pull/455)）
  - （V2）修复了 l2MissMatch IO 的编译错误（[CoupledL2 #456](https://github.com/OpenXiangShan/CoupledL2/pull/456)）
- 性能优化
  - （V2）将 uncachebuffer 的容量从 4 增加至 16（[#5364](https://github.com/OpenXiangShan/XiangShan/pull/5364)）
  - 为 LoadUnit 添加了 PerfCCT 支持（[#5286](https://github.com/OpenXiangShan/XiangShan/pull/5286)）
- 时序
  - （V2）调整了 LoadUnit 中 s0 source 的仲裁顺序（[#5300](https://github.com/OpenXiangShan/XiangShan/pull/5300)）
  - （V2）优化了 VSegmentUnit、exceptionBuffer 的时序（[#5330](https://github.com/OpenXiangShan/XiangShan/pull/5330)，[#5292](https://github.com/OpenXiangShan/XiangShan/pull/5292)）
  - （V2）移除了 Sbuffer 中 store 预取的 IO 端口（[#5329](https://github.com/OpenXiangShan/XiangShan/pull/5329)）
  - （V2）移除了 MemBlock 中 TLB 生成 paddr 时非必要的 Mux（[#5331](https://github.com/OpenXiangShan/XiangShan/pull/5331)）
  - （V2）将 BitmapCache 从寄存器替换为 SRAM（[#5346](https://github.com/OpenXiangShan/XiangShan/pull/5346)）
- 调试工具
  - 在 tl-test-new 中支持输出性能计数器（[tl-test-new #84](https://github.com/OpenXiangShan/tl-test-new/pull/84)）
  - 在 NEMU 中支持在 check_paddr 失败时输出详细信息（[NEMU #867](https://github.com/OpenXiangShan/NEMU/pull/867)）
  - 持续改进 CHI 基础设施 CHIron
  - 开发用于新版 L2 Cache 的验证工具 CHI Test。持续推进中
  - 改进了 L2 Topdown Monitor 中统计的预取信息（[CoupledL2 #452](https://github.com/OpenXiangShan/CoupledL2/pull/452)）

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 36.71  | 410.bwaves       | 73.92  |
| 401.bzip2         | 27.45  | 416.gamess       | 54.70  |
| 403.gcc           | 42.71  | 433.milc         | 45.12  |
| 429.mcf           | 59.65  | 434.zeusmp       | 60.17  |
| 445.gobmk         | 35.10  | 435.gromacs      | 38.47  |
| 456.hmmer         | 44.18  | 436.cactusADM    | 54.20  |
| 458.sjeng         | 32.30  | 437.leslie3d     | 52.85  |
| 462.libquantum    | 107.84 | 444.namd         | 37.91  |
| 464.h264ref       | 61.89  | 447.dealII       | 61.38  |
| 471.omnetpp       | 43.56  | 450.soplex       | 54.62  |
| 473.astar         | 30.43  | 453.povray       | 56.90  |
| 483.xalancbmk     | 75.89  | 454.Calculix     | 19.18  |
| GEOMEAN           | 45.85  | 459.GemsFDTD     | 44.14  |
|                   |        | 465.tonto        | 36.35  |
|                   |        | 470.lbm          | 93.88  |
|                   |        | 481.wrf          | 48.77  |
|                   |        | 482.sphinx3      | 56.20  |
|                   |        | GEOMEAN          | 49.72  |

我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

编译参数如下所示：

|                  |          |
| ---------------- | -------- |
| 编译器           | gcc12    |
| 编译优化         | O3       |
| 内存库           | jemalloc |
| -march           | RV64GCB  |
| -ffp-contraction | fast     |

处理器及 SoC 参数如下所示：

|           |            |
| --------- | ---------- |
| commit    | 64e7bff7f  |
| 日期      | 2025/12/19 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | TileLink   |
| 内存延迟  | DDR4-3200  |

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
