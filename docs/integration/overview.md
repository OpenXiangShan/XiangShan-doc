XiangShan-2 (NANHU) support single-core and dual-core configurations, where each core has its own private L1/L2 cache. L3 is shared by multiple cores.

NANHU communicates with the uncore through 3 AXI interfaces, including the memory port, the DMA port and the peripheral port. It also has clock, reset, and JTAG interfaces. Please refer to the integration guide for more detailed information.

NANHU targets 2GHz@14nm, and 2.4GHz~2.8GHz@7nm.

# Typical Configurations
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

# ISA Support

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

# Priviledge Mode

NANHU supports three levels of privilege mode: machine (M), supervisor (S), and user (U).

# Microarchitecture

Please refer to Section CPU Core for more details.
