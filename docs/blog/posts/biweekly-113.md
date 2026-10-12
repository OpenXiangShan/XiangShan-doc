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

- RTL 新特性
  - 新增基于 DPI-C PteHelper 的 `softTLB`/`softPTW` 仿真翻译路径，支持两阶段地址翻译，用于评估 MMU 翻译性能上限（[#6115](https://github.com/OpenXiangShan/XiangShan/pull/6115)）

- Bug 修复
  - 对 TLB 和页表缓存的全局属性增加 `PTE.V` 门控，修复无效 PTE 的页故障条目无法被 ASID 定向 `SFENCE.VMA` 清除及跨 ASID 错误匹配的问题（[#6695](https://github.com/OpenXiangShan/XiangShan/pull/6695)）
  - （V2）在同一 load 同时触发 RAR/RAW 违规时优先选择会重新取指当前指令的 RAW 回滚，避免 RAR 回滚掩盖 RAW 违规并导致读取错误数据（[#6677](https://github.com/OpenXiangShan/XiangShan/pull/6677)）
  

### XSAI

- RTL 新特性
  - 集成矩阵引导的 L2 预取器（[XSAI #124](https://github.com/OpenXiangShan/XSAI/pull/124)、[XSAICache #7](https://github.com/OpenXiangShan/XSAICache/pull/7)）
  - 基于双组缓冲实现独立转置加载引擎，支持多通道转置加载（[CUTE #43](https://github.com/OpenXiangShan/CUTE/pull/43)、[XSAI #132](https://github.com/OpenXiangShan/XSAI/pull/132)）
- Bug 修复
  - 同步昆明湖 V2 的 bug-fix（[XSAI #131](https://github.com/OpenXiangShan/XSAI/pull/131)、[XSAICache #9](https://github.com/OpenXiangShan/XSAICache/pull/9)）
- 调试工具
  - 修复 DiffTest 在 MinimalMatrixConfig 下的矩阵完成事件步长错误（[difftest #976](https://github.com/OpenXiangShan/difftest/pull/976)）
  - 修复 NEMU 隐式状态更新后导出过期 CSR 值的问题（[NEMU #1237](https://github.com/OpenXiangShan/NEMU/pull/1237)）
  - 修复 NEMU 读取大尺寸 zstd 镜像的问题（[NEMU #1239](https://github.com/OpenXiangShan/NEMU/pull/1239)）
  - 支持矩阵寄存器 hash 对比（[CUTE #45](https://github.com/OpenXiangShan/CUTE/pull/45)、[difftest #978](https://github.com/OpenXiangShan/difftest/pull/978)、[NEMU #1238](https://github.com/OpenXiangShan/NEMU/pull/1238)、[XSAI #133](https://github.com/OpenXiangShan/XSAI/pull/133)）

### 基础设施

### XS-GEM5

- 模拟器对齐
  - L2 低准确率预取 offload 配置对齐 ([XS-GEM5 #1183](https://github.com/OpenXiangShan/GEM5/pull/1183))
  - SBuffer 同 cache line store miss 合并行为对齐 ([XS-GEM5 #1171](https://github.com/OpenXiangShan/GEM5/pull/1171))
- Bug 修复
  - 修复向量 load 寄存器越界导致的 rename panic ([XS-GEM5 #1185](https://github.com/OpenXiangShan/GEM5/pull/1185))
  - 支持 UARTLite 32-bit MMIO 访问 ([XS-GEM5 #1199](https://github.com/OpenXiangShan/GEM5/pull/1199))
- 基础设施
  - 更新每周性能回归配置 ([XS-GEM5 #1188](https://github.com/OpenXiangShan/GEM5/pull/1188))
  - 增加 Clang `gem5.fast` 构建检查 ([XS-GEM5 #1209](https://github.com/OpenXiangShan/GEM5/pull/1209))
  - 完善中文仓库日报生成流程 ([XS-GEM5 #1204](https://github.com/OpenXiangShan/GEM5/pull/1204), [XS-GEM5 #1212](https://github.com/OpenXiangShan/GEM5/pull/1212))

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
