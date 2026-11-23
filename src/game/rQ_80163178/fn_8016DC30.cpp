#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
void fn_80165F94(Unit*, int, int);
s8 fn_8012408C(Unit*);
int fn_801658E4(Unit*, s8, s8);
u16 fn_801676D8(int, int);
}
extern "C" u32 fn_8016DC30(Unit* u, u32 thr, s16* ox, s16* oy) {
    Map* m;
    u16 bd;
    u16 bc;
    s16 cx;
    s16 cy;
    s16 bx;
    s16 by;
    int ux;
    int rng;
    int x1;
    int y;
    int x;
    int uy;
    int x0;
    int y1;
    bd = 0xFFFF;
    bc = bd;
    m = &lbl_803EC898;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    uy = u->y;
    ux = u->x;
    rng = fn_8012408C(u);
    x0 = ux - rng;
    if (x0 < lbl_803EC898.x0) {
        x0 = lbl_803EC898.x0;
    }
    y = uy - rng;
    if (y < lbl_803EC898.y0) {
        y = lbl_803EC898.y0;
    }
    x1 = ux + rng;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = uy + rng;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            if (rng >= ABS(ux - x) + ABS(uy - y)) {
                if (((Map*)&lbl_803EC898)->costS[(s8)x + (s8)y * 0x40] >= 0 && ((Map*)&lbl_803EC898)->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y)) {
                    u8 t = m->ter[0][(s8)x + (s8)y * 0x40];
                    if (t == 0 || t == u->tid) {
                        if (fn_801676D8((s8)x, (s8)y) < thr) {
                            int c = ((Map*)&lbl_803EC898)->costS[(s8)x + (s8)y * 0x40];
                            if (c < bc) {
                                bx = x;
                                by = y;
                                bc = c;
                            }
                        } else if (fn_801676D8((s8)x, (s8)y) < bd) {
                            cy = y;
                            cx = x;
                            bd = fn_801676D8((s8)x, (s8)y);
                        }
                    }
                }
            }
        }
    }
    if (bc != 0xFFFF) {
        *ox = bx;
        *oy = by;
        return 1;
    }
    if (bd != 0xFFFF) {
        *ox = cx;
        *oy = cy;
        return 1;
    }
    return 0;
}
