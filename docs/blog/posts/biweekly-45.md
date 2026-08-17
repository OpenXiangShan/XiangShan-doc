---
slug: biweekly-45
date: 2024-02-05
categories:
  - Biweekly
---

# 【香山双周报 45】20240205 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 45 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流，也提前祝愿大家新年快乐，龙年大吉！

近期，昆明湖研发接近尾声，各组持续推进面积和时序的优化；前端优化了 ICacheMissUnit，后端实现 zvbb 指令并实现整数寄存器堆分 bank 读功能，访存完成向量 Unit-stride 元素合并功能，缓存新增真实访存 trace 功能。

<!-- more -->
## 近期进展

### 前端

* 实现 ICacheMissUnit 优化，实现 fetch 及 prefetch 逻辑
* 修复 ICache 的 sfence 相关 bug
* 跑通 FTB 低功耗设计的功能测试
* 完成香山前端模块面积优化初步版本评估，进行前端面积优化工作报告

### 后端流水线

* 修复 fle 指令执行时错误地写 mstatus.FS 位（[#2695](https://github.com/OpenXiangShan/XiangShan/pull/2695)）
* 实现整数寄存器堆分 bank 读功能（[#2688](https://github.com/OpenXiangShan/XiangShan/pull/2688)）
* 实现 zvbb 指令（[#2686](https://github.com/OpenXiangShan/XiangShan/pull/2686)）
* 优化整数指令 dispatch2iq 的平衡策略（[#2671](https://github.com/OpenXiangShan/XiangShan/pull/2671)）

### 访存单元

* 完成向量 Unit-stride 元素合并功能，支持合并成 64-bit，目前已通过 rvv-bench 和 riscv-vector-tests
* 完成 DCache Evict on Refill 以及 DCache Refill Hint 的 RTL 设计，在 spec int/fp 上分别取得 1.22% 和 3.18% 的收益
* 修复 vsatp 被修改后 TLB 项没有被刷干净导致连续嵌套 page fault 的 bug
* 根据覆盖率与性能评估结果缩减 LoadQueue 各项队列项数，在保持性能不变的前提下 MemBlock 缩减了 13.58% 的面积

### 缓存系统

* 修改 TL-test 的 trace 接口，实现利用 TL-test 为 L2-L3 系统发送真实的访存 trace，加快替换算法的参数迭代
* 统计 spec 程序中能被 FPC 算法压缩的数据占比
* 分析 L2 设计，构思面积与功耗优化方案

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

香山昆明湖架构研发接近尾声，性能会每月公布一次，敬请期待。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
