#ifndef DELTA_SCRIPT_TVALUE
    #define DELTA_SCRIPT_TVALUE
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
    #include <stddef.h>
    #include "canary.h"
    typedef struct TValue {
        CANARY_P1
        void* data;
        delta_types _t;
        CANARY_P2
    } TValue;
    const char* tvalue_type(TValue* t);
    size_t tvalue_sizeof(TValue* v);
#endif