# Workloads Overview

Workloads refer to programs that run on the XiangShan processor. When developing, debugging, evaluating, or researching on the XiangShan simulation environment, workloads are essential.

!!! note
    The requirements for workloads described in this document generally also apply to emulators like NEMU and XS-GEM5.

## Workload File Format

The XiangShan simulation environment only supports flat binary format workload files, which do not contain any headers. The XiangShan simulation environment directly loads the workload file as is into the memory space at physical address `0x80000000`. You can use the `-i` parameter to pass the workload to the XiangShan simulation environment:

```bash
./build/emu -i path/to/workload.bin
```

The XiangShan simulation environment only accepts one workload file. If your workload has multiple parts, you need to merge them into a single file using tools like `dd`. For example, if you have a file `a.bin` that you want to place at `0x80000000` and a file `b.bin` that you want to place at `0x80200000`, you can use the following command to concatenate them into a single `workload.bin`:

```bash
# Copy a.bin as the base
cp a.bin workload.bin
# Inject b.bin at the position 1024 * 2048 = 0x200000
dd of=workload.bin if=b.bin obs=1024 seek=2048 conv=notrunc
```

The XiangShan simulation environment does not support ELF format executable files. If your workload is in ELF format, you need to convert it into a flat binary using tools like `objcopy`. For example, you can use the following command to convert an ELF executable `workload.elf` into a flat binary `workload.bin`:

```bash
riscv64-unknown-linux-gnu-objcopy -O binary workload.elf workload.bin
```

## Ending Simulation

### XiangShan Trap / NEMU Trap Instruction

The XiangShan simulation environment provides a special instruction called XiangShan Trap (also known as NEMU Trap) to immediately end the simulation and return a value.

The format of the XiangShan Trap instruction is as follows:

* The opcode field is `0x6B`
* Source operand 1 (`rs1`) points to the register that holds the return value, usually `a0` / `x10`
* Other fields remain zero

The return value has the following meanings:

* A return value of 0 indicates `HIT GOOD TRAP`, meaning the simulation exited normally.
* A return value of 1 indicates `HIT BAD TRAP`, meaning the simulation exited abnormally.
* Other values are reserved by the simulation framework and may have special meanings, which are not recommended for use.

The XiangShan Trap instruction depends on the XiangShan simulation environment and the Difftest framework to take effect. For XiangShan cores not connected to Difftest, this instruction acts as a `nop`.

### Example

To end the simulation using a XiangShan Trap, typically two steps are involved: writing the return value into the `a0` register and calling the XiangShan Trap instruction.

For assembly programs, you can use the following snippet:

```
li a0, 0        # Write 0 into the a0 register (HIT GOOD TRAP)
.word 0x5006b   # Call the XiangShan Trap
```

For C programs, you can use the following snippet:

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
