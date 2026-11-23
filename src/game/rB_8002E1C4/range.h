#ifndef RB_RANGE_H
#define RB_RANGE_H
#include "game/rB_8002E1C4/types.h"

/* Map-range highlight functor callbacks (0x8003B6D0..): visit(self, target)
 * marks the target's tile in the highlight layer lbl_803E7320 when it
 * qualifies. self->u is the acting unit. */

typedef struct MapUnit {
    u8 pad[0xec];
    void* xec;  /* 0x0ec job data */
    void* xf0;
    void* xf4;  /* 0x0f4 faction / army */
    struct MapUnit* xf8; /* 0x0f8 rescued / carried unit */
    u8 xfc;     /* 0x0fc */
    u8 padfd[0x102 - 0xfd];
    s8 x;       /* 0x102 */
    s8 y;       /* 0x103 */
    u8 pad104[0x108 - 0x104];
    u32 x108;
    u32 x10c;
    u16 x110;
    u8 pad112[2];
    s8 x114;    /* current HP */
    u8 pad115[0x12c - 0x115];
    u8 x12c[0x1bc - 0x12c]; /* skills */
    Item items[7];          /* 0x1bc */
    u8 pad2d4[0x37c - 0x2d4];
    u16 x37c;
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
int fn_8010E398(void* a, void* b);   /* same side? */
s16 fn_801237EC(MapUnit* u);         /* max HP */
int fn_80108F68(void* p);
int fn_8011B77C(void* skills, void* sid); /* has skill */
int fn_80111F5C(Item* s);

static inline void markT(MapUnit* t, int mode)
{
    fn_800CFC50(lbl_803E7320, t->x, t->y, t->xfc, mode);
}

static inline u8 sameSide(Functor* self, MapUnit* t)
{
    return (u8)fn_8010E398(self->u->xf4, t->xf4);
}

#endif
