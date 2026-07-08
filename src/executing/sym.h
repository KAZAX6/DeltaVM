#ifndef _DEL_SYM
    #define _DEL_SYM
    #include <stddef.h>
    #include <stdint.h>
    typedef struct DeltaVM_t DeltaVM_t;
    typedef struct {
        char* sym;
        uint64_t addr;
        uint64_t len;
    } DeltaSym_t;
    DeltaSym_t __sym(DeltaVM_t* v,size_t addr) ;
#endif