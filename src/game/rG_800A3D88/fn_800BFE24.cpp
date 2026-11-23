#include "game/rG_800A3D88/types.h"

// Attached effect in flight: move along a line or an arc until it lands.
extern "C" {
typedef f32 Mt[3][4];
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct Bn { u8 p[0x58]; f32 m58, m5c, m60; u8 p64[0x70 - 0x64]; f32 m70, m74, m78; };
struct EMdl { u8 p[0x10]; Mt m10; };
struct Eff {
    u8 p[0x34];
    EMdl* m34;
    void* m38;
    u8 p3c[0x46 - 0x3C];
    u16 m46;
    u8 p48[0x58 - 0x48];
    f32 m58;
    s16 m5c, m5e, m60, m62, m64, m66;
    f32 m68, m6c;
    u8 m70[6];
    u8 m76[6];
    u8 m7c[6];
    u8 m82[6];
};
extern W3 lbl_80365B58;
extern char lbl_80365B64[];
void fn_8001E0B4(W3*, void*);
f32 fn_8001E064(int);
void fn_800C0F44(Eff*, int);
void fn_8001E1A4(void*, Mt);
Bn* fn_800078E4(EMdl*, int);
f32 fn_80006CF8();
f32 fn_8001EF30(f32, f32, f32, f32);
void fn_80312318(Mt);
u8 fn_800A6844(void*, int);
void fn_8001E9E4(Mt, Vec*);
double fn_80295940(double);
void fn_80312654(Mt, int, f32);
void fn_80312378(const void*, const void*, void*);
void fn_80313484(Vec*, Vec*, Vec*);
f32 fn_80313508(Vec*);
void fn_803134C4(Vec*, Vec*);
void fn_8031356C(Vec*, Vec*, Vec*);
f32 fn_8001EA74(Vec*, Vec*);
void fn_80312830(Mt, Vec*, f32);
void fn_803128AC(Mt, f32, f32, f32);
void fn_802549C4(const char*, Vec*, f32);
void fn_800C0894(Eff*);
static inline void Get(Vec* out, void* in) {
    W3 t;
    fn_8001E0B4(&t, in);
    *(W3*)out = t;
}
static inline void Warn(const Vec& v) {
    Vec t;
    t = v;
    fn_802549C4(lbl_80365B64 + 0x32, &t, 0.0f);
}
void fn_800BFE24(Eff* e) {
    Mt m128, mf8, mc8, m98;
    Vec n, p, a, b, c;
    if (e->m34 == NULL) return;
    if (!(e->m46 & 2)) return;
    Get(&a, e->m70);
    Get(&b, e->m76);
    Get(&c, e->m7c);
    fn_8001E064(e->m60);
    f32 f28 = fn_8001E064(e->m62);
    f32 f29 = fn_8001E064(e->m64);
    f32 f30 = fn_8001E064(e->m5e);
    f32 f31 = fn_8001E064(e->m66);
    Vec k = {0.0f, 0.0f, 1.0f};
    Vec x, piv;
    e->m46 = (e->m46 & ~4) | 0x10;
    fn_800C0F44(e, -1);
    fn_8001E1A4(e->m82, m98);
    Bn* bn = fn_800078E4(e->m34, 0);
    piv.x = bn->m58 + bn->m70;
    piv.y = bn->m5c + bn->m74;
    piv.z = bn->m60 + bn->m78;
    e->m58 += fn_80006CF8();
    f32 t = fn_8001EF30(0.0f, 1.0f, e->m5c, e->m58);
    f32 dt = f28 * fn_80006CF8();
    e->m68 += dt;
    e->m6c += dt;
    fn_80312318(mf8);
    switch (fn_800A6844(e->m38, -1)) {
    case 2: case 4: case 5: case 7: case 15:
        fn_8001E9E4(e->m34->m10, &p);
        n.x = fn_8001EF30(a.x, b.x, 1.0f, t);
        n.y = fn_8001EF30(a.y, b.y, 1.0f, t);
        n.z = fn_8001EF30(a.z, b.z, 1.0f, t);
        if (f29 > 0.0f) {
            f32 u = t * f31;
            if (u > 1.5f) u = 1.5f;
            n.y += f29 * (f32)fn_80295940(3.1415927f * u);
        }
        if (0.0f != e->m68) {
            fn_80312654(mc8, 0x7A, 0.017453292f * e->m68);
            fn_80312378(mc8, mf8, mf8);
        }
        if (e->m46 & 0x40) {
            fn_80312654(mc8, 0x78, 0.017453292f * e->m6c);
            fn_80312378(mc8, mf8, mf8);
        }
        fn_80313484(&n, &p, &c);
        if (fn_80313508(&c) > 0.0f) {
            fn_803134C4(&c, &c);
            fn_8031356C(&k, &c, &x);
            fn_80312830(mc8, &x, fn_8001EA74(&k, &c));
            fn_80312378(mc8, mf8, mf8);
        }
        break;
    case 3: case 6:
        if (t < 0.5f) {
            n.x = fn_8001EF30(a.x, b.x, 0.5f, t);
            n.y = fn_8001EF30(a.y, b.y, 0.5f, t);
            n.z = fn_8001EF30(a.z, b.z, 0.5f, t);
            n.y += f29 * (f32)fn_80295940(2.0f * (3.1415927f * t));
        } else {
            n.x = fn_8001EF30(b.x, a.x, 0.5f, t - 0.5f);
            n.y = fn_8001EF30(b.y, a.y, 0.5f, t - 0.5f);
            n.z = fn_8001EF30(b.z, a.z, 0.5f, t - 0.5f);
            n.y -= f29 * (f32)fn_80295940(2.0f * (3.1415927f * (t - 0.5f)));
        }
        fn_803128AC(m128, -piv.x, -piv.y, -piv.z);
        fn_80312654(mf8, 0x79, 0.017453292f * e->m68);
        fn_80312378(mf8, m128, mc8);
        fn_803128AC(m128, piv.x, piv.y, piv.z);
        fn_80312378(m128, mc8, mc8);
        fn_80312378(m98, mc8, mf8);
        if ((f32)__fabs(e->m68) > 720.0f) {
            Warn(n);
            if (e->m68 > 720.0f) e->m68 -= 720.0f;
            if (e->m68 < -720.0f) e->m68 += 720.0f;
        }
        break;
    case 0: case 1: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
        break;
    }
    fn_803128AC(m128, n.x, n.y, n.z);
    fn_80312378(m128, mf8, e->m34->m10);
    if (!(e->m46 & 8)) {
        fn_80313484(&n, &a, &p);
        if (fn_80313508(&p) >= 0.75f * f30) e->m46 |= 0xC;
    }
    if (e->m58 >= e->m5c || ((e->m46 & 8) && n.y < 0.0f)) fn_800C0894(e);
}
}
