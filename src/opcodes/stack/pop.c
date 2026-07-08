#include "../../Struct.h"

uint64_t __pop (DeltaVM_t* vm, uint64_t unused1, uint64_t unused2, int mode) {
    uint64_t vl = *((uint64_t*)vm->rsp);
    vm->rsp += 8;
    vm->rip += 11;
    return vl;
}