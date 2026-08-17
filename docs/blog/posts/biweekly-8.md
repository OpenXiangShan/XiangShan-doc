---
slug: biweekly-8
date: 2022-01-10
categories:
  - Biweekly
---

# 【香山双周报 8】20220110 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 8 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

<!-- more -->
## 近期进展

### 前端

* **BPU 时序修改分支合并：**

    * 重构 uBTB，去除时延较长的 tag 比较，加入分支历史索引，整体预测下一个取指块的地址
    * 去除 BIM，第一级全部由 uBTB 做出预测
    * TAGE 和 ITTAGE 改为单口 SRAM，利用 bank-interleaving 减少读写冲突，当写 SRAM 时将读数据无效
    * TAGE 对每个取指块的两条分支用 PC 的一位数据 hash 到两个逻辑表中
    * TAGE 和 ITTAGE 的 useful 计数器改为 1bit
    * TAGE 减少到 4 张历史表，每张表 4K 个项
    * TAGE 的历史长度调优
    * SC（统计校正器）和 ITTAGE 增加一拍延迟
    * SC 存储开销缩减
    * FTB 项数减半

* **Fetch (IFU/ICache/IBuffer) 部分：**

    * 修复了 MMIO 半条指令取指问题，添加了半条重发 MMIO 请求的地址检查
    * 修复了指令预取的性能问题
    * 添加了预取和奇偶校验的控制寄存器

### 后端

* **Debug Mode & Trigger：**

    * 按照手册在 Atomic 指令部件加入 Trigger 比较
    * 修复 dcsr 和 mcontrol CSR 部分位的问题

* **Dispatch：**

    * 阻塞被标记异常的指令的后续指令的入队。这样可以避免出现一条异常指令和一条无异常指令接连入队后，Dispatch Queue 为第二条指令分配表项，但 Dispatch Queue 指针量只增加 1（入队的 Valid 指令数）的情况

* **ROB：**

    * 修复标记 flushPipe 的指令会正常 commit 的问题
    * 在 Trigger Hit 时置 Writebacked 为 0，就像常规的异常指令一样
    * 设置 ExceptionGen 的 wb 端口只和后端 Trigger Hit 信号连接，enq 端口只与前端 Trigger Hit 信号连接。由于前端 Trigger Hit 只会在前端被置为 1，且相应的指令不会到通过功能部件的写回。因此 ExceptionGen 模块的 wb 的不需要这些信号。同理，ExceptionGen 的 enq 端口也不需要后端 TriggerHit 的端口

## 后记

香山开源处理器正在火热地开发中，前端分支预测模块经过比较大的改动后，时序接近达标，预计将在这两周内收敛。我们也同时开启了对功能和性能的总体验证，我们将继续通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

编辑：勾凌睿、金越、李乾若
