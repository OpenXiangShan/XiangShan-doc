---
slug: biweekly-103
date: 2026-05-25
categories:
  - Biweekly
---

# 【香山双周报 103】20260525 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 103 期双周报。

基于香山昆明湖 V2 二次开发的进迭时空第三代高性能 RISC-V 处理器核 X200 研发完成！X200 在传统云计算处理器核的基础上，面向云端 Agent 应用与旗舰级终端 Agent 应用进行了针对性优化，SPECInt 2006 性能达到 16.0 分/GHz，单核频率可达 3.3GHz；相比 X100，单位性能提升 100% 以上，达到 SPECint 2006 50 分/Core。

相比使用了昆明湖 V2，更让我们高兴的是 X200 的研究过程中使用了全套的香山开源基础设施，这是支撑 X200 走向可量产状态的冰山水面下部分。这些开源工具链极大加速了 X200 二次开发的效率，为 X200 的质量提供了有力保障。

关于香山近期开发进展，前端在优化时序的同时进行 2-fetch 实现；后端和访存修复了一些功能 bug，并继续推进新版 L2 的设计；XSAI 为矩阵模块添加了 FP8 支持，同时优化了代码质量和评估工具。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 支持当 BPU 长期预测正确时，丢弃 resolve 请求，从而在降低 BPU 读冲突的同时减少功耗（[#5759](https://github.com/OpenXiangShan/XiangShan/pull/5759)）
- Bug 修复
  - 从后端直接获得排空状态，修复特定情况下 MMIO 取指卡死的问题（[#5787](https://github.com/OpenXiangShan/XiangShan/pull/5787)）
  - 修复 IFU 处理紧贴页边界的 RVC 指令，出现非法指令以外的异常时未正确发送到后端的问题（[#5959](https://github.com/OpenXiangShan/XiangShan/pull/5959)）
  - 修复 ICache `s1_itlbPbmt` 寄存器位宽不正确的问题（[#5962](https://github.com/OpenXiangShan/XiangShan/pull/5962)）
  - 修复 IFU 在处理跨过 MMIO-cacheable 边界的 RVI 指令时，指令拼接及元数据选择有误的问题（[#5985](https://github.com/OpenXiangShan/XiangShan/pull/5985)）
- PPA 优化
  - 调整 UBTB、ABTB、UTAGE 预测流水中 tag 比较、寄存器读等相关逻辑，优化时序（[#5686](https://github.com/OpenXiangShan/XiangShan/pull/5686)）
  - 调整 MBTB 训练流水中 replacer 相关逻辑，优化时序（[#5897](https://github.com/OpenXiangShan/XiangShan/pull/5897)，[#5944](https://github.com/OpenXiangShan/XiangShan/pull/5944)）
  - 调整 TAGE 训练流水，优化时序（[#5890](https://github.com/OpenXiangShan/XiangShan/pull/5890)）
  - 调整 SC 预测流水中计数器和的计算逻辑，优化时序（[#5911](https://github.com/OpenXiangShan/XiangShan/pull/5911)）
  - 调整 SC 训练流水中写回使能计算逻辑，优化时序（[#5923](https://github.com/OpenXiangShan/XiangShan/pull/5923)）
  - 调整 CommonHR 在重定向时计算折叠历史相关逻辑，优化时序（[#5975](https://github.com/OpenXiangShan/XiangShan/pull/5975)）
  - 调整 PHR S1 流水级中计算折叠历史相关逻辑，优化时序（[#5892](https://github.com/OpenXiangShan/XiangShan/pull/5892)）
  - 在 IFU 中使用并行或逻辑代替优先编码器，优化时序（[#5937](https://github.com/OpenXiangShan/XiangShan/pull/5937)）
- 代码质量
  - 使用隐式传参简化 ITTAGE 表的参数传递（[#5924](https://github.com/OpenXiangShan/XiangShan/pull/5924)）

### 后端

- RTL 新特性
  - 支持 smcdeleg/ssccfg 扩展（[#5841](https://github.com/OpenXiangShan/XiangShan/pull/5841)）
- Bug 修复
  - 当后端排空时，返回空状态到 FTQ（[#5787](https://github.com/OpenXiangShan/XiangShan/pull/5787)）
  - 修改 CSR 以支持 debug spec 1.0（[#5952](https://github.com/OpenXiangShan/XiangShan/pull/5952)）
  - （V2）stepie 应该控制 hvictl 注入中断（[#5926](https://github.com/OpenXiangShan/XiangShan/pull/5926)）

### 访存与缓存

- RTL 新特性
  - 将 CoupledL2 的容量增大到 2MB（[#5969](https://github.com/OpenXiangShan/XiangShan/pull/5969)）
- Bug 修复
  - 修复了 unalignQueue 在跨页存储操作出队后未能正确清除队列条目的问题（[#5913](https://github.com/OpenXiangShan/XiangShan/pull/5913)）
  - 为发往 L2 的预取请求添加握手信号以避免无故丢失预取请求（[#5989](https://github.com/OpenXiangShan/XiangShan/pull/5989)）
- PPA 优化
  - 在 DCache 重填过程中仅在替换块为脏时才读取数据，而不是每次都读取数据（[#5956](https://github.com/OpenXiangShan/XiangShan/pull/5956)）
  - 优化了 CoupledL2 的时序，2MB 容量下时序违例从 -130 ps 优化至 -40 ps，最大逻辑级数从 44 级优化至 24 级（[XSCache #4](https://github.com/OpenXiangShan/XSCache/pull/4)）
  - 修复了 CoupledL2 发往 MemBlock 的提前唤醒信号的准确性，并添加了统计准确性的性能计数器（[XSCache #5](https://github.com/OpenXiangShan/XSCache/pull/5), [#5993](https://github.com/OpenXiangShan/XiangShan/pull/5993)）
- 代码重构
  - 新建 XSCache 仓库，并将原 CoupledL2 与 OpenLLC 仓库的代码迁移到 XSCache 仓库中，以解决循环依赖和代码重复等问题（[#5938](https://github.com/OpenXiangShan/XiangShan/pull/5938)，[XSCache #7](https://github.com/OpenXiangShan/XSCache/pull/7)）
  - 移除了 XSCache 对 L2 与 L3 之间 Tilelink 总线协议的支持，仅保留对 CHI 总线协议的支持（[XSCache #6](https://github.com/OpenXiangShan/XSCache/pull/6)）
- 调试工具
  - 添加 pfLateHitType 和 Berti 监控器（[#5964](https://github.com/OpenXiangShan/XiangShan/pull/5964)）

### XSAI

- RTL 新特性
  - 拆分 C 矩阵访存模块的 load 与 store，使两种指令能够重叠执行（[CUTE #11](https://github.com/OpenXiangShan/CUTE/pull/11)）
- Bug 修复
  - 修复 XSAI 向 XSAI DiffTest 传递的错误常量（[XSAI #65](https://github.com/OpenXiangShan/XSAI/pull/65)）
  - 修复 HBL2 的 A 通道 Put Matrix 被 C 通道打断的错误（[XSAI #64](https://github.com/OpenXiangShan/XSAI/pull/64)）
- 代码质量
  - 加速 XSAI FIR elaboration，使 XSAI 生成 Verilog 的速度提高到原来的 4.75 倍（[CUTE #12](https://github.com/OpenXiangShan/CUTE/pull/12)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | f65a4e6c3  |
| 日期      | 2026/05/07 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.42  | 47.53  | 410.bwaves         | 85.27  | 89.88  |
| 401.bzip2           | 27.43  | 28.28  | 416.gamess         | 57.05  | 53.23  |
| 403.gcc             | 55.26  | 38.88  | 433.milc           | 64.93  | 64.04  |
| 429.mcf             | 61.00  | 55.47  | 434.zeusmp         | 71.27  | 64.66  |
| 445.gobmk           | 38.94  | 40.10  | 435.gromacs        | 37.20  | 34.38  |
| 456.hmmer           | 54.38  | 64.72  | 436.cactusADM      | 76.13  | 87.68  |
| 458.sjeng           | 38.87  | 39.48  | 437.leslie3d       | 56.26  | 56.36  |
| 462.libquantum      | 136.67 | 294.84 | 444.namd           | 43.23  | 45.23  |
| 464.h264ref         | 63.46  | 71.99  | 447.dealII         | 64.25  | 68.39  |
| 471.omnetpp         | 41.07  | 39.47  | 450.soplex         | 52.12  | 63.93  |
| 473.astar           | 30.42  | 29.63  | 453.povray         | 73.34  | 65.77  |
| 483.xalancbmk       | 75.83  | 84.61  | 454.Calculix       | 43.74  | 39.61  |
| GEOMEAN             | 50.90  | 54.07  | 459.GemsFDTD       | 63.50  | 63.95  |
|                     |        |        | 465.tonto          | 52.59  | 35.01  |
|                     |        |        | 470.lbm            | 125.82 | 133.04 |
|                     |        |        | 481.wrf            | 54.96  | 41.58  |
|                     |        |        | 482.sphinx3        | 59.39  | 62.42  |
|                     |        |        | GEOMEAN            | 61.07  | 59.18  |

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

编辑：徐之皓、吉骏雄、陈卓、余俊杰、孙际儒、李衍君
