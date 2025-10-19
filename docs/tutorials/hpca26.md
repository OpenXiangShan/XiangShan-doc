# Tutorials at HPCA 2026

We are excited to host a tutorial on XiangShan at HPCA 2026! We look forward to seeing you in Sydney, Australia!


## Agenda

| Time | Topic                                            | Slides          |
| ---- | ------------------------------------------------ | --------------- |
| TBD  | General introduction                             | To be disclosed |
| TBD  | Introduction of XS-Gem5 and hands-on             | To be disclosed |
| TBD  | Coffee Break                                     |                 |
| TBD  | Microarchitecture design philosophy of XiangShan | To be disclosed |
| TBD  | Development workflows and hands-on               | To be disclosed |

## Startup

In this tutorial, we're hosting a code-server for our participants. Here are steps to take part in the hands-on sessions:

1. Open <https://t.xiangshan.cc> in your browser
2. Enter password: TO BE DISCLOSED ON SITE
3. By default you should see a terminal
   - If not, click Menu (triple dashes) on the top-left corner, then "Terminal > New Terminal"
4. Run `./start.sh` in the terminal
   - This will create a unique random id for you, and create your workspace at `/data/${random}`
5. When your workspace is created, it should be opened automatically
   - If not, click "Menu > File > Open Folder", enter `/data/${random}`, then click "OK"

## XiangShan: An Open-Source High Performance RISC-V Processor and Infrastructure for Architecture Research

Over the past decade, agile and open-source hardware has gained increasing attention in both academia and industry. In 2019, the SIGARCH Visioning Workshop “Agile and Open Hardware for Next-Generation Computing” in conjunction with MICRO invited eleven experts to present their visions on this direction. We believe that open-source hardware design, and more importantly, free and open development infrastructure, has the opportunity to bring more convenience to architecture research and stimulate innovations.

A prominent example in this domain is XiangShan, an open-source, high-performance RISC-V processor that competes at an industrial level. Since its release in 2021, XiangShan has pushed the boundaries of publicly available processors and established a competitive foundation for future research in computer architecture. In this tutorial, we will share the latest advancements in XiangShan and the agile development platform MinJie, with special emphasis on XS-GEM5, a software simulator calibrated with XiangShan. We will also demonstrate how XiangShan and MinJie enable researchers agilely implement their ideas and obtain reliable evaluation results. Our work was previously published at the MICRO'22 conference, and was selected as an IEEE Micro Top Pick from the 2022 Computer Architecture Conferences.

The major goal of the tutorial is to demonstrate how the XiangShan project can make architecture research more convenient and solid. XiangShan has been developing on an agile hardware development platform called MinJie. We believe MinJie has the potential to become one of the most important infrastructures for computer architecture researchers.

In this tutorial, we will guide our audience how to setup and make customization or do research on XiangShan agilely and obtain accurate and convincing evaluation results. Targeted audience includes researchers on architecture design, agile development, etc.

## Tutorial Contents

### General Introduction to the XiangShan Project

In June 2020, we launched XiangShan project. We have developed three major generations of codenamed YQH, NH and KMH respectively. KMH V2 achieves a score of 15 in SPEC 2006, which has the highest performance among open-source RISC-V processors to the best of our knowledge. We are working on KMH V3, which targets at a score of 22 in SPEC 2006 at the end of 2026.

XiangShan has been adopted by many companies from industry, including SpacemiT, Lanxin Computing, Innosilicon, etc. It has also been used in many academic research, which has been published in top conferences like MICRO and ISCA, etc.

### Calibrated XS-GEM5 Simulator for XiangShan Processor and Hands-on

XiangShan now has a calibrated software simulator XS-GEM5, as part of an integrated toolchain designed to support architecture exploration and development. We will demonstrate practical use cases of architectural exploration using XiangShan and XS-GEM5.

### Microarchitecture Design Philosophy of XiangShan Processor

XiangShan is a superscalar out-of-order RISC-V processor with full support for RVA23 profile. It features high-throughput frontend with advanced branch predictor, six-way aggressive out-of-order execution engine, high-bandwidth load/store unit and highly configurable cache system.

Instead of just giving a flat description of the microarchitecture of XiangShan, we will share our design philosophy and trade-offs in various aspects, hoping to provide insights for architecture researchers.

### Introduction to the Infrastructures for XiangShan Development and Hands-on

We will introduce the development infrastructure of XiangShan processor, also known as the MinJie platform, which is fully open-sourced. It includes a series of tools that can accelerate the process of hardware development, functional verification, and performance evaluation. We will first talk about the principles and instructions of MinJie toolsets, and then demonstrate how to employ these tools to help quickly develop XiangShan processor.

We have established a comprehensive workflow to simulate XiangShan processor and do prototype on FPGA. In this part, we will perform a practical demonstration, including argument details and key points to pay attention to. We will present some typical cases for XiangShan development. For example, how to add an instruction, how to add a peripheral device and how to re-configure cache structure. Based on XiangShan and Minjie platform, many architectural works can be reproduced and accelerate the interactions between academia and industry.
