---
slug: biweekly-76
date: 2025-05-12
categories:
  - Biweekly
---

# 【香山双周报 76】20250512 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 76 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

无

### 后端流水线

- Bug 修复
    - 修复 LCOFI (本地计数器溢出中断) 位在 xvip/xvien 寄存器中的可读写性问题 ([#4648](https://github.com/OpenXiangShan/XiangShan/pull/4648))
    - 修复 xstateen 对 sireg/vsireg 寄存器控制出错的问题 ([#4649](https://github.com/OpenXiangShan/XiangShan/pull/4649))
    - 修复虚拟中断注入没有被 mnstatus.nmie 控制的问题 ([#4645](https://github.com/OpenXiangShan/XiangShan/pull/4645))
    - 修复 wfi 未能被非屏蔽中断唤醒的问题 ([#4645](https://github.com/OpenXiangShan/XiangShan/pull/4645))
    - 修复 tval 寄存器在中断，CSR 相关异常，重定向同时发生的综合场景下更新出错的问题 ([#4671](https://github.com/OpenXiangShan/XiangShan/pull/4671))
    - 修复 mcause 在中断的双重陷入时更新出错的问题 ([#4671](https://github.com/OpenXiangShan/XiangShan/pull/4671))
    - 修复部分发生 EX\_II/EX\_VI 异常指令同时发生中断，且在中断处理函数再次发生上述异常时，tval 寄存器无法正常更新的错误 ([#4671](https://github.com/OpenXiangShan/XiangShan/pull/4671))

- 其他
    - 在仿真输出中添加版本信息 ([#4626](https://github.com/OpenXiangShan/XiangShan/pull/4626))

### 访存与缓存

- Bug 修复
    - 修复 StoreQueue 中，一条 uncache store 发生异常时的出队逻辑 ([#4641](https://github.com/OpenXiangShan/XiangShan/pull/4641))
    - UncacheBuffer 的 store 和 load 改为按照 robIdx 仲裁入队，防止依赖卡死 ([#4628](https://github.com/OpenXiangShan/XiangShan/pull/4628))
    - 修复非对齐访存跨页且新页产生异常时，写入 *tval 的值依然为前一页地址的 bug ([#4673](https://github.com/OpenXiangShan/XiangShan/pull/4673))
    - 对于非对齐访存指令，当 RAW queue 满时需要 rollback 以避免阻塞 ([#4674](https://github.com/OpenXiangShan/XiangShan/pull/4674))
    - 修复在 StoreQueue 中 cbo 指令出现异常时的 bug ([#4663](https://github.com/OpenXiangShan/XiangShan/pull/4663))
    - 修复 genVpn 函数未考虑虚拟化不同阶段、以及未考虑大页的 vpn 拼接等 bug ([#4647](https://github.com/OpenXiangShan/XiangShan/pull/4647))
    - 修复虚拟化 allStage 且两阶段均为大页时的部分场景下，生成 ppn 有误的 bug ([#4648](https://github.com/OpenXiangShan/XiangShan/pull/4648))
    - 修复 MMU 在 napot 场景下的部分命中匹配逻辑 ([#4659](https://github.com/OpenXiangShan/XiangShan/pull/4659))
    - 修复 StoreQueue 中向量异常的 flag 误发生超时 assert 的问题 ([#4660](https://github.com/OpenXiangShan/XiangShan/pull/4660))

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **5 月 8 日 f9d8efe 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.93  | 410.bwaves        | 66.86  |
| 401.bzip2         | 25.51  | 416.gamess        | 40.90  |
| 403.gcc           | 47.91  | 433.milc          | 45.17  |
| 429.mcf           | 59.57  | 434.zeusmp        | 52.09  |
| 445.gobmk         | 30.32  | 435.gromacs       | 33.66  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.52  | 437.leslie3d      | 45.90  |
| 462.libquantum    | 122.43 | 444.namd          | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII        | 73.57  |
| 471.omnetpp       | 41.45  | 450.soplex        | 52.64  |
| 473.astar         | 29.30  | 453.povray        | 53.39  |
| 483.xalancbmk     | 72.95  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.59  | 459.GemsFDTD      | 35.68  |
|                   |        | 465.tonto         | 36.69  |
|                   |        | 470.lbm           | 91.19  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.54  |

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
