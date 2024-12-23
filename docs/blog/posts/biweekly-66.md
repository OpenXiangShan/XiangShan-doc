---
slug: biweekly-66
date: 2024-12-23
categories:
  - Biweekly
---

# 【香山双周报 66】20241223 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 66 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - 修复 ([#1](https://github.com/OpenXiangShan/XiangShan/pull/1))

- 面积

### 后端流水线

- Bug 修复
    - 修复部分向量指令无法设置 vs dirty 的问题 ([#4024](https://github.com/OpenXiangShan/XiangShan/pull/4024))
    - 修复在 LMUL 小于 1 时， vlmax 设置出错的问题 ([#4028](https://github.com/OpenXiangShan/XiangShan/pull/4028))
    - 修复 rocket-chip 未处理对向量掩码指令保留 vm 为 0 的问题 ([#3918](https://github.com/OpenXiangShan/XiangShan/pull/3918))
    - 修复在 rob 满时快照选取以及 walk 时刷新出错的问题 ([#4049](https://github.com/OpenXiangShan/XiangShan/pull/4049))
    - 修复在 menvcfg.DTE 关闭时，写 sdt 对 sie 错误清空的问题 ([#4064](https://github.com/OpenXiangShan/XiangShan/pull/4064))
    - 修复在 VS 模式处理的部分中断，计算陷入 PC 出错的问题 ([#4054](https://github.com/OpenXiangShan/XiangShan/pull/4054))
    - 修复 NEMU FS/VS dirty 同步逻辑 ([#720](https://github.com/OpenXiangShan/NEMU/pull/720))
    - 修复 NEMU LCOFI 中断相关系列问题 ([#733](https://github.com/OpenXiangShan/NEMU/pull/733), [#729](https://github.com/OpenXiangShan/NEMU/pull/729))

- 面积优化
    - 目前后端整体面积已减小 25% 。
    - 将 IQ 中 exuOH 编码为 UInt 类型减少存储空间 ([#4033](https://github.com/OpenXiangShan/XiangShan/pull/4033))
    - 修复 VFMA/FMA 面积过大问题 ([#4069](https://github.com/OpenXiangShan/XiangShan/pull/4069))
    - 功能单元新增可选参数：控制复制源操作数 ([#4063](https://github.com/OpenXiangShan/XiangShan/pull/4063))
    - 合入先前完成的新版 dispatch 逻辑、新版 TargeMem、将四条标量浮点缩减为三条等 ppa 优化点 ([#4049](https://github.com/OpenXiangShan/XiangShan/pull/4049))

- 时序优化
    - 修改 rob 选择逻辑，准确从出队组中选择 ([#4067](https://github.com/OpenXiangShan/XiangShan/pull/4067))
    - 向量复杂译码器按照顺序每周期出 6 条 uop ([#4025](https://github.com/OpenXiangShan/XiangShan/pull/4025))
    - 增加 newestTarget 旁路，从每个读口均存一份改为只存一份 ([#4049](https://github.com/OpenXiangShan/XiangShan/pull/4049))

- RVA23 Profile
    - Trace 拓展已合入香山主线 ([#3843](https://github.com/OpenXiangShan/XiangShan/pull/3843))

### 访存与缓存

- CHI 总线
  - 提升 CHI-AXI 转接桥并发度 ([#4008](https://github.com/OpenXiangShan/XiangShan/pull/4008))

- RVA23 Profile
  - CMO：在 tl-test-new 上添加 cbo.inval 指令的测试环境，通过双核测试 ([tl-test-new #45](https://github.com/OpenXiangShan/tl-test-new/pull/45))

- Bug 修复

- PPA 优化
  - 时序：优化 StoreQueue 中关键路径 ([#3988](https://github.com/OpenXiangShan/XiangShan/pull/3988))
  - 面积：删除 VirtualLoadQueue 中冗余的寄存器 ([#4061](https://github.com/OpenXiangShan/XiangShan/pull/4061))；删除 DCache 中冗余的 CacheOpDecoder ([#4050](https://github.com/OpenXiangShan/XiangShan/pull/4050))
  - 功耗：裁剪 LSQ，优化 MemBlock 功耗 ([#4059](https://github.com/OpenXiangShan/XiangShan/pull/4059))；单核关断进行冒烟测试


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **12 月 06 日 a60d667 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.10  | 410.bwaves        | 67.07  |
| 401.bzip2         | 25.53  | 416.gamess        | 42.95  |
| 403.gcc           | 47.17  | 433.milc          | 45.29  |
| 429.mcf           | 58.86  | 434.zeusmp        | 56.75  |
| 445.gobmk         | 30.30  | 435.gromacs       | 37.44  |
| 456.hmmer         | 40.79  | 436.cactusADM     | 49.30  |
| 458.sjeng         | 30.22  | 437.leslie3d      | 45.29  |
| 462.libquantum    | 124.56 | 444.namd          | 34.65  |
| 464.h264ref       | 57.72  | 447.dealII        | 74.37  |
| 471.omnetpp       | 40.11  | 450.soplex        | 54.63  |
| 473.astar         | 29.14  | 453.povray        | 54.95  |
| 483.xalancbmk     | 73.25  | 454.Calculix      | 18.33  |
| **GEOMEAN**       | 44.61  | 459.GemsFDTD      | 40.22  |
|                   |        | 465.tonto         | 37.99  |
|                   |        | 470.lbm           | 102.47 |
|                   |        | 481.wrf           | 43.22  |
|                   |        | 482.sphinx3       | 53.26  |
|                   |        | **GEOMEAN**       | 47.48  |

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
