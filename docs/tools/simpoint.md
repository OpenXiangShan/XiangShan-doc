Checkpoint的生成和运行
=====================

!!! note
    Checkpoint 相关的功能目前依赖于一个独立的 NEMU 分支。主线上的 NEMU 并不支持 Checkpoint生成。

我们使用 NEMU 运行 workload 并生成 checkpoint，使用方式如下：

```bash
# 用NEMU进行simpoint profiling (以100M指令为周期)：
./build/riscv64-nemu-interpreter **$BBL_FOR_GCC_200** --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C run_spec -b **--simpoint-profile** --interval 100000000

# 用NEMU均匀地生成checkpoints (以1 Billion指令为周期)：
./build/riscv64-nemu-interpreter **$BBL_FOR_GCC_200** --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C run_spec -b **--checkpoint-interval** 1000000000

# 用NEMU同时均匀的生成checkpoint(1B)和进行simpoint profiling(100M)
./build/riscv64-nemu-interpreter $BBL_FOR_GCC_200 --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C run_spec -b --checkpoint-interval 1000000000 --simpoint-profile --interval 100000000
# !!请注意磁盘空间，取决于参数，可能占用几十~几千G

# NEMU生成的SimPoint profiling results和GEM5生成的完全一样，经过SimPoint clustering之后即可用于指导生成SimPoint checkpoints，我们假设clustering的结果在目录$POINTS_DIR
# 生成SimPoint checkpoints：
./build/riscv64-nemu-interpreter **$BBL_FOR_GCC_200** --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C take_cpt -S $POINTS_DIR
# !!请注意磁盘空间，取决于参数，整个SPEC06可能占用几十~几百G

# 恢复一个checkpoint，假设checkpoint文件为$CPT_GZ
./build/riscv64-nemu-interpreter **$BBL_FOR_GCC_200** --sdcard-img $SDCARD_IMG -D $TOP_OUTPUT_DIR -w gcc_200 -C restore_cpt -c $CPT_GZ
```

参数说明：

-  注意，-C（大C）是描述任务的名字，可以随便填，NEMU会把结果存放在相应的文件夹里 
-  w则对应-C下面一级的子目录 
-  -C spec_run -w namd 对应的目录结构就是 spec_run/namd 
-  $SDCARD_IMG是打包好的Linux和应用，可以是SPEC，也可以是其它程序。 
-  $BBL_FOR_GCC_200 是**让Linux启动后第一个程序执行gcc_200，通过BBL传参数给kernel**（如果写死在SDCARD里面的话，每个应用需要一个SDCARD，非常大） 
   - 这个要怎么使用呢？
-  SDCARD_IMG怎么生成？详见rootfs打包部分
## 准备工作：
### 环境变量

   1. SPEC: 设为 /bigdata/xs-workloads/spec/spec-all 
      1. 在下面编译spec-lite时，Makefile里也有一个SPEC，可以用于make init，把workload的数据拷贝过来，但是默认已经有了，所以并不需要。如果需要，需要设为 /bigdata/cpu2006v99
   2. RISCV：这个为riscv-toolchains，在易难师兄的目录下面有 
      1. 这个主要是为了一些库函数，在下面的init-ramfs.txt里面能够找到
   3. CROSS_COMPILE：这个在编译SPEC时需要手动指定，riscv64-linux-gnu-
   3. 编译器还需要一个riscv64-unknown-elf: 需要直接加到$PATH里面，参考易难师兄的zshrc 
      1. 当然也可以自己编译
   5. 编译器还需要一个riscv64-unknown-linux-**的路径，也需要加到PATH里面，也就是RISCV/bin，可以参考易难师兄的zshrc
