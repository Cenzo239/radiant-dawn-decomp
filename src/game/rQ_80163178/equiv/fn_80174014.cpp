/* fn_80174014 (0x4F8): complete draft, round 21, written from the disassembly. Functionally equal at
 * `regs` level (tools/check_regs.py, round 21; 30 words differ in registers). `Filt* fp` and the u8 `tx`/`ty` are
 * what the original code shape needs (pointer held in r29, late sign extension).
 * AI: skill-driven attack choice over all AI units (names guessed). For each AI unit with skill lbl_804CA5C4 the
 * free tiles in its move range are collected into lbl_803E7320 (filter object with vtable lbl_803878E0), then the
 * target pickers fn_801739D0, fn_80173C04, fn_80173D10, fn_80173F08 are tried in order of priority; a hit by a
 * better (lower) picker than any before resets the best score. The unit whose target has the highest h3BE wins and
 * attacks it (action 0x2C with skill lbl_804CA4EC, else 0x12).
 * Faithful oddity: when `mode` is 3 or 4 and all four pickers return 0 the original still reads t->h3BE through
 * the null result (address 0x3BE); a port should skip the comparison when t is 0.
 */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
extern u8 lbl_803878E0[];
extern u8 lbl_80387338[];
extern ListHdr lbl_803E7320[];
extern u32 lbl_804CA5C4;
extern u32 lbl_804CA4EC;
void* memset(void*, int, u32);
void fn_80163010(AiCfg*, Unit*);
void fn_80045120(AiAct*, Unit*);
void fn_80045548(AiAct*);
void fn_80166720(Unit*);
void fn_8010E41C(u8*, int);
int fn_8011B77C(void*, u32);
void fn_800CFB34(ListHdr*);
void fn_800392FC(void*, int, int);
void fn_80165F94(Unit*, int, int);
s8 fn_8012408C(Unit*);
int fn_801658E4(Unit*, s8, s8);
Unit* fn_801739D0(ListHdr*);
Unit* fn_80173C04(ListHdr*);
Unit* fn_80173D10(ListHdr*);
Unit* fn_80173F08(ListHdr*);
void fn_80169B20(Unit*, u16, int, int, void*, s16*, s16*);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
}
/* collect the free tiles in f->u's move range */
static inline void Scan(Filt* f) {
    int ux, uy, rng, x0, y, x1, y1, x;
    fn_80165F94(f->u, 6, -1);
    ux = f->u->x;
    uy = f->u->y;
    rng = fn_8012408C(f->u);
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
                if (lbl_803EC898.curS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(f->u, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40] == 0) {
                    fn_800392FC(f, (s8)x, (s8)y);
                }
            }
        }
    }
}
extern "C" u8 fn_80174014(void) {
    AiAct* act;
    int mode;
    int m;
    Unit* best;
    Unit* tgt;
    Unit* v;
    Unit* t;
    int id;
    u8 tbl[0xB];
    Filt f;
    Filt b;
    s16 ox;
    s16 oy;
    Filt* fp;
    act = &lbl_803CA870;
    mode = 4;
    m = 0x80000000;
    best = 0;
    tgt = 0;
    fn_8010E41C(tbl, 0);
    fp = &f;
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
                if (fn_8011B77C(v->skills, lbl_804CA5C4)) {
                    f.u = v;
                    f.vt = lbl_803878E0;
                    fn_800CFB34(lbl_803E7320);
                    Scan(fp);
                    if (lbl_803E7320->n != 0) {
                        if ((t = fn_801739D0(lbl_803E7320)) != 0) {
                            if (mode != 0) {
                                mode = 0;
                                m = 0x80000000;
                            }
                        } else if (mode >= 1 && (t = fn_80173C04(lbl_803E7320)) != 0) {
                            if (mode != 1) {
                                mode = 1;
                                m = 0x80000000;
                            }
                        } else if (mode >= 2 && (t = fn_80173D10(lbl_803E7320)) != 0) {
                            if (mode != 2) {
                                mode = 2;
                                m = 0x80000000;
                            }
                        } else if (mode >= 3 && (t = fn_80173F08(lbl_803E7320)) != 0) {
                            if (mode != 3) {
                                mode = 3;
                                m = 0x80000000;
                            }
                        }
                        if (t->h3BE > m) {
                            best = v;
                            tgt = t;
                            m = t->h3BE;
                        }
                    }
                }
                lbl_804183F0.done = 0;
                fn_80045548(act);
            }
        }
    }
    if (best) {
        u8 tx, ty;
        best->m3D0[0] = 0x40;
        best->b3BC = 0;
        fn_80163010(&lbl_804183F0, best);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, best);
        fn_80166720(best);
        fn_80165F94(best, 6, -1);
        b.u = best;
        b.vt = lbl_80387338;
        fn_80169B20(best, 0xFFFF, tgt->x, tgt->y, &b, &ox, &oy);
        ty = tgt->y;
        tx = tgt->x;
        fn_80160610(fn_8011B77C(best->skills, lbl_804CA4EC) ? 0x2C : 0x12, (s8)ox, (s8)oy, tgt, (s8)tx, (s8)ty, -1, 0, 0);
    }
    return lbl_804183F0.done;
}
