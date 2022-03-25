# GCB 工具链使用说明

香山处理器南湖架构支持 RV64GCBK 扩展（具体指令集字符串为 `RV64IMAFDC_zba_zbb_zbc_zbs_zbkb_zbkc_zbkx_zknd_zkne_zknh_zksed_zksh_svinval` ）。

由于目前发行版工具链还不支持 B 扩展，本文说明如何为香山编译 B 扩展 GNU 工具链。如果需要 K 扩展等更多的指令支持，可以修改本文中的配置选项。

## 工具链版本说明

* riscv-gnu-toolchain 官方 master 分支
* riscv-gcc 替换成软件所的版本 https://github.com/pz9115/riscv-gcc
  切换到 riscv-gcc-experimental 分支 e5ec1231dd03ec1e10807ab5677a600489fa017e
* riscv-binutils 替换成软件所的版本 https://github.com/pz9115/riscv-binutils-gdb
  切换到
* riscv-binutils-experimental 分支 520f5066004f7db320b39d09e9dd6d1a79202733


(Hint: 先 clone riscv-gnu-toolchain，再按照上述要求替换其中的 riscv-gcc, riscv-binutils)


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

* 编译完成后将 `RISCV` 环境变量设置为 `PATH_TO_INSTALL`
* 再将 `RISCV/bin` 添加到 `PATH`

```bash
export RISCV=PATH_TO_INSTALL
export PATH=$RISCV/bin:$PATH
```

## 生成 B 扩展指令

在 gcc 编译选项中加入 `-march=rv64gc_zba_zbb_zbc_zbs`

以编译 AM 中的应用为例:
```shell
# $AM_HOME/am/arch/isa/riscv64.mk

-COMMON_FLAGS  := -fno-pic -march=rv64gc -mcmodel=medany
+COMMON_FLAGS  := -fno-pic -march=rv64gc_zba_zbb_zbc_zbs -mcmodel=medany
```
