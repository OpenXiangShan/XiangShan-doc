# Cross-compilation Toolchain Instructions

When building workloads for XiangShan, you might use cross-compilation toolchains with the following prefixes:

* `riscv64-linux-gnu-`:
    * A toolchain for riscv64 targeting the linux-gnu platform (using the glibc library).
    * It can be installed via package managers (e.g., apt on Ubuntu). However, due to the limitations of distribution software sources, the compiler version might be outdated.
* `riscv64-unknown-linux-gnu-`:
    * A toolchain for riscv64 targeting the linux-gnu platform (using the glibc library), which can be used interchangeably with `riscv64-linux-gnu-`.
    * Can be built from [riscv-collab/riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain).
* `riscv64-unknown-elf-`:
    * A toolchain for riscv64 targeting embedded/bare-metal platforms (using the newlib library).
    * Can be built from [riscv-collab/riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain).
    * It is not recommended to install this toolchain via package managers, as the toolchain in distribution software sources often lacks the essential newlib standard library.

!!! note
    "Targeting xx platform" actually refers to the version of the C runtime library used by the compiler, not that the compiled program can only run on the xx platform.

    For more information about toolchain naming conventions, please read this document: [Target Triplet](https://wiki.osdev.org/Target_Triplet).

Next, we will introduce how to install the aforementioned toolchains.

## Get Distribution Toolchains

On Ubuntu, you can install the `riscv64-linux-gnu-` toolchain by running:
```
apt-get install gcc-riscv64-linux-gnu g++-riscv64-linux-gnu gfortran-riscv64-linux-gnu binutils-riscv64-linux-gnu
```

After installation, you can check it with:
```
riscv64-linux-gnu-gcc --version
riscv64-linux-gnu-g++ --version
riscv64-linux-gnu-gfortran --version
riscv64-linux-gnu-objdump --version
```

## Get the riscv-gnu-toolchain

The [RISC-V Collaboration](https://github.com/riscv-collab) provides a set of RISC-V cross-compilation toolchains in [riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) repository. You can build the cross-compilation toolchain yourself according to the README of this repository.

In addition, riscv-gnu-toolchain periodically releases nightly builds, which are recommended for direct use.

### Get the Nightly Builds

You can get nightly builds of riscv-gnu-toolchain from the following sources:
* The GitHub repository for riscv-gnu-toolchain: [Releases](https://github.com/riscv-collab/riscv-gnu-toolchain/releases)

Each version of riscv-gnu-toolchain includes various packages. Please select two packages with the following keywords based on your Ubuntu version:
* For `riscv64-unknown-linux-gnu-`:
    * Choose filenames containing `riscv64`, `glibc`, and `gcc`
    * For example, `riscv64-glibc-ubuntu-22.04-gcc-nightly-2024.04.12-nightly.tar.gz`
* For `riscv64-unknown-elf-`:
    * Choose filenames containing `riscv64`, `elf`, and `gcc`
    * For example, `riscv64-elf-ubuntu-22.04-gcc-nightly-2024.04.12-nightly.tar.gz`

Extract the downloaded tar.gz files to `/opt`, and add `/opt/riscv/bin` to your `PATH`.
```
tar -xzf <downloaded_tar_gz_file> -C /opt
export PATH=/opt/riscv/bin:$PATH
```

!!!! tip
    If you do not have superuser permission, you can also extract the tar.gz files to another writable directory and add the `riscv/bin` directory under the extracted path to your `PATH`.

After completion, you can check with the following commands:
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

### Compiling from Source

If you wish to compile the toolchain from source, you can refer to the [official instructions for riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain). However, please note that we cannot assist with any issues encountered about the compilation process.


## Generate extension instructions
Nanhu structure of Xiangshan support RV64GCBK extension (`RV64IMAFDC_zba_zbb_zbc_zbs_zbkb_zbkc_zbkx_zknd_zkne_zknh_zksed_zksh_svinval`)

Add `-march=rv64gc_zba_zbb_zbc_zbs` to gcc compilation options

Here we take an example of compilation applications in AM:
```shell
# $AM_HOME/am/arch/isa/riscv64.mk

-COMMON_FLAGS  := -fno-pic -march=rv64gc -mcmodel=medany
+COMMON_FLAGS  := -fno-pic -march=rv64gc_zba_zbb_zbc_zbs -mcmodel=medany
```
