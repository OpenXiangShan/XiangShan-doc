---
slug: biweekly-71
date: 2025-03-03
categories:
  - Biweekly
---

# 【香山双周报 71】20250303 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 71 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 调整 RAS 溢出的处理逻辑，避免潜在的卡死风险 ([#4317](https://github.com/OpenXiangShan/XiangShan/pull/4317))

### 后端流水线

- Bug 修复
    - 修复相邻中断/异常触发时，xtval 以及 epc 更新错误的问题 ([#4307](https://github.com/OpenXiangShan/XiangShan/pull/4307))
    - 修复 mhpmevent 寄存器备份信息更新不一致的问题 ([#4321](https://github.com/OpenXiangShan/XiangShan/pull/4321))
    - 修复对 debugmodule 的 mmio 访问，错误排除 debugmodule 地址空间的问题 ([#4324](https://github.com/OpenXiangShan/XiangShan/pull/4324))
    - 删除新版 dispatch 冗余模块，以及相关硬件性能计数器的冗余接口 ([#4288](https://github.com/OpenXiangShan/XiangShan/pull/4288))
    - 修复 Spike 模拟器中，未根据 hgatp.mode 做写 vsatp 限制的问题 ([Spike #86](https://github.com/OpenXiangShan/riscv-isa-sim/pull/86))

- 性能优化
    - 在新版 dispatch 模块，支持通过 vlbusytable 进行 oldvd 消除 ([#4198](https://github.com/OpenXiangShan/XiangShan/pull/4198))
    - 支持更多 CSRR 读指令乱序执行 ([#4128](https://github.com/OpenXiangShan/XiangShan/pull/4128))

### 访存与缓存

- Bug 修复
    - 修复非对齐访存在违例检测和写回唤醒上有关的遗留问题 ([#4333](https://github.com/OpenXiangShan/XiangShan/pull/4333))
    - 修复 uncache 请求在地址不对齐的情况下未报异常的 bug ([#4304](https://github.com/OpenXiangShan/XiangShan/pull/4304))
    - 修复 uncache 冲刷处理有误导致卡死的 bug ([#4300](https://github.com/OpenXiangShan/XiangShan/pull/4300))
    - 修复 LR 指令提前释放对后续 LR 的阻塞的 bug ([#4337](https://github.com/OpenXiangShan/XiangShan/pull/4337))

- RVA23 Profile
    - RAS
        - 设置 ECC 校验报错触发 NMI_31 中断 ([#4335](https://github.com/OpenXiangShan/XiangShan/pull/4335))
        - 修复 ECC 故障注入指令导致 DCache 出现多重命中的 bug ([#4285](https://github.com/OpenXiangShan/XiangShan/pull/4285))
        - 修复无效的 DCache MSHR 向 LDU 转发 corrupt 的 bug ([#4292](https://github.com/OpenXiangShan/XiangShan/pull/4292))
        - 补充一系列 L2 Cache 中被遗漏的错误处理 ([CoupledL2 #355](https://github.com/OpenXiangShan/CoupledL2/pull/355)， [CoupledL2 #357](https://github.com/OpenXiangShan/CoupledL2/pull/357)， [CoupledL2 #368](https://github.com/OpenXiangShan/CoupledL2/pull/368))

- CHI 总线
    - 补充 CMO 事务对 Snoop 的阻塞情况 ([CoupledL2 #370](https://github.com/OpenXiangShan/CoupledL2/pull/370))
    - 修复一系列与 Snoop 相关的嵌套问题 ([CoupledL2 #351](https://github.com/OpenXiangShan/CoupledL2/pull/351)， [CoupledL2 #358](https://github.com/OpenXiangShan/CoupledL2/pull/358)， [CoupledL2 #369](https://github.com/OpenXiangShan/CoupledL2/pull/369))
    - 添加对 CHI Issue C 版本的基本支持 ([#4298](https://github.com/OpenXiangShan/XiangShan/pull/4298))


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **2 月 14 日 7f475a2 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.88  | 410.bwaves        | 66.62  |
| 401.bzip2         | 25.55  | 416.gamess        | 40.91  |
| 403.gcc           | 46.67  | 433.milc          | 45.21  |
| 429.mcf           | 58.13  | 434.zeusmp        | 51.96  |
| 445.gobmk         | 30.34  | 435.gromacs       | 33.61  |
| 456.hmmer         | 41.60  | 436.cactusADM     | 46.26  |
| 458.sjeng         | 30.50  | 437.leslie3d      | 46.10  |
| 462.libquantum    | 122.57 | 444.namd          | 28.91  |
| 464.h264ref       | 56.66  | 447.dealII        | 73.69  |
| 471.omnetpp       | 39.35  | 450.soplex        | 52.00  |
| 473.astar         | 29.24  | 453.povray        | 53.42  |
| 483.xalancbmk     | 72.01  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.17  | 459.GemsFDTD      | 36.01  |
|                   |        | 465.tonto         | 36.74  |
|                   |        | 470.lbm           | 91.18  |
|                   |        | 481.wrf           | 40.62  |
|                   |        | 482.sphinx3       | 48.61  |
|                   |        | **GEOMEAN**       | 44.52  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/

编辑：李燕琴、林志达、满洋、刘泽昊、冯浩原、马月骁

审校：香山宣传工作组
