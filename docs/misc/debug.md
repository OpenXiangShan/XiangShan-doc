使用GDB调试香山
===================

我们在香山内接入了 Rocket Chip 的 Debug Module ，使其支持 0.13 版本 [RISCV Debug 手册](https://riscv.org/wp-content/uploads/2019/03/riscv-debug-release.pdf)中的调试模式（Debug Mode）。

## 原理

Debug Module 可以通过中断的方法使得处理器核进入调试模式，随后GDB可以使处理器核执行任意指令和读取任意寄存器。在 Debug Module 发出中断后，处理器核会陷入到 Debug Module 的 MMIO 地址空间并开始循环。Debug Module 通过在这片地址空间中写入指令来控制核的行为并读取核的寄存器。

Debug Module 也支持 System Bus Access 功能，即不通过处理器核来读写物理内存。香山的 Debug Module 通过 TileLink 接入了 L3 缓存，以便于数据一致性的维护。请注意，要在仿真时使用该功能，请使用 Default Config。

## 软件与配置
通过 GDB 调试香山需要安装 `riscv64-unknown-elf-gdb` 与 `openocd`。安装方式请参考相应的 Github 项目（直接按照README安装即可，无需额外配置）：[GDB](https://github.com/riscv-collab/riscv-binutils-gdb)， [OpenOCD](https://github.com/riscv/riscv-openocd)

OpenOCD 需要配置文件，可使用下面的配置：
```
adapter speed 10000

adapter driver remote_bitbang
remote_bitbang host localhost
remote_bitbang port 23334

set _CHIPNAME riscv
jtag newtap $_CHIPNAME cpu -irlen 5

set _TARGETNAME $_CHIPNAME.cpu
target create $_TARGETNAME riscv -chain-position $_TARGETNAME 

# riscv set_reset_timeout_sec 120
# riscv set_command_timeout_sec 30
riscv set_mem_access sysbus
init
halt
echo "Ready for Remote Connections"
```

## 用 GDB 连接香山
编译得到 emu 后，执行 `./build/emu --enable-jtag` ，同时在另一个终端里执行 `openocd -f config.cfg` ，其中 `config.cfg` 为 OpenOCD 配置文件，通时在第三个终端里执行 `riscv64-unknown-elf-gdb`。推荐使用 tmux 分屏进行操作。

在 GDB 的命令行中执行 `target extended-remote localhost:3333` ，稍等即可连接到香山仿真程序。