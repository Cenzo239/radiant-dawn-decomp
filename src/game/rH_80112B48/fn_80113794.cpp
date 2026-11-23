/* Wall flag set and clear with the neighbouring tiles, 80113794 and 80113890. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
static inline void Or1(u16* p, u32 f) { u16 v = *p; v |= f; *p = v; }
static inline void An1(u16* p, u32 f) { u16 v = *p; v &= ~f; *p = v; }
void fn_80113794(Map* m, s8 x, s8 y, u32 f) {
    m->flags[x + y * 0x40] |= f;
    if (x > 0) {
        Or1(&m->flags[(s8)(x-1) + y * 0x40], f & 0x222);
    }
    if (x < m->w - 1) {
        Or1(&m->flags[(s8)(x+1) + y * 0x40], f & 0x111);
    }
    if (y > 0) {
        Or1(&m->flags[x + (s8)(y-1) * 0x40], f & 0x444);
    }
    if (y < m->h - 1) {
        Or1(&m->flags[x + (s8)(y+1) * 0x40], f & 0x888);
    }
}
void fn_80113890(Map* m, s8 x, s8 y, u32 f) {
    m->flags[x + y * 0x40] &= ~f;
    if (x > 0) {
        An1(&m->flags[(s8)(x-1) + y * 0x40], f & 0x222);
    }
    if (x < m->w - 1) {
        An1(&m->flags[(s8)(x+1) + y * 0x40], f & 0x111);
    }
    if (y > 0) {
        An1(&m->flags[x + (s8)(y-1) * 0x40], f & 0x444);
    }
    if (y < m->h - 1) {
        An1(&m->flags[x + (s8)(y+1) * 0x40], f & 0x888);
    }
}
}
