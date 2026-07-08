#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "../../Struct.h"
#ifndef _WIN32
    #include <sys/mman.h>
#else
    #include <windows.h>
#endif
static inline uint64_t __round_up_pow2(uint64_t x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x + 1;
}
static inline uint64_t __round_up(uint64_t x, uint64_t align) {
    x = __round_up_pow2(x);
    return (x + align - 1) & ~(align - 1);
}

int __check(void* f) ;
void delta_load(DeltaVM_t* v, void* byte, size_t s, int is_maped) {
    if (!v || !byte) return;
    void* mem = NULL;
    if (is_maped) {
        mem = byte;
        v->maped = 0;
    } else {
        size_t size = __round_up(s, 4096);
    #ifndef _WIN32
            mem = mmap(NULL, size, PROT_READ | PROT_WRITE,
            MAP_ANON | MAP_PRIVATE, -1, 0);
            if (mem == MAP_FAILED) return;
        #else
            mem = VirtualAlloc(NULL, size,
            MEM_RESERVE | MEM_COMMIT,
            PAGE_READWRITE);
            if (!mem) return;
        #endif
        memcpy(mem, byte, s);
        if (!__check(mem)) {
            #ifndef _WIN32
                munmap(mem, size);
            #else
                VirtualFree(mem, 0, MEM_RELEASE);
            #endif
            return;
        }
        v->maped = 1;
    }
    v->file = mem;
    v->l = s;
    uint64_t symtab_off;
    memcpy(&symtab_off, (uint8_t*)mem + 16, 8);
    v->symtab = (uint64_t*)((uint8_t*)mem + symtab_off);
    v->rip = (uint64_t)(((uint8_t*)byte)[8]);
}
