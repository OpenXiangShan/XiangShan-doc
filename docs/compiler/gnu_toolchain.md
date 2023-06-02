# GCB 工具链使用说明

This chapter has [English version](./gnu_toolchain-en.md).

香山处理器南湖架构支持 RV64GCBK 扩展（具体指令集字符串为 `RV64IMAFDC_zba_zbb_zbc_zbs_zbkb_zbkc_zbkx_zknd_zkne_zknh_zksed_zksh_svinval` ）。

由于目前发行版工具链还不支持 B 扩展，本文说明如何为香山编译 B 扩展 GNU 工具链。如果需要 K 扩展等更多的指令支持，可以修改本文中的配置选项。

## 工具链版本说明


### ~~方案1 (弃用)~~
* [riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain.git) 官方 master 分支(`df6ecbe4ddb2a1a261b44af822d22f1253d3f0e4`已验证)
* riscv-gcc 替换成软件所的版本 [https://github.com/pz9115/riscv-gcc](https://github.com/pz9115/riscv-gcc)
  切换到 riscv-gcc-experimental-bkp 分支(`fbfa8d9ad496a2d69a38be2c2c3c0dc0956ffb9e`已验证)
* riscv-binutils 替换成软件所的版本 [https://github.com/pz9115/riscv-binutils-gdb](https://github.com/pz9115/riscv-binutils-gdb)
  切换到riscv-binutils-experimental-bkp 分支 (`586f9af7f39d5185e8c133ab794167e46bd721de`已验证)


(Hint: 先 clone riscv-gnu-toolchain，再按照上述要求替换其中的 riscv-gcc, riscv-binutils)


### ~~方案2 (弃用)~~
为了简化submodule分支切换操作，香山Fork了一份[riscv-gnu-toolchain](https://github.com/OpenXiangShan/riscv-gnu-toolchain)并更新了其中的submodule以支持
bk扩展，**该仓库中的submodule已经切换完成，不需要再手工切换，可以直接编译**。

```bash
git clone git@github.com:OpenXiangShan/riscv-gnu-toolchain.git
```

### 方案3
感谢中科院软件所，提供了一份RISC-V工具链镜像[riscv-gnu-toolchain](https://help.mirrors.cernet.edu.cn/riscv-toolchains)并实时同步submodule的更新

```bash
## 单独克隆（不推荐）
git clone https://mirror.iscas.ac.cn/riscv-toolchains/git/riscv-collab/riscv-gnu-toolchain.git
## 同时克隆子模块（推荐）
curl https://mirror.iscas.ac.cn/riscv-toolchains/git/riscv-collab/riscv-gnu-toolchain.sh | bash
```


## 工具链编译方法

### 安装交叉编译过程中依赖的软件

请参考[riscv-gnu-toolchain官方文档](https://github.com/riscv-collab/riscv-gnu-toolchain#prerequisites)中的对应章节。

### 编译工具链

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

* 如果发生make失败，可能是权限的问题，建议将 `PATH_TO_INSTALL` 设置为用户可写的路径，如 `/home/username/riscv-gnu-toolchain-install`
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
