XiangShan Front-end Development Environment
===================

In this chapter, we will introduce how to run Xiangshan core in simulation, how to generate workload for Xiangshan. We will also introduce some useful tools for Xiangshan core development.

**If you encounter problems, you may refer to [Troubleshooting](./troubleshoot.md) and [https://github.com/OpenXiangShan/XiangShan/issues](https://github.com/OpenXiangShan/XiangShan/issues) for Q&As**.

##TLDR

Use the following script to deploy the Xiangshan development environment, **the deployment script only needs to be run once**:

This script will setup XiangShan develop environment automatically. Note that `./setup-tools.sh` and `setup.sh` only need to be run **ONCE**. You may need to read and modify `setup-tools.sh` before you start.

````sh
git clone https://github.com/OpenXiangShan/xs-env
cd xs-env
sudo -s ./setup-tools.sh # use apt to install dependencies, you may modify it to use different pkg manager
source setup.sh # prepare tools, test develop env using a small project
````

**After environment setup, every time you want to use the development environment, just use the following command to configure the environment variables**:

<!-- After XiangShan Develop Environment setup, use the following script **every time** before using XiangShan Develop Environment. -->

````sh
cd xs-env
source ./env.sh # setup XiangShan environment variables
````

## Requirements for the server

- Operating system: Ubuntu 20.04 LTS (other versions have not been tested and are not recommended)
CPU: no limit. Will influence the speed of Verilog generation & simulation
- Memory: **32G minimum, 64G and above recommended**
- Disk space: 20G or above
- Network: should be able to access Github

> Tip: insufficient memory and insufficient SWAP space will cause compilation errors. See: [https://github.com/OpenXiangShan/XiangShan/issues/891](https://github.com/OpenXiangShan/XiangShan/issues/891)

## Setup Verilator based simulation environment

<!-- If possible, it is recommended to use a desktop environment or enable X11 forwarding when logging in to try out some tools with a GUI interface -->

Install git on the server, then use git to clone the following repositories:

```bash
git clone https://github.com/OpenXiangShan/xs-env.git
cd xs-env
````

This repository contains a script to install the dependencies of the Xiangshan project. Check and modify that script (if needed), then run it.

```bash
sudo -s ./setup-tools.sh
````

> Tip: The execution of this script requires sudo privileges to install the packages that Xiangshan project depends on. Please read and understand the content of the script and execute it to avoid breaking the environment

Execute `setup.sh` script after installing the dependencies. This script will compile NEMU, then use a small Chisel project to test if the environment has been setup correctly.

```bash
./setup.sh
```

## Configure environment variables

**After completing the development environment setup, you only need to configure the environment variables by `source env.sh` before using the development environment**. 3 environment variables need to be setup to use Xiangshan's environment. To set these environments, enter `xs-env`, then run:

```shell
source env.sh
````

The above script sets three environment variables: `NOOP_HOME`(Core RTL Position), `NEMU_HOME`(ISA Simulator Position), `AM_HOME`(Abstract Machine, bare metal runtime). You can add these environment variables to `.bashrc` / `.zshrc`, or re-run the `env.sh` script to configure environment variables every time when you use Xiangshan (recommended).

## Generate Verilog code for Xiangshan core

Execute under `/xs-env/XiangShan`:

```shell
make init
```

This command will clone some necessary submodules.
> Tip: Make sure you have a good network connection to github during this process. Incomplete clones of submodules will result in subsequent compilation errors. See: [https://github.com/OpenXiangShan/XiangShan/issues/837](https://github.com/OpenXiangShan/XiangShan/issues/837)

### Generate single core Verilog code

Run `make verilog` under `/xs-env/XiangShan`, this command will compile Xiangshan's Chisel code and generate Verilog, the output Verilog file is `XiangShan/build/XSTop.v`. It takes about 40 minutes. 

### Generate dual core Verilog code

Run `make verilog NUM_CORES=2` under `/xs-env/XiangShan`, this command will generate the Verilog of Xiangshan (dual core), the output Verilog file is `XiangShan/build/XSTop.v`

## Verify Xiangshan in the simulation environment

### Generate workload using AM

AM is a bare metal runtime environment. Users can use AM to compile programs running on Xiangshan bare metal. 

An example of compiling a program using AM:

Enter the `/xs-env/nexus-am/apps` directory, you can see that there are some preset workloads in this directory. Take coremark as an example, enter `/xs-env/nexus-am/apps/coremark`, execute `make ARCH=riscv64-xs -j8`. Then you can see 3 files in the current `build` directory:

```
coremark-riscv64-xs.elf   # ELF file for the program
coremark-riscv64-xs.bin   # binary running image of the program
coremark-riscv64-xs.txt   # Disassemble of the program
```

The generated `coremark-riscv64-xs.bin` can be used as program input in simulation. 


#### Generate custom workload with AM

To generate custom workloads using AM, see [generate custom workload with AM](./gen-workload-with-am-en.md)

### Generate Linux Kernel as workload

To run Linux Kernel on XiangShan, we need to use BBL. See [building the Linux Kernel](./linux-kernel-for-xs-en.md).

The environment we provide does not include the src code for compiling Linux Kernel, users need to download it by themselves.

> Tip: We provide pre-generated workloads in `xs-env/XiangShan/ready-to-run`, including workloads that boots linux and run hello.c (linux.bin).

### Run workload using NEMU emulator

NEMU is an instruction set emulator. We use NEMU as the implementation reference for Xiangshan. After you generated workload based on nexus-am or bbl, it is recommend that to test the workload on NEMU.

Before running the workload on the NEMU emulator, we need to make sure the virtual peripherals of NEMU uses the same address as Xiangshan. Go to the `/xs-env/NEMU` directory and run the following command:

```bash
make clean
make riscv64-xs_defconfig
````

Then, compile the NEMU emulator with the following command:

```bash
make -j
````

> Tip: these commands will generate NEMU executable file (instead of shared lib, which will be used later).

Next, run `./build/riscv64-nemu-interpreter -b MY_WORKLOAD.bin` where `MY_WORKLOAD.bin` is replaced with the path to your workload, such as `coremark-riscv64-xs.bin` generated in the previous section. 

For example, this command will run pre-generated linux-hello workload:

```bash
./build/riscv64-nemu-interpreter -b $NOOP_HOME/ready-to-run/linux.bin
````

### Generate the simulation program of Xiangshan core (Verilator)

Verilator is used to generate Xiangshan core simulation program. Enter `XiangShan` directory, and run the following command:

```bash
make emu CONFIG=MinimalConfig EMU_TRACE=1 -j32
````

In this command, `CONFIG=MinimalConfig` specifies the configuration used by the Xiangshan core. `EMU_TRACE=1` will add a waveform output function to the emulator, allowing the waveform output to be enabled during the simulation.

A simulation program of Xiangshan (minimal configuration) will be generated by this command. When build is finished, you can see an emulator named `emu` in `./build/` directory. 

> For more parameters, please refer to the `Makefile` script code.

To emulate the full Xiangshan core with the **default configuration**, the following command can be used in `XiangShan` directory:

```bash
make emu EMU_TRACE=1 -j32
```


> Attention! Generate Verilog is slow. It is recommended to use tools such as Tmux to run these commands in background

### Run workload on Xiangshan core simulator

By default, NEMU co-simulation is enabled in simulation. DUT will be compared with NEMU every cycle in simulation.

To run co-simulation, NEMU needs to be configured before co-simulation starts. Note that NEMU's configuration for co-simulation with the Xiangshan core is slightly different from what we did above. Use the following command to compile NEMU used in co-simulation:

Run under `/xs-env/NEMU`:

````
make clean
make riscv64-xs-ref_defconfig
make -j
````

This command will compile the NEMU simulator into a dynamic link library, and will generate the file `riscv64-nemu-interpreter-so` in the `build` directory, which will be connected to Xiangshan co-simulation framework.


Then we can start Xiangshan simulation (Verilator) using the previously generated Xiangshan simulation program, NEMU dynamic link library and workload.
To run a workload, enter the `/xs-env/XiangShan` directory and run the command `./build/emu -i MY_WORKLOAD.bin` where `MY_WORKLOAD.bin` is the path of the workload.

You can let Xiangshan run pre-generated workload. E.g:

```sh
./build/emu -i $NOOP_HOME/ready-to-run/linux.bin
```


### Generate waveform

One can use `--dump-wave` parameter to enable waveform generation, and use `-b` and `-e` parameters to set the start and end cycles of the generated waveform. For example, if you want to generate a waveform of 10000 ~ 11000 cycles, you can use the following command :

```shell
./build/emu -i MY_WORKLOAD.bin --dump-wave -b 10000 -e 11000
````


The default value of `-b` and `-e` is 0. Note that the waveform will only be recorded when the `-e` parameter is greater than `-b`; the waveform file will be generated in the `./build/` directory , the format is vcd. Waveform files can be viewed using open source tools such as gtkwave or commercial tools such as dve.

> Note: To generate waveforms in simulation, you need to use the `EMU_TRACE=1` parameter when generating the simulation program.

### Print log

While running emu, log (`printf` in Chiesl code) will be printed if log printing is enabled when compiling emu (which is not enabled by default). To avoid outputting logs on the terminal, occupying the terminal IO bandwidth and causing the terminal to freeze, please redirect the terminal output to a file. Use the following command:
`./build/emu -i MY_WORKLOAD.bin -b 10000 -e 11000 2>&1 | tee > MY_LOGNAME.log`

### Generate the simulation program of Xiangshan core (VCS)

Enter `XiangShan` directory, run:

```sh
cd 
make simv
```

Then run:

```sh
./simv
```

By default, simv uses `XiangShan/ram.bin` as input.

### Viewing and analyzing performance counters

When the workload execution ends, the performance counter results will be printed. If you redirect the content of performance counters to a file, you can use visualization tools to see structured performance counter information.
> Tip: before running `emu`, you can add the `--force-dump-result` parameter to force print performance counter results to standard output stream.

We provide a [tool to visualize the results of performance counters](https://github.com/OpenXiangShan/perfUI). The tool has a GUI interface, if you want to use it, please do X11 forwarding related configuration.