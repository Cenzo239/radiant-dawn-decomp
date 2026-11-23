/* fn_80166720 (0xFB8): complete draft, round 21, written from the disassembly. Level `other`: 1004 of 1006
 * instructions, same calls, constants and control flow. What differs (tools/equiv/dd.py):
 *   - the original re-extends the damage before clamping it (`clrlwi r0,rD,16; cmplwi r0,0xff`) in both write
 *     loops; ours compares the register directly (the two missing instructions). u16/int/u32 locals, a cast, an
 *     inline taking u16 and opt_propagation off all gave the same code;
 *   - `buf + (xx + yy * w)` is added in the other operand order in the two write loops;
 *   - the two out-parameter addresses of fn_801586C8 and a few loads at loop heads are scheduled one slot apart,
 *     the spilled locals sit in other stack slots, and registers differ (the original spills eleven values).
 * The check_func.py "wrong reference" lines are artefacts of the 8-byte shift.
 * AI: builds the "danger" grid for unit `u` (names guessed). For every enemy `v` on the map that can act against
 * `u`, pick its best melee weapon (range <= 1, highest fn_80110DA8) and its best ranged weapon (longest range, then
 * highest fn_80110DA8), simulate `v` attacking `u` with each (fn_800269E4 / fn_8002742C / fn_801586C8) and take the
 * expected damage. The damage is written (as a maximum per tile, in a scratch byte buffer) on every tile around `u`
 * within u's move that `v` can attack with that weapon (grid g4 after fn_80170910) and then added, saturating at
 * 0xFF, to grid g3. A last pass adds trap damage (objects of kind 0xE from fn_80066130) to g3.
 * Notes for a port:
 *   - Blk is fn_801658E4 (matched in fn_801658E4.cpp) inlined by the original five times; keep one copy.
 *   - The two battle-side templates are lbl_8036B0F0 (target side) and lbl_8036B0E0 (attacker side), both
 *     {0, 0, 0, 0, 1, 0, 0} in the DOL; they are read through externs here.
 *   - lbl_8036B100 is the empty allocation tag "" (8 zero bytes in .rodata).
 *   - The original uses _savegpr_14 (no stmw), hence the pragma.
 */
#include "game/rQ_80163178/common.h"
#pragma use_lmw_stmw off
#define ABS(a) ((a) < 0 ? -(a) : (a))
struct Bs { Unit* u; s8 x; s8 y; u8 k; u8 p7; u32 a; u32 b; };
extern "C" {
void fn_80114B44(Map*, int, int);
void* fn_80078CCC(int, const char*, int);
void fn_80078E24(void*);
int fn_801148D8(Map*, int);
void fn_801148CC(Map*, void*);
void DCZeroRange(void*, u32);
s8 fn_8012408C(Unit*);
void fn_80165F94(Unit*, int, int);
int fn_8011F1A8(Unit*, Unit*);
int fn_8012BA20(Unit*, u8*);
u8 fn_801107C0(u8*, Unit*);
u8 fn_80110DA8(Inv*);
u32 fn_80170664(Unit*, Unit*, Inv*);
u8 fn_80127520(Unit*);
void fn_800269E4(void*, void*, void*);
void* fn_80165818(void);
void fn_8002742C(u8*, int);
void fn_801586C8(u8*, u8*, int*, int*, int);
void fn_80170910(Unit*, Inv*);
u8* fn_80158C98(void);
int fn_800A05B0(int, int, int);
void fn_80026CD8(u8*, Unit*, int);
void fn_8002C170(u8*);
u8* fn_80066130(u8*, int, int, int);
int fn_80067128(u8*, int);
extern Bs lbl_8036B0E0;
extern Bs lbl_8036B0F0;
extern const char lbl_8036B100[];
extern u8 lbl_803C8E80[];
extern u8 lbl_803CB770[];
extern u8 lbl_803CAB38[];
}
static inline u8 Rng(Inv* p, Unit* v) {
    return p->item ? fn_801107C0(p->item, v) : 0;
}
/* fn_801658E4 inlined */
static inline int Blk(Unit* u, s8 x, s8 y) {
    u8* s;
    int r;
    if (!u || u->team[8] != 2) {
        return 0;
    }
    s = fn_80158C98();
    if (s && (*(u32*)(s + 0x14) & 0x800)) {
        return 0;
    }
    if (lbl_803EC898.ter[4][x + y * 0x40] != 0) {
        r = 0;
        if (fn_800A05B0(0xD, x, y) || fn_800A05B0(0x2A, x, y) || fn_800A05B0(0xE, x, y) || fn_800A05B0(9, x, y)) {
            r = 1;
        }
        return r;
    }
    return 0;
}
static inline const u8& MaxB(const u8& a, const u8& b) {
    return a < b ? b : a;
}
/* expected damage of v attacking u with v's inventory slot `slot` */
#define SIM(d, slot) { \
    int o1, o2; \
    Bs a = lbl_8036B0F0; \
    a.u = u; a.x = u->x; a.y = u->y; a.k = fn_80127520(u); \
    Bs b = lbl_8036B0E0; \
    b.u = v; b.x = v->x; b.y = v->y; b.k = slot; \
    fn_800269E4(lbl_803C8E80, &b, &a); \
    fn_801148CC(&lbl_803EC898, fn_80165818()); \
    fn_8002742C(lbl_803C8E80, 0xf); \
    fn_801586C8(lbl_803C8E80, lbl_803C8E80 + 0x4a0, &o1, &o2, 0); \
    d = (u16)o1; }
