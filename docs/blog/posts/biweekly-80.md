---
slug: biweekly-80
date: 2025-07-07
categories:
  - Biweekly
---

# 【香山双周报 80】20250707 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 80 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组开始进行 V3 的设计。此外，前端修复 ICache 请求跨行时，parity 检查可能使用无效结果的问题，后端修复 VTypeBuffer 中指令提交总数、回滚总数等变量在特定参数下位宽计算错误的问题，访存和缓存部分修复向量 segment 指令未成功上报 ecc error 的问题。本期还更新了昆明湖架构近期性能。


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ICache 请求跨行时，parity 检查可能使用无效结果的问题 ([#4814](https://github.com/OpenXiangShan/XiangShan/pull/4814))

- V3 Feature
    - BPU 顶层流水、新 uBTB、Ahead BTB ([#4851](https://github.com/OpenXiangShan/XiangShan/pull/4851))
    - IFU 将预译码的检查从关键路径上移除 ([#4849](https://github.com/OpenXiangShan/XiangShan/pull/4849))

### 后端流水线

- Bug 修复
    - 修复 xtopi 选出条件与选出数据错拍的问题 ([#4836](https://github.com/OpenXiangShan/XiangShan/pull/4836))
    - 修复 VTypeBuffer 中指令提交总数、回滚总数等变量在特定参数下位宽计算错误的问题 ([#4850](https://github.com/OpenXiangShan/XiangShan/pull/4850))

- V3 Feature
    - 增加 ROB 可压缩指令类型 ([#4114](https://github.com/OpenXiangShan/XiangShan/pull/4114))
    - 协商修改提交时后端通知前端 ftq 的机制 ([#4114](https://github.com/OpenXiangShan/XiangShan/pull/4114))

### 访存与缓存

- Bug 修复
    - 修复向量 segment 指令未成功上报 ecc error 的 Bug ([#4831](https://github.com/OpenXiangShan/XiangShan/pull/4831))
    - 对齐 RTL 和 NEMU 对 vleff 指令的 agnostic 设置 ([#4820](https://github.com/OpenXiangShan/XiangShan/pull/4820))、([NEMU #906](https://github.com/OpenXiangShan/NEMU/pull/906))
    - 修复 Dcache 请求阻塞在 s1 时，extra_meta_resp 信号错误地被覆盖的 Bug ([#4842](https://github.com/OpenXiangShan/XiangShan/pull/4842))
    - 修复已被 flush 的一条非对齐访存指令依然错误地进入 misaligned buffer 的 Bug ([#4840](https://github.com/OpenXiangShan/XiangShan/pull/4840))
    - 在 sbuffer 清空前，向量 segment 单元应该保持 flush sbuffer 的信号一直拉高 ([#4853](https://github.com/OpenXiangShan/XiangShan/pull/4853))
    - 修复一条非对齐向量指令被拆分成两条对齐的请求后，第二条请求触发异常时上报异常有误的 Bug ([#4854](https://github.com/OpenXiangShan/XiangShan/pull/4854))
    - 修复 Dcache 请求缺失后产生的 mainpipe X 态传播 Bug ([#4856](https://github.com/OpenXiangShan/XiangShan/pull/4856))
    - 修复向量 unit-stride 指令触发 guest page fault 时，gpaddr 计算有误的 Bug ([#4865](https://github.com/OpenXiangShan/XiangShan/pull/4865))
    - 修复断电（退出一致性状态）后 linkactive 在 syscozck==0 前失效的问题 ([CoupledL2 #422](https://github.com/OpenXiangShan/CoupledL2/pull/422))
    - 修复 reset 后 exitcoDone 信号错误有效时机的问题 ([CoupledL2 #424](https://github.com/OpenXiangShan/CoupledL2/pull/424))

- V3 Feature
    - 重构 L1 预取框架，包括参数化和去耦合等 ([#4790](https://github.com/OpenXiangShan/XiangShan/pull/4790))


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **7 月 3 日 c25dcc6 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 67.02  |
| 401.bzip2         | 25.50  | 416.gamess        | 40.99  |
| 403.gcc           | 47.90  | 433.milc          | 44.69  |
| 429.mcf           | 60.13  | 434.zeusmp        | 51.57  |
| 445.gobmk         | 30.70  | 435.gromacs       | 33.63  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.65  | 437.leslie3d      | 46.68  |
| 462.libquantum    | 105.08 | 444.namd          | 28.87  |
| 464.h264ref       | 56.60  | 447.dealII        | 72.19  |
| 471.omnetpp       | 41.52  | 450.soplex        | 52.33  |
| 473.astar         | 29.35  | 453.povray        | 53.46  |
| 483.xalancbmk     | 72.11  | 454.Calculix      | 16.37  |
| **GEOMEAN**       | 44.09  | 459.GemsFDTD      | 39.64  |
|                   |        | 465.tonto         | 36.12  |
|                   |        | 470.lbm           | 85.79  |
|                   |        | 481.wrf           | 40.30  |
|                   |        | 482.sphinx3       | 48.48  |
|                   |        | **GEOMEAN**       | 44.50  |

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
