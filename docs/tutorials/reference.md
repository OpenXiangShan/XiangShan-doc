# Reference

## Instruction Fetching

[1] Glenn Reinman, Todd Austin, and Brad Calder. "[A scalable front-end architecture for fast instruction delivery.](https://doi.org/10.1145/307338.300999){target="_blank"}" ACM SIGARCH Computer Architecture News 27.2 (1999): 234-245. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/NewFtq.scala){target="_blank"}

[2] Alex Ramirez, Oliverio J. Santana, Josep L. Larriba-Pey and Mateo Valero. "[Fetching instruction streams.](https://doi.org/10.1109/MICRO.2002.1176264){target="_blank"}" 35th Annual IEEE/ACM International Symposium on Microarchitecture, 2002.(MICRO-35). Proceedings. IEEE, 2002. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend){target="_blank"}

## Instruction Prefetch

[1] Glenn Reinman, Brad Calder, and Todd Austin. "[Fetch directed instruction prefetching.](https://doi.org/10.1109/MICRO.1999.809439){target="_blank"}" MICRO-32. Proceedings of the 32nd Annual ACM/IEEE International Symposium on Microarchitecture. IEEE, 1999. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/icache){target="_blank"}

[2] Yasuo Ishii, Jaekyu Lee, Krishnendra Nathella and Dam Sunwoo. "[Rebasing instruction prefetching: An industry perspective.](https://doi.org/10.1109/LCA.2020.3035068){target="_blank"}" IEEE Computer Architecture Letters 19.2 (2020): 147-150. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend){target="_blank"}

[3] Yasuo Ishii, Jaekyu Lee, Krishnendra Nathella and Dam Sunwoo. "[Re-establishing fetch-directed instruction prefetching: An industry perspective.](https://doi.org/10.1109/ISPASS51385.2021.00034){target="_blank"}" 2021 IEEE International Symposium on Performance Analysis of Systems and Software (ISPASS). IEEE, 2021. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend){target="_blank"}

## Branch prediction

[1] Kevin Skadron, P. S. Ahuja, Margaret Martonosi and D. W. Clark. "[Improving prediction for procedure returns with return-address-stack repair mechanisms.](https://doi.org/10.1109/MICRO.1998.742787){target="_blank"}" Proceedings. 31st Annual ACM/IEEE International Symposium on Microarchitecture. IEEE, 1998. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/newRAS.scala){target="_blank"}

[2] Pierre Michaud. "[A PPM-like, tag-based branch predictor.](https://inria.hal.science/hal-03406188){target="_blank"}" The Journal of Instruction-Level Parallelism 7 (2005): 10. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/Tage.scala){target="_blank"}

[3] André Seznec and Pierre Michaud. "[A case for (partially) tagged geometric history length branch prediction.](https://inria.hal.science/hal-03408381){target="_blank"}" The Journal of Instruction-Level Parallelism 8 (2006): 23. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/Tage.scala){target="_blank"}

[4] André Seznec. "[A 256 kbits l-tage branch predictor.](http://www.irisa.fr/caps/people/seznec/L-TAGE.pdf){target="_blank"}" Journal of Instruction-Level Parallelism (JILP) Special Issue: The Second Championship Branch Prediction Competition (CBP-2) 9 (2007): 1-6. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/Tage.scala){target="_blank"}

[5] André Seznec. "[A 64-Kbytes ITTAGE indirect branch predictor.](https://inria.hal.science/hal-00639041){target="_blank"}" JWAC-2: Championship Branch Prediction. 2011. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/ITTAGE.scala){target="_blank"}

[6] André Seznec. "[Tage-sc-l branch predictors.](https://inria.hal.science/hal-01086920){target="_blank"}" JILP-Championship Branch Prediction. 2014. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/SC.scala){target="_blank"}

[7] André Seznec. "[Tage-sc-l branch predictors again.](https://inria.hal.science/hal-01354253){target="_blank"}" 5th JILP Workshop on Computer Architecture Competitions (JWAC-5): Championship Branch Prediction (CBP-5). 2016. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/SC.scala){target="_blank"}

[8] Tan Hongze and Wang Jian. "[A Return Address Predictor Based on Persistent Stack.](https://crad.ict.ac.cn/en/article/doi/10.7544/issn1000-1239.202111274){target="_blank"}" Journal of Computer Research and Development 60.6 (2023): 1337-1345. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/newRAS.scala){target="_blank"}

## Scheduling

[1] Tomasulo, Robert M. "[An efficient algorithm for exploiting multiple arithmetic units.](https://github.com/OpenXiangShan/XiangShan/tree/master/src/main/scala/xiangshan/backend){target="_blank"}" IBM Journal of research and Development 11.1 (1967): 25-33. [[RTL Codes]](){target="_blank"}

[2] Smith, James E., and Andrew R. Pleszkun. "[Implementation of precise interrupts in pipelined processors.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/rob/Rob.scala){target="_blank"}" ACM SIGARCH Computer Architecture News 13.3 (1985): 36-44. [[RTL Codes]](){target="_blank"}

[3] Latorre, Fernando, et al. "[Crob: implementing a large instruction window through compression.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/rename/CompressUnit.scala){target="_blank"}" Transactions on high-performance embedded architectures and compilers III. Berlin, Heidelberg: Springer Berlin Heidelberg, 2011. 115-134. [[RTL Codes]](){target="_blank"}

