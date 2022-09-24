# Linux Kernel for XiangShan in EMU

#### 1. 在仿真环境下如何构建一个可在香山或者 NEMU 上运行的最简 Linux Kernel

!!! note
    注意，过程中出现任何问题，请首先观察出错信息并结合 Makefile 文件，自行网上搜索可以解决一些简单问题，比如工具链和依赖包相关的问题。

- 从香山项目中克隆下来 riscv-pk, riscv-linux, riscv-rootfs，分别是启动加载程序 Bootloader, Linux kernel 和根文件系统 rootfs。请将三个仓库**放到同一目录下**。

    - https://github.com/OpenXiangShan/riscv-pk noop 分支
    - https://github.com/OpenXiangShan/riscv-linux nanshan 分支
    - https://github.com/OpenXiangShan/riscv-rootfs master 分支
- 设置环境变量
    - NEMU_HOME：NEMU 的路径
    - NOOP_HOME：XiangShan 的路径
    - RISCV_ROOTFS_HOME：riscv-rootfs 的路径
    - RISCV：riscv-gnu-toolchain 的安装路径（包含bin, include, lib等的顶层目录路径）

    > riscv-gnu-toolchain 的安装请参考 [riscv-gnu-toolchain 官方文档](https://github.com/riscv-collab/riscv-gnu-toolchain)，如果需要为香山编译 B 扩展 GNU 工具链请参见 [GCB 工具链使用说明](../compiler/gnu_toolchain.md)。

- 构建 rootfs
    - 到 riscv-rootfs 目录
    - 在仿真环境下，我们让 Linux Kernel 在 ramfs 上启动，因此首先准备好想要运行的 initramfs 文件，里面可以放想要跑的 workload。默认使用的是 `riscv-rootfs/rootfsimg/initramfs-emu.txt`，在 Linux 启动后运行 hello。下一章会介绍如何运行自定义程序。
    - 本步骤中不需要在该仓库进行操作
- 构建 Linux Kernel
    - 到 riscv-linux 目录
    - 使用默认的 emu_defconfig 配置，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- emu_defconfig`
    - （可选）根据自己的需求通过 menuconfig 做修改，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`
- 构建 BBL 并链接 Kernel
    - 到 riscv-pk 目录
    - 配置设备树，在 riscv-pk/dts 中让 platform.dtsi 软链接到对应的 noop.dtsi
    - 运行 `make -j`，该命令会自动去 rootfs 和 Linux Kernel 目录进行编译，并作为 payload 链接到 BBL 中，最后打包成 build/bbl.bin 二进制镜像，随后就可以让香山跑这一镜像了（详见 Makefile）

- 其他
    - riscv-pk 的 Makefile 依赖有一点小问题，因此做了任何修改后，请在 riscv-pk 里面**先 `make clean`**
    - 请预先准备好 riscv64 工具链，可能用到的 prefix 有 `riscv64-linux-gnu-`，`riscv64-unknown-linux-gnu-`，`riscv64-unknown-elf-`



#### 2. 在此基础上，如何在 Linux 下跑 BusyBox 以及一些简单的应用程序

* 重新配置 Linux Kernel
    * 到 riscv-linux 目录
    * 使用 fpga_defconfig 配置，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- fpga_defconfig`
    * 根据自己的需求酌情通过 menuconfig 做修改，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`，其中一个**较为必要的修改**是将 initramfs 的 source 从 `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs.txt` 改为 `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs-autorun.txt`
    
* 酌情修改 rootfs
    * 到 riscv-rootfs 目录下的 rootfsimg 目录
    * initramfs 里指定了文件系统里的内容，而 inittab 在初始化时会被解析执行
    * 可以参考二者文件内容，进行酌情修改或者自己编写新的 initramfs 和 inittab，以在 Linux 启动过后跑你所想要的程序（默认情况下是 stream 和 redis）
    
* 重新配置 BBL
    * 到 riscv-pk 目录
    * 修改 dts 中地址空间大小，支持占用内存更大的程序运行
    ```shell
    # ./riscv-pk/dts/noop.dtsi

	L11: memory@100000000 {
	    device_type = "memory";
	    -reg = <0x0 0x80000000 0x0 0x2000000>;
        +reg = <0x0 0x80000000 0x0 0x80000000>;
	};
    ```
    * `make clean` 后运行 `make -j` 生成 bbl.bin，供香山或者 NEMU 运行



#### 3. 在此基础上，如何在 NEMU 上跑 Debian 发行版

* 重新配置 Linux Kernel
    * 到 riscv-linux 目录
    * 使用 debian_defconfig 配置，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- debian_defconfig`
* 重新配置 BBL
    * 到 riscv-pk 目录
    * 修改 dts 中 bootargs 参数
    ```shell
    # ./riscv-pk/dts/noop.dtsi

	chosen {
        -bootargs = "root=/dev/mmcblk0 rootfstype=ext4 ro rootwait earlycon";
        +bootargs = "root=/dev/mmcblk0p1 rootfstype=ext4 ro rootwait earlycon";
    };
    ```
    （参见 [https://github.com/OpenXiangShan/NEMU/tree/master/resource/sdcard](https://github.com/OpenXiangShan/NEMU/tree/master/resource/sdcard)）
    * `make clean` 后运行 `make -j` 生成 bbl.bin
* 配置 NEMU
    * 到 NEMU 目录
    * 编辑 src/device/sdcard.c，在 init_sdcard() 函数中找到 sdimg 变量并将其赋值为 Debian 镜像的路径（Debian 镜像的生成请参考[如何制作 Debian 镜像](./debian.md)）
    * 重新编译 NEMU，然后再运行 riscv-pk 项目下的 build/bbl.bin



#### 4. 在此基础上，如何在香山上跑 Debian 发行版

* 配置香山
    * 到香山目录
    * 编辑 ./difftest/config/config.h 文件，将 SDCARD_IMAGE 这个宏设定为 Debian 镜像的路径
    * 重新构建香山，然后再运行 riscv-pk 项目下的 build/bbl.bin


#### 5. 在此基础上，如何编译双核Linux kernal
* 重新配置 Linux Kernel
    * 到 riscv-linux 目录
    * `make clean`清除编译文件
    * 根据需求使用 emu_defconfig 、fpga_defconfig 、或 debian_defconfig 进行配置，命令同上
    * 通过 menuconfig 修改配置开启多核，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`，
    进入Platform type目录，将 Symmetric Multi-Processing 置为 Yes ，保存修改并退出
* 重新配置 BBL
    * 到 riscv-pk 目录
    * `git stash`将没有提交的内容缓存并移除
    * `git checkout dualcore`切换到 dualcore 分支
    * 修改 dts 中地址空间大小
    ```shell
    # ./riscv-pk/dts/noop.dtsi

	L11: memory@100000000 {
	    device_type = "memory";
	    -reg = <0x0 0x80000000 0x0 0x2000000>;
        +reg = <0x0 0x80000000 0x0 0x8000000>;
	};
    ```
    * 如果运行 16G Debian , 还需要修改 dts 中 bootargs 参数
    ```shell
    # ./riscv-pk/dts/noop.dtsi

	chosen {
        -bootargs = "root=/dev/mmcblk0 rootfstype=ext4 ro rootwait earlycon";
        +bootargs = "root=/dev/mmcblk0p1 rootfstype=ext4 ro rootwait earlycon";
    };
    ```
    * `make clean` 后运行 `make -j` 生成 bbl.bin
