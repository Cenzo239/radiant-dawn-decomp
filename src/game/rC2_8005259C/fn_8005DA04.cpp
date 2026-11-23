#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005DA04(void* a, MenuEntry* e) {
    if (e->active == 2) {
        Color4 c = *fn_800CD204(0);
        fn_80080508(&c);
    } else {
        Color4 c = *fn_800CD204(((u8*)e)[0x38] != 0);
        fn_80080508(&c);
    }
}

/* Only matches when it is not the first function of the file: as the first one
 * it gets r4 instead of r5 for m->proc. */
extern "C" int fn_8005DA9C(void* a, Menu* m) {
    u8 one = 1;
    ((u8*)m->proc)[0x50] = one;
    fn_800453B4(&lbl_803CA870, 0x9a);
    lbl_804CB550 = 0x9a;
    return 5;
}
