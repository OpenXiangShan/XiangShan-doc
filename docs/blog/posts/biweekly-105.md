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

- Bug 修复
  - （V2）修复 M 态注入 SEI 时的优先级编号，按 AIA 规范将其设为 S 级优先级 256（[#6010](https://github.com/OpenXiangShan/XiangShan/pull/6010)）
  - （V2）修复 `mret` 进入 VU 模式时 `vsstatus.SDT` 未被清除的问题（[#6074](https://github.com/OpenXiangShan/XiangShan/pull/6074)）
  - （V2/V3）修复 `vstopi` Candidate3 使能条件（[#6030](https://github.com/OpenXiangShan/XiangShan/pull/6030)、[#6031](https://github.com/OpenXiangShan/XiangShan/pull/6031)）
  - （V2）修复 Candidate3 与 Candidate5 同时使能时的 iid 选择（[#6086](https://github.com/OpenXiangShan/XiangShan/pull/6086)）
  - （V2）修复 `fence` 指令 opcode 匹配（[#6096](https://github.com/OpenXiangShan/XiangShan/pull/6096)）
  - （V2）修复 ROB 中 `commit_w` 的 X-state 传播（[#6070](https://github.com/OpenXiangShan/XiangShan/pull/6070)）
  - （V2）修复 IGPF 过程中 `mtval2` 生成错误的问题（[#6058](https://github.com/OpenXiangShan/XiangShan/pull/6058)）
  - （V2）修复 `MNret` 对 `mnstatus.MNPP/MNPV` 的处理（[#6075](https://github.com/OpenXiangShan/XiangShan/pull/6075)）
  - （V2）按陷入类型约束 VS `hvictl` 中断原因的生成，并完善 WFI 唤醒相关的中断 pending 判断（[#6067](https://github.com/OpenXiangShan/XiangShan/pull/6067)）
  - （V2）修复 `trapInstInfo` 暂存逻辑，避免 flush 与更老 CSR trap 同周期到达时遗漏陷入指令信息（[#6084](https://github.com/OpenXiangShan/XiangShan/pull/6084)）
  - （V2）将 HLV/HLVX/HSV 访存异常标记为虚拟访存陷入，以正确更新 `htval`/`mtval`（[#6071](https://github.com/OpenXiangShan/XiangShan/pull/6071)）
  - （V2）修复 PMP/PMA 在 `CSRRS`/`CSRRC` 读-改-写时的基值选择（[#6051](https://github.com/OpenXiangShan/XiangShan/pull/6051)）

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
| commit    | 8c4daa743  |
| 日期      | 2026/06/18 |
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
| 400.perlbench       | 50.55  | 49.66  | 410.bwaves         | 104.21 | 95.87  |
| 401.bzip2           | 28.61  | 29.56  | 416.gamess         | 57.76  | 54.82  |
| 403.gcc             | 57.06  | 40.22  | 433.milc           | 69.94  | 68.81  |
| 429.mcf             | 71.47  | 62.54  | 434.zeusmp         | 74.95  | 67.02  |
| 445.gobmk           | 39.90  | 40.89  | 435.gromacs        | 37.90  | 34.82  |
| 456.hmmer           | 54.84  | 65.42  | 436.cactusADM      | 80.64  | 91.86  |
| 458.sjeng           | 39.36  | 40.48  | 437.leslie3d       | 59.90  | 59.70  |
| 462.libquantum      | 141.89 | 312.28 | 444.namd           | 43.55  | 45.46  |
| 464.h264ref         | 66.56  | 72.86  | 447.dealII         | 69.14  | 74.72  |
| 471.omnetpp         | 43.55  | 42.80  | 450.soplex         | 58.74  | 69.98  |
| 473.astar           | 32.92  | 32.64  | 453.povray         | 76.71  | 70.42  |
| 483.xalancbmk       | 81.13  | 92.62  | 454.Calculix       | 44.54  | 40.60  |
| GEOMEAN             | 53.57  | 57.00  | 459.GemsFDTD       | 69.93  | 70.40  |
|                     |        |        | 465.tonto          | 54.49  | 37.22  |
|                     |        |        | 470.lbm            | 128.45 | 148.55 |
|                     |        |        | 481.wrf            | 56.39  | 42.33  |
|                     |        |        | 482.sphinx3        | 60.94  | 63.63  |
|                     |        |        | GEOMEAN            | 64.55  | 62.40  |

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
