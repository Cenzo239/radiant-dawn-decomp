/* fn_800FCD10: functionally equal (regs, 7 of 32 words differ in registers only). Helpers from fn_800FCA40.c (exported bodies removed), body from wip/fn_800FCD10.c. */
/* symcheck: (a) block 1: float temporaries in other registers, the three stores are equal; leftover f1 at blr of a void function (clean with --ret=none). */
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
extern void fn_80102928(MapUnit*, s32, s32, s32, s32);
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


/* ---- from rE_800E5DE4/wip/fn_800FCD10.c ---- */
/* Near misses from the map-unit effect processes in ../fn_800FCA40.c
 * (UProc/PSlot structs and externs live there).
 * fn_800FCD10: 6-7 of 32 words, FP register choice only (frsp f1,f1; zero in f2).
 * fn_800FCDD8 / fn_800FCEE4: the u32 colour is split into stack bytes with the
 *   shift result reused in one register and interleaved stb (a, r, g, b). The
 *   source form is unknown; a GXColor-writing inline gets within 7 of 66 words
 *   for 800FCEE4, and 800FCDD8 still forwards the bytes (size 0xD0 vs 0xE4).
 * fn_800FD05C: 17 of 28 words, FP register allocation of the bounce formula. */
void fn_800FCD10(UProc* p) {
    f32 s;
    p->s44.f += p->s34.f;
    p->s40.i++;
    s = fn_80295940(p->s44.f);
    SetOff(p->unit, p->s3C.f * s, 0.0f, 0.0f);
    if (p->s40.i >= p->s38.i) {
        fn_80083B78(p);
    }
}