## Execution

[1] Booth, Andrew D. "[A signed binary multiplication technique.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/Multiplier.scala){target="_blank"}" The Quarterly Journal of Mechanics and Applied Mathematics 4.2 (1951): 236-240. [[RTL Codes]](){target="_blank"}

[2] Wallace, Christopher S. "[A suggestion for a fast multiplier.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/Multiplier.scala){target="_blank"}" IEEE Transactions on electronic Computers 1 (1964): 14-17. [[RTL Codes]](){target="_blank"}

[3] Antelo, Elisardo, et al. "[Digit-recurrence dividers with reduced logical depth.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/SRT16Divider.scala){target="_blank"}" IEEE Transactions on Computers 54.7 (2005): 837-851. [[RTL Codes]](){target="_blank"}

## MDP

[1] Chrysos, George Z., and Joel S. Emer. "[Memory dependence prediction using store sets.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/mdp/StoreSet.scala){target="_blank"}" ACM SIGARCH Computer Architecture News 26.3 (1998): 142-153. [[RTL Codes]](){target="_blank"}

[2] Kessler, Richard E. "[The alpha 21264 microprocessor.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/mdp/WaitTable.scala){target="_blank"}" IEEE micro 19.2 (1999): 24-36. [[RTL Codes]](){target="_blank"}

## TLB

[1] Pham, Binh, et al. "Colt: Coalesced large-reach tlbs." 2012 45th Annual IEEE/ACM International Symposium on Microarchitecture. IEEE, 2012. [[RTL Codes]](){target="_blank"}

## Non-blocking Cache

[1] Kroft, David. "[Lockup-free instruction fetch/prefetch cache organization.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/cache/dcache/mainpipe/MissQueue.scala){target="_blank"}" 25 years of the international symposia on Computer architecture (selected papers). 1998. [[RTL Codes]](){target="_blank"}

## Multi Port Data Cache

[1] Sohi, Gurindar S., and Manoj Franklin. "[High-bandwidth data memory systems for superscalar processors.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/cache/dcache/data/BankedDataArray.scala){target="_blank"}" Proceedings of the fourth international conference on Architectural support for programming languages and operating systems. 1991. [[RTL Codes]](){target="_blank"}

## Cache Directory Structure

[1] Zhao, Li, et al. "[NCID: a non-inclusive cache, inclusive directory architecture for flexible and efficient cache hierarchies.](https://github.com/OpenXiangShan/CoupledL2/tree/master/src/main/scala/coupledL2){target="_blank"}" Proceedings of the 7th ACM international conference on Computing frontiers. 2010. [[RTL Codes]](){target="_blank"}

## Data Replacement

[1] Jaleel, Aamer, et al. "[High performance cache replacement using re-reference interval prediction (RRIP).](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/utils/Replacer.scala){target="_blank"}" ACM SIGARCH computer architecture news 38.3 (2010): 60-71. [[RTL Codes]](){target="_blank"}

## Data Prefetch

[1] Baer, Jean-Loup, and Tien-Fu Chen. "[An effective on-chip preloading scheme to reduce data access penalty.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/L1StridePrefetcher.scala){target="_blank"}" Proceedings of the 1991 ACM/IEEE conference on Supercomputing. 1991. [[RTL Codes]](){target="_blank"}

[2] Somogyi, Stephen, et al. "[Spatial memory streaming.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/SMSPrefetcher.scala){target="_blank"}" ACM SIGARCH Computer Architecture News 34.2 (2006): 252-263. [[RTL Codes]](){target="_blank"}

[3] Srinath, Santhosh, et al. "[Feedback directed prefetching: Improving the performance and bandwidth-efficiency of hardware prefetchers.](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/FDP.scala){target="_blank"}" 2007 IEEE 13th International Symposium on High Performance Computer Architecture. [[RTL Codes]](){target="_blank"}IEEE, 2007.

[4] Michaud, Pierre. "[A Best-Offset Prefetcher.](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/BestOffsetPrefetch.scala){target="_blank"}" 2nd Data Prefetching Championship, Jun 2015, Portland, United States. hal-01165600 [[RTL Codes]](){target="_blank"}

[5] Michaud, Pierre. "[Best-Offset Hardware Prefetching.](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/BestOffsetPrefetch.scala){target="_blank"}" 2016 IEEE International Symposium on High Performance Computer Architecture (HPCA), 2016, pp. 469–80, https://doi.org/10.1109/HPCA.2016.7446087. [[RTL Codes]](){target="_blank"}

[6] Wu, Hao, et al. "[Temporal prefetching without the off-chip metadata.](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/TemporalPrefetch.scala){target="_blank"}" Proceedings of the 52nd Annual IEEE/ACM International Symposium on Microarchitecture. 2019. [[RTL Codes]](){target="_blank"}

[7] Ainsworth, Sam, and Lev Mukhanov. "[Triangel: A High-Performance, Accurate, Timely On-Chip Temporal Prefetcher.](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/TemporalPrefetch.scala){target="_blank"}" arXiv preprint arXiv:2406.10627 (2024). [[RTL Codes]](){target="_blank"}
