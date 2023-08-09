# DFT Guide <br> DFT指南

This section describes the basic DFT requirements.
本节介绍DFT的基本要求。

## Shared-bus Design &nbsp; 共享总线设计

The traditional design flow of inserting MBIST around Memory has increasingly highlighted the contradiction of PPA (Performance, Power, Area) on high-performance processors. In order to avoid affecting the function timing as much as possible, reduce the area cost of MBIST, and reduce the test power consumption of MBIST, NANHU adopts the MBIST bus interface based on sharedbus.
在高性能处理器上，在内存周围插入 MBIST 的传统设计流程越来越凸显出 PPA（性能、功耗、面积）的矛盾。为了尽可能不影响功能时序，减少 MBIST 的面积成本，以及降低 MBIST 的测试功耗，南湖采用了基于共享总线的 MBIST 总线接口。