### 准备spec

   1. 子濠师兄有个spec-lite，可以从易难师兄哪里拷贝过来
   1. 在仓库根目录直接make build-int不能正常生成程序：
      1. 编译时设置ARCH和CROSS_COMPILE
      1. 有两个程序，perlbench和dealII会出问题，其余程序可以正常编译
         1. dealII的gcc选项不对，有个x86架构的选项'-mlong-double-64'，删掉就可以了
         1. perlbench需要一个选项**-std=gnu89**，添加到CFLAGS就可以了
   3. 需要进入特定的程序目录下make CROSS_COMPILE=riscv64-linux-gnu-riscv64
   3. 生成的是每个spec程序的base程序，不针对某一个workload，也没有ref之类的区别
   3. 把生成的程序拷贝到$SPEC/spec06_exe下面，可以先复用原先的名字，名字在下面的riscv-rootfs里面写死了
### 准备NEMU

   1. 在NEMU的cpp-gem5分支
   1. 这个分支的main被改成了nemu_main，不知为何，所以不能跑了，改成main之后能跑 
      1. 猜测是需要后期生成simpoint checkpoint时需要，但是还没跑到这里，TODO
   3. 如果直接运行，报错没有gcpt.bin，因此在resource/gcpt_restore里面直接make 
      1. 还没搞懂是干什么的，也许后面需要
   4. 这个分支做了很多修改，外设对xiangshan做了对齐，还有一些对于checkpoint的奇怪设计，如load_img的起始地址不是0x80000000，而是增加了0xa0000. 因此对应的bin文件也需要做相应修改。 
      1. reset-vector不需要修改，放着checkpoint相关的代码。
      1. 修改bin文件的链接地址，从0x800a0000开始。见下面
   5. 默认不开始profiling，需要运行一个nemu_trap指令才能开启。
### 准备bin

   1. 准备riscv-rootfs: 
      1. 在rootfsimg下面，利用spec-gen.py可以生成启动linux后运行的脚本和initramfs-spec.txt，需要指定spec名和workload名 
         1. 默认是不开启profiling的，运行before_workload程序开始，在$SPEC目录下面有，似乎还关了时钟中断？
         1. 修改spec-gen.py，在运行spec之前，先运行before_workload
   2. 准备riscv-pk： 
      1. dts下面的platform-dtsi需要指向noop.dts，因为nemu的cpp-gem5分支，对齐了香山
      1. 修改bbl/bbl.lds，修改起始地址 . = MEM_START + 0xa0000.
      1. 直接make -j，尽量加上proxychains，还会下载riscv-linux,和其他一堆程序的代码，断了就不会重启（目录存在就不会再git clone了）
   3. 准备riscv-linux: 
      1. 在上面搞定了，但是有些riscv64交叉编译，因此需要提前把PATH搞好，不然会出错，可能不太容易看出来
      1. 需要make menuconfig -> General setup -> Initramfs source file，修改emu为spec
