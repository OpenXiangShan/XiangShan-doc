# Reference

## Instruction Fetching

- Reinman, Glenn, Todd Austin, and Brad Calder. "A scalable front-end architecture for fast instruction delivery." ACM SIGARCH Computer Architecture News 27.2 (1999): 234-245.
- Ramirez, Alex, et al. "Fetching instruction streams." 35th Annual IEEE/ACM International Symposium on Microarchitecture, 2002.(MICRO-35). Proceedings.. IEEE, 2002.

## Instruction Prefetch

- Reinman, Glenn, Brad Calder, and Todd Austin. "Fetch directed instruction prefetching." MICRO-32. Proceedings of the 32nd Annual ACM/IEEE International Symposium on Microarchitecture. IEEE, 1999.
- Ishii, Yasuo, et al. "Re-establishing fetch-directed instruction prefetching: An industry perspective." 2021 IEEE International Symposium on Performance Analysis of Systems and Software (ISPASS). IEEE, 2021.
- Ishii, Yasuo, et al. "Rebasing instruction prefetching: An industry perspective." IEEE Computer Architecture Letters 19.2 (2020): 147-150.

## Branch prediction

- Michaud, Pierre. "A PPM-like, tag-based branch predictor." The Journal of Instruction-Level Parallelism 7 (2005): 10.
- Seznec, André, and Pierre Michaud. "A case for (partially) tagged geometric history length branch prediction." The Journal of Instruction-Level Parallelism 8 (2006): 23.
- Seznec, André. "A 64-Kbytes ITTAGE indirect branch predictor." JWAC-2: Championship Branch Prediction. 2011.
- Seznec, André. "A 256 kbits l-tage branch predictor." Journal of Instruction-Level Parallelism (JILP) Special Issue: The Second Championship Branch Prediction Competition (CBP-2) 9 (2007): 1-6.
- Seznec, André. "Tage-sc-l branch predictors." JILP-Championship Branch Prediction. 2014.
- Seznec, André. "Tage-sc-l branch predictors again." 5th JILP Workshop on Computer Architecture Competitions (JWAC-5): Championship Branch Prediction (CBP-5). 2016.
- Skadron, Kevin, et al. "Improving prediction for procedure returns with return-address-stack repair mechanisms." Proceedings. 31st Annual ACM/IEEE International Symposium on Microarchitecture. IEEE, 1998.

## Scheduling

- Tomasulo, Robert M. "[An efficient algorithm for exploiting multiple arithmetic units.](https://github.com/OpenXiangShan/XiangShan/tree/master/src/main/scala/xiangshan/backend)" IBM Journal of research and Development 11.1 (1967): 25-33.
- Smith, James E., and Andrew R. Pleszkun. "[Implementation of precise interrupts in pipelined processors.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/rob/Rob.scala)" ACM SIGARCH Computer Architecture News 13.3 (1985): 36-44.
- Latorre, Fernando, et al. "[Crob: implementing a large instruction window through compression.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/rename/CompressUnit.scala)" Transactions on high-performance embedded architectures and compilers III. Berlin, Heidelberg: Springer Berlin Heidelberg, 2011. 115-134.

## Execution

- Wallace, Christopher S. "[A suggestion for a fast multiplier.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/Multiplier.scala)" IEEE Transactions on electronic Computers 1 (1964): 14-17.
- Booth, Andrew D. "[A signed binary multiplication technique.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/Multiplier.scala)" The Quarterly Journal of Mechanics and Applied Mathematics 4.2 (1951): 236-240.
- Antelo, Elisardo, et al. "[Digit-recurrence dividers with reduced logical depth.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/SRT16Divider.scala)" IEEE Transactions on Computers 54.7 (2005): 837-851.

## MDP

- Kessler, Richard E. "[The alpha 21264 microprocessor.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/mdp/WaitTable.scala)" IEEE micro 19.2 (1999): 24-36.
- Chrysos, George Z., and Joel S. Emer. "[Memory dependence prediction using store sets.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/mdp/StoreSet.scala)" ACM SIGARCH Computer Architecture News 26.3 (1998): 142-153.

## TLB

- Pham, Binh, et al. "Colt: Coalesced large-reach tlbs." 2012 45th Annual IEEE/ACM International Symposium on Microarchitecture. IEEE, 2012.

## Non-blocking Cache

- Kroft, David. "Lockup-free instruction fetch/prefetch cache organization." 25 years of the international symposia on Computer architecture (selected papers). 1998.

## Multi Port Data Cache

- Sohi, Gurindar S., and Manoj Franklin. "High-bandwidth data memory systems for superscalar processors." Proceedings of the fourth international conference on Architectural support for programming languages and operating systems. 1991.

## Cache Directory Structure

- Zhao, Li, et al. "[NCID: a non-inclusive cache, inclusive directory architecture for flexible and efficient cache hierarchies.](https://github.com/OpenXiangShan/CoupledL2/tree/master/src/main/scala/coupledL2)" Proceedings of the 7th ACM international conference on Computing frontiers. 2010.

## Data Replacement

- Jaleel, Aamer, et al. "[High performance cache replacement using re-reference interval prediction (RRIP).](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/utils/Replacer.scala)" ACM SIGARCH computer architecture news 38.3 (2010): 60-71.

## Data Prefetch

- Michaud, Pierre. "[A Best-Offset Prefetcher.](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/BestOffsetPrefetch.scala)" 2nd Data Prefetching Championship, Jun 2015, Portland, United States. hal-01165600
- Michaud, Pierre. "[Best-Offset Hardware Prefetching.](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/BestOffsetPrefetch.scala)" 2016 IEEE International Symposium on High Performance Computer Architecture (HPCA), 2016, pp. 469–80, https://doi.org/10.1109/HPCA.2016.7446087.
- Baer, Jean-Loup, and Tien-Fu Chen. "[An effective on-chip preloading scheme to reduce data access penalty.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/L1StridePrefetcher.scala)" Proceedings of the 1991 ACM/IEEE conference on Supercomputing. 1991.
- Srinath, Santhosh, et al. "[Feedback directed prefetching: Improving the performance and bandwidth-efficiency of hardware prefetchers.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/FDP.scala)" 2007 IEEE 13th International Symposium on High Performance Computer Architecture. IEEE, 2007.
- Somogyi, Stephen, et al. "[Spatial memory streaming.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/SMSPrefetcher.scala)" ACM SIGARCH Computer Architecture News 34.2 (2006): 252-263.
- Wu, Hao, et al. "[Temporal prefetching without the off-chip metadata.](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/TemporalPrefetch.scala)" Proceedings of the 52nd Annual IEEE/ACM International Symposium on Microarchitecture. 2019.
- Ainsworth, Sam, and Lev Mukhanov. "[Triangel: A High-Performance, Accurate, Timely On-Chip Temporal Prefetcher.](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/TemporalPrefetch.scala)" arXiv preprint arXiv:2406.10627 (2024).
