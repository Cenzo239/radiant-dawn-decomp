/* Prim2D command dispatcher: walks a node's command chain and draws each one. */
#include "game/rJ_800799AC/types.h"

typedef union {
    volatile u8 u8;
    volatile f32 f32;
} WGPipe;

#define GX ((WGPipe*)0xCC008000)

struct RGBA {
    u8 r, g, b, a;
};

struct UV {
    f32 x, y, u, v;
};

struct PrimCmd {
    PrimCmd* next; /* 0x00 */
    u8 type;       /* 0x04 */
    f32 z;         /* 0x08 */
    RGBA col;      /* 0x0C */
    union {
        struct {
            UV v[4];    /* 0x10: corners 0, 1 are also a rect's two corners */
            RGBA c[3];  /* 0x50 */
        } quad;
        struct {
            f32 x, y;   /* 0x10 */
            RGBA c;     /* 0x18 */
            f32 p1c;
            f32 p20[1];
            f32 w, h;   /* 0x24 */
            s16 a, b;   /* 0x2C */
            u8 p30[4];
        } text;
        struct {
            void (*fn)(void*); /* 0x10 */
            void* arg;  /* 0x14 */
        } cb;
        struct {
            void (*fn)(void*, RGBA*, u32, u8, f32); /* 0x10 */
            void* arg;  /* 0x14 */
        } cb2;
    };
};

extern "C" {

void fn_80304314(int prim, int fmt, int n);
void fn_80304538(int a, int b);
void fn_80080CD4(PrimCmd* c, u8 r, u8 g, u8 b, u8 a);
#if TARGET_PC
FE10_PROTO void fn_800CC71C(f32, f32, f32, f32, f32, s16, s16, u8, ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>);
#else
void fn_800CC71C(f32, f32, f32, f32, f32, s16, s16, u8, RGBA*, u32*, void*, void*, void*);
#endif
void fn_800CC8AC(f32, f32, f32, f32, f32, s16, s16, u8, RGBA*, u32*, void*, void*, void*);
#if TARGET_PC
FE10_PROTO void fn_800CCA3C(f32, f32, f32, f32, f32, s16, s16, u8, ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>);
FE10_PROTO void fn_800CCBCC(f32, f32, f32, f32, f32, s16, s16, u8, ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>);
FE10_PROTO void fn_800CCD5C(f32, f32, f32, f32, f32, s16, s16, u8, ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>, ptr32<const void>);
#else
void fn_800CCA3C(f32, f32, f32, f32, f32, s16, s16, u8, RGBA*, u32*, void*, void*, void*);
void fn_800CCBCC(f32, f32, f32, f32, f32, s16, s16, u8, RGBA*, u32*, void*, void*, void*);
void fn_800CCD5C(f32, f32, f32, f32, f32, s16, s16, u8, RGBA*, u32*, void*, void*, void*);
#endif

static inline void pos3(f32 x, f32 y, f32 z) {
    GX->f32 = x;
    GX->f32 = y;
    GX->f32 = z;
}
static inline void col4(u8 r, u8 g, u8 b, u8 a) {
    GX->u8 = r;
    GX->u8 = g;
    GX->u8 = b;
    GX->u8 = a;
}
static inline void tex2(f32 u, f32 v) {
    GX->f32 = u;
    GX->f32 = v;
}

#define VTX(i) \
    pos3(c->quad.v[i].x, c->quad.v[i].y, c->z); \
    col4(r, g, b, a); \
    tex2(c->quad.v[i].u, c->quad.v[i].v);

#define RV(i, j) \
    pos3(c->quad.v[i].x, c->quad.v[j].y, c->z); \
    col4(r, g, b, a); \
    tex2(c->quad.v[i].u, c->quad.v[j].v);

#define VTXC(i, n) \
    { \
        u8 r2 = (c->quad.c[n].r * s) >> 7; \
        u8 g2 = (c->quad.c[n].g * s) >> 7; \
        u8 b2 = (c->quad.c[n].b * s) >> 7; \
        pos3(c->quad.v[i].x, c->quad.v[i].y, c->z); \
        col4(r2, g2, b2, (c->quad.c[n].a * ia) >> 8); \
        tex2(c->quad.v[i].u, c->quad.v[i].v); \
    }

#define TEXT(fn) \
    { \
        w = (c->col.r << 24) + (c->col.g << 16) + (c->col.b << 8) + a; \
        t.r = c->text.c.r; \
        t.g = c->text.c.g; \
        t.b = c->text.c.b; \
        t.a = (c->text.c.a * ia) >> 8; \
        fn(c->text.x, c->text.y, c->z, c->text.w, c->text.h, c->text.a, c->text.b, s, &t, &w, &c->text.p1c, &c->text.p20, c->text.p30); \
    } \
    break;

void fn_8007F048(PrimCmd* c, u32 alpha, u8 s) {
    RGBA t;
    u32 w;
    RGBA t2;
    int ia = alpha + 1;
    for (; c != 0; c = c->next) {
        u8 r = (c->col.r * s) >> 7;
        u8 g = (c->col.g * s) >> 7;
        u8 b = (c->col.b * s) >> 7;
        u8 a = (c->col.a * ia) >> 8;
        switch (c->type) {
        case 0:
            break;
        case 1:
            fn_80304314(0x98, 0, 4);
            RV(0, 0)
            RV(1, 0)
            RV(0, 1)
            RV(1, 1)
            break;
        case 2:
            fn_80304314(0x98, 0, 4);
            VTX(0)
            VTX(2)
            VTX(3)
            VTX(1)
            break;
        case 3:
            fn_80304314(0x98, 0, 4);
            pos3(c->quad.v[0].x, c->quad.v[0].y, c->z);
            col4(r, g, b, (c->col.a * ia) >> 8);
            tex2(c->quad.v[0].u, c->quad.v[0].v);
            VTXC(2, 0)
            VTXC(3, 1)
            VTXC(1, 2)
            break;
        case 4:
            fn_80304538(6, 0);
            fn_80304314(0xA8, 0, 2);
            VTX(0)
            VTX(1)
            break;
        case 5:
            TEXT(fn_800CC71C)
        case 6:
            TEXT(fn_800CC8AC)
        case 7:
            TEXT(fn_800CCA3C)
        case 8:
            TEXT(fn_800CCBCC)
        case 9:
            TEXT(fn_800CCD5C)
        case 10:
            fn_80080CD4(c, r, g, b, a);
            break;
        case 11:
            c->cb.fn(c->cb.arg);
            break;
        case 12:
            t2.r = c->col.r;
            t2.g = c->col.g;
            t2.b = c->col.b;
            t2.a = c->col.a;
            c->cb2.fn(c->cb2.arg, &t2, alpha, s, c->z);
            break;
        }
    }
}

}
