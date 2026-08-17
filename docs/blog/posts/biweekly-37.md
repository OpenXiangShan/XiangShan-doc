---
slug: biweekly-37
date: 2023-10-16
categories:
  - Biweekly
---

# 【香山双周报 37】20231016 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 37 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发稳步推进，前端完成 FDIP 部分优化工作，后端继续推进向量功能单元，访存开始主要代码合并和时序优化等工作，缓存完成 Hint 优化和 CHI 相关的仿真测试；此外香山代码环境正式步入 chisel 6 时代，终于不用“编辑五分钟，编译一小时”了！

<!-- more -->
## 近期进展

### 前端

* 重新设计 redirect 抢拍的实现接口，前端修改对应 RTL（[#2329](https://github.com/OpenXiangShan/XiangShan/pull/2329)）
* FDIP prefetchToL2 合并主线
* 完成 FDIP ICache MSHR 减少一拍设计

### 后端流水线

* 完成 vfcvt 功能单元，支持 vfrsqrt7, vfrec7 和浮点向量指令（[#2350](https://github.com/OpenXiangShan/XiangShan/pull/2350)）
* 优化派遣的选择逻辑，平衡出队端口（[#2358](https://github.com/OpenXiangShan/XiangShan/pull/2358)，[#2359](https://github.com/OpenXiangShan/XiangShan/pull/2359)）
* 实现流水化向量复杂译码单元逻辑（[#2361](https://github.com/OpenXiangShan/XiangShan/pull/2361)）
* 虚拟化扩展单元调试，通过所有测试用例
* 优化访存指令的 uop 数量生成，无需生成 uopidx

### 访存单元

* 完成 TLB Filter 的优化和 TLB Hint 的实现（[#2366](https://github.com/OpenXiangShan/XiangShan/pull/2366)）
* 修复 BOP + delay queue 的性能 bug（[#2239](https://github.com/OpenXiangShan/XiangShan/pull/2239)）
* 代码整合：将 HybridUnit 和 BOP 虚地址预取合并到旧后端（[#2382](https://github.com/OpenXiangShan/XiangShan/pull/2382)，[#2390](https://github.com/OpenXiangShan/XiangShan/pull/2390)）
* 继续推进 VLSU 代码，实现向量访存与标量访存之间的违例处理与数据前递
* 修复部分时序问题

### 缓存系统

* 完成了对 Hint 通路的优化，并进行性能测试，提升了 Hint 的准确率
* 进行跨模块路径的时序优化
* 修复请求融合相关的 bug，并在融合 Task 处理时更新预取器训练信息
* 分析 DSU 的 CHI 接口，实现 DSU + core 的仿真测试
* 优化 LLC 中的替换算法，正在进行功能测试
* 运行并调试四核香山

### 工具

* 支持 Chisel 6 + CIRCT 生成 verilog，加快 verilog 生成速度。其中，在 EPYC 服务器上，香山 master 分支生成 DefaultConfig 配置的 verilog 由原先的约 70 分钟缩短至约 5 分钟；在 12900K 上，由 15 分钟缩短至 2 分半（[#2372](https://github.com/OpenXiangShan/XiangShan/pull/2372)）

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
