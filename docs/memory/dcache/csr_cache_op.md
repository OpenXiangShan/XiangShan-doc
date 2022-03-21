# 自定义一级缓存操作

南湖架构支持基于 CSR 的自定义 l1 cache 操作. 

## L1 Cache 指令寄存器

cache 指令寄存器分成3类: 一个 `CSR_CACHE_OP` 缓存指令寄存器, 一个 `CSR_OP_FINISH` 缓存指令状态寄存器, `CSR_CACHE_*`: 一级缓存控制寄存器, 自定义缓存指令的参数配置和结果返回都经由这些寄存器进行. 寄存器的基地址由 `Sfetchctl` 指定,  默认为 `Sfetchctl`. 详细寄存器列表按顺序如下:

寄存器名称|说明
-|-
CSR_CACHE_OP|cache op 指令码. 写入该寄存器会触发自定义 L1 cache 指令的执行
CSR_OP_FINISH|L1 cache 指令完成标志位
CACHE_LEVEL|缓存指令目标选择. 0: ICache, 1: DCache
CACHE_WAY|cache way select
CACHE_IDX|cache index select
CACHE_BANK_NUM|cache bank select
CACHE_TAG_ECC|tag ecc
reserved|reserved
CACHE_TAG_LOW|tag data
CACHE_TAG_HIGH|reserved
reserved|reserved
CACHE_DATA_ECC|data ecc
CACHE_DATA_X|data [64(X+1)-1:64(X)]

<!-- TODO: 精简编码空间 -->

## cache 指令码

自定义L1缓存指令支持的操作码如下:

操作|操作码
-|-
READ_TAG_ECC|0
READ_DATA_ECC|1
READ_TAG|2
READ_DATA|3
WRITE_TAG_ECC|4
WRITE_DATA_ECC|5
WRITE_TAG|6
WRITE_DATA|7
<!-- COP_FLUSH_BLOCK|8 -->
## 自定义 L1 cache 指令基本执行流程

1. 使用 CSR 指令写入 cache 指令寄存器中的参数配置寄存器, 清空 OP_FINISH 寄存器
1. 向 CSR_CACHE_OP 寄存器写入指令码
1. (可选) 轮询  CSR_OP_FINISH, 直到指令完成, CSR_OP_FINISH == 1
1. 使用 CSR 指令读取 cache 指令寄存器中的结果寄存器, 获得 cache 指令结果
