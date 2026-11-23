/* AI: best staff/item target from a tile, scored by fn_80157094 (names guessed). */
#include "game/rQ_80163178/common.h"
struct Res {
    u8 x, y;
    u16 slot;
    Unit* tgt;
    int score;
    u8 b;
};
extern "C" {
extern u8 lbl_80387338[];
void* memset(void*, int, u32);
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
int fn_8012BA20(Unit*, u8*);
void fn_8010E41C(u8*, int);
int fn_80153910(Unit*, Unit*, Inv*);
u32 fn_801107C0(u8*, Unit*);
u32 fn_801107A0(u8*, Unit*);
int fn_8017062C(int, int, int, int, u8);
void fn_801663E0(int, int, u8, u8, int);
int fn_80157094(Unit*, int, int, Res*, Filt*);
void fn_8012A088(Unit*, u16);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);

static inline u8 MaxR(Inv* it, Unit* u) {
    if (it->item) return fn_801107C0(it->item, u);
    return 0;
}
static inline u8 MinR(Inv* it, Unit* u) {
    if (it->item) return fn_801107A0(it->item, u);
    return 0;
}

#pragma auto_inline on
int fn_801645D8(Unit* u, int x, int y) {
    Res best;
    Res cur;
    u8 mask[0x10];
    Filt f;
    Inv* it;
    int i;
    memset(&best, 0, 0x10);
    best.score = 0x80000000;
    best.tgt = 0;
    fn_80114B44(&lbl_803EC898, 6, -1);
    fn_80114888(&lbl_803EC898, 6);
    lbl_803EC898.cur[(s8)x + (s8)y * 0x40] = 0;
    memset(&cur, 0, 0x10);
    for (i = 0, it = u->inv; i < 7; i++, it++) {
        if (!it || !it->item) break;
        if (!fn_8012BA20(u, it->item)) continue;
        cur.slot = i;
        fn_8010E41C(mask, 1);
        for (int id = 1; id <= 0xFE; id++) {
            Unit* t = UnitGet(id);
            if (t->person && mask[t->team[8]] && fn_80153910(u, t, it) && !(t->flags10C & 0x10000DC) && !MapOutU(&lbl_803EC898, t)) {
                if (fn_8017062C(x, y, t->x, t->y, MaxR(it, u))) {
                    u8 a = MaxR(it, u);
                    fn_801663E0(t->x, t->y, MinR(it, u), a, 7);
                    cur.tgt = t;
                    f.vt = lbl_80387338;
                    f.u = u;
                    if (fn_80157094(u, x, y, &cur, &f) && cur.score > best.score) {
                        best = cur;
                    }
                }
            }
        }
    }
    if (best.tgt) {
        if (best.slot < 7) {
            fn_8012A088(u, best.slot);
            best.slot = 0;
        }
        fn_80160610(0xF, (s8)best.x, (s8)best.y, best.tgt, best.tgt->x, best.tgt->y, (s8)best.slot, 0, 0);
        return 1;
    }
    return 0;
}
}
