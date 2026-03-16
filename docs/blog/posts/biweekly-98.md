---
slug: biweekly-98
date: 2026-03-16
categories:
  - Biweekly
---

# 【香山双周报 98】20260316 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 98 期双周报。

关于香山近期开发进展，~~香山的同学们度过了一个快乐的春节~~。不多的细节请见近期进展一节。~~但是都不白来~~，我们还为大家准备了一个香山开发中的小花絮。

<!-- more -->

## 与 verilator 搏斗的一周
在香山的开发过程中，仿真器是非常重要的基础设施。为了贯彻开源理念，在香山的开发与一部分验证工作中，我们一直使用的是开源仿真器 verilator。即使现在有了属于香山自己的仿真器 gsim，verilator 在功能验证方面仍然具有不可替代的作用，~~因为 gsim 现在还不支持打波形~~。此外，在 gsim 的开发过程中，verilator 一直作为重要的参考平台，帮助我们验证 gsim 的正确性和性能。

在平平无奇的一天，L 同学突然被抓去背了一个锅，前端 FTQ 模块触发了一个 assertion。这本来不是什么大问题，~~如果这个 assert 不是在已经冻结交付的 master 上触发的话~~。L 同学愉快地打开了出错波形，看了半天越看越觉得不对，因为 `commitStateQueueReg_42_5` 这个信号奇迹般地没有发生变化，这导致 FTQ 对提交状态的判断出错。

![](./figs/verilator-1.png)

L 同学觉得一定是锅背太多了导致出现了幻觉。他拉上 X 同学和他一起人肉执行了 verilog 代码。然而不幸的是 X 同学也和他出现了一样的幻觉，似乎按照 verilog 代码的逻辑，`commitStateQueueReg_42_5` 应当在虚线后由 `1` 变为 `2`。

这时 L 和 X 判断一定是 verilator 的 bug，但另一位 X 总表示即使是 verilator 的 bug 也得再确定一下，~~不然怎么让人相信迄今为止的验证是正确的呢~~。

由于香山设置了 `--trace` 选项，verilator 不会将 `_GEN_350234` 这样的以下划线开头的信号打印在波形中。L 同学决定先将 FTQ 模块中所有的 `_GEN_350234` 这样的信号替换成 `GEN_350234`，这样就能在波形中看到他们了。当他再次生成波形后，他发现 `commitStateQueueReg_42_5` 再次奇迹般地发生了变化，在虚线处从 `1` 变成了 `2`。

![](./figs/verilator-2.png)

L 同学有点麻。他将 `--trace` 选项改为 `--trace-underscore`，在不改变代码的情况下，将所有的下划线信号打印在波形中，发现 `commitStateQueueReg_42_5` 同样正确地变化了。

![](./figs/verilator-3.png)

L 同学彻底麻了，他不想去看 verilator 生成的 C++ 代码，并且觉得这个锅不应当继续由他背。他将这个问题扔给了 verilator 社区，并且更新了 verilator 版本。这个问题确实消失了，然而到底是真的消失了，还是悄悄隐藏到了更深处，就等到下次遇到再说吧，L 只觉得盯着波形看了一周眼睛要瞎了。

## 近期进展

### 前端

因春节放假，进展较少。部分进展已经在 96 期双周报提到，本期对状态变化的部分进行补充介绍。

