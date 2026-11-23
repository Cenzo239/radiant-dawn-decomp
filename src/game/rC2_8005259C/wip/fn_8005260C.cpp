/* NEAR MISS: fn_8005260C, 11 of 47 words. Only &lbl_803CAB38 is materialised too late (lis r5 / addi r3,r5 expected around the 0x33 test). */
#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

static inline void* slotGet(GameData* const& g) {
    u32 k = 3;
    if (lbl_804CB3F8 == 0x33) {
        k = 0;
    }
    return fn_80062A9C(g, k);
}
static inline int slotColor(void) {
    int n = 6;
    if (lbl_804CB3F8 == 0x33) {
        n = 7;
    }
    return n;
}

extern "C" void fn_8005260C(Cmd0* c) {
    u8* q = (u8*)slotGet(&lbl_803CAB38);
    if (q) {
        u8 b = q[4];
        if (b == (u8)c->v58()) {
            Color4 col = *fn_800CD204(slotColor());
            fn_80080508(&col);
        }
    }
}
