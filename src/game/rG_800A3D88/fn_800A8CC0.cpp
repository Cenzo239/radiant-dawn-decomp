#include "game/rG_800A3D88/chr.h"

// Lens flare: projects the sun to the screen, fades on the Z peek, draws one sprite per element along the screen centre line.
extern "C" {
struct FlTex { u8 p[4]; u16 m4; u8 p6[0x10 - 6]; f32 m10; f32 m14; };
struct FlDat { u8 p[8]; u8 c0, c1, c2, c3; u8 pC[0x14 - 0xC]; FlTex* tex; };
struct FlEl { u8 p[4]; FlDat* d; f32 m8; };
struct Fl { u8 p[0x30]; u8 m30; u8 p31[3]; Vec m34; void* m40; int m44; FlEl* m48; u8 m4c; };
void* fn_80007F68(void*);
#if TARGET_PC
FE10_PROTO void fn_80011C4C(p32arg, Vec*, Vec*);
#else
void fn_80011C4C(int, Vec*, Vec*);
#endif
f32 fn_80313508(Vec*);
f32 fn_8001EF30(f32, f32, f32, f32);
void fn_803134C4(Vec*, Vec*);
f32 fn_8031354C(Vec*, Vec*);
double fn_80295A90(f32);
void fn_80303E8C(u16, u16, u32*);
void fn_8007E154();
void fn_8007E164();
void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
void fn_8007E374(void*, u16, int);
#endif
void fn_8007E7DC(u8);
void fn_8007E7F4();
void fn_800800D4(int);
void fn_80080348(f32, f32, f32, f32);
void fn_80080368(f32, f32, f32, f32);
void fn_80080578(int);
void fn_80080730(f32, f32, f32);
void fn_800804D4(u8, u8, u8, u8);
void fn_80080308();
static inline f32 Ac(f32 x) { return fn_80295A90(x); }
void fn_800A8CC0(Fl* p) {
int a;
int o;
f32 hw;
f32 hh;
f32 ang;
int n;
int i;
void* res;
FlEl* e;
FlDat* d;
FlTex* x;
u16 id;
f32 a0;
f32 u;
f32 v;
f32 sx;
f32 sy;
f32 sz;
f32 b0;
f32 b1;
u8 c0;
u8 c1;
u8 c2;
u8 c3;
    Vec s;
    if (p->m30 != 0 && p->m40 != NULL && p->m44 != 0) {
    a = 0;
    res = fn_80007F68(p->m40);
    hw = 304.0f;
    hh = 224.0f;
    fn_80011C4C(0, &p->m34, &s);
    if (s.z < 0.0f) {
        s.z = 0.0f;
        f32 dd = fn_80313508(&s);
        if (dd < 1.0f) {
            a = (int)fn_8001EF30(255.0f, 0.0f, 1.0f, dd);
        }
    }
    if (a == 0) {
        p->m4c = 0;
    } else {
    Vec t = s;
    ang = 0.0f;
    t.z = 0.0f;
    if (fn_80313508(&t) > 0.0f) {
        Vec up = {0.0f, 1.0f, 0.0f};
        fn_803134C4(&t, &t);
        f32 c = Ac(fn_8031354C(&up, &t));
        if (t.x < 0.0f) c *= -1.0f;
        ang = 57.29578f * c;
    }
    u32 z;
    fn_80303E8C(s.x * hw + hw, hh - s.y * hh, &z);
    if (z <= 0xFFC000) {
        if (p->m4c != 0) p->m4c--;
    } else {
        if (p->m4c < 8) p->m4c++;
    }
    n = a * p->m4c / 8;
    if (n != 0) {
    for (i = 0, o = 0; i < p->m44; o += 0xC, i++) {
        e = (FlEl*)((u8*)p->m48 + o);
        d = e->d;
        x = d->tex;
        if (x != NULL) {
            id = x->m4;
            sz = e->m8;
            u = fn_8001EF30(s.x, 0.0f, p->m44 / 2.0f, i);
            v = fn_8001EF30(s.y, 0.0f, p->m44 / 2.0f, i);
            sx = 1.25f * (u * hw) + hw;
            sy = hh - 1.25f * (v * hh);
            fn_8007E154();
            fn_8007E4E4(sx, sy, 800.0f, sz);
            fn_8007E374(res, id, 0x20);
            fn_8007E7DC(n);
            fn_8007E164();
            f32 u0 = 0.0f; a0 = 1.0f; b0 = u0; b1 = a0;
            if (a0 != x->m10) a0 = x->m10;
            if (1.0f != x->m14) { b0 = 1.0f; b1 = 1.0f - x->m14; }
            c0 = d->c0; c1 = d->c1; c2 = d->c2; c3 = d->c3;
            fn_800800D4(2);
            fn_80080348(-64.0f, -64.0f, u0, b0);
            fn_80080368(64.0f, 64.0f, a0, b1);
            fn_80080578(0);
            fn_80080730(0.0f, 0.0f, ang);
            fn_800804D4(c0, c1, c2, c3);
            fn_80080308();
        }
    }
    fn_8007E7F4();
    }
    }
    }
}
}