- 上期提到，目前已合入
  - Bug 修复
    - 修复 SC 训练条件未判断 MBTB 是否命中，导致用无效数据训练的问题（[#5601](https://github.com/OpenXiangShan/XiangShan/pull/5601)）
  - 时序/面积优化
    - 调整 BPU s2 流水级，MBTB 部分信息提前给到 TAGE（[#5614](https://github.com/OpenXiangShan/XiangShan/pull/5614)）
- 新合入
  - Bug 修复
    - 修改 BPU s1 级预测生成逻辑，只要 utage 命中就全部使用 utage 修正后的预测（[#5611](https://github.com/OpenXiangShan/XiangShan/pull/5611)）
- 进行中
  - RTL 新特性
    - 支持 UTAGE 以分支粒度进行预测（[#5513](https://github.com/OpenXiangShan/XiangShan/pull/5513)）
    - 支持设置 SC 阈值范围（[#5632](https://github.com/OpenXiangShan/XiangShan/pull/5632)）
  - Bug 修复
    - 修复 MBTB 中 baseTable 在正确预测时饱和计数器未更新的问题（[#5602](https://github.com/OpenXiangShan/XiangShan/pull/5602)）
    - 修复历史信息寄存器在遇到 s3 override 的处理逻辑（[#5625](https://github.com/OpenXiangShan/XiangShan/pull/5625)）
  - 时序/面积优化
    - 调整 MBTB 位置比较逻辑流水级（[#5603](https://github.com/OpenXiangShan/XiangShan/pull/5603)）
    - 调整 UTAGE 历史信息流水级（[#5517](https://github.com/OpenXiangShan/XiangShan/pull/5517)）
    - 修复 SC 内部部分串行逻辑（暂未 PR）
    - 调整 ICache parity 校验逻辑流水级（暂未 PR）
    - 进一步评估和修复持续进行中
  - 代码质量
    - 修复 MBTB 编译期 warning（[#5543](https://github.com/OpenXiangShan/XiangShan/pull/5543)）

从下期开始将回归仅介绍已合入 PR 的方式。

### 后端

- RTL 新特性
  - 当 ldu 不能接收 uop 时为其提供缓存（[#5604](https://github.com/OpenXiangShan/XiangShan/pull/5604)）
- 代码质量
  - 拆分 Og0InUop 和 Og1Uop 用于后续时序优化（[#5575](https://github.com/OpenXiangShan/XiangShan/pull/5575)）
  - 将 fusion 指令的 imm32 生成从 rename 移动到 fusionDecoder（[#5606](https://github.com/OpenXiangShan/XiangShan/pull/5606)）
- 时序修复
  - 将部分信号从 IQPayload 移动到 og1Payload（[#5595](https://github.com/OpenXiangShan/XiangShan/pull/5595)）

### 访存与缓存

- RTL 新特性
  - MMU、LoadUnit、StoreQueue、L2 等模块重构与测试持续推进中
- 代码重构
  - （V2）对向量 store 的 difftest 进行了重构（[#5587](https://github.com/OpenXiangShan/XiangShan/pull/5587)）
- 调试工具
  - 开发用于新版 L2 Cache 的验证工具 CHI Test。持续推进中

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 316946d28  |
| 日期      | 2026/02/11 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存延迟  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | GCC12  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  | GCC12  |
| :------------------ | :----: | :----: | :----: | :----------------- | :----: | :----: | :----: |
| 400.perlbench       | 47.47  | 46.45  | 43.61  | 410.bwaves         | 85.75  | 90.56  | 73.28  |
| 401.bzip2           | 27.12  | 27.83  | 27.51  | 416.gamess         | 56.30  | 52.50  | 54.94  |
| 403.gcc             | 50.86  | 37.33  | 51.30  | 433.milc           | 64.92  | 63.73  | 49.28  |
| 429.mcf             | 59.70  | 54.36  | 60.69  | 434.zeusmp         | 69.45  | 63.50  | 60.37  |
| 445.gobmk           | 35.66  | 36.59  | 37.44  | 435.gromacs        | 36.47  | 34.17  | 38.56  |
| 456.hmmer           | 53.69  | 63.60  | 43.52  | 436.cactusADM      | 75.62  | 86.54  | 53.69  |
| 458.sjeng           | 35.56  | 36.40  | 34.82  | 437.leslie3d       | 56.60  | 56.81  | 54.45  |
| 462.libquantum      | 135.55 | 285.26 | 133.21 | 444.namd           | 42.30  | 44.19  | 37.42  |
| 464.h264ref         | 62.47  | 71.27  | 63.01  | 447.dealII         | 63.89  | 67.16  | 64.28  |
| 471.omnetpp         | 40.89  | 39.25  | 43.04  | 450.soplex         | 49.21  | 57.92  | 53.33  |
| 473.astar           | 31.75  | 30.28  | 30.34  | 453.povray         | 72.35  | 66.59  | 61.60  |
| 483.xalancbmk       | 74.63  | 84.92  | 80.96  | 454.Calculix       | 44.24  | 39.20  | 19.43  |
| GEOMEAN             | 49.54  | 52.67  | 48.92  | 459.GemsFDTD       | 64.85  | 64.68  | 46.68  |
|                     |        |        |        | 465.tonto          | 51.73  | 34.73  | 36.69  |
|                     |        |        |        | 470.lbm            | 126.78 | 132.83 | 104.98 |
|                     |        |        |        | 481.wrf            | 55.26  | 41.58  | 48.68  |
|                     |        |        |        | 482.sphinx3        | 58.58  | 61.17  | 55.05  |
|                     |        |        |        | GEOMEAN            | 60.58  | 58.50  | 50.80  |

编译参数如下所示：

| 参数             | GCC12    | GCC15       | XSCC                |
| ---------------- | -------- | ----------- | ------------------- |
| 编译器           | gcc12    | gcc15       | xscc                |
| 编译优化         | O3       | O3          | O3                  |
| 内存库           | jemalloc | jemalloc    | jemalloc            |
| -march           | RV64GCB  | RV64GCB     | RV64GCB             |
| -ffp-contraction | fast     | fast        | fast                |
| 链接优化         | -        | -flto       | -flto               |
| 浮点优化         | -        | -ffast-math | -ffast-math         |
| -mcpu            | -        | -           | xiangshan-kunminghu |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
