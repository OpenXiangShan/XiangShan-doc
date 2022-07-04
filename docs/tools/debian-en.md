# How to create a Debian image

This chapter is translated from [https://github.com/OpenXiangShan/NEMU/tree/master/resource/debian](https://github.com/OpenXiangShan/NEMU/tree/master/resource/debian).

`qemu-riscv64-static` is used to create a debian image. We recommend using debian 10 or ubuntu 19.04. (Maybe docker can help you)

* Create an empty image and create partitions

```
dd if=/dev/zero of=debian.img bs=1G count=16  # Here image size is 16G
sudo cfdisk debian.img # Create two partitions, first 12GB is used as rootfs, left 4GB is used as swap
sudo losetup --partscan --show --find debian.img # Start the loop device
ls /dev/loop0* # You should see /dev/loop0p1 and /dev/loop0p2
```

* Create ext4 and swap file systems

```
sudo mkfs.ext4 /dev/loop0p1
sudo mkswap /dev/loop0p2
```

* Mount the ext4 partition

```
sudo mount /dev/loop0p1 /mnt
```

* Install debian base system. Operations of the following two commands are from[ guidance of debian community](https://wiki.debian.org/RISC-V#debootstrap)

```
sudo apt-get install debootstrap qemu-user-static binfmt-support debian-ports-archive-keyring
sudo debootstrap --arch=riscv64 --keyring /usr/share/keyrings/debian-ports-archive-keyring.gpg --include=debian-ports-archive-keyring unstable /mnt http://deb.debian.org/debian-ports
```

To install an x86 operating system, type

```
sudo debootstrap --arch=i386 --keyring /usr/share/keyrings/debian-archive-keyring.gpg --include=debian-archive-keyring stable /mnt http://deb.debian.org/debian
```

You can install the newest package manually from the listed mirrors of [debian official image website](https://packages.debian.org/bullseye/all/debian-ports-archive-keyring/download) if gpg key error is given when running the above `debootstrap` command. After updating the debian-ports-archive-keyring package, you can execute the above `debootstrap` command again. The following commands are available on July 3, 2022:

```
wget http://ftp.cn.debian.org/debian/pool/main/d/debian-ports-archive-keyring/debian-ports-archive-keyring_2022.02.15\~deb11u1_all.deb .
sudo dpkg -i debian-ports-archive-keyring_2022.02.15\~deb11u1_all.deb
```

* Access the image

```
sudo chroot /mnt /bin/bash
```

Riscv64 executable files in the image is executed by `qemu-riscv64-static` actually.

* Install the packages needed for the system (You can choose on your actual situation)

```
apt-get update
apt-get install gcc build-essential
apt-get install tmux libreadline-dev
apt-get install net-tools openssh-server
# fix long delay of openssh server
apt-get install haveged
agt-get install sbt
```

* Add swap partition in `/etc/fstab`

```
/dev/mmcblk0p2 none swap sw 0 0
```

* Add write and execute permissions to `/root/` directory so that normal users on host can access it

```
chmod +w,+x /root
```

* Write required test files in `/root/` directory in advance, such as `hello.c`, etc

* Add following contents to `/root/.bashrc` in order to run commands automatically after login (You can modify on your actual situation):

```
TMP_DIR=/run/mytest

cmd=(
# enbale swap
  "swapon -a"

# show system information
  "uname -a"
  "cat /etc/issue"
  "cat /proc/cpuinfo"
  "df -ah"
  "free -h"

# show time
  "date"
  "uptime"

# create and switch to tmp directory
  "mkdir $TMP_DIR"
  "cd $TMP_DIR"

# compile and run hello
  "ls /root"
  "ls /root/hello"
  "cat /root/hello/hello.c"
  "gcc -time /root/hello/hello.c -o $TMP_DIR/hello"
  "ls -lh $TMP_DIR"
  "$TMP_DIR/hello"

# compile and run x86-nemu
  "ls /root/nemu"
  "cp -r /root/nemu $TMP_DIR"
  "export NEMU_HOME=$TMP_DIR/nemu"
  "make -C $TMP_DIR/nemu ISA=x86"
  "ls -lh /root/nemu-prog"
  "file /root/nemu-prog/amtest-x86-nemu.elf"
  "$TMP_DIR/nemu/build/x86-nemu --batch --mainargs=h /root/nemu-prog/amtest-x86-nemu.bin"
  "file /root/nemu-prog/microbench-x86-nemu.elf"
  "$TMP_DIR/nemu/build/x86-nemu --batch --mainargs=test /root/nemu-prog/microbench-x86-nemu.bin"

# compile and run riscv64-nemu
  "make -C $TMP_DIR/nemu clean"
  "make -C $TMP_DIR/nemu ISA=riscv64"
  "$TMP_DIR/nemu/build/riscv64-nemu --batch /root/nemu-prog/linux-hello-riscv64-nemu.bin"
)

prompt="`whoami`@`hostname`:`pwd`#"

echo -e "\n============ Now running preset commands =============\n"

for ((i = 0; i < ${#cmd[@]}; i++)); do
  c=${cmd[$i]}
  echo "$prompt $c"
  $c
  echo ""
done

echo -e "\n============ End of preset commands =============\n"

/root/nemutrap/good-trap
```

* You can choose one of the following methods to avoid input when login if you test in an inconvenient input environment. (Such as NEMU, verilator simulation, etc)

    * Login through emergency mode

    ```
    cd /lib/systemd/system
    # Login through emergency mode. It can save nearly half of the login time as unnecessary services are not started
    ln -sf emergency.target default.target
    # Run bash directly and skip login prompt
    vim emergency.service
      -ExecStart=-/lib/systemd/systemd-sulogin-shell emergency
      +ExecStart=-/bin/bash
    ```

    * Login without password，see [here](https://superuser.com/questions/969923/automatic-root-login-in-debian-8-0-console-only)

    ```
    cd /lib/systemd/system
    vim serial-getty@.service
      -ExecStart=-/sbin/agetty -o '-p -- \\u' --keep-baud 115200,57600,38400,9600 %I $TERM
      +ExecStart=-/sbin/agetty -a root --keep-baud 115200,57600,38400,9600 %I $TERM
    ```

* Exit and unmount the image

```
exit  # Entered with `chroot` command before
sudo umount /mnt  # Do not forget to umount! Image will be damaged if you reopen `debian.img` through writeable access without umount. (Such as  implemented as file system of qemu)
sudo losetup -d /dev/loop0  # Delete loop device
```

* You can use the image after modifying the `img` in `init_sdcard()` of `nemu/src/device/sdcard.c`. We tested on i9-9900k and the debian login prompt appeared after about 90s.

* Opening image through writeable access means that, crash consistency may be damaged when NEMU encounters an error or being exited directly with Ctrl+C. You can repair the partition with `fsck` command at that time.