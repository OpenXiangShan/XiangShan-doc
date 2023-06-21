#ifndef __EVENTS_H__
#define __EVENTS_H__

#include <stdio.h>
#include <sys/syscall.h>
#include <stdint.h>

// due to the probable performance event change
// it is recommeded to parse_encoding again
// to update this event_encoding
#define noEvent 0

#define Frontend_frontendFlush 1
#define Frontend_ifu_req 2
#define Frontend_ifu_miss 3
#define Frontend_ifu_req_cacheline_0 4
#define Frontend_ifu_req_cacheline_1 5
#define Frontend_ifu_req_cacheline_0_hit 6
#define Frontend_ifu_req_cacheline_1_hit 7
#define Frontend_only_0_hit 8
#define Frontend_only_0_miss 9
#define Frontend_hit_0_hit_1 10
#define Frontend_hit_0_miss_1 11
#define Frontend_miss_0_hit_1 12
#define Frontend_miss_0_miss_1 13
#define Frontend_IBuffer_Flushed 14
#define Frontend_IBuffer_hungry 15
#define Frontend_IBuffer_1_4_valid 16
#define Frontend_IBuffer_2_4_valid 17
#define Frontend_IBuffer_3_4_valid 18
#define Frontend_IBuffer_4_4_valid 19
#define Frontend_IBuffer_full 20
#define Frontend_Front_Bubble 21
#define Frontend_icache_miss_cnt 22
#define Frontend_icache_miss_penalty 23
#define Frontend_bpu_s2_redirect 24
#define Frontend_bpu_s3_redirect 25
#define Frontend_bpu_to_ftq_stall 26
#define Frontend_mispredictRedirect 27
#define Frontend_replayRedirect 28
#define Frontend_predecodeRedirect 29
#define Frontend_to_ifu_bubble 30
#define Frontend_from_bpu_real_bubble 31
#define Frontend_BpInstr 32
#define Frontend_BpBInstr 33
#define Frontend_BpRight 34
#define Frontend_BpWrong 35
#define Frontend_BpBRight 36
#define Frontend_BpBWrong 37
#define Frontend_BpJRight 38
#define Frontend_BpJWrong 39
#define Frontend_BpIRight 40
#define Frontend_BpIWrong 41
#define Frontend_BpCRight 42
#define Frontend_BpCWrong 43
#define Frontend_BpRRight 44
#define Frontend_BpRWrong 45
#define Frontend_ftb_false_hit 46
#define Frontend_ftb_hit 47
#define Frontend_fauftb_commit_hit 48
#define Frontend_fauftb_commit_miss 49
#define Frontend_tage_tht_hit 50
#define Frontend_sc_update_on_mispred 51
#define Frontend_sc_update_on_unconf 52
#define Frontend_ftb_commit_hits 53
#define Frontend_ftb_commit_misses 54

