---
slug: biweekly-100
date: 2026-04-13
categories:
  - Biweekly
---

# 【香山双周报 100】20260413 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 100 期双周报。

3 月 26 日，“香山”+“如意”在中关村论坛年会正式发布！阅读双周报的大家相信对香山已经很熟悉了，这里不再赘述，如意（openRuyi）则是由中国科学院软件研究所联合如意社区广大伙伴共同研发的RISC-V原生操作系统，在开发过程中与香山团队紧密协作，实现了对香山开源高性能RISC-V处理器的深度适配和优化。这种软硬协同是 RISC-V 生态建设的关键一步，也是“香山+如意”开源社区的核心竞争力之一。我们希望能与整个社区一起，推动软硬件协同创新，打造一个开放、包容、繁荣的 RISC-V 生态。

![如意生态示意 软件所供图](./figs/biweekly-99/ruyi.jpg)

在香山方面，此次发布包含“昆明湖”处理器核、全球首个数据中心开源片上互连网络“温榆河”和首款终端开源片上互连IP“珠江”。本次展出的基于“昆明湖”处理器核的服务器芯片 V100 由我们的合作企业进迭时空设计流片，实测单核性能达到 SPEC2006 16.5 分/GHz，是全球首个完全支持 RVA23 profile、单核性能最高的开源处理器核。

![现场展出的 V100 处理器 朱献东摄](./figs/biweekly-99/v100.jpg)

另外，下一代“昆明湖”联合研发计划在会上正式启动，我们将携手中国科学院计算技术研究所、软件研究所、信息工程研究所，以及进迭时空、奕斯伟计算、腾讯、砺睿微电子、中国移动、中国电信、阿里达摩院、摩尔线程、算能科技、蓝芯算力等产学研单位一起，推动香山核心技术的产业化落地，进一步提升香山系列在高端算力领域的竞争力，力争打造一个高性能 RISC-V 芯片的创新底座，从而支撑企业研发更具竞争力的产品。

![联合研发计划启动合影](./figs/biweekly-99/collab.jpg)

我们还为大家准备了 V100 装在服务器中的样子，作为大家关注双周报的独家福利~

![V100 服务器](./figs/biweekly-99/server.jpg)

