---
slug: biweekly-39
date: 2023-11-13
categories:
  - Biweekly
---

# 【香山双周报 39】20231113 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 39 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发接近尾声，前端继续优化面积和时序，后端合并 HybridUnit 到新后端并通过 debug module 单核调试，访存 TLB 和 SMS 优化合入主线，向量访存有了阶段性成果，缓存上完成时序优化并跑通部分多核测试。此外，逐步开展了 FPGA 和硬件仿真加速器的联合调试。

<!-- more -->
## 近期进展

### 前端

* 裁剪前端 FTQ 模块面积（[#2453](https://github.com/OpenXiangShan/XiangShan/pull/2453)）
* 优化前端 debug 相关模块面积（[#2424](https://github.com/OpenXiangShan/XiangShan/pull/2424)）

### 后端流水线

* debug module 单核调试通过，完成多核启停测试
* HybridUnit（同时支持 load 和 store）接入新版后端完成，基本测试通过（[#2471](https://github.com/OpenXiangShan/XiangShan/pull/2471)）
* 优化 Issue 流水线中的取消路径时序，通过基本回归测试
* 完成复杂指令的 i2v 通路修改，支持所有 opivi 指令（[#2463](https://github.com/OpenXiangShan/XiangShan/pull/2463)）

### 访存单元

* 将 TLB new Filter 和 TLB Hint 合入主线，在 gcc12 -o3 SPECint 上有约 0.1 分的提升（[#2366](https://github.com/OpenXiangShan/XiangShan/pull/2366)）
* 将 SMS AGT Fast Evict 合入主线，在 SPECint 上有微小的提升（[#2437](https://github.com/OpenXiangShan/XiangShan/pull/2437)）
* 向量访存跑通所有非 Segment 测试（Unit-Stride + Strided + Indexed）
* L1-L2 总线改造跑通 CoreMark
* 修复 RAR 违例可能陷入活锁的 bug
* 修复访存部分时序

### 缓存系统

* Hint 优化完成性能评估，有一定性能提升但暂不合入主线
* L2 模块内时序优化基本完成，跨模块时序违例还在修复中
* 继续进行多核验证，双核/四核跑通部分 litmus test，正在定位出错点原因

### 其他

* 成功将 difftest 框架移植到硬件仿真加速器上运行并进行优化，利用 Trace 合并、批处理、非阻塞通信等方法，目前差分测试仿真速度达到 0.86MHz，正在进一步优化中
* FPGA 与硬件仿真加速器联合调试，目前在 FPGA 上已跑通 SPEC

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

香山昆明湖架构研发接近尾声，性能会每月底公布一次，敬请期待。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
