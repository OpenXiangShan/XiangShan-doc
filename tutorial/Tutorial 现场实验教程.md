# Tutorial 现场实验教程

<font color=#FF0000>注意：本教程为 2021.6.25 日下午 RVWC 香山 Session 中 Tutorial 部分所使用的原始教程，其中的内容依赖于现场云服务器中的文件镜像，因此流程仅作为参考，更多信息请参考后续文档。</font>

在本 Tutorial 教程中，我们将给大家介绍如何编译和仿真香山代码、如何生成可运行的 Workload，并带大家体验我们敏捷开发和调试香山核的过程中所使用到的一些工具。
​

## 一、初始环境准备


使用 SSH 登录服务器，服务器信息将在现场提供。（如果有条件，登录时推荐开启 X11 转发）

首先在外挂硬盘 /mnt 下新建一个自己的目录作为本次 Tutorial 的工作目录：
注意！请将下方命令中的 “INPUT_YOUR_NAME” 替换成你喜欢的名字，尤其避免重名。

```shell
export MY_DIRNAME=INPUT_YOUR_NAME 
cd /mnt
mkdir $MY_DIRNAME
```


大家可以在 `/home/xs` 目录下看到一些项目文件夹，这是为了节省大家时间，预先从 github 克隆下来了；请大家将该目录下的所有项目都复制一份到自己的工作目录：


```shell
cp -r /home/xs/* /mnt/$MY_DIRNAME/
```


执行 `ls /mnt/$MY_DIRNAME` 确认其中拥有以下的一些目录：


```
XiangShan    NEMU    nexus-am    misc    workloads
```


配置环境变量：
```shell
source /mnt/$MY_DIRNAME/misc/env.sh
```


上述命令其实等价于执行的脚本内容如下：

```shell
export NOOP_HOME=/mnt/$MY_DIRNAME/XiangShan
export NEMU_HOME=/mnt/$MY_DIRNAME/NEMU
export AM_HOME=/mnt/$MY_DIRNAME/nexus-am
```


接下来我们需要安装一些依赖的软件包，不过在当前云服务器环境中已经帮大家装好了，后续我们将会给出一份依赖的软件包列表与 Docker 镜像。


所有的机器已经预先配置了代理，如果遇到因网络问题造成的卡顿，请在命令前添加 `proxychains4`

比如  `make init`  改成  `proxychains4 make init`




## 二、生成香山核的 Verilog 代码


在 `/mnt/$MY_DIRNAME/XiangShan` 下执行 
```shell
make init
```
该命令会将一些必要的 submodule 克隆下来。



### 1. 生成单核代码


运行 `make verilog` ，该命令将会编译香山的 Chisel 代码，生成 Verilog，输出的文件在 `XiangShan/build/XSTop.v`



### 2. 生成双核代码

运行 `make SIM_ARGS="--dual-core" verilog` ，该命令将会生成香山双核的 Verilog，输出的文件在 `XiangShan/build/XSTop.v`
​

## 三、仿真环境下验证香山

<font color=#FF0000>注意！生成 Verilog 所需的时间会稍久，推荐大家先挂在后台，然后新开一个 Shell 窗口重新登录服务器用于后续的所有内容，并在其中重新配置环境变量，如下：</font>

```shell
export MY_DIRNAME=INPUT_YOUR_NAME
source /mnt/$MY_DIRNAME/misc/env.sh
```



### 1. 生成香山核的仿真程序

我们使用 Verilator 生成香山核的仿真程序，进入 `XiangShan` 目录，运行命令
```bash
make emu CONFIG=MinimalConfig SIM_ARGS=--disable-log EMU_TRACE=1 -j32
```
将会生成一个最小配置的香山的仿真程序，这一步时间会比较久，需要耐心等待。生成结束后，可以在 `./build/` 目录下看到一个名为 `emu` 的仿真程序。<font color=#FF0000>注意！ 这一步会消耗大量的运算资源，尤其多人编译会占用服务器资源，降低服务器使用体验，因此推荐使用我们预先编译好的 `emu` 继续后面的流程，位于 `/mnt/$MY_DIRNAME/misc/emu-prebuilt` </font>


