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
    - RISCV：Installation path of riscv-gnu-toolchain

    > You can see [riscv-gnu-toolchain official documents](https://github.com/riscv-collab/riscv-gnu-toolchain) to install riscv-gnu-toolchain. You can also see [GCB tool chain instructions](../compiler/gnu_toolchain-en.md) if you need to compile B extension GNU tool chain for Xiangshan.

- build rootfs
    - Enter `riscv-rootfs` directory
    - In simulation environment, we let the Linux Kernel start on the ramfs, so first prepare the initramfs that you want to run, and you can put the workload you want to run in it. The default is riscv-rootfs/rootfsimg/initramfs-emu.txt, Can be modified as needed
- Build the Linux Kernel Manually
    - Enter `riscv-linux` directory
    - Use emu_defconfig to configure. The command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- emu_defconfig`
    - (Optional) Modify config according to your own needs through menuconfig, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`
    - Compile, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- -j`
    - If succeed, a vmlinux file will be generated in the directory
    - (You do not need to compile here in the subsequent development process, as long as the config is good, because Linux will be compiled in the following BBL makefile)
- Build BBL and Kernel, then link Kernel
    - Enter `riscv-pk` directory
    - Configure the device tree, let `platform.dtsi` symlink to the `noop.dtsi` in `riscv-pk/dts`
    - Run `make -j`, this command will automatically compile the Linux Kernel, link it to BBL as a payload, and finally package it into a build/bbl.bin binary image. After that, Xiangshan is able to run this image (See Makefile).

- Others
    - There is a small problem with the Makefile dependency of riscv-pk, so after any modification, please `make clean` first in riscv-pk
    - Please prepare the riscv64 tool chains in advance, you may use `riscv64-linux-gnu-`, `riscv64-unknown-linux-gnu-` and `riscv64-unknown-elf-`

## 2. Run BusyBox and some simple applications in Linux

* Reconfigure the Linux Kernel
    * Enter `riscv-linux` directory
    * Use `fpga_defconfig` to configure, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- fpga_defconfig`
    * Modify config according to your own needs through menuconfig, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`, change the source of initramfs from `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs.txt` to `${RISCV_ROOTFS_HOME}/rootfsimg/initramfs-autorun.txt`
* Modify rootfs as appropriate
    * Go to the `rootfsimg` directory in `riscv-rootfs` directory
    * Modify the contents of initramfs-autorun.txt and inittab to run the programs you want after Linux has booted (stream and redis by default)
* Reconfigure BBL
    * Enter `riscv-pk` directory
    * Modify the size of address space size in dts
    ```shell
    # ./riscv-pk/dts/noop.dtsi

	L11: memory@100000000 {
	    device_type = "memory";
	    -reg = <0x0 0x80000000 0x0 0x2000000>;
        +reg = <0x0 0x80000000 0x0 0x8000000>;
	};
    ```
    * After `make clean` run `make -j` to generate bbl.bin, let Xiangshan or NEMU run it



## 3. Based on this, how to run Debian distribution on NEMU

* Reconfigure the Linux Kernel
    * to the riscv-linux directory
    * Use debian_defconfig to configure, the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- debian_defconfig`
* Reconfigure BBL
    * Enter `riscv-pk` directory
    * Modify the bootargs in dts
    ```shell
    # ./riscv-pk/dts/noop.dtsi

	chosen {
        -bootargs = "root=/dev/mmcblk0 rootfstype=ext4 ro rootwait earlycon";
        +bootargs = "root=/dev/mmcblk0p1 rootfstype=ext4 ro rootwait earlycon";
    };
    ```
    (Please see [https://github.com/OpenXiangShan/NEMU/tree/master/resource/sdcard](https://github.com/OpenXiangShan/NEMU/tree/master/resource/sdcard))
    * After `make clean` run `make -j` to generate `bbl.bin`
* Configure NEMU
    * Enter `NEMU` directory
    * Edit `src/device/sdcard.c`, find the sdimg variable in the init_sdcard() function and assign it to the path of the Debian mirror (for the generation of the Debian mirror, please refer to [How to create a Debian image](./debian-en.md))
    * Recompile NEMU, and then run build/bbl.bin under the riscv-pk project


## 4. How to run Debian distribution on Xiangshan

* Configure Xiangshan
    * Enter `Xiangshan` directory
    * Edit the `./difftest/config/config.h` file, set the SDCARD_IMAGE macro to the path to the Debian image
    * Rebuild Xiangshan, then run build/bbl.bin under the riscv-pk project


#### 5. Based on this, how to build dualcore Linux kernal
* Reconfigure the Linux Kernel
    * Enter riscv-linux directory
    * `make clean`
    * Use emu_defconfig, fpga_defconfig or debian_defconfig to configure, command is same as above
    * Use menuconfig to configure SMP，the command is `make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- menuconfig`, in Platform type submenu, set Symmetric Multi-Processing to Yes, save it and exit
* Reconfigure BBL
    * Enter riscv-pk directory
    * `git stash`
    * `git checkout dualcore`
    * Modify the size of address space size in dts
    ```shell
    # ./riscv-pk/dts/noop.dtsi

	L11: memory@100000000 {
	    device_type = "memory";
	    -reg = <0x0 0x80000000 0x0 0x2000000>;
        +reg = <0x0 0x80000000 0x0 0x8000000>;
	};
    ```
    * When running 16g Debian, modify the bootargs in dts
    ```shell
    # ./riscv-pk/dts/noop.dtsi

	chosen {
        -bootargs = "root=/dev/mmcblk0 rootfstype=ext4 ro rootwait earlycon";
        +bootargs = "root=/dev/mmcblk0p1 rootfstype=ext4 ro rootwait earlycon";
    };
    ```
    * After `make clean` run `make -j` to generate `bbl.bin`
