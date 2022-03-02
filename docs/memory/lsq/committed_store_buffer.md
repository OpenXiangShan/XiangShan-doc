# Committed Store Buffer

本章介绍香山处理器南湖架构 committed store buffer (sbuffer) 的设计.

南湖架构的 Committed Store Buffer 中最多可以存放16项以 cacheline 为单位组织的数据. Committed Store Buffer 每周期至多:

* 接收2条 SQ 写入的 store 指令
* 向数据缓存写一个 cacheline

Committed Store Buffer 以 cacheline 为粒度合并 store 的写请求. 当容量超过设定好的阈值时, Committed Store Buffer 会执行换出操作, 使用 PLRU 选出要写入数据缓存的 cacheline, 并将其写入数据缓存.

TODO: 图

## sbuffer 中每项的内容

* 状态位
    * state_valid
    * state_inflight
    * w_timeout
    * w_sameblock_inflight
* 虚实地址
* 数据
* 有效 mask

## sq 向 sbuffer 的写入机制

因为时序, sq 向 sbuffer 写入数据需要两拍.

* 第一拍: 从 sq 中读出数据和地址并暂存 (DatamoduleResultBuffer)
* 第二拍: 使用上一拍暂存的地址与 sbuffer 中已有的地址/状态对比, 判断能否写入. 如果可以的话, 实际执行写入操作.

第二拍执行的地址和状态检查会产生以下结果:

* 无匹配, 写入
* 有匹配, 该项没有发起过写 dcache 请求, 合并
* 有匹配, 该项正在写 dcache 请求, 阻塞
* 无空项, 阻塞

写入后状态变化:

* 无效
* 有效, 未向 dcache 写入

或

* 有效, 未向 dcache 写入

如果成功执行了写入或合并, 会更新对应项的数据和 mask. 首次写入时还会写入地址和控制信息.

## sbuffer 向 dcache 的写入机制

写入流程:

* 第一拍: 选出需要写入 dcache 的项, 读出数据, 对应项被标识为正在写入 dcache
* 第二拍: 写入请求发到 dcache

sbuffer 向 dcache 发出写入请求后等待 dcache 返回的写入结果. dcache 到 sbuffer 的反馈接口分为两种: 命中接口和重发接口. 命中接口来自 TODO. 重发接口来自 mainpipe TODO. 参见 dcache mainpipe 的说明.

dcache 可能不接受写入请求 (miss 且 MSHR 满, 参见 dcache mainpipe 部分), 此时的 store 指令会在 sbuffer 中启动重发计时器并等待. 当重发计时器归 0 后, sbuffer 会再次尝试将这一项写入 dcache. 只有在 dcache 报告某项的写入成功命中后, sbuffer 才会将这项标为无效状态.

sbuffer 向 dcache 的写入期间, sbuffer 中一项的状态变化流程如下:

* 有效, 未向 dcache 写入
* 有效, 正在向 dcache 写入
* 向 dcache 写入失败, 等待重发 或 无效

### 向 dcache 写入项的选择

满足以下条件(带优先级)的 sbuffer 项会被 sbuffer 写入到 dcache 中:

* dcache 请求重发达到等待时间
* sbuffer 刷新
* 一项在 sbuffer 中存在的时间达到阈值, 超时离开
* sbuffer 处于接近满的状态, 部分项被选择换出

换出项的选择使用 PLRU 算法

### 换出阈值的设置

CSR可配置

### sbuffer 刷新机制

支持刷新, 会一并刷新 sq

### 定期刷新机制

TODO

## 虚地址前递支持

确保使用虚拟地址产生的前递结果是正确的结果

### 写入时检查

如果发现实地址相同但虚地址不同, 触发 sbuffer 强制刷新. sbuffer 中的对应项会被更新成新的虚地址.

### 前递时检查

前递时发现虚实地址的匹配结果不同, 则触发 sbuffer 强制刷新. 将所有项写入 dcache 来防止 sbuffer 继续产生错误的前递结果.

## 硬件性能计数器

计数器名称|描述
-|-
sbuffer_req_valid|-
sbuffer_req_fire|-
sbuffer_merge|-
sbuffer_newline|-
dcache_req_valid|-
dcache_req_fire|-
sbuffer_idle|-
sbuffer_flush|-
sbuffer_replace|-
mpipe_resp_valid|-
refill_resp_valid|-
replay_resp_valid|-
coh_timeout|-
sbuffer_1_4_valid|-
sbuffer_2_4_valid|-
sbuffer_3_4_valid|-
sbuffer_full_valid|-