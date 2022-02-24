# 这是什么？

这是使用 [mkdocs](https://www.mkdocs.org/) 工具构建出来的香山文档。该工具可以将 markdown 格式的文档转化为网页并以美观的方式展现出来。经过 mkdocs 构建出来的工程可以被 readthedocs 托管到互联网上以供访问。[Chipyard](https://chipyard.readthedocs.io/en/stable/index.html)、[BOOM](https://docs.boom-core.org/) 等项目均以此种方式公开文档。（略有区别的是，他们使用的是 rst 格式的书写规范，而我们可能更倾向于 markdown）



# 添加新内容的流程

该文档与 XiangShan-doc 的 Github 工程绑定：https://github.com/OpenXiangShan/XiangShan-doc，注意要切换到 mkdocs 分支。每当该分支接收到 git push 更新后，网页会自动重构展示新内容。

因此，如果要添加新内容，请按照如下的步骤：

* 克隆 XiangShan-doc 项目，切换到 mkdocs 分支
* 在本地安装 mkdocs 环境（请参考https://www.mkdocs.org/user-guide/installation/）
* 在本地修改文档内容
* 通过 mkdocs serve 命令在本地 build 文档，在浏览器中查看是否符合预期
* git push 到远程



# 项目结构

mkdocs 项目结构非常简单，在根目录下有一个 mkdocs.yml 文件用于记录配置信息。其中我们需要重点关注其中的 nav 子项，它决定了整个文档在网页上展现的目录结构，可根据情况酌情修改；根目录下的 docs 文件夹中保存了 markdown 格式的文档，这也是我们需要添加或修改的实际内容。

