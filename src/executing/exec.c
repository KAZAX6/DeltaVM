#include "fns.h"
#include "fetch.h"
static void* table[0x25] = {0};
static int table_f = 0;
typedef int (*fn_t)(DeltaVM_t*,uint64_t,uint64_t,int);
static int __jifh(DeltaVM_t* v,uint64_t dest,uint64_t src,int m) {
    Delta_Reg_t r1 = dest;
    Delta_Reg_t r2 = src >> 56;
    uint64_t pos = src & ~0xFF00000000000000;
    return __jif(v,r1,r2,pos);
}
static int __jifnh(DeltaVM_t* v,uint64_t dest,uint64_t src,int m) {
    Delta_Reg_t r1 = dest;
    Delta_Reg_t r2 = src >> 56;
    uint64_t pos = src & ~0xFF00000000000000;
    return __jifn(v,r1,r2,pos);
}
static int __eifh(DeltaVM_t* v,uint64_t dest,uint64_t src,int m) {
    Delta_Reg_t r1 = dest;
    Delta_Reg_t r2 = src >> 56;
    uint64_t pos = src & ~0xFF00000000000000;
    return __eif(v,r1,r2,pos);
}
static int __poph(DeltaVM_t* v,uint64_t dest,uint64_t src,int m) {
    delta_set_reg(v,dest,__pop(v,0,0,0),0);
    return 1;
}
static void __init_table(void) {
    if (!table_f) {
        table[OP_PUSH] = __push;
        table[OP_POP]  = __poph;
        table[OP_MOV]  = __mov;
        table[OP_ADD]  = __add;
        table[OP_SUB]  = __sub;
        table[OP_MUL]  = __mul;
        table[OP_DIV]  = __div;
        table[OP_JMP]  = __jmp;
        table[OP_JIF]  = __jifh;
        table[OP_EIF]  = __eifh;
        table[OP_JIFN] = __jifnh;
        table[OP_AND]  = __and;
        table[OP_OR]   = __or;
        table[OP_NOT]  = __not;
        table[OP_XOR]  = __xor;
        table[OP_CALL] = __call;
        table[OP_RET]  = __ret;
        table[OP_ENDE] = __ende;
        table[OP_COPY] = __copy;
        table[OP_PRT] = __print;
        table[OP_ALC] = __alc;
        table_f = 1;
    }
}
void __exec_op(DeltaVM_t* v,DeltaVM_Opcode_t* op) {
    fn_t fn = (fn_t)table[op->op];
    fn(v,op->dest,op->src,op->type);
}
void __exec(DeltaVM_t* v,uint8_t* bf) {
    __init_table();
    DeltaVM_Opcode_t op = __fetch(bf);
    __exec_op(v,&op);
}