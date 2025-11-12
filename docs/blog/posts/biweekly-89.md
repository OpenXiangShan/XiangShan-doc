---
slug: biweekly-89
date: 2025-11-10
categories:
  - Biweekly
---

# 【香山双周报 89】20251110 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 89 期双周报。

香山开发方面，前端继续修复 BPU 重构带来的性能 bug~~希望下次双周报时性能能够达到重构前水平~~。后端推进 V3 向量单元的新设计实现，同时优化了 V2 后端的时序。访存持续推进 V3 各个模块的重构与测试，并且修复了一些 V2 功能 bug，优化了时序，提升了代码质量。

<!-- more -->

## 开发花絮
双核昆明湖 V2 成功在 FPGA 上以 50MHz 启动 GUI OpenEuler 24.03！我们还成功运行了 LibreOffice，并且来了一把~~激情四射~~的 DOOM！这标志着香山验证工作的一个里程碑，也给了我们更大的信心。

由于 FPGA 频率比较低，因此启动稍慢，还望大家耐心观看~

（由于 GitHub 的限制，请大家移步公众号观看）

~~请忽略画质问题，这是极为艺术的摇晃镜头~~

## 近期进展

### 前端

- RTL 新特性
  - 支持 RISC-V 特权手册 v1.13 引入的 Hardware Error 异常（[#4770](https://github.com/OpenXiangShan/XiangShan/pull/4770)）
  - 启用 UBTB 快速训练（[#5145](https://github.com/OpenXiangShan/XiangShan/pull/5145)）
  - 移除 UBTB 的 takenCnt 和 valid 域（[#5157](https://github.com/OpenXiangShan/XiangShan/pull/5157)）
  - 实现 SC 预测器的 globalTable（[#5150](https://github.com/OpenXiangShan/XiangShan/pull/5150)）
  - 支持 PHR 追踪分支 target（[#5169](https://github.com/OpenXiangShan/XiangShan/pull/5169)）
  - ABTB 快速恢复、MicroTAGE 等新性能特性探索中
  - Decoupled BPU train、commit 通路重构进行中
- Bug 修复
  - 修复 ABTB、MBTB SRAM 读出数据没有被寄存导致的 X 态传播问题（[#5153](https://github.com/OpenXiangShan/XiangShan/pull/5153), [#5158](https://github.com/OpenXiangShan/XiangShan/pull/5158)）
  - 修复 ABTB 训练条件相关问题（[#5160](https://github.com/OpenXiangShan/XiangShan/pull/5160)）
  - 修复 MBTB multi-hit 冲刷逻辑 waymask 非 one-hot 的问题（[#5181](https://github.com/OpenXiangShan/XiangShan/pull/5181)）
  - 修复 TAGE BaseTable、MBTB set 索引计算有误的问题（[#5155](https://github.com/OpenXiangShan/XiangShan/pull/5155)）
  - 修复 PHR 指针元数据错位相关问题（[#5139](https://github.com/OpenXiangShan/XiangShan/pull/5139)）
  - 修复 WriteBuffer 写端口连线相关问题（[#5143](https://github.com/OpenXiangShan/XiangShan/pull/5143)）
  - 修复 IBuffer 在入队项数量为 0 时仍然记录 exception 的问题（[#5147](https://github.com/OpenXiangShan/XiangShan/pull/5147)）
- 时序优化
  - （V2）更换 FTQ 的双端口 SRAM 为寄存器（[#5142](https://github.com/OpenXiangShan/XiangShan/pull/5142)）
- 面积优化
  - 支持 ICache WayLookup 仅存储上电/重定向后遇到的第一条 exception（[#4959](https://github.com/OpenXiangShan/XiangShan/pull/4959), [#5165](https://github.com/OpenXiangShan/XiangShan/pull/5165)）
- 代码质量
  - 重构 s1 预测器组的快速训练接口（[#5144](https://github.com/OpenXiangShan/XiangShan/pull/5144)）
  - 重构 MBTB alignBank，顺便修复了 bank 索引计算有误的问题（[#5159](https://github.com/OpenXiangShan/XiangShan/pull/5159)）

### 后端

- RTL 新特性
  - 正在推进 V3 向量单元的新设计实现
  - 支持 OpenSBI 的 PMU 扩展（[#5172](https://github.com/OpenXiangShan/XiangShan/pull/5172)）
  - 参数化设计 PMP 和 PMA（[#5177](https://github.com/OpenXiangShan/XiangShan/pull/5177)）
- 时序优化
  - 继续推进对 V2 向量运算单元时序的优化

### 访存与缓存

- RTL 新特性
  - MMU、LoadUnit、StoreQueue、L2 等模块重构与测试持续推进中
- Bug 修复
  - 修复 TLB 刷新逻辑错误的问题。在hfence.vvma、 sfence.vma 且 v=1、或者 mbmc.BME = 1 且 CMODE = 0 时忽略地址匹配，直接刷新所有 TLB 条目（[#5114](https://github.com/OpenXiangShan/XiangShan/pull/5114)）
  - 修复 VsegmentUnit 中拆分非对齐元素时没有锁存 Paddr 的 Bug。该 Bug 会导致错误发起访存请求（[#5164](https://github.com/OpenXiangShan/XiangShan/pull/5164)）
  - 修复 TLB 处于 onlyS2 阶段时 gpaddr 与 vaddr 不同的问题（[#5189](https://github.com/OpenXiangShan/XiangShan/pull/5189)）
- 时序
  - 修复了 PTW 的时序问题（[#5170](https://github.com/OpenXiangShan/XiangShan/pull/5170)）
  - 正在修复 LoadReplayQueue 以及 DCache 中的时序问题（[#5185](https://github.com/OpenXiangShan/XiangShan/pull/5185)）
- 代码质量
  - 将 beu 中的 IntBuffer 移动到 L2Top 以进行分区（[#5110](https://github.com/OpenXiangShan/XiangShan/pull/5110)）
  - 移除了顶层模块 XSCore 中所有的组合逻辑，仅保留连线逻辑（[#5120](https://github.com/OpenXiangShan/XiangShan/pull/5120)）
  - 对 PMP 与 PMA 进行参数化（[#5177](https://github.com/OpenXiangShan/XiangShan/pull/5177)）
- 调试工具
  - 在 DCache 与 LDU 中新增一些硬件性能计数器（[#5166](https://github.com/OpenXiangShan/XiangShan/pull/5166)）
  - 继续完善 CHI 相关基础设施 CHIron 的功能（[CHIron](https://github.com/RISMicroDevices/CHIron)）

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
