---
slug: biweekly-101
date: 2026-04-27
categories:
  - Biweekly
---

# 【香山双周报 101】20260427 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 101 期双周报。

昆明湖 V3 的设计文档已经逐步公开，欢迎大家阅读并与我们讨论！目前，新版设计文档包含 ICache 和 BPU 两个模块，其他模块的设计文档将随着开发的进行陆续发布。设计文档仍然在 <https://docs.xiangshan.cc/projects/design/zh-cn/>，如果大家对昆明湖 V2 的设计文档感兴趣，可以通过网页右下角切换分支来查看。

关于香山核近期开发进展，前端着重优化了 BPU 的时序，后端和访存实现了多个新特性，并且修复了一些功能 bug。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 启用 SC Backward 表（[#5796](https://github.com/OpenXiangShan/XiangShan/pull/5796)）
- Bug 修复
  - 修复 S1 级 RAS 在 S3 override 时栈顶地址用错的问题（[#5680](https://github.com/OpenXiangShan/XiangShan/pull/5680)）
- PPA 优化
  - 去除存储在 FTQ 的 SC 训练元数据，改为更新时读，节省面积（[#5819](https://github.com/OpenXiangShan/XiangShan/pull/5819)）
  - 解耦 TAGE 跳转计数器和 useful 计数器的写入，节省功耗（[#5782](https://github.com/OpenXiangShan/XiangShan/pull/5782)）
  - 修复 BPU S3 多条时序路径（[#5797](https://github.com/OpenXiangShan/XiangShan/pull/5797)）
  - 修复 SC 预测时序路径（[#5843](https://github.com/OpenXiangShan/XiangShan/pull/5843)）
  - 修复 FTQ 重定向及分支 resolve 时序路径（[#5835](https://github.com/OpenXiangShan/XiangShan/pull/5835)）
- 代码质量
  - 删除未使用的 V2 工具类（[#5821](https://github.com/OpenXiangShan/XiangShan/pull/5821)）

### 后端

- RTL 新特性
  - (V2) 允许通过 CSR 配置“提交停滞”（commit stuck）关键错误检查 ([#5806](https://github.com/OpenXiangShan/XiangShan/pull/5806))
  - 新增开关，用于禁用分派负载均衡优化 ([#5815](https://github.com/OpenXiangShan/XiangShan/pull/5815))
  - 解决因主流水线资源不足导致的误报问题 ([#5803](https://github.com/OpenXiangShan/XiangShan/pull/5803))
- PPA 优化
  - 优化分派策略以提升性能 ([#5801](https://github.com/OpenXiangShan/XiangShan/pull/5801))
- Bug 修复
  - 修复间接 CSR RegOut 问题 ([(V2) #5823](https://github.com/OpenXiangShan/XiangShan/pull/5823), [5833](https://github.com/OpenXiangShan/XiangShan/pull/5833))

### 访存与缓存

- RTL 新特性
  - 完成新版 StoreUnit 设计（[#5760](https://github.com/OpenXiangShan/XiangShan/pull/5760)）
  - 持续推进新版 L2 设计
- Bug 修复
  - 修复了 StoreUnit 跨 16 字节前递时 OverLapMask 的问题（[#5814](https://github.com/OpenXiangShan/XiangShan/pull/5814)）
  - CoupledL2 在本地 Flush All 时跳过全局 CleanInvalid（[CoupledL2 #499](https://github.com/OpenXiangShan/CoupledL2/pull/499)）

### XSAI

- RTL 新特性
  - 正在测试矩阵模块的 FP8 精度支持
  - 正在评估矩阵模块的 8 通道访存
  - 正在与后端组配合实现 BF16 标量与向量
- 代码质量
  - 优化了 XSAI 的参数系统（[XSAI #59](https://github.com/OpenXiangShan/XSAI/pull/59)）
- 调试工具
  - NEMU 新增 BF16 扩展支持（[NEMU #995](https://github.com/OpenXiangShan/NEMU/pull/995)）
  - HBL2 测试兼容多核环境

## 性能评估

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 82d2669b2  |
| 日期      | 2026/04/23 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | CHI        |
| 内存配置  | DDR4-3200  |

性能数据如下所示：

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.55  | 47.58  | 410.bwaves         | 85.31  | 90.03  |
| 401.bzip2           | 27.44  | 28.26  | 416.gamess         | 57.05  | 53.20  |
| 403.gcc             | 55.18  | 39.57  | 433.milc           | 64.74  | 64.04  |
| 429.mcf             | 61.07  | 55.44  | 434.zeusmp         | 71.39  | 64.13  |
| 445.gobmk           | 38.93  | 40.08  | 435.gromacs        | 37.20  | 34.38  |
| 456.hmmer           | 54.39  | 64.70  | 436.cactusADM      | 76.02  | 87.74  |
| 458.sjeng           | 38.89  | 39.43  | 437.leslie3d       | 56.29  | 56.46  |
| 462.libquantum      | 136.76 | 294.79 | 444.namd           | 43.21  | 45.23  |
| 464.h264ref         | 63.44  | 72.03  | 447.dealII         | 64.12  | 68.46  |
| 471.omnetpp         | 41.05  | 39.51  | 450.soplex         | 52.08  | 64.00  |
| 473.astar           | 30.46  | 29.66  | 453.povray         | 73.34  | 66.37  |
| 483.xalancbmk       | 75.80  | 84.53  | 454.Calculix       | 43.80  | 39.68  |
| GEOMEAN             | 50.92  | 54.14  | 459.GemsFDTD       | 63.55  | 64.27  |
|                     |        |        | 465.tonto          | 52.57  | 35.04  |
|                     |        |        | 470.lbm            | 125.76 | 133.04 |
|                     |        |        | 481.wrf            | 54.94  | 41.59  |
|                     |        |        | 482.sphinx3        | 59.37  | 62.42  |
|                     |        |        | GEOMEAN            | 61.05  | 59.23  |

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
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、孙际儒、李衍君
