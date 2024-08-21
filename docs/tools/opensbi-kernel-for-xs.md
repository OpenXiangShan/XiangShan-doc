# Linux Kernel for XiangShan in EMU

!!! note
    注意，下文所有使用的工具链是通过 [riscv-toolchains](https://github.com/riscv-collab/riscv-gnu-toolchain) 构建得到的，要构建在 Linux 上运行的程序使用的前缀是 `riscv64-unknown-linux-gnu-` ，某些 Linux 发行版使用包管理工具安装的工具链仅有 `riscv64-linux-gnu-` 前缀，此时仅需要将下文所有的 `riscv64-unknown-linux-gnu-` 替换为 `riscv64-linux-gnu-` 即可，它和 `riscv64-unknown-linux-gnu-` 是等价的，详细请看[Target Triplet](https://wiki.osdev.org/Target_Triplet)

#### 1. 如何构建一个可在香山或者 NEMU 上运行的使用 OpenSBI 的最简 Linux Kernel

!!! note
    注意，过程中出现任何问题，请首先观察出错信息并结合 Makefile 文件，自行网上搜索可以解决一些简单问题，比如工具链和依赖包相关的问题。

- 分别克隆或下载启动加载程序 OpenSBI、Linux kernel、根文件系统 rootfs以及构建时所需的设备树和内核配置文件。并将四个仓库和一个压缩文件放到**同一目录下**
```bash
git clone https://github.com/riscv-software-src/opensbi.git
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.10.3.tar.xz
git clone https://github.com/OpenXiangShan/riscv-rootfs -b checkpoint
git clone https://github.com/OpenXiangShan/nemu_board.git
```
!!! note
    注意，本文档中使用的内核版本 6.10.3 不是必须的，用户可以自行选择内核版本以满足不同的需求

- 解压 Linux kernel 代码
```bash
tar -xf linux-6.10.3.tar.xz
```

* 设置环境变量
    * `RISCV_LINUX_HOME`：Linux Kernel 的路径
    * `RISCV_ROOTFS_HOME`：riscv-rootfs 的路径
    * `WORKLOAD_BUILD_ENV_HOME`: nemu board 的路径
    * `OPENSBI_HOME`：OpenSBI 的路径
    * `RISCV`：riscv-gnu-toolchain 的安装路径（包含bin, include, lib等的顶层目录路径）
    > riscv-gnu-toolchain 的安装请参考 [riscv-gnu-toolchain 官方文档](https://github.com/riscv-collab/riscv-gnu-toolchain)，如果需要为香山编译 B 扩展 GNU 工具链请参见 [GCB 工具链使用说明](../compiler/gnu_toolchain.md)。

* 设置交叉编译工具链和目标架构
```bash
export ARCH=riscv
export CROSS_COMPILE=$RISCV/bin/riscv64-unknown-linux-gnu-
```

* 构建 rootfs
    * 到 `$RISCV_ROOTFS_HOME` 目录
    * 在仿真环境下，我们让 Linux Kernel 在 ramfs 上启动，因此首先准备好想要运行的 initramfs 文件，里面可以放想要跑的 workload。默认使用的是 `riscv-rootfs/rootfsimg/initramfs-emu.txt`（在 Kernel 的 menuconfig 中设置），在 Linux 启动后运行 hello
    * 使用 `make` 构建可能被打包的应用

* 构建设备树
    * 到 `$WORKLOAD_BUILD_ENV_HOME` 目录
    * 配置设备树，在 `$WORKLOAD_BUILD_ENV_HOME/dts` 中让 platform.dtsi 软链接到对应的 `platform_noop.dtsi`
    * 运行脚本 `build_single_core_for_nemu.sh`，该脚本会在 build 目录下生成 xiangshan.dtb （如需在 QEMU 上运行双核或四核 workload，可以运行 `build_dualcore_for_qemu.sh` 或 `build_fourcore_for_qemu.sh` 生成双核的设备树或者四核的设备树）

* 构建 Linux Kernel
    * 到 `$RISCV_LINUX_HOME` 目录
    * 将 `$WORKLOAD_BUILD_ENV_HOME/configs/xiangshan_defconfig` 拷贝到 `$RISCV_LINUX_HOME/arch/riscv/configs/xiangshan_defconfig`
    * 使用 `xiangshan_defconfig` 配置内核
    ```bash
    make xiangshan_defconfig
    ```
    * 根据自己的需求通过 menuconfig 做修改
    ```bash
    make menuconfig
    ```
    * 使用 `make -j` 构建内核

* 构建 OpenSBI 并链接内核
    * 到 `$OPENSBI_HOME` 目录
    * 构建 OpenSBI
    ```bash
    make PLATFORM=generic FW_PAYLOAD_PATH=$RISCV_LINUX_HOME/arch/riscv/boot/Image FW_FDT_PATH=$WORKLOAD_BUILD_ENV_HOME/dts/build/xiangshan.dtb FW_PAYLOAD_OFFSET=0x200000
    ```
    * 构建得到二进制文件 `$OPENSBI_HOME/build/platform/generic/firmware/fw_payload.bin`

* 其他
    * 请预先准备好 riscv64 工具链，可能用到的 prefix 有 `riscv64-unknown-linux-gnu-`，`riscv64-unknown-elf-`

#### 2. 在此基础上，如何在 Linux 下跑 SPEC2006 以及其他程序作为 SimPoint profiling 和 checkpoint 的 workload

* 重新配置内核
    * 到 `$RISCV_LINUX_HOME` 目录
    * 使用 `make menuconfig` 将 initramfs 的 source 从 `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs-emu.txt` 改为 `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs-spec.txt`

* 修改 rootfsimg
    * 按需修改 `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs-spec.txt` 文件（不修改无法使用）
    * 构建内核 `make -j16`

* 构建 OpenSBI
    * 删除 `$OPENSBI_HOME/build`
    * 检查 `${RISCV_LINUX_HOME}/arch/riscv/boot/Image` 大小是否超过 32MB
    * 如果超过，计算 `FW_PAYLOAD_FDT_ADDR` =（该文件大小 + 2M + 0x80000000）以 1M 对齐，作为 OpenSBI 重定向设备树的地址并使用该命令构建 OpenSBI 
    ```bash
    make PLATFORM=generic FW_PAYLOAD_PATH=$RISCV_LINUX_HOME/arch/riscv/boot/Image FW_FDT_PATH=$WORKLOAD_BUILD_ENV_HOME/dts/build/xiangshan.dtb FW_PAYLOAD_OFFSET=0x100000 FW_PAYLOAD_FDT_ADDR=$(FW_PAYLOAD_FDT_ADDR) -j10
    ```
    * 如果没超过，则使用该命令构建OpenSBI 
    ```bash
    make PLATFORM=generic FW_PAYLOAD_PATH=$RISCV_LINUX_HOME/arch/riscv/boot/Image FW_FDT_PATH=$WORKLOAD_BUILD_ENV_HOME/dts/build/xiangshan.dtb FW_PAYLOAD_OFFSET=0x100000 -j10
    ```

* 使用 gcpt 链接 OpenSBI
    * 克隆 gcpt 仓库 `git clone https://github.com/OpenXiangShan/LibCheckpointAlpha.git`
    * 设置环境变量 `export GCPT_HOME=/path/to/LibCheckpointAlpha`
    * 到 `$GCPT_HOME` 目录
    * 链接 OpenSBI `make GCPT_PAYLOAD_PATH=$OPENSBI_HOME/build/platform/generic/firmware/fw_payload.bin` 得到 `$GCPT_HOME/build/gcpt.bin` 可以用于直接启动或者作为 SimPoint profiling 和 checkpoint 的 workload

## FAQs

#### `riscv64-unknown-linux-gnu-gcc: command not found`

确保 riscv64-unknown-linux-gnu-gcc 在你的 PATH 中
