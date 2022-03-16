# GCB 工具链使用说明

香山处理器南湖架构支持RV64 GCB扩展，由于目前发行版工具链还不支持B扩展，本文说明如何为香山编译B扩展GNU工具链。

## 工具链版本说明

* riscv-gun-toolchain 官方master分支
* riscv-gcc 替换成软件所的版本 https://github.com/pz9115/riscv-gcc
  切换到riscv-gcc-experimental分支 e5ec1231dd03ec1e10807ab5677a600489fa017e
* riscv-binutils 替换成软件所的版本 https://github.com/pz9115/riscv-binutils-gdb
  切换到riscv-binutils-experimental分支 520f5066004f7db320b39d09e9dd6d1a79202733

(先clone riscv-gnu-toolchain，再按照上述要求替换其中的riscv-gcc, riscv-binutils)


## 工具链编译方法

```bash
cd riscv-gnu-toolchain
mkdir build
cd build
../configure --prefix=PATH_TO_INSTALL --with-arch=rv64gc_zba_zbb_zbc_zbs
# newlib (riscv-unknown-elf-)
make -j
# linux (riscv-unknown-linux-gnu-)
make linux -j
```

* 编译完成后将`RISCV`环境变量设置为`PATH_TO_INSTALL`
* 再将`RISCV/bin`添加到`PATH`

```bash
export RISCV=PATH_TO_INSTALL
export PATH=$RISCV/bin:$PATH
```

## 生成B扩展指令

在gcc编译选项中加入`-march=rv64gc_zba_zbb_zbc_zbs`

以编译AM中的应用为例:
```shell
# $AM_HOME/am/arch/isa/riscv64.mk

-COMMON_FLAGS  := -fno-pic -march=rv64gc -mcmodel=medany
+COMMON_FLAGS  := -fno-pic -march=rv64gc_zba_zbb_zbc_zbs -mcmodel=medany
```
