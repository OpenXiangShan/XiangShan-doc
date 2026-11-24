---
slug: biweekly-116
date: 2026-11-25
categories:
  - Biweekly
---

# 【香山双周报 116】20261125 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 116 期双周报。

关于香山近期开发进展，前端修正虚拟化取指的故障地址，修复 ICache 误报 ECC 错误的问题，后端为昆明湖 V3 增加中断、异常和指令计数触发器。访存与缓存支持在昆明湖 V2 上为可缓存访存启用 TSO，并修复页表遍历与访存重放停滞的问题。XSAI 支持将矩阵寄存器写回内存，并优化多核矩阵校验。基础设施将 RISC-V 架构冒烟测试纳入回归，让每轮性能回归中的各项负载共用同一份仿真器。XS-GEM5 完善双线程访存模型，新增指令分派分析工具。

<!-- more -->

## 近期进展

### 前端

- Bug 修复
  - 修正虚拟化取指的客户页故障地址，在昆明湖 V3 中按首个取指块的起始地址查询 ITLB，直接使用返回的客户物理地址，在 V2 中保留触发故障的 VS 级非叶页表项地址（[#6870](https://github.com/OpenXiangShan/XiangShan/pull/6870)、[#6911](https://github.com/OpenXiangShan/XiangShan/pull/6911)）
  - 按最短指令长度（2 字节）发起 ICache 的 ITLB 和 PMP 检查，修复昆明湖 V2 和 V3 在合法地址范围末端取指时误报页故障的问题（[#6945](https://github.com/OpenXiangShan/XiangShan/pull/6945)、[#6947](https://github.com/OpenXiangShan/XiangShan/pull/6947)）
  - 仅对有效取指请求检查 ICache 标签和数据的 ECC，避免第二个请求槽空闲时向总线错误单元误报错误（[#6871](https://github.com/OpenXiangShan/XiangShan/pull/6871)）
  - 按取指地址模式补齐 ITTAGE 预测目标的高位，修复高、低规范地址区间之间的间接跳转预测，并在 VS Bare 模式下正确扩展无符号客户物理地址（[#6986](https://github.com/OpenXiangShan/XiangShan/pull/6986)）

### 后端

- RTL 新特性
  - 为昆明湖 V3 新增中断触发器 `itrigger` 和异常触发器 `etrigger`，在第 0 个槽位支持指令计数触发器 `icount`，并在 Spike 参考模型中对齐支持的触发器类型（[#6942](https://github.com/OpenXiangShan/XiangShan/pull/6942)、[riscv-isa-sim #103](https://github.com/OpenXiangShan/riscv-isa-sim/pull/103)）
- Bug 修复
  - 在 CSR 读操作的写回流水线中逐级传递有效位和 ROB 索引，使重定向能取消尚未写回的错误路径读取（[#6853](https://github.com/OpenXiangShan/XiangShan/pull/6853)）
  - 处理 `hvictl` 注入的 VS 中断时保留原始中断号，使 `vscause` 和向量陷入入口使用相同的中断号（[#6793](https://github.com/OpenXiangShan/XiangShan/pull/6793)）
  - 在 `vsetvl` 类指令冲刷流水线后延迟一拍恢复译码，使后续向量指令读到提交时清零的 `vstart`，避免误报非法指令（[#6983](https://github.com/OpenXiangShan/XiangShan/pull/6983)）
  - 当 CSR 写入改变当前特权级的断点使能条件时重新取指，确保取指触发器使用更新后的条件（[#6865](https://github.com/OpenXiangShan/XiangShan/pull/6865)）
  - 在跳转单元发起后端重定向时保留压缩指令标记，使流水线能正确识别触发重定向的压缩跳转指令（[#6917](https://github.com/OpenXiangShan/XiangShan/pull/6917)）
- PPA 优化
  - 在同一 ROB bank 内共享入队头部数据的选择逻辑，减少各表项重复的选择电路（[#6930](https://github.com/OpenXiangShan/XiangShan/pull/6930)）
- 代码质量
  - 在 ROB 中单独保存提交类型、功能单元类型和操作类型，使异常与向量访存处理只需读取这三个字段，调试和验证仍可读取完整微操作（[#6937](https://github.com/OpenXiangShan/XiangShan/pull/6937)）
- 调试工具
  - 将浮点发射队列的占用、发射和取消信息纳入 Top-down 性能分析，区分 ROB 队首因发射取消而停顿的周期（[#6709](https://github.com/OpenXiangShan/XiangShan/pull/6709)）
  - 为总线错误单元增加可选的独立冷复位输入，使暖复位后仍可读取已记录的错误（[#6740](https://github.com/OpenXiangShan/XiangShan/pull/6740)）

### 访存与缓存

- RTL 新特性
  - 新增监管态 CSR `stsoctl`，支持在昆明湖 V2 上为可缓存访存启用 TSO，复位后默认使用 RVWMO。TSO 模式下需保持 load-load 违规检查开启，SBuffer 按序排空。软件须在启用 TSO 后、关闭 TSO 前分别执行 `fence rw,rw`（[#6940](https://github.com/OpenXiangShan/XiangShan/pull/6940)、[#6962](https://github.com/OpenXiangShan/XiangShan/pull/6962)）
  - 在 L2 TLB 回填时跳过会引发页故障的页表项，并默认在 L1 TLB 使用页故障项后将其清除。软件可通过 `smblockctl` 控制 L1 TLB 的刷新行为，NEMU 同步支持该控制位（[#6928](https://github.com/OpenXiangShan/XiangShan/pull/6928)、[NEMU #1285](https://github.com/OpenXiangShan/NEMU/pull/1285)）
- 地址翻译 Bug 修复
  - 缓存无效页表项时忽略其全局位，避免在地址空间之间复用页故障项，并允许按 ASID 执行的 `sfence.vma` 清除旧故障（[#6698](https://github.com/OpenXiangShan/XiangShan/pull/6698)）
  - 在一级翻译命中时清除上次页表遍历遗留的状态，使越界客户物理地址能正确上报故障。二级遍历响应与匹配的访存请求同拍到达时，保留重复请求的等待状态（[#6898](https://github.com/OpenXiangShan/XiangShan/pull/6898)、[#7002](https://github.com/OpenXiangShan/XiangShan/pull/7002)）
  - 按一级页表遍历响应实际覆盖的页匹配等待请求，并在 L1 TLB 多路命中时清除全部冲突项，避免重叠回填反复触发重放（[#6973](https://github.com/OpenXiangShan/XiangShan/pull/6973)、[#6978](https://github.com/OpenXiangShan/XiangShan/pull/6978)）
  - 在取指或数据翻译长期收不到响应时，暂停向 L2 TLB 送入新请求，让在途请求先完成（[#7018](https://github.com/OpenXiangShan/XiangShan/pull/7018)）
- 访存流水线 Bug 修复
  - 修复跨 16 字节边界的 store 误用旧整行写和预取标记的问题，并将跨页 store 对第二页的转发保护保持到 StoreQueue 出队，避免后续 load 读到旧数据（[#6770](https://github.com/OpenXiangShan/XiangShan/pull/6770)、[#6822](https://github.com/OpenXiangShan/XiangShan/pull/6822)）
  - 在不可缓存 load 的写回路径上，V3 锁存等待写回的数据和错误标记，避免请求编号复用后被覆盖。发生重定向时，V2 取消已缓冲的不可缓存 load，避免错误路径写回（[#6773](https://github.com/OpenXiangShan/XiangShan/pull/6773)、[#6873](https://github.com/OpenXiangShan/XiangShan/pull/6873)）
  - 将发生客户页故障的 load 推迟到 ROB 队首再重放，并在标量与向量 store 争用地址通路时优先选择较老指令，避免等待客户物理地址的访存阻塞较老指令（[#6989](https://github.com/OpenXiangShan/XiangShan/pull/6989)、[#6992](https://github.com/OpenXiangShan/XiangShan/pull/6992)）
  - 按共享 DTLB 端口的实际使用者选择取消信号，并在原子指令接管端口时取消第一级流水中的预取，避免预取使用错误的物理地址（[#6970](https://github.com/OpenXiangShan/XiangShan/pull/6970)、[#6994](https://github.com/OpenXiangShan/XiangShan/pull/6994)）
  - 在单位步长向量访存触发断点时，将实际命中的字节地址写入 `mtval`，便于定位触发断点的元素（[#6882](https://github.com/OpenXiangShan/XiangShan/pull/6882)）
  - 为等待下游接收的缓存管理请求锁存通道号，避免昆明湖 V3 在背压时将请求发往错误通道。修正 V2 StoreQueue 的 MMIO 和缓存管理状态机，防止出错后重复发起请求，并在 `cbo.zero` 完成后恢复空闲状态（[#6907](https://github.com/OpenXiangShan/XiangShan/pull/6907)、[#6991](https://github.com/OpenXiangShan/XiangShan/pull/6991)）
- 缓存与一致性 Bug 修复
  - 从 L1 DCache 收到首拍回填数据起阻塞对同一块、同一别名的 probe，避免探测请求越过尚未完成的回填（[#6931](https://github.com/OpenXiangShan/XiangShan/pull/6931)）
  - 计算 CoupledL2 的 CHI 发送队列预留空间时保留加法进位，修复四个在途预留被计为零的问题（[XSCache #58](https://github.com/OpenXiangShan/XSCache/pull/58)）
- Oceanus L2 开发
  - 为 L2 命中增加默认关闭的快速返回选项，将目录 SRAM 的请求和响应分别寄存，并在仲裁前查询各请求的替换 CAM，缩短选择路径（[XSCache #56](https://github.com/OpenXiangShan/XSCache/pull/56)、[XSCache #67](https://github.com/OpenXiangShan/XSCache/pull/67)、[XSCache #73](https://github.com/OpenXiangShan/XSCache/pull/73)、[XSCache #74](https://github.com/OpenXiangShan/XSCache/pull/74)）
  - 为需要分配缓存路的替换操作加锁，等标签和元数据就绪后再释放命中路，并修复目录回写选错路和释放请求停滞的问题（[XSCache #59](https://github.com/OpenXiangShan/XSCache/pull/59)、[XSCache #60](https://github.com/OpenXiangShan/XSCache/pull/60)、[XSCache #79](https://github.com/OpenXiangShan/XSCache/pull/79)）
  - 将冲突的 snoop 延后到预填充状态提交后处理，并在处理读请求和 MakeUnique 时排除别名匹配的请求方，避免其自身副本被误置为无效（[XSCache #68](https://github.com/OpenXiangShan/XSCache/pull/68)、[XSCache #72](https://github.com/OpenXiangShan/XSCache/pull/72)）
  - 将 L2 数据 SRAM 的输入寄存并保持两个周期，使读响应的有效信号和数据在同一拍返回给对应的请求方（[XSCache #76](https://github.com/OpenXiangShan/XSCache/pull/76)）

### XSAI

- RTL 新特性
  - 支持将 CUTE 的 A、B 矩阵寄存器按普通、转置或整寄存器形式写回内存，并在 DiffTest 中跟踪 TR 写回。普通 A、B 加载可使用任一 TR 加载单元（[CUTE #55](https://github.com/OpenXiangShan/CUTE/pull/55)、[difftest #1044](https://github.com/OpenXiangShan/difftest/pull/1044)、[XSAI #177](https://github.com/OpenXiangShan/XSAI/pull/177)）
  - 支持 XSAICache 的 CHI 桥连接珠江互连的原生异步 socket（[XSAICache #18](https://github.com/OpenXiangShan/XSAICache/pull/18)）
- Bug 修复
  - 同步昆明湖 V2 的 bug-fix（[XSAI #176](https://github.com/OpenXiangShan/XSAI/pull/176)）
  - 为 CoupledL2 解耦 CHI 接口的出站请求、响应和数据补上本地节点 ID，使接收方能识别发送节点（[XSAICache #17](https://github.com/OpenXiangShan/XSAICache/pull/17)）
- 调试工具
  - 优化 CPU 参考模型的矩阵乘加校验，并行计算独立结果并复用已解码的浮点操作数，便于编译器向量化（[difftest #1038](https://github.com/OpenXiangShan/difftest/pull/1038)）
  - 将异步 CPU MMA 校验移入独立进程，通过共享线程池并行处理多个 DUT 核的请求，并按各核的请求顺序返回结果（[difftest #1050](https://github.com/OpenXiangShan/difftest/pull/1050)）
  - 减少矩阵 DiffTest 对软件 ROB 的扫描，在 DUT 完成 `mrelease` 或回放恢复后才检查释放顺序，有条目等待参考模型的控制事件时才扫描匹配项（[difftest #1047](https://github.com/OpenXiangShan/difftest/pull/1047)、[difftest #1049](https://github.com/OpenXiangShan/difftest/pull/1049)）
  - 在 NEMU 的共享参考模型中启用矩阵访存的整行拷贝和 AVX2 转置路径，加快矩阵 load/store 校验（[NEMU #1284](https://github.com/OpenXiangShan/NEMU/pull/1284)）
  - 在矩阵缓存测试分支接入 L2-only 测试顶层，由 CHI 从节点模型直接响应 L2 请求，支持在 VCS 中独立回放访存轨迹（[XSAICache #16](https://github.com/OpenXiangShan/XSAICache/pull/16)、[tl-test-new #105](https://github.com/OpenXiangShan/tl-test-new/pull/105)）
  - 为矩阵缓存 VCS 测试平台增加轨迹结束后的回读校验，覆盖缓存和 MMIO 访问过的所有地址，并在缓存行换出后再次核对数据（[tl-test-new #106](https://github.com/OpenXiangShan/tl-test-new/pull/106)）

### 基础设施

- 回归测试与仿真
  - 将 643 个 RISC-V 架构冒烟测试程序纳入 EMU 基础回归，按 29 个指令集扩展分组并行运行（[#6805](https://github.com/OpenXiangShan/XiangShan/pull/6805)）
  - 在夜间和每周性能回归中共用一次仿真器构建，保证同一轮的各项负载测量同一提交（[#6893](https://github.com/OpenXiangShan/XiangShan/pull/6893)）
  - 为 EMU 增加 `--stuck-check`，定期采样各核的指令退休数，定位时钟仍在前进但已无指令退休的仿真（[difftest #1043](https://github.com/OpenXiangShan/difftest/pull/1043)）
  - 按内存通道分别向 DiffTest 上报 DCache 回填，避免同拍回填因排队延迟到参考内存的后续 store 之后（[#6987](https://github.com/OpenXiangShan/XiangShan/pull/6987)）
  - 将 DiffTest 的镜像解压与 RAM 装载分开，支持从 gzip 或 zstd 压缩流装载 ELF 并检测镜像截断，昆明湖 V2 同步集成该改动（[difftest #1042](https://github.com/OpenXiangShan/difftest/pull/1042)、[#6966](https://github.com/OpenXiangShan/XiangShan/pull/6966)）
  - 在 FPGA DiffTest 的 FORK 模式达到指令数上限时，先完成已执行指令的剩余检查，再向宿主返回原始停止原因（[difftest #1037](https://github.com/OpenXiangShan/difftest/pull/1037)）
  - 将 FPGA DiffTest 的 FORK 模式参考检查点间隔默认设为 1 秒，并扩大共享 XDMA 包缓冲池，MinJie 同步更新该依赖（[difftest #1034](https://github.com/OpenXiangShan/difftest/pull/1034)、[minjie-playground #48](https://github.com/OpenXiangShan/minjie-playground/pull/48)）
  - 将 Rocket Chip、Utility 和 DiffTest 的默认构建切换到香山维护的 Chisel 7.16.0-xiangshan-1，保留使用上游 Chisel 的选项（[rocket-chip #47](https://github.com/OpenXiangShan/rocket-chip/pull/47)、[Utility #166](https://github.com/OpenXiangShan/Utility/pull/166)、[difftest #1045](https://github.com/OpenXiangShan/difftest/pull/1045)）
  - 修复 ChiselAIA 的 IMSIC 在背压下丢失中断的问题，多个中断文件共享仲裁，FIFO 满时保留待写入的 MSI，并将修复集成到昆明湖 V2（[ChiselAIA #55](https://github.com/OpenXiangShan/ChiselAIA/pull/55)、[#6933](https://github.com/OpenXiangShan/XiangShan/pull/6933)）
- NEMU 参考模型
  - 标量 load/store 跨页且第二页地址超出规范范围时，NEMU 上报第二页的起始地址，与 RTL 的故障地址对齐（[NEMU #1257](https://github.com/OpenXiangShan/NEMU/pull/1257)、[NEMU #1258](https://github.com/OpenXiangShan/NEMU/pull/1258)）
  - 按宿主、VS 和 G 级分别失效地址翻译缓存，并在翻译失效或直接陷入改变上下文后清除已译码指令块，确保重新取指使用当前映射和权限（[NEMU #1297](https://github.com/OpenXiangShan/NEMU/pull/1297)、[NEMU #1300](https://github.com/OpenXiangShan/NEMU/pull/1300)、[NEMU #1304](https://github.com/OpenXiangShan/NEMU/pull/1304)）
  - 缓存块操作命中 LR/SC 保留集时清除本地保留，避免后续条件存储错误成功（[NEMU #1295](https://github.com/OpenXiangShan/NEMU/pull/1295)）
  - 零长度的向量 gather、slide 和掩码逻辑指令成功执行后将 VS 标记为 Dirty，与硬件提交状态一致（[NEMU #1286](https://github.com/OpenXiangShan/NEMU/pull/1286)）
- GSIM 仿真器
  - 将 GSIM 的断言失败交给 DiffTest 处理，使 LightSSS 能在断言触发时唤醒子进程生成波形（[gsim #154](https://github.com/OpenXiangShan/gsim/pull/154)、[difftest #1035](https://github.com/OpenXiangShan/difftest/pull/1035)）
  - 在确定信号归属后收集 FST 波形字段，补全跨仿真节点的中间信号，并新增 `--trace-fst-max-width`，支持按总位宽过滤数组信号（[gsim #153](https://github.com/OpenXiangShan/gsim/pull/153)、[gsim #160](https://github.com/OpenXiangShan/gsim/pull/160)）
  - 修复动态数组下标中嵌套别名的替换问题，以及顶层向量 I/O 读写接口的代码生成问题（[gsim #157](https://github.com/OpenXiangShan/gsim/pull/157)、[gsim #162](https://github.com/OpenXiangShan/gsim/pull/162)）

### XS-GEM5

- 新特性探索
  - 在双线程 SpMT 模型中按线程划分访存队列、StoreBuffer 容量及 SQ 到 StoreBuffer 的每拍带宽，减少线程间的资源争用（[XS-GEM5 #1277](https://github.com/OpenXiangShan/GEM5/pull/1277)）
  - 在 Ideal KMH-V3 配置中支持 SMS 动态选择预取层级，根据各偏移的置信度和触发访问发往 L2 或 L3，置信度不足时跳过预取（[XS-GEM5 #1318](https://github.com/OpenXiangShan/GEM5/pull/1318)）
  - 为物理和虚拟 BOP 预取器增加师生学习机制，由学生预测器跨轮次保留有效偏移，覆盖率达标后使用这些偏移发起预取（[XS-GEM5 #1319](https://github.com/OpenXiangShan/GEM5/pull/1319)）
  - 使用取指块起始 PC 校验 PairTAGE 标签，限制第二个跳转块提前入队的距离，并在配对信息变化时清除旧置信度（[XS-GEM5 #1342](https://github.com/OpenXiangShan/GEM5/pull/1342)）
- 模型对齐与修复
  - 在两阶段翻译时让 L1 TLB 缓存客户虚拟地址到宿主物理地址的最终映射，将中间结果保留在 L2 和页表遍历器中，并按 KMH-V3 RTL 对齐 L2 页表缓存容量和每项保存的 PTE 数量（[XS-GEM5 #1310](https://github.com/OpenXiangShan/GEM5/pull/1310)、[XS-GEM5 #1323](https://github.com/OpenXiangShan/GEM5/pull/1323)）
  - 按 KMH-V3 RTL 对齐整数、浮点和 load 发射队列容量，并根据重命名后的操作数估算整数除法延迟，按结果可用时间提前唤醒依赖整数或浮点除法结果的指令（[XS-GEM5 #1312](https://github.com/OpenXiangShan/GEM5/pull/1312)、[XS-GEM5 #1324](https://github.com/OpenXiangShan/GEM5/pull/1324)、[XS-GEM5 #1327](https://github.com/OpenXiangShan/GEM5/pull/1327)）
  - 第三级快速训练使用 ITTAGE 或 RAS 最终选中的目标，后级预测顺序取指时也能纠正前级的跳转预测（[XS-GEM5 #1329](https://github.com/OpenXiangShan/GEM5/pull/1329)、[XS-GEM5 #1333](https://github.com/OpenXiangShan/GEM5/pull/1333)）
  - 从 MainBTB 组索引中排除 SRAM 选择位，修复每片 SRAM 只能使用一半组的问题（[XS-GEM5 #1344](https://github.com/OpenXiangShan/GEM5/pull/1344)）
  - 在本地 L1 写入生效时通知同核其他 SMT 线程，使其能检测同址 load 的顺序违规并重放（[XS-GEM5 #1346](https://github.com/OpenXiangShan/GEM5/pull/1346)）
- 调试工具
  - 新增指令分派分析工具 DIP，将错误路径和重新取指占用的分派槽归因到触发重定向的指令，可与提交侧分析工具 TEA 一同生成 CSV 和 Markdown 报告。单线程经典内存配置默认启用 DIP（[XS-GEM5 #1311](https://github.com/OpenXiangShan/GEM5/pull/1311)、[XS-GEM5 #1335](https://github.com/OpenXiangShan/GEM5/pull/1335)）
  - 完善经典内存模型的多核差分检查，按字节区分标量 load 的缓存返回与本核 store 转发，并对照参考模型检查原子操作的目标寄存器及写入后的内存（[XS-GEM5 #1356](https://github.com/OpenXiangShan/GEM5/pull/1356)、[XS-GEM5 #1357](https://github.com/OpenXiangShan/GEM5/pull/1357)）
  - 对齐模拟器与差分参考模型的中断来源和目标特权级，确保两者进入相同的陷阱处理程序（[XS-GEM5 #1307](https://github.com/OpenXiangShan/GEM5/pull/1307)）
- 基础设施
  - 分布式性能回归的 SSH 连接关闭时终止对应的远端仿真进程组，避免已取消的任务继续占用计算节点（[XS-GEM5 #1360](https://github.com/OpenXiangShan/GEM5/pull/1360)）

## 性能评估

处理器及 SoC 配置

| 参数      | 选项       |
| --------- | ---------- |
| commit | `8b15f0652` |
| 日期 | 2026/11/13 |
| L1 ICache | 64 KB |
| L1 DCache | 64 KB |
| L2 Cache | 2 MB |
| L3 Cache | 32 MB |
| 访存单元 | 3ld2st |
| 总线协议 | CHI E.b |
| 内存配置 | DDR4-3200 |

SPEC CPU2006 分数

| SPECint 2006 @ 3 GHz | GCC16  | XSCC   | SPECfp 2006 @ 3 GHz | GCC16  | XSCC   |
| :------------------- | :----: | :----: | :------------------ | :----: | :----: |
| 400.perlbench        | 57.95  | 61.55  | 410.bwaves          | 146.16 | 148.79 |
| 401.bzip2            | 31.13  | 32.48  | 416.gamess          | 61.92  | 57.83  |
| 403.gcc              | 64.38  | 62.64  | 433.milc            | 77.20  | 75.76  |
| 429.mcf              | 84.47  | 80.40  | 434.zeusmp          | 78.98  | 78.42  |
| 445.gobmk            | 47.24  | 45.42  | 435.gromacs         | 43.41  | 42.68  |
| 456.hmmer            | 55.27  | 67.38  | 436.cactusADM       | 89.30  | 95.89  |
| 458.sjeng            | 45.59  | 46.90  | 437.leslie3d        | 68.40  | 67.34  |
| 462.libquantum       | 167.97 | 382.01 | 444.namd            | 47.71  | 48.64  |
| 464.h264ref          | 70.29  | 74.06  | 447.dealII          | 86.24  | 168.68 |
| 471.omnetpp          | 59.25  | 60.66  | 450.soplex          | 70.56  | 81.47  |
| 473.astar            | 35.66  | 34.26  | 453.povray          | 84.37  | 72.64  |
| 483.xalancbmk        | 92.74  | 138.14 | 454.calculix        | 48.09  | 48.13  |
| GEOMEAN              | 61.09  | 69.05  | 459.GemsFDTD        | 82.97  | 83.30  |
|                      |        |        | 465.tonto           | 79.58  | 64.84  |
|                      |        |        | 470.lbm             | 128.13 | 151.49 |
|                      |        |        | 481.wrf             | 62.53  | 61.24  |
|                      |        |        | 482.sphinx3         | 68.88  | 100.23 |
|                      |        |        | GEOMEAN             | 74.21  | 78.56  |

编译配置

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

本栏使用 SimPoint 采样的程序片段和香山自定义格式的检查点估算分数。完整 SPEC CPU2006 评测和芯片实测的结果可能与采样估计有差异。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：李衍君、曾锦鸿、杨泽辰、张韩乐、游昆霖、李昕、吴天择、燕翼鸣
