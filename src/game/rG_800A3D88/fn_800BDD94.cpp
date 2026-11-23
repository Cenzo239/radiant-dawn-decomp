#include "game/rG_800A3D88/chr.h"

// Battle character: step forward to melee range of the opponent.
extern "C" {
struct Arc { u8 p[4]; f32 m4, m8, mC, m10, m14; };
struct ChK { u8 p[0x30]; Mdl* mdl; u8 p34[0x78 - 0x34]; void* data; u8 p7c[4]; ChK* m80; u8 p84[0x8C - 0x84]; Arc* m8c; };
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
int fn_800BDD94(ChK* c) {
    Vec old;
    Vec va4;
    Vec a2, b2, a1, b1;
    Vec v68;
    VU r5c;
    Vec v50;
    VU r44;
    Vec v38, d2c, pos;
    VU r14;
    Vec v8;
    f32 rb, ra, dist;
    Mdl* m = c->mdl;
    if (m == NULL) return 0;
    int fr = (int)m->frame;
    int to = fn_80008E88(m, fr, 0x36);
    int d = to - fr;
    if (to < 0) return 0;
    int ev = c->mdl == NULL ? -1 : fn_80008CF0(c->mdl, 0x34);
    dist = (f32)ev;
    if (0.0f == dist) dist = fn_800A84A4(STR(0x348));
    r44.w.a = 0;
    r44.w.b = 0;
    r44.w.c = 0;
    fn_800B4000(c, Node(c, STR(0x26)), &r44, -1, 0);
    *(W3*)&v50 = r44.w;
    v50.y = 0.0f;
    v50.z = 0.0f;
    *(W3*)&pos = *(W3*)&v50;
    ChK* o = c->m80;
    if (o != NULL) {
        r5c.w.a = 0;
        r5c.w.b = 0;
        r5c.w.c = 0;
        fn_800B4000(o, Node(o, STR(0x26)), &r5c, -1, 0);
        *(W3*)&v68 = r5c.w;
        v68.y = 0.0f;
        v68.z = 0.0f;
        *(W3*)&v38 = *(W3*)&v68;
        fn_80313484(&v38, &pos, &d2c);
        Radius(c, &a1, &b1, to, ra);
        Radius(c->m80, &a2, &b2, -1, rb);
        if (dist < ra + rb) dist = ra + rb;
        if (fn_80313508(&d2c) > 0.0f) {
            fn_803134C4(&d2c, &d2c);
            fn_803134A8(&d2c, &d2c, dist);
            fn_80313460(&v38, &d2c, &pos);
        }
    }
    *(W3*)&old = *(W3*)&pos;
    r14.w.a = 0;
    r14.w.b = 0;
    r14.w.c = 0;
    fn_800B4000(c, Node(c, STR(0x26)), &r14, to, 0);
    *(W3*)&v8 = r14.w;
    v8.y = 0.0f;
    v8.z = 0.0f;
    *(W3*)&va4 = *(W3*)&v8;
    f32 h = old.x - va4.x;
    if (0.0f != h) {
        Arc* a = c->m8c;
        a->m8 = 0.0f;
        a->mC = 0.0f;
        a->m10 = 0.0f;
        a->m4 = h;
        a->m14 = d;
    }
    return 1;
}
}
