/* fn_801C957C: is any tile in the unit's range (by the move-range stat) free and passable? */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw on
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
typedef struct MUnit { u8 pad[0x102]; s8 x, y; } MUnit;
typedef struct BMap {
    s32 w, h;
    s8 x0, y0, x1, y1;
    u8 padC[0xF18E - 0xC];
    s8 b5S[0x2000];
    u8 pad1118E[0x15190 - 0x1118E];
    s16* curS;
} BMap;
extern BMap lbl_803EC898;
extern u32 fn_80110940(MUnit*);
extern void fn_801213D0(MUnit*, int);
extern int fn_801658E4(MUnit*, s8, s8);
int fn_801C957C(MUnit* u) {
    /*P*/
    int r;
    int found;
    int ux, uy;
    int x0, y0, x1, y1;
    int yy, xx;
    /*E*/
    r = (u8)fn_80110940(u);
    fn_801213D0(u, r);
    ux = u->x;
    uy = u->y;
    found = 0;
    x0 = ux - r;
    if (x0 < lbl_803EC898.x0) x0 = lbl_803EC898.x0;
    y0 = uy - r;
    if (y0 < lbl_803EC898.y0) y0 = lbl_803EC898.y0;
    x1 = ux + r;
    if (x1 > lbl_803EC898.x1 - 1) x1 = lbl_803EC898.x1 - 1;
    y1 = uy + r;
    if (y1 > lbl_803EC898.y1 - 1) y1 = lbl_803EC898.y1 - 1;
    for (yy = y0; yy <= y1; yy++) {
        for (xx = x0; xx <= x1; xx++) {
            if (r >= ABS(ux - xx) + ABS(uy - yy)) {
                if (lbl_803EC898.curS[(s8)xx + (s8)yy * 0x40] >= 0 && lbl_803EC898.b5S[(s8)xx + (s8)yy * 0x40] == 0 && !fn_801658E4(0, (s8)xx, (s8)yy)) {
                    found = 1;
                    goto out;
                }
            }
        }
    }
out:
    return found;
}
}
