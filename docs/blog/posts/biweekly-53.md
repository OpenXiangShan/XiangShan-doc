---
slug: biweekly-53
date: 2024-06-12 
categories:
  - Biweekly
---

# 【香山双周报 53】20240612期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 53 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端完成 new ICache 的实现，后端完成 v0 和 vl 拆分，访存模块正在实现新版 CHI-L3 基础框架并建立仓库，实现相关缓存子系统的 TL-test 测试环境搭建。

<!-- more -->
## 近期进展

### 前端

* 完成 new ICache 实现（[#3051](https://github.com/OpenXiangShan/XiangShan/pull/3051)）
* 修复 IFU 的 MMIO 相关 bug（[#3038](https://github.com/OpenXiangShan/XiangShan/pull/3038)）
* 预测器中 pc 分高低位实现 CGE（[#3027](https://github.com/OpenXiangShan/XiangShan/pull/3027)）

### 后端流水线

* v0 和 vl 拆分为独立重命名表和物理寄存器堆（[#3040](https://github.com/OpenXiangShan/XiangShan/pull/3040)）
* 继续优化后端时序（[#3052](https://github.com/OpenXiangShan/XiangShan/pull/3052)、[#3018](https://github.com/OpenXiangShan/XiangShan/pull/3018)）
* 修复浮点开方时涉及到的 NaN 类型错误问题（[#3047](https://github.com/OpenXiangShan/XiangShan/pull/3047)）
* 修复高位非全零时，f2v boxing 错误的问题（[#3035](https://github.com/OpenXiangShan/XiangShan/pull/3035)）

### 访存与缓存

* CHI 总线
    * 正在实现新版 CHI-L3 基础框架，建立 GitHub 仓库（[OpenXiangShan/OpenLLC](https://github.com/OpenXiangShan/OpenLLC)）
    * 完成 CoupledL2-OpenLLC 缓存子系统的 TL-test 测试环境搭建（[OpenXiangShan/tl-test-new](https://github.com/OpenXiangShan/tl-test-new)）
* H扩展
    * 为 NEMU 添加 Zicntr、Zihpm 支持（[NEMU#350](https://github.com/OpenXiangShan/NEMU/pull/350)）
* 向量访存
    * 继续优化时序，目前时序违例从 -160ps 收敛到 -86ps
    * 修复部分逻辑 bug 和仿真 X 态 bug
    * 初步性能测试中，向量化 hmmer 分数从 13.04/GHz 提升到 15.33/GHz，向量化 libquantum 出现显著性能下降，正在进一步确认和测试。
* 性能优化
    * 利用 Trace TL-Test 微观分析 TP meta on L2 实现，修复若干 bug，利用 RRIP 进行替换管理，目前测试结果发现 TP 预取并没有充分发挥性能作用，正在继续优化
    * 通过对软件模拟- RTL 仿真的替换路选择结果进行对比，定位到多个 Hawkeye 替换相关的 bug
    * Tubins 替换经测试，在 L2 中 SPEC 性能比 PLRU 高 0.03%，在 L3 中比 PLRU 高 0.3%
* 功耗优化
    * LSQ 门控修改合入主线
    * 修复门控工具中的仿真 X 态 bug

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

**News**: 香山开源技术讨论 QQ 群人数首破 500，感谢大家关注，也欢迎新人进群和香山开源爱好者一起交流！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/


编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
