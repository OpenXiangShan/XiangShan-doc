#include "hpmdriver.h"

int main() {
    uint64_t result[32] = {0};
    for (int i = 3; i < 28; i++)
    {
        result[i] = syscall(GET_PERF, COUNTER_BASE + i);
    }

    printf("HPM statistic: ====================\n");
    printf("Frontend: \n");
    printf("ifu_req, %ld\n", result[3]);
    printf("ifu_miss, %ld\n", result[4]);
    printf("IBuffer_hungry, %ld\n", result[5]);
    printf("Front_Bubble, %ld\n", result[6]);
    printf("mispredictRedirect, %ld\n", result[7]);
    printf("to_ifu_bubble, %ld\n", result[8]);
    printf("BpInstr, %ld\n", result[9]);
    printf("BpWrong, %ld\n", result[10]);

    printf("CtrlBlock: \n");
    printf("rob_walkInstr, %ld\n", result[11]);
    printf("rob_walkCycle, %ld\n", result[12]);
    printf("rob_interrupt_num, %ld\n", result[13]);
    printf("rob_exception_num, %ld\n", result[14]);
    printf("rob_flush_pipe_num, %ld\n", result[15]);
    printf("rob_replay_inst_num, %ld\n", result[16]);
    printf("rob_commitUop, %ld\n", result[17]);
    printf("rob_commitInstr, %ld\n", result[18]);

    printf("Memblock: \n");
    printf("l1_load_issue, %ld\n", result[19]);
    printf("l1_load_miss, %ld\n", result[20]);
    printf("l1_load_replay, %ld\n", result[21]);
    printf("rollback, %ld\n", result[22]);
    printf("mmio_in_progess, %ld\n", result[23]);
    printf("probe, %ld\n", result[24]);
    printf("release, %ld\n", result[25]);
    printf("l1_tlb_miss, %ld\n", result[26]);

    printf("Huaucun: \n");
    printf("selfdir_A_req, %ld\n", result[27]);
    printf("selfdir_A_hit, %ld\n", result[28]);

    printf("HPM Statistic over ===================\n");

    return 0;
}
