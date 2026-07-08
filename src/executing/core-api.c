#include "../Struct.h"
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
    #include <sys/mman.h>
#else
    #include <windows.h>
#endif
void __ende(DeltaVM_t* v) ;
DeltaVM_t* delta_new(void) {
    DeltaVM_t* v = calloc(1,sizeof(DeltaVM_t));
    return v;
}
void delta_free(DeltaVM_t** v) {
    if (!v || !(*v)) return;
    __ende(*v);
        uint64_t l = (uint64_t)
        ((uint8_t*)(*v)->pool_max - (uint8_t*)(*v)->pool);
    #ifndef _WIN32
        if ((*v)->maped)
            munmap((*v)->file,(*v)->l);
        munmap((void*)(*v)->stack,2048*4096);
        munmap((*v)->pool,l);
    #else
        if ((*v)->maped)
            VirtualFree((*v)->file,0,MEM_RELEASE);
        VirtualFree((void*)(*v)->stack,0,MEM_RELEASE);
        VirtualFree((*v)->pool,0,MEM_RELEASE);
    #endif
    memset(*v,0,sizeof(DeltaVM_t));
    free(*v);
    *v = NULL;
}