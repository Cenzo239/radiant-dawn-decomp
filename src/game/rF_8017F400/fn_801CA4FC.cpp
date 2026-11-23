#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct Mdl { u32 flags; u8 pad[0x58]; f32 x5C; u8 pad60[0x18]; f32 x78; } Mdl;
typedef struct MInn { u8 pad[0xA]; s16 xA; u8 padC[0xAC]; u32 xB8; u8 padBC[0]; } MInn;
typedef struct MObj {
    u8 x0;
    u8 pad1[3];
    s8 x4, x5, x6, x7;
    u8 pad8[4];
    f32 xC;
    MInn* x10;
    Mdl x14;
} MObj;
typedef struct MCol { u8 pad[0x1C]; u8 r, g, b, a; } MCol;
extern void fn_8000866C(void*, f32);
extern void fn_80007C58(void*);
extern void* fn_8013B9A8(void);
extern void* fn_801379F8(void*, int);
extern void fn_8012D908(void*);
extern void fn_800081D4(void*);
extern void fn_800F15AC(void*, f32, f32, f32);
extern void fn_80083DC4(void*, int);
extern void fn_80083B78(void*);
extern BOOL fn_80008C98(void*, int);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void* fn_800893E4(void*, void*, void*);
extern void* fn_800811E4(void*, void*);
extern void fn_80081A90(void*);
extern void fn_801CA674(void* p, void* arg);
extern u8 lbl_8038ACF8[];
extern u8 lbl_8038AD38[];
extern f32 fn_8001EBC8(int, f32, f32, f32, f32);
extern void fn_801CC5CC(void*, f32, f32, f32, f32);
extern void fn_80008F10(void*, u8, u8, u8);
extern void fn_80008F20(void*, u8);

void fn_801CA4FC(MObj* m, int f) {
    m->x0 |= 8;
    fn_8000866C(&m->x14, -1.0f);
    fn_80007C58(&m->x14);
    if (f) fn_8012D908(fn_801379F8(fn_8013B9A8(), 1));
}
void fn_801CA568(MObj* m, int f) {
    m->x0 &= ~8;
    fn_8000866C(&m->x14, 0.0f);
    fn_80007C58(&m->x14);
    if (f) fn_8012D908(fn_801379F8(fn_8013B9A8(), 1));
}
Vec3 fn_801CA5D4(MObj* m) {
    Vec3 v;
    int a = m->x4 + m->x6 + 1;
    int b = m->x5 + m->x7 + 1;
    v.x = 0.5f * a;
    v.y = 0.5f * b;
    v.z = m->xC;
    return v;
}
typedef struct PX {
    u8 pad[0x30];
    MObj* m;
    Mdl* x34;
    f32 x38, x3C, x40;
    int x44;
    u8 x48;
    u8 pad49[3];
    int x4C;
} PX;
void fn_801CA858(PX* p) {
    Mdl* a = &p->m->x14;
    fn_800081D4(a);
    fn_80007C58(a);
    fn_800F15AC(p->x34, p->x38, p->x3C, p->x40);
    if (a->flags & 2) {
        MInn* in = p->m->x10;
        if (p->x44 == 5 && !(in->xB8 & 0x1000000)) {
            fn_80083DC4(p, 10);
        } else {
            fn_80083B78(p);
        }
    } else if (fn_80008C98(a, 8)) {
        p->x48 = 1;
        fn_80083B78(p);
    }
}
void fn_801CA920(PX* p) {
    Mdl* a = &p->m->x14;
    fn_800081D4(a);
    fn_80007C58(a);
    p->x4C++;
    a->x78 = fn_8001EF30(1.0f, 0.0f, 60.0f, p->x4C);
    if (p->x4C >= 0x3C) {
        fn_80083B78(p);
        return;
    }
    fn_80083B78(p);
}
void fn_801CAA24(MObj* m, void* parent, int k) {
    if (m->x10->xB8 & 0x200) {
        Mdl* a = &m->x14;
        switch (k) {
        case 3:
            fn_8000866C(a, 0.0f);
            fn_80007C58(a);
            a->x5C = 1.0f;
            break;
        case 4:
            fn_8000866C(a, -1.0f);
            fn_80007C58(a);
            a->x5C = 1.0f;
            break;
        default: {
            PX* p = (PX*)fn_800893E4(lbl_8038ACF8, (void*)fn_801CA674, m);
            if (p) {
                if ((u32)k == 5 && p->x44 == 5) break;
                fn_80083DC4(p, 0);
            } else {
                p = (PX*)fn_800811E4(lbl_8038ACF8, parent);
            }
            p->x34 = a;
            p->m = m;
            p->x44 = k;
            p->x48 = 0;
            p->x4C = 0;
            p->x38 = (f32)(m->x4 + m->x6) / 2.0f;
            p->x3C = (f32)(m->x5 + m->x7) / 2.0f;
            p->x40 = m->xC;
        }
        }
    }
}
typedef struct PY {
    u8 pad[0x30];
    MInn* m;
    u8 pad34[4];
    f32 x38;
    int x3C, x40;
    f32 x44, x48;
} PY;
static inline s16 Fx(f32 x) { return 64.0f * x; }
void fn_801CAC38(PY* p) {
    p->m->xA = Fx(p->x48);
}
void fn_801CAC64(PY* p) {
    f32 v;
    p->x40++;
    v = fn_8001EBC8(2, p->x44, p->x48, p->x3C, p->x40);
    p->m->xA = 64.0f * (int)v;
    fn_801CC5CC(p->m, 0.0f, 0.0f, 0.0f, 0.0f);
    if (p->x3C == p->x40) fn_80083B78(p);
}
void fn_801CAD54(void* m, void* parent, int k, f32 v) {
    void* e = fn_800893E4(lbl_8038AD38, (void*)fn_801CA674, m);
    PY* p;
    if (e) fn_80081A90(e);
    p = (PY*)fn_800811E4(lbl_8038AD38, parent);
    p->x38 = v;
    p->x3C = k;
    p->m = (MInn*)m;
}
typedef struct RGBA { u8 r, g, b, a; } RGBA;
#ifdef __cplusplus
}
struct C4 { u8 r, g, b, a;
  C4() {}
  C4(const C4& o) { r = o.r; g = o.g; b = o.b; a = o.a; }
  C4& operator=(const C4& o) { r = o.r; g = o.g; b = o.b; a = o.a; return *this; }
};
extern "C" {
#endif
typedef struct PZ { u8 pad[0x30]; MCol* m; int x34; u8 pad38[4]; C4 x3C; RGBA x40; } PZ;
void fn_801CAE28(PZ* p) {
    RGBA c = p->x40;
    Mdl* a = &((MObj*)p->m)->x14;
    fn_80008F10(a, c.r, c.g, c.b);
    fn_80008F20(a, c.a);
}
}
