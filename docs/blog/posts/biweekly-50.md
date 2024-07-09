---
slug: biweekly-50
date: 2024-04-29
categories:
  - Biweekly
---

# 【香山双周报 50】20240429期

欢迎来到我们的双周报专栏，本次是香山双周报专栏的第 50 期。我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习、一起进步。

近期，昆明湖各组持续推进面积、时序、功耗的优化。此外，前端重构了 ICache 和 ITLB，newBackend 合入主线，CHI 总线的 XSTile 集成完成，BOP 优化和 DCache Evict on Refill 优化合入主线，多核 TLTest + VIP 的测试环境完成搭建。本期还更新了昆明湖架构近期性能。

<!-- more -->
## 近期进展

### 前端

* 初始化 s2_req_vsetIdx 寄存器解决 X 态传播问题（[#2909](https://github.com/OpenXiangShan/XiangShan/pull/2909)）
* 添加 sstval 的前端支持（[#2850](https://github.com/OpenXiangShan/XiangShan/pull/2850)）
* 完成重构新 ICache 和 ITLB 的时序调优
* 通过对 FTBBank 分 Row gate 提升 clock gating efficiency

### 后端流水线

* 完成 Load 推测唤醒依赖向量 LoadDependency 减少一位，优化面积（[#2911](https://github.com/OpenXiangShan/XiangShan/pull/2911)）
* 新后端时序优化分支合入主线（[#2908](https://github.com/OpenXiangShan/XiangShan/pull/2908)）
* 优化重命名快照生成策略，提高快照的利用率
* 去除向量访存指令唤醒时的错误依赖关系，提高向量访存性能

### 访存与缓存

* CHI 总线
    * 完成 CHI 总线的 XSTile 集成，实现 MMIO 空间的 TL 转 CHI 转接桥
    * CHI-CoupledL2 系统测试添加 VCS 仿真 difftest 功能，目前成功通过 uart 串口测试程序、stream 测试、coremark 测试
    * CHI-CoupledL2 优化关键路径违例（90 ps -> 56 ps），优化 L2 面积（74 w -> 63.9w）
* H 扩展
    * 调试 H 扩展合入 NewBackend 后产生的 bug，目前通过了 Xvisor 的测试，但仍未通过 KVM 测试
* 向量访存
    * 推进 Segment 向量访存指令的实现和验证，开始合并 master 分支并对接验证需求
* 性能优化
    * L2 BOP 预取虚地址训练优化合入香山主线（[#2382](https://github.com/OpenXiangShan/XiangShan/pull/2382)）
    * DCache Evict on Refill 优化合并入香山主线（[#2919](https://github.com/OpenXiangShan/XiangShan/pull/2919)）
    * 优化 L2 DRRIP 替换并实现 Hawkeye 替换
    * 完成 Temperal 预取器 meta 共享 L2 data 空间并添加所占 way 数限制，但测试性能不及预期
    * 优化 RequestBuffer 中正常请求和预取请求的仲裁逻辑
    * L2 缓存数据压缩算法通过 TLTest 验证，正在修复 spec 测试的 bug
* 功耗优化
    * 访存子模块静态门控覆盖率优化功耗评估，模块总功耗降低 14.34%
* 多核测试
    * 完成多核 TLTest + VIP 的测试环境，开始多核压力测试

## 评估

我们采用 SimPoint 对程序进行采样，基于我们自定义的 Checkpoint 格式制作检查点镜像，**Simpoint 聚类的覆盖率为 80%**。SPEC06 使用 gcc 12 进行编译，开启 O3 优化，采用 jemalloc 内存库，设置 SPEC06FP 的 `-ffp-contraction` 选项为 `fast`，指令集为 RV64GCB。我们使用 **4月29日 19fbeaf47**的香山处理器（**缓存大小配置为 64KB L1 ICache + 64KB L1 DCache + 1MB L2 + 16MB L3，访存单元为 3ld3st 流水线**），在仿真环境下运行了 SPEC06 片段，使用 DRAMsim3 模拟 CPU 在 3GHz 情况下 DDR4-3200 内存的延迟。以下为 SPECCPU 2006 的分数估计情况：

| SPECint 2006   | @ 3GHz | SPECfp 2006   | @ 3GHz |
| :------------- | :----: | :------------ | :----: |
| 400.perlbench  | 35.82  | 410.bwaves    | 60.23  |
| 401.bzip2      | 26.58  | 416.gamess    | 42.50  |
| 403.gcc        | 47.87  | 433.milc      | 37.17  |
| 429.mcf        | 61.37  | 434.zeusmp    | 40.79  |
| 445.gobmk      | 30.29  | 435.gromacs   | 30.34  |
| 456.hmmer      | 38.32  | 436.cactusADM | 42.14  |
| 458.sjeng      | 30.44  | 437.leslie3d  | 41.36  |
| 462.libquantum | 121.28 | 444.namd      | 30.60  |
| 464.h264ref    | 57.09  | 447.dealII    | 68.63  |
| 471.omnetpp    | 39.58  | 450.soplex    | 55.52  |
| 473.astar      | 31.45  | 453.povray    | 53.07  |
| 483.xalancbmk  | 73.18  | 454.Calculix  | 19.49  |
| **GEOMEAN**    | 44.62  | 459.GemsFDTD  | 30.69  |
|                |        | 465.tonto     | 33.68  |
|                |        | 470.lbm       | 93.81  |
|                |        | 481.wrf       | 36.10  |
|                |        | 482.sphinx3   | 48.50  |
|                |        | **GEOMEAN**   | 42.16  |

**上述分数为基于程序片段的分数估计，非完整 SPEC CPU 2006 评估，和真实芯片实际性能可能存在偏差！**

## 后记

香山开源处理器正在火热地开发中，新的功能与新的优化在持续添加中，我们将通过香山双周报专栏定期地同步我们的开源进展。感谢您的关注，欢迎在后台留言与我们交流！

在香山昆明湖架构研发后期，性能会每月公布一次，敬请期待！

## 相关链接

* 香山技术讨论 QQ 群：879550595
* 香山技术讨论网站：https://github.com/OpenXiangShan/XiangShan/discussions
* 香山文档：https://xiangshan-doc.readthedocs.io/


编辑：高泽宇、唐浩晋、李燕琴、蔡洛姗

审校：香山宣传工作组
