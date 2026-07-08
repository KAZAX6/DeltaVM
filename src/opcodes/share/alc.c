#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stddef.h>
#include <stdint.h>
void delta_set_reg(DeltaVM_t *v, Delta_Reg_t r, uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t *v, Delta_Reg_t r);

int __alc(DeltaVM_t* v,size_t s,uint64_t st,int st2) {
    if (((uint8_t*)v->pool_free + s > (uint8_t*)v->pool_max)) {
        delta_set_reg(v,REG_R0,0);
        return 1;
    }
    delta_set_reg(v,REG_R0,(uint64_t)v->pool_free);
    v->pool_free = (uint8_t*)v->pool_free + s;
    v->rip += 11; 
    return 1;
}