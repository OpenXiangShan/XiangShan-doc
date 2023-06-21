#include "hpmdriver.h"

int main() {
    printf("Hello, XiangShan!\n");
    printf("Begin HPM init!\n");

    se_cc_single(3, MODE_M, Frontend_ifu_req);
    se_cc_single(4, MODE_M, Frontend_ifu_miss);
    se_cc_single(5, MODE_M, Frontend_IBuffer_hungry);
    se_cc_single(6, MODE_M, Frontend_Front_Bubble);
    se_cc_single(7, MODE_M, Frontend_mispredictRedirect);
    se_cc_single(8, MODE_M, Frontend_to_ifu_bubble);
    se_cc_single(9, MODE_M, Frontend_BpInstr);
    se_cc_single(10, MODE_M, Frontend_BpWrong);

    se_cc_single(11, MODE_M, CtrlBlock_rob_walkInstr);
    se_cc_single(12, MODE_M, CtrlBlock_rob_walkCycle);
    se_cc_single(13, MODE_M, CtrlBlock_rob_interrupt_num);
    se_cc_single(14, MODE_M, CtrlBlock_rob_exception_num);
    se_cc_single(15, MODE_M, CtrlBlock_rob_flush_pipe_num);
    se_cc_single(16, MODE_M, CtrlBlock_rob_replay_inst_num);
    se_cc_single(17, MODE_M, CtrlBlock_rob_commitUop);
    se_cc_single(18, MODE_M, CtrlBlock_rob_commitInstr);

    se_cc_double(19, MODE_M, OPTYPE_ADD, MemBlock_lu0_load_s1_in_fire, MemBlock_lu1_load_s1_in_fire);
    se_cc_double(20, MODE_M, OPTYPE_ADD, MemBlock_lu0_load_s2_dcache_miss, MemBlock_lu1_load_s2_dcache_miss);
    se_cc_double(21, MODE_M, OPTYPE_ADD, MemBlock_lu0_load_s2_replay, MemBlock_lu1_load_s2_replay);
    se_cc_single(22, MODE_M, MemBlock_lq_rollback);
    se_cc_single(23, MODE_M, MemBlock_lq_mmioCycle);
    se_cc_single(24, MODE_M, MemBlock_dcache_probq_req);
    se_cc_single(25, MODE_M, MemBlock_dcache_wbq_req);
    se_cc_double(26, MODE_M, OPTYPE_ADD, MemBlock_lu0_load_s2_replay_tlb_miss, MemBlock_lu1_load_s2_replay_tlb_miss);

    se_cc_quad(27, MODE_M, OPTYPE_ADD, OPTYPE_ADD, OPTYPE_ADD, Huancun_Bank0_selfdir_A_req, Huancun_Bank1_selfdir_A_req, Huancun_Bank2_selfdir_A_req, Huancun_Bank3_selfdir_A_req);
    se_cc_quad(28, MODE_M, OPTYPE_ADD, OPTYPE_ADD, OPTYPE_ADD, Huancun_Bank0_selfdir_A_hit, Huancun_Bank1_selfdir_A_hit, Huancun_Bank2_selfdir_A_hit, Huancun_Bank3_selfdir_A_hit);

    printf("End HPM init!\n");
    return 0;
}
