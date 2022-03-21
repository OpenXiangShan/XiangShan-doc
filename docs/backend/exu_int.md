# 整数部件

## ALU

香山的 ALU 支持加减、逻辑、分支、部分位扩展等指令。

## MUL

## DIV

香山使用了 SRT16 定点除法器[^1]，每周期运算4位，除法循环前后处理各两拍。

## MISC: CSR/JUMP

香山的 CSR 实现支持 riscv-priv-1.12 版本规范。

由于 JUMP 指令的特殊操作数需求，我们在 MISC 单元中实现了 JUMP 指令的操作。

[^1]: E. Antelo, T. Lang, P. Montuschi and A. Nannarelli, "Digit-recurrence dividers with reduced logical depth", IEEE Trans. Comput., vol. 54, no. 7, pp. 837-851, Jul. 2005.