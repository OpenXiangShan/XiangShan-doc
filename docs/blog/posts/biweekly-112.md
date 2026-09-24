---
slug: biweekly-112
date: 2026-09-30
categories:
  - Biweekly
---

# 【香山双周报 112】20260930 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 112 期双周报。

<!-- more -->

## 近期进展

### 前端

### 后端

### 访存与缓存

### XSAI

### 基础设施

### XS-GEM5

- 模拟器对齐
  - 向量访存的写回增加 3 周期延迟 ([XS-GEM5 #1155](https://github.com/OpenXiangShan/GEM5/pull/1155))
  - 对齐 pre-decode ([XS-GEM5 #1150](https://github.com/OpenXiangShan/GEM5/pull/1150))
  - vset 指令 ibuffer 旁路行为对齐 ([XS-GEM5 #1135](https://github.com/OpenXiangShan/GEM5/pull/1135))
  - cache hit under block 支持 ([XS-GEM5 #1164](https://github.com/OpenXiangShan/GEM5/pull/1164))
  - 浮点除法延迟对齐 ([XS-GEM5 #1167](https://github.com/OpenXiangShan/GEM5/pull/1167))
  - 向量 IQ 配置对齐 ([XS-GEM5 #1179](https://github.com/OpenXiangShan/GEM5/pull/1179))
- 新特性探索
  - 新指针预取算法 LLDP ([XS-GEM5 #1158](https://github.com/OpenXiangShan/GEM5/pull/1158))
  - tage 预测从 s3->s2 ([XS-GEM5 #1165](https://github.com/OpenXiangShan/GEM5/pull/1165))
  - safe-iq watermark ([XS-GEM5 #1175](https://github.com/OpenXiangShan/GEM5/pull/1175))
- 基础设施
  - cbo.zero 指令的实现 ([XS-GEM5 #1153](https://github.com/OpenXiangShan/GEM5/pull/1153))
  - se 模式的改进与文档完善 ([XS-GEM5 #1154](https://github.com/OpenXiangShan/GEM5/pull/1154))
  - 支持更多 se 模式的 workload ([XS-GEM5 #1156](https://github.com/OpenXiangShan/GEM5/pull/1156))

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 0eea07ed9  |
| 日期      | 2026/09/11 |
| L1 ICache | 64 KB      |
| L1 DCache | 64 KB      |
| L2 Cache  | 2 MB       |
| L3 Cache  | 32 MB      |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        | 56.40  | 54.24  | 410.bwaves          | 126.11 | 112.18 |
| 401.bzip2            | 30.49  | 31.20  | 416.gamess          | 59.54  | 56.55  |
| 403.gcc              | 61.93  | 42.58  | 433.milc            | 76.56  | 73.10  |
| 429.mcf              | 77.90  | 64.10  | 434.zeusmp          | 79.58  | 70.77  |
| 445.gobmk            | 44.90  | 44.46  | 435.gromacs         | 41.68  | 36.92  |
| 456.hmmer            | 54.74  | 67.53  | 436.cactusADM       | 86.33  | 94.33  |
| 458.sjeng            | 43.73  | 43.69  | 437.leslie3d        | 66.56  | 64.63  |
| 462.libquantum       | 164.48 | 382.99 | 444.namd            | 44.46  | 45.48  |
| 464.h264ref          | 69.46  | 76.01  | 447.dealII          | 66.08  | 81.12  |
| 471.omnetpp          | 56.40  | 56.29  | 450.soplex          | 65.94  | 79.40  |
| 473.astar            | 34.28  | 33.67  | 453.povray          | 79.62  | 74.37  |
| 483.xalancbmk        | 89.19  | 107.78 | 454.calculix        | 42.15  | 41.17  |
| GEOMEAN              | 58.94  | 62.57  | 459.GemsFDTD        | 80.02  | 76.96  |
|                      |        |        | 465.tonto           | 55.04  | 37.92  |
|                      |        |        | 470.lbm             | 128.56 | 149.77 |
|                      |        |        | 481.wrf             | 59.50  | 45.14  |
|                      |        |        | 482.sphinx3         | 62.02  | 64.63  |
|                      |        |        | GEOMEAN             | 68.19  | 65.95  |

编译参数如下所示：

| 参数          | GCC16                      | XSCC                |
| ------------- | -------------------------- | ------------------- |
| 编译器        | gcc16                      | xscc                |
| 编译优化      | O3                         | O3                  |
| 内存库        | jemalloc                   | jemalloc            |
| 指令集配置    | 基于 RVA23（禁用向量扩展） | RV64GCB             |
| -ffp-contract | fast                       | fast                |
| 链接优化      | -flto                      | -flto               |
| 浮点优化      | -ffast-math                | -ffast-math         |
| -mcpu         | -                          | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，SimPoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、甄好、燕翼鸣
