/* fn_80164064: round m1, exact (from equiv/fn_80164064.cpp, regs: the final test reads the unit id through
   an accessor inline `tid(u)`). AI: move toward a tile near a unit that needs help. Declarations copied from fn_8016A9BC.cpp (bodies stripped). */
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


BOOL fn_8016A280(Unit* u, Unit* t, Inv* p, Filter* f, s16* ox, s16* oy);

int fn_8016A9BC(Unit* u, int x, int y, int a, int r);
}


/* ---- fn_80164064 ---- */
static inline u8 tid(Unit* u) { return u->tid; }
struct T181 { u8 pad[8]; u8* p8; };
extern "C" {
u8 fn_80164064(Unit* u, u32 lim) {
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        return 0;
    } else {
/*P*/
        Map* m = &lbl_803EC898;
        int cb = 0x7FFFFFFF;
        int best = 0xFF;
        int bx;
        int by;
        int y;
        int x;
        Unit* v;
/*E*/
        Filt g;
        fn_80165F94(u, 6, lbl_803EC898.w * m->h);
        for (y = m->y0; y <= m->y1 - 1; y++) {
            for (x = m->x0; x <= m->x1 - 1; x++) {
                if (m->costS[(s8)x + (s8)y * 0x40] >= 0 && ((Map*)&lbl_803EC898)->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y) && lim >= fn_801676D8((s8)x, (s8)y)) {
                    if (((T181*)fn_801181E8(m, (s8)x, (s8)y))->p8[6]) {
                        if (m->ter[0][(s8)x + (s8)y * 0x40]) {
                            v = UnitGet(m->ter[0][(s8)x + (s8)y * 0x40]);
                            if (SameT(u, v, 1)) continue;
                            if (!(v->w3B4 & 0x7000000) || (v->w3B4 & 4)) {} else continue;
                        }
                    } else {
                        if (m->ter[0][(s8)x + (s8)y * 0x40] == 0) continue;
                        v = UnitGet(m->ter[0][(s8)x + (s8)y * 0x40]);
                        if (SameT(u, v, 1)) continue;
                        if (!(v->w3B4 & 4)) continue;
                    }
                    {
                        int c;
                        g.u = u;
                        g.vt = lbl_80387308;
                        c = fn_80171378((s16)x, (s16)y, &g);
                        if (c <= cb && m->curS[(s8)x + (s8)y * 0x40] < best) {
                            cb = c;
                            best = (u8)m->curS[(s8)x + (s8)y * 0x40];
                            bx = (s16)x;
                            by = (s16)y;
                        }
                    }
                }
            }
        }
        if (cb != 0x7FFFFFFF && m->ter[0][(s8)bx + (s8)by * 0x40] != tid(u)) {
            int K = 0x10000;
            fn_8016F94C(u, bx, by, 1, (u16)(K - 1), 0, 0, -1);
        }
        return lbl_804183F0.done;
    }
}
}
