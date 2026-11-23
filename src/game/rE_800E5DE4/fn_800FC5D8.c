#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

/* Map-unit effect processes, part 2 (800FC5D8..800FD65C). */
typedef struct Turn {
    u8 pad[0x30];
    MapUnit* u;  /* 0x30 */
    u8 pad34[4];
    s32 n;       /* 0x38 */
    s32 t;       /* 0x3C */
    u8 pad40[8];
    f32 from;    /* 0x48 */
    f32 to;      /* 0x4C */
    f32 target;  /* 0x50 */
} Turn;

typedef struct Hop {
    u8 pad[0x30];
    MapUnit* u;   /* 0x30 */
    f32 sx, sy, sz; /* 0x34 */
    f32 ex, ey, ez; /* 0x40 */
    u8 pad4C[4];
    s32 t;        /* 0x50 */
    s32 n;        /* 0x54 */
} Hop;

typedef struct Fxp {
    u8 pad[0x30];
    MapUnit* u;   /* 0x30 */
    GXColor c;    /* 0x34 */
    void* e;      /* 0x38 */
    void* e2;     /* 0x3C */
} Fxp;

typedef struct Knock {
    u8 pad[0x30];
    MapUnit* u;   /* 0x30 */
    s32 t;        /* 0x34 */
    u8 pad38[4];
    f32 f3C;      /* 0x3C */
    u8 pad40[8];
    f32 x, y, z;  /* 0x48 */
    f32 tx, ty;   /* 0x54 */
    f32 sx, sy;   /* 0x5C */
    f32 dx, dy;   /* 0x64 */
    u8 b6C;       /* 0x6C */
} Knock;

typedef struct Mtx34 { f32 m[3][4]; } Mtx34;

extern s32 lbl_803EC898[];
extern u8 lbl_8038536C[];
extern void* lbl_80367CA4[];
extern f32 fn_8001EDF8(int, f32, f32, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_8001EBC8(int, f32, f32, f32, f32);
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern void fn_80081A90(void*);
extern void fn_80083B78(void*);
extern void fn_800F3F08(MapUnit*, int);
extern int fn_80008C98(void*, int);
extern int fn_80008CF0(void*, int);
#if TARGET_PC
extern FE10_PROTO int fn_800F43B0(MapUnit*);
#else
extern void* fn_800F43B0(MapUnit*);
#endif
#if TARGET_PC
extern FE10_PROTO void* fn_800F08DC(unsigned int);
#else
extern void* fn_800F08DC(void*);
#endif
#if TARGET_PC
extern FE10_PROTO unsigned char * fn_80068DE4(void);
#else
extern int fn_80068DE4(void);
#endif
#if TARGET_PC
extern FE10_PROTO void* fn_80179040(void*, int, int, void *);
#else
extern void* fn_80179040(void*, void*, int, int);
#endif
extern void fn_80177FCC(void*, GXColor);
#if TARGET_PC
extern FE10_PROTO void * fn_80007F10(void*);
#else
extern int fn_80007F10(void*);
#endif
extern void fn_801780B0(void*);
extern void fn_80312654(Mtx34*, int, f32);
extern void fn_80312DB4(Mtx34*, Vec*, Vec*);

void fn_800FCBFC(Turn* p) {
    f32 a;
    int k;
    p->t++;
    a = fn_8001EDF8(2, p->from, p->to, (f32)p->n, (f32)p->t);
    k = a / 360.0f;
    p->u->angle = 64.0f * (a - 360.0f * (f32)k);
    if (p->t == p->n) {
        p->u->angle = 64.0f * p->target;
        fn_80081A90(p);
    }
}

void fn_800FD108(Hop* p) {
    int a;
    f32 x, y, z;
    p->t++;
    if (p->t >= p->n) {
        p->t = p->n;
        fn_80083B78(p);
    }
    a = fn_8001EDF8(2, 0.0f, 255.0f, (f32)p->n, (f32)p->t);
    x = fn_8001EF30(p->sx, p->ex, (f32)p->n, (f32)p->t);
    y = fn_8001EF30(p->sy, p->ey, (f32)p->n, (f32)p->t);
    z = fn_8001EF30(p->sz, p->ez, (f32)p->n, (f32)p->t);
    {
        f32 h = 0.5f * (f32)p->n;
        if ((f32)p->t < h) {
            z += fn_8001EBC8(2, 0.0f, -0.5f, h, (f32)p->t);
        } else {
            z += fn_8001ECE4(2, -0.5f, 0.0f, h, (f32)p->t - h);
        }
    }
    fn_800F3F08(p->u, a);
    {
        MapUnit* u = p->u;
        u->x = x;
        u->y = y;
        u->z = z;
    }
}

#pragma use_lmw_stmw on
static inline void KillFx(Fxp* p) {
    if (p->e) {
        fn_801780B0(p->e);
        p->e = 0;
        p->e2 = 0;
    }
}
void fn_800FD368(Fxp* p) {
    void* k;
    int n;
    u8* m = (u8*)p->u + 0x28;
    if (fn_80008C98(m, 0x50)) {
        u16 f = fn_80008CF0(m, 0x50);
        n = 1;
        if (f) n = 3;
        if (p->e) {
            fn_80081A90(p->e);
            p->e = 0;
            p->e2 = 0;
        }
        k = fn_800F08DC(fn_800F43B0(p->u));
        if (k) {
            u8* m2 = (u8*)p->u + 0x28;
            p->e = fn_80179040(m2, k, n, fn_80068DE4());
            fn_80177FCC(p->e, p->c);
            *((u8*)p->e + 0x50) |= 0x20;
            p->e2 = (void*)fn_80007F10(m2);
        }
    }
    if (fn_80008C98(m, 0x51)) {
        KillFx(p);
    }
    if (p->e) {
        if ((u32)p->e2 != fn_80007F10(m)) {
            KillFx(p);
        }
    }
}
#pragma use_lmw_stmw off

void fn_800FD51C(Knock* p) {
    Mtx34 m;
    int x, y;
    MapUnit* u = p->u;
    p->x = u->x;
    p->y = u->y;
    p->z = u->z;
    p->t = 0;
    {
    Vec v = {0.0f, 1.0f, 0.0f};
    fn_80312654(&m, 0x7A, 0.017453292f * -p->f3C);
    fn_80312DB4(&m, &v, &v);
    {
    f32 a = v.x;
    p->dx = a;
    x = p->x + a;
    }
    {
    f32 b = v.y;
    p->dy = b;
    y = p->y + b;
    }
    }
    if (x < 0 || y < 0 || x >= lbl_803EC898[0] || y >= lbl_803EC898[1]) {
        p->dx *= -1.0f;
        p->dy *= -1.0f;
    }
    p->sx = 0.0f;
    p->sy = 0.0f;
    p->tx = 0.25f * p->dx;
    p->ty = 0.25f * p->dy;
}

static inline int Half(int v) { return v >> 1; }
