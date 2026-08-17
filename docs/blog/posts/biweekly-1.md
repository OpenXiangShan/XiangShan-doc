---
slug: biweekly-1
date: 2021-10-04
categories:
  - Biweekly
---

# 【香山双周报 1】20211004 期

欢迎来到我们的新专栏。今天是香山双周报专栏的第 1 期，之后我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

<!-- more -->
## 近期进展

### 前端

* [#1036](https://github.com/OpenXiangShan/XiangShan/pull/1036)：修复了 FTQ 中产生 False Hit 的 Bug

    mcf 测试中不再有 false hit 了（手动撒花）

* [#1057](https://github.com/OpenXiangShan/XiangShan/pull/1057)：uBTB 的组织形式从全相联改为直接相联
* [#1065](https://github.com/OpenXiangShan/XiangShan/pull/1065)：修复了 MMIO 地址空间取指没有标记异常的问题

    由于新前端还未添加 MMIO 地址空间取指的逻辑，所以前端实际上无法正确取指。当分支预测给出了 MMIO 地址空间内的跳转目标，IFU 可能会发出 MMIO 地址空间内的取指请求，造成错误。我们暂时将 MMIO 地址空间内的取指标记了 access fault 异常，很快将恢复 MMIO 地址空间取指的支持。

### 后端

* [#1019](https://github.com/OpenXiangShan/XiangShan/pull/1019)：合入了新的整型除法器，采用 SRT16 算法

    SRT16 算法实现来自于 hyf6661669 ([XS-Verilog-Library#2](https://github.com/OpenXiangShan/XS-Verilog-Library/pull/2))。

* [#1042](https://github.com/OpenXiangShan/XiangShan/pull/1042)：保留站支持对 FMA 指令的发射逻辑优化

    FMA 指令包含了乘加两步，当乘法操作数就绪时，即可发射到执行单元，中间计算结果返回保留站；而后，当加法操作数就绪时，指令第二次发射进行加法运算。这一优化能够降低 FMA 指令的实际执行延迟。CI 中的 povray 片段显示，FMA 指令的平均运算延迟从 5 拍降低到了 3.54 拍。

* [#1052](https://github.com/OpenXiangShan/XiangShan/pull/1052)：优化了 Freelist 的时序

    同时减少了 Chisel 翻译出的 verilog 代码长度。

* [#1054](https://github.com/OpenXiangShan/XiangShan/pull/1054)：将 RVC mv 指令译码至 addi

    根据 RISC-V 手册，mv 伪指令是用 addi 实现的，我们的 move 消除 (move elimination) 设计同样假设 mv 是用 addi 的伪指令实现。然而，从我们使用的 rocket-chip 里面的 RVC 指令展开器来看，压缩的 mv 指令被展开到了 add。为了更好地实现 move 指令消除，我们将 mv 指令改为展开到了 addi 指令。

* [#1059](https://github.com/OpenXiangShan/XiangShan/pull/1059)：添加了对 zbk{b,c,x} 扩展的支持

    这是计算所作为 RISC-V 基金会发展伙伴 (development partner)，承担的指令集扩展验证工作之一。我们将在后续完善对 K 扩展其他部分的支持。

* [#1061](https://github.com/OpenXiangShan/XiangShan/pull/1061)：优化了 aluOpType 的编码，减少了长度
* [#1064](https://github.com/OpenXiangShan/XiangShan/pull/1064)：保留站中存储 JALR 所需的 PC

    JALR 指令的运算需要寄存器值、PC、立即数，判断是否误预测需要前端给出的预测目标地址。我们目前的实现是在保留站中存储寄存器值和前端预测跳转目标地址，PC 有一个独立的存储空间来保存。由于更早之前保留站的修改，导致这一存储空间被去掉了，PC 会通过流水线一级级传下来，造成了一定的浪费。我们暂时恢复了专为 PC 设置的存储空间，同时添加了对流水线中 PC 域的强制性回归检查，这一设计待后续再进行优化调整。

* [#1072](https://github.com/OpenXiangShan/XiangShan/pull/1072)：调整 ROB 大小为 256，物理寄存器堆大小为 192
* [#1080](https://github.com/OpenXiangShan/XiangShan/pull/1080)：重新组织了保留站，执行单元和寄存器堆

    恢复了 14 读 8 写的寄存器堆配置，Load Queue 调整为 80 项，Store Queue 调整为 64 项。

### 缓存

* [#1051](https://github.com/OpenXiangShan/XiangShan/pull/1051)：DCache 增加至 128KB，L2 & L3 Cache 采用 non-inclusive 策略

    我们在硬件上支持了对别名的处理，在保持分路数量不变的情况下，允许 DCache 有更大的容量。我们同时更新了 HuanCun 子模块，支持了 non-inclusive L2 和 L3。

* [#1070](https://github.com/OpenXiangShan/XiangShan/pull/1070)：DCache 添加参数 alwaysReleaseData，控制是否“总是释放数据”
* [#1083](https://github.com/OpenXiangShan/XiangShan/pull/1083)：L2 Cache 添加了对 multi-bank 的支持

### 测试与验证

* [#1062](https://github.com/OpenXiangShan/XiangShan/pull/1062)：CI（持续集成测试）中增加了外部中断的测试
* [#1074](https://github.com/OpenXiangShan/XiangShan/pull/1074)：CI 中添加了 cache alias 的测试

本周是国庆假期，香山的工作也来到了一个阶段性的时间节点，我们将在最近完成南湖版本新功能的冻结，并全面转向时序优化与收敛的工作。

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

编辑：张紫飞、徐易难
