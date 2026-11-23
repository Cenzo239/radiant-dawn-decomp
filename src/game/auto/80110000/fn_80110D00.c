#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_80110D38(void* slot);

/* Set remaining uses, clearing the item slot when the low byte is zero. */
s32 fn_80110D00(s8* slot, s32 uses) {
    *(u8*)(slot + 4) = uses;
    if ((u8)uses == 0) {
        fn_80110D38(slot);
        return 1;
    }
    return 0;
}
