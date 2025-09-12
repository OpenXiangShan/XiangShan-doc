---
slug: read-find-fix-season1-en
date: 2025-09-15
categories:
- Event-en
---

# Read, Find, Fix! Become a XiangShan Documentation Guardian — "Bug Hunt in Docs" Season 1

Have you ever been discouraged by an incomprehensible “scripture-like” documentation when using an open-source project? Or do you have sharp eyes that can always spot tiny mistakes in docs? Now is your chance!

The XiangShan community officially launches **"Bug Hunt in Docs" Season 1**, inviting all open-source enthusiasts and explorers to join us in finding issues and improving the quality of XiangShan documentation!

<!-- more -->

## 💡 Why do we need a "Bug Hunt"?

Clear, accurate, and easy-to-read documentation is the cornerstone of open-source prosperity. It helps newcomers get started quickly and enables experienced developers to understand project details more efficiently.

Through this campaign, we aim to:

1. **Improve readability and accuracy**: Identify and fix vague, incorrect, or outdated content.
2. **Encourage deeper community engagement**: Let more people dive into XiangShan by reading its documentation and actively contributing to the community.

## 🎯 Who can participate?

No matter if you are:

* A developer, user, or documentation contributor in the open-source community
* A tech enthusiast interested in XiangShan
* Even a newcomer to open source who is willing to read documentation

👉 **We welcome you with open arms! No prior experience required — all you need is a "bug-hunting" mindset.**

## 🗓️ Campaign Duration

**September 15, 2025 — October 31, 2025**

Progress and final results will be announced on the [XiangShan Community Website](https://xiangshan.cc). Stay tuned!

## 📚 Target Documents

This campaign mainly focuses on the Chinese and English documentation of the following XiangShan open-source projects:

* **XiangShan Open-Source Processor User Guide**
* Docs: [User Guide Online Documentation](https://docs.xiangshan.cc/projects/user-guide/zh-cn/latest/introduction/)
* Repo: [OpenXiangShan/XiangShan-User-Guide](https://github.com/OpenXiangShan/XiangShan-User-Guide)

* **XiangShan Open-Source Processor Design Docs**
* Docs: [Design Docs Online](https://docs.xiangshan.cc/projects/design/zh-cn/latest/frontend/BPU/Composer/)
* Repo: [OpenXiangShan/XiangShan-Design-Doc](https://github.com/OpenXiangShan/XiangShan-Design-Doc)

## 📝 How to participate?

The process is simple — just a few steps to become a XiangShan Documentation Guardian!

### 1. Read the docs

Carefully read the listed documentation, get familiar with its structure, and focus on the sections you are most interested in or knowledgeable about to better identify potential issues.

### 2. Claim a task

To avoid overlapping efforts, this campaign uses a **claim-before-contribute** model:

* [User Guide Task List](https://github.com/OpenXiangShan/XiangShan-User-Guide/issues/27)
* [Design Docs Task List](https://github.com/OpenXiangShan/XiangShan-Design-Doc/issues/88)

Before hunting bugs, check the task list and pick a file you want to claim (e.g., `docs/zh/introduction.md`). Comment under the Issue with:

```

/claim docs/zh/introduction.md

```

The bot will automatically record your username.

Multiple participants can claim the same task, but we recommend choosing unclaimed files first.

If you want to cancel a claim, comment:

```

/unclaim docs/zh/introduction.md

```

### 3. Find issues

Once you’ve claimed a task, start hunting! Common issues include:

* **Vague or unclear expressions**: Poor wording that makes content hard to understand
* **Technical errors or outdated info**: Incorrect details, broken examples, or obsolete information
* **Missing explanations or examples**: Lacking key clarifications or usage examples
* **Formatting/layout problems**: Messy structure, broken images/tables, rendering errors, inconsistent layout, etc.
* **Typos and grammar mistakes**: Misspellings, incorrect grammar, or punctuation issues
* **Translation problems**: Mistranslations, inconsistent terminology, or improper handling of technical terms
* **Other**: Any additional problems that affect documentation quality

### 4. Submit an Issue

When you find a problem, submit an **Issue** in the corresponding repository with full details.

* Choose **Document Bug Report** when creating the Issue
* Fill in all required fields according to the template

After submission, wait for community reviewers to confirm and evaluate your Issue.

For simpler problems, you may directly submit a Pull Request (PR).

### 5. Submit a Pull Request

Once your Issue is confirmed, you can make changes and submit a PR.

PR requirements:

* Title format: `fix(part/chapter): fix something`
* Description in **English**, detailing the changes
* If fixing a specific Issue, add `Fix #id` at the end

Example:

```plaintext
fix(memblock/MMU): fix wrong description of need_gpa

The previous document said that xxx, but actually xxxx.

Fix #23.
```

⚠️ Note: English docs are maintained via [Weblate](https://hosted.weblate.org/projects/openxiangshan/) and synced to GitHub. If you’re unfamiliar with Weblate, it’s recommended to just file an Issue and let maintainers handle it.

## 🏆 Scoring Rules

* **Each valid Issue**: **1–3 points**, based on importance and report quality
    * First Issue in a repo may receive the *Good First Issue* label and a **2× bonus**
* **Each merged PR**: **3–5 points**, based on significance and contribution quality
    * First PR in a repo gets a **2× bonus**
* **Total score = Issue points + PR points**

## 🎁 Rewards

To appreciate your efforts, we’ve prepared generous rewards based on your points and contributions:

* **Top Contributor Award (10 winners)**: Logitech Lift ergonomic mouse + *RISC-V CPU Design: XiangShan Source Code Analysis* (by Prof. Mao Dechao) + XiangShan eco bag + 100 community points
* **Best Issue Award (15 winners)**: 50 points + portable outdoor inflatable camping bed + XiangShan fridge magnet
* **Active Participation Award (30 winners)**: 10 points + handheld head massager + XiangShan stickers
* **Special Reward**: Any PR merged into the main branch earns an **extra 5 points**

> **Community points** can be redeemed for training, gifts, and leaderboard ranking.

## 🤝 Community Support

If you encounter any issues during the campaign, feel free to ask in GitHub Issues or follow XiangShan’s official community channels for updates and support.

* XiangShan Technical Discussion QQ Group: **879550595**

**We look forward to your participation — let’s safeguard XiangShan documentation and build a better open-source community together!**
