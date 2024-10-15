# 工作负载概述

This chapter has [English version](./overview.en.md).

工作负载（Workloads）泛指运行在香山处理器之上的程序。在香山仿真环境上进行开发、调试、评估、研究时，工作负载是必不可少的。

!!! note
    这篇文档介绍的工作负载要求通常也适用于 NEMU、XS-GEM5 等模拟器环境。

## 工作负载格式

香山仿真环境仅支持纯二进制（Flat binary）格式的工作负载文件，不包含任何文件头。香山仿真环境会直接将工作负载文件按原样加载到物理地址为 `0x80000000` 的内存空间中。在香山仿真环境中，您可使用 `-i` 参数传递工作负载：

```bash
./build/emu -i path/to/workload.bin
```

香山仿真环境仅支持传递 1 个工作负载文件。如果您的工作负载包含多个部分，您需要通过 `dd` 等工具将它们合并为同一个文件。例如，如果您有文件 `a.bin` 希望放置于 `0x80000000`，文件 `b.bin` 希望放置于 `0x80200000`，则可使用下面的命令将他们拼接为单个 `workload.bin`：

```bash
# 将 a.bin 复制一份作为基底
cp a.bin workload.bin
# 注入 b.bin，位置是 1024 * 2048 = 0x200000
dd of=workload.bin if=b.bin obs=1024 seek=2048 conv=notrunc
```

香山仿真环境不支持 ELF 格式的可执行文件。如果您的工作负载是 ELF 格式的可执行文件，您需要使用 `objcopy` 等工具将它转化为纯二进制文件。例如，可使用下面的命令将 ELF 格式的可执行文件 `workload.elf` 转化为纯二进制文件 `workload.bin`：

```bash
riscv64-unknown-linux-gnu-objcopy -O binary workload.elf workload.bin
```

## 结束仿真运行

### XiangShan Trap / NEMU Trap 指令

香山仿真环境提供了特殊命令 XiangShan Trap（亦称 NEMU Trap）来立即结束仿真，并给出一个返回值。

XiangShan Trap 指令的格式如下：

* 操作码（`opcode`）字段为 `0x6B`
* 源操作数 1（`rs1`）字段指向存储返回值的通用寄存器，通常为 `a0` / `x10`
* 其他字段保持为 0

返回值含义如下：

* 返回值为 0 时，提示 `HIT GOOD TRAP`，标识仿真正常退出；
* 返回值为 1 时，报 `HIT BAD TRAP`，标识仿真非正常退出；
* 其他值为仿真框架保留，可能有带有特殊含义，不建议使用。

XiangShan Trap 指令依赖于香山仿真环境和 Difftest 框架来发挥作用。对于未接入 Difftest 的香山核，该指令相当于 `nop`。

### 示例

使用 XiangShan Trap 结束仿真通常包含两步：将返回值写入 `a0` 寄存器，调用 XiangShan Trap 指令。

对于汇编程序，可使用以下片段：

```
li a0, 0        # 将 0 写入 a0 寄存器（HIT GOOD TRAP）
.word 0x5006b   # 调用 XiangShan Trap
```

对于 C 语言程序，可使用以下片段：

```c
void trap(int trap_code) {
    asm volatile (
        "mv a0, %0\n"
        ".word 0x5006b\n"
        :
        : "r"(trap_code)
        : "a0"
    );
}
```
