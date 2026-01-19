---
slug: biweekly-94
date: 2026-01-19
categories:
  - Biweekly
---

# 【香山双周报 94】20260119 期

欢迎来到香山双周报专栏，我们将通过这一专栏定期介绍香山的开发进展。本次是第 94 期双周报。

这是 2026 年第一期双周报！在过去的 2025 年中，香山团队脚踏实地，高质量完成了多个重要里程碑：

- 首次实现产业落地。第二代香山南湖作为主控CPU，分别被摩尔线程与芯动科技集成到最新一代芯片中，其中摩尔线程出货量已有数万颗；第三代香山昆明湖已完成面向首批 SoC 芯片的产品级交付，其中两家企业分别于 10 月与 11 月完成 SoC 芯片流片，将于 2026 年 Q1 回片
- 荣获中国计算机学会 CCF 体系结构专委会首届开源贡献奖
- “香山”开源处理器核作为 2025 年度中国科学院科研成果代表之一，写入中科院侯建国院长的新年贺词
- 在 ISCA、HPCA、MICRO 等顶级会议上作 tutorial，向全世界介绍香山的最新进展
- 开发了多项工具，并在国际顶级会议上发表论文，如 GSIM（DAC25）、DiffTest-H（MICRO25）、TraceRTL（HPCA26）、UCAgent 等
- 数篇基于香山评估的论文在国际顶级会议发表
- 验证工作持续完善，成功通过 8 核一致性验证、启动 GUI OpenEuler 等多个里程碑测试
- 昆明湖 V3 成为新的默认分支，最新性能超越昆明湖 V2
- 举办 RISCV Hackathon、文档捉虫等社区活动，在第二节香山开源社区大会与全世界关心香山进展的朋友们热烈交流
- 香山编译器（XSCC）发布，香山有了自己的编译器
- 万众一芯团队的 AI 智能体 UCAgent 发布，成功举办首届开源芯片黑客马拉松

新的一年意味着新的开始。在 2026 年，香山将继续贯彻“开源”这一新理念，持续推进昆明湖 V3 的迭代研发与开源社区建设。衷心感谢大家一直以来对香山的陪伴与支持！

香山开发方面，1-taken 与 1-fetch 的新前端基本完成；后端继续推进新向量单元的设计实现，同时重构了现有代码；访存继续重构了 MMU、LoadUnit、StoreQueue、L2 等模块，并修复了一些 bug。

<!-- more -->

## 近期进展

### 前端

