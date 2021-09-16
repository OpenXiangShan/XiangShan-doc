# LightSSS 的使用



#### [可选] 配置修改

- LightSSS实现的主要代码包含在 `/difftest/src/test/csrc/verilator` 目录下的 `emu.cpp` 文件中
- LightSSS的配置文件在 `/difftest/config` 目录下的 `config.h` 文件中
- LightSSS默认fork的时间间隔为1秒，你可以在 `config.h` 文件中修改 `FORK_INTERVAL` 宏来更改时间间隔（单位为秒）

- 默认保存的快照数量为2，你可以在 `emu.h` 中更改 `SLOT_SIZE` 来修改设置.

#### [可选] 编译选项

- 在生成 emu 时加入编译选项 EMU_THREADS=n(n为线程数，n至少为2) EMU_TRACE=1 ：

```
make emu EMU_THREADS=8 EMU_TRACE=1 
```

**NOTE：使用 LightSSS 时请避免使用EMU_THREADS=1，因为1.单线程跑仿真速度很慢，我们仅仅用来跑测试用例，而测试用例一般波形和仿真时间都比较短，不需要用到lightSSS; 2.EMU_THREAD=1 编译时会报错，因为verilator在生成cpp时不会引入多线程的ThreadPool **

##### 

### 运行仿真存储快照

- 选择稍微大一点的程序，比如可以执行 `ready-to-run` 目录下的 `linux.bin`。在香山目录下执行如下命令：
- 打开emu的`--enable-fork`选项使能lightSSS
- 生成的波形文件默认保存到`$NOOP_HOME/build`下

```
cd ready-to-run
../build/emu -i linux.bin -I 20000 --enable-fork 2>/dev/null
```

- 上述命令会在香山上启动Linux并且只跑100000条指令。
- 启动后看到"enable fork debugging"信息，提示LightSSS成功启动

[![lightSSS1](https://z3.ax1x.com/2021/09/16/4nNzNV.jpg)](https://imgtu.com/i/4nNzNV)

- 到达最大指令数后，仿真停止，自动dump剩余的检查点到`$NOOP_HOME/build`目录下

[![lightSSS2](https://z3.ax1x.com/2021/09/16/4nUm4K.jpg)](https://imgtu.com/i/4nUm4K)


- dump波形结束后，打印出错信息，这里为了演示打印的是达到最大指令的信息（指令数，周期数，IPC）

[![lightSSS3](https://z3.ax1x.com/2021/09/16/4nUTV1.jpg)](https://imgtu.com/i/4nUTV1)

**注意：请提前设置好NOOP_HOME环境变量**

- [试一试？]感兴趣的朋友也可以选择自行修改RTL代码，让仿真触发difftest报错保存快照

