---
slug: biweekly-82
date: 2025-08-04
categories:
  - Biweekly
---

# 【香山双周报 82】20250804 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 82 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 面积

### 后端流水线

- Bug 修复
    - 修复 xcontext 寄存器未复位的问题 ([#4915](https://github.com/OpenXiangShan/XiangShan/pull/4915))
    - 修复软件检查异常未配置异常优先级的问题 ([#4923](https://github.com/OpenXiangShan/XiangShan/pull/4923))

- V3 Feature
    - 扩大发射宽度至 8，配套修改发射队列配置，并增加 ALU 数量 ([#4845](https://github.com/OpenXiangShan/XiangShan/pull/4845))
    - 支持不定周期功能单元的推测唤醒及取消 ([#4845](https://github.com/OpenXiangShan/XiangShan/pull/4845))
    - 支持 load 推测唤醒及取消 ([#4845](https://github.com/OpenXiangShan/XiangShan/pull/4845))

### 访存与缓存

- Bug 修复
    - 修复 Napot 页的判断条件，只有 PPN 低 4 位为 4'b1000 的页才能覆盖 64KB 范围 ([#4828](https://github.com/OpenXiangShan/XiangShan/pull/4828))、([#4900](https://github.com/OpenXiangShan/XiangShan/pull/4900))
    - 修复发生 gpf、获取 gpaddr 时的 vpn 匹配逻辑未考虑 Napot 页的 bug ([#4911](https://github.com/OpenXiangShan/XiangShan/pull/4911))
    - 修复 vaddr 最高 2 位被误截断，导致部分场景下写回 CSR 的 gpaddr 值高两位可能错误的 bug ([#4913](https://github.com/OpenXiangShan/XiangShan/pull/4913))
    - 修复 Dcache bus error 相关的生成逻辑，以避免 X 态传播 ([#4899](https://github.com/OpenXiangShan/XiangShan/pull/4899))
    - 在 Dcache MSHR 中设置 memBackType 初始值，以正确告知 L2 Cache 请求的类型属于 memory 或 uncache ([#4907](https://github.com/OpenXiangShan/XiangShan/pull/4907))
    - 修复向量 Segment 指令的 vaddr 高位被截断，导致误报异常的 bug ([#4892](https://github.com/OpenXiangShan/XiangShan/pull/4892))
    - 修复向量非对齐可能产生的部分卡死问题 ([#4914](https://github.com/OpenXiangShan/XiangShan/pull/4914))


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
