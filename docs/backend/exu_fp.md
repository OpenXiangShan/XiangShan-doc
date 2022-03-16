# 浮点部件简介

香山南湖版本使用的浮点部件在[fudian](https://github.com/OpenXiangShan/fudian)处进行维护，其中包含以下模块:

* Two-path Floating-point Adder
* Floating-point Multiplier
* Cascade FMA
* Float -> Int Converter
* Int -> Float Converter
* Float -> Float Converter

其中FMA操作延迟为5拍，其余运算均为3拍延迟。
