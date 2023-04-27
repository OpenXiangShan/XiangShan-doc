# Tutorials at ASPLOS'23

We are hosting tutorials on XiangShan and MinJie during ASPLOS'23 at Vancouver, Canada on March 25, 2023.

## XiangShan: An Open Source High Performance RISC-V Processor and Infrastructure for Architecture Research
Over the past decade, agile and open-source hardware has gained increasing attentions in both academia and industry. In 2019, the SIGARCH Visioning Workshop “Agile and Open Hardware for Next-Generation Computing” in conjunction with ISCA invited eleven experts to present their visions on this direction. We believe that open-source hardware design, and more importantly, free and open development infrastructure, has the opportunity to bring more convenience to architecture research and stimulate innovations.

In this tutorial, we will present our efforts on XiangShan project. XiangShan is an open-source, industry-competitive, high performance RISC-V processor. It has raised the performance ceiling of publicly accessible processors and set the competitive groundwork for future computer architecture research. Behind the processor itself, there is also an agile development platform called Minjie that integrates a broad set of development tools as infrastructure. We will demonstrate how XiangShan, together with Minjie, helps researchers realize their innovative ideas agilely and obtain convincing evaluation results.

Target audience: Researchers on micro-architecture, high performance processor design, agile development and verification, etc. No prior experience with XiangShan/RISC-V/Chisel is necessary.

## Agenda

| Time | Topic | Slides |
| ---- | ----- | ------ |
| 9:00-9:25 | Introduction of the XiangShan Project | [PDF](https://github.com/OpenXiangShan/XiangShan-doc/raw/main/tutorial/20230325-ASPLOS23-1-Introduction-XiangShan.pdf) |
| 9:25-9:35 | Tutorial Overview and Highlights | [PDF](https://github.com/OpenXiangShan/XiangShan-doc/raw/main/tutorial/20230325-ASPLOS23-2-Tutorial-Overview.pdf) |
| 9:35-10:20 | Microarchitecture Design and Implementation | [PDF](https://github.com/OpenXiangShan/XiangShan-doc/raw/main/tutorial/20230325-ASPLOS23-3-Microarchitecture.pdf) |
| | Coffee Break | |
| 10:40-12:00 | Hands-on Development | [PDF](https://github.com/OpenXiangShan/XiangShan-doc/raw/main/tutorial/tutorial/20230325-ASPLOS23-4-Dev-Tools.pdf) |

## To be covered

- Introduction to XiangShan project

In June 2020, we launched XiangShan project. We have developed two major generations of codenamed YQH and NH respectively. The latest version of XiangShan processor achieves the highest performance of open-source RISC-V processors to the best of our knowledge. This topic will also cover XiangShan tape-out status, performance evaluation, future roadmap, etc.

- Introduction to micro-architecture and design concept of XiangShan processor

We will talk about micro-architecture design of XiangShan processor. XiangShan is a superscalar out-of-order RISC-V processor with RV64GCBK ISA support. It features high-throughput frontend with advanced branch predictor, six-width aggressive out-of-order execution engine, high-bandwidth load/store unit and highly configurable cache system. Written in Chisel, a high-level hardware description language, XiangShan also achieves high readability and maintainability.


- Demonstration of simulation flow and FPGA prototype of XiangShan processor

We have established a comprehensive workflow to simulate XiangShan processor and do prototype on FPGA. In this part, we will perform a practical demonstration, including argument details and key points to pay attention to.


- Introduction to infrastructure for XiangShan development

We will introduce the development infrastructure of XiangShan processor, also known as Minjie platform. Minjie is open sourced as well. It includes a series of tools that can accelerate the process of hardware development, functional verification, and performance evaluation. We will first talk about the principles and instructions of Minjie toolsets, and then demonstrate how to employ these tools to help quickly develop XiangShan processor.


- Typical cases sharing of modification and experimentation on XiangShan

We will present some typical cases for XiangShan development. For example, how to add an instruction, how to add a peripheral device and how to re-configure cache structure. Based on XiangShan and Minjie platform, many architectural works can be reproduced and accelerate the interactions between academia and industry.
