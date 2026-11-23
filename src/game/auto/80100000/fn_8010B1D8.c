#include "game/auto/m2c_prelude.h"
#if TARGET_PC
/* Host: PID string in, person struct out (pointers, not s32) */
void* fn_80076F54(const char*);

void* fn_8010B1D8(const char* arg0) {
    return fn_80076F54(arg0);
}
#else
M2C_UNK fn_80076F54(s32);

s32 fn_8010B1D8(s32 arg0) {
    return fn_80076F54(arg0);
}
#endif
