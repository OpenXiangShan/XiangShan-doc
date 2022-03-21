香山参数系统说明
==================

香山的参数系统使用了 Context-Dependent Evironments 这个参数环境, 对应仓库中的 api-config-chipsalliance 这个 submodule. 更详细的使用说明可以参考[这个仓库的文档](https://github.com/chipsalliance/api-config-chipsalliance).

修改香山的配置可以参考[Configs.scala](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/top/Configs.scala)中 `MinimalConfig` 的处理方式, 在构建自己的 Config 的时候只需要将与默认配置不同的部分写在 Config 里即可。

使用类似的方式定义自己的 Config 之后可以在生成 Verilog /仿真时使用 `CONFIG` 参数确定使用哪种配置. 例如: `make emu CONFIG=MinimalConfig`.

香山的默认参数在 [Parameters.scala](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/Parameters.scala) 中, 一般不建议修改。


# 示例

举例来说, 如果想要修改香山的 ROB 和 IBuffer 大小, 则可以[在这里](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/top/Configs.scala)新建一个 `MyConfig`. `MyConfig` 会继承香山的所有默认参数. 接下来, 在 `MyConfig` 中修改 ROB 和 IBuffer 的参数:

```scala
class MyConfig(n: Int = 1) extends Config(
  new DefaultConfig(n).alter((site, here, up) => {
    case SoCParamsKey => up(SoCParamsKey).copy(
      cores = up(SoCParamsKey).cores.map(_.copy(
        RobSize = 32,
        IBufSize = 16
    )))
  })
)
```

随后, 就可以在生成仿真程序和 verilog 代码时, 在 `make` 命令中添加 `CONFIG=MyConfig` 这一选项, 将默认的 `DefaultConfig` 替换为 `MyConfig`.

