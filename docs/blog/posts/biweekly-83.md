---
slug: biweekly-83
date: 2025-08-18
categories:
  - Biweekly
---

# 【香山双周报 83】20250818 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 83 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。


<!-- more -->

## 近期进展

### 前端

### 后端流水线

- Bug 修复
  - 修复 PMA 寄存器输出的命名问题 ([#4929](https://github.com/OpenXiangShan/XiangShan/pull/4929))
  - 调整 PMA 寄存器的基地址 ([#4940](https://github.com/OpenXiangShan/XiangShan/pull/4940))
  - 修复 load 快速唤醒 `vsetvli` 指令产生错误的问题 ([#4941](https://github.com/OpenXiangShan/XiangShan/pull/4941))

- V3 Feature
  - 更改后段内部分 Bundle 的命名格式 ([#4921](https://github.com/OpenXiangShan/XiangShan/pull/4921))、([#4937](https://github.com/OpenXiangShan/XiangShan/pull/4937))
  - 允许FTQ中最后一项的指令进行压缩 ([#4931](https://github.com/OpenXiangShan/XiangShan/pull/4931))
  - 在后端中检查BJU的跳转目标预测 ([#4932](https://github.com/OpenXiangShan/XiangShan/pull/4932))

### 访存与缓存


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **8 月 1 日 99d41d3 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

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

编辑：
