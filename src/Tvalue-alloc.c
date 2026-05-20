#include "include/TValue.h"
#include "include/allocator.h"
#include "include/canary.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#define EXCEPTION_HEAP_EXPLOTATION 1
#define EXCEPTION_NO_MEM 2
#define ALLOC_POOL_PAGES 16777216
static allocator_t* al = NULL;
extern void vm_panic(int exc);

TValue* _get_tvalue(void) {
    if (!al) {
        al = allocator_get(ALLOC_POOL_PAGES,sizeof(TValue));
        if (!al) vm_panic(EXCEPTION_NO_MEM);
    }
    TValue* v = allocator_allocate(al);
    if (!v) vm_panic(EXCEPTION_NO_MEM);
    INIT_STRUCT_PTR(v);
    return v;
}
void tvalue_push_u8(TValue*v,uint8_t d) {
    CHECK_STRUCT(*v);
    if (!strcmp(tvalue_type(v),"unsigned char") || !strcmp(tvalue_type(v),"char")) return;
    v->data = (void*)(uintptr_t)d;
}
void tvalue_push_u16(TValue*v,uint16_t d) {
    CHECK_STRUCT(*v);
    if (!strcmp(tvalue_type(v),"unsigned short") || !strcmp(tvalue_type(v),"short")) return;
    v->data = (void*)(uintptr_t)d;
}
void tvalue_push_u32(TValue* v, uint32_t d) {
    CHECK_STRUCT(*v);
    if (!strcmp(tvalue_type(v), "unsigned int") ||
        !strcmp(tvalue_type(v), "int"))
        return;

    v->data = (void*)(uintptr_t)d;
}
void tvalue_push_u64(TValue* v, uint64_t d) {
    CHECK_STRUCT(*v);
    if (!strcmp(tvalue_type(v), "unsigned long") ||
        !strcmp(tvalue_type(v), "long"))
        return;

    v->data = (void*)(uintptr_t)d;
}
void _free_bf(void) {
    allocator_free(&al);
}