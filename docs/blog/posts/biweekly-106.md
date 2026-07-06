---
slug: biweekly-106
date: 2026-07-06
categories:
  - Biweekly
---

# 【香山双周报 106】20260706 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 106 期双周报。

RISC-V 欧洲峰会圆满落幕！中国科学院计算技术研究所副所长、北京开源芯片研究院首席科学家包云岗研究员与大家分享了他的[参会感受](https://mp.weixin.qq.com/s/sqesKwSbE1oDy3cL0ei1ZQ)，以及对 RISC-V 发展前景的展望，欢迎大家与我们交流讨论！

关于香山近期开发进展，前端继续优化时序；后端和访存修复了一些功能 bug，同时优化了 DCache 与 Sbuffer 性能；XSAI 支持了 BF16 扩展，HBL2 实现了 TL-TL 与 TL-CHI 的 PutFullData。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 支持 IFU 预译码训练 BPU（[#6112](https://github.com/OpenXiangShan/XiangShan/pull/6112)）
  - 初步支持 2-fetch（单周期处理两个取指块）（[#5996](https://github.com/OpenXiangShan/XiangShan/pull/5996)）
- Bug 修复
  - 修复 FTQ trainCache 冲刷条件（[#6147](https://github.com/OpenXiangShan/XiangShan/pull/6147)）
  - 修复 IFU UncacheUnit 处理 PBMT.IO 区域的取指时，未等待指令提交，导致推测性取指的问题（[#6144](https://github.com/OpenXiangShan/XiangShan/pull/6144)）

### 后端

- Bug 修复
  - （V2）修复 M 态注入 SEI 时的优先级编号，按 AIA 规范将其设为 S 级优先级 256（[#6010](https://github.com/OpenXiangShan/XiangShan/pull/6010)）
  - （V2）修复 `mret` 进入 VU 模式时 `vsstatus.SDT` 未被清除的问题（[#6074](https://github.com/OpenXiangShan/XiangShan/pull/6074)）
  - （V2/V3）修复 `vstopi` Candidate3 使能条件（[#6030](https://github.com/OpenXiangShan/XiangShan/pull/6030)、[#6031](https://github.com/OpenXiangShan/XiangShan/pull/6031)）
  - （V2）修复 Candidate3 与 Candidate5 同时使能时的 iid 选择（[#6086](https://github.com/OpenXiangShan/XiangShan/pull/6086)）
  - （V2）修复 `fence` 指令 opcode 匹配（[#6096](https://github.com/OpenXiangShan/XiangShan/pull/6096)）
  - （V2）修复 ROB 中 `commit_w` 的 X-state 传播（[#6070](https://github.com/OpenXiangShan/XiangShan/pull/6070)）
  - （V2）修复 IGPF 过程中 `mtval2` 生成错误的问题（[#6058](https://github.com/OpenXiangShan/XiangShan/pull/6058)）
  - （V2）修复 `MNret` 对 `mnstatus.MNPP/MNPV` 的处理（[#6075](https://github.com/OpenXiangShan/XiangShan/pull/6075)）
  - （V2）按陷入类型约束 VS `hvictl` 中断原因的生成，并完善 WFI 唤醒相关的中断 pending 判断（[#6067](https://github.com/OpenXiangShan/XiangShan/pull/6067)）
  - （V2）修复 `trapInstInfo` 暂存逻辑，避免 flush 与更老 CSR trap 同周期到达时遗漏陷入指令信息（[#6084](https://github.com/OpenXiangShan/XiangShan/pull/6084)）
  - （V2）将 HLV/HLVX/HSV 访存异常标记为虚拟访存陷入，以正确更新 `htval`/`mtval`（[#6071](https://github.com/OpenXiangShan/XiangShan/pull/6071)）
  - （V2）修复 PMP/PMA 在 `CSRRS`/`CSRRC` 读-改-写时的基值选择（[#6051](https://github.com/OpenXiangShan/XiangShan/pull/6051)）

### 访存与缓存

- Bug 修复
  - 修复了 cbo 执行早于指令提交的问题（[#6081](https://github.com/OpenXiangShan/XiangShan/pull/6081)）
  - 修复了 loadUnit 的性能计数器（[#5939](https://github.com/OpenXiangShan/XiangShan/pull/5939)）
  - 添加指针越界断言（[#5795](https://github.com/OpenXiangShan/XiangShan/pull/5795)）
- 性能优化
  - 实现了 DCache MissQueue 的并行入队，同一周期允许最多 4 个 miss_req（[#5887](https://github.com/OpenXiangShan/XiangShan/pull/5887)）
  - 优化了 Sbuffer 的请求合并逻辑（[#6117](https://github.com/OpenXiangShan/XiangShan/pull/6117)）
- 时序优化
  - 修复了 Memblock 的时序（[#5963](https://github.com/OpenXiangShan/XiangShan/pull/5963)）

### XSAI

- Bug 修复
  - 修复了 MMA 指令在 mtilen 过大时漏报非法指令异常的错误（[XSAI #79](https://github.com/OpenXiangShan/XSAI/pull/79)）
- RTL 新特性
  - 支持细粒度矩阵访存以及 8bit 元素的转置访存（[CUTE #19](https://github.com/OpenXiangShan/CUTE/pull/19)）
  - 指令扩展更新至 XSAI proposal 12（[XSAI #68](https://github.com/OpenXiangShan/XSAI/pull/68)）
- 代码质量
  - 重构 CUTE FPE 代码，拆分文件，清除符号链接（[XSAI #81](https://github.com/OpenXiangShan/XSAI/pull/81)）
- 调试工具
  - 将 DiffTest 中的 C++17 写法回退到 C++11，以增强兼容性（[XSAI #75](https://github.com/OpenXiangShan/XSAI/pull/75)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 8c4daa743  |
| 日期      | 2026/06/18 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 2MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 50.55  | 49.66  | 410.bwaves         | 104.21 | 95.87  |
| 401.bzip2           | 28.61  | 29.56  | 416.gamess         | 57.76  | 54.82  |
| 403.gcc             | 57.06  | 40.22  | 433.milc           | 69.94  | 68.81  |
| 429.mcf             | 71.47  | 62.54  | 434.zeusmp         | 74.95  | 67.02  |
| 445.gobmk           | 39.90  | 40.89  | 435.gromacs        | 37.90  | 34.82  |
| 456.hmmer           | 54.84  | 65.42  | 436.cactusADM      | 80.64  | 91.86  |
| 458.sjeng           | 39.36  | 40.48  | 437.leslie3d       | 59.90  | 59.70  |
| 462.libquantum      | 141.89 | 312.28 | 444.namd           | 43.55  | 45.46  |
| 464.h264ref         | 66.56  | 72.86  | 447.dealII         | 69.14  | 74.72  |
| 471.omnetpp         | 43.55  | 42.80  | 450.soplex         | 58.74  | 69.98  |
| 473.astar           | 32.92  | 32.64  | 453.povray         | 76.71  | 70.42  |
| 483.xalancbmk       | 81.13  | 92.62  | 454.Calculix       | 44.54  | 40.60  |
| GEOMEAN             | 53.57  | 57.00  | 459.GemsFDTD       | 69.93  | 70.40  |
|                     |        |        | 465.tonto          | 54.49  | 37.22  |
|                     |        |        | 470.lbm            | 128.45 | 148.55 |
|                     |        |        | 481.wrf            | 56.39  | 42.33  |
|                     |        |        | 482.sphinx3        | 60.94  | 63.63  |
|                     |        |        | GEOMEAN            | 64.55  | 62.40  |

编译参数如下所示：

| 参数             | GCC15       | XSCC                |
| ---------------- | ----------- | ------------------- |
| 编译器           | gcc15       | xscc                |
| 编译优化         | O3          | O3                  |
| 内存库           | jemalloc    | jemalloc            |
| -march           | RV64GCB     | RV64GCB             |
| -ffp-contraction | fast        | fast                |
| 链接优化         | -flto       | -flto               |
| 浮点优化         | -ffast-math | -ffast-math         |
| -mcpu            | -           | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://docs.xiangshan.cc/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、孙际儒、李衍君
