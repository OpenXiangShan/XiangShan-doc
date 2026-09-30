---
slug: biweekly-112
date: 2026-09-30
categories:
  - Biweekly
---

# 【香山双周报 112】20260930 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 112 期双周报。

关于香山近期开发进展，前端修复了 CommonHR 历史、取指地址检查等问题并优化了 uBTB 时序；后端新增统一的向量浮点功能单元和标量浮点源操作数支持，并修复了多项向量状态、CBO 和 DiffTest 相关问题；访存与缓存集成了 ZhuJiang NoC，修复了多项向量访存、StoreQueue、异常处理和一致性相关问题，并优化了访存依赖跟踪及时序；XSAI 完善了 CUTE、NEMU 和 DiffTest 的矩阵调试能力；基础设施增强了 FPGA DiffTest、NEMU 参考模型、测试负载、采样切片和 GSIM；XS-GEM5 持续推进向量访存、预取、分支预测和执行队列等功能的模型对齐与探索。

同时向大家预告一则消息：2026 RISC-V 中国峰会将于 2026 年 10 月 18 日至 20 日在深圳会展中心（福田）举行。香山团队将在峰会上介绍最新的微架构进展，并举办香山 tutorial，期待与大家在深圳相见！

<!-- more -->

## 近期进展

### 前端

