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
  - 修复异常发生时 IFU 计算指令数出错的问题（[#6301](https://github.com/OpenXiangShan/XiangShan/pull/6301)）
  - 修复 write buffer 中读写冲突优先级的问题（[#6315](https://github.com/OpenXiangShan/XiangShan/pull/6315)）
  - 使用没有 taken 的分支训练相关计数器（[#6305](https://github.com/OpenXiangShan/XiangShan/pull/6305)）
- PPA 优化
  - 在 main BTB 中使用 `attribute` 替代 `valid`（[#6350](https://github.com/OpenXiangShan/XiangShan/pull/6350)）
  - 优化 FTQ 和 ICache 在 2-fetch 接口处的时序（[#6281](https://github.com/OpenXiangShan/XiangShan/pull/6281)）
  - 修复 PHR S1 和 S3 流水的更新时序（[#6263](https://github.com/OpenXiangShan/XiangShan/pull/6263)）
  - 优化 ABTB 的更新时序（[#6326](https://github.com/OpenXiangShan/XiangShan/pull/6326)）
  - 优化 BPU S3 计算最终 taken 分支的时序（[#6324](https://github.com/OpenXiangShan/XiangShan/pull/6324)）

### 后端

- Bug 修复
- 调试工具
- 代码同步

### 访存与缓存

- RTL 新特性
  - 实现并集成 L2 CDP 预取器（[XSCache #15](https://github.com/OpenXiangShan/XSCache/pull/15)、[XiangShan #6341](https://github.com/OpenXiangShan/XiangShan/pull/6341)）
- Bug 修复
  - 修复 DCache latency flag 的索引计算（[XiangShan #6339](https://github.com/OpenXiangShan/XiangShan/pull/6339)）
  - 修复跨页非对齐 store 的 TLB miss 处理（[XiangShan #6332](https://github.com/OpenXiangShan/XiangShan/pull/6332)）
  - 修复非对齐 store 的发射重放问题（[XiangShan #6322](https://github.com/OpenXiangShan/XiangShan/pull/6322)）
  - [V2] 修复 StoreQueue 读指针乱序更新（[XiangShan #6353](https://github.com/OpenXiangShan/XiangShan/pull/6353)）
  - [V2] 修复 coupledL2 的请求丢弃和 Directory MultiHit 错误上报（[CoupledL2 #523](https://github.com/OpenXiangShan/CoupledL2/pull/523)、[XiangShan #6345](https://github.com/OpenXiangShan/XiangShan/pull/6345)）
  - [V2] 补充 vector load 的非叶 PTE 元数据传递（[XiangShan #6344](https://github.com/OpenXiangShan/XiangShan/pull/6344)）
  - [V2] 修复预取过滤器无效状态导致的 X 传播（[XiangShan #6342](https://github.com/OpenXiangShan/XiangShan/pull/6342)）
  - [V2] 修复 vector store replay 元数据丢失（[XiangShan #6338](https://github.com/OpenXiangShan/XiangShan/pull/6338)）
  - [V2] 修复跨页非对齐 vector store 卡死（[XiangShan #6337](https://github.com/OpenXiangShan/XiangShan/pull/6337)）
  - [V2] 修复 TLB miss 时 StoreQueue 地址状态误更新（[XiangShan #6334](https://github.com/OpenXiangShan/XiangShan/pull/6334)）
  - [V2] 修复同一 uop 内非对齐 vector element 的执行顺序（[XiangShan #6323](https://github.com/OpenXiangShan/XiangShan/pull/6323)）
  - [V2] 将 CHI 异步桥队列深度从 4 调整为 8（[XiangShan #6306](https://github.com/OpenXiangShan/XiangShan/pull/6306)）

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

| SPECint 2006 @ 3GHz | GCC15  | XSCC  | SPECfp 2006 @ 3GHz | GCC15  | XSCC  |
| :------------------ | :----: | :---: | :----------------- | :----: | :---: |
| 400.perlbench       | 52.73  |       | 410.bwaves         | 120.79 |       |
| 401.bzip2           | 30.01  |       | 416.gamess         | 58.36  |       |
| 403.gcc             | 57.23  |       | 433.milc           | 71.04  |       |
| 429.mcf             | 73.02  |       | 434.zeusmp         | 78.12  |       |
| 445.gobmk           | 39.94  |       | 435.gromacs        | 38.27  |       |
| 456.hmmer           | 55.34  |       | 436.cactusADM      | 80.63  |       |
| 458.sjeng           | 39.49  |       | 437.leslie3d       | 60.95  |       |
| 462.libquantum      | 138.67 |       | 444.namd           | 42.98  |       |
| 464.h264ref         | 70.17  |       | 447.dealII         | 74.57  |       |
| 471.omnetpp         | 48.87  |       | 450.soplex         | 60.27  |       |
| 473.astar           | 32.78  |       | 453.povray         | 76.58  |       |
| 483.xalancbmk       | 83.08  |       | 454.Calculix       | 42.77  |       |
| GEOMEAN             | 54.89  |       | 459.GemsFDTD       | 71.73  |       |
|                     |        |       | 465.tonto          | 54.23  |       |
|                     |        |       | 470.lbm            | 128.82 |       |
|                     |        |       | 481.wrf            | 61.79  |       |
|                     |        |       | 482.sphinx3        | 61.20  |       |
|                     |        |       | GEOMEAN            | 66.12  |       |

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
