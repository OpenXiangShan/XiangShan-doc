---
slug: biweekly-9
date: 2022-01-24
categories:
  - Biweekly
---

# 【香山双周报 9】20220124 期

欢迎来到我们的双周报专栏。本次是香山双周报专栏的第 9 期，我们将通过这一专栏，定期介绍香山的开源进展，希望与大家共同学习，一起进步。欢迎大家通过公众号后台留言的方式与我们交流！

<!-- more -->
## 近期进展

### 前端

* **BPU 部分**

    * 时序收敛完成；
    * 修复一些造成误预测率上升的性能 bug；
    * TAGE 预测器的修改

        * 用 bim 的结果作为 altpred；
        * 实现 use-alt-on-na 的算法；
        * 优化 useful bit reset 算法；

    * 误预测重新取指加一拍；
    * 去除了 oversize 逻辑，现在取指令允许的最大 packet 长度为 32 Bytes（之前允许 34 Bytes 取指令）；
    * 把 fall through address error 的检查放在 BPU stage 3。

* **Fetch(IFU/ICache/IBuffer) 部分**

    * 时序收敛完成；
    * 上一周后端对这部分做了重新布局，多出来几条时序违例比较严重的路径。
    * 1 月 13 号的评估结果发现从 FTQ 过来的 redirect 信号串接到了 ITLB 产生的 miss 信号上，这个信号又通过 FTQ 请求端口的 ready 信号送回 FTQ，造成 FTQ 自身的一个比较长的路径回环。我们在 ICacheMainPipe 的 s0 阶段把 FTQ 的请求锁存下来，同时让 FTQ 的 valid 信号和 redirect 信号解耦开；
    * 1 月 16 号的评估结果发现 IFU、ICache 和 IPrefetch 去争抢 PMP 两个端口的逻辑比较长（3 级 MUX），因此我们在前端把访问 PMP 的端口增加到 4 个（ICache 使用两个，其它分别给 IFU 和 IPrefetch）；
    * 1 月 20 号的评估结果时序已经达标。

* **整个 Frontend 模块（包含 BPU 和 Fetch）时序已达标**

### 后端

* **Debug Mode & Trigger**

    * 这周修改了 Debug Module 的 SBA 模块，SBA 的功能是直接访问物理内存，每个请求可读写 2^n 字节数据，最多 128bit。在香山里它和 L3 连接以维护数据一致性。Rocket 使用 Tilelink 的 Put/Get 请求来写/读，Tilelink 请求的地址就是 SBA 请求的地址。但由于 SBA 每次写入都少于 256bit，所以这里把 Put 请求改成 PutPartial+mask 的方式来实现。

## 后记

这周香山处理器前端的时序收敛已基本到位，整个南湖架构的代码也只剩下细微的调整，同时南湖架构代码的验证工作（FPGA 平台/仿真平台）也在进一步推进。

同时另一个令人激动的消息是香山雁栖湖架构的流片芯片已完成封装和测试板焊接，这周我们将开始对芯片进行调试，预计春节期间我们将展示第一版芯片的相关情况。

编辑：金越、勾凌睿、李乾若
