#include "game/auto/m2c_prelude.h"
#if TARGET_PC
/* Host: the name is a pointer and the loaded data is returned (tail call). */
void* fn_8023BF78(const char*, s32);

void* fn_8023F1A4(const char* arg0, s32 arg1) {
    return fn_8023BF78(arg0, arg1);
}
#else
M2C_UNK fn_8023BF78(s32, s32);

void fn_8023F1A4(s32 arg0, s32 arg1) {
    fn_8023BF78(arg0, arg1);
}
#endif
