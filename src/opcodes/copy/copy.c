#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stddef.h>
#include <stdint.h>

void delta_set_reg(DeltaVM_t *v, Delta_Reg_t r, uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t *v, Delta_Reg_t r);

int __copy(DeltaVM_t* v,uint64_t dest,uint64_t src,int m) {
    switch (m) {
        case 0: // <IMM>
            delta_set_reg(v,dest,src);
            break;
        case 1: // <REG>
            delta_set_reg(v,dest,delta_get_reg(v,src));
            break;
        case 2: // <MEM>
            delta_set_reg(v,dest,delta_get_reg(v,src));
            break;
    }
    v->rip += 11;
    return 0;
}