#define Huancun_Bank0_req_buffer_merge 0
#define Huancun_Bank0_req_buffer_flow 1
#define Huancun_Bank0_req_buffer_alloc 2
#define Huancun_Bank0_req_buffer_full 3
#define Huancun_Bank0_recv_prefetch 4
#define Huancun_Bank0_recv_normal 5
#define Huancun_Bank0_nrWorkingABCmshr 6
#define Huancun_Bank0_nrWorkingBmshr 7
#define Huancun_Bank0_nrWorkingCmshr 8
#define Huancun_Bank0_conflictA 9
#define Huancun_Bank0_conflictByPrefetch 10
#define Huancun_Bank0_conflictB 11
#define Huancun_Bank0_conflictC 12
#define Huancun_Bank0_client_dir_conflict 13
#define Huancun_Bank0_selfdir_A_req 14
#define Huancun_Bank0_selfdir_A_hit 15
#define Huancun_Bank0_selfdir_B_req 16
#define Huancun_Bank0_selfdir_B_hit 17
#define Huancun_Bank0_selfdir_C_req 18
#define Huancun_Bank0_selfdir_C_hit 19
#define Huancun_Bank0_selfdir_dirty 20
#define Huancun_Bank0_selfdir_TIP 21
#define Huancun_Bank0_selfdir_BRANCH 22
#define Huancun_Bank0_selfdir_TRUNK 23
#define Huancun_Bank0_selfdir_INVALID 24
#define Huancun_Bank1_req_buffer_merge 25
#define Huancun_Bank1_req_buffer_flow 26
#define Huancun_Bank1_req_buffer_alloc 27
#define Huancun_Bank1_req_buffer_full 28
#define Huancun_Bank1_recv_prefetch 29
#define Huancun_Bank1_recv_normal 30
#define Huancun_Bank1_nrWorkingABCmshr 31
#define Huancun_Bank1_nrWorkingBmshr 32
#define Huancun_Bank1_nrWorkingCmshr 33
#define Huancun_Bank1_conflictA 34
#define Huancun_Bank1_conflictByPrefetch 35
#define Huancun_Bank1_conflictB 36
#define Huancun_Bank1_conflictC 37
#define Huancun_Bank1_client_dir_conflict 38
#define Huancun_Bank1_selfdir_A_req 39
#define Huancun_Bank1_selfdir_A_hit 40
#define Huancun_Bank1_selfdir_B_req 41
#define Huancun_Bank1_selfdir_B_hit 42
#define Huancun_Bank1_selfdir_C_req 43
#define Huancun_Bank1_selfdir_C_hit 44
#define Huancun_Bank1_selfdir_dirty 45
#define Huancun_Bank1_selfdir_TIP 46
#define Huancun_Bank1_selfdir_BRANCH 47
#define Huancun_Bank1_selfdir_TRUNK 48
#define Huancun_Bank1_selfdir_INVALID 49
#define Huancun_Bank2_req_buffer_merge 50
#define Huancun_Bank2_req_buffer_flow 51
#define Huancun_Bank2_req_buffer_alloc 52
#define Huancun_Bank2_req_buffer_full 53
#define Huancun_Bank2_recv_prefetch 54
#define Huancun_Bank2_recv_normal 55
#define Huancun_Bank2_nrWorkingABCmshr 56
#define Huancun_Bank2_nrWorkingBmshr 57
#define Huancun_Bank2_nrWorkingCmshr 58
#define Huancun_Bank2_conflictA 59
#define Huancun_Bank2_conflictByPrefetch 60
#define Huancun_Bank2_conflictB 61
#define Huancun_Bank2_conflictC 62
#define Huancun_Bank2_client_dir_conflict 63
#define Huancun_Bank2_selfdir_A_req 64
#define Huancun_Bank2_selfdir_A_hit 65
#define Huancun_Bank2_selfdir_B_req 66
#define Huancun_Bank2_selfdir_B_hit 67
#define Huancun_Bank2_selfdir_C_req 68
#define Huancun_Bank2_selfdir_C_hit 69
#define Huancun_Bank2_selfdir_dirty 70
#define Huancun_Bank2_selfdir_TIP 71
#define Huancun_Bank2_selfdir_BRANCH 72
#define Huancun_Bank2_selfdir_TRUNK 73
#define Huancun_Bank2_selfdir_INVALID 74
#define Huancun_Bank3_req_buffer_merge 75
#define Huancun_Bank3_req_buffer_flow 76
#define Huancun_Bank3_req_buffer_alloc 77
#define Huancun_Bank3_req_buffer_full 78
#define Huancun_Bank3_recv_prefetch 79
#define Huancun_Bank3_recv_normal 80
#define Huancun_Bank3_nrWorkingABCmshr 81
#define Huancun_Bank3_nrWorkingBmshr 82
#define Huancun_Bank3_nrWorkingCmshr 83
#define Huancun_Bank3_conflictA 84
#define Huancun_Bank3_conflictByPrefetch 85
#define Huancun_Bank3_conflictB 86
#define Huancun_Bank3_conflictC 87
#define Huancun_Bank3_client_dir_conflict 88
#define Huancun_Bank3_selfdir_A_req 89
#define Huancun_Bank3_selfdir_A_hit 90
#define Huancun_Bank3_selfdir_B_req 91
#define Huancun_Bank3_selfdir_B_hit 92
#define Huancun_Bank3_selfdir_C_req 93
#define Huancun_Bank3_selfdir_C_hit 94
#define Huancun_Bank3_selfdir_dirty 95
#define Huancun_Bank3_selfdir_TIP 96
#define Huancun_Bank3_selfdir_BRANCH 97
#define Huancun_Bank3_selfdir_TRUNK 98
#define Huancun_Bank3_selfdir_INVALID 99

