# 交叉编译工具链说明

This chapter has [English version](./toolchain.en.md).

在为香山构建工作负载时，您可能用到以下几种前缀的交叉编译工具链：

* `riscv64-linux-gnu-`：
    * 适用于 riscv64 架构、面向 linux-gnu 平台（使用 glibc 标准库）的工具链。
    * 可通过包管理工具（如 Ubuntu 的 apt）安装。受限于发行版软件源限制，其编译器版本可能较老。
* `riscv64-unknown-linux-gnu-`：
    * 适用于 riscv64 架构、面向 linux-gnu 平台（使用 glibc 标准库）的工具链，可以与 `riscv64-unknown-linux-gnu-` 相互替换。
    * 可从 [riscv-collab/riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) 构建。
* `riscv64-unknown-elf-`：
    * 适用于 riscv64 架构、面向嵌入式/裸机平台（使用 newlib 标准库）的工具链。
    * 可从 [riscv-collab/riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) 构建。
    * 不推荐通过包管理工具安装此编译链。发行版软件源中的此工具链常常缺少关键的 newlib 标准库。

!!! note
    “面向××平台”实际上指代的是编译器使用的 C 运行库的版本，并非编译出来的程序只能运行在××平台。

    关于工具链的命名规则，推荐您阅读阅读这篇文章来了解更多信息：[Target Triplet](https://wiki.osdev.org/Target_Triplet)

下面，我们将介绍如何安装上述工具链。

## 获取发行版工具链

在 Ubuntu 上，您可以运行以下命令来安装 `riscv64-linux-gnu-` 工具链：
```
apt-get install gcc-riscv64-linux-gnu g++-riscv64-linux-gnu gfortran-riscv64-linux-gnu binutils-riscv64-linux-gnu
```

安装完成后，可以通过以下命令检查安装是否成功：
```
riscv64-linux-gnu-gcc --version
riscv64-linux-gnu-g++ --version
riscv64-linux-gnu-gfortran --version
riscv64-linux-gnu-objdump --version
```

## 获取 riscv-gnu-toolchain 工具链

[RISC-V Collaboration](https://github.com/riscv-collab) 提供了一套 RISC-V 交叉编译工具链 [riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)。您可以根据此仓库的 README 自行构建交叉编译工具链。

此外，riscv-gnu-toolchain 会以夜间版本的形式不定期的发布预编译版本的工具链，我们更推荐直接使用它们。

### 直接获取夜间版本

您可以从这些地方获取 riscv-gnu-toolchain 的夜间版本：

* riscv-gnu-toolchain 的 Github 仓库：[Releases](https://github.com/riscv-collab/riscv-gnu-toolchain/releases)
* ISCAS 提供的镜像：[Releases](https://mirror.iscas.ac.cn/riscv-toolchains/release/riscv-collab/riscv-gnu-toolchain/)

riscv-gnu-toolchain 的每个版本会包含许多不同的包，请根据您的 Ubuntu 版本选择包含以下关键词的 2 个包：

* 对于 `riscv64-unknown-linux-gnu-`：
    * 选择文件名包含 `riscv64`、`glibc`、`gcc` 的
    * 例如 `riscv64-glibc-ubuntu-22.04-gcc-nightly-2024.04.12-nightly.tar.gz`
* 对于 `riscv64-unknown-elf-`：
    * 选择文件名包含 `riscv64`、`elf`、`gcc` 的
    * 例如 `riscv64-elf-ubuntu-22.04-gcc-nightly-2024.04.12-nightly.tar.gz`

将下载到的 2 个 tar.gz 文件解压到 `/opt`，并把 `/opt/riscv/bin` 添加到 `PATH` 中。
```
tar -xzf <downloaded_tar_gz_file> -C /opt
export PATH=/opt/riscv/bin:$PATH
```

!!! tip
    如果您没有管理员权限，您也可以把 tar.gz 文件解压到其他可写目录，并把解压路径下的 `riscv/bin` 目录添加到 `PATH` 中。

完成后，可以通过以下命令检查安装是否成功：
```
riscv64-unknown-linux-gnu-gcc --version
riscv64-unknown-linux-gnu-g++ --version
riscv64-unknown-linux-gnu-gfortran --version
riscv64-unknown-linux-gnu-objdump --version
riscv64-unknown-linux-gnu-gdb --version
riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-g++ --version
riscv64-unknown-elf-objdump --version
riscv64-unknown-elf-gdb --version
```

### 从源代码编译

如果您希望从源代码自行编译工具链，您可参考 [riscv-gnu-toolchain 的官方说明](https://github.com/riscv-collab/riscv-gnu-toolchain)。但请注意，我们无法帮助您解决工具链编译过程中遇到的问题。

## 生成 RV64GC 以外的其他扩展指令

香山处理器南湖架构支持 RV64GCBK 扩展（具体指令集字符串为 `RV64IMAFDC_zba_zbb_zbc_zbs_zk_svinval` ）。

在 gcc 编译选项中加入 `-march=rv64gc_zba_zbb_zbc_zbs`

以编译 AM 中的应用为例:
```shell
# $AM_HOME/am/arch/isa/riscv64.mk

-COMMON_FLAGS  := -fno-pic -march=rv64gc -mcmodel=medany
+COMMON_FLAGS  := -fno-pic -march=rv64gc_zba_zbb_zbc_zbs -mcmodel=medany
```
