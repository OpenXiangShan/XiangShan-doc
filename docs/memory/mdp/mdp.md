# 访存依赖预测

这一章描述香山处理器访存违例预测预测器的整体架构。

香山处理器在 decode 附近根据 PC 预测访存依赖. 目前的代码支持两种预测方式:

* Load Wait Table[^21264]
* Store Sets[^storesets] 的变种

南湖架构使用了与 Store Sets 类似的访存依赖预测机制. 如果预测到一条 load 指令可能违例, 则这条 load 指令需要在保留站中等待到之前的 store 都发射之后才能发射.

## 南湖的访存违例预测器

### 依赖预测

* 整体思路基于 Store Sets, 实现了 Store Sets 中的两个表: SSIT 和 LFST
* 南湖架构只预测 store addr 未就绪引起的违例
* 一个 Store Set 会同时追踪**多个** inflight 的 store, 只有这里所有的 store 都执行完成后, 依赖于这个 Store Set 的 load 才会被预测为没有依赖
* SSIT 的查询在 rename 进行. LFST 的查询在 dispatch 进行

### 依赖处理

* 南湖架构的访存违例预测器使用 robIdx 追踪指令前后关系
* 与原始 Store Sets 不同, **不要求同一个 Store Set 内的 store 指令顺序执行**
* 预测器会**尝试预测 load 指令是否可能依赖多个 store 的结果**. 如果预测器认为 load 指令不依赖多个 store 的结果, 那么在这个 load 前的最后一个依赖的 store 地址产生后, 这条 load 指令就可以被发射. 否则, 这条 load 只有在它被预测依赖的所有 store 都产生地址之后才会被发射.

### 预测器更新

在发生 store - load 违例时, 触发违例的指令的 PC 会被传递到访存违例预测器以进行更新. 每过一个刷新间隔, 违例预测器中的信息会被无效化. 刷新间隔可以使用 `slvpredctl` CSR 寄存器配置.

<!-- 违例预测器刷新时会直接将对应项无效化. 后面会考虑加入置信度的设计, 只将置信度低的刷掉. -->

<!-- 目前正常执行的 load 的结果不会反馈给预测器进行更新, 下一版本中将考虑相关的设计. -->

## 引用

[^21264]: Kessler, Richard E. "The alpha 21264 microprocessor." IEEE micro 19.2 (1999): 24-36.

[^storesets]: Chrysos, George Z., and Joel S. Emer. "Memory dependence prediction using store sets." ACM SIGARCH Computer Architecture News 26.3 (1998): 142-153.


