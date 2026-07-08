 // RESERVED :: void delta_log_mode(DeltaVM_t* v,int f);
 // RESERVED :: void delta_traceback(DeltaVM_t* v);
#ifndef DVM_H
    #define DVM_H
    #include <stddef.h>
    #include <stdint.h>
    #define DBIN_MAGIC '\0','D','B','I','N','\0','\0','\n'
    typedef struct DeltaVM_Opcode_t {
        uint8_t type;
        uint8_t op;
        uint8_t dest;
        uint64_t src;
    } DeltaVM_Opcode_t;
    typedef struct DeltaVM_t DeltaVM_t; 
    DeltaVM_t* delta_new(void);
    void delta_load(DeltaVM_t* v,void* byte,size_t s,int is_maped);
    void delta_run(DeltaVM_t* v,size_t max_mem);
    void delta_exec(DeltaVM_t* v,DeltaVM_Opcode_t* op);
    DeltaVM_Opcode_t delta_get_op(void* raw_data_ptr);
    void delta_free(DeltaVM_t** v); 
#endif 