#define MemBlock_lu0_load_s0_in_fire 1
#define MemBlock_lu0_load_to_load_forward 2
#define MemBlock_lu0_stall_dcache 3
#define MemBlock_lu0_load_s1_in_fire 4
#define MemBlock_lu0_load_s1_tlb_miss 5
#define MemBlock_lu0_load_s2_in_fire 6
#define MemBlock_lu0_load_s2_dcache_miss 7
#define MemBlock_lu0_load_s2_replay 8
#define MemBlock_lu0_load_s2_replay_tlb_miss 9
#define MemBlock_lu0_load_s2_replay_cache 10
#define MemBlock_lu1_load_s0_in_fire 11
#define MemBlock_lu1_load_to_load_forward 12
#define MemBlock_lu1_stall_dcache 13
#define MemBlock_lu1_load_s1_in_fire 14
#define MemBlock_lu1_load_s1_tlb_miss 15
#define MemBlock_lu1_load_s2_in_fire 16
#define MemBlock_lu1_load_s2_dcache_miss 17
#define MemBlock_lu1_load_s2_replay 18
#define MemBlock_lu1_load_s2_replay_tlb_miss 19
#define MemBlock_lu1_load_s2_replay_cache 20
#define MemBlock_lu1_sbuffer_req_valid 21
#define MemBlock_sbuffer_req_fire 22
#define MemBlock_sbuffer_merge 23
#define MemBlock_sbuffer_newline 24
#define MemBlock_dcache_req_valid 25
#define MemBlock_dcache_req_fire 26
#define MemBlock_sbuffer_idle 27
#define MemBlock_sbuffer_flush 28
#define MemBlock_sbuffer_replace 29
#define MemBlock_mpipe_resp_valid 30
#define MemBlock_refill_resp_valid 31
#define MemBlock_replay_resp_valid 32
#define MemBlock_coh_timeout 33
#define MemBlock_sbuffer_1_4_valid 34
#define MemBlock_sbuffer_2_4_valid 35
#define MemBlock_sbuffer_3_4_valid 36
#define MemBlock_sbuffer_full_valid 37
#define MemBlock_lq_rollback 38
#define MemBlock_lq_mmioCycle 39
#define MemBlock_lq_mmio_Cnt 40
#define MemBlock_lq_refill 41
#define MemBlock_lq_writeback_success 42
#define MemBlock_lq_writeback_blocked 43
#define MemBlock_ltq_1_4_valid 44
#define MemBlock_ltq_2_4_valid 45
#define MemBlock_ltq_3_4_valid 46
#define MemBlock_ltq_4_4_valid 47
#define MemBlock_sq_mmioCycle 48
#define MemBlock_sq_mmioCnt 49
#define MemBlock_sq_mmio_wb_success 50
#define MemBlock_sq_mmio_wb_blocked 51
#define MemBlock_stq_1_4_valid 52
#define MemBlock_stq_2_4_valid 53
#define MemBlock_stq_3_4_valid 54
#define MemBlock_stq_4_4_valid 55
#define MemBlock_dcache_wbq_req 56
#define MemBlock_dcache_wbq_1_4_valid 57
#define MemBlock_dcache_wbq_2_4_valid 58
#define MemBlock_dcache_wbq_3_4_valid 59
#define MemBlock_dcache_wbq_4_4_valid 60
#define MemBlock_dcache_mp_req 61
#define MemBlock_dcache_mp_total_penalty 62
#define MemBlock_dcache_missq_req 63
#define MemBlock_dcache_missq_1_4_valid 64
#define MemBlock_dcache_missq_2_4_valid 65
#define MemBlock_dcache_missq_3_4_valid 66
#define MemBlock_dcache_missq_4_4_valid 67
#define MemBlock_dcache_probq_req 68
#define MemBlock_dcache_probq_1_4_valid 69
#define MemBlock_dcache_probq_2_4_valid 70
#define MemBlock_dcache_probq_3_4_valid 71
#define MemBlock_dcache_probq_4_4_valid 72
#define MemBlock_loadpipe0_load_req 73
#define MemBlock_loadpipe0_load_replay 74
#define MemBlock_loadpipe0_load_replay_for_data_nack 75
#define MemBlock_loadpipe0_load_replay_for_no_mshr 76
#define MemBlock_loadpipe0_load_replay_for_conflict 77
#define MemBlock_loadpipe1_load_req 78
#define MemBlock_loadpipe1_load_replay 79
#define MemBlock_loadpipe1_load_replay_for_data_nack 80
#define MemBlock_loadpipe1_load_replay_for_no_mshr 81
#define MemBlock_loadpipe1_load_replay_for_conflict 82
#define PTW_tlbllptw_incount 83
#define PTW_tlbllptw_inblock 84
#define PTW_tlbllptw_memcount 85
#define PTW_tlbllptw_memcycle 86
#define PTW_access 87
#define PTW_l1_hit 88
#define PTW_l2_hit 89
#define PTW_l3_hit 90
#define PTW_sp_hit 91
#define PTW_pte_hit 92
#define PTW_rwHarzad 93
#define PTW_out_blocked 94
#define PTW_fsm_count 95
#define PTW_fsm_busy 96
#define PTW_fsm_idle 97
#define PTW_resp_blocked 98
#define PTW_mem_count 99
#define PTW_mem_cycle 100
#define PTW_mem_blocked 101
#define MemBlock_ldDeqCount 102
#define MemBlock_stDeqCount 103

