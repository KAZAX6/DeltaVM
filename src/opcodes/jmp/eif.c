#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stddef.h>
#include <stdint.h>

void delta_set_reg(DeltaVM_t *v, Delta_Reg_t r, uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t *v, Delta_Reg_t r);
void __exec(DeltaVM_t* v,uint64_t p);
int __eif(DeltaVM_t* v,Delta_Reg_t r1,Delta_Reg_t r2,uint64_t pos) {
    if (delta_get_reg(v,r1) == delta_get_reg(v,r2)) {
        delta_set_reg(v,REG_RIP,pos);
        return 1;
    }
    v->rip += 11;
    return 0;
}