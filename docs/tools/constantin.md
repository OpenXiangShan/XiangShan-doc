# Constantin简介

在处理器调试、性能探索过程中，有一些常数参数需要频繁调整，有一些新实现组件需要和原版比较性能/功能。如果采用修改Chisel RTL并重新编译仿真环境的方法，需要花费20-120分钟时间且容易因各种小错误被打断，迭代效率低。为此，我们开发了`Constantin`允许常数参数的决定推迟到运行时，从而实现一次RTL编译可仿真多个常数值、多种组件版本、打开不同功能开关的功能。

本工具利用`DPI-C`在仿真器运行时读取配置文件内的信息获取当前各常量预期值，从而实现运行时改变常量取值。当前机制从技术上也支持在单次仿真过程中改变常量的取指，但尚未找到有效应用场景，如有对应场景，欢迎在香山 repo issue区提出。

## 使用方法

### 运行时可变常量值

可以使用`Constantin`提供的`createRecord`方法，创建特定名字的常量信号，在相同常量信号被重复创建时，返回的将会是同一常量，受同一配置文件项控制。

```scala
val loop_lower_bound = Wire(UInt(64.W))
loop_lower_bound := Constantin.createRecord("lowerbound")
```

在`${NOOP_HOME}/build/constantin.txt`文件内可以如下格式指明对应常量取值：

```
lowerbound 10
```

### 运行时切换模块版本

可以使用`Constantin`附带的`MuxModule`功能辅助`createRecord`实现运行时动态切换模块。

```scala
val predMux = Module(new MuxModule(new BasePredictorIO()(p), 2))
predMux.io.in(1) <> predComposer.io
predMux.io.in(0) <> predFake.io
val predSel = Constantin.createRecord("predSel")
predMux.io.sel := predSel

val predictors = predMux.io.out
```

`MuxModule`接受模块端口类型与可选版本数量两个参数，其`in`端口可接受指明类型的端口，`out`端口输出选通版本，`sel`可连接到由`createRecord`创建的常量从而实现运行时版本的切换。

### 动态控制开关

运行时可变常量可类型转换为`Bool`，从而作为一些RTL功能开关的控制信号。