# 香山核RTL仿真流程

1. Chisel 生成 Verilog
2. Verilator/VCS 将生成的Verilog转换为C++源文件
3. 编译仿真器生成的C++源码得到elf格式可执行程序(emu)
4. 使用emu运行workload

## 加快Chisel->Verilog编译速度

1.更换JVM

我们推荐使用`GraalVM`代替`OpenJDK`，使用`GraalVM`免费版作为JVM编译香山比`OpenJDK`快10%-20%。

具体安装方式请参考[https://www.graalvm.org/docs/getting-started/](https://www.graalvm.org/docs/getting-started/)。

2.使用CIRCT (*测试阶段*) 编译香山

相比使用默认的scala firrtl complier，使用CIRCT能够将香山代码编译到Verilog的速度提高50%左右。

要使用CIRCT编译Chisel代码，可以参考以下步骤进行配置:

* 在本地从源码编译[CIRCT](https://github.com/llvm/circt)，在编译完成后将`circt/bin`路径加入`PATH`中。
* 在执行make命令时加上`MFC=1`，例如`make verilog MFC=1`或`make emu MFC=1`。

## 加快Verilator生成的C++源文件到emu的编译速度

Verilator会将Chisel生成的Verilog源码转换为数百/千个C++源文件，为了加快这些文件的编译速度，推荐使用核数多的处理器进行编译，
使用`make emu -jN`指定核数N，可以提高编译并行度。

## 加快emu仿真运行速度

1. 通过`EMU_THREADS`指定emu仿真时要使用的线程数，例如`make emu EMU_THREADS=8`。

2. 使用`numactl`将emu运行时使用的核限制在一个node内，例如`numactl -m 0 -C 0-7 ./build/emu ...`

3. 对 Verilator 编译的 C++ 代码使用 Profile Guided Optimization (PGO)

    我们提供了以下参数进行 PGO :

    - `PGO_WORKLOAD`: 用于指定 PGO 的工作负载，例如 <code>PGO_WORKLOAD=\`realpath ready-to-run/coremark-2-iteration.bin\`</code>。
    - `PGO_MAX_CYCLE`: 仿真器运行 PGO 的最大周期数，默认值为 `2000000` 。
    - `PGO_EMU_ARGS`: 指定 PGO 运行时的参数，例如担心 CPU 存在 Bug 影响 PGO 执行可以指定 `PGO_EMU_ARGS='--no-diff'` 。
    - `LLVM_PROFDATA`: 指定 llvm-profdata 版本，通常情况下传递 `LLVM_PROFDATA=llvm-profdata` 即可。 

    使用举例：

    ```bash
    make emu EMU_THREADS=8 \
             PGO_WORKLOAD=`realpath ready-to-run/coremark-2-iteration.bin` \
             LLVM_PROFDATA=llvm-profdata \
             -j `nproc`
    ``` 

    !!! warning
        若在 Debian / Ubuntu 中安装了不同版本的 clang 与 llvm 时，需将 `LLVM_PROFDATA` 指定为对应版本。例如 Verilator 使用了 clang-18 ，则相应地需要指定 `LLVM_PROFDATA=llvm-profdata-18` 。使用 `GCC` 编译 Verilator 生成的 C 文件时请将该参数留空，否则将因为找不到 LLVM 生成的 Profile 文件而导致报错。

    !!! info
        对于已经完成编译的 emu ，开启 PGO 不需要 `make clean`，这会导致 Chisel 的重新编译以及 Verilator 重新生成 C 代码，仅需 <code>make -C ./difftest clean_obj DESIGN_DIR=\`pwd\`</code> ，再重新执行上述的 `make emu PGO...` 即可，在大多数机器上可在 15 分钟内完成。
    
    !!! info
        部份编译器特性可能导致 O3 + PGO + Verilator 生成的 C 代码编译非常缓慢，已知 LLVM-18 存在，可以尝试指定 `OPT_FAST=-O1` 编译，通常性能损失不多，依然会比非 PGO 的 O3 快上不少。例如：
        ```bash
        make emu EMU_THREADS=8 OPT_FAST=-O1 \
                 PGO_WORKLOAD=`realpath ready-to-run/coremark-2-iteration.bin` \
                 LLVM_PROFDATA=llvm-profdata \
                 -j `nproc`
        ``` 

    PGO 通常能让仿真速度在 L3 Cache 足够的情况下提升 2 倍左右，经过测试在使用香山`commit 9810c04`，在 AMD 7950X3D + LLVM-14 平台上 8 线程 Verilator 使用 CoreMark 训练 PGO，后续使用 numactl 绑定到具有 96M L3 Cache 的 CCX ，运行 CoreMark 测试可以达到约 9K Cycles/s 的仿真速度，而不使用 PGO 只有约 4K Cycles/s。