#ifndef RB_8002E1C4_TYPES_H
#define RB_8002E1C4_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
typedef double f64;

/* 0x28-byte item slot (weapon / inventory entry). fn_80110D38 = clear,
 * fn_80111C78 = copy, fn_80111C24 = destructor, fn_801116B8 = get item data. */
typedef struct Item {
    struct ItemData* data; /* 0x00 */
    u8 uses;               /* 0x04 */
    u8 b5_7 : 1;           /* 0x05 */
    u8 b5_6 : 1;
    u8 b5_5 : 1;
    u8 b5_4 : 1;           /* unbreakable? */
    u8 b5_low : 4;
    u8 pad6[0x28 - 6];
} Item;

/* Battle combatant (0x4A0 bytes). Three of these sit at the start of the
 * battle state lbl_803C8E80 (offsets 0x000, 0x4A0, 0x940). The first
 * 0x3F0 bytes are a copy of the unit (same layout as the unit struct that
 * x3f0 points to). */
typedef struct BUnit {
    u8 pad000[0xec];
    struct JobData* xec;
    struct PersonData* xf0;
    u32 xf4;
    u8 padf8[0x108 - 0xf8];
    u32 x108;
    u32 x10c;
    u16 x110;
    u16 x112;
    s8 x114;
    u8 pad115[0x118 - 0x115];
    s8 x118;
    u8 pad119[0x12c - 0x119];
    u8 x12c[0x1bc - 0x12c];
    Item arr1bc[7];
    s16 x2d4[12];
    u8 pad2ec[0x3f0 - 0x2ec];
    struct BUnit* unit; /* 0x3f0 pointer to the real unit */
    Item item;       /* 0x3f4 equipped item */
    Item item2;      /* 0x41c */
    s8 x444;
    u8 x445;
    u8 x446;
    u8 pad447;
    s16 x448[11];    /* 0x448..0x45c */
    u16 x45e;
    struct X460* x460;
    u8 x464;
    u8 x465;
    u8 x466;
    u8 pad467;
    s16 x468[9];     /* 0x468..0x478 */
    u8 x47a;
    u8 x47b;
    s8 x47c;         /* current weapon uses */
    u8 x47d;         /* weapon disabled flag */
    s8 x47e;
    u8 x47f;
    u8 x480;
    u8 x481;
    u8 x482;
    u8 x483;
    u8 x484;
    u8 pad485;
    s16 x486;
    s16 x488;
    u8 x48a;
    u8 x48b;
    u32 x48c;
    u8 x490[11];     /* 0x490..0x49a */
    u8 pad49b;
    u32 x49c;
} BUnit;

typedef struct ItemData {
    u32 x0;
    u32 flags;
    u8 pad8[4];
    u16 xc;
    u8 pade[4];
    u8 x12;          /* weapon type */
    u8 x13;
    u8 pad14[2];
    u16 x16;         /* item index */
} ItemData;

/* battle state, lbl_803C8E80 */
typedef struct BattleState {
    BUnit u[3];
    u8 xde0[0x15ec - 0xde0]; /* battle event/animation queue */
    u32 flags;               /* 0x15ec */
} BattleState;

#endif
