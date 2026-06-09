---
slug: biweekly-104-en
date: 2026-06-08
categories:
  - Biweekly-en
---

# [XiangShan Biweekly 104] 20260608

Welcome to XiangShan biweekly column! Through this column, we will regularly share the latest development progress of XiangShan. This is the 104th issue of the biweekly report.

We recently received many issues on GitHub! We welcome every developer who is interested in XiangShan to communicate and provide feedback with us. Whether it's bug reports, feature suggestions, or questions about using XiangShan, we will respond in a timely manner. In this biweekly report, we share a very interesting issue with you, through which we fixed four bugs.

As for the recent development of XiangShan, the frontend fixed some bugs while continuing to optimize timing; the backend implemented new extensions and fixed some bugs; the memory subsystem expanded L2 to 2MB while optimizing PPA and code style; XSAI implemented overlapping execution of the C matrix memory access module and fixed some bugs.

<!-- more -->

## Development Stories

Recently, we have receved an [issue #5910](https://github.com/OpenXiangShan/XiangShan/issues/5910), ~~(actually we have received many, but the analysis process of this one is particularly interesting)~~. The issue pointed out that when an RVI instruction crosses a page boundary, and both pages are in MMIO space, with the former page being executable and the latter page being non-executable, difftest reports an error.

```plaintext
RTL : mtval=0x1dfaf000, mepc=0x1dfaf000, mcause=0x1 (instruction access fault)
NEMU: mtval=0x1dfadffe, mepc=0x1dfadffe, mcause=0x1 (instruction access fault)
```

At first glance, this issue seems to be a simple difftest failure caused by a mis-alignment between NEMU and RTL, as described in the instruction set manual: the `mtval` of an IAF exception is the virtual address of the portion of the memory accesses that caused the fault. In this case, since the bus requires aligned access, IFU splits an instruction fetch into two memory accesses, with the first access at `0x1dfadffe-0x1dfadfff` being in an executable region and causing no exception, while the second access at `0x1dfaf000` being in a non-executable region and causing an IAF exception, thus `mtval` should be the starting address of the second access `0x1dfaf000`, which is inconsistent with NEMU's behavior. Therefore, we forwarded this issue to the NEMU team for analysis.

Simultaneously, we carefully checked the waveforms and noticed that IFU actually read `0x0` when reading `0x1dfadffe-0x1dfadfff`, which is an illegal RVC instruction rather than the expected half of a legal RVI instruction. This may be caused by a cache consistency issue due to the workload enabling PMP at an inappropriate time, since NEMU does not have a cache model, it is expected that difftest reports an error in this case. In fact, the behavior of RTL is: it detects an illegal RVC instruction at `0x1dfadffe`, while NEMU triggers an IAF.

-- But in this case, RTL should report `mtval=0x0, mepc=0x1dfadffe, mcause=0x2 (illegal instruction)`, which is also inconsistent with the actual behavior, indicating that there is another issue.

When we were confused, our internal verification team reported a very similar bug: RVC instructions close to page boundaries were skipped for execution. This was caused by a communication issue: the InstrUncache unit only checks the low bits of the address to determine if it crosses a page boundary, without considering the instruction length. Therefore, when an RVC instruction starts at the last instruction before a page boundary, InstrUncache marks it as `incomplete`. The intention is to reuse the existing pre-decoding unit in IFU, and if IFU's pre-decoding finds that the instruction is actually complete (an RVC instruction), it should ignore InstrUncache's marking and send it to the backend for normal execution. However, due to communication issues, IFU directly treated InstrUncache's `incomplete` flag as an indication of actual instruction incompleteness, leading to the above problem. This issue was fixed in [#5959](https://github.com/OpenXiangShan/XiangShan/pull/5959).

Applying the situation of #5910 to the analysis of the new bug, although RTL detects an illegal RVC instruction at `0x1dfadffe`, it does not correctly send it to the backend, so the processor tries to execute the next instruction at `0x1dfaf000`, finds an IAF exception, and thus gets the observed `mtval` and `mepc` values.

At this point, we thought the bug was completely fixed. Since the provided workload has cache consistency issues and cannot be used, we constructed a test case ourselves to verify the effectiveness of the fix. However, the responsible colleague was not very familiar with the PMP configuration process, so they used the mechanism provided by the Svpbmt extension to control `MMIO`/`X` attributes through page table entries. In theory, except for access fault (physical address without execute permission) becoming page fault (virtual address without execute permission), the processing flow and phenomena should be consistent.

-- However, the actual situation was surprising. When configuring the first page as `Pbmt=IO, X=1` and the second page as `Pbmt=IO, X=0`, RTL correctly reported an exception with `mtval=0x1dfaf000, mepc=0x1dfadffe, mcause=0x1`, passing the difftest check, as if the previous two bugs never existed.

So we checked the waveforms again and found that although we configured `Pbmt=IO`, RTL still treated it as a cacheable space, with IFU's related paths completely inactive and ICache providing the correct response instead. After checking the Pbmt-related paths, we found that the bit width of the `Pbmt.PMA` constant was not explicitly specified, which led to an incorrect bit width of the `s1_itlbPbmt` register inferred by Chisel, causing `Pbmt=IO (2'b10)` to be stored as `1'b0` and thus treated as `Pbmt=PMA (2'b00)`. This bug originated from a refactoring a year ago, when the responsible colleague thought that `RegInit(..., init=Pbmt.PMA)` looked better than `RegInit(..., init=0.U(Pbmt.width.W))`, so they changed it without realizing that it would introduce such a subtle bug. This also exposed the insufficient coverage of our test suite for new features introduced in RVA23 (specifically referring to the Svpbmt extension here). This issue was fixed in [#5962](https://github.com/OpenXiangShan/XiangShan/pull/5962), and we will continue to improve the quality of our test suite in the future.

At this point, we thought the bug was completely fixed ~~again~~, but when we reran the newly constructed test case, it still reported a difftest error:

```plaintext
RTL : mtval=0x1dfaf000, mepc=0x1dfaf000, mcause=0xc (instruction page fault)
NEMU: mtval=0x1dfaf000, mepc=0x1dfadffe, mcause=0xc (instruction page fault)
```

-- ~~Why on earth is the mepc still wrong😡~~

Anyway, we checked the waveforms AGAIN and found that IFU ignores its MMIO marking when handling exceptions (which is expected, since the PMP/ITLB checks done by ICache have already failed, it makes no sense to further distinguish whether it's MMIO or not, just pass it to the backend for handling), so for such instructions with exception on latter half, the data path in IFU will handle it with logic similar to instruction concatenation and metadata selection for instructions crossing MMIO-cacheable boundaries. However, unfortunately, this logic was newly added in V3 and was designed with some issues without much consideration for verification. Therefore, IFU actually discarded the metadata of the previous page and directly processed it according to the metadata of the latter page, thus IFU actually thought it was processing an instruction at `0x1dfaf000` when it encountered the exception, rather than at `0x1dfadffe`, ultimately leading to an incorrect `mepc` calculated by the backend. This issue was fixed in [#5985](https://github.com/OpenXiangShan/XiangShan/pull/5985).

At this point, we thought the bug was completely fixed ~~AGAIN~~, and this time we really passed the test case. We also verified that other combinations of different attributes (for example, both pages are executable but with inconsistent MMIO attributes: first page `Pbmt=PMA, X=1`, second page `Pbmt=IO, X=1`) can also get correct results.

## Recent Developments

### Frontend

- RTL features
  - Read the corresponding FTQ entry of a redirect request in advance, optimizing timing and reducing redirect latency ([#5990](https://github.com/OpenXiangShan/XiangShan/pull/5990))
- Bug fixes
  - Fix the issue introduced by UBTB timing optimization, which treats overwritten entries as hits and causes incorrect predictions ([#6009](https://github.com/OpenXiangShan/XiangShan/pull/6009))
- PPA optimizations
  - Optimize the timing of IBuffer enqueue logic ([#5946](https://github.com/OpenXiangShan/XiangShan/pull/5946))

### Backend

- RTL features
  - Use sparse vector (SparseVec) for the structure of exception vector ([#5738](https://github.com/OpenXiangShan/XiangShan/pull/5738))
  - Sdtrig extension support tdata3 ([#5983](https://github.com/OpenXiangShan/XiangShan/pull/5983))

### MemBlock and Cache

- Bug fixes
  - Fix bug of fullOverlap when store is cross16B ([#6003](https://github.com/OpenXiangShan/XiangShan/pull/6003))
- PPA optimizations
  - Split L2 prefetch request queue by slices, reducing blocking between different slices ([XSCache #13](https://github.com/OpenXiangShan/XSCache/pull/13))
- Code refactoring
  - Move prefetch from loadUnit to mainPipe ([#5997](https://github.com/OpenXiangShan/XiangShan/pull/5997))

### XSAI

- RTL features
  - Add an option to disable data types with scaling factors, such as mxfp8. When these data types are disabled, modules that handle scaling factors will not be instantiated ([CUTE #13](https://github.com/OpenXiangShan/CUTE/pull/13))
  - Add a set of matrix performance events for CUTE ([CUTE #18](https://github.com/OpenXiangShan/CUTE/pull/18))
  - Continue advancing HBL2 support for the CHI bus protocol
- Bug fixes
  - Fix the performance event numbers of XSAI V2R2A and align them with the event numbers of Kunminghu V2R2 ([XSAI #70](https://github.com/OpenXiangShan/XSAI/pull/70))
  - Fix the issue where matrix functional unit exceptions were not handled by ROB ([XSAI #71](https://github.com/OpenXiangShan/XSAI/pull/71))
- Code refactoring
  - Refactor CUTE scheduling ([CUTE #14](https://github.com/OpenXiangShan/CUTE/pull/14))

## Performance Evaluation

Processor and SoC parameters are as follows:

| Parameters           | Options    |
| -------------------- | ---------- |
| Commit               | dcc1d2689  |
| Date                 | 2026/05/21 |
| L1 ICache            | 64KB       |
| L1 DCache            | 64KB       |
| L2 Cache             | 2MB        |
| L3 Cache             | 16MB       |
| LSU                  | 3ld2st     |
| Bus protocol         | CHI        |
| Memory configuration | DDR4-3200  |

The SPEC CPU2006 scores are as follows:

| SPECint 2006 @ 3GHz | GCC15  |  XSCC  | SPECfp 2006 @ 3GHz | GCC15  |  XSCC  |
| :------------------ | :----: | :----: | :----------------- | :----: | :----: |
| 400.perlbench       | 48.42  | 47.53  | 410.bwaves         | 85.27  | 89.88  |
| 401.bzip2           | 27.43  | 28.28  | 416.gamess         | 57.05  | 53.23  |
| 403.gcc             | 55.26  | 38.88  | 433.milc           | 64.93  | 64.04  |
| 429.mcf             | 61.00  | 55.47  | 434.zeusmp         | 71.27  | 64.66  |
| 445.gobmk           | 38.94  | 40.10  | 435.gromacs        | 37.20  | 34.38  |
| 456.hmmer           | 54.38  | 64.72  | 436.cactusADM      | 76.13  | 87.68  |
| 458.sjeng           | 38.87  | 39.48  | 437.leslie3d       | 56.26  | 56.36  |
| 462.libquantum      | 136.67 | 294.84 | 444.namd           | 43.23  | 45.23  |
| 464.h264ref         | 63.46  | 71.99  | 447.dealII         | 64.25  | 68.39  |
| 471.omnetpp         | 41.07  | 39.47  | 450.soplex         | 52.12  | 63.93  |
| 473.astar           | 30.42  | 29.63  | 453.povray         | 73.34  | 65.77  |
| 483.xalancbmk       | 75.83  | 84.61  | 454.Calculix       | 43.74  | 39.61  |
| GEOMEAN             | 50.90  | 54.07  | 459.GemsFDTD       | 63.50  | 63.95  |
|                     |        |        | 465.tonto          | 52.59  | 35.01  |
|                     |        |        | 470.lbm            | 125.82 | 133.04 |
|                     |        |        | 481.wrf            | 54.96  | 41.58  |
|                     |        |        | 482.sphinx3        | 59.39  | 62.42  |
|                     |        |        | GEOMEAN            | 61.07  | 59.18  |

Compilation parameters are as follows:

| Parameters                  | GCC15       | XSCC                |
| --------------------------- | ----------- | ------------------- |
| Compiler                    | gcc15       | xscc                |
| Optimization level          | O3          | O3                  |
| Memory library              | jemalloc    | jemalloc            |
| -march                      | RV64GCB     | RV64GCB             |
| -ffp-contraction            | fast        | fast                |
| Linker optimization         | -flto       | -flto               |
| Floating-point optimization | -ffast-math | -ffast-math         |
| -mcpu                       | -           | xiangshan-kunminghu |

Note: We use SimPoint to sample the programs and create checkpoint images based on our custom checkpoint format, with a SimPoint clustering coverage of 100%. The above scores are estimates based on program segments, not full SPEC CPU2006 evaluations, and may differ from actual chip performance.

## Related links

- XiangShan technical discussion QQ group: 879550595
- XiangShan technical discussion website: <https://github.com/OpenXiangShan/XiangShan/discussions>
- XiangShan Documentation: <https://docs.xiangshan.cc/>
- XiangShan User Guide: <https://docs.xiangshan.cc/projects/user-guide/>
- XiangShan Design Doc: <https://docs.xiangshan.cc/projects/design/>

Editors: Zhihao Xu, Junxiong Ji, Zhuo Chen, Jiru Sun, Yanjun Li
