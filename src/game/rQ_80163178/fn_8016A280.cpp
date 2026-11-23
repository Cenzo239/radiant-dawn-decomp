/* fn_8016A280: EXACT (round 23a, from equiv/fn_8016A280.cpp; the Tid(u) accessor fixes the cmplw operand order). AI: best tile from which to use an item on t. Declarations copied from fn_8016A9BC.cpp (bodies stripped). */
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


/* ---- fn_8016A280 ---- */
extern "C++" { static inline u8 Tid(Unit* u) { return u->tid; } }

#define GM ((Map*)&lbl_803EC898)
extern "C" {
BOOL fn_8016A280(Unit* u, Unit* t, Inv* p, Filter* f, s16* ox, s16* oy) {
/*P*/
    Map* m = &lbl_803EC898;
    int best;
    int s;
    int y;
    int x;
/*E*/
    {
        u8 a = p->item ? fn_80110880(p->item, u) : 0;
        u8 b = p->item ? fn_801107B8(p->item, u) : 0;
        fn_801663E0(t->x, t->y, b, a, 7);
    }
    best = 0x80000000;
    for (y = GM->y0; y <= GM->y1 - 1; y++) {
        for (x = GM->x0; x <= GM->x1 - 1; x++) {
            if (GM->costS[(s8)x + (s8)y * 0x40] >= 0 && GM->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y) && m->g4[(s8)x + (s8)y * 0x40] != 0 &&
                (m->ter[0][(s8)x + (s8)y * 0x40] == 0 || m->ter[0][(s8)x + (s8)y * 0x40] == Tid(u))) {
                if (f->at((int)t, (s16)x, (s16)y)) {
                    int d = fn_801676D8((s8)x, (s8)y);
                    if (fn_8016D11C(u) >= d) {
                        s = fn_8015814C(u, x, y, 0);
                        s += fn_80158208(u, x, y, 0);
                        s -= (fn_801676D8((s8)x, (s8)y) >> 4);
                        s -= m->cost2S[(s8)x + (s8)y * 0x40];
                        if (best < s) {
                            *ox = x;
                            best = s;
                            *oy = y;
                        }
                    }
                }
            }
        }
    }
    return best != 0x80000000;
}
}
