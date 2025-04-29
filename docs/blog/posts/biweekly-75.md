---
slug: biweekly-75
date: 2025-04-28
categories:
  - Biweekly
---

# 【香山双周报 75】20250428 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 75 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- 杂项
    - FTQ meta SRAM 规格修改 ([#4569](https://github.com/OpenXiangShan/XiangShan/pull/4569))

### 后端流水线

- Bug 修复
    - 修复 xtopi CSR 的最高优先级结果选择出错的问题 ([#4571](https://github.com/OpenXiangShan/XiangShan/pull/4571))
    - 去除 CSR 中 regOut 里只读的 CSR 寄存器 ([#4412](https://github.com/OpenXiangShan/XiangShan/pull/4412))
    - 修复 singlestep 状态下异常指令未能停在异常处理程序之前的问题 ([#4629](https://github.com/OpenXiangShan/XiangShan/pull/4629))
    - 修复在 wfi 指令设置为死等时，指令提交超时寄存器溢出，错误导致 critical error 的问题 ([#4623](https://github.com/OpenXiangShan/XiangShan/pull/4623))
    - 修复 rnmi 中断未能唤醒 wfi 指令的问题 ([#4645](https://github.com/OpenXiangShan/XiangShan/pull/4645))
    - 在 debug halt 请求到来时，开启 CPU 时钟 ([#4583](https://github.com/OpenXiangShan/XiangShan/pull/4583))
    - 修复部分 trace 参数设置出错的问题 ([#4561](https://github.com/OpenXiangShan/XiangShan/pull/4561))
    - 修复 imsic 错误发送非法异常的问题 ([#4546](https://github.com/OpenXiangShan/XiangShan/pull/4546))
    - 修复 xiselect 范围设置过小的问题 ([#4594](https://github.com/OpenXiangShan/XiangShan/pull/4594))
    - 修复更年轻的向量访存异常错误覆盖已经存在的向量访存指令异常的问题 ([#4570](https://github.com/OpenXiangShan/XiangShan/pull/4570))
    - 修复 difftest 时，pc 高位计算出错的问题 ([#4632](https://github.com/OpenXiangShan/XiangShan/pull/4632))
    - 修复 rob 提交指针在极端情况下越界的问题 ([#4642](https://github.com/OpenXiangShan/XiangShan/pull/4642))

### 访存与缓存

- Bug 修复
    - 修复仿真环境内存 AXI4Memory 连续写 burst=1 时产生的卡死 bug ([#4611](https://github.com/OpenXiangShan/XiangShan/pull/4611))
    - 修复 StoreQueue 中与 uncache store 出队逻辑有关的若干 bug ([#4641](https://github.com/OpenXiangShan/XiangShan/pull/4641))
    - 修复 cbo.zero 没有按 cacheline 粒度做 RAW 违例检查的 bug ([#4592](https://github.com/OpenXiangShan/XiangShan/pull/4592))
    - 修复非对齐 load 在 replay 时，误做 RAR/RAW 违例检查的 bug ([#4580](https://github.com/OpenXiangShan/XiangShan/pull/4580))
    - 修复在个别 corner case 下没有正确上报 ECC 错误的 bug ([#4572](https://github.com/OpenXiangShan/XiangShan/pull/4572))
    - 修复向量 EMUL<1 的非对齐 Unit-stride 指令元素 index 计算错误，导致异常信息有误的 bug ([#4593](https://github.com/OpenXiangShan/XiangShan/pull/4593))
    - 软件预取指令不应产生 uncache 地址的访问，避免误报异常 ([#4636](https://github.com/OpenXiangShan/XiangShan/pull/4636))
    - 修复 Dcache 中，同 set 访存密集场景下的死锁 bug ([#4622](https://github.com/OpenXiangShan/XiangShan/pull/4622))
    - 对于 MMIO 通路产生的异常，应上报 Hardware Error 而非 Access Fault ([#4619](https://github.com/OpenXiangShan/XiangShan/pull/4619))
    - 修复 MMU 页表遍历时，在 PTW 与 LLPTW 模块中和异常处理相关的几处 bug ([#4586](https://github.com/OpenXiangShan/XiangShan/pull/4586))、([#4596](https://github.com/OpenXiangShan/XiangShan/pull/4596))、([#4597](https://github.com/OpenXiangShan/XiangShan/pull/4597))
    - 修复 L1 TLB 中与虚拟化扩展相关的两处 bug ([#4587](https://github.com/OpenXiangShan/XiangShan/pull/4587))、([#4588](https://github.com/OpenXiangShan/XiangShan/pull/4588))
    - 修复 L2 Cache 中 tag 校验出错时的相关处理逻辑 ([CoupledL2 #399](https://github.com/OpenXiangShan/CoupledL2/pull/399))
    - 修复 L2 Cache 退出一致性状态时，没有去激活 TX 通道 linkactive 的 bug ([CoupledL2 #407](https://github.com/OpenXiangShan/CoupledL2/pull/407))

- PPA 优化
    - 优化 LoadQueue 中 uncacheBuffer 的冗余入队逻辑以改善时序 ([#4603](https://github.com/OpenXiangShan/XiangShan/pull/4603))
    - 调整 L2 Cache 中 tag 和 data SRAM 规格 ([CoupledL2 #402](https://github.com/OpenXiangShan/CoupledL2/pull/402))、([CoupledL2 #405](https://github.com/OpenXiangShan/CoupledL2/pull/405))

- 工具
    - CLog.B 支持多种时间输入方式 ([OpenLLC #62](https://github.com/OpenXiangShan/OpenLLC/pull/62))


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **4 月 25 日 6683fc4 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线，总线协议为 TileLink**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 35.90  | 410.bwaves        | 66.86  |
| 401.bzip2         | 25.51  | 416.gamess        | 40.88  |
| 403.gcc           | 47.87  | 433.milc          | 45.17  |
| 429.mcf           | 59.56  | 434.zeusmp        | 52.09  |
| 445.gobmk         | 30.31  | 435.gromacs       | 33.66  |
| 456.hmmer         | 41.61  | 436.cactusADM     | 46.18  |
| 458.sjeng         | 30.52  | 437.leslie3d      | 45.90  |
| 462.libquantum    | 122.43 | 444.namd          | 28.88  |
| 464.h264ref       | 56.58  | 447.dealII        | 73.57  |
| 471.omnetpp       | 41.42  | 450.soplex        | 52.63  |
| 473.astar         | 29.30  | 453.povray        | 53.39  |
| 483.xalancbmk     | 72.95  | 454.Calculix      | 16.38  |
| **GEOMEAN**       | 44.58  | 459.GemsFDTD      | 35.68  |
|                   |        | 465.tonto         | 36.68  |
|                   |        | 470.lbm           | 91.19  |
|                   |        | 481.wrf           | 40.64  |
|                   |        | 482.sphinx3       | 49.10  |
|                   |        | **GEOMEAN**       | 44.54  |

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
