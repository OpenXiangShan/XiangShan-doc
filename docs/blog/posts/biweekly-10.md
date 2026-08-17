---
slug: biweekly-10
date: 2022-02-28
categories:
  - Biweekly
---

# 【香山双周报 10】20220228 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 10 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

<!-- more -->
## 近期进展

### 前端

* **BPU 部分：**

    * 减少 GHR buffer 到满足需求的长度
    * 修复 FTB 替换算法的两个性能 bug
    * 恢复 BPU 控制信号的功能（可以在运行时通过改变 CSR 的值控制 BPU 的功能）

* **FTQ 部分：**

    * 在给 IFU 发请求的前一拍读对应 FTQ 项的 fetch status（比原来早一拍）
    * 把后端与误预测和 load replay 相关的路径上，计算 pc 和 target 的逻辑放到 FTQ 中，避免不必要的线延迟

* **ICache 部分：**

    * 锁存了 ITLB 的 miss 请求避免从 FTQ req 到 miss 再到 FTQ ready 的长路径。
    * ITLB 的 requesetor 端口增加到 6 个（4 个给 ICacheMainPipe，1 个给 IFU，1 个给 IPrefetch），减少查询端口竞争带来的时序问题。
    * 修复了 prefetch ID 的位宽问题。

### 后端

* 将 store data 的浮点数据读推迟一拍进行。由于浮点物理寄存器堆与 store data 保留站距离过远，我们根据物理设计结果相应地调整了前端代码的实现
* 为 store data 保留站的时序考虑，将浮点 busyTable 复制了一份。目前有两份浮点的 busyTable，分别被 store data 和浮点运算部件使用

### 访存子系统

* 修正了 ld-ld 违例检查的问题
* 调整了 dcache tag error 相关的逻辑以优化时序

### HuanCun 子模块

* 修复了一个运行 Debian 仿真测试时发现的 bug:

    L2 因 A 通道请求而向上 Probe toB 时，L1D 有可能会发回 ProbeAck BtoN（与一个 Release 合并了），此时 L2 需要根据 ProbeAck 的 param 来决定如何写 Clients dir。

### SoC

* 由于时序问题，在 L1->L2 的路径上增加了一级 buffer。

**香山第一版（雁栖湖）芯片已经在农历新年前回来**，并在寒假期间成功点亮并**正确运行 Linux/Debian 操作系统**，目前在调试板卡上**正确支持 SD 卡、以太网等外设**。在**使用 DDR4-1600 的情况下，SPEC CPU 2006 实测评分超过 7 分@1GHz**，更细致的 DDR 与 CPU 性能调优（主要是 CPU/DDR 在更高频率下的稳定性验证）正在进行中。我们会在有更新结果时及时与大家分享，欢迎关注！

**下面是包云岗老师针对香山芯片调试过程的一个分享：**

## 后记

香山开源处理器正在火热地开发中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

编辑：徐易难、勾凌睿、金越、王华强、王凯帆、蔺嘉炜、张紫飞
