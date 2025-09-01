---
slug: biweekly-84
date: 2025-09-01
categories:
  - Biweekly
---

# 【香山双周报 84】20250901 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。我们期待您的贡献。

本次是第 84 期双周报。

<!-- 在过去的两周，前端继续进行 V3 的 RTL 开发，同时在模型上探索分支预测的设计。后端与访存缓存修复了一系列功能 bug。后端还进行了 V3 开发的准备工作，主要包含一些代码清理和前后端接口重构。 -->

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
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
  - 整理 IFU 代码

### 后端

- RTL 新特性
  - 修改普通微操作的写回寄存器个数来源（[#4944](https://github.com/OpenXiangShan/XiangShan/pull/4944)）
- Bug 修复
  - （V2）将 Zicfilp 引起的软件检查异常添加到异常优先级（[#4923](https://github.com/OpenXiangShan/XiangShan/pull/4923)）
  - （V2）修复 DPC 寄存器的相关问题（[#4979](https://github.com/OpenXiangShan/XiangShan/pull/4979)）

### 访存与缓存

- RTL 新特性
  - L2 目录更新从主流水线第 3 级后移至第 4 级
  - MMU、LoadUnit、StoreQueue、L2 等模块重构持续推进中
- Bug 修复
  - 调整了 tlb 请求中 fullva 的位宽，以传递完整的虚拟地址用于虚拟地址检查（[#4954](https://github.com/OpenXiangShan/XiangShan/pull/4954)）
  - 修复了执行 segment fault only first 指令时参考模型和被测设计不一致的问题，这类指令应写回 vl CSR（[#4956](https://github.com/OpenXiangShan/XiangShan/pull/4956)）
  - 修复了 pTW 中 Mux 使用未初始化的 stage1Hit 信号导致 X 态传播的问题（[#4916](https://github.com/OpenXiangShan/XiangShan/pull/4916)）

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves       | 67.22  |
| 401.bzip2         | 25.51  | 416.gamess       | 41.01  |
| 403.gcc           | 47.95  | 433.milc         | 45.09  |
| 429.mcf           | 60.19  | 434.zeusmp       | 51.78  |
| 445.gobmk         | 30.62  | 435.gromacs      | 33.67  |
| 456.hmmer         | 41.61  | 436.cactusADM    | 46.20  |
| 458.sjeng         | 30.62  | 437.leslie3d     | 47.80  |
| 462.libquantum    | 122.58 | 444.namd         | 28.88  |
| 464.h264ref       | 56.57  | 447.dealII       | 73.27  |
| 471.omnetpp       | 41.35  | 450.soplex       | 52.50  |
| 473.astar         | 29.30  | 453.povray       | 53.49  |
| 483.xalancbmk     | 72.76  | 454.Calculix     | 16.37  |
| GEOMEAN           | 44.66  | 459.GemsFDTD     | 39.71  |
|                   |        | 465.tonto        | 36.73  |
|                   |        | 470.lbm          | 91.98  |
|                   |        | 481.wrf          | 40.63  |
|                   |        | 482.sphinx3      | 49.10  |
|                   |        | GEOMEAN          | 44.94  |

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
| commit    | ef913a6    |
| 日期      | 2025/08/14 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | TileLink   |
| 内存延迟  | DDR4-3200  |

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