您可以将预先编译好的 `emu-prebuilt` 复制到 `XiangShan/build` 目录下. 之后的操作与现场编译 `emu` 时的操作相同。
```bash
cp /mnt/$MY_DIRNAME/misc/emu-prebuilt /mnt/$MY_DIRNAME/XiangShan/build/emu
```



### 2. 使用 AM 的环境生成 workload

进入 `/mnt/$MY_DIRNAME/nexus-am/apps` 目录，可以看到在该目录下有一些预置的 workload，以 coremark 为例，进入`/mnt/$MY_DIRNAME/nexus-am/apps/coremark`，执行 `make ARCH=riscv64-xs -j8`，即可在当前 `build` 目录下看到 3 个文件：


```shell
coremark-riscv64-xs.elf  应用程序的 ELF 文件
coremark-riscv64-xs.bin  应用程序的二进制运行镜像
coremark-riscv64-xs.txt  应用程序的反汇编
```

另外，在 `/mnt/$MY_DIRNAME/workloads` 目录下我们还提供了一些预先编译好的其他 workload，比如 Linux Kernel 等。
​

### 3. 使用 NEMU 模拟器运行 workload
进入 `/mnt/$MY_DIRNAME/NEMU` 目录，运行 `make ISA=riscv64 XIANGSHAN=1 -j` 编译 NEMU 模拟器，其中 `XIANGSHAN=1` 参数的作用是将模拟器的外设与香山处理器对齐。


接下来运行 `./build/riscv64-nemu-interpreter -b MY_WORKLOAD.bin` 其中将 `MY_WORKLOAD.bin` 替换为想要运行镜像的路径，例如上一节中生成的 coremark，即可让 NEMU 模拟器运行指定的程序了。
​

运行 `make ISA=riscv64 XIANGSHAN=1 SHARE=1 -j` 命令编译 NEMU 模拟器动态链接库，将会在 `build` 目录下生成文件 `riscv64-nemu-interpreter-so`，用作后续香山的差分测试。
​

### 4. 在香山核上仿真运行 workload
利用前面生成好的香山仿真程序，NEMU 动态链接库与 workload，可以默认在差分测试框架打开的情况下让香山核运行指定的应用程序，进入`/mnt/$MY_DIRNAME/XiangShan` 目录运行指令 `./build/emu -i MY_WORKLOAD.bin`  其中将 `MY_WORKLOAD.bin` 替换为想要运行镜像的路径，比如前面生成的 coremark，即可让香山仿真运行指定的程序了。
​

### 5. 生成波形
我们可以使用 `--dump-wave` 参数打开波形，并使用 `-b` 和 `-e` 参数设置生成波形的开始和结束周期，例如想要生成 10000 ~ 11000 周期的波形，可以使用如下命令：
```shell
./build/emu -i MY_WORKLOAD.bin --dump-wave -b 10000 -e 11000
```

其中 `-b` 和 `-e` 的默认值为 0，注意仅当 `-e` 参数大于 `-b` 时才会真正记录波形；波形文件将会生成在 `./build/` 目录下，格式为 vcd。波形文件可以后续使用 gtkwave 等开源工具或者 dve 等商业工具进行查看，这里不再进行展示。




### 6. 日志功能简介
如果编译 emu 时打开了打印日志的功能（前述流程默认关闭），那么在运行 emu 时，将会打印日志。为了避免在终端输出日志，占用终端 IO 带宽，导致终端卡死，请将终端输出重定向到文件中。使用如下命令：
`./build/emu -i MY_WORKLOAD.bin -b 10000 -e 11000 2>&1 | tee > MY_LOGNAME.log`
可以使用 LogViewer 工具查看日志，但在本 Tutorial 中略过。
​

