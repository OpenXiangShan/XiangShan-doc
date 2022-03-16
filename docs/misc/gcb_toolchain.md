# GCB 工具链使用说明

工具链版本说明:

- riscv-toolchain 官方master分支
- riscv-gcc 替换成软件所的版本 [https://github.com/pz9115/riscv-gcc](https://github.com/pz9115/riscv-gcc)  	
   - riscv-gcc-experimental分支 e5ec1231dd03ec1e10807ab5677a600489fa017e
- riscv-binutils 替换成软件所的版本 [https://github.com/pz9115/riscv-binutils-gdb](https://github.com/pz9115/riscv-binutils-gdb)
   - riscv-binutils-experimental分支 520f5066004f7db320b39d09e9dd6d1a79202733
- 构建参数：../configure --prefix=/bigdata/zfw/b-tools --target=riscv64-unknown-linux-gnu --with-arch=rv64gc_zba_zbb_zbc_zbs --with-abi=lp64d --with-multilib-generator="rv64gc_zba_zbb_zbc_zbs-lp64d--" --enable-multilib=true

由于手动编译的工具链都是带 unknown 的，导致我们开发环境中很多地方需要修改 Makefile 中的 `CROSS_COMPILE`选项，包括但不仅限于 am， spec2006-lite

生成b扩展指令：编译时除了修改编译器还要修改-march，以am为例：

```shell
# $AM_HOME/am/arch/isa/riscv64.mk

-CROSS_COMPILE := riscv64-linux-gnu-
-COMMON_FLAGS  := -fno-pic -march=rv64gc -mcmodel=medany
+CROSS_COMPILE := riscv64-unknown-linux-gnu-
+COMMON_FLAGS  := -fno-pic -march=rv64gc_zba_zbb_zbc_zbs -mcmodel=medany
```

5. 注意事项：

编bbl时建议 kernel linux busybox 和动态库使用原来工具链，workload可以使用GCB工具链编
