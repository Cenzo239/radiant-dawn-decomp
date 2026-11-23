#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_80062A7C(NameTable* t, s16 v) {
    t->hb8 += v;
}

extern "C" void fn_80062A8C(NameTable* t, s16 v) {
    t->hba += v;
}

extern "C" void* fn_80062A9C(GameData* g, u32 k) {
    if (k == 0) {
        return (u8*)g + 0x134;
    }
    if (k == 3) {
        return (u8*)g + 0x13c;
    }
    fn_8010E7F4(lbl_804CB558, 1);
    return lbl_804CB558;
}
