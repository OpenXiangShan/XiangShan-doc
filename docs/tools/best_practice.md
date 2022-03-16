XiangShan 前端开发注意事项
=====================

本章介绍一些进行香山前端开发的注意事项。

## Bug 调试

默认的仿真脚本并不能满足所有的需求。根据需求的不同，在进行 Verilator 仿真之前，需要调整仿真配置。`XiangShan/difftest/config`下包含了一些需要在仿真程序`emu`编译前指定的仿真配置。

`difftest/config/verilator.mk`中的关键配置包括：

`EMU_TRACE ?= 1`允许 Verilog 编译的仿真程序生成波形。关闭这一选项会加快编译速度。只有启用这一选项，在后续执行`emu --dump-wave ...`时才会输出波形到 `XiangShan/build`。

`EMU_THREADS ?= 8`指定 Verilog 编译的仿真程序的线程数。提高线程数到一个合理的数值以加快仿真速度。4/8线程是比较合理的配置，太多了反而会变慢。

> 注意：在启用多线程仿真时， Chisel 代码中同一拍内 printf 输出的顺序会比较混乱

`difftest/config/config.h`中的关键配置包括：

`#define EMU_RAM_SIZE (8 * 1024 * 1024 * 1024UL)`配置仿真中仿真 memory 的大小。仿真时执行的程序的大小以及程序所访问的 memory 地址空间不能超过这个范围。

> 注意： 用于对比的模拟器 （如NEMU） 中也有类似的设置。在仿真前请确保将仿真框架的仿真 memory 大小和模拟器的 memory 大小对齐。

> 如果仿真过程中处理器所执行的程序访问的地址范围超过了配置，仿真框架不会报错且不保证结果的正确性。请务必在仿真前确认仿真框架和模拟器中配置的仿真 memory 大小足够。一般而言，只有像 spec 这样的大型程序才会需要非常大的仿真 memory （8GB）。

> 如果是在内存大小受限的服务器上运行，可以考虑适当调小仿真 memory 的大小。128MB足够运行绝大多数程序了。

## 性能评估/回归测试

同上，注意配置`difftest/config/verilator.mk`中的`EMU_THREADS`来加快仿真速度。

## 加速仿真的手段

参考 [https://www.graalvm.org/docs/getting-started/](https://www.graalvm.org/docs/getting-started/) 配置 graalvm 可以加速 java 的运行, 从而提高 XiangShan 的编译效率。