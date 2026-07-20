---
slug: biweekly-107
date: 2026-07-20
categories:
  - Biweekly
---

# 【香山双周报 107】20260720 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 107 期双周报。

ISCA 2026 香山 tutorial ~~不那么~~顺利举办！虽然一些同学因为签证原因没能现场报告，但我们紧急召集了替补，最终保证了 tutorial 高质量完成。特别感谢每一位关注香山发展的伙伴们！

关于香山近期开发进展，前端支持了 2-fetch 特性；访存优化了 DCache、Sbuffer 和预取器；XSAI 支持了新的矩阵访存模式，同时更新了指令扩展。

<!-- more -->

## Tutorial 与会议花絮

- 合影镇楼。只有左一的幸运儿在会议开始前 2 天及时拿到了签证，其他老师与同学用的都是已有的签证
  ![合影](./figs/biweekly-106/group.jpg)
- XSAI 首次在 tutorial 中亮相，吸引了广泛关注
  ![XSAI 报告](./figs/biweekly-106/xsai.jpg)
  ![交流讨论](./figs/biweekly-106/qa.jpg)
- 万众一芯论文报告
  ![万众一芯论文](./figs/biweekly-106/uc.jpg)

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
  - （V2）修复 PMP bug：非 dmode 无法访问调试内存（[#6095](https://github.com/OpenXiangShan/XiangShan/pull/6095)）

### 访存与缓存

- RTL 新特性
  - DCache 的 data SRAM 拆分为 32x2B（[#6118](https://github.com/OpenXiangShan/XiangShan/pull/6118)）
  - 通过哈希函数优化了 DCache 的寻址（[#6166](https://github.com/OpenXiangShan/XiangShan/pull/6166)）
- Bug 修复
  - 修复了 CoupledL2 drrip 替换算法中 set dueling 逻辑错误的问题（[XSCache #20](https://github.com/OpenXiangShan/XSCache/pull/20)）
- 性能优化
  - 优化了 Sbuffer 的请求合并逻辑（[#6117](https://github.com/OpenXiangShan/XiangShan/pull/6117)）
  - 优化了预取器的训练（[#5544](https://github.com/OpenXiangShan/XiangShan/pull/5544)，[XSCache #18](https://github.com/OpenXiangShan/XSCache/pull/18)）
  - 根据 CoupledL2 MSHR 的压力对预取请求进行限流（[XSCache #21](https://github.com/OpenXiangShan/XSCache/pull/21)）
- 时序优化
  - 将 l1 预取器中 sent_vec 的更新推迟到 pf fire（[#6102](https://github.com/OpenXiangShan/XiangShan/pull/6102)）
  - 在 loadQueueRAW 中使用年龄矩阵选取最老的项（[#6120](https://github.com/OpenXiangShan/XiangShan/pull/6120)）
- 代码质量
  - 将预取器相关的参数化配置移动到 Parameter.scala（[#5382](https://github.com/OpenXiangShan/XiangShan/pull/5382)）

### XSAI

- Bug 修复
  - 修复了 load/store whole C 指令的控制信号（[XSAI #86](https://github.com/OpenXiangShan/XSAI/pull/86)）
- RTL 新特性
  - 可配置的 CUTE 多通道访存（[XSAI #83](https://github.com/OpenXiangShan/XSAI/pull/83)）
  - 缓存系统使用 XSAICache 仓库替代原有的 coupledL2/huancun/openLLC（[XSAI #85](https://github.com/OpenXiangShan/XSAI/pull/85)）
- 代码质量
  - 对近期 CUTE 新增的调试输出添加控制开关（[CUTE #24](https://github.com/OpenXiangShan/CUTE/pull/24)、[CUTE #27](https://github.com/OpenXiangShan/CUTE/pull/27)）
- 调试工具
  - uop 的生命周期 trace 分析（[XSAI #84](https://github.com/OpenXiangShan/XSAI/pull/84)）

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 59ef4ea7d  |
| 日期      | 2026/07/03 |
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
| 400.perlbench       | 51.19  | 50.90  | 410.bwaves         | 116.08 | 104.81 |
| 401.bzip2           | 29.85  | 30.51  | 416.gamess         | 58.05  | 55.30  |
| 403.gcc             | 56.10  | 40.67  | 433.milc           | 70.32  | 69.31  |
| 429.mcf             | 70.05  | 62.69  | 434.zeusmp         | 77.83  | 67.38  |
| 445.gobmk           | 40.11  | 41.89  | 435.gromacs        | 38.20  | 34.94  |
| 456.hmmer           | 55.33  | 67.72  | 436.cactusADM      | 80.45  | 92.49  |
| 458.sjeng           | 40.66  | 41.54  | 437.leslie3d       | 60.27  | 60.78  |
| 462.libquantum      | 138.14 | 307.82 | 444.namd           | 43.31  | 45.56  |
| 464.h264ref         | 70.11  | 75.34  | 447.dealII         | 74.19  | 74.80  |
| 471.omnetpp         | 43.74  | 43.17  | 450.soplex         | 59.17  | 71.65  |
| 473.astar           | 33.73  | 33.05  | 453.povray         | 76.48  | 69.48  |
| 483.xalancbmk       | 83.35  | 92.95  | 454.Calculix       | 42.84  | 40.82  |
| GEOMEAN             | 54.22  | 57.95  | 459.GemsFDTD       | 68.28  | 65.83  |
|                     |        |        | 465.tonto          | 53.95  | 37.31  |
|                     |        |        | 470.lbm            | 128.22 | 146.35 |
|                     |        |        | 481.wrf            | 61.43  | 44.92  |
|                     |        |        | 482.sphinx3        | 61.15  | 63.82  |
|                     |        |        | GEOMEAN            | 65.52  | 62.92  |

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
