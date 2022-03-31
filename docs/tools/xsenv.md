XiangShan 前端开发环境
==================

在这一章中，我们将介绍如何编译和仿真香山代码、如何生成可运行的 Workload，并介绍一些开发中用到的辅助工具。

如果遇到问题，可以参考 [Troubleshooting](./troubleshoot.md) 以及 [https://github.com/OpenXiangShan/XiangShan/issues](https://github.com/OpenXiangShan/XiangShan/issues) 中的问题及解答。

## TLDR

使用以下脚本来一键布署香山开发环境（需要sudo权限）：

This script will setup XiangShan develop environment automatically：

```sh
git clone https://github.com/OpenXiangShan/xs-env
cd xs-env
sudo -s ./setup-tools.sh
source setup.sh
```

## 初始环境准备

请准备一台**性能较强**的服务器，以下为服务器的一些配置要求：

- 操作系统：Ubuntu 20.04 LTS （其他版本未测试，不建议使用）
CPU：不限，性能将决定编译与生成的速度
- 内存：**最低 32G，推荐 64G 及以上**
- 磁盘空间：20G 及以上
- 网络：请自行配置顺畅的网络环境

> 提示：内存过小、SWAP空间不足会导致编译错误。参见：[https://github.com/OpenXiangShan/XiangShan/issues/891](https://github.com/OpenXiangShan/XiangShan/issues/891)

（如果有条件，登录时推荐使用桌面环境或者开启 X11 转发以试用一些带有 GUI 界面的工具）

在服务器上安装 git, 随后使用 git 克隆以下仓库到本地:

```bash
git clone https://github.com/OpenXiangShan/xs-env.git
cd xs-env
```

该仓库中包含有一个脚本自动安装香山项目的依赖，请在运行前按需修改。

```bash
sudo -s ./setup-tools.sh
```
> 提示：这个脚本的执行需要 sudo 权限来安装香山项目依赖的软件包，请阅读理解脚本内容后执行，以防搅乱环境


安装完依赖以后执行`make`脚本
```bash
./setup.sh
```

执行 `ls` 确认其中拥有以下目录：

```
XiangShan    NEMU    nexus-am
```


配置环境变量：
```shell
source env.sh
```


上述命令设置了`NOOP_HOME`，`NEMU_HOME`，`AM_HOME`三个环境变量。您可以将这些环境变量加入到`.bashrc`中，也可以在每次使用香山前重新运行`env.sh`这一脚本配置环境变量（推荐）。
> 提示：在同时开发多个分支的香山时，推荐在每次运行前用脚本配置环境变量

在后续步骤出现问题时，可以参考 [Troubleshooting-Guide](https://github.com/OpenXiangShan/XiangShan/wiki/Troubleshooting-Guide) 来自行排查。

## 生成香山核的 Verilog 代码


在 `/xs-env/XiangShan` 下执行 
```shell
make init
```
该命令会将一些必要的 submodule 克隆下来。
> 提示：请务必确保这一过程期间到 github 的网络连接顺畅。submodule 的克隆不完整将会导致后续的编译错误。参见：[https://github.com/OpenXiangShan/XiangShan/issues/837](https://github.com/OpenXiangShan/XiangShan/issues/837)

### 生成单核代码


在 `/xs-env/XiangShan` 下运行 `make verilog` ，该命令将会编译香山的 Chisel 代码，生成 Verilog，输出的文件在 `XiangShan/build/XSTop.v`


### 生成双核代码


在 `/xs-env/XiangShan` 下运行 `make verilog NUM_CORES=2` ，该命令将会生成香山双核的 Verilog，输出的文件在 `XiangShan/build/XSTop.v`

## 仿真环境下验证香山

### 使用 AM 生成 workload

AM 是一个裸机运行时环境，用户可以使用 AM 来编译在香山裸机上运行的程序。使用 AM 编译程序的示例如下：

进入 `/xs-env/nexus-am/apps` 目录，可以看到在该目录下有一些预置的 workload，以 coremark 为例，进入`/xs-env/nexus-am/apps/coremark`，执行 `make ARCH=riscv64-xs -j8`，即可在当前 `build` 目录下看到 3 个文件：

```shell
coremark-riscv64-xs.elf  应用程序的 ELF 文件
coremark-riscv64-xs.bin  应用程序的二进制运行镜像
coremark-riscv64-xs.txt  应用程序的反汇编
```

生成的`coremark-riscv64-xs.bin`可以作为仿真中的程序输入。要使用 AM 生成自定义的 workload，请参考

#### 使用 AM 生成自定义 workload

[使用 AM 生成自定义 workload](./gen-workload-with-am.md)

#### 生成 Linux Kernel 作为 workload

[Linux Kernel 的构建](./linux-kernel-for-xs.md)

我们提供的环境中没有默认包含编译 Linux Kernel 相关的仓库，需要用户自行下载。


> 提示：我们在`xs-env/XiangShan/ready-to-run`中提供了预先编译好的 workload，包括启动 linux 并运行 hello.c 的 workload。



### 使用 NEMU 模拟器运行 workload
我们使用 NEMU 模拟器作为香山的实现参考。NEMU 模拟器是一个解释型的指令集模拟器。相比其他的 RISC-V 解释型指令集模拟器（如 spike），NEMU 在运行速度上有数量级的优势。


在使用 NEMU 模拟器运行 workload 时，我们需要将模拟器的虚拟外设与香山的外设地址空间对齐。进入 `/xs-env/NEMU` 目录，运行以下命令：
```bash
make clean
make riscv64-xs_defconfig
```
随后，使用以下命令编译 NEMU 模拟器：
```bash
make -j
```
> 提示：新旧版本的 NEMU 使用略有区别。要从旧版本的 NEMU 迁移到新版本的 NEMU，可以参考以下文档：
> [htps://github.com/OpenXiangShan/NEMU/wiki/%E6%96%B0NEMU%E4%B8%B4%E6%97%B6%E4%BD%BF%E7%94%A8%E6%8C%87%E5%8D%97](https://github.com/OpenXiangShan/NEMU/wiki/%E6%96%B0NEMU%E4%B8%B4%E6%97%B6%E4%BD%BF%E7%94%A8%E6%8C%87%E5%8D%97)

接下来运行 `./build/riscv64-nemu-interpreter -b MY_WORKLOAD.bin` 其中将 `MY_WORKLOAD.bin` 替换为想要运行镜像的路径，例如上一节中生成的 coremark，即可让 NEMU 模拟器运行指定的程序了。例如：


```bash
./build/riscv64-nemu-interpreter -b $NOOP_HOME/ready-to-run/linux.bin
```


### 生成香山核的仿真程序
我们使用 Verilator 生成香山核的仿真程序，进入 `XiangShan` 目录，运行命令
```bash
make emu CONFIG=MinimalConfig EMU_TRACE=1 -j32
```
将会生成一个最小配置的香山的仿真程序，这一步时间会比较久，需要耐心等待。生成结束后，可以在 `./build/` 目录下看到一个名为 `emu` 的仿真程序。其中，`CONFIG=MinimalConfig`指定了香山核使用的配置（参见：[https://github.com/OpenXiangShan/XiangShan-doc/blob/main/documentation/0-%E5%8F%82%E6%95%B0%E7%B3%BB%E7%BB%9F.md](https://github.com/OpenXiangShan/XiangShan-doc/blob/main/documentation/0-%E5%8F%82%E6%95%B0%E7%B3%BB%E7%BB%9F.md)），`EMU_TRACE=1`会为仿真程序添加波形输出功能，允许在仿真过程中启用波形输出。


> 更多参数请参考`Makefile`脚本代码。



要仿真默认配置的完整香山核，可以使用以下命令：
```bash
make emu -j32
```
> 注意！生成 Verilog 所需的时间会稍久，推荐大家使用 Tmux 等工具在后台运行上述命令

### 在香山核仿真程序上仿真运行 workload
与香山核协同仿真的 NEMU 模拟器配置与独立运行时略有不同。我们使用以下的命令编译仿真中使用的 NEMU：


在 `/xs-env/NEMU`下运行：
```
make clean
make riscv64-xs-ref_defconfig
make -j
```
这个命令会将 NEMU 模拟器编译成动态链接库，将会在 `build` 目录下生成文件 `riscv64-nemu-interpreter-so`，从而接入到香山仿真差分测试中。


利用前面生成好的香山仿真程序，NEMU 动态链接库与 workload，可以默认在差分测试框架打开的情况下让香山核运行指定的应用程序，进入`/xs-env/XiangShan` 目录运行指令 `./build/emu -i MY_WORKLOAD.bin`  其中将 `MY_WORKLOAD.bin` 替换为想要运行镜像的路径，比如前面生成的 coremark，即可让香山仿真运行指定的程序了。例如：
```
./build/emu -i $NOOP_HOME/ready-to-run/linux.bin
```


### 生成波形
我们可以使用 `--dump-wave` 参数打开波形，并使用 `-b` 和 `-e` 参数设置生成波形的开始和结束周期，例如想要生成 10000 ~ 11000 周期的波形，可以使用如下命令：
```shell
./build/emu -i MY_WORKLOAD.bin --dump-wave -b 10000 -e 11000
```


其中 `-b` 和 `-e` 的默认值为 0，注意仅当 `-e` 参数大于 `-b` 时才会真正记录波形；波形文件将会生成在 `./build/` 目录下，格式为 vcd。波形文件可以后续使用 gtkwave 等开源工具或者 dve 等商业工具进行查看。


> 注意：在仿真中生成波形需要在生成仿真程序时使用`EMU_TRACE=1`的参数，详见*生成香山核的仿真程序*一节

### 日志功能简介
如果编译 emu 时打开了打印日志的功能（前述流程默认关闭），那么在运行 emu 时，将会打印日志。为了避免在终端输出日志，占用终端 IO 带宽，导致终端卡死，请将终端输出重定向到文件中。使用如下命令：
`./build/emu -i MY_WORKLOAD.bin -b 10000 -e 11000 2>&1 | tee > MY_LOGNAME.log`
> 提示：可以使用 LogViewer 工具查看日志



### 性能计数器的查看和分析
当 workload 执行结束后，将会打印性能计数器结果。如果将性能计数器的内容重定向到文件中，就可以使用可视化工具参看结构化的性能计数器信息。
> 提示: 在运行 `emu` 时, 可以添加 `--force-dump-result` 参数来强制输出性能计数器结果到标准输出流。

我们提供了一个[可视化性能计数器的结果的工具](https://github.com/OpenXiangShan/perfUI)。注意！该工具具有 GUI 界面，如果想要使用请做好 X11 转发相关配置。
