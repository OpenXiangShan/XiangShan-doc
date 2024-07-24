---
slug: biweekly-56
date: 2024-07-22
categories:
  - Biweekly
---

# 【香山双周报 56】20240722期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 56 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端实现 RVA23 Zcb 拓展，后端合入新版 CSR，CHI-L3 完成剩余模块设计，Sv48 环境下 RTL 和 NEMU 成功启动 Linux kernel。

<!-- more -->
## 近期进展

### 前端
- 功能
    - 实现 RVA23 Zcb 拓展 （[#3257](https://github.com/OpenXiangShan/XiangShan/pull/3257)）
    - 修复在 guest 态从 mmio 空间取指发生 guest page fault 时 ， 相关的信息没有正确传到 ibuffer  的潜在问题 （[#3182](https://github.com/OpenXiangShan/XiangShan/pull/3182)）
    - 修复 ITTAGE 的 ready 信号复位行为不符合预期问题 （[#3198](https://github.com/OpenXiangShan/XiangShan/pull/3198)）
    - 修复训练 SC 时 totalSum 与 scSum + tagePvdr 不相符的问题 （[#3178](https://github.com/OpenXiangShan/XiangShan/pull/3178)）
    - 修复传给后端的 newest target 错误问题 （[#3269](https://github.com/OpenXiangShan/XiangShan/pull/3269)）
    - 修复 IPrefetch s2_miss(1) 条件错误 bug（[#3239](https://github.com/OpenXiangShan/XiangShan/pull/3239)）
    - 修复 tageTaken 和 tageTarget 的选择条件导致错误的输出 bug（[#3241](https://github.com/OpenXiangShan/XiangShan/pull/3241)）
- 性能
    - 完成 ITTAGE useful 移入 sram 方案 （[#3247](https://github.com/OpenXiangShan/XiangShan/pull/3247)）
    - 修复多个 RAS 相关性能 bug（[#3194](https://github.com/OpenXiangShan/XiangShan/pull/3194)、[#3237](https://github.com/OpenXiangShan/XiangShan/pull/3237)）

### 后端流水线

- 合入新版 CSR 实现（[#3218](https://github.com/OpenXiangShan/XiangShan/pull/3218)）
    - 由 CSR registers、CSR events、Permission Check 和 Trap Handler 四部分组成
    - 每个 CSR 例化一个模块
    - 支持 IMSIC
    - 支持 Sstc、Ssovfpmf 和 Smaia 等新扩展
    - 修复了旧版实现的一系列 Bug
- Bug 修复
    - 修复 vsstatus.vs 检测的 bug（[#3253](https://github.com/OpenXiangShan/XiangShan/pull/3253)）
    - 修复 vfredosum 指令的 uop num（[#3230](https://github.com/OpenXiangShan/XiangShan/pull/3230)）
- 时序优化
    - 优化 og0 cancel 信号时序（[#3235](https://github.com/OpenXiangShan/XiangShan/pull/3235)）
    - decode 的 isComplex 移除 uopNum =/= 1.U 的条件判断

### 访存与缓存

- CHI 总线
    - CHI-L3 完成剩余模块设计；接入 CoupledL2-OpenLLC-CHI2AXI4 框架，准备进行 tl-test 测试
    - 正在搭建从 Issue B 升级到 Issue E.b 的 TLTest + VIP 验证环境
    - 向量访存
    - 修复 Segment 访存指令相关、MMIO 空间向量访存相关、trigger 异常相关的 bug
    - 修复 vlenb csrr 频繁清空流水线的性能 bug，并采用 gcc15 编译，自动向量化 hmmer 由 gcc14 的 15.3/GHz 提升至 19.7/GHz，libquantum checkpoint 为 43.08/GHz（标量分别为 13.1/GHz、41.84/GHz）
- 功能
    - RTL 和 NEMU 成功启动 Sv48 的 Linux kernel、{sv39, sv48} × {sv39x4, sv48x4} 的 gos 测试组合
    - H 扩展上，迭代 10 轮 CoreMark 虚拟机性能约为物理机的 91.2%，性能损失主要来源于无中断虚拟化和 MMU 优化不足
    - 设计 RVA23 CMO 指令支持的实现方案并开始代码实现
- 性能
    - 多端口 DCache MSHR 入队修复多个 bug，目前已经成功跑通 linux-hello
    - TP meta on L2 基于最新 master 测试模拟拆分，测试结果不达预期 ；分析发现 TP meta 与 L2 数据在访存敏感程序上存在负面竞争，正在进行优化，保留有效 TP Trigger
    - 在 L3 上实现 CHROME 替换算法，单元测试框架随机激励下命中率接近 roofline，但 SPEC 测试性能不佳，观察到有效训练请求过少，进行 Q-Table 训练加速以及增加预取请求进行训练的优化
- 时序
    - MemBlock：内部违例 -48ps，Backend-MemBlock 端口违例修复正在评估
    - CHI-CoupledL2：内部违例 -50ps，端口违例 -170ps
    - 基于物理设计上 L2 Data SRAM 的 MCP2 时序需求（MultiCyclePath2，在读请求握手后需要两拍才能采样读数据），修改 RTL 使其满足 MCP2 要求，并实现了用于仿真的 MCP2 SRAM 模型
- PPA
    - 避免 dcache 面积暴增，将 8 banks * 8 ways 改为 4 banks * 8 ways，但因 bank 冲突增加（约 3 倍），SPECint 下降 0.22/GHz，SPECfp 下降 0.49/GHz
    - 优化 loadunit、lsq 和 dcache 的 clock gating，memblock 的静态门控覆盖率 88.4% -> 91.9%；解决门控时钟引入的部分 VCS 仿真 X 态传播
    - 预取的异步复位优化，以缓解时序和面积（[#3229](https://github.com/OpenXiangShan/XiangShan/pull/3229)）

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/


编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
