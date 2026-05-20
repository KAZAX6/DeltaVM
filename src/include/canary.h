#ifndef CANARY_H
    #include <stdint.h>
    #include <stddef.h>
    extern void vm_structs_corruption(void* corrupted, size_t size);
    #define CANARY_H
    #define CANARY_TAIL uint64_t __canary_tail;
    #define CANARY_HEAD uint64_t __canary_head;
    #define CANARY_P1 CANARY_HEAD
    #define CANARY_P2 CANARY_TAIL
    #define CANARY_TAIL_VALUE 0xBAADF00DBAADF00D
    #define CANARY_HEAD_VALUE 0xDEADDEADDEADDEAD
    #define INIT_STRUCT_PTR(s) do { \
    (s)->__canary_head = CANARY_HEAD_VALUE; \
    (s)->__canary_tail = CANARY_TAIL_VALUE; \
} while (0)

#define INIT_STRUCT(s) do { \
    (s).__canary_head = CANARY_HEAD_VALUE; \
    (s).__canary_tail = CANARY_TAIL_VALUE; \
} while (0)
#define CHECK_STRUCT_PTR(s,size) \
    do { \
        if ((s)->__canary_head != CANARY_HEAD_VALUE) vm_structs_corruption(s,size); \
        if ((s)->__canary_tail != CANARY_TAIL_VALUE) vm_structs_corruption(s,size); \
    }while(0)
#define CHECK_STRUCT(s) CHECK_STRUCT_PTR(&s,sizeof(s))
#endif