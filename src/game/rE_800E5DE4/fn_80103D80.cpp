#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct Climb {
    u8 pad[0x30];
    MapUnit* u; /* 0x30 */
    s16 dir;    /* 0x34 */
    s16 x0;     /* 0x36 */
    s16 y0;     /* 0x38 */
    s16 x1;     /* 0x3A */
    s16 y1;     /* 0x3C */
    u8 pad3E[2];
    f32 z0;     /* 0x40 */
    f32 z1;     /* 0x44 */
    u8 pad48[0x18];
    f32 f60;    /* 0x60 */
    u8 pad64[2];
    s16 dur;    /* 0x66 */
    u8 pad68[2];
    s8 anim;    /* 0x6A */
    u8 b6B;     /* 0x6B */
} Climb;

typedef struct CF { u8 pad[0x10]; u8 b10; } CF;
typedef struct CD { u8 pad[0x10]; CF* v10; } CD;

extern "C" {
extern u8 lbl_80367D50[];
extern u8 lbl_803EC898[];
#if TARGET_PC
extern FE10_PROTO p32ret fn_80102E10(MapUnit*, int, p32arg, f32, void*);
#else
extern int fn_80102E10(MapUnit*, int, int, f32, void*);
#endif
extern f32 fn_80113F00(void*, f32, f32);
extern s8 fn_800F0994(char*);
extern void fn_80083DC4(void*, int);
extern CD* fn_800F43F0(MapUnit*);
extern void fn_800F651C(MapUnit*, int);

static inline int DirAngle(u8 c) {
    int n;
    switch (c) {
    case 4: n = 0; break;
    case 6: n = 0x2D; break;
    case 2: n = 0x5A; break;
    case 10: n = 0x87; break;
    case 8: n = 0xB4; break;
    case 9: n = 0xE1; break;
    case 1: n = 0x10E; break;
    case 5: n = 0x13B; break;
    default: n = 0; break;
    }
    return n;
}
static inline int Face(MapUnit* u, int c, int a, int b, void* d) {
    if (c == 0x40 || c == 0) return 0;
    return fn_80102E10(u, a, b, (f32)DirAngle(c), d);
}
static inline int DirX(u8 d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}
static inline int DirY(u8 d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}
void fn_80103D80(Climb* p) {
    Face(p->u, p->dir, 8, 0, 0);
    p->dur = 0x3C;
    p->x0 = p->u->x;
    p->y0 = p->u->y;
    p->x1 = p->x0 + DirX(p->dir) * 2;
    p->y1 = p->y0 + DirY(p->dir) * 2;
    p->z0 = fn_80113F00(lbl_803EC898, (f32)p->x0, (f32)p->y0);
    p->z1 = fn_80113F00(lbl_803EC898, (f32)p->x1, (f32)p->y1);
    if (p->z1 < p->z0) {
        p->f60 = 0.4f;
        p->anim = fn_800F0994((char*)lbl_80367D50 + 0xB);
        fn_80083DC4(p, 0);
    } else {
        p->f60 = 0.6f;
        p->anim = fn_800F0994((char*)lbl_80367D50 + 0x10);
        fn_80083DC4(p, 1);
    }
    if (fn_800F43F0(p->u)->v10->b10 & 1) {
        p->b6B = 1;
    } else {
        p->b6B = 0;
    }
    fn_800F651C(p->u, p->anim);
    p->u->flags &= ~0x3C0;
}
}
