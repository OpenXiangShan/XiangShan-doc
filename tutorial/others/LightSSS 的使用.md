# LightSSS 的使用



#### [可选] 配置修改

- LightSSS实现的主要代码包含在 `src/test/csrc/verilator` 目录下的 `emu.h` 和 `emu.cpp` 文件中
- LightSSS默认fork的时间间隔为10秒，你可以在 `emu.h` 文件中修改 `FORK_INTERVAL` 宏来更改时间间隔（单位为秒）

- 默认保存的快照数量为2，你可以在 `emu.h` 中更改 `SLOT_SIZE` 来修改设置，注意这里的数量等于快照数量+1（有一个控制进程）

#### [可选] 编译选项

- 在生成 emu 时加入编译选项 EMU_FORKWAIT=1 和 EMU_TRACE=1：

```
make emu EMU_FORKWAIT=1 EMU_TRACE=1 
```

**由于存在潜在的 Bug，使用 LightSSS 时请避免使用verilator的多线程选项，否则会造成 emulator 卡死的情况。该问题将在近期修复.**

##### 

### 运行仿真存储快照

- 选择稍微大一点的程序，比如可以执行 `ready-to-run` 目录下的 `linux.bin`。在香山目录下执行如下命令：

```
cd ready-to-run
../build/emu -i linux.bin -I 100000 -b 0 -e -1 2>/dev/null
```

- 上述命令会在香山上启动Linux并且只跑100000条指令。
- 启动后看到如下信息，提示LightSSS成功启动

![img](https://cdn.nlark.com/yuque/0/2021/jpeg/1648845/1624554647672-319f50a4-6635-49aa-8ef4-3b4703d2a037.jpeg)

- 到达最大指令数后，仿真停止，打印信息（第二个 `EXCEEDING` 信息可以忽略）

![img](https://cdn.nlark.com/yuque/0/2021/jpeg/1648845/1624554655699-d6107729-6bcf-4424-828f-4920e089ade2.jpeg)

- 这时保存仿真信息的进程被唤醒开始打印波形，默认保存两个快照，完成后主进程退出

![img](https://cdn.nlark.com/yuque/0/2021/jpeg/1648845/1624554665435-90e7dd29-b771-40ff-a5ea-503f9e28db87.jpeg)

- 快照进程产生的波形文件在build目录下

![img](https://cdn.nlark.com/yuque/0/2021/jpeg/1648845/1624554677375-fa7cbb6c-62fc-45ee-9830-39aa0e4910e2.jpeg)

**注意：请提前设置好NOOP_HOME环境变量，快照保存的波形会放在NOOP_HOME/build目录下**

- [试一试？]感兴趣的朋友也可以选择自行修改RTL代码，让仿真触发difftest报错保存快照

