---
slug: biweekly-78
date: 2025-06-09
categories:
  - Biweekly
---

# 【香山双周报 78】20250609 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 78 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 面积

### 后端流水线

- Bug 修复
    - 修复 xtopi 寄存器异步更新导致 difftest 同步出错的问题：暂时跳过 xtopi 比对 ([#4742](https://github.com/OpenXiangShan/XiangShan/pull/4742))
    - 修复 sstateenx 未正确生成为 Verilog 模块的问题 ([#4723](https://github.com/OpenXiangShan/XiangShan/pull/4723))
    - 将核内 trace 对 xret 指令的统计从指令提交阶段提前到重命名阶段 ([#4736](https://github.com/OpenXiangShan/XiangShan/pull/4736))

- 工具
    - 添加自定义 HINT 指令作为 FPGA 仿真调试触发器 ([#4776](https://github.com/OpenXiangShan/XiangShan/pull/4776))

### 访存与缓存

- Bug 修复
    - 修复在 DCache 中发生 cache 别名时，Probe 请求阻塞只考虑了物理地址，没有考虑别名位，导致卡死的 bug ([#4741](https://github.com/OpenXiangShan/XiangShan/pull/4741))
    - 修复 DCache MetaArray 读写冲突，但没有在 RAR 中作相应标记，导致 Load 读到旧值的 bug ([#4795](https://github.com/OpenXiangShan/XiangShan/pull/4795))
    - 修复若干与 DCache ECC 与自定义故障注入有关的 bug ([#4753](https://github.com/OpenXiangShan/XiangShan/pull/4753))、([#4755](https://github.com/OpenXiangShan/XiangShan/pull/4755))、([#4782](https://github.com/OpenXiangShan/XiangShan/pull/4782))
    - 修复非对齐且跨页的访存请求发生异常时，写入 *tval 的异常地址错误的 bug ([#4751](https://github.com/OpenXiangShan/XiangShan/pull/4751))
    - 修复 uncache 访问非法地址没有正确报 hardware error 的 bug ([#4774](https://github.com/OpenXiangShan/XiangShan/pull/4774))
    - 修复 difftest 框架中，uncache store 和 memory store 对比时机不同导致的 diff 出错 ([#4779](https://github.com/OpenXiangShan/XiangShan/pull/4779))
    - 修复 IFU 在生成物理地址时，部分场景下误使用了错误的地址低位作为 offset 的 bug ([#4748](https://github.com/OpenXiangShan/XiangShan/pull/4748))
    - 修复两阶段地址翻译过程中，G-Stage 已经触发 gpf，但错误地同时上报 pf 和 gpf 的 bug ([#4754](https://github.com/OpenXiangShan/XiangShan/pull/4754))
    - 修复 PMA 在根据请求 cmd 类型做地址检查时信号错拍，导致权限检查出错的 bug ([#4769](https://github.com/OpenXiangShan/XiangShan/pull/4769))
    - 修复部分 corner case 情况下，TLB 的命中逻辑没有考虑两阶段页大小不同的情况导致误匹配的 bug ([#4780](https://github.com/OpenXiangShan/XiangShan/pull/4780))
    - 修复 TLB 的 handle_block 函数中，生成 gpaddr 在部分场景下逻辑有误的 bug ([#4793](https://github.com/OpenXiangShan/XiangShan/pull/4793))
    - 将 TXRSP、TXDAT 通道的仲裁逻辑修改为轮询，以避免拥塞场景下低优先级请求超时问题 ([CoupledL2 #415](https://github.com/OpenXiangShan/CoupledL2/pull/415))

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **6 月 6 日 2272661 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.89  | 410.bwaves        | 66.98  |
| 401.bzip2         | 25.51  | 416.gamess        | 40.91  |
| 403.gcc           | 47.90  | 433.milc          | 45.05  |
| 429.mcf           | 60.24  | 434.zeusmp        | 51.65  |
| 445.gobmk         | 30.43  | 435.gromacs       | 33.66  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.20  |
| 458.sjeng         | 30.46  | 437.leslie3d      | 47.95  |
| 462.libquantum    | 122.63 | 444.namd          | 28.87  |
| 464.h264ref       | 56.59  | 447.dealII        | 73.03  |
| 471.omnetpp       | 41.38  | 450.soplex        | 52.52  |
| 473.astar         | 29.36  | 453.povray        | 53.40  |
| 483.xalancbmk     | 72.54  | 454.Calculix      | 16.37  |
| **GEOMEAN**       | 44.62  | 459.GemsFDTD      | 39.16  |
|                   |        | 465.tonto         | 36.65  |
|                   |        | 470.lbm           | 91.98  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.87  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
- 香山文档：https://xiangshan-doc.readthedocs.io/
- 香山用户手册：https://docs.xiangshan.cc/projects/user-guide/
- 香山设计文档：https://docs.xiangshan.cc/projects/design/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
