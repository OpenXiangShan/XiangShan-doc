---
slug: biweekly-85
date: 2025-09-01
categories:
  - Biweekly
---

# 【香山双周报 85】20250915 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 85 期双周报。

<!-- 在本次双周报中，我们非常高兴地与大家分享一则消息。蓝芯算力基于近期交付的昆明湖 V2 IP 核搭建 8 核 SoC，成功启动 Linux，完成了 8 核一致性验证。在下一阶段，我们将继续与蓝芯算力紧密合作，开展 32 核一致性验证和性能优化。

在过去的两周，前端继续进行 V3 开发，一阶段重构即将完成。后端和访存与缓存稳步推进 V3 探索与代码重构，同时修复了一系列 V2 的 Bug。

从本期双周报开始，我们将不定期加入香山处理器的时序、面积与功耗数据，供大家参考。 -->

<!-- more -->

## 近期进展

### 前端

<!-- - RTL 新特性
  - 优化 IFU 指令标记和跨块指令拼接逻辑（[#4961](https://github.com/OpenXiangShan/XiangShan/pull/4961)）
    - 使用指令末尾的 2B 标记指令（4 字节指令的 `pc + 2` 或 2 字节指令的 `pc`）
    - 将单条 4 字节指令跨取指块的处理逻辑由每次从 ICache 多读取 2 字节改为缓存并等待下一次取指再拼接
  - 优化 FTQ 重定向逻辑：当重定向请求使 FTQ 项为空时，将新项写入该空项，而非分配新项（[#4939](https://github.com/OpenXiangShan/XiangShan/pull/4939)）
  - 删除 ICache 和 IFU 内的跨页取指支持（[#4909](https://github.com/OpenXiangShan/XiangShan/pull/4909)，[#4989](https://github.com/OpenXiangShan/XiangShan/pull/4989)）
  - 优化 mBTB 多路命中处理逻辑（[#4984](https://github.com/OpenXiangShan/XiangShan/pull/4984)）
  - TAGE、ITTAGE、分支 resolve 更新等特性持续开发中
- Bug 修复
  - （V2）修复 FTB 中 SRAM 读写冲突导致的 X 态传播问题（[#4971](https://github.com/OpenXiangShan/XiangShan/pull/4971)）
  - 修复 BPU SRAM 未完全初始化就开始预测导致的 X 状态传播问题（[#4968](https://github.com/OpenXiangShan/XiangShan/pull/4968)）
  - 修复 uBTB 会训练不跳转分支的问题（[#4977](https://github.com/OpenXiangShan/XiangShan/pull/4977)）
- 模型探索
  - 调试 SC 可落地方案
  - 调整 PHR 实现，避免降低仿真性能
- 代码质量
  - 整理 IFU 代码 -->

### 后端

<!-- - RTL 新特性
  - 修改普通微操作的写回寄存器个数来源（[#4944](https://github.com/OpenXiangShan/XiangShan/pull/4944)）
- Bug 修复
  - （V2）将 Zicfilp 引起的软件检查异常添加到异常优先级（[#4923](https://github.com/OpenXiangShan/XiangShan/pull/4923)）
  - （V2）修复 DPC 寄存器的相关问题（[#4979](https://github.com/OpenXiangShan/XiangShan/pull/4979)） -->

### 访存与缓存

<!-- - RTL 新特性
  - L2 目录更新从主流水线第 3 级后移至第 4 级
  - MMU、LoadUnit、StoreQueue、L2 等模块重构持续推进中
- Bug 修复
  - （V2）调整 TLB 请求中 `fullva` 的位宽，以传递完整的虚拟地址用于虚拟地址检查（[#4954](https://github.com/OpenXiangShan/XiangShan/pull/4954)）
  - （V2）修复执行 segment fault only first 指令时参考模型和被测设计不一致的问题，这类指令应写回 `vl` CSR（[#4956](https://github.com/OpenXiangShan/XiangShan/pull/4956)）
  - （V2）修复 PTW 中 Mux 使用未初始化的 `stage1Hit` 信号导致 X 态传播的问题（[#4916](https://github.com/OpenXiangShan/XiangShan/pull/4916)） -->

## 性能评估

| <!--           | SPECint 2006 est. | @ 3GHz        | SPECfp 2006 est. | @ 3GHz |
| :------------- | :---------------: | :------------ | :--------------: |
| 400.perlbench  |       35.90       | 410.bwaves    |      67.22       |
| 401.bzip2      |       25.50       | 416.gamess    |      41.01       |
| 403.gcc        |       47.89       | 433.milc      |      45.10       |
| 429.mcf        |       60.18       | 434.zeusmp    |      51.83       |
| 445.gobmk      |       30.48       | 435.gromacs   |      33.67       |
| 456.hmmer      |       41.61       | 436.cactusADM |      46.20       |
| 458.sjeng      |       30.62       | 437.leslie3d  |      47.80       |
| 462.libquantum |      122.58       | 444.namd      |      28.87       |
| 464.h264ref    |       56.59       | 447.dealII    |      73.63       |
| 471.omnetpp    |       41.50       | 450.soplex    |      52.48       |
| 473.astar      |       29.30       | 453.povray    |      53.49       |
| 483.xalancbmk  |       72.79       | 454.Calculix  |      16.38       |
| GEOMEAN        |       44.66       | 459.GemsFDTD  |      39.71       |
|                |                   | 465.tonto     |      36.72       |
|                |                   | 470.lbm       |      91.98       |
|                |                   | 481.wrf       |      40.78       |
|                |                   | 482.sphinx3   |      49.13       |
|                |                   | GEOMEAN       |      44.97       | -->    |

我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

编译参数如下所示：

|                  |          |
| ---------------- | -------- |
| 编译器           | gcc12    |
| 编译优化         | O3       |
| 内存库           | jemalloc |
| -march           | RV64GCB  |
| -ffp-contraction | fast     |

处理器及 SoC 参数如下所示：

|           |            |
| --------- | ---------- |
| commit    | b2daf0a    |
| 日期      | 2025/08/29 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | TileLink   |
| 内存延迟  | DDR4-3200  |


<!-- ## 功耗与面积

|                | 时序（GHz） | 单元面积（mm2） | 布局规划面积（mm2） | 功耗（W） |
| -------------- | ----------- | --------------- | ------------------- | --------- |
| 前端           | 2.8         | 0.18            | 0.28                | 0.39      |
| 后端           | 2.8         | 0.37            | 0.57                | 0.68      |
| 访存           | 2.8         | 0.30            | 0.46                | 0.47      |
| L2（512KB）    | 2.8         | 0.39            | 0.55                | 0.11      |
| 香山（层次化） | 2.8         | 1.24            | 1.86                | 1.65      |
| 香山（扁平化） | 2.7         | 1.23            | 1.73                | 1.63      | --> |

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
