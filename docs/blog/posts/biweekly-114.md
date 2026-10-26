---
slug: biweekly-114
date: 2026-10-28
categories:
  - Biweekly
---

# 【香山双周报 114】20261028 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 114 期双周报。

<!-- TODO: 补充本期开发进展概述。 -->

<!-- more -->

## 近期进展

### 前端

- Bug 修复
  - （V2）在 BPU、IFU 和 RAS 等通路中保留真实的 PC guard bit，修复 VS Bare / Sv48x4 地址被错误符号扩展导致的取指地址错误及 RAS 恢复后 `mepc` 被污染的问题（[#6720](https://github.com/OpenXiangShan/XiangShan/pull/6720)）
  - 为 ICache 数据 ECC 检查传递真实的取指块结束偏移，修复误将请求有效信号作为偏移导致的 bank 选择错误（[#6635](https://github.com/OpenXiangShan/XiangShan/pull/6635)）
  - 按取指请求分别传递 ICache 的 ITLB/PMP 和 TileLink 异常，修复第二个取指请求的异常传递，并按请求累积回填异常（[#6414](https://github.com/OpenXiangShan/XiangShan/pull/6414)）

### 后端

- TODO

### 访存与缓存

- RTL 新特性
  - 为 CoupledL2 增加按 set 分 bank 的 Directory/Data SRAM、hint 队列背压及预取准入限制，并更新集成至 XiangShan（[XSCache #36](https://github.com/OpenXiangShan/XSCache/pull/36)、[#6738](https://github.com/OpenXiangShan/XiangShan/pull/6738)）
  - 以 CustomL1L2Fabric 替换通用 L1–L2 互连，并加入 miss 跟踪、资源预留和可取消的推测 A 通道缓冲，以缩短 DCache 到 L2 的请求路径（[#6713](https://github.com/OpenXiangShan/XiangShan/pull/6713)）
- Bug 修复
  - 在 StoreQueue 中比较同一候选域内的虚拟地址与物理地址匹配掩码，不一致时触发 replay，修复地址别名场景下 load 转发较旧 store 数据的问题（[#6693](https://github.com/OpenXiangShan/XiangShan/pull/6693)）
  - 将 TLB 返回的指针屏蔽后地址传入 StoreUnit 后续流水级，使 store 和 CBO 异常在 `mtval`/`stval` 中报告正确地址（[#6742](https://github.com/OpenXiangShan/XiangShan/pull/6742)）

### XSAI

- RTL 新特性
  - 支持 CUTE 独立异步时钟域（[CUTE #44](https://github.com/OpenXiangShan/CUTE/pull/44)、[XSAI #135](https://github.com/OpenXiangShan/XSAI/pull/135)）
  - 优化 CUTE 多通道访存调度与矩阵寄存器写入，完善相应 DiffTest 支持（[CUTE #46](https://github.com/OpenXiangShan/CUTE/pull/46)、[difftest #991](https://github.com/OpenXiangShan/difftest/pull/991)、[XSAI #136](https://github.com/OpenXiangShan/XSAI/pull/136)）
- Bug 修复
  - 修复 XSAICache HintQueue 容量预留与重试处理问题，恢复矩阵预取总开关的控制作用（[XSAICache #10](https://github.com/OpenXiangShan/XSAICache/pull/10)）
- 调试工具
  - 加速 NEMU 矩阵寄存器 hash 计算（[NEMU #1248](https://github.com/OpenXiangShan/NEMU/pull/1248)）
  - 为矩阵 CSR 和配置状态启用 DiffTest Delta 传输（[difftest #985](https://github.com/OpenXiangShan/difftest/pull/985)、[XSAI #134](https://github.com/OpenXiangShan/XSAI/pull/134)）
  - 修复 NEMU 矩阵存储回滚时的内存恢复不完整问题（[NEMU #1251](https://github.com/OpenXiangShan/NEMU/pull/1251)）
  - 修复 DiffTest Replay 在反压下重复记录和跳过事件的问题（[difftest #990](https://github.com/OpenXiangShan/difftest/pull/990)）
  - 优化 DiffTest MMA 验证后端的内存管理、数据拷贝与计算内核（[difftest #994](https://github.com/OpenXiangShan/difftest/pull/994)、[difftest #996](https://github.com/OpenXiangShan/difftest/pull/996)、[difftest #999](https://github.com/OpenXiangShan/difftest/pull/999)、[difftest #1000](https://github.com/OpenXiangShan/difftest/pull/1000)、[difftest #1001](https://github.com/OpenXiangShan/difftest/pull/1001)、[difftest #1002](https://github.com/OpenXiangShan/difftest/pull/1002)）
  - 完善 xsai-env 可选源码与测试依赖初始化（[xsai-env #1](https://github.com/OpenXiangShan/xsai-env/pull/1)、[xsai-env #2](https://github.com/OpenXiangShan/xsai-env/pull/2)）
- 代码质量
  - 重构 NEMU 矩阵访存接口，分离事件分发与物理内存访问（[NEMU #1249](https://github.com/OpenXiangShan/NEMU/pull/1249)）

### 基础设施

- FPGA DiffTest
  - 新增可动态切换的 FAST/SLOW 参考执行模式，并在单核 XDMA 配置下支持基于 fork 的并行检查，由 SLOW 进程完整检查 DUT、按段确认结果，并在 FAST 执行分歧时接替（[difftest #980](https://github.com/OpenXiangShan/difftest/pull/980)、[NEMU #1247](https://github.com/OpenXiangShan/NEMU/pull/1247)）
  - 支持单核 REF-driving trace 的录制与独立回放，记录 SLOW、FAST 和 FORK 模式下驱动参考模型的 DUT 窗口，支持普通及 ZSTD 压缩格式（[difftest #981](https://github.com/OpenXiangShan/difftest/pull/981)）
- NEMU 参考模型
  - 在主线新增昆明湖 V2 单核、双核 REF、调试 REF 及独立运行配置，将参考模型纳入 CI 构建与发布，并以独立功能配置区分 V2/V3 行为差异，同步 HLVX 权限、LR 原子访问权限、双重陷阱及向量存储状态等公共修复（[NEMU #1246](https://github.com/OpenXiangShan/NEMU/pull/1246)）
  - 修复非 segment、单位步长向量存储跨页遇到异常时首个页面写入丢失的问题，保留已完成的部分写入及对应 DiffTest 存储记录，并同步至主线和昆明湖 V2 分支（[NEMU #1240](https://github.com/OpenXiangShan/NEMU/pull/1240)、[NEMU #1241](https://github.com/OpenXiangShan/NEMU/pull/1241)）
  - 优化 StoreHash 的 CRC 软件校验，将逐半字节查表改为按 64 位字折叠计算，降低存储记录校验开销（[NEMU #1252](https://github.com/OpenXiangShan/NEMU/pull/1252)）

### XS-GEM5

- TODO

## 性能评估

<!-- TODO: 核对处理器、SoC 及编译参数配置，补充 commit、评估日期与性能数据。 -->

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | TBD        |
| 日期      | TBD        |
| L1 ICache | 64 KB      |
| L1 DCache | 64 KB      |
| L2 Cache  | 2 MB       |
| L3 Cache  | 32 MB      |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        | TBD    | TBD    | 410.bwaves          | TBD    | TBD    |
| 401.bzip2            | TBD    | TBD    | 416.gamess          | TBD    | TBD    |
| 403.gcc              | TBD    | TBD    | 433.milc            | TBD    | TBD    |
| 429.mcf              | TBD    | TBD    | 434.zeusmp          | TBD    | TBD    |
| 445.gobmk            | TBD    | TBD    | 435.gromacs         | TBD    | TBD    |
| 456.hmmer            | TBD    | TBD    | 436.cactusADM       | TBD    | TBD    |
| 458.sjeng            | TBD    | TBD    | 437.leslie3d        | TBD    | TBD    |
| 462.libquantum       | TBD    | TBD    | 444.namd            | TBD    | TBD    |
| 464.h264ref          | TBD    | TBD    | 447.dealII          | TBD    | TBD    |
| 471.omnetpp          | TBD    | TBD    | 450.soplex          | TBD    | TBD    |
| 473.astar            | TBD    | TBD    | 453.povray          | TBD    | TBD    |
| 483.xalancbmk        | TBD    | TBD    | 454.calculix        | TBD    | TBD    |
| GEOMEAN              | TBD    | TBD    | 459.GemsFDTD        | TBD    | TBD    |
|                      |        |        | 465.tonto           | TBD    | TBD    |
|                      |        |        | 470.lbm             | TBD    | TBD    |
|                      |        |        | 481.wrf             | TBD    | TBD    |
|                      |        |        | 482.sphinx3         | TBD    | TBD    |
|                      |        |        | GEOMEAN             | TBD    | TBD    |

编译参数如下所示：

| 参数          | GCC16                      | XSCC                |
| ------------- | -------------------------- | ------------------- |
| 编译器        | gcc16                      | xscc                |
| 编译优化      | O3                         | O3                  |
| 内存库        | jemalloc                   | jemalloc            |
| 指令集配置    | 基于 RVA23（禁用向量扩展） | RV64GCB             |
| -ffp-contract | fast                       | fast                |
| 链接优化      | -flto                      | -flto               |
| 浮点优化      | -ffast-math                | -ffast-math         |
| -mcpu         | -                          | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，SimPoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、李昕、燕翼鸣
