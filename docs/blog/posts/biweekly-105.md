---
slug: biweekly-105
date: 2026-06-23
categories:
  - Biweekly
---

# 【香山双周报 105】20260623 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 105 期双周报。

我们非常高兴地与大家分享“香山”+“如意”生态中的重要组成部分 RuyiSDK！这是一个面向 RISC-V 架构的一站式开发资源管理平台，依托 ruyi 包管理器与 IDE 插件体系，整合工具链、模拟器、运行时环境及调试工具，提供全流程开发支持。平台构建了完善的 RISC-V 开发板与操作系统支持矩阵，为开发者提供更便捷的操作体验，是推动 RISC-V 开发与生态建设的重要基础设施。

大家可以通过以下链接获取更多信息：

- RuyiSDK 官网：<https://ruyisdk.org/>
- RuyiSDK 开发者社区：<https://ruyisdk.cn/>

RISC-V 欧洲峰会正在举行！香山团队在峰会上有多个 talk 和 poster，详细日程见[这里](https://mp.weixin.qq.com/s/gNpOxypE4UKLWLr2H103Yg)。

在 RISC-V 国际协会的开场报告中，CEO Andrea Gallo 介绍了香山在高性能服务器场景的应用。

![Andrea Gallo 介绍香山在高性能服务器场景的应用](./figs/biweekly-104/riscv-international.jpg)

中国科学院计算技术研究所副所长、北京开源芯片研究院首席科学家包云岗研究员作了题为 XiangShan Practice: The Path to Industrial Deployment of Open-Source High-Performance RISC-V Processor 的报告，介绍了香山的产业部署之路。

![包云岗研究员介绍香山的产业部署之路](./figs/biweekly-104/xiangshan-1.jpg)

![香山家族](./figs/biweekly-104/xiangshan-2.jpg)

我们还首次举办了万众一芯的 workshop，与大家分享软件原生的开源芯片智能众包验证探索与实践。

![万众一芯 workshop](./figs/biweekly-104/unity_chip.jpg)

关于香山近期开发进展，前端继续优化时序，同时降低了重定向延迟；后端实现了一些新特性与指令集扩展；访存修复了一些 bug，同时优化了 L2 的时序；XSAI 优化了代码结构，同时推进了 HBL2 对 CHI 的支持。

<!-- more -->

## 近期进展

### 前端

- PPA 优化
  - 优化 UTAGE 训练及预测时序（[#5517](https://github.com/OpenXiangShan/XiangShan/pull/5517)）
  - 优化 SC 计数器累加时序（[#5999](https://github.com/OpenXiangShan/XiangShan/pull/5999)）
  - 优化历史寄存器时序（[#6076](https://github.com/OpenXiangShan/XiangShan/pull/6076))
  - 优化 BPU pc 相关路径时序（[#5945](https://github.com/OpenXiangShan/XiangShan/pull/5945))
  - 优化 IBuffer 入队逻辑时序（[#6047](https://github.com/OpenXiangShan/XiangShan/pull/6047))
- 代码质量
  - 重构 BPU Replacer，简化冗余逻辑（[#6008](https://github.com/OpenXiangShan/XiangShan/pull/6008))
  - 重构 MBTB TargetFix，参数化可开关，与 UBTB/ABTB 对齐（[#6007](https://github.com/OpenXiangShan/XiangShan/pull/6007))
- 调试工具
  - 修复 FTQ perfQueue 相关性能计数器逻辑（[#6101](https://github.com/OpenXiangShan/XiangShan/pull/6101))

### 后端

- RTL 新特性
  - 使用稀疏向量（SparseVec）作为异常向量的存储结构 ([#5738](https://github.com/OpenXiangShan/XiangShan/pull/5738))
  - Sdtrig 扩展支持 tdata3 ([#5983](https://github.com/OpenXiangShan/XiangShan/pull/5983))

### 访存与缓存

- Bug 修复
  - 修复了 cbo 执行早于指令提交的问题（[#6081](https://github.com/OpenXiangShan/XiangShan/pull/6081)）
  - 修复了 loadUnit 的性能计数器（[#5939](https://github.com/OpenXiangShan/XiangShan/pull/5939)）
  - 添加指针越界断言（[#5795](https://github.com/OpenXiangShan/XiangShan/pull/5795)）
- 性能优化
  - 实现了 DCache MissQueue 的并行入队，同一周期允许最多 4 个 miss_req（[#5887](https://github.com/OpenXiangShan/XiangShan/pull/5887)）
  - 优化了 Sbuffer 的请求合并逻辑（[#6117](https://github.com/OpenXiangShan/XiangShan/pull/6117)）
- 时序优化
  - 修复了 Memblock 的时序（[#5963](https://github.com/OpenXiangShan/XiangShan/pull/5963)）

### XSAI

- RTL 新特性
  - 支持 RISC-V BF16 扩展（[XSAI #72](https://github.com/OpenXiangShan/XSAI/pull/72)）
  - 缩放因子存储改用香山的 SRAMTemplate，与香山统一（[CUTE #20](https://github.com/OpenXiangShan/CUTE/pull/20)）
  - 实现 TL-TL 与 TL-CHI 的 PutFullData（[HBL2 #3](https://github.com/OpenXiangShan/HBL2/pull/3)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 9443d04bd  |
| 日期      | 2026/06/05 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 2MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.90  | 48.25  | 410.bwaves         | 88.69  | 91.73  |
| 401.bzip2           | 28.31  | 29.27  | 416.gamess         | 57.30  | 53.54  |
| 403.gcc             | 56.28  | 39.51  | 433.milc           | 66.53  | 65.90  |
| 429.mcf             | 66.85  | 59.54  | 434.zeusmp         | 73.03  | 65.97  |
| 445.gobmk           | 39.78  | 41.14  | 435.gromacs        | 37.38  | 34.51  |
| 456.hmmer           | 54.41  | 65.27  | 436.cactusADM      | 77.86  | 89.84  |
| 458.sjeng           | 39.41  | 40.16  | 437.leslie3d       | 58.05  | 58.10  |
| 462.libquantum      | 137.87 | 299.94 | 444.namd           | 43.40  | 45.31  |
| 464.h264ref         | 63.34  | 71.92  | 447.dealII         | 66.97  | 73.51  |
| 471.omnetpp         | 42.06  | 40.56  | 450.soplex         | 54.04  | 66.91  |
| 473.astar           | 31.23  | 30.68  | 453.povray         | 74.04  | 66.76  |
| 483.xalancbmk       | 78.52  | 88.13  | 454.Calculix       | 44.18  | 40.21  |
| GEOMEAN             | 52.10  | 55.46  | 459.GemsFDTD       | 64.69  | 66.48  |
|                     |        |        | 465.tonto          | 53.87  | 35.81  |
|                     |        |        | 470.lbm            | 127.14 | 145.16 |
|                     |        |        | 481.wrf            | 55.65  | 41.90  |
|                     |        |        | 482.sphinx3        | 59.74  | 62.42  |
|                     |        |        | GEOMEAN            | 62.24  | 60.73  |

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

编辑：徐之皓、吉骏雄、陈卓、孙际儒、李衍君
