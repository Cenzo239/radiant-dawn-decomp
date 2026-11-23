/* fn_8016B90C (0x4F4): functionally equal at `regs` level (tools/check_regs.py, round 20). Sibling of
 * fn_8016B3F4 (see equiv/fn_8016B3F4.cpp for the notes): the target test is `fn_80108F68(&v->w110) != 1` and any
 * item fn_8012B63C accepts, and the score adds fn_80126BA4(v) instead of fn_80123998(v). Derived from the
 * fn_8016B3F4 file by text substitution after diffing the two originals.
 * Caveats: templates as aggregate initialisers; the original reads lbl_8036B258 (target) and lbl_8036B248 (actor),
 * same values as lbl_8036B238/lbl_8036B228. fn_80108F68's result is compared unsigned (cast here; its real return
 * type is probably unsigned).
 */
/* symcheck: (a) block 0 stays flagged, artefact: the original's asm has `lis r0, 0x803f` ... `subi r4, r4, 0x3768` unsymbolised (the half goes through a stack slot); 0x803F0000 - 0x3768 = lbl_803EC898, which is what ours loads. */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
struct Bs { Unit* u; s8 x; s8 y; u8 k; u8 p7; u32 a; u32 b; };
extern "C" {
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
void fn_80165F94(Unit*, int, int);
void fn_80169C70(Unit*, void*);
void fn_80170B70(Unit*, Inv*);
u8 fn_80110880(u8*, Unit*);
s8 fn_8012408C(Unit*);
int fn_80108F68(void*);
u8 fn_80126BA4(Unit*);
int fn_8016D11C(Unit*);
BOOL fn_80169B20(Unit*, u16, int, int, void*, s16*, s16*);
void fn_8012A088(Unit*, int);
int fn_8016A280(Unit*, Unit*, Inv*, void*, s16*, s16*);
u8* fn_801116B8(Inv*);
int fn_8012B63C(Unit*, u8*);
u8 fn_80127520(Unit*);
void fn_800269E4(void*, void*, void*);
void fn_8002C0EC(void*, int);
s8 fn_80120928(Unit*, Unit*);
s16 fn_80123998(Unit*);
extern const struct Bs lbl_8036B238;
extern const struct Bs lbl_8036B228;
extern u8 lbl_803C8E80[];
void fn_80160610(int, int, int, Unit*, int, int, int, int, int);
}
static inline void Do(Unit* u, Unit* v, s16& ox, s16& oy, int slot) {
    Bs b = {0, 0, 0, 0, 1, 0, 0x1000000};
    b.u = v; b.x = v->x; b.y = v->y; b.k = fn_80127520(v);
    Bs a = {0, 0, 0, 0, 0, 0, 0x1000000};
    a.u = u; a.x = ox; a.y = oy; a.k = slot;
    fn_800269E4(lbl_803C8E80, &a, &b);
}
static inline BOOL HasK(Unit* v, Inv*& q) {
    int i;
    q = v->inv;
    for (i = 0; i < 7; i++, q++) {
        if (!q || !q->item) {
            break;
        }
        if (fn_8012B63C(v, q->item)) {
            return 1;
        }
    }
    return 0;
}
extern "C" u32 fn_8016B90C(Unit* u, int slot, Filter* f, void* arg) {
    Map* m = &lbl_803EC898;
/*P*/
    Unit* v;
    Inv* q;
    u8 bs;
    int ux;
    int rng;
    int x1;
    int x;
    s16 bx;
    s16 by;
    Unit* bv;
    int uy;
    int x0;
    int y1;
    int y;
    int bx2;
/*E*/
    s16 ox;
    s16 oy;
    int s;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    fn_80169C70(u, arg);
    fn_80170B70(u, &u->inv[slot]);
    bv = 0;
    bs = 0;
    uy = u->y;
    ux = u->x;
    bx2 = (u->inv[slot].item ? fn_80110880(u->inv[slot].item, u) : 0);
    {
        int b = fn_8012408C(u);
        rng = b + bx2;
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
    for (; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            if (rng >= ABS(ux - x) + ABS(uy - y)) {
                if (m->g4[(s8)x + (s8)y * 0x40]) {
                    u8 t = m->ter[0][(s8)x + (s8)y * 0x40];
                    if (t && t != u->tid) {
                        v = UnitGet(t);
                        if ((lbl_804183F0.flags & 4) || f->check(v)) {
                            if ((u32)fn_80108F68((u8*)v + 0x110) != 1 && HasK(v, q)) {
                                if (fn_8016A280(u, v, &u->inv[slot], arg, &ox, &oy)) {
                                    Do(u, v, ox, oy, slot);
                                    fn_8002C0EC(lbl_803C8E80, (s8)slot);
                                    s = fn_80120928(u, v);
                                    if (s >= 5 && bs <= s + fn_80126BA4(v)) {
                                        bs = s + fn_80126BA4(v);
                                        bx = ox;
                                        by = oy;
                                        bv = v;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (bv) {
        if (slot >= 0 && slot < 7) {
            fn_8012A088(u, slot);
            slot = 0;
        }
        fn_80160610(0x10, (s8)bx, (s8)by, bv, bv->x, (s8)*(u8*)&bv->y, (s8)slot, 0, 0);
        u->h3BE = bs;
    }
    return bv != 0;
}
