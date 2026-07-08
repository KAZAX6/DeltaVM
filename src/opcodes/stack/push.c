#include "../../Struct.h"

int __push(DeltaVM_t* vm, uint64_t val, uint64_t unused, int mode) {
    vm->rsp -= 8;
    *((uint64_t*)vm->rsp) = val;
    vm->rip += 11;
    return 1;
}