## 生成Simpoint Checkpoint
### profiling

   1. 参考最上面的命令行参数
   1. 不需要sdcard-img了，sdcard-img是为了同时可以跑多个程序，所以把程序都存在了一个sdcard上，可以都存了， 通过参数执行不同的程序。现在为了省事，每次都是不同的bin文件，就不需要sdcard-img了
   1. simpoint需要跑两轮，第一轮生成checkpoint和profiling，第二轮根据profiling和cpt生成simpoint checkpoint 
      1. 还没跑完，大致如此吧。
      1. 如何使用到第一轮生成的checkpoint: [take_simpoint_cpt.py](https://github.com/shinezyy/DirtyStuff/blob/main/nemutasks/take_simpoint_cpt.py)
   4. 命令示例：/bigdata/zzf/RISCVERS/NEMU/build/riscv64-nemu-interpreter /bigdata/zzf/RISCVERS/riscv-pk/build/bbl.bin -D /bigdata/zzf/spec_cpt -w gamess_cytosine -C run_spec -b --simpoint-profile --interval 100000000 --checkpoint-interval 100000000000
### cluster

   1. 在NEMU的resource/simpoint/simpoint_repo这里，是一个submodule，因此需要执行git submodule - - init，之后make，在bin文件得到一个可执行文件simpoint 
      1. 在这个目录下，还有个do_simpoint_balabala.py，运行之后发现没啥用，只能给怎么用simpoint做个例子，但是也没有注释，不知道为什么执行了10次这个指令，还有一堆奇奇怪怪的参数。
   2. 将simpoint_repo/bin加入到PATH中，方便之后使用
   2. 执行simpoint之后，可以得到一个weight文件和一个simpoint文件
### 生成simpoint checkpoint

   4. 和profiling类似，但是需要加上-S参数，同时还得有—checkpoint-intervel参数。
## 其他

1. 在NEMU/examples下面，有一些用例，可以参考
1. 发现生成的profiling的时候，顺便生成的checkpoints可以用于加速simpoint checkpoint的生成，不知道怎么用也没关系。感兴趣可以看这里[take_simpoint_cpt.py](https://github.com/shinezyy/DirtyStuff/blob/main/nemutasks/take_simpoint_cpt.py)
1. spec编译： 
   1. 


### interval的设置
参数中有两个interval，一个是'interval'，另一个是‘checkpoint-interval’，前者是profiling时的interval，后者时打checkpoint时的interval。容易混淆的是，后者是否也会是打simpoint profiling时的interval。**是的**。因此在打simpoint checkpoint时，需要checkpoint-interval，而不需要interval。
![image.png](https://cdn.nlark.com/yuque/0/2021/png/1658967/1629256983328-08316523-aded-4e26-bb75-a833f176d353.png#clientId=u249010a1-2dbf-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=650&id=ue2ab2d33&margin=%5Bobject%20Object%5D&name=image.png&originHeight=1300&originWidth=1128&originalType=binary&ratio=1&rotation=0&showTitle=false&size=574493&status=done&style=none&taskId=ufdcbdc8e-cc5f-4e99-bdb0-08daeba1771&title=&width=564)
### 自动生成目录：
有的命令可以自己生成文件夹，有的不行。如NEMU进行profiling和生成checkpoint可以自己生成workload的目录，但是simpoint生成simpints和weights不能够生成目录，因此需要手动生成

### 程序自动停止
cpt打完之后，程序并不会停下来。并且会继续后面的流程，然后打checkpoint时，simpoint2Weights数组里面已经空了，然后取出来的值是0，就会打一个0开始0权重的点，然后程序就卡住了，后面无论如何都会运行的Log没有打出来，然后程序也不会停止，不知道程序在做什么。
修改：当simpoint2Weights为空时，直接exit

### bug修改
shouldTakeCpt函数开头的判断逻辑写错了，会导致不会返回false

命令示例：
### 命令示例：
### profiling：
/bigdata/zzf/RISCVERS/NEMU/build/riscv64-nemu-interpreter /bigdata/zzf/RISCVERS/emubin/spec/wrf/bbl.bin -D /bigdata/zzf/spec_cpt -w wrf -C run_spec -b --simpoint-profile --interval 100000000 --checkpoint-interval 100000000000
### cluster：
simpoint -loadFVFile simpoint_bbv.gz -saveSimpoints simpoints0 -saveSimpointWeights weights0 -inputVectorsGzipped -maxK 30 -numInitSeeds 2 -iters 1000 -seedkm 123456 -seedproj 654321
### checkpointing
/bigdata/zzf/RISCVERS/NEMU/build/riscv64-nemu-interpreter /bigdata/zzf/RISCVERS/emubin/spec/gamess_cytosine/bbl.bin -D /bigdata/zzf/spec_cpt -w gamess_cytosine -C take_cpt -b -S /bigdata/zzf/spec_cpt/cluster --checkpoint-interval 100000000 2>&1 | tee /bigdata/zzf/temp/b.log

### 脚本：
```makefile
#!/bin/zsh

SPECINT = 400.perlbench 401.bzip2 403.gcc 429.mcf 445.gobmk 456.hmmer 458.sjeng 462.libquantum 464.h264ref 471.omnetpp 473.astar 483.xalancbmk
SPECFP = 410.bwaves 416.gamess 433.milc 434.zeusmp 435.gromacs 436.cactusADM 437.leslie3d 444.namd 447.dealII 450.soplex 453.povray 454.calculix 459.GemsFDTD 465.tonto 470.lbm 481.wrf 482.sphinx3

# SPECINT + SPECFP
SPECALL = $(SPECINT) $(SPECFP)
# SPECNAME without number
SPECALLNAME = $(foreach n,$(SPECALL),$(word 2,$(subst ., ,$(n))))

BASE_SUFFIX = _base.riscv64-linux-gnu-gcc-10.3.0
BASE_SRCDIR = /bigdata/zzf/RISCVERS/spec2006-lite
BASE_DESDIR = /bigdata/xs-workloads/spec/spec-all/spec06_exe
TEMPDIR = /bigdata/zzf/temp



tmp:
	echo $(SPECALLNAME)


# ==================== build-spec ==================
#
build-spec:
	@echo make build-int and build-fp in spec2006-lite
    @echo the spec2006-lite has some bugs, make sure you have fix it


# ==================== cp spec ====================

# /bigdata is only allowed for user xs to write, please switch to xs first.
cp-spec:
	cp $(foreach t,$(SPECALL),$(BASE_SRCDIR)/$(t)/build/$(word 2,$(subst ., ,$(t)))) $(TEMPDIR)
	for t in $(SPECALLNAME); do \
		cp $(TEMPDIR)/$$t $(BASE_DESDIR)/$${t}$(BASE_SUFFIX); \
	done


# ==================== build bin and cp ===============

# short can finish in 3 days in epyc 150.
# long may finish in 3 days in intel 10850.
# you can run different workloads on different machines.
SPECWORKLOAD_LONG = cactusADM \
	calculix \
	gamess_triazolium \
	h264ref_sss \
	sphinx3 \
	tonto \
	hmmer_retro

SPECWORKLOAD_SHORT = astar_biglakes \
	astar_rivers \
	bwaves \
	bzip2_chicken \
	bzip2_combined \
	bzip2_html \
	bzip2_liberty \
	bzip2_program \
	bzip2_source \
	dealII \
	gamess_cytosine \
	gamess_gradient \
	gcc_166 \
	gcc_200 \
	gcc_cpdecl \
	gcc_expr2 \
	gcc_expr \
	gcc_g23 \
	gcc_s04 \
	gcc_scilab \
	gcc_typeck \
	GemsFDTD \
	gobmk_13x13 \
	gobmk_nngs \
	gobmk_score2 \
	gobmk_trevorc \
	gobmk_trevord \
	gromacs \
	h264ref_foreman.baseline \
	h264ref_foreman.main \
	hmmer_nph3 \
	lbm \
	leslie3d \
	libquantum \
	mcf \
	milc \
	namd \
	omnetpp \
	perlbench_checkspam \
	perlbench_diffmail \
	perlbench_splitmail \
	povray \
	sjeng \
	soplex_pds-50 \
	soplex_ref \
	wrf \
	xalancbmk \
	zeusmp

SPECWORKLOAD = $(SPECWORKLOAD_LONG) $(SPECWORKLOAD_SHORT)

RISCV_ROOTFS_HOME ?= /bigdata/zzf/RISCVERS/riscv-rootfs
RISCV_PK_HOME ?= /bigdata/zzf/RISCVERS/riscv-pk
SPECBIN_DIR = /bigdata/zzf/spec_cpt/bins
SPECBIN_NORMAL_DIR = /bigdata/zzf/spec_cpt/normal-bins

# when build-bin, please do-not use -j, all the jobs use one riscv-pk/linux-rootfs
build-bin:
	for t in $(SPECWORKLOAD); do \
		cd $(RISCV_ROOTFS_HOME)/rootfsimg; \
		python3 spec_gen_10.py $${t}; \
		$(MAKE) -C $(RISCV_PK_HOME) clean; \
		$(MAKE) -C $(RISCV_PK_HOME) -j; \
		mkdir -p $(SPECBIN_DIR)/$${t}; \
  	cp $(RISCV_PK_HOME)/build/bbl.txt $(SPECBIN_DIR)/$${t}/; \
  	cp $(RISCV_PK_HOME)/build/bbl.bin $(SPECBIN_DIR)/$${t}/; \
  	cp $(RISCV_PK_HOME)/build/vmlinux.txt $(SPECBIN_DIR)/$${t}/; \
  	cp $(RISCV_PK_HOME)/build/bbl $(SPECBIN_DIR)/$${t}/; \
		cd -; \
	done

# ========================= profiling ========================

# NEMU = /bigdata/zzf/spec_cpt/nemu/riscv64-nemu-interpreter
NEMU = /bigdata/zzf/RISCVERS/NEMU/build/riscv64-nemu-interpreter
ROOT_DIR = /bigdata/zzf/spec_cpt
PROFILE_DIR = profiling
CLUSTER_DIR = cluster
CHECKPOINT_DIR = take_cpt
LOG_DIR = logs

ENABLE_PROFILE = --simpoint-profile
PROFILE_INTERVAL = --interval 20000000
CHECKPOINT_INTERVAL = --checkpoint-interval 20000000
ENABLE_SIMPOINTCPT = -S $(ROOT_DIR)/$(CLUSTER_DIR)

simpoint:
	mkdir -p ${ROOT_DIR}/${PROFILE_DIR};
	mkdir -p ${ROOT_DIR}/${CLUSTER_DIR};
	mkdir -p ${ROOT_DIR}/${CHECKPOINT_DIR};
	for t in $(SPECWORKLOAD); do \
	{ mkdir -p $(ROOT_DIR)/${CLUSTER_DIR}/$${t} \
		&& simpoint -loadFVFile ${ROOT_DIR}/${PROFILE_DIR}/$${t}/simpoint_bbv.gz -saveSimpoints ${ROOT_DIR}/${CLUSTER_DIR}/$${t}/simpoints0 -saveSimpointWeights ${ROOT_DIR}/${CLUSTER_DIR}/$${t}/weights0 -inputVectorsGzipped -maxK 30 -numInitSeeds 2 -iters 1000 -seedkm 123456 -seedproj 654321 2>&1 | tee ${ROOT_DIR}/${LOG_DIR}/cluster/$${t}.log \
		&& $(NEMU) $(SPECBIN_DIR)/$${t}/bbl.bin -D $(ROOT_DIR) -w $${t} -C $(CHECKPOINT_DIR) -b $(ENABLE_SIMPOINTCPT) ${CHECKPOINT_INTERVAL} 2>&1 | tee ${ROOT_DIR}/${LOG_DIR}/take_cpt/$${t}.log; }& \
	done

# $(NEMU) $(SPECBIN_DIR)/$${t}/bbl.bin -D $(ROOT_DIR) -w $${t} -C $(PROFILE_DIR) -b $(ENABLE_PROFILE) $(PROFILE_INTERVAL) 2>&1 | tee ${ROOT_DIR}/${LOG_DIR}/profiling/$${t}.log &&


clean:
	rm -r $(TEMPDIR)/*

clean-bins:
	rm -r $(SPECBIN_DIR)/*

clean-cluster:
	rm -r ${ROOT_DIR}/${CLUSTER_DIR}/*

clean-cpt:
	rm -r ${ROOT_DIR}/${CHECKPOINT_DIR}/*

clean-sim:
	rm -rf ${ROOT_DIR}/${PROFILE_DIR}/*
	rm -rf ${ROOT_DIR}/${CLUSTER_DIR}/*
	rm -rf ${ROOT_DIR}/${CHECKPOINT_DIR}/*
	rm -rf ${ROOT_DIR}/${LOG_DIR}/profiling/*
	rm -rf ${ROOT_DIR}/${LOG_DIR}/cluster/*
	rm -rf ${ROOT_DIR}/${LOG_DIR}/take_cpt/*

# rm -r $(BASE_DESDIR)/*

```
# 结果
地址：/bigdata/zzf/spec_cpt

1. 目录take_cpt：生成的checkpoints
1. 文件simpoint_summary.json，记录workload的checkpoints的信息
1. 目录bins：跑checkpoint时用到的spec的bin
1. 目录profiling：记录profiling的结果
1. 目录cluster：同上
1. 目录normal-bins：记录正常编译的spec的bin，但是都有非对其访问的问题，nemu不支持，所以还没法使用
1. 目录scripts：脚本，但是就一个Makefile和一个gen_json.py