/* tile (x, y) is on the path grid, free, and not blocked for u */
#define OPEN(mm, x, y) (lbl_803EC898.curS[(s8)(x) + (s8)(y) * 0x40] >= 0 && lbl_803EC898.b5S[(s8)(x) + (s8)(y) * 0x40] == 0 && !Blk(u, x, y))
static inline BOOL Foe(Unit* u, Unit* v) {
    return (u8)fn_8010E398(u->team, v->team) == 1;
}
extern "C" void fn_80166720(Unit* u) {
    Map* m = &lbl_803EC898;
    u8* buf;
    void* save;
    int sz;
    int ux, uy, mv;
    int x, y;
    int xx, yy, x0, y0, x1, y1;
    u8 found;
    Unit* v;
    Inv* p;
    Inv* p1;
    Inv* p2;
    int i, i1, i2;
    u16 d1, d2;

    fn_80114B44(m, 8, 0);
    sz = ((s16)(lbl_803EC898.w * m->h) + 0x1f) & ~0x1f;
    buf = (u8*)fn_80078CCC(sz, lbl_8036B100, 0);
    save = fn_80078CCC(fn_801148D8(m, 6), lbl_8036B100, 0);
    DCZeroRange(buf, sz);
    uy = u->y;
    ux = u->x;
    mv = fn_8012408C(u);
    found = 0;
    fn_801148CC(m, save);
    fn_80165F94(u, 0xc, -1);
    for (y = m->y0; y <= m->y1 - 1; y++) {
        for (x = m->x0; x <= m->x1 - 1; x++) {
            u8 t = m->ter[0][(s8)x + (s8)y * 0x40];
            if (t == 0) {
                continue;
            }
            v = UnitGet(t);
            if (!Foe(u, v)) {
                continue;
            }
            if (v->flags10C & 0x9d) {
                continue;
            }
            if (!fn_8011F1A8(v, u)) {
                continue;
            }
            i2 = -1;
            i1 = -1;
            p1 = 0;
            p2 = 0;
            p = v->inv;
            for (i = 0; i < 7; i++, p++) {
                if (!p || !p->item) {
                    break;
                }
                if (fn_8012BA20(v, p->item)) {
                    if (Rng(p, v) > 1) {
                        if (!p2 || Rng(p, v) > Rng(p2, v)
                            || (Rng(p, v) == Rng(p2, v) && fn_80110DA8(p) > fn_80110DA8(p2))) {
                            i2 = i;
                            p2 = p;
                        }
                    } else {
                        if (!p1 || fn_80110DA8(p) > fn_80110DA8(p1)) {
                            p1 = p;
                            i1 = i;
                        }
                    }
                }
            }
            if (!p1 && !p2) {
                continue;
            }
            d1 = 0;
            d2 = 0;
            if (p1 && fn_80170664(v, u, p1) == 1) {
                SIM(d1, i1);
                if (d1 == 0) {
                    i1 = -1;
                }
            }
            if (p2 && fn_80170664(v, u, p2) == 1) {
                SIM(d2, i2);
                if (d2 == 0) {
                    i2 = -1;
                }
            }
            if (d1 == 0 && d2 == 0) {
                continue;
            }
            fn_80165F94(v, 6, -1);
            if (i1 >= 0) {
                fn_80170910(v, &v->inv[i1]);
                fn_801148CC(m, save);
                x0 = ux - mv;
                if (x0 < m->x0) {
                    x0 = m->x0;
                }
                yy = uy - mv;
                if (yy < m->y0) {
                    yy = m->y0;
                }
                x1 = ux + mv;
                if (x1 > m->x1 - 1) {
                    x1 = m->x1 - 1;
                }
                y1 = uy + mv;
                if (y1 > m->y1 - 1) {
                    y1 = m->y1 - 1;
                }
                for (; yy <= y1; yy++) {
                    for (xx = x0; xx <= x1; xx++) {
                        if (mv >= ABS(ux - xx) + ABS(uy - yy) && OPEN(m, xx, yy)) {
                            if (m->g4[(s8)xx + (s8)yy * 0x40] != 0 && m->g3[(s8)xx + (s8)yy * 0x40] < 0xff) {
                                u8* q = &buf[xx + yy * lbl_803EC898.w];
                                if (d1 > 0xff) {
                                    d1 = 0xff;
                                }
                                *q = MaxB(*q, (u8)d1);
                                found = 1;
                            }
                        }
                    }
                }
            }
            if (i2 >= 0) {
                fn_80170910(v, &v->inv[i2]);
                fn_801148CC(m, save);
                x0 = ux - mv;
                if (x0 < m->x0) {
                    x0 = m->x0;
                }
                yy = uy - mv;
                if (yy < m->y0) {
                    yy = m->y0;
                }
                x1 = ux + mv;
                if (x1 > m->x1 - 1) {
                    x1 = m->x1 - 1;
                }
                y1 = uy + mv;
                if (y1 > m->y1 - 1) {
                    y1 = m->y1 - 1;
                }
                for (; yy <= y1; yy++) {
                    for (xx = x0; xx <= x1; xx++) {
                        if (mv >= ABS(ux - xx) + ABS(uy - yy) && OPEN(m, xx, yy)) {
                            if (m->g4[(s8)xx + (s8)yy * 0x40] != 0 && m->g3[(s8)xx + (s8)yy * 0x40] < 0xff) {
                                u8* q = &buf[xx + yy * lbl_803EC898.w];
                                if (d2 > 0xff) {
                                    d2 = 0xff;
                                }
                                *q = MaxB(*q, (u8)d2);
                                found = 1;
                            }
                        }
                    }
                }
            }
            if (found) {
                fn_801148CC(m, save);
                x0 = ux - mv;
                if (x0 < m->x0) {
                    x0 = m->x0;
                }
                yy = uy - mv;
                if (yy < m->y0) {
                    yy = m->y0;
                }
                x1 = ux + mv;
                if (x1 > m->x1 - 1) {
                    x1 = m->x1 - 1;
                }
                y1 = uy + mv;
                if (y1 > m->y1 - 1) {
                    y1 = m->y1 - 1;
                }
                for (; yy <= y1; yy++) {
                    for (xx = x0; xx <= x1; xx++) {
                        if (mv >= ABS(ux - xx) + ABS(uy - yy) && OPEN(m, xx, yy)) {
                            u8* q = buf + xx;
                            int o = yy * lbl_803EC898.w;
                            u8 b = q[o];
                            if (b != 0) {
                                u32 s = b + m->g3[(s8)xx + (s8)yy * 0x40];
                                if (s > 0xff) {
                                    s = 0xff;
                                }
                                m->g3[(s8)xx + (s8)yy * 0x40] = s;
                                q[o] = 0;
                            }
                        }
                    }
                }
                found = 0;
            }
        }
    }
    fn_80026CD8(lbl_803C8E80, u, -1);
    fn_8002C170(lbl_803C8E80);
    fn_801148CC(m, save);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (OPEN(&lbl_803EC898, x, y)) {
                u8* t = fn_80066130(lbl_803CB770, (s8)x, (s8)y, 0xe);
                if (t && fn_80067128(t, *(s16*)(lbl_803CAB38 + 0x12) + 1)) {
                    int s = (int)((f32)(t[6] * t[5]) / 100.0f) + m->g3[(s8)x + (s8)y * 0x40];
                    if (s > 0xffff) {
                        s = 0xffff;
                    }
                    if (s < 0) {
                        s = 0;
                    }
                    m->g3[(s8)x + (s8)y * 0x40] = s;
                }
            }
        }
    }
    fn_80078E24(save);
    fn_80078E24(buf);
}
