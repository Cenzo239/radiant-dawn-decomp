#include "game/rI_801DD7D4/fn_wf.h"
/* Creates the talk list window. */
struct L78 { WF w; int a40; LN l44; int a4c; int a50; u8 a54; s16 a56, a58, a5a, a5c; f32 a60; u8 p64[8]; int a6c; LN l70; };
extern "C" {
extern u8 lbl_80390EF4[];
void fn_8024044C(L78*);
void fn_80241F3C(void* parent) {
    L78* o = (L78*)fn_80079150(0x78);
    if (o) {
        gInit((G40*)o, 0x58, 0x6F, 0x208, 0x167, 0x1B0, 0xF8, 500, 0x10);
        o->w.vt = lbl_80390EF4;
        o->a4c = 0;
        o->a50 = 0;
        o->a54 = 1;
        o->a56 = 0;
        o->a58 = -0x8000;
        o->a5a = -0x8000;
        o->a5c = 0;
        o->a60 = 0.0f;
        o->a6c = 0;
        LN* l = &o->l70; l->next = l; l->prev = l; ((Lst*)o)->v2C();
        fn_8024044C(o);
    }
    o->w.id = 0x81;
    o->w.flags |= 0x10;
    fn_801E5448(parent, o);
}
}
