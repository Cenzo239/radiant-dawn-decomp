/* Round 23 (r23b), exact: fn_800FD05C. From equiv/fn_800FD05C.c. Shape: the step `p->s48.f += 1.0f` and the
 * unit's z read through small inlines (Tick, Gz, Hgt), and in the clamp the s40 damping store first. */
#include "game/rE_800E5DE4/mapunit.h"

/* Map-unit effect processes (guessed): small processes that animate one
 * MapUnit (+0x30): colour fades, bobbing, jumps and anim swaps. Each class
 * uses the fields after +0x34 differently. */
typedef union PSlot {
    s32 i;
    u32 u;
    f32 f;
    u16 h;
    GXColor c;
    void* p;
} PSlot;

typedef struct UProc {
    u8 pad0[0x30];
    MapUnit* unit; /* 0x30 */
    PSlot s34;     /* 0x34 */
    PSlot s38;     /* 0x38 */
    PSlot s3C;     /* 0x3C */
    PSlot s40;     /* 0x40 */
    PSlot s44;     /* 0x44 */
    PSlot s48;     /* 0x48 */
    PSlot s4C;     /* 0x4C */
    PSlot s50;     /* 0x50 */
    PSlot s54;     /* 0x54 */
    PSlot s58;     /* 0x58 */
    PSlot s5C;     /* 0x5C */
    PSlot s60;     /* 0x60 */
    u8 pad64[8];
    u8 b6C;        /* 0x6C */
} UProc;

typedef struct CharFlags {
    u8 pad0[0x10];
    u8 flags; /* 0x10 */
} CharFlags;

typedef struct CharDesc {
    u8 pad0[0x10];
    CharFlags* sub; /* 0x10 */
} CharDesc;

typedef struct NameEnt {
    u8 pad0[0xA];
    u8 unkA; /* 0x0A */
} NameEnt;

extern u8 lbl_80367D50[];
extern CharDesc* fn_800F43F0(MapUnit*);
extern NameEnt* fn_800F0AA8(int);
extern int fn_800F0994(char*);
extern int fn_800F4628(MapUnit*, int);
extern void fn_800F651C(MapUnit*, int);
extern BOOL fn_800F66F8(MapUnit*, int);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, s32, s32, s32, void *);
#else
extern void fn_80102928(MapUnit*, s32, s32, s32, s32);
#endif
extern void fn_80083B78(void*);
extern double fn_80295940(double);
extern f32 fn_8001EF44(f32, f32, int, int);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern u32 fn_80175E7C(GXColor, GXColor, f32);
extern void fn_80008F10(void*, u8, u8, u8);
extern void fn_800F3EB0(MapUnit*, GXColor);
extern void fn_800F3F08(MapUnit*, int);
extern void fn_80081A90(void*);

static inline void SetOff(MapUnit* m, f32 x, f32 y, f32 z) {
    m->offX = x;
    m->offY = y;
    m->offZ = z;
}

static inline void ColorFromU32(GXColor* c, u32 v) {
    c->a = v;
    c->r = v >> 24;
    c->g = v >> 16;
    c->b = v >> 8;
}
void fn_800FCA40(UProc* p, MapUnit* m, u16 f);

BOOL fn_800FCB30(UProc* p);

void fn_800FCB74(UProc* p);

void fn_800FCBD0(UProc* p);

void fn_800FCCFC(UProc* p);

void fn_800FCD90(UProc* p);

void fn_800FCDA8(UProc* p);

void fn_800FCEBC(UProc* p);

void fn_800FCED8(UProc* p);

void fn_800FCFEC(UProc* p);

void fn_800FD034(UProc* p);

void fn_800FD0CC(UProc* p);

void fn_800FD0EC(UProc* p);

void fn_800FD330(UProc* p);

void fn_800FD358(UProc* p);

void fn_800FD4D4(UProc* p);

void fn_800FD768(UProc* p);

void fn_800FD774(UProc* p);

void fn_800FD7B0(UProc* p);

void fn_800FD7D8(UProc* p);


#pragma use_lmw_stmw off
/* ---- from rE_800E5DE4/wip/fn_800FCD10.c ---- */


static inline f32 Hgt(UProc* p, f32 t) { return p->s40.f - t * (p->s44.f * t); }
static inline f32 Tick(UProc* p) { return p->s48.f += 1.0f; }
static inline f32 Gz(UProc* p) { return p->unit->z; }
void fn_800FD05C(UProc* p) {
    f32 z;
    z = Tick(p);
    z = Gz(p) - Hgt(p, z);
    if (z > p->s3C.f) {
        p->s40.f = p->s40.f * p->s4C.f;
        z = p->s3C.f;
        p->s48.f = 0.0f;
    }
    p->unit->z = z;
    if (p->s40.f < 0.01f) {
        fn_80083B78(p);
    }
}
