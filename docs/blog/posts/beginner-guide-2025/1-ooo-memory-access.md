---
slug: "memory-access-827-1-ooo-memory-access"
date: 2025-10-31
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

# 【2025 香山入门指南 · 我在 827 做访存】（一）乱序访存

香山支持访存指令的乱序执行。

所谓访存指令的乱序执行，意味着我们可以向运算指令一样，乱序的调度执行访存指令。可能有些同学会觉得这是很正常很简单的事情，但我们确实为了支持乱序访存付出了很大的代价。

<!-- more -->

## 由内存一致性说起

在程序的世界中，对于内存的访问会期望在满足某些规则的情况下总是得到一定规律的值，而这些规则与得到的内存的值一起构成了我们常说的**内存模型**。

所谓内存模型，规定了我的软件以什么的方式编写可以得到什么样的内存访问结果。这是十分重要的。

通常来讲，内存一致性是面向多核系统的约束。在单核的世界里，程序总是以程序序来执行的，这是不容置喙的。而在多核的世界中，每个核当然也是以自己的程序序来执行的，但是他们必然会涉及到一些公用的资源——内存。

内存作为所有核心公用的资源，理论上会对所有的核心可见，假设我们有一个无穷大和无穷快的内存，那么我们当然可以让所有的核心自己任意的访问内存。但很可惜，正因为不存在这样的内存，所以硬件设计者为了提高访存的速度而在处理器核内部引入了各种 Cache 以及 Buffer。

我们认为，所有核的 Cache、Buffer 与内存一起构成了这个**处理器的内存系统**。在这个系统中，有些部分的可以被所有核心观测到的，而有些则只能被所拥有的核心的观测到。

对于香山而言，每个核心分别拥有：StoreQueue、Sbuffer、L1 DCache、L2 Cache。这其中，StoreQueue 与 Sbuffer 保存的 Store 指令的执行结果不会被其他核心以任何方式观测到，只有数据进入到 L1 DCache 之后，才有可能被其他核心访问观测到。

现在，我们假设我们正在编写下面这样的多核程序：

![r2 的值总是 NEW 吗？ —— A Primer on Memory Consistency and Cache Coherence](images/6985a61f.png)

我们可能会期望 r2 的值总是 NEW。这是因为，我们如果我们从单核的角度来看，我们总是期望 <font style="color:rgb(25, 27, 31);">S1 一定会在 S2 之前执行，B1 一定会在 L2 之前执行，L2 只有在 S2 执行后才能执行，因此我们会期望这里的执行序列是：</font>

```
S1 -> S2
      L1 -> B1 -> L2
```

因此，这样的指令序列最后一定会得到 `r2 = NEW`。

但是，如果我们真的编写了一段这样的代码，我们可能会得到一些奇怪的结果：

在不同架构、实现的机器上可能得到截然不同的结果。甚至在相同的机器上面多次运行得到的结果可能也不同。有可能最终 `r2 = 0`，也有可能 `r2 = NEW`。这就表现的十分奇怪。

这就产生了一些奇怪的冲突。硬件的设计者总是希望我们可以在大部分情况下执行的更快，而这就需要引入一些假设或者额外的要求。在单核程序上面，这些假设可能不会对软件开发者产生一些令人困惑的歧义，而在多核程序上，这些假设可能就会带来一些意想不到的结果。

这是因为，程序序与访存序是完全不同的两个概念。

**程序序：**程序中的 Load / Store 指令的**<font style="color:#AD1A2B;">指令序列。</font>**

**访存序：**Load / Store 指令引起的对**<font style="color:#AD1A2B;">处理器的内存系统的读写操作的顺序。</font>**

由于硬件乱序执行访存指令，因此在访存序上并不一定会严格按照程序序进行。而在多核程序上，除了每个核的程序序，还会有一个额外的为所有核的程序序排序的**全局序**。

因此，硬件开发者与软件开发者约定，**在一定的情况下硬件会满足一定的访存序，且可以提供一些特殊的方式来手动保证指令执行的顺序。**这些约定，就是**内存一致性模型**了。

---

**<font style="color:#DF2A3F;">请带着问题阅读相关资料：</font>**

**内存一致性到底是什么？  
****内存一致性模型是如何保证内存一致性的？**

---

**书籍：**_<font style="color:rgb(138, 143, 141);">A Primer on Memory Consistency and Cache Coherence</font>_

