/* Clear the side of the move grids past a tile, 80117E30. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern Map lbl_803EC898;
#pragma use_lmw_stmw on
void fn_80117E30(Map* m, s8 x, s8 y, int d) {
    Map* g;
    u8* row;
    int j;
    int i;
    int o;
    int s;
    int k;
    u16* cur;
    g = &lbl_803EC898;
    for (j = g->y0; j <= g->y1 - 1; j++) {
        o = (s8)j << 7;
        i = g->x0;
        row = (u8*)m + o;
        for (; i <= g->x1 - 1; i++) {
            s = (s8)i * 2;
            cur = m->cur;
            k = s + o;
            if (*(s16*)((u8*)cur + k) >= 0) {
                switch (d) {
                case 1:
                    if (x < i) {
                        *(s16*)((u8*)cur + k) = -1;
                        *(u16*)(row + s + 0xD18E) = 0;
                    }
                    break;
                case 2:
                    if (i < x) {
                        *(s16*)((u8*)cur + k) = -1;
                        *(u16*)(row + s + 0xD18E) = 0;
                    }
                    break;
                case 8:
                    if (y < j) {
                        *(s16*)((u8*)cur + k) = -1;
                        *(u16*)(row + s + 0xD18E) = 0;
                    }
                    break;
                case 4:
                    if (j < y) {
                        *(s16*)((u8*)cur + k) = -1;
                        *(u16*)(row + s + 0xD18E) = 0;
                    }
                    break;
                }
            }
        }
    }
}
}
