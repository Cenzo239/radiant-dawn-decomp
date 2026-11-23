/* Inventory add with auto-equip, 8012A0F4 and 8012A440. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

struct Item {
    u8 pad0[0x38];
    u64 flags;    /* 0x38 */
};

extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern void fn_80111C78(Inv*, Inv*);
extern void fn_80111B34(Inv*);
extern void fn_80111C24(Inv*, int);
extern void fn_80110D38(Inv*);
extern s8 fn_80127520(Unit*);
extern void fn_80110BFC(Inv*, void*);
extern int fn_8012ADC8(Unit*, Item*);
extern int fn_800CD4DC(void);
extern u8* fn_80111850(Item*);
extern int fn_801118C0(Unit*, Item*);
extern void* lbl_804CA4EC;
extern void* lbl_804CA4FC;

static inline BOOL ItemT(Unit* u, Item* it, u64 f) {
    if (f & 4) {
        if (fn_8011B77C(u->skills, lbl_804CA4FC)) {
            return 1;
        }
        if (fn_8011B77C(u->skills, lbl_804CA4EC)) {
            return 1;
        }
        return 0;
    }
    if (u->wt == 0) {
        return 1;
    }
    if (f & 2) {
        return 0;
    }
    return !(f & 0x10);
}

#pragma push
#pragma use_lmw_stmw on

static inline BOOL ItemW1(Unit* u, Item* it, u64 f) {
    if (!(f & 1)) {
        return 0;
    }
    if (ItemT(u, it, f) == 0) {
        return 0;
    }
    return fn_8012ADC8(u, it) != 0;
}

static inline BOOL ItemW2(Unit* u, Item* it, u64 f) {
    if (!(f & 0x10)) {
        return 0;
    }
    if (ItemT(u, it, f) == 0) {
        return 0;
    }
    return fn_8012ADC8(u, it) != 0;
}

static inline BOOL ItemA40(Unit* u, Item* it, u64 f) {
    if (!(f & 0x40)) {
        return 0;
    }
    return fn_8012ADC8(u, it);
}

static inline BOOL ItemA20(Item* it, u64 f) {
    if ((f & 0x20) == 0) {
        return 0;
    }
    return (f & 0x1000000000000ULL) == 0;
}

static inline BOOL ItemCanW(Unit* u, Item* it, u64 f) {
    if (f & 0x60) {
        return 0;
    }
    if (f & 1) {
        return ItemW1(u, it, f);
    }
    if (f & 0x10) {
        return ItemW2(u, it, f);
    }
    return 0;
}

static inline BOOL ItemCanA(Unit* u, Item* it, u64 f) {
    if (f & 0x11) {
        return 0;
    }
    if (f & 0x20) {
        return ItemA20(it, f);
    }
    if (f & 0x40) {
        return ItemA40(u, it, f);
    }
    return 0;
}

static inline BOOL ItemCanF(Unit* u, Item* it, u64 f) {
    if (f & 0x11) {
        return ItemCanW(u, it, f);
    }
    if (f & 0x60) {
        return ItemCanA(u, it, f);
    }
    return 0;
}


static inline int FreeSlot(Unit* u) {
    int i;
    for (i = 0; i < 7; i++) {
        if (u->inv[i].item == 0) {
            return i;
        }
    }
    return -1;
}


BOOL fn_8012A0F4(Unit* u, Inv* src) {
    Inv* e;
    Item* it;
    int k = FreeSlot(u);
    if (k < 0) {
        return 0;
    }
    e = &u->inv[k];
    fn_80111C78(e, src);
    e->equipped = 0;
    if (e && e->item && (*(u32*)(fn_801116B8(e) + 4) & 0x11) && fn_80127520(u) < 0) {
        it = (Item*)e->item;
        if (ItemCanF(u, it, it->flags)) {
            e->equipped = 1;
        }
    }
    return 1;
}

BOOL fn_8012A440(Unit* u, void* item) {
        BOOL r;
    Inv* e;
    Item* it;
    Inv t;
    int k;
        fn_80111B34(&t);
    fn_80110BFC(&t, item);
    k = FreeSlot(u);
    if (k < 0) {
        r = 0;
    } else {
    e = &u->inv[k];
    fn_80111C78(e, &t);
    e->equipped = 0;
    if (e && e->item && (*(u32*)(fn_801116B8(e) + 4) & 0x11) && fn_80127520(u) < 0) {
        it = (Item*)e->item;
        if (ItemCanF(u, it, it->flags)) {
            e->equipped = 1;
        }
    }
    r = 1;
    }
    fn_80111C24(&t, -1);
    return r;
}
#pragma pop

}
