#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stdint.h>
#include <string.h>
void delta_set_reg(DeltaVM_t* v,Delta_Reg_t r,uint64_t newv);
uint64_t delta_get_reg(DeltaVM_t* v,Delta_Reg_t r);
void __panic(DeltaVM_t* v);
#define CASE(val,c) \
    case val: c \
    break;
void __divf(DeltaVM_t* v,uint64_t save,uint64_t a1,uint64_t a2,int mode) {
    double res = 0;
    switch (mode) {
        CASE(0,{ // REG / IMM
            double vl = (double)delta_get_reg(v,a1);
            double dv = (double)a2;
            if (dv == 0.0) __panic(v);
            res = vl / dv;
        })

        CASE(1,{ // REG / REG
            double vl = (double)delta_get_reg(v,a1);
            double dv = (double)delta_get_reg(v,a2);
            if (dv == 0.0) __panic(v);
            res = vl / dv;
        })

        CASE(2,{ // REG / MEM
            double vl = (double)delta_get_reg(v,a1);
            double dv = *(double*)a2;
            if (dv == 0.0) __panic(v);
            res = vl / dv;
        })

        CASE(3,{ // MEM / REG
            double vl = *(double*)a1;
            double dv = (double)delta_get_reg(v,a2);
            if (dv == 0.0) __panic(v);
            res = vl / dv;
        })
    }

    uint64_t r;
    memcpy(&r, &res, sizeof(res));
    delta_set_reg(v, save, r);
}

int __div(DeltaVM_t* v,uint64_t a1,uint64_t a2,int mode) {
    uint64_t save = a1;
    if (a2 == 0 || (a1 == 0 && a2 == 0)) __panic(v);
    if (a1 == a2) delta_set_reg(v,save,1);
    if (save >= REG_F0) __divf(v,save,a1,a2,mode);
    else
    switch (mode) {
        CASE(0,{
            delta_set_reg(v,save,delta_get_reg(v,a1) / a2);
        })
        CASE(1,{
            delta_set_reg(v,save,delta_get_reg(v,a1) / delta_get_reg(v,a2));
        })
        CASE(2,{
            uint64_t dv =  delta_get_reg(v,a1);
            uint64_t vl = *(uint64_t*)a2;
            if (dv == 0) __panic(v);
            delta_set_reg(v,save,vl / dv);
        })
        CASE(3,{
            uint64_t dv =  delta_get_reg(v,a2);
            uint64_t vl = *(uint64_t*)a1;
            if (dv == 0) __panic(v);
            delta_set_reg(v,save,vl / dv);
        })
    }
    v->rip += 11;
    return 0;
}