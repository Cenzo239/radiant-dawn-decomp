/* Draws one coloured map tile: a quad when it is flat, otherwise a fan around its centre. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off

struct C4 { u8 r, g, b, a; };
union Fifo {
    u8 u8;
    f32 f32;
};
#define FIFO (*(volatile Fifo*)0xCC008000)

extern "C" {
extern u8 lbl_803EC898[];
extern u8 fn_801147E4(void*, int, int);
extern f32 fn_80114728(void*, int, int);
extern f32 fn_801146A8(void*, int, int, int);
extern void fn_80304314(int, int, int);

static inline void Pos(f32 x, f32 z, f32 y) {
    volatile f32* p = (volatile f32*)0xCC008000;
    *p = x;
    *p = z;
    *p = y;
}
static inline void Col(u8 r, u8 g, u8 b, u8 a) {
    volatile u8* p = (volatile u8*)0xCC008000;
    *p = r;
    *p = g;
    *p = b;
    *p = a;
}

void fn_8013EA08(s8 x, s8 y, C4* c, f32 r) {
    f32 ax = (f32)x;
    f32 az = 1.0f + (f32)y - r;
    f32 bx = ax + r;
    f32 bz = (f32)(y + 1);
    if (fn_801147E4(lbl_803EC898, x, y)) {
        fn_80304314(0x98, 0, 4);
        Pos(ax, az, fn_801146A8(lbl_803EC898, x, y, 0));
        Col(c[0].r, c[0].g, c[0].b, c[0].a);
        Pos(bx, az, fn_801146A8(lbl_803EC898, x, y, 1));
        Col(c[1].r, c[1].g, c[1].b, c[1].a);
        Pos(ax, bz, fn_801146A8(lbl_803EC898, x, y, 2));
        Col(c[2].r, c[2].g, c[2].b, c[2].a);
        Pos(bx, bz, fn_801146A8(lbl_803EC898, x, y, 3));
        Col(c[3].r, c[3].g, c[3].b, c[3].a);
    } else {
        f32 mx = 0.5f * (ax + bx);
        f32 mz = 0.5f * (az + bz);
        f32 my = fn_80114728(lbl_803EC898, x, y);
        int cr = (c[0].r + c[1].r + c[2].r + c[3].r) >> 2;
        int cg = (c[3].g + c[2].g + (c[0].g + c[1].g)) >> 2;
        int cb = (c[3].b + c[2].b + (c[0].b + c[1].b)) >> 2;
        int ca = (c[3].a + c[2].a + (c[0].a + c[1].a)) >> 2;
        fn_80304314(0xA0, 0, 6);
        Pos(mx, mz, my);
        Col(cr, cg, cb, ca);
        Pos(ax, az, fn_801146A8(lbl_803EC898, x, y, 0));
        Col(c[0].r, c[0].g, c[0].b, c[0].a);
        Pos(bx, az, fn_801146A8(lbl_803EC898, x, y, 1));
        Col(c[1].r, c[1].g, c[1].b, c[1].a);
        Pos(bx, bz, fn_801146A8(lbl_803EC898, x, y, 3));
        Col(c[3].r, c[3].g, c[3].b, c[3].a);
        Pos(ax, bz, fn_801146A8(lbl_803EC898, x, y, 2));
        Col(c[2].r, c[2].g, c[2].b, c[2].a);
        Pos(ax, az, fn_801146A8(lbl_803EC898, x, y, 0));
        Col(c[0].r, c[0].g, c[0].b, c[0].a);
    }
}
}
