#include "game/auto/m2c_prelude.h"
#if TARGET_PC
/* Host: SID string in, skill record out; the m2c draft dropped the tail-call result */
void* fn_80076F54(const char*);

void* fn_8010B23C(const char* arg0) {
    return fn_80076F54(arg0);
}
#else
M2C_UNK fn_80076F54(s32);

void fn_8010B23C(s32 arg0) {
    fn_80076F54(arg0);
}
#endif
