/* Equip checks, 80129CB8..8012B104. Item flags at +0x38 are a u64. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

struct Item {
    u8 pad0[0x12];
    u8 type;      /* 0x12 */
    u8 pad13[5];
    s16 rank;     /* 0x18 */
    u8 pad1A[0x38 - 0x1A];
    u64 flags;    /* 0x38 */
};

extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern s16 fn_8012C0A8(Unit*, int, int);
extern void* fn_8010B200(const char*);
extern Inv* fn_80129B20(Unit*, int);
extern char lbl_80369210[];
extern void* lbl_804CA4D8;
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;
extern void* lbl_804CA4FC;
extern void* lbl_804CA510;
extern void* lbl_804CA53C;
extern void* lbl_804CA554;
extern void* lbl_804CA558;
extern void* lbl_804CA55C;
extern void* lbl_804CA560;
extern void* lbl_804CA564;
extern void* lbl_804CA568;
extern void* lbl_804CA56C;
extern void* lbl_804CA570;
extern void* lbl_804CA574;
extern void* lbl_804CA578;

int fn_8012ADC8(Unit* u, Item* it);

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

static inline BOOL ItemA(Unit* u, Item* it) {
    u32 f = it->flags;
    if (f & 0x11) {
        if (fn_8012ADC8(u, it)) {
            return 1;
        }
        return 0;
    }
    if (f & 0x60) {
        return fn_8012ADC8(u, it);
    }
    return 0;
}

static inline BOOL ItemB(Unit* u, Item* it) {
    u64 f = it->flags;
    if (!(f & 1)) {
        return 0;
    }
    if (ItemT(u, it, f) == 0) {
        return 0;
    }
    return fn_8012ADC8(u, it) != 0;
}

Inv* fn_80129CB8(Unit* u, int idx) {
        Inv* it;
    Inv* base;
    Inv* found;
/*E*/
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        return u->inv;
    }
    base = u->inv;
    {
        it = base;
        for (int i = 0; i < 7; i++) {
            if (it->item == 0) {
                break;
            }
            if (*(u32*)(fn_801116B8(it) + 4) & 0x11) {
                it->equipped = 0;
            }
            it++;
        }
    }
    {
    if (idx < 0) {
        found = 0;
        for (int i = 0; i < 7; i++) {
            if (base == 0 || base->item == 0) {
                break;
            }
            if (ItemA(u, (Item*)base->item)) {
                if (found == 0 && (*(u32*)(fn_801116B8(base) + 4) & 0x10)) {
                    found = base;
                } else if (ItemB(u, (Item*)base->item)) {
                    found = base;
                    goto equip;
                }
            }
            base++;
        }
        if (found == 0) {
            return 0;
        }
    } else {
        found = &u->inv[idx];
        if (!ItemA(u, (Item*)found->item)) {
            return 0;
        }
    }
equip:
    found->equipped = 1;
    return fn_80129B20(u, -1);
    }
}

static inline BOOL ItemC(Unit* u, Item* it) {
    if (it->flags & 0x40) {
        return fn_8012ADC8(u, it);
    }
    return 0;
}

Inv* fn_80129F40(Unit* u, int idx) {
        Inv* it;
    Inv* e;
    Inv* base = u->inv;
/*E*/
    {
        it = base;
        for (int i = 0; i < 7; i++) {
            if (it == 0 || it->item == 0) {
                break;
            }
            if (*(u32*)(fn_801116B8(it) + 4) & 0x60) {
                it->equipped = 0;
            }
            it++;
        }
    }
    if (idx >= 0) {
        e = &u->inv[idx];
        if (ItemC(u, (Item*)e->item)) {
            e->equipped = 1;
            return e;
        }
    } else {
        for (int i = 0; i < 7; i++) {
            if (base == 0 || base->item == 0) {
                break;
            }
            if ((*(u32*)(fn_801116B8(base) + 4) & 0x60) && ItemC(u, (Item*)base->item)) {
                base->equipped = 1;
                return base;
            }
            base++;
        }
    }
    return 0;
}
#pragma pop

#define NEED(mask, sk)                                                  \
    if ((it->flags & (mask)) && !fn_8011B77C(u->skills, sk)) {          \
        return 0;                                                       \
    }

int fn_8012ADC8(Unit* u, Item* it) {
    if (it->flags & 0x1FFFE00000ULL) {
        NEED(0x800000, lbl_804CA4D8)
        if ((it->flags & 0x1000000) && !(*(u16*)((u8*)u->job + 0xEE) & 0x20)) {
            return 0;
        }
        NEED(0x2000000, lbl_804CA4E8)
        NEED(0x4000000, lbl_804CA510)
        NEED(0x8000000, lbl_804CA554)
        NEED(0x10000000, lbl_804CA558)
        NEED(0x20000000, lbl_804CA55C)
        NEED(0x40000000, lbl_804CA560)
        NEED(0x80000000ULL, lbl_804CA564)
        NEED(0x100000000ULL, lbl_804CA568)
        NEED(0x200000000ULL, lbl_804CA56C)
        NEED(0x400000000ULL, lbl_804CA570)
        NEED(0x800000000ULL, lbl_804CA574)
        if ((it->flags & 0x1000000000ULL) && fn_8011B77C(u->skills, lbl_804CA578)) {
            return 0;
        }
        NEED(0x200000, lbl_804CA4FC)
        if (it->flags & 0x400000) {
            Job* j = u->job;
            if (j != fn_8010B200(lbl_80369210)) {
                return 0;
            }
        }
    }
    switch (it->type) {
    case 0xd:
        return fn_8011B77C(u->skills, lbl_804CA53C);
    case 0xf:
        return 1;
    case 0xe:
    case 0x10:
        return 0;
    default: {
s16 v = fn_8012C0A8(u, it->type, u->s2D4[it->type]); return v >= (s16)(it->rank + (it->rank == 0));
    }
    }
}

}
