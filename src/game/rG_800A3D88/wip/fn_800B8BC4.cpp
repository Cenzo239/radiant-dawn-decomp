// WIP, does not match: 23 lines, right size: only the 0.0f constant's float register (f0 wanted, ours f2) in the two arc setups; a named constant and argument order did not move it.
#include "game/rG_800A3D88/chr.h"

// Battle character: jump arcs and other per-frame animation events.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct Arc { u8 p[4]; f32 m4, m8, mC, m10, m14; };
struct ChJ { u8 p[0x30]; Mdl* mdl; u8 p34[0x44 - 0x34]; Vec m44; u32 m50; u8 p54[4]; s16 m58; u8 p5a[0x78 - 0x5A]; void* data; u8 p7c[4]; ChJ* m80; u8 p84[0x90 - 0x84]; Arc* m90; };
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_80008C98(Mdl*, int);
int fn_80008E88(Mdl*, int, int);
int fn_80007630(Mdl*, const char*);
void fn_800B4000(ChJ*, int, VU*, int, int);
f32 fn_800A7370(void*, const char*);
f32 fn_8001E064(int);
void fn_80312654(Mtx34*, int, f32);
void fn_80312DB4(Mtx34*, Vec*, Vec*);
void fn_80313460(Vec*, Vec*, Vec*);
void fn_800BD294(ChJ*);
void fn_800BD86C(ChJ*);
void fn_800BDD94(ChJ*);
static inline int Ev(ChJ* c, int k) {
    if (c->mdl == NULL) return 0;
    return fn_80008C98(c->mdl, k);
}
static inline int Node(ChJ* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
static inline void Jump(ChJ* c, f32 h, int t) {
    Arc* a = c->m90;
    a->m8 = 0.0f;
    a->mC = 0.0f;
    a->m10 = 0.0f;
    a->m4 = h;
    a->m14 = t;
}
static inline void Arc_Set(ChJ* c, f32 h, int t) {
    if (0.0f != h) Jump(c, h, t);
}
struct FB8BC4 { VU b; VU a; VU t; VU r0, r1; Vec k; VU s; u8 p5c[4]; Mtx34 m; };
void fn_800B8BC4(ChJ* c) {
    Mtx34 mm;
    VU vs;
    Vec vk;
    VU r1, r0, vt, va, vb;
/*P*/
int fr;
ChJ* o;
int to;
int d;
/*E*/
    if (!(c->m50 & 0x800000)) return;
    if (Ev(c, 0x43) && c->mdl != NULL) {
        fr = (int)c->mdl->frame;
        to = fn_80008E88(c->mdl, fr, 0x44);
        d = to - fr;
        if (to >= 0) {
            r0.w.a = 0;
            r0.w.b = 0;
            r0.w.c = 0;
            fn_800B4000(c, Node(c, STR(0x26)), &r0, to, 0);
            o = c->m80;
            va.w = r0.w;
            r1.w.a = 0;
            r1.w.b = 0;
            r1.w.c = 0;
            fn_800B4000(o, Node(o, STR(0x26)), &r1, -1, 0);
            vs.w = r1.w;
            vk.x = 0.0f;
            vk.y = fn_800A7370(o->data, STR(0x16D));
            vk.z = fn_800A7370(o->data, STR(0x176));
            fn_80312654(&mm, 0x79, 0.017453292f * fn_8001E064(o->m58));
            fn_80312DB4(&mm, &vk, &vk);
            fn_80313460(&vs.v, &vk, &vs.v);
            vt.w = vs.w;
            f32 h = vt.v.y - va.v.y;
            if (h > 0.0f) {
                Jump(c, h, d);
                c->m50 |= 0x100000;
            }
        }
    }
    if (Ev(c, 0x45) && c->mdl != NULL) {
        int fr = (int)c->mdl->frame;
        int to = fn_80008E88(c->mdl, fr, 0x46);
        int d2 = to - fr;
        if (to >= 0) {
            vb.w = *(W3*)&c->m44;
            f32 h = -vb.v.y;
            Arc_Set(c, h, d2);
            c->m50 &= ~0x100000;
        }
    }
    if (Ev(c, 0xC)) fn_800BD294(c);
    if (Ev(c, 0x33)) {
        fn_800BD86C(c);
        c->m50 &= ~0xC;
    }
    if (Ev(c, 0x34)) fn_800BDD94(c);
    if (Ev(c, 0x36)) c->m50 |= 0xC;
    if (Ev(c, 0x47)) c->m50 &= ~4;
    if (Ev(c, 0x48)) c->m50 |= 4;
}
}
