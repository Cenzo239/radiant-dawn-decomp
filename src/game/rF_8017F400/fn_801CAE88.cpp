#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct RGBA { u8 r, g, b, a; } RGBA;
}
struct C4 { u8 r, g, b, a;
  C4& operator=(const RGBA& o) { r = o.r; g = o.g; b = o.b; a = o.a; return *this; }
};
extern "C" {
typedef struct MInn { u8 pad[0xB8]; u32 xB8; u8 padBC[0xCD - 0xBC]; u8 xCD; } MInn;
typedef struct MObj {
    u8 x0[0x10];
    MInn* x10;
    u8 x14[0xB9];
    u8 xCD;
} MObj;
typedef struct PZ { u8 pad[0x30]; MObj* m; int x34; int x38; union { u8 x3C; RGBA x3Cc; int x3Ci; }; union { C4 x40; int x40i; }; } PZ;
typedef struct PZ2 { u8 pad[0x30]; MObj* m; int x34; int x38; u8 x3C, x3D; u8 pad3E[2]; } PZ2;
extern void* fn_800893E4(void*, void*, void*);
extern void* fn_800811E4(void*, void*);
extern void fn_80081A90(void*);
extern void fn_801CA674(void* p, void* arg);
extern void fn_80083B78(void*);
extern void fn_80008F10(void*, u8, u8, u8);
extern void fn_80008F20(void*, u8);
extern f32 fn_8001EBC8(int, f32, f32, f32, f32);
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern void* fn_8013B9A8(void);
extern void fn_8013B2B8(void*);
extern void fn_8013B8D0(void*);
extern void fn_80017DF0(void*);
extern u8 lbl_8038AD60[], lbl_8038ADA8[], lbl_8038ADD0[];
static inline void Refresh(void) {
    void* r = fn_8013B9A8();
    if (r) {
        fn_8013B2B8(r);
        fn_8013B8D0(r);
    }
}
#define SETCOL(NAME, CLS) \
void NAME(MObj* m, void* parent, RGBA c, int t) { \
    void* e = fn_800893E4(CLS, (void*)fn_801CA674, m); \
    if (e) fn_80081A90(e); \
    if (t == 0) { \
        RGBA z = c; \
        void* a = m->x14; \
        fn_80008F10(a, z.r, z.g, z.b); \
        fn_80008F20(a, z.a); \
    } else { \
        PZ* p = (PZ*)fn_800811E4(CLS, parent); \
        p->x40 = c; \
        p->x38 = t; \
        p->m = m; \
    } \
}
SETCOL(fn_801CB0A4, lbl_8038AD60)
void fn_801CB4B8(PZ* p) {
    p->m->xCD = p->x40i;
    Refresh();
}
void fn_801CB504(PZ* p) {
    f32 v;
    p->x34++;
    v = fn_8001ECE4(2, p->x3Ci, p->x40i, p->x38, p->x34);
    p->m->xCD = (int)v;
    Refresh();
    if (p->x38 == p->x34) fn_80083B78(p);
}
void fn_801CB5EC(MObj* m, void* parent, int v, int t) {
    void* e = fn_800893E4(lbl_8038ADA8, (void*)fn_801CA674, m);
    if (e) fn_80081A90(e);
    if (t == 0) {
        m->xCD = v;
        Refresh();
    } else {
        PZ* p = (PZ*)fn_800811E4(lbl_8038ADA8, parent);
        p->x40i = v;
        p->x38 = t;
        p->m = m;
    }
}
void fn_801CB6D4(PZ* p) {
    RGBA c = p->x3Cc;
    void* a = p->m->x14;
    fn_80008F10(a, c.r, c.g, c.b);
    fn_80008F20(a, c.a);
}
SETCOL(fn_801CB920, lbl_8038ADD0)
void fn_801CCCA0(MObj* m) {
    if (m->x10->xB8 & 0x400) fn_80017DF0(m->x14);
}
typedef struct Pt { f32 x, y, z; } Pt;
typedef struct PV { u8 pad[0x30]; struct { u8 pad[0xA4]; void* xA4; }* x30; } PV;
extern char lbl_8036EA00[];
extern BOOL fn_800B41C0(void*, const char*, Pt*, int, int);
extern void fn_800E48C8(void*, Pt*);
void fn_801CD994(PV* p) {
    Pt v;
    if (fn_800B41C0(p->x30->xA4, lbl_8036EA00, &v, -1, 0)) {
        Pt t = v;
        fn_800E48C8(p, &t);
    }
}
extern u32 fn_8030585C(int, int, int, int, int);
extern void* fn_80078D9C(u32, const char*, int);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);
extern void* fn_80007F3C(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80014E24(void*, const char*, void*, p32arg);
#else
extern void fn_80014E24(void*, const char*, void*, int);
#endif
extern void fn_801CDC14(void* p);
typedef struct NN { u8 pad[0x5C]; f32 x5C; u8 pad60[0x28]; void* x88; } NN;
typedef struct PW { u8 pad[0x30]; NN** x30; u8 pad34[0xB]; u8 x3F; u8 pad40[0x20]; void* x60; } PW;
void fn_801CE068(PW* p) {
    u32 sz;
    NN* n = *p->x30;
    sz = fn_8030585C(0x80, 0x20, 6, 0, 0);
    p->x60 = fn_80078D9C(sz, lbl_8036EA00 + 0x24, 0);
    memset(p->x60, 0, sz);
    DCFlushRange(p->x60, sz);
    n->x88 = p;
    fn_80014E24(fn_80007F3C(n), lbl_8036EA00 + 0x25, (void*)fn_801CDC14, 2);
    if (p->x3F) n->x5C = 2.0f;
}
typedef struct UA { u8 pad[0x3F0]; struct UB* x3F0; } UA;
typedef struct UB { u8 pad[0xEC]; void* xEC; } UB;
typedef struct EE { UA* a; s16 x4, x6; s16 x8, xA; } EE;
extern const char* fn_80118C44(void*);
static inline UB* EGet(EE* e) {
    if (e->a) return e->a->x3F0;
    return 0;
}
BOOL fn_801CE5B8(EE* e) {
    if (EGet(e)) {
        if (e->x6 <= 0) return 1;
        if (e->xA <= 0) return 1;
    }
    return 0;
}
const char* fn_801CE670(EE* e) {
    UB* b = EGet(e);
    if (b) return fn_80118C44(b->xEC);
    return 0;
}

extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_8001EF44(int, int, f32, f32);
typedef struct PQ { u8 pad[0x30]; MObj* m; int x34; int x38; RGBA a; RGBA b; } PQ;
static inline void SetCol(void* a, RGBA c) {
    fn_80008F10(a, c.r, c.g, c.b);
    fn_80008F20(a, c.a);
}
void fn_801CAE88(PQ* p) {
    RGBA c;
    p->x34++;
    c.r = (int)fn_8001EF30(p->a.r, p->b.r, p->x38, p->x34);
    c.g = (int)fn_8001EF30(p->a.g, p->b.g, p->x38, p->x34);
    c.b = (int)fn_8001EF30(p->a.b, p->b.b, p->x38, p->x34);
    c.a = (int)fn_8001EF30(p->a.a, p->b.a, p->x38, p->x34);
    SetCol(p->m->x14, c);
    if (p->x38 == p->x34) fn_80083B78(p);
}
void fn_801CB734(PQ* p) {
    RGBA c;
    int t;
    p->x34++;
    t = fn_8001EF44(p->x38, p->x34, 0.0f, 256.0f);
    c.r = (int)fn_8001EF30(p->a.r, p->b.r, 256.0f, t);
    c.g = (int)fn_8001EF30(p->a.g, p->b.g, 256.0f, t);
    c.b = (int)fn_8001EF30(p->a.b, p->b.b, 256.0f, t);
    c.a = (int)fn_8001EF30(p->a.a, p->b.a, 256.0f, t);
    SetCol(p->m->x14, c);
    if (p->x38 == p->x34) fn_80083B78(p);
}
}
