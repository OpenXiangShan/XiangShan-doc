# Committed Store Buffer

本章介绍香山处理器南湖架构 committed store buffer (sbuffer) 的设计.

南湖架构的 Committed Store Buffer 中最多可以存放 16 项以 cacheline 为单位组织的数据. Committed Store Buffer 每周期至多:

* 接收 2 条 store queue 写入的 store 指令
* 向数据缓存写一个 cacheline

Committed Store Buffer 以 cacheline 为粒度合并 store 的写请求. 当容量超过设定好的阈值时, Committed Store Buffer 会执行换出操作, 使用 PLRU 选出要写入数据缓存的 cacheline, 并将其写入数据缓存. Committed Store Buffer 的自动换出阈值可以使用 `smblockctl` CSR 来设置.

<!-- TODO: 图 -->

## sbuffer 中每项的内容

* 状态位
* 虚实地址:
* 数据
* 数据有效掩码

状态位|说明
-|-
state_valid|该项有效
state_inflight|已经向 dcache 发出写入请求, 正在等待 dcache 写入结果
w_timeout|wait for timeout, 等待重发计时器 timeout, 以重新向 dcache 发出写请求
w_sameblock_inflight|with sameblock inflight, 存在一个相同 cacheline 的 sbuffer 项正在写入 dcache. 处于此状态的指令不会被选出写入 dcache, 以维护 sbuffer 对 dcache 写操作的顺序. 参见 [向 dcache 写入项的选择](#向-dcache-写入项的选择)

## sq 向 sbuffer 的写入机制

因为时序, sq 向 sbuffer 写入数据需要两拍.

* 第一拍: 从 sq 中读出数据和地址并暂存进 `DatamoduleResultBuffer` 中, 参见 [store queue](../lsq/store_queue.md).
* 第二拍: 使用上一拍暂存的地址与 sbuffer 中已有的地址/状态对比, 判断能否写入. 如果可以的话, 实际执行写入操作.

第二拍执行的地址和状态检查会产生以下结果:

* 地址无匹配, 写入
* 地址有匹配, 该项没有发起过写 dcache 请求, 合并
* 地址有匹配, 该项正在写 dcache 请求, 阻塞
* sbuffer 无空项, 阻塞

如果成功执行了写入或合并, 会更新对应项的数据和 mask. 首次写入时还会写入地址和控制信息到 sbuffer 中.

## sbuffer 向 dcache 的写入机制

sbuffer 向 dcache 发起写入分为两拍:

* 第一拍: 选出需要写入 dcache 的项, 读出数据, 对应项被标识为正在写入 dcache
* 第二拍: 写入请求发到 dcache

sbuffer 向 dcache 发出写入请求后会等待 dcache 返回的写入结果. dcache 可能不接受写入请求 (miss 且 MSHR 满, 参见 dcache mainpipe 部分), 此时的 store 指令会在 sbuffer 中启动重发计时器并等待. 当重发计时器归 0 后, sbuffer 会再次尝试将这一项写入 dcache. 只有在 dcache 报告某项的写入成功命中后, sbuffer 才会将这项标为无效状态.

dcache 到 sbuffer 的反馈接口分为两种: 命中接口和重发接口. 命中接口来自可能来自于 MainPipe (命中) 或 RefillPipe (未命中, 但分配到了 MissQueue entry 后完成写入). 重发接口同样来自 MainPipe (未命中且未分配到 MissQueue entry). 详细参见 [dcache mainpipe](../dcache/main_pipe.md) 的说明.

sbuffer 向 dcache 的写入期间, sbuffer 中一项的状态变化流程如下:

1. 有效, 未向 dcache 写入
1. 有效, 正在向 dcache 写入
1. 向 dcache 写入失败, 等待重发 或 无效

!!! note
    sbuffer 的设计允许在 sbuffer 中的一项正在写入 dcache 时, 相同 cacheline 的数据被写入 sbuffer. 新的数据与正在写入 sbuffer data 的数据会占用 sbuffer 中不同的两项.

### 向 dcache 写入项的选择

满足以下条件的 sbuffer 项会被 sbuffer 写入到 dcache 中, 条件按优先级从高到低排列:

1. dcache 请求重发达到等待时间
1. sbuffer 刷新
1. 一项在 sbuffer 中存在的时间达到阈值, 超时离开
1. sbuffer 处于接近满的状态, 部分项被选择换出

换出项的选择使用 PLRU 算法, 在 store 写入到 sbuffer 中时, 或是 store 和 sbuffer 中某项 merge 时, PLRU 会被更新. 在一项的 `w_sameblock_inflight` flag 为高(意味着相同 cacheline 使用的另一个 sbuffer entry 正在被写入 dcache)时, 这一项不会被选为写入到 dcache 的对象.

### flush sbuffer

在主动清空 sbuffer 时, sbuffer 会一并将 store queue 中已经 commit 的指令全部写入 dcache. sbuffer 还会自行刷新以支持虚地址前递机制. 在 sbuffer 发现虚实地址前递的结果产生了冲突(参见[前递支持](./committed_store_buffer.md#store-to-load-forward-query))时, 会自动触发刷新操作.

### 定期刷新机制

sbuffer 会追踪其中每一项在 sbuffer 中的周期数, 支持将在 sbuffer 中超过一定周期数的项自动换出. 

<!-- 触发自动换出的周期数暂时不支持手动配置. -->

## store to load forward query

在 load 指令进行 store to load forward query 时, sbuffer 也会向 load 指令提供已提交但未写入 dcache 的 store 的 data. 在当前的[前递机制](../mechanism.md#store-to-load-forward)下, 来自 sbuffer 的前递机制采用虚地址前递, 实地址检查.

### 产生前递结果

sbuffer 会在前递查询请求到达的下一个周期反馈前递结果, 与 store queue 一致. 

### 虚地址前递支持

为了确保使用虚拟地址产生的前递结果是正确的结果, store buffer 会进行虚地址前递相关检查:

* **前递时检查.** 前递时发现虚实地址的匹配结果不同, 则触发 sbuffer 强制刷新. 将所有项写入 dcache 来防止 sbuffer 继续产生错误的前递结果.

<!-- * **写入时检查.** store buffer 的写入操作会尝试按实地址将对相同 cacheline 的写操作 merge 到 sbuffer 的一项中. 如果发现实地址相同但虚地址不同, 触发 sbuffer 强制刷新. sbuffer 中的对应项会被更新成新的虚地址.  -->

<!-- 写入时检查机制可以考虑取消, 只有在前递中发现问题时才惰性进行 sbuffer 刷新. -->
