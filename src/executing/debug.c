#include "../Struct.h"
#include "../../include/Delta-Regs.h"
#include "../../include/Delta-ExtAPI.h"
#include <stdio.h>
#include <inttypes.h>
void __exec(DeltaVM_t* v,uint64_t p);
void delta_step(DeltaVM_t* v) {
    if (!v->rip) v->rip = 24;
    __exec(v,(uint64_t)v->file + v->rip);
}
void delta_prt_trace(DeltaVM_t* v) {
    puts("===== Delta VM Traceback =====");
    for (int i = 0;i <= REG_R15;i++) {
        printf("REGISTER: R%d :%"PRIu64"\n",i,delta_get_reg(v,i));
    }
    printf("REGISTER: RRA : %"PRIu64"\n",delta_get_reg(v,REG_RRA));
    printf("REGISTER: RIP : %"PRIu64"\n",delta_get_reg(v,REG_RIP));
    printf("REGISTER: RSP : %"PRIu64"\n",delta_get_reg(v,REG_RSP));
    printf("REGISTER: RBP : %"PRIu64"\n",delta_get_reg(v,REG_RBP));
    for (int i = 0;i <= 15;i++) 
        printf("REGISTER: F%d :%lf\n",i,v->fregs[i]);
    printf("CURRENT FUNCTION: %s\n",v->fn);
    printf("RETURN FUNCTION: %s\n",v->rfn);
    printf("EXECUTED BYTES: %"PRIu64"\n",v->ebytes);
    puts("===== Delta VM Traceback End ====");
}