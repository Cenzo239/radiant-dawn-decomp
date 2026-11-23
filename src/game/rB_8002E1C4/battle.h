#ifndef RB_BATTLE_H
#define RB_BATTLE_H
#include "game/rT_80026898/types.h"

/* Battle context lbl_803C8E80 and its three combatant copies. */
struct ItemD { u32 x0; u32 flags; u8 pad8[0x12 - 8]; u8 x12; u8 x13; };
typedef struct BU {
    Unit u;
    u8 pad3f4[0x448 - 0x3f4];
    s16 x448;
    s16 x44a;
    s16 x44c;
    u8 pad44e[0x452 - 0x44e];
    s16 x452;
    u8 pad454[0x458 - 0x454];
    s16 x458;
    u8 pad45a[0x468 - 0x45a];
    s16 x468, x46a, x46c, x46e, x470, x472;
    s16 x474;
    s16 x476;
    s16 x478;
    u8 pad47a;
    u8 x47b;
    u8 pad47c;
    u8 x47d;
    s8 s47e;
    u8 pad47f;
    u8 x480;
    u8 x481;
    u8 x482;
    u8 pad483[0x486 - 0x483];
    s16 x486;
    s16 x488;
    u8 x48a;
    u8 x48b;
    u8 pad48c[0x4a0 - 0x48c];
} BU;
struct Battle {
    BU a;     /* 0x000 */
    BU b;     /* 0x4A0 */
    BU c;     /* 0x940 */
    u8 log[0x15e4 - 0xde0]; /* 0xDE0 */
    u8 f15e4;
    u8 pad15e5[3];
    int f15e8;
    u32 f15ec;
    u32 f15f0;
    u32 f15f4;
    u32 f15f8;
    s8 f15fc;
    u8 f15fd;
    u8 pad15fe[2];
    u32 f1600;
    union {
        u8 f1604;
        char s1604[0x20];
    };
    char s1624[0x20];
};
/* One combatant to set up: the unit, its tile, and either an inventory index or a weapon. */
struct Spec {
    Unit* u;
    s8 x, y;
    s8 idx;
    u8 f7;
    Slot* item;
    u8 fc;
    u8 fd, fe, ff;
};
#endif
