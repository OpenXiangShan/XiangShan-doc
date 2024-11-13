# Acknowledgments

This list outlines the techniques used in the XiangShan RTL codes.

## Instruction Fetching

[1] Glenn Reinman, Todd Austin, and Brad Calder. "[A scalable front-end architecture for fast instruction delivery.](https://doi.org/10.1109/ISCA.1999.765954){target="_blank"}" 26th International Symposium on Computer Architecture (ISCA). 1999. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/NewFtq.scala){target="_blank"}

[2] Alex Ramirez, Oliverio J. Santana, Josep L. Larriba-Pey, and Mateo Valero. "[Fetching instruction streams.](https://doi.org/10.1109/MICRO.2002.1176264){target="_blank"}" 35th Annual IEEE/ACM International Symposium on Microarchitecture (MICRO). 2002. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend){target="_blank"}

## Instruction Prefetch

[1] Glenn Reinman, Brad Calder, and Todd Austin. "[Fetch directed instruction prefetching.](https://doi.org/10.1109/MICRO.1999.809439){target="_blank"}" 32nd Annual ACM/IEEE International Symposium on Microarchitecture (MICRO). 1999. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/icache){target="_blank"}

[2] Yasuo Ishii, Jaekyu Lee, Krishnendra Nathella, and Dam Sunwoo. "[Rebasing instruction prefetching: An industry perspective.](https://doi.org/10.1109/LCA.2020.3035068){target="_blank"}" IEEE Computer Architecture Letters 19.2: 147-150. 2020. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend){target="_blank"}

[3] Yasuo Ishii, Jaekyu Lee, Krishnendra Nathella, and Dam Sunwoo. "[Re-establishing fetch-directed instruction prefetching: An industry perspective.](https://doi.org/10.1109/ISPASS51385.2021.00034){target="_blank"}" 2021 IEEE International Symposium on Performance Analysis of Systems and Software (ISPASS). 2021. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend){target="_blank"}

## Branch prediction

[1] Kevin Skadron, Pritpal S. Ahuja, Margaret Martonosi, and Douglas W. Clark. "[Improving prediction for procedure returns with return-address-stack repair mechanisms.](https://doi.org/10.1109/MICRO.1998.742787){target="_blank"}" 31st Annual ACM/IEEE International Symposium on Microarchitecture (MICRO). 1998. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/newRAS.scala){target="_blank"}

[2] Pierre Michaud. "[A PPM-like, tag-based branch predictor.](https://inria.hal.science/hal-03406188){target="_blank"}" The Journal of Instruction-Level Parallelism (JILP) 7: 10. 2005. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/Tage.scala){target="_blank"}

[3] André Seznec, and Pierre Michaud. "[A case for (partially) tagged geometric history length branch prediction.](https://inria.hal.science/hal-03408381){target="_blank"}" The Journal of Instruction-Level Parallelism (JILP) 8: 23. 2006. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/Tage.scala){target="_blank"}

[4] André Seznec. "[A 256 kbits l-tage branch predictor.](http://www.irisa.fr/caps/people/seznec/L-TAGE.pdf){target="_blank"}" The Journal of Instruction-Level Parallelism (JILP) Special Issue: The Second Championship Branch Prediction Competition (CBP) 9: 1-6. 2007. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/Tage.scala){target="_blank"}

[5] André Seznec. "[A 64-Kbytes ITTAGE indirect branch predictor.](https://inria.hal.science/hal-00639041){target="_blank"}" The Journal of Instruction-Level Parallelism (JILP) 2nd JILP Workshop on Computer Architecture Competitions (JWAC): Championship Branch Prediction (CBP). 2011. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/ITTAGE.scala){target="_blank"}

[6] André Seznec. "[Tage-sc-l branch predictors.](https://inria.hal.science/hal-01086920){target="_blank"}" The Journal of Instruction-Level Parallelism (JILP) 4th JILP Workshop on Computer Architecture Competitions (JWAC): Championship Branch Prediction (CBP). 2014. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/SC.scala){target="_blank"}

