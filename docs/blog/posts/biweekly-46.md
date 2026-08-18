---
slug: biweekly-46
date: 2024-03-04
categories:
  - Biweekly
---

# 【香山双周报 46】20240304 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 46 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发接近尾声，各组持续推进面积、时序、功耗的优化。此外，前端优化了 ITTAGE；后端完成新后端代码整理，并支持 3load3store 配置；访存完成 128 bits 访存通路初步验证；缓存搭建了 CHI-CoupledL2 代码框架及参数系统。

<!-- more -->
## 近期进展

### 前端

* 前端 BPU 模块和 IFU 模块实现 clock gating（[#2733](https://github.com/OpenXiangShan/XiangShan/pull/2733)、[#2734](https://github.com/OpenXiangShan/XiangShan/pull/2734)）
* 优化 ITTAGE entry，ITTAGE validArray 并入 SRAM（[#2705](https://github.com/OpenXiangShan/XiangShan/pull/2705)）
* 修复 IFU 的 MMIO 重定向时偶发 bug（[#2704](https://github.com/OpenXiangShan/XiangShan/pull/2704)）

### 后端流水线

* 完成新后端不同分支代码的合并
* 新版后端支持 3 load - 3 store 配置（[#2739](https://github.com/OpenXiangShan/XiangShan/pull/2739)）
* 推进功耗优化，后端静态门控覆盖率提升至 95.4%（[#2729](https://github.com/OpenXiangShan/XiangShan/pull/2729)）

### 访存单元

* 完成 128 bits 访存通路的初步验证；推进向量化 hmmer 的调试。
* L2 BOP 实现 delay queue，SPEC2006 FP 性能提升 1.91%
* 时序修改阶段性同步主线（[#2724](https://github.com/OpenXiangShan/XiangShan/pull/2724)）
* 继续推进面积优化（[#2678](https://github.com/OpenXiangShan/XiangShan/pull/2678)）
* 开展功耗优化，优化访存模块的静态门控覆盖率（[#2743](https://github.com/OpenXiangShan/XiangShan/pull/2743)）

### 缓存系统

* 搭建 CHI-CoupledL2 代码框架及参数系统
* 修改 TL-Test 框架，增加自定义 trace 导入、命中率计算的功能
* 继续推进缓存压缩的 RTL 实现
* 评估面积优化的冗余单元
* 在模拟器上初步实现可配置 Cache-BP

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

香山昆明湖架构研发接近尾声，性能会每月公布一次，敬请期待。

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
