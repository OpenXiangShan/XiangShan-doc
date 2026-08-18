---
slug: biweekly-34
date: 2023-08-28
categories:
  - Biweekly
---

# 【香山双周报 34】20230828 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 34 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

近期，昆明湖研发稳步推进，前端修复部分时序问题，后端逐步推进向量浮点功能和 H 扩展工作，访存近期集中在通路优化、预取改进和部分向量代码合并等工作，缓存继续推进 CHI 和请求融合工作。

<!-- more -->
## 近期进展

### 前端

* FTB read 到替换算法时序优化合并（[#2227](https://github.com/OpenXiangShan/XiangShan/pull/2227)）
* 重新引入南湖架构寄存器复制并合并到主线（[#2254](https://github.com/OpenXiangShan/XiangShan/pull/2254)）
* FDIP 将 ICache 中多路数据的选择逻辑部分移动至前级流水线从而优化时序（[#2255](https://github.com/OpenXiangShan/XiangShan/pull/2255)）
* uop Cache 性能 bug 初步解决

### 后端流水线

* 实现了 RAB 重命名快照功能
* 修复了 ROB 压缩引入的浮点指令 wflags 的 bug（[#2241](https://github.com/OpenXiangShan/XiangShan/pull/2241)）
* 实现了将标量浮点指令转到向量浮点运算单元执行（[#2247](https://github.com/OpenXiangShan/XiangShan/pull/2247)）
* 实现了 LUI 和 ADDI 的指令融合
* 基本完成了为适配 H 扩展进行的 L1TLB 修改

### 访存单元

* L2 虚地址 BOP 预取添加 ReqFilter（[#2239](https://github.com/OpenXiangShan/XiangShan/pull/2239)）
* 优化预取器，将 Stride 的训练地址单位从 Block 改为 Byte
* 在 L1 增加评估预取的计数器（[#2229](https://github.com/OpenXiangShan/XiangShan/pull/2229)）
* 继续合并部分向量访存代码（[#2237](https://github.com/OpenXiangShan/XiangShan/pull/2237)）
* 将新访存设计（2 条 load 流水线、2 条 store 流水线、1 条混合流水线）合入新后端，协调后端保留站设计
* 指令融合 rtl 代码修改完成，待合入新后端调试

### 缓存系统

* 改进 TileLink to CHI 转接桥控制部分，修复若干 bug 后能通过简单测试，正在添加更多的总线信号
* 请求融合 Acquire → Late Prefetch 机制完成代码编写，正在进行测试
* 优化了 L2 partition 的时序

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

## 相关链接

* https://xiangshan-doc.readthedocs.io/

编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
