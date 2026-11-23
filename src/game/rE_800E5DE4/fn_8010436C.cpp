/* fn_8010436C: exact (round m6). PA() is the inline of fn_800FD7F0.cpp with animation mode 8.
   Levers: the slow factor is a named float computed first (`f32 k = 1.0f - p->slow;`), and the step count is
   scaled with the compound assignment `n *= k;` (as in fn_800FDDE8): the first conversion result then stays
   in n's own register (lwz r5; xoris r0,r5), and the float registers and the store schedule follow. */
/* fn_8010436C: start of a straight-line unit move (when not already set up): remember the start position,
   take the centre of the target tile as the goal, compute the step count from the speed and play the walk animation. */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef struct Mv2 {
    u8 pad0[0x30];
    MapUnit* unit;  /* 0x30 */
    u8 pad34[6];
    s16 tx;         /* 0x3A */
    s16 ty;         /* 0x3C */
    u8 pad3E[6];
    f32 z;          /* 0x44 */
    Vec from;       /* 0x48 */
    Vec to;         /* 0x54 */
    f32 slow;       /* 0x60 */
    s16 t;          /* 0x64 */
    s16 n;          /* 0x66 */
    s16 speed;      /* 0x68 */
    u8 b6A;
    u8 ready;       /* 0x6B */
} Mv2;
extern "C" {
extern u8 lbl_80367D50[];
extern int fn_800F0994(char*);
extern void fn_80102928(MapUnit*, int, int, int, int);
static inline void PA(MapUnit* u, char* name) {
    fn_80102928(u, fn_800F0994(name), 8, 0x20, 0);
}
void fn_8010436C(Mv2* p) {
    if (p->ready == 0) {
        int n;
        MapUnit* u = p->unit;
        p->from.x = u->x;
        p->from.y = u->y;
        p->from.z = u->z;
        p->to.x = 0.5f + (f32)p->tx;
        p->to.y = 0.5f + (f32)p->ty;
        p->to.z = p->z;
        p->t = 0;
        { f32 k = 1.0f - p->slow; n = (int)((f32)p->speed / 16.666666f);
        n *= k; }
        if (n < 4) n = 4;
        p->n = n + 1;
        PA(p->unit, (char*)lbl_80367D50 + 5);
    }
}
}
