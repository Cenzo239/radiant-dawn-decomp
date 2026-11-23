#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
struct XY { s16 x, y; };
struct F { int a; void* x; };
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
static inline L84* newL88(void) {
    L84* o = (L84*)fn_80079150(0x88);
    if (o != NULL) {
        l84Init(o, 0x18c, 0x45, 0x294, 0x17f, 0x108, 0x13a, 0x1d6, 0x10);
        o->w.vt = lbl_8038CC9C;
        o->a84 = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
static inline void addEx2(Lst* l, void* u, F f) {
    for (; u != NULL; u = *(void**)((u8*)u + 0xe8)) {
        if (u != f.x) l->v30(u);
    }
}
static inline void addEx(Lst* l, void* u, F f) {
    if (u != NULL) addEx2(l, u, f);
}
static inline void addF(Lst* l, void* u, void* x) {
    F f;
    f.x = x;
    addEx(l, u, f);
}
static inline void addG(Lst* l, void* u, void* x) {
    F c;
    F f;
    f.x = x;
    if (u != NULL) {
        c.a = f.a;
        c.x = f.x;
        for (; u != NULL; u = *(void**)((u8*)u + 0xe8)) {
            if (u != c.x) l->v30(u);
        }
    }
}
extern "C" {
void fn_80214C00(S48* s) {
    void* x = fn_801E7A28(s->a44);
    {
        L6C* o = newL6C(-0x34, 0x1d6);
        o->w.id = 0x84;
        o->w.a28 = 8;
        o->a40 = x;
        fn_801E5448(s, o);
    }
    {
        L84* r = newL88();
        s->a48 = r;
        if (r != NULL) r->w.rc++;
    }
    s->a48->w.id = 0x82;
    s->a48->w.a28 = 8;
    addG((Lst*)s->a48, lbl_804CB814[0], x);
    addG((Lst*)s->a48, lbl_804CB814[0xf], x);
    s->a48->a84 = x;
    fn_801E5448(s, s->a48);
}
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
