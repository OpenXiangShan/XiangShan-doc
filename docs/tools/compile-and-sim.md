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

1.通过`EMU_THREADS`指定emu仿真时要使用的线程数，例如`make emu EMU_THREADS=8`。
2.使用`numactl`让将emu运行时使用的核限制在一个node内，例如`numactl -m 0 -C 0-7 ./build/emu ...`
