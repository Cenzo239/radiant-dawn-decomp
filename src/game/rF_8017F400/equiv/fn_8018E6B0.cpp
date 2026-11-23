/* symcheck: r21 review, flag was an artefact. fn_8018E6B0: (a) runtime helper names; 2 blocks: stale r8/r9
   (texture size temporaries) before fn_801BC88C (reads r3-r7, f1-f8). See docs/SCHED_REVIEW.md. */
/* r20: `sched` (check_regs.py). Copy of wip/fn_8018E6B0.cpp. Moved instructions (dd.py -u), in the two bar-piece
   blocks before fn_801BC88C: `li r4/r6/r7`, constant `lfd`/`lfs` loads, two `lhz` of the texture size and the
   int-to-float conversions through the stack slots 0x20/0x28. For each slot the store, load, store, load order is the
   same in both versions, so each conversion reads the value it was given. */
/* Config menu cursor draw: slide, pulsing alpha and a three-piece bar. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct GXColor2 { u8 r, g, b, a; } GXColor2;
typedef struct TexH { u16 x0, x2; } TexH;
typedef struct Cfg { u8 pad[0x30]; void* arch; u8 pad34[0x49 - 0x34]; u8 x49; s16 x4a, x4c, x4e, x50, x52, x54; } Cfg;
typedef s64 OSTime;
extern OSTime OSGetTime(void);
#define OS_BUS_CLOCK (*(u32*)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
extern double fn_80295940(double);
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_801BCA5C(f32);
extern void fn_800712E8(int, int, int);
extern void* fn_80006A0C(void*, int);
extern u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, GXColor2* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
static inline void Dr2(void* arch, int tile, GXColor2* c, GXColor2* t, f32 x1, f32 y1, f32 x2, f32 y2, u16 tw, u16 th) {
    *(u32*)t = *(u32*)c;
    fn_801BC88C(arch, tile, t, 0x11, 0, x1, y1, x2, y2, 0.0f, 0.0f, tw, th);
}
static inline void Dr2b(void* arch, int tile, GXColor2* c, GXColor2* t, f32 x1, f32 y1, f32 x2, f32 y2, u16 th, u16 tw) {
    *(u32*)t = *(u32*)c;
    fn_801BC88C(arch, tile, t, 0x11, 0, x1, y1, x2, y2, 0.0f, 0.0f, tw, th);
}
static inline void Dr2c(void* arch, int tile, GXColor2* c, GXColor2* t, f32 x1, f32 y1, f32 x2, f32 y2, f32 tw, f32 th) {
    *(u32*)t = *(u32*)c;
    fn_801BC88C(arch, tile, t, 0x11, 0, x1, y1, x2, y2, 0.0f, 0.0f, tw, th);
}
static inline void Dr2d(void* arch, int tile, GXColor2* c, GXColor2* t, f32 x1, f32 y1, f32 x2, f32 y2, f32 th, f32 tw) {
    *(u32*)t = *(u32*)c;
    fn_801BC88C(arch, tile, t, 0x11, 0, x1, y1, x2, y2, 0.0f, 0.0f, tw, th);
}
static inline void Dr2e(void* arch, int tile, GXColor2* c, GXColor2* t, f32 x1, f32 y1, f32 x2, f32 y2, TexH* s) {
    *(u32*)t = *(u32*)c;
    fn_801BC88C(arch, tile, t, 0x11, 0, x1, y1, x2, y2, 0.0f, 0.0f, s->x2, s->x0);
}
void fn_8018E6B0(Cfg* c) {
    /*P*/
    int a;
    void* ar1;
    u16 w3;
    u16 h1;
    u16 w1;
    int t0;
    void* ar3;
    void* ar2;
    u16 h3;
/*E*/
    if (c->x49 != 0) {
        s16 d = 4;
        c->x49--;
        t0 = d - c->x49;
        c->x4a = fn_8017F68C(4, c->x4e, c->x52, t0, d);
        c->x4c = fn_8017F68C(4, c->x50, c->x54, t0, d);
    }
    fn_801BCA5C(-10.0f);
    fn_800712E8(c->x4a + 0x1c, c->x4c + 3, 1);
    fn_801BCA5C(10.0f);
    {
        f32 pi = 3.141592f;
        f32 v = (OSGetTime() / (OS_TIMER_CLOCK / 1000)) % 1500;
        u32 hi = 0xff;
        u32 lo = 0xa2;
        f32 d = (f32)hi - (f32)lo;
        f32 q = v / 1500.0f;
        f32 s = fn_80295940(2.0f * pi * q);
        a = 0.5f * (d * (1.0f + s)) + (f32)lo;
    }
    fn_801BCA5C(-1.0f);
    {
        ar1 = c->arch;
        f32 y = c->x4c + 3;
        TexH** t = (TexH**)fn_80006A0C(ar1, 1);
        w1 = (*t)->x2; h1 = (*t)->x0;
        GXColor2 k, kt;
        u8* p = fn_800CD204(1);
        k.r = p[0]; k.g = p[1]; k.b = p[2]; k.a = a;
        t = (TexH**)fn_80006A0C(ar1, 1);
        Dr2b(ar1, 1, &k, &kt, 16.0f, y, 16.0f + w1, y + h1, (*t)->x0, (*t)->x2);
#undef t
    }
    {
        ar2 = c->arch;
        f32 y = c->x4c + 3;
        TexH** t;
        GXColor2 kt, k;
        u8* p = fn_800CD204(1);
        k.r = p[0]; k.g = p[1]; k.b = p[2]; k.a = a;
        t = (TexH**)fn_80006A0C(ar2, 2);
        Dr2b(ar2, 2, &k, &kt, 80.0f, y, 504.0f, y + 32.0f, (*t)->x0, (*t)->x2);
#undef t
    }
    {
        ar3 = c->arch;
        f32 y = c->x4c + 3;
        TexH** t = (TexH**)fn_80006A0C(ar3, 3);
        w3 = (*t)->x2; h3 = (*t)->x0;
        GXColor2 k, kt;
        u8* p = fn_800CD204(1);
        k.r = p[0]; k.g = p[1]; k.b = p[2]; k.a = a;
        t = (TexH**)fn_80006A0C(ar3, 3);
        Dr2b(ar3, 3, &k, &kt, 504.0f, y, 504.0f + w3, y + h3, (*t)->x0, (*t)->x2);
#undef t
    }
    fn_801BCA5C(1.0f);
}
}
