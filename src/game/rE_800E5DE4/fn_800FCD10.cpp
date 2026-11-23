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

extern "C" {
extern u8 lbl_80367D50[];
extern CharDesc* fn_800F43F0(MapUnit*);
extern NameEnt* fn_800F0AA8(int);
extern int fn_800F0994(char*);
extern int fn_800F4628(MapUnit*, int);
extern void fn_800F651C(MapUnit*, int);
extern BOOL fn_800F66F8(MapUnit*, int);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, s32, s32, s32, p32arg);
#else
extern void fn_80102928(MapUnit*, s32, s32, s32, s32);
#endif
extern void fn_80083B78(void*);
extern double fn_80295940(double);
extern f32 fn_8001EF44(f32, f32, int, int);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern GXColor fn_80175E7C(GXColor, GXColor, f32);
extern void fn_80008F10(void*, u8, u8, u8);
extern void fn_800F3EB0(MapUnit*, GXColor);
extern void fn_800F3F08(MapUnit*, int);
extern void fn_80081A90(void*);

static inline void SetOff(MapUnit* m, f32 x, f32 y, f32 z) {
    m->offX = x;
    m->offY = y;
    m->offZ = z;
}


void fn_800FCDD8(UProc* p) {
    void* mdl;
    f32 t;
    GXColor c;
    p->s44.i++;
    mdl = p->unit->model;
    if (p->s44.i >= p->s40.i) {
        p->s44.i = p->s40.i;
        fn_80083B78(p);
    }
    t = fn_8001EF44(0.0f, 1.0f, p->s40.i, p->s44.i);
    c = fn_80175E7C(p->s34.c, p->s38.c, t);
    fn_80008F10(mdl, c.r, c.g, c.b);
}

void fn_800FCEE4(UProc* p) {
    f32 t;
    p->s40.i++;
    t = fn_8001EF30(0.0f, 1.0f, p->s3C.i, p->s40.i);
    GXColor c = fn_80175E7C(p->s34.c, p->s38.c, t);
    fn_800F3EB0(p->unit, c);
    if (p->s40.i >= p->s3C.i) {
        fn_80083B78(p);
    }
}
}
