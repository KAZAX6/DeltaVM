/* #ifndef DTHREAD_H
    #define DTHREAD_H
    #include <stddef.h>
    #include <stdint.h>
    typedef struct DeltaVM_t DeltaVM_t; 
    typedef struct DeltaVM_Thread Delta_VM_Thread_t;

    * @brief create a new coroutine, coroutine not started
    *
    * @param stacksize pages of coroutine stack
    * @param v Virtual Machine context
    *
    * @return pointer to new coroutine
    * @retval NULL if fail
    * @retval not-NULL if success
    Delta_VM_Thread_t* delta_thread_new(size_t stacksize,DeltaVM_t* v);

    * @brief wait coroutine end while time t
    *
    * @param th pointer on coroutine
    * @param t time for join
    * @return 1 if ended, 0 if running
    int delta_thread_join(Delta_VM_Thread_t* th,uint64_t t);

    * @brief running new coroutine
    *
    * @param t pointer on coroutine
    * @param fstart start value of register RIP
    void delta_thread_run(Delta_VM_Thread_t* t,intptr_t fstart);

    * @brief force switch of current thread to next
    * 
    void delta_thread_yield();

    * @brief locking thread t
    *
    * @param t pointer on coroutine
    void delta_thread_lock(Delta_VM_Thread_t* t);

    * @brief unlocking thread t
    *
    * @param t pointer on coroutine
    void delta_thread_unlock(Delta_VM_Thread_t* t);

    * @brief freeing coroutine and set pointer on NULL
    *
    * @param t pointer on pointer on coroutine

    void delta_thread_free(Delta_VM_Thread_t** t);

    * @brief end coroutine
    *
    * @param t pointer on coroutine
    void delta_thread_end(Delta_VM_Thread_t* t);

    * @brief add priotity to coroutine priority or reset
    *
    * @param t pointer on coroutine
    * @param c count of priority

    void delta_thread_boost(Delta_VM_Thread_t* t,size_t c);
#endif */