#ifndef _DVM_STR
    #define _DVM_STR
    #include "executing/fetch.h"
    #include <stdint.h>
    typedef struct DeltaVM_t {
        uintptr_t regs[16];
        uintptr_t rra,rip;
        uintptr_t rsp,rbp;
        double   fregs[16];
        void*    stack;
        int      maped;
        void*    pool;
        void*    pool_free;
        void*    pool_max;
        int      state;
        void*    symtab;
        void*    file;
        uint64_t l;
        uint64_t ebytes;
        const char*    fn;
        const char*    rfn;
    } DeltaVM_t; 
#endif