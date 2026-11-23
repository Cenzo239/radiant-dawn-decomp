/* Round 20, exact (check_regs.py: exact): fn_800FD65C. Self-contained. check_func.py --strict-references: MATCH. fn_800FC5D8.c with exported bodies removed plus the function (new, written from the asm). Same li; srawi idiom as fn_80101EEC: inline with a local constant under #pragma opt_propagation off. */
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
void fn_800FCBFC(Turn* p);

void fn_800FD108(Hop* p);


#pragma use_lmw_stmw on
static inline void KillFx(Fxp* p) {
    if (p->e) {
        fn_801780B0(p->e);
        p->e = 0;
        p->e2 = 0;
    }
}
void fn_800FD368(Fxp* p);

#pragma use_lmw_stmw off

void fn_800FD51C(Knock* p);


static inline int Half(int v) { return v >> 1; }

/* ---- from build/tmp/r20small/rE/frag_FD65C.c ---- */

#pragma opt_propagation off
static inline int Half12(void) { int x = 0xC; return x >> 1; }
/* Knock-back slide: 12 frames (6 when p->b6C), offset eased from (sx,sy) to (tx,ty). */
void fn_800FD65C(Knock* p) {
    int n = 0xC;
    f32 a;
    f32 b;
    f32* o;
    if (p->b6C) {
        n = Half12();
    }
    if (++p->t >= n) {
        p->t = n;
        fn_80083B78(p);
    }
    a = fn_8001EDF8(2, p->sx, p->tx, (f32)n, (f32)p->t);
    b = fn_8001EDF8(2, p->sy, p->ty, (f32)n, (f32)p->t);
    o = (f32*)p->u;
    o[4] = a;
    o[5] = b;
    o[6] = 0.0f;
}