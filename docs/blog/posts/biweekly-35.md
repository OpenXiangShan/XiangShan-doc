---
slug: biweekly-35
date: 2023-09-11
categories:
  - Biweekly
---

# 【香山双周报 35】20230911 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 35 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发稳步推进，前端稳步推进时序和性能的双向优化，后端实现了 CVT FP16 和部分 load 优化，访存 L1 预取工作合入主线并着手向量访存重写工作，缓存重构了 TileLink-CHI 转接口。

<!-- more -->
## 近期进展

### 前端

* 修复 uop Cache 替换算法和错误检查命中指令大小的性能问题和功能问题
* 落实 BPU 中 ITTAGE 预测算法的更新优化点
* TAGE 优化点模拟器实现，评估性能收益
* 优化迭代 RTL 时序，分析 mcf 性能瓶颈

### 后端流水线

* 实现乱序 vfreduction 指令（[#2274](https://github.com/OpenXiangShan/XiangShan/pull/2274)）
* 实现 load 指令的推测唤醒和取消（[#2286](https://github.com/OpenXiangShan/XiangShan/pull/2286)）
* 实现 CVT FP16，完成功能验证
* 优化 lui + addi 指令融合实现，启用 lui + load 指令融合（[#2271](https://github.com/OpenXiangShan/XiangShan/pull/2271)）

### 访存单元

* L1 预取合入主线（[#2261](https://github.com/OpenXiangShan/XiangShan/pull/2261)）
* Hybrid unit 合进新后端较稳定的分支
* 解决仿真随机性问题（[#2269](https://github.com/OpenXiangShan/XiangShan/pull/2269)）
* 修改 BOP 中的 ReqBuffer，取得较大性能收益（[#2239](https://github.com/OpenXiangShan/XiangShan/pull/2239)）
* 向量访存重写，已完成 Load Uop Queue 代码
* 修复 ForwardCache 和 SMS 的 bug

### 缓存系统

* 修复了双核数据错 bug 和 GrantBuf 溢出 bug，重构 GrantBuf（[#2270](https://github.com/OpenXiangShan/XiangShan/pull/2270)）
* 请求融合 Acquire –> Late Prefetch 成功通过测试，正在进行性能分析
* 重构 TileLink-CHI 转接口，完成代码，修改了状态机解决死锁问题，添加依赖电路解决冲突问题
* 完成 GrantBuf 和 s4/s5 级的 L2→L1 重填 Hint 信号计算

### 工具

* TopDown 性能分析工具支持 Rolling（[#2280](https://github.com/OpenXiangShan/XiangShan/pull/2280)）
* DiffTest 差分测试代码完成重构，支持基于 Chisel 源码自动生成 C++ 配置文件，并支持覆盖率引导的模糊测试流程（[#2284](https://github.com/OpenXiangShan/XiangShan/pull/2284)）

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
