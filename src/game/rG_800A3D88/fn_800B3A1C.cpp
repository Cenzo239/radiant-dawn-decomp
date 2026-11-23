#include "game/rG_800A3D88/types.h"

// Battle character: root position for the current animation frame, with optional lift.
extern "C" {
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct Anm { u8 p[8]; u16 m8; u8 pa; u8 mb; };
struct Mo { u8 p[0x14]; int m14; };
struct ChrU { u8 p[0x30]; void* mdl; u8 p34[0x5A - 0x34]; s16 m5a; u8 p5c[0x78 - 0x5C]; void* data; Anm* m7c; };
struct Sc { u8 p[0x34]; u8 m34; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_80007630(void*, const char*);
int fn_800B4000(ChrU*, int, Vec*, int, int);
f32 fn_8001E064(int);
f32 fn_800081B4(void*);
Mo* fn_80007F10(void*);
int fn_800B5AB8(ChrU*);
f32 fn_8001EF30(f32, f32, f32, f32);
f32 fn_800A7370(void*, const char*);
Sc* fn_800AAD2C();
static inline int Node(ChrU* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
#define ZERO(v) *(u32*)&v.x = 0; *(u32*)&v.y = 0; *(u32*)&v.z = 0
static inline void PosI(ChrU* c, int i, Vec* out) {
    Vec v, t;
    ZERO(t);
    fn_800B4000(c, Node(c, STR(0x26)), &t, i, 0);
    *(W3*)&v = *(W3*)&t;
    v.y = fn_8001E064(c->m5a);
    *(W3*)out = *(W3*)&v;
}
static inline void PosF(ChrU* c, f32 f, Vec* out) {
    Vec v, t;
    ZERO(t);
    fn_800B4000(c, Node(c, STR(0x26)), &t, (int)f, 0);
    *(W3*)&v = *(W3*)&t;
    v.y = fn_8001E064(c->m5a);
    *(W3*)out = *(W3*)&v;
}
static inline void Full(ChrU* c, int i, Vec* p) {
    Vec r;
    PosI(c, i, &r);
    *p = r;
}
static inline void XF(ChrU* c, f32 f, Vec* p) {
    Vec r;
    PosF(c, f, &r);
    p->x = r.x;
}
static inline void XI(ChrU* c, int i, Vec* p) {
    Vec r;
    PosI(c, i, &r);
    p->x = r.x;
}
static inline void FullF(ChrU* c, f32 f, Vec* p) {
    Vec r;
    PosF(c, f, &r);
    *p = r;
}
static inline int Len(ChrU* c) {
    if (c->mdl == NULL) return 0;
    Mo* m = fn_80007F10(c->mdl);
    if (m == NULL) return 0;
    return m->m14;
}
Vec fn_800B3A1C(ChrU* c, int flag, int idx) {
    Vec p, a, b;
    if (!fn_800B4000(c, Node(c, STR(0x17F)), &p, idx, 0)) Full(c, idx, &p);
    Anm* m = c->m7c;
    if (m != NULL && (m->m8 & 0x200)) {
        f32 fr;
        if (c->mdl == NULL) fr = 0.0f;
        else fr = fn_800081B4(c->mdl);
        f32 s = Len(c);
        f32 e = fn_800B5AB8(c);
        switch (c->m7c->mb) {
        case 0:
            XF(c, s, &p);
            break;
        case 1:
            XF(c, e, &p);
            break;
        case 2:
            FullF(c, s, &a);
            FullF(c, e, &b);
            p.x = fn_8001EF30(a.x, b.x, e - s, fr - s);
            break;
        default:
            XI(c, idx, &p);
            break;
        }
        p.z = 0.0f;
    }
    if (flag != 0) p.y += fn_800A7370(c->data, STR(0x183));
    Sc* sc = fn_800AAD2C();
    if (sc != NULL) {
        f32 lim = (int)sc->m34;
        if (p.x < -lim) p.x = -lim;
        if (p.x > lim) p.x = lim;
    }
    return p;
}
}
