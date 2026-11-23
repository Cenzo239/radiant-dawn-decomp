#include "game/rI_801DD7D4/types.h"
struct Pt { s16 x, y; };
struct Pu { u16 x, y; };
struct W;
extern "C" {
Pu fn_801E32C8(const Pu& a, const Pt& b) {
    Pu r = a;
    r.x = (s16)r.x + b.x;
    r.y = (s16)r.y + b.y;
    return r;
}
f32 fn_801E3300(W*);
f32 fn_801E33B4(W*);
f32 fn_801E3468(W*);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, int);
void fn_8007E5C0(f32, f32, f32, f32, f32, f32, f32, f32);
void fn_8007E7DC(int);
void fn_8007E7E8(int);
}
struct W { u8 p[0xa]; Pu pos; s16 xe_, x10_; Pt ofs; u8 p16[0x10]; s16 x26; u8 p28[4]; f32 x2c, x30, x34; u32 x38; W* parent; };
#define CHAIN(res, W0, FN, F, v1, v2, v3, v4) {     W* w1 = (W0);     v1 = w1->F;     if (w1->parent) {         W* w2 = w1->parent;         v2 = w2->F;         if (w2->parent) {             W* w3 = w2->parent;             v3 = w3->F;             if (w3->parent) {                 W* w4 = w3->parent;                 v4 = w4->F;                 if (w4->parent) v4 *= FN(w4->parent);                 v3 *= v4;             }             v2 *= v3;         }         v1 *= v2;     }     res = v1; }
#pragma use_lmw_stmw on
#pragma push
#pragma inline_depth(3)
extern "C" Pu* fn_801E2204(const W* o, Pu* out, const Pu* in) {
    Pu p;
    p.x = o->pos.x;
    p.y = o->pos.y;
    W* w = o->parent;
    if (w) fn_801E2204(w, &p, &p);
    Pu t = fn_801E32C8(fn_801E32C8(p, o->ofs), *(Pt*)in);
    out->x = (s16)t.x; out->y = (s16)t.y;
    return out;
}
#pragma pop
#pragma use_lmw_stmw off
//PRAG
struct N { Pu v; };
static inline void addR(Pu& r, const Pu& a, const Pt& b) {
    r = a;
    r.x = (s16)r.x + b.x;
    r.y = (s16)r.y + b.y;
}
static inline void as(Pu& d, const Pu& r) { d.x = (s16)r.x; d.y = (s16)r.y; }
extern "C" void fn_801E2424(W* o) {
/*P*/
    f32 c2, c3, c4;
    f32 d1, d2, d3, d4;
    f32 sx, sy;
/*E*/
    N p0, a32, a31, p4, t4, a22, a21, p3, t3, a12, a11, p2, t2, t1, p1, a42, a41;
    W* w1; W* w2; W* w3; W* w4;
    p0.v.x = ((const W*)o)->pos.x;
    p0.v.y = ((const W*)o)->pos.y;
    w1 = o->parent;
    if (w1) {
        p1.v.x = w1->pos.x; p1.v.y = w1->pos.y;
        w2 = w1->parent;
        if (w2) {
            p2.v.x = w2->pos.x; p2.v.y = w2->pos.y;
            w3 = w2->parent;
            if (w3) {
                p3.v.x = w3->pos.x; p3.v.y = w3->pos.y;
                w4 = w3->parent;
                if (w4) {
                    p4.v.x = w4->pos.x; p4.v.y = w4->pos.y;
                    if (w4->parent) fn_801E2204(w4->parent, &p4.v, &p4.v);
                    addR(a41.v, p4.v, w4->ofs);
                    addR(a42.v, a41.v, *(Pt*)&p3.v);
                    t4.v = a42.v;
                    as(p3.v, t4.v);
                }
                addR(a31.v, p3.v, w3->ofs);
                addR(a32.v, a31.v, *(Pt*)&p2.v);
                t3.v = a32.v;
                as(p2.v, t3.v);
            }
            addR(a21.v, p2.v, w2->ofs);
            addR(a22.v, a21.v, *(Pt*)&p1.v);
            t2.v = a22.v;
            as(p1.v, t2.v);
        }
        addR(a11.v, p1.v, w1->ofs);
        addR(a12.v, a11.v, *(Pt*)&p0.v);
        t1.v = a12.v;
        as(p0.v, t1.v);
    }
#define p p0.v
    fn_8007E154();
    {
    f32 a1, a2, a3, a4, s1;
    CHAIN(s1, o, fn_801E3300, x2c, a1, a2, a3, a4);
    sx = s1;
    f32 b1;
    CHAIN(b1, o, fn_801E3300, x2c, b1, a4, a3, a2);
    sy = b1;
    }
    fn_8007E5C0((s16)p.x, (s16)p.y, o->x26, (s16)(o->xe_ - o->pos.x) >> 1, (s16)(o->x10_ - o->pos.y) >> 1, sx, sy, 0.0f);
    fn_8007E174(0, (u16)(o->x38 | 2));
    {
    f32 a1,a2,a3,a4,r;
    CHAIN(r, o, fn_801E33B4, x30, a1,a2,a3,a4);
    fn_8007E7DC((u8)(int)(255.99f * r));
    }
    {
    f32 a1,a2,a3,a4,r;
    CHAIN(r, o, fn_801E3468, x34, a1,a2,a3,a4);
    fn_8007E7E8((u8)(int)(128.99f * r));
    }
    fn_8007E164();
}
