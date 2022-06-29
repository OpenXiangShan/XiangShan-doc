Checkpoint 的生成和运行
=====================

!!! note
    Checkpoint 相关的功能目前依赖于一个独立的 NEMU 分支。主线上的 NEMU 并不支持 Checkpoint 生成。

## 背景介绍

如果您对 Checkpoint 不了解，推荐 zyy 大佬的视频：[Checkpoint + Sampling：10 小时内估算出 RISC-V CPU 的 SPEC 分数](https://www.bilibili.com/video/BV1eb4y167cE)

## 使用 NEMU 生成 Checkpoint

### 环境准备


关于 NEMU 的基本使用方式，可以参考 [NEMU 的使用指南](nemu.md)

#### [NEMU (cpt-bk 分支)](https://github.com/OpenXiangShan/NEMU/tree/cpt-bk)

1. NEMU 拥有一个 submodule `NEMU/resource/simpoint` ，使用 `git submodule update --init` 下载同步，并编译（`analysiscode` 目录下执行 `make simpoint` ），得到可执行文件 `NEMU/resource/simpoint/bin/simpoint`
2. 在 `NEMU/resource/gcpt_restore` 目录下执行 `make` 命令编译
3. 在 `NEMU` 目录下执行 `make ISA=riscv64 XIANGSHAN=1` 生成 NEMU 的可执行文件。

备注：NEMU 的 `cpt-bk` 分支还没有添加对 `menuconfig` 的支持，可以使用上面的命令进行编译。


#### workload 的生成

关于 workload 的生成方式，可以参考 [Linux Kernel for XiangShan in EMU](linux-kernel-for-xs.md) 和 [使用 AM 生成自定义 workload](gen-workload-with-am.md)

NEMU 生成 checkpoint 时，需要添加一段恢复程序 `gcpt.bin`，在 `(0x80000000, 0xa0000)`。因此在生成 workload 时，需要避开这一段空间，将起始地址设置在 `0x800a0000` 。如在 [riscv-pk/bbl/bbl.lds](https://github.com/OpenXiangShan/riscv-pk/blob/noop/bbl/bbl.lds#L15) 中，修改为 `. = MEM_START + 0xa0000` 。

NEMU 默认不会进入 checkpoint 模式，需要使用 NEMU 自定义指令进行模式转换。

RTFSC: [nemu_trap](https://github.com/OpenXiangShan/NEMU/blob/cpt-bk/src/isa/riscv64/exec/special.c#L25)

具体如下：

1. NEMU 使用 nemu_trap 指令（0x6b），进行 `结束运行`，`关闭时钟中断`，`进入 Simpoint Profiling 模式` ，具体行为由 `a0` 寄存器内容决定。
2. a0：0x100 - 关闭时钟中断
3. a0：0x101 - 进入 Simpoint Profiling 模式
4. a0：其他  - NEMU 结束执行，返回 a0 内容。若 a0 内容为 0，NEMU 认为程序 GOOD_TRAP。

因此在真正执行目标程序之前，需要完成两个操作 *关闭时钟中断* 和 *进入 Simpoint Profiling 模式*。

NEMU 目前不支持在 M 态下进行 Profiling，因此 workload 需要运行在 S 态或 U 态下运行，比如 linux 上运行 SPEC2006。

### 流程介绍

生成 Simpoint Checkpoint 分三步：

1. Profiling 采样，执行一轮 workload，收集程序行为信息
2. Cluster 聚类，得到权重最高的多个程序片段（节点）
3. Checkpointing 生成，再执行一轮 workload，根据聚类的结果生成对应的 Checkpoint

### 执行命令

RTFSC：[NEMU 的参数](https://github.com/OpenXiangShan/NEMU/blob/cpt-bk/src/monitor/monitor.c#L178)

Checkpoint 相关参数介绍：

1. `-D`：生成 Checkpoint 的工作根目录，会自动创建指定目录，可以任取
2. `-C`：描述任务的名字（上节三步流程的 Profiling 和 Cluster 等），可以任取
3. `-w`：workload 的名字，可以任取
4. `--simpoint-profile`：进行 Profiling，用于 Profiling 环节
5. `--interval`：采样的区间大小，以指令数为单位，用于 Profiling 环节
6. `-S`：指定 Cluster 环节的结果，用于 Checkpointing 环节
7. `--checkpoint-interval`：生成 Checkpoint，同时设置 Checkpoint 的区间，需和 “--interval” 参数保持一致，用于 Checkpointing 环节

命令示例：

```shell
# Assuming the dest dir is /home/user/spec_cpt

# Profiling
riscv64-nemu-interpreter workload.bin -D /home/user/spec_cpt -w workloadName -C profiling -b --simpoint-profile --interval 100000000

# Cluster
mkdir -p /home/user/spec_cpt/cluster/workloadName
# Run this command under /home/user/spec_cpt/cluster/workloadName
# --!!-- make sure the simpoint_bbv.gz is for your target workload --!!--
simpoint -loadFVFile ../../simpoint_bbv.gz -saveSimpoints simpoints0 -saveSimpointWeights weights0 -inputVectorsGzipped -maxK 30 -numInitSeeds 2 -iters 1000 -seedkm 123456 -seedproj 654321

# Checkpointing
riscv64-nemu-interpreter workload.bin -D /home/user/spec_cpt -w workloadName -C take_cpt -b -S /home/user/spec_cpt/cluster --checkpoint-interval 100000000
```

## 性能分析

### Warm-Up

处理器中的 Cache、MMU、分支预测器的冷启动会影响性能评估的准确性，因此需要进行 Warm-Up，对 Cache、MMU、分支预测器进行数据预热。具体实现方式为提前多执行一个 “区间” 的指令，例如：一个预期的 Checkpoint，时间节点为 N，区间长度为 M。真正生成的 Checkpoint 节点为 N-M，处理器执行时，需要执行（N-M，N+M），即 2M 条指令。收集性能数据时需要舍去 (N-M, N) 部分，只收集 （N，N+M）部分的性能数据。

### 数据汇总
NEMU 执行 workload 的结尾，会打印出执行的指令数。
一个 workload 的每个 Checkpoint 有各自的权重，以及统一的区间（以指令为单位）。处理器如香山，执行每一段 Checkpoint ，会有各自的周期数。通过所有 Checkpoint 的权重，区间和周期数，以及 workload 的总指令数，就能得到处理器执行 workload 的总周期数。结合处理器的时钟频率，可以得到实际执行时间。

## 注意事项

在使用 NEMU 生成 Checkpoint 之前，推荐先正常执行一遍 workload，确认：

1. workload 本身是正确的
2. NEMU 可以正常执行 workload


PS:
如果您对 Checkpoint 生成流程有疑问，欢迎提 issue 进行讨论。
