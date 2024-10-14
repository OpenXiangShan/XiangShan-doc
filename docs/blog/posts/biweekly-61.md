---
slug: biweekly-61
date: 2024-10-14
categories:
  - Biweekly
---
# 【香山双周报 61】20241014 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 61 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，

<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复一个取指块跨页导致的 gpaddr 被错误丢弃的 Bug ([#3719](https://github.com/OpenXiangShan/XiangShan/pull/3719))
    - 修复 Zcb 扩展中算术指令被识别为非法指令的问题 ([#3721](https://github.com/OpenXiangShan/XiangShan/pull/3721) OpenXiangShan/rocket-chip [#14](https://github.com/OpenXiangShan/rocket-chip/pull/14))


### 后端流水线

- Bug 修复
    - 持续推进功能 Bug 修复，当前版本致命和严重 Bug 趋于收敛：
    - 修复连续 redirect 情况下 vtype 恢复错误 ([#3705](https://github.com/OpenXiangShan/XiangShan/pull/3705))
    - 修复 CSR 寄存器一系列读写以及权限检查相关错误 ([#3717](https://github.com/OpenXiangShan/XiangShan/pull/3717), [#3701](https://github.com/OpenXiangShan/XiangShan/pull/3701), [#3700](https://github.com/OpenXiangShan/XiangShan/pull/3700), [#3703](https://github.com/OpenXiangShan/XiangShan/pull/3703))
    - 修复 rtl 未正确指导 NEMU 中 mip.LCOFIP 更新的错误 ([#3710](https://github.com/OpenXiangShan/XiangShan/pull/3710)，[#572](https://github.com/OpenXiangShan/XiangShan/pull/572))
    - 修复向量访存异常处理相关错误 ([#3722](https://github.com/OpenXiangShan/XiangShan/pull/3722), [#3720](https://github.com/OpenXiangShan/XiangShan/pull/3720), [#3714](https://github.com/OpenXiangShan/XiangShan/pull/3714), [#3704](https://github.com/OpenXiangShan/XiangShan/pull/3704), [#3702](https://github.com/OpenXiangShan/XiangShan/pull/3702), [#3695](https://github.com/OpenXiangShan/XiangShan/pull/3695))
    - 修复 mstatus.FS 关闭时，vfslide1up/down 未报非法指令异常的错误 ([#3696](https://github.com/OpenXiangShan/XiangShan/pull/3696))

- 时序/功耗优化
    - 计划重构 LoadDependency 设计：通过重构 ldcancel 依赖链 cancel 逻辑，优化 issue queue 内时序，争取增加 issue queue 容量

- RVA23 Profile
    - Debug 拓展支持 mcontrol6，废弃 mcontrol, 以支持 H 拓展的硬件断点调试 ([#3693](https://github.com/OpenXiangShan/XiangShan/pull/3693))
    - Smrnmi 拓展：提供两种 NMI 中断，并提供中断线接口 ([#3691](https://github.com/OpenXiangShan/XiangShan/pull/3691))

### 访存与缓存

- CHI 总线
  - OpenLLC：CHI-L3 接入 SoC 出现性能下降，原因定位到与转接桥并发度有关
  - CHI 转接桥：OpenNCB 支持大于 15 的内存请求并发；OpenNCB + CMN600 框架下在双核情况下支持最大 45 的内存请求并发度

- RVA23 Profile

- 性能

- Bug 修复

- 时序 & 面积优化

- 工具
  - 性能计数器：Coupled L2 HPM 接入香山 CSR，并优化输出格式 ([#3708](https://github.com/OpenXiangShan/XiangShan/pull/3708))
  - CHIron (CHI Log)：完成二进制格式的设计实现，改善记录文件大小和解析速度


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的-ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **10 月 12 日 75dea01 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 37.87  | 410.bwaves        | 75.03  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.49  |
| 403.gcc           | 46.48  | 433.milc          | 43.59  |
| 429.mcf           | 57.44  | 434.zeusmp        | 56.84  |
| 445.gobmk         | 30.16  | 435.gromacs       | 37.40  |
| 456.hmmer         | 40.83  | 436.cactusADM     | 48.59  |
| 458.sjeng         | 30.23  | 437.leslie3d      | 43.70  |
| 462.libquantum    | 125.15 | 444.namd          | 34.69  |
| 464.h264ref       | 57.82  | 447.dealII        | 74.58  |
| 471.omnetpp       | 39.69  | 450.soplex        | 54.58  |
| 473.astar         | 29.00  | 453.povray        | 56.00  |
| 483.xalancbmk     | 74.77  | 454.Calculix      | 18.32  |
| **GEOMEAN**       | 44.47  | 459.GemsFDTD      | 37.98  |
|                   |        | 465.tonto         | 38.18  |
|                   |        | 470.lbm           | 102.01 |
|                   |        | 481.wrf           | 42.59  |
|                   |        | 482.sphinx3       | 52.55  |
|                   |        | **GEOMEAN**       | 47.40  |

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
