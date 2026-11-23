/* Round 23 (r23b), exact: fn_8006746C. From equiv/fn_8006746C.cpp; only change: fn_80115DEC declared with its
 * CATALOG prototype (Map*, s8, s8, u8, u16) instead of (Map*, s8, s8, int, int). */
/* Round 18, functionally equal (check_regs.py: renamed/regs): fn_8006746C. Self-contained: fn_80067168.cpp with its exported fn_ bodies removed (originals the function inlines kept as static inline *_inl copies) plus the function. From wip/near.cpp. */
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
extern void fn_80115DEC(Map*, s8, s8, u8, u16);
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
extern "C" {
/* from fn_80067168.cpp: 11 of 72 words differ */
void fn_8006746C(Unit* u) {
    int a;
    /*PERM*/
    Inv* it;
    s8 mn;
    s8 mx;
    int i;
    /*ENDPERM*/
    fn_80114B44(&lbl_803EC898, 6, -1);
    fn_80114B44(&lbl_803EC898, 9, 0);
    fn_80114888(&lbl_803EC898, 7);
    it = u->inv;
    mn = 100;
    mx = 0;
    for (i = 0; i < 7; i++) {
        if (it == 0 || it->item == 0) {
            break;
        }
        if (fn_8012BA20(u, it->item)) {
            int b;
            a = RangeMin(it, u);
            b = RangeMax(it, u);
            if (mn > a || b > mx) {
                if (a < mn) {
                    mn = a;
                }
                if (mx < b) {
                    mx = b;
                }
                fn_80115DEC(&lbl_803EC898, u->x, u->y, a, b);
            }
        }
        it++;
    }
}


}
