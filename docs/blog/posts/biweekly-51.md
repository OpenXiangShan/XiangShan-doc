---
slug: biweekly-51
date: 2024-05-13
categories:
  - Biweekly
---

# 【香山双周报 51】20240513期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 51 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端初步完成 ITTAGE 功耗优化，后端拆分浮点向量流水线和功能单元，访存与缓存各工作持续 debug 中，向量访存跑通第一个 segment 指令的 riscv-vector-test 测试。

<!-- more -->
## 近期进展

### 前端
- 完成部分 clock gating efficiency 优化（[#2981](https://github.com/OpenXiangShan/XiangShan/pull/2981)、[#2979](https://github.com/OpenXiangShan/XiangShan/pull/2979)）
- 前端面积功耗优化合并主线（[#2957](https://github.com/OpenXiangShan/XiangShan/pull/2957)、[#2956](https://github.com/OpenXiangShan/XiangShan/pull/2956)）
- 完成 ITTAGE低功耗优化，在没有间接跳转时关闭ITTAGE 
- 初步完成 ICache DataArray 细粒度划分

### 后端流水线
- 拆分浮点向量流水线和功能单元，优化向量浮点性能（[#2954](https://github.com/OpenXiangShan/XiangShan/pull/2954)）
- 实现向量 Segment 指令独占 ROB 的功能特性

### 访存与缓存
- CHI 总线
    - 搭建新版 TLTest 框架，可同时支持 Verilator 与 VCS 仿真
    - 修复 MCP2 相关的若干 bug；在 VCS + DiffTest 框架下迭代 CI 测试，目前通过 185/204
    - 修复 4 核 TLTest 压力测试下的死锁
- H扩展
    - 修复系列 gpa 相关 bug，正逐步合入主线（[#2967](https://github.com/OpenXiangShan/XiangShan/pull/2967)）
- 向量访存
    - 修复大量 VSegmentUnit 模块的 bug，跑通第一个 segment 指令的 riscv-vector-test 测试
    - 重写 Split 模块适应乱序向量访存时 redirect 刷表项问题
    - 目前可以跑通部分向量化 hmmer checkpoint，能跑通的两个较大权重 checkpoint 的 ipc 均为 1.85 左右
- 性能优化
    - 修复关键字优先的性能 bug（[#2972](https://github.com/OpenXiangShan/XiangShan/pull/2972)）
    - Temperal 预取器 meta on L2 功能修复并优化，实现 TP meta 与 data 的替换算法分离，并进行硬的路划分
    - 优化 DRRIP 替换，尝试不同的参数设置，目前性能与 PLRU 基本持平；原 L3 替换算法迁移至 L2，正在 debug
    - FPC 缓存压缩算法性能测试，对 Spec int 程序有一定的提升，对 Spec fp 基本没有提升
    - 修复 SRAM 拆分模块在多路 SRAM 下的问题
- 功耗优化
    - 持续推进 wpu 功耗异常排查和 lsq 功耗优化（[#2976](https://github.com/OpenXiangShan/XiangShan/pull/2976)、[#2928](https://github.com/OpenXiangShan/XiangShan/pull/2928)）

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/


编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
