/* NOT MATCHING, not compiled. fn_8011E864: 71 words, all ranks: want v r31, t r30, u r29; every release form scores the same. */
/* Unit leaves the map: rescue pair release and list moves, 8011E864. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern u8* lbl_804CB814;
extern void fn_800F7410(Unit*, int);
extern void fn_8010E27C(u8*, Unit*);
extern void fn_8010E054(void*, Unit*);
extern void fn_8010E168(void*, Unit*);
extern void fn_8012EEFC(Unit*);
extern void fn_80121E3C(Unit*);
extern void fn_801221E8(Unit*, int);
extern void fn_80126EB0(Unit*, int, int);
extern void fn_8012AB70(Unit*);
extern void fn_8012AA8C(Unit*);
BOOL fn_8011E864(Unit* u);
static inline BOOL IsRanged(int k) {
    switch (k) {
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
        return 1;
    case 6:
    default:
        return 0;
    }
}
static inline BOOL TeamIs0(Unit* u) {
    switch (u->team[8]) {
    case 0:
        return 1;
    default:
        return 0;
    }
}
static inline void Drop(Unit* a, Unit* b, s8 x, s8 y) {
    a->flags &= ~(u64)2;
    b->flags &= ~(u64)4;
    a->actor = 0;
    b->actor = 0;
    fn_80126EB0(b, x, y);
    b->flags10C |= 1;
}
static inline void Rel(Unit* u) { Unit* v; Unit* t = (Unit*)u->actor;
    if (t) {
        if (u->flags & 2) {
            Drop(u, t, u->x, u->y);
            fn_8011E864(t);
        } else if (u->flags & 4) {
            v = (Unit*)t->actor;
            Drop(t, v, u->x, u->y);
            fn_8011E864(t);
        }
    }
}
static inline void Rel2(Unit* u, Unit* t) { Unit* v;
    if (t) {
        if (u->flags & 2) {
            Drop(u, t, u->x, u->y);
            fn_8011E864(t);
        } else if (u->flags & 4) {
            v = (Unit*)t->actor;
            Drop(t, v, u->x, u->y);
            fn_8011E864(t);
        }
    }
}
static inline void Rel3(Unit* u, Unit*& t, Unit*& v) { t = (Unit*)u->actor;
    if (t) {
        if (u->flags & 2) {
            Drop(u, t, u->x, u->y);
            fn_8011E864(t);
        } else if (u->flags & 4) {
            v = (Unit*)t->actor;
            Drop(t, v, u->x, u->y);
            fn_8011E864(t);
        }
    }
}
static inline void Rel4(Unit* u, Unit* t) { 
        if (u->flags & 2) {
            Drop(u, t, u->x, u->y);
            fn_8011E864(t);
        } else if (u->flags & 4) {
            Unit* v = (Unit*)t->actor;
            Drop(t, v, u->x, u->y);
            fn_8011E864(t);
        }
}
static inline void Rel5(Unit* u, Unit* t, Unit*& v) { 
        if (u->flags & 2) {
            Drop(u, t, u->x, u->y);
            fn_8011E864(t);
        } else if (u->flags & 4) {
            v = (Unit*)t->actor;
            Drop(t, v, u->x, u->y);
            fn_8011E864(t);
        }
}
BOOL fn_8011E864(Unit* u) {
    /*P*/
    Unit* v;
    Unit* t;
    int k;
/*E*/
    t = (Unit*)u->actor;
    if (t) {
        if (u->flags & 2) {
            Drop(u, t, u->x, u->y);
            fn_8011E864(t);
        } else if (u->flags & 4) {
            v = (Unit*)t->actor;
            Drop(t, v, u->x, u->y);
            fn_8011E864(t);
        }
    }
    fn_800F7410(u, 1);
    if (!(u->flags10C & 0x20000000)) {
        if (IsRanged(u->b380)) {
            fn_8012AB70(u);
            k = u->b380;
            switch (k) {
            case 0:
            case 2:
            case 3:
            case 5:
            case 7:
            case 8:
            case 9:
            case 10:
                fn_8012AA8C(u);
                u->flags &= ~(u64)0x10000000;
                break;
            case 1:
            case 4:
            case 6:
                break;
            }
            fn_8010E27C(u->team, u);
            fn_8010E054(lbl_804CB814 + k * 0xc, u);
            u->flags10C |= 0x4000;
            return 0;
        }
        if (TeamIs0(u)) {
            fn_8012AA8C(u);
            u->flags &= ~(u64)0x10000000;
            fn_8010E27C(u->team, u);
            fn_8010E054(lbl_804CB814 + 0x3c, u);
            u->flags10C |= 0x4000;
            return 0;
        }
        fn_8012EEFC(u);
    }
    fn_80121E3C(u);
    fn_8010E27C(u->team, u);
    fn_801221E8(u, -1);
    fn_8010E168(lbl_804CB814 + 0x30, u);
    return 1;
}
}
