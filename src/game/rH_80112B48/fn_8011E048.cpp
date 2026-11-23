/* Unit: rescue pairing, damage comparisons, 8011E048..8011F0E0. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern Unit* fn_80127B68(Unit*);
extern void fn_80126EB0(Unit*, int, int);
extern s16 fn_801237EC(Unit*);
extern void fn_80126D9C(Unit*, int);
extern s8 fn_80124144(Unit*);
extern s8 fn_8012401C(Unit*);
extern int fn_801192A8(void*);
extern int fn_801093B0(void*);
extern s16 fn_80123BF0(Unit*);
extern s16 fn_8012386C(Unit*);
extern int fn_80110EB0(Inv*);
extern u8* fn_801116B8(Inv*);
extern int fn_80129A8C(Unit*);
extern void* lbl_804CA5B8;
extern void* lbl_804CA588;
extern void* lbl_804CA63C;
extern void* lbl_804CA5BC;
extern void* lbl_804CA6F8;

struct UnitInit {
    u16 v0;
    u16 flags;
    u8 pad4[8];
    u8 vC;
    u8 padD[0x67 - 0xD];
    u8 v67;
};

void fn_8011E048(Unit* u, UnitInit* d) {
    if (d->flags & 4) {
        Unit* o = fn_80127B68(u);
        if (o == 0 || o == u) {
            u->flags10C |= 0x100;
        }
    }
    if (d->vC == 1 && (d->flags & 0x2000)) {
        u->flags10C |= 0x10000000;
    }
    if (d->vC == 0) {
        if (d->flags & 0x800) {
            u->flags10C |= 0x10000;
        }
        if (d->flags & 0x1000) {
            u->flags10C |= 0x20000;
        }
    }
    if (d->v67) {
        u->fd = d->v67;
    }
    u->h37E = d->v0;
}

void fn_8011E294(Unit* a, Unit* b) {
    fn_80126EB0(b, a->x, (s8)*(u8*)&a->y);
    a->flags10C |= 2;
    b->flags10C |= 4;
    a->actor = (u8*)b;
    b->actor = (u8*)a;
}

void fn_8011E300(Unit* u, s8 x, s8 y, int k) {
    Unit* b;
    u->flags &= ~(u64)2;
    b = (Unit*)u->actor;
    b->flags &= ~(u64)4;
    u->actor = 0;
    b->actor = 0;
    fn_80126EB0(b, x, y);
    if (k) {
        b->flags10C |= 1;
    }
}

BOOL fn_8011E3A0(Unit* u, int d) {
    int hp = u->hp;
    if (hp == fn_801237EC(u)) {
        return 0;
    }
    fn_80126D9C(u, d + u->hp);
    return 1;
}

BOOL fn_8011ED4C(Unit* a, Unit* b) {
    if (fn_8011B77C(b->skills, lbl_804CA5B8)) {
        return 0;
    }
    {
        int x = fn_80124144(b);
        int y = fn_80124144(a);
        return x <= y;
    }
}

BOOL fn_8011EDC4(Unit* a, Unit* b) {
    if (fn_801192A8(b->job)) {
        return 0;
    }
    {
        int x = fn_80124144(b);
        int y = fn_80124144(a);
        return x <= y - 2;
    }
}

BOOL fn_8011EE3C(Unit* a, Unit* b) {
    if (fn_8011B77C(b->skills, lbl_804CA588)) {
        return 0;
    }
    if (fn_8011B77C(b->skills, lbl_804CA63C)) {
        return 0;
    }
    {
        int x = fn_80124144(b);
        int y = fn_8012401C(a);
        return x <= y + 2;
    }
}

void fn_8011EED4(Unit* a, Unit* b, int k, u8* ox, u8* oy) {
    s8 dx = (u8)b->x - (u8)a->x;
    s8 dy = (u8)b->y - (u8)a->y;
    int t = k * dx;
    *ox = t + b->x;
    t = dy * k;
    *oy = t + b->y;
}

BOOL fn_8011EF14(Unit* a, Unit* b) {
    if (fn_801093B0(a->skills110)) {
        return 0;
    }
    if (b && fn_801093B0(b->skills110)) {
        return 0;
    }
    return 1;
}

BOOL fn_8011EF78(Unit* u) {
    if (fn_8011B77C(u->skills, lbl_804CA5BC)) {
        return 1;
    }
    return fn_8011B77C(u->skills, lbl_804CA6F8);
}

static inline u32 ItemA(Inv* it) {
    return *(u32*)fn_801116B8(it) & 0x1000000;
}

static inline u32 ItemB(Inv* it) {
    return it->bit4;
}

static inline int CanUse(Unit* u, Inv* it) {
    if (it->equipped) {
        return 2;
    }
    {
        int s = fn_8012386C(u);
        if ((u8)fn_80110EB0(it) >= s) {
            return 1;
        }
    }
    {
        BOOL t = ItemA(it) || ItemB(it);
        if (t) {
            return 3;
        }
    }
    return (fn_80129A8C(u) >> 31) & 4;
}

int fn_8011F024(Unit* u, Inv* it) {
    return CanUse(u, it);
}

BOOL fn_8011F0E0(Unit* u, Inv* it) {
    return (u8)CanUse(u, it) == 0;
}

}
