#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
struct XY { s16 x, y; };
struct S48 { u8 p[0x44]; void* a44; L84* a48; };
static inline L6C* newL6C(s16 x0, s16 a26) {
    L6C* o = (L6C*)fn_80079150(0x6c);
    if (o != NULL) {
        l6cInit(o, x0, 0x45, x0 + 0x108, 0x17f, 0x108, 0x13a, a26, 0x10);
        o->w.vt = lbl_8038F548;
        ((Lst*)o)->v2C();
    }
    return o;
}
extern "C" {
void fn_80215490(S48* s) {
    void* x = fn_801E7A28(s->a48);
    L6C* o = newL6C(0x18c, 0x1cc);
    o->w.id = 0x85;
    o->w.a28 = 8;
    o->a40 = x;
    fn_801E5448(s, o);
    {
        XY p;
        p.x = 0x138;
        p.y = 0x45;
        fn_801E459C(s, o, &p, 1);
    }
}
}
