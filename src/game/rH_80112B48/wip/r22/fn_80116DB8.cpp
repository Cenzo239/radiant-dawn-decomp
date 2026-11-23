/*
 * fn_80116DB8 (round 22 draft, `other`: size 0xC0, want 0xCC).
 * Can a unit step from (x0,y0) to the orthogonally adjacent (x1,y1)? Returns 0 unless the two tiles
 * are exactly one step apart; otherwise tests the wall-flag word of the source tile
 * (m->flags[x0 + y0*64], at Map+0x508E) against the direction bit (2 = +x, 1 = -x, 4 = +y, 8 = -y,
 * 0x40 = same tile, unreachable here).
 *
 * What still differs: the original converts the flag test to 0/1 twice (`neg; or; srwi` twice in a
 * row, at 0x80116E60..0x80116E74); every spelling tried folds the second one (3 instructions short,
 * no other difference). Converting an already-0/1 value again is the identity, so this source
 * behaves the same. `Test(u16, u8)` taking the loaded halfword is what puts the `clrlwi` of the
 * direction after the address add as in the original (the old r7 fragment had 12 words off).
 *
 * Tried this round (all fold the second conversion): bool/BOOL/int/u8 return types at every level,
 * `!!`, `!(x == 0)`, `? 1 : 0`, a named bool/u8 local, `!= 0 != 0`, three nested inlines. Putting the
 * distance test inside a bool inline (`return CanMove(...) != 0`) gives the right size but sends the
 * zero path through the second conversion (4 words off), so the original's early `return 0` is in the
 * function itself.
 */
#include "game/rH_80112B48/map.h"

#define ABS(a) ((a) < 0 ? -(a) : (a))

extern "C" {

static inline u8 DirOf(s8 x0, s8 y0, s8 x1, s8 y1)
{
    if (x0 < x1) return 2;
    if (x0 > x1) return 1;
    if (y0 < y1) return 4;
    if (y0 > y1) return 8;
    return 0x40;
}

static inline bool Test(u16 v, u8 d)
{
    return (v & d) != 0;
}

static inline bool Pass(Map* m, s8 x, s8 y, u8 d)
{
    return Test(m->flags[x + y * 0x40], d);
}

BOOL fn_80116DB8(Map* m, s8 x0, s8 y0, s8 x1, s8 y1)
{
    if (ABS(x0 - x1) + ABS(y0 - y1) != 1) {
        return 0;
    }
    return Pass(m, x0, y0, DirOf(x0, y0, x1, y1)) != 0;
}

}
