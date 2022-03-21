Checkpoint的生成和运行
=====================

!!! note
    Checkpoint 相关的功能目前依赖于一个独立的 NEMU 分支。主线上的 NEMU 并不支持 Checkpoint生成。

## 背景介绍

如果您对 Checkpoint 不了解，推荐 zyy 大佬的视频：[Checkpoint + Sampling：10小时内估算出RISC-V CPU的SPEC分数](https://www.bilibili.com/video/BV1eb4y167cE)

## 使用 NEMU 生成 Checkpoint

### 环境准备

1. [NEMU (cpt-bk 分支)](https://github.com/OpenXiangShan/NEMU/tree/cpt-bk)
2. workload （非 可执行文件格式，需使用 objcopy 命令进行处理）

关于 NEMU 如何使用，以及如何生成 workload，请参考 NEMU 和香山的相关文档。

其他准备：

1. NEMU 拥有一个 submodule `NEMU/resource/simpoint` ，使用 `git submodule update --init` 下载同步，并编译（`analysiscode` 目录下执行 `make simpoint` ），得到可执行文件 `NEMU/resource/simpoint/bin/simpoint`
2. 在 `NEMU/resource/gcpt_restore` 目录下执行 `make` 命令编译

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
# Profiling
riscv64-nemu-interpreter workload.bin -D /home/user/spec_cpt -w workloadName -C run_spec -b --simpoint-profile --interval 100000000

# Cluster
simpoint -loadFVFile simpoint_bbv.gz -saveSimpoints simpoints0 -saveSimpointWeights weights0 -inputVectorsGzipped -maxK 30 -numInitSeeds 2 -iters 1000 -seedkm 123456 -seedproj 654321
# Assuming the dest dir is /home/user/spec_cpt/cluster

# Checkpointing
riscv64-nemu-interpreter workload.bin -D /home/user/spec_cpt -w workloadName -C take_cpt -b -S /home/user/spec_cpt/cluster --checkpoint-interval 100000000
```

### 其他注意事项

默认情况下，NEMU 不会进入 Checkpoint 模式，需要执行 NEMU 自定义指令进入 Checkpoint 模式。

RTFSC: [nemu_trap](https://github.com/OpenXiangShan/NEMU/blob/cpt-bk/src/isa/riscv64/exec/special.c#L25)

解析：

NEMU 使用 nemu_trap 指令（0x6b）表示程序执行结束 或 进行 Checkpoint 模式切换等行为，并根据 a0 寄存器进行判断。Profiling 时需要关闭时间中断，并打开 Simpoint Profiler；生成 Checkpoint 时，需要关闭时间中断。在执行 workload 之前（或者在 linux 环境下执行 workload 之前），需要执行相应的 nemu_trap 指令进行模式切换。

PS:
如果您对 Checkpoint 生成流程有疑问，欢迎提 issue 进行讨论。