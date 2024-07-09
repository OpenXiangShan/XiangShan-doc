---
slug: biweekly-55
date: 2024-07-08
categories:
  - Biweekly
---

# 【香山双周报 55】20240708期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 55 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端 ICache 重构已合入主线，后端正在实现寄存器堆 Cache，访存完成 DummyLLC 和香山的集成并合入主线，MMU Sv48 基本完成并通过 AM 简单测试。

<!-- more -->
## 近期进展

### 前端

* 功能
    * 修复 IPrefetch 没有取消掉已经被 MainPipe 重填的 miss 请求的 bug（[#3122](https://github.com/OpenXiangShan/XiangShan/pull/3122)）
* 面积
    * PageFault 编码从独热码改成 2 bit 的编码（[#3104](https://github.com/OpenXiangShan/XiangShan/pull/3104)）
    * 完成 WayLookup 面积裁剪，实现提前选择 gpaddr（[#3139](https://github.com/OpenXiangShan/XiangShan/pull/3139)）
* 功耗
    * 完成 Clock Gating Efficiency 优化点分析，继续推进 Clock Gating Efficiency 优化
    * 初步完成 ITTage 功耗优化，实现 ITTage 后移（[#3092](https://github.com/OpenXiangShan/XiangShan/pull/3092)），正在进行进一步优化
    * ICache 重构合入主线（[#3051](https://github.com/OpenXiangShan/XiangShan/pull/3051)）
* 性能
    * 初步完成 RAS 性能 bug 修复，评估性能收益中

### 后端流水线
* 将 csrr vlenb 转译为 addi 指令，提升向量程序性能（[#3143](https://github.com/OpenXiangShan/XiangShan/pull/3143)）
* 修复重命名表地址位宽与实际不匹配的问题（[#3128](https://github.com/OpenXiangShan/XiangShan/pull/3128)，first-time contributor @Squareless-XD）
* 持续推进后端时序优化（[#3145](https://github.com/OpenXiangShan/XiangShan/pull/3145)、[#3127](https://github.com/OpenXiangShan/XiangShan/pull/3127)、[#3120](https://github.com/OpenXiangShan/XiangShan/pull/3120)、[#3106](https://github.com/OpenXiangShan/XiangShan/pull/3106)、[#3105](https://github.com/OpenXiangShan/XiangShan/pull/3105)）和 bug 修复（[#3151](https://github.com/OpenXiangShan/XiangShan/pull/3151)、[#3150](https://github.com/OpenXiangShan/XiangShan/pull/3150)、[#3137](https://github.com/OpenXiangShan/XiangShan/pull/3137)、[#3135](https://github.com/OpenXiangShan/XiangShan/pull/3135)、[#3131](https://github.com/OpenXiangShan/XiangShan/pull/3131)、[#3124](https://github.com/OpenXiangShan/XiangShan/pull/3124)、[#3117](https://github.com/OpenXiangShan/XiangShan/pull/3117)、[#3116](https://github.com/OpenXiangShan/XiangShan/pull/3116)、[#3111](https://github.com/OpenXiangShan/XiangShan/pull/3111)、[#3109](https://github.com/OpenXiangShan/XiangShan/pull/3109)、[#3107](https://github.com/OpenXiangShan/XiangShan/pull/3107)、[#3101](https://github.com/OpenXiangShan/XiangShan/pull/3101)、[#3100](https://github.com/OpenXiangShan/XiangShan/pull/3100)）
* 正在实现寄存器堆 Cache，用于降低 RegFile 读口

### 访存与缓存
* CHI 总线
    * 完成 DummyLLC 和香山的集成，跑通 linux-hello 并合入主线（[#3129](https://github.com/OpenXiangShan/XiangShan/pull/3129)）
    * CHI-L3 完成 MainPipe 模块 s2-s6 流水级设计，完成全部 AXI 写通道的正向设计
* 向量访存
    * 移植联想提供的向量性能测例（向量乘法和 softmax）到 AM 上
    * 性能分析发现 dispatch 拥塞严重，并修复 csrr 读取只读寄存器清空流水的问题
* 功能
    * MMU Sv48 有关的RTL修改基本完成，已通过 AM 的简单测试样例
* 性能
    * 修复 MSHR 多端口入队有关的 bug
    * 着手 Berti 硬件实现
    * 旧版 TP L3 设计在新 gcc12 的 checkpoint 上调整参数进行了一系列测试，SPEC Int 提升 0.17 分，总分提升 0.09
    * 新版 TP meta on L2 尝试优化 metaTable 的替换算法，用 BRRIP/DRRIP 代替 random 算法，有一定正向提升，但 GemsFDTD 下降严重；新增动态开关功能，相较于无动态开关，总体性能有 0.1% 的提升
    * L2-tubins 在 kunminghu 分支上对性能提升 0.11% ，正在迁移到 master 进行测试
    * CHROME 框架完成实现，在性能测试程序中，除了 libquantum 分数有明显提升，其他多数程序有下降，有待进一步调试。
    * 发现 DRRIP 中关于 set dueling 采样的 bug ，修复后对 mcf 有 3% 的性能提升
* 时序
    * 修复 BOP Mem2cgt 引入的关键路径及 L2 其它关键路径，违例 -150ps 优化到 -50ps 左右

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/


编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
