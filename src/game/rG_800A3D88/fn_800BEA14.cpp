#include "game/rG_800A3D88/chr.h"

// Effect following a battle character.
extern "C" {
struct ChQ { u8 p[0x30]; Mdl* mdl; u8 p34[0x58 - 0x34]; s16 m58, m5a; };
struct EffC { u8 p[0x8]; u16 m8; };
struct EffN { u8 p[0xA4]; ChQ* mA4; u8 pa8[0xC4 - 0xA8]; EffC* mC4; };
struct Eff { u8 p[0x30]; EffN* m30; };
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
extern char lbl_803657E8[];
f32 fn_8001E064(int);
int fn_80007630(Mdl*, const char*);
void fn_800B4000(ChQ*, int, VU*, int, int);
void fn_800E48C8(Eff*, Vec*);
void fn_800E49AC(Eff*, f32);
static inline int Node(ChQ* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
void fn_800BEA14(Eff* e) {
    Vec out, b, d;
    W3 arg;
    VU q1, t, q2;
    ChQ* c = e->m30->mA4;
    if (c == NULL) return;
    f32 rot = fn_8001E064(c->m58);
    if (e->m30->mC4->m8 & 0x80) {
        q1.w.a = 0;
        q1.w.b = 0;
        q1.w.c = 0;
        fn_800B4000(c, Node(c, lbl_803657E8 + 0x26), &q1, -1, 0);
        t.w = q1.w;
        t.v.y = fn_8001E064(c->m5a);
        *(W3*)&b = t.w;
        out = b;
    } else {
        q2.w.a = 0;
        q2.w.b = 0;
        q2.w.c = 0;
        fn_800B4000(c, Node(c, lbl_803657E8 + 0x26), &q2, -1, 0);
        *(W3*)&d = q2.w;
        out = d;
    }
    arg = *(W3*)&out;
    fn_800E48C8(e, (Vec*)&arg);
    fn_800E49AC(e, rot);
}
}
