---
slug: "memory-access-827-5-atomic-operation"
date: 2025-11-04
categories:
  - "2025 香山入门指南"
links:
  - blog/posts/beginner-guide-2025/0-before-start.md
  - blog/posts/beginner-guide-2025/1-ooo-memory-access.md
  - blog/posts/beginner-guide-2025/2-memory-access-pipeline.md
  - blog/posts/beginner-guide-2025/3-powerful-cache.md
  - blog/posts/beginner-guide-2025/4-virtual-memory.md
  - blog/posts/beginner-guide-2025/5-atomic-operation.md
---

# 【2025 香山入门指南 · 我在 827 做访存】（五）原子不可分！
---

!!! warning "百度百科——原子"
    关于物质是由离散单元组成且能够被任意分割的概念流传了上千年，但这些想法只是基于抽象的、哲学的推理，而非实验和实验观察。随着时间的推移以及文化及学派的转变，哲学上原子的性质也有着很大的改变，而这种改变往往还带有一些精神因素。

    尽管如此，对于原子的基本概念在数千年后仍然被化学家们采用，因为它能够很简明地阐述一些化学界的现象。

    原子论是元素派学说中最简明、最具科学性的一种理论形态。英国自然科学史家丹皮尔认为，原子论在科学上“要比它以前或以后的任何学说都更接近于现代观点”。原子论的创始人是古希腊人留基伯（公元前500～约公元前440年），他是德谟克利特的老师。古代学者在论及原子论时,通常是把他们俩人的学说混在一起的。留基伯的学说由他的学生德谟克利特发展和完善,因此德谟克利特被公认为原子论的主要代表。

    德谟克利特认为，万物的本原或根本元素是“原子”和“虚空”。“原子”在希腊文中是“不可分”的意思。德谟克利特用这一概念来指称构成具体事物的最基本的物质微粒。原子的根本特性是“充满和坚实”，即原子内部没有空隙，是坚固的、不可入的，因而是不可分的。德谟克利特认为，原子是永恒的、不生不灭的；原子在数量上是无限的；原子处在不断的运动状态中，它的惟一的运动形式是“振动”，原子的体积微小，是眼睛看不见的，即不能为感官所知觉，只能通过理性才能认识。

    经过二十几个世纪的探索，科学家在17世纪~18世纪通过实验，证实了原子的真实存在。19世纪初英国化学家J.道尔顿在进一步总结前人经验的基础上，提出了具有近代意义的原子学说。这种原子学说的提出开创了化学的新时代，他解释了很多物理、化学现象。

    原子是一种元素能保持其化学性质的最小单位。一个原子包含有一个致密的原子核及若干围绕在原子核周围带负电的电子。原子核由带正电的质子和电中性的中子组成。原子是化学变化的最小粒子，分子是由原子组成的，许多物质是由原子直接构成的。


