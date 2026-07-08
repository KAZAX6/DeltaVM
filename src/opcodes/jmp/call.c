#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stddef.h>
#include <stdint.h>
#include "../../executing/sym.h"
void delta_set_reg(DeltaVM_t *v, Delta_Reg_t r, uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t *v, Delta_Reg_t r);
int __call(DeltaVM_t* v,uint64_t pos,uint64_t stub,int mod) {
    v->rfn = v->fn;
    DeltaSym_t sm = __sym(v,pos);
    const char* s = sm.sym;
    if (s) v->fn = s;
    delta_set_reg(v,REG_RRA,delta_get_reg(v,REG_RIP) + 11);
    if (mod != 1)
        delta_set_reg(v,REG_RIP,pos);
    else delta_set_reg(v, REG_RIP,delta_get_reg(v,pos));
    return 0;
}