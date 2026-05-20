#include "include/structs.h"
#include <stdlib.h>
static Delta_Scope* global = NULL;
Delta_Scope* delta_run(void) {
    Delta_Scope* new_scope = calloc(1, sizeof(Delta_Scope));
    if (!new_scope) return NULL;
    if (!global) {
        global = new_scope;
        new_scope->global = NULL;
    } else {
        new_scope->global = global;
    }
    return new_scope;
}
Delta_Scope* delta_global() {
    return global;
}
void delta_end(void) {
    
}
