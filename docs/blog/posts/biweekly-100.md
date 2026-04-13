---
slug: biweekly-100
date: 2026-04-13
categories:
  - Biweekly
---

# 【香山双周报 100】20260413 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 100 期双周报。

从本期开始，香山双周报也将汇报 [香山AI（XSAI）](https://github.com/OpenXiangShan/XSAI) 的开发进展。XSAI 是基于香山开源高性能 RISC-V 处理器实现的“通推一体”AI 处理器，其技术曾在 2025 年 RISC-V 中国峰会上有过介绍。XSAI 是香山团队基于已有 RISC-V CPU 生态积累基础上，对于“通推一体” AI 芯片的探索，也是对香山敏捷开发方法学的实践。北京开源芯片研究院与中国科学院计算技术研究所微处理器研究中心、先进计算机系统研究中心共同参与了 XSAI 的开发。XSAI 将在 2026 年逐步发布指令扩展手册、架构文档、用户手册，开源我们的开发工具链，并且在香山系列 tutorial 中添加 XSAI “通推一体”处理器的内容。

目前 XSAI 基于昆明湖 V2R2 开发，型号名称是昆明湖 V2R2A。最终的 V2R2A 将会在 V2R2 的基础上增加 bf16/fp8 的向量扩展以及 bf16/fp8/int8 的矩阵扩展，且具备高带宽 L2 缓存，用于展示。XSAI 组近期进行了一些初步测试，这些测试意在验证 XSAI 的通算、智算功能。本期向香山双周报的各位读者汇报测试结果。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 实现 SC 更精确的预测阈值逻辑（[#5716](https://github.com/OpenXiangShan/XiangShan/pull/5716)）
  - 启用 SC Global 表（[#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756)）
- Bug 修复
  - 修复历史寄存器在发生高级预测器 Override 时元数据更新错误的问题（[#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756)）
- 面积/时序优化
  - 将 SRAMTemplate resetState 暴露到接口上，BPU 使用该接口判断 SRAM 是否准备好接收请求（[#5735](https://github.com/OpenXiangShan/XiangShan/pull/5735)，[Utility#141](https://github.com/OpenXiangShan/Utility/pull/141)）
  - 更多时序修复正在评估中
- 代码质量
  - 重构 SC 表索引相关参数传递机制（[#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756)）
- 调试工具
  - Make Topdown Accurate Again！协同后端组重写 Top-Down 性能计数器（[#5564](https://github.com/OpenXiangShan/XiangShan/pull/5564)）
  - 修复 BPU 顶层 `train_stall` 计数器条件永远为假的问题（[#5734](https://github.com/OpenXiangShan/XiangShan/pull/5734)）

### 后端

- RTL 新特性
  - 将整型 RegCache 的大小增加到 24 以支持 6 alu 的配置（[#5613](https://github.com/OpenXiangShan/XiangShan/pull/5613)）
  - 修改 vsetvl x0, x0 使得 reserved 情况表现与 Spike 一致（[#5744](https://github.com/OpenXiangShan/XiangShan/pull/5744)）
- Bug 修复
  - 在 critical-error 的 debug 重入口维持 dpc（[#5730](https://github.com/OpenXiangShan/XiangShan/pull/5730)）
  - 同步修复 V2 的 debug 相关 bug（[#5754](https://github.com/OpenXiangShan/XiangShan/pull/5754)）
  - 修复 Mcontrol6/Tdata1 相关问题（[#5722](https://github.com/OpenXiangShan/XiangShan/pull/5722)）
  - 修复 TopDown 当中的 mis_pred 和 total_flush（[#5762](https://github.com/OpenXiangShan/XiangShan/pull/5762)）
  - 修复 Bypass 中 psrcVl 的驱动为 pdestVl（[#5743](https://github.com/OpenXiangShan/XiangShan/pull/5743)）
- 时序优化
  - 优化 Rename 的时序（[#5685](https://github.com/OpenXiangShan/XiangShan/pull/5685)）
- 代码质量
  - 重命名 halt 为 wfi（[#4512](https://github.com/OpenXiangShan/XiangShan/pull/4512)）

### 访存与缓存

- RTL 新特性
  - MMU、L2 等模块重构与测试持续推进中
  - 优化了 Stream 预取器，启用了 decr 模式并优化了训练策略（[#5691](https://github.com/OpenXiangShan/XiangShan/pull/5691)）
  - 修改了 TL2CHICoupledL2 顶层模块的接口，将 io_cpu_halt 改为 io_cpu_wfi（[CoupledL2 #482](https://github.com/OpenXiangShan/CoupledL2/pull/482)）
  - 新增了 NextLine 预取器（[CoupledL2 #477](https://github.com/OpenXiangShan/CoupledL2/pull/477)）
- Bug 修复
  - 修复了 StoreQueue 中 deqPtr 过早移动的问题（[#5748](https://github.com/OpenXiangShan/XiangShan/pull/5748)）
  - 修复了 pbmt 与 hypervisor 访问设备区域时的一些问题（[#5751](https://github.com/OpenXiangShan/XiangShan/pull/5751)）
  - 修复了 unalignedHead 重发时卡死的问题（[#5783](https://github.com/OpenXiangShan/XiangShan/pull/5783)）
- 代码质量
  - 重构了 storeEvent 的相关 Bundle（[#5763](https://github.com/OpenXiangShan/XiangShan/pull/5763)）
  - 重构 CoupledL2，OpenLLC，HuanCun 仓库之间的依赖关系。进行中
- 时序修复
  - 修复了 StoreQueue 的时序问题（[#5698](https://github.com/OpenXiangShan/XiangShan/pull/5698)）

### XSAI

使用 SPEC CPU 2006 测试 XSAI 的通算功能。本次测试的检查点、处理器参数以及 SoC 参数与香山双周报 91 一致。

| SPECint 2006 est. | V2R2A@3GHz | V2R2@3GHz | SPECfp 2006 est. | V2R2A@3GHz | V2R2@3GHz |
| :---------------- | :--------: | :-------: | :--------------- | :--------: | :-------: |
| 400.perlbench     |   36.03    |   36.18   | 410.bwaves       |   67.35    |   66.73   |
| 401.bzip2         |   25.75    |   25.46   | 416.gamess       |   40.61    |   40.99   |
| 403.gcc           |   48.15    |   48.00   | 433.milc         |   44.38    |   45.12   |
| 429.mcf           |   63.26    |   60.63   | 434.zeusmp       |   51.65    |   51.61   |
| 445.gobmk         |   30.30    |   30.32   | 435.gromacs      |   33.50    |   33.60   |
| 456.hmmer         |   41.35    |   41.62   | 436.cactusADM    |   46.06    |   46.19   |
| 458.sjeng         |   30.25    |   30.24   | 437.leslie3d     |   48.31    |   47.97   |
| 462.libquantum    |   126.54   |  122.43   | 444.namd         |   28.82    |   28.86   |
| 464.h264ref       |   56.49    |   56.58   | 447.dealII       |   73.37    |   73.55   |
| 471.omnetpp       |   42.32    |   41.77   | 450.soplex       |   52.85    |   52.50   |
| 473.astar         |   29.23    |   29.19   | 453.povray       |   53.05    |   53.46   |
| 483.xalancbmk     |   71.39    |   72.84   | 454.Calculix     |   16.35    |   16.37   |
| GEOMEAN           |   44.92    |   44.66   | 459.GemsFDTD     |   38.31    |   38.60   |
|                   |            |           | 465.tonto        |   36.65    |   36.66   |
|                   |            |           | 470.lbm          |   91.30    |   91.94   |
|                   |            |           | 481.wrf          |   40.25    |   40.70   |
|                   |            |           | 482.sphinx3      |   48.88    |   49.13   |
|                   |            |           | GEOMEAN          |   44.72    |   44.85   |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差。

> 解读：V2R2A 频率 3GHz 仅代表仿真设置，该设置与 V2R2 的仿真对齐，以确认 XSAI 的修改没有导致性能显著倒退。我们预期的 XSAI 频率低于 3GHz。在通算场景下，导致性能差异的因素是高带宽 L2 的架构设计以及缓存替换算法的改变。上述测试结果表明，XSAI 对香山的修改没有显著影响香山原有的通算功能与性能。

在智算测试方面，我们在 XCVU19p FPGA 上，使用经过裁剪的 V2R2A 运行了 Llama-2 15M 模型的推理。XSAI 频率 50MHz，矩阵 int8 算力 4Tops/GHz，内存 DDR4-2400 MHz。测试得到的 Prefill/Decode 阶段性能分别是 343.61 toks/s 与 36.24 toks/s，输出符合预期。

![XSAI FPGA test](./figs/biweekly-100/XSAI-fpga.png)

> 解读：测试使用的内存频率贴近硅后的使用情况，但 XSAI 的频率远远低于硅后，从这方面来讲，本次测试的结果偏乐观。但是 V2R2A 为了部署在 XCVU19p 上做了不少裁剪，对性能不利，从这方面来讲，本次测试的结果又是偏悲观的。因此，本次测试仅作为功能方面的原型测试，证明 XSAI 在功能上支持大模型推理。

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 87d03b2cc  |
| 日期      | 2026/03/24 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存延迟  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.54  | 47.50  | 410.bwaves         | 85.76  | 90.75  |
| 401.bzip2           | 27.41  | 28.22  | 416.gamess         | 56.92  | 53.01  |
| 403.gcc             | 55.42  | 38.93  | 433.milc           | 64.88  | 63.62  |
| 429.mcf             | 59.81  | 54.32  | 434.zeusmp         | 70.31  | 64.42  |
| 445.gobmk           | 39.25  | 40.59  | 435.gromacs        | 36.39  | 34.26  |
| 456.hmmer           | 53.63  | 63.65  | 436.cactusADM      | 75.77  | 86.49  |
| 458.sjeng           | 39.50  | 39.74  | 437.leslie3d       | 56.50  | 52.29  |
| 462.libquantum      | 135.53 | 294.09 | 444.namd           | 42.58  | 44.54  |
| 464.h264ref         | 62.93  | 71.26  | 447.dealII         | 64.88  | 69.53  |
| 471.omnetpp         | 41.18  | 39.38  | 450.soplex         | 49.79  | 60.47  |
| 473.astar           | 31.04  | 30.22  | 453.povray         | 73.02  | 66.48  |
| 483.xalancbmk       | 74.59  | 84.30  | 454.Calculix       | 43.93  | 39.70  |
| GEOMEAN             | 50.84  | 53.98  | 459.GemsFDTD       | 64.37  | 64.29  |
|                     |        |        | 465.tonto          | 52.49  | 34.91  |
|                     |        |        | 470.lbm            | 126.77 | 132.75 |
|                     |        |        | 481.wrf            | 55.04  | 41.52  |
|                     |        |        | 482.sphinx3        | 58.62  | 61.20  |
|                     |        |        | GEOMEAN            | 60.79  | 58.63  |

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
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、孙际儒、李衍君
