#ifndef RO_MAP_H
#define RO_MAP_H
#include "game/rO_80065D64/types.h"

struct MapNode {
    u8 x, y;
    u8 dir;
    u8 pad3;
    u16 cost;
};

/* The battle map (global at lbl_803EC898). 64x64 grids indexed x + (y << 6). */
struct Map {
    s32 w;                 /* 0x00000 */
    s32 h;                 /* 0x00004 */
    s8 x0, y0, x1, y1;     /* 0x00008: playable bounds */
    u8 padC;               /* 0x0000C */
    u8 ter[5][0x1000];     /* 0x0000D: 0x0D unit, 0x100D terrain, 0x300D flags */
    u8 pad500D;
    u16 border[0x40];      /* 0x0500E */
    u16 flags[0x1000];     /* 0x0508E: wall flags */
    u16 border2[0x40];     /* 0x0708E */
    s16 cost[0x1000];      /* 0x0710E */
    u16 border3[0x40];     /* 0x0910E */
    u16 cost2[0x1000];     /* 0x0918E */
    u16 g3[0x1000];        /* 0x0B18E */
    u16 g4[0x1000];        /* 0x0D18E */
    s8 g5[0x2000];         /* 0x0F18E */
    u16 g6[0x1000];        /* 0x1118E */
    u16 g7[0x1000];        /* 0x1318E */
    u8 pad1518E[2];
    s16* cur;              /* 0x15190 */
    u8 buf[0x100];         /* 0x15194: move path */
    u16 costTbl[0xC7];     /* 0x15294 */
    s16 hgt[0x4000];       /* 0x15422: 4 corner heights per tile */
    u8 pad1D422[2];
    f32 scale;             /* 0x1D424 */
    u8 pad1D428[4];
    s16 hgt2[0x4000];      /* 0x1D42C: second height layer */
    u8 bits[0x200];        /* 0x2542C */
    u8 pad2562C[0x2622C - 0x2562C];
    MapNode* head;         /* 0x2622C */
    MapNode* tail;         /* 0x26230 */
    u8 pad26234;
    u8 count;              /* 0x26235 */
    u16 limit;             /* 0x26236 */
    u8 team[4];            /* 0x26238 */
    u8 unk2623C;
    u8 unk2623D;
    u8 unk2623E;
};

#endif
