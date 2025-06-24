---
slug: biweekly-79
date: 2025-06-23
categories:
  - Biweekly
---

# 【香山双周报 79】20250623 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 79 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，后端修复向量访存指令发生异常时，xstatus.VS 更新错误的问题，访存和缓存部分修复页表 global 设置导致进程切换失败问题。


<!-- more -->

## 近期进展

### 前端

无

### 后端流水线

- Bug 修复
    - 修复向量访存指令发生异常时，xstatus.VS 更新错误的问题 ([#4817](https://github.com/OpenXiangShan/XiangShan/pull/4817))
    - 修复 aia 相关寄存器读取出错的问题 ([#4802](https://github.com/OpenXiangShan/XiangShan/pull/4802))
    - 修复 nmi 中断等待位未正常清空的问题 ([#4825](https://github.com/OpenXiangShan/XiangShan/pull/4825))
    - 修复 external trigger 在 cluster 内引起广播风暴的问题 ([#4801](https://github.com/OpenXiangShan/XiangShan/pull/4801))

### 访存与缓存

- Bug 修复
    - 修复出现 NDERR 时，MSHR 错误等待缓存替换导致卡死的问题 ([CoupledL2 #418](https://github.com/OpenXiangShan/CoupledL2/pull/418))
    - 修复 LLPTW 同时虚拟化和非虚拟化请求的 corner case 导致硬件卡死的 Bug ([#4829](https://github.com/OpenXiangShan/XiangShan/pull/4829))
    - 修复页表 global 设置导致进程切换失败问题 ([#4811](https://github.com/OpenXiangShan/XiangShan/pull/4811))
    - 调整/区分了 StoreUnit 中 storemisalignbuffernack 在标量/向量下，smb 满时的处理逻辑 ([#4807](https://github.com/OpenXiangShan/XiangShan/pull/4807))
    - 向量访存不产生非对齐异常（当前向量不支持 MMIO 访问）([#4792](https://github.com/OpenXiangShan/XiangShan/pull/4792))
    - 修复 vector segment load 与 store(MMIO) 不响应 hardware error 异常的问题 ([#4800](https://github.com/OpenXiangShan/XiangShan/pull/4800)) ([#4799](https://github.com/OpenXiangShan/XiangShan/pull/4799))
    - 修复 LLPTW 虚拟化场景下状态机状态错误转移导致的 assertion 问题 ([#4788](https://github.com/OpenXiangShan/XiangShan/pull/4788))



## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **6 月 6 日 2272661 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

**注：本次双周报的性能评估代码版本与上次双周报相同，将会在下次双周报时更新最新分数。**

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.89  | 410.bwaves        | 66.98  |
| 401.bzip2         | 25.51  | 416.gamess        | 40.91  |
| 403.gcc           | 47.90  | 433.milc          | 45.05  |
| 429.mcf           | 60.24  | 434.zeusmp        | 51.65  |
| 445.gobmk         | 30.43  | 435.gromacs       | 33.66  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.20  |
| 458.sjeng         | 30.46  | 437.leslie3d      | 47.95  |
| 462.libquantum    | 122.63 | 444.namd          | 28.87  |
| 464.h264ref       | 56.59  | 447.dealII        | 73.03  |
| 471.omnetpp       | 41.38  | 450.soplex        | 52.52  |
| 473.astar         | 29.36  | 453.povray        | 53.40  |
| 483.xalancbmk     | 72.54  | 454.Calculix      | 16.37  |
| **GEOMEAN**       | 44.62  | 459.GemsFDTD      | 39.16  |
|                   |        | 465.tonto         | 36.65  |
|                   |        | 470.lbm           | 91.98  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.87  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
- 香山文档：https://xiangshan-doc.readthedocs.io/
- 香山用户手册：https://docs.xiangshan.cc/projects/user-guide/
- 香山设计文档：https://docs.xiangshan.cc/projects/design/

编辑：李燕琴、林志达、满洋、刘泽昊、刘威丁、马月骁
