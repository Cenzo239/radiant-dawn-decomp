/* fn_80214C00 (0x424), round 20 state: `other`. 265 of 265 instructions, same order and registers.
 * Fix over wip/fn_80214C00.cpp (a real gap of the old draft, 257 instructions): the two "add every unit
 * except x" loops pass a functor object {empty op; void* x} BY VALUE (struct F2 with a nested empty
 * member, which keeps it in memory), so the original's stack copies are now present.
 * The ONLY remaining difference: in each of the two calls the functor and its by-value copy sit in
 * swapped 8-byte slots (original: functor 0x20 / copy 0x18, then 0x10 / 0x8; ours: 0x18 / 0x20, then
 * 0x8 / 0x10). Functionally equal. Tried: temporary vs named functor, by-reference and by-value
 * wrapper levels (these give functor, functor, copy, copy), a named copy in the inner inline (copies
 * bytewise). */
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
struct E0 {};
struct F2 { E0 op; void* x; F2(void* v) : x(v) {} };
static inline void each2(Lst* l, void* u, F2 f) {
    for (; u != NULL; u = *(void**)((u8*)u + 0xe8)) {
        if (u != f.x) l->v30(u);
    }
}
static inline void addH(Lst* l, void* u, void* x) {
    F2 f(x);
    if (u != NULL) each2(l, u, f);
}
static inline void addI(Lst* l, void* u, void* x) {
    if (u != NULL) each2(l, u, F2(x));
}
static inline void each3(Lst* l, void* u, F2 f) {
    if (u != NULL) each2(l, u, f);
}
static inline void addJ(Lst* l, void* u, void* x) {
    each3(l, u, F2(x));
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
    addH((Lst*)s->a48, lbl_804CB814[0], x);
    addH((Lst*)s->a48, lbl_804CB814[0xf], x);
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
