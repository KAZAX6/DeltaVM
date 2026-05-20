#include <stdlib.h>
extern void vm_panic(int exc);
#define HEAP_PTR_LIMIT 2
void test_heap() {
    void* ptrs[5];
    for (int i = 0; i < 5; i++) {
        ptrs[i] = malloc(1);
    }

    int repeats = 1;
    for (int i = 1; i < 5; i++) {
        if (ptrs[i] == ptrs[i - 1]) {
            repeats++;
            if (repeats > HEAP_PTR_LIMIT) {
                vm_panic(0);
            }
        } else {
            repeats = 1;
        }
    }
    for (int i = 0;i < 4;i++)
        free(ptrs[i]);
}
