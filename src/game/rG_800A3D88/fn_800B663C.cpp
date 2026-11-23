#include "game/rG_800A3D88/chr.h"

// Distance between a character and its opponent, optionally minus their radii.
extern "C" {
struct ChK { u8 p[0x30]; Mdl* mdl; u8 p34[0x50 - 0x34]; u32 m50; u8 p54[0x78 - 0x54]; void* data; struct { u8 p[8]; u16 m8; }* m7c; ChK* m80; };
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChK*, int, Vec*, int, int);
void fn_80313484(Vec*, Vec*, Vec*);
f32 fn_80313508(Vec*);
f32 fn_800A7370(void*, const char*);
f32 fn_800A84A4(const char*);
static inline int Node(ChK* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline int NodeB(ChK* c, const char* n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline f32 Radius(ChK* c, Vec* a, Vec* b, f32& v) {
    if (c->mdl == NULL) { v = 4.0f; return v; }
    v = 0.0f;
    if (fn_800B4000(c, Node(c, STR(0xC2)), a, -1, 1)) {
        if (fn_800B4000(c, Node(c, STR(0x26)), b, -1, 1)) {
            fn_80313484(a, b, a);
            v = fn_80313508(a);
        }
    }
    if (v < 0.001f) v = fn_800A7370(c->data, STR(0x18E));
    return v;
}
struct B8 { u8 p[8]; u16 a:13; u16 b:1; u16 c:1; u16 d:1; };
static inline int Armed(ChK* c) {
    if (c->mdl == NULL) return 0;
    if (c->m7c == NULL) return 0;
    B8* v = (B8*)c->m7c;
    if (v->d == 0) return 0;
    return v->b;
}
int fn_800B663C(ChK* c) {
    Vec a2, b2, a1, b1;
    VU r1, r0;
    Vec q, p;
    f32 e; f32 d; f32 v1; f32 v2; f32 d1;
    if (c->m50 & 0x20) return 1;
    if (Armed(c)) {
    if (c->mdl == NULL) d = 0.0f;
    else if (c->m80 == NULL) d = 0.0f;
    else {
        r0.w.a = 0;
        r0.w.b = 0;
        r0.w.c = 0;
        fn_800B4000(c, Node(c, STR(0x26)), &r0.v, -1, 0);
        *(W3*)&p = r0.w;
        ChK* o = c->m80;
        r1.w.a = 0;
        r1.w.b = 0;
        r1.w.c = 0;
        fn_800B4000(o, Node(o, STR(0x26)), &r1.v, -1, 0);
        *(W3*)&q = r1.w;
        fn_80313484(&p, &q, &p);
        e = fn_80313508(&p); Radius(c, &a1, &b1, v1); v1 = e - v1; o = c->m80; Radius(o, &a2, &b2, e); d = v1 - e;


    }
    if (d <= fn_800A84A4(STR(0x1E0))) return 1;
    }
    return 0;
}
}
