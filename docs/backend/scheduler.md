# 乱序调度器 Scheduler

在香山处理器中，`Scheduler` 模块是乱序调度的核心，其中维护了保留站 `ReservationStation`、物理寄存器堆 `Regfile`、物理寄存器状态 `BusyTable` 等模块。`Scheduler` 的顶层几乎没有逻辑，绝大多数都是模块间的连线。
