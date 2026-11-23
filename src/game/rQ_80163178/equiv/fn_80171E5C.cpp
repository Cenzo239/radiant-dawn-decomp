/* fn_80171E5C (0x54C): functionally equal at `regs` level (tools/check_regs.py, round 20; 52 words differ in
 * registers). New this round, written from the disassembly; uses all of r14..r31 with one spilled value (x0 of the
 * first scan), which this form reproduces.
 * Notes for a port:
 *   - FindWpn is faithful to the original and looks odd: when the unit has an equipped weapon entry with an item it
 *     still walks the inventory for the first item fn_8012BB08 accepts, and when the walk runs through all seven
 *     slots `w` is left on the last slot. `w` lives on the stack (the original passes it by reference).
 *   - `Map* m` is declared just before the second scan on purpose: declared at the top it takes a saved register
 *     for the whole function and a second value spills.
 *   - The one-case `switch` on the attack grid gives the original's `beq; b` pair; `if (... == 0) continue;` gives
 *     one `bne`. The mix of `m->`, `lbl_803EC898.` and `((Map*)&lbl_803EC898)->` follows the neighbouring files.
 *   - Parameter names (useWpn, fromPos, all) are guesses from the calls they select.
 */
/* fn_80171E5C: AI: counts the units accepted by filter `f` that `u` could reach an attack on within `range`
 * moves (plus weapon range when `useWpn`), after rebuilding the movement and attack grids. Names guessed. */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
extern "C" {
Inv* fn_8012759C(Unit*);
int fn_8012BB08(Unit*, u8*);
void fn_80165E18(Unit*, int, int);
void fn_80165F94(Unit*, int, int);
void fn_801659F4(int, int, int, int, int);
void fn_80165A64(int, int, int, int, int);
int fn_80165818(void);
void fn_801148CC(Map*, int);
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
u8 fn_801107A0(u8*, Unit*);
u8 fn_801107C0(u8*, Unit*);
int fn_801658E4(Unit*, s8, s8);
void fn_80115DEC(Map*, int, int, u8, u8);
}
static inline void FindWpn(Unit* u, Inv*& w) {
    int i;
    Inv* q;
    w = fn_8012759C(u);
    if (w != 0 && w->item == 0) {
        return;
    }
    for (i = 0, q = u->inv; i < 7; i++, q++) {
        w = q;
        if (!q || !q->item) {
            break;
        }
        if (fn_8012BB08(u, q->item)) {
            break;
        }
    }
}
extern "C" int fn_80171E5C(Filter* f, Unit* u, int range, int useWpn, int fromPos, int all) {
    Inv* w = 0;
    u32 keep;
    int n;
    if (useWpn) {
        FindWpn(u, w);
    }
    if (useWpn && w == 0) {
        useWpn = 0;
    }
    keep = u->w3B4 & 0x7000000;
    u->w3B4 &= ~0x7000000;
    if (all) {
        if (!fromPos) {
            fn_80165E18(u, 6, range);
        } else {
            fn_801659F4(u->x, u->y, 0, 6, range);
        }
    } else {
        if (!fromPos) {
            fn_80165F94(u, 6, range);
        } else {
            fn_80165A64(u->x, u->y, 0, 6, range);
        }
    }
    u->w3B4 |= keep;
    if (useWpn) {
        int ux;
        int uy;
        s8 mn;
        s8 mx;
        int x0;
        int y;
        int x1;
        int y1;
        int x;
        fn_801148CC(&lbl_803EC898, fn_80165818());
        fn_80114B44(&lbl_803EC898, 9, 0);
        ux = u->x;
        uy = u->y;
        mn = w->item ? fn_801107A0(w->item, u) : 0;
        mx = w->item ? fn_801107C0(w->item, u) : 0;
        x0 = ux - range;
        if (x0 < lbl_803EC898.x0) {
            x0 = lbl_803EC898.x0;
        }
        y = uy - range;
        if (y < lbl_803EC898.y0) {
            y = lbl_803EC898.y0;
        }
        x1 = ux + range;
        if (x1 > lbl_803EC898.x1 - 1) {
            x1 = lbl_803EC898.x1 - 1;
        }
        y1 = uy + range;
        if (y1 > lbl_803EC898.y1 - 1) {
            y1 = lbl_803EC898.y1 - 1;
        }
        for (; y <= y1; y++) {
            for (x = x0; x <= x1; x++) {
                if (range >= ABS(ux - x) + ABS(uy - y)) {
                    if (((Map*)&lbl_803EC898)->costS[(s8)x + (s8)y * 0x40] >= 0 && ((Map*)&lbl_803EC898)->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y) && ((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40] == 0) {
                        fn_80115DEC(&lbl_803EC898, (s8)x, (s8)y, mn, mx);
                    }
                }
            }
        }
        fn_80114888(&lbl_803EC898, 6);
    }
    {
        int ux = u->x;
        int uy = u->y;
        int r;
        int x0;
        int y;
        int x1;
        int y1;
        int x;
        n = 0;
        r = range + (useWpn ? (w->item ? fn_801107C0(w->item, u) : 0) : 0);
        x0 = ux - r;
        if (x0 < lbl_803EC898.x0) {
            x0 = lbl_803EC898.x0;
        }
        y = uy - r;
        if (y < lbl_803EC898.y0) {
            y = lbl_803EC898.y0;
        }
        x1 = ux + r;
        if (x1 > lbl_803EC898.x1 - 1) {
            x1 = lbl_803EC898.x1 - 1;
        }
        y1 = uy + r;
        if (y1 > lbl_803EC898.y1 - 1) {
            y1 = lbl_803EC898.y1 - 1;
        }
        Map* m = &lbl_803EC898;
        for (; y <= y1; y++) {
            for (x = x0; x <= x1; x++) {
                if (r >= ABS(ux - x) + ABS(uy - y)) {
                    u8 t = m->ter[0][(s8)x + (s8)y * 0x40];
                    if (t != 0) {
                        Unit* v = UnitGet(t);
                        if (useWpn) {
                            switch (m->g4[(s8)x + (s8)y * 0x40]) {
                            case 0:
                                continue;
                            }
                        } else {
                            if (m->costS[(s8)x + (s8)y * 0x40] < 0) {
                                continue;
                            }
                        }
                        if (v != u && f->check(v)) {
                            n++;
                        }
                    }
                }
            }
        }
    }
    return n;
}
