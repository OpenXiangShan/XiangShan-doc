---
slug: biweekly-64
date: 2024-11-25
categories:
  - Biweekly
---

# 【香山双周报 64】20241125 期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 64 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端修复 BPU s2_fire 的赋值，后端调试模式完成 dcsr 剩余字段设计，访存和缓存部分修复前端取指出现 guest page fault 时，gpaddr 生成逻辑错误的 Bug。本期还更新了昆明湖架构近期性能。


<!-- more -->

## 近期进展

### 前端

- Bug 修复
    - BPU s2_fire 赋值修复 ([#3850](https://github.com/OpenXiangShan/XiangShan/pull/3850))
    - 修复 xstatus.FS 关闭时 C 扩展 fp 指令报异常时 xtval 的值不正确的问题 ([#3859](https://github.com/OpenXiangShan/XiangShan/pull/3859))
    - 不允许顺序取指跨越 MMIO/非MMIO边界 ([#3873](https://github.com/OpenXiangShan/XiangShan/pull/3873))
    - 修复 H 扩展取指 Guest Page Fault 时 gpaddr 不正确的问题 ([#3795](https://github.com/OpenXiangShan/XiangShan/pull/3795))
    - 修复支持 Zcb 后剩余 16b 空间指令异常时 xtval 的值不正确的问题 ([#3886](https://github.com/OpenXiangShan/XiangShan/pull/3886))

- 功能
    - L1 ICache 校验出错时从 L2 重新取指 ([#3899](https://github.com/OpenXiangShan/XiangShan/pull/3899))

- 功耗
    - BPU 动态时钟门控率优化 ([#3579](https://github.com/OpenXiangShan/XiangShan/pull/3579), [#3670](https://github.com/OpenXiangShan/XiangShan/pull/3670))
    - 增加 SRAM 时钟门控，前端功耗降低 10% ([#3889](https://github.com/OpenXiangShan/XiangShan/pull/3889))

### 后端流水线

- Bug 修复
    - 修复 Debug 模式相关问题：
        - 修复 dret 返回到机器模式时，未清除虚拟特权级标志位 ([#3898](https://github.com/OpenXiangShan/XiangShan/pull/3898))
        - 修复 vstval 在访存 trigger 触发 breakpoint 异常时没有正确更新 ([#3875](https://github.com/OpenXiangShan/XiangShan/pull/3875))
    - 修复 fround/fcvtmod.w.d 指令实现问题 ([#3816](https://github.com/OpenXiangShan/XiangShan/pull/3816))
    - 修复 vnclip 立即数是无符号数问题 ([#3894](https://github.com/OpenXiangShan/XiangShan/pull/3894))
    - 修复 vlbusytable 向量浮点与整数混淆的问题 ([#3909](https://github.com/OpenXiangShan/XiangShan/pull/3909))
    - 修复 critical-error 信号传递过早导致 difftest 比对失败 ([#3885](https://github.com/OpenXiangShan/XiangShan/pull/3885))
    - 修复 flh/fsh 在 fs 关闭的时候应当报非法指令异常的问题 ([#3841](https://github.com/OpenXiangShan/XiangShan/pull/3841))
    - 修复 ase64ks1i 保留位未报非法指令异常的问题 ([#3845](https://github.com/OpenXiangShan/XiangShan/pull/3845))
    - 修复大量 NEMU 模拟器与 RTL 未对齐的问题 ([#669](https://github.com/OpenXiangShan/NEMU/pull/669), [#667](https://github.com/OpenXiangShan/NEMU/pull/667), [#666](https://github.com/OpenXiangShan/NEMU/pull/666), [#665](https://github.com/OpenXiangShan/NEMU/pull/665), [#664](https://github.com/OpenXiangShan/NEMU/pull/664))

- 时序/面积优化
    - 完成去除 dispatch queue 的新版分派算法，正在评估性能
    - 评估裁剪浮点乘加流水线条数后的性能

- RVA23 Profile
    - 调试模式完成 dcsr 剩余字段 stopcount, stoptime, nmip, certig, extcause 设计
    - 支持 critical error 进入 debug 模式 ([#3786](https://github.com/OpenXiangShan/XiangShan/pull/3786))
    - 完善 spike 对 smrnmi/dbltrp 拓展的支持 ([#3870](https://github.com/OpenXiangShan/XiangShan/pull/3870))

- 工具
    - 在 verilog 代码中插入编译所用 RTL 版本的 commitID 信息 ([#3818](https://github.com/OpenXiangShan/XiangShan/pull/3818))

### 访存与缓存

- RVA23 Profile
    - 实现完成支持 uncache outstanding 的初版 RTL 代码，正在完善自测用例并进行测试（[#3900](https://github.com/OpenXiangShan/XiangShan/pull/3900)）
    - 在 RTL 和 NEMU 中为验证 DCache ECC 添加硬件故障注入指令（[#3923](https://github.com/OpenXiangShan/XiangShan/pull/3923)），正在本地 [AM](https://github.com/OpenXiangShan/nexus-am) 环境中进行测试
    - 完成 RTL 和 NEMU 对 pointer masking（Ssnpm + Smnpm + Smmpm）扩展的支持，正在整理代码准备合入主线（[XiangShan #3921](https://github.com/OpenXiangShan/XiangShan/pull/3921), [NEMU #677](https://github.com/OpenXiangShan/NEMU/pull/677)）

- Bug 修复
    - 修复 NEMU 在虚拟化 G-stage 翻译中 GVPNi 生成逻辑错误，导致根页表的物理地址计算错误的 Bug（[NEMU #673](https://github.com/OpenXiangShan/NEMU/pull/673)）
    - 修复前端取指出现 guest page fault 时，gpaddr 生成逻辑错误的 Bug（[#3871](https://github.com/OpenXiangShan/XiangShan/pull/3871)）
    - 修复 load 指令首次进入 LoadQueueReplay 且需 redirect 时，enqMask 的生成逻辑（[#3884](https://github.com/OpenXiangShan/XiangShan/pull/3884)）

- PPA 优化
    - 时序：MemBlock 优化 ECC 校验相关的关键路径，优化时序违例 -54ps -> -40ps ([#3908](https://github.com/OpenXiangShan/XiangShan/pull/3908))
    - 面积：
      - 优化 L1 TLB 中寄存器多份复制导致的面积冗余，优化后 L1 TLB 面积降低约 24% ([#3903](https://github.com/OpenXiangShan/XiangShan/pull/3903))
      - DCache 容量不变的同时由 8-way 改为 4-way ([#3849](https://github.com/OpenXiangShan/XiangShan/pull/3849))
      - Directory 中合并 tagArray 与 eccArray ([#3902](https://github.com/OpenXiangShan/XiangShan/pull/3902))
      - 删除 MemBlock 中冗余的信号/逻辑以优化面积 ([#3560](https://github.com/OpenXiangShan/XiangShan/pull/3560))
    - 功耗：为 DCache SRAM 添加门控，MemBlock 总功耗降低 23.38% ([#3824](https://github.com/OpenXiangShan/XiangShan/pull/3824))


## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 100%**。SPEC CPU2006 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPECfp 2006 的 -ffp-contraction 选项为 fast，指令集为 RV64GCB。我们使用 **11 月 22 日 f12520c 版本**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld2st 流水线**），在仿真环境下运行了 SPEC CPU2006 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPEC CPU2006 的分数估计情况：

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est.  | @ 3GHz |
| :---------------- | :----: | :---------------- | :----: |
| 400.perlbench     | 38.09  | 410.bwaves        | 66.01  |
| 401.bzip2         | 25.53  | 416.gamess        | 43.43  |
| 403.gcc           | 47.23  | 433.milc          | 45.26  |
| 429.mcf           | 58.81  | 434.zeusmp        | 56.88  |
| 445.gobmk         | 30.26  | 435.gromacs       | 37.45  |
| 456.hmmer         | 40.79  | 436.cactusADM     | 49.19  |
| 458.sjeng         | 30.27  | 437.leslie3d      | 45.32  |
| 462.libquantum    | 124.42 | 444.namd          | 34.65  |
| 464.h264ref       | 57.74  | 447.dealII        | 74.48  |
| 471.omnetpp       | 40.03  | 450.soplex        | 54.65  |
| 473.astar         | 29.06  | 453.povray        | 55.00  |
| 483.xalancbmk     | 74.23  | 454.Calculix      | 18.33  |
| **GEOMEAN**       | 44.64  | 459.GemsFDTD      | 40.22  |
|                   |        | 465.tonto         | 38.16  |
|                   |        | 470.lbm           | 102.48 |
|                   |        | 481.wrf           | 43.22  |
|                   |        | 482.sphinx3       | 53.24  |
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
