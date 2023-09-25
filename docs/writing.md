# 这是什么？

这是使用 [mkdocs](https://www.mkdocs.org/) 工具构建出来的香山文档。该工具可以将 markdown 格式的文档转化为网页并以美观的方式展现出来。经过 mkdocs 构建出来的工程可以被 readthedocs 托管到互联网上以供访问。[Chipyard](https://chipyard.readthedocs.io/en/stable/index.html)、[BOOM](https://docs.boom-core.org/) 等项目均以此种方式公开文档。（略有区别的是，他们使用的是 rst 格式的书写规范，而我们可能更倾向于 markdown）

# 添加新内容的流程

该文档与 Github 上的 [XiangShan-doc](https://github.com/OpenXiangShan/XiangShan-doc) 工程绑定。每当 `main` 分支接收到 git push 更新后，网页会自动重构展示新内容。

因此，如果要添加新内容，请按照如下的步骤：

- 克隆 [XiangShan-doc](https://github.com/OpenXiangShan/XiangShan-doc) 项目。
- 在本地安装 mkdocs 环境（参阅 [MkDocs Installation](https://www.mkdocs.org/user-guide/installation/)）
- 在本地安装 Material for MkDocs 主题 （参阅 [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/getting-started/)）(TLDR: `pip install -r docs/requirements.txt`)
- 在本地修改文档内容
- 通过 `mkdocs serve` 命令在本地预览文档，在浏览器中查看是否符合预期
- `git push`` 到远端

# 项目结构

mkdocs 项目结构非常简单，在根目录下有一个 mkdocs.yml 文件用于记录配置信息。其中我们需要重点关注其中的 nav 子项，它决定了整个文档在网页上展现的目录结构，可根据情况酌情修改；根目录下的 docs 文件夹中保存了 markdown 格式的文档，这也是我们需要添加或修改的实际内容。

# Material for MkDocs

我们使用 Material for MkDocs 基于以下的原因：

1. 更好的多级标题支持
1. 对导出为 pdf 友好
1. 可以整的花活比较多，参见：https://squidfunk.github.io/mkdocs-material/reference/

!!! note
    比如这种花活。

# 导出为 pdf

使用 Material for MkDocs 主题配合 mkdocs-with-pdf 插件，我们可以将整个文档自动导出为 pdf 文件。mkdocs.yml 中已经包含了一个预设的 pdf 导出配置。关于如何配置 pdf 导出环境及如何使用，请参考https://pypi.org/project/mkdocs-with-pdf/

!!! info
    注意，原生主题在将代码块导出为 pdf 时有一定问题，建议在导出 pdf 时使用 material 主题。