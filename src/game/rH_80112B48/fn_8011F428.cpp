/* Unit: map state queries, level-up and accuracy formulas, 8011F428..80120928. */
#include "game/rH_80112B48/map.h"
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern u8* fn_8006074C(void*);
extern u8* fn_80060728(void*);
extern u32 fn_80076D18(const char*);
extern int fn_80291188(const char*, const char*);
extern void* lbl_804CA598;
extern void* lbl_804CA4E8;
extern void* lbl_804CA594;
extern void* lbl_804CA4F8;
extern void* lbl_804CA4FC;
extern void* lbl_804CA6BC;
extern void* lbl_804CA6C8;
extern char lbl_80369010[];
extern u8 lbl_804CB830;
extern Map lbl_803EC898;
extern void fn_8012AA8C(Unit*, u32);
extern void fn_8010E27C(u8*, Unit*);
extern void fn_8010E054(u8*, Unit*);
extern void fn_8010E168(u8*, Unit*);
extern u8* lbl_804CB814;
extern u8 fn_80126B0C(Unit*);
extern s8 fn_80124144(Unit*);
extern s16 fn_80123BF0(Unit*);
extern s16 fn_80123998(Unit*);
extern s16 fn_80123EF0(Unit*);
extern s16 fn_80123AC4(Unit*);
extern u8 fn_80126F34(Unit*, Unit*);

struct FlagTable {
    u8 pad0[0x144];
    const char* names[0x80]; /* 0x144 */
    u32 hashes[0x80];        /* 0x344 */
    u8 bits[0x10];           /* 0x544 */
};

extern FlagTable lbl_803CAB38;

static inline int flagFind(FlagTable* t, const char* name) {
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline bool flagTestBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return t->bits[i >> 3] & (1 << (i & 7));
}

static inline bool flagGetBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return flagTestBit(t, i);
}

static inline bool flagGet(FlagTable* t, const char* name) {
    if (name[0] == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}

#pragma push
#pragma use_lmw_stmw on
#pragma pop

BOOL fn_8011F5B4(Unit* u) {
    if (u->person) {
        if (u->flags10C & 0x18) {
            return 0;
        }
        switch (u->team[8]) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 1;
        }
    }
    return 0;
}

static inline BOOL PhaseOk(void) {
    return lbl_804CB830 == 1 || lbl_804CB830 == 2;
}

static inline BOOL OnSpecial(Unit* u) {
    if (!PhaseOk()) {
        return 0;
    }
    if (u->team[8] != 1) {
        return 0;
    }
    return !lbl_803EC898.ter[2][u->x + (u->y << 6)];
}

BOOL fn_8011F600(Unit* u) {
    return !OnSpecial(u);
}

BOOL fn_8011F680(Unit* u) {
    return OnSpecial(u);
}

BOOL fn_8011F6F8(Unit* u) {
    return (u->flags & 0x80) != 0;
}

void fn_8011FDD8(Unit* u, u32 k) {
    switch (k) {
    case 0:
    case 2:
    case 3:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
        fn_8012AA8C(u, k);
        u->flags &= ~(u64)0x10000000;
        break;
    case 1:
    case 4:
    case 6:
        break;
    }
    fn_8010E27C(u->team, u);
    fn_8010E054(lbl_804CB814 + k * 0xc, u);
}

void fn_8011FE74(Unit* u, u32 k) {
    switch (k) {
    case 0:
    case 2:
    case 3:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
        fn_8012AA8C(u, k);
        u->flags &= ~(u64)0x10000000;
        break;
    case 1:
    case 4:
    case 6:
        break;
    }
    fn_8010E27C(u->team, u);
    fn_8010E168(lbl_804CB814 + k * 0xc, u);
}

void fn_8011FF10(Unit* u, int v) {
    if (v) {
        u->fd = v;
    }
}

void fn_8011FF20(Unit* u, u8 v) {
    u->u117 = v;
}

BOOL fn_8011FF28(Unit* u, int k) {
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        return 0;
    }
    if (fn_8011B77C(u->skills, lbl_804CA594)) {
        return 0;
    }
    if (u->job->p14 == 0) {
        return 0;
    }
    if (k && u->gauge < 10) {
        return 0;
    }
    return 1;
}

static inline BOOL CanPromote(Unit* u) {
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        return 0;
    }
    if (fn_8011B77C(u->skills, lbl_804CA594)) {
        return 0;
    }
    return u->job->p14 != 0;
}

extern int fn_80120378(Unit*);

u8 fn_801204E8(Unit* u) {
    int v = fn_80120378(u);
    if (v > 100) {
        v = 100;
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

u8 fn_801207B4(Unit* u, int v) {
    if (v == 0) {
        return 0;
    }
    if (fn_8011B77C(u->skills, lbl_804CA6BC)) {
        v *= 2;
    }
    if (fn_8011B77C(u->skills, lbl_804CA6C8)) {
        v /= 2;
    }
    if (v > 100) {
        v = 100;
    }
    if (v < 1) {
        v = 1;
    }
    return v;
}

static inline BOOL Immune(Unit* u) {
    if (fn_8011B77C(u->skills, lbl_804CA4F8)) {
        return 1;
    }
    return fn_8011B77C(u->skills, lbl_804CA4FC);
}

u8 fn_8012084C(Unit* a, Unit* b) {
    if (Immune(b)) {
        return 0;
    }
    {
        int s;
        int x = fn_80124144(a);
        int d = (x - fn_80124144(b)) * 3;
        int r;
        s = fn_80123BF0(a);
        r = (s - fn_80123BF0(b)) * 2; r = r + d + 0x14;
        if (r > 100) {
            r = 100;
        }
        if (r < 0) {
            r = 0;
        }
        return r;
    }
}

u8 fn_80120928(Unit* a, Unit* b) {
    int s = fn_80123998(a);
    int d = (s - fn_80123EF0(b)) * 5;
    int k = fn_80123AC4(a);
    int r = k + d + 0x1e - fn_80126F34(a, b) * 2;
    if (r > 100) {
        r = 100;
    }
    if (r < 0) {
        r = 0;
    }
    return r;
}

}
