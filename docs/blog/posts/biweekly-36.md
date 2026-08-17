---
slug: biweekly-36
date: 2023-09-25
categories:
  - Biweekly
---

# 【香山双周报 36】20230925 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 36 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发稳步推进，前端修复部分 bug，后端目前着手于 BusyTable、快速反馈重定向、流水化 CVT 等优化点，访存稳步推进向量访存和预取相关优化，缓存已完成 CHI-TileLink 的顶层电路。

<!-- more -->
## 近期进展

### 前端

* 修复 Predecode 部分时序问题（[#2291](https://github.com/OpenXiangShan/XiangShan/pull/2291)）
* 修复 IFU 的 redirect 的 predecode 检查指令有效性问题（[#2300](https://github.com/OpenXiangShan/XiangShan/pull/2300)）
* 修复 BPU 模块的 target 通路时序问题（[#2324](https://github.com/OpenXiangShan/XiangShan/pull/2324)）
* 实现 FTQ 中提前一拍接收后端的 redirect 信号，减少 redirect penalty（[#2329](https://github.com/OpenXiangShan/XiangShan/pull/2329)）

### 后端流水线

* 实现推测 BusyTable，以支持快速唤醒和取消（[#2290](https://github.com/OpenXiangShan/XiangShan/pull/2290)）
* 重构 PcTargetMem，修复 Jump 误预测问题（[#2318](https://github.com/OpenXiangShan/XiangShan/pull/2318)）
* 实现提前一拍反馈重定向信号给前端（[#2329](https://github.com/OpenXiangShan/XiangShan/pull/2329)）
* 流水化 CVT 模块，使其多拍完成，优化时序

### 访存单元

* 完成向量访存 Load Flow Queue 的代码、向量访存测试环境的搭建，向量 Store 新方案正在开发中
* 完成 TLB 结构变化的修改（[#2289](https://github.com/OpenXiangShan/XiangShan/pull/2289)）
* 设计 Load 地址预测算法
* 探索和实现 Indirect Memory Prefetcher
* 完成 Stride 的动态调控机制
* 完成 BOP with delay queue 的代码（[#2239](https://github.com/OpenXiangShan/XiangShan/pull/2239)）
* 实现 SMS 预取优化（[#2314](https://github.com/OpenXiangShan/XiangShan/pull/2314)）

### 缓存系统

* 定位并解决请求融合的性能 bug，请求融合合入主线（[#2337](https://github.com/OpenXiangShan/XiangShan/pull/2337)）
* 包含 CHI-TileLink 转接桥的顶层电路搭建完成，能够跑通简单 case
* 正在进行 L2→L1 Hint 设计优化，确保 Hint 的准确性

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
