#ifndef DELTA_SCRIPT_H
    #define DELTA_SCRIPT_H
    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>
    #ifndef DELTA_TYPES
        #define DELTA_TYPES
        typedef enum { 
        TYPE_INT8 ,
        TYPE_INT16 ,
        TYPE_INT32 ,
        TYPE_INT64 ,

        TYPE_UINT8 ,
        TYPE_UINT16 ,
        TYPE_UINT32 ,
        TYPE_UINT64  ,

        TYPE_PTR ,
        TYPE_STR ,
        TYPE_DOUBLE
        } delta_types;
    #endif
    #ifndef DELTA_REGISTERS_ENUM 
    typedef enum {
    DELTA_REG_RAX = 0,
    DELTA_REG_RDI = 1,
    DELTA_REG_RSI = 2,
    DELTA_REG_RDX = 3,
    DELTA_REG_RCX = 4,
    DELTA_REG_R8  = 5,
    DELTA_REG_R9  = 6,
    DELTA_REG_R10 = 7,
    DELTA_REG_R11 = 8,
    DELTA_REG_RBX = 9,
    DELTA_REG_R12 = 10,
    DELTA_REG_R13 = 11,
    DELTA_REG_R14 = 12,
    DELTA_REG_R15 = 13,
    DELTA_REG_U1 = 14,
    } delta_reg_index;
    typedef enum {
        DELTA_REG_XMM0,
        DELTA_REG_XMM1,
        DELTA_REG_XMM2,
        DELTA_REG_XMM3,
        DELTA_REG_XMM4,
        DELTA_REG_XMM5,
        DELTA_REG_XMM6,
        DELTA_REG_XMM7,
        DELTA_REG_XMM8,
        DELTA_REG_XMM9,
        DELTA_REG_XMM10,
        DELTA_REG_XMM11,
        DELTA_REG_XMM12,
        DELTA_REG_XMM13,
        DELTA_REG_XMM14,
        DELTA_REG_XMM15
    } delta_fp_reg_index;
    #endif
    typedef struct Delta_Scope Delta_Scope;
    typedef struct Delta_Module Delta_Module;
    typedef struct {
        const char* name;
        void(*cfn)(Delta_Scope*);
        int ret_type;
        const char* descr;
    } delta_c_fn_decl;
    typedef struct {
        const char* field_name;
        int _type;
        void* data;
    } delta_class_field;
    Delta_Scope* delta_run(void);
    
    int delta_top(Delta_Scope* s);
    void delta_settop(Delta_Scope*s,int ind);
    void delta_call(Delta_Scope* s,void(*cfn)(Delta_Scope*));
    void delta_push(Delta_Scope* s,delta_types type,void* data);
    const void* delta_pop(Delta_Scope* s,delta_types type);
    void delta_end(void);

    Delta_Scope* delta_global();

    void delta_register(Delta_Scope* global_s,delta_c_fn_decl dec);
    void delta_register_by_arr(Delta_Scope* global_s,delta_c_fn_decl decls[],size_t count);
    void delta_call_registered(Delta_Scope* s,const char* name);

    void delta_struct_define(Delta_Scope* s,const char* class_name,delta_class_field fields[]);
    void delta_struct_new(Delta_Scope* s,const char* class_name,const char* var_name);
    const void* delta_struct_get(Delta_Scope* s,const char* var_name,const char* field);

    void delta_arr_new(Delta_Scope* s,const char* name,delta_types t,size_t elems);
    const void* delta_arr_get(Delta_Scope* s,const char* name,size_t ind);
    void delta_arr_set(Delta_Scope*s,const char* name,size_t ind,void* elem);

    void delta_def_var(Delta_Scope* s,const char* name,delta_types t,void* v);
    const void* delta_get_var_val(Delta_Scope* s,const char* name);
    void delta_set_var_val(Delta_Scope*s ,const char* name,void* d);

    void delta_def_ptr(Delta_Scope* s,const char* name,delta_types t);
    void delta_ptr_alloc(Delta_Scope* s,const char* name,size_t size);
    void delta_ptr_free(Delta_Scope*s,const char* name);
    void delta_ptr_store(Delta_Scope*s ,const char* name,void* to_write);
    const void* delta_ptr_load(Delta_Scope* s,const char* name);

    bool delta_exception(Delta_Scope* s);
    const char* delta_exception_message(Delta_Scope* s);
    void delta_throw(Delta_Scope* s, const char* message);


    Delta_Module* delta_module_import(Delta_Scope* gscope,const char* path);
    Delta_Module* delta_module_make(Delta_Scope* s,const char* name);
    void delta_module_call(Delta_Module* m,const char* fn_name,Delta_Scope* args);
    const void* delta_module_get_var(Delta_Module* m,const char* varname,delta_types type);
     // TODO: void delta_func_new(Delta_State*s ,char* name,void* op_codes,size_t opcodes_len);
    
    void delta_reg_move(Delta_Scope*s,delta_reg_index reg,intptr_t v);
    void delta_reg_copy(Delta_Scope*s,delta_reg_index dest,delta_reg_index src);
    void delta_reg_add(Delta_Scope*s,delta_reg_index dest,intptr_t v);
    intptr_t delta_reg_get_val(Delta_Scope*s,delta_reg_index dest);
    void delta_reg_make_zero(Delta_Scope* s,delta_reg_index reg);
    void delta_reg_sub(Delta_Scope*s,delta_reg_index reg,intptr_t toSub);

    void delta_reg_fp_move(Delta_Scope*s,delta_fp_reg_index reg,double v);
    void delta_reg_fp_copy(Delta_Scope*s,delta_fp_reg_index dest,delta_fp_reg_index src);
    void delta_reg_fp_add(Delta_Scope*s,delta_fp_reg_index dest,double v);
    intptr_t delta_reg_fp_get_val(Delta_Scope*s,delta_fp_reg_index dest);
    void delta_reg_fp_make_zero(Delta_Scope* s,delta_fp_reg_index reg);
    void delta_reg_fp_sub(Delta_Scope*s,delta_fp_reg_index reg,double toSub);
    
    void delta_copy_regs_to_real(Delta_Scope* s);
    void delta_copy_regs_from_real(Delta_Scope* s);
    #define DELTA_PUSH(s,t,v,ct) \
        do { \
            ct __Templ = v; \
            delta_push(s,t,&__Templ); \
        } while(0)
#endif
