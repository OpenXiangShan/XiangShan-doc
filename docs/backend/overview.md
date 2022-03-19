# 后端流水线

## 整体设计

处理器的流水线后端负责指令的重命名与乱序执行。香山处理器后端可以分为 CtrlBlock、IntBlock、FloatBlock、Memblock 4 个部分， CtrlBlock 负责指令的译码、重命名和分派， IntBlock、FloatBlock、MemBlock 分别负责整数、浮点、访存指令的乱序执行。

在这些模块中，有很多可以配置的参数。在目前的代码中，上述 4 个 Block 分别默认采用如下配置：

* CtrlBlock

* 译码 / 重命名 / 分派宽度 = 6

  * 发射前读寄存器堆

* IntBlock

  * 192 项物理寄存器

  * 4 * ALU + 2 * MUL/DIV + 1 * CSR/JMP

* FloatBlock

  * 192 项物理寄存器

  * 4 * FMAC + 2 * FMISC

* MemBlock

  * 2 * LOAD + 2 * STORE （其中 STORE 分为 data 和 address 独立进行运算）

## 代码实现

目前，香山后端代码写得较为粗放，通过人工的参数化传递实现设计的可配置。未来，我们计划使用Diplomacy重写代码，实现更为清晰的参数化设计。

在香山南湖的代码版本中，保留站与功能单元、寄存器堆被包裹成ExuBlock，其中包含Scheduler和FUBlock两部分，前者又再次包含了保留站和寄存器堆、BusyTable，后者则包含了对应的功能单元。这些层次的包裹仅仅为参数传递与连线作用，其中的有效逻辑代码非常少。

在定点ExuBlock中，包含了(1) ALU、MUL/DIV、MISC的保留站；(2) LOAD、STORE DATA、STORE ADDR的保留站；(3) ALU、MUL/DIV、MISC功能单元。

在浮点ExuBlock中，包含了(1) FMA、FMISC的保留站；(2) FMA、FMISC功能单元。

在访存MemBlock中，包含了访存子系统的设计。
