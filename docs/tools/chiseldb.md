# ChiselDB简介

在处理器调试过程中，有一些结构化数据使用波形存储效率太低且不方便分析(例如memory trace)，
因此我们开发了`ChiselDB`来将这些结构化数据存储在数据库中，方便查询和分析使用。

该工具利用`DPI-C`功能实现，在仿真代码中通过`DPI-C`调用C++函数，将我们希望保存的数据存进数据库中(`sqlite3`)。

## TlieLink Memory Trace

目前我们实现了对L1、L2、L3各个层级的memory trace记录，并可以根据需求进行扩展。

### 存储结构

| 字段 | 数据类型 | 备注 |
| ---  | ---      | ---  |
| NAME  | TEXT     | 节点名称(例如`L2_L1D_0`, `L3_L2_0`, `MEM_L3`) |
| CHANNEL | INT    | 通道编号 |
| OPCODE | INT | |
| PARAM | INT | |
| SOURCE | INT | |
| SINK | INT | |
| ADDRESS | INT | |
| DATA_0 | INT | |
| DATA_1 | INT | |
| DATA_2 | INT | |
| DATA_3 | INT | |
| USER | INT | |
| ECHO | INT | |
| STAMP | INT | 时间戳 |

(表名为`TL_LOG`)

### 使用方法

1.生成数据库

运行emu时添加参数`--dump-db`
``` bash
./build/emu --dump-db -e 10000 -i YOUR_IMAGE.bin
```
运行结束时，emu将会在`$NOOP_HOME/build`目录下以运行结束时间为文件名，
db为后缀生成一个sqlite3数据库文件(例如: `$NOOP_HOME/build/2021-10-31@22:54:30.db`)。

2.使用SQL语句操作数据库中的数据

使用标准sql语句即可对数据库进行增删查改

例如查询所有内存与L3 Cache之间的Tilelink请求:
``` bash
sqlite3 $NOOP_HOME/build/2021-10-31@22:54:30.db "SELECT * FROM TL_LOG WHERE NAME='MEM_L3'"
```
执行结果如下:

```
3|MEM_L3|0|6|0|0|0|2147483648|0|0|0|0|0|0|1159
4|MEM_L3|3|5|0|0|0|2147483648|3747295551104745583|333609570813414499|3756043814912998435|6075433238254179|0|0|1331
5|MEM_L3|3|5|0|0|0|2147483648|195082375286228243|3478239557827167507|3766452341692171539|396657079026267395|0|0|1332
12|MEM_L3|0|6|0|0|0|2147484160|0|0|0|0|0|0|1362
13|MEM_L3|3|5|0|0|1|2147484160|1181116006547|2280627634579|3380139262611|4479650890643|0|0|1508
14|MEM_L3|3|5|0|0|1|2147484160|6678674146451|7778185774739|8877697402771|9977209030803|0|0|1509
21|MEM_L3|0|6|0|0|0|2147484224|0|0|0|0|0|0|1536
22|MEM_L3|3|5|0|0|0|2147484224|11076720658835|12176232286867|13275743914899|14375255542931|0|0|1682
23|MEM_L3|3|5|0|0|0|2147484224|15474767170963|16574278798995|3747012976079540115|-2827554048163446121|0|0|1683
30|MEM_L3|0|6|0|0|0|2147484288|0|0|0|0|0|0|1711
```

本步骤中的查询结果是数据库中的原始数据，如果希望获得更好的可读性，请参考步骤3.

3.使用数据处理脚本

我们在`$NOOP_HOME/scripts/utils/convert.sh`处提供了一个awk脚本，用于在线处理数据库查询结果，
可以通过将数据库原始查询结果重定向到该脚本来获取具有更强可读性的输出。

使用举例:
``` bash
sqlite3 $NOOP_HOME/build/2021-10-31@22:54:30.db "SELECT * FROM TL_LOG WHERE NAME='MEM_L3'" | sh $NOOP_HOME/scripts/utils/convert.sh
```

效果如下:
```
1159 MEM_L3 A AcquireBlock Grow NtoB 0 0 80000000 0000000000000000 0000000000000000 0000000000000000 0000000000000000 user: 0 echo: 0 
1331 MEM_L3 D GrantData Cap toT 0 0 80000000 340111732000006f 04a138231a010c63 342025f304b13c23 001595930805d263 user: 0 echo: 0 
1332 MEM_L3 D GrantData Cap toT 0 0 80000000 02b5126300e00513 3045307308000513 3445207302000513 0581358305013503 user: 0 echo: 0 
1362 MEM_L3 A AcquireBlock Grow NtoB 0 0 80000200 0000000000000000 0000000000000000 0000000000000000 0000000000000000 user: 0 echo: 0 
1508 MEM_L3 D GrantData Cap toT 0 1 80000200 0000011300000093 0000021300000193 0000031300000293 0000041300000393 user: 0 echo: 0 
1509 MEM_L3 D GrantData Cap toT 0 1 80000200 0000061300000493 0000071300000693 0000081300000793 0000091300000893 user: 0 echo: 0 
1536 MEM_L3 A AcquireBlock Grow NtoB 0 0 80000240 0000000000000000 0000000000000000 0000000000000000 0000000000000000 user: 0 echo: 0 
1682 MEM_L3 D GrantData Cap toT 0 0 80000240 00000a1300000993 00000b1300000a93 00000c1300000b93 00000d1300000c93 user: 0 echo: 0 
1683 MEM_L3 D GrantData Cap toT 0 0 80000240 00000e1300000d93 00000f1300000e93 3400107300000f93 d8c2829300000297 user: 0 echo: 0 
1711 MEM_L3 A AcquireBlock Grow NtoB 0 0 80000280 0000000000000000 0000000000000000 0000000000000000 0000000000000000 user: 0 echo: 0
```

## 自定义数据结构

`ChiselDB`可以根据任何`Record`及其子类的硬件类型自动生成数据库中的一张表，表中字段对应`Record`类型的`elements`。

### 创建表/获取已有表

* 创建表可以通过`ChiselDB.createTable` API完成

``` scala
// API: def createTable[T <: Record](tableName: String, hw: T): Table[T]

import huancun.utils.ChiselDB

class MyBundle extends Bundle {
  val fieldA = UInt(10.W)
  val fieldB = UInt(20.W)
}

val table = ChiselDB.createTable("MyTableName", new MyBundle)
```

* `ChiselDB`不允许表重名，要在不同代码中获取一个已存在的表，可以使用`ChiselDB.getTable` API

``` scala
def getTable(tableName: String): Option[Table[_]]
```

### Dump数据

Dump数据需要使用`table.log`方法，其功能是在使能信号有效时将硬件数据值写入数据库对应的表中,
其中`site`参数指`table.log`调用地点，用来区分数据库中同一张表的不同写入来源。

``` scala
/* APIs
def log(data: T, en: Bool, site: String = "", clock: Clock, reset: Reset)
def log(data: Valid[T], site: String, clock: Clock, reset: Reset): Unit
def log(data: DecoupledIO[T], site: String, clock: Clock, reset: Reset): Unit
*/

table.log(
  data = my_data /* hardware of type T */,
  en = my_cond,
  site = "MyCallSite",
  clock = clock,
  reset = reset
)
```
