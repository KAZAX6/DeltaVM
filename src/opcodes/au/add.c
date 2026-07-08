#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stdint.h>
#include <string.h>
void delta_set_reg(DeltaVM_t* v,Delta_Reg_t r,uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t* v,Delta_Reg_t r);
#define CASE(val,c) \
    case val: c \
    break;
void __addf(DeltaVM_t* v,uint64_t save,uint64_t a1,uint64_t a2,int mode) {
    double res = 0;
    switch (mode) {
        CASE(0,{
            res = (double)delta_get_reg(v,a1) + (double)a2;
        })
        CASE(1,{
            res = (double)delta_get_reg(v,a1) + (double)delta_get_reg(v,a2);
        })
        CASE(2,{
            res = (double)delta_get_reg(v,a1) + *(double*)a2;
        })
        CASE(3,{
            res = *(double*)a1 + (double)delta_get_reg(v,a2);
        })
    }

    uint64_t bits;
    memcpy(&bits, &res, sizeof(bits));
    delta_set_reg(v, save, bits);
}

int __add(DeltaVM_t* v,uint64_t a1,uint64_t a2,int mode) {
    uint64_t save = a1;
    if (save >= REG_F0) __addf(v,save,a1,a2,mode);
    else
    switch (mode) {
        CASE(0,{
            delta_set_reg(v,save,delta_get_reg(v,a1) + a2);
        })
        CASE(1,{
            delta_set_reg(v,save,delta_get_reg(v,a1) + delta_get_reg(v,a2));
        })
        CASE(2,{
            delta_set_reg(v,save,delta_get_reg(v,a1) + *(uint64_t*)a2);
        })
        CASE(3,{
            delta_set_reg(v,save,*(uint64_t*)a1 + delta_get_reg(v,a2));
        })
    }
    v->rip += 11;
    return 0;
}