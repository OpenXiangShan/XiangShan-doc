---
slug: biweekly-65
date: 2024-12-09
categories:
  - Biweekly
---

# 【香山双周报 65】20241209 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 65 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 MMIO/非MMIO 边界跨越时全部报异常的问题 ([#3963](https://github.com/OpenXiangShan/XiangShan/pull/3963))
    - 修复 iTLB 在特殊情况下冲刷不正确的问题 ([#3996](https://github.com/OpenXiangShan/XiangShan/pull/3996))

- 面积
    - ITTAGE target 地址高位拆分和缩减 ([#3935](https://github.com/OpenXiangShan/XiangShan/pull/3935))

### 后端流水线

- Bug 修复
    - 修复标量/向量半精度浮点拓展 (Zfh/Zvfh) 功能单元计算错误：([#3939](https://github.com/OpenXiangShan/XiangShan/pull/3939), [#3932](https://github.com/OpenXiangShan/XiangShan/pull/3932))
    - 修复 menvcfg.DTE 控制 xstatus.SDT 读写行为错误：([#3981](https://github.com/OpenXiangShan/XiangShan/pull/3981), [#3955](https://github.com/OpenXiangShan/XiangShan/pull/3955))
    - 修复 vstart 为 0 情况下，错误消除 old vd：([#3948](https://github.com/OpenXiangShan/XiangShan/pull/3948))
    - 修复 CSR 同步访问 IMSIC 的问题：([#3989](https://github.com/OpenXiangShan/XiangShan/pull/3989))
    - 修复 custom PMA CSR 寄存器读写问题：([#3966](https://github.com/OpenXiangShan/XiangShan/pull/3966))
    - 修复在中断时错误置位向量异常信息的问题：([#3990](https://github.com/OpenXiangShan/XiangShan/pull/3990))
    - 修复在某些向量指令不应当置位 vs.dirty 的问题：([#3965](https://github.com/OpenXiangShan/XiangShan/pull/3965))

- 时序/面积优化
    - 将向量异常检测模块从 6 个简单译码器中移到 1 个复杂译码器 ([#3961](https://github.com/OpenXiangShan/XiangShan/pull/3961))
    - 优化 AIA 中断优先级选择逻辑，修复 CSR 时序 ([#3946](https://github.com/OpenXiangShan/XiangShan/pull/3946))


- RVA23 Profile
    - 在参数列表以及设备树信息中添加香山目前支持的指令集及拓展信息 ([#3986](https://github.com/OpenXiangShan/XiangShan/pull/3986), [#3953](https://github.com/OpenXiangShan/XiangShan/pull/3953))

### 访存与缓存

- RVA23 Profile
  - CMO：在 TileLink 总线中添加自定义的 CMO 操作，并完成 CMO 在 L1 DCache 与 L2 之间的处理通路 ([#3968](https://github.com/OpenXiangShan/XiangShan/pull/3968))
  - RAS：
    - L1 DCache 完成 ECC 故障注入指令的实现并通过自测用例，默认开启 ECC ([#3925](https://github.com/OpenXiangShan/XiangShan/pull/3925))
    - L2 Cache ECC (检错) 实现完成，L2 Cache 以及 OpenLLC（CHI 版本）实现支持 Poison 和 DataCheck ([#3808](https://github.com/OpenXiangShan/XiangShan/pull/3808))
  - Svpbmt：完成 Svpbmt 和 outstanding uncache 访问的代码实现，整理代码并已合入主线 ([#3900](https://github.com/OpenXiangShan/XiangShan/pull/3900))
  - Zicclsm：重构非对齐访存通路、完成向量非对齐访存的实现，正在整理代码准备合入主线 ([#3994](https://github.com/OpenXiangShan/XiangShan/pull/3994))

- Bug 修复
  - 修复 guest page fault 处理过程中，TLB 相应项被替换导致的卡死 bug ([#3964](https://github.com/OpenXiangShan/XiangShan/pull/3964), [#3985](https://github.com/OpenXiangShan/XiangShan/pull/3985))
  - 修复 vset 指令在 flushPipe 时无法处理中断的 bug，将 vset 指令设置为不响应中断 ([#3991](https://github.com/OpenXiangShan/XiangShan/pull/3991))
  - 修复 NEMU 处理跨页地址翻译时产生的 bug ([NEMU #710](https://github.com/OpenXiangShan/NEMU/pull/710))

- PPA 优化
  - 时序：优化 DCache 命中路选择逻辑，优化 CMO 有关的时序路径（[#3988](https://github.com/OpenXiangShan/XiangShan/pull/3988)）
  - 面积：
    - 删除 LoadQueueReplay / StoreQueue 中冗余的组合逻辑（[#3976](https://github.com/OpenXiangShan/XiangShan/pull/3976)）
    - MMU 面积裁剪：将 MMU page cache 项数由 2k 裁剪至 1k，性能降低幅度较小（[#4003](https://github.com/OpenXiangShan/XiangShan/pull/4003)）
    - 功耗：完成单核关断 RTL 代码，正在测试单核关断流程


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **12 月 06 日 a60d667 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.10  | 410.bwaves        | 67.07  |
| 401.bzip2         | 25.53  | 416.gamess        | 42.95  |
| 403.gcc           | 47.17  | 433.milc          | 45.29  |
| 429.mcf           | 58.86  | 434.zeusmp        | 56.75  |
| 445.gobmk         | 30.30  | 435.gromacs       | 37.44  |
| 456.hmmer         | 40.79  | 436.cactusADM     | 49.30  |
| 458.sjeng         | 30.22  | 437.leslie3d      | 45.29  |
| 462.libquantum    | 124.56 | 444.namd          | 34.65  |
| 464.h264ref       | 57.72  | 447.dealII        | 74.37  |
| 471.omnetpp       | 40.11  | 450.soplex        | 54.63  |
| 473.astar         | 29.14  | 453.povray        | 54.95  |
| 483.xalancbmk     | 73.25  | 454.Calculix      | 18.33  |
| **GEOMEAN**       | 44.61  | 459.GemsFDTD      | 40.22  |
|                   |        | 465.tonto         | 37.99  |
|                   |        | 470.lbm           | 102.47 |
|                   |        | 481.wrf           | 43.22  |
|                   |        | 482.sphinx3       | 53.26  |
|                   |        | **GEOMEAN**       | 47.48  |

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
