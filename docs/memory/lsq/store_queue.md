Store Queue
===========

雁栖湖架构的 store queue 是一个48项循环队列. 其每周期至多: 
* 从 dispatch 处接收6条指令
* 从 store 流水线接收2条指令的结果
* 将2条指令的数据写入 committed store buffer
* 为2条load流水线提供 store 到 load 前递结果
