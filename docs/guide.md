# 香山项目导引

## 香山项目链接

- GitHub：[https://github.com/OpenXiangShan](https://github.com/OpenXiangShan)

- 码云/Gitee：[https://gitee.com/OpenXiangShan](https://gitee.com/OpenXiangShan)

- 确实/GitLink：[https://gitlink.org.cn/OpenXiangShan/XiangShan](https://gitlink.org.cn/OpenXiangShan/XiangShan)

## 香山文档链接

- 处理器核介绍：[https://xiangshan-doc.readthedocs.io/zh_CN/latest/arch/](https://xiangshan-doc.readthedocs.io/zh_CN/latest/arch/)

- 敏捷开发框架

    - 使用说明：[https://xiangshan-doc.readthedocs.io/zh_CN/latest/tools/xsenv/](https://xiangshan-doc.readthedocs.io/zh_CN/latest/tools/xsenv/)

    - 工具介绍：[https://xiangshan-doc.readthedocs.io/zh_CN/latest/tools/difftest/](https://xiangshan-doc.readthedocs.io/zh_CN/latest/tools/difftest/)

    - Troubleshooting：[https://xiangshan-doc.readthedocs.io/zh_CN/latest/tools/troubleshoot/](https://xiangshan-doc.readthedocs.io/zh_CN/latest/tools/troubleshoot/)

- 工具链编译：[https://xiangshan-doc.readthedocs.io/zh_CN/latest/compiler/gnu_toolchain/](https://xiangshan-doc.readthedocs.io/zh_CN/latest/compiler/gnu_toolchain/)

## 香山项目仓库介绍

香山本身的 RTL 代码：

* [**XiangShan**](https://github.com/OpenXiangShan/XiangShan)：香山处理器实现

* [**HuanCun**](https://github.com/OpenXiangShan/HuanCun)：香山处理器的非阻塞 L2/L3 缓存

* [**FuDian**](https://github.com/OpenXiangShan/fudian)：香山处理器的浮点部件

香山的仿真环境：

* [**Difftest**](https://github.com/OpenXiangShan/XiangShan)：香山使用的处理器协同仿真框架

* [**NEMU**](https://github.com/OpenXiangShan/NEMU/tree/master)：一个效率接近 QEMU 的高性能 ISA 解释器，这里有一个[介绍视频](https://www.bilibili.com/video/BV1Zb4y1k7RJ)

* [**nexus-am**](https://github.com/OpenXiangShan/nexus-am)：Abstract Machine，提供程序的运行时环境，这里有一个[简单的介绍](https://nju-projectn.github.io/ics-pa-gitbook/ics2020/2.3.html)

* [**DRAMsim3**](https://github.com/OpenXiangShan/DRAMsim3)：Cycle-level 地模拟内存的行为，针对香山项目进行了配置

* [**env-scripts**](https://github.com/OpenXiangShan/env-scripts)：一些脚本文件，包括性能分析、模块替换和时序分析等

* [**xs-env**](https://github.com/OpenXiangShan/xs-env)：香山处理器前端开发环境部署脚本

香山的文档：

* [**XiangShan-doc**](https://github.com/OpenXiangShan/XiangShan-doc)：香山处理器文档，包括设计文档、公开报告以及对错误新闻的澄清

香山项目下的其他仓库还包括 **riscv-linux** ，**riscv-pk** ，**riscv-torture** 等等。

## 香山处理器目录结构

[**XiangShan**](https://github.com/OpenXiangShan/XiangShan) 主仓库的目录结构如下：

```
.
├── scripts              # 生成 Verilog 及仿真使用的一些脚本
├── src                  # 结构设计与验证代码
│   └── main               # 结构设计代码
│       └── scala
│           ├── device         # 仿真用的一些外设
│           ├── system         # SoC 的描述
│           ├── top            # 顶层文件
│           ├── utils          # 一些基础硬件工具库
│           ├── xiangshan      # 香山 CPU 部分的设计代码
│           └── xstransforms   # 一些 FIRRTL Transforms
├── fudian               # 香山浮点子模块
├── huancun              # 香山 L2/L3 缓存子模块
├── difftest             # 香山协同仿真框架
├── ready-to-run         # 预先编译好的 nemu 动态链接库，和一些负载
└── rocket-chip          # 用来获取 Diplomacy 框架（等待上游拆分）
```
