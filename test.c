#include "include/DeltaVM-Core.h"
#undef __cplusplus
#include "src/Struct.h"
#include <signal.h>
#include <DeltaVM/DeltaVM.h>
#include <luajit-2.1/lauxlib.h>
#include <luajit-2.1/lualib.h>
#include <luajit-2.1/lua.h>
#include <luajit-2.1/luajit.h>
#include <python3.14/Python.h>
#include <time.h>
#include <stdio.h>
#define ITER 500000
void* arr[SIGINT];
static inline double ts_diff(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) + (b.tv_nsec - a.tv_nsec) / 1e9;
}
void handler(int s) {
    DeltaVM_t* v = arr[s - 1];
    delta_prt_trace(v);
    delta_free(&v);
    raise(SIGABRT);
}
int main() {
    struct timespec start, end;
    signal(SIGINT,handler);
    /* ============================
       Python benchmark
       ============================ */
    Py_Initialize();
    PyObject* code = Py_CompileString(
        "i = 0\nfor _ in range(500000): i += 1\n",
        "<bench>", Py_file_input
    );
    PyObject* globals = PyDict_New();
    clock_gettime(CLOCK_MONOTONIC, &start);
    PyEval_EvalCode(code, globals, globals);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Python: %.6f sec\n", ts_diff(start, end));
    Py_Finalize();
/* ============================
   LuaJIT benchmark
   ============================ */
lua_State* L = luaL_newstate();
if (!L) return 1;
// НЕ вызываем luaL_openlibs — в LuaJIT это может не работать или быть другим
// Если очень нужны стандартные либы, можно вручную подключить только нужные,
// но для цикла "i = i + 1" они не нужны.

const char* lua_code =
    "local i = 0\n"
    "for _ = 1, 500000 do\n"
    "    i = i + 1\n"
    "end\n";

if (luaL_loadstring(L, lua_code) != 0) {
    fprintf(stderr, "LuaJIT load error: %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
}

clock_gettime(CLOCK_MONOTONIC, &start);
// В LuaJIT лучше использовать lua_pcall напрямую; lua_pcallk — это внутренняя деталь
if (lua_pcall(L, 0, 0, 0) != 0) {
    fprintf(stderr, "LuaJIT run error: %s\n", lua_tostring(L, -1));
    lua_close(L);
    return 1;
}
clock_gettime(CLOCK_MONOTONIC, &end);

printf("LuaJIT: %.6f sec\n", ts_diff(start, end));
lua_close(L);

    /* ============================
       DVM benchmark
       ============================ */
    DeltaVM_t* vm = delta_new();
    arr[SIGINT - 1] = vm;
    uint64_t src = ((uint64_t)REG_R1 << 56) | (uint64_t)35;
    uint8_t byte[] = {
        DBIN_MAGIC,
        0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        U64_TO_BE_BYTES(0),
        MODE_TO_UINT8(OP_MODE_IMM),OP_MOV,REG_R1,U64_TO_BE_BYTES(ITER),
        MODE_TO_UINT8(OP_MODE_IMM),OP_ADD,REG_R0,U64_TO_BE_BYTES(1),
        MODE_TO_UINT8(OP_MODE_IMM),OP_JIFN,REG_R0,U64_TO_BE_BYTES(src),
        MODE_TO_UINT8(OP_MODE_REG),OP_ENDE,0,U64_TO_BE_BYTES(0)
    };
    delta_load(vm,byte,sizeof(byte),1);
    clock_gettime(CLOCK_MONOTONIC, &start);
    delta_run(vm, 4096);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("DVM: %.6f sec\n", ts_diff(start, end));
    delta_free(&vm);
    return 0;
}
