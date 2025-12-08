---
slug: biweekly-91
date: 2025-12-08
categories:
  - Biweekly
---

# 【香山双周报 91】20251208 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 91 期双周报。

香山开发方面，前端在 V3 实现了一些新的性能特性，同时修复了多个 BPU 重构带来的性能 bug~~希望下次双周报时性能能够达到重构前水平（×2）~~。后端正在推进 V3 新向量单元的设计，V2 的 bug 修复，同时进行时序优化。访存新增了 berti 预取器，同时继续推动各个模块的代码重构，还修复了一些 V2 功能 bug。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 新增 UTAGE 预测器，作为 S1 预测器组的方向预测器，提供比 UBTB 和 ABTB 更精准的方向预测（[#5194](https://github.com/OpenXiangShan/XiangShan/pull/5194)）
  - 支持 UBTB 和 ABTB 预测分支位置比较，选择靠前的预测结果（[#5243](https://github.com/OpenXiangShan/XiangShan/pull/5243)）
  - 支持 MBTB 不训练 fallThrough 类型分支，减少容量浪费（[#5245](https://github.com/OpenXiangShan/XiangShan/pull/5245)）
  - 支持 MBTB 纠正 indirect 类型分支目标（[#5226](https://github.com/OpenXiangShan/XiangShan/pull/5226)）
  - 修改 MBTB replacer setIdx 选取位置（[#5260](https://github.com/OpenXiangShan/XiangShan/pull/5260)）
  - 对齐 TAGE 参数与 GEM5 一致（[#5261](https://github.com/OpenXiangShan/XiangShan/pull/5261)）
  - 修改 TAGE setIdx 和 bankIdx 选取位置（[#5294](https://github.com/OpenXiangShan/XiangShan/pull/5294)）
  - 修改 PHR Shamt 参数（[#5315](https://github.com/OpenXiangShan/XiangShan/pull/5315)）
  - 支持 commit 通路更新 RAS（[#5196](https://github.com/OpenXiangShan/XiangShan/pull/5196)）
- Bug 修复
  - 修复 ABTB 计数器更新逻辑（[#5266](https://github.com/OpenXiangShan/XiangShan/pull/5266)）
  - 修复 MBTB internalBank 写/写冲突的问题（[#5255](https://github.com/OpenXiangShan/XiangShan/pull/5255)）
  - 修复 MBTB replacer 更新逻辑错误的问题（[#5302](https://github.com/OpenXiangShan/XiangShan/pull/5302)）
  - 修复 TAGE 计数器初值（[#5252](https://github.com/OpenXiangShan/XiangShan/pull/5252)）
  - 修复 TAGE 分配逻辑（[#5254](https://github.com/OpenXiangShan/XiangShan/pull/5254)）
  - 修复 ITTAGE 训练数据错拍的问题（[#5244](https://github.com/OpenXiangShan/XiangShan/pull/5244)）
  - 修复 FTQ ResolveQueue 来自 BPU 和来自 Redirect 的冲刷互相冲突的问题（[#5273](https://github.com/OpenXiangShan/XiangShan/pull/5273)）
  - 修复 SRAMTemplate 编译期 warning（[#5276](https://github.com/OpenXiangShan/XiangShan/pull/5276)）
- 时序/面积优化
  - （V2）寄存 iPMP 读结果以修复 PMP 项数增大后的时序问题（[#5242](https://github.com/OpenXiangShan/XiangShan/pull/5242)）
- 代码质量
  - 移除 UBTB 冗余参数（[#5262](https://github.com/OpenXiangShan/XiangShan/pull/5262)）
  - 重构 ICache Meta/DataArray，修复参数化支持不完整的问题（[#5232](https://github.com/OpenXiangShan/XiangShan/pull/5232)）
  - 新增 AddrField 工具简化地址相关的索引计算逻辑，增加编译期日志便于调试，同时修复了 TAGE 一些 typo（[#5274](https://github.com/OpenXiangShan/XiangShan/pull/5274)，[#5295](https://github.com/OpenXiangShan/XiangShan/pull/5295)，[#5306](https://github.com/OpenXiangShan/XiangShan/pull/5306)）
- 调试工具
  - 修复 TAGE condTrace 工具参数使用错误的问题（[#5251](https://github.com/OpenXiangShan/XiangShan/pull/5251)）
  - 减少 TAGE condTrace 工具的冗余输出（[#5247](https://github.com/OpenXiangShan/XiangShan/pull/5247)）
  - 新增 TAGE bank 冲突相关性能计数器（[#5303](https://github.com/OpenXiangShan/XiangShan/pull/5303)）
  - 新增 WriteBuffer nameSuffix 参数，提高调试信息可读性（[#5277](https://github.com/OpenXiangShan/XiangShan/pull/5277)，[#5310](https://github.com/OpenXiangShan/XiangShan/pull/5310)）
  - 修复 predictionSource 性能计数器寄存器使能信号 typo（[#5271](https://github.com/OpenXiangShan/XiangShan/pull/5271)）
  - 新增 FTQ PerfQueue 用于分支预测性能分析（[#5304](https://github.com/OpenXiangShan/XiangShan/pull/5304)）

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
  - （V2）禁用了 LoadUnit ecc 生成的硬件错误（[#5285](https://github.com/OpenXiangShan/XiangShan/pull/5285)）
  - 将用于 beu 的 IntBuffer 移动到 L2Top 以进行分区（[#5110](https://github.com/OpenXiangShan/XiangShan/pull/5110)）
- Bug 修复
  - （V2）修复了非对齐 store 的边界情况（[#5233](https://github.com/OpenXiangShan/XiangShan/pull/5233)）
  - （V2）修复了 MemBlock 中生成 tilelink 错误异常的逻辑（[#5269](https://github.com/OpenXiangShan/XiangShan/pull/5269)）
  - （V2）修复了 MemBlock 中 misailgn 异常的优先级（[#5270](https://github.com/OpenXiangShan/XiangShan/pull/5270)）
  - 修复了 TLB 发生异常时错误的重填级别（[#5087](https://github.com/OpenXiangShan/XiangShan/pull/5087)）
  - 修复了 Bitmap 检查结果唤醒 l0BitmapReg 的逻辑（[#5073](https://github.com/OpenXiangShan/XiangShan/pull/5073)）
  - 在 hfence.vvma 或 sfence.vma 且 v = 1 时禁用地址匹配（[#5114](https://github.com/OpenXiangShan/XiangShan/pull/5114)）
  - 修复了 LoadMissalighBuffer 中 writeback 的端口连线
- 性能优化
  - 只向 L1DCache 发送一次 stream 预取请求（[#5224](https://github.com/OpenXiangShan/XiangShan/pull/5224)）
- 时序
  - （V2）移除了 TLBStorage 中的一些 RegEnable 以避免门控 （[#5229](https://github.com/OpenXiangShan/XiangShan/pull/5229)）
  - （V2）调整了 StoreUnit 中非对齐重发的逻辑（[#5207](https://github.com/OpenXiangShan/XiangShan/pull/5207)）
  - （V2）将 VSplit 中 vsta 与 vstd 的 valid 信号解耦（[#5208](https://github.com/OpenXiangShan/XiangShan/pull/5208)）
  - （V2）移除了 TLB 中由 need_gpa 引发的 ICG（[#5230](https://github.com/OpenXiangShan/XiangShan/pull/5230)）
  - （V2）优化了 StoreQueueData、MainPipe 与 MissQueue 的时序
  - （V2）修复了 CoupledL2 中从 Dir error 到 GrantBuffer 的关键路径（[CoupledL2 #448](https://github.com/OpenXiangShan/CoupledL2/pull/448)）
  - 优化了 pmp 检查、bitmap 与 PTW 的时序
- 代码质量
  - （V2）重命名了 MainPipe 中中间变量以提升可读性
- 构建工具
  - 禁用了 chisel7 将 assertion 文件放在不同层级文件夹的行为（[OenLLC #71](https://github.com/OpenXiangShan/OpenLLC/pull/71)）
- 调试工具
  - 在 tl-test-new 中支持了 L2ToL1Hint 检测（[tl-test-new #82](https://github.com/OpenXiangShan/tl-test-new/pull/82)）

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 36.13  | 410.bwaves       | 67.28  |
| 401.bzip2         | 25.39  | 416.gamess       | 40.98  |
| 403.gcc           | 47.97  | 433.milc         | 45.01  |
| 429.mcf           | 60.54  | 434.zeusmp       | 51.85  |
| 445.gobmk         | 30.29  | 435.gromacs      | 33.58  |
| 456.hmmer         | 41.60  | 436.cactusADM    | 46.22  |
| 458.sjeng         | 30.21  | 437.leslie3d     | 48.02  |
| 462.libquantum    | 122.60 | 444.namd         | 28.86  |
| 464.h264ref       | 56.59  | 447.dealII       | 73.54  |
| 471.omnetpp       | 41.73  | 450.soplex       | 52.53  |
| 473.astar         | 29.14  | 453.povray       | 53.41  |
| 483.xalancbmk     | 72.80  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.62  | 459.GemsFDTD     | 38.92  |
|                   |        | 465.tonto        | 36.69  |
|                   |        | 470.lbm          | 91.96  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 49.10  |
|                   |        | GEOMEAN          | 44.90  |

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
| commit    | d0adbd4    |
| 日期      | 2025/11/21 |
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
