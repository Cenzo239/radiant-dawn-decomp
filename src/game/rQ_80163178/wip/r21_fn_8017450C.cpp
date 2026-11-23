/* fn_8017450C (0x720): complete draft, round 21, written from the disassembly with matched fn_80172E70 and the
 * fn_80174CAC draft as models. Level `other`: 458 of 456 instructions, same calls,
 * constants and control flow. What differs (dd.py): the original keeps the count table pointer in r30 and spills
 * one more loop bound (`y1` and the row difference); ours spills the table pointer and reloads it before each of
 * its four reads, and tests `cnt[k] <= mx` with swapped compare operands. Declaring `cnt` first made it worse.
 * AI: phase fallback move (names guessed). For every unit on an AI-controlled side, set up the AI state and the
 * danger grid (fn_80166720), then score either every free tile in its move range (when the side's order is the
 * one with the highest count in lbl_803CB860, or that side is of kind 2 while any side is "on") or the tile the
 * search fn_8016E50C/fn_8016F94C proposes, with fn_8015804C. The best unit then moves there (fn_80160610 action 1).
 */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
struct Sb { u8 d[0xC]; };
extern "C" {
extern u8 lbl_80387308[];
extern u8 lbl_803872F8[];
extern struct Sb* lbl_804CB814;
extern u8 lbl_803CAB38[];
extern int lbl_803CB860[4];
int fn_8010E2F4(void*);
void* memset(void*, int, u32);
void fn_80163010(AiCfg*, Unit*);
void fn_80045120(AiAct*, Unit*);
void fn_80045548(AiAct*);
void fn_80166720(Unit*);
void fn_8010E41C(u8*, int);
void fn_80165F94(Unit*, int, int);
s8 fn_8012408C(Unit*);
int fn_801658E4(Unit*, s8, s8);
int fn_8015804C(Unit*, int, int);
BOOL fn_8016E50C(Filt*, Unit*, s16*, s16*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
}
static inline BOOL IsNz(int v) {
    return v != 0;
}
static inline BOOL SideOn(int i, int k) {
    BOOL r = 0;
    if (fn_8010E2F4(&lbl_804CB814[i]) > 0 && lbl_803CAB38[k] == 1) {
        r = 1;
    }
    return r;
}
static inline bool Not(bool v) { return !v; }
extern "C" u8 fn_8017450C(void) {
    AiAct* act;
    Map* m;
    int best;
    Unit* bu;
    int bx;
    int by;
    Unit* v;
    bool y;
    int id;
    bool x;
    u8 tbl[0xB];
    Filt a1;
    Filt c1;
    s16 ox;
    s16 oy;
    int* cnt;
    act = &lbl_803CA870;
    m = &lbl_803EC898;
    x = IsNz(SideOn(0, 0x14));
    x = x | SideOn(3, 0x17);
    x = x | SideOn(1, 0x15);
    x = x | SideOn(2, 0x16);
    best = 0x80000000;
    bu = 0;
    fn_8010E41C(tbl, 0);
    y = Not(x);
    cnt = lbl_803CB860;
    for (id = 1; id <= 0xFE; id++) {
        v = UnitGet(id);
        if (v->person) {
            if (tbl[v->team[8]] && !(v->flags10C & 0x9D)) {
                v->m3D0[0] = 0x40;
                v->b3BC = 0;
                fn_80163010(&lbl_804183F0, v);
                lbl_804183F0.done = 0;
                memset(lbl_804183F0.res, 0, 0x14);
                fn_80045120(act, v);
                fn_80166720(v);
                if (!(lbl_804183F0.flags & 2) && !(v->w3B4 & 0x7000000)) {
                    u8 cur = lbl_803CAB38[0x11];
                    bool on;
                    int mx;
                    u8 k;
                    BOOL all;
                    on = IsNz(SideOn(0, 0x14));
                    on = on | SideOn(3, 0x17);
                    on = on | SideOn(1, 0x15);
                    on = on | SideOn(2, 0x16);
                    mx = 0x80000000;
                    if (mx < cnt[0]) {
                        k = 0;
                        mx = cnt[0];
                    }
                    if (mx < cnt[1]) {
                        k = 1;
                        mx = cnt[1];
                    }
                    if (mx < cnt[2]) {
                        k = 2;
                        mx = cnt[2];
                    }
                    if (mx < cnt[3]) {
                        k = 3;
                    }
                    all = 0;
                    if ((on && lbl_803CAB38[0x14 + k] == 2) || k == cur) {
                        all = 1;
                    }
                    if (all) {
                        int ux, uy, rng, x0, y1, x1, xx, yy;
                        fn_80165F94(v, 6, -1);
                        uy = v->y;
                        ux = v->x;
                        rng = fn_8012408C(v);
                        x0 = ux - rng;
                        if (x0 < lbl_803EC898.x0) {
                            x0 = lbl_803EC898.x0;
                        }
                        yy = uy - rng;
                        if (yy < lbl_803EC898.y0) {
                            yy = lbl_803EC898.y0;
                        }
                        x1 = ux + rng;
                        if (x1 > lbl_803EC898.x1 - 1) {
                            x1 = lbl_803EC898.x1 - 1;
                        }
                        y1 = uy + rng;
                        if (y1 > lbl_803EC898.y1 - 1) {
                            y1 = lbl_803EC898.y1 - 1;
                        }
                        for (; yy <= y1; yy++) {
                            for (xx = x0; xx <= x1; xx++) {
                                if (rng >= ABS(ux - xx) + ABS(uy - yy)) {
                                    if (((Map*)&lbl_803EC898)->costS[(s8)xx + (s8)yy * 0x40] >= 0 && ((Map*)&lbl_803EC898)->b5S[(s8)xx + (s8)yy * 0x40] == 0 && !fn_801658E4(v, (s8)xx, (s8)yy)) {
                                        u8 t = m->ter[0][(s8)xx + (s8)yy * 0x40];
                                        if (t == 0 || t == v->tid) {
                                            int s = fn_8015804C(v, xx, yy);
                                            if (s > best) {
                                                best = s;
                                                bu = v;
                                                bx = xx;
                                                by = yy;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        Filt* s;
                        a1.u = v;
                        c1.u = v;
                        a1.vt = lbl_80387308;
                        c1.vt = lbl_803872F8;
                        s = &c1;
                        if (y) {
                            s = &a1;
                        }
                        if (fn_8016E50C(s, v, &ox, &oy)) {
                            int sc;
                            fn_8016F94C(v, ox, oy, 1, 0xFFFF, 0, 0, -1);
                            ox = act->x;
                            oy = act->y;
                            sc = fn_8015804C(v, ox, oy);
                            if (sc > best) {
                                bx = ox;
                                best = sc;
                                by = oy;
                                bu = v;
                            }
                        }
                    }
                }
                lbl_804183F0.done = 0;
                fn_80045548(act);
            }
        }
    }
    if (bu) {
        bu->m3D0[0] = 0x40;
        bu->b3BC = 0;
        fn_80163010(&lbl_804183F0, bu);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, bu);
        fn_80166720(bu);
        fn_80160610(1, (s8)bx, (s8)by, 0, (s8)bx, (s8)by, -1, 0, 0);
    }
    return lbl_804183F0.done;
}
