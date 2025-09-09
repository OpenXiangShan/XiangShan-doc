# 文档贡献指南

文档是香山项目的重要组成部分之一。如果您想要对香山的文档做贡献，请先阅读本指南。

## 概述

香山文档主要使用流行的 Markdown 标记语言编写，目前分为了以下三个部分：

| 名称  | 存储库 | 网址  | 文档框架 |
| :---: | :---- | :--- | :------: |
| 综合文档 | [OpenXiangShan/XiangShan-doc](https://github.com/OpenXiangShan/XiangShan-doc) | [https://docs.xiangshan.cc/](https://docs.xiangshan.cc/) | 旧版文档框架 |
| 用户手册 | [OpenXiangShan/XiangShan-User-Guide](https://github.com/OpenXiangShan/XiangShan-User-Guide) | [https://docs.xiangshan.cc/projects/user-guide](https://docs.xiangshan.cc/projects/user-guide) | 新版文档框架 |
| 设计文档 | [OpenXiangShan/XiangShan-Design-Doc](https://github.com/OpenXiangShan/XiangShan-Design-Doc) | [https://docs.xiangshan.cc/projects/design](https://docs.xiangshan.cc/projects/design) | 新版文档框架 |

不同部分使用了不同的文档框架，可分为旧版文档框架和新版文档框架，他们支持的特性有一些差异。

## 新版文档框架

新版文档框架提供了生成网站和 PDF 版式文件两套流程：

* 基于 Python-Markdown、Mkdocs、Mkdocs-Material 生成网站的流程
* 基于 Pandoc、LaTeX 生成 PDF 版式文件的流程

这基本满足了工业界和开源社区对处理器文档的不同需求。

新版文档框架提供了一系列工具、插件来为两套流程提供基本相同的编写体验，托管于 [OpenXiangShan/docs-utils](https://github.com/OpenXiangShan/docs-utils) 仓库。

有关在本地使用文档框架、构建网站和 PDF 版式文件的操作方法，请参见各文档仓库的 README：[用户手册](https://github.com/OpenXiangShan/XiangShan-User-Guide)、[设计文档](https://github.com/OpenXiangShan/XiangShan-design-Doc)

## 参与撰写

为提高文档质量，我们制定了一些规则，请在开始撰写之前仔细阅读：

* [文档组织规则](structure.md)
* [文档排版规则](formatting.md)
* [语言风格建议](#) （尚未完成）

为文档提交贡献的流程与要求与代码提交保持一致，请参阅相关文档。

## 翻译与国际化

香山文档通常以中文为原始语言，并通过 [Weblate 平台](https://hosted.weblate.org/) 进行翻译与国际化。

目前，我们为用户手册、设计文档等提供英文翻译版本。翻译版本的表述可能与原文存在差异，如出现冲突，应以中文原文为准。

对翻译版本的修改应首先在 [Weblate 平台](https://hosted.weblate.org/projects/openxiangshan/) 上进行，然后通过 Weblate 机制同步到 GitHub 仓库。一般情况下，不能手动修改 GitHub 仓库中的翻译后的文件。

文档翻译过程中可能会使用大语言模型等人工智能技术。
