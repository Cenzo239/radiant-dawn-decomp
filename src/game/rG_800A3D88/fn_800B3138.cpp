#include "game/rG_800A3D88/chr.h"

// Battle character: rebuild the model matrix from position, scale and facing.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct ChM { u8 p[0x30]; Mdl* mdl; u8 p34[0x44 - 0x34]; Vec m44; u32 m50; u8 p54[4]; s16 m58, m5a; u8 p5c[0x78 - 0x5C]; void* data; };
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
extern W3 lbl_80382574;
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
f32 fn_800A7370(void*, const char*);
f32 fn_8001E064(int);
void fn_8031292C(Mtx34*, f32, f32, f32);
void fn_803128AC(Mtx34*, f32, f32, f32);
void fn_80312654(Mtx34*, int, f32);
void fn_80312378(Mtx34*, Mtx34*, Mtx34*);
void fn_80312344(Mtx34*, void*);
int fn_80007630(Mdl*, const char*);
void fn_800B4000(ChM*, int, VU*, int, int);
static inline int Node(ChM* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
void fn_800B3138(ChM* c) {
    Mtx34 m3, m2, m1, m0;
    Vec sc, p;
    Vec t;
    if (c->mdl == NULL) return;
    Vec s = *(Vec*)&lbl_80382574;
    VU r;
    if (c->data != NULL) {
        s.x = fn_800A7370(c->data, STR(0x147));
        s.y = fn_800A7370(c->data, STR(0x152));
        s.z = fn_800A7370(c->data, STR(0x15D));
    }
    *(W3*)&sc = *(W3*)&s;
    *(W3*)&p = *(W3*)&c->m44;
    f32 a = fn_8001E064(c->m58);
    fn_8031292C(&m3, sc.x, sc.y, sc.z);
    f32 y = fn_8001E064(c->m5a);
    fn_803128AC(&m2, p.x, p.y + y, p.z);
    fn_80312654(&m1, 0x79, 0.017453292f * a);
    fn_80312378(&m1, &m3, &m0);
    fn_80312378(&m2, &m0, &m0);
    if (c->m50 & 2) {
        fn_8031292C(&m3, -1.0f, 1.0f, 1.0f);
        fn_80312378(&m0, &m3, &m0);
        c->mdl->flags |= 0x8000000;
    } else {
        c->mdl->flags &= ~0x8000000;
    }
    fn_80312344(&m0, (u8*)c->mdl + 0x10);
    f32 v = fn_800A7370(c->data, STR(0x168));
    if (v > 0.0f) {
        r.w.a = 0;
        r.w.b = 0;
        r.w.c = 0;
        fn_800B4000(c, Node(c, STR(0x26)), &r, -1, 0);
        *(W3*)&t = r.w;
        p.x = t.x;
        p.y = t.y;
        p.z = t.z;
        fn_803128AC(&m2, -p.x, 0.0f, -p.z);
        fn_80312654(&m1, 0x79, 0.017453292f * v);
        fn_80312378(&m1, &m2, &m0);
        fn_803128AC(&m2, p.x, 0.0f, p.z);
        fn_80312378(&m2, &m0, &m0);
        fn_80312378(&m0, (Mtx34*)((u8*)c->mdl + 0x10), (Mtx34*)((u8*)c->mdl + 0x10));
    }
}
}
