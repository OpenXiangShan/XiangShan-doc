# NEMU 使用指南

NEMU (NJU Emulator) is a simple but complete full-system emulator designed for teaching purpose. Currently it supports x86, mips32, riscv64, and riscv32.

## 使用指南

第一步，配置环境变量：`export NEMU_HOME=/path/to/NEMU`。如果在 NEMU 仓库所在位置，可以通过 `export NEMU_HOME=$(pwd)` 配置。

第二步，对 NEMU 的选项进行配置。master 分支上的 NEMU 支持通过 `menuconfig` 配置成两种模式：单独运行、动态链接库。

在 `configs` 目录下有一些预先配置好的文件。如果希望 NEMU 能够独立运行，可以使用 `make riscv64-xs_defconfig`，对应配置下的 NEMU 与香山的仿真环境外设对齐一致。如果希望配置 NEMU 为作为 DiffTest 使用的 golden model（通过动态链接库的形式），可以使用 `make riscv64-xs-ref_defconfig`。如果有希望修改的参数，可以通过 `make menuconfig` 改一些配置. 注意这个版本的 NEMU 有些配置可能会挂掉。

第三步，编译生成可执行程序或动态链接库：`make`。

## 其他文档

可以参考 [https://github.com/OpenXiangShan/NEMU/tree/master/resource](https://github.com/OpenXiangShan/NEMU/tree/master/resource)。
