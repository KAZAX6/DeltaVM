#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
void delta_set_reg(DeltaVM_t* v,Delta_Reg_t r,uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t* v,Delta_Reg_t r);
int __mov(DeltaVM_t* v,uint64_t dest,uint64_t src,int mod) {
    switch (mod) {
        case 0: // mov <REG> <IMM>
            delta_set_reg(v,dest,src);
            break;
        case 1: // mov <REG> <REG>
            delta_set_reg(v,dest,delta_get_reg(v,src));
            break;
        case 2: // mov <REG> <MEM>
            delta_set_reg(v,dest,*(uint64_t*)src);
            break;
        case 3: // mov <MEM> <REG>
            *(uint64_t*)dest = delta_get_reg(v,src);
            break;
    }
    v->rip += 11;
    return 1;
}
