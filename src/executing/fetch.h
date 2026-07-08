#ifndef _DEL_FETCH
    #define _DEL_FETCH
    #include <stdint.h>
    #include "../../include/Delta-Op.h"
    #include "../../include/DeltaVM-Core.h"
    static DeltaVM_Opcode_t __fetch(uint8_t* bytes) {
        DeltaVM_Opcode_t op;
        if (__builtin_expect(bytes[0] == MODE_TO_UINT8(OP_MODE_IMM),1)) {
            op.type = 0;
        } else if (__builtin_expect(bytes[0] == MODE_TO_UINT8(OP_MODE_REG),0)) {
            op.type = 1;
        } else if (__builtin_expect(bytes[0] == MODE_TO_UINT8(OP_MODE_REG_MEM),0)) {
            op.type = 2;
        } else if (__builtin_expect(bytes[0] == MODE_TO_UINT8(OP_MODE_MEM_REG),0)) {
            op.type = 3;
        }
        op.op   = bytes[1];
        op.dest = bytes[2];
        uint64_t src = 0;
        __builtin_memcpy(&src,&(bytes[3]),8);
        src = __builtin_bswap64(src);
        op.src = src;
        return op;
    }
    static inline _Bool __cmp_opcodes(DeltaVM_Opcode_t a,DeltaVM_Opcode_t b) {
        return ((a.type == b.type) && (a.op == b.op) && (a.dest == b.dest) && (a.src == b.src));
    }
#endif