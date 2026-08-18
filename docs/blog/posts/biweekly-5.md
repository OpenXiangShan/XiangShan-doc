---
slug: biweekly-5
date: 2021-11-29
categories:
  - Biweekly
---

# 【香山双周报 5】20211129 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 5 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

<!-- more -->
## 近期进展

### 前端

* **ICache 增加 TileLink 一致性支持**
* **修复 MMIO 取指通路的 bug**，解决分支预测进入 MMIO 空间后卡死的问题
* **优化 BPU 代码实现**，把 wrbypass 抽取出来形成单独共用的父类模块
* **优化 FTQ 时序**，把 fallThroughError 情况下 fallThroughAddr 的计算和其它路径解耦
* **优化 BPU 时序：**

    * 把 FTB 命中和不命中情况下 fallThroughAddr 计算逻辑解耦
    * 让最紧张的 uBTB 预测路径更新 GHR 的操作放在最后一级 Mux
    * 修复 PhyPriorityMuxGenerator 的实现，让 uBTB 预测路径真的在最后一级 Mux。
    * 让 FTB 的预测使用 one hot mux
    * 对每种可能的折叠历史更新情况分别更新，用预测信息做最后的选择，把折叠历史的更新内容关键路径和预测信号关键路径解耦

### 后端

* **优化了指令融合的判断逻辑时序：**之前有部分情况会使用译码后的信号进行判断，造成了综合报告中逻辑级数过多，现在已经全部修改为使用原始指令码进行判断
* **支持了定点与浮点除法的提前写回仲裁**，优化了时序
* **将浮点寄存器堆、浮点运算部件写回结果到 store data 保留站增加了一拍延迟**，以满足时序要求
* **将部分 B 和 K 扩展指令增加了一拍的延迟**，目前处理复杂 B 扩展指令和 K 扩展指令的 BKU 是定点模块的关键路径，因为这部分指令使用频率较低，我们增加了他们的延迟
* **清理了香山代码仓库中的 submodule**，去掉了对 hardfloat、api-config-chipsalliance 和 chiseltest 的 submodule 形式依赖，现在来自非香山的 submodule 只有 rocket-chip 了。我们使用 rocket-chip 中的 Diplomacy 和相关的 TileLink、AXI 库完成了总线上的一些设计
* **修复了 difftest 中 LightSSS 错误产生大量 zombie 进程的问题**

    LightSSS 采用 fork() 系统调用实现快照功能，超时的快照进程会被 kill 掉，同时只保留两个快照。因为某些原因，我们选择父进程继续执行，而把子进程当作快照，因此当 kill 掉子进程时，父进程还存在，这会导致子进程成为僵尸进程，包括 PID 等资源无法释放。在执行很长的任务时，会产生非常多的僵尸进程，进而导致 PID 资源耗尽，程序无法再 fork()，从而出错。解决方式很简单，kill 掉子进程之后，再 wait() 一下就可以了

