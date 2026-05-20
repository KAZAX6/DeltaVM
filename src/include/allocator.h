#ifndef AURORA_ALLOCATOR
    #define AURORA_ALLOCATOR
    #include <stddef.h>
    typedef struct allocator allocator_t;

    allocator_t* allocator_get(size_t pages,size_t elem_size);
    size_t allocator_max(allocator_t* al);
    void* allocator_allocate(allocator_t* a);
    void allocator_free(allocator_t** a);
#endif