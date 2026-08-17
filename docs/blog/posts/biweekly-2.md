---
slug: biweekly-2
date: 2021-10-18
categories:
  - Biweekly
---

# 【香山双周报 2】20211018 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 2 期，之后我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

<!-- more -->
## 近期进展

### 前端

* [#1128](https://github.com/OpenXiangShan/XiangShan/pull/1128)：解决了 TAGE base table 的更新信号和数据不同步的问题

### 后端

* [#1102](https://github.com/OpenXiangShan/XiangShan/pull/1102)：添加了对 K 扩展的部分支持与测试

    K 扩展，即 RISC-V Cryptographic Extension，密码学扩展。香山添加了对子扩展 zknd、zkne、zknh、zksed、zksh 的支持。

* [#1096](https://github.com/OpenXiangShan/XiangShan/pull/1096)：Scheduler 增加了读取浮点状态的接口
* [#1101](https://github.com/OpenXiangShan/XiangShan/pull/1101)：优化了重命名表的读写逻辑的时序

* [#1103](https://github.com/OpenXiangShan/XiangShan/pull/1103)：更新了寄存器堆端口分配方式
* [#1035](https://github.com/OpenXiangShan/XiangShan/pull/1035)：优化了阻塞 LOAD 指令的逻辑，优化了 StoreSet 的实现逻辑
* [#1113](https://github.com/OpenXiangShan/XiangShan/pull/1113)：优化了 StoreSet 的逻辑，降低误预测的数量
* [#1121](https://github.com/OpenXiangShan/XiangShan/pull/1121)：把给每个模块的 flush 信号，合并到了 redirect 中
* [#1123](https://github.com/OpenXiangShan/XiangShan/pull/1123)：优化了 MV 指令消除的逻辑，优化了时序
* [#1124](https://github.com/OpenXiangShan/XiangShan/pull/1124)：在 Rename 之后，lsrc 信号复用 imm 信号
* [#1126](https://github.com/OpenXiangShan/XiangShan/pull/1126)：Rename 不需要更新 refCounter[0]，因为这一项对应的物理寄存器 x0 不会被释放
* [#1089](https://github.com/OpenXiangShan/XiangShan/pull/1089)：修复了 SRT 16 除法器的 bug
* [#1100](https://github.com/OpenXiangShan/XiangShan/pull/1100)：修复了快速唤醒信号的连线逻辑
* [#1125](https://github.com/OpenXiangShan/XiangShan/pull/1125)：修复了 ROB walkcounter 在所有项被刷新时出错的问题

### 访存子系统

* [#1099](https://github.com/OpenXiangShan/XiangShan/pull/1099)：添加了软件访存预取指令

    软件访存预取指令（PREFETCH.R 和 PREFETCH.W）被编码为目的寄存器为 x0 的 ORI 指令。

* [#1092](https://github.com/OpenXiangShan/XiangShan/pull/1092)：添加了对 PMP 的支持和测试

    PMP 对于安全具有很大意义。PMP 寄存器在前端取指、后端访存和 Hardware Page Walker 都有一份拷贝，默认配置了 16 组 PMP 寄存器，可以通过参数修改。

* [#1108](https://github.com/OpenXiangShan/XiangShan/pull/1108)：L2TLB 添加了 Next-Line 预取，简单而有效
* [#1098](https://github.com/OpenXiangShan/XiangShan/pull/1098)：L2TLB 的 page table cache 添加了 ECC 检查，但只检错，不纠错
* [#1081](https://github.com/OpenXiangShan/XiangShan/pull/1081)：DCache 发生 bank conflict 时能够提早一拍反馈给保留站

保留站就可以更早的重发，降低 bank conflict 带来的损失。

* [#1128](https://github.com/OpenXiangShan/XiangShan/pull/1128)：优化了 L2TLB 的预取，可以跨 2MB 页进行预取
* [#1127](https://github.com/OpenXiangShan/XiangShan/pull/1127)：修复了 L2TLB 的 SFENCE.VMA 刷新访存部分的问题

### 测试与验证

* [#1097](https://github.com/OpenXiangShan/XiangShan/pull/1097)：增加了 CI 的功能，可以保留 CI 出错时的波形信息等

    优化 LightSSS 和 Difftest 的细节逻辑，修复了一些小问题。一般 CI 出错时，需要本地重新复现，需要比较长的时间，这个功能的添加能够大幅提高 debug 的效率。

* [#1122](https://github.com/OpenXiangShan/XiangShan/pull/1122)：添加了 fatal/fwrite 的检查，更新了 PrintControl transform
* [#1120](https://github.com/OpenXiangShan/XiangShan/pull/1120)：修复了 LightSSS 子进程不能正常停止的问题

### HuanCun 子模块

* 修改控制逻辑支持半频的 Data SRAM
* 增加 Put 操作支持、ECC 支持、CMO Cache 指令支持以及自定义 Cache 操作支持
* 修复一系列因密集 Probe 带来的功能 Bug

## 评估

我们采用 SimPoint 程序切片技术，仿真运行了 SPEC06 片段，每个程序的测试覆盖率大于 80%，使用 gcc 10.2 进行编译，优化选项为 O2，使用 DRAMSim 模拟内存延迟，使用 10.7 号版本的香山处理器。以下为 SPEC06 的分数统计：

| SPEC CPU2006 | @ 2GHz | 每 GHz |
| :-- | --: | --: |
| astar | 14.04 | 7.02 |
| bwaves | 33.66 | 16.83 |
| bzip2 | 11.43 | 5.72 |
| cactusADM | 18.51 | 9.25 |
| calculix | 7.35 | 3.68 |
| dealII | 34.66 | 17.33 |
| gamess | 21.34 | 10.67 |
| gcc | 20.39 | 10.20 |
| GemsFDTD | 23.23 | 11.62 |
| gobmk | 19.85 | 9.93 |
| gromacs | 15.74 | 7.87 |
| h264ref | 28.38 | 14.19 |
| hmmer | 19.67 | 9.84 |
| lbm | 39.48 | 19.74 |
| leslie3d | 16.80 | 8.40 |
| libquantum | 49.81 | 24.90 |
| mcf | 13.63 | 6.81 |
| milc | 22.21 | 11.11 |
| namd | 24.04 | 12.02 |
| omnetpp | 13.77 | 6.88 |
| perlbench | 20.18 | 10.09 |
| povray | 24.98 | 12.49 |
| sjeng | 20.12 | 10.06 |
| soplex | 19.34 | 9.67 |
| sphinx3 | 23.91 | 11.96 |
| tonto | 16.60 | 8.30 |
| wrf | 15.49 | 7.75 |
| xalancbmk | 20.58 | 10.29 |
| zeusmp | 23.37 | 11.68 |
| **总分** | **20.33** | **10.16** |

国庆假期结束了，我们加班修复了无数个 bug，大部分新功能也已经冻结，已经开始时序优化与收敛，并继续进行更全面的功能正确性验证。

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

编辑：张紫飞、徐易难
