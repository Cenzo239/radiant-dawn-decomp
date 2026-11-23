/* Reset the wall flags of the whole map, 80113BB4. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern void fn_8017F464(void*, int, int);
void fn_80113BB4(Map* m) {
    int x;
    int y;
    
    for (y = 0; y < m->h; y++) {
        for (x = 0; x < m->w; x++) {
            u16 v;
            int a = x == 0 ? 0x10 : 1;
            int b = y == 0 ? 0x80 : 8;
            v = a | b;
            v |= (x == m->w - 1 ? 0x20 : 2);
            v = v | (y == m->h - 1 ? 0x40 : 4);
            m->flags[(s8)x + ((s8)y << 6)] = v;
        }
    }
    fn_8017F464(m->border, 0xF000F0, 0x80);
}
}
