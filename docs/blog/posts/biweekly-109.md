---
slug: biweekly-109
date: 2026-08-18
categories:
  - Biweekly
---

# 【香山双周报 109】20260818 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 109 期双周报。

关于香山近期开发进展，前端；后端；访存与缓存方面，；XSAI 。

<!-- more -->

## 近期进展

### 前端

- Bug 修复
- PPA 优化
- 调试工具

### 后端

- Bug 修复
- 调试工具
- 代码同步

### 访存与缓存

- RTL 新特性
- Bug 修复

### XSAI

- RTL 新特性
  - 支持 tile register 的 e8/e16/e32 多精度转置 load（[CUTE #35](https://github.com/OpenXiangShan/CUTE/pull/35)）
- Bug 修复
  - 修复多通道 CUTE 的 DiffTest 支持并优化面积（[XSAI #93](https://github.com/OpenXiangShan/XSAI/pull/93)、[CUTE #33](https://github.com/OpenXiangShan/CUTE/pull/33)）
- 调试工具
  - 在 DiffTest 中实现 MMA batching，减少 kernel launch 次数（[difftest #920](https://github.com/OpenXiangShan/difftest/pull/920)）
  - 实现反压，避免 MMA backend 吞吐不足时队列无限增长（[difftest #923](https://github.com/OpenXiangShan/difftest/pull/923)）

### 基础设计

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | ff4720da4  |
| 日期      | 2026/08/17 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 2MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 52.73  |        | 410.bwaves         | 120.79 |        |
| 401.bzip2           | 30.01  |        | 416.gamess         | 58.36  |        |
| 403.gcc             | 57.23  |        | 433.milc           | 71.04  |        |
| 429.mcf             | 73.02  |        | 434.zeusmp         | 78.12  |        |
| 445.gobmk           | 39.94  |        | 435.gromacs        | 38.27  |        |
| 456.hmmer           | 55.34  |        | 436.cactusADM      | 80.63  |        |
| 458.sjeng           | 39.49  |        | 437.leslie3d       | 60.95  |        |
| 462.libquantum      | 138.67 |        | 444.namd           | 42.98  |        |
| 464.h264ref         | 70.17  |        | 447.dealII         | 74.57  |        |
| 471.omnetpp         | 48.87  |        | 450.soplex         | 60.27  |        |
| 473.astar           | 32.78  |        | 453.povray         | 76.58  |        |
| 483.xalancbmk       | 83.08  |        | 454.Calculix       | 42.77  |        |
| GEOMEAN             | 54.89  |        | 459.GemsFDTD       | 71.73  |        |
|                     |        |        | 465.tonto          | 54.23  |        |
|                     |        |        | 470.lbm            | 128.82 |        |
|                     |        |        | 481.wrf            | 61.79  |        |
|                     |        |        | 482.sphinx3        | 61.20  |        |
|                     |        |        | GEOMEAN            | 66.12  |        |

编译参数如下所示：

| 参数             | GCC15       | XSCC                |
| ---------------- | ----------- | ------------------- |
| 编译器           | gcc15       | xscc                |
| 编译优化         | O3          | O3                  |
| 内存库           | jemalloc    | jemalloc            |
| -march           | RV64GCB     | RV64GCB             |
| -ffp-contraction | fast        | fast                |
| 链接优化         | -flto       | -flto               |
| 浮点优化         | -ffast-math | -ffast-math         |
| -mcpu            | -           | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、燕翼鸣
