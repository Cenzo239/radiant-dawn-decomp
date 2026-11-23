#include "game/rG_800A3D88/chr.h"

// Battle character: step forward to melee range of the opponent.
extern "C" {
struct Arc { u8 p[4]; f32 m4, m8, mC, m10, m14; };
struct Mtx34 { f32 m[3][4]; };
struct ChK { u8 p[0x30]; Mdl* mdl; u8 p34[0x50 - 0x34]; u32 m50; u8 p54[4]; s16 m58; u8 p5a[0x78 - 0x5A]; void* data; u8 p7c[4]; ChK* m80; u8 p84[0x8C - 0x84]; Arc* m8c; };
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_80008E88(Mdl*, int, int);
s16 fn_80008CF0(Mdl*, int);
f32 fn_800A84A4(const char*);
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChK*, int, void*, int, int);
void fn_80313484(Vec*, Vec*, Vec*);
void fn_80313460(Vec*, Vec*, Vec*);
f32 fn_80313508(Vec*);
void fn_803134C4(Vec*, Vec*);
void fn_803134A8(Vec*, Vec*, f32);
f32 fn_800A7370(void*, const char*);
f32 fn_8001E064(int);
void fn_80312654(Mtx34*, int, f32);
void fn_80312DB4(Mtx34*, Vec*, Vec*);
static inline int Node(ChK* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline void Radius(ChK* c, Vec* a, Vec* b, int fr, f32& v) {
    if (c->mdl == NULL) { v = 4.0f; return; }
    v = 0.0f;
    if (fn_800B4000(c, Node(c, STR(0xC2)), a, fr, 1)) {
        if (fn_800B4000(c, Node(c, STR(0x26)), b, fr, 1)) {
            fn_80313484(a, b, a);
            v = fn_80313508(a);
        }
    }
    if (v < 0.001f) v = fn_800A7370(c->data, STR(0x18E));
}
f32 fn_800B8FF8(ChK* c) {
    Mtx34 m;
    Vec v8c;
    Vec v80, v74, v68;
    VU r5c;
    Vec p50;
    VU r44;
    Vec p38;
    Vec b1, a1, b2, a2;
    f32 ra, rb;
    ChK* o = c->m80;
    if (o == NULL) return 0.0f;
    if (o->mdl == NULL) return 0.0f;
    if (!(c->m50 & 8)) return 0.0f;
    if (!(o->m50 & 8)) return 0.0f;
    r5c.w.a = 0;
    r5c.w.b = 0;
    r5c.w.c = 0;
    *(u32*)&v8c.x = 0;
    *(u32*)&v8c.y = 0;
    *(u32*)&v8c.z = 0;
    fn_800B4000(c, Node(c, STR(0x26)), &r5c, -1, 0);
    *(W3*)&p50 = r5c.w;
    p50.y = 0.0f;
    p50.z = 0.0f;
    *(W3*)&v80 = *(W3*)&p50;
    o = c->m80;
    r44.w.a = 0;
    r44.w.b = 0;
    r44.w.c = 0;
    fn_800B4000(o, Node(o, STR(0x26)), &r44, -1, 0);
    *(W3*)&p38 = r44.w;
    p38.y = 0.0f;
    p38.z = 0.0f;
    *(W3*)&v74 = *(W3*)&p38;
    Radius(c, &a1, &b1, -1, ra);
    Radius(c->m80, &a2, &b2, -1, rb);
    f32 sum = ra + rb;
    fn_80313484(&v74, &v80, &v68);
    f32 rot = fn_8001E064(c->m58);
    fn_80312654(&m, 0x79, 0.017453292f * -rot);
    fn_80312DB4(&m, &v68, &v68);
    if (v68.z < sum) {
        v68.x = 0.0f;
        v68.y = 0.0f;
        v68.z -= sum;
        fn_80312654(&m, 0x79, 0.017453292f * rot);
        fn_80312DB4(&m, &v68, &v68);
        return v68.x;
    }
    return 0.0f;
}
}
