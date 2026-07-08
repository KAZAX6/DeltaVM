#include <stdint.h>
typedef struct {
    char magic[8];
    uint64_t start;
    uint64_t symtab;
} header_t;

int __check(void* f) {
    header_t* h = f;
    char origm[8] = {'\0','D','B','I','N','\0','\0','\n'};
    for (int i = 0;i < 8;i++) 
        if (h->magic[i] != origm[i]) return 0;
    return 1;
}