/* fn_80171494 (round 18): other. Logic complete; 262 vs 282 instructions. The original runs out of saved registers: it rematerialises &lbl_803EC898 at each direct use, spills both vtable addresses (0x3C, 0x40) and hoists four row pointers (r23..r26); here the direct uses are CSE'd into one function-wide base instead. Needs the exact live set (see fn_8016DC30). */
/* AI: nearest reachable tile (by the cost2 grid) that passes the lbl_803877D0 tile test, preferring
 * tiles that are also in move range. Sibling of fn_8016D27C / fn_80171A30. Names guessed. */
#include "game/rQ_80163178/common.h"
struct Ak {
    void* vt;
    Unit* u;
    u8 k;
    Ak(void* v, Unit* w, u8 kk) {
        u = w;
        vt = v;
        k = kk;
    }
};
extern "C" {
extern ListHdr lbl_803E7320[];
extern s16 lbl_8036B278[];
extern u8 lbl_80387308[];
extern u8 lbl_803877D0[];
void fn_80165F94(Unit*, int, int);
void fn_80165E18(Unit*, int, int);
void fn_80166110(Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
void fn_800CFB34(ListHdr*);
void fn_80039708(void*, int, int);
}
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}
static inline s16 C2A(int x, int y) { return ((Map*)&lbl_803EC898)->cost2S[(s8)x + (s8)y * 0x40]; }
static inline s16 C2(Map* m, int x, int y) { return m->cost2S[(s8)x + (s8)y * 0x40]; }
static inline s16 C1(Map* m, int x, int y) { return m->costS[(s8)x + (s8)y * 0x40]; }
static inline s8 B5(int x, int y) { return ((Map*)&lbl_803EC898)->b5S[(s8)x + (s8)y * 0x40]; }
static inline u8 T0(Map* m, int x, int y) { return m->ter[0][(s8)x + (s8)y * 0x40]; }
static inline u8 T0d(int x, int y) { return lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]; }
static inline s16 C2d(int x, int y) { return lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40]; }
static inline s16 C1d(int x, int y) { return lbl_803EC898.costS[(s8)x + (s8)y * 0x40]; }
static inline int Cnt(Map* m, Unit* u, s16 y, s16 x, Filt& g) {
    int n = 0;
    s16* d;
    g.u = u;
    g.vt = lbl_80387308;
    for (d = lbl_8036B278; *d != 0x7FFF; d += 2) {
        int py = y + d[1];
        int px = x + d[0];
        BOOL o = 0;
        if (px < m->x0 || m->x1 - 1 < px || py < m->y0 || m->y1 - 1 < py) {
            o = 1;
        }
        if (!o && T0(m, px, py) && ((Filter*)&g)->check(UnitGet(T0(m, px, py)))) {
            n++;
        }
    }
    return n;
}
static inline s16 C2m(Map* m, int x, int y) { return m->cost2S[(s8)x + (s8)y * 0x40]; }
static inline s8 B5m(Map* m, int x, int y) { return m->b5S[(s8)x + (s8)y * 0x40]; }
extern "C" BOOL fn_80171494(Unit* u, u8 k, u32 fl, s16* ox, s16* oy) {
/*P*/
    Map* m;
    s16 best;
    s16 bc;
    int y;
    int x;
    int bx;
    int by;
/*E*/
    Filt g;
    best = 0x7FFF;
    bc = -1;
    fn_80165F94(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    if (fl & 0x100) {
        fn_80166110(u, 7, lbl_803EC898.w * lbl_803EC898.h);
    } else {
        fn_80165E18(u, 7, lbl_803EC898.w * lbl_803EC898.h);
    }
    if (fl & 8) {
        k &= ~1;
    }
    if (fl & 0x10) {
        k &= ~2;
    }
    m = &lbl_803EC898;
    for (y = m->y0; y <= m->y1 - 1; y++) {
        for (x = m->x0; x <= m->x1 - 1; x++) {
            if (C2m(m, x, y) >= 0 && B5m(m, x, y) == 0 && !fn_801658E4(u, (s8)x, (s8)y) && (!(fl & 1) || T0d(x, y) == 0)) {
                if ((fl & 2) && T0d(x, y)) {
                    Unit* v = UnitGet(T0d(x, y));
                    if (SameT(u, v, 1)) continue;
                }
                if ((fl & 4) && Cnt(m, u, y, x, g)) continue;
                {
                    Ak a(lbl_803877D0, u, k);
                    fn_800CFB34(lbl_803E7320);
                    fn_80039708(&a, (s8)x, (s8)y);
                }
                if (lbl_803E7320->n) {
                    s16 c = C1d(x, y);
                    s16 c2 = C2d(x, y);
                    if (T0d(x, y)) {
                        c = -1;
                    }
                    if (c2 < best) {
                        if (c >= 0 || bc < 0) {
                            best = c2;
                            bc = c;
                            bx = x;
                            by = y;
                        }
                    } else if (c >= 0 && bc < 0) {
                        best = c2;
                        bc = c;
                        bx = x;
                        by = y;
                    }
                }
            }
        }
    }
    if (best != 0x7FFF) {
        Ak a2(lbl_803877D0, u, k);
        fn_800CFB34(lbl_803E7320);
        fn_80039708(&a2, (s8)bx, (s8)by);
        *ox = bx;
        *oy = by;
        return 1;
    }
    fn_800CFB34(lbl_803E7320);
    return 0;
}
