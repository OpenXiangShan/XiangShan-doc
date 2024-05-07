# Linux Kernel for XiangShan in EMU

!!! note
    注意，下文所有使用的工具链是通过 [riscv-toolchains](https://github.com/riscv-collab/riscv-gnu-toolchain) 构建得到的，要构建在 Linux 上运行的程序使用的前缀是 `riscv64-unknown-linux-gnu-` ，某些 Linux 发行版使用包管理工具安装的工具链仅有 `riscv64-linux-gnu-` 前缀，此时仅需要将下文所有的 `riscv64-unknown-linux-gnu-` 替换为 `riscv64-linux-gnu-` 即可，它和 `riscv64-unknown-linux-gnu-` 是等价的，详细请看[Target Triplet](https://wiki.osdev.org/Target_Triplet)

#### 1. 如何构建一个可在香山或者 NEMU 上运行的使用 OpenSBI 的最简 Linux Kernel

!!! note
    注意，过程中出现任何问题，请首先观察出错信息并结合 Makefile 文件，自行网上搜索可以解决一些简单问题，比如工具链和依赖包相关的问题。

- 分别克隆或下载启动加载程序 OpenSBI、Linux kernel、根文件系统 rootfs、NEMU以及构建时所需的设备树和内核配置文件。并将四个仓库和一个压缩文件放到**同一目录下**
     ```shell
         git clone https://github.com/riscv-software-src/opensbi.git -b v1.4
         wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.6.30.tar.xz
         git clone https://github.com/OpenXiangShan/riscv-rootfs -b checkpoint
         git clone https://github.com/OpenXiangShan/NEMU -b gcpt_new_mem_layout
         git clone https://github.com/xyyy1420/workload_build_env.git
     ```
!!! note
    注意，本文档中使用的内核版本 6.6.30 不是必须的，用户可以自行选择内核版本以满足不同的需求，但是如果选择使用其他版本的内核，我们无法提供任何可用的配置文件，也无法提供任何有关配置方面的支持

- 解压 Linux kernel 代码
    - 运行 `tar -xf linux-6.6.30.tar.xz`

- 设置环境变量
    - NEMU_HOME：NEMU 的路径
    - GCPT_HOME：GCPT_RESTORE 的路径（$NEMU_HOME/resource/gcpt_restore）
    - RISCV_LINUX_HOME：Linux Kernel 的路径
    - RISCV_ROOTFS_HOME：riscv-rootfs 的路径
    - WORKLOAD_BUILD_ENV_HOME: workload build env 的路径
    - OPENSBI_HOME：OpenSBI 的路径
    - RISCV：riscv-gnu-toolchain 的安装路径（包含bin, include, lib等的顶层目录路径）
    > riscv-gnu-toolchain 的安装请参考 [riscv-gnu-toolchain 官方文档](https://github.com/riscv-collab/riscv-gnu-toolchain)，如果需要为香山编译 B 扩展 GNU 工具链请参见 [GCB 工具链使用说明](../compiler/gnu_toolchain.md)。

- 设置交叉编译工具链
    - 运行 `export CROSS_COMPILE=$RISCV/bin/riscv64-unknown-linux-gnu-`

- 构建 rootfs
    - 到 $RISCV_ROOTFS_HOME 目录
    - 在仿真环境下，我们让 Linux Kernel 在 ramfs 上启动，因此首先准备好想要运行的 initramfs 文件，里面可以放想要跑的 workload。默认使用的是 `riscv-rootfs/rootfsimg/initramfs-emu.txt`（在 Kernel 的 menuconfig 中设置），在 Linux 启动后运行 hello
    - 运行 `make` 将在 rootfsimg/build 中得到 hello、busybox 等，在后续内核的编译过程中会自动与内核一同打包

- 构建设备树
    - 到 $WORKLOAD_BUILD_ENV_HOME 目录
    - 配置设备树，在 $WORKLOAD_BUILD_ENV_HOME/dts 中让 platform.dtsi 软链接到对应的 platform_noop.dtsi
    - 运行 `build_single_core_for_nemu.sh`，该命令会在 build 目录下生成 xiangshan.dtb （如需在 QEMU 上运行双核或四核 workload，可以运行 build_dualcore_for_qemu.sh 或 build_fourcore_for_qemu.sh 生成双核的设备树或者四核的设备树）

- 构建 Linux Kernel
    - 到 $RISCV_LINUX_HOME 目录
    - 将 $WORKLOAD_BUILD_ENV_HOME/configs/xiangshan_defconfig 拷贝到 $RISCV_LINUX_HOME/arch/riscv/configs/xiangshan_defconfig
    - 使用 xiangshan_defconfig 配置，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-gnu- xiangshan_defconfig`
    - 根据自己的需求通过 menuconfig 做修改，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-gnu- menuconfig`
    - 如果要运行 SPEC2006 或其他程序，一个**较为必要的修改**是将 initramfs 的 source 改为 $RISCV_ROOTFS_HOME/rootfsimg/initramfs-spec.txt，并修改该文件（该文件非开箱即用）
    - 使用 `make -j` 构建内核

- 构建 OpenSBI 并链接内核
    - 到 $OPENSBI_HOME 目录
    - 运行 `make PLATFORM=generic FW_PAYLOAD_PATH=$RISCV_LINUX_HOME/arch/riscv/boot/Image FW_FDT_PATH=$WORKLOAD_BUILD_ENV_HOME/dts/build/xiangshan.dtb FW_TEXT_START=0x80100000 FW_PAYLOAD_OFFSET=0x100000`

- 构建 GCPT 并链接 OpenSBI 作为 PAYLOAD
    - 到 $GCPT_HOME 目录
    - 运行 `make GCPT_PAYLOAD_PATH=$OPENSBI_HOME/build/platform/generic/firmware/fw_payload.bin` 得到 build/gcpt.bin 可用于直接运行或者用于 profiling 或生成 checkpoint

- 其他
    - 请预先准备好 riscv64 工具链，可能用到的 prefix 有 `riscv64-unknown-linux-gnu-`，`riscv64-unknown-elf-`

## FAQs

#### `riscv64-unknown-linux-gnu-gcc: command not found`

确保 riscv64-unknown-linux-gnu-gcc 在你的 PATH 中