- Bug 修复
  - 修复重定向后 CommonHR 生成的历史无法参与预测的问题，使重定向后的首次 CommonHR 预测能够使用新生成的历史（[#6617](https://github.com/OpenXiangShan/XiangShan/pull/6617)）
  - 修复前端 PC canonical 地址检查，补充取指相关地址的高位传递和异常处理，覆盖 Sv39、Sv48 等地址模式（[#6272](https://github.com/OpenXiangShan/XiangShan/pull/6272)）
- 时序优化
  - 将 uBTB 命中检查移至 T1 阶段，移除 T1 到 T0 的前递，缩短 BPU 关键路径（[#6489](https://github.com/OpenXiangShan/XiangShan/pull/6489)）

### 后端

- RTL 新特性
  - （V3）将 VFALU 与 VFMul 合并为统一的 VFMac 功能单元，支持向量浮点加减、乘法和融合乘加/减法，并统一对应的配置与延迟解码（[#6573](https://github.com/OpenXiangShan/XiangShan/pull/6573)）
  - （V3）支持向量浮点指令使用标量浮点源操作数，打通 VecRegion 与 FltRegion 的寄存器读取、旁路、唤醒和重放路径（[#6615](https://github.com/OpenXiangShan/XiangShan/pull/6615)）
- Bug 修复
  - （V2）修复 vector store helper uop 错误置 `mstatus.VS` 和 `mstatus.SD` 为 Dirty 的问题，并根据 `vstart` 保留必要的状态更新（[#6570](https://github.com/OpenXiangShan/XiangShan/pull/6570)）
  - （V3）将 CBO 指令的 `numWb` 修正为 2，使解码结果匹配 StdUnit 与 StoreQueue 的双写回路径（[#6583](https://github.com/OpenXiangShan/XiangShan/pull/6583)）
  - （V3）改从 Rename 侧物理寄存器状态获取 DiffTest 的 VL，移除 CSR ROB commit 中仅供 DiffTest 使用的冗余 VL 通路，并仅在基础调试配置下连接（[#6591](https://github.com/OpenXiangShan/XiangShan/pull/6591)）
  - （V2）写入非零 `vstart` 时刷新流水线，确保后续向量指令不会使用过期状态执行（[#6613](https://github.com/OpenXiangShan/XiangShan/pull/6613)）
- 代码重构
  - （V3）使用 StdFreeList 替换整数 Rename 的 MEFreeList，保留初始物理寄存器映射，并关闭不适用于寄存器移动消除场景的 arch free list 完整性检查（[#6593](https://github.com/OpenXiangShan/XiangShan/pull/6593)）

### 访存与缓存

- RTL 新特性
  - 集成 ZhuJiang NoC 到 XiangShan 环境（[XSCache #14](https://github.com/OpenXiangShan/XSCache/pull/14)， [#6122](https://github.com/OpenXiangShan/XiangShan/pull/6122)）

- Bug 修复
  - 在检测到阻塞后优先推进 ROB 队头请求，修复跨 16B Load/Store 因 DCache/TLB 反复替换造成的 Replay 死锁（[#6590](https://github.com/OpenXiangShan/XiangShan/pull/6590)）
  - 修正 CBO 指令的双写回计数及 StoreQueue 中后续 store 的阻塞条件（[#6583](https://github.com/OpenXiangShan/XiangShan/pull/6583)）
  - 仅在 refill 无需重试时更新 L2 Directory 的 DRRIP 策略选择计数器 PSEL（[XSCache #35](https://github.com/OpenXiangShan/XSCache/pull/35)）
  - （V2）将 S3 延迟返回的 DCache 错误纳入向量 load 的最终异常状态，避免异常丢失及错误重放（[#6633](https://github.com/OpenXiangShan/XiangShan/pull/6633)）
  - （V2）初始化 Sbuffer 转发路径的 tag 匹配寄存器，避免复位后首次转发传播不定值（[#6579](https://github.com/OpenXiangShan/XiangShan/pull/6579)）
  - （V2）缓冲并发 L2 ECC 错误，并更新子模块集成该修复及 MSHR/MMIOBridge 的错误响应传播修复（[CoupledL2 #529](https://github.com/OpenXiangShan/CoupledL2/pull/529)、[#6578](https://github.com/OpenXiangShan/XiangShan/pull/6578)）
  - （V2）补齐访存首尾字节的完整虚拟地址检查及异常地址上报，并将异常地址与访存 trigger 匹配地址分离（[#6558](https://github.com/OpenXiangShan/XiangShan/pull/6558)）
  - （V2）为向量 store 向 TLB 传递正确的访问宽度，使完整虚拟地址检查覆盖实际访问字节（[#6559](https://github.com/OpenXiangShan/XiangShan/pull/6559)）
  - （V2）保留 NC load 返回后在 LoadUnit 流水线中携带的访问异常和硬件错误（[#6521](https://github.com/OpenXiangShan/XiangShan/pull/6521)）
  - （V2）在 StoreQueue 接收 CMO 响应时正确生成 `denied/corrupt` 对应的异常（[#6554](https://github.com/OpenXiangShan/XiangShan/pull/6554)）
  - （V2）为向量访存异常分别设置队列恢复与异常缓冲的 flush 级别，保留待排空的 store 并清除旧异常地址（[#6548](https://github.com/OpenXiangShan/XiangShan/pull/6548)）
  - （V2）修复 VMergeBuffer 在 VS 页表遍历发生 G-stage fault 时错误地为 `gpaddr` 叠加 unit-stride 偏移的问题（[#6514](https://github.com/OpenXiangShan/XiangShan/pull/6514)）
  - （V2）对齐 VSegmentUnit 的 trigger 结果与锁存地址，避免漏报或使用旧地址的匹配结果（[#6513](https://github.com/OpenXiangShan/XiangShan/pull/6513)）
  - （V2）阻止需要重放的标量 store 提前写回或更新 StoreQueue，并避免同一拆分 store 重复推进读指针（[#6507](https://github.com/OpenXiangShan/XiangShan/pull/6507)）
  - （V2）使 NC/MMIO `cbo.zero` 经 StoreQueue 的 MMIO 状态机完成，修复其阻塞 ROB 的问题（[#6485](https://github.com/OpenXiangShan/XiangShan/pull/6485)）
- 时序优化
  - 重构基于 SQ 指针的访存依赖跟踪，流水化 LSQ/VSQ 的出队与恢复逻辑，并优化 Load/Store、PTW 和预取仲裁路径（[#6556](https://github.com/OpenXiangShan/XiangShan/pull/6556)）

### XSAI

- 代码质量
  - 将 CI nightly 随机回归切换至 RVA23 无向量 SPEC checkpoint 池（[XSAI #130](https://github.com/OpenXiangShan/XSAI/pull/130)）
- 调试工具
  - 增加 CUTE 与 L2 联合测试顶层，并提供写请求观测接口（[CUTE #40](https://github.com/OpenXiangShan/CUTE/pull/40)、[CUTE #41](https://github.com/OpenXiangShan/CUTE/pull/41)）
  - 完善 NEMU 的 CUTE 控制模式回调与矩阵同步支持（[NEMU #1225](https://github.com/OpenXiangShan/NEMU/pull/1225)）
  - 修复 DiffTest batch 模式下 AME 事件结构体与 NEMU 的布局不一致问题（[difftest #962](https://github.com/OpenXiangShan/difftest/pull/962)）
  - 修复 CUTE DiffTest 事件的 `coreid` 与 PC 采样问题（[CUTE #42](https://github.com/OpenXiangShan/CUTE/pull/42)）
  - 限制 NEMU 矩阵加载结果的对比范围，避免未写入区域引发误报（[NEMU #1217](https://github.com/OpenXiangShan/NEMU/pull/1217)）
  - 为 NEMU 增加矩阵访存同步缺失与矩阵寄存器未定义区域读取检查（[NEMU #1212](https://github.com/OpenXiangShan/NEMU/pull/1212)、[NEMU #1224](https://github.com/OpenXiangShan/NEMU/pull/1224)）

### 基础设施

- FPGA DiffTest
  - 为 FPGA DiffTest 增加可选的 GBus 传输支持，完善 FPGA 端适配、主机运行库接入及构建流程，并修复 GBus 配置下 XDMA endpoint 的错误实例化（[env-scripts #163](https://github.com/OpenXiangShan/env-scripts/pull/163)、[env-scripts #177](https://github.com/OpenXiangShan/env-scripts/pull/177)）
  - 修复 IOTrace 的 Zstd 解压在文件末尾丢弃最后一个不完整读取块的问题，并仅保留实际解压生成的数据，避免回放提前耗尽记录（[difftest #972](https://github.com/OpenXiangShan/difftest/pull/972)）
- NEMU 参考模型
  - 修复未启用异常注入时跳过 RVH final TLB 填充的问题，恢复普通执行路径的翻译缓存，减少重复的 G-stage 地址转换（[NEMU #1218](https://github.com/OpenXiangShan/NEMU/pull/1218)）
  - 优化 GCC/x86-64 下共享参考模型的寄存器导出，使用更高效的 `memmove` 路径降低状态复制开销（[NEMU #1219](https://github.com/OpenXiangShan/NEMU/pull/1219)）
  - 修复共享参考模型的 CSR 更新标记，确保 CSR 写入及 `mret`/`sret` 后正确刷新导出的 CSR 镜像（[NEMU #1220](https://github.com/OpenXiangShan/NEMU/pull/1220)）
  - 对齐 NutShell 的 CSR 配置，支持按配置关闭 `mseccfg`，移除未实现的计数器与保护相关 CSR，并在禁用 Zicntr 时保留计数器使能位的可写性，支持 OpenSBI 模拟计时器访问（[NEMU #1221](https://github.com/OpenXiangShan/NEMU/pull/1221)、[NEMU #1222](https://github.com/OpenXiangShan/NEMU/pull/1222)、[NEMU #1223](https://github.com/OpenXiangShan/NEMU/pull/1223)）
  - 修复 Clang 构建因部分主机 CPU 特性组合警告被 `-Werror` 升级为错误的问题（[NEMU #1227](https://github.com/OpenXiangShan/NEMU/pull/1227)）
  - 同步香山 Spike 参考模型至新版上游实现，对齐 NEMU 的 ISA 扩展、PMP 布局及复位状态，并新增独立可执行版本的构建支持（[riscv-isa-sim #97](https://github.com/OpenXiangShan/riscv-isa-sim/pull/97)、[riscv-isa-sim #99](https://github.com/OpenXiangShan/riscv-isa-sim/pull/99)、[riscv-isa-sim #101](https://github.com/OpenXiangShan/riscv-isa-sim/pull/101)）
- 测试负载及采样切片
  - 完善 NutShell RV64IMAC 测试负载支持，新增设备树与 SPEC CPU2006 编译配置，支持构建 Linux 镜像及匹配的 checkpoint 恢复程序（[workload-builder #76](https://github.com/OpenXiangShan/workload-builder/pull/76)、[workload-builder #77](https://github.com/OpenXiangShan/workload-builder/pull/77)、[workload-builder #78](https://github.com/OpenXiangShan/workload-builder/pull/78)、[LibCheckpointAlpha #14](https://github.com/OpenXiangShan/LibCheckpointAlpha/pull/14)）
  - 修正 `nemu-trap`、`nemu-exec` 和 Linux `hello` 的自定义 trap 指令编码，使其通过 `a0` 正确传递控制码及退出状态（[workload-builder #75](https://github.com/OpenXiangShan/workload-builder/pull/75)）
  - 对齐 SPEC CPU2006 与 CPU2017 的单核采样控制流程，支持通过 `PROFILING=0` 关闭采样启动标记，并保留负载退出状态上报（[workload-builder #79](https://github.com/OpenXiangShan/workload-builder/pull/79)）
  - 扩展性能回归流程，支持按镜像列表运行测试负载，并配置预热指令数、最大指令数及最大周期数（[env-scripts #172](https://github.com/OpenXiangShan/env-scripts/pull/172)、[XiangShan #6600](https://github.com/OpenXiangShan/XiangShan/pull/6600)）
  - 修复虚拟化采样时 `nemu_trap` 错误关闭 Host 定时器中断的问题，仅关闭 Guest 的虚拟 supervisor 定时器中断，保留 Host 调度能力（[NEMU #1230](https://github.com/OpenXiangShan/NEMU/pull/1230)）
  - 将 NEMU 采样切片配置的内存范围扩大至 8 TiB 地址空间，与香山默认配置保持一致（[NEMU #1234](https://github.com/OpenXiangShan/NEMU/pull/1234)）
- GSIM 仿真器
  - 修复聚合数组赋值代码生成中的元素位宽处理，按目标位宽逐元素转换并限制 `memcpy` 条件，避免窄位元素被错误保留高位（[gsim #134](https://github.com/OpenXiangShan/gsim/pull/134)）
  - 放宽编译器版本约束，构建系统改为接受 Clang 19 及以上版本，并优化 `clang++` 选择与版本检查提示（[gsim #136](https://github.com/OpenXiangShan/gsim/pull/136)）
  - 修复多项代码生成宽度与有符号算术问题：聚合扩宽保留成员语义、定义有符号减法回绕行为、规范窄化输入端口写入，并规避有符号 `% -1` 的未定义行为（[gsim #137](https://github.com/OpenXiangShan/gsim/pull/137)）

### XS-GEM5

- 模拟器对齐
  - 将向量访存完成到 IEW 写回的延迟设为 3 个周期 ([XS-GEM5 #1155](https://github.com/OpenXiangShan/GEM5/pull/1155))
  - 对齐 pre-decode ([XS-GEM5 #1150](https://github.com/OpenXiangShan/GEM5/pull/1150))
  - vset 指令 ibuffer 旁路行为对齐 ([XS-GEM5 #1135](https://github.com/OpenXiangShan/GEM5/pull/1135))
  - cache hit under block 支持 ([XS-GEM5 #1164](https://github.com/OpenXiangShan/GEM5/pull/1164))
  - 浮点除法延迟对齐 ([XS-GEM5 #1167](https://github.com/OpenXiangShan/GEM5/pull/1167))
  - 向量 IQ 配置对齐 ([XS-GEM5 #1179](https://github.com/OpenXiangShan/GEM5/pull/1179))
- 新特性探索
  - 新指针预取算法 LLDP ([XS-GEM5 #1158](https://github.com/OpenXiangShan/GEM5/pull/1158))
  - 将 MBTB 和 TAGE 预测结果的可用阶段从 S3 提前到 S2 ([XS-GEM5 #1165](https://github.com/OpenXiangShan/GEM5/pull/1165))
  - 为 SMT 发射队列增加按线程保留容量的 watermark 策略 ([XS-GEM5 #1175](https://github.com/OpenXiangShan/GEM5/pull/1175))
- 基础设施
  - 实现 `cbo.zero` 指令 ([XS-GEM5 #1153](https://github.com/OpenXiangShan/GEM5/pull/1153))
  - 改进 SE 模式并完善文档 ([XS-GEM5 #1154](https://github.com/OpenXiangShan/GEM5/pull/1154))
  - 支持更多 SE 模式的 workload ([XS-GEM5 #1156](https://github.com/OpenXiangShan/GEM5/pull/1156))

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | aa6b52033  |
| 日期      | 2026/09/24 |
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
| 400.perlbench        | 57.27  | 59.16  | 410.bwaves          | 124.81 | 136.74 |
| 401.bzip2            | 30.50  | 32.49  | 416.gamess          | 60.13  | 56.82  |
| 403.gcc              | 62.21  | 44.57  | 433.milc            | 76.13  | 85.77  |
| 429.mcf              | 78.05  | 70.32  | 434.zeusmp          | 77.92  | 79.49  |
| 445.gobmk            | 45.44  | 44.31  | 435.gromacs         | 41.91  | 38.34  |
| 456.hmmer            | 54.81  | 68.30  | 436.cactusADM       | 86.71  | 90.97  |
| 458.sjeng            | 43.17  | 46.14  | 437.leslie3d        | 66.54  | 67.58  |
| 462.libquantum       | 168.06 | 380.90 | 444.namd            | 44.70  | 45.82  |
| 464.h264ref          | 69.48  | 73.54  | 447.dealII          | 65.07  | 97.13  |
| 471.omnetpp          | 56.13  | 56.73  | 450.soplex          | 66.57  | 80.45  |
| 473.astar            | 34.26  | 33.91  | 453.povray          | 79.31  | 72.48  |
| 483.xalancbmk        | 88.29  | 118.65 | 454.calculix        | 41.90  | 37.91  |
| GEOMEAN              | 59.08  | 64.70  | 459.GemsFDTD        | 80.37  | 82.58  |
|                      |        |        | 465.tonto           | 55.67  | 44.40  |
|                      |        |        | 470.lbm             | 126.33 | 153.29 |
|                      |        |        | 481.wrf             | 60.76  | 63.23  |
|                      |        |        | 482.sphinx3         | 61.06  | 63.76  |
|                      |        |        | GEOMEAN             | 68.09  | 70.74  |

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
