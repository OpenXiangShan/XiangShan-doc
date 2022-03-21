# 使用 AM 生成自定义 workload



我们以在AM环境下编译并运行 hello world 为例:

```shell
cd $AM_HOME/apps
mkdir hello
cd hello
vim Makefile
```



在 Makefile 中输入以下内容, 您也可以参考 apps 下其他程序的 Makefile:

```shell
NAME = hello
SRCS = $(shell find -L ./src/ -name "*.c")
include $(AM_HOME)/Makefile.app
```



接下来创建 hello.c

```shell
mkdir src
vim src/hello.c
```



在 hello.c 中输入以下内容:

```shell
#include <klib.h>

int main() {
  printf("Hello Xiangshan!\n");
  return 0;
}
```



KLIB 是 AM 提供的一个运行时库, 提供了 printf 函数的实现. 更详细的关于 KLIB 的介绍请大家后续阅读源码.

准备好 src/hello.c 后, 使用以下命令编译适用于 Xiangshan 架构的程序(当前目录为 $AM_HOME/apps/hello):

```shell
make ARCH=riscv64-xs
```



ELF 文件, 二进制运行镜像, 应用程序的反汇编会被生成在 /build 目录下. 可以使用以下命令来运行编译好的镜像:

```shell
$NOOP_HOME/build/emu -i $AM_HOME/apps/hello/build/hello-riscv64-xs.bin
```

