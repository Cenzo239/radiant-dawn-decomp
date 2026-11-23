#include "game/rG_800A3D88/types.h"

// Attached effect: launch toward a target, children first.
extern "C" {
typedef f32 Mt[3][4];
struct Vec { f32 x, y, z; };
struct S3 { s16 x, y, z; };
struct EMdl { u8 p[0x10]; Mt m10; };
struct OMdl { u32 flags; };
struct Owner { u8 p[0x30]; OMdl* m30; };
struct Eff {
    void* vt;
    u8 p4[0x18];
    Eff* m1c;
    u8 p20[4];
    Eff* m24;
    u8 p28[0x34 - 0x28];
    EMdl* m34;
    void* m38;
    Owner* m3c;
    u8 p40[6];
    u16 m46;
    u8 p48[0x58 - 0x48];
    f32 m58;
    s16 m5c, m5e, m60, m62, m64, m66;
    f32 m68, m6c;
    S3 m70;
    S3 m76;
    S3 m7c;
    u8 m82[6];
};
extern u8 lbl_803825A8[];
extern char lbl_80365B64[];
u8 fn_800A6844(void*, int);
f32 fn_800A84A4(const char*);
void fn_8001E9E4(Mt, Vec*);
void fn_80313484(Vec*, Vec*, Vec*);
f32 fn_80313508(Vec*);
void fn_803134C4(Vec*, Vec*);
S3 fn_8001E144(Vec*);
s16 fn_8001E094(f32);
void fn_8001E6D0(Mt, Mt);
void fn_8001E318(Mt, void*);
void fn_800C0BD0(Eff*, int);
void fn_800C0478(Eff* e, Vec v, int n) {
    Mt m;
    Vec p, d, t;
    Eff* c;
    const char* s;
    f32 a, f, h, dist, r, g;
    if (e->m34 == NULL) return;
    c = e->m1c;
    if (c != NULL) {
        for (; c != NULL; c = c->m24) {
            if (c->vt == lbl_803825A8) fn_800C0478(c, v, n);
        }
    }
    f = 0.0f;
    a = 1.0f;
    h = f;
    g = 10.0f;
    switch (fn_800A6844(e->m38, -1)) {
    case 2: case 5:
        s = lbl_80365B64;
        a = fn_800A84A4(s + 0x48);
        g = fn_800A84A4(s + 0x51);
        f = fn_800A84A4(s + 0x5A);
        h = fn_800A84A4(s + 0x63);
        break;
    case 3: case 6:
        if (n < 0) return;
        s = lbl_80365B64;
        g = fn_800A84A4(s + 0x6C);
        f = fn_800A84A4(s + 0x75);
        h = fn_800A84A4(s + 0x7E);
        break;
    case 15:
        s = lbl_80365B64;
        a = fn_800A84A4(s + 0x87);
        g = fn_800A84A4(s + 0x8E);
        f = fn_800A84A4(s + 0x95);
        break;
    case 4: case 7:
        s = lbl_80365B64;
        a = fn_800A84A4(s + 0x9C);
        g = fn_800A84A4(s + 0xA5);
        f = fn_800A84A4(s + 0xAE);
        break;
    case 0: case 1: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
        break;
    }
    fn_8001E9E4(e->m34->m10, &p);
    fn_80313484(&v, &p, &d);
    dist = fn_80313508(&d);
    if (0.0f == dist) {
        e->m46 |= 4;
        return;
    }
    fn_803134C4(&d, &d);
    v.x += d.x * g;
    v.y += d.y * g;
    v.z += d.z * g;
    fn_80313484(&v, &p, &t);
    r = fn_80313508(&t) / dist;
    switch (fn_800A6844(e->m38, -1)) {
    case 4: case 5: case 7: case 15:
        n = (int)((dist + g) / a);
        break;
    }
    e->m5c = n;
    e->m58 = 0.0f;
    e->m70 = fn_8001E144(&p);
    e->m76 = fn_8001E144(&v);
    e->m7c = fn_8001E144(&d);
    e->m60 = fn_8001E094(a);
    e->m62 = fn_8001E094(f);
    e->m64 = fn_8001E094(h);
    e->m5e = fn_8001E094(dist);
    e->m66 = fn_8001E094(r);
    e->m68 = 0.0f;
    fn_8001E6D0(e->m34->m10, m);
    fn_8001E318(m, e->m82);
    e->m46 |= 2;
    e->m46 &= ~8;
    e->m46 &= ~0x40;
    fn_800C0BD0(e, 1);
    OMdl* o = e->m3c->m30;
    if (o != NULL) o->flags |= 8;
}
}
