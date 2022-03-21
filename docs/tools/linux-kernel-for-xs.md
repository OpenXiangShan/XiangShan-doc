# Linux Kernel for XiangShan in EMU

#### 1. 首先介绍在仿真环境下如何构建一个可在香山或者 NEMU 上运行的最简 Linux Kernel

注意，过程中出现任何问题，请首先观察出错信息并结合 Makefile 文件，自行网上搜索可以解决一些简单问题，比如工具链和依赖包相关的问题。

- 从香山项目中克隆下来 riscv-pk, riscv-linux, riscv-rootfs，分别是 Bootloader, Linux kernel 和 rootfs
    - https://github.com/OpenXiangShan/riscv-pk noop 分支
    - https://github.com/OpenXiangShan/riscv-linux nanshan 分支
    - https://github.com/OpenXiangShan/riscv-rootfs master 分支
- 设置环境变量
    - NEMU_HOME：NEMU 的路径
    - NOOP_HOME：XiangShan 的路径
    - RISCV_ROOTFS_HOME：riscv-rootfs 的路径
- 构建 rootfs
    - 到 riscv-rootfs 目录
    - 运行 `make rootfsimg`，编译我们预先配置的 workload（位于 apps 目录下）
    - 在仿真环境下，我们让 Linux Kernel 在 ramfs 上启动，因此首先准备好想要运行的 initramfs，里面可以放想要跑的 workload，默认使用的是 riscv-rootfs/rootfsimg/initramfs-emu.txt，可以根据需要酌情进行修改
- 构建 Linux Kernel
    - 到 riscv-linux 目录
    - 使用 emu_defconfig 配置，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- defconfig emu_defconfig`
    - 根据自己的需求酌情通过 menuconfig 做修改，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`
    - 编译，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- -j`
    - 如果顺利，在目录下会产生 vmlinux 文件
    - （后续开发过程中可以不用在这里编译，只要 config 好就行，因为在下述的 BBL makefile 里会做 Linux 的编译）
- 构建 BBL 并链接 Kernel
    - 到 riscv-pk 目录
    - 配置设备树，在 riscv-pk/dts 中让 platform.dtsi 软链接到对应的 noop.dtsi
    - 运行 `make -j`，该命令会自动编译 Linux Kernel，并作为 payload 链接到 BBL 中，最后打包成 build/bbl.bin 二进制镜像，随后就可以让香山跑这一镜像了（详见 Makefile）

------

- 其他
    - riscv-pk 的 Makefile 依赖有一点小问题，因此做了任何修改后，请在 riscv-pk 里面先 make clean
    - 请预先准备好 riscv64 工具链，可能用到的 prefix 有 riscv64-linux-gnu-，riscv64-unknown-linux-gnu-，riscv64-unknown-elf-



#### 2. 在此基础上，介绍如何在 Linux 下跑 BusyBox 以及一些简单的应用程序

* 重新配置 Linux Kernel
    * 到 riscv-linux 目录
    * 使用 fpga_defconfig 配置，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- defconfig fpga_defconfig`
    * 根据自己的需求酌情通过 menuconfig 做修改，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`，其中一个较为必要的修改是将 initramfs 的 source 从 ${RISCV_ROOTFS_HOME}/rootfsimg/initramfs.txt 改为 ${RISCV_ROOTFS_HOME}/rootfsimg/initramfs-autorun.txt
* 酌情修改 rootfs
    * 到 riscv-rootfs 目录下的 rootfsimg 目录
    * 酌情修改 initramfs-autorun.txt 和 inittab 中的内容，以在 Linux 启动过后跑你所想要的程序（默认情况下是 stream 和 redis）
* 重新配置 BBL
    * 到 riscv-pk 目录
    * `make clean` 后运行 `make -j` 生成 bbl.bin，让香山或者 NEMU 跑它



#### 3. 在此基础上，介绍如何在 NEMU 上跑 Debian 发行版

* 重新配置 Linux Kernel
    * 到 riscv-linux 目录
    * 使用 debian_defconfig 配置，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- defconfig debian_defconfig`

* 重新配置 BBL
    * 到 riscv-pk 目录
    * `make clean` 后运行 `make -j` 生成 bbl.bin
* 配置 NEMU
    * 到 NEMU 目录
    * 编辑 src/device/sdcard.c，在 init_sdcard() 函数中找到 sdimg 变量并将其赋值为 Debian 镜像的路径（Debian 镜像的生成请参考[https://github.com/OpenXiangShan/NEMU/tree/master/resource/debian](https://github.com/OpenXiangShan/NEMU/tree/master/resource/debian)）
    * 重新编译 NEMU，然后再运行 riscv-pk 项目下的 build/bbl.bin



#### 4. 在此基础上，介绍如何在香山上跑 Debian 发行版

* 配置香山
    * 到香山目录
    * 编辑 ./difftest/config/config.h 文件，将 SDCARD_IMAGE 这个宏设定为 Debian 镜像的路径
    * 重新构建香山，然后再运行 riscv-pk 项目下的 build/bbl.bin

