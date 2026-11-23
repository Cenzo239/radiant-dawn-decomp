/* fn_8010403C (0x1A0): exact (round m8). Starts a straight move of a map unit: start and end position from the
 * direction bits, frame count from speed and distance, then the walk animation.
 * Two things were needed over the round 18 draft: `p->t = 0` stands before the frame count, and the count is built
 * in `n` with a compound assignment (`n = p->speed / 16.666666f; n *= p->dist;`), which keeps the first float-to-int
 * result in n's register (r4) as in fn_800FDDE8. DirX/DirY are inlines inferred from the two switches; PA is the
 * inline of fn_800FD7F0.cpp with animation mode 8. */
/* fn_8010403C: start of a one-direction unit push (when not already set up): goal = position + dist along the
   direction bits (1 left, 2 right, 4 down, 8 up), step count from the speed and dist, walk animation. */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef struct Mv3 {
    u8 pad0[0x30];
    MapUnit* unit;  /* 0x30 */
    s16 dir;        /* 0x34 */
    u8 pad36[0x12];
    Vec from;       /* 0x48 */
    Vec to;         /* 0x54 */
    f32 dist;       /* 0x60 */
    s16 t;          /* 0x64 */
    s16 n;          /* 0x66 */
    s16 speed;      /* 0x68 */
    u8 b6A;
    u8 ready;       /* 0x6B */
} Mv3;
extern "C" {
extern u8 lbl_80367D50[];
extern int fn_800F0994(char*);
extern void fn_80102928(MapUnit*, int, int, int, int);
static inline void PA(MapUnit* u, char* name) {
    fn_80102928(u, fn_800F0994(name), 8, 0x20, 0);
}
static inline int DirX(int d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}
static inline int DirY(int d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}
void fn_8010403C(Mv3* p) {
    if (p->ready == 0) {
        int n;
        MapUnit* u = p->unit;
        p->from.x = u->x;
        p->from.y = u->y;
        p->from.z = u->z;
        p->to.x = p->from.x + p->dist * (f32)DirX((u8)p->dir);
        p->to.y = p->from.y + p->dist * (f32)DirY((u8)p->dir);
        p->to.z = p->from.z;
        p->t = 0;
        n = p->speed / 16.666666f;
        n *= p->dist;
        if (n < 4) n = 4;
        p->n = n + 1;
        PA(p->unit, (char*)lbl_80367D50 + 5);
    }
}
}
