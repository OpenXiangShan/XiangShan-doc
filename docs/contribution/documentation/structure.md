# 结构

!!! note
    本节仅适用于使用新版文档框架的[用户手册](https://github.com/OpenXiangShan/XiangShan-User-Guide/)和[设计文档](https://github.com/OpenXiangShan/XiangShan-Design-Doc/)。

    由于新版文档框架同时使用 Mkdocs 和 Pandoc 两套工具链来分别生成在线网站和可打印的 PDF 文件，我们在撰写文档时需要同时满足两方的要求和约定。

## 章节结构
### 管理章节结构
**注意：撰写文档时需同时考虑 Pandoc 和 MkDocs 的文档的章节结构**。

Pandoc 使用 include 机制来处理章节关系，而 MkDocs 使用 mkdocs.yml 来记录章节结构。

文档目录宜按照章节分级排列。

```plain
docs
├── Part
│   ├── index.md
│   ├── Section1
│   │   ├── .index.md
│   │   ├── index.md
│   │   ├── Subsection1.md
│   │   └── SubSection2.md
│   ├── Section2.md
│   └── Section3.md
```



**每个带文件夹的章节都需要一个入口文件**，命名为 `index.md` 或 `.index.md`。这个文件可能包含导言，并通过 include 代码块引入子章节或其他页面。`index.md` 和 `.index.md` 可以同时存在。

+ 对于 Pandoc，在填写 `include` 代码块时，应当以当前文件为参照点；
+ 对于 MkDocs，在填写 `mkdocs.yml` 的 `nav` 部分时，应当以 `docs` 目录为参照点。

#### 例 1 - 只有 `index.md`
适用于该章节只有简单导言的情况，导言中不能有二级标题。

示例中的 include 代码块引入了：

+ （子文件夹形式）Section1
+ （单独文件形式的）Section2
+ （单独文件形式的）Section3。

```markdown
# 第一章

这里是这个章节的简单导言，可以简要介绍本章节内容。

这里不能出现二级标题。如果需要二级标题，请参考例 3。

``` {.include}
Section1/.index.md
Section2.md
Section3.md
```
```

对于此例，pdf 版的目录类似于：

```markdown
1 第一章
  1.1 第一节
  1.2 第二节
  1.3 第三节
```

同时，需要配置 `mkdocs.yml` 的 `nav` 部分如下：

```yaml
nav:
- 第一章:
  - index.md
  - 第一节:
    - ...... # 递归
  - 第二节: Chap1/Section2.md
  - 第三节: Chap1/Section3.md
```

#### 例 2 - 只有 `.index.md`
适用于该章节没有导言的情况，也无需整体介绍。**通常应避免此种情况。**`**.index.md**`** 中不应有任何正文内容。**

示例中的 include 代码块引入了：

+ （子文件夹形式）Section1
+ （单独文件形式的）Section2
+ （单独文件形式的）Section3。

```markdown
# 第二章

``` {.include}
Section1/.index.md
Section2.md
Section3.md
```
```

对于此例，pdf 版的目录类似于：

```markdown
2 第二章
  2.1 第一节
  2.2 第二节
  2.3 第三节
```

同时，需要配置 `mkdocs.yml` 的 `nav` 部分如下：

```yaml
nav:
- 第二章:
  - 第一节:
    - ...... # 递归
  - 第二节: Chap2/Section2.md
  - 第三节: Chap2/Section3.md
```

#### 例 3 - 同时有 `index.md` 和 `.index.md`
适用于该章节有一个“整体介绍”子章节的情况。`**.index.md**`** 中不应有任何正文内容。**

示例中的 include 代码块引入了：

+ 章节整体介绍 index.md
+ （子文件夹形式）Section1
+ （单独文件形式的）Section2
+ （单独文件形式的）Section3。

```markdown
# 第三章

``` {.include}
index.md
SectionA/.index.md
SectionB.md
SectionC.md
```
```

```markdown
# 第三章整体介绍

这里可以是第三章整体内容的介绍，这是导言。

## 整体介绍第一部分

这里可以有二级标题哦。

## 整体介绍第二部分

这里可以有二级标题哦。
```

对于此例，pdf 版的目录类似于：

```markdown
3 第三章
  2.1 第三章整体介绍
    2.1.1 整体介绍第一部分
    2.1.2 整体介绍第二部分
  2.2 第甲节
  2.3 第乙节
  2.4 第丙节
```

同时，需要配置 `mkdocs.yml` 的 `nav` 部分如下：

```yaml
nav:
- 第三章:
  - Chap3/index.md
  - 第甲节:
    - ...... # 递归
  - 第乙节: Chap3/Section2.md
  - 第丙节: Chap3/Section3.md
```

### 以一级标题为页面标题
**所有文件均以一级标题为页面标题**，需要且仅需要包括当前页面（章节）标题。

### 减少单文件内的标题层次
**请尽可能减少单文件内的标题层次**，否则可能导致文档手册整体的章节层次太多。

例如，以下的章节设置可能显得冗余

```markdown
## 功能描述

### 功能概述
这里是功能概述。这里是功能概述。

### 功能详述

#### 功能一
这里是功能一。这里是功能一。

#### 功能二
这里是功能二。这里是功能二。
```

可以简化为

```markdown
## 功能
这里是功能概述。这里是功能概述。

### 功能一
这里是功能一。这里是功能一。

### 功能二
这里是功能二。这里是功能二。
```

