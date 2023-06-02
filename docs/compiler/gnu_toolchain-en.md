# GCB tool chain instructions

Nanhu structure of Xiangshan support RV64GCBK extension (`RV64IMAFDC_zba_zbb_zbc_zbs_zbkb_zbkc_zbkx_zknd_zkne_zknh_zksed_zksh_svinval`)

This instruction explains how to compile B extension GNU tool as GNU toolchain release does not support it yet. You can modify the configuration options in this instruction if you need more support such as K extension.


## Release notes of tool chain


### ~~Option 1 (Deprecated)~~
* [riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain.git) official master branch (`df6ecbe4ddb2a1a261b44af822d22f1253d3f0e4` verified)
* Replace riscv-gcc with the version of ISCAS [https://github.com/pz9115/riscv-gcc](https://github.com/pz9115/riscv-gcc)
  switch to branch riscv-gcc-experimental-bkp (`fbfa8d9ad496a2d69a38be2c2c3c0dc0956ffb9e` verified)
* Replace riscv-binutils with the version of ISCAS [https://github.com/pz9115/riscv-binutils-gdb](https://github.com/pz9115/riscv-binutils-gdb)
  switch to branch riscv-binutils-experimental-bkp (`586f9af7f39d5185e8c133ab794167e46bd721de` verified)


(Hint: you can clone riscv-gnu-toolchain before replacing riscv-gcc and riscv-binutils as above)


### ~~Option 2 (Deprecated)~~
To simplify the operation of switching branchs in submodule, Xiangshan forked a [riscv-gnu-toolchain](https://github.com/OpenXiangShan/riscv-gnu-toolchain) and had updated the submodules in order to support B extension and K extension.
**Submodules in this repository has been switched and can be compiled directly without switching manually**.

```bash
git clone git@github.com:OpenXiangShan/riscv-gnu-toolchain.git
```

## Option 3 (Recommended)

For users in China, we highly recommend using the mirrors provided by [PLCT](https://plctlab.github.io/) at ISCAS. We express our special thanks to them for providing the mirrors for [riscv-gnu-toolchain](https://help.mirrors.cernet.edu.cn/riscv-toolchains) and had updated the submodules constantly.

```bash
## to clone (not recommended)
git clone https://mirror.iscas.ac.cn/riscv-toolchains/git/riscv-collab/riscv-gnu-toolchain.git
## to clone with submodules (recommended)
curl https://mirror.iscas.ac.cn/riscv-toolchains/git/riscv-collab/riscv-gnu-toolchain.sh | bash
```

For users outside China, we recommend using the official [riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) repository.

## Compiling method of tool chain

### Install related standard packages

Please refer to the corresponding parts in [riscv-gnu-toolchain official documents](https://github.com/riscv-collab/riscv-gnu-toolchain#prerequisites)。

### Compile tool chain

```bash
cd riscv-gnu-toolchain
mkdir build
cd build
../configure --prefix=PATH_TO_INSTALL --with-arch=rv64gc_zba_zbb_zbc_zbs
# newlib (riscv-unknown-elf-)
make -jN
# linux (riscv-unknown-linux-gnu-)
make linux -jN
```

* If make fails, it may be a permissions issue, so try again with the `sudo make` command
* Set the environment variable `RISCV=PATH_TO_INSTALL` after compiling
* Add `RISCV/bin` to `PATH`

```bash
export RISCV=PATH_TO_INSTALL
export PATH=$RISCV/bin:$PATH
```

## Generate B extension instructions

Add `-march=rv64gc_zba_zbb_zbc_zbs` to gcc compilation options

Here we take an example of compilation applications in AM:
```shell
# $AM_HOME/am/arch/isa/riscv64.mk

-COMMON_FLAGS  := -fno-pic -march=rv64gc -mcmodel=medany
+COMMON_FLAGS  := -fno-pic -march=rv64gc_zba_zbb_zbc_zbs -mcmodel=medany
```
