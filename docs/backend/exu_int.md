# 整数部件

## ALU

香山的 ALU 支持加减、逻辑、分支、部分位扩展等指令。

## MUL/DIV


## MISC: CSR/JUMP

香山的 CSR 实现支持 riscv-priv-1.12 版本规范。

由于 JUMP 指令的特殊操作数需求，我们在 MISC 单元中实现了 JUMP 指令的操作。
