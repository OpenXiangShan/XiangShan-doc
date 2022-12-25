# JTAG and Debug

NANHU implements [RISC-V External Debug Support Version 0.13.2](https://riscv.org/wp-content/uploads/2019/03/riscv-debug-release.pdf).

NANHU uses components including Debug Module, Debug Module Interface, Debug Transport Module and JTAG Interface.

NANHU Debug Module supports Program Buffer (16 bytes) and System Bus Access. Abstract Commands are implemented using Program Buffer.
It is connected to L3 crossbar using TileLink to support System Bus Access.
It has two parts: DMInner and DMOuter. DMInner is driven by core clock while DMOuter is driven by JTAG clock. DMOuter issues debug interrupts.

## Debug

NANHU CSR has a one bit register indicating whether it is in Debug Mode.

Debug mode can be entered when:

* Debug Module issues a debug interrupt.

* An ebreak is executed in mode X and ebreakX is executed (X is M, S, or U).

* The hart has returned from Debug Mode, and step bit in dcsr is set. The hart enters debug mode after exactly one instruction has committed.

* Trigger hit with action bit set to 1 in the corresponding mcontrol CSR.

NANHU implements the following debug mode registers:
Debug control and status register (dcsr), Debug PC (dpc), Debug Scratch (dscratch and dscratch1).

### Debug control and status register

NANHU implements optional dcsr bits ebreaks, ebreaku, mprven and step.
See [RISC-V External Debug Support Version 0.13.2](https://riscv.org/wp-content/uploads/2019/03/riscv-debug-release.pdf) for more detail.

### Debug PC

Debug PC stores the program counter of the exact instruction that trapped into debug mode. The pc is recovered when a dret is executed. Debug Module can modify this CSR to manipulate the path of program execution.

### Debug Scratch

There are 2 debug scratch registers (dscratch and dscratch1) in NANHU. These registers are used as scratch registers by the Debug Module.

## Trigger

### Trigger select register

Tselect selects one of the 10 triggers in  NANHU. All NANHU's triggers are listed below.

| No. | Type | Timing bit | Chain  bit | Select bit | Match bit |
| --- | --- | --- | --- | --- | --- |
| 0 | execute/store/load | Wired to  0 | Y | Y* | 0, 2 or 3 |
| 1 | execute/store/load |  | Y | Y* |
| 2 | execute/store/load |  | Y | Y* |
| 3 | execute/store/load |  | Y | Y* |
| 4 | execute/store/load |  | Y | Y* |
| 5 | execute/store/load |  | Y | Y* |
| 6 | execute/store/load |  | Y | Y* |
| 7 | execute/store/load |  | Y | Y* |
| 8 | execute/store/load |  | Y | Y* |
| 9 | execute/store/load |  | Wired to 0 | Y* |

*: If type is store or load, select bit will be WARL as 0.

### Trigger data status register

All triggers in NANHU are match control triggers. Each has a mcontrol (tdata1), data (tdata2) and info (tinfo) register.

## Breakpoint

NANHU supports using ebreak instruction as software breakpoint. To use this in privileged mode X, ebreakX bit in dcsr should be set. Hardware breakpoints are implemented using triggers.

## Debug memory map

Debug Module uses address space (0x3802_0000,  0x3802_0fff).

## Debug Module Interface

DMI has a bus width of 7 bits.

## JTAG Interface

Nanhu’s JTAG interface supports asynchronous reset TRSTn.

## Connecting to Debug Module

First, [riscv-openocd](https://github.com/riscv/riscv-openocd) needs to be compiled. See [Github README](https://github.com/riscv/riscv-openocd/blob/riscv/README) on how to compile riscv-openocd.

Run simv with options: `./difftest/simv [+workload=WorkloadName.bin] +no-diff +enable-jtag`

Then in another terminal, run: `./openocd -f XS.cfg`

The content of an example openocd config file XS.cfg is shown as below:

```
adapter driver remote_bitbang
remote_bitbang host localhost
remote_bitbang port 23334


set _CHIPNAME riscv
jtag newtap $_CHIPNAME cpu -irlen 5

set _TARGETNAME $_CHIPNAME.cpu
target create $_TARGETNAME riscv-chain-position $_TARGETNAME

init
reset halt
echo "reset and halt at the reset vector"
exit
```

To connect to GDB, remove the “exit” command shown above. In another terminal, launch riscv64-unknown-elf-gdb and run command: `target extended-remote:3333`
