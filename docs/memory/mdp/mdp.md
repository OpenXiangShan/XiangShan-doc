# 访存依赖预测

这一章描述香山处理器访存违例预测预测器的整体架构。

香山处理器在 decode 附近根据 PC 预测访存依赖. 目前的代码支持两种预测方式: 

* Load Wait Table[1]
* Store Sets[2]

雁栖湖架构只实现了基于 Wait Table 的访存依赖预测. 如果预测到一条 load 指令可能违例, 则这条 load 指令需要在保留站中等待到之前的 store 都发射之后才能发射.

# 参考文献

[1] Kessler R E . The Alpha 21264 Microprocessor[J]. IEEE Micro, 1999, 19(2):24-36.

[2] Chrysos G Z ,  Emer J S . Memory Dependence Prediction using Store Sets[J]. ACM SIGARCH Computer Architecture News, 2002, 26(3):142-153.


