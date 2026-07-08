#ifndef DELTA_DEBUG_H
    #define DELTA_DEBUG_H
    typedef struct DeltaVM_t DeltaVM_t;
    void delta_step(DeltaVM_t* v);
    void delta_prt_trace(DeltaVM_t* v);
#endif