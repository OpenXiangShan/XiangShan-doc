# Build Linux Kernel for XiangShan

## 1. How to build a minimal Linux Kernel that can run on Xiangshan or NEMU in a simulation environment

> Note: Please prepare the riscv64 toolchain in advance, the possible prefixes are `riscv64-linux-gnu-`, `riscv64-unknown-linux-gnu-`, `riscv64-unknown-elf-`. You may refer to https://github.com/riscv-collab/riscv-gnu-toolchain to setup toolchain needed by Linux.

- Clone riscv-pk, riscv-linux, riscv-rootfs from Xiangshan project, which are Bootloader, Linux kernel and rootfs respectively. Then checkout to target branch.
    - https://github.com/OpenXiangShan/riscv-pk (noop branch)
    - https://github.com/OpenXiangShan/riscv-linux (nanshan branch)
    - https://github.com/OpenXiangShan/riscv-rootfs (master branch)
- Set environment variables
    - NEMU_HOME: Path to NEMU (you may `source env.sh` in `xs-env`)
    - NOOP_HOME: Path to XiangShan (you may `source env.sh` in `xs-env`)
    - RISCV_ROOTFS_HOME: path to `riscv-rootfs`
- build rootfs
    - Enter `riscv-rootfs` directory
    - Run `make rootfsimg` to compile preconfigured workload (located in the apps directory)
    - In simulation environment, we let the Linux Kernel start on the ramfs, so first prepare the initramfs that you want to run, and you can put the workload you want to run in it. The default is riscv-rootfs/rootfsimg/initramfs-emu.txt, Can be modified as needed
- Build the Linux Kernel Manually
    - Enter `riscv-linux` directory
    - Use emu_defconfig to configure. The command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-defconfig emu_defconfig`
    - (Optional) Modify config according to your own needs through menuconfig, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-menuconfig`
    - Compile, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- -j`
    - If succeed, a vmlinux file will be generated in the directory
    - (You do not need to compile here in the subsequent development process, as long as the config is good, because Linux will be compiled in the following BBL makefile)
- Build BBL and Kernel, then link Kernel
    - Enter `riscv-pk` directory
    - Configure the device tree, let `platform.dtsi` symlink to the `noop.dtsi` in `riscv-pk/dts`
    - Run `make -j`, this command will automatically compile the Linux Kernel, link it to BBL as a payload, and finally package it into a build/bbl.bin binary image. After that, Xiangshan is able to run this image

- Others
    - There is a small problem with the Makefile dependency of riscv-pk, so after any modification, please `make clean` first in riscv-pk

## 2. Run BusyBox and some simple applications in Linux

* Reconfigure the Linux Kernel
    * Enter `riscv-linux` directory
    * Use `fpga_defconfig` to configure, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-defconfig fpga_defconfig`
    * Modify config according to your own needs through menuconfig, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-menuconfig`, change the source of initramfs from `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs.txt` to `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs-autorun.txt`
* Modify rootfs as appropriate
    * Go to the `rootfsimg` directory in `riscv-rootfs` directory
    * Modify the contents of initramfs-autorun.txt and inittab to run the programs you want after Linux has booted (stream and redis by default)
* Reconfigure BBL
    * Enter `riscv-pk` directory
    * After `make clean` run `make -j` to generate bbl.bin, let Xiangshan or NEMU run it



## 3. Based on this, how to run Debian distribution on NEMU

* Reconfigure the Linux Kernel
    * to the riscv-linux directory
    * Use debian_defconfig to configure, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-defconfig debian_defconfig`
* Reconfigure BBL
    * Enter `riscv-pk` directory
    * After `make clean` run `make -j` to generate `bbl.bin`
* Configure NEMU
    * Enter `NEMU` directory
    * Edit `src/device/sdcard.c`, find the sdimg variable in the init_sdcard() function and assign it to the path of the Debian mirror (for the generation of the Debian mirror, please refer to [https://github.com/OpenXiangShan/NEMU/tree/ master/resource/debian](https://github.com/OpenXiangShan/NEMU/tree/master/resource/debian))
    * Recompile NEMU, and then run build/bbl.bin under the riscv-pk project


## 4. How to run Debian distribution on Xiangshan

* Configure Xiangshan
    * Enter `Xiangshan` directory
    * Edit the `./difftest/config/config.h` file, set the SDCARD_IMAGE macro to the path to the Debian image
    * Rebuild Xiangshan, then run build/bbl.bin under the riscv-pk project