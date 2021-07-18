# 香山项目介绍导引

## 一、香山是什么

香山是一款开源的高性能 RISC-V 处理器，基于Chisel硬件设计语言实现，支持 RV64GC 指令集。在香山处理器的开发过程中，使用了包括 Chisel、Verilator、GTKwave 等在内的大量开源工具，实现了差分验证、仿真快照、  RISC-V 检查点等处理器开发的基础工具，建立起了一套包含设计、实现、验证等在内的基于全开源工具的处理器敏捷开发流程。

**香山项目链接**：

github：[https://github.com/OpenXiangShan](https://github.com/OpenXiangShan)

码云：[https://gitee.com/OpenXiangShan](https://gitee.com/OpenXiangShan)


**香山项目仓库介绍**：

**XiangShan**：香山处理器实现

**XiangShan-doc**：香山处理器文档，包括设计文档、公开报告以及对错误新闻的澄清。

**NEMU**：运行速度可以匹敌 QEMU 的 ISA 模拟器

**nexus-am**：Abstract Machine，提供程序的运行时环境

**DRAMsim3**：cycle-level 的模拟内存的行为

**env-scripts**：一些脚本文件，包括性能分析、模块替换和时序分析等

以及其他仓库包括 **riscv-linux** ，**riscv-pk** ，**riscv-torture** 等等。

## 二、香山处理器目录结构

![香山仓库目录结构](https://cdn.nlark.com/yuque/0/2021/png/1658967/1626589677507-f2e2be8b-50b3-4a3d-ba51-878966c4d97e.png#clientId=u36ff8c37-b511-4&from=paste&height=280&id=u42dc4fd8&margin=%5Bobject%20Object%5D&name=image.png&originHeight=500&originWidth=680&originalType=binary&ratio=1&size=123143&status=done&style=none&taskId=uc0300f28-db39-432a-a59a-bf9ee6f4ce1&width=381.0000305175781)

## 三、香山处理器架构设计

香山处理器是乱序六发射结构设计，前端包括取值单元，分支预测单元，指令缓冲等单元，顺序取值。后端包括译码，重命名，重定序缓冲，保留站，整型/浮点寄存器堆，整型/浮点运算单元。我们将访存子系统分离开，包括两条 load 流水线和两条 store 流水线，以及独立的 load 队列和 store 队列，Store Buffer等。缓存包括I$、D$、L1+$、L2$、TLB和预取器等模块。各部分的在流水线中的位置以及参数配置可以从下图中获得。

![香山处理器结构图](https://github.com/OpenXiangShan/XiangShan/raw/master/xs-arch-simple.svg#from=url&height=710&id=lut7D&margin=%5Bobject%20Object%5D&originHeight=3033&originWidth=3118&originalType=binary&ratio=1&status=done&style=none&width=730.0000610351562)

香山处理器的具体结构设计见后续介绍

## 四、单元测试

我们基于 Chiseltest2 实现了类 UVM 的单元测试 Agent-Faker ，目前应用于 Dcache ，L2Cache 和 TLB .

![Agent-Faker](https://cdn.nlark.com/yuque/0/2021/png/1658967/1626597614804-74b94bad-238a-44a9-b145-8aedfe661e03.png#clientId=u36ff8c37-b511-4&from=paste&height=606&id=u5f77fdb5&margin=%5Bobject%20Object%5D&name=image.png&originHeight=590&originWidth=527&originalType=binary&ratio=1&size=192248&status=done&style=none&taskId=u07260fc4-9b52-44ac-80f8-03029db39e7&width=541.5)

## 五、仿真测试

香山处理器主要使用 verilator 进行仿真，并模拟 uart 和 sd 卡等外设。仿真时和模拟器 NEMU [链接] 做运行时对比，并将处理器的时钟中断等信息传递给模拟器，指导模拟器在关键选择上和处理器保持一致，提高仿真的灵活度。

![Diff-test](https://cdn.nlark.com/yuque/0/2021/png/1658967/1626600254022-9212589c-6146-4c75-b29e-bc23c7c4b479.png#clientId=u36ff8c37-b511-4&from=paste&height=383&id=udd05f69d&margin=%5Bobject%20Object%5D&name=image.png&originHeight=519&originWidth=572&originalType=binary&ratio=1&size=42137&status=done&style=none&taskId=uf9d09eb9-80be-4830-8f16-1a97b62794f&width=422)

当处理器和模拟器行为不一致时，仿真程序将会停止，通过查看波形和日志的方式进行错误分析。我们开发了 Wave Terminator [链接]，将低层次语义的波形提取成具有高层次语义的日志。另外，我们还开发了日志查看器 LogViewer [链接]，从而更方便的查看日志。

## 六、性能评估

在仿真时，每个模块都可以自由地打印计数器，可以选择实时打印计数器以及在仿真结束时打印计数器。通过脚本工具对性能计数器进行分析 [env-script链接] ，我们还开发了可视化工具对性能计数器进行分析。
为了测试 SPEC 基准测试的性能，以及对 SPEC 程序进行性能分析，使用 NEMU 生成 SPEC 程序的 SimPoint ，进行大规模的并行测试，快速得出 SPEC 分数。另外，SPEC 片段也可以用于开发时的性能评估。
