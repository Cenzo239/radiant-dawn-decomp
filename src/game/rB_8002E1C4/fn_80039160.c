#include "game/rB_8002E1C4/types.h"

/* notice frame (fading on-screen notice) */
typedef struct Notice {
    u8 pad[0x3a];
    s8 alpha;  /* 0x3a */
    s8 target; /* 0x3b */
    s8 step;   /* 0x3c */
    s8 slot;   /* 0x3d */
} Notice;

extern u8 lbl_804CB184[8]; /* slot-in-use flags */
void fn_80083B78(Notice* n); /* destroy */

void fn_80039160(Notice* n)
{
    lbl_804CB184[n->slot] = 0;
}

/* fade in */
void fn_80039178(Notice* n)
{
    n->alpha = 0;
    n->target = 0x10;
    n->step = 1;
}

/* fade out */
void fn_80039194(Notice* n)
{
    n->alpha = 0x10;
    n->target = 0;
    n->step = -1;
}

void fn_800391B0(Notice* n)
{
    n->alpha += n->step;
    if (n->alpha == n->target) fn_80083B78(n);
}
