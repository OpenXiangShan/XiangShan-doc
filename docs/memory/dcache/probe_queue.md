# Probe Queue

Probe Queue 包含 16 项 Probe Entry, 负责接收来自 L2 Cache 的 Probe 请求, 并将 Probe 请求转成内部信号发送到 Main Pipe, 在 Main Pipe 中修改被 Probe 块的权限.

## Probe 请求的调度

!!! todo
    逐拍介绍 probe 请求写入 probe queue, 从 probe queue 中选出, 送入 mainpipe 的流程 

## 补充

### Alias 的处理

!!! todo
    介绍 alias_addr_frag 的来源, 解释为什么要对主流水线的 req.vaddr 进行拼位操作

### 原子指令支持

!!! todo
    介绍 lr 阻塞 probe 的细节