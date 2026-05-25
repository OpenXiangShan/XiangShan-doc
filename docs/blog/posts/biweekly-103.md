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
  - 实现初版 2-prefetch 方案（[#5775](https://github.com/OpenXiangShan/XiangShan/pull/5775)）
- Bug 修复
  - （V2）协同后端组修复 satp 更新后出现异常时 xepc 和 xtval 寄存器更新错误的问题（[#5860](https://github.com/OpenXiangShan/XiangShan/pull/5860)）
  - 修复 IFU 处理跨页指令引起的异常时标记错误的问题（[#5874](https://github.com/OpenXiangShan/XiangShan/pull/5874)）
- PPA 优化
  - 使用 SRAM 保存 TAGE useful counter 以节省面积（[#5852](https://github.com/OpenXiangShan/XiangShan/pull/5852)）
  - 调整 BPU 顶层处理 mbtb attribute 的流水级划分以提升时序（[#5842](https://github.com/OpenXiangShan/XiangShan/pull/5842)）
- 代码质量
  - 移除 MBTB 中一个可能引起误解的参数（[#5891](https://github.com/OpenXiangShan/XiangShan/pull/5891)）

### 后端

- Bug 修复
  - （V2）前端组协同下修复 satp 更新后出现异常时 xepc 和 xtval 寄存器更新错误的问题（[#5860](https://github.com/OpenXiangShan/XiangShan/pull/5860)）
  - （V2）修复每条 jump 指令执行时都会触发的 redirect 的问题（[#5867](https://github.com/OpenXiangShan/XiangShan/pull/5867)）
  - （V2）为 mtvec 添加初始化值（[#5862](https://github.com/OpenXiangShan/XiangShan/pull/5862)）

### 访存与缓存

- RTL 新特性
  - 实现了 DCache mshr 的 store-load 前递（[#5870](https://github.com/OpenXiangShan/XiangShan/pull/5870)）
  - 持续推进新版 L2 设计
- Bug 修复
  - 修复了 L2TLB 中错误使用 PPN 截断位来索引 cfs 的问题（[#5858](https://github.com/OpenXiangShan/XiangShan/pull/5858)）
  - 修复了 StoreQueue 处理跨 16 字节访存时的行为（[#5855](https://github.com/OpenXiangShan/XiangShan/pull/5855)）

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
