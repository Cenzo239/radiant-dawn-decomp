/* Unit inventory management, 8012A7B8..8012AD38. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern int fn_80110C60(Inv*);
extern void fn_80110D38(Inv*);
extern void fn_80111B34(Inv*);
extern void fn_80111C24(Inv*, int);
extern void fn_80111C78(Inv*, Inv*);
extern u8* fn_801116B8(Inv*);
extern int fn_801116F4(Inv*);
extern void fn_80129CB8(Unit*, int);
extern void* lbl_804CA4EC;
extern void* lbl_804CA4FC;
void fn_8012A850(Unit* u);

BOOL fn_8012A7B8(Unit* u, int i) {
    if (fn_80110C60(&u->inv[i])) {
        fn_8012A850(u);
        return 1;
    }
    return 0;
}

void fn_8012A80C(Unit* u, s8 i) {
    fn_80110D38(&u->inv[i]);
    fn_8012A850(u);
}

void fn_8012AA8C(Unit* u) {
    Inv* it = u->inv;
    int i;
    for (i = 0; i < 7; i++) {
        if (it && it->item) {
            it->bit40 = 0;
        }
        it++;
    }
}

void fn_8012AB70(Unit* u) {
    Inv* it = u->inv;
    int i;
    for (i = 0; i < 7; i++) {
        if (it && it->item && it->bits2) {
            fn_80110D38(it);
        }
        it++;
    }
    fn_8012A850(u);
    fn_80129CB8(u, -1);
}

BOOL fn_8012ABFC(Unit* u) {
    u32 i;
    for (i = 0; i < 7; i++) {
        if (u->inv[i].item == 0) {
            break;
        }
    }
    if (i == 7) {
        return 1;
    }
    return 0;
}

static inline u32 InvA(Inv* it) {
    return *(u32*)fn_801116B8(it) & 0x20000;
}

static inline u32 InvB(Inv* it) {
    return it->bit10;
}

#pragma push
#pragma use_lmw_stmw on
s8 fn_8012AC88(Unit* u) {
    Inv* it = u->inv;
    int idx = -1;
    int best = 1000000;
    int i;
    for (i = 0; i < 7; i++) {
        if (it && it->item) {
            BOOL t = InvA(it) || InvB(it);
            if (!t) {
                if (fn_801116F4(it) < best) {
                    idx = i;
                    best = fn_801116F4(it);
                }
            }
        }
        it++;
    }
    return idx;
}
#pragma pop

BOOL fn_8012AD38(Unit* u, u8* w) {
    u32 f = *(u32*)(w + 0x3c);
    if (f & 4) {
        if (fn_8011B77C(u->skills, lbl_804CA4FC)) {
            return 1;
        }
        return fn_8011B77C(u->skills, lbl_804CA4EC);
    }
    if (u->wt == 0) {
        return 1;
    }
    if (f & 2) {
        return 0;
    }
    return !(f & 0x10);
}

}
