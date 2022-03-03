# Load Pipeline

本章描述香山处理器 DCache Load 流水线的实现。

## DCache Load 流水线的划分

DCache 的 load 流水线与 load unit 的 load 流水线各流水级一一对应, 同步流动. 两者在逻辑上可以被视为同一条流水线. 

**非阻塞性**. 一旦 dcache 流水线 stage 0 接收了一条 load 指令, 这条 load 指令就不会被阻塞. 不过在出现冲突的情况下, dcache 流水线 stage 0 可能会拒绝接收 load 指令.

### Stage 0

* 接收 load 流水线计算出的虚拟地址
* 使用虚拟地址查询 tag
* 使用虚拟地址查询 tag

### Stage 1bank_conflict_slow

* 获得 tag 查询结果
* 获得 meta 查询结果
* 进行 tag 匹配
    * 判断 dcache 访问是否命中
* 检查 tag error
* 使用物理地址查询 data
* 获取 PLRU 信息, 选出替换 way
* 检查 bank 冲突
* 生成快速唤醒信号

### Stage 2

* 更新 dcache PLRU
* 获得 data 查询结果
* 如果 miss, 尝试分配 MSHR (miss queue) 项
* 检查 data error

## 硬件性能计数器

计数器名称|描述
-|-
load_req|-
load_replay|-
load_replay_for_data_nack|-
load_replay_for_no_mshr|-
load_replay_for_conflict|-