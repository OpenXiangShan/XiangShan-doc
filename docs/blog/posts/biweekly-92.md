---
slug: biweekly-92
date: 2025-12-22
categories:
  - Biweekly
---

# 【香山双周报 92】20251222 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。

本次是第 92 期双周报。

昆明湖 V2 最后一次性能回归顺利完成！不知不觉间，我们已经累计完成了 46 次双周性能回归测试。这 46 次回归不仅记录了昆明湖 V2 的性能演进，也是香山处理器蓬勃发展和持续进步的有力见证。

![Performance Regression Results for XiangShan V2](./figs/performance-regression.png)

在过去四年里，香山处理器从一个校园课程项目逐步发展为工业级处理器。从一切开始的起点“雁栖湖”，到首次实现工业交付并已在多项目中投入使用的“南湖”，再到成为当前性能最高的开源处理器核“昆明湖 V2”——这三代香山的演进，不仅凝聚着每一位团队成员的努力，也离不开社区伙伴们的持续关注与大力支持。在此，向大家表示由衷的感谢！

现在，我们即将告别昆明湖 V2，迎接昆明湖 V3 的到来！V3 将具备比 V2 更强大的性能，这同时也意味着更大的挑战。在香山团队面前的是一片未知的领域，我们的每一步都在书写新的历史。但是，我们坚信，通过“开源”这一新理念、新方法，我们能够与整个社区共同前进，进一步提升开源处理器的性能标杆。

感谢大家对香山的陪伴与支持，也期待您继续关注昆明湖 V3 的后续进展！

香山开发方面，前端修复了~~无数~~ BPU 相关的性能 bug~~性能终于接近重构前的水平~~，同时添加了性能计数器，以便更好地进行性能分析。后端和访存修复了 V2 的数个 bug，并且进一步优化了时序。在 V3 方面，后端继续推进新向量单元的设计，访存进行了模块重构与测试，同时进行了预取性能探索。

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
  - 修复 CSR 唤醒的相关问题（[#5259](https://github.com/OpenXiangShan/XiangShan/pull/5259)）
  - 修复浮点除法、开方在流水线冲刷时非确定唤醒的相关问题（[YunSuan #5131](https://github.com/OpenXiangShan/YunSuan/pull/192)）
  - 进行寄存器堆读仲裁、唤醒性能 bug 等的修复
- 时序优化
  - 去除一处 BypassNetwork 内的门控（[#5291](https://github.com/OpenXiangShan/XiangShan/pull/5291/files)）

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
| 400.perlbench     | 36.18  | 410.bwaves       | 66.73  |
| 401.bzip2         | 25.46  | 416.gamess       | 40.99  |
| 403.gcc           | 48.00  | 433.milc         | 45.12  |
| 429.mcf           | 60.63  | 434.zeusmp       | 51.61  |
| 445.gobmk         | 30.32  | 435.gromacs      | 33.60  |
| 456.hmmer         | 41.62  | 436.cactusADM    | 46.19  |
| 458.sjeng         | 30.24  | 437.leslie3d     | 47.97  |
| 462.libquantum    | 122.43 | 444.namd         | 28.86  |
| 464.h264ref       | 56.58  | 447.dealII       | 73.55  |
| 471.omnetpp       | 41.77  | 450.soplex       | 52.50  |
| 473.astar         | 29.19  | 453.povray       | 53.46  |
| 483.xalancbmk     | 72.84  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.66  | 459.GemsFDTD     | 38.60  |
|                   |        | 465.tonto        | 36.66  |
|                   |        | 470.lbm          | 91.94  |
|                   |        | 481.wrf          | 40.70  |
|                   |        | 482.sphinx3      | 49.13  |
|                   |        | GEOMEAN          | 44.85  |

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
| commit    | f9daf7c15  |
| 日期      | 2025/12/08 |
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
