/* fn_80167704: functionally equal (regs level per tools/check_regs.py; registers differ from the original).  */
/* AI: build the threat grid (g3) of the army hostile to `team`: for every such unit on the map, its
 * strongest melee and strongest ranged weapon are spread over the tiles they can reach this turn,
 * keeping the larger value per tile, then added into g3 (capped at 255). Names guessed. */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
struct ItemInfo { u32 w0; u32 flags; };
extern "C" {
extern char lbl_8036B100[];
void fn_80114B44(Map*, int, int);
void* fn_80078CCC(int, const char*, int);
void DCZeroRange(void*, u32);
void fn_80078E24(void*);
int fn_8012BA20(Unit*, u8*);
u8 fn_801107C0(u8*, Unit*);
u8 fn_80110DA8(Inv*);
ItemInfo* fn_801116B8(Inv*);
int fn_80123998(Unit*);
int fn_8012386C(Unit*);
void fn_80170910(Unit*, Inv*);
s8 fn_8012408C(Unit*);
void fn_80165F94(Unit*, int, int);
}
static inline u8 Rng(Inv* p, Unit* v) { return p->item ? fn_801107C0(p->item, v) : 0; }
static inline BOOL SameP(u8* a, u8* b, int w) { return (u8)fn_8010E398(a, b) == w; }
template <class T> inline const T& Max(const T& a, const T& b) { return a < b ? b : a; }

#define SPREAD(W) \
    { \
        int pow; \
        int p8; \
        int t; \
        int vx; \
        int vy; \
        int rng; \
        int x0; \
        int yy; \
        int x1; \
        int y1; \
        int xx; \
        fn_80165F94(v, 6, -1); \
        p8 = fn_80110DA8(W); \
        if (fn_801116B8(W)->flags & 0x202) { \
            t = fn_80123998(v); \
        } else { \
            t = fn_8012386C(v); \
        } \
        pow = (u16)(p8 + t); \
        if (pow != 0) { \
            fn_80170910(v, W); \
            vx = v->x; \
            vy = v->y; \
            rng = Rng(W, v); \
            rng = fn_8012408C(v) + rng; \
            x0 = vx - rng; \
            if (x0 < m->x0) x0 = m->x0; \
            yy = vy - rng; \
            if (yy < m->y0) yy = m->y0; \
            x1 = vx + rng; \
            if (x1 > m->x1 - 1) x1 = m->x1 - 1; \
            y1 = vy + rng; \
            if (y1 > m->y1 - 1) y1 = m->y1 - 1; \
            for (; yy <= y1; yy++) { \
                for (xx = x0; xx <= x1; xx++) { \
                    if (rng >= ABS(vx - xx) + ABS(vy - yy) && m->g4[(s8)xx + (s8)yy * 0x40] != 0) { \
                        u8* q; \
                        int idx = xx + yy * lbl_803EC898.w; \
                        if ((u32)pow > 0xFF) pow = 0xFF; \
                        q = buf + idx; \
                        *q = Max(*q, (u8)pow); \
                        dirty = 1; \
                    } \
                } \
            } \
        } \
    }

extern "C" void fn_80167704(u8* team) {
/*P*/
    int i;
    int size;
    BOOL dirty;
    int y;
    int x;
    Unit* v;
    Inv* p;
    Inv* a;
    Map* m = &lbl_803EC898;
    u8* buf;
    Inv* b;
/*E*/
    fn_80114B44(m, 8, 0);
    size = ((s16)(lbl_803EC898.w * m->h) + 0x1F) & ~0x1F;
    buf = (u8*)fn_80078CCC(size, lbl_8036B100, 0);
    DCZeroRange(buf, size);
    dirty = 0;
    for (y = m->y0; y <= m->y1 - 1; y++) {
        for (x = m->x0; x <= m->x1 - 1; x++) {
            if (m->ter[0][(s8)x + (s8)y * 0x40]) {
                v = UnitGet(m->ter[0][(s8)x + (s8)y * 0x40]);
                if (SameP(v->team, team, 1) && !(v->flags10C & 0x9D)) {
                    p = v->inv;
                    a = 0;
                    b = 0;
                    for (i = 0; i < 7; i++, p++) {
                        if (!p || !p->item) break;
                        if (fn_8012BA20(v, p->item)) {
                            if (Rng(p, v) > 1) {
                                if (!b || Rng(p, v) > Rng(b, v) || (Rng(p, v) == Rng(b, v) && fn_80110DA8(p) > fn_80110DA8(b))) {
                                    b = p;
                                }
                            } else {
                                if (!a || fn_80110DA8(p) > fn_80110DA8(a)) {
                                    a = p;
                                }
                            }
                        }
                    }
                    if (a || b) {
                        if (a) SPREAD(a)
                        if (b) SPREAD(b)
                        if (dirty) {
                            int yy;
                            int xx;
                            for (yy = m->y0; yy <= m->y1 - 1; yy++) {
                                for (xx = m->x0; xx <= m->x1 - 1; xx++) {
                                    u8* q = &buf[xx + yy * lbl_803EC898.w];
                                    u8 c = *q;
                                    if (c) {
                                        u32 t = c + m->g3[(s8)xx + (s8)yy * 0x40];
                                        if (t > 0xFF) t = 0xFF;
                                        m->g3[(s8)xx + (s8)yy * 0x40] = (u8)t;
                                        *q = 0;
                                    }
                                }
                            }
                            dirty = 0;
                        }
                    }
                }
            }
        }
    }
    fn_80078E24(buf);
}
