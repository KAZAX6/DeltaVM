#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stddef.h>
#include <stdint.h>
void delta_set_reg(DeltaVM_t *v, Delta_Reg_t r, uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t *v, Delta_Reg_t r);
int __ret(DeltaVM_t* v,uint64_t s1,uint64_t s2,int s3) {
    delta_set_reg(v,REG_RIP,delta_get_reg(v,REG_RRA));
    v->fn = v->rfn;
    return 0;
}