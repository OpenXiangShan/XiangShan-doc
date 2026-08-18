---
slug: biweekly-43
date: 2024-01-08
categories:
  - Biweekly
---

# 【香山双周报 43】20240108 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 43 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发接近尾声，各组持续推进时序优化和验证文档；前端实现部分 ICache 优化，后端统一了快速推测唤醒，访存关键字优先合入主线，缓存实现 skewed 缓存压缩算法。

<!-- more -->
## 近期进展

### 前端

* ICache SRAM 划分方式优化并修复遗留性能 bug（[#2604](https://github.com/OpenXiangShan/XiangShan/pull/2604)，[#2605](https://github.com/OpenXiangShan/XiangShan/pull/2605)）
* 继续推进昆明湖验证文档工作，完成 BPU top、RAS、FTQ 验证文档
* 实现 ICache cacheline 划分、miss 减拍等功能（[#2609](https://github.com/OpenXiangShan/XiangShan/pull/2609)）

### 后端流水线

* 完成整数指令派遣时序性能优化，减少派遣冲突（[#2614](https://github.com/OpenXiangShan/XiangShan/pull/2614)）
* 去除 load 指令写回唤醒，所有指令唤醒采取快速推测唤醒（[#2615](https://github.com/OpenXiangShan/XiangShan/pull/2615)）
* 新后端合并 master 分支，已修复所有跑 checkpoint 过程中出现的 bug
* Slow fast entry 混合的 IQ 性能调试完成，满足时序和性能要求

### 访存单元

* 修复关键字优先引入的 FMA bug，并合入 master（[#2562](https://github.com/OpenXiangShan/XiangShan/pull/2562)）
* 在 L2-L1 D 通道的 Bank 选择优先级上引入请求 Stall 的因素，milc 性能提升
* 完成向量访存例外测试；rvv-bench 目前跑通了 8/11
* 继续推进时序优化和验证文档

### 缓存系统

* 发现 LLC 性能计数器统计存在问题，修复后继续分析 LLC 替换算法在 mcf 上性能下降的原因
* skewed 缓存压缩算法完成实现，测试性能符合预期，在 milc 上有较大提升，在 mcf 等程序上有一定程度下降
* 继续推进 L2 验证文档

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

香山昆明湖架构研发接近尾声，性能会每月公布一次，敬请期待。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
