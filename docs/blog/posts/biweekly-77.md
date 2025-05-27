---
slug: biweekly-77
date: 2025-05-26
categories:
  - Biweekly
---

# 【香山双周报 77】20250526 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 77 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ICache 性能计数器 ([#4725](https://github.com/OpenXiangShan/XiangShan/pull/4725))

### 后端流水线

- Bug 修复

- 时序/面积优化

- RVA23 Profile

### 访存与缓存

- 功能
  - L2 Cache 支持 NS；MPAM NS 位与可配置 NS 位绑定 ([CoupledL2 #412](https://github.com/OpenXiangShan/CoupledL2/pull/412))、([CoupledL2 #414](https://github.com/OpenXiangShan/CoupledL2/pull/414))
  - 添加 WFI 的安全保护机制，确保在进入 WFI 状态前，CPU 核没有未返回的 L2 请求 ([#4691](https://github.com/OpenXiangShan/XiangShan/pull/4691))

- Bug 修复
  - 添加 Uncache Store 发生 bus error 的处理逻辑 ([#4717](https://github.com/OpenXiangShan/XiangShan/pull/4717))
  - 修复一条非对齐的向量 store 指令发生异常时，对 sbuffer 写入有误的 bug ([#4731](https://github.com/OpenXiangShan/XiangShan/pull/4731))
  - 修复对 cbo 指令是否触发 page fault 判断的一处 bug ([#4702](https://github.com/OpenXiangShan/XiangShan/pull/4702))
  - 修复对 cmo 指令的前递掩码设置有误导致的 store-load forward 数据出错 ([#4730](https://github.com/OpenXiangShan/XiangShan/pull/4730))
  - 修复 storequeue 中对向量指令重定向处理有误导致的卡死 ([#4711](https://github.com/OpenXiangShan/XiangShan/pull/4711))
  - 修复部分场景下，TLB 中存储的大页本应命中，但误报缺失的性能 bug ([#4694](https://github.com/OpenXiangShan/XiangShan/pull/4694))
  - 修复 sc / amo 指令的访存地址不具有 atomic 权限时，未成功上报 access fault 的 bug ([#4724](https://github.com/OpenXiangShan/XiangShan/pull/4724))
  - 修复 ECC 错误注入处理相关的 bug ([#4718](https://github.com/OpenXiangShan/XiangShan/pull/4718))

- PPA 优化
  - L2 Cache 支持非阻塞式 RXDAT 和 RXRSP ([CoupledL2 #397](https://github.com/OpenXiangShan/CoupledL2/pull/397))
  - 调整 BOP 延迟，以适配 CHI 版本 L2 Cache ([CoupledL2 #413](https://github.com/OpenXiangShan/CoupledL2/pull/413))

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
