/* fn_801818E0: world map per-frame update. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef s64 OSTime;
typedef struct Gfx { u8 pad[8]; u16 x8; u8 pada[0x10-0xa]; u8 x10; u8 pad11[0x64-0x11]; u8 x64, x65, x66, x67; u8 x68[1]; } Gfx;
typedef struct Spr { u8 pad[0x30]; Gfx* g; } Spr;
typedef struct E1 { s8 x0; s8 x1; u8 x2; u8 x3; int x4; Spr* x8; } E1;
typedef struct E2 { s8 x0; u8 x1; u8 pad[2]; Spr* x4; } E2;
typedef struct E3 { u8 x0; s8 x1; u8 pad[5]; u8 x7; } E3;
typedef struct Trk { u8 pad[0x1c]; int x1c; } Trk;
typedef struct E4 { s16 x0; u16 x2; u16 x4; u16 x6; s16 x8; s16 xa; Trk* xc; } E4;
typedef struct GMap {
    u8 pad[0x10]; f32 x10, x14, x18, x1c; u8 pad20[0x28-0x20]; u8 x28; u8 pad29[0x2c-0x29]; int x2c; u8 pad30[4];
    E2 e2[20]; E1 e1[10]; E3 e3[9]; E4 e4[8];
    s16 x214, x216, x218, x21a; Spr* x21c; u8 pad220[0x240-0x220]; int x240; f32 x244; u8 pad248[0x24c-0x248];
    u16 x24c, x24e; u8 x250, x251; u16 x252, x254; u8 pad256[2]; f32 x258, x25c, x260, x264, x268, x26c, x270, x274;
} GMap;
#define OS_BUS_CLOCK (*(u32*)0x800000F8)
extern OSTime OSGetTime(void);
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_800E57B4(Spr*, int, int);
extern int fn_801D09F0(void);
extern void fn_8031292C(f32*, f32, f32, f32);
extern void fn_80312344(f32*, void*);
extern void fn_80081A90(void*);
typedef struct Col { u8 r, g, b, a; } Col;
static inline void PutC(Gfx* g, Col c) { g->x64 = c.r; g->x65 = c.g; g->x66 = c.b; g->x67 = c.a; }
static inline void PutC2(Gfx* g, Col c0, u8 a) { Col c; c.r = c0.r; c.g = c0.g; c.b = c0.b; c.a = a; PutC(g, c); }
static inline void SetA(Spr* s, u8 a) {
    Gfx* g = s->g;
    Col c0 = *(Col*)&g->x64;
    PutC2(g, c0, a);
}
static inline void Wr1(Spr* s, u8 a) { SetA(s, a); }
static inline void Wr2(Spr* s, u8 a) { Wr1(s, a); }
void fn_801818E0(GMap* m) {
    /*P*/
    E2* f;
    int i2;
    int i;
    E1* e;
    Spr* o;
/*E*/
    f32 mtx[3][4];
    m->x240 = (OSGetTime() / (OS_BUS_CLOCK / 4 / 1000)) % 3000;
    if (m->x252) {
        m->x252--;
        m->x10 = fn_8017F68C(m->x2c, m->x258, m->x25c, m->x254 - m->x252, m->x254);
        m->x14 = fn_8017F68C(m->x2c, m->x260, m->x264, m->x254 - m->x252, m->x254);
        m->x18 = fn_8017F68C(m->x2c, m->x268, m->x26c, m->x254 - m->x252, m->x254);
        m->x1c = fn_8017F68C(m->x2c, m->x270, m->x274, m->x254 - m->x252, m->x254);
    }
    if (m->x24c) {
        m->x24c--;
        m->x28 = (int)fn_8017F68C(0, m->x250, m->x251, m->x24e - m->x24c, m->x24e);
    }
    e = m->e1;
    for (i = 0; i < 10; i++, e++) {
        o = e->x8;
        if (o) {
            f32 a, b;
            SetA(o, e->x3 * m->x28 / 255);
            o->g->x8 = (int)(m->x244 - 2.0f);
            a = 1.6842105f * m->x18;
            b = 1.6964285f * m->x1c;
            fn_800E57B4(o, (int)(304.0f * a + m->x10), (int)(229.0f * b + m->x14));
            {
            f32 off;
            if (fn_801D09F0()) off = 0.022f; else off = 0.0f;
            fn_8031292C(mtx[0], a + off, b, 1.0f);
            }
            fn_80312344(mtx[0], o->g->x68);
        }
        switch (e->x1) {
        case 2: {
            s16 n = e->x3; n -= 5;
            if (n <= 0) {
                e->x1 = 0;
                if (o) {
                    fn_80081A90(e->x8);
                    e->x8 = 0;
                }
            } else {
                e->x3 = n;
            }
            break;
        }
        case 0: case 1:
        default:
            break;
        }
    }
    f = m->e2;
    for (i2 = 0; i2 < 20; i2++, f++) {
        o = f->x4;
        if (o) Wr2(o, f->x1 * m->x28 / 255);
        switch (f->x0) {
        case 0: break;
        case 1: {
            s16 n = f->x1; n += 5;
            if (n >= 0xff) { n = 0xff; f->x0 = 3; }
            f->x1 = n;
            break;
        }
        case 3:
            break;
        case 5: {
            s16 n = f->x1; n -= 5;
            if (n <= 0) {
                f->x0 = 0;
                if (o) {
                    fn_80081A90(f->x4);
                    f->x4 = 0;
                }
            } else {
                f->x1 = n;
            }
            break;
        }
        }
    }
    {
    E3* g = m->e3;
    int k;
    for (k = 0; k < 9; k++, g++) {
        switch (g->x1) {
        case 0: break;
        case 1: {
            s16 n = g->x7; n += 10;
            if (n > 0xff) { n = 0xff; g->x1 = 2; }
            g->x7 = n;
            break;
        }
        case 2: break;
        case 3: {
            s16 n = g->x7; n -= 10;
            if (n < 0) { n = 0; g->x1 = n; }
            g->x7 = n;
            break;
        }
        }
    }
    }
    switch (m->x214) {
    case 0:
        if (m->x216 > 0) {
            m->x216--;
            m->x21a = (int)fn_8017F68C(0, 0.0f, 255.0f, m->x216, m->x218);
        }
        break;
    case 1:
        if (m->x216 > 0) {
            m->x216--;
            m->x21a = (int)fn_8017F68C(0, 0.0f, 255.0f, m->x216, m->x218);
        }
        break;
    }
    if (m->x21c) m->x21c->g->x10 = m->x21a * m->x28 / 255;
    {
    E4* t = m->e4;
    int k;
    for (k = 0; k < 8; k++, t++) {
        if (t->x4 & 1) {
            if (t->x4 & 2) {
                t->x8 += 10;
                if (t->x8 > 0xaa) t->x8 = 0xaa;
            } else {
                t->x8 -= 10;
                if (t->x8 < 0) t->x8 = 0;
            }
            if (t->x4 & 4) {
                t->xa -= 2;
                if (t->xa < 0x32) t->xa = 0x32;
            } else {
                t->xa += 2;
                if (t->xa > 0x64) t->xa = 0x64;
            }
            switch (t->x0) {
            case 1:
                t->x6++;
                if (t->x6 >= t->xc->x1c) t->x0 = 0;
                break;
            case 0:
            default:
                break;
            }
        }
    }
    }
}
}
