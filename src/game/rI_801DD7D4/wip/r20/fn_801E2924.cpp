/* fn_801E2924 (0x4CC): draws a widget's sprite at its absolute position (own position plus the parent
 * chain's), with scale/alpha/brightness multiplied up the parent chain. Sibling of fn_801E2424.
 * State: `other`. 307 of 307 instructions, same order, same registers. The ONLY difference is the order of
 * the 13 four-byte point locals in the frame: the original's slot X (0x10..0x40) is our slot 0x50-X
 * (mirror image); the two innermost temporaries (0x8, 0xc) and everything else agree. Functionally equal.
 * Tried for the slot order: inline_bottom_up on/off, a wrapper inline for level 0, by-reference result,
 * real recursion on fn_801E2204 (only inlined into a caller under `#pragma inline_bottom_up off`, and then
 * the depth limit cuts the last level differently from the original), deferred (inline) emission.
 * L2/L3/L4 are hand-expanded levels of fn_801E2204 (W::absPos); a port should call that function. */
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
#pragma inline_depth(30)
#pragma inline_max_size(4000)
extern "C" Pu* fn_801E2204(const W*, Pu*, const Pu*);
static inline void L4(const W* o, Pu* out, const Pu* in) {
    Pu p;
    p.x = o->pos.x;
    p.y = o->pos.y;
    W* w = o->parent;
    if (w) fn_801E2204(w, &p, &p);
    Pu t = fn_801E32C8(fn_801E32C8(p, o->ofs), *(Pt*)in);
    out->x = (s16)t.x; out->y = (s16)t.y;
}
static inline void L3(const W* o, Pu* out, const Pu* in) {
    Pu p;
    p.x = o->pos.x;
    p.y = o->pos.y;
    W* w = o->parent;
    if (w) L4(w, &p, &p);
    Pu t = fn_801E32C8(fn_801E32C8(p, o->ofs), *(Pt*)in);
    out->x = (s16)t.x; out->y = (s16)t.y;
}
static inline void L2(const W* o, Pu* out, const Pu* in) {
    Pu p;
    p.x = o->pos.x;
    p.y = o->pos.y;
    W* w = o->parent;
    if (w) L3(w, &p, &p);
    Pu t = fn_801E32C8(fn_801E32C8(p, o->ofs), *(Pt*)in);
    out->x = (s16)t.x; out->y = (s16)t.y;
}
static inline void L1(const W* o, Pu* out, const Pu* in) {
    Pu p;
    p.x = o->pos.x;
    p.y = o->pos.y;
    W* w = o->parent;
    if (w) L2(w, &p, &p);
    Pu t = fn_801E32C8(fn_801E32C8(p, o->ofs), *(Pt*)in);
    out->x = (s16)t.x; out->y = (s16)t.y;
}
extern "C" void fn_801E2924(W* o) {
    f32 sx, sy;
    Pu p;
    p.x = ((const W*)o)->pos.x;
    p.y = ((const W*)o)->pos.y;
    if (o->parent) L2(o->parent, &p, &p);
    Pu q = fn_801E32C8(p, ((const W*)o)->ofs);
    int hw = (s16)(((s16)(o->xe_ - (s16)o->pos.x) >> 1) - ((const W*)o)->ofs.x);
    int hh = (s16)(((s16)(o->x10_ - (s16)o->pos.y) >> 1) - ((const W*)o)->ofs.y);
    int qy = (s16)q.y;
    fn_8007E154();
    {
    f32 a1, a2, a3, a4, s1;
    CHAIN(s1, o, fn_801E3300, x2c, a1, a2, a3, a4);
    sx = s1;
    f32 b1;
    CHAIN(b1, o, fn_801E3300, x2c, b1, a4, a3, a2);
    sy = b1;
    }
    fn_8007E5C0((s16)q.x, qy, o->x26, hw, hh, sx, sy, 0.0f);
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
