# JTAG and Debug<br>JTAG和调试

NANHU implements [RISC-V External Debug Support Version 0.13.2](https://riscv.org/wp-content/uploads/2019/03/riscv-debug-release.pdf).<br>南湖实现了[RISC-V外部调试支持0.13.2版本](https://riscv.org/wp-content/uploads/2019/03/riscv-debug-release.pdf)。

NANHU uses components including Debug Module, Debug Module Interface, Debug Transport Module and JTAG Interface.<br>南湖使用的组件包括调试模块、调试模块接口、调试传输模块和 JTAG 接口。

NANHU Debug Module supports Program Buffer (16 bytes) and System Bus Access. Abstract Commands are implemented using Program Buffer.
It is connected to L3 crossbar using TileLink to support System Bus Access.
It has two parts: DMInner and DMOuter. DMInner is driven by core clock while DMOuter is driven by JTAG clock. DMOuter issues debug interrupts.<br>南湖调试模块支持程序缓冲区（16字节）和系统总线访问。抽象命令通过程序缓冲区实现。
它通过 TileLink 连接到 L3 互联以支持系统总线访问。
它由两部分组成：DMInner 和 DMOuter。DMInner 由内核时钟驱动，而 DMOuter 则由 JTAG 时钟驱动。DMOuter 触发调试中断。

## Debug &nbsp; 调试

NANHU CSR has a one bit register indicating whether it is in Debug Mode.<br>南湖的CSR通过一个单比特寄存器指示它是否处于调试模式。

Debug mode can be entered when:<br>以下情况可以进入调试模式：

* Debug Module issues a debug interrupt.<br>调试模块触发了调试中断。

* An ebreak is executed in mode X and ebreakX is executed (X is M, S, or U).<br>在X模式下执行ebreak，并执行ebreakX（X为M、S或U）。

* The hart has returned from Debug Mode, and step bit in dcsr is set. The hart enters debug mode after exactly one instruction has committed.<br>硬件线程（hart）已从调试模式返回，且 dcsr 中的step位被置位。当一条指令执行完毕后，硬件线程进入调试模式。

* Trigger hit with action bit set to 1 in the corresponding mcontrol CSR.<br>触发器命中时将 mcontrol CSR 中相应的将操作位设置为 1

NANHU implements the following debug mode registers:
Debug control and status register (dcsr), Debug PC (dpc), Debug Scratch (dscratch and dscratch1).<br>南湖实现了以下调试模式寄存器：
调试控制和状态寄存器（dssr）、调试 PC（dpc）、调试暂存器（dscratch 和 dscratch1）。

### Debug control and status register &nbsp; 调试控制和状态寄存器

NANHU implements optional dcsr bits ebreaks, ebreaku, mprven and step.
See [RISC-V External Debug Support Version 0.13.2](https://riscv.org/wp-content/uploads/2019/03/riscv-debug-release.pdf) for more detail.<br>NANHU实现了可选的 dcsr 位 ebreaks、ebreaku、mprven 和 step。
更多细节请参阅 [RISC-V 外部调试支持 0.13.2 版](https://riscv.org/wp-content/uploads/2019/03/riscv-debug-release.pdf)。

### Debug PC &nbsp; 调试PC

Debug PC stores the program counter of the exact instruction that trapped into debug mode. The pc is recovered when a dret is executed. Debug Module can modify this CSR to manipulate the path of program execution.<br>调试PC用于存储进入调试模式的精确指令的程序计数器。PC在执行dret指令时恢复。调试模块可以修改该 CSR，以控制程序的执行路径。

### Debug Scratch &nbsp; 调试暂存器

There are 2 debug scratch registers (dscratch and dscratch1) in NANHU. These registers are used as scratch registers by the Debug Module.<br>NANHU 中有 2 个调试暂存器（dscratch 和 dscratch1）。这些寄存器被调试模块用作暂存器。

## Trigger &nbsp; 触发器

### Trigger select register &nbsp; 触发选择寄存器

Tselect selects one of the 10 triggers in  NANHU. All NANHU's triggers are listed below.<br>Tselect 从南湖的 10 个触发器中选择一个。下表列出了南湖的所有触发器。

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

*: If type is store or load, select bit will be WARL as 0.<br>如果类型是store或load，select位将被置为WARL的0。

### Trigger data status register &nbsp; 触发器数据状态寄存器

All triggers in NANHU are match control triggers. Each has a mcontrol (tdata1), data (tdata2) and info (tinfo) register.<br>南湖中的所有触发器都是匹配控制触发器。每个触发器都有一个 mcontrol（tdata1）、data（tdata2）和info（tinfo）寄存器。

## Breakpoint &nbsp; 断点

NANHU supports using ebreak instruction as software breakpoint. To use this in privileged mode X, ebreakX bit in dcsr should be set. Hardware breakpoints are implemented using triggers.<br>南湖支持使用 ebreak 指令作为软件断点。为了在特权模式 X 下使用该指令，应设置 dcsr 中的 ebreakX 位。硬件断点通过触发器实现。

## Debug memory map &nbsp; 调试内存映射

Debug Module uses address space (0x3802_0000,  0x3802_0fff).<br>调试模块使用从0x3802_0000到 0x3802_0fff的地址空间。

## Debug Module Interface &nbsp; 调试模块接口

DMI has a bus width of 7 bits.<br>DMI有一个宽度为7位的总线。

## JTAG Interface &nbsp; JTAG接口

Nanhu’s JTAG interface supports asynchronous reset TRSTn.<br>南湖的 JTAG 接口支持异步复位 TRSTn。

## Connecting to Debug Module &nbsp; 连接调试模块

First, [riscv-openocd](https://github.com/riscv/riscv-openocd) needs to be compiled. See [Github README](https://github.com/riscv/riscv-openocd/blob/riscv/README) on how to compile riscv-openocd.<br>首先，您需要编译 [riscv-openocd](https://github.com/riscv/riscv-openocd)。有关如何编译 riscv-openocd，请参考 [Github README](https://github.com/riscv/riscv-openocd/blob/riscv/README)。

Run simv with options: `./difftest/simv [+workload=WorkloadName.bin] +no-diff +enable-jtag`<br>通过以下操作运行 simv： `./difftest/simv [+workload=WorkloadName.bin] +no-diff +enable-jtag`

Then in another terminal, run: `./openocd -f XS.cfg`<br
后在其他终端运行：`./openocd -f XS.cfg`

The content of an example openocd config file XS.cfg is shown as below:<br>openocd 配置文件 XS.cfg 示例内容如下：

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

To connect to GDB, remove the “exit” command shown above. In another terminal, launch riscv64-unknown-elf-gdb and run command: `target extended-remote:3333`<br>要连接 GDB，请删除上面的 "exit "命令，并在另一个终端启动 riscv64-unknown-elf-gdb，运行命令：`target extended-remote:3333`
