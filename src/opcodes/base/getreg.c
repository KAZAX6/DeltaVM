#include "../../Struct.h"
#include "../../../include/Delta-Regs.h"
uint64_t delta_get_reg(DeltaVM_t* vm, uint64_t r, uint64_t unused, int mode) {
    return ((uint64_t*)vm)[r];
}