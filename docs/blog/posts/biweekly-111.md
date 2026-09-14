---
slug: biweekly-111
date: 2026-09-16
categories:
  - Biweekly
---

# 【香山双周报 111】20260916 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 111 期双周报。

<!-- more -->

## 近期进展

### 前端

### 后端

- RTL 新特性
  - 支持通过 I2F 单元执行标量 Zfa `fli.h`、`fli.s` 和 `fli.d` 指令，并按标量 NaN boxing 规则生成结果（[#6441](https://github.com/OpenXiangShan/XiangShan/pull/6441)）
  - 当 `mstatus.VS` 关闭时，将 `vsetvli`、`vsetivli` 和 `vsetvl` 解码为非法指令（[#6459](https://github.com/OpenXiangShan/XiangShan/pull/6459)）
  - 初步接入新的 VCVTWrapper（[#6473](https://github.com/OpenXiangShan/XiangShan/pull/6473)）
  - 支持向量整数宽化与窄化指令，并接入 Exu、MGU 和 VIAlu 数据通路（[#6490](https://github.com/OpenXiangShan/XiangShan/pull/6490)）
  - 支持向量转换的宽化及 2-to-1 窄化操作，窄化指令可读取两个源寄存器并写回一个完整寄存器（[#6493](https://github.com/OpenXiangShan/XiangShan/pull/6493)）
  - 在新的向量后端中加入 VFMA 单元，完善 VFMA 管线元数据和流水线寄存器（[#6503](https://github.com/OpenXiangShan/XiangShan/pull/6503)）
  - 支持向量整数除法 VIDiv，并增加基于延迟的提前唤醒机制（[#6510](https://github.com/OpenXiangShan/XiangShan/pull/6510)）
  - 恢复条件启用的 Smmtt 扩展及其 `mfence` 指令解码（[#6538](https://github.com/OpenXiangShan/XiangShan/pull/6538)）
  - 支持向量浮点除法和平方根，并接入非固定延迟的发射、唤醒与写回路径（[#6552](https://github.com/OpenXiangShan/XiangShan/pull/6552)）
- Bug 修复
  - DiffTest 更新 VL RAT 时使用专用的 `pdestVl`，避免错误使用通用目的寄存器索引（[#6440](https://github.com/OpenXiangShan/XiangShan/pull/6440)）
  - 增加 `is0FlushNext`，确保 IssuePipe 中待刷新的 is0 项能够正确清除（[#6458](https://github.com/OpenXiangShan/XiangShan/pull/6458)）
  - 修复非法 `vtype` 被当作 `vsetivli` 解析时将 `vtype[10]` 错误传入 `vl` 的问题（[#6465](https://github.com/OpenXiangShan/XiangShan/pull/6465)）
  - 修正 `VMSGTU.VI`、`VMSLEU.VI` 和 `VSADDU.VI` 的立即数扩展方式为符号扩展（[#6469](https://github.com/OpenXiangShan/XiangShan/pull/6469)）
  - 修复向量 Exu 在所有阶段都使用旁路数据的问题，仅在第 0 阶段使用旁路源操作数（[#6470](https://github.com/OpenXiangShan/XiangShan/pull/6470)）
  - 修正向量浮点指令使用 VF opcode 而非 FP opcode（[#6491](https://github.com/OpenXiangShan/XiangShan/pull/6491)）
  - 在 ex1 阶段补充 `vmax` 的 VecDataSplit 源数据（[#6492](https://github.com/OpenXiangShan/XiangShan/pull/6492)）
  - 允许 `vfwcvt` 在 SEW=8 时执行，补充对应的 FP16 转换 opcode（[#6494](https://github.com/OpenXiangShan/XiangShan/pull/6494)）
  - 修复 `vm` 为 1 时 VMove 掩码未全 1 的问题，并使 whole-register move 写回完整寄存器结果（[#6495](https://github.com/OpenXiangShan/XiangShan/pull/6495)）
  - 修复 JAL/JALR 链接与跳转 uop 的解码、重命名依赖和跳转类型跟踪（[#6496](https://github.com/OpenXiangShan/XiangShan/pull/6496)）
  - 将 `VFREC7.V` 和 `VFRSQRT7.V` 加入 fflags 写使能表（[#6506](https://github.com/OpenXiangShan/XiangShan/pull/6506)）
  - 修复旁路网络对 ready 源和非寄存器源的处理（[#6508](https://github.com/OpenXiangShan/XiangShan/pull/6508)）
  - 对齐 ROD 编码（[#6509](https://github.com/OpenXiangShan/XiangShan/pull/6509)）
  - 修复 I2F 单元的 fflags 输出（[#6519](https://github.com/OpenXiangShan/XiangShan/pull/6519)）
  - 在 CSR 读改写期间暂存并优先处理 LCOFIP，避免丢失本地计数器溢出请求（[#6522](https://github.com/OpenXiangShan/XiangShan/pull/6522)、[#6551](https://github.com/OpenXiangShan/XiangShan/pull/6551)）
  - 修正 FMA 加数的 NaN boxing 检查（[#6532](https://github.com/OpenXiangShan/XiangShan/pull/6532)）
  - 为 VMove 浮点结果增加正确的 FP boxing（[#6564](https://github.com/OpenXiangShan/XiangShan/pull/6564)）
- 时序优化
  - 在 DecodeStage 寄存 uop fire、exception 和 uopBits，缩短解码关键路径（[#6466](https://github.com/OpenXiangShan/XiangShan/pull/6466)）
- 代码重构与清理
  - 统一 LatDecoder 的 opcode 输入，支持 VMove、Stu opcode 及不确定延迟配置（[#6445](https://github.com/OpenXiangShan/XiangShan/pull/6445)）
  - 初始化新的 VIMac 支持，移除旧的 VIMacU 并统一使用 `splitToVecN`（[#6471](https://github.com/OpenXiangShan/XiangShan/pull/6471)）
  - 移除 FusionDecoder 对 DecodeUnit 的依赖及冗余的 `instructions.scala`（[#6477](https://github.com/OpenXiangShan/XiangShan/pull/6477)）
  - 清理向量 ALU 无用代码并将 vialuf 重命名为 vialu（[#6478](https://github.com/OpenXiangShan/XiangShan/pull/6478)）
  - 清理向量/访存过时代码，并修正连续 store 处理中 `vecInactive` 的状态处理（[#6479](https://github.com/OpenXiangShan/XiangShan/pull/6479)）
  - 移除旧 VFMA/VFAlu wrapper，并将对应配置的 `fuGen` 置空（[#6530](https://github.com/OpenXiangShan/XiangShan/pull/6530)）
  - 移除不再使用的 VPUCtrlSignals（[#6531](https://github.com/OpenXiangShan/XiangShan/pull/6531)）
  - 将扩展列表传入 decode fields，使解码表按启用的 ISA 扩展生成（[#6537](https://github.com/OpenXiangShan/XiangShan/pull/6537)）
  - 删除向量后端中无用的类和方法（[#6562](https://github.com/OpenXiangShan/XiangShan/pull/6562)）
  - 移除 VL busy table 中过时的 nonzero 状态及相关接口（[#6563](https://github.com/OpenXiangShan/XiangShan/pull/6563)）
  - 将向量源操作数交换延后到寄存器读取之后，统一在 Exu 中处理（[#6565](https://github.com/OpenXiangShan/XiangShan/pull/6565)）
- 工具更新
  - 更新 ready-to-run 使用的 NEMU 参考版本，包含 RV64 mstatus 初始化、SimPoint profiling 等修复与优化（[#6472](https://github.com/OpenXiangShan/XiangShan/pull/6472)）

### 访存与缓存

- RTL 新特性
  - 新增基于延迟的 LoadQueueReplay 提前唤醒机制（[#6510](https://github.com/OpenXiangShan/XiangShan/pull/6510)）
  - 将 F-POP L2 预取器集成到香山（[XSCache #24](https://github.com/OpenXiangShan/XSCache/pull/24)、[#6255](https://github.com/OpenXiangShan/XiangShan/pull/6255)）
  - 师生结构 BOP 预取器（[XSCache #29](https://github.com/OpenXiangShan/XSCache/pull/29)、[#6435](https://github.com/OpenXiangShan/XiangShan/pull/6435)）
- Bug 修复
  - 修复 LoadQueueReplay 在非对齐队头 replay 中延迟唤醒处理错误（[#6480](https://github.com/OpenXiangShan/XiangShan/pull/6480)）
  - 修复向量 inactive element 导致 StoreQueue 错误触发 uncacheMove 的问题（[#6474](https://github.com/OpenXiangShan/XiangShan/pull/6474)）
  - 修复非对齐 replay 时 LoadUnit 未保留队头 TLB 元数据的问题（[#6457](https://github.com/OpenXiangShan/XiangShan/pull/6457)）
  - 修复 AtomicsUnit 的异常生成逻辑（[#6316](https://github.com/OpenXiangShan/XiangShan/pull/6316)）
  - （V2）使用 PMM 归一化后的虚拟地址处理 LoadUnit 和 StoreUnit trigger（[#6311](https://github.com/OpenXiangShan/XiangShan/pull/6311)）
  - （V2）支持 unit-stride store 的 partial replay（[#6434](https://github.com/OpenXiangShan/XiangShan/pull/6434)）
  - （V2）将向量访存异常的 `gpaddr` 扩展至 XLEN 宽度（[#6432](https://github.com/OpenXiangShan/XiangShan/pull/6432)）
- 时序优化
  - 将 LoadQueueReplay 流水线由三级缩短为两级，并优化 DCache、Uncache、TLB hint 和 replay 仲裁路径（[#6422](https://github.com/OpenXiangShan/XiangShan/pull/6422)）

### XSAI

### 基础设施

### XS-GEM5

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 53a957667  |
| 日期      | 2026/08/21 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 2MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC16  |  XSCC  | SPECfp 2006 @ 3GHz | GCC16  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 55.02  | 53.33  | 410.bwaves         | 123.07 | 105.77 |
| 401.bzip2           | 29.89  | 30.60  | 416.gamess         | 58.70  | 55.81  |
| 403.gcc             | 58.27  | 41.61  | 433.milc           | 71.84  | 68.77  |
| 429.mcf             | 72.01  | 62.81  | 434.zeusmp         | 77.33  | 67.78  |
| 445.gobmk           | 43.70  | 42.34  | 435.gromacs        | 40.04  | 35.10  |
| 456.hmmer           | 54.59  | 67.12  | 436.cactusADM      | 85.01  | 93.51  |
| 458.sjeng           | 41.66  | 41.74  | 437.leslie3d       | 61.20  | 61.31  |
| 462.libquantum      | 138.17 | 305.05 | 444.namd           | 44.25  | 45.26  |
| 464.h264ref         | 69.92  | 75.51  | 447.dealII         | 64.71  | 79.14  |
| 471.omnetpp         | 48.18  | 47.76  | 450.soplex         | 59.78  | 72.28  |
| 473.astar           | 33.06  | 32.50  | 453.povray         | 78.25  | 73.65  |
| 483.xalancbmk       | 85.35  | 92.62  | 454.Calculix       | 41.80  | 40.77  |
| GEOMEAN             | 55.75  | 58.70  | 459.GemsFDTD       | 74.41  | 73.41  |
|                     |        |        | 465.tonto          | 55.70  | 37.80  |
|                     |        |        | 470.lbm            | 127.10 | 146.69 |
|                     |        |        | 481.wrf            | 58.65  | 44.97  |
|                     |        |        | 482.sphinx3        | 61.39  | 64.02  |
|                     |        |        | GEOMEAN            | 66.14  | 63.98  |

编译参数如下所示：

| 参数             | GCC16                       | XSCC                |
| ---------------- | --------------------------- | ------------------- |
| 编译器           | gcc16                       | xscc                |
| 编译优化         | O3                          | O3                  |
| 内存库           | jemalloc                    | jemalloc            |
| 指令集配置       | 基于 RVA23（禁用向量扩展） | RV64GCB             |
| -ffp-contraction | fast                        | fast                |
| 链接优化         | -flto                       | -flto               |
| 浮点优化         | -ffast-math                 | -ffast-math         |
| -mcpu            | -                           | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、甄好、燕翼鸣
