---
slug: biweekly-89
date: 2025-11-10
categories:
  - Biweekly
---

# 【香山双周报 89】20251110 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 89 期双周报。

香山成功举办了 MICRO 2025 tutorial！我们非常高兴能与大家在首尔相见，感谢每一位参会的朋友和关心香山发展的伙伴们！如果未能现场参与，欢迎大家访问 <https://tutorial.xiangshan.cc/micro25/> 回顾本次 tutorial 的内容。香山的下一场 tutorial 将于明年初在澳大利亚举办的 HPCA 2026 会议上进行，期待与大家再次相见！

在此次 tutorial 中，我们进行了大规模的重构，主要包括：

- 完全重构的上手环节。新的上手环节使用 Jupyter Notebook 组织，进一步降低了解香山的门槛。所有内容都已开源到 <https://github.com/OpenXiangShan/bootcamp>，欢迎大家尝试
- 完全重构的微架构介绍。相比于扁平化地介绍香山微架构现状，新的微架构部分着重介绍香山的设计哲学，帮助大家更好地理解香山的设计思路
- 非常荣幸地邀请到 Nisa Bostanci 代表 Onur Mutlu 教授的团队分享 Ramulator！香山的 GEM5 模拟器现已集成 Ramulator

香山开发方面，前端修复数个 V3 BPU 重构后带来的性能 bug，同时推进取指侧对 2-fetch 的支持。后端继续进行 V3 开发与重构。访存完善了一部分 topdown PMU 与 CHIron 工具。

<!-- more -->

## Tutorial 花絮
- 合影镇楼

  ![合影镇楼](./figs/micro2025-tutorial/group-photo.png)
- 10 月 17 日清晨 5:28，Mutlu 教授回复了我们的邀请，确认将出席并介绍 Ramulator

  ![Mutlu 教授](./figs/micro2025-tutorial/professor-mutlu.png)
- 10 月 18 日晚，香山团队的同学在烤肉店修改 GEM5 部分的上手代码

  ![DDL 是第一生产力](./figs/micro2025-tutorial/ddl.png)
- 10 月 19 日，tutorial 于上午 8:00 准时开始。由于时间较早，一开始参加的人数并不多~~早八还是太超模了，看来大家都起不来~~。随着 tutorial 的进行，现场人数逐渐增多，最终坐满了整个屋子

  ![会场座无虚席](./figs/micro2025-tutorial/full-house.jpg)
- ![香山 30 年](./figs/micro2025-tutorial/xiangshan-30years.png)

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

- Bug 修复
  - 修复特定情况下 CSR 中 XIP 寄存器乱序读取造成的错误 （[#5131](https://github.com/OpenXiangShan/XiangShan/pull/5131)）
- RTL 新特性
  - 实现在 IQ 出口对直接跳转指令拆分 uop 的方案（[#5128](https://github.com/OpenXiangShan/XiangShan/pull/5128)）
  - 将浮点物理寄存器增加到 256，robSize 和 rabSize 增加到 352
  - 新增 Vmove 功能单元，将需要搬数据的指令 uop 拆分修改为使用 Vmove 单元（[#5126](https://github.com/OpenXiangShan/XiangShan/pull/5126)）
- 时序优化
  - 改善 vfcvt 的时序以支持向量单元的快速唤醒（[YunSuan #189](https://github.com/OpenXiangShan/YunSuan/pull/189)）
  - 完成 vialu 的重构以支持向量单元的快速唤醒（[#5136](https://github.com/OpenXiangShan/XiangShan/pull/5136)）
- 代码质量
  - 修改近期代码遗留问题，提升代码质量（[#5135](https://github.com/OpenXiangShan/XiangShan/pull/5135)）

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
| commit    | 0fb84f8    |
| 日期      | 2025/10/23 |
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
