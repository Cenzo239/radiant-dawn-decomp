/* Tiled textured quad through the GX FIFO. */
#include "game/rJ_800799AC/types.h"

#define F(c, o) (*(f32*)((c) + (o)))

typedef union {
    volatile u8 u8;
    volatile f32 f32;
} WGPipe;

extern "C" {

void fn_80304314(int prim, int fmt, int n);

void fn_80080CD4(u8* c, u8 r, u8 g, u8 b, u8 a) {
    WGPipe* gx = (WGPipe*)0xCC008000;
    f32 y0;
    f32 y1;
    f32 v0;
    f32 u1;
    f32 v1 = F(c, 0x2C);
    f32 x0;
    f32 x1;
    f32 u0;
    {
        f32 t = F(c, 0x1C);
        f32 m;
        y0 = F(c, 0x14);
        m = y0 + (v1 - t);
        v0 = t + F(c, 0x34);
        y1 = m - F(c, 0x34);
    }
    for (;;) {
        {
            f32 d;
            f32 lim = F(c, 0x24);
            if (y1 > lim) {
                d = y1 - lim;
                y1 = lim;
                v1 -= d;
            }
        }
        u1 = F(c, 0x28);
        {
            f32 t = F(c, 0x18);
            f32 m;
            x0 = F(c, 0x10);
            m = x0 + (u1 - t);
            u0 = t + F(c, 0x30);
            x1 = m - F(c, 0x30);
        }
        for (;;) {
            {
                f32 d;
                f32 lim = F(c, 0x20);
                if (x1 > lim) {
                    d = x1 - lim;
                    x1 = lim;
                    u1 -= d;
                }
            }
            fn_80304314(0x98, 0, 4);
            {
                f32 z = F(c, 8);
                gx->f32 = x0;
                gx->f32 = y0;
                gx->f32 = z;
            }
            gx->u8 = r;
            gx->u8 = g;
            gx->u8 = b;
            gx->u8 = a;
            gx->f32 = u0;
            gx->f32 = v0;
            {
                f32 z = F(c, 8);
                gx->f32 = x1;
                gx->f32 = y0;
                gx->f32 = z;
            }
            gx->u8 = r;
            gx->u8 = g;
            gx->u8 = b;
            gx->u8 = a;
            gx->f32 = u1;
            gx->f32 = v0;
            {
                f32 z = F(c, 8);
                gx->f32 = x0;
                gx->f32 = y1;
                gx->f32 = z;
            }
            gx->u8 = r;
            gx->u8 = g;
            gx->u8 = b;
            gx->u8 = a;
            gx->f32 = u0;
            gx->f32 = v1;
            {
                f32 z = F(c, 8);
                gx->f32 = x1;
                gx->f32 = y1;
                gx->f32 = z;
            }
            gx->u8 = r;
            gx->u8 = g;
            gx->u8 = b;
            gx->u8 = a;
            gx->f32 = u1;
            gx->f32 = v1;
            if (x1 >= F(c, 0x20)) {
                break;
            }
            u0 = F(c, 0x18);
            x0 = x1;
            x1 = x1 + (F(c, 0x28) - u0);
        }
        if (y1 >= F(c, 0x24)) {
            break;
        }
        v0 = F(c, 0x1C);
        y0 = y1;
        y1 = y1 + (F(c, 0x2C) - v0);
    }
}

}
