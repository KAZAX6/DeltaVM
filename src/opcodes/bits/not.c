#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stddef.h>
#include <stdint.h>

void delta_set_reg(DeltaVM_t *v, Delta_Reg_t r, uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t *v, Delta_Reg_t r);

int __not(DeltaVM_t* v,uint64_t a1,uint64_t a2,int mod){
    int a = mod;
    uint64_t save = a1;
    switch (a) {
        case 1: // <REG>
            delta_set_reg(v,save,~delta_get_reg(v,a1));
            break;
        case 2:
        *(uint64_t*)save = ~(*(uint64_t*)a1);
    }
    v->rip += 11;
    return 0;
}