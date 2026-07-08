#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
void delta_set_reg(DeltaVM_t* vm, uint64_t r, uint64_t val, int mode) {
    ((uint64_t*)vm)[r] = val;
}