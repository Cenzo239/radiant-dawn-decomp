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

void fn_800FCA40(UProc* p, MapUnit* m, u16 f) {
    p->unit = m;
    p->s34.h = f;
    p->s40.i = -1;
    p->s44.i = -1;
    if (f & 1) {
        CharDesc* c = fn_800F43F0(m);
        if (c) {
            int j = m->unkC7;
            NameEnt* e = fn_800F0AA8(j);
            int k;
            if ((c->sub->flags & 8) && e->unkA) {
                k = fn_800F0994((char*)lbl_80367D50);
            } else {
                k = fn_800F0994((char*)lbl_80367D50 + 5);
            }
            if (fn_800F4628(m, k)) {
                p->s40.i = j;
                p->s44.i = k;
                fn_800F651C(m, k);
            }
        }
    }
}

BOOL fn_800FCB30(UProc* p) {
    if (p->s44.i >= 0 && !fn_800F66F8(p->unit, p->s44.i)) {
        return 1;
    }
    return 0;
}

void fn_800FCB74(UProc* p) {
    if (p->s40.i != p->s44.i) {
        fn_80102928(p->unit, p->s44.i, p->s38.i, 0x3A0, 0);
        p->unit->flags |= 0x2000;
    }
}

void fn_800FCBD0(UProc* p) {
    if (p->unit->flags & 0x2000) {
        fn_80102928(p->unit, p->s40.i, 0x10, 0x20, 0);
    }
}

void fn_800FCCFC(UProc* p) {
    p->s40.i = 0;
    p->s44.f = 0.0f;
}

void fn_800FCD90(UProc* p) {
    MapUnit* m = p->unit;
    m->offX = 0.0f;
    m->offY = 0.0f;
    m->offZ = 0.0f;
}

void fn_800FCDA8(UProc* p) {
    p->s34.c = p->unit->color;
    p->s44.i = 0;
}

void fn_800FCEBC(UProc* p) {
    fn_80008F10(p->unit->model, p->s34.c.r, p->s34.c.g, p->s34.c.b);
}

void fn_800FCED8(UProc* p) {
    p->s40.i = 0;
}

void fn_800FCFEC(UProc* p) {
    fn_800F3EB0(p->unit, p->s38.c);
}

void fn_800FD034(UProc* p) {
    MapUnit* m = p->unit;
    p->s34.f = m->x;
    p->s38.f = m->y;
    p->s3C.f = m->z;
    p->s48.f = 0.0f;
}

void fn_800FD0CC(UProc* p) {
    f32 x, y, z;
    MapUnit* m;
    z = p->s3C.f;
    y = p->s38.f;
    x = p->s34.f;
    m = p->unit;
    m->x = x;
    m->y = y;
    m->z = z;
}

void fn_800FD0EC(UProc* p) {
    p->s50.i = 0;
    p->s54.i = 0x10;
    fn_800F3F08(p->unit, 0);
}

void fn_800FD330(UProc* p) {
    f32 x, y, z;
    MapUnit* m;
    z = p->s48.f;
    y = p->s44.f;
    x = p->s40.f;
    m = p->unit;
    m->x = x;
    m->y = y;
    m->z = z;
    fn_800F3F08(p->unit, 0xFF);
}

void fn_800FD358(UProc* p) {
    p->s38.i = 0;
    p->s3C.i = 0;
}

void fn_800FD4D4(UProc* p) {
    if (p->s38.p) {
        fn_80081A90(p->s38.p);
        p->s38.p = NULL;
        p->s3C.p = NULL;
    }
}

void fn_800FD768(UProc* p) {
    p->s34.i = 0;
}

void fn_800FD774(UProc* p) {
    int k = p->s38.i - 12;
    if (p->b6C) {
        k = 0;
    }
    if (++p->s34.i >= k) {
        p->s34.i = 0;
        fn_80083B78(p);
    }
}

void fn_800FD7B0(UProc* p) {
    p->s34.i = 0;
    p->s5C.f = p->s54.f;
    p->s60.f = p->s58.f;
    p->s54.f = 0.0f;
    p->s58.f = 0.0f;
}

void fn_800FD7D8(UProc* p) {
    MapUnit* m = p->unit;
    m->offX = 0.0f;
    m->offY = 0.0f;
    m->offZ = 0.0f;
}
