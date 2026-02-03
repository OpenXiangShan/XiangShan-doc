---
slug: biweekly-95
date: 2026-02-02
categories:
  - Biweekly
---

# 【香山双周报 95】20260202 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 95 期双周报。

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
  - MBTB 使用 LRU 替换算法，并使用 TAGE-SC 的精确预测结果进行更新，尽可能使有用的分支留在 MBTB 中（[#5525](https://github.com/OpenXiangShan/XiangShan/pull/5525)）
  - 实现 SC BW 表（[#5528](https://github.com/OpenXiangShan/XiangShan/pull/5528)）
  - 支持 RAS 在 S1 提供预测结果（[#5366](https://github.com/OpenXiangShan/XiangShan/pull/5366)）
- Bug 修复
  - 增加 BPU 训练流水控制信号的复位，避免 X 态（[#5539](https://github.com/OpenXiangShan/XiangShan/pull/5539)）
  - 修复有符号饱和计数器错误溢出的问题（[#5545](https://github.com/OpenXiangShan/XiangShan/pull/5545)）
  - 修复有符号饱和计数器 isWeakPositive 方法判断错误的问题（[#5551](https://github.com/OpenXiangShan/XiangShan/pull/5551)）
- 时序/面积优化
  - 移除 MBTB 跨页时不读 SRAM 的限制，避免读 valid 时序路径和写 ready 时序路径串在一起导致时序不好（[#5541](https://github.com/OpenXiangShan/XiangShan/pull/5541)）
- 调试工具
  - 修复一些性能计数器条件（[#5536](https://github.com/OpenXiangShan/XiangShan/pull/5536)，[#5568](https://github.com/OpenXiangShan/XiangShan/pull/5568)）

### 后端

- RTL 新特性
  - 添加 I2F FU 以支持 FMV 和 FCVT 的 i2f 类型（[#5557](https://github.com/OpenXiangShan/XiangShan/pull/5557), [#5577](https://github.com/OpenXiangShan/XiangShan/pull/5577)）
  - 支持 Smcntrpmf 扩展（[#4286](https://github.com/OpenXiangShan/XiangShan/pull/4286)）
- 时序/面积优化
  - 在 csrToDecode 与 Decode 之间增加一拍（[#5542](https://github.com/OpenXiangShan/XiangShan/pull/5542)）
  - 将 ALU 的数据处理从 Bypass 阶段转移到 ALU 内部（[#5562](https://github.com/OpenXiangShan/XiangShan/pull/5562)）
  - 对整数 IQ 添加 og1Payload，利用只在 OG1 中使用的信号以优化 IQ 选择时序。（[#5570](https://github.com/OpenXiangShan/XiangShan/pull/5570)）
- Bug 修复
  - 修复了来自功能单元写回的 redirect.valid 信号，以及 TopDown 中的 mis_pred 和 total flush 问题（[#5538](https://github.com/OpenXiangShan/XiangShan/pull/5538)）
  - 修复了 NewCSR 中 RegNext 的重复使用问题（[#5441](https://github.com/OpenXiangShan/XiangShan/pull/5441)）
  - 修复了 ROB 中 flushpipe 对 redirect.interrupt 的错误假设（[#5583](https://github.com/OpenXiangShan/XiangShan/pull/5583)）
- 代码质量
  - 重构所有 resps 信号，简化代码逻辑（[#5537](https://github.com/OpenXiangShan/XiangShan/pull/5537)）
  - 优化 resps 信号的代码质量（[#5550](http://github.com/OpenXiangShan/XiangShan/pull/5550)）
  - 移除 IsssueQueue 中部分冗余代码，调整唤醒 pdest 宽度，添加 ROB bankNum 参数（[#5051](https://github.com/OpenXiangShan/XiangShan/pull/5051)）
  - 重构 vialuf 以支持快速唤醒（[#5136](https://github.com/OpenXiangShan/XiangShan/pull/5136)）
  - 删除 Datapath 中的无用代码（[#5567](https://github.com/OpenXiangShan/XiangShan/pull/5567)）
  - 重构写回至 ROB 和 Regfile 的Bundle（[#5535](https://github.com/OpenXiangShan/XiangShan/pull/5535)）
  - 整合信号，使用 EnqRObUop 代替 DynInst 以减去多余的信号（[#5560](http://github.com/OpenXiangShan/XiangShan/pull/5560)）
  - 删除无用的 IntToFP 功能单元（[#5586](https://github.com/OpenXiangShan/XiangShan/pull/5586)）
- 结构调整
  - 删除 fudian 子模块，从现在起昆明湖 V3 将不再使用 fudian 仓库内容作为子模块（[#5585](https://github.com/OpenXiangShan/XiangShan/pull/5585)）

### 访存与缓存

- RTL 新特性
  - MDP、MMU、LoadUnit、StoreQueue、L2 等模块重构与测试持续推进中
- Bug 修复
  - 修复了 Sbuffer 中的超时判断逻辑，通过 csr 中的 SMBLOCKCTL 配置超时阈值（[#5573](https://github.com/OpenXiangShan/XiangShan/pull/5573)）
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
