---
slug: biweekly-113
date: 2026-10-14
categories:
  - Biweekly
---

# 【香山双周报 113】20261014 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 113 期双周报。

关于香山近期开发进展，前端新增 VictimBTB，复用 MainBTB 淘汰表项参与分支预测；后端实现混合压缩 ROB（CROB），优化 FMA 提前唤醒与旁路，并修复浮点转换和指令合法性检查等问题；访存与缓存新增支持两阶段地址翻译的 softTLB/softPTW 仿真路径，并修复 TLB 全局属性与访存违规回滚相关问题；XSAI 集成矩阵引导的 L2 预取器和独立转置加载引擎，并完善矩阵调试与 hash 对比；基础设施增强 FPGA DiffTest、NEMU、Palladium 和 AI 辅助调试工具，修复 GSIM 代码生成问题；XS-GEM5 推进 L2 预取与 SBuffer 行为对齐，修复向量 load 寄存器访问越界问题，并完善 MMIO 支持、性能回归和构建检查。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - （V3）新增全相联 VictimBTB，保存 MainBTB 淘汰的分支表项并参与预测，支持表项原地训练和重复表项清理，并适配 SC 的预测与训练通路（[#6587](https://github.com/OpenXiangShan/XiangShan/pull/6587)）

### 后端

- RTL 新特性
  - （V3）实现混合压缩 ROB（CROB），支持普通压缩和简单 ALU 指令的高密度压缩，并为双槽位 ROB 条目适配顺序提交及 DiffTest 的 StoreEvent/ArchEvent 处理（[#6648](https://github.com/OpenXiangShan/XiangShan/pull/6648)）
- Bug 修复
  - （V3）为目的寄存器为 `x0` 的浮点转换指令预留 FEX0 输出时隙，避免因不写寄存器而漏记资源占用（[#6649](https://github.com/OpenXiangShan/XiangShan/pull/6649)）
  - （V3）在 `aes64ks1i` 的轮数立即数 `rnum > 10` 时触发非法指令异常，并清理相关无效译码逻辑（[#6687](https://github.com/OpenXiangShan/XiangShan/pull/6687)）
  - （V3）更新 yunsuan，按目标浮点格式选择 CVT64Narrow 的移位偏置，修复 FP32 转 FP16 非规格化数的转换错误（[#6689](https://github.com/OpenXiangShan/XiangShan/pull/6689)）
- 性能优化
  - （V3）为 FMA 的第三源操作数 `src2` 增加来自 FMA、FMUL 和 load 的提前唤醒与旁路，使乘法阶段可提前执行，并完善 load 取消时的重放处理（[#6679](https://github.com/OpenXiangShan/XiangShan/pull/6679)）
- 代码重构
  - （V3）移除 FEX0 中未使用的 F2vCfg、向量写回端口及相关类型和写回统计逻辑（[#6651](https://github.com/OpenXiangShan/XiangShan/pull/6651)）
- 工具更新
  - （V2）更新 ready-to-run 中的 NEMU 参考模型版本（[#6620](https://github.com/OpenXiangShan/XiangShan/pull/6620)）

### 访存与缓存

- RTL 新特性
  - （V3）新增基于 DPI-C PteHelper 的 `softTLB`/`softPTW` 仿真翻译路径，支持两阶段地址翻译，用于评估 MMU 翻译性能上限（[#6115](https://github.com/OpenXiangShan/XiangShan/pull/6115)）
- Bug 修复
  - （V3）对 TLB 和页表缓存的全局属性增加 `PTE.V` 门控，修复无效 PTE 的页故障条目无法被针对特定 ASID 的 `SFENCE.VMA` 清除及跨 ASID 错误匹配的问题（[#6695](https://github.com/OpenXiangShan/XiangShan/pull/6695)）
  - （V2）在同一 load 同时触发 RAR/RAW 违规时优先进行 RAW 回滚以重新获取当前指令，避免 RAR 回滚掩盖 RAW 违规并导致读取错误数据（[#6677](https://github.com/OpenXiangShan/XiangShan/pull/6677)）

### XSAI

- RTL 新特性
  - 集成矩阵引导的 L2 预取器（[XSAI #124](https://github.com/OpenXiangShan/XSAI/pull/124)、[XSAICache #7](https://github.com/OpenXiangShan/XSAICache/pull/7)）
  - 基于双组缓冲实现独立转置加载引擎，支持多通道转置加载（[CUTE #43](https://github.com/OpenXiangShan/CUTE/pull/43)、[XSAI #132](https://github.com/OpenXiangShan/XSAI/pull/132)）
- Bug 修复
  - 同步昆明湖 V2 的 Bug 修复（[XSAI #131](https://github.com/OpenXiangShan/XSAI/pull/131)、[XSAICache #9](https://github.com/OpenXiangShan/XSAICache/pull/9)）
- 调试工具
  - 修复 DiffTest 在 MinimalMatrixConfig 下的矩阵完成事件步长错误（[difftest #976](https://github.com/OpenXiangShan/difftest/pull/976)）
  - 修复 NEMU 隐式状态更新后导出过期 CSR 值的问题（[NEMU #1237](https://github.com/OpenXiangShan/NEMU/pull/1237)）
  - 修复 NEMU 读取大体积 zstd 镜像的问题（[NEMU #1239](https://github.com/OpenXiangShan/NEMU/pull/1239)）
  - 支持矩阵寄存器 hash 对比（[CUTE #45](https://github.com/OpenXiangShan/CUTE/pull/45)、[difftest #978](https://github.com/OpenXiangShan/difftest/pull/978)、[NEMU #1238](https://github.com/OpenXiangShan/NEMU/pull/1238)、[XSAI #133](https://github.com/OpenXiangShan/XSAI/pull/133)）

### 基础设施

- FPGA DiffTest
  - 支持基于 CRC-64 的 FPGA store hash 对比，将每核每个 Squash 窗口内的 store 事件压缩为有序摘要，由 NEMU 校验对应 store 队列，降低验证数据传输量（[difftest #973](https://github.com/OpenXiangShan/difftest/pull/973)、[NEMU #1231](https://github.com/OpenXiangShan/NEMU/pull/1231)）
  - 为 FPGA 平台特定传输机制增加可选主机后端，支持寄存器访问、负载加载及 DiffTest 数据接收，并统一该后端与 XDMA 的传输接口（[difftest #954](https://github.com/OpenXiangShan/difftest/pull/954)）
- NEMU 参考模型
  - 修复 store-log 恢复中的重复写入，仅回滚指令数大于恢复点的记录，避免错误写回边界记录及产生重复的 store 对比事件（[NEMU #1250](https://github.com/OpenXiangShan/NEMU/pull/1250)）
- 开发与调试工具
  - 完善 Palladium（PLDM）构建与发布流程，修复与 DiffTest 禁用、时钟门控及 DPI 库链接相关的问题，新增 `pldm-lib` 目标支持仅重编译软件库，并补充运行与波形调试文档（[difftest #982](https://github.com/OpenXiangShan/difftest/pull/982)）
  - 完善香山 AI 辅助调试 skill，采用单用例复现与证据驱动的根因分析流程，补充 FSDB 裁剪、格式转换及定点波形分析指导，并将相关文档统一为英文（[minjie-playground #39](https://github.com/OpenXiangShan/minjie-playground/pull/39)、[minjie-playground #40](https://github.com/OpenXiangShan/minjie-playground/pull/40)）
  - 简化 DiffTest 的 AI 开发流程文档，保留计划与进度记录要求，取消固定文件路径及特定确认工具的限制（[difftest #984](https://github.com/OpenXiangShan/difftest/pull/984)）
- GSIM 仿真器
  - 支持一维数组拆分时的动态索引写入（不超过 4096 个元素），修复依赖构建与遍历顺序造成的代码生成不稳定问题，并修复 `DEBUG=1` 构建失败问题（[gsim #138](https://github.com/OpenXiangShan/gsim/pull/138)）
  - 修复有符号数全宽 `bits()` 切片保留 C++ 符号扩展高位的问题，按 FIRRTL 的无符号结果语义生成掩码，避免后续拼接结果错误，并新增覆盖全部 32 个 5 位输入值的回归测试（[gsim #141](https://github.com/OpenXiangShan/gsim/pull/141)）

### XS-GEM5

- 模拟器对齐
  - 对齐 L2 低准确率预取 offload 配置（[XS-GEM5 #1183](https://github.com/OpenXiangShan/GEM5/pull/1183)）
  - 对齐 SBuffer 对同一缓存行的 store miss 合并行为（[XS-GEM5 #1171](https://github.com/OpenXiangShan/GEM5/pull/1171)）
- Bug 修复
  - 修复向量 load 寄存器访问越界导致的 rename panic（[XS-GEM5 #1185](https://github.com/OpenXiangShan/GEM5/pull/1185)）
  - 支持 UARTLite 的 32 位 MMIO 访问（[XS-GEM5 #1199](https://github.com/OpenXiangShan/GEM5/pull/1199)）
- 基础设施
  - 更新每周性能回归配置（[XS-GEM5 #1188](https://github.com/OpenXiangShan/GEM5/pull/1188)）
  - 增加 Clang `gem5.fast` 构建检查（[XS-GEM5 #1209](https://github.com/OpenXiangShan/GEM5/pull/1209)）
  - 完善中文仓库日报生成流程（[XS-GEM5 #1204](https://github.com/OpenXiangShan/GEM5/pull/1204)、[XS-GEM5 #1212](https://github.com/OpenXiangShan/GEM5/pull/1212)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 244af70c1  |
| 日期      | 2026/10/09 |
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
| 400.perlbench        | 57.26  | 59.16  | 410.bwaves          | 142.94 | 148.07 |
| 401.bzip2            | 30.50  | 32.49  | 416.gamess          | 61.09  | 57.56  |
| 403.gcc              | 62.17  | 44.57  | 433.milc            | 76.24  | 86.48  |
| 429.mcf              | 78.05  | 70.32  | 434.zeusmp          | 78.10  | 79.78  |
| 445.gobmk            | 45.44  | 44.31  | 435.gromacs         | 42.71  | 39.24  |
| 456.hmmer            | 54.81  | 68.29  | 436.cactusADM       | 88.79  | 94.21  |
| 458.sjeng            | 43.17  | 46.04  | 437.leslie3d        | 66.80  | 68.43  |
| 462.libquantum       | 167.36 | 380.91 | 444.namd            | 47.33  | 48.38  |
| 464.h264ref          | 69.39  | 73.54  | 447.dealII          | 68.47  | 104.83 |
| 471.omnetpp          | 56.25  | 56.73  | 450.soplex          | 66.90  | 80.62  |
| 473.astar            | 34.26  | 33.91  | 453.povray          | 80.45  | 73.88  |
| 483.xalancbmk        | 88.29  | 118.65 | 454.calculix        | 46.61  | 43.31  |
| GEOMEAN              | 59.06  | 64.69  | 459.GemsFDTD        | 80.98  | 81.83  |
|                      |        |        | 465.tonto           | 59.80  | 46.98  |
|                      |        |        | 470.lbm             | 127.54 | 153.93 |
|                      |        |        | 481.wrf             | 61.18  | 63.67  |
|                      |        |        | 482.sphinx3         | 65.33  | 64.67  |
|                      |        |        | GEOMEAN             | 70.53  | 72.99  |

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
