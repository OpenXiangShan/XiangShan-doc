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

- RTL 新特性
  - 将 openLLC 容量配置扩大到 32 MB（[#6401](https://github.com/OpenXiangShan/XiangShan/pull/6401)）
  - 实现并集成独立的 L3 stash 预取路径，包括 L1 侧桥接、CHI StashOnceShared 请求及 openLLC stash refill 处理（[XSCache #25](https://github.com/OpenXiangShan/XSCache/pull/25)、[#6274](https://github.com/OpenXiangShan/XiangShan/pull/6274)）
  - 新增 TLB、请求过滤器、PTW 和 L2TLB 完成路径的性能计数器，并修正 PageCache 命中统计条件（[#6383](https://github.com/OpenXiangShan/XiangShan/pull/6383)）
  - 新增 F-POP L2 预取反馈控制器，根据命中、延迟、污染和竞争反馈调节各类预取器（[XSCache #24](https://github.com/OpenXiangShan/XSCache/pull/24)）
- Bug 修复
  - 对齐前端与 MemBlock 的 CSR 变更 TLB flush 延迟，避免旧 epoch 的 PTW 请求跨越 flush 边界（[#6421](https://github.com/OpenXiangShan/XiangShan/pull/6421)）
  - 修复 L3 预取接收端口的生成条件，并在编码前检查普通 MSHR TxnID 是否侵入 stash 预留空间（[XSCache #28](https://github.com/OpenXiangShan/XSCache/pull/28)）
  - 修复非最老的跨页非对齐 store 注入 tail 请求后持续阻塞最老请求所导致的死锁（[#6382](https://github.com/OpenXiangShan/XiangShan/pull/6382)）
  - 补齐预取请求使能向量，使六个预取器的请求使能保持同步（[XSCache #27](https://github.com/OpenXiangShan/XSCache/pull/27)）
  - 仅在 MissEntry 请求有效时允许 secondary miss 合并（[#6308](https://github.com/OpenXiangShan/XiangShan/pull/6308)）
  - （V2）在 VSegment 接管 DCache load port 0 时终止尚未完成的硬件预取请求（[#6389](https://github.com/OpenXiangShan/XiangShan/pull/6389)）
- 时序优化
  - 将 DCache WritebackQueue 的 release 仲裁从轮询策略改为最低索引优先策略（[#6379](https://github.com/OpenXiangShan/XiangShan/pull/6379)）

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

- FPGA DiffTest
  - 支持运行时动态配置 CPU AXI 各通道延迟（[difftest #950](https://github.com/OpenXiangShan/difftest/pull/950)）
  - 修复 DiffTest Squash 数据通路重复握手问题（[difftest #946](https://github.com/OpenXiangShan/difftest/pull/946)）
  - 支持 FPGA 过滤调试价值低、面积开销大的验证信号（[difftest #948](https://github.com/OpenXiangShan/difftest/pull/948)）
  - FPGA 划片约束支持 OpenLLC，并更新昆明湖 flash 初始化固件（[env-scripts #162](https://github.com/OpenXiangShan/env-scripts/pull/162)）
  - 修复 FPGA 跨片路径及时钟异步路径约束，支持按固定 CPU/RTC 比例调整运行时钟频率（[env-scripts #159](https://github.com/OpenXiangShan/env-scripts/pull/159)、[env-scripts #161](https://github.com/OpenXiangShan/env-scripts/pull/161)）
- NEMU 参考模型
  - 在 CI 中增加 nexus-am RVH 裸机回归测试（[NEMU #1162](https://github.com/OpenXiangShan/NEMU/pull/1162)）
  - 修复 RVH final TLB 命中时未恢复 MBMC 页表层级的问题（[NEMU #1171](https://github.com/OpenXiangShan/NEMU/pull/1171)）
  - 修复 Linux 开启 THP 时，按地址执行 `SFENCE.VMA` 未完整失效大页对应 HostTLB 条目的问题（[NEMU #1175](https://github.com/OpenXiangShan/NEMU/pull/1175)）
- 切片
  - 开启 Linux THP 透明大页模式，提升部分 workload 的性能（[workload-builder #54](https://github.com/OpenXiangShan/workload-builder/pull/54)）
  - QEMU 支持 UART16550 串口，并与香山平台的串口地址及参数对齐（[qemu #17](https://github.com/OpenXiangShan/qemu/pull/17)）
  - libcheckpoint 支持配置串口地址（[LibCheckpoint #27](https://github.com/OpenXiangShan/LibCheckpoint/pull/27)）
  - 改进 QEMU profilingv2 插件，通过 `nemu_trap` 显式启动 profiling，提速 23%（[qemu #16](https://github.com/OpenXiangShan/qemu/pull/16)）
  - 优化 NEMU SimPoint profiling 热路径，提速约 20%（[NEMU #1178](https://github.com/OpenXiangShan/NEMU/pull/1178)）
- GSIM 仿真器
  - 新增 `--threads` 参数控制 FIRRTL 解析器工作线程数，并根据进程可用 CPU 数量限制线程上限（[gsim #119](https://github.com/OpenXiangShan/gsim/pull/119)）
  - 完善 CI 与发布流程，引入 Dependabot、统一依赖安装，并支持多 LLVM 版本及 ARM64 构建（[gsim #121](https://github.com/OpenXiangShan/gsim/pull/121)）
  - 优化一维数组赋值的代码生成，在满足条件时使用 `memcpy` 替代逐元素复制，显著降低生成代码的编译耗时（[gsim #125](https://github.com/OpenXiangShan/gsim/pull/125)）

### XS-GEM5
- 模拟器对齐
  - CDP预取配置对齐 （[XS-GEM5 #1060](https://github.com/OpenXiangShan/GEM5/commit/ce755f54cb3fc7c93ab4b82143e9d0f54d04a2c9)）
  - BPU S1行为对齐（[XS-GEM5 #980](https://github.com/OpenXiangShan/GEM5/pull/980)）
  - 2fetch对齐 （[XS-GEM5 #1072](https://github.com/OpenXiangShan/GEM5/pull/1072)）
  - Virtual StoreQueue对齐实现 ([XS-GEM5 #991](https://github.com/OpenXiangShan/GEM5/pull/991))
  - LSU可参数化配置代码重构 ([XS-GEM5 #1042](https://github.com/OpenXiangShan/GEM5/pull/1042))
- 新特性探索
  - MDP算法PHAST ([XS-GEM5 #1008](https://github.com/OpenXiangShan/GEM5/pull/1008))
  - SMT：一拍同时预测两个线程的fetch_block ([XS-GEM5 #1052](https://github.com/OpenXiangShan/GEM5/pull/1052))
  - PairTAGE的实现（2Taken） ([XS-GEM5 #830](https://github.com/OpenXiangShan/GEM5/pull/830))
- 基础设施
  - 优化预取调度，提升模拟器速度 ([XS-GEM5 #1071](https://github.com/OpenXiangShan/GEM5/pull/1071))
  - 优化ROB及FTQ代码，提升模拟器速度 ([XS-GEM5 #1067](https://github.com/OpenXiangShan/GEM5/pull/1067))
  - CI维护，更新至GCC16相关切片 ([XS-GEM5 #1064](https://github.com/OpenXiangShan/GEM5/pull/1064))
  - CI维护，新增ASan 及 UBSan的冒烟测试 ([XS-GEM5 #1073](https://github.com/OpenXiangShan/GEM5/pull/1073))


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
