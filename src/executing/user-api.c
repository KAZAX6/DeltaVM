#include "../Struct.h"
#include "fetch.h"
#include "sym.h"
#include "../../include/Delta-Regs.h"
#include <stddef.h>
#ifndef _WIN32
    #include <sys/mman.h>
#else
    #include <windows.h>
#endif
void __exec(DeltaVM_t* v,uint8_t* p);
void __exec_op(DeltaVM_t* v,DeltaVM_Opcode_t* op);
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
#define __round_up(x,align) __round_up_pow2(x)
void delta_run(DeltaVM_t* v,size_t max_mem) {
    if (!v->file) return;
    if (!v->stack) {
        #ifndef _WIN32 
            void* p = mmap(
                NULL,
                2048*4096,
                PROT_READ | PROT_WRITE,
                MAP_ANON | MAP_PRIVATE,
                -1,0
            );
            if (p == MAP_FAILED) return;
        #else
            void* p = VirtualAlloc(
                NULL,
                2048*4096,
                MEM_COMMIT | MEM_RESERVE,
                PAGE_READWRITE
            );
            if (!p) return;
        #endif
        v->stack = p;
    }
    if (!v->pool) {
        size_t s = __round_up(max_mem,4096);
        #ifndef _WIN32
            void* p = mmap(NULL,
            s,
        PROT_READ | PROT_WRITE,
        MAP_ANON | MAP_PRIVATE,
        -1,0);
        if (p == MAP_FAILED) {
            munmap((void*)v->rsp,2048*4096);
            v->rsp = 0;
            return;
        }
        #else
            void* p = VirtualAlloc(NULL,s,MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
            if (!p) {
                VirtualFree((void*)v->rsp,0,MEM_RELEASE);
                v->rsp = 0;
                return;
            }
        #endif
        v->pool = p;
        v->pool_max = (uint8_t*)p + s;
        v->pool_free = v->pool;
    }
    v->state = 1;
    for (;;) {
        if (v->state == 1 && v->rip < v->l) {
            __exec(v,(uint8_t*)v->file + v->rip);
            v->ebytes += 11;
        }
        else break;
    }
}
void delta_exec(DeltaVM_t* v,DeltaVM_Opcode_t* op) {
    __exec_op(v,op);
}