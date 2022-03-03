# 访存依赖预测

这一章描述香山处理器访存违例预测预测器的整体架构。

香山处理器在 decode 附近根据 PC 预测访存依赖. 目前的代码支持两种预测方式: 

* Load Wait Table[1]
* Store Sets 的变种[2]

南湖架构使用了与 Store Sets 类似的访存依赖预测机制. 如果预测到一条 load 指令可能违例, 则这条 load 指令需要在保留站中等待到之前的 store 都发射之后才能发射.

## 南湖的 Store Sets 变种

* 两个表: SSIT 和 LFST
* 不要求 store 指令顺序
* 只预测 addr 未就绪引起的违例 
* 使用 robIdx 追踪指令前后关系
* 一个 Store Set 会同时追踪多个 inflight 的 store, 只有这里所有的 store 都执行完成, 依赖于这个 store set 的 load 才能自由发射.

SSIT 的查询在 rename 进行. LFST 的查询在 dispatch 进行.

# 参考文献

[1] Kessler R E . The Alpha 21264 Microprocessor[J]. IEEE Micro, 1999, 19(2):24-36.

[2] Chrysos G Z ,  Emer J S . Memory Dependence Prediction using Store Sets[J]. ACM SIGARCH Computer Architecture News, 2002, 26(3):142-153.


