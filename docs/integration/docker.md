<style> 
     pre { 
         overflow-y: auto; 
         max-height: 512px; 
     }
</style>

# Docker Instruction
## 准备
在需要部署的服务器上安装docker应用
## 服务器导入docker镜像
云盘下载链接：(7z自解压文件)

[阿里云盘分享](https://www.aliyundrive.com/s/1abKfjYKWJ6)

Docker镜像MD5SUM：3ebafca4bfaa53c93abaf6ab3a3a8626

进入服务器后执行以下命令，结果如下
```
docker load --input <服务器镜像路径(蓝字部分)>
docker images   # 执行后可以看到image_id,大小为4.53GB
pwd	  #执行后得到<宿主机上文件夹的绝对路径>
docker run -it -v <宿主机上文件夹的绝对路径>:</home/your_name(尽量填名字方便找)> image_id /bin/bash
```
![load_docker_image.jpeg](../figs/docker_images/load_docker_image.jpeg)
## 进入容器，完成用户切换
```
addgroup --gid 5 your_name
adduser --uid 4 --gid 5 your_name
su your_name   #切换到用户, 至此环境部署完毕
```
![user_switch_1.jpeg](../figs/docker_images/user_switch_1.jpeg)
![user_switch_2.jpeg](../figs/docker_images/user_switch_2.jpeg)
## 添加环境变量
```
vim ~/.bashrc
export  RISCV="/opt/riscv"
export PATH=$RISCV/bin:$PATH
export CROSS_COMPILE=riscv64-unknown-linux-gnu-
export ARCH=riscv
source  ~/.bashrc
```
![set_env.jpeg](../figs/docker_images/set_env.jpeg)
## 获取源码并编译（基于南湖FPGA开源最小系统）
### 获取源码并cp到服务器下
```
git clone git@github.com:OpenXiangShan/ns-bbl.git -b nanhu-dualcore-fpga
cd ns-bbl
rm -r riscv-linux riscv-pk riscv-rootfs
git clone git@github.com:openxiangshan/riscv-linux.git -b linux-5.10.167
git clone git@github.com:openxiangshan/riscv-pk.git -b nanhu-mini-sys
git clone git@github.com:openxiangshan/riscv-rootfs.git -b nanhu-nfs
mkdir build
cd ../
scp -r ns-bbl/ your_name@<服务器IP>:<宿主机上文件夹的绝对路径>
```
### 定制app 到rootfs.cpio （选做）

准备，在docker中先交叉编译定制app，生成可执行文件

```
例：将i2cdelect命令加入 rootfs.cpio
cpio -imdv < rootfs.cpio  //解压原始rootfs.cpio
chmod 777 i2cdelect | cp i2cdelect /usr/bin/  //可执行文件需要赋777权限
sudo chown -R root:root .
find . | cpio -o -H newc > ../rootfs.cpio  //打包新的rootfs.cpio
cp ../rootfs.cpio ns-bbl  //拷贝使用
```
### 编译
```
cd riscv-linux
make nanhu_fpga_defconfig
cd ../
make sw -j200  #完成后buid目录下有linux.bin
```
![compile.jpeg](../figs/docker_images/compile.jpeg)
### 生成烧录FPGA的txt文件
在linux环境下使用下面的工具，将linux.bin生成烧录FPGA的txt文件

[bin2fpgadata.tar.gz](https://raw.githubusercontent.com/OpenXiangShan/XiangShan-doc/main/docs/integration/resources/bin2fpgadata.tar.gz)
```
#生成data.txt
<bin2fpgadata路径>/bin2fpgadata -i linux.bin
```

## 获取源码并编译（基于南湖v3的四核系统）

### 获取源码并cp到服务器下

```shell
git clone git@github.com:OpenXiangShan/ns-bbl.git -b nanhu-dualcore-fpga
cd ns-bbl
rm -r riscv-linux riscv-pk riscv-rootfs
git clone git@github.com:OpenXiangShan/riscv-linux.git -b linux-5.10.167
git clone git@github.com:OpenXiangShan/riscv-pk.git -b nanhu-v3
git clone git@github.com:OpenXiangShan/riscv-rootfs.git -b nanhu-nfs
mkdir build
cd ../
scp -r ns-bbl/ your_name@<服务器IP>:<宿主机上文件夹的绝对路径>
```

 

### 替换设备树

使用如下文件替换/ns-bbl/riscv-pk/dts/system.dts文件

```dts
/dts-v1/;

/ {
    #address-cells = <2>;
    #size-cells = <2>;
    compatible = "freechips,rocketchip-unknown-dev";
    model = "freechips,rocketchip-unknown";
    cpus {
        #address-cells = <1>;
        #size-cells = <0>;
        timebase-frequency = <500000>;//100Khz
        cpu0: cpu@0 {
            clock-frequency = <1000000>;
            compatible = "XiangShan,Nanhu-v3", "riscv";
            d-cache-block-size = <64>;
            d-cache-sets = <64>;
            d-cache-size = <16384>;
            d-tlb-sets = <1>;
            d-tlb-size = <32>;
            device_type = "cpu";
            i-cache-block-size = <64>;
            i-cache-sets = <64>;
            i-cache-size = <16384>;
            i-tlb-sets = <1>;
            i-tlb-size = <32>;
            mmu-type = "riscv,sv39";
            next-level-cache = <&memory>;
            reg = <0x0>;
            riscv,isa = "rv64imafdc";
            status = "okay";
            timebase-frequency = <500000>;//100Khz
            tlb-split;
            cpu0_intc: interrupt-controller {
            	#interrupt-cells = <1>;
            	compatible = "riscv,cpu-intc";
            	interrupt-controller;
            };
        };

        cpu1: cpu@1 {
            clock-frequency = <0>;
            compatible = "XiangShan,Nanhu-v3", "riscv";
            d-cache-block-size = <64>;
            d-cache-sets = <64>;
            d-cache-size = <16384>;
            d-tlb-sets = <1>;
            d-tlb-size = <32>;
            device_type = "cpu";
            i-cache-block-size = <64>;
            i-cache-sets = <64>;
            i-cache-size = <16384>;
            i-tlb-sets = <1>;
            i-tlb-size = <32>;
            mmu-type = "riscv,sv39";
            next-level-cache = <&memory>;
            reg = <0x1>;
            riscv,isa = "rv64imafdc";
            status = "okay";
            timebase-frequency = <100000>;//100Khz
            tlb-split;
            cpu1_intc: interrupt-controller {
            	#interrupt-cells = <1>;
            	compatible = "riscv,cpu-intc";
            	interrupt-controller;
            };
        };
    
        cpu2: cpu@2 {
            clock-frequency = <0>;
            compatible = "XiangShan,Nanhu-v3", "riscv";
            d-cache-block-size = <64>;
            d-cache-sets = <64>;
            d-cache-size = <16384>;
            d-tlb-sets = <1>;
            d-tlb-size = <32>;
            device_type = "cpu";
            i-cache-block-size = <64>;
            i-cache-sets = <64>;
            i-cache-size = <16384>;
            i-tlb-sets = <1>;
            i-tlb-size = <32>;
            mmu-type = "riscv,sv39";
            next-level-cache = <&memory>;
            reg = <0x2>;
            riscv,isa = "rv64imafdc";
            status = "okay";
            timebase-frequency = <100000>;//100Khz
            tlb-split;
            cpu2_intc: interrupt-controller {
                #interrupt-cells = <1>;
                compatible = "riscv,cpu-intc";
                interrupt-controller;
            };
        };
    
        cpu3: cpu@3 {
            clock-frequency = <0>;
            compatible = "XiangShan,Nanhu-v3", "riscv";
            d-cache-block-size = <64>;
            d-cache-sets = <64>;
            d-cache-size = <16384>;
            d-tlb-sets = <1>;
            d-tlb-size = <32>;
            device_type = "cpu";
            i-cache-block-size = <64>;
            i-cache-sets = <64>;
            i-cache-size = <16384>;
            i-tlb-sets = <1>;
            i-tlb-size = <32>;
            mmu-type = "riscv,sv39";
            next-level-cache = <&memory>;
            reg = <0x3>;
            riscv,isa = "rv64imafdc";
            status = "okay";
            timebase-frequency = <100000>;//100Khz
            tlb-split;
            cpu3_intc: interrupt-controller {
                #interrupt-cells = <1>;
                compatible = "riscv,cpu-intc";
                interrupt-controller;
            };
        };
    
    };
    
    soc {
        #address-cells = <2>;
        #size-cells = <2>;
        compatible = "freechips,rocketchip-unknown-soc", "simple-bus";
        ranges;
        debug_controller0: debug-controller@0 {
        	compatible = "sifive,debug-013", "riscv,debug-013";
        	interrupts-extended = <&cpu0_intc 65535>;
        	reg = <0x0 0x0 0x0 0x1000>;
        	reg-names = "control";
        };
        
        clint0: clint@38000000 {
            compatible = "riscv,clint0";
            interrupts-extended = <&cpu0_intc 3 &cpu0_intc 7 &cpu1_intc 3 &cpu1_intc 7 &cpu2_intc 3 &cpu2_intc 7 &cpu3_intc 3 &cpu3_intc 7>;
            reg = <0x0 0x38000000 0x0 0x10000>;
            reg-names = "control";
            clock-frequency-mhz = <10>;
        };
    
        PLIC: interrupt-controller@3c000000 {
            #interrupt-cells = <1>;
            compatible = "riscv,plic0";
            interrupt-controller;
            interrupts-extended = <&cpu0_intc 0xb &cpu0_intc 0x9 &cpu1_intc 0xb &cpu1_intc 0x9 &cpu2_intc 0xb &cpu2_intc 0x9 &cpu3_intc 0xb &cpu3_intc 0x9>;
            reg = <0 0x3c000000 0 0x4000000>;
            reg-names = "control";
            riscv,max-priority = <7>;
            riscv,ndev = <64>;
        };
    
        clkc: misc_clk_0 {
            #clock-cells = <0>;
            clock-frequency = <10000000>;
            compatible = "fixed-clock";
        };
    
        serial@310B0000 {
            compatible = "ns16550a";
            reg = <0x0 0x310B0000 0x0 0x10000>;
            reg-shift = <0x02>;
            reg-io-width = <0x04>;
            interrupt-parent = <&PLIC>;
            interrupts = <40>;
            clock-frequency = <10000000>;
            status = "okay";
        };
    
    };
    
    chosen {
         bootargs = "root=/dev/nvme0n1p2 rootfstype=ext4 rw rootwait console=ttyS0,9600n8 earlycon noinitrd";
         stdout-path = "/soc/serial@310B0000";
    };
    
    memory: memory@100000000 {
         device_type = "memory";
         reg = <0x0 0x80000000 0x0 0x80000000>;
    };

};
```


### 编译

```shell
cd riscv-linux
make nanhu_fpga_defconfig
cd ../
make sw -j2 # 完成后buid目录下有linux.bin
```

### 生成烧录FPGA的txt文件
在linux环境下使用下面的工具，将linux.bin生成烧录FPGA的txt文件

[bin2fpgadata.tar.gz](https://raw.githubusercontent.com/OpenXiangShan/XiangShan-doc/main/docs/integration/resources/bin2fpgadata.tar.gz)
```
#生成data.txt
<bin2fpgadata路径>/bin2fpgadata -i linux.bin
```

## 测试（以南湖FPGA开源最小系统为例）
按照[基于南湖的FPGA开源最小系统构建](https://xiangshan-doc.readthedocs.io/zh_CN/latest/integration/fpga/#_1)中演示的操作，将生成好的txt文件放到最小系统中就能进行测试
