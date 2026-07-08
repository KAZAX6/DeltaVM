#ifndef DELTA_EXT_API
    #include <stddef.h>
    #include <stdint.h>
    #include "Delta-Regs.h"
    typedef struct DeltaVM_t DeltaVM_t;
    uint64_t delta_get_reg(DeltaVM_t* v,Delta_Reg_t r);
    void delta_set_reg(DeltaVM_t* v,Delta_Reg_t r,uint64_t newv);
    void delta_new_frame(DeltaVM_t* v);
    void delta_end_frame(DeltaVM_t* v);
     // RESERVED :: void delta_try(DeltaVM_t* v);
     // RESERVED :: void delta_runTry(DeltaVM_t* v);
     // RESERVED :: void delta_catch(DeltaVM_t* v);
     // RESERVED :: void delta_throw(DeltaVM_t* v,const char* e);
    void* delta_alloc(DeltaVM_t* v,size_t s);
    #define DELTA_ALLOCA(v,s) \
        delta_set_reg(v,REG_RSP,delta_get_reg(v,REG_RSP) - s)
    
#endif