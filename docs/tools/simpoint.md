Checkpoint 的生成和运行
=====================
## 使用 NEMU 生成 Simpoint Checkpoint

!!! note
    Checkpoint 相关的功能目前依赖于独立的 NEMU 分支，主线上的 NEMU 并不支持 Checkpoint 生成。
    cpt-bk分支和tracing分支支持simpoint profiling和生成checkpoint。
    其中cpt-bk分支是旧版的，可能缺乏最新的bug修复和feature，例如profiling速度会比tracing慢10倍以上。
    对于cpt-bk分支的bug，我们不再进行修复。
    此外，tracing分支的API和cpt-bk分支略有修改，主要修改了一些有歧义的参数名称，我们在文档中进行了更新。

### 背景介绍

Simpoint Checkpoint 会根据程序特性找到具有代表性的检查点。如果您对 Simpoint Checkpoint 不了解，推荐以下论文、视频和笔记。

- [SimPoint's paper](http://www-cse.ucsd.edu/~calder/papers/ASPLOS-02-SimPoint.pdf)
- [Checkpoint + Sampling：10 小时内估算出 RISC-V CPU 的 SPEC 分数](https://www.bilibili.com/video/BV1eb4y167cE)
- [关于SimPoint的一些笔记](https://zhuanlan.zhihu.com/p/380561873)

需要注意的是SimPoint不是香山团队发明的，是UCSD发明的。
我们只是提出了一套RISC-V的基础设施来使得checkpoint可以跨平台使用。
因此关于SimPoint原理性的问题建议读论文，不建议发issue。

### 环境准备

关于 NEMU 的基本使用方式，可以参考 [NEMU 的使用指南](nemu.md)

#### [NEMU (cpt-bk/tracing 分支)](https://github.com/OpenXiangShan/NEMU/tree/cpt-bk)

1. NEMU 拥有一个 submodule `NEMU/resource/simpoint` ，使用 `git submodule update --init` 下载同步，并编译（`analysiscode` 目录下执行 `make simpoint` ），得到可执行文件 `NEMU/resource/simpoint/bin/simpoint`
2. 在 `NEMU/resource/gcpt_restore` 目录下执行 `make` 命令编译，得到`gcpt.bin`
3. cpt-bk分支：在 `NEMU` 目录下执行 `make ISA=riscv64 XIANGSHAN=1` 生成 NEMU 的可执行文件。
   tracing分支：在 `NEMU` 目录下执行 `make riscv64-xs-simpoint_defconfig; make menuconfig # --> Save; make -j` 生成 NEMU 的可执行文件。



#### workload 的生成

因为checkpoint的原理，我们不支持在 M 态下生成checkpoint([Issue #54](https://github.com/OpenXiangShan/NEMU/issues/54))，
因此 workload 需要运行在 S 态或 U 态下运行，比如 Linux 上运行 SPEC2006。构建的方法可以参考 [Linux Kernel for XiangShan in EMU](linux-kernel-for-xs.md) 。

NEMU 生成 checkpoint 时，需要添加一段恢复程序 `gcpt.bin`，在 `(0x80000000, 0xa0000)`。因此在生成 workload 时，需要避开这一段空间，将起始地址设置在 `0x800a0000` 。如在 [riscv-pk/bbl/bbl.lds](https://github.com/OpenXiangShan/riscv-pk/blob/noop/bbl/bbl.lds#L15) 中，修改为 `. = MEM_START + 0xa0000` 。

**NEMU 默认不会进入 checkpoint 模式**，需要使用 NEMU 自定义指令进行模式转换。

RTFSC: [nemu_trap](https://github.com/OpenXiangShan/NEMU/blob/cpt-bk/src/isa/riscv64/exec/special.c#L25)

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



### 流程介绍

生成 Simpoint Checkpoint 分三步：

1. Profiling 采样，执行一轮 workload，收集程序行为信息
2. Cluster 聚类，得到权重最高的多个程序片段（节点）
3. Checkpointing 生成，再执行一轮 workload，根据聚类的结果生成对应的 Checkpoint

### 执行命令

RTFSC：[NEMU 的参数](https://github.com/OpenXiangShan/NEMU/blob/cpt-bk/src/monitor/monitor.c#L178)

Checkpoint 相关参数介绍：

1. `-b`：以 `batch` 模式运行（省略的话，会在启动 NEMU 后暂停等待输入命令）
2. `-D`：生成 Checkpoint 的工作根目录，会自动创建指定目录，可以任取
3. `-C`：描述任务的名字（上节三步流程的 Profiling 和 Cluster 等），可以任取
4. `-w`：workload 的名字，可以任取
5. `--simpoint-profile`：进行 Profiling，用于 Profiling 环节
6. `--interval` in cpt-bk or `--cpt-interval` in tracing：采样的区间大小，以指令数为单位，用于 Profiling 环节
7. `-S`：指定 Cluster 环节的结果，用于 Checkpointing 环节
8. `--checkpoint-interval` in cpt-bk (merged into `--cpt-interval` in tracing)：
生成 Checkpoint，同时设置 Checkpoint 的区间，需和 “--interval” 参数保持一致，用于 Checkpointing 环节

必须指定`-D`, `-C`, `-w`，否则运行时会报错

命令示例：

```shell
# Assuming the dest dir is /home/user/spec_cpt

# Profiling
tracing branch:
./build/riscv64-nemu-interpreter $RISCV_PK_HOME/build/bbl.bin \
    -D /home/user/spec_cpt -w workloadName -C profiling       \
    -b --simpoint-profile --cpt-interval 100000000            \
    -r ./resource/gcpt_restore/build/gcpt.bin

cpt-bk branch:
./build/riscv64-nemu-interpreter $RISCV_PK_HOME/build/bbl.bin \
	-D /home/user/spec_cpt -w workloadName -C profiling \
	-b --simpoint-profile --interval 100000000

# Cluster
mkdir -p /home/user/spec_cpt/cluster/workloadName
export CLUSTER=/home/user/spec_cpt/cluster/workloadName
# --!!-- make sure the simpoint_bbv.gz is for your target workload --!!--
# or disable -DFLAT_CPTPATH in Makefile:CFLAGS to generate bbv.gz under dir profile/workloadName
./resource/simpoint/simpoint_repo/bin/simpoint                                  \
    -loadFVFile /home/user/spec_cpt/profiling/workloadName/simpoint_bbv.gz      \
    -saveSimpoints $CLUSTER/simpoints0 -saveSimpointWeights $CLUSTER/weights0   \
    -inputVectorsGzipped -maxK 30 -numInitSeeds 2 -iters 1000 -seedkm 123456 -seedproj 654321

# Checkpointing
tracing branch:
./build/riscv64-nemu-interpreter $RISCV_PK_HOME/build/bbl.bin  \
    -D /home/user/spec_cpt -w workloadName -C take_cpt         \
    -b -S /home/user/spec_cpt/cluster --cpt-interval 100000000 \
    -r ./resource/gcpt_restore/build/gcpt.bin

cpt-bk branch:
./build/riscv64-nemu-interpreter $RISCV_PK_HOME/build/bbl.bin \
	-D /home/user/spec_cpt -w workloadName -C take_cpt \
	-b -S /home/user/spec_cpt/cluster --checkpoint-interval 100000000

`-S /path/to/simpoints/` provides the path of selected simulation points

```

## 使用 NEMU 生成 Uniform Checkpoint

Uniform Checkpoint 为均匀生成的检查点，每隔 N 条指令记录一个。

[NEMU (Master 分支)]([OpenXiangShan/NEMU (github.com)](https://github.com/OpenXiangShan/NEMU)) 支持 Uniform Checkpoint 的生成。在仓库的 [README](https://github.com/OpenXiangShan/NEMU#prepare-workloads:~:text=2%2Diteration.bin-,Prepare%20workloads,-Link%20your%20bbl) 中介绍了使用方法。


## Checkpoint 的运行

- NEMU 运行检查点：

    ```shell
    ./build/riscv64-nemu-interpreter -b\
      --restore \
      $TARGET_CPT_GZ
    ```
  
  - 如果在打印寄存器前报错`CONFIG_MEM_COMPRESS is disabled, turn it on in menuconfig!`
  
    请在`make menuconfig`中选择`Memory Configuration -> Initialize the memory with a compressed gz file`，按 Y 键加入此功能，然后 Save 配置，重新 `make` 编译运行即可。


- 香山仿真运行检查点：

  - Checkpoint 生成的 gz 文件可以当成正常的 workload 使用，可参考[香山仿真流程](./xsenv.md#生成香山核的仿真程序)

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

PS：如果您对 Checkpoint 生成流程有疑问，欢迎在 [issue]([Issues · OpenXiangShan/NEMU (github.com)](https://github.com/OpenXiangShan/NEMU/issues)) 进行讨论。
