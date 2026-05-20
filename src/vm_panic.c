#include <stdlib.h>
#define EXCEPTION_HEAP_EXPLOTATION 1
#define EXCEPTION_NO_MEM 2
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#define CANARY_TAIL_VALUE 0xBAADF00DBAADF00D
#define CANARY_HEAD_VALUE 0xDEADDEADDEADDEAD
#define STR(x) #x
void vm_panic(int exc) {
    switch (exc) {
    case EXCEPTION_HEAP_EXPLOTATION: {
        fprintf(stderr,"VM PANIC: Exception inside VM!\n");
        fprintf(stderr,"|-> Exception : %s\n",STR(EXCEPTION_HEAP_EXPLOTATION));
        abort();
    }
    case EXCEPTION_NO_MEM: {
        fprintf(stderr,"VM PANIC: Exception inside VM!\n");
        fprintf(stderr,"|-> Exception : %s\n",STR(EXCEPTION_NO_MEM));
        abort();
    }
    default:
    fprintf(stderr,"VM PANIC: Unknown exception inside VM!\n");
    abort();
    }
}
void vm_segv(void* address) {
    fprintf(stderr,"VM PANIC : Segfault\n");
    fprintf(stderr,"|-->Adress: %p\n",address);
    abort();
}
void vm_abrt(void) {
    fprintf(stderr,"VM PANIC : Got signal for abort!\n");
    abort();
}
void vm_structs_corruption(void* corrupted, size_t size) {
    fprintf(stderr, "VM PANIC : Corrupted Struct!\n");
    fprintf(stderr, "|-> Corrupted Address : %p ... %p\n",
            corrupted, (uint8_t*)corrupted + size);

    uint64_t* head = (uint64_t*)corrupted;
    uint64_t* tail = (uint64_t*)((uint8_t*)corrupted + size - sizeof(uint64_t));

    fprintf(stderr, "|-> Canary head: 0x%016" PRIx64 ", expected: 0x%016" PRIx64 "\n",
            *head, (uint64_t)CANARY_HEAD_VALUE);

    fprintf(stderr, "|-> Canary tail: 0x%016" PRIx64 ", expected: 0x%016" PRIx64 "\n",
            *tail, (uint64_t)CANARY_TAIL_VALUE);

    abort();
}
