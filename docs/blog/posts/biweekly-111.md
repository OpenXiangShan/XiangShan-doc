---
slug: biweekly-111
date: 2026-09-16
categories:
  - Biweekly
---

# 【香山双周报 111】20260916 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 111 期双周报。

关于香山近期开发进展，前端新增 BPU S2 override 并扩大超前距离，修复了 ICache 替换策略相关 bug；后端完善了向量宽化、窄化、乘加及除法支持，并修复了多项解码、旁路和浮点处理相关 bug；访存与缓存方面，集成了 F-POP 和师生结构 BOP 预取器，新增 LoadQueueReplay 提前唤醒并优化其流水线；XSAI 支持在 CUTE 访存请求中传递矩阵预取描述信息，修复了预取活锁，并完善了 AME DiffTest 检查；基础设施完善了 FPGA DiffTest 流程，优化 NEMU 参考模型，扩展测试负载并修复 GSIM 仿真问题；XS-GEM5 持续对齐 Sbuffer、向量写回和 BPU 等行为，并优化 SMT 流水线与 LSQ 竞争逻辑。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 新增 BPU S2 override，使用 MainBTB 和 TAGE provider 的快速预测结果提前修正 S1 预测，并重构 AheadBTB 以支持该流程（[#6423](https://github.com/OpenXiangShan/XiangShan/pull/6423)）
- Bug 修复
  - 为 ICache 替换策略增加第二组访问更新端口，修复 2-fetch 时第二个取指块未更新 PLRU 状态的问题（[#6416](https://github.com/OpenXiangShan/XiangShan/pull/6416)）
- 性能优化
  - 统一 BPU 超前距离与 ICache WayLookup 深度，默认将超前距离由 8 扩大至 32，使预取流水线能够充分填充 WayLookup（[#6425](https://github.com/OpenXiangShan/XiangShan/pull/6425)）
- PPA 优化
  - 缩小 MainBTB WriteBuffer 在 `hitWritten` 时检查表项变化的比较范围，减少比较逻辑（[#5898](https://github.com/OpenXiangShan/XiangShan/pull/5898)）
  - 比较 MainBTB 与 S1 预测的跳转目标时，仅比较必要的目标地址低位，减少冗余比较逻辑（[#6431](https://github.com/OpenXiangShan/XiangShan/pull/6431)）

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
  - 修复 `vm` 为 1 时 VMove 掩码未全部置 1 的问题，并使 whole-register move 写回完整寄存器结果（[#6495](https://github.com/OpenXiangShan/XiangShan/pull/6495)）
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

- RTL 新特性
  - 为 CUTE 访存请求传递矩阵预取描述信息（[CUTE #39](https://github.com/OpenXiangShan/CUTE/pull/39)）
- Bug 修复
  - 同步昆明湖 V2 的 bug-fix（[XSAI #123](https://github.com/OpenXiangShan/XSAI/pull/123)、[XSAI #129](https://github.com/OpenXiangShan/XSAI/pull/129)）
  - 修复预取 RequestBuffer 活锁（[XSAI #126](https://github.com/OpenXiangShan/XSAI/pull/126)、[XSAICache #8](https://github.com/OpenXiangShan/XSAICache/pull/8)）
- 代码质量
  - 更新 nightly 回归 checkpoint 池并固定 matrix jobs 使用 node runner（[XSAI #120](https://github.com/OpenXiangShan/XSAI/pull/120)、[XSAI #122](https://github.com/OpenXiangShan/XSAI/pull/122)）
- 调试工具
  - 完善 AME DiffTest 的 `mrelease` 退役与旧 `mstore` 顺序检查（[XSAI #121](https://github.com/OpenXiangShan/XSAI/pull/121)、[difftest #953](https://github.com/OpenXiangShan/difftest/pull/953)、[XSAI #128](https://github.com/OpenXiangShan/XSAI/pull/128)、[difftest #958](https://github.com/OpenXiangShan/difftest/pull/958)）
  - 为 AME 错误路径记录正确的指令 PC（[XSAI #121](https://github.com/OpenXiangShan/XSAI/pull/121)、[difftest #955](https://github.com/OpenXiangShan/difftest/pull/955)）
  - 优化 NEMU 浮点 MMACC，并完善指令语义检查（[NEMU #1189](https://github.com/OpenXiangShan/NEMU/pull/1189)、[NEMU #1197](https://github.com/OpenXiangShan/NEMU/pull/1197)、[NEMU #1200](https://github.com/OpenXiangShan/NEMU/pull/1200)）

### 基础设施

- FPGA DiffTest
  - 整理 FPGA 运行流程，支持 Runtime/Host 跨主机命令协同，完善设备状态检查及运行结束后的清理流程（[env-scripts #167](https://github.com/OpenXiangShan/env-scripts/pull/167)、[env-scripts #168](https://github.com/OpenXiangShan/env-scripts/pull/168)、[minjie-playground #31](https://github.com/OpenXiangShan/minjie-playground/pull/31)）
  - 新增香山 DiffTrapEvent 探针，并修复 DiffTest 信号命名，使指定信号能够通过 XMR 路径进行 ILA 采集（[env-scripts #165](https://github.com/OpenXiangShan/env-scripts/pull/165)、[difftest #959](https://github.com/OpenXiangShan/difftest/pull/959)）
  - 补充 XDMA pre-PERST 时钟与 PCIe 参考时钟之间的异步 CDC 约束（[env-scripts #169](https://github.com/OpenXiangShan/env-scripts/pull/169)）
  - 修复 Replay 中浅拷贝 DiffState 所引起的状态所有权错误，避免在恢复快照时复制队列和集合等临时状态（[difftest #957](https://github.com/OpenXiangShan/difftest/pull/957)）
- NEMU 参考模型
  - 优化未使用掩码的向量访存路径，避免无须执行的 `v0` 读取（[NEMU #1155](https://github.com/OpenXiangShan/NEMU/pull/1155)）
  - 精简单指令共享 REF 的执行边界，并在 CSR 状态未发生变化时跳过重复的 CSR 镜像准备（[NEMU #1136](https://github.com/OpenXiangShan/NEMU/pull/1136)、[NEMU #1027](https://github.com/OpenXiangShan/NEMU/pull/1027)）
  - 缓存有效地址无需转换的状态，简化共享 REF 页表遍历中的 PTE 读取路径，同时保持原有权限与异常检查语义（[NEMU #1011](https://github.com/OpenXiangShan/NEMU/pull/1011)、[NEMU #1138](https://github.com/OpenXiangShan/NEMU/pull/1138)）
  - 在未启用 profiling 或 checkpointing 时，跳过基本块边界上的重复轮询（[NEMU #1137](https://github.com/OpenXiangShan/NEMU/pull/1137)）
- 采样切片
  - 新增七类 RVA23 Linux RocksDB 测试负载，覆盖读写混合、随机事务及时间序列等场景（[workload-builder #66](https://github.com/OpenXiangShan/workload-builder/pull/66)）
  - 支持 Geekbench 5/6 Preview 离线运行（[workload-builder #62](https://github.com/OpenXiangShan/workload-builder/pull/62)）
  - 修复 Linux `hello` 中消息地址被错误松弛为 `gp` 相对寻址的问题，并在输出失败时正确报告运行结果（[workload-builder #67](https://github.com/OpenXiangShan/workload-builder/pull/67)）
  - 为 SPEC CPU2017/2026 适配 jemalloc，修复 SPEC2017 多命令运行脚本，并统一 SPEC 负载的 jemalloc 配置（[workload-builder #56](https://github.com/OpenXiangShan/workload-builder/pull/56)、[workload-builder #68](https://github.com/OpenXiangShan/workload-builder/pull/68)）
  - 整理 QEMU `nemu` 机器的 workload 构建与运行支持，包括平台 DTS、固件输出及运行脚本（[workload-builder #60](https://github.com/OpenXiangShan/workload-builder/pull/60)）
  - 根据选定 DTS 中的 DRAM 基址和 CLINT 地址，自动配置单核固件、内核及 checkpoint 的地址布局，生成与目标平台配置匹配的镜像（[workload-builder #55](https://github.com/OpenXiangShan/workload-builder/pull/55)）
  - 确认 profiling 指令数波动源于 DTS 随机种子；统一固定 `rng-seed` 后，采样指令数保持稳定（[workload-builder #57](https://github.com/OpenXiangShan/workload-builder/pull/57)）
  - 对齐 workload-builder DTS 与香山平台的 ISA 扩展声明，并更新香山核心的 ISA 扩展参数（[workload-builder #59](https://github.com/OpenXiangShan/workload-builder/pull/59)、[XiangShan #6463](https://github.com/OpenXiangShan/XiangShan/pull/6463)）
  - 支持依据 `nemu_board` 配置，在构建时动态生成匹配的 DTS，统一 FPGA、QEMU 和 NEMU 的设备树配置（[workload-builder #71](https://github.com/OpenXiangShan/workload-builder/pull/71)）
- GSIM 仿真器
  - 修复动态右移超移时的未定义行为，超移后无符号值返回零、有符号值按符号填充，避免 DiffTest 失败（[gsim #128](https://github.com/OpenXiangShan/gsim/pull/128)）
  - 修复常量传播中有符号右移误将目的操作数作为输入，导致负数右移被错误折叠为零的问题（[gsim #129](https://github.com/OpenXiangShan/gsim/pull/129)）
  - 修复节点拆分中有符号常量切片语义，负数算术右移改用 floor 除法保留符号扩展，位选择先转为无符号表示（[gsim #130](https://github.com/OpenXiangShan/gsim/pull/130)）
  - 修复拼接常量等值比较优化中高位切片边界差一的错误，按拼接实际布局精确切片，避免比较结果出错（[gsim #131](https://github.com/OpenXiangShan/gsim/pull/131)）
  - 为动态向量索引添加边界保护，越界读返回确定零值、越界写变为空操作，消除越界读写的未定义行为（[gsim #132](https://github.com/OpenXiangShan/gsim/pull/132)）

### XS-GEM5

- 模拟器对齐
  - Sbuffer 行为对齐（[XS-GEM5 #1140](https://github.com/OpenXiangShan/GEM5/pull/1140)）
  - 向量指令写回行为对齐（[XS-GEM5 #1113](https://github.com/OpenXiangShan/GEM5/pull/1113)）
  - IQ 对齐（[XS-GEM5 #1127](https://github.com/OpenXiangShan/GEM5/pull/1127)）
  - 浮点除法行为对齐（[XS-GEM5 #1116](https://github.com/OpenXiangShan/GEM5/pull/1116)）
  - BPU 行为对齐（[XS-GEM5 #1122](https://github.com/OpenXiangShan/GEM5/pull/1122)）
- 代码质量
  - 向量代码整理（[XS-GEM5 #1075](https://github.com/OpenXiangShan/GEM5/pull/1075)）
- 新特性探索
  - SMT：取指阻塞与流水线冲刷策略优化（[XS-GEM5 #1124](https://github.com/OpenXiangShan/GEM5/pull/1124)）（感谢来自阿里同事的贡献）
  - SMT：优化 SMT 情况下 LSQ 的竞争逻辑（[XS-GEM5 #1094](https://github.com/OpenXiangShan/GEM5/pull/1094)）（感谢来自中兴同事的贡献）
- 基础设施
  - AMO 指令 bug 修复（[XS-GEM5 #1098](https://github.com/OpenXiangShan/GEM5/pull/1098)）（感谢来自阿里同事的贡献）
  - 新指令实现（[XS-GEM5 #1118](https://github.com/OpenXiangShan/GEM5/pull/1118)）（感谢来自阿里同事的贡献）
  - CI 维护，统一使用的 NEMU 版本（[XS-GEM5 #1105](https://github.com/OpenXiangShan/GEM5/pull/1105)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 0eea07ed9  |
| 日期      | 2026/09/11 |
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
| 400.perlbench        | 56.40  | 54.24  | 410.bwaves          | 126.11 | 112.18 |
| 401.bzip2            | 30.49  | 31.20  | 416.gamess          | 59.54  | 56.55  |
| 403.gcc              | 61.93  | 42.58  | 433.milc            | 76.56  | 73.10  |
| 429.mcf              | 77.90  | 64.10  | 434.zeusmp          | 79.58  | 70.77  |
| 445.gobmk            | 44.90  | 44.46  | 435.gromacs         | 41.68  | 36.92  |
| 456.hmmer            | 54.74  | 67.53  | 436.cactusADM       | 86.33  | 94.33  |
| 458.sjeng            | 43.73  | 43.69  | 437.leslie3d        | 66.56  | 64.63  |
| 462.libquantum       | 164.48 | 382.99 | 444.namd            | 44.46  | 45.48  |
| 464.h264ref          | 69.46  | 76.01  | 447.dealII          | 66.08  | 81.12  |
| 471.omnetpp          | 56.40  | 56.29  | 450.soplex          | 65.94  | 79.40  |
| 473.astar            | 34.28  | 33.67  | 453.povray          | 79.62  | 74.37  |
| 483.xalancbmk        | 89.19  | 107.78 | 454.calculix        | 42.15  | 41.17  |
| GEOMEAN              | 58.94  | 62.57  | 459.GemsFDTD        | 80.02  | 76.96  |
|                      |        |        | 465.tonto           | 55.04  | 37.92  |
|                      |        |        | 470.lbm             | 128.56 | 149.77 |
|                      |        |        | 481.wrf             | 59.50  | 45.14  |
|                      |        |        | 482.sphinx3         | 62.02  | 64.63  |
|                      |        |        | GEOMEAN             | 68.19  | 65.95  |

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

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、甄好、燕翼鸣