### 7. 性能计数器的查看和分析
当 workload 执行结束后，将会打印性能计数器结果。如果将性能计数器的内容重定向到文件中，就可以使用可视化工具参看结构化的性能计数器信息。我们提供了一个 CI 上运行 Linux 的性能计数器的 Perf-log 作为范例，位置在 `/mnt/$MY_DIRNAME/misc/perf-tools/linux-perf.log`。
```bash
cd /mnt/$MY_DIRNAME/misc/perf-tools
./perfviewer
```
注意！该工具具有 GUI 界面，如果想要体验请做好 X11 转发相关配置。
Tips: 在运行 `emu` 时, 可以添加 `--force-dump-result` 参数来强制输出性能计数器结果到标准输出流.
​

### 8. 单元测试
单元测试 Agent-Faker 基于旧版 Verilator，API 与新版有出入，本次 Tutorial 暂不做展示。后续修复后我们将发布单元测试相关的详细文档。
​

## 四、如何为香山贡献
推荐在香山处理器的基础上进行修改，提交PR，通过CI验证之后可以merge到主分支。
我们随时欢迎您能指出香山处理器设计的不足或缺陷，更加欢迎提出香山处理器需要或者可以添加的优化技术。我们也欢迎您能对香山项目的验证测试环境提出新的想法，或者发现验证测试环境的不足之处。
我们会以可视的方法表现出您对开源香山处理器的贡献，但具体方式还在讨论中。
​

---------------------------------------------------------------
# 拓展项目：大家如果时间宽裕可以尝试
### 1. 尝试触发 Difftest 报错
故意修改错香山核中的代码，然后重新根据上述流程运行一些 workload，将会触发差分测试框架的报错并打印错误现场.
​

### 2. 试用 LightSSS
提供额外文档进行说明

 


### 3. 生成更多的 Workload
#### a. 使用 AM 生成自定义 workload
提供额外文档进行说明



#### b. 生成 Linux Kernel 作为 worload

提供额外文档进行说明，服务器中没有配置相关环境，会后可以自行尝试


### 4. Checkpoint的生成和运行
我们使用 NEMU 运行 workload 并生成 checkpoint，使用方式如下：
```shell
# 用NEMU进行simpoint profiling (以100M指令为周期)：
./build/riscv64-nemu-interpreter $BBL_FOR_GCC_200 --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C run_spec -b --simpoint-profile --interval 100000000

# 用NEMU均匀地生成checkpoints (以1 Billion指令为周期)：
./build/riscv64-nemu-interpreter $BBL_FOR_GCC_200 --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C run_spec -b --checkpoint-interval 1000000000

# 用NEMU同时均匀的生成checkpoint(1B)和进行simpoint profiling(100M)
./build/riscv64-nemu-interpreter $BBL_FOR_GCC_200 --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C run_spec -b --checkpoint-interval 1000000000 --simpoint-profile --interval 100000000
# !!请注意磁盘空间，取决于参数，可能占用几十~几千G

# NEMU生成的SimPoint profiling results和GEM5生成的完全一样，经过SimPoint clustering之后即可用于指导生成SimPoint checkpoints，我们假设clustering的结果在目录$POINTS_DIR
# 生成SimPoint checkpoints：
./build/riscv64-nemu-interpreter $BBL_FOR_GCC_200 --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C take_cpt -S $POINTS_DIR
# !!请注意磁盘空间，取决于参数，整个SPEC06可能占用几十~几百G

# 恢复一个checkpoint，假设checkpoint文件为$CPT_GZ
./build/riscv64-nemu-interpreter $BBL_FOR_GCC_200 --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C restore_cpt -c $CPT_GZ


```
参数说明：

- 注意，-C（大C）是描述任务的名字，可以随便填，NEMU会把结果存放在相应的文件夹里
- -w则对应-C下面一级的子目录
   - -C spec_run -w namd 对应的目录结构就是 spec_run/namd
- $SDCARD_IMG是打包好的Linux和应用，可以是SPEC，也可以是其它程序。
- $BBL_FOR_GCC_200 是让Linux启动后第一个程序执行gcc_200，通过BBL传参数给kernel（如果写死在SDCARD里面的话，每个应用需要一个SDCARD，非常大）
- SDCARD_IMG怎么生成？详见rootfs打包部分
