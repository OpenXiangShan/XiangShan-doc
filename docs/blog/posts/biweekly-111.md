---
slug: biweekly-111
date: 2026-09-16
categories:
  - Biweekly
---

# 【香山双周报 111】20260916 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 111 期双周报。

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
| commit    | 53a957667  |
| 日期      | 2026/08/21 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 2MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC16  |  XSCC  | SPECfp 2006 @ 3GHz | GCC16  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 55.02  | 53.33  | 410.bwaves         | 123.07 | 105.77 |
| 401.bzip2           | 29.89  | 30.60  | 416.gamess         | 58.70  | 55.81  |
| 403.gcc             | 58.27  | 41.61  | 433.milc           | 71.84  | 68.77  |
| 429.mcf             | 72.01  | 62.81  | 434.zeusmp         | 77.33  | 67.78  |
| 445.gobmk           | 43.70  | 42.34  | 435.gromacs        | 40.04  | 35.10  |
| 456.hmmer           | 54.59  | 67.12  | 436.cactusADM      | 85.01  | 93.51  |
| 458.sjeng           | 41.66  | 41.74  | 437.leslie3d       | 61.20  | 61.31  |
| 462.libquantum      | 138.17 | 305.05 | 444.namd           | 44.25  | 45.26  |
| 464.h264ref         | 69.92  | 75.51  | 447.dealII         | 64.71  | 79.14  |
| 471.omnetpp         | 48.18  | 47.76  | 450.soplex         | 59.78  | 72.28  |
| 473.astar           | 33.06  | 32.50  | 453.povray         | 78.25  | 73.65  |
| 483.xalancbmk       | 85.35  | 92.62  | 454.Calculix       | 41.80  | 40.77  |
| GEOMEAN             | 55.75  | 58.70  | 459.GemsFDTD       | 74.41  | 73.41  |
|                     |        |        | 465.tonto          | 55.70  | 37.80  |
|                     |        |        | 470.lbm            | 127.10 | 146.69 |
|                     |        |        | 481.wrf            | 58.65  | 44.97  |
|                     |        |        | 482.sphinx3        | 61.39  | 64.02  |
|                     |        |        | GEOMEAN            | 66.14  | 63.98  |

编译参数如下所示：

| 参数             | GCC16                       | XSCC                |
| ---------------- | --------------------------- | ------------------- |
| 编译器           | gcc16                       | xscc                |
| 编译优化         | O3                          | O3                  |
| 内存库           | jemalloc                    | jemalloc            |
| 指令集配置       | 基于 RVA23（禁用向量扩展） | RV64GCB             |
| -ffp-contraction | fast                        | fast                |
| 链接优化         | -flto                       | -flto               |
| 浮点优化         | -ffast-math                 | -ffast-math         |
| -mcpu            | -                           | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、甄好、燕翼鸣
