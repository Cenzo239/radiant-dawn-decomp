/* Scroll offset for the map view. */
#include "game/rL_80133EB4/types.h"
struct P14 { u8 pad[8]; f32 x8, xc; };
struct C5 { u8 pad[0x14]; P14* x14; };
extern "C" {
extern f32 lbl_804CB854, lbl_804CB858;
void fn_80143374(void* a, void* b, C5* c) {
    f32 k = lbl_804CB854;
    f32 n = lbl_804CB858;
    P14* p = c->x14;
    f32 m = -n;
    p->x8 = k;
    p->xc = m;
}
}
