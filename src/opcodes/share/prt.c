#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
uint64_t delta_get_reg(DeltaVM_t* v,Delta_Reg_t r);

int __print(DeltaVM_t* vm, uint64_t vl, uint64_t unused, int mode) {
    int m = mode;

    if (m == 1 && vl >= REG_F0) m = 3;
    double r;
    switch (m) {
        case 0: //<IMM>
            printf("%"PRIu64"\n",vl);
            break;
        case 1: // <REG>
            printf("%"PRIu64"\n",delta_get_reg(vm,vl));
            break;
        case 2: // <MEM>
            printf("%s\n",(char*)vl);
            break;
        case 3: // <FREG>
            memcpy(&r,&vl, sizeof(vl));
            printf("%lf",r);
    }
    vm->rip += 11;
    return 1;
}