[https://zhuanlan.zhihu.com/p/694673551](https://zhuanlan.zhihu.com/p/694673551)

[https://web.csl.cornell.edu/courses/ece5750/gharachorloo.isca90.pdf](https://web.csl.cornell.edu/courses/ece5750/gharachorloo.isca90.pdf)

---

## RVWMO
内存一致性模型是硬件与软件的约定，自然，不同的硬件平台可能会带来一些截然不同的约定。

常见的，X86 平台可能采用 **TSO (Total Store Ordering) **内存一致性模型 (但其实看上去 Intel 和 AMD 从来没有保证是这样的)，ARM 平台可能采用 **RC (****<font style="color:rgb(0, 0, 0);">Relaxed Consistency Model)</font>**<font style="color:rgb(0, 0, 0);"> 内存一致性模型。</font>

**<font style="color:#AD1A2B;">而 RISC-V 则采用 RVWMO (RISC-V Weak Memory Ordering) 内存一致性模型。</font>**

相对来说，R<font style="color:rgb(25, 27, 31);">VWMO 主要部分仍然沿用了 </font>RC（release consistency）<font style="color:rgb(25, 27, 31);">内存一致性模型，整体上没有对内存访问顺序进行特别强力的约束，为硬件实现和性能优化提供了宽松的条件；同时，禁止若干过于复杂费解的乱序情况，方便了软件程序的开发利用。总体上 RVWMO 是一种</font>**<font style="color:rgb(25, 27, 31);">弱内存序模型</font>**<font style="color:rgb(25, 27, 31);">。</font>

<font style="color:rgb(25, 27, 31);">当然，考虑到 X86 平台存在的大量的依赖 TSO 内存一致性模型运行的程序，RISC-V 还提供了一个额外的拓展：</font>**<font style="color:rgb(25, 27, 31);">Ztso</font>**<font style="color:rgb(25, 27, 31);"> 扩展来支持 </font>**<font style="color:rgb(25, 27, 31);">RVTSO (RISC-V Total Store Ordering)</font>**<font style="color:rgb(25, 27, 31);"> 以兼容 X86 平台的程序。但这就属于后话了，目前香山还未实现 Ztso 扩展，不过 Ztso 扩展已经提上了我们的下一步开发计划惹。</font>

<font style="color:rgb(25, 27, 31);">一般情况下，我们认为 RVWMO 规定可以总结为：</font>

**<font style="color:#AD1A2B;">十三条规则、四条公理</font>**

软件代码在编写时需要满足对应的规则，硬件自然会保证软件看到的内存操作是符合 RVWMO 模型的。

那具体的细节就留给各位同学们进行探索啦。

---

**<font style="color:#DF2A3F;">请带着问题阅读相关资料：</font>**

**RVWMO 的规范要求是什么？**

---

了解了 RVWMO 的规范之后，我们就很容易能够得到一些硬件上的优化方案，最直观的就是 RVWMO 对 Store Buffer 的极大宽容，使得我们可以轻易的添加这一模块对 Store/Load 进行硬件层面的优化。

并且，大家在阅读过 RVWMO 之后，应该可以理解到这一内存一致性模型的设计思路：**可以支持高性能高扩展的 RISC-V 硬件平台的内存一致性模型。并在一定程度上保证软件代码的编写方便。 **

为了高性能的要求，我们保证了在单 Hart 下的访存序要保证其软件代码的程序序，而在多 Hart 的场景下，我们放宽了大部分情况下的多 Hart 间访存序与程序序的一致性要求，仅在部分场景保证，其余大部分情况需要软件开发者手动显式的使用类似 Fence 之类的同步屏障指令进行访存序的维护。

---

!!! note "“No Silver Bullet”"
    从另一个角度来看，越弱的内存一致性模式势必会为软件编写者引入越多的心智负担，这是不可避免的。
    在软件工程的领域，常常有关于“银弹，Silver Bullet”是否存在的争议。
    一方面，有观点认为：不存在一种通用的方法或工具可以解决所有软件工程问题。
    而另一方面，有观点认为：最终肯定会存在一种方法可以解决这些概念性的本质性的问题。
    但无论他们的观点如何，我们始终要明白，最起码目前，在体系结构和硬件的世界，基本不可能存在可以兼顾所有方向，解决所有问题的方法。


    Trade-Off，是盘旋在每一个硬件开发者头顶的幽灵，所谓不可能三角也是如此，我们很难保证存在一种情况可以使得性能、面积、时序功耗都最优，只能是在开发过程中经过尝试，找到一个平衡的结果。
    RVWMO 也是这样的，我们很难去评判 RVWMO 是否一定优于其他的内存一致性模型，或者可以说，这些内存一致性模型可能本身就不存在绝对的优劣之分，无非就是在各个层面的取舍权衡罢了。
    因此，我们还希望可以通过 RVWMO 这个例子来让大家明白另一个关键问题：权衡与取舍，是大家最应该掌握的理念，无论是硬件设计还是人生。




## “染色的苔藓”
既然有了内存一致性模型的规范，那自然就需要硬件设计者去进行满足内存一致性模型规范的硬件实现，这其中又会带来一个老生常谈的问题：  
**<font style="color:#AD1A2B;">如何保证内存一致性模型规范硬件实现的正确性？</font>**

一个直观的想法是：**使用针对内存一致性场景的系统测试软件，来将特定平台在各个特定场景下的所有执行结果列举出来，来与符合规范的模型进行比对。**

为此，**<font style="color:#AD1A2B;">Litmus </font>**—— 常用的内存一致性套件出现了。

Litmus 使用特殊的工具编写测试用例，再使用特定的工具生成 C 语言代码，最终编译出可执行文件。而对于 RISC-V 而言，有一套专门用来测试 RISC-V RVWMO 内存一致性模型的开源 Litmus 测试套件，香山也依赖这套测试套件进行内存一致性的验证测试。

[GitHub - litmus-tests/litmus-tests-riscv: RISC-V architecture concurrency model litmus tests](https://github.com/litmus-tests/litmus-tests-riscv)



下面是 RISC-V Litmus 测试套件中的其中一个测试。

这段 Litmus 的代码会使用特定的工具生成 C 语言与汇编代码来进行测试，我简单的为这段代码添加了一些注释来帮助大家理解一下。

```shell
RISCV LB+amoadd-data-amoadd.rl+amoadd.aq-data-amoadd

# 两个个核心分别初始化的寄存器与内存情况。
{
 0:x3=x; 0:x6=y;
 1:x3=y; 1:x6=x;
}

# 测试主体代码
# 两个核心分别执行的执行序列，请注意，这里两个核心间不存在执行上的顺序约束。
 P0                     | P1                     ;
 ori x2,x0,1            | ori x2,x0,1            ;
 amoadd.w x1,x2,(x3)    | amoadd.w.aq x1,x2,(x3) ;
 xor x4,x1,x1           | xor x4,x1,x1           ;
 ori x4,x4,1            | ori x4,x4,1            ;
 amoadd.w.rl x5,x4,(x6) | amoadd.w x5,x4,(x6)    ;

# 断言，暂时可以无视。
exists ([x]=2 /\ [y]=2 /\ 0:x1=1 /\ 0:x5=0 /\ 1:x1=1 /\ 1:x5=0)

# --- 

# 上述 Litmus 主题代码通过工具生成的 RISC-V 汇编代码
Generated assembler
#START _litmus_P0
	ori t5,x0,1
	amoadd.w a1,t5,(a5)
	xor t4,a1,a1
	ori t4,t4,1
	amoadd.w.rl a0,t4,(a4)
#START _litmus_P1
	ori t5,x0,1
	amoadd.w.aq a1,t5,(a5)
	xor t4,a1,a1
	ori t4,t4,1
	amoadd.w a0,t4,(a4)
Test LB+amoadd-data-amoadd.rl+amoadd.aq-data-amoadd Allowed

# 在 20000 次运行循环测试主题代码后得到的运行结果统计。
# 一共得到了三种运行结果，这三种结果都是符合 RVWMO 内存一致性模型的。
Histogram (3 states)
99703 :>0:x1=1; 0:x5=1; 1:x1=0; 1:x5=0; [x]=2; [y]=2;
365   :>0:x1=0; 0:x5=1; 1:x1=0; 1:x5=1; [x]=2; [y]=2;
99932 :>0:x1=0; 0:x5=0; 1:x1=1; 1:x5=1; [x]=2; [y]=2;

```

---

!!! note "缺失的内存一致性"
    在 2025 年 5 月份的时候，我们发现了 FPGA 上的 4 核 Litmus 系统测试中昆明湖 V2 出现了若干处内存一致性缺失。

    这是十分严重的问题，我们立马开始了一些尝试，先是尝试在帕拉丁上开启 Difftest 重新运行，希望可以通过 Difftest 来捕捉到一些问题。可惜由于 Difftest 在多核场景上存在一些适配不足的情况，在开启 Difftest 后会在比较早的阶段产生一些误报错，在多次修改之后仍然存在各种误报，考虑到交付的时间越来越紧迫，因此我们不得已在这个测试上暂时先放弃使用 Difftest，转而思考使用一些特殊的方式来进行调试。

    这其中遇到了很多问题，也产生了很多失误，但最终，我们还是解决了这一问题。

    我们发现并修复了存在许久的、多核 RAR 场景下的一些未考虑到的 corner 情况，并成功通过了目前为止运行的所有 RVWMO Litmus 测试。但其实我们都知道，这并不能保证我们的处理器不存在内存一致性的问题。

    其实不只是一致性的问题，对我们来说，整个处理器的验证尚有许多空白，还需要大家携手共进 ······


---

**<font style="color:#74B602;">请带着问题阅读相关资料：</font>**

**下面这段 Litmus 代码与执行结果是上面提到的验证出的香山存在内存一致性缺失 Bug 的一个测试。 **

**这个测试产生的结果一共有 10 种，其中只有一种结果违反了 RVWMO 规范的。**

**请找出哪条结果违反了 RVWMO 的结果并说明为什么违反了 RVWMO 规范。**

```shell
RISCV MP+fence.rw.rw+addr-[fr-rf]
"Fence.rw.rwdWW Rfe DpAddrdR FrLeave RfBack Fre"
{
 0:x5=2; 0:x6=x; 0:x7=1; 0:x8=y;
 1:x6=y; 1:x9=x;
 2:x5=1; 2:x6=x;
}
 P0          | P1            | P2          ;
 sw x5,0(x6) | lw x5,0(x6)   | sw x5,0(x6) ;
 fence rw,rw | xor x7,x5,x5  |             ;
 sw x7,0(x8) | add x10,x9,x7 |             ;
             | lw x8,0(x10)  |             ;
             | lw x11,0(x9)  |             ;

exists ([x]=2 /\ 1:x5=1 /\ 1:x8=0 /\ 1:x11=1)

Result:
Test MP+fence.rw.rw+addr-[fr-rf] Allowed
Histogram (10 states)
21427 :>1:x5=0; 1:x8=0; 1:x11=0; [x]=1;
25    :>1:x5=0; 1:x8=2; 1:x11=0; [x]=1;
3615  :>1:x5=0; 1:x8=1; 1:x11=1; [x]=1;
14    :>1:x5=1; 1:x8=1; 1:x11=1; [x]=1;
19775 :>1:x5=0; 1:x8=2; 1:x11=2; [x]=1;
21    :>1:x5=1; 1:x8=2; 1:x11=2; [x]=1;
5110  :>1:x5=0; 1:x8=0; 1:x11=0; [x]=2;
7     :>1:x5=0; 1:x8=1; 1:x11=1; [x]=2;
4     :>1:x5=0; 1:x8=2; 1:x11=2; [x]=2;
2     :>1:x5=1; 1:x8=2; 1:x11=2; [x]=2;
```

---

---

!!! note "AI 的一些比喻"
    在 2025 年的今天，AI 是任何一个学习者都要学会使用的工具，但同时，我们要学会掌握这个工具，而不是将这个工具视为绝对真理。**请读者记住，至少在 2025 年的今天，AI 只是一个工具，而不是真理。**

    而香山的一些验证老师由于并非 RISC-V 和体系结构出身，因此在一些相关问题上可能不是十分了解，因此我们的一些验证老师在某些一致性的问题上询问了 AI，下面是 AI 对有关某些一致性问题的回答。

    不论这些回答的真实性如何，编者都在这里摆出来供大家鉴赏学习，个中真假就让读者自行辩决了~ 通过比喻的方式进行学习确实是我们了解未知知识的好方式！

    **AI 回复：**

    CPU 的这种“预知未来”般的能力，其实是一种非常“笨拙”但高效的机制：

    **做事之前先打借条**：每个推测的加载（`ld`）就像打了一张借条，记录在 LSQ 账本上（借了哪个地址的数据）。

    **耳朵一直竖着听**：LSQ 不断监听着全村的广播（缓存一致性流量），看有没有人喊“某某地址的账要变了！”。

    **一听到自己的名字就撕借条**：一旦监听到自己借条上的地址被人动了，不管三七二十一，先把这张借条和基于它做的所有后续计划全部撕掉。

    **重新打借条**：从被撕掉的那张借条开始，一切重新来过。


## 访存队列，严格的秩序维护者
上面讲了很多和香山实际代码无关的内容，这其实主要是为了引出下面要提高到的 **LSQ 访存队列**。

访存队列的概念十分的简单：**维护访存指令的生命周期**。

这里提到的生命周期主要是指访存指令的顺序、进入乱序访存的时间和结束的时间。

客观的讲，当一条访存指令进入到访存 IssueQueue 之后，TA 在 MemBlock 中的生命就开始了。

这是因为，当一条访存指令进入访存 IssueQueue 时，TA 还会申请进入 (Virtual)LoadQueue 或 StoreQueue，并分配初始化一项基础的表项。

随后，当一条访存指令指令被从 IssueQueue 中发射出来后，TA 就会在对应的访存单元中进行执行，并会在合适的计划更新 LSQ 中的某些元数据或者标记位等信息。

而当一条访存指令执行完成后，会根据具体情况将这条指令在 LSQ 中标记为已经执行完毕，而后，LSQ 会按照顺序将这些指令占据的表项释放掉。

---

!!! note "分离的 LoadQueue"
    如果你有心去追溯香山的 LSQ 的实现过程，你会发现，Store 从始至终都是一整个模块，而 LoadQueue 却经历过由统一的大模块到拆成成若干个分离的小模块的重构过程。

    在最初，所有为了 Load 指令服务的 Queue 的都集中在一起，由一个统一的大的 LoadQueue 来进行维护，而后来，随着香山发展，统一的 LoadQueue 渐渐产生了各种各样的问题，因此，我们在某一个版本将 LoadQueue 拆分成了若干个独立的小的 Queue，每个 Queue 分别只负责一部分任务。


对于 LSQ 来说，TA 负责在访存侧维护所有访存指令的顺序，并利用这些顺序进行**违例检查**。

从客观上来讲，LSQ 是类似 ROB 的，都是为了维护指令的顺序，区别可能主要在于 ROB 是维护所有指令的，而 LSQ 只维护**可以进行乱序访存的访存指令**。

![LSQ 的基础入队示意图](images/LSQ_的基础入队示意图_ed0bb817.svg)

---

**<font style="color:#DF2A3F;">请带着问题阅读代码与文档：</font>**

**VirtualLoadQueue 与 StoreQueue 的入队分配方式是怎么样的？**

[XiangShan/src/main/scala/xiangshan/mem/lsqueue/LSQWrapper.scala at bcdd2d6ce0ade31d0c1662abcb0fa57deef14257 · OpenXiangShan/XiangShan](https://github.com/OpenXiangShan/XiangShan/blob/bcdd2d6ce0ade31d0c1662abcb0fa57deef14257/src/main/scala/xiangshan/mem/lsqueue/LSQWrapper.scala#L324)

[XiangShan/src/main/scala/xiangshan/mem/lsqueue/VirtualLoadQueue.scala at bcdd2d6ce0ade31d0c1662abcb0fa57deef14257 · OpenXiangShan/XiangShan](https://github.com/OpenXiangShan/XiangShan/blob/bcdd2d6ce0ade31d0c1662abcb0fa57deef14257/src/main/scala/xiangshan/mem/lsqueue/VirtualLoadQueue.scala#L163)

[XiangShan/src/main/scala/xiangshan/mem/lsqueue/StoreQueue.scala at bcdd2d6ce0ade31d0c1662abcb0fa57deef14257 · OpenXiangShan/XiangShan](https://github.com/OpenXiangShan/XiangShan/blob/bcdd2d6ce0ade31d0c1662abcb0fa57deef14257/src/main/scala/xiangshan/mem/lsqueue/StoreQueue.scala#L374)

---

为了满足功能与内存一致性的需要，我们利用 LSQ 进行违例检查与 Load 指令的重发。

+ LoadQueueRAR：主要用于多核场景下 RAR 违例的检测。
+ LoadQueueRAW：主要用于 Store-Load 违例的检查。
+ LoadQueueReplay：主要用于进行基于 ReplayQueue 的 Load 指令重发。

我们还利用 VirtualLoadQueue 与 StoreQueue 进行 Load/Store 指令顺序的维护：

+ VirtualLoadQueue：用来维护 Load 的指令的顺序，以供违例检查等。
+ StoreQueue：用来维护 Store 指令的顺序，且保存地址与数据进行数据前递与写入下级数据缓存。

此外，我们还有一些其他的 Queue 来实现一些额外的功能。

![LSQ 的构成](images/LSQ_的构成_e6584daf.svg)

---

**<font style="color:#DF2A3F;">请带着问题阅读代码与文档：</font>**

**LSQ 的各个部分的作用是什么？**

---

---

**<font style="color:#74B602;">请带着问题阅读代码与文档：</font>**

**上文没有展开讲，为什么我们需要为乱序访存额外维护指令的顺序呢？**

**这与一致性有关，并且不只是关系到 LSQ 访存队列，还与访存流水线有关，如果你现在不会，可以继续向下阅读，可能后面你就会有答案。**

---

到这里，已经简单介绍完了 LSQ 的基本功能，但实际上，LSQ 中还有许多的设计细节没有展开。考虑到这些细节往往和整个 MemBlock 比较耦合，要涉及到其他模块的一些设计思路，在这里就先不展开介绍了，后面介绍完其他模块之后会在展开给大家介绍一下。
