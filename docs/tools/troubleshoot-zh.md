Troubleshooting 指南
================

This chapter has [English version](./troubleshoot.md).

* 编译和仿真香山代码需要耗费大量内存，请确保设备具有足够的内存。对于 MinimalConfig 选项，我们推荐内存至少为 32GB；对于完整的香山核，推荐内存至少为 64GB。（参见：[https://github.com/OpenXiangShan/XiangShan/issues/995](https://github.com/OpenXiangShan/XiangShan/issues/995)）
    * 改变 swap 区的大小可能有所帮助。（参见：[https://github.com/OpenXiangShan/XiangShan/issues/852](https://github.com/OpenXiangShan/XiangShan/issues/852)）
* 香山需要 Java 11 或更高的版本，请确认 Java 的版本。我们已经了解到香山在 Java 8 环境下无法正常工作。
    * 我们推荐使用 graalvm 代替 openjdk 以降低内存消耗，同时提高编译速度。（参见：[https://github.com/OpenXiangShan/XiangShan/issues/997](https://github.com/OpenXiangShan/XiangShan/issues/997)）
* 在 `XiangShan/build.sc`中的 `-Xmx64G` 可能影响香山的编译过程，请检查 JVM 的参数。（参见：[https://github.com/OpenXiangShan/XiangShan/issues/906](https://github.com/OpenXiangShan/XiangShan/issues/906)）
* 基于仿真 snapshot 的 fork-wait 需要 Verilator v4.204 版本，请确认 Verilator 的版本。我们不建议使用通过 `apt get` 方式安装 Verilator，这样得到的版本很低。手动安装 Verilator 可以参考 [https://github.com/OpenXiangShan/xs-env/blob/master/install-verilator.sh](https://github.com/OpenXiangShan/xs-env/blob/master/install-verilator.sh) (v4.204) 或官方教程 [https://verilator.org/guide/latest/install.html](https://verilator.org/guide/latest/install.html)。
* 请检查子模块是否已经正确初始化，如果遇到来自于香山本身或者其子模块的奇怪的语法错误，有可能是因为子模块并没有被正确初始化。可以尝试通过在 `Xiangshan` 目录下运行 `make init` 进行对子模块重新进行下载。
    * 香山需要从 GitHub 中克隆子模块，请确认你的设备可以连上 GitHub，或者可以手动将这些子模块下载下来。
* 编译或仿真默认配置的完整香山核需要花费大量的时间和内存空间，可以首先尝试最小配置的香山 (`make emu CONFIG=MinimalConfig`)，从而确认香山的环境是否已经配置正确。（参见：[https://github.com/OpenXiangShan/XiangShan/issues/852](https://github.com/OpenXiangShan/XiangShan/issues/852)）
* 生成行为仿真用 verilog 代码和可综合 verilog 代码的命令是不同的。通过 `make verilog` 命令可以生成可综合的 verilog 代码；而 `make emu` 用于行为仿真。（参见：[https://github.com/OpenXiangShan/XiangShan/issues/933](https://github.com/OpenXiangShan/XiangShan/issues/933)）

另外，[https://github.com/OpenXiangShan/xs-env](https://github.com/OpenXiangShan/xs-env) 提供了搭建香山开发环境的一些辅助工具，包括用于安装香山依赖的脚本，以及相关的文档。