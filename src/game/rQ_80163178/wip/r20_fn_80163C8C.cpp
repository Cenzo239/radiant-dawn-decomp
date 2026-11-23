/* fn_80163C8C (0x3D8, round 20): `other`. Complete and correct draft, compiles on its own (declarations of
 * equiv/fn_80164064.cpp). AI: move to the best free tile within reach that is a shelter tile or has one of the
 * four neighbours with terrain flag 0x40, when its threat value is at most `lim` (names guessed).
 * What differs: 242 instructions against 246, same blocks and calls. The original runs out of saved registers
 * (stmw r14) and spills ux, uy, bx, by as s16 slots (0x26, 0x24, 0x2A, 0x28): `ux = (u8)u->x; ux = (s8)ux;` is
 * stored, reloaded with `lha`, sign-extended and stored again, and every later use reloads it. Here the first
 * store/reload pair of ux and uy is forwarded (spilled as int words after the `extsb`), which is the 4 missing
 * instructions and moves the other spill slots by 4. Tried: reading through a GetPos(u, &x, &y) inline (same), a
 * nested-struct position (best position goes to memory, the unit position still does not), volatile (right
 * load/store pattern but a different frame).
 * `Shelter` returns through a local so that `found = 0` is materialised as in the original.
 */
/* AI: closest tile searches on the map. */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
struct Ar { void* vt; u32 k; };
extern "C" {
extern ListHdr lbl_803E7320[];
extern s16 lbl_8036B278[];
extern s16 lbl_8036B060[][2];
extern u8 lbl_80387308[];
extern u8 lbl_80387800[];
void fn_80165E18(Unit*, int, int);
void fn_80165F94(Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
void fn_800CFB34(ListHdr*);
void fn_80039708(void*, int, int);
int fn_800A05B0(int, int, int);
u16 fn_801676D8(int, int);
void* fn_801181E8(Map*, int, int);
int fn_80171378(int, int, Filt*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
s8 fn_8012408C(Unit*);
int fn_8011799C(Map*, int, int);
u8 fn_80118098(Map*, int, int);
u8* fn_8010B240(u8);
u8 fn_80110880(u8*, Unit*);
u8 fn_801107B8(u8*, Unit*);
void fn_801663E0(int, int, u8, u8, int);
int fn_8016D11C(Unit*);
int fn_8015814C(Unit*, int, int, int);
int fn_80158208(Unit*, int, int, int);
void fn_80116BD0(Map*, int, int, int, int);
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}

BOOL fn_8016D27C(Unit* u, u32 fl, u32 k, s16* ox, s16* oy);

u8 fn_80164064(Unit* u, u32 lim);
u8 fn_80163C8C(Unit* u, u16 lim);


BOOL fn_8016A280(Unit* u, Unit* t, Inv* p, Filter* f, s16* ox, s16* oy);

int fn_8016A9BC(Unit* u, int x, int y, int a, int r);
}


struct T181 { u8 pad[8]; u8* p8; };
static inline T181* Shelter(int x, int y) {
    s16 (*d)[2] = lbl_8036B060;
    T181* r = 0;
    u32 k;
    for (k = 0; k < 4; k++, d++) {
        int xx = x + (*d)[0];
        int yy = y + (*d)[1];
        if (fn_8011799C(&lbl_803EC898, (s8)xx, (s8)yy)) {
            u8 t = fn_80118098(&lbl_803EC898, (s8)xx, (s8)yy);
            if (((T181*)fn_8010B240(t))->p8[7] & 0x40) {
                r = (T181*)fn_8010B240(t);
                break;
            }
        }
    }
    return r;
}
extern "C" {
u8 fn_80163C8C(Unit* u, u16 lim) {
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        return 0;
    } else {
/*P*/
        Map* m = &lbl_803EC898;
        int cb = 0x7FFFFFFF;
        int best = 0xFF;
        s16 bx;
        s16 by;
        s16 ux;
        s16 uy;
        int rng;
        int x0;
        int y;
        int x1;
        int y1;
        int x;
/*E*/
        Filt g;
        fn_80165F94(u, 6, -1);
        ux = *(u8*)&u->x;
        uy = *(u8*)&u->y;
        ux = (s8)ux;
        uy = (s8)uy;
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
                    if (((Map*)&lbl_803EC898)->costS[(s8)x + (s8)y * 0x40] >= 0 && ((Map*)&lbl_803EC898)->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y) && ((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40] == 0) {
                        if (Shelter((s16)x, (s16)y) == 0) {
                            if (((T181*)fn_801181E8(m, (s8)x, (s8)y))->p8[6] == 0) {
                                continue;
                            }
                        }
                        if (lim >= fn_801676D8((s8)x, (s8)y)) {
                            int c;
                            g.u = u;
                            g.vt = lbl_80387308;
                            c = fn_80171378((s16)x, (s16)y, &g);
                            if (c <= cb && m->curS[(s8)x + (s8)y * 0x40] < best) {
                                best = (u8)m->curS[(s8)x + (s8)y * 0x40];
                                bx = x;
                                cb = c;
                                by = y;
                            }
                        }
                    }
                }
            }
        }
        if (cb != 0x7FFFFFFF && m->ter[0][(s8)bx + (s8)by * 0x40] != u->tid) {
            int K = 0x10000;
            fn_8016F94C(u, bx, by, 1, (u16)(K - 1), 0, 0, -1);
        }
        return lbl_804183F0.done;
    }
}
}
