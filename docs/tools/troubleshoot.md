Compiling Troubleshooting Guide
================

* Make sure your device have enough memory. Xiangshan project is quite memory intensive. We recommend 32GB memory for MinimalConfig and 64GB memory for full XiangShan. ([https://github.com/OpenXiangShan/XiangShan/issues/995](https://github.com/OpenXiangShan/XiangShan/issues/995))
    * Change swap size may help. ([https://github.com/OpenXiangShan/XiangShan/issues/852](https://github.com/OpenXiangShan/XiangShan/issues/852))

* Check Java version. XiangShan requires Java 11 or higher version. We have already know that XiangShan does not work on Java 8.
    * By the way, we recommend using graalvm to reduce memory cost and speedup compiling as well. ([https://github.com/OpenXiangShan/XiangShan/issues/997](https://github.com/OpenXiangShan/XiangShan/issues/997))

* Check JVM arguments. `-Xmx64G` in `XiangShan/build.sc` may influence XiangShan compiling. (Chinese: [https://github.com/OpenXiangShan/XiangShan/issues/906](https://github.com/OpenXiangShan/XiangShan/issues/906))

* Check Verilator version. Fork-wait based simulation snapshot requires Verilator v4.204. We suggest you use that version instead of `apt get` version (which is much lower). To setup Verilator manually, see [https://github.com/OpenXiangShan/xs-env/blob/master/install-verilator.sh](https://github.com/OpenXiangShan/xs-env/blob/master/install-verilator.sh) (Verilator v4.204) or [https://verilator.org/guide/latest/install.html](https://verilator.org/guide/latest/install.html) (Offical Verilator install instructions).

* Check if submodules are initialized correctly. If you meet strange syntax errors from submodules or XiangShan itself, it may because of that submodules are not initialized correctly. Run `make init` in `XiangShan` to re-init submodules may help.
    * Make sure your device have access to GitHub. XiangShan needs to clone submodules from GitHub. Or you may download these submodules manually.

* Try Minimal XiangShan first. XiangShan's default config will take quite long time and huge memory space to build. We suggest you try Minimal XiangShan (`make emu CONFIG=MinimalConfig`) first to make sure the environment is set up correctly. ([https://github.com/OpenXiangShan/XiangShan/issues/852](https://github.com/OpenXiangShan/XiangShan/issues/852))

* Commands for generating behavior simulation verilog and synthesizable verilog are different. Run `make verilog` to generate synthesizable verilog. Run `make emu` for behavior simulation ([https://github.com/OpenXiangShan/XiangShan/issues/933](https://github.com/OpenXiangShan/XiangShan/issues/933))

By the way, [https://github.com/OpenXiangShan/xs-env](https://github.com/OpenXiangShan/xs-env) provides scripts for installing XiangShan dependencies and a detailed document (Chinese only, En WIP) about how to set up XiangShan develop environment.