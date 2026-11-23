/* NOT MATCHING, not compiled. fn_80117E30: size 0x15C vs 0x144; needs the cur grid base and index computed like the original (lwz cur; slwi; add). */
/* Clear a side of the move grids, 80117E30. Support gain, 8012EAB4 tried. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern Map lbl_803EC898;

#define KILL(m, i, j)                                                   \
    {                                                                   \
        cur[k] = -1;                                                    \
        ((u16*)row)[(s8)(i) + 0xD18E / 2] = 0;                          \
    }

#pragma push
#pragma use_lmw_stmw on
void fn_80117E30(Map* m, s8 x, s8 y, int d) {
    /*P*/
    Map* g = &lbl_803EC898;
    int j;
    int i;
    u8* row;
/*E*/
    for (j = g->y0; j <= g->y1 - 1; j++) {
        row = (u8*)m + (s8)j * 0x80;
        for (i = g->x0; i <= g->x1 - 1; i++) {
            if (((s16*)m->cur)[(s8)i + (s8)j * 0x40] >= 0) {
                switch (d) {
                case 1:
                    if (x < i) {
                        ((s16*)m->cur)[(s8)i + (s8)j * 0x40] = -1;
                        *(u16*)(row + (s8)i * 2 + 0xD18E) = 0;
                    }
                    break;
                case 2:
                    if (i < x) {
                        ((s16*)m->cur)[(s8)i + (s8)j * 0x40] = -1;
                        *(u16*)(row + (s8)i * 2 + 0xD18E) = 0;
                    }
                    break;
                case 8:
                    if (y < j) {
                        ((s16*)m->cur)[(s8)i + (s8)j * 0x40] = -1;
                        *(u16*)(row + (s8)i * 2 + 0xD18E) = 0;
                    }
                    break;
                case 4:
                    if (j < y) {
                        ((s16*)m->cur)[(s8)i + (s8)j * 0x40] = -1;
                        *(u16*)(row + (s8)i * 2 + 0xD18E) = 0;
                    }
                    break;
                }
            }
        }
    }
}
#pragma pop

}
