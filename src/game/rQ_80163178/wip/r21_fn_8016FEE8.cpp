/* fn_8016FEE8 (0x6C0): complete self-contained draft (round 21), the round 12 section of wip/near2.cpp unchanged.
 * Level `other`: 430 of 432 instructions, same calls, constants and control flow. What differs (dd.py, 76 masked
 * lines, all spill placement): the function uses r14..r31 and spills twelve locals. The original keeps the stepped
 * `x + r` in r14 (set with an `add` at the head of the x loop) and spills the flag `ok` and the row bound; ours
 * spills `x + r` and keeps `ok` in a register, and the s16 result locals (bx, by, ax, ay, cx, cy, bd, b22, d, d24)
 * sit in other stack slots. The plain form (`Safe(u, x, y, x + r, y + r, f, r)` without the hand-stepped xe/ye)
 * is 14 instructions shorter and further away.
 * Port caveat: xe/ye are only `x + r` / `y + r`; drop them and pass the sums. The declaration order is from an old search.
 * AI: move `u` toward (x_, y_) by picking the reachable tile with the lowest path cost that no unit accepted by
 * `f` can reach within `r`; fallbacks cx/cy (closest above the current cost) and ax/ay (lowest danger above
 * `thr`) are used when `f9` is set (names guessed).
 */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
void fn_80165B48(int, int, Unit*, int, int);
void fn_80165CB0(int, int, Unit*, int, int);
void fn_80165AD4(int, int, int, u8*, int, int);
s8 fn_8012408C(Unit*);
int fn_801658E4(Unit*, s8, s8);
u16 fn_801676D8(int, int);
int fn_80165818(void);
void fn_801148CC(Map*, int);
}
static inline s16 CostAt(Unit* u, int x, int y) {
    if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < 0) {
        return 0x7FFF;
    }
    return lbl_803EC898.cost2S[u->x + u->y * 0x40];
}
static inline int Safe(Unit* u, int x, int y, int xe, int ye, Filter* f, int r) {
                        int xx0, xx1, yy, yy1, xx;
                        xx0 = x - r;
                        if (xx0 < lbl_803EC898.x0) {
                            xx0 = lbl_803EC898.x0;
                        }
                        yy = y - r;
                        if (yy < lbl_803EC898.y0) {
                            yy = lbl_803EC898.y0;
                        }
                        xx1 = xe;
                        if (xx1 > lbl_803EC898.x1 - 1) {
                            xx1 = lbl_803EC898.x1 - 1;
                        }
                        yy1 = ye;
                        if (yy1 > lbl_803EC898.y1 - 1) {
                            yy1 = lbl_803EC898.y1 - 1;
                        }
                        for (; yy <= yy1; yy++) {
                            for (xx = xx0; xx <= xx1; xx++) {
                                if (r >= ABS(x - xx) + ABS(y - yy)) {
                                    u8 t2 = lbl_803EC898.ter[0][(s8)xx + (s8)yy * 0x40];
                                    if (t2 && f->check(UnitGet(t2))) {
                                        fn_801148CC(&lbl_803EC898, fn_80165818());
                                        fn_80165AD4(xx, yy, 0, u->team, 0xC, lbl_803EC898.w * lbl_803EC898.h);
                                        if (lbl_803EC898.curS[(s8)x + (s8)y * 0x40] <= r) {
                                            return 0;
                                        }
                                    }
                                }
                            }
                        }
    return 1;
}
extern "C" void fn_8016FEE8(Unit* u, int x_, int y_, Filter* f, int r, u8 act, u16 thr, int fl, u8 f9, int rng) {
/*P*/
    int y;
    int x;
    int ok;
    int xe;
    int ye;
    s16 bx;
    s16 b22;
    s16 d;
    s16 d24;
    s16 by;
    u16 bd;
    s16 ax;
    s16 ay;
    s16 cx;
    s16 cy;
    int ux;
    int uy;
    int x0;
    int x1;
    int y1;
/*E*/
    if (fl) {
        fn_80165B48(x_, y_, u, 7, lbl_803EC898.w * lbl_803EC898.h);
    } else {
        fn_80165CB0(x_, y_, u, 7, lbl_803EC898.w * lbl_803EC898.h);
    }
    d = CostAt(u, x_, y_);
    ux = u->x;
    uy = u->y;
    bd = 0xFFFF;
    d24 = -1;
    bx = -1;
    b22 = 0x7FFF;
    if (rng < 0) {
        rng = fn_8012408C(u);
    }
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
    for (ye = y + r; y <= y1; ye++, y++) {
        for (x = x0, xe = x + r; x <= x1; xe++, x++) {
            if (rng >= ABS(ux - x) + ABS(uy - y)) {
                if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y)) {
                    u8 t = lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40];
                    if ((t == 0 || t == u->tid) && lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40] >= 0) {
                        ok = Safe(u, x, y, xe, ye, f, r);
                        if (ok) {
                            if (thr < fn_801676D8((s8)x, (s8)y)) {
                                if (bd > fn_801676D8((s8)x, (s8)y)) {
                                    bd = fn_801676D8((s8)x, (s8)y);
                                    ax = x;
                                    ay = y;
                                }
                            } else {
                                s16 c = lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40];
                                if (d < c) {
                                    if (b22 > c) {
                                        b22 = c;
                                        cx = x;
                                        cy = y;
                                    }
                                } else if (c < d || fn_801676D8((s8)x, (s8)y) < d24) {
                                    d = lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40];
                                    d24 = fn_801676D8((s8)x, (s8)y);
                                    bx = x;
                                    by = y;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (bx != -1) {
        fn_80160610(act, (s8)bx, (s8)by, 0, (s8)bx, (s8)by, -1, 0, 0);
    } else if (f9 && b22 != 0x7FFF) {
        fn_80160610(act, (s8)cx, (s8)cy, 0, (s8)cx, (s8)cy, -1, 0, 0);
    } else if (f9 && bd != 0xFFFF) {
        fn_80160610(act, (s8)ax, (s8)ay, 0, (s8)ax, (s8)ay, -1, 0, 0);
    }
}
