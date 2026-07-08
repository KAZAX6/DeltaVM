#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stddef.h>
#include <stdint.h>

void delta_set_reg(DeltaVM_t *v, Delta_Reg_t r, uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t *v, Delta_Reg_t r);

int __and(DeltaVM_t* v,uint64_t a1,uint64_t a2,int a) {
    uint64_t save = a1;
    switch (a) {
        case 0: // <REG> <IMM>
            delta_set_reg(v,save,delta_get_reg(v,a1) & a2);
            break;
        case 1:  // <REG> <REG>
            delta_set_reg(v,save,delta_get_reg(v,a1) & delta_get_reg(v,a2));
            break;
        case 2: // <REG> <MEM>
            delta_set_reg(v,save,delta_get_reg(v,a1) & *(uint64_t*)a2);
            break;
        case 3: // <MEM> <REG>
            *(uint64_t*)save = *(uint64_t*)a1 & delta_get_reg(v,a2);
            break;
    }
    v->rip += 11;
    return 0;
}