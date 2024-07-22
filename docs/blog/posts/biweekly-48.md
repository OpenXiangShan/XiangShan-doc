---
slug: biweekly-48
date: 2024-04-01
categories:
  - Biweekly
---

# 【香山双周报 49】20240401期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 48 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖研发接近尾声，各组持续推进面积、时序、功耗的优化。此外，前端展开 FTB 功耗评估；后端完成新后端合并主线的 RTL bug 修复和 ROB 重构；访存完成 H 扩展大部分调试和 VLSU 初版重构；缓存完成 CHI - CoupledL2 初版设计，实现四核 TL-Test 验证框架。

<!-- more -->
## 近期进展

### 前端
- 完成昆明湖分支前端模块面积裁剪 & clock gating 合并提交（[#2806](https://github.com/OpenXiangShan/XiangShan/pull/2806)）
- 完成 FTB 低功耗设计性能数据获取及功耗评估

### 后端流水线
- 修复合并后产生的多核 difftest 等错误，基本完成新后端合并主线，等待提交（[#2814](https://github.com/OpenXiangShan/XiangShan/pull/2814)）
- 定位浮点推测唤醒失效的问题，修复后浮点性能提升约 32.38%，达到 master 水平（[#2830](https://github.com/OpenXiangShan/XiangShan/pull/2830)）
- ROB 重构完成，已合入新后端，时序面积已达标（[#2820](https://github.com/OpenXiangShan/XiangShan/pull/2820)）
- 写回向量浮点寄存器时序优化，延迟一拍写回寄存器堆（[#2824](https://github.com/OpenXiangShan/XiangShan/pull/2824)）

### 访存单元
- Xvisor 和 KVM 成功启动虚拟机，并从硬件侧和软件侧分别着手将 H 扩展合入香山主线。
- VLSU 重构的基本通路已经完成并开始调试，修改 difftest 框架以适配 VLSU 128-bit 粒度的 Store 指令提交。
- 模块级门控在 LoadQueue 上的设计实现并开始调试。
- 访存流水线 3ld2st 版本优化后面积减少 3.28%。

### 缓存系统
- 完成 CHI-CoupledL2 初版 RTL 设计，推进 TL-Test 验证环境的搭建。
- L2 Data SRAM 读改为 Multicycle Path 2，通过功能测试且对性能影响较小。
- L2 新版 Hint 设计合入 CoupledL2 主线。
- 实现四核 TL-Test 验证框架，成功发现并修复 L2 bug。
- 评估 L2/L3 上实现缓存压缩的潜在性能收益，计划将缓存压缩实现到 L2 中。

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/


编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