[7] André Seznec. "[Tage-sc-l branch predictors again.](https://inria.hal.science/hal-01354253){target="_blank"}" The Journal of Instruction-Level Parallelism (JILP) 5th JILP Workshop on Computer Architecture Competitions (JWAC): Championship Branch Prediction (CBP). 2016. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/SC.scala){target="_blank"}

[8] Tan Hongze, and Wang Jian. "[A Return Address Predictor Based on Persistent Stack.](https://crad.ict.ac.cn/en/article/doi/10.7544/issn1000-1239.202111274){target="_blank"}" Journal of Computer Research and Development (CRAD) 60.6: 1337-1345. 2023. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/frontend/newRAS.scala){target="_blank"}

## Scheduling

[1] Robert. M. Tomasulo. "[An efficient algorithm for exploiting multiple arithmetic units.](https://doi.org/10.1147/rd.111.0025){target="_blank"}" IBM Journal of Research and Development (IBMJ) 11.1: 25-33. 1967. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/tree/master/src/main/scala/xiangshan/backend){target="_blank"}

[2] James E. Smith, and Andrew R. Pleszkun. "[Implementation of precise interrupts in pipelined processors.](https://dl.acm.org/doi/10.5555/327010.327125){target="_blank"}" 12th Annual International Symposium on Computer Architecture (ISCA). 1985. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/rob/Rob.scala){target="_blank"}

[3] Fernando Latorre, Grigorios Magklis, Jose González, Pedro Chaparro, and Antonio González. "[Crob: implementing a large instruction window through compression.](https://doi.org/10.1007/978-3-642-19448-1_7){target="_blank"}" Transactions on High-Performance Embedded Architectures and Compilers III: 115-134. Berlin, Heidelberg: Springer Berlin Heidelberg. 2011. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/rename/CompressUnit.scala){target="_blank"}

## Execution

[1] Andrew D. Booth. "[A signed binary multiplication technique.](https://doi.org/10.1093/qjmam/4.2.236){target="_blank"}" The Quarterly Journal of Mechanics and Applied Mathematics 4.2: 236-240. 1951. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/Multiplier.scala){target="_blank"}

[2] Christopher. S. Wallace. "[A suggestion for a fast multiplier.](https://doi.org/10.1109/PGEC.1964.263830){target="_blank"}" IEEE Transactions on Electronic Computers 1: 14-17. 1964. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/Multiplier.scala){target="_blank"}

[3] Elisardo Antelo, Tomas Lang, Paolo Montuschi, and Alberto Nannarelli. "[Digit-recurrence dividers with reduced logical depth.](https://doi.org/10.1109/TC.2005.115){target="_blank"}" IEEE Transactions on Computers 54.7: 837-851. 2005. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/backend/fu/SRT16Divider.scala){target="_blank"}

## MDP

[1] George Z. Chrysos, and Joel S. Emer. "[Memory dependence prediction using store sets.](https://doi.org/10.1109/ISCA.1998.694770){target="_blank"}" 25th Annual International Symposium on Computer Architecture (ISCA). 1998. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/mdp/StoreSet.scala){target="_blank"}

[2] Richard Kessler. "[The alpha 21264 microprocessor.](https://doi.org/10.1109/40.755465){target="_blank"}" IEEE Micro 19.2: 24-36. 1999. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/mdp/WaitTable.scala){target="_blank"}

## TLB

[1] Binh Pham, Viswanathan Vaidyanathan, Aamer Jaleel, and Abhishek Bhattacharjee. "[Colt: Coalesced large-reach tlbs.](https://doi.org/10.1109/MICRO.2012.32){target="_blank"}" 45th Annual IEEE/ACM International Symposium on Microarchitecture (MICRO). 2012. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/cache/mmu/TLB.scala){target="_blank"}

## Non-blocking Cache

