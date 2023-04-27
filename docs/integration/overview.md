# CPU Core Overview

XiangShan-2 (NANHU) support single-core and dual-core configurations, where each core has its own private L1/L2 cache. L3 is shared by multiple cores.

NANHU communicates with the uncore through 3 AXI interfaces, including the memory port, the DMA port and the peripheral port. It also has clock, reset, and JTAG interfaces. Please refer to the integration guide for more detailed information.

NANHU targets 2GHz@14nm, and 2.4GHz~2.8GHz@7nm.

## Typical Configurations
Below is the typical NANHU core configurations:

| Feature | NANHU (XiangShan-2) |
| ------- | ------------------- |
| Pipeline stage | 11 |
| Decoder width | 6 |
| Rename width | 6 |
| ROB | 256 |
| Physical register | 192(integer), 192(float) |
| Load Queue | 80 |
| Store Queue | 64|
| L1 Instruction Cache | 64KB/128KB (4/8-way) |
| L1 Data Cache | 64KB/128KB(4/8 way) |
| L2 Cache | 512KB/1MB, 8-way, non inclusive |
| L3 Cache | 2MB~8MB, 8-way, non inclusive |
| Physical RF size | 192x64 bits, 14R8W |
| ECC Support | Y |
| Virtual Memory Support | Y |
| Physical memory protection | Y |
| Virtualization | N |
| Vector | N |

## ISA Support

| Instruction Set | Description |
| ------- | ------------------- |
| I | Integer |
| M | Integer Multiplication and Division |
| A | Atomics |
| F | Single-Precision Floating-Point |
| D | Double-Precision Floating-Point |
| C | 16-bit Compressed Instructions |
| Zba | Bitmanip Extension - address generation |
| Zbb | Bitmanip Extension - basic bit manipulation |
| Zbc | Bitmanip Extension - carryless multiplication |
| Zbs | Bitmanip Extension - single-bit instructions |
| zbkb | Cryptography Extensions - Bitmanip instructions |
| Zbkc | Cryptography Extensions - Carry-less multiply instructions |
| zbkx | Cryptography Extensions - Crossbar permutation instructions |
| zknd | Cryptography Extensions - AES Decryption |
| zkne | Cryptography Extensions - AES Encryption |
| zknh | Cryptography Extensions - Hash Function Instructions |
| zksed | Cryptography Extensions - SM4 Block Cipher Instructions |
| zksh | Cryptography Extensions - SM3 Hash Function Instructions |
| svinval | Fine-Grained Address-Translation Cache Invalidation |

## Priviledge Mode

NANHU supports three levels of privilege mode: machine (M), supervisor (S), and user (U).

## Microarchitecture

Please refer to Section CPU Core for more details.

## Cache Controller

There is a cache controller connected to L3 Cache, which used to perform Cache Maintenance Operation (CMO). Programmers ought to use MMIO based memory access to trigger operation required.

The following is a register table of the L3 cache controller.

| Address | Width | Attr. | Description |
| ------- | ----- | ----- | ----------- |
| 0x3900_0100 | 8B | RW | `Tag` register of the interest cache block |
| 0x3900_0108 | 8B | RW | `Set` register of the interest cache block |
| 0x3900_0110 | 8B | RW | `Way` register of the interest cache block (deprecated) |
| 0x3900_0118 - 0x3900_0150 | 64B in total | RW | `Data` register of the interest cache block (deprecated) |
| 0x3900_0180 | 8B | RO | `Flag` register indicates ready for receiving next command<br>Value 1 indicates ready, 0 indicates not ready<br>
| 0x3900_0200 | 8B | WO | `Command` register for cache operation<br>Supported commands are:<br>Command Number 16 (`CMD_CMO_INV`)<br>Command Number 17 (`CMD_CMO_CLEAN`)<br>Command Number 18 (`CMD_CMO_FLUSH`) |

A standard Cache operation follows the following process:

1. Inquire the `Flag` register, which indicates ready for receiving requests when valid

2. Set `Tag` register to the tag of the interest cache block

3. Set `Set` register to the set of the interest cache block

4. Write command number to `Command` register

Afterwards, the command is desired to be done.

There are three commands available.

1. Command Number 16 (`CMD_CMO_INV`): Invalidate the cache block from cache hierarchy (Note that this operation may break cache coherence).

2. Command Number 17 (`CMD_CMO_CLEAN`): make cache block data in memory up-to-date. In other words, write back a block to memory if it is dirty in cache hierarchy. In current implementation, this command behaves just like `CMD_CMO_FLUSH`.

3. Command Number 18 (`CMD_CMO_FLUSH`): flush the cache block to memory. In other words, write back a block to memory and invalidate the block.
