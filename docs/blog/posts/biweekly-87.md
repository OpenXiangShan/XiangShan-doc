---
slug: biweekly-87
date: 2025-10-13
categories:
  - Biweekly
---

# 【香山双周报 87】20251013 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 87 期双周报。

在过去的两周，~~香山团队的大家度过了一个愉快的国庆假期~~前端继续修复 V3 BPU 重构后带来的性能 bug。后端整理现有代码，继续推进 V3 开发。访存缓存部分修复了数个 V2 的 bug，同时进行代码重构工作，为 V3 开发做准备。

同时向大家预告一则消息，香山团队将于 10 月 19 日在 MICRO 2025 会议上作 tutorial，我们非常期待与大家在首尔相见！

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 移除 identifiedCfi （[#5025](https://github.com/OpenXiangShan/XiangShan/pull/5025)）
  - 合入 V3 SC 框架（[#5062](https://github.com/OpenXiangShan/XiangShan/pull/5062)，[#5097](https://github.com/OpenXiangShan/XiangShan/pull/5097)）
  - 支持 WriteBuffer 多端口写入（[#5081](https://github.com/OpenXiangShan/XiangShan/pull/5081)）
  - 优化 V3 ITTAGE，接入 WriteBuffer，支持 resolve 训练（[#5099](https://github.com/OpenXiangShan/XiangShan/pull/5099)）
- Bug 修复
  - 修复 BPU fallthrough 预测时 cfiPosition 域有误的问题（[#5058](https://github.com/OpenXiangShan/XiangShan/pull/5058)）
  - 修复 TAGE 若干笔误（[#5086](https://github.com/OpenXiangShan/XiangShan/pull/5086)，[#5090](https://github.com/OpenXiangShan/XiangShan/pull/5090)）
  - 修复 MBTB 若干笔误（[#5096](https://github.com/OpenXiangShan/XiangShan/pull/5096)）
  - 修复 FTQ resolve queue 未被 redirect 冲刷导致 meta SRAM 读写冲突的问题（[#5085](https://github.com/OpenXiangShan/XiangShan/pull/5085)，[#5104](https://github.com/OpenXiangShan/XiangShan/pull/5104)）
  - 移除 FTQ-后端接口中 newest target 逻辑（[#5101](https://github.com/OpenXiangShan/XiangShan/pull/5101)）
  - 修复 ICache WayLookup 读写冲突断言条件有误的问题（[#5082](https://github.com/OpenXiangShan/XiangShan/pull/5082)）
  - 修复 Direct 类型分支被 IFU 修正，导致后端 JumpUnit 认为没有误预测，进而导致 BPU 无法训练的问题（[#5103](https://github.com/OpenXiangShan/XiangShan/pull/5103)）
- 代码质量
  - 重构 BPU first taken branch 选择逻辑，换用 CompareMatrix 类（[#5075](https://github.com/OpenXiangShan/XiangShan/pull/5075)）
  - 修复 FTQ resolve queue 分支索引计算从 1 开始的问题（[#5092](https://github.com/OpenXiangShan/XiangShan/pull/5092)）
  - 重构 IFU MMIO 取指处理逻辑（[#5021](https://github.com/OpenXiangShan/XiangShan/pull/5021)）
  - 重构 IFU redirect 端口，将仲裁逻辑从 FTQ 挪到 IFU（[#5064](https://github.com/OpenXiangShan/XiangShan/pull/5064)）
- 调试工具
  - 新增 BpTrace 及相关分析脚本（[#5091](https://github.com/OpenXiangShan/XiangShan/pull/5091)）

### 后端

- Bug 修复
  - 修复了当 ROB 压缩关闭时，跨两个 FTQ 的融合指令不可压缩的问题（[#5079](https://github.com/OpenXiangShan/XiangShan/pull/5079)）
- RTL 新特性
  - 在 ALU 中添加 jalr/jal/auipc 的新 uop 拆分实现
- 代码质量
  - 优化 NewMgu 中 vialuf 的时序（[#5078](https://github.com/OpenXiangShan/XiangShan/pull/5078)）

### 访存与缓存

- Bug 修复
  - （V2）修复发生异常时 TLB 层级重填错误、将大页错误记录为小页的问题（[#5087](https://github.com/OpenXiangShan/XiangShan/pull/5087)）
  - （V2）修复位图检查唤醒 l0BitmapReg 逻辑的问题（[#5073](https://github.com/OpenXiangShan/XiangShan/pull/5073)）
  - 将 NEMU 的 PMEMBASE 移至更高的地址空间，以防止在 mmap 以 MAP_FIXED 模式映射时发生冲突。未来可能会进一步消除对 MAP_FIXED 的依赖（[NEMU #930](https://github.com/OpenXiangShan/NEMU/pull/930)）
- 时序优化
  - 旧版 MMU、LoadQueueReplay 时序修复进行中
- RTL 新特性
  - MMU、LoadUnit、StoreQueue、L2 等模块重构持续推进中
  - L1 Acquire 时获取路信息以在 Release 时省去读目录获得路数的过程。正在修复 Bug

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.87  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.87  | 433.milc         | 45.07  |
| 429.mcf           | 60.18  | 434.zeusmp       | 51.83  |
| 445.gobmk         | 30.62  | 435.gromacs      | 33.65  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.87  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.82  |
| 471.omnetpp       | 41.41  | 450.soplex       | 52.48  |
| 473.astar         | 29.30  | 453.povray       | 53.50  |
| 483.xalancbmk     | 72.81  | 454.Calculix     | 16.38  |
| GEOMEAN           | 44.66  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 49.13  |
|                   |        | GEOMEAN          | 44.96  |

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
| commit    | defcc01    |
| 日期      | 2025/10/10 |
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
