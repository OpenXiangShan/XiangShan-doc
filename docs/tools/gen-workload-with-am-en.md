# Use AM to generate custom workload

Take compiling and running hello world in the AM environment for an example:

```shell
# make sure AM_HOME env var has been setup
cd $AM_HOME/apps
mkdir hello
cd hello
vim Makefile
```



Enter the following in the Makefile, you can also refer to the Makefiles of other programs in `$AM_HOME/apps`:

```shell
NAME = hello
SRCS = $(shell find -L ./src/ -name "*.c")
include $(AM_HOME)/Makefile.app
```

Create hello.c:

```shell
mkdir src
vim src/hello.c
```

Write the following code to hello.c:

```c
#include <klib.h> // [1]

int main() {
  printf("Hello Xiangshan!\n");
  return 0;
}
```

> [1] KLIB is a runtime library provided by AM, which provides the implementation of the printf function. For more detailed introduction to KLIB, please read the source code later.

After preparing src/hello.c, use the following command to compile the program for Xiangshan architecture (current directory is $AM_HOME/apps/hello):

```shell
make ARCH=riscv64-xs
```

ELF file, binary image, and disassemble of the program will be generated in the /build directory. The compiled image can be run with the following command:

```shell
$NOOP_HOME/build/emu -i $AM_HOME/apps/hello/build/hello-riscv64-xs.bin
```