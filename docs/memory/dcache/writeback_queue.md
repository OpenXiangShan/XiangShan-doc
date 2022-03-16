# Writeback Queue

!!! todo
    在写了在写了

## Writeback Queue 入队

[writeback merge](#writeback-merge).

## Writeback Queue 状态维护

!!! todo
    111 
    

### late release

(或者什么名字, 指直到 refill 上来才 release)

### writeback merge

## 阻塞 Miss Queue 请求

```scala
  val miss_req_conflict = VecInit(entries.map(e => e.io.block_addr.valid && e.io.block_addr.bits === io.miss_req.bits)).asUInt.orR
  io.block_miss_req := io.miss_req.valid && miss_req_conflict
```