#define CtrlBlock_noEvent 0
#define CtrlBlock_decoder_fused_instr 1
#define CtrlBlock_decoder_waitInstr 2
#define CtrlBlock_decoder_stall_cycle 3
#define CtrlBlock_decoder_utilization 4
#define CtrlBlock_rename_in 5
#define CtrlBlock_rename_waitinstr 6
#define CtrlBlock_rename_stall_cycle_dispatch 7
#define CtrlBlock_rename_stall_cycle_fp 8
#define CtrlBlock_rename_stall_cycle_int 9
#define CtrlBlock_rename_stall_cycle_walk 10
#define CtrlBlock_me_freelist_1_4_valid 11
#define CtrlBlock_me_freelist_2_4_valid 12
#define CtrlBlock_me_freelist_3_4_valid 13
#define CtrlBlock_me_freelist_4_4_valid 14
#define CtrlBlock_std_freelist_1_4_valid 15
#define CtrlBlock_std_freelist_2_4_valid 16
#define CtrlBlock_std_freelist_3_4_valid 17
#define CtrlBlock_std_freelist_4_4_valid 18
#define CtrlBlock_dispatch_in 19
#define CtrlBlock_dispatch_empty 20
#define CtrlBlock_dispatch_utili 21
#define CtrlBlock_dispatch_waitinstr 22
#define CtrlBlock_dispatch_stall_cycle_lsq 23
#define CtrlBlock_dispatch_stall_cycle_rob 24
#define CtrlBlock_dispatch_stall_cycle_int_dq 25
#define CtrlBlock_dispatch_stall_cycle_fp_dq 26
#define CtrlBlock_dispatch_stall_cycle_ls_dq 27
#define CtrlBlock_intdq_dispatchq_in 28
#define CtrlBlock_intdq_dispatchq_out 29
#define CtrlBlock_intdq_dispatchq_out_try 30
#define CtrlBlock_intdq_dispatchq_fake_block 31
#define CtrlBlock_intdq_dispatchq_1_4_valid 32
#define CtrlBlock_intdq_dispatchq_2_4_valid 33
#define CtrlBlock_intdq_dispatchq_3_4_valid 34
#define CtrlBlock_intdq_dispatchq_4_4_valid 35
#define CtrlBlock_fpdq_dispatchq_in 36
#define CtrlBlock_fpdq_dispatchq_out 37
#define CtrlBlock_fpdq_dispatchq_out_try 38
#define CtrlBlock_fpdq_dispatchq_fake_block 39
#define CtrlBlock_fpdq_dispatchq_1_4_valid 40
#define CtrlBlock_fpdq_dispatchq_2_4_valid 41
#define CtrlBlock_fpdq_dispatchq_3_4_valid 42
#define CtrlBlock_fpdq_dispatchq_4_4_valid 43
#define CtrlBlock_lsdq_dispatchq_in 44
#define CtrlBlock_lsdq_dispatchq_out 45
#define CtrlBlock_lsdq_dispatchq_out_try 46
#define CtrlBlock_lsdq_dispatchq_fake_block 47
#define CtrlBlock_lsdq_dispatchq_1_4_valid 48
#define CtrlBlock_lsdq_dispatchq_2_4_valid 49
#define CtrlBlock_lsdq_dispatchq_3_4_valid 50
#define CtrlBlock_lsdq_dispatchq_4_4_valid 51
#define CtrlBlock_rob_interrupt_num 52
#define CtrlBlock_rob_exception_num 53
#define CtrlBlock_rob_flush_pipe_num 54
#define CtrlBlock_rob_replay_inst_num 55
#define CtrlBlock_rob_commitUop 56
#define CtrlBlock_rob_commitInstr 57
#define CtrlBlock_rob_commitInstrMove 58
#define CtrlBlock_rob_commitInstrFused 59
#define CtrlBlock_rob_commitInstrLoad 60
#define CtrlBlock_rob_commitInstrLoad_1 61
#define CtrlBlock_rob_commitInstrLoadWait 62
#define CtrlBlock_rob_commitInstrStore 63
#define CtrlBlock_rob_walkInstr 64
#define CtrlBlock_rob_walkCycle 65
#define CtrlBlock_rob_1_4_valid 66
#define CtrlBlock_rob_2_4_valid 67
#define CtrlBlock_rob_3_4_valid 68
#define CtrlBlock_rob_4_4_valid 69
#define CtrlBlock_Eu0_sche_allocate_fire 70
#define CtrlBlock_Eu0_sche_issue_fire 71
#define CtrlBlock_Eu0_std_freelist_1_4_valid 72
#define CtrlBlock_Eu0_std_freelist_2_4_valid 73
#define CtrlBlock_Eu0_std_freelist_3_4_valid 74
#define CtrlBlock_Eu0_std_freelist_4_4_valid 75
#define CtrlBlock_Eu1_sche_allocate_fire 76
#define CtrlBlock_Eu1_sche_issue_fire 77
#define CtrlBlock_Eu1_std_freelist_1_4_valid 78
#define CtrlBlock_Eu1_std_freelist_2_4_valid 79
#define CtrlBlock_Eu1_std_freelist_3_4_valid 80
#define CtrlBlock_Eu1_std_freelist_4_4_valid 81
#define CtrlBlock_Rs0_full 82
#define CtrlBlock_Rs1_full 83
#define CtrlBlock_Rs2_full 84
#define CtrlBlock_Rs3_full 85
#define CtrlBlock_Rs4_full 86
#define CtrlBlock_Rs5_full 87
#define CtrlBlock_Rs6_full 88
#define CtrlBlock_Rs7_full 89
#define CtrlBlock_Rs8_full 90
#define CtrlBlock_Rs9_full 91



