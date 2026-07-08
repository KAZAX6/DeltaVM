#ifndef _DEL_FNS
    #define _DEL_FNS
    #include "../Struct.h"
    #include "../../include/Delta-Regs.h"
    #include <stddef.h>
    
    #define DELTA_OPC 21
    int __call(DeltaVM_t* vm, uint64_t pos, uint64_t unused, int mode);
    int __ret (DeltaVM_t* vm, uint64_t unused1, uint64_t unused2, int mode);
    int __alc (DeltaVM_t* vm, uint64_t size, uint64_t unused, int mode);
    int __ende(DeltaVM_t* vm, uint64_t unused1, uint64_t unused2, int mode);
    int __print(DeltaVM_t* vm, uint64_t val, uint64_t unused, int mode);
    int __add(DeltaVM_t* v,uint64_t a1,uint64_t a2,int mode);
    int __div(DeltaVM_t* v,uint64_t a1,uint64_t a2,int mode);
    int __mul(DeltaVM_t* v,uint64_t a1,uint64_t a2,int mode);
    int __sub(DeltaVM_t* v,uint64_t a1,uint64_t a2,int mode);
    int __and(DeltaVM_t* v,uint64_t a1,uint64_t a2,int a) ;
    int __not(DeltaVM_t* v,uint64_t a1,uint64_t a2,int mod);
    int __or(DeltaVM_t* v,uint64_t a1,uint64_t a2,int a) ;
    int __xor(DeltaVM_t* v,uint64_t a1,uint64_t a2,int a);
    int __copy(DeltaVM_t* v,uint64_t dest,uint64_t src,int m);
    int __jif  (DeltaVM_t* vm, uint64_t r1, uint64_t r2, uint64_t pos);
    int __jifn (DeltaVM_t* vm, uint64_t r1, uint64_t r2, uint64_t pos);
    int __eif  (DeltaVM_t* vm, uint64_t r1, uint64_t r2, uint64_t pos);
    int __jmp (DeltaVM_t* vm, uint64_t pos, uint64_t unused, int mode);
    int __mov(DeltaVM_t* v,uint64_t dest,uint64_t src,int mod) ; 
    int     __push(DeltaVM_t* vm, uint64_t val, uint64_t unused, int mode);
    uint64_t __pop (DeltaVM_t* vm, uint64_t unused1, uint64_t unused2, int mode);
    uint64_t delta_get_reg(DeltaVM_t* vm, uint64_t r, uint64_t unused, int mode);
    void     delta_set_reg(DeltaVM_t* vm, uint64_t r, uint64_t val, int mode);
#endif