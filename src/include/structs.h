#ifndef DELTA_STRUCTS
#define DELTA_STRUCTS
#include "canary.h"
#include "TValue.h"
#include "dict.h"
#include <stdbool.h>
#include <stdint.h>
typedef struct Delta_Scope Delta_Scope;
typedef enum {
    DELTA_FN_BYTECODE,
    DELTA_FN_NATIVE
} Delta_FunctionType;
typedef struct {
    CANARY_P1
    uint64_t v64[16];
    double vf64[16];
    CANARY_P2
} Delta_Regs;
typedef struct {
    CANARY_P1
    Delta_FunctionType t;
    const uint32_t* bytecode;
    size_t bytecode_ln;
    void(*cfn)(Delta_Scope*);
    const char* fn_name;
    CANARY_P2
} Delta_Function;
typedef struct {
    CANARY_P1
    TValue* stack;
    size_t cap;
    size_t size;
    CANARY_P2
} Delta_Stack;
typedef struct {
    CANARY_P1
    TValue* array;
    size_t size;
    size_t cap;
    int elem_t;
    CANARY_P2
} Delta_Array;
typedef struct {
    CANARY_P1
    const char* name;
    size_t field_count;
    char** field_names;
    int* field_types;
    size_t* field_offsets;
    size_t size;
    CANARY_P2
} Delta_Struct;
struct Delta_Module{
    CANARY_P1
#ifndef _WIN32
    void* handle;
#else
    HMODULE handle;
#endif
    Delta_Scope* s;
    const char* name;
    bool loaded;
    CANARY_P2
};
typedef struct _Frame {
    CANARY_P1
    struct _Frame* next;
    struct _Frame* prev;
    Delta_Stack s;
    Delta_Function* curr;
    Delta_Scope* sc;
    size_t pc;
    uint64_t retadress;
    CANARY_P2
} Delta_Frame;
struct Delta_Scope {
    CANARY_P1
    Delta_Regs* rs;
    struct Delta_Scope* next;
    struct Delta_Scope* prev;
    Delta_Frame* frames;
    Delta_Frame* curr;
    dict_t* vars;
    dict_t* arrays;
    dict_t* structs;
    dict_t* functions;
    dict_t* modules;
    bool exceprion;
    char* exception_msg;
    struct Delta_Scope* global;
    CANARY_P2
};

#endif
