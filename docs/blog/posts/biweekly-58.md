---
slug: biweekly-58
date: 2024-09-02
categories:
  - Biweekly
---
# 【香山双周报 58】20240902 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 58 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端修复了 prefetchPipe s1 级状态机中软件预取相关转移的设计缺陷，后端支持了 Sstval/Shvstval 扩展，访存和缓存部分实现了 48 位虚存管理（Sv48）扩展。本期还更新了昆明湖架构近期性能。

<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 prefetchPipe s1 级状态机中软件预取相关转移的设计缺陷 ([#3433](https://github.com/OpenXiangShan/XiangShan/pull/3433))
    - 修复前端 Topdown 仿真计数器和硬件 PMU ([#3437](https://github.com/OpenXiangShan/XiangShan/pull/3437))

### 后端流水线

- Bug 修复
    - 持续推进功能 Bug 修复，共修复 30 余例，以下是部分 PR：
    - 修复 H 拓展功能 Bug ([#3450](https://github.com/OpenXiangShan/XiangShan/pull/3450), [#3447](https://github.com/OpenXiangShan/XiangShan/pull/3447), [#3442](https://github.com/OpenXiangShan/XiangShan/pull/3442), [#3428](https://github.com/OpenXiangShan/XiangShan/pull/3428), [#3427](https://github.com/OpenXiangShan/XiangShan/pull/3427), [#3423](https://github.com/OpenXiangShan/XiangShan/pull/3423), [#3420](https://github.com/OpenXiangShan/XiangShan/pull/3420), [#3397](https://github.com/OpenXiangShan/XiangShan/pull/3397), [#3385](https://github.com/OpenXiangShan/XiangShan/pull/3385))
    - 修复 Debug 拓展功能 Bug ([#3441](https://github.com/OpenXiangShan/XiangShan/pull/3441), [#3422](https://github.com/OpenXiangShan/XiangShan/pull/3422), [#3418](https://github.com/OpenXiangShan/XiangShan/pull/3418),[#3395](https://github.com/OpenXiangShan/XiangShan/pull/3395))
    - 修复 V 拓展功能 Bug ([#3430](https://github.com/OpenXiangShan/XiangShan/pull/3430), [#3384](https://github.com/OpenXiangShan/XiangShan/pull/3384))

- 时序优化
    - 持续推进时序优化，内部时序违例 -50ps，距离目标 -15ps
    - 移除 DataPath 中部分 loadCancel 信号 ([#3457](https://github.com/OpenXiangShan/XiangShan/pull/3457))
    - v0,vl 寄存器堆写回信号改为寄存器直出 ([#3387](https://github.com/OpenXiangShan/XiangShan/pull/3387))

- RVA23 Profile
    - 浮点加载常数和特殊偏序比较拓展 (Zfa) 正在合入主线 ([#3439](https://github.com/OpenXiangShan/XiangShan/pull/3439))
    - 支持 FP16 访存和数据类型转换 (Zfhmin) ([#3421](https://github.com/OpenXiangShan/XiangShan/pull/3421))
    - 支持 Sstval/Shvstval (非法指令异常时保存对应指令编码在 tval CSR 中) ([#3407](https://github.com/OpenXiangShan/XiangShan/pull/3407)) 
    - 可恢复非屏蔽中断 (Smrnmi) 拓展正在合入主线

### 访存与缓存

- CHI 总线
    - CHI to AXI4 转接桥：完成事务队列的设计实现，实现五种事务的乱序策略，正在完成协议层接口的实现
    - 为 CHI 与 CLINT 异步桥添加开关，可以在 SoCParameters 中设置参数 ([#3459](https://github.com/OpenXiangShan/XiangShan/pull/3459))

- RVA23 Profile
    - CMO 指令实现：修复若干 bug，成功通过简单的 XiangShan 系统指令测试；通过 CMO RISCV-tests。将 CMO 指令拓展 Zicbom 合入主线（[#3426](https://github.com/OpenXiangShan/XiangShan/pull/3426)）
    - 软件预取（Zicbop）扩展：优化软件指令预取有关的时序 ([#3425](https://github.com/OpenXiangShan/XiangShan/pull/3425))
    - 48 位虚存管理（Sv48）扩展：修复 48 位物理地址有关的 bug，目前已经通过 48 位物理地址自测用例 ([#3424](https://github.com/OpenXiangShan/XiangShan/pull/3424))

- 性能
    - TP meta on L2 迁移至新 master，进行性能评估
    - 发现 load 发射队列频繁抢占失败带来的一系列性能 bug，正在分析和修复

- bug 修复
    - 修复 LoadReplayQueue 无法入队，导致 load 指令丢失的 bug ([#3436](https://github.com/OpenXiangShan/XiangShan/pull/3436))
    - 添加 AXI4Error 外设，使得仿真环境下 SoC 能够识别非法地址并返回 non-data error 给 CPU；同时修复 store access fault 异常时 mtval 更新错误的 bug ([#3458](https://github.com/OpenXiangShan/XiangShan/pull/3458))
    - 修复向量访存与非对齐访问相关的 bug，目前只有标量可以硬件处理非对齐，向量仍然需要报异常由软件处理 ([#3460](https://github.com/OpenXiangShan/XiangShan/pull/3460))、([#3462](https://github.com/OpenXiangShan/XiangShan/pull/3462))


- PPA 优化
    - L2 Cache 上使用 SRAM 搭建 Queue，对 data SRAM 进行拆分。时序评估正常，面积有所优化，功耗增加过多
    - 继续修复 MemBlock 的关键路径，主要包括简化 DCache MSHR 入队逻辑、优化 LDU s0 的路径、打断长流水线（向量地址生成模块）的 ready 串联逻辑。准备合入主线 ([#3467](https://github.com/OpenXiangShan/XiangShan/pull/3467))

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **8 月 24 日 49162c9 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 33.66  | 410.bwaves        | 76.67  |
| 401.bzip2         | 24.99  | 416.gamess        | 43.33  |
| 403.gcc           | 47.90  | 433.milc          | 42.42  |
| 429.mcf           | 58.75  | 434.zeusmp        | 59.01  |
| 445.gobmk         | 30.17  | 435.gromacs       | 37.87  |
| 456.hmmer         | 40.28  | 436.cactusADM     | 47.68  |
| 458.sjeng         | 29.72  | 437.leslie3d      | 46.13  |
| 462.libquantum    | 127.00 | 444.namd          | 34.34  |
| 464.h264ref       | 56.62  | 447.dealII        | 73.80  |
| 471.omnetpp       | 41.22  | 450.soplex        | 54.63  |
| 473.astar         | 29.09  | 453.povray        | 55.70  |
| 483.xalancbmk     | 75.13  | 454.Calculix      | 18.15  |
| **GEOMEAN**       | 44.18  | 459.GemsFDTD      | 37.00  |
|                   |        | 465.tonto         | 35.73  |
|                   |        | 470.lbm           | 101.16 |
|                   |        | 481.wrf           | 42.20  |
|                   |        | 482.sphinx3       | 51.45  |
|                   |        | **GEOMEAN**       | 47.15  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
