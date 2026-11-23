/* Mark tiles in a diamond around a point, 80116CFC. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
#define ABS(a) ((a) < 0 ? -(a) : (a))
void fn_80116CFC(Map* m, s8 cx, s8 cy, s8 r) {
    int y; int x;
    for (y = 0; (s8)y < m->h; y++) {
        for (x = 0; (s8)x < m->w; x++) {
            if (ABS((s8)x - cx) + ABS((s8)y - cy) <= r) {
                m->ter[2][x + (y << 6)] = 1;
            }
        }
    }
}
}
