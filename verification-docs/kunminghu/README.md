# 昆明湖 V1 验证文档说明

本文档为昆明湖 V1 验证文档，对应香山 kunminghu 分支：https://github.com/OpenXiangShan/XiangShan/tree/kunminghu

**!!** 请注意，该验证文档为**并非**完整交付版本，仅为初始版本

**!!** 其中部分模块的描述存在遗漏或缺陷，**任何**内容均可能在后续版本中被修改。



## 验证文档目录结构

├─Backend：  乱序执行后端，包括 CtrlBlock、ExuBlock、ReservationStation
├─Cache：  L2 缓存，**目前暂缺**
├─Frontend：  取指前端，包括 BPU、FTQ、IBuffer、ICache、IFU
└─LSU：  访存单元，包括 DCache、Memblock、MMU、Prefetch



## 验证文档接口人

	        模块	接口人
	前端设计		
		    BPU 陈国凯
		    FTQ 高泽宇
		    IBuffer 满洋
		    ICache 宋政伟
		    IFU 陈国凯
	后端设计		
		    CtrlBlock 张梓悦
		    ExuBlock 胡轩
		    RS 胡轩
	访存设计		
		    DCache 张林隽
		    LSU 吴凌云
		    MMU 冯浩原
		    Prefetch 李昕
	缓存设计
		    TODO
