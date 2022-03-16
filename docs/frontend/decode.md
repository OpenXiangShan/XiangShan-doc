# 译码单元 (Decode Unit)
## 基本功能
指令从指令缓存中取出，送进指令缓冲（队列）中暂存，然后以每周期 6 条的的速度送入译码单元译码，再传给下一个流水级。

## 指令融合 (Instruction Fusion)
译码单元支持了一些指令的融合，在`FusionDecoder`模块中会基于两条指令的32bit数据完成指令融合。

目前，香山支持如下情况的指令融合：

* clear upper 32 bits / get lower 32 bits: `slli r1, r0, 32` + `srli r1, r1, 32`
* clear upper 48 bits / get lower 16 bits: `slli r1, r0, 48` + `srli r1, r1, 48`
* clear upper 48 bits / get lower 16 bits: `slliw r1, r0, 16` + `srliw r1, r1, 16`
* sign-extend a 16-bit number: `slliw r1, r0, 16` + `sraiw r1, r1, 16`
* shift left by one and add: `slli r1, r0, 1` + `add r1, r1, r2`
* shift left by two and add: `slli r1, r0, 2` + `add r1, r1, r2`
* shift left by three and add: `slli r1, r0, 3` + `add r1, r1, r2`
* shift zero-extended word left by one: `slli r1, r0, 32` + `srli r1, r0, 31`
* shift zero-extended word left by two: `slli r1, r0, 32` + `srli r1, r0, 30`
* shift zero-extended word left by three: `slli r1, r0, 32` + `srli r1, r0, 29`
* get the second byte: `srli r1, r0, 8` + `andi r1, r1, 255`
* shift left by four and add: `slli r1, r0, 4` + `add r1, r1, r2`
* shift right by 29 and add: `srli r1, r0, 29` + `add r1, r1, r2`
* shift right by 30 and add: `srli r1, r0, 30` + `add r1, r1, r2`
* shift right by 31 and add: `srli r1, r0, 31` + `add r1, r1, r2`
* shift right by 32 and add: `srli r1, r0, 32` + `add r1, r1, r2`
* add one if odd, otherwise unchanged: `andi r1, r0, 1`` + `add r1, r1, r2`
* add one if odd (in word format), otherwise unchanged: `andi r1, r0, 1` + `addw r1, r1, r2`
* addw and extract its lower 8 bits (fused into addwbyte)
* addw and extract its lower 1 bit (fused into addwbit)
* addw and zext.h (fused into addwzexth)
* addw and sext.h (fused into addwsexth)
* logic operation and extract its LSB
* logic operation and extract its lower 16 bits
* OR(Cat(src1(63, 8), 0.U(8.W)), src2)
* mul 7bit data with 32-bit data
