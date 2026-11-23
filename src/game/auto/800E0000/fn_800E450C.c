#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_80081A90(void*);
s32 fn_800E450C(u8 *arg0) {
    if (*(s32*)(*(u8**)(arg0 + 0x30) + 0x18) & 0x08000000) {
        return 0;
    }
    fn_80081A90(arg0);
    return 0;
}
