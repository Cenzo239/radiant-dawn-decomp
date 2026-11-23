/* Can a unit be revived or counted dead, 8011F428. */
/* NOT MATCHING, not compiled. fn_8011E414 (7 words: name and table walker swapped), fn_8011E864 (69 words: want v r31, t r30, u r29), fn_8011EB4C (about 60 words of colouring). */
/* Unit death and removal, level-based stats, class change, 8011E414..80120378. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {

extern Map lbl_803EC898;
struct FlagTable {
    u8 pad0[0x10];
    u8 b10;
    u8 pad11[0x144 - 0x11];
    const char* names[0x80]; /* 0x144 */
    u32 hashes[0x80];        /* 0x344 */
    u8 bits[0x10];           /* 0x544 */
};
extern FlagTable lbl_803CAB38;
struct Side { u8 v[0xc]; };
extern u8* lbl_804CB814;
extern char lbl_80369010[];
extern void* lbl_804CA58C;
extern void* lbl_804CA598;
extern void* lbl_804CA5BC;
extern void* lbl_804CA6F8;

extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern void fn_80126D9C(Unit*, int);
extern void fn_80128E14(Unit*, int);
extern void fn_801283F8(Unit*);
extern void fn_800F7410(Unit*, int);
extern s16 fn_801237EC(Unit*);
extern u32 fn_80076D18(const char*);
extern int fn_80291188(const char*, const char*);
extern u8* fn_8006074C(FlagTable*);
extern int fn_80060754(FlagTable*);
extern void fn_8010E27C(u8*, Unit*);
extern void fn_8010E054(void*, Unit*);
extern void fn_8010E168(void*, Unit*);
extern void fn_8012EEFC(Unit*);
extern void* fn_801059B0(void);
extern void fn_801053EC(void*, Inv*);
extern void fn_80110D38(Inv*);
extern void fn_8012A850(Unit*);
extern void fn_80121E3C(Unit*);
extern void fn_801221E8(Unit*, int);
extern void fn_80126EB0(Unit*, int, int);
extern void fn_8012AB70(Unit*);
extern void fn_8012AA8C(Unit*);
extern void fn_80114888(Map*, int);
extern void fn_801151BC(Map*, Unit*);
extern void fn_8011567C(Map*, void*);
extern void fn_80115764(Map*, int, int, int);
extern s16 fn_80115CD8(Map*, int, int);
extern u8* fn_801181E8(Map*, int, int);

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

static inline BOOL InvA(Inv* e) {
    BOOL t = 1;
    if ((*(u32*)fn_801116B8(e) & 0x20000) == 0 && e->bit10 == 0) {
        t = 0;
    }
    return t;
}

static inline BOOL InvB(Inv* e) {
    BOOL t = 1;
    if ((*(u32*)fn_801116B8(e) & 0x1000000) == 0 && e->bit4 == 0) {
        t = 0;
    }
    return t;
}

#pragma pool_strings on
const char* dumS() { return "PID_SOTHE"; }

#pragma push
#pragma use_lmw_stmw on
BOOL fn_8011F428(Unit* u) {
    u8* cfg = fn_8006074C(&lbl_803CAB38);
    if (flagGet(&lbl_803CAB38, "gf_gameover")) {
        return 0;
    }
    if (IsRanged(u->b380)) {
        return 1;
    }
    if (fn_8011B77C(u->skills, lbl_804CA598)) {
        return 1;
    }
    return (((u8*)u->person)[0xe0] & (cfg[0x8e] & 0x1f)) != 0;
}
#pragma pop
}
