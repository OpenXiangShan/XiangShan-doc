---
slug: biweekly-11
date: 2022-06-13
categories:
  - Biweekly
---

# 【香山双周报 11】20220613 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 11 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

距离上一次双周报已经有一段时间了，我们在这期间完成了香山第二版南湖微架构的系统级验证与 FPGA 原型验证，目前代码稳定即将流片。香山团队已经联合多家企业并行地启动两个项目，分别是第三版昆明湖微架构的设计与实现，以及南湖微架构的产品化改造。

根据规划，下一版昆明湖架构将实现 RISC-V Vector 扩展，同时进行性能优化迭代，期待在先进工艺下达到 SPEC CPU 2006 45 分@3GHz 的较高水平。这一版我们也将会与更多的第三方企业进行深入合作，实现开源平台下的协同创新。

南湖架构产品化改造则是一个全新的项目类型，我们将会与企业合作，以工业级产品的要求对南湖架构进行更加细致的验证与优化，期待早日能见到基于香山的产品面市。

从本期开始，双周报将会分为两个部分，分别介绍香山昆明湖架构开源主线和南湖产品化改造项目的开发进展。

<!-- more -->
## 近期进展

### 前端

* **BPU 部分：**

    * 修复 ITTAGE target 写入存在不定态的 bug
    * 修复 uBTB fallThruPred 的 waymask 恒 1 bug
    * 修复 TAGE、ITTAGE 中 SRAM 的 ridx 非预期变化 bug
    * 修复 TAGE 中 SRAM waymask 端口未使用 bug

* **ICache 部分：**

    * 修复 ICache 关闭 ECC 时 DataArray 宽度不匹配 bug

* **FTQ 部分：**

    * 修复 FTBEntryGen 中 last\_may\_be\_rvi\_call 逻辑

### 后端流水线

* **后端架构设计讨论：添加 V 扩展的新香山后端设计**

    * **V 拓展有两种实现方式，核内紧耦合与核外松耦合。目前我们围绕核内紧耦合设计展开讨论，总结了其中的设计难点问题。**
    * **支持 LMUL > 1**

        * 将向量指令依据 LMUL 拆分成多个 uop，以 uop 为单位调度后端流水线。在拆分方式上有状态机实现和 rom 存 uop 两种方式。

    * **跨域操作**

        * 方案一：对向量指令的标量源操作数，不做 bypass。
        * 方案二：增加 mv uop 实现向量与标量之间的跨域操作。

    * **mask/tail undisturbed**

        * 方案一：将前目的寄存器作为源寄存器读入来实现 undisturbed。
        * 方案二：为寄存器配置使能位来控制最小粒度写入。

    * **访存指令**

        * 向量访存需要支持多种类型的访存模式，包括 unit-stride, stride, index 三种模式，还需要考虑 segment 等特殊操作，增加了向量访存设计的复杂度。关于向量访存的设计仍在讨论中。

### 访存单元

* **继续推进初版 L1 预取器的设计：**

    * 使用 load queue 提供的顺序预取地址的机制给预取器提供顺序的 load 地址流进行训练
    * 每拍产生 2 个预取地址，使用 2 个地址进行训练

* **LSQ 部分：**

    * 探索将保留站的重发机制移动到 LSQ 的影响，每拍分别从 load queue 和 store queue 中选择需要重发的两项进行重发

### 缓存系统

* **调研下一版缓存设计空间，基本确定以下的设计参数：**

    * **L2 和 L3 间采用 ACE 协议，总线位宽 256 位。**
    * **L2 Feature：**

        * Inclusive
        * 不做 I/D 一致性
        * 支持 Hardware Anti-alias

    * **L3 Feature：**

        * Non-Inclusive（类 Victim 策略）
        * Directory-Based
        * Client dir conflict resolve

### 产品化改造

* **南湖产品化代码分支上的设计改动：**

    * 添加真实的 WFI (wait-for-interrupt) 指令支持，目前 WFI 会阻塞在 ROB 队头，直到出现可能的中断。修改同时已经合并到主分支 ([#1542](https://github.com/OpenXiangShan/XiangShan/pull/1542), [#1547](https://github.com/OpenXiangShan/XiangShan/pull/1547), [#1550](https://github.com/OpenXiangShan/XiangShan/pull/1550))
    * 支持外部可配的 CPU 启动地址。在 XSTop 端口上添加了 reset\_vector 输入信号，用来在 CPU 复位有效时初始化对应的 PC 寄存器。修改同时已经合并到主分支 ([#1545](https://github.com/OpenXiangShan/XiangShan/pull/1545))
    * 添加对 CLINT 的 real-time clock 支持，在 XSTop 端口上添加 rtc\_clock 输入信号，基于固定频率的低频时钟生成 CLINT 的时钟使能信号。修改同时已经合并到主分支 ([#1553](https://github.com/OpenXiangShan/XiangShan/pull/1553), [#1565](https://github.com/OpenXiangShan/XiangShan/pull/1565))
    * 修复一些功能与性能问题，修改同时已经合并到主分支
    * CPU 内部寄存器默认采用异步复位，添加带 DFT 支持的异步复位、同步撤离模块，修复了部分寄存器初始值非常量的问题
    * 添加对 SRAM 的 MBIST 支持，采用 sharebus 方案
    * 添加对 SRAM 库的非功能 pin 脚的连线支持
    * 修复 SRAMTemplate 在 SRAM multicycle 配置下的行为
    * 优化 Regfile 与 DataModuleTemplate 的写法
    * 代码风格规范，如修复了部分变量名的 keyword 冲突、复位信号使用、仿真 X 态传播等问题
    * 切换访问外设的 AXI 总线数据宽度为 256bit

### 杂项

* **产品化分支仿真环境：**

    * 调整 vcs 仿真参数，禁用 RANDOM\_MEM\_INIT，开启 -xprop
    * 统一了仿真 RTL 和验证 RTL, 现在仿真和 release RTL 可以使用相同的 RTL 代码

* **测试用例：**

    * 修正在关闭 printf 时部分测试 (llcop, plic) 无法通过的问题，在 plic 测试中禁用时钟中断
    * 新增了简单的 DMA 测试
    * 添加了 memscan 和 rtc-freq 测试用例
    * 添加了独立的 jtag 测试

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

编辑：徐易难、王凯帆、王华强、陈熙、李昕、张梓悦、胡轩、陈国凯
