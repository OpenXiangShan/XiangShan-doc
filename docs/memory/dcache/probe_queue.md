# Probe Queue

Probe Queue 包含 8 项 Probe Entry, 负责接收来自 L2 Cache 的 Probe 请求, 并将 Probe 请求转成内部信号发送到 Main Pipe, 在 Main Pipe 中修改被 Probe 块的权限.