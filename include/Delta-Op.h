#ifndef DVM_OP_H
    #define DVM_OP_H
    #define OP_PREF_NONE 0x0000
    // RESERVED :: #define OP_PREF_ATOM 0x0100 // 
    #define OP_MODE_IMM  0x0000
    #define OP_MODE_REG      0x1000
    #define OP_MODE_MEM_REG  0x2000
    #define OP_MODE_REG_MEM  0x4000
    #define MODE_TO_UINT8(m) m >> 8
    #define U64_TO_BE_BYTES(x) \
        (uint8_t)(((uint64_t)(x) >> 56) & 0xFF), \
        (uint8_t)(((uint64_t)(x) >> 48) & 0xFF), \
        (uint8_t)(((uint64_t)(x) >> 40) & 0xFF), \
        (uint8_t)(((uint64_t)(x) >> 32) & 0xFF), \
        (uint8_t)(((uint64_t)(x) >> 24) & 0xFF), \
        (uint8_t)(((uint64_t)(x) >> 16) & 0xFF), \
        (uint8_t)(((uint64_t)(x) >>  8) & 0xFF), \
        (uint8_t)(((uint64_t)(x) >>  0) & 0xFF)  \
    
    #define OP_PUSH   0x0001  //R
    #define OP_POP    0x0002  // R
    #define OP_MOV    0x0003  // R
    #define OP_ADD    0x0004  // R
    #define OP_SUB    0x0005  //R 
    #define OP_MUL   0x0006 // r
    #define OP_DIV    0x0007 // r
    #define OP_JMP    0x0008 // r
    #define OP_JIF    0x0009 // r
    #define OP_EIF    0x000A // r
    #define OP_JIFN   0x000B // r
    #define OP_AND    0x000C //r
    #define OP_OR     0x000D // r
    #define OP_NOT    0x000E // r
    #define OP_XOR    0x000F // r
    #define OP_CALL   0x0010 // r
    #define OP_RET    0x0011 // r
    #define OP_ENDE   0x0012 // r
    // RESERVED :: #define OP_TRYB   0x0013 :: RESERVED //
    // RESERVED :: #define OP_CTCH   0x0014 :: RESERVED //
    // RESERVED :: #define OP_THRW   0x0015 :: RESERVED //
    // RESERVED :: #define OP_NCO    0x0016 :: RESERVED //
    // RESERVED :: #define OP_RCO    0x0017 :: RESERVED //
    // RESERVED :: #define OP_YCO    0x0018 :: RESERVED //
    // RESERVED :: #define OP_JCO    0x0019 :: RESERVED //
    // RESERVED :: #define OP_ECO    0x001A :: RESERVED //
    #define OP_COPY   0x001B // r
    // RESERVED :: #define OP_COPY16 0x001C :: RESERVED // 
    // RESERVED :: #define OP_COPY32 0x001D :: RESERVED // 
    #define OP_PRT    0x001E
    #define OP_ALC    0x001F
    // RESERVED :: #define OP_USE    0x0022 :: RESERVED // 
    // RESERVED :: #define OP_NTC    0x0023 :: RESERVED // 
    // RESERVED :: #define OP_ULD    0x0024 :: RESERVED // 
    // RESERVED :: #define OP_MCA    0x0025 :: RESERVED // 
#endif