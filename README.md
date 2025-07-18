# XiangShan-doc
Documentation for XiangShan

这是香山的官方文档仓库。

* 香山微结构文档已托管到 ReadTheDocs 平台，欢迎访问 https://xiangshan-doc.readthedocs.io

* slides 目录下存放了我们的技术汇报，包括 2021 RISC-V 中国峰会的报告等内容



## 联系我们 Contact us

邮件列表：xiangshan-all AT ict DOT ac DOT cn

Mailing list: xiangshan-all AT ict DOT ac DOT cn



## 关注我们

- **微信公众号：香山开源处理器**

![wechat](articles/wechat.png)

- **知乎：[香山开源处理器](https://www.zhihu.com/people/openxiangshan)**

- **微博：[香山开源处理器](https://weibo.com/u/7706264932)**



## Translations needed

We need to translate most of the documentations to English and other languages. Contributions welcomed!



## 实习生计划 Interns

欢迎加入开源英才实习生计划（长期有效），具体内容请点击此[链接](articles/开源英才实习生计划.pdf)。



## 香山是什么？

2019 年，在中国科学院支持下，**由[中国科学院计算技术研究所](http://www.ict.ac.cn/)牵头发起“香山”高性能开源 RISC-V 处理器项目**，研发出目前国际上性能最高的开源高性能RISC-V处理器核“香山”，在全球最大的开源项目托管平台 GitHub 上获得超过 2500 个星标（Star），形成超过 277 个分支（Fork），成为国际上最受关注的开源硬件项目之一，得到国内外企业的积极支持——16 家企业联合发起开源芯片创新联合体，围绕“香山”进一步联合开发，形成示范应用，加速 RISC-V 生态建设。

我们的目标是成为**面向世界的体系结构创新开源平台**，服务于工业界、学术界、个人爱好者等的体系结构研究需求。此外，我们希望在香山的开发过程中，**探索高性能处理器的敏捷开发流程**，建立一套基于开源工具的高性能处理器设计、实现、验证流程，大幅提高处理器开发效率、降低处理器开发门槛。

**香山将保持半年左右的微结构迭代周期、流片周期，持续进行微结构创新与敏捷开发方法实践。** 香山处理器的正式开发从 2020 年 6 月开始，1e3fad1 是我们[第一个提交](https://github.com/OpenXiangShan/XiangShan/commit/1e3fad102a1e42f73b646332d264923bfbe9c77e)的哈希值，代码仓库中在此之前的提交均属于 [2019 年第一期一生一芯计划产出的果壳处理器](https://github.com/OSCPU/NutShell)。在 2021 年 7 月，香山处理器的第一版（代号雁栖湖）已经投片，在 28nm 的工艺节点下达到 1.3GHz 的频率。目前（2022 年 3 月），香山处理器第二版架构（代号南湖）的 RTL 代码已经冻结，正在进行后端设计验证流程，目标是在 14nm 工艺节点下频率达到 2GHz。我们希望通过持续不断的优化与流片验证，逐步提高香山处理器的 PPA 水平，让香山成为一个开源的工业级别处理器，并成为面向世界的体系结构创新开源平台。

**香山处理器将始终坚持开源策略，坚定地开源我们所有的设计、验证、基础工具代码。** 我们非常感谢社区对香山的贡献，在硬件设计方面，香山处理器的部分模块设计受到了开源处理器、公开论文等的启发，曾参考了现有的开源 rocket-chip、berkeley-hardfloat、SiFive block-inclusivecache 等代码。我们在 Chisel 开源社区的现有总线工具、浮点运算单元、系统缓存等基础上，修改完善了它们的功能，同时优化了频率、吞吐等性能指标。与此同时，我们非常欢迎社区基于香山进行开发或者使用香山项目的代码。在众多开源协议中，我们选择了[木兰宽松许可证第 2 版](http://license.coscl.org.cn/MulanPSL2/)，希望（1）始终保持香山处理器的开放性，木兰宽松许可证不具有传染性，用户可以放心使用；（2）立足中国国内、面向全世界，木兰宽松许可证以中英文双语表述，中英文版本具有同等法律效力。

**香山处理器积极地拥抱开源社区，非常欢迎来自社区的贡献。** 我们看到，一些开源 RISC-V 处理器项目很少接收外部代码提交，我们理解这一现象背后有观念与技术上的多重原因，如担心开发计划冲突、处理器设计需要兼顾多方面需求、难以评估外部贡献的质量等。对于香山项目来说，在观念方面，我们非常欢迎外部贡献，如提交问题、提交特性需求、提交代码等，每一条意见与建议我们都会认真考虑与评估。举例来说，Chisel 对工业界仍然是一个新东西，如果您更熟悉 Verilog/SystemVerilog、但希望为香山提交代码贡献，我们欢迎您向[这个仓库](https://github.com/OpenXiangShan/XS-Verilog-Library)提交 Pull Request。在技术层面，我们希望探索一套评估代码改动质量的流程与工具，由基础流程来确定是否接受一个代码提交。举例来说，我们希望在不久的未来，开放一套更快速、更准确的性能采样框架，来评估一个架构改动带来的性能收益，当代码提交满足不破坏已有的模块性和扩展性、具有较为一定性能收益、具有良好的代码风格等条件时，我们将接收这一代码修改。如果用一句话总结我们的开发者策略，我们非常欢迎任何对香山有益的讨论、问题提交、代码修改等。

**除了微结构探索之外，香山项目还希望探索并建立一套高性能处理器的敏捷开发流程。** 香山处理器的目标是成为面向世界的体系结构创新开源平台，基础能力、设施、流程的建立是香山处理器长期高质量发展的关键，我们将保持长期稳定的投入，不断努力建立处理器敏捷开发的基础设施、基础流程。在香山项目初期，我们沿用了果壳处理器的开发与验证框架。在香山项目的推进过程中，我们对其进行了大量改进，添加了包括仿真检查点、压缩文件加载、多核验证支持等功能。目前，香山处理器的验证环境相比果壳处理器已有大量改进，丰富的基础工具支撑起了香山这一复杂度量级的敏捷验证流程。此外，UCB 和 Chipyard 框架是我们学习的榜样，我们参考或使用了他们发起的很多开源项目。我们希望，随着香山项目的推进与深入，我们能够推动开源社区的不断进步，与开源社区一道，推动建立高性能处理器的敏捷开发流程与基础设施。

香山处理器的正式开发从 2020 年 6 月开始，经过不到 2 年的努力，我们实现了香山雁栖湖版本的流片，并即将完成南湖版本的流片准备工作。从香山项目参与者的角度，在过去约 2 年的时间中，共有二十多位来自中科院计算所、鹏城实验室、深圳大学、华中科技大学、北京大学等高校和科研单位的老师及同学参与到了香山处理器雁栖湖版本的前端流程中。在项目开始时，香山团队中大多数老师和同学并没有丰富的高性能处理器设计和实现经验，但经过一年在香山项目中的锻炼，大家建立起了对高性能处理器的初步认识。在香山处理器中，包括核心前端、后端、访存流水线、L1 Cache、L2 Cache 对下一致性支持等在内的关键代码均由开发团队从零实现，我们对代码的所有修改历史均在 Git 提交记录中可见。香山处理器的物理设计流程主要由我们在鹏城实验室的后端工程师团队完成。

**我们清楚地认识到，香山处理器距离业界主流水平还有很大的差距，比如在很多技术点的方案选择上，我们做的不够好。香山处理器的目标是成为面向世界的体系结构创新开源平台，我们非常欢迎来自业界前辈、高性能处理器爱好者、开源社区等提出建议和意见，只要对香山处理器项目是有益的，我们都会接受并且改进，同时，我们也欢迎并且鼓励更多的人一起加入香山处理器的开发，推动香山项目的持续创新。**




## 推荐关于香山的报道

香山始终坚持实事求是的原则，始终保持建立开源平台、探索敏捷开发的初衷，不希望在宣传上出现任何可能导致误解的内容。

自香山在 2021 年 6 月举办的 RISC-V 中国峰会上正式发布以来，我们在社交媒体、自媒体、新闻媒体上看到了很多对香山处理器的报道，其中有一些是作者的“自我发挥”，存在误导读者的可能性。为此我们特意创建了一个[辟谣专区](https://github.com/OpenXiangShan/XiangShan-doc/tree/main/clarifications)，用来澄清一些广为流传的误会。

我们推荐以下关于香山处理器的报道，来自于我们的官方发布和科普渠道：

- 包云岗老师亲自撰写的[香山处理器相关介绍](https://www.zhihu.com/question/466393646/answer/1955410750)
- 中国开放指令生态（RISC-V）联盟的官方公众号的[文章](https://mp.weixin.qq.com/s/MAkxKZ1eS4UwBkvgD91Xng)
- 香山处理器的[源码](https://github.com/OpenXiangShan)

香山的核心理念之一是开源、开放，针对这一话题，我们推荐阅读[孙凝晖院士的《论开源精神》](https://mp.weixin.qq.com/s/1Irs9a0EKoB7P-J_4ju66A)。

## LICENSE

XiangShan Documents are licensed under CC BY 4.0.

Copyright © 2021-2025 The XiangShan Team
