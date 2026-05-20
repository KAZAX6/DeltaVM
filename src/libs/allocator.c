#include "../include/allocator.h"
#include <stdint.h>
#include <stdlib.h>
#define PAGE_SIZE 4096
#ifdef _WIN32
    #include <windows.h>
    #define POSIX 0
#else
    #include <sys/mman.h>
    #define POSIX 1
#endif
struct allocator {
    uint8_t* arena;
    uint8_t* free;
    size_t size;
    uint8_t* end;
    size_t elems;
};
allocator_t* allocator_get(size_t pages,size_t elem_size) {
    if (!pages || !elem_size) return NULL;
    allocator_t* a = calloc(1,sizeof(allocator_t));
    if (!a) return NULL;
    size_t s = pages * PAGE_SIZE;
    #if POSIX
        a->arena = mmap(NULL,s,
        PROT_READ | PROT_WRITE,
    MAP_ANONYMOUS | MAP_PRIVATE,-1,0);
    if (a->arena == MAP_FAILED) {
        free(a);
        return NULL;
    }
    #else
    a->arena = VirtualAlloc(
        NULL,
        s,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );
    if (!a->arena) {
        free(a);
        return NULL;
    }
    #endif
    a->end = a->arena +  s;
    a->free = a->arena;
    a->size = s;
    a->elems = elem_size;
    return  a;
}
size_t allocator_max(allocator_t* al) {
    if (!al || !al->size || !al->elems)
        return 0;
    return al->size / al->elems;
}
void* allocator_allocate(allocator_t* a) {
    if (!a || !a->arena || ((size_t)(a->end - a->free) < a->elems)) return NULL;
    void* p = a->free;
    a->free += a->elems;
    return p;
}
void allocator_free(allocator_t** a) {
    if (!a || !(*a)) return;
    allocator_t* al = *a;
    #if POSIX
        munmap(al->arena,al->size);
    #else
        VirtualFree(al->arena, 0, MEM_RELEASE);
    #endif
    free(al);
    *a = NULL;
}