/* NEAR MISS: 11 words, registers for x/path swapped (x wants r30, path r28). */
#include "game/rB_8002E1C4/types.h"

/* Map-range highlight functor callbacks: visit(self, target) marks the
 * target's tile in the highlight layer lbl_803E7320 when it qualifies. */

typedef struct MapUnit {
    u8 pad[0xf4];
    void* xf4;  /* 0x0f4 faction / army */
    u8 padf8[0xfc - 0xf8];
    u8 xfc;     /* 0x0fc */
    u8 padfd[0x102 - 0xfd];
    s8 x;       /* 0x102 */
    s8 y;       /* 0x103 */
    u8 pad104[0x10c - 0x104];
    u32 x10c;
    u16 x110;
    u8 pad112[2];
    s8 x114;    /* current HP */
    u8 pad115[0x12c - 0x115];
    u8 x12c[0x1bc - 0x12c]; /* skills */
} MapUnit;

typedef struct Functor {
    void* vt;
    MapUnit* u;
} Functor;

extern u8 lbl_803E7320[];
void fn_800CFB34(void* map);
#if TARGET_PC
FE10_PROTO void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, void *);
#else
void fn_800CFC50(void* layer, s8 x, s8 y, u8 v, int mode);
#endif
MapUnit* fn_8012CF28(s8 x, s8 y);
int fn_8010E398(void* a, void* b);
s16 fn_801237EC(MapUnit* u);
int fn_80108F68(void* p);

static inline int dirX(u8 c)
{
    switch (c) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}

static inline int dirY(u8 c)
{
    switch (c) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}

/* mark every unit along a move path (direction bytes, 0x40 = end) */
void fn_8003B5C8(s8 x0, s8 y0, u8* p0)
{
    s8 x;
    s8 y;
    MapUnit* u;
    u8* path;

    x = x0; y = y0; path = p0;
    fn_800CFB34(lbl_803E7320);
    for (;;) {
        u = fn_8012CF28(x, y);
        if (u != 0) fn_800CFC50(lbl_803E7320, u->x, u->y, u->xfc, 0);
        if (*path == 0x40) break;
        x += dirX(*path);
        y += dirY(*path);
        path++;
    }
}
