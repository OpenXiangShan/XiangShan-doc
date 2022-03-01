# Refill Pipe

NanHu 架构相比于 YanqiHu 架构添加了专门的回填流水线 Refill Pipe. 对于 load 或 store 的 miss 请求, 在进入 Miss Queue 之前会选择出替换路, 在拿到 L2 返回的数据后就可以发送到 Refill Pipe, 因此只需要一拍即可将回填数据写入 DCache, 而无需再访问一遍 DCache.