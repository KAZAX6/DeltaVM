
#ifndef DELTA_VM_OPCODES_H
#define DELTA_VM_OPCODES_H
#define OP_PUSH     0x01
#define OP_POP      0x02
#define OP_GETTOP   0x03
#define OP_SETTOP   0x04
#define OP_REMOVE   0x05
#define OP_MOV      0x06
#define OP_DECL_VAR 0x10
#define OP_SET_VAL  0x11
#define OP_GET_VAL  0x12
#define OP_ADD      0x20
#define OP_SUB      0x21
#define OP_MULT     0x22
#define OP_DIV      0x23
#define OP_MOD      0x24
#define OP_ALLOC    0x30
#define OP_FREE     0x31
#define OP_DEFERENCE 0x32
#define OP_CALL     0x40
#define OP_RET      0x41
#define OP_JMP      0x50
#define OP_JMP_IF   0x51
#define OP_JMP_IFN  0x52
#define OP_STRUCT_DEFINE 0x60
#define OP_STRUCT_NEW    0x61
#define OP_STRUCT_GET    0x62
#define OP_STRUCT_SET    0x63
#define OP_ARR_NEW   0x70
#define OP_ARR_GET   0x71
#define OP_ARR_SET   0x72
#define OP_PRINT    0x80
#define OP_DECL_FN  0x90
#define OP_ENTRY    0x100
#define OP_EQUAL    0x110
#define OP_NOT      0x111
#define OP_AND      0x112
#define OP_OR       0x113
#define OP_GREATER  0x114
#define OP_LESS     0x115
#define OP_XOR      0x116
#define OP_ALIAS    0x120
#endif