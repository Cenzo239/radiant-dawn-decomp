/* Cloud shadow layer draw: two scrolling quads with vertex colours. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
extern "C" {
extern void fn_80304314(int, int, int);

static inline void C4(volatile f32* f, u8* c) {
    u8 c0 = c[0];
    u8 c1 = c[1];
    u8 c2 = c[2];
    u8 c3 = c[3];
    *(volatile u8*)f = c0;
    *(volatile u8*)f = c1;
    *(volatile u8*)f = c2;
    *(volatile u8*)f = c3;
}
void fn_801445E8(u8* o) {
    f32 pos[12] = {0.0f, 0.0f, 800.0f, 608.0f, 0.0f, 800.0f, 0.0f, 448.0f, 800.0f, 608.0f, 448.0f, 800.0f};
    f32 uv[12];
    u8 col[16] = {0xFF, 0xFF, 0xFF, 0x20, 0xFF, 0xFF, 0xFF, 0x20, 0xFF, 0xFF, 0xFF, 0x40, 0xFF, 0xFF, 0xFF, 0x40};
    volatile f32* fifo = (volatile f32*)0xCC008000;
    f32 b, du, dv, a;
    du = 304.0f;
    dv = 224.0f;
    a = 1.0f;
    b = 1.5f;
    /*P*/
    u8* o2;
    int i;
    f32* p;
    f32* t;
    u8* c;
/*E*/
    o2 = o;
    for (i = 0; i < 2; i++) {
        f32 b0, a0, v1, u1, u, v;
        a0 = *(f32*)(o2 + 0x34);
        b0 = *(f32*)(o2 + 0x3C);
        c = col;
        t = uv;
        p = pos;
        u = -a0;
        v = -b0;
        u1 = u + du;
        v1 = v + dv;
        uv[0] = u;
        uv[1] = v;
        uv[3] = u1;
        uv[4] = v;
        uv[6] = u;
        uv[7] = v1;
        uv[9] = u1;
        uv[10] = v1;
        fn_80304314(0x98, 0, 4);
        for (int k = 0; k < 4; k++) {
            *fifo = p[0];
            *fifo = p[1];
            *fifo = 0.0f;
            C4(fifo, c);
            *fifo = t[0];
            *fifo = t[1];
            p += 3;
            t += 3;
            c += 4;
        }
        o2 += 4;
        a *= b;
    }
}
}
