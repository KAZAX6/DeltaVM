
#include <string.h>
#include "../Struct.h"
typedef struct {
    char* sym;
    uint64_t addr;
    uint64_t len;
} DeltaSym_t;
DeltaSym_t __sym(DeltaVM_t* v,size_t addr) {
    DeltaSym_t s = {0};
    char* sym = v->symtab;
    while (*sym != '\0') {
        size_t l = strlen(sym);
        uint64_t adr = *(uint64_t*)(sym + l + 1);
        if (adr == addr) {
            s.addr = adr;
            s.len = *(uint64_t*)(sym + l + (1 + 8));
            s.sym = sym;
            break;
        }
        sym += l + (1 + 8 + 8);
    }
    return s;
}
