#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <DeltaVM/Delta-Regs.h>
#include <stddef.h>
#include <stdint.h>

void delta_set_reg(DeltaVM_t *v, Delta_Reg_t r, uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t *v, Delta_Reg_t r);

int __jmp (DeltaVM_t* vm, uint64_t pos, uint64_t unused, int mode) {
    if (mode == 0)
        delta_set_reg(vm,REG_RIP,pos);
    else delta_set_reg(vm,REG_RIP,delta_get_reg(vm,pos));
    return 1;
}