- RTL 新特性
  - 实现 MBTB replacer 仅 touch 预测结果为跳转的分支，使无用分支优先被替换出 MBTB（[#5414](https://github.com/OpenXiangShan/XiangShan/pull/5414)）
  - 实现 ITTAGE SRAM 分 bank，减少读写冲突（[#5430](https://github.com/OpenXiangShan/XiangShan/pull/5430)）
  - 实现 TAGE 将 provider 信息存入 metaQueue 减少更新时读，从而减少读写冲突（[#5400](https://github.com/OpenXiangShan/XiangShan/pull/5400)）
- Bug 修复
  - 修复 ITTAGE SRAM 读写冲突条件有误的问题（[#5392](https://github.com/OpenXiangShan/XiangShan/pull/5392)）
  - 修复 TAGE 训练阻塞时其它预测器被重复训练的问题（[#5399](https://github.com/OpenXiangShan/XiangShan/pull/5399)）
- 时序/面积优化
  - 修复 MBTB、TAGE 中 WriteBuffer 写端口的时序问题（[#5418](https://github.com/OpenXiangShan/XiangShan/pull/5418)，[#5433](https://github.com/OpenXiangShan/XiangShan/pull/5433)）
  - 修复 ABTB SRAM 位宽过大、选型不佳导致的时序问题（[#5417](https://github.com/OpenXiangShan/XiangShan/pull/5417)）
- 代码质量
  - 重写 Frontend 顶层模块中不符合 style guide 的部分代码，修复 IDE warning（[#5395](https://github.com/OpenXiangShan/XiangShan/pull/5395)）
  - 使用 AddrField 类重写 ABTB、UBTB 的各索引选择逻辑（[#5397](https://github.com/OpenXiangShan/XiangShan/pull/5397)）
  - 清理 ABTB 中无用代码（[#5456](https://github.com/OpenXiangShan/XiangShan/pull/5456)）
- 调试工具
  - 新增 MicroTAGE Trace（[#5388](https://github.com/OpenXiangShan/XiangShan/pull/5388)）
  - 新增 ICache Trace（[#5452](https://github.com/OpenXiangShan/XiangShan/pull/5452)）
  - 新增大量性能计数器（[#5442](https://github.com/OpenXiangShan/XiangShan/pull/5442)，[#5443](https://github.com/OpenXiangShan/XiangShan/pull/5443)，[#5289](https://github.com/OpenXiangShan/XiangShan/pull/5289)）

### 后端

- RTL 新特性
  - 正在推进 V3 向量单元的新设计实现
  - （V3）修改 mvendorid 的值（[#5427](https://github.com/OpenXiangShan/XiangShan/pull/5427)）
  - （V3）重构 vimac64b 模块，实现 vimac 金模型并添加相应接口到 VecSimTop（[YunSuan #193](https://github.com/OpenXiangShan/YunSuan/pull/193)）
- Bug 修复
  - （V3）修复提交时的 RAS 操作问题（[#5421](https://github.com/OpenXiangShan/XiangShan/pull/5421)）
  - （V2/V3）修复 CSR 读指令读取 vl/vlenb 导致非法指令异常的优先级的问题（[#5420](https://github.com/OpenXiangShan/XiangShan/pull/5420)，[#5422](https://github.com/OpenXiangShan/XiangShan/pull/5422)）
  - （V3）在 diffVl 的 debug 接口中使用 basicDebugEn 信号（[#5465](https://github.com/OpenXiangShan/XiangShan/pull/5465)）
  - （V2）升级 NEMU config 以修复 vfredusum 问题（[#5434](https://github.com/OpenXiangShan/XiangShan/pull/5434)）
- 时序
  - （V3）减少 redirect 中的一周期延迟（[#5378](https://github.com/OpenXiangShan/XiangShan/pull/5378)）
  - （V3）将 oldestExuRedirect 的选择从 ctrlblock 移动到 intRegion（[#5462](https://github.com/OpenXiangShan/XiangShan/pull/5462)）
  - （V3）将 targetPc 分为 trap 和 xret 路径以优化时序，分别处理例外和 CSR FunctionUnit 的写回（[#5475](https://github.com/OpenXiangShan/XiangShan/pull/5475)）
- 代码优化
  - （V3）移除部分死代码（[#5405](https://github.com/OpenXiangShan/XiangShan/pull/5405)，[#5324](https://github.com/OpenXiangShan/XiangShan/pull/5324)）
  - （V3）移除一些使用 0.U 宽度进行连接的代码（[#5413](https://github.com/OpenXiangShan/XiangShan/pull/5413)）
  - （V3）转用 CSRs.scala 文件保持对 CSR 地址的跟踪（[#5440](https://github.com/OpenXiangShan/XiangShan/pull/5440)）
  - （V3）在后端每个参数类中单独配置 vl src 以便于维护（[#5368](https://github.com/OpenXiangShan/XiangShan/pull/5368)）

### 访存与缓存

- RTL 新特性
  - MMU、LoadUnit、StoreQueue、L2 等模块重构与测试持续推进中
- Bug 修复
  - 修改 PerfetcgWrapper 中 Pipeline 的 pipe 参数为 true（[#5275](https://github.com/OpenXiangShan/XiangShan/pull/5275/files)）
  - 修复了 storeMisalignBuffer 满时多次写回的错误（[#5415](https://github.com/OpenXiangShan/XiangShan/pull/5415)）
  - 移除L2中冗余的BEU范围排除（[CoupledL2 #457](https://github.com/OpenXiangShan/CoupledL2/pull/457)）
  - 将其他 V2 上的 pr 同步到 V3 上
- 代码重构
  - 移除了 fdpMonitor 并修复了一些统计错误（[#5272](https://github.com/OpenXiangShan/XiangShan/pull/5272)）
- 调试工具
  - 持续改进 CHI 基础设施 CHIron
  - 开发用于新版 L2 Cache 的验证工具 CHI Test。持续推进中

## 性能评估

| SPECint 2006 est. | @ 3GHz | SPECfp 2006 est. | @ 3GHz |
| :---------------- | :----: | :--------------- | :----: |
| 400.perlbench     | 38.38  | 410.bwaves       | 73.28  |
| 401.bzip2         | 27.53  | 416.gamess       | 55.10  |
| 403.gcc           | 48.17  | 433.milc         | 46.08  |
| 429.mcf           | 60.25  | 434.zeusmp       | 60.34  |
| 445.gobmk         | 37.30  | 435.gromacs      | 38.58  |
| 456.hmmer         | 44.20  | 436.cactusADM    | 54.30  |
| 458.sjeng         | 34.49  | 437.leslie3d     | 53.87  |
| 462.libquantum    | 127.76 | 444.namd         | 38.02  |
| 464.h264ref       | 63.36  | 447.dealII       | 62.95  |
| 471.omnetpp       | 43.19  | 450.soplex       | 54.69  |
| 473.astar         | 30.68  | 453.povray       | 61.24  |
| 483.xalancbmk     | 81.47  | 454.Calculix     | 19.40  |
| GEOMEAN           | 48.07  | 459.GemsFDTD     | 44.60  |
|                   |        | 465.tonto        | 36.34  |
|                   |        | 470.lbm          | 104.91 |
|                   |        | 481.wrf          | 48.88  |
|                   |        | 482.sphinx3      | 56.16  |
|                   |        | GEOMEAN          | 50.55  |

编译参数如下所示：

| 参数             | 选项     |
| ---------------- | -------- |
| 编译器           | gcc12    |
| 编译优化         | O3       |
| 内存库           | jemalloc |
| -march           | RV64GCB  |
| -ffp-contraction | fast     |

处理器及 SoC 参数如下所示：

| 参数      | 选项       |
| --------- | ---------- |
| commit    | 1a9a2f52c  |
| 日期      | 2025/12/31 |
| L1 ICache | 64KB       |
| L1 DCache | 64KB       |
| L2 Cache  | 1MB        |
| L3 Cache  | 16MB       |
| 访存单元  | 3ld2st     |
| 总线协议  | TileLink   |
| 内存延迟  | DDR4-3200  |

注：我们使用 SimPoint 对程序进行采样，基于我们自定义的 checkpoint 格式制作检查点镜像，Simpoint 聚类的覆盖率为 100%。上述分数为基于程序片段的分数估计，非完整 SPEC CPU2006 评估，和真实芯片实际性能可能存在偏差。

## 相关链接

- 香山技术讨论 QQ 群：879550595
- 香山技术讨论网站：<https://github.com/OpenXiangShan/XiangShan/discussions>
- 香山文档：<https://xiangshan-doc.readthedocs.io/>
- 香山用户手册：<https://docs.xiangshan.cc/projects/user-guide/>
- 香山设计文档：<https://docs.xiangshan.cc/projects/design/>

编辑：徐之皓、吉骏雄、陈卓、余俊杰、李衍君
