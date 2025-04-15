---
slug: biweekly-74
date: 2025-04-14
categories:
  - Biweekly
---

# 【香山双周报 74】20250414 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 74 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 面积

### 后端流水线

- Bug 修复
    - 修复修改 hstatus.VGEIN 后, vstopi 比对出错的问题 ([#4517](https://github.com/OpenXiangShan/XiangShan/pull/4517))
    - 修复 vstopi 在 SEI/LCOFI 中断混合场景选择出错的问题 ([#4533](https://github.com/OpenXiangShan/XiangShan/pull/4533))
    - 修复 imisc 错误给 csr 传递非法异常的问题 ([#4546](https://github.com/OpenXiangShan/XiangShan/pull/4546))
    - 修复 vsetvl 未完成更新vtypegen操作，导致译码错误的问题 ([#4535](https://github.com/OpenXiangShan/XiangShan/pull/4535))
    - 修复 ROB 中针对 Svinval 拓展添加过于严格 assertion 的问题 ([#4519](https://github.com/OpenXiangShan/XiangShan/pull/4519))

- RVA23 Profile
    - 集成 Chisel AIA ([#4509](https://github.com/OpenXiangShan/XiangShan/pull/4509))
    - WFI 状态自动退出 ([#4491](https://github.com/OpenXiangShan/XiangShan/pull/4491))

### 访存与缓存

- Bug 修复
  - 修复 misalign 请求访问 uncache 空间时，未成功报出非对齐异常的 bug ([#4526](https://github.com/OpenXiangShan/XiangShan/pull/4526))
  - 修复一处 storequeue 指针更新同步的 bug ([#4531](https://github.com/OpenXiangShan/XiangShan/pull/4531))
  - 修复预取相关自定义 CSR 控制逻辑的 bug ([#4534](https://github.com/OpenXiangShan/XiangShan/pull/4534))
  - 修复在 MMU 进行 Page Table Walk 时，异常处理的若干 bug ([#4510](https://github.com/OpenXiangShan/XiangShan/pull/4510))、([#4524](https://github.com/OpenXiangShan/XiangShan/pull/4524))、([#4525](https://github.com/OpenXiangShan/XiangShan/pull/4525))、([#4540](https://github.com/OpenXiangShan/XiangShan/pull/4540))
  - 修复与 hfence 或 flush 相关的两处 bug ([#4539](https://github.com/OpenXiangShan/XiangShan/pull/4539))、([#4541](https://github.com/OpenXiangShan/XiangShan/pull/4541))
  - 修复 PageCache 命中 napot 项后，生成 ppn 有误的 bug ([#4527](https://github.com/OpenXiangShan/XiangShan/pull/4527))
  - 修正 Temporal Prefetcher 参数化 ([CoupledL2 #391](https://github.com/OpenXiangShan/CoupledL2/pull/391))、([HuanCun #187](https://github.com/OpenXiangShan/HuanCun/pull/187))

- CHI 总线
  - 将 Non-secure 字段默认设为 Secure ([CoupledL2 #398](https://github.com/OpenXiangShan/CoupledL2/pull/398))

- 工具
  - 添加 CHIron CLog.B （CHI 事务记录）功能 ([OpenLLC #55](https://github.com/OpenXiangShan/OpenLLC/pull/55))

- PPA 优化
  - 修复 storeMisalignBuffer 的入队逻辑以优化时序 ([#4493](https://github.com/OpenXiangShan/XiangShan/pull/4493))


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **3 月 28 日 0e64db5 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 35.85  | 410.bwaves       | 66.93  |
| 401.bzip2         | 25.49  | 416.gamess       | 40.90  |
| 403.gcc           | 46.64  | 433.milc         | 45.30  |
| 429.mcf           | 58.07  | 434.zeusmp       | 51.77  |
| 445.gobmk         | 30.25  | 435.gromacs      | 33.65  |
| 456.hmmer         | 41.60  | 436.cactusADM    | 46.21  |
| 458.sjeng         | 30.39  | 437.leslie3d     | 45.99  |
| 462.libquantum    | 122.51 | 444.namd         | 28.88  |
| 464.h264ref       | 56.56  | 447.dealII       | 73.41  |
| 471.omnetpp       | 39.51  | 450.soplex       | 51.98  |
| 473.astar         | 29.22  | 453.povray       | 53.43  |
| 483.xalancbmk     | 71.97  | 454.Calculix     | 16.37  |
| **GEOMEAN**       | 44.13  | 459.GemsFDTD     | 36.38  |
|                   |        | 465.tonto        | 36.72  |
|                   |        | 470.lbm          | 91.22  |
|                   |        | 481.wrf          | 40.64  |
|                   |        | 482.sphinx3      | 48.59  |
|                   |        | **GEOMEAN**      | 44.53  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

> 注：本次双周报的性能评估代码版本与上次双周报相同，将会在下次双周报时更新最新分数。

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组