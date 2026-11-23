#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_8010DF10(void* l, int n);
void fn_8010E27C(void* a, void* u);
void fn_8010E168(void* l, void* u);
}
typedef struct UFull2 { u8 pad[0xe8]; struct UFull2* nextE8; u8 padec[8]; UnitSub* f4; u8 padf8[0x10c-0xf8]; u32 flags; } UFull2;
extern "C" void fn_80058094(void) {
    UFull2* l[6];
        UFull2* nx;
    UFull2* n3;
    UFull2* u;
    UFull2* u2;
    UFull2* n2;
    u32 f;
    UFull2* u3;

    fn_8010DF10(l, 0);
    for (u = *(UFull2**)lbl_804CB814; u; u = nx) {
        nx = u->nextE8;
        if (!(u->flags & 0x10000dcULL)) {
            fn_8010E27C(u->f4, u);
            fn_8010E168(l, u);
        }
    }
    for (u2 = *(UFull2**)lbl_804CB814; u2; u2 = n2) {
        n2 = u2->nextE8;
        if (!(u2->flags & 0x10000dcULL)) break;
        fn_8010E27C(u2->f4, u2);
        fn_8010E168(l, u2);
        u2->flags |= 0x10000dcULL;
    }
    for (u3 = l[0]; u3; u3 = n3) {
        f = u3->flags & 0x10000dcULL;
        n3 = u3->nextE8;
        fn_8010E27C(u3->f4, u3);
        fn_8010E168(lbl_804CB814, u3);
        if (f) {
            u3->flags |= 0x10000dcULL;
        }
    }
}