[原子](https://baike.baidu.com/item/%E5%8E%9F%E5%AD%90/420269)



上面是百度百科对于原子这一概念的介绍，目前普遍认为，原子这一概念最初是由古希腊留基伯与德谟克里特发展和完善的，其中**德谟克里特作为原子论的代表认为原子不可构造且永恒不变**。

当然，现代科学告诉我们，原子并非真的是不可分割的最小粒子，**原子也是由许多亚原子粒子构成的**。但是由原子论带来的原子这一概念却被大家一直保留到了现在，可能这也就是探索未知的意义和乐趣吧。

<!-- more -->

---

!!! note "借鉴，借鉴"
    标题灵感来自香山团队 yym 同学的毕业设计。


## 计算机中的原子
我们先来看这么一个情况：

```c
int main() {
    int i = 0;
    i++;
    return 0;
}
```

上面这是一段 i++ 的 C 代码，在经过编译器的努力之后会变成下面这样：

```plain
main:
        addi    sp, sp, -32
        sd      ra, 24(sp)
        sd      s0, 16(sp)
        addi    s0, sp, 32
        li      a0, 0
        sw      a0, -20(s0) 
        sw      a0, -24(s0) # int i = 0;
        lw      a1, -24(s0) # i++;
        addiw   a1, a1, 1   # i++;
        sw      a1, -24(s0) # i++;
        ld      ra, 24(sp)
        ld      s0, 16(sp)
        addi    sp, sp, 32
        ret
```

我们可以看到，这其中 C 代码的一条 i++ 是由 lw addiw sw 三条指令构成的，也就是说，i++ 的这个操作在真正的执行时是存在中间态的。

这在单线程的场景中不会带来影响，但是随着我们对于计算加速的需求越来越大，我们势必会引入多线程编程的方案，此时，一切就变的不一样了。

下面是来自 jyy 的 OS 2023 讲义中的一段代码，大家应该无法直接运行，但是可以看一下基本的结构。

```c
#define N 100000000
long sum = 0;

void Tsum() { for (int i = 0; i < N; i++) sum++; }

int main() {
    create(Tsum);
    create(Tsum);
    join();
    printf("sum = %ld\n", sum);
}
```

这段代码比较简单，有一个全局变量 sum，创建两个线程来为 sum++。如果大家大家自己编写类似的代码并场尝试的化，应该会得到完全随机的值，这个值看上去没有任何规律。  


---

**<font style="color:#DF2A3F;">请完成任务：</font>**

**在你的机器上实现上面这段多线程求和代码的逻辑，并多次测试结果。**

---

我们假设这是运行香山昆明湖 V2 处理器上，每个线程运行在一个物理核心上，那么由上面提到的 i++ 对应的汇编指令来看，大家应该很容易能猜到为什么会产生随机的结果。

---

**<font style="color:#DF2A3F;">请完成任务：</font>**

**结合上一个任务的实验结果和汇编指令思考为什么会出现这样的结果。**

**当然，上一个任务是在你自己的机器上做的实验，而更上面的汇编是 RISC-V 的汇编。**

**因此，你还需要重新编写一份基于 AM 的可以在香山上运行的这段多线程求和程序，并测试分析结果。**

---

---

**<font style="color:#74B602;">请带着问题阅读资料：</font>**

**如果你在实验之后对照汇编还是无法理解为什么会产生这样的结果，可以参考阅读 jyy 老师的 OS 课程。**

[Yanyan’s Wiki](https://jyywiki.cn/OS/2025/lect13.md)

---

这就是非原子操作带来的问题，在单线程时，一切都那么自然且美好，只有多线程的恶魔看上去那么的狰狞。

---

!!! note "Threads are evil?"
    有关多线程的问题一直是软件工程领域的讨论的要点。在最初，人们发现单核已经无法满足

    下面是一些参考阅读的资料，感兴趣的读者可以自行阅读。但无论如何，多核处理器与多线程编程是计算机领域的一大突破，使得我们在单核性能停滞不前的时代可以有其他更多可以尝试突破的机会。

    [https://www2.eecs.berkeley.edu/Pubs/TechRpts/2006/EECS-2006-1.pdf](https://www2.eecs.berkeley.edu/Pubs/TechRpts/2006/EECS-2006-1.pdf)

    [https://becpp.org/blog/wp-content/uploads/2018/01/Frederik-Vannoote-Threads-are-evil.pdf](https://becpp.org/blog/wp-content/uploads/2018/01/Frederik-Vannoote-Threads-are-evil.pdf)




因此，几乎所有的硬件架构都提供了专门的原子指令来解决这一问题。

所谓原子指令，我们可以简单的认为，在外界观测来看，以这条指令为界限，只存在两种状态：**这条指令未完成、这条指令已完成**。不存在任何其他的中间状态，也就是说，这条指令要么以完成后的结果影响外界的观测，要么不会影响外界的观测，不应该被外界观测到任何中间态。

对于 RISC-V 来说，我们有 AMOADD 指令来原子性的完成 i++ 这一操作，我们看下面这段代码：

```c
#include <stdatomic.h>

int main() {
    atomic_int i = ATOMIC_VAR_INIT(0);
    i++;
    return 0;
}
```

上面这是一段使用 C 标准原子操作库来原子执行 i++ 的 C 代码，在经过编译器的努力之后会变成下面这样：

```plain
main:
        addi    sp, sp, -32
        sd      ra, 24(sp)
        sd      s0, 16(sp)
        addi    s0, sp, 32
        li      a0, 0
        sw      a0, -20(s0)
        sw      a0, -24(s0) 				 # atomic_int i = ATOMIC_VAR_INIT(0);
        li      a2, 1							   # atomic_int i = ATOMIC_VAR_INIT(0);
        addi    a1, s0, -24 				 # atomic_int i = ATOMIC_VAR_INIT(0);
        amoadd.w.aqrl   a1, a2, (a1) # i++;
        ld      ra, 24(sp)
        ld      s0, 16(sp)
        addi    sp, sp, 32
        ret
```

我们会发现，在使用了 C 语言的原子操作原语之后，我们的 i++ 语句由三条 RISC-V 汇编变成了一条 RISC-V 汇编。**我们保证，这条指令的 Load、Add、Store 都会以相同的状态结束，从外界来看，我执行这一条指令就可以完成上面提到的三条指令的效果。更简单的来说，在外界来看，这一条指令在同时完成了就完成了：****<font style="color:#AD1A2B;">从内存中取得数据，将内存的原值写回寄存器，完成 add 操作，再将新的数据写回内存。</font>**

因此，我们可以发现，在使用原子操作之后，i++ 的行为不再存在中间态了，对于 AMOADD 这一条汇编指令而言，**只存在两种状态：未完成 i++、已完成 i++**。

---

**<font style="color:#DF2A3F;">请完成任务：</font>**

**将你上面编写的 AM 的 i++ 多线程测试改造为使用这条 amoadd 指令来实现，并测试结果。**

**如果发现结果符合预期且不再随机，请解释为什么。**

**如果发现结果不符合预期且依然随机，请解释为什么。**

**<font style="color:#DF2A3F;">提示：这可能涉及到一些一致性的概念。</font>**

---

## <font style="color:rgb(37, 41, 51);">Compare and Exchange</font>
在目前的 RISC-V 标准中，有两个原子操作相关的扩展：

 "A" Extension for Atomic Instructions 和 "Zacas" Extension for Atomic Compare-and-Swap (CAS) Instructions

这其中，"A" 扩展为我们带来了两类标准的原子操作指令：

LR/SC 两条指令用来进行现在软件多线程的锁操作。

若干条标准 AMO 操作指令用来进行原子计算、原子比较、原子交换等等操作。

我们上面用 AMOADD 指令来介绍了标准 AMO 操作指令逻辑，下面简单介绍一下 LR/SC 指令。



我们知道，现在使用最广泛的桌面端与服务器领域的处理器是 X86 架构。在经典的 X86 架构的操作系统中，往往存在这样的一个 API: 

**<font style="color:rgb(51, 51, 51);">int cmpxchg(void* ptr, int  expected , int new)</font>**

cmpxchg 是一个 x86 中的比较交换指令，即：**<font style="color:rgb(37, 41, 51);">Compare and Exchange.</font>**

<font style="color:rgb(37, 41, 51);">笔者也不是很了解 x86，但在 linux 中，这个以这条指令为名的 API 大概是以</font>**<font style="color:#AD1A2B;">原子</font>**<font style="color:rgb(37, 41, 51);">执行这样的逻辑的：</font>

+ 读取<font style="color:rgb(37, 41, 51);">：从 </font>`**<font style="color:rgb(37, 41, 51);">ptr</font>**`<font style="color:rgb(37, 41, 51);"> 指向的内存地址读取</font>_**当前值**_<font style="color:rgb(37, 41, 51);">。</font>
+ 比较<font style="color:rgb(37, 41, 51);">：将这个</font>_**当前值**_<font style="color:rgb(37, 41, 51);">与 </font>`**<font style="color:rgb(37, 41, 51);">expected</font>**`<font style="color:rgb(37, 41, 51);">（期望的旧值）进行比较。</font>
+ 成功/失败<font style="color:rgb(37, 41, 51);">：</font>
    - 如果_**当前值**_<font style="color:rgb(37, 41, 51);"> == </font>`<font style="color:rgb(37, 41, 51);">expected</font>`<font style="color:rgb(37, 41, 51);">：说明从上次读到这个值到现在，没有其他线程修改过它，此时，将 </font>`<font style="color:rgb(37, 41, 51);">new</font>`<font style="color:rgb(37, 41, 51);"> 写入到 </font>`<font style="color:rgb(37, 41, 51);">ptr</font>`<font style="color:rgb(37, 41, 51);"> 地址，并返回 </font>`<font style="color:rgb(37, 41, 51);">expected</font>`<font style="color:rgb(37, 41, 51);"> 值（通常的）。</font>
    - 如果_**当前值**_<font style="color:rgb(37, 41, 51);"> != </font>`<font style="color:rgb(37, 41, 51);">expected</font>`<font style="color:rgb(37, 41, 51);">：说明在你准备写入时，有其他线程已经修改了这个值。此时，操作</font>失败<font style="color:rgb(37, 41, 51);">，它</font>不会<font style="color:rgb(37, 41, 51);">写入 </font>`<font style="color:rgb(37, 41, 51);">new</font>`<font style="color:rgb(37, 41, 51);"> 值，并且会返回那个它刚刚读到的、非预期的</font>_当前值_<font style="color:rgb(37, 41, 51);">。</font>

linux 的 cmpxchg API 在 x86 架构上使用 cmpxchg 指令作为底层实现，我们可以使用这个 API 来构建无锁数据结构（lock-free data structures）、一些锁（例如自旋锁 Spinlock）。

因此，与之类似的，在 ARMv8 中具有名为 **CAS(****<font style="color:rgb(25, 27, 31);">Compare And Swap</font>****)** 的比较并交换指令。

---

而在 RISC-V 中，情况可能有了一些不同。

上面提到了在目前的 RISC-V 标准中存在在两个原子操作相关的扩展。其中，"Zacas" 是近两年才进入标准的扩展，"Zacas" 故名思意，就是 RISC-V 的 **CAS** 指令扩展。而在之前，RISC-V 的原子操作指令只有 LR/SC 与标准 AMO 操作指令。

因此，在 "Zacas" 之前，linux 不得不使用 LR/SC 来构建 cmpxchg API，这就带来了一些问题。

LR/SC 指令在直觉上比较简单：  
**LR(Load Reserved) **_**<font style="background-color:rgb(252, 252, 252);">lr.{w/d}.{aqrl} rd, (rs1)</font>**_**<font style="background-color:rgb(252, 252, 252);"> </font>**指令读取一个地址的数据到 dest 中，并在该地址放在一个 flag。

**SC(Store Conditionnal) **_**<font style="background-color:rgb(252, 252, 252);">sc.{w/d}.{aqrl} rd, rs2, (rs1)</font>**_**<font style="background-color:rgb(252, 252, 252);"> </font>**指令先检查访问的地址是否具有被 LR 指令设置的 flag，若有，则将数据写入地址，并设置 rd 为 0；否则，不更改地址中的数据，并将非 0 值写入 rd。

这里的设置和检查和 flag 可能比较模糊，在实际的硬件中，我们只需要在 CPU 内设置一个 1bit 的标记位即可，大部分设置会将这个标记为放置在 L1 DCache 中。

LR/SC 指令早在 ARM 架构中已经被使用了。LR/SC 指令往往会以一种 LR/SC Loop 的方式在软件代码中成对出现：先由 LR 设定 Reservation，再由 SC 进行条件存储，后续会使用分支指令检测是否成功，如果失败，则跳回 Loop 起始重新尝试执行。

但是 LR/SC 却在客观上存在**活锁**的问题，为了解决活锁的问题，RISC-V 为 LR/SC 设立了一些约束。

---

**<font style="color:#DF2A3F;">请完成任务：</font>**

**阅读 RISC-V 非特权手册的 A 扩展部分，回答下列问题：**

**为什么 LR/SC 在没有约束的情况下会活锁？**

**RISC-V 对 LR/SC 的约束都有哪些？**

---

前面我们提到，RISC-V 在近两年以前，是不具备 CAS 指令的。

笔者认为，这是当初的 RISC-V 制定者们认为 LR/SC 相比 CAS 具有足够的优势。 

---

!!! warning "RISC-V unpriv isa —— LR/SC 的优点"
    Both compare-and-swap (CAS) and LR/SC can be used to build lock-free data structures. After extensive discussion, we opted for LR/SC for several reasons:

    1) CAS suffers from the ABA problem, which LR/SC avoids because it monitors all writes to the address rather than only checking for changes in the data value;

    2) CAS would also require a new integer instruction format to support three source operands (address, compare value, swap value) as well as a different memory system message format, which would complicate microarchitectures;

    3) Furthermore, to avoid the ABA problem, other systems provide a double-wide CAS (DW-CAS) to allow a counter to be tested and incremented along with a data word. This requires reading five registers and writing two in one instruction, and also a new larger memory system message type, further complicating implementations;

    4) LR/SC provides a more efficient implementation of many primitives as it only requires one load as opposed to two with CAS (one load before the CAS instruction to obtain a value for speculative computation, then a second load as part of the CAS instruction to check if value is unchanged before updating).


