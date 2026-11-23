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

void fn_80067168(Unit* u) {
    fn_80114888(&lbl_803EC898, 6);
    fn_801151BC(&lbl_803EC898, u);
    fn_8011567C(&lbl_803EC898, u->team);
    s8 y = u->y;
    s8 x = u->x;
    fn_80115764(&lbl_803EC898, x, y, (s8)fn_8012408C(u));
    fn_80114888(&lbl_803EC898, 7);
    fn_80114B44(&lbl_803EC898, 9, 0);
    fn_800676C4(u);
    fn_8006758C(u);
    fn_80114888(&lbl_803EC898, 6);
}

void fn_80067230(Unit* u) {
    fn_80114888(&lbl_803EC898, 6);
    fn_801151BC(&lbl_803EC898, u);
    fn_8011567C(&lbl_803EC898, u->team);
    s8 y = u->y;
    s8 x = u->x;
    fn_80115764(&lbl_803EC898, x, y, (s8)fn_8012408C(u));
}

#pragma push
#pragma use_lmw_stmw on
void fn_800672B8(Unit* u) {
    int i;
    for (i = 0; i < fn_800660E8(&lbl_803CB770); i++) {
        Trap* t = At(&lbl_803CB770, i);
        if (t->type == 0xC) {
            t->type = 0x20;
        }
    }
    fn_801151BC(&lbl_803EC898, u);
    fn_8011567C(&lbl_803EC898, 0);
    fn_80115764(&lbl_803EC898, u->x, u->y, 1000);
    for (i = 0; i < fn_800660E8(&lbl_803CB770); i++) {
        Trap* t = At(&lbl_803CB770, i);
        if (t->type == 0x20) {
            t->type = 0xC;
        }
    }
}

void fn_800673A0(int a, int b) {
    s8 y;
    for (y = 0; y < lbl_803EC898.h; y++) {
        s8 x;
        for (x = 0; x < lbl_803EC898.w; x++) {
            if (lbl_803EC898.cost[x + (y << 6)] >= 0 && lbl_803EC898.g5[x + (y << 6)] == 0 &&
                lbl_803EC898.ter[0][x + (y << 6)] == 0) {
                fn_80115DEC(&lbl_803EC898, x, y, (u8)a, (u8)b);
            }
        }
    }
}

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

void fn_800676C4(Unit* u) {
    if (fn_8011B77C(u->skills, lbl_804CA510)) {
        int i;
        for (i = 0; i < fn_800660E8(&lbl_803CB770); i++) {
            Trap* t = At(&lbl_803CB770, i);
            if (t->type == 7 && (s16)lbl_803EC898.cost[t->x + (t->y << 6)] >= 0 && t->d[1] != 0) {
                s8 y;
                s8 x;
                u8* item;
                u8 mx;
                u8 mn;
                item = fn_8010B204(t->d[0]);
                y = t->y;
                x = t->x;
                mx = fn_801107C0(item, u);
                mn = fn_801107A0(item, u);
                fn_80115DEC(&lbl_803EC898, x, y, mn, mx);
                fn_80117E30(&lbl_803EC898, t->x, t->y, t->ext);
            }
        }
    }
}
#pragma pop

void fn_800677E0(void) {}
}
