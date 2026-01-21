---
slug: biweekly-94
date: 2026-01-19
categories:
  - Biweekly
---

# 【香山双周报 94】20260119 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 94 期双周报。

香山开发方面，前端对 1-taken 1-fetch 架构进行收尾工作，同时进行 2-taken 2-fetch 架构探索；后端继续推进向量单元的设计与多个模块的重构；访存修复了数个 bug，同时继续预取与 MDP 的探索工作。

<!-- more -->

## 加速！加速！！
众所周知，处理器的仿真非常花费计算资源。香山完整性能回归使用的 checkpoint 一共有 1169 个。使用 verilator 进行仿真时，我们通常会编译成 8 个或 16 个线程的版本以提升仿真速度。即便如此，一些 checkpoint 也需要运行数十个小时。

随着 V3 规模的变大，仿真速度下降到了 V2 速度的约 1/3，这让本来就慢的性能回归雪上加霜。更关键的是，现在 V3 正在经历快速性能迭代，性能回归的需求比以往更大，没有数据就进行性能优化无异于闭眼开车。

为了解决仿真速度的问题，我们首先定位了使用 verilator 时仿真速度性能下降的原因。经过前后对比分析，我们发现 V3 仿真速度下降的锅竟然有很重要的一部分要由升级 Chisel 7 来背。简单来说，Chisel 7 换了一种 Mux1H 的生成方法，导致 verilator 生成了查找表，而不是数组访问。详细的分析可以查看这个 [issue](https://github.com/verilator/verilator/issues/6760)。这一修复可以带来 100% 的速度提高，相关修复也已经进入了 verilator 主线。

可是，即使提高了 100% 的速度，V3 的仿真速度仍然只有 V2 的 60%。为了进一步提高仿真速度，我们引入了香山团队自己开发的仿真器 [GSIM](https://github.com/OpenXiangShan/gsim)。准确地说，GSIM 其实并没有加快仿真速度，单线程的 GSIM 仿真速度惜败于 16 线程的 verilator，小胜 8 线程的 verilator。虽然速度没有提高，但并行度却提高了 10 倍，这意味着我们现在能够以同样的计算资源，狠狠进行 10 倍数量的性能回归。

为了进一步压榨现有服务器，香山团队的 L 和 X 同学最近还搓出了一个基于 GitHub 的香山特色作业调度系统 [perf trigger](https://github.com/OpenXiangShan/XiangShan/actions/workflows/perf-trigger.yml)。这一青春版的 lsf 系统可以利用上所有服务器，同时统一管理所有的仿真配置和结果。Perf trigger 已经成功管理了多个性能回归作业，虽然有时还会有一些不稳定的情况~~爱来每天凌晨 4 点自动重启的 GitHub Runner 、小水管专线和、服务器维护~~，不过 trigger 在整个香山团队内大受好评。

## 近期进展

### 前端

- RTL 新特性
  - 完善 SC 预测器的 bias 和 path 表（[#5458](https://github.com/OpenXiangShan/XiangShan/pull/5458)）
  - 在 TAGE 中使用 WriteBuffer 的计数器累加机制（[#5470](https://github.com/OpenXiangShan/XiangShan/pull/5470)）
  - 将 ABTB 的 set 和 bank 索引存入元数据，移除 BPU 顶层额外保存的 s4 级 pc（[#5494](https://github.com/OpenXiangShan/XiangShan/pull/5494)）
  - 支持开关 ICache parity 出错时自动重取的机制（[#5501](https://github.com/OpenXiangShan/XiangShan/pull/5501)）
- Bug 修复
  - 修复 MBTB replacer 一处笔误（[#5540](https://github.com/OpenXiangShan/XiangShan/pull/5540)）
  - 修复 TAGE 使用元数据更新的条件（[#5461](https://github.com/OpenXiangShan/XiangShan/pull/5461)）
  - 修复 GHR 在 FTQ 阻塞情况下丢失更新的问题（[#5469](https://github.com/OpenXiangShan/XiangShan/pull/5469)）
  - 修复 RAS 在 FTQ 阻塞情况下错误更新元数据的问题（[#5481](https://github.com/OpenXiangShan/XiangShan/pull/5481)）
  - 修复 WriteBuffer 在 setIdx 命中时的替换选择逻辑（[#5526](https://github.com/OpenXiangShan/XiangShan/pull/5526)）
  - 修复 IFU 在 MMIO 空间推测取指的问题（[#5459](https://github.com/OpenXiangShan/XiangShan/pull/5459)）
- 时序/面积优化
  - 禁用 ICache parity 出错时自动重取的机制以优化时序（[#5501](https://github.com/OpenXiangShan/XiangShan/pull/5501)）
- 代码质量
  - 重构 SaturateCounter 工具类（[#5363](https://github.com/OpenXiangShan/XiangShan/pull/5363)）
  - 重构 BPU 元数据类（[#5486](https://github.com/OpenXiangShan/XiangShan/pull/5486)）
  - 解耦 ABTB 和 UTAGE（[#5500](https://github.com/OpenXiangShan/XiangShan/pull/5500)）
- 调试工具
  - 增加 MBTB trace（[#5466](https://github.com/OpenXiangShan/XiangShan/pull/5466)）

### 后端

- RTL 新特性
  - 重构乘法单元（[#5514](https://github.com/OpenXiangShan/XiangShan/pull/5514)）
  - 将整数 Regfile 分为 4 个 bank 以减少读冲突（[#5438](https://github.com/OpenXiangShan/XiangShan/pull/5438)）
- 时序/面积优化
  - 访存单元重定向不再通过 flushpipe 和 replayInst 写回 (slow redirect)，统一通过 memviolation 写回 (fast redirect)（[#5491](https://github.com/OpenXiangShan/XiangShan/pull/5491)）
  - 调整 TopDown 的时序（[#5451](https://github.com/OpenXiangShan/XiangShan/pull/5451)）
（[#5491](https://github.com/OpenXiangShan/XiangShan/pull/5491)）
- 代码质量
  - 删除无用代码 isXret（[#5483](https://github.com/OpenXiangShan/XiangShan/pull/5483)）
  - 在立即数上改用样例类 Imm 进行配置，而非直接使用 UInt（[#5523](https://github.com/OpenXiangShan/XiangShan/pull/5523)）
  - 删除部分 IssueQueue 相关的无用代码（[#5519](https://github.com/OpenXiangShan/XiangShan/pull/5519)）
  - 删除 Regfile 中 assertion 外不必要的条件判断（[#5505](https://github.com/OpenXiangShan/XiangShan/pull/5505)）
- 性能分析工具
  - 添加后端 V2 配置参数 BackendV2Config 以用于性能对比（[#5476](https://github.com/OpenXiangShan/XiangShan/pull/5476)）

### 访存与缓存

- RTL 新特性
  - MDP、MMU、LoadUnit、StoreQueue、L2 等模块重构与测试持续推进中
- Bug 修复
  - （V2）修复了 exception buffer 入队逻辑中 lqIdx 与 sqIdx 未连线的问题（[#5512](https://github.com/OpenXiangShan/XiangShan/pull/5512)）
  - （V2）修复了 SnpXFwd 中未考虑 SnpPreferUniqueFwd 的错误（[CoupledL2 #460](https://github.com/OpenXiangShan/CoupledL2/pull/460)）
  - （V2）修复了 MainPipe 中 l2Error_s3 的生成逻辑（[CoupledL2 #463](https://github.com/OpenXiangShan/CoupledL2/pull/463)）
- 调试工具
  - 持续改进 CHI 基础设施 CHIron
  - 开发用于新版 L2 Cache 的验证工具 CHI Test。持续推进中

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 38.59  | 410.bwaves       | 73.45  |
| 401.bzip2         | 27.13  | 416.gamess       | 54.67  |
| 403.gcc           | 47.59  | 433.milc         | 50.97  |
| 429.mcf           | 58.76  | 434.zeusmp       | 60.65  |
| 445.gobmk         | 37.31  | 435.gromacs      | 38.47  |
| 456.hmmer         | 43.58  | 436.cactusADM    | 53.99  |
| 458.sjeng         | 34.16  | 437.leslie3d     | 54.47  |
| 462.libquantum    | 132.86 | 444.namd         | 37.28  |
| 464.h264ref       | 62.77  | 447.dealII       | 64.50  |
| 471.omnetpp       | 42.60  | 450.soplex       | 54.20  |
| 473.astar         | 30.43  | 453.povray       | 61.69  |
| 483.xalancbmk     | 80.75  | 454.Calculix     | 19.39  |
| GEOMEAN           | 47.79  | 459.GemsFDTD     | 47.03  |
|                   |        | 465.tonto        | 36.23  |
|                   |        | 470.lbm          | 105.07 |
|                   |        | 481.wrf          | 48.84  |
|                   |        | 482.sphinx3      | 55.21  |
|                   |        | GEOMEAN          | 50.97  |

编译参数如下所示：

| 参数             | 选项     |
| ---------------- | -------- |
| 编译器           | gcc12    |
| 编译优化         | O3       |
| 内存库           | jemalloc |
| -march           | RV64GCB  |
| -ffp-contraction | fast     |

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | fd1e37f95  |
| 日期      | 2026/01/16 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存延迟  | DDR4-3200  |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
