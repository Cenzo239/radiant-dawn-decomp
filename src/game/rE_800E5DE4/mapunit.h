#ifndef RE_800E5DE4_MAPUNIT_H
#define RE_800E5DE4_MAPUNIT_H

#include "game/rE_800E5DE4/types.h"

typedef unsigned long long u64;

/* Map unit sprite (guessed): a model instance at +0x28, map position at
 * +0x04..0x0C, facing angle (deg*64) at +0xC4. */
typedef struct MUData {
    u8 pad0[0x20];
    char* name20;  /* 0x20 */
    u8 unk24[4];   /* 0x24 */
} MUData;

typedef struct MUOwner {
    u8 pad0[0x18];
    MUData* data; /* 0x18 */
} MUOwner;

typedef struct MUTable {
    u8 pad0[0xEC];
    char* names[5]; /* 0xEC */
} MUTable;

typedef struct Model {
    u8 pad0[0x82];
    u8 unk82;       /* 0x82 */
    u8 pad83;
    void* unk84;    /* 0x84 */
    void* owner;    /* 0x88 */
} Model;

typedef struct UnitInfo {
    u8 pad0[0x12];
    s8 unk12; /* 0x12 */
    s8 unk13; /* 0x13 */
} UnitInfo;

typedef struct UnitRef {
    u8 pad0[0x10];
    UnitInfo* info; /* 0x10 */
} UnitRef;

typedef struct MUInfo {
    u8 pad0[8];
    u8 unk8;        /* 0x08 */
} MUInfo;

typedef struct MUFlagBits {
    u16 b15 : 1;
    u16 b14 : 1;
    u16 b13 : 1;
    u16 b12 : 1;
    u16 b11 : 1;
    u16 b10 : 1;
    u16 b9 : 1;
    u16 b8 : 1;
    u16 b7 : 1;
    u16 b6 : 1;
    u16 b5 : 1;
    u16 b4 : 1;
    u16 b3 : 1;
    u16 b2 : 1;
    u16 loaded : 1; /* 0x2 */
    u16 b0 : 1;
} MUFlagBits;

typedef struct MapUnit {
    union {
        u16 flags;
        MUFlagBits bits;
    };              /* 0x00 */
    u16 unk2;       /* 0x02 */
    f32 x;          /* 0x04 */
    f32 y;          /* 0x08 */
    f32 z;          /* 0x0C */
    f32 offX;       /* 0x10 */
    f32 offY;       /* 0x14 */
    f32 offZ;       /* 0x18 */
    f32 f1C;        /* 0x1C */
    f32 f20;        /* 0x20 */
    f32 f24;        /* 0x24 */
    union {
        u8 model[0x5C]; /* 0x28 */
        struct {
            u8 pad28[0xB];
            u8 unk33;   /* 0x33 */
        };
        struct {
            u8 pad28b[8];
            GXColor color; /* 0x30 */
        };
    };
    f32 unk84;      /* 0x84 */
    u8 pad88[0x3C];
    s16 angle;      /* 0xC4 */
    u8 unkC6;       /* 0xC6 */
    s8 unkC7;       /* 0xC7 */
    s8 unkC8;       /* 0xC8 */
    u8 nJoints;     /* 0xC9 */
    s8 joints[0xE]; /* 0xCA */
    s8 unkD8;       /* 0xD8 */
    s8 unkD9;       /* 0xD9 */
    s16 unkDA;      /* 0xDA */
    struct UnitRef* unkDC; /* 0xDC */
    void* unkE0;    /* 0xE0 */
    u8 padE4[8];
    MUTable* tbl;   /* 0xEC */
    MUData* data;   /* 0xF0 */
    MUInfo* unkF4;  /* 0xF4 */
    u8 padF8[6];
    s8 unkFE;       /* 0xFE */
    u8 padFF[3];
    s8 mapX;        /* 0x102 */
    s8 mapY;        /* 0x103 */
    u8 pad104[4];
    u64 flags2;     /* 0x108 */
    union {
        u8 unk110[4];   /* 0x110 */
        u16 unk110h;
    };
    s8 unk114;      /* 0x114 */
} MapUnit;

#endif
