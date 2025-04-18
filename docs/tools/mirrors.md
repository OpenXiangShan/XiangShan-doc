# 使用代码仓库镜像

我们在 Gitee、GitLink 等平台提供了香山项目大部分代码仓库的只读镜像。如果您的网络环境访问 GitHub 存在困难，您可以参照下面的介绍使用这些镜像。

请注意，Gitee、GitLink 只作为代码仓库的只读镜像使用，请在 GitHub 平台报告缺陷、提出问题、提交贡献。

## 使用 Gitee 上的代码仓库镜像

Gitee 上的镜像位于 [OpenXiangShan 组织](https://gitee.com/OpenXiangShan/) 下，包含了构建香山处理器所需的所有仓库，定时与 GitHub 仓库同步。

要使用 Gitee 镜像仓库代替原有 GitHub 仓库，请执行以下命令：

```bash
git config --global url."https://gitee.com/OpenXiangShan/".insteadOf https://github.com/OpenXiangShan/
git config --global --add url."https://gitee.com/OpenXiangShan/".insteadOf https://github.com/chipsalliance/
git config --global --add url."https://gitee.com/OpenXiangShan/".insteadOf https://github.com/ucb-bar/
```

现在，您可以参照 [前端开发环境](xsenv.md) 等文档执行 `git clone`、`make init` 等命令了。Git 会自动将香山相关的 GitHub 的仓库地址替换为 Gitee 的对应镜像地址。

> 上述命令为 Git 设置了一组全局的 URL 重写规则，要求 Git 自动将 GitHub 仓库地址替换为 Gitee 的镜像仓库地址。例如，运行 `git clone https://github.com/OpenXiangShan/XiangShan.git` 时，实际 Git 执行的是 `git clone https://gitee.com/OpenXiangShan/XiangShan.git`。
>
> 香山代码中使用到了 [CHIPS Alliance](https://github.com/chipsalliance)、[UC Berkeley Architecture Research](https://github.com/ucb-bar) 提供的一些组件，例如 [berkeley-hardfloat](https://github.com/ucb-bar/berkeley-hardfloat) 等。为此，我们在 Gitee 的 OpenXiangShan 组织下也提供了这些仓库的镜像。

如果您发现 Gitee 上缺少一些仓库的镜像，欢迎通过 Issue 等渠道向我们报告。

如果您不再需要使用 Gitee 镜像仓库，可以执行以下命令：

```bash
git config --global --unset-all url."https://gitee.com/OpenXiangShan/".insteadOf
```

## 使用 GitLink 上的代码仓库镜像

GitLink 上的镜像位于 [OpenXiangShan 组织](https://www.gitlink.org.cn/OpenXiangShan/) 下，包含了构建香山处理器所需的大部分仓库。

目前，GitLink 上的镜像仍在建设中。

