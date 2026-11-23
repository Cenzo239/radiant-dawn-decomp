#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005F424(ObjB4* a, MenuEntry* m) {
    Color4 c;
    if (m->active == 2) {
        c = *fn_800CD204(0);
        fn_80080508(&c);
    } else if (a->b4) {
        Color4 c2 = *fn_800CD204(0x13);
        fn_80080508(&c2);
    } else {
        Color4 c3 = *fn_800CD204(1);
        fn_80080508(&c3);
    }
}
