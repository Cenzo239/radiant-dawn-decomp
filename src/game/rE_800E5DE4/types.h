#ifndef RE_800E5DE4_TYPES_H
#define RE_800E5DE4_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
typedef int BOOL;
#define NULL ((void*)0)

/* Unit-like object reachable through a handle; +0x3F0 is a pointer to the
 * attached "map unit"/actor object. */
typedef struct UnitObj {
    u8 pad0[0x3F0];
    void* actor; /* 0x3F0 */
} UnitObj;

typedef struct Handle {
    UnitObj* obj; /* 0x00 */
    u8 pad4[2];
    s16 unk6;     /* 0x06 */
    u8 pad8[6];
    s16 unkE;     /* 0x0E */
} Handle;

typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct Vec {
    f32 x, y, z;
} Vec;

/* Map actor (attached to a unit at UnitObj+0x3F0). */
typedef struct Actor {
    u8 pad0[4];
    Vec pos; /* 0x04 */
} Actor;

typedef struct EvSubObj {
    u8 pad0[0x40];
    char* str40; /* 0x40 */
    char* str44; /* 0x44 */
    char* str48; /* 0x48 */
} EvSubObj;

typedef struct EvSub {
    EvSubObj* obj;
} EvSub;

/* Event/script process with two participants (0x34/0x38). */
typedef struct EvProc {
    u8 pad0[0x30];
    void* unk30;          /* 0x30 */
    Handle* h1;           /* 0x34 */
    Handle* h2;           /* 0x38 */
    void* actor1;         /* 0x3C */
    void* actor2;         /* 0x40 */
    u8 doneCb;            /* 0x44 */
    char name[0x23];      /* 0x45 */
    struct EvSub* sub;    /* 0x68 */
    s8 unk6C;             /* 0x6C */
    s8 unk6D;             /* 0x6D */
    s8 unk6E;             /* 0x6E */
    u8 pad6F;
    s16 unk70;            /* 0x70 */
    u8 pad72[2];
    void (*cb)(struct EvProc*); /* 0x74 */
    /* 0x78..: subclass fields, differ per process class */
    union {
        u8 b;
        u8* p;
    } u78;                /* 0x78 */
    s8 unk7C;             /* 0x7C */
    s8 unk7D;             /* 0x7D */
    s8 unk7E;             /* 0x7E */
    s8 unk7F;             /* 0x7F */
    s16 unk80;            /* 0x80 */
    s16 unk82;            /* 0x82 */
} EvProc;

struct EvCmd;

/* Animation/effect controller owned by an EvCmd. */
typedef struct EvAnimCtl {
    void* unk0;                      /* 0x00 */
    u8 pad4[0x14];
    u32 flags;                       /* 0x18 */
    u8 pad1C[0x98 - 0x1C];
    void (*onUpdate)(struct EvCmd*); /* 0x98 */
    void (*onEvent)(struct EvCmd*);  /* 0x9C */
    u8 padA0[4];
    u8* unkA4;                       /* 0xA4 */
    s32 unkA8;                       /* 0xA8 */
} EvAnimCtl;

/* Effect/animation command spawned by an event process (fn_800E3A10 /
 * fn_800E3810 create these); callbacks receive it. */
typedef struct EvCmd {
    u8 pad0[0x18];
    EvProc* proc;    /* 0x18 */
    u8 pad1C[0x14];
    EvAnimCtl* ctl;  /* 0x30 */
} EvCmd;

static inline void* HandleActor(Handle* h) {
    UnitObj* o = h->obj;
    return o ? o->actor : NULL;
}


#endif
