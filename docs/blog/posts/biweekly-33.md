---
slug: biweekly-33
date: 2023-08-14
categories:
  - Biweekly
---

# 【香山双周报 33】20230814 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 33 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发稳步推进，前端修复部分时序问题，后端完成 IQ 重构代码并逐步推进向量浮点功能和 H 扩展工作，访存近期集中在通路优化、预取改进和部分向量代码合并等工作，缓存 refill 选择替换路工作合入主线。

<!-- more -->
## 近期进展

### 前端

* 在预取部分将从 ICache Meta 中读到的数据打一拍再进行后续处理，修复相关时序问题（[#2233](https://github.com/OpenXiangShan/XiangShan/pull/2233)）
* 在 ICache 中将一些 ready 信号与中间信号解耦，降低 ready 信号延迟
* 完成 BPU 中 FTB read 到替换算法更新的时序问题修复
* uop cache 模拟器初步实现，需继续探索性能问题

### 后端流水线

* IssueQueue 重构完成，减小了 IQ 入队和 IQ 间唤醒的扇出（[#2240](https://github.com/OpenXiangShan/XiangShan/pull/2240)）
* ROB 压缩功能重构测试完成（[#2192](https://github.com/OpenXiangShan/XiangShan/pull/2192)）
* 优化寄存器堆相关参数计算和传递逻辑（[#2218](https://github.com/OpenXiangShan/XiangShan/pull/2218)）
* 开始将浮点标量指令转到向量浮点功能单元执行
* L2TLB 中 ptw、llptw、hptw 以及 page cache 修改完成，正在修改 L1TLB
* 完成在 NEMU 上 PMPtable 功能的实现，通过随机测试。

### 访存单元

* 访存通路

    * load 流水线增加在 s2 前递总线数据的能力，之前只存在于 s1（s 表示流水级）（[#2238](https://github.com/OpenXiangShan/XiangShan/pull/2238)）
    * 将 PTW 移动到 Memblock 内（[#2211](https://github.com/OpenXiangShan/XiangShan/pull/2211)）

* 预取

    * 改进 stride 预取，在 milc 上有一定性能收益
    * 增加预取到 L3 的通路，初步评估
    * L2 BOP 虚地址空间训练初版方案已实现（[#2239](https://github.com/OpenXiangShan/XiangShan/pull/2239)）

* 功能

    * 继续合并部分向量访存代码（[#2237](https://github.com/OpenXiangShan/XiangShan/pull/2237)）

* 修复几个性能 bug：L2 Hint 相关、预取相关

### 缓存系统

* “refill 选择替换路”成功通过所有测试，合入主线，评估有较大性能收益（[#2232](https://github.com/OpenXiangShan/XiangShan/pull/2232)）
* 利用 ChiselDB 记录的访问 trace，软件分析最优替换和预取感知下的 miss rate，探索替换的提升空间
* 开始实现 TileLink to CHI 转接桥，完成了请求通路的控制逻辑部分

### 工具

* 实现了 XSPerfRolling，能够将性能计数器按照时间维度展开（[#2228](https://github.com/OpenXiangShan/XiangShan/pull/2228)）

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

## 相关链接

* https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
