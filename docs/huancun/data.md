# DataStorage

`DataStorage`模块负责cache数据的存储与读写，
根据Tilelink各通道特性，`DataStorage`模块共有2个读口(`sourceC_r`, `sourceD_r`)，
3个写口(`sinkD_w`, `sourceD_w`, `sinkC_w`)，
为了提高读写并发性，该模块可以参数化配置内部bank数量，不同bank之间可以并行读写。
此外，该模块还支持为SRAM读出的数据进行参数化的加拍，从而达到更高的频率要求。