#define SET_PERF_EXPECT 1
#define SET_PERF 294
#define GET_PERF_EXPECT 2
#define GET_PERF 295

#define MODE_OFFSET 59
#define MODE_MASK 0x1F
#define MODE_M 0x10
#define MODE_H 0x08
#define MODE_S 0x04
#define MODE_U 0x02
#define MODE_D 0x01

#define OPTYPE2_OFFSET 50
#define OPTYPE2_MASK 0x1F
#define OPTYPE1_OFFSET 45
#define OPTYPE1_MASK 0x1F
#define OPTYPE0_OFFSET 40
#define OPTYPE0_MASK 0x1F
#define OPTYPE_OR 0x0
#define OPTYPE_AND 0x1
#define OPTYPE_XOR 0x2
#define OPTYPE_ADD 0x4
// Operations
// Event0 <Optype0> Event1 = T1
// Event2 <Optype1> Event3 = T2
// T1 <Optype2> T2 = Result

#define EVENT3_OFFSET 30
#define EVENT3_MASK 0x3FF
#define EVENT2_OFFSET 20
#define EVENT2_MASK 0x3FF
#define EVENT1_OFFSET 10
#define EVENT1_MASK 0x3FF
#define EVENT0_OFFSET 0
#define EVENT0_MASK 0x3FF

