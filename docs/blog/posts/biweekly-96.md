---
slug: biweekly-96
date: 2026-02-16
categories:
  - Biweekly
---

# 【香山双周报 96】20260216 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 96 期双周报。

香山团队的高性能 DDR4 内存控制器 IP 白杨正式发布了！如果还没有看过，欢迎大家阅读我们的[白杨发布文章](https://mp.weixin.qq.com/s/ovHD6oHDHgMaVwybmnk_lw/)了解更多细节。在这里，我们与大家独家分享一个小故事。香山于 1 月 31 日在 HPCA 2026 上作 tutorial，其中有涉及到白杨的介绍。演讲的前一天晚上，白杨还在为开源作最后的准备，在第二天 tutorial 开始前才将仓库转为 public，~~果然 DDL 是第一生产力~~。

在上周，我们引入了新的 GCC15 和 XSCC 编译器。这两个编译器相比现有的 GCC12 有着 10% 以上的性能提升，现在香山的 SPEC CPU2006 性能已经达到了 18.5 分/GHz。这一期双周报中，我们为不同编译器进行了对比分析。在之后的开发中，我们将逐渐切换到 GCC15 和 XSCC 编译器，同时更加注重编译器和硬件的协同优化。不同编译器的具体分数仍然在性能评估一节，欢迎大家持续关注！

关于香山近期开发进展，前端方面，MBTB 引入了 LRU 替换算法，并使用 TAGE-SC 的精确预测结果进行更新，以提升分支预测的准确率。后端方面，添加了 I2F 功能单元以支持 FMV 和 FCVT 的 i2f 类型指令，并对整数 IQ 添加 og1Payload 以优化选择时序。访存与缓存方面，Sbuffer 中的超时判断逻辑得到了修复，并通过 csr 中的 SMBLOCKCTL 配置超时阈值。更多细节请见近期进展一节。

<!-- more -->

## 编译优化

一直以来，双周报中性能评估采用的都是使用 GCC12 编译的祖传切片。这些切片对于性能相对较低的昆明湖 V2 时代已经足够了，但随着昆明湖 V3 性能的不断迭代和编译技术的发展，原有的切片已经无法充分展现香山的性能潜力。在上周，我们使用 GCC15 和 XSCC 两个编译器对 SPEC CPU2006 进行了重新编译，并对比了不同编译器和优化选项下的性能表现。结果如下图所示：

![编译优化](./figs/complier-optimization.png)

可以看到，仅仅是切换编译器，就能在总分上提高约 12%。其中，GCC15 在打开 -ffast-math 这一优化选项后，对浮点测试程序的提升更是能达到接近 20%。而对于 libquantum 子项，XSCC 可以实现惊人的约 110% 的提升，~~不愧是刷分专用子项~~。

还有一个很有意思的现象，XSCC 在 GCC 这个子项上有约 20% 的性能倒退。XSCC 是基于 LLVM 的编译器，~~LLVM 不擅长优化 GCC 听起来意外地合理啊~~。

## Tutorial @ HPCA 2026

香山在 HPCA 2026 上成功举办 Tutorial！我们非常高兴能与大家在悉尼相见，感谢每一位参会的朋友和关心香山发展的伙伴们！欢迎大家访问 <https://tutorial.xiangshan.cc/hpca26/> 回顾本次 tutorial 的内容、获取 slides。

![合影镇楼](./figs/hpca2026-tutorial/group.jpg)

我们持续根据举办效果和大家的反馈对 tutorial 内容进行优化，希望在给新朋友们提供更清晰、全面和深度的介绍的同时，也能给老朋友们带来新的收获。本次 tutorial 的主要改进在于：

- 分享了最新的正在开发中的昆明湖-V3 微架构的设计哲学、观察和实现细节。
- 增加了对敏捷开发工具链的系统介绍和理念分享。
- 很荣幸地邀请到了我们的合作伙伴关于 XSCC 和白杨内存控制器的介绍：
  - XSCC：针对 RISC-V 优化的高性能编译器；

    ![XSCC 做现场汇报](./figs/hpca2026-tutorial/xscc.jpg)
  - 白杨内存控制器：高性能开源内存控制器 IP。

    很遗憾的是，原定主讲人因签证问题没能来到现场，转而由香山团队成员代替介绍。我们会持续沟通，期待在下次 tutorial 上邀请到白杨团队的同学来进行更深入的介绍！
- 持续对 bootcamp 上手环节进行更新，欢迎大家使用 <https://github.com/OpenXiangShan/bootcamp> 仓库提供的 docker 环境和预编译 assets 进行本地体验！

![议程](./figs/hpca2026-tutorial/agenda.jpg)

在现场的茶歇时间中，我们与来自世界各地的优秀学者进行了深入的交流。我们非常珍惜与大家面对面交流的机会，这一方面能让大家更好地了解香山微架构的设计和敏捷工具链的使用，让香山更好地成为学术研究和工业应用的基石；另一方面也能让我们更好地了解大家的反馈和创新想法，持续改进我们的设计和工具链。感谢每一位参与交流的朋友们！也欢迎未能到场的朋友们通过 <all@xiangshan.cc> 邮件列表、Github Issues、文末所列的技术讨论 QQ 群等渠道与我们交流。

![茶歇交流](./figs/hpca2026-tutorial/chat.jpg)

另外，香山的下一场 tutorial 将于 6 月下旬在美国举办的 [ISCA 2026](https://iscaconf.org/isca2026/) 会议上进行，期待与大家再次相见！

## 近期进展

### 前端

前端组近两周由于多位组员参加 HPCA 2026 及春节放假，暂无新合入主线的 PR，正在进行/等待 review 的进展包括：

- Bug 修复
  - 修复 SC 训练条件未判断 MBTB 是否命中，导致用无效数据训练的问题（[#5601](https://github.com/OpenXiangShan/XiangShan/pull/5601)）
  - 修复 MBTB 中 baseTable 在正确预测时饱和计数器未更新的问题（[#5602](https://github.com/OpenXiangShan/XiangShan/pull/5602)）
- 时序/面积优化
  - 在 V3 前端的前期开发中，主要以 BPU 重写为 region-BTB 结构的功能实现和性能调优为主。近一个月功能逐渐稳定，故进行了密集的时序评估工作。~~不出意料地大暴死了，什么叫逻辑级数直奔3位数。~~问题主要集中在流水级划分未仔细考虑、使用不合适的 Scala 魔法进行快速实现等。针对这些，我们进行了多轮分析和修复。前两次双周报已经介绍过一些 MBTB、TAGE、ICache 等模块的修复。近两周仍在继续的工作有：
    - 调整 BPU s2 流水级，MBTB 部分信息提前给到 TAGE（[#5614](https://github.com/OpenXiangShan/XiangShan/pull/5614)）
    - 调整 MBTB 位置比较逻辑流水级（[#5603](https://github.com/OpenXiangShan/XiangShan/pull/5603)）
    - 调整 UTAGE 历史信息流水级（[#5517](https://github.com/OpenXiangShan/XiangShan/pull/5517)）
    - 修复 SC 内部部分串行逻辑（暂未 PR）
    - 调整 ICache parity 校验逻辑流水级（暂未 PR）
    - 进一步评估和修复持续进行中

### 后端

- RTL 新特性
  - 添加 I2F FU 以支持 FMV 和 FCVT 的 i2f 类型（[#5557](https://github.com/OpenXiangShan/XiangShan/pull/5557), [#5577](https://github.com/OpenXiangShan/XiangShan/pull/5577)）
  - 支持 Smcntrpmf 扩展（[#4286](https://github.com/OpenXiangShan/XiangShan/pull/4286)）
- 时序/面积优化
  - 在 csrToDecode 与 Decode 之间增加一拍（[#5542](https://github.com/OpenXiangShan/XiangShan/pull/5542)）
  - 将 ALU 的数据处理从 Bypass 阶段转移到 ALU 内部（[#5562](https://github.com/OpenXiangShan/XiangShan/pull/5562)）
  - 对整数 IQ 添加 og1Payload，利用只在 OG1 中使用的信号以优化 IQ 选择时序。（[#5570](https://github.com/OpenXiangShan/XiangShan/pull/5570)）
- Bug 修复
  - 修复了来自功能单元写回的 redirect.valid 信号，以及 TopDown 中的 mis_pred 和 total flush 问题（[#5538](https://github.com/OpenXiangShan/XiangShan/pull/5538)）
  - 修复了 NewCSR 中 RegNext 的重复使用问题（[#5441](https://github.com/OpenXiangShan/XiangShan/pull/5441)）
  - 修复了 ROB 中 flushpipe 对 redirect.interrupt 的错误假设（[#5583](https://github.com/OpenXiangShan/XiangShan/pull/5583)）
- 代码质量
  - 重构所有 resps 信号，简化代码逻辑（[#5537](https://github.com/OpenXiangShan/XiangShan/pull/5537)）
  - 优化 resps 信号的代码质量（[#5550](http://github.com/OpenXiangShan/XiangShan/pull/5550)）
  - 移除 IsssueQueue 中部分冗余代码，调整唤醒 pdest 宽度，添加 ROB bankNum 参数（[#5051](https://github.com/OpenXiangShan/XiangShan/pull/5051)）
  - 重构 vialuf 以支持快速唤醒（[#5136](https://github.com/OpenXiangShan/XiangShan/pull/5136)）
  - 删除 Datapath 中的无用代码（[#5567](https://github.com/OpenXiangShan/XiangShan/pull/5567)）
  - 重构写回至 ROB 和 Regfile 的Bundle（[#5535](https://github.com/OpenXiangShan/XiangShan/pull/5535)）
  - 整合信号，使用 EnqRObUop 代替 DynInst 以减去多余的信号（[#5560](http://github.com/OpenXiangShan/XiangShan/pull/5560)）
  - 删除无用的 IntToFP 功能单元（[#5586](https://github.com/OpenXiangShan/XiangShan/pull/5586)）
- 结构调整
  - 删除 fudian 子模块，从现在起昆明湖 V3 将不再使用 fudian 仓库内容作为子模块（[#5585](https://github.com/OpenXiangShan/XiangShan/pull/5585)）

### 访存与缓存

- RTL 新特性
  - MDP、MMU、LoadUnit、StoreQueue、L2 等模块重构与测试持续推进中
- Bug 修复
  - 修复了 Sbuffer 中的超时判断逻辑，通过 csr 中的 SMBLOCKCTL 配置超时阈值（[#5573](https://github.com/OpenXiangShan/XiangShan/pull/5573)）
- 调试工具
  - 持续改进 CHI 基础设施 CHIron
  - 开发用于新版 L2 Cache 的验证工具 CHI Test。持续推进中

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 4e78369f4  |
| 日期      | 2026/01/29 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存延迟  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006   | GCC12 @3GHz | GCC15 @3GHz | XSCC @3GHz | SPECfp 2006   | GCC12 @3GHz | GCC15 @3GHz | XSCC @3GHz |
| :------------- | :---------: | :---------: | :--------: | :------------ | :---------: | :---------: | :--------: |
| 400.perlbench  |    38.87    |    43.00    |   41.70    | 410.bwaves    |    72.14    |    80.98    |   90.75    |
| 401.bzip2      |    27.05    |    26.74    |   27.75    | 416.gamess    |    54.49    |    55.54    |   51.90    |
| 403.gcc        |    47.55    |    50.17    |   37.16    | 433.milc      |    49.10    |    64.58    |   63.76    |
| 429.mcf        |    58.23    |    59.55    |   54.50    | 434.zeusmp    |    60.60    |    69.41    |   63.22    |
| 445.gobmk      |    37.34    |    35.51    |   36.30    | 435.gromacs   |    38.34    |    36.19    |   34.00    |
| 456.hmmer      |    43.11    |    53.10    |   63.26    | 436.cactusADM |    53.57    |    75.24    |   86.24    |
| 458.sjeng      |    34.47    |    34.80    |   36.03    | 437.leslie3d  |    54.20    |    56.48    |   56.64    |
| 462.libquantum |   132.83    |   135.28    |   282.43   | 444.namd      |    37.28    |    42.16    |   44.17    |
| 464.h264ref    |    62.00    |    61.95    |   70.30    | 447.dealII    |    64.13    |    58.88    |   66.92    |
| 471.omnetpp    |    42.63    |    39.60    |   39.03    | 450.soplex    |    52.43    |    49.25    |   59.39    |
| 473.astar      |    30.37    |    31.22    |   30.31    | 453.povray    |    61.43    |    70.66    |   63.65    |
| 483.xalancbmk  |    80.42    |    74.48    |   84.38    | 454.Calculix  |    19.37    |    43.84    |   39.05    |
| GEOMEAN        |    47.69    |    48.61    |   51.93    | 459.GemsFDTD  |    46.59    |    64.51    |   64.40    |
|                |             |             |            | 465.tonto     |    36.20    |    50.61    |   33.84    |
|                |             |             |            | 470.lbm       |   104.99    |   126.71    |   132.13   |
|                |             |             |            | 481.wrf       |    48.68    |    55.06    |   41.45    |
|                |             |             |            | 482.sphinx3   |    55.06    |    58.58    |   60.80    |
|                |             |             |            | GEOMEAN       |    50.56    |    59.73    |   58.16    |

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