关于香山近期开发进展，前端修复了一些 BPU 的性能 bug，后端优化了部分模块的时序，访存继续进行模块的重构与测试。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 实现 SC 更精确的预测阈值逻辑（[#5716](https://github.com/OpenXiangShan/XiangShan/pull/5716)）
  - 启用 SC Global 表（[#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756)）
- Bug 修复
  - 修复历史寄存器在发生高级预测器 Override 时元数据更新错误的问题（[#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756)）
- 面积/时序优化
  - 将 SRAMTemplate resetState 暴露到接口上，BPU 使用该接口判断 SRAM 是否准备好接收请求（[#5735](https://github.com/OpenXiangShan/XiangShan/pull/5735)，[Utility#141](https://github.com/OpenXiangShan/Utility/pull/141)）
  - 更多时序修复正在评估中
- 代码质量
  - 重构 SC 表索引相关参数传递机制（[#5756](https://github.com/OpenXiangShan/XiangShan/pull/5756)）
- 调试工具
  - Make Topdown Accurate Again！协同后端组重写 Top-Down 性能计数器（[#5564](https://github.com/OpenXiangShan/XiangShan/pull/5564)）
  - 修复 BPU 顶层 `train_stall` 计数器条件永远为假的问题（[#5734](https://github.com/OpenXiangShan/XiangShan/pull/5734)）

### 后端

- RTL 新特性
  - 将整型 RegCache 的大小增加到 24 以支持 6 alu 的配置（[#5613](https://github.com/OpenXiangShan/XiangShan/pull/#5613)）
  - 修改 vsetvl x0, x0 使得 reserved 情况表现与 Spike 一致（[#5744](https://github.com/OpenXiangShan/XiangShan/pull/#5744)）
- Bug 修复
  - 在 critical-error 的 debug 重入口维持 dpc（[#5730](https://github.com/OpenXiangShan/XiangShan/pull/#5730)）
  - 同步修复 V2 的 debug 相关 bug（[#5754](https://github.com/OpenXiangShan/XiangShan/pull/#5754)）
  - 修复 Mcontrol6/Tdata1 相关问题（[#5722](https://github.com/OpenXiangShan/XiangShan/pull/#5722)）
  - 修复 TopDown 当中的 mis_pred 和 total_flush（[#5762](https://github.com/OpenXiangShan/XiangShan/pull/#5762)）
  - 修复 Bypass 中 psrcVl 的驱动为 pdestVl（[#5743](https://github.com/OpenXiangShan/XiangShan/pull/#5743)）
- 时序优化
  - 优化 Rename 的时序（[#5685](https://github.com/OpenXiangShan/XiangShan/pull/#5685)）
- 代码质量
  - 重命名 halt 为 wfi（[#4512](https://github.com/OpenXiangShan/XiangShan/pull/#4512)）

### 访存与缓存

- RTL 新特性
  - MMU、L2 等模块重构与测试持续推进中
  - 新版 LoadUnit 与 StoreQueue 合入主线并修复若干相关的问题（[#5548](https://github.com/OpenXiangShan/XiangShan/pull/5548)）
- Bug 修复
  - （V2）修复了 Store MMIO 没有标记 Rob 的问题（[#5640](https://github.com/OpenXiangShan/XiangShan/pull/5640)）
  - （V2）修复了 MisalignBuffer 的撤销逻辑（[#5674](https://github.com/OpenXiangShan/XiangShan/pull/5674)）
  - （V2）修复了 Uncache 模块中 mem_acquire 未触发时的前递顺序冒险问题（[#5630](https://github.com/OpenXiangShan/XiangShan/pull/5630)）
  - （V2）在 L1Prefetcher 中使用单独的信号来控制 RegEnable PC（[#5720](https://github.com/OpenXiangShan/XiangShan/pull/5720)）
  - 修复了非对齐访问 MMIO 区域时发出的异常类型（[#5700](https://github.com/OpenXiangShan/XiangShan/pull/5700)）
- 时序修复
  - 修复了 MemBlock 若干时序问题（[#5697](https://github.com/OpenXiangShan/XiangShan/pull/5697)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 87d03b2cc  |
| 日期      | 2026/03/24 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存延迟  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.54  | 47.50  | 410.bwaves         | 85.76  | 90.75  |
| 401.bzip2           | 27.41  | 28.22  | 416.gamess         | 56.92  | 53.01  |
| 403.gcc             | 55.42  | 38.93  | 433.milc           | 64.88  | 63.62  |
| 429.mcf             | 59.81  | 54.32  | 434.zeusmp         | 70.31  | 64.42  |
| 445.gobmk           | 39.25  | 40.59  | 435.gromacs        | 36.39  | 34.26  |
| 456.hmmer           | 53.63  | 63.65  | 436.cactusADM      | 75.77  | 86.49  |
| 458.sjeng           | 39.50  | 39.74  | 437.leslie3d       | 56.50  | 52.29  |
| 462.libquantum      | 135.53 | 294.09 | 444.namd           | 42.58  | 44.54  |
| 464.h264ref         | 62.93  | 71.26  | 447.dealII         | 64.88  | 69.53  |
| 471.omnetpp         | 41.18  | 39.38  | 450.soplex         | 49.79  | 60.47  |
| 473.astar           | 31.04  | 30.22  | 453.povray         | 73.02  | 66.48  |
| 483.xalancbmk       | 74.59  | 84.30  | 454.Calculix       | 43.93  | 39.70  |
| GEOMEAN             | 50.84  | 53.98  | 459.GemsFDTD       | 64.37  | 64.29  |
|                     |        |        | 465.tonto          | 52.49  | 34.91  |
|                     |        |        | 470.lbm            | 126.77 | 132.75 |
|                     |        |        | 481.wrf            | 55.04  | 41.52  |
|                     |        |        | 482.sphinx3        | 58.62  | 61.20  |
|                     |        |        | GEOMEAN            | 60.79  | 58.63  |

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
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
