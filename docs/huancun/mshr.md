# MSHR设计

本章介绍huancun中non-inclusive MSHR(Miss Status Holding Registers)的设计。

当huancun接收到上层cache的Acquire/Release请求，或者接收到下层cache的Probe请求时，会为该请求分配一项MSHR，同时通过读目录获取该地址在本层及以上cache中的权限信息，MSHR根据这些信息决定：
* [权限控制](#meta_control)：如何更新self directory/client directory中的权限；
* [请求控制](#request_control)：是否需要向上下层cache发送子请求，并等待这些子请求的响应；
<!--
TODO
* 遇到请求的嵌套如何处理等。
-->
下面将<b>以L2 Cache为例</b>从这几个方面介绍huancun MSHR的设计。


<h2 id=meta_control>权限控制</h2>

huancun中的数据是non-inclusive存储的，但目录是严格采用包含策略的，所以MSHR可以拿到请求地址在ICache、DCache和L2 Cache中的所有权限信息，从而控制该地址权限的变化。XiangShan的缓存系统中每个地址都遵循TileLink一致性树的规则，每个块在缓存系统的各层都有N(None)、B(Branch)、T(Trunk)、TT(TIP)四个状态，前三者分别对应着没有权限、只读、可读可写。一致性树按照内存、L3、L2、L1的顺序自下而上生长，内存作为根节点拥有可读可写的权限，在每一层中子节点的权限都不能超过父节点的权限。其中TT代表拥有T权限的枝杈上的叶子节点，说明该节点上层只有N或B权限，相反T权限而不是TT权限的节点代表上层一定还有T/TT权限节点。详细规则请参考TileLink手册9.1章。

MSHR根据请求的类型和读目录的结果更新self directory的dirty位、权限域、clientStates域，其中clientStates表示如果该地址在当前cache中有权限(B及以上权限)，那么这个地址在上层的L1 Cache中的权限是什么；此外，MSHR还会更新ICache和DCache对应的client directory，包括权限域和别名域（将在[Cache 别名问题](./cache_alias.md)一章中介绍）。

下面举两个例子简单说明MSHR如何判断权限的修改，以及目录的设计为什么需要这些域。

1. 假如DCache拥有地址X的权限，而ICache没有，这时ICache向L2请求获取X的权限。这时L2需要判断L2是否有块X、DCache是否有块X、如果有的话权限够不够等，MSHR将根据这些信息决定是直接向ICache返回数据，还是向DCache要数据(Probe)再返回给ICache，还是需要向L3 Acquire这个块再转发给ICache，所以我们需要在self directory和client directory中分别维护权限位。

2. 假如DCache拥有地址X的权限，而L2没有，这时DCache将X替换了出去，向下发送Release地址X的请求，L2收到请求后分配了一项MSHR，同时我们希望L2能够保存DCache Release下来的块X，如果需要替换的话L2还要根据替换策略向L3 Release替换块Y。在这个例子中，我们需要知道Y在L2中是否是脏数据，这涉及到向L3 Release Y时是否需要带数据，所以self directory中需要dirty位；在把Y替换出L2时，需要保证L1中已经没有Y的权限了，所以self directory中需要维护clientStates域，从而判断都有哪些上层节点拥有地址Y的权限，L2需要把ICache、DCache中有Y的权限的cache块都Probe下来，才可以向L3 Release Y。


<h2 id=request_control>请求控制</h2>

MSHR需要根据请求的内容和读目录的结果判断需要完成哪些子请求，包括是否需要向下Acquire或Release，是否需要向上Probe，是否应该触发一条预取，是否需要修改目录和tag等等；除了子请求，MSHR还要记录需要等待哪些子请求的应答。

MSHR将这些要调度的请求和要等待的应答具体成一个个事件，并用一系列状态寄存器记录这些事件是否完成。`s_*`寄存器表示要调度的请求，`w_*`寄存器表示要等待的应答，MSHR在拿到读目录的结果后会把需要完成的事件(`s_*`和`w_*`寄存器)置为`false.B`，表示请求还未发送或应答还没有收到，在事件完成后再将寄存器置为`true.B`，当所有事件都完成后，该项MSHR就会被释放。
