---
slug: biweekly-63
date: 2024-11-11
categories:
  - Biweekly
---

# 【香山双周报 63】20241111 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 63 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 添加 FTB pred_data 寄存器的复位 ([#3628](https://github.com/OpenXiangShan/XiangShan/pull/3628))
    - 后端的重定向带有异常时不进行预取 ([#3787](https://github.com/OpenXiangShan/XiangShan/pull/3787))

- 性能
    - 从未改变过 target 的间接跳转不进入 ITTAGE 间接跳转预测器 ([#3718](https://github.com/OpenXiangShan/XiangShan/pull/3718))

- 功耗
    - FTB 关闭时不进行更新 ([#3543](https://github.com/OpenXiangShan/XiangShan/pull/3543))

### 后端流水线

- Bug 修复
    - 修复 Debug 模式相关问题：
        - 修复重定向后，step 指令提交时多提交一条指令的问题 ([#3828](https://github.com/OpenXiangShan/XiangShan/pull/3828))
        - 修复 nmie 为 0 时，debug 中断无法响应的问题 ([#3826](https://github.com/OpenXiangShan/XiangShan/pull/3826))
        - 修复 原子访存在 trigger 触发 break point 异常时 mtval 更新错误 ([#3803](https://github.com/OpenXiangShan/XiangShan/pull/3803))
    - 修复 mip 寄存器赋值不完全的问题 ([#3827](https://github.com/OpenXiangShan/XiangShan/pull/3827))
    - 修复 XStrap 指令没有正确停止仿真的问题 ([#3848](https://github.com/OpenXiangShan/XiangShan/pull/3848))，NEMU 也完成了对应修改 ([#639](https://github.com/OpenXiangShan/NEMU/pull/639))
    - 修复虚拟中断注入后，未能陷入正确特权级的问题 ([#3812](https://github.com/OpenXiangShan/XiangShan/pull/3812))
    - NEMU 修复部分译码错误，未触发非法指令异常等问题 ([#646](https://github.com/OpenXiangShan/NEMU/pull/646), [#628](https://github.com/OpenXiangShan/NEMU/pull/628), [#645](https://github.com/OpenXiangShan/NEMU/pull/645))

- 时序/面积优化
    - 读取 vl 状态时，消除 old vd 操作数 ([#3847](https://github.com/OpenXiangShan/XiangShan/pull/3847))
    - 删除 rob 表项中冗余参数变量 ([#3833](https://github.com/OpenXiangShan/XiangShan/pull/3833))

- RVA23 Profile
    - VS/S/M 模式双重陷入拓展 (Ss/mdbltrp) 已合入主线（[#3789](https://github.com/OpenXiangShan/XiangShan/pull/3789)）
    - 支持 critical-error 检查以及进入 critical-error state ([#3793](https://github.com/OpenXiangShan/XiangShan/pull/3793), [#3835](https://github.com/OpenXiangShan/XiangShan/pull/3835))
    - 初步支持暂停提示拓展 (Zihintpause) ([#3823](https://github.com/OpenXiangShan/XiangShan/pull/3823))
    - 支持标量/向量半精度浮点拓展 (Zfh/Zvfh) ([#3840](https://github.com/OpenXiangShan/XiangShan/pull/3840))
    - NEMU 支持作为 REF 时对 icount/itrigger 检查 ([#614](https://github.com/OpenXiangShan/NEMU/pull/614))

### 访存与缓存

- CHI 总线
    - 通过提高 CHI 转接桥并发度与 TL 版本对齐 SPEC CPU 2006 libquantum 测试点性能，但是其他测试点仍然存在性能严重倒退问题
    - 完成 OpenLLC（基于 CHI 总线的 L3 Cache）、以及 OpenNCB（CHI-AXI 转接桥）与香山的集成，并合入主线 ([#3672](https://github.com/OpenXiangShan/XiangShan/pull/3672))。OpenLLC 的 github 仓库为 ([OpenLLC](https://github.com/OpenXiangShan/OpenLLC))

- Bug 修复
    - 修复 CMO.clean / flush 操作在 L1 miss、L2 hit 时的 bug ([#3814](https://github.com/OpenXiangShan/XiangShan/pull/3814))
    - 修复非对齐访存指令访问 mmio 空间时，mcause 设置错误的 bug ([NEMU #650](https://github.com/OpenXiangShan/NEMU/pull/650))
    - 修复非对齐访存指令发生 guest page fault 时，写入 *tval 的 gpaddr 有误的 bug ([#3809](https://github.com/OpenXiangShan/XiangShan/pull/3809))、([#3822](https://github.com/OpenXiangShan/XiangShan/pull/3822))
    - 修复取指发生 guest page fault 时，因地址位宽问题导致写入 *tval 的 gpaddr 被截断的 bug ([#3795](https://github.com/OpenXiangShan/XiangShan/pull/3795))

- PPA 优化
    - 调研 MemBlock 的一系列面积优化点，主要包括队列项数裁剪、冗余逻辑删除、功能单元合并等

- 工具
    - TL-Test 验证框架：在 tl-test-new 中添加 CMO 的测试环境，目前可以在 tl-test-new 上运行 CMO transaction ([#3804](https://github.com/OpenXiangShan/XiangShan/pull/3804))
    - 在 DiffTest store event 中添加 PC 和 RobIdx 等信息辅助调试 ([difftest #499](https://github.com/OpenXiangShan/difftest/pull/499))



## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **11 月 08 日 fbdb359 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.17  | 410.bwaves        | 76.73  |
| 401.bzip2         | 25.55  | 416.gamess        | 43.51  |
| 403.gcc           | 47.25  | 433.milc          | 44.07  |
| 429.mcf           | 58.61  | 434.zeusmp        | 56.96  |
| 445.gobmk         | 30.29  | 435.gromacs       | 37.46  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 49.48  |
| 458.sjeng         | 30.27  | 437.leslie3d      | 44.93  |
| 462.libquantum    | 124.52 | 444.namd          | 34.73  |
| 464.h264ref       | 57.82  | 447.dealII        | 75.09  |
| 471.omnetpp       | 39.74  | 450.soplex        | 54.54  |
| 473.astar         | 29.00  | 453.povray        | 56.03  |
| 483.xalancbmk     | 74.59  | 454.Calculix      | 18.35  |
| **GEOMEAN**       | 44.64  | 459.GemsFDTD      | 37.94  |
|                   |        | 465.tonto         | 38.21  |
|                   |        | 470.lbm           | 102.06 |
|                   |        | 481.wrf           | 43.45  |
|                   |        | 482.sphinx3       | 53.21  |
|                   |        | **GEOMEAN**       | 47.75  |

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
