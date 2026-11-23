/* functionally equal (regs). Helpers from ../fn_801CAE88.cpp, body from wip/fn_801CAE88.cpp */
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





typedef struct Pt { f32 x, y, z; } Pt;
typedef struct PV { u8 pad[0x30]; struct { u8 pad[0xA4]; void* xA4; }* x30; } PV;
extern char lbl_8036EA00[];
extern BOOL fn_800B41C0(void*, const char*, Pt*, int, int);
extern void fn_800E48C8(void*, Pt*);

extern u32 fn_8030585C(int, int, int, int, int);
extern void* fn_80078D9C(u32, const char*, int);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);
extern void* fn_80007F3C(void*);
extern void fn_80014E24(void*, const char*, void*, int);
extern void fn_801CDC14(void* p);
typedef struct NN { u8 pad[0x5C]; f32 x5C; u8 pad60[0x28]; void* x88; } NN;
typedef struct PW { u8 pad[0x30]; NN** x30; u8 pad34[0xB]; u8 x3F; u8 pad40[0x20]; void* x60; } PW;

typedef struct UA { u8 pad[0x3F0]; struct UB* x3F0; } UA;
typedef struct UB { u8 pad[0xEC]; void* xEC; } UB;
typedef struct EE { UA* a; s16 x4, x6; s16 x8, xA; } EE;
extern const char* fn_80118C44(void*);
static inline UB* EGet(EE* e) {
    if (e->a) return e->a->x3F0;
    return 0;
}



extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_8001EF44(int, int, f32, f32);
typedef struct PQ { u8 pad[0x30]; MObj* m; int x34; int x38; RGBA a; RGBA b; } PQ;
static inline void SetCol(void* a, RGBA c) {
    fn_80008F10(a, c.r, c.g, c.b);
    fn_80008F20(a, c.a);
}




void fn_801CB1A0(PZ2* p) {
    int v;
    p->x34++;
    if (p->x3C > p->x3D) {
        v = fn_8001EBC8(2, p->x3C, p->x3D, p->x38, p->x34);
    } else {
        v = fn_8001ECE4(2, p->x3C, p->x3D, p->x38, p->x34);
    }
    fn_80008F20(p->m->x14, (u8)v);
    if (p->x38 == p->x34) fn_80083B78(p);
}

}
