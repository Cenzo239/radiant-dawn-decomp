/* Round 20, functionally equal (check_regs.py: sched): fn_8006758C. Self-contained. fn_80067168.cpp with exported bodies removed plus the fragment from wip/near.cpp. Changed: mx and i are initialised after the terrain byte is cleared (the original uses a separate li r0,0 for that store). Moved (harmless): slwi of y and extsb of x swapped in the index computation. */
/* Move range display for units, 80067168..800677E0. */
#include "game/rO_80065D64/trap.h"
#pragma auto_inline off

extern "C" {
extern void fn_80114888(Map*, int);
extern void fn_801151BC(Map*, Unit*);
extern void fn_8011567C(Map*, u8*);
extern s8 fn_8012408C(Unit*);
extern void fn_80115764(Map*, s8, s8, u16);
extern void fn_80114B44(Map*, int, int);
extern void fn_800676C4(Unit*);
extern void fn_8006758C(Unit*);
extern void fn_800673A0(int,int);
extern int fn_800660E8(TrapList*);
extern void fn_80115DEC(Map*, s8, s8, int, int);
extern int fn_8012BA20(Unit*, u8*);
extern u8 fn_801107A0(u8*, Unit*);
extern u8 fn_801107C0(u8*, Unit*);
extern int fn_8011B77C(void*, void*);
extern void* lbl_804CA510;
extern u8* fn_8010B204(u8);
extern void fn_80117E30(Map*, s8, s8, u8);
void fn_80067168(Unit* u);

void fn_80067230(Unit* u);


#pragma push
#pragma use_lmw_stmw on

void fn_800672B8(Unit* u);

void fn_800673A0(int a, int b);


static inline int RangeMin(Inv* it, Unit* u) {
    if (it->item != 0) {
        return fn_801107A0(it->item, u);
    }
    return 0;
}

static inline int RangeMax(Inv* it, Unit* u) {
    if (it->item != 0) {
        return fn_801107C0(it->item, u);
    }
    return 0;
}

void fn_8006746C(Unit* u);

void fn_8006758C(Unit* u);
void fn_800676C4(Unit* u);

#pragma pop

void fn_800677E0(void);

}

#pragma use_lmw_stmw on
/* ---- from build/tmp/r20small/rO/frag_fn_8006758C.cpp ---- */
extern "C" {
/* from fn_80067168.cpp: 71 of 77 words differ */
void fn_8006758C(Unit* u) {
    Map* m = &lbl_803EC898;
    Inv* it = u->inv;
    s8 mn = 100;
    s8 mx;
    int i;
    int idx = u->x + (u->y << 6);
    u8 save = m->ter[0][idx];
    m->ter[0][idx] = 0;
    mx = 0;
    i = 0;
    for (; i < 7; i++) {
        if (it == 0 || it->item == 0) {
            break;
        }
        if (fn_8012BA20(u, it->item)) {
            int a = RangeMin(it, u);
            int b = RangeMax(it, u);
            if (mn > a || b > mx) {
                if (a < mn) {
                    mn = a;
                }
                if (mx < b) {
                    mx = b;
                }
                fn_800673A0((s8)a, (s8)b);
            }
        }
        it++;
    }
    lbl_803EC898.ter[0][u->x + (u->y << 6)] = save;
}
}
