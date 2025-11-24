---
slug: biweekly-90
date: 2025-11-24
categories:
  - Biweekly
---

# 【香山双周报 90】20251124 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 90 期双周报。

香山开发方面，前端继续修复 BPU 重构带来的性能 bug~~希望下次双周报时性能能够达到重构前水平~~。后端继续稳推进 bug 修复和新功能开发。访存持续推进 V3 各个模块的重构与测试，并且修复了一些 V2 功能 bug，优化了时序，提升了代码质量。

<!-- more -->

## 开发花絮
双核昆明湖 V2 成功在 FPGA 上以 50MHz 启动 GUI OpenEuler 24.03！我们还成功运行了 LibreOffice，并且来了一把~~激情四射~~的 DOOM！这标志着香山验证工作的一个里程碑，也给了我们更大的信心。

由于 FPGA 频率比较低，因此启动稍慢，还望大家耐心观看~

（由于 GitHub 的限制，请大家移步公众号观看）

~~请忽略画质问题，这是极为艺术的摇晃镜头~~

## 近期进展

### 前端

- RTL 新特性
  - 支持 BPU 训练反压 Ftq Resolve Queue，避免读写冲突时训练数据丢弃（[#5148](https://github.com/OpenXiangShan/XiangShan/pull/5148)）
  - 修改 PHR 哈希逻辑（[#5209](https://github.com/OpenXiangShan/XiangShan/pull/5209)）
- Bug 修复
  - 修复 ABTB 在阻塞时输出失效的问题（[#5197](https://github.com/OpenXiangShan/XiangShan/pull/5197)）
  - 修复 TAGE 主表的若干问题，启用主表（[#5156](https://github.com/OpenXiangShan/XiangShan/pull/5156)）
  - 修复 ITTAGE 训练索引非 one-hot 导致的 assertion fail（[#5184](https://github.com/OpenXiangShan/XiangShan/pull/5184)）
  - 修复 FTQ ResolveQueue 未被 redirect 正确冲刷的问题（[#5149](https://github.com/OpenXiangShan/XiangShan/pull/5149)，[#5238](https://github.com/OpenXiangShan/XiangShan/pull/5238)）
  - 修复 FTQ ResolveQueue 项滞留过久导致 BPU 新预测结果已经覆盖原始 FTQ 项，进而导致 BPU 训练错误的问题（[#5225](https://github.com/OpenXiangShan/XiangShan/pull/5225)）
  - 修复 FTQ bpTrainStallCnt 位宽有误的问题（[#5201](https://github.com/OpenXiangShan/XiangShan/pull/5201)）
- 时序/面积优化
  - 移除 ICache Meta/DataArray 的 SRAMTemplate 中冗余的 holdRead 参数，同时优化时序和面积（[#5186](https://github.com/OpenXiangShan/XiangShan/pull/5186)）
- 代码质量
  - 移除去除跨页取指支持后冗余的 ipmp/itlb 端口（[#5213](https://github.com/OpenXiangShan/XiangShan/pull/5213)）
  - 重构 TAGE BaseTable alignBank，顺便修复了 bank 索引计算有误的问题（[#5162](https://github.com/OpenXiangShan/XiangShan/pull/5162)）
  - 重构 VecRotate 逻辑（[#5218](https://github.com/OpenXiangShan/XiangShan/pull/5218)）
- 调试工具
  - 新增 Tage Trace DB（[#5219](https://github.com/OpenXiangShan/XiangShan/pull/5219)）
  - 新增大量软件仿真性能计数器（[#5187](https://github.com/OpenXiangShan/XiangShan/pull/5187)）

### 后端

- RTL 新特性
  - 正在推进 V3 向量单元的新设计实现
  - 为顶层 debug 模块添加每个 traceGroup 的有效标志，以及 mstatus 寄存器的跟踪支持（[#5146](https://github.com/OpenXiangShan/XiangShan/pull/5146)）
- Bug 修复
  - 修复 nmi 寄存器 gating 相关问题（[#5067](https://github.com/OpenXiangShan/XiangShan/pull/5067)[#5215](https://github.com/OpenXiangShan/XiangShan/pull/5215)）
  - 拒绝 xip 类 CSR 的乱序读取（[#5131](https://github.com/OpenXiangShan/XiangShan/pull/5131)）
  - 正在修复对 oldVd 的错误依赖、ROB 压缩等等问题
- 代码质量
  - 进行 V3 后段代码的质量优化，删除部分冗余代码，修改一些代码风格，进行部分重命名（[#5135](https://github.com/OpenXiangShan/XiangShan/pull/5135)）
- 时序优化
  - 推进对向量 reduction、Regfile 等单元的评估与优化

### 访存与缓存

- RTL 新特性
  - （V2）为 TLB 添加 pmu 性能事件（[#5205](https://github.com/OpenXiangShan/XiangShan/pull/5205)）
  - （V2）为 CoupledL2 添加了一些性能事件（[CoupledL2 #437](https://github.com/OpenXiangShan/CoupledL2/pull/437)，[CoupledL2 #441](https://github.com/OpenXiangShan/CoupledL2/pull/441)）
  - 新增 berti 预取器（[#5049](https://github.com/OpenXiangShan/XiangShan/pull/5049)）
  - 调整了 MemBlock 中发射与写回的端口（[#5167](https://github.com/OpenXiangShan/XiangShan/pull/5167)）
  - MMU、LoadUnit、StoreQueue、L2 等模块重构与测试持续推进中
- Bug 修复
  - （V2）修复了 MXR 有效时 PMM 没有被禁用的问题（[#4997](https://github.com/OpenXiangShan/XiangShan/pull/4997)）
  - （V2）修复了 DCache 转发 corrupt 状态时时序不匹配的问题（[#5228](https://github.com/OpenXiangShan/XiangShan/pull/5228)）
  - （V2）添加使能位来决定是否检查 KeyID（[#5241](https://github.com/OpenXiangShan/XiangShan/pull/5241)）
  - （V2）修复了 CoupledL2 中将 SnpUnique 错误译码为 SnpPreferUnique 的问题（[CoupledL2 #438](https://github.com/OpenXiangShan/CoupledL2/pull/438)）
  - （V2）在 CoupledL2 中添加 l-credit 管理器以修复性能（[CoupledL2 #433](https://github.com/OpenXiangShan/CoupledL2/pull/433)）
- 时序
  - （V2）简化了 CoupledL2 中 RXSNP 端口的 CMO 请求，并将 RXRSP 与 RXDAT 流水化（[CoupledL2 #436](https://github.com/OpenXiangShan/CoupledL2/pull/436)）

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.82  | 410.bwaves       | 67.23  |
| 401.bzip2         | 25.40  | 416.gamess       | 40.96  |
| 403.gcc           | 47.81  | 433.milc         | 45.06  |
| 429.mcf           | 60.26  | 434.zeusmp       | 51.80  |
| 445.gobmk         | 30.24  | 435.gromacs      | 33.58  |
| 456.hmmer         | 41.60  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.35  | 437.leslie3d     | 47.88  |
| 462.libquantum    | 122.66 | 444.namd         | 28.86  |
| 464.h264ref       | 56.55  | 447.dealII       | 73.57  |
| 471.omnetpp       | 41.43  | 450.soplex       | 52.49  |
| 473.astar         | 29.12  | 453.povray       | 53.44  |
| 483.xalancbmk     | 72.71  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.54  | 459.GemsFDTD     | 39.73  |
|                   |        | 465.tonto        | 36.65  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.65  |
|                   |        | 482.sphinx3      | 49.09  |
|                   |        | GEOMEAN          | 44.94  |

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
| commit    | 1e9f1b4    |
| 日期      | 2025/11/07 |
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