[1] David Kroft. "[Lockup-free instruction fetch/prefetch cache organization.](https://dl.acm.org/doi/10.5555/800052.801868){target="_blank"}" 8th Annual Symposium on Computer Architecture (ISCA). 1981. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/cache/dcache/mainpipe/MissQueue.scala){target="_blank"}

## Multi Port Data Cache

[1] Gurindar S. Sohi, and Manoj Franklin. "[High-bandwidth data memory systems for superscalar processors.](https://doi.org/10.1145/106972.106980){target="_blank"}" 4th International Conference on Architectural Support for Programming Languages and Operating Systems (ASPLOS). 1991. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/cache/dcache/data/BankedDataArray.scala){target="_blank"}

## Data Replacement

[1] Aamer Jaleel, Kevin B. Theobald, Simon C. Steely, and Joel Emer. "[High performance cache replacement using re-reference interval prediction (RRIP).](https://doi.org/10.1145/1815961.1815971){target="_blank"}" 37th Annual International Symposium on Computer Architecture (ISCA). 2010. [[RTL Codes]](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/utils/Replacer.scala){target="_blank"}

## Data Prefetch

[1] Jean-Loup Baer, and Tien-Fu Chen. "[An effective on-chip preloading scheme to reduce data access penalty.](https://doi.org/10.1145/125826.125932){target="_blank"}" ACM/IEEE Conference on Supercomputing. 1991. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/L1StridePrefetcher.scala){target="_blank"}

[2] Stephen Somogyi, Thomas F. Wenisch, Anastassia Ailamaki, Babak Falsafi and Andreas Moshovos. "[Spatial memory streaming.](https://doi.org/10.1109/ISCA.2006.38){target="_blank"}" 33rd International Symposium on Computer Architecture (ISCA). 2006. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/SMSPrefetcher.scala){target="_blank"}

[3] Santhosh Srinath, Onur Mutlu, Hyesoon Kim, and Yale N. Patt "[Feedback directed prefetching: Improving the performance and bandwidth-efficiency of hardware prefetchers.](https://doi.org/10.1109/HPCA.2007.346185){target="_blank"}" IEEE 13th International Symposium on High Performance Computer Architecture (HPCA). 2007. [[RTL Codes]](https://github.com/OpenXiangShan/XiangShan/blob/master/src/main/scala/xiangshan/mem/prefetch/FDP.scala){target="_blank"}

[4] Pierre Michaud. "[A Best-Offset Prefetcher.](https://inria.hal.science/hal-01165600/){target="_blank"}" 2nd Data Prefetching Championship (DPC). 2015. [[RTL Codes]](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/BestOffsetPrefetch.scala){target="_blank"}

[5] Pierre Michaud. "[Best-Offset Hardware Prefetching.](https://doi.org/10.1109/HPCA.2016.7446087){target="_blank"}" IEEE International Symposium on High Performance Computer Architecture (HPCA). 2016. [[RTL Codes]](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/BestOffsetPrefetch.scala){target="_blank"}

[6] Hao Wu, Krishnendra Nathella, Joseph Pusdesris, Dam Sunwoo, Akanksha Jain, and Calvin Lin. "[Temporal Prefetching Without the Off-Chip Metadata.](https://doi.org/10.1145/3352460.3358300){target="_blank"}" 52nd Annual IEEE/ACM International Symposium on Microarchitecture (MICRO). 2019. [[RTL Codes]](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/TemporalPrefetch.scala){target="_blank"}

[7] Sam Ainsworth, and Lev Mukhanov. "[Triangel: A High-Performance, Accurate, Timely On-Chip Temporal Prefetcher.](https://doi.org/10.1109/ISCA59077.2024.00090){target="_blank"}" ACM/IEEE 51st Annual International Symposium on Computer Architecture (ISCA). 2024. [[RTL Codes]](https://github.com/OpenXiangShan/CoupledL2/blob/master/src/main/scala/coupledL2/prefetch/TemporalPrefetch.scala){target="_blank"}
