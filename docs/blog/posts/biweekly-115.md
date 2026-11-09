---
slug: biweekly-115
date: 2026-11-11
draft: true
categories:
  - Biweekly
---

# 【香山双周报 115】20261111 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 115 期双周报。

关于香山近期开发进展，前端统一软件指令预取调度，优化 TAGE 训练并修复分支预测问题；后端恢复 CSR 只读操作的乱序执行，修正 CBO 译码和提交类型；访存与缓存修复回滚、转发和一致性问题，并推进 Oceanus 开发；XSAI 完善精简矩阵配置和 NoLLC 内存桥，优化矩阵数据通路与验证；基础设施增强远程 FPGA DiffTest、BOOM 支持、切片与 GSIM 波形能力；XS-GEM5 推进值预测、SMT 资源分配与性能分析工具。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 新增 FtqPrefetchQueue，统一缓存和调度软件指令预取与 FDIP 请求，减少同周期软件预取丢失及其对 FDIP 的阻塞，并允许在无 bank 冲突时组合发出预取请求（[#6691](https://github.com/OpenXiangShan/XiangShan/pull/6691)）
- Bug 修复
  - 修复 VBTB 隐藏分支命中时错误抑制 MainBTB 分配的问题，并仅在条件分支实际跳转时更新目标信息，避免使用顺序 PC 污染分支目标（[#6750](https://github.com/OpenXiangShan/XiangShan/pull/6750)）
  - 使用 DataHoldBypass 保持 SC 预测响应，修复 S1 阻塞时训练重读覆盖预测数据的问题（[#6764](https://github.com/OpenXiangShan/XiangShan/pull/6764)）
  - 将 ITTAGE 分配控制显式初始化为零，修复 GSIM 中旧分配状态残留导致目标区域错误写入及分配计数失真的问题（[#6837](https://github.com/OpenXiangShan/XiangShan/pull/6837)）
- 性能优化
  - 将折叠历史纳入 TAGE bank 索引，使不同历史能够使用不同 bank 的表项；同时保存备用预测器元数据，减少正确预测训练时的 SRAM 重读冲突（[#6771](https://github.com/OpenXiangShan/XiangShan/pull/6771)、[#6800](https://github.com/OpenXiangShan/XiangShan/pull/6800)）
- PPA 优化
  - 预先计算各分支候选的 S2/S3 override 条件和不同 TAGE 结果下的跳转候选，缩短晚到信号之后的 next-PC 逻辑路径（[#6753](https://github.com/OpenXiangShan/XiangShan/pull/6753)）
- 调试工具
  - 修正 S1 预测来源及 S2 override 相关性能计数，并为地址字段和前端地址宽度约束增加更明确的编译期检查（[#6777](https://github.com/OpenXiangShan/XiangShan/pull/6777)、[#6846](https://github.com/OpenXiangShan/XiangShan/pull/6846)）

### 后端

- RTL 新特性
  - 恢复新译码单元对 CSR 只读操作的乱序执行支持，并将零源操作数的 CSR 置位、清位及立即数形式纳入相同处理，补齐 VL/VLENB 的特殊译码（[#6779](https://github.com/OpenXiangShan/XiangShan/pull/6779)）
- Bug 修复
  - 在 CBIE 要求将 `cbo.inval` 转换为 flush 时直接选择完整 opcode，避免按位或误译码为 `cbo.zero`；同时将 CBO 的提交类型修正为 STORE（[#6754](https://github.com/OpenXiangShan/XiangShan/pull/6754)、[#6847](https://github.com/OpenXiangShan/XiangShan/pull/6847)）
- 调试工具
  - 在后端调试配置下保留 CROB 前、后半条目剩余写回次数的解码结果，便于定位压缩提交问题（[#6749](https://github.com/OpenXiangShan/XiangShan/pull/6749)）

### 访存与缓存

- RTL 新特性
  - 调整软件预取在 LSU、Rename 和 Dispatch 中的处理，使其在 LoadUnit S2 结束，不计入 CROB 写回次数，也不产生正常 load 的写回和唤醒（[#6735](https://github.com/OpenXiangShan/XiangShan/pull/6735)）
  - 在 Oceanus 开发分支中对齐 CoupledL2 的 Data/Tag/Meta 存储组织和 DRRIP 替换策略，并增加基于 SRAM 与 CAM 的替换状态实现及发布参数（[XSCache #45](https://github.com/OpenXiangShan/XSCache/pull/45)）
- Bug 修复
  - 在同一 ROB 条目同时发生 RAR 与 RAW 违规时，优先选择需要重新执行当前指令的回滚，避免 RAW 重放信息被覆盖（[#6678](https://github.com/OpenXiangShan/XiangShan/pull/6678)）
  - 排除已经退休的 MDP 预测目标，避免 StoreQueue 指针回绕后让 load 永久等待不存在的 STA；修正跨 16 字节非对齐转发掩码，防止循环旋转带入不重叠的 store 字节（[#6714](https://github.com/OpenXiangShan/XiangShan/pull/6714)、[#6718](https://github.com/OpenXiangShan/XiangShan/pull/6718)）
  - 等待当前 `cbo.zero` 请求实际进入存储数据队列后再排空 Sbuffer，避免更老 store 的出队提前推进 CBO 状态机（[#6762](https://github.com/OpenXiangShan/XiangShan/pull/6762)）
  - 禁止 store 合并到已由互连接管 Acquire 的推测 load miss，避免返回权限不足以支持写入并导致后续 load 读到旧数据（[#6842](https://github.com/OpenXiangShan/XiangShan/pull/6842)）
  - 将 CoupledL2 的 L1 hint 仲裁改为带初始化的轮询仲裁，并更新主仓库集成，避免部分 slice 的 hint 长期被阻塞（[XSCache #46](https://github.com/OpenXiangShan/XSCache/pull/46)、[XSCache #48](https://github.com/OpenXiangShan/XSCache/pull/48)、[#6803](https://github.com/OpenXiangShan/XiangShan/pull/6803)）

### XSAI

- RTL 新特性
  - 打通 INT8 MMA 的配置裁剪，新增保留 BF16/FP8 的 TinyMatrixConfig，并将 MinimalMatrixConfig 的 L2 缩小至 512 KiB、统一精简配置的 LLC 容量（[CUTEFPE #5](https://github.com/OpenXiangShan/CUTEFPE/pull/5)、[CUTE #47](https://github.com/OpenXiangShan/CUTE/pull/47)、[XSAI #154](https://github.com/OpenXiangShan/XSAI/pull/154)、[XSAI #155](https://github.com/OpenXiangShan/XSAI/pull/155)、[XSAI #157](https://github.com/OpenXiangShan/XSAI/pull/157)、[XSAI #164](https://github.com/OpenXiangShan/XSAI/pull/164)）
  - 新增单核 NoLLC CHI–AXI 内存桥，支持可配置在途事务、地址顺序控制和多写缓冲，并将 TinyMatrixConfig 切换为 NoLLC（[XSAI #165](https://github.com/OpenXiangShan/XSAI/pull/165)、[XSAI #168](https://github.com/OpenXiangShan/XSAI/pull/168)、[XSAI #169](https://github.com/OpenXiangShan/XSAI/pull/169)）
- PPA 优化
  - 按启用精度裁剪矩阵乘法器宽度，压缩输入有效数与对齐移位寄存器，保留各精度的数值尺度和运算语义（[CUTEFPE #6](https://github.com/OpenXiangShan/CUTEFPE/pull/6)、[CUTEFPE #7](https://github.com/OpenXiangShan/CUTEFPE/pull/7)、[CUTE #48](https://github.com/OpenXiangShan/CUTE/pull/48)、[CUTE #49](https://github.com/OpenXiangShan/CUTE/pull/49)、[XSAI #156](https://github.com/OpenXiangShan/XSAI/pull/156)、[XSAI #159](https://github.com/OpenXiangShan/XSAI/pull/159)）
  - 移除 CUTE 和向量 exp2 流水线中冗余的数据复位，保留有效位、占用和控制状态的复位（[CUTE #54](https://github.com/OpenXiangShan/CUTE/pull/54)、[YunSuan #229](https://github.com/OpenXiangShan/YunSuan/pull/229)、[XSAI #174](https://github.com/OpenXiangShan/XSAI/pull/174)）
- Bug 修复
  - 避免 Palladium 提交监视器将合法 WFI 等待误判为卡死；同步昆明湖 V2 的回滚、PC guard bit 和共享依赖修复，并将暂不支持的 MXFP 转换输入置为确定值（[XSAI #147](https://github.com/OpenXiangShan/XSAI/pull/147)、[XSAI #171](https://github.com/OpenXiangShan/XSAI/pull/171)、[XSAI #175](https://github.com/OpenXiangShan/XSAI/pull/175)）
  - 修复 PutFullData miss 替换 victim 时未处理嵌套 snoop 的问题，使后续 CopyBackWrData 使用正确的失效状态（[XSAICache #14](https://github.com/OpenXiangShan/XSAICache/pull/14)）
- 调试工具
  - 补齐 FPGA 矩阵配置的内存 AXI 与 AMU/CUTE、Msync 探针，并分别将 AMU 控制和 msync 探针收敛为每核一份（[XSAI #160](https://github.com/OpenXiangShan/XSAI/pull/160)、[XSAI #161](https://github.com/OpenXiangShan/XSAI/pull/161)、[XSAI #166](https://github.com/OpenXiangShan/XSAI/pull/166)）
  - 区分矩阵写回数据与 store/release 完成事件，按实际探针推导写回宽度，并只为最终 K-sweep 结果生成 MMA 写回探针（[CUTE #50](https://github.com/OpenXiangShan/CUTE/pull/50)、[CUTE #51](https://github.com/OpenXiangShan/CUTE/pull/51)、[CUTE #52](https://github.com/OpenXiangShan/CUTE/pull/52)、[difftest #1025](https://github.com/OpenXiangShan/difftest/pull/1025)、[XSAI #163](https://github.com/OpenXiangShan/XSAI/pull/163)、[XSAI #167](https://github.com/OpenXiangShan/XSAI/pull/167)、[XSAI #170](https://github.com/OpenXiangShan/XSAI/pull/170)）
  - 将矩阵完成指纹切换为 CRC32C，保持写入覆盖和独立字节计数；压缩 bank-valid 与可选写回掩码，减少 DiffTest 传输负担（[NEMU #1280](https://github.com/OpenXiangShan/NEMU/pull/1280)、[difftest #1028](https://github.com/OpenXiangShan/difftest/pull/1028)、[difftest #1029](https://github.com/OpenXiangShan/difftest/pull/1029)、[CUTE #53](https://github.com/OpenXiangShan/CUTE/pull/53)、[XSAI #172](https://github.com/OpenXiangShan/XSAI/pull/172)、[XSAI #173](https://github.com/OpenXiangShan/XSAI/pull/173)）
  - 在 replay 中保存和恢复 NEMU 矩阵状态、软件 ROB 及异步验证状态，并通过独立 CUDA 服务进程支持 LightSSS 快照恢复（[NEMU #1255](https://github.com/OpenXiangShan/NEMU/pull/1255)、[difftest #987](https://github.com/OpenXiangShan/difftest/pull/987)、[difftest #1017](https://github.com/OpenXiangShan/difftest/pull/1017)）
  - 修复零尺寸和部分 tile 的 MMA 验证，统一 CPU/CUDA 与物理矩阵寄存器布局；修正 HostTLB 矩阵寄存器选择参数，并为共享参考模型启用矩阵访存快路径（[difftest #1012](https://github.com/OpenXiangShan/difftest/pull/1012)、[difftest #1013](https://github.com/OpenXiangShan/difftest/pull/1013)、[NEMU #1274](https://github.com/OpenXiangShan/NEMU/pull/1274)、[NEMU #1275](https://github.com/OpenXiangShan/NEMU/pull/1275)）
  - 复用 MMA 结果缓冲及连续操作数槽，流水化 CUDA 传输与计算，在 GPU 上比较结果，并优化 INT8、浮点和 FP8 参考计算，降低验证开销（[difftest #1014](https://github.com/OpenXiangShan/difftest/pull/1014)、[difftest #1016](https://github.com/OpenXiangShan/difftest/pull/1016)、[difftest #1018](https://github.com/OpenXiangShan/difftest/pull/1018)、[difftest #1019](https://github.com/OpenXiangShan/difftest/pull/1019)、[difftest #1021](https://github.com/OpenXiangShan/difftest/pull/1021)、[difftest #1022](https://github.com/OpenXiangShan/difftest/pull/1022)、[difftest #1023](https://github.com/OpenXiangShan/difftest/pull/1023)）
  - 在测试分支中增加 TestTopMatrix 的 VCS trace 回放、MMIO 测试接口及可配置 D 通道反压覆盖套件，完善矩阵缓存的定向验证（[XSAICache #13](https://github.com/OpenXiangShan/XSAICache/pull/13)、[XSAICache #15](https://github.com/OpenXiangShan/XSAICache/pull/15)、[tl-test-new #102](https://github.com/OpenXiangShan/tl-test-new/pull/102)、[tl-test-new #103](https://github.com/OpenXiangShan/tl-test-new/pull/103)、[tl-test-new #104](https://github.com/OpenXiangShan/tl-test-new/pull/104)）
- 基础设施
  - 通过 perf-trigger 分发 nightly checkpoint 和固定负载，修正无矩阵配置的参考模型与状态布局，并为双核 EMU 测试选择精简矩阵配置（[XSAI #149](https://github.com/OpenXiangShan/XSAI/pull/149)、[XSAI #151](https://github.com/OpenXiangShan/XSAI/pull/151)、[XSAI #153](https://github.com/OpenXiangShan/XSAI/pull/153)、[XSAI #162](https://github.com/OpenXiangShan/XSAI/pull/162)）

### 基础设施

- FPGA DiffTest
  - 在 Delta–Batch 通路和 CPU AXI R/B 响应上增加队列以隔离组合时序路径，并更新 MinJie 集成（[difftest #1004](https://github.com/OpenXiangShan/difftest/pull/1004)、[minjie-playground #47](https://github.com/OpenXiangShan/minjie-playground/pull/47)）
  - 修复 fork REF 在最后检查点通过后无法完成退出的问题，保持子进程退休推进，并为尾部检查阶段的 XDMA 超时提供有界重试（[difftest #1010](https://github.com/OpenXiangShan/difftest/pull/1010)）
  - 新增远程 XDMA 板卡中继，允许参考模型在计算主机执行，配套管理会话与清理流程，并合并寄存器写请求以减少传输延迟（[difftest #1011](https://github.com/OpenXiangShan/difftest/pull/1011)、[difftest #1020](https://github.com/OpenXiangShan/difftest/pull/1020)、[env-scripts #193](https://github.com/OpenXiangShan/env-scripts/pull/193)、[env-scripts #194](https://github.com/OpenXiangShan/env-scripts/pull/194)、[minjie-playground #41](https://github.com/OpenXiangShan/minjie-playground/pull/41)）
  - 新增 `--ila-size`，按已通过 SLOW 检查的前缀限制 DUT 超前执行周期，以配合 ILA 波形窗口；支持分别配置 CPU 工作时钟与时序目标，保持 UART 时钟固定（[difftest #1026](https://github.com/OpenXiangShan/difftest/pull/1026)、[env-scripts #185](https://github.com/OpenXiangShan/env-scripts/pull/185)）
  - 在 MinJie 中接入 BOOM 的 RTL、发布和 FPGA DiffTest 流程，并更新共享参考模型及 fast/fork 配置选择（[minjie-playground #42](https://github.com/OpenXiangShan/minjie-playground/pull/42)、[minjie-playground #43](https://github.com/OpenXiangShan/minjie-playground/pull/43)、[minjie-playground #44](https://github.com/OpenXiangShan/minjie-playground/pull/44)）
- NEMU 参考模型
  - 在主线和昆明湖 V2 分支保留 HVICTL 注入中断的原始 IID，避免错误转换 `vscause` 及向量陷入入口（[NEMU #1272](https://github.com/OpenXiangShan/NEMU/pull/1272)、[NEMU #1279](https://github.com/OpenXiangShan/NEMU/pull/1279)）
  - 在主线和昆明湖 V2 分支为成功执行的零长度向量 load 更新 VS Dirty 状态，保持不访问内存的行为（[NEMU #1277](https://github.com/OpenXiangShan/NEMU/pull/1277)、[NEMU #1278](https://github.com/OpenXiangShan/NEMU/pull/1278)）
  - 新增 NutShell FastRef 配置；昆明湖 V2 更新 ready-to-run，采用主线中的 V2 专用参考配置及共享 FAST HostTLB 支持（[NEMU #1273](https://github.com/OpenXiangShan/NEMU/pull/1273)、[#6792](https://github.com/OpenXiangShan/XiangShan/pull/6792)）
- 测试负载及采样切片
  - 为 BOOM 新增独立 Linux、设备树及 SPEC CPU2006 配置，限制编译器生成该核支持的指令；新增 GCC16 SPEC06 动态 LMUL 构建配置（[workload-builder #83](https://github.com/OpenXiangShan/workload-builder/pull/83)、[workload-builder #84](https://github.com/OpenXiangShan/workload-builder/pull/84)）
  - 将 Linux 释放 initramfs 时的填充值改为零，避免 checkpoint 恢复时为无用的非零页面分配内存（[workload-builder #85](https://github.com/OpenXiangShan/workload-builder/pull/85)）
- 开发与调试工具
  - 更新性能 profile 组织与 XSCC 切片池，启用 XSCC/SPEC17 fuzz 并过滤预计运行过慢的切片；调度器兼容非 UTF-8 仿真日志，并在可用内存不足时延迟启动任务（[env-scripts #190](https://github.com/OpenXiangShan/env-scripts/pull/190)、[#6758](https://github.com/OpenXiangShan/XiangShan/pull/6758)、[env-scripts #195](https://github.com/OpenXiangShan/env-scripts/pull/195)、[env-scripts #196](https://github.com/OpenXiangShan/env-scripts/pull/196)）
  - 支持在手工性能回归中关闭 DiffTest，并在结果目录中标注 nodiff；新增 Python CI runner 管理器，支持 runner 组的创建、扩容和运行管理（[#6804](https://github.com/OpenXiangShan/XiangShan/pull/6804)、[env-scripts #191](https://github.com/OpenXiangShan/env-scripts/pull/191)）
- GSIM 仿真器
  - 在 DiffTest 中接入 GSIM FST 波形及 LightSSS，支持 CI 出错后的自动波形生成；将周期调度移入仿真后端，修复波形采样时输入和输出错拍的问题（[difftest #867](https://github.com/OpenXiangShan/difftest/pull/867)、[#6802](https://github.com/OpenXiangShan/XiangShan/pull/6802)、[difftest #1030](https://github.com/OpenXiangShan/difftest/pull/1030)）
  - 抑制 FST 中重复的信号值变化以减少波形生成开销，并修复启用波形支持后的 Nix 构建依赖和头文件安装（[gsim #150](https://github.com/OpenXiangShan/gsim/pull/150)、[gsim #151](https://github.com/OpenXiangShan/gsim/pull/151)）

### XS-GEM5

- 新特性探索
  - 新增延迟值预测接口及 EgDiff 预测器，支持在操作数就绪后预测 load 结果；在 SE 昆明湖 V3 分支新增由已退休 fence.i 触发的可选 BPU 上下文刷新模型（[XS-GEM5 #1186](https://github.com/OpenXiangShan/GEM5/pull/1186)、[XS-GEM5 #1248](https://github.com/OpenXiangShan/GEM5/pull/1248)）
  - 根据参数扫描调整 SMT 动态借用的 ROB、LQ、SQ 默认配置，并扩展相关参数接口（[XS-GEM5 #1283](https://github.com/OpenXiangShan/GEM5/pull/1283)）
- Bug 修复
  - 支持 `vwsll.vi` 并修复首个向量 slide-up 微操作的源寄存器映射；对齐标量浮点及虚拟化执行的 FS/SD Dirty 状态（[XS-GEM5 #1280](https://github.com/OpenXiangShan/GEM5/pull/1280)、[XS-GEM5 #1281](https://github.com/OpenXiangShan/GEM5/pull/1281)）
  - 使用同周期最老 squash 边界过滤已排队和新到达的 resolve 结果，防止错误路径结果在冲刷后重新进入 BPU 训练队列（[XS-GEM5 #1282](https://github.com/OpenXiangShan/GEM5/pull/1282)）
- 调试工具
  - 引入可选的 TEA 时间占比事件分析，按 PC 和事件签名归因采样时间并导出可视化数据；补充取指块已提交指令字节统计（[XS-GEM5 #1255](https://github.com/OpenXiangShan/GEM5/pull/1255)、[XS-GEM5 #1291](https://github.com/OpenXiangShan/GEM5/pull/1291)）
- 基础设施
  - 将 Google Workload Traces 和 CBP traces 纳入 CI，更新每周 XSCC 切片池并支持选择手工周回归任务；修正 Ruby 多核 CI 的 TEA 配置（[XS-GEM5 #1272](https://github.com/OpenXiangShan/GEM5/pull/1272)、[XS-GEM5 #1274](https://github.com/OpenXiangShan/GEM5/pull/1274)、[XS-GEM5 #1300](https://github.com/OpenXiangShan/GEM5/pull/1300)、[XS-GEM5 #1269](https://github.com/OpenXiangShan/GEM5/pull/1269)）

## 性能评估

性能数据来自 2026 年 11 月 6 日启动的 [Weekly Regression](https://github.com/OpenXiangShan/XiangShan/actions/runs/42199436965)，实际测试 DefaultConfig / a253c1163（提交日期 2026 年 11 月 5 日）。GCC16 与 XSCC 分别完成 1094/1094 和 1099/1099 个 checkpoint，均无失败负载。


处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | a253c1163  |
| 日期      | 2026/11/05 |
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
| 400.perlbench        | 57.59  | 61.40  | 410.bwaves          | 146.16 | 148.79 |
| 401.bzip2            | 31.13  | 32.49  | 416.gamess          | 61.92  | 57.81  |
| 403.gcc              | 64.39  | 62.49  | 433.milc            | 77.20  | 75.81  |
| 429.mcf              | 84.44  | 80.40  | 434.zeusmp          | 78.98  | 78.42  |
| 445.gobmk            | 46.88  | 45.32  | 435.gromacs         | 43.41  | 42.68  |
| 456.hmmer            | 55.27  | 67.39  | 436.cactusADM       | 89.25  | 95.89  |
| 458.sjeng            | 45.14  | 46.48  | 437.leslie3d        | 68.40  | 67.34  |
| 462.libquantum       | 167.97 | 382.02 | 444.namd            | 47.71  | 48.63  |
| 464.h264ref          | 70.26  | 74.06  | 447.dealII          | 86.29  | 168.64 |
| 471.omnetpp          | 59.27  | 60.55  | 450.soplex          | 70.55  | 81.49  |
| 473.astar            | 35.67  | 34.25  | 453.povray          | 80.42  | 68.63  |
| 483.xalancbmk        | 92.60  | 136.98 | 454.calculix        | 48.12  | 48.15  |
| GEOMEAN              | 60.96  | 68.90  | 459.GemsFDTD        | 82.97  | 83.21  |
|                      |        |        | 465.tonto           | 79.48  | 64.71  |
|                      |        |        | 470.lbm             | 128.13 | 151.49 |
|                      |        |        | 481.wrf             | 62.60  | 61.24  |
|                      |        |        | 482.sphinx3         | 68.96  | 100.22  |
|                      |        |        | GEOMEAN             | 74.01  | 78.29  |

编译参数如下所示：

| 参数 | GCC16 | XSCC |
| --- | --- | --- |
| 编译器 | gcc16 | xscc |
| 编译优化 | O3 | O3 |
| 内存库 | jemalloc | jemalloc |
| 指令集配置 | 基于 RVA23（禁用向量扩展） | RV64GCB |
| -ffp-contract | 整数：off；浮点：fast | fast |
| 链接优化 | -flto | -flto |
| 浮点优化 | -ffast-math（povray 除外） | -ffast-math |
| -mcpu | - | xiangshan-kunminghu |

GCC16 配置还包含 -static、-fno-strict-aliasing、-fno-tree-vectorize 和 -fno-tree-loop-vectorize；具体语言及子项参数以切片池保存的构建配置为准。XSCC 编译参数按本期编辑要求沿用第 114 期，尚未重新核验本次切片的完整构建元数据。

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，SimPoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、李昕、燕翼鸣
