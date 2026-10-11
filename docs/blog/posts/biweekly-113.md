---
slug: biweekly-113
date: 2026-10-14
categories:
  - Biweekly
---

# 【香山双周报 113】20261014 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 113 期双周报。

<!-- more -->

## 近期进展

### 前端

### 后端

### 访存与缓存

### XSAI

### 基础设施

### XS-GEM5

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    |            |
| 日期      |            |
| L1 ICache |            |
| L1 DCache |            |
| L2 Cache  |            |
| L3 Cache  |            |
| 访存单元  |            |
| 总线协议  |            |
| 内存配置  |            |

性能数据如下所示：

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        |        |        | 410.bwaves          |        |        |
| 401.bzip2            |        |        | 416.gamess          |        |        |
| 403.gcc              |        |        | 433.milc            |        |        |
| 429.mcf              |        |        | 434.zeusmp          |        |        |
| 445.gobmk            |        |        | 435.gromacs         |        |        |
| 456.hmmer            |        |        | 436.cactusADM       |        |        |
| 458.sjeng            |        |        | 437.leslie3d        |        |        |
| 462.libquantum       |        |        | 444.namd            |        |        |
| 464.h264ref          |        |        | 447.dealII          |        |        |
| 471.omnetpp          |        |        | 450.soplex          |        |        |
| 473.astar            |        |        | 453.povray          |        |        |
| 483.xalancbmk        |        |        | 454.calculix        |        |        |
| GEOMEAN              |        |        | 459.GemsFDTD        |        |        |
|                      |        |        | 465.tonto           |        |        |
|                      |        |        | 470.lbm             |        |        |
|                      |        |        | 481.wrf             |        |        |
|                      |        |        | 482.sphinx3         |        |        |
|                      |        |        | GEOMEAN             |        |        |

编译参数如下所示：

| 参数          | GCC16                      | XSCC                |
| ------------- | -------------------------- | ------------------- |
| 编译器        |                            |                     |
| 编译优化      |                            |                     |
| 内存库        |                            |                     |
| 指令集配置    |                  |                     |
| -ffp-contract |                            |                     |
| 链接优化      |                            |                     |
| 浮点优化      |                            |                     |
| -mcpu         |                            |                     |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，SimPoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：
