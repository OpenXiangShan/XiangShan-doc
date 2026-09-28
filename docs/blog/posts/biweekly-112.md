---
slug: biweekly-112
date: 2026-09-30
categories:
  - Biweekly
---

# 【香山双周报 112】20260930 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 112 期双周报。

<!-- more -->

## 近期进展

### 前端

### 后端

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

### XS-GEM5

- 模拟器对齐
  - 向量访存的写回增加 3 周期延迟 ([XS-GEM5 #1155](https://github.com/OpenXiangShan/GEM5/pull/1155))
  - 对齐 pre-decode ([XS-GEM5 #1150](https://github.com/OpenXiangShan/GEM5/pull/1150))
  - vset 指令 ibuffer 旁路行为对齐 ([XS-GEM5 #1135](https://github.com/OpenXiangShan/GEM5/pull/1135))
  - cache hit under block 支持 ([XS-GEM5 #1164](https://github.com/OpenXiangShan/GEM5/pull/1164))
  - 浮点除法延迟对齐 ([XS-GEM5 #1167](https://github.com/OpenXiangShan/GEM5/pull/1167))
  - 向量 IQ 配置对齐 ([XS-GEM5 #1179](https://github.com/OpenXiangShan/GEM5/pull/1179))
- 新特性探索
  - 新指针预取算法 LLDP ([XS-GEM5 #1158](https://github.com/OpenXiangShan/GEM5/pull/1158))
  - tage 预测从 s3->s2 ([XS-GEM5 #1165](https://github.com/OpenXiangShan/GEM5/pull/1165))
  - safe-iq watermark ([XS-GEM5 #1175](https://github.com/OpenXiangShan/GEM5/pull/1175))
- 基础设施
  - cbo.zero 指令的实现 ([XS-GEM5 #1153](https://github.com/OpenXiangShan/GEM5/pull/1153))
  - se 模式的改进与文档完善 ([XS-GEM5 #1154](https://github.com/OpenXiangShan/GEM5/pull/1154))
  - 支持更多 se 模式的 workload ([XS-GEM5 #1156](https://github.com/OpenXiangShan/GEM5/pull/1156))

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
