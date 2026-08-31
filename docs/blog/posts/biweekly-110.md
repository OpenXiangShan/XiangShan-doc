---
slug: biweekly-110
date: 2026-09-01
categories:
  - Biweekly
---

# 【香山双周报 110】20260901 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 110 期双周报。

<!-- more -->

## 近期进展

### 前端

- Bug 修复
  - 修复前端对 canonical PC 地址的检查，并增加相关仿真测试（[#6340](https://github.com/OpenXiangShan/XiangShan/pull/6340)）
  - 在 IFU redirect 的 `canTrain` 条件中补充 `notCfiTaken` 信号（[#6398](https://github.com/OpenXiangShan/XiangShan/pull/6398)）
  - 在 TAGE 重置 useful counter 时清空待处理的写请求，避免旧请求覆盖重置结果（[#6377](https://github.com/OpenXiangShan/XiangShan/pull/6377)）
  - 修复 TAGE 使用 base prediction 时重复读取预测表的问题（[#6356](https://github.com/OpenXiangShan/XiangShan/pull/6356)）
  - 修复 BPU S1 和 S3 均预测 not taken 时可能误触发 `s3_override` 的问题（[#6417](https://github.com/OpenXiangShan/XiangShan/pull/6417)）
  - 使用训练访问而非预测访问更新 BTB 替换状态（[#6348](https://github.com/OpenXiangShan/XiangShan/pull/6348)）
- 性能优化
  - 按预测表的训练状态维护 `UseAltOnNa`，降低分支别名干扰和寄存器开销（[#6328](https://github.com/OpenXiangShan/XiangShan/pull/6328)）
  - 同时使用 resolve 和 fast train 路径训练 uBTB，减少错误预测重定向后的额外气泡（[#6237](https://github.com/OpenXiangShan/XiangShan/pull/6237)）
- PPA 优化
  - 提前计算 `t0_firstMispredictMask`，优化 FTQ 到 BPU train cache 的写入时序（[#6375](https://github.com/OpenXiangShan/XiangShan/pull/6375)）
  - 移动 pre-decode 和 `maybeRvc` 逻辑并寄存 ICache 数据，优化 IFU/ICache 指令对齐路径时序（[#6220](https://github.com/OpenXiangShan/XiangShan/pull/6220)）
- 代码重构
  - 将 `vtype` 生成逻辑从 Decode 移至 IBuffer，使每条指令携带对应的 `vtype` 和 `specvtype`（[#6376](https://github.com/OpenXiangShan/XiangShan/pull/6376)）
  - 使用 PNR 指针判断 2-prefetch 和 2-fetch 条件，替代与 BPU 指针间的固定距离判断（[#6378](https://github.com/OpenXiangShan/XiangShan/pull/6378)）

### 后端

### 访存与缓存

### XSAI

- Bug 修复
  - 修复 MLCT 转置数据布局和 MSC/MSCT 的 C MatrixReg 读地址（[XSAI #106](https://github.com/OpenXiangShan/XSAI/pull/106)、[CUTE #38](https://github.com/OpenXiangShan/CUTE/pull/38)）
  - 修复 `msetcfg`/`mgetcfg` 误译码（[XSAI #107](https://github.com/OpenXiangShan/XSAI/pull/107)）
  - 修复矩阵访存 `AccessAckData` 响应与 HintQueue 状态不同步问题（[XSAI #110](https://github.com/OpenXiangShan/XSAI/pull/110)、[XSAICache #6](https://github.com/OpenXiangShan/XSAICache/pull/6)）
  - 修复 Mx 操作数延迟写回漏唤醒导致 MLS 指令永久阻塞的问题（[XSAI #111](https://github.com/OpenXiangShan/XSAI/pull/111)）
- 代码质量
  - 清理未使用的矩阵提交和调度反馈接口（[XSAI #113](https://github.com/OpenXiangShan/XSAI/pull/113)）
  - 优化 CI：并行化 EMU 与 nightly 回归（[XSAI #114](https://github.com/OpenXiangShan/XSAI/pull/114)、[XSAI #116](https://github.com/OpenXiangShan/XSAI/pull/116)）
- 调试工具
  - DiffTest 支持 AME `mcfg` 状态对比（[XSAI #107](https://github.com/OpenXiangShan/XSAI/pull/107)、[difftest #944](https://github.com/OpenXiangShan/difftest/pull/944)、[NEMU #1172](https://github.com/OpenXiangShan/NEMU/pull/1172)）
  - 支持 16-byte store checker 事件（[XSAI #112](https://github.com/OpenXiangShan/XSAI/pull/112)）
  - 处理 MMA 操作数获取失败，并改进 AMU 事件诊断（[difftest #926](https://github.com/OpenXiangShan/difftest/pull/926)、[difftest #927](https://github.com/OpenXiangShan/difftest/pull/927)）

### 基础设施

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项 |
| --------- | ---- |
| commit    |      |
| 日期      |      |
| L1 ICache |      |
| L1 DCache |      |
| L2 Cache  |      |
| L3 Cache  |      |
| 访存单元  |      |
| 总线协议  |      |
| 内存配置  |      |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15 | XSCC | SPECfp 2006 @ 3GHz | GCC15 | XSCC |
| :------------------ | :---: | :--: | :----------------- | :---: | :--: |
| 400.perlbench       |       |      | 410.bwaves         |       |      |
| 401.bzip2           |       |      | 416.gamess         |       |      |
| 403.gcc             |       |      | 433.milc           |       |      |
| 429.mcf             |       |      | 434.zeusmp         |       |      |
| 445.gobmk           |       |      | 435.gromacs        |       |      |
| 456.hmmer           |       |      | 436.cactusADM      |       |      |
| 458.sjeng           |       |      | 437.leslie3d       |       |      |
| 462.libquantum      |       |      | 444.namd           |       |      |
| 464.h264ref         |       |      | 447.dealII         |       |      |
| 471.omnetpp         |       |      | 450.soplex         |       |      |
| 473.astar           |       |      | 453.povray         |       |      |
| 483.xalancbmk       |       |      | 454.Calculix       |       |      |
| GEOMEAN             |       |      | 459.GemsFDTD       |       |      |
|                     |       |      | 465.tonto          |       |      |
|                     |       |      | 470.lbm            |       |      |
|                     |       |      | 481.wrf            |       |      |
|                     |       |      | 482.sphinx3        |       |      |
|                     |       |      | GEOMEAN            |       |      |

编译参数如下所示：

| 参数             | GCC15 | XSCC |
| ---------------- | ----- | ---- |
| 编译器           |       |      |
| 编译优化         |       |      |
| 内存库           |       |      |
| -march           |       |      |
| -ffp-contraction |       |      |
| 链接优化         |       |      |
| 浮点优化         |       |      |
| -mcpu            |       |      |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、燕翼鸣