[“A” Extension for Atomic Instructions, Version 2.1 :: RISC-V Ratified Specifications Library](https://docs.riscv.org/reference/isa/unpriv/a-st-ext.html)

上面引用了 RISC-V 手册中对于为什么选择 LR/SC 指令而不是 CAS 指令的论述。

没有问题，LR/SC 确实相比 CAS 具有这些显著的优点，这也是 RISC-V 的制定者们选择 LR/SC 而不是 CAS 指令的理论依据。

但可惜的是，考虑到软件兼容性与实现上的客观情况，linux 直接使用了 LR/SC 来进行 cmpxchg API 的实现：

```plain
#define __arch_cmpxchg(lr_sfx, sc_sfx, prepend, append, r, p, co, o, n)	\
({									\
    register unsigned int __rc;					\
        \
        __asm__ __volatile__ (						\
                      prepend							\
                      "0:	lr" lr_sfx " %0, %2\n"				\
                      "	bne  %0, %z3, 1f\n"				\
                      "	sc" sc_sfx " %1, %z4, %2\n"			\
                      "	bnez %1, 0b\n"					\
                      append							\
                      "1:\n"							\
                      : "=&r" (r), "=&r" (__rc), "+A" (*(p))			\
                      : "rJ" (co o), "rJ" (n)					\
                      : "memory");						\
  })
```

---

**<font style="color:#74B602;">请回答问题：</font>**

**在这样的使用方式下，LR/SC 并不会比 CAS 具有更多的优势，请查询相关资料并解释为什么。**

**你可能需要先系统的了解 LR/SC 与 CAS 指令都是什么，然后可能需要你去查阅 linux 源码，具体的，你可能需要分别查看 RISC-V 与 ARM 架构在 linux 中分别是如何实现与使用 cmpxchg 与各种锁的。**

**这个问题难度较大，请善用 AI。**

---

现在我们知道了在一些情况下，LR/SC 可能不一定总是比 CAS 更合适。

ARM 在最初也只有 LR/SC 指令，只到 ARMv8 才引入了 CAS 指令，与之类似的，RISC-V 的指定者们通过标准扩展的方式也为 RISC-V 引入了 CAS 指令。

不过这些都是后话了，有关 LR/SC 与 CAS 谁更优秀的讨论可能不会停止，也可能不会有一个确切的结论，不过考虑到 RISC-V 已经同时具备了 LR/SC 与 CAS 指令，因此我们可以自由的根据使用场景选择合适的指令，这一切都取决于软件编写者的能力，至少，**我们不应该再怪罪 RISC-V 指令集没有为我们提供 CAS 了。**

## AtomicUnit
AtomicUnit，香山昆明湖 V2 中的原子访存控制模块。

事实上，抛开 Cache 谈论原子操作是十分不合理的事情，因为在事实上，原子操作的实现势必要与 Cache、缓存一致性以及总线协议相关。

对香山来说，AtomicUnit 模块只作为 MemBlock 侧的控制模块，AtomicUnit 会根据原子访存的不同进行权限检查等访存前操作，最终 AtomicUnit 会产生不同的控制信号，并向 DCache 发出原子操作请求。自然地，DCache 会根据控制信号的不同来实现不同原子指令的特殊处理。

并且由于原子指令的一致性要求，昆明湖 V2 目前采用了非推测执行的方式来实现原子指令。因此，其实 AtomicUnit 是由一个十分简单的状态机来实现的。

---

!!! note "别忘了回头再来看看"
    编者相信大家可以较为轻松的理解 AtomicUnit 中的内容，并且考虑到这里的逻辑相对独立，仅与 DCache 中的部分逻辑相关，对此不了解也不会影响到对整个 MemBlock 的掌握，因此就不再设计必答题了。

    但当然，如果你对这个原子操作感兴趣，编者还是十分欢迎读者去完整的了解原子操作有关的一切的！

    因此，如果学有余力，别忘了再回来看看。


## 更快的原子指令执行
从一定程度上来看，原子类指令是现代处理器所必须要支持的的特性，因为原子指令在常规 CPU 体系结构在执行多线程任务的时候所必须要的功能。例如，锁。因此，从某种方面来看，更快的原子指令势必会从硬件层面加速多线程软件的执行。

**怎么让原子指令更快？**

常规的体系结构优化无非就是：预测、推测。

我们先来分析一下原子指令的执行逻辑是什么样的：在正常情况下，现代处理器往往会具有多个核心，在正常情况下，由于原子指令的特殊性质，当一个处理器核心执行原子指令的时候，我们会阻塞流水线，让处理器只处理原子指令，并且原子指令需要从缓存系统获得到写权限才可以执行，目前香山昆明湖 V2 就是这么做的。

但问题是：**如果多个核心同时进行原子操作该怎么办？**

如果熟悉缓存一致性协议的同学看到这里应该有了一些想法，如果多核同时对一个地址进行原子操作，每个核都需要获取写权限，因此每个核都需要等另一个核做完原子操作才能开始自己的原子操作，但原子操作又是阻塞的非推测执行的，本身就非常的慢。如果一个先做完原子操作的核在之后又需要进行原子/写操作，那就又需要重新获取写权限 ······，以此类推，在一个多核系统中，如果多核同时执行原子操作，可能会存在一些性能上的问题。

其实这个本质上是因为我们执行原子操作前需要先获取缓存的写权限。因此多个处于缓存一致性树最上层的节点同时执行原子操作就可能产生**写权限的乒乓。**

基于此，我们可以有一些比较朴素的优化方案：

既然位于缓存一致性树最上层的节点在同时进行获取原子操作的时候可能会存在写权限的乒乓，那我们将原子操作下放到缓存一致性树的下层不行吗？我们可以有条件的将原子操作下放到更下级缓存来执行，用以减轻可能存在的对写权限的争抢。

或者，原子操作真的一定需要先获取写操作吗？对于标准的 AMO 操作来说，这是肯定的，但是对于 LR/SC 与 CAS 来说，这可能就不一定了。我们知道 SC 与 CAS 指令可能会存在失败，只有当成功时，才会将新的数据写入到内存中，而失败的时候，其实是不需要为内存写入新数据的，也就是说，如果 SC 或者 CAS 执行失败，其实是不需要写权限的。因此或许我们可以使用某些体系结构常见的预测的方法，来预测 SC 或者 CAS 是否能够成功执行，如果能够成功执行，则为他们获取写权限，否则，我们预先获取读权限。

---

!!! note "不过其实编者也不是很懂（🥲"
    这些相关的工作有一部分已经被香山的同学们探索过了，可能会在之后添加进昆明湖 V3 当中，不过这些工作大部分都与缓存系统相关，编者对缓存系统还是不非常的掌握，因此在这里只是为了让行文更加完整而简单的抛出来一些观点，具体可行与否还要交给大家去自行判断啦~


# <font style="color:#000000;">并行计算的诱惑</font>
