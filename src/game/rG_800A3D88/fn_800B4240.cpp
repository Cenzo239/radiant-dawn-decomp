#include "game/rG_800A3D88/chr.h"

// Distance between a character and its opponent, optionally minus their radii.
extern "C" {
struct ChK { u8 p[0x30]; Mdl* mdl; u8 p34[0x78 - 0x34]; void* data; u8 p7c[4]; ChK* m80; };
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChK*, int, Vec*, int, int);
void fn_80313484(Vec*, Vec*, Vec*);
f32 fn_80313508(Vec*);
f32 fn_800A7370(void*, const char*);
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
static inline f32 Radius(ChK* c, Vec* a, Vec* b) {
    f32 v;
    if (c->mdl == NULL) return 4.0f;
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
f32 fn_800B4240(ChK* c, int sub) {
    Vec p, q;
    VU r0, r1;
    Vec b1, a1, b2, a2;
    if (c->mdl == NULL) return 0.0f;
    if (c->m80 == NULL) return 0.0f;
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
    f32 d = fn_80313508(&p);
    if (sub) {
        d -= Radius(c, &a1, &b1);
        ChK* o2 = c->m80;
        d -= Radius(o2, &a2, &b2);
    }
    return d;
}
}
