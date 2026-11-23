#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_800531D8(void) {
    GameData* g = &lbl_803CAB38;
    s8 y;
    s8 x;
    y = g->f938;
    x = g->f934;
    fn_800454A8(&lbl_803CA870, x, y);
    y = g->f938;
    x = g->f934;
    fn_800620A8(g, x, y);
}

extern "C" void fn_80053298(void* p) {
    u8 a = lbl_803CA870.b0c;
    if (a != 0x25 && a != 0x2e) {
        fn_80253EE4(lbl_80361B8C + 0x9a, 0.0f);
        fn_80044E3C(p);
    }
}
