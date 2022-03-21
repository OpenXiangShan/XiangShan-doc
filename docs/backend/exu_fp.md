# 浮点部件简介

香山南湖版本使用的浮点部件在[fudian](https://github.com/OpenXiangShan/fudian)处进行维护，其中包含以下模块:

* Two-path Floating-point Adder
* Floating-point Multiplier
* Cascade FMA
* Float -> Int Converter
* Int -> Float Converter
* Float -> Float Converter
* Floating-point Divider and SQRT Unit

其中FMA操作延迟为5拍，其余运算均为3拍延迟。

## DIV & SQRT

香山的浮点除法部件和定点除法一样采用 SRT16 算法。浮点开方部件使用 SRT4 算法。两者共用预处理和后处理逻辑。