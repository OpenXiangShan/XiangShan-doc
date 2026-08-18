---
slug: biweekly-41
date: 2023-12-11
categories:
  - Biweekly
---

# 【香山双周报 41】20231211 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 41 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发接近尾声，各组持续推进面积和时序的优化；前端开始着手验证文档，后端 Hybrid Unit 性能优化基本完成，访存实现向量 MMIO 访存，缓存持续推进四核修复和 CHI 测试。

<!-- more -->
## 近期进展

### 前端

* 完成 ICache SRAM 拆分，优化 IFU 的 RTL 代码
* 继续推进 FTQ 面积压缩工作
* 开始完善前端模块验证文档

### 后端流水线

* Hybrid Unit 性能优化基本完成，相较添加 Hybrid Unit 前约有 1.2% 的性能提升
* 写 0 号整数寄存器时，不再占用寄存器堆写口（[#2526](https://github.com/OpenXiangShan/XiangShan/pull/2526)）
* 去除 load 以外的写回唤醒，优化时序面积（[#2515](https://github.com/OpenXiangShan/XiangShan/pull/2515)）
* 去除 rename 和 dispatch 之间的寄存器，减小一拍流水线深度（[#2522](https://github.com/OpenXiangShan/XiangShan/pull/2522)）

### 访存单元

* 实现 MMIO 空间的向量访存
* 在 NEMU 上跑通 rvv-bench 测试集
* 完成关键字优先的初版性能评估并修复其与 L2 Hint 有关的 bug，目前在 milc 有明显性能提升

### 缓存系统

* 定位并修复四核 litmus test 的两个卡死 bug 和一个数据错 bug
* TL-Test 功能增强，可以将 trace 作为输入激励
* 缓存压缩尝试实现 Skewed Compressed Cache，修改 LLC 目录为斜相连结构，正在进行测试
* CHI 转接桥接入系统测试，触发 bug，正在定位问题

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

香山昆明湖架构研发接近尾声，性能会每月底公布一次，敬请期待。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
