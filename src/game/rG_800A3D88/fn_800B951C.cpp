#include "game/rG_800A3D88/types.h"

// Battle character: finish a slide-in movement, then fix up the root position.
extern "C" {
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct Mdl { u8 p[0x78]; f32 m78; };
struct Tw { int mode; f32 m4, m8, mc, m10, m14; };
struct ChrU {
    u8 p[0x30];
    Mdl* mdl;
    u8 p34[0x44 - 0x34];
    Vec m44;
    u32 m50;
    u8 p54[0x61 - 0x54];
    u8 m61;
    u8 p62[2];
    f32 m64;
    u8 p68[0x94 - 0x68];
    Tw* m94;
};
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
f32 fn_80006CF8();
f32 fn_8001EF30(f32, f32, f32, f32);
f32 fn_8001EBC8(int, f32, f32, f32, f32);
f32 fn_8001ECE4(int, f32, f32, f32, f32);
f32 fn_8001EDF8(int, f32, f32, f32, f32);
void fn_800B33F4(ChrU*, int);
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChrU*, int, Vec*, int, int);
void fn_800081D4(Mdl*);
void fn_80007DE8(Mdl*);
void fn_80008B50(Mdl*);
void fn_800B9884(ChrU*);
static inline void Step(Tw* w) {
    w->m10 += fn_80006CF8();
    if (w->m10 >= w->m14) w->m10 = w->m14;
    w->m8 = w->mc;
    switch (w->mode) {
    case 0:
        w->mc = fn_8001EF30(0.0f, w->m4, w->m14, w->m10);
        break;
    case 1:
        w->mc = fn_8001EBC8(2, 0.0f, w->m4, w->m14, w->m10);
        break;
    case 2:
        w->mc = fn_8001ECE4(2, 0.0f, w->m4, w->m14, w->m10);
        break;
    case 3:
        w->mc = fn_8001EDF8(2, 0.0f, w->m4, w->m14, w->m10);
        break;
    }
}
static inline void Add(ChrU* c, Vec* a, f32 x, f32 y, f32 z) {
    f32 rz = a->z + z;
    f32 ry = a->y + y;
    c->m44.x = a->x + x;
    c->m44.z = rz;
    c->m44.y = ry;
}
static inline int Node(ChrU* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
void fn_800B951C(ChrU* c) {
    Vec base, t, r, p, o;
    Tw* w;
    *(u32*)&r.x = 0;
    *(u32*)&r.y = 0;
    *(u32*)&r.z = 0;
    fn_800B4000(c, Node(c, STR(0x26)), &r, -1, 0);
    *(W3*)&base = *(W3*)&r;
    fn_800081D4(c->mdl);
    if (c->m50 & 0x100) {
        if (c->m64 < 0.0f) {
            c->m64 = 0.0f;
            goto no_slide;
        }
        c->m64 += fn_80006CF8();
        if (c->m64 >= c->m61) c->m64 = c->m61;
        c->mdl->m78 = fn_8001EDF8(2, 0.0f, 1.0f, c->m61, c->m64);
        fn_80007DE8(c->mdl);
        w = c->m94;
        Step(w);
        w = c->m94;
        f32 d = w->mc - w->m8;
        *(W3*)&p = *(W3*)&c->m44;
        Add(c, &p, d, 0.0f, 0.0f);
        fn_800B33F4(c, 1);
        if (c->m64 >= c->m61) {
            fn_80008B50(c->mdl);
            c->m50 &= ~0x100;
            c->m64 = 0.0f;
            w = c->m94;
            w->m4 = 0.0f;
            w->m8 = 0.0f;
            w->mc = 0.0f;
            w->m10 = 0.0f;
            w->m14 = 0.0f;
        }
        goto after;
    } else {
no_slide:
        fn_80007DE8(c->mdl);
    }
after:
    if (c->m50 & 0x800) {
        *(u32*)&o.x = 0;
        *(u32*)&o.y = 0;
        *(u32*)&o.z = 0;
        fn_800B4000(c, Node(c, STR(0x26)), &o, -1, 0);
        *(W3*)&t = *(W3*)&o;
        c->m44.x += base.x - t.x;
    }
    fn_800B9884(c);
}
}
