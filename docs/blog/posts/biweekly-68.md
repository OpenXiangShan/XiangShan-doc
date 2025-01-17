---
slug: biweekly-68
date: 2025-01-20
categories:
  - Biweekly
---

# 【香山双周报 68】20250120 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 68 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 面积

### 后端流水线

- Bug 修复
    - 修复 xTIP (时钟中断等待位) 更新失败，导致错误产生中断的问题 ([#4157](https://github.com/OpenXiangShan/XiangShan/pull/4157))
    - 修复边界条件下，rob 发生重定向时没有成功刷新 rob 表项的问题 ([#4153](https://github.com/OpenXiangShan/XiangShan/pull/4153))
    - 添加对 htimedelta csr 初始化，以防止软件读取采用未初始化信息造成错误 ([#4145](https://github.com/OpenXiangShan/XiangShan/pull/4145))
    - 修复 mnret 部分输出信号未连线的问题 ([#4194](https://github.com/OpenXiangShan/XiangShan/pull/4194))
    - 添加 AIA 拓展遗漏的权限检查 ([#4166](https://github.com/OpenXiangShan/XiangShan/pull/4166))
    - 整理对 CSR 的访问异常，分类为多个模块共同完成 ([#4146](https://github.com/OpenXiangShan/XiangShan/pull/4146))
    - 修复修复重定向时快照选择在极端情况出错的问题 ([#4197](https://github.com/OpenXiangShan/XiangShan/pull/4197))
    - 修复 unorder reduction 指令掩码错误问题 ([#4197](https://github.com/OpenXiangShan/XiangShan/pull/4197))
    - 修复 reduction 指令 f16 数据选择错误问题 ([#4181](https://github.com/OpenXiangShan/XiangShan/pull/4181))

- Debug Module
    - 新增 hartReset 功能，在多核调试下，允许重启指定核 ([#4134](https://github.com/OpenXiangShan/XiangShan/pull/4134))

- 工具
    - 支持硬件可综合的三级分类 Top-Down 计数器 ([#4122](https://github.com/OpenXiangShan/XiangShan/pull/4122))
    - 添加 mcorepwd/mflushpwd 两个自定义 CSR 寄存器以控制功耗 ([#4164](https://github.com/OpenXiangShan/XiangShan/pull/4164))

### 访存与缓存

- RVA23 Profile

- Bug 修复

- PPA 优化


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