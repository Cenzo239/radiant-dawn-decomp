#include "game/rG_800A3D88/types.h"

// Battle character per-frame update: animation, tweened position offsets and velocity.
extern "C" {
typedef f32 Mt[3][4];
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct Mdl { u32 flags; };
struct Anm { u8 p[8]; u16 m8; };
struct Tw { int mode; f32 m4, m8, mc, m10, m14; };
struct ChrU {
    u8 p[0x30];
    Mdl* mdl;
    u8 p34[0x44 - 0x34];
    Vec m44;
    u32 m50;
    u8 p54[4];
    s16 m58;
    u8 p5a[4];
    s8 m5e;
    u8 p5f[0x78 - 0x5F];
    void* data;
    Anm* m7c;
    ChrU* m80;
    u8 p84[8];
    Tw* m8c;
    Tw* m90;
};
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
f32 fn_800081B4(Mdl*);
int fn_800B5AB8(ChrU*);
int fn_800B1B48(ChrU*, int, int, u16, int);
void fn_800B9D18(ChrU*);
void fn_800B951C(ChrU*);
f32 fn_80006CF8();
f32 fn_8001EF30(f32, f32, f32, f32);
f32 fn_8001EBC8(int, f32, f32, f32, f32);
f32 fn_8001ECE4(int, f32, f32, f32, f32);
f32 fn_8001EDF8(int, f32, f32, f32, f32);
void fn_800B33F4(ChrU*, int);
f32 fn_800A7370(void*, const char*);
f32 fn_8001E064(int);
void fn_80312654(Mt, int, f32);
void fn_80312DB4(Mt, Vec*, Vec*);
void fn_803134A8(Vec*, Vec*, f32);
void fn_800B8BC4(ChrU*);
void fn_800B99DC(ChrU*);
int fn_80007630(Mdl*, const char*);
int fn_800B4000(ChrU*, int, Vec*, int, int);
void fn_800B0CD4(ChrU*);
static inline BOOL Done(ChrU* c) {
    Mdl* m = c->mdl;
    if (m == NULL) return 1;
    Anm* a = c->m7c;
    if (a == NULL) return 1;
    if (a->m8 & 1) return 1;
    if (m->flags & 2) return 1;
    f32 f;
    if (m == NULL) f = 0.0f;
    else f = fn_800081B4(m);
    return f >= (f32)fn_800B5AB8(c);
}
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
static inline void Add1(ChrU* c, Vec* a, f32 x, f32 y, f32 z) {
    f32 rz = a->z + z;
    f32 ry = a->y + y;
    c->m44.x = a->x + x;
    c->m44.z = rz;
    c->m44.y = ry;
}
static inline void Add2(ChrU* c, Vec* a, f32 x, f32 y, f32 z) {
    f32 rz = a->z + z;
    f32 ry = a->y + y;
    c->m44.x = a->x + x;
    c->m44.z = rz;
    c->m44.y = ry;
}
static inline void Add3(ChrU* c, Vec* a, f32 x, f32 y, f32 z) {
    z = a->z + z;
    y = a->y + y;
    c->m44.x = a->x + x;
    c->m44.y = y;
    c->m44.z = z;
}
static inline int Node(ChrU* c, const char* const& n) {
    int k;
    if (c->mdl == NULL) k = -1;
    else { int t = fn_80007630(c->mdl, n); k = t; }
    return k;
}
void fn_800BE3B4(ChrU* c) {
    Mt m;
    Vec a3, q, p2, p1, v38, v, t, r, z;
    Tw* w;
    if (c->data == NULL) return;
    if (c->mdl == NULL) return;
    if (c->m5e >= 0) {
        if (Done(c)) fn_800B1B48(c, c->m5e, -1, 0xFFFF, -1);
    }
    fn_800B9D18(c);
    fn_800B951C(c);
    w = c->m8c;
    if (!(w->m10 >= w->m14)) {
        Step(w);
        w = c->m8c;
        f32 d = w->mc - w->m8;
        *(W3*)&p1 = *(W3*)&c->m44;
        Add1(c, &p1, d, 0.0f, 0.0f);
        fn_800B33F4(c, 1);
    }
    w = c->m90;
    if (!(w->m10 >= w->m14)) {
        Step(w);
        w = c->m90;
        f32 d = w->mc - w->m8;
        *(W3*)&p2 = *(W3*)&c->m44;
        Add2(c, &p2, 0.0f, d, 0.0f);
        fn_800B33F4(c, 1);
    }
    if (c->m50 & 0x80000) {
        W3* vp;
        if (c->data == NULL) {
            *(u32*)&z.x = 0;
            *(u32*)&z.y = 0;
            *(u32*)&z.z = 0;
            *(u32*)&v.x = 0;
            *(u32*)&v.y = 0;
            *(u32*)&v.z = 0;
            vp = (W3*)&v;
        } else {
            *(u32*)&q.x = 0;
            *(u32*)&q.y = 0;
            *(u32*)&q.z = 0;
            q.z = fn_800A7370(c->data, STR(0x1CE));
            fn_80312654(m, 0x79, 0.017453292f * fn_8001E064(c->m58));
            fn_80312DB4(m, &q, &q);
            *(W3*)&v = *(W3*)&q;
            vp = (W3*)&v;
        }
        *(W3*)&t = *vp;
        fn_803134A8(&t, &t, fn_80006CF8());
        *(W3*)&v38 = *(W3*)&t;
        *(W3*)&a3 = *(W3*)&c->m44;
        Add3(c, &a3, v38.x, v38.y, v38.z);
        fn_800B33F4(c, 1);
    }
    fn_800B8BC4(c);
    fn_800B99DC(c);
    if (c->mdl != NULL) {
        ChrU* o = c->m80;
        if (o != NULL && !(o->m50 & 1) && (c->m50 & 0x40)) {
            fn_800B4000(o, Node(o, STR(0x26)), &r, -1, 0);
        }
    }
    fn_800B0CD4(c);
    fn_800B33F4(c, 1);
}
}
