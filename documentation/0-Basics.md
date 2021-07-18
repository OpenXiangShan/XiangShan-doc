# 香山基础

香山是一款高性能的开源RISC-V处理器，支持RV64GC指令集。

## 基础架构

11级流水（IFU1, IFU2, IFU3, IFU4, Decode, Rename, Dispatch, Regfile, Issue, Execute, Commit），默认宽度为6（可参数化配置）

## 仿真环境下支持的外设

uartlite串口、Flash（作为bootrom）、自定义SDCard、内存、VGA等，具体参考SimMMIO模块