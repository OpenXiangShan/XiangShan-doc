Checkpoint 的生成和运行
=====================
## 使用 NEMU 生成 Simpoint Checkpoint

!!! note
    Checkpoint 相关的功能目前使用 NEMU 的 master 分支。之前使用的 tracing 和 cpt-bk 分支虽然也支持simpoint profiling和checkpoint，但是我们不再进行维护、修复bug或提供任何支持。

### 背景介绍

Simpoint Checkpoint 会根据程序特性找到具有代表性的检查点。如果您对 Simpoint Checkpoint 不了解，推荐以下论文、视频和笔记。

- [SimPoint's paper](http://www-cse.ucsd.edu/~calder/papers/ASPLOS-02-SimPoint.pdf)
- [Checkpoint + Sampling：10 小时内估算出 RISC-V CPU 的 SPEC 分数](https://www.bilibili.com/video/BV1eb4y167cE)
- [关于SimPoint的一些笔记](https://zhuanlan.zhihu.com/p/380561873)

需要注意的是 SimPoint 不是香山团队发明的，是 UCSD 发明的。
我们只是提出了一套 RISC-V 的基础设施来使得 checkpoint 可以跨平台使用。
因此关于 SimPoint 原理性的问题建议读论文，不建议发 issue。

### 环境准备

关于 NEMU 的基本使用方式，可以参考 [NEMU 的使用指南](https://github.com/OpenXiangShan/NEMU/tree/master/README.md)

#### [NEMU (master 分支)](https://github.com/OpenXiangShan/NEMU/tree/master)

1. 设置环境变量 `export NEMU_HOME=/path/to/NEMU`
1. 在 `$NEMU_HOME` 目录下使用 `git submodule update --init` 下载同步 NEMU 的 submodule
2. 在 `$NEMU_HOME/resource/simpoint/simpoint_repo` 目录下执行 `make`，得到可执行文件 `NEMU/resource/simpoint/simpoint_repo/bin/simpoint`
2. 在 `$NEMU_HOME` 目录下使用 `make riscv64-xs-cpt_defconfig` 配置NEMU，然后使用 `make menuconfig` 按需调整配置选项，最后使用 `make -j` 生成NEMU的可执行文件
3. 在 `$NEMU_HOME/resource/gcpt_restore` 目录下执行 `make` 命令编译，得到`gcpt.bin`

#### workload 的生成

!!! note
    因为 checkpoint 的原理，我们不建议在 M 态下生成 checkpoint ([Issue #54](https://github.com/OpenXiangShan/NEMU/issues/54))，如果您一定要在 M 态生成 checkpoint，我们不会提供任何支持。

在 S 态或 U 态下运行 workload，比如 Linux 上运行 SPEC2006。构建的方法可以参考 [Linux Kernel with RISCV-pk for XiangShan in EMU](linux-kernel-for-xs.md) 或 [Linux Kernel with OpenSBI for XiangShan in EMU](opensbi-kernel-for-xs.md)

如果参考了[Linux Kernel with OpenSBI for XiangShan in EMU](opensbi-kernel-for-xs.md)文档，请将 NEMU 切换至 gcpt_new_mem_layout 分支

NEMU 生成 checkpoint 时，需要添加一段恢复程序 `gcpt.bin`，在 `(0x80000000, 0x100000)`。因此在生成 workload 时，需要避开这一段空间，将起始地址设置在 `0x80100000` 。如在 [riscv-pk/bbl/bbl.lds](https://github.com/OpenXiangShan/riscv-pk/blob/noop/bbl/bbl.lds#L15) 中，修改为 `. = MEM_START + 0x100000` 。

**NEMU 默认不会进入 checkpoint 模式**，需要使用 NEMU 自定义指令进行模式转换。

RTFSC: [nemu_trap](https://github.com/OpenXiangShan/NEMU/blob/54894f558d61a5833260f1f158452d24ea6237c1/src/isa/riscv64/instr/special.h#L36)
具体如下：

1. NEMU 使用 nemu_trap 指令（0x6b），进行 `结束运行`，`关闭时钟中断`，`进入 Simpoint Profiling 模式` ，具体行为由 `a0` 寄存器内容决定。
2. a0：0x100 - 关闭时钟中断
3. a0：0x101 - 进入 Simpoint Profiling 模式
4. a0：其他  - NEMU 结束执行，返回 a0 内容。若 a0 内容为 0，NEMU 认为程序 GOOD_TRAP。

因此在真正执行目标程序之前，需要完成两个操作 *关闭时钟中断* 和 *进入 Simpoint Profiling 模式*。可以将如下程序编译后，在运行目标程序之前执行，以完成上述两个操作。在目标程序结束后，可以执行 GOOD_TRAP 。

```c
#define DISABLE_TIME_INTR 0x100
#define NOTIFY_PROFILER 0x101
#define GOOD_TRAP 0x0

void nemu_signal(int a){
    asm volatile ("mv a0, %0\n\t"
                  ".insn r 0x6B, 0, 0, x0, x0, x0\n\t"
                  :
                  : "r"(a)
                  : "a0");
}

int main(){
    nemu_signal(DISABLE_TIME_INTR);
    nemu_signal(NOTIFY_PROFILER);
}
```

### 生成SimPoint checkpoint
#### 流程介绍

生成 Simpoint Checkpoint 分三步：

1. Profiling 采样，执行一轮 workload，收集程序行为信息
2. Cluster 聚类，得到权重最高的多个程序片段（节点）
3. Checkpointing 生成，再执行一轮 workload，根据聚类的结果生成对应的 Checkpoint

#### 命令

RTFSC：[NEMU 的参数](https://github.com/OpenXiangShan/NEMU/blob/54894f558d61a5833260f1f158452d24ea6237c1/src/monitor/monitor.c#L232)

NEMU Checkpoint 部分相关参数介绍，具体请RTFSC：

1. `-b`：以 `batch` 模式运行（省略的话，会在启动 NEMU 后暂停等待输入命令）
2. `-D`：生成 Checkpoint 的工作根目录，会自动创建指定目录，可以任取，例如`-D simpoint_checkpoint`
3. `-C`：描述任务的名字（上节三步流程的 Profiling 和 Cluster 等），可以任取，例如`-C profiling`
4. `-w`：workload 的名字，可以任取，例如`-w bbl`
5. `--simpoint-profile`：进行 SimPoint Profiling，用于 Profiling 环节
6. `--cpt-interval`：用于 Profiling 环节：采样的区间大小，以指令数为单位, 用于 Checkpoint 环节：设置 Checkpoint 的区间，需和 profiling 过程中的 `--cpt-interval` 参数保持一致。
7. `-S`：指定 Cluster 环节的结果，用于 Checkpointing 环节
8. `--checkpoint-format`：支持选择 `gz` 或者 `zstd` 两种格式生成checkpoint，如果不指定该参数，默认使用 `gz` 格式。
9. `-r`: 指定 GCPT 恢复程序的二进制文件 `gcpt.bin` 路径。指定路径后，NEMU 会将恢复程序与用户指定的 Workload 合并为一个统一的 Workload 运行。具体来说，恢复程序将被加载至 `0x80000000`， `(0x80000000, 0x100000)` 将用于存放恢复程序及 Checkpoint 环节保存的体系结构状态，用户指定的 Workload 则会被加载至 `0x80100000`。

SimPoint 的参数请RTFSC [SimPoint Repo](https://github.com/shinezyy/SimPoint.3.2-fix/tree/e51a936d7fddfa03c81692039f184ab6c437e99e)

!!! note
    结合 `-D -C -w` 三个参数，最终会获得 `simpoint_checkpoint/profiling/bbl/` 这样的目录结构，此外必须指定`-D`, `-C`, `-w`参数，否则运行时会报错。<br>
    如果未提前将恢复程序与 Workload 链接在一起（链接方法详见 [Linux Kernel with OpenSBI for XiangShan in EMU](opensbi-kernel-for-xs.md#2-linux-spec2006-simpoint-profiling-checkpoint-workload)），则必须指定 `-r` 参数。否则，保存的 Checkpoint 将不包含恢复程序，无法正常使用。

命令示例（均默认使用 gz 格式，如需使用 zstd 格式，请自行修改命令）：

```shell
#!/bin/bash

# prepare env

export NEMU_HOME=
export NEMU=$NEMU_HOME/build/riscv64-nemu-interpreter
export GCPT=$NEMU_HOME/resource/gcpt_restore/build/gcpt.bin
export SIMPOINT=$NEMU_HOME/resource/simpoint/simpoint_repo/bin/simpoint

export WORKLOAD_ROOT_PATH=
export LOG_PATH=$NEMU_HOME/checkpoint_example_result/logs
export RESULT=$NEMU_HOME/checkpoint_example_result
export profiling_result_name=simpoint-profiling
export PROFILING_RES=$RESULT/$profiling_result_name
export interval=$((20*1000*1000))

# Profiling

profiling(){
    set -x
    workload=$1
    log=$LOG_PATH/profiling_logs
    mkdir -p $log

    $NEMU ${WORKLOAD_ROOT_PATH}/${workload}.bin \
        -D $RESULT -w $workload -C $profiling_result_name    \
        -b --simpoint-profile --cpt-interval ${interval}            \
        -r $GCPT > $log/${workload}-out.txt 2>${log}/${workload}-err.txt
}

export -f profiling

profiling bbl

# Cluster


cluster(){
    set -x
    workload=$1

    export CLUSTER=$RESULT/cluster/${workload}
    mkdir -p $CLUSTER

    random1=`head -20 /dev/urandom | cksum | cut -c 1-6`
    random2=`head -20 /dev/urandom | cksum | cut -c 1-6`

    log=$LOG_PATH/cluster_logs/cluster
    mkdir -p $log

    $SIMPOINT \
        -loadFVFile $PROFILING_RES/${workload}/simpoint_bbv.gz \
        -saveSimpoints $CLUSTER/simpoints0 -saveSimpointWeights $CLUSTER/weights0 \
        -inputVectorsGzipped -maxK 30 -numInitSeeds 2 -iters 1000 -seedkm ${random1} -seedproj ${random2} \
        > $log/${workload}-out.txt 2> $log/${workload}-err.txt
}

export -f cluster

cluster bbl

# Checkpointing

checkpoint(){
    set -x
    workload=$1

    export CLUSTER=$RESULT/cluster
    log=$LOG_PATH/checkpoint_logs
    mkdir -p $log
    $NEMU ${WORKLOAD_ROOT_PATH}/${workload}.bin  \
         -D $RESULT -w ${workload} -C spec-cpt   \
         -b -S $CLUSTER --cpt-interval $interval \
         -r $GCPT > $log/${workload}-out.txt 2>$log/${workload}-err.txt 
}

export -f checkpoint

checkpoint bbl

```

## 使用 NEMU 生成 Uniform Checkpoint

Uniform Checkpoint 为均匀生成的检查点，每隔 interval 条指令记录一个。

[NEMU (Master 分支)](https://github.com/OpenXiangShan/NEMU) 支持 Uniform Checkpoint 的生成。

命令示例：

```
#!/bin/bash

# prepare env

export NEMU_HOME=
export NEMU=$NEMU_HOME/build/riscv64-nemu-interpreter
export GCPT=$NEMU_HOME/resource/gcpt_restore/build/gcpt.bin
export SIMPOINT=$NEMU_HOME/resource/simpoint/simpoint_repo/bin/simpoint

export WORKLOAD_ROOT_PATH=
export LOG_PATH=$NEMU_HOME/checkpoint_example_result/logs
export RESULT=$NEMU_HOME/checkpoint_example_result
export profiling_result_name=simpoint-profiling
export PROFILING_RES=$RESULT/$profiling_result_name
export interval=$((20*1000*1000))

uniform_cpt(){
    set -x
    workload=$1
    log=$LOG_PATH/uniform
    mkdir -p $log
    name="uniform"

    $NEMU ${WORKLOAD_ROOT_PATH}/${workload}.bin                   \
        -D $RESULT -w $workload -C $name                          \
        -b -u --cpt-interval ${interval} --dont-skip-boot         \
        -r $GCPT > $log/${workload}-out.txt 2>${log}/${workload}-err.txt
}

export -f uniform_cpt

uniform_cpt bbl

```

## 使用 NEMU 生成 Manual Uniform Checkpoint 和 Manual Oneshot Checkpoint

Manual oneshot checkpoint 在用户按下 ctrl-c 后马上生成一个 checkpoint，Manual uniform checkpoint 在用户按下 ctrl-c 后生成均匀的间隔为 interval 的 checkpoint。但是要注意的是，这两种方法不能在脚本中运行，并且生成 checkpoint 之后只能通过 kill 进程的方式来结束 NEMU 的运行。

[NEMU (Master 分支)](https://github.com/OpenXiangShan/NEMU) 支持 Manual oneshot checkpoint 和 Manual uniform checkpoint 生成。

```
#!/bin/bash

# prepare env

export NEMU_HOME=
export NEMU=$NEMU_HOME/build/riscv64-nemu-interpreter
export GCPT=$NEMU_HOME/resource/gcpt_restore/build/gcpt.bin
export SIMPOINT=$NEMU_HOME/resource/simpoint/simpoint_repo/bin/simpoint

export WORKLOAD_ROOT_PATH=
export LOG_PATH=$NEMU_HOME/checkpoint_example_result/logs
export RESULT=$NEMU_HOME/checkpoint_example_result
export profiling_result_name=simpoint-profiling
export PROFILING_RES=$RESULT/$profiling_result_name
export interval=$((20*1000*1000))

# Manual oneshot checkpoint
manual_oneshot_cpt(){
    set -x
    workload=$1
    log=$LOG_PATH/manual_oneshot/${workload}
    mkdir -p $log

    name="manual_oneshot"

    $NEMU ${WORKLOAD_ROOT_PATH}/${workload}-bbl-linux-spec.bin \
        -D $RESULT -w $workload -C $name      \
        -b --cpt-interval ${interval}            \
        --manual-oneshot-cpt \
        -r $GCPT > $log/${workload}-out.txt 2>${log}/${workload}-err.txt

}

# Manual uniform checkpoint
manual_uniform_cpt(){
    set -x
    workload=$1
    log=$LOG_PATH/manual_uniform
    mkdir -p $log
    name="manual_uniform"

    $NEMU ${WORKLOAD_ROOT_PATH}/${workload}-bbl-linux-spec.bin \
        -D $RESULT -w $workload -C $name      \
        -b --cpt-interval ${interval}            \
        --manual-uniform-cpt \
        -r $GCPT > $log/${workload}-out.txt 2>${log}/${workload}-err.txt

}

```

## Checkpoint 的运行

- NEMU 运行检查点：

    ```shell
    ./build/riscv64-nemu-interpreter -b --restore $TARGET_CPT_GZ
    ```

  - 如果在打印寄存器前报错`CONFIG_MEM_COMPRESS is disabled, turn it on in menuconfig!`

    请在`make menuconfig`中选择`Memory Configuration -> Initialize the memory with a compressed gz file`，按 Y 键加入此功能，然后 Save 配置，重新 `make` 编译运行即可。


- 香山仿真运行检查点：

  - Checkpoint 生成的 gz/zstd 文件可以通过 gcpt_restore 恢复到内存中运行，可参考[香山仿真流程](./xsenv.md#生成香山核的仿真程序)

    ```shell
    ./build/emu -i $TARGET_CPT_GZ
    ```

## 性能分析

### Warm-Up

处理器中的 Cache、MMU、分支预测器的冷启动会影响性能评估的准确性，因此需要进行 Warm-Up，对 Cache、MMU、分支预测器进行数据预热。
具体实现方式为提前多执行 W (Warmup length) 条指令，例如：一个预期的 Checkpoint，时间节点为 N，采样区间长度(cpt-interval的参数)为I，预热长度为 W。真正生成的 Checkpoint 节点为 N-W，处理器执行时，需要执行 (N-W，N+I) ，
即 W+I 条指令。收集性能数据时需要舍去 (N-M, N) 部分，只收集 （N，N+I）部分的性能数据。
需要注意的是，我们默认设置了W=I，当I=50*10**6，这是合理的。如果需要改变interval，W需要改源码额外调整。

### 数据汇总

NEMU 执行 workload 的结尾，会打印出执行的指令数。
一个 workload 的每个 Checkpoint 有各自的权重，以及统一的区间（以指令为单位）。处理器如香山，执行每一段 Checkpoint ，会有各自的周期数。
通过所有 Checkpoint 的权重，区间和周期数，以及 workload 的总指令数，就能得到处理器执行 workload 的总周期数。结合处理器的时钟频率，可以得到估算的执行时间。

## 注意事项

在使用 NEMU 生成 Checkpoint 之前，推荐先正常执行一遍 workload，确认：

1. workload 本身是正确的
2. NEMU 可以正常执行 workload

PS：如果您对 Checkpoint 生成流程有疑问，欢迎在 [Issues · OpenXiangShan/XiangShan-doc (github.com)](https://github.com/OpenXiangShan/XiangShan-doc/issues) 进行讨论。

本文档所给出的示例脚本可能并不会随NEMU主线的更新而更新，因此如果出现任何问题，请查看 [NEMU中的example](https://github.com/OpenXiangShan/NEMU/tree/master/scripts/checkpoint_example) ，如果 [NEMU中的example](https://github.com/OpenXiangShan/NEMU/tree/master/scripts/checkpoint_example) 出现任何问题，欢迎在 [Issues · OpenXiangShan/NEMU (github.com)](https://github.com/OpenXiangShan/NEMU/issues) 进行讨论。
