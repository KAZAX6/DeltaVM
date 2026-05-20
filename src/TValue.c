#include "include/TValue.h"
#include "include/canary.h"
#include <stddef.h>
#include <stdint.h>

#define COUNT_S(a) (sizeof(a) / sizeof((a)[0]))

static const size_t sizes[] = {
    sizeof(int8_t),
    sizeof(int16_t),
    sizeof(int32_t),
    sizeof(int64_t),
    sizeof(uint8_t),
    sizeof(uint16_t),
    sizeof(uint32_t),
    sizeof(uint64_t),
    sizeof(void*),
    sizeof(char*),
    sizeof(double)
};

static const char* const types[] = {
    "char",
    "short",
    "int",
    "long long",
    "unsigned char",
    "unsigned short",
    "unsigned int",
    "unsigned long long",
    "ptr",
    "str",
    "double"
};

static inline int valid_type(int t) {
    return t >= 0 && t < (int)COUNT_S(types);
}

const char* tvalue_type(TValue* t) {
    CHECK_STRUCT(*t);
    if (!t || !valid_type(t->_t))
        return NULL;
    return types[t->_t];
}

size_t tvalue_sizeof(TValue* v) {
    CHECK_STRUCT(*v);
    if (!v  || !valid_type(v->_t))
        return 0;
    return sizes[v->_t];
}
