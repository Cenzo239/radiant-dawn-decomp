#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* map object init from the map stream */
typedef struct MDef { u8 pad[0xB8]; u32 fl; } MDef;
typedef struct MH { u32 fl; void* x4; u8 pad[0x54]; f32 x5C; u8 pad60[0xC8 - 0x74]; } MH;
typedef struct MObj {
    u8 x0, x1, x2, x3; s8 x4, x5, x6, x7;
    u16 x8; s16 xA; f32 xC; MDef* def;
    MH h;
    u32 xC8; u8 xCC, xCD, xCE, xCF;
} MObj;
typedef struct MMap { u8 pad[8]; u8* defs; u8 padC[0xB1 - 0xC]; u8 xB1; } MMap;
extern MMap* fn_8013B9A8(void);
extern void fn_80006E94(void*);
extern u8 fn_80109A18(void*);
extern u16 fn_80109A2C(void*);
extern f32 fn_80109AD0(void*);
extern void fn_80006F20(void*);
extern void* fn_80007F3C(void*);
extern void fn_80008F54(void*, int);
#if TARGET_PC
extern FE10_PROTO struct GEntry20 * fn_80008110(void*, const char*);
#else
extern int fn_80008110(void*, const char*);
#endif
extern int fn_80014D40(void*, const char*, int);
extern int fn_80014DE4(void*, int);
extern u8* fn_80007F10(void*);
extern int fn_80009D60(void*, int, void*);
extern u32 fn_80089ED0(void);
extern void fn_8000866C(void*, f32);
extern void fn_80007C58(void*);
extern int fn_800A05B0(int, int, int);
extern void fn_80008F5C(void*, int);
extern int fn_8000A168(void*, int, u16*);
extern char lbl_8036E9AC[];

static inline void L4(MObj* o, int& any) { int y; int x; for (y = o->x5; y <= o->x7; y++) { for (x = o->x4; x <= o->x6; x++) { if (fn_800A05B0(9, (s8)x, (s8)y)) any = 1; } } }
void* fn_801CBA60(MObj* o, void* st) {
    MMap* m = fn_8013B9A8();
    MH* h = &o->h;

    u16 di;
    u8 rot;
    MDef* d;
    void* mdl;

    f32 sc;
    fn_80006E94(h);
    o->x0 = fn_80109A18(&st);
    o->x1 = fn_80109A18(&st);
    o->x2 = fn_80109A18(&st);
    rot = fn_80109A18(&st);
    o->xCE = fn_80109A18(&st);
    o->xCF = fn_80109A18(&st);
    di = fn_80109A2C(&st);
    o->x4 = fn_80109A18(&st);
    o->x5 = fn_80109A18(&st);
    o->x6 = fn_80109A18(&st);
    o->x7 = fn_80109A18(&st);
    sc = fn_80109AD0(&st);
    o->x3 = fn_80109A18(&st);
    fn_80109A18(&st);
    fn_80109A18(&st);
    fn_80109A18(&st);
    d = (MDef*)(m->defs + di * 0xC0);
    o->x8 = 0;
    o->def = d;
    o->xC8 = 0;
    o->xCC = 0xFF;
    o->xCD = 0;
    o->xC = sc;
    o->xA = 64.0f * (f32)(0x168 - (rot * 0x168 >> 8));
    h->x4 = (u8*)d + 4;
    if (d->fl & 0x200) {
        h->fl |= 0x40000;
        fn_80006F20(h);
    }
    mdl = fn_80007F3C(h);
    switch (m->xB1) {
    case 0:
        fn_80008F54(h, 0x81);
        if (d->fl & 0x10) fn_80008F54(h, 0x80);
        if (d->fl & 0x80) fn_80008F54(h, 0x8B);
        if (d->fl & 0x40) fn_80008F54(h, 0x8C);
        if (d->fl & 0x20000) fn_80008F54(h, 0x8A);
        if (d->fl & 0x2000) {
            fn_80008F54(h, 0x93);
            if (fn_80008110(h, lbl_8036E9AC + 0x1D) == 0) h->fl |= 0x80, h->fl |= 0xA0000000;
        }
        if (d->fl & 0x800) fn_80008F54(h, 0x94);
        if (d->fl & 0x20) fn_80008F54(h, 0x95);
        break;
    case 1: case 2: case 3:
        fn_80008F54(h, 0x86);
        if (fn_80014D40(mdl, lbl_8036E9AC + 0x27, 0) >= 0) fn_80008F54(h, 0x82);
        if (d->fl & 0x4000000) fn_80008F54(h, 0x93);
        if (d->fl & 0x20) fn_80008F54(h, 0x95);
        if (d->fl & 0x80) fn_80008F54(h, 0x8B);
        break;
    }
    if (d->fl & 0x40) h->fl |= 0x30000;
    if (d->fl & 0x40020000) o->x0 |= 4;
    if (fn_80014DE4(mdl, 0x400) > 0) o->x0 |= 2;
    if (d->fl & 0x800000) {
        MH* g = &o->h;
        u8* a = fn_80007F10(g);
        if (a != 0) {
            u32 len = *(int*)(a + 0x18) - *(int*)(a + 0x14);
            if (d->fl & 0x4000) {
                void* tbl[0x40];
                int n = fn_80009D60(fn_80007F10(g), 0x37, tbl);
                int v;
                if (n > 0) v = *(u16*)tbl[n - 1];
                else v = -1;
                if (v > 0) len = v - *(int*)(a + 0x14);
            }
            fn_8000866C(g, (f32)(*(int*)(a + 0x14) + fn_80089ED0() % len));
            fn_80007C58(g);
        }
    }
    if (d->fl & 0x40000) {
        int any = 0;
        int i;
        int j;
        for (i = o->x4; i <= o->x6; i++) {
            if (fn_800A05B0(9, (s8)i, (s8)(o->x5 - 1))) any = 1;
            if (fn_800A05B0(9, (s8)i, (s8)(o->x7 + 1))) any = 1;
        }
        for (j = o->x5; j <= o->x7; j++) {
            if (fn_800A05B0(9, (s8)(o->x4 - 1), (s8)j)) any = 1;
            if (fn_800A05B0(9, (s8)(o->x6 + 1), (s8)j)) any = 1;
        }
        L4(o, any);
        if (!any) {
            fn_8000866C(&o->h, -1.0f);
            fn_80007C58(&o->h);
        }
    }
    fn_80008F5C(h, 0);
    {
    u8* a = fn_80007F10(h);
    if (a != 0) {
        u16 v;
        if (fn_8000A168(a, 0x19, &v) && v != 0) h->x5C = (f32)v / 100.0f;
        fn_80007C58(h);
    }
    }
    return st;
}
}