#define SET(reg, field, value) (reg) = ((reg) & ~((uint64_t)(field##_MASK) << (field##_OFFSET))) | ((uint64_t)(value) << (field##_OFFSET));

#define EVENT_BASE 0x320
#define COUNTER_BASE 0xb00

#define clear_counter(id) syscall(SET_PERF, COUNTER_BASE + id, 0x0UL)
#define clear_event(id) syscall(SET_PERF, EVENT_BASE + id, 0x0UL)

#define print_event(id) printf("mhpmevent%d: %lx\n", id, syscall(GET_PERF, EVENT_BASE + id))
#define print_counter(id) printf("mhpmcounter%d: %lu\n", id, syscall(GET_PERF, COUNTER_BASE + id))
#define printd_csr(csr) printf(#csr": %ld\n", syscall(GET_PERF, csr))
#define printu_csr(csr) printf(#csr": %lu\n", syscall(GET_PERF, csr))
#define printx_csr(csr) printf(#csr": %lx\n", syscall(GET_PERF, csr))

#define set_event_quad(csr_id, mode, optype2, optype1, optype0, event3, event2, event1, event0) \
    {   \
        uint64_t value = syscall(GET_PERF, EVENT_BASE + csr_id); \
        SET(value, MODE, mode); \
        SET(value, OPTYPE2, optype2); \
        SET(value, OPTYPE1, optype1); \
        SET(value, OPTYPE0, optype0); \
        SET(value, EVENT3, event3); \
        SET(value, EVENT2, event2); \
        SET(value, EVENT1, event1); \
        SET(value, EVENT0, event0); \
        syscall(SET_PERF, EVENT_BASE + csr_id, value); \
    }

#define set_event_double(csr_id, mode, optype0, event1, event0) \
    set_event_quad(csr_id, mode, OPTYPE_OR, OPTYPE_OR, optype0, noEvent, noEvent, event1, event0)

#define set_event_single(csr_id, mode, event)\
    set_event_quad(csr_id, mode, OPTYPE_OR, OPTYPE_OR, OPTYPE_OR, noEvent, noEvent, noEvent, event)

// set event and clear counter
#define se_cc_quad(csr_id, mode, optype2, optype1, optype0, event3, event2, event1, event0) \
    {set_event_quad(csr_id, mode, optype2, optype1, optype0, event3, event2, event1, event0);clear_counter(csr_id);}
#define se_cc_double(csr_id, mode, optype0, event1, event0) \
    {set_event_double(csr_id, mode, optype0, event1, event0);clear_counter(csr_id);}
#define se_cc_single(csr_id, mode, event) \
    {set_event_single(csr_id, mode, event);clear_counter(csr_id);}

#endif // __EVENTS_H__
