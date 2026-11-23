#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_80081A90(void*, void*);
s32 fn_80104A70(u8 *arg0, u8 *arg1) {
    if (*(u32*)(arg0 + 0x30) == *(u32*)(arg1 + 0x30)) {
        fn_80081A90(arg0, arg1);
    }
    return 0;
}
