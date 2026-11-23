#include "game/rG_800A3D88/chr.h"

// Battle character: per-frame jump arc and knockback.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct ChV { u8 p[0x30]; Mdl* mdl; u8 p34[0x44 - 0x34]; Vec m44; u32 m50; u8 p54[4]; s16 m58; u8 p5a[0x84 - 0x5A]; f32 m84; f32 m88; };
struct W3 { u32 a, b, c; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
f32 fn_80006CF8();
int fn_80008C98(Mdl*, int);
f32 fn_800A84A4(const char*);
void fn_800087FC(Mdl*, int);
f32 fn_8001E064(int);
void fn_80312654(Mtx34*, int, f32);
void fn_80312DB4(Mtx34*, Vec*, Vec*);
void fn_800B33F4(ChV*, int);
static inline int Ev(ChV* c, int k) {
    if (c->mdl == NULL) return 0;
    return fn_80008C98(c->mdl, k);
}
static inline void Stop(ChV* c, int k) {
    if (c->mdl->flags & 4) {
        c->mdl->flags &= ~4;
        fn_800087FC(c->mdl, k);
    }
}
void fn_800B99DC(ChV* c) {
    Mtx34 m;
    Vec p;
    Vec v;
    Vec r;
    if (!(c->m50 & 0x600)) return;
    *(W3*)&p = *(W3*)&c->m44;
    if (c->m50 & 0x200) {
        p.y = c->m84 * fn_80006CF8() + p.y;
        if (p.y <= 0.0f) p.y = 0.0f;
        if (Ev(c, 0x41) && c->m84 >= 0.0f) c->mdl->flags |= 4;
        if (Ev(c, 0x42) && c->m84 <= 0.0f) c->mdl->flags |= 4;
        f32 old = c->m84;
        f32 g = fn_800A84A4(STR(0x27F));
        f32 t = g * fn_80006CF8();
        c->m84 -= t;
        if (old * c->m84 < 0.0f) Stop(c, 0x41);
        if (p.y <= 0.0f) {
            c->m50 &= ~0x200;
            Stop(c, 0x42);
        }
    }
    if (c->m50 & 0x400) {
        *(u32*)&v.x = 0;
        *(u32*)&v.y = 0;
        *(u32*)&v.z = 0;
        v.z = c->m88 * fn_80006CF8();
        f32 d = fn_800A84A4(STR(0x28A));
        d = (d - 1.0f) * fn_80006CF8() + 1.0f;
        f32 a = fn_8001E064(c->m58);
        fn_80312654(&m, 0x79, 0.017453292f * -a);
        fn_80312DB4(&m, &v, &v);
        p.x += v.x;
        c->m88 *= d;
        double av = __fabs(c->m88);
        if ((f32)av <= 0.05f) c->m50 &= ~0x400;
    }
    *(W3*)&r = *(W3*)&p;
    c->m44 = r;
    fn_800B33F4(c, 1);
}
}
