#include "../../Struct.h"
#include <stdio.h>
int __ende(DeltaVM_t* vm, uint64_t unused1, uint64_t unused2, int mode) {
    vm->state = 0;
    return 0;
}
