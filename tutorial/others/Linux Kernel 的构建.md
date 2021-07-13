#Linux Kernel for XiangShan Guidence



####下面介绍在仿真环境下如何构建一个可在香山上运行的最简单的 Linux Kernel

<font color=#FF0000>注意，过程中出现任何问题，请首先观察出错信息，自行网上搜索可以解决一些简单的与工具链和依赖包相关的问题；另外，也请仔细阅读相关的 Makefile 文件。后续将不断完善文档。</font>

* 从香山项目中克隆下来 riscv-pk, riscv-linux, riscv-rootfs，分别是 Bootloader, Linux kernel 和 rootfs

  * https://github.com/OpenXiangShan/riscv-pk  noop 分支
  * https://github.com/OpenXiangShan/riscv-linux nanshan 分支
  * https://github.com/OpenXiangShan/riscv-rootfs master 分支

* 设置环境变量

  * NEMU_HOME：NEMU 的路径
  * NOOP_HOME：XiangShan 的路径
  * RISCV_ROOTFS_HOME：riscv-rootfs 的路径

* 构建 rootfs

  * 到 riscv-rootfs 目录
  * 运行 `make rootfsimg`，编译我们预先配置的 workload（位于 apps 目录下）
  * 在仿真环境下，我们让 Linux Kernel 在 ramfs 上启动，因此首先准备好想要运行的 initramfs，里面可以放想要跑的 workload，默认使用的是 riscv-rootfs/rootfsimg/initramfs-emu.txt，可以根据需要酌情进行修改

* 构建 Linux Kernel

  * 到 riscv-linux 目录
  * 使用 emu_defconfig 配置，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- defconfig emu_defconfig`
  * 根据自己的需求酌情通过 menuconfig 做修改，命令为  `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`
  * 编译，命令为 `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- -j`
  * 如果顺利，在目录下会产生 vmlinux 文件
  * （后续开发过程中可以不用在这里编译，只要 config 好就行，因为在下述的 BBL makefile 里会做 Linux 的编译）

* 构建 BBL 并链接 Kernel
  * 到 riscv-pk 目录
  * 配置设备树，在 riscv-pk/dts 中让 platform.dtsi 软链接到 noop.dtsi
  * 运行 `make noop -j`，该命令会自动编译 Linux Kernel，并作为 payload 链接到 BBL 中，最后打包成 build/bbl.bin 二进制镜像，随后让香山跑这一镜像（详见 Makefile）

-----

* 其他
  * riscv-pk 的 Makefile 依赖有一点小问题，因此做了任何修改后，请在 riscv-pk 里面先 make clean
  * 请预先准备好 riscv64 工具链，可能用到的 prefix 有 riscv64-linux-gnu-，riscv64-unknown-linux-gnu-，riscv64-unknown-elf-，前两者应该没啥差别，报错的话可以修改 Makefile 统一一下，最后一个主要在 rootfs 里面做静态编译用
  * 遇到其他问题可以先看报错信息做排查，注意多看 Makefile 的行为
  * 想要拓展 Kernel 的功能（比如跑 Busybox、仿真启动 Debian 等 Linux 发行版等）可以参考后续的文档