* **优化了物理寄存器引用计数模块中的寄存器释放逻辑，**之前代码作者偷懒直接使用 refCounterNext（引用计数器的更新值）为 0 作为释放物理寄存器的条件，但由于香山的物理寄存器有 192 项，造成了时序非常紧张。现在修改为使用当拍的分配、释放次数，与当拍的引用计数器值 refCounter 三者进行判断，优化了时序
* **修复了多核生成 verilog 没有被去重的问题**

    由于香山的部分部件使用了最新的 chisel decoder api，而 decoder 内部使用了 scala 中的 Map 这种无序结构，导致同一个模块在多次例化时会产生功能相同但代码顺序不同的电路，从而使双核代码无法被 dedup 优化 (消除重复的模块，将多个模块各例化一次转变为同一个模块例化多次，有利于加快后端综合时间)。我们通过 chisel hierarchy api 解决了这一问题并向 chisel 社区进行了反馈（chisel [#2188](https://github.com/OpenXiangShan/XiangShan/pull/2188) [#2217](https://github.com/OpenXiangShan/XiangShan/pull/2217)）

### 访存子系统

* **时序优化：**

    * load queue：

        * **优化 missed load 写回操作的时序**
        * **调整 load 命中判断条件以优化时序。**现在若 dcache 不命中但可由 store queue 前递 load 结果，load 将不会命中

    * dcache：

        * **不再在 dcache 中使用 RRArbiter**
        * **优化 miss queue entry 写入逻辑**
        * **优化原子指令处理时序**
        * **提高 refill 请求的优先级。删除冗余的阻塞逻辑以优化时序**
        * **优化 writeback queue entry 写入逻辑**
        * **优化 miss queue entry 写入 valid 信号。**将其拆分成一个快速的 valid 信号和一个慢速的 cancel 信号。慢速的 cancel 信号来源于并行执行的 PMP 检查等操作。如果检查出这一操作需要取消，cancel 信号会在 miss queue entry 状态更新前的最后一刻取消此操作
        * **合并 dcache replace pipe 到 main pipe。**目前只有 refill pipe 独立在 main pipe 之外

    * sbuffer：

        * **优化数据前递时序**
        * **优化写回项选择逻辑时序。**sbuffer 写回一项时会检查之前的同一 cacheline 的写操作已经执行完成。这一检查原本会造成时序瓶颈，现在被分散到其他位置。现在检查写回项是否有效时只需要查看预先计算好的 flag

* 配合 dispatch 改动，恢复了访存违例预测机制的运作
* **修正了在某些情况下，store queue 中未初始化的地址信息会导致前递错误检查呈现 X 态的状况，**这一问题不会影响正确性

### HuanCun 子模块

* 根据后端的反馈，减少 DataStorage 的 Bank 数量，并将 Refill Buffer 从直接映射改为全相连
* **优化时序：**

    * 将预取请求和 ProbeHelper 的请求发送加拍；
    * SourceA, SinkC, SourceD 收到 task 后延一拍再去访问数据

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率大于 80%。SPEC 使用 gcc 10.2 进行编译，优化选项为 O2，指令集是 RV64GCB。**我们使用 11.13 号版本的香山处理器（缓存大小配置为 128KB L1 ICache + 128KB L1 DCache + 1MB L2 + 8MB L3），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 2GHz 情况下 DDR4-2400 内存的延迟**。以下为 SPEC06 的分数估计情况：

| SPECint 2006 | @ 2GHz | SPECfp 2006 | @ 2GHz |
| :-- | --: | :-- | --: |
| 400.perlbench | 20.25 | 410.bwaves | 28.29 |
| 401.bzip2 | 11.89 | 416.gamess | 22.17 |
| 403.gcc | 20.51 | 433.milc | 20.01 |
| 429.mcf | 11.81 | 434.zeusmp | 21.95 |
| 445.gobmk | 19.49 | 435.gromacs | 18.81 |
| 456.hmmer | 20.09 | 436.cactusADM | 14.70 |
| 458.sjeng | 18.91 | 437.leslie3d | 18.11 |
| 462.libquantum | 41.80 | 444.namd | 26.86 |
| 464.h264ref | 29.46 | 447.dealII | 33.21 |
| 471.omnetpp | 12.14 | 450.soplex | 18.24 |
| 473.astar | 14.33 | 453.povray | 27.96 |
| 483.xalancbmk | 16.40 | 454.Calculix | 9.45 |
| **GEOMEAN** | **18.41** | 459.GemsFDTD | 17.48 |
|  |  | 465.tonto | 17.85 |
|  |  | 470.lbm | 39.93 |
|  |  | 481.wrf | 18.42 |
|  |  | 482.sphinx3 | 21.03 |
|  |  | **GEOMEAN** | **20.94** |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

我们原计划在 11 月中旬完成南湖版本的 RT L 冻结，但因为距离 2G 的目标频率还有一些距离，我们仍然在进行时序优化，原定的时间节点也延迟了几周。按目前的进展，我们希望能在 12 月中旬完成 RTL 冻结。

## 后记

香山开源处理器正在火热地开发中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

编辑：徐易难、勾凌睿、王凯帆、蔺嘉炜、王华强、张紫飞
