#include "game/rG_800A3D88/chr.h"

// Battle character: spawn a hit effect on the opponent.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct ChH { u8 p[0x30]; Mdl* mdl; u8 p34[0x58 - 0x34]; s16 m58, m5a; u8 p5c[0x78 - 0x5C]; void* data; u8 p7c[4]; ChH* m80; };
struct EfC { u8 p[8]; u16 m8; };
struct EfN { u8 p[0xE]; u8 mE; u8 pf[0xC4 - 0xF]; EfC* mC4; };
struct Ef { u8 p[0x30]; EfN* m30; };
struct Sc { u8 m0, m1; s16 m2; };
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
void* fn_800BAB5C(ChH*, Sc*);
Ef* fn_800E3810(void*, ChH*);
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChH*, int, void*, int, int);
f32 fn_800A7370(void*, const char*);
f32 fn_8001E064(int);
void fn_80312654(Mtx34*, int, f32);
void fn_80312DB4(Mtx34*, Vec*, Vec*);
void fn_80313460(Vec*, Vec*, Vec*);
void fn_800E48C8(Ef*, Vec*);
void fn_800E49AC(Ef*, f32);
static inline int Node(ChH* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
int fn_800BB074(ChH* c, Sc* s) {
    Mtx34 m1, m2;
    Vec out, sh, b2, b1;
    W3 arg;
    VU s1;
    Vec k1;
    VU r1, t, r2;
    Vec k2;
    VU s2;
    ChH* o;
    Ef* e;
    void* d = fn_800BAB5C(c, s);
    if (d == NULL) return 0;
    e = fn_800E3810(d, c);
    if (e != NULL) {
    o = c->m80;
    if (e->m30->mC4->m8 & 0x80) {
        r1.w.a = 0;
        r1.w.b = 0;
        r1.w.c = 0;
        fn_800B4000(o, Node(o, STR(0x26)), &r1, -1, 0);
        s1.w = r1.w;
        k1.x = 0.0f;
        k1.y = fn_800A7370(o->data, STR(0x16D));
        k1.z = fn_800A7370(o->data, STR(0x176));
        fn_80312654(&m1, 0x79, 0.017453292f * fn_8001E064(o->m58));
        fn_80312DB4(&m1, &k1, &k1);
        fn_80313460(&s1.v, &k1, &s1.v);
        t.w = s1.w;
        t.v.y = fn_8001E064(o->m5a);
        *(W3*)&b2 = t.w;
        out = b2;
    } else {
        r2.w.a = 0;
        r2.w.b = 0;
        r2.w.c = 0;
        fn_800B4000(o, Node(o, STR(0x26)), &r2, -1, 0);
        s2.w = r2.w;
        k2.x = 0.0f;
        k2.y = fn_800A7370(o->data, STR(0x16D));
        k2.z = fn_800A7370(o->data, STR(0x176));
        fn_80312654(&m2, 0x79, 0.017453292f * fn_8001E064(o->m58));
        fn_80312DB4(&m2, &k2, &k2);
        fn_80313460(&s2.v, &k2, &s2.v);
        *(W3*)&b1 = s2.w;
        out = b1;
    }
    if (s != NULL && s->m2 == 0x70) {
        if (fn_800B4000(o, Node(o, STR(0x304)), &sh, -1, 0)) out = sh;
    }
    arg = *(W3*)&out;
    fn_800E48C8(e, (Vec*)&arg);
    fn_800E49AC(e, fn_8001E064(o->m58));
    e->m30->mE = 3;
    return 1;
    }
    return 0;
}
}
