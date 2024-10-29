---
slug: biweekly-62
date: 2024-10-28
categories:
  - Biweekly
---

# 【香山双周报 62】20241028 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 62 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端修复了 ECC 到 Bus Error Unit 路径上的 Mux1H，后端 VS/S/M 模式双重中断拓展 (Ss/mdbltrp) 正在合入主线，访存和缓存部分修复了向量异常相关的 Bug。本期还更新了昆明湖架构近期性能。


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - ECC 到 Bus Error Unit 路径上的 Mux1H 修复 ([#3784](https://github.com/OpenXiangShan/XiangShan/pull/3784))

- 时序
    - FTQ -> FDIP 预取的时序优化 ([#3499](https://github.com/OpenXiangShan/XiangShan/pull/3499))
    - 将 io.flush 从预取的关键路径上移除 ([#3542](https://github.com/OpenXiangShan/XiangShan/pull/3542))
    - s2_finish 到预取的时序优化 ([#3545](https://github.com/OpenXiangShan/XiangShan/pull/3545))

- Code Style
    - 打开了 scalafmt 自动格式化，并在 CI 加入自动检查 ([#3370](https://github.com/OpenXiangShan/XiangShan/pull/3370))
    - 移除了未使用的 import，手动格式化一些 scalafmt 处理得不好得折行 ([#3791](https://github.com/OpenXiangShan/XiangShan/pull/3791))

### 后端流水线

- Bug 修复
    - 修复 H 拓展 gpa 获取不一致的问题以及修复 Misalign 访存相关 TLB 的问题 ([#3681](https://github.com/OpenXiangShan/XiangShan/pull/3681), [#3679](https://github.com/OpenXiangShan/XiangShan/pull/3679))
    - 修复向量访存异常在写回时，如果有更老的异常时，isEnqExcp 应置零的问题 ([#3778](https://github.com/OpenXiangShan/XiangShan/pull/3778))
    - 修复 ebreak 指令触发 breakpoint 异常时，以及压缩指令发生非法指令异常时，xtval 更新错误的问题 ([#3769](https://github.com/OpenXiangShan/XiangShan/pull/3769), [#3762](https://github.com/OpenXiangShan/XiangShan/pull/3762)，[#599](https://github.com/OpenXiangShan/XiangShan/pull/599))
    - 修复向量访存 trigger 相关问题 ([#3772](https://github.com/OpenXiangShan/XiangShan/pull/3772), [#3745](https://github.com/OpenXiangShan/XiangShan/pull/3745))
    - 修复 CSR 异常分开存储导致的错误拉高问题 ([#3771](https://github.com/OpenXiangShan/XiangShan/pull/3771))
    - 修复 xcause 的中断选择策略与 xtopi 不一致的问题（[#3753](https://github.com/OpenXiangShan/XiangShan/pull/3753)）
    - 修复 NEMU 在部分指令设置 xstatus.FS 为 Dirty 时的行为与 RTL 不一致的问题 ([#606](https://github.com/OpenXiangShan/XiangShan/pull/606), [#605](https://github.com/OpenXiangShan/XiangShan/pull/605), [#598](https://github.com/OpenXiangShan/XiangShan/pull/598), [#595](https://github.com/OpenXiangShan/XiangShan/pull/595), [#591](https://github.com/OpenXiangShan/XiangShan/pull/591), [#588](https://github.com/OpenXiangShan/XiangShan/pull/588))
    - 修复 Misalign 访存相关 TLB 的问题 ([#3731](https://github.com/OpenXiangShan/XiangShan/pull/3731))

- 时序/功耗优化
    - 优化向量译码，使用 RVV 自身编码构建 OP_TYPE
    - 优化唤醒，取消以及访存依赖时序 ([#3737](https://github.com/OpenXiangShan/XiangShan/pull/3737))
    - 评估后端面积优化点以及潜在收益

- RVA23 Profile
    - 计数溢出和基于特权级的过滤拓展 (Sscofpmf): 添加 RTL 指导 NEMU overflow 更新，RTL 支持基于特权级的过滤，NEMU 完成 mhpmevent 实现 ([#3771](https://github.com/OpenXiangShan/XiangShan/pull/3771), [#574](https://github.com/OpenXiangShan/XiangShan/pull/574))
    - VS/S/M 模式双重陷入拓展 (Ss/mdbltrp) 正在合入主线 （[#3789](https://github.com/OpenXiangShan/XiangShan/pull/3789)）
    - NEMU 实现 A 拓展的 trigger 支持 ([#592](https://github.com/OpenXiangShan/XiangShan/pull/592))

### 访存与缓存

- CHI 总线
    - CHI-L3: OpenLLC + OpenNCB 合入主线（配置：KunminghuV2Config）([#3672](https://github.com/OpenXiangShan/XiangShan/pull/3672))

- Bug 修复
    - 修复连续的两条 MMIO 访存，均发生 non-data error 异常时导致的卡死问题 ([#3728](https://github.com/OpenXiangShan/XiangShan/pull/3728))
    - 修复对非对齐的 HLV（hypervisor load）指令进行拆分后，丢失虚拟化相关信息的 Bug ([#3759](https://github.com/OpenXiangShan/XiangShan/pull/3759))
    - 修复未执行完毕一条非对齐指令前，storequeue 误提交该指令的 Bug ([#3758](https://github.com/OpenXiangShan/XiangShan/pull/3758))
    - 修复向量异常相关的 Bug，保证向量访存指令在乱序执行后，能够保留按顺序最早的一项异常 ([#3733](https://github.com/OpenXiangShan/XiangShan/pull/3733))
    - 修复由向量访存单元错误地无法接收 uop 发射，导致的卡死问题 ([#3741](https://github.com/OpenXiangShan/XiangShan/pull/3741))

- PPA 优化
    - MemBlock 内部和端口时序持续优化，目前内部违例优化至 -45ps，近期优化包括：去除 Dcache s2tag 到 dataArray 之间的关键路径、优化 MemBlock 向 L2 Cache 发送 CMO 请求的时序、优化 LoadUnit 写回端口的选择逻辑，以及非对齐访存的异常写回逻辑等 ([#3748](https://github.com/OpenXiangShan/XiangShan/pull/3748))
    - 对 DCache SRAM 添加 clock gating，memory 的内部功耗降低 51%

- 工具
    - CHIron：实现以二进制形式存储 CHI Log 信息，相较于文本格式存储，解析速度快 6 倍，文件空间占用减少 83%
    - TL-test-new：添加 OpenLLC 的 CI 流程，支持 MMIO 测试
    - L2 HPM（性能计数器）：根据物理设计调整连线 ([#3747](https://github.com/OpenXiangShan/XiangShan/pull/3747))



## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **10 月 26 日 b3c3582 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.85  | 410.bwaves        | 75.02  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.49  |
| 403.gcc           | 46.49  | 433.milc          | 43.61  |
| 429.mcf           | 57.50  | 434.zeusmp        | 56.80  |
| 445.gobmk         | 30.18  | 435.gromacs       | 37.38  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 48.77  |
| 458.sjeng         | 30.18  | 437.leslie3d      | 43.82  |
| 462.libquantum    | 125.07 | 444.namd          | 34.69  |
| 464.h264ref       | 57.81  | 447.dealII        | 74.53  |
| 471.omnetpp       | 40.01  | 450.soplex        | 54.54  |
| 473.astar         | 29.00  | 453.povray        | 55.93  |
| 483.xalancbmk     | 74.74  | 454.Calculix      | 18.32  |
| **GEOMEAN**       | 44.49  | 459.GemsFDTD      | 37.82  |
|                   |        | 465.tonto         | 38.21  |
|                   |        | 470.lbm           | 102.05 |
|                   |        | 481.wrf           | 42.68  |
|                   |        | 482.sphinx3       | 52.71  |
|                   |        | **GEOMEAN**       | 47.42  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
