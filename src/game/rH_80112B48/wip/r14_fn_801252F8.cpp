/* NOT MATCHING, not compiled. fn_801252F8: 14-18 words. EQUIP_SUM moves the stat temps to r27 at all three sites but breaks the first walker; EQUIP_SUM2 keeps the walker with temps r28. */
/* Equipment-and-aura stat bonuses, 80124CF0..801264E8. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern f32 fn_801070A4(Unit*);
extern u32 fn_80076D18(const char*);
extern int fn_80291188(const char*, const char*);
extern char lbl_80385DD0[];
extern char lbl_80385DBC[];
extern void* lbl_804CA4EC;
extern void* lbl_804CA4F4;
extern void* lbl_804CA65C;
extern void* lbl_804CA660;
extern void* lbl_804CA664;
extern void* lbl_804CA6D8;

struct Bonus {
    s8 v[7];
    Bonus() {}
    Bonus(const Bonus& o);
};
extern Bonus fn_80107864(u8*, f32);
extern int fn_80124A4C(Unit*, void*, void*);
extern s8 fn_8010F0C8(void);
extern s8 fn_8010F160(void);
extern s8 fn_8010F1F8(void);
extern s8 fn_8010F290(void);
extern s8 fn_8010F3C0(void);
extern s8 fn_8010F328(void);
extern s8 fn_8010F458(void);

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
    FlagTable* p;
    for (i = 0, p = t; i < 0x80; i++, p = (FlagTable*)((u8*)p + 4)) {
        if (h == p->hashes[0] && fn_80291188(p->names[0], name) == 0) {
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

static inline int flagFind2(FlagTable* t, const char* name);
static inline bool flagHasA(FlagTable* t, const char* name) {
    return flagFind(t, name) >= 0;
}
static inline int flagFind2(FlagTable* t, const char* name) {
    u32 h = fn_80076D18(name);
    FlagTable* p = t;
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == p->hashes[0] && fn_80291188(p->names[0], name) == 0) {
            return i;
        }
        p = (FlagTable*)((u8*)p + 4);
    }
    return -1;
}
static inline bool flagHas(FlagTable* t, const char* name) {
    return flagFind2(t, name) >= 0;
}

static inline BOOL AuraOn(Unit* u) {
    if (u == 0) {
        return 0;
    }
    switch (u->team[8]) {
    case 1:
    case 4:
    default:
        return 0;
    case 0:
    case 2:
    case 3:
    case 5:
        break;
    }
    return flagHasA(&lbl_803CAB38, lbl_80385DD0) && flagGetBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, lbl_80385DBC));
}

static inline BOOL AuraOn2(Unit* u) {
    if (u == 0) {
        return 0;
    }
    switch (u->team[8]) {
    case 1:
    case 4:
    default:
        return 0;
    case 0:
    case 2:
    case 3:
    case 5:
        break;
    }
    return flagHas(&lbl_803CAB38, lbl_80385DD0) && flagGetBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, lbl_80385DBC));
}

static inline int EquipIdx(Unit* u) {
    Inv* it = u->inv;
    int i;
    for (i = 0; i < 7; i++) {
        if (it->item == 0) {
            break;
        }
        if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) {
            return (s8)i;
        }
        it++;
    }
    return -1;
}

static inline int EquipIdx2(Unit* u) {
    int i;
    for (i = 0; i < 7; i++) {
        Inv* it = &u->inv[i];
        if (it->item == 0) {
            break;
        }
        if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) {
            return (s8)i;
        }
    }
    return -1;
}

#define EQUIP_SUM(off)                                                  \
    {                                                                   \
        int idx = EquipIdx(u);                                          \
        if (idx < 0) {                                                  \
            e = 0;                                                      \
        } else {                                                        \
            e = &u->inv[idx];                                           \
        }                                                               \
    }                                                                   \
    if (e) {                                                            \
        r = (s8)e->item[off];                                           \
    }                                                                   \
    for (i = 0; i < 7; i++) {                                           \
        u32 t;                                                          \
        if (base == 0 || base->item == 0) {                             \
            break;                                                      \
        }                                                               \
        t = base->item ? base->item[0x12] : 0x13;                       \
        if (t == 0xe) {                                                 \
            if (base->equipped || (*(u32*)fn_801116B8(base) & 0x2000000)) { \
                r += (s8)base->item[off];                               \
            }                                                           \
        }                                                               \
        base++;                                                         \
    }

#define EQUIP_SUM2(off)                                                  \
    {                                                                   \
        int idx = EquipIdx2(u);                                          \
        if (idx < 0) {                                                  \
            e = 0;                                                      \
        } else {                                                        \
            e = &u->inv[idx];                                           \
        }                                                               \
    }                                                                   \
    if (e) {                                                            \
        r = (s8)e->item[off];                                           \
    }                                                                   \
    for (i = 0; i < 7; i++) {                                           \
        u32 t;                                                          \
        if (base == 0 || base->item == 0) {                             \
            break;                                                      \
        }                                                               \
        t = base->item ? base->item[0x12] : 0x13;                       \
        if (t == 0xe) {                                                 \
            if (base->equipped || (*(u32*)fn_801116B8(base) & 0x2000000)) { \
                r += (s8)base->item[off];                               \
            }                                                           \
        }                                                               \
        base++;                                                         \
    }

struct UBits {
    u16 a : 2;
    u16 b : 2;
    u16 pad : 2;
    u16 d : 2;
    u16 c : 3;
    u16 pad2 : 5;
};
#define UB(u) ((UBits*)&(u)->skills110[2])

static inline int StatJ(Unit* u, int i) {
    return u->stat[i] + u->job->base[i];
}

static inline s16 StatBaseF(Unit* u, int i) {
    int a = StatJ(u, i);
    int v = u->person->base[i] + a;
    if (v > u->job->max[i]) {
        v = u->job->max[i];
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

static inline s16 StatDbl(Unit* u, int i) {
    int v = StatBaseF(u, i);
    if (fn_8011B77C(u->skills, lbl_804CA4EC)) {
        if (fn_8011B77C(u->skills, lbl_804CA4F4) || (u->flags10C & 0x8000000)) {
            v *= 1.5f;
        } else {
            v *= 2;
        }
    }
    if (v > u->job->max[i]) {
        v = u->job->max[i];
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}


#define BODY(v) \
    v = StatBaseF(u, 3); \
    if (fn_8011B77C(u->skills, lbl_804CA4EC)) { \
        if (fn_8011B77C(u->skills, lbl_804CA4F4) || (u->flags10C & 0x8000000)) { \
            v *= 1.5f; \
        } else { \
            v *= 2; \
        } \
    } \
    if (v > u->job->max[3]) { \
        v = u->job->max[3]; \
    } \
    if (v < 0) { \
        v = 0; \
    }
static inline s16 SD2(Unit* u) { int v; BODY(v) return v; }
static inline s16 SD3(Unit* u) { s16 x; int v; BODY(v) x = v; return x; }
static inline int SD4(Unit* u) { int v; BODY(v) return (s16)v; }
static inline s16 W1(Unit* u) { return StatDbl(u, 3); }
static inline s16 W2(Unit* u) { s16 x = StatDbl(u, 3); return x; }
static inline s16 W3(Unit* u) { return W1(u); }
static inline int W4(Unit* u) { return StatDbl(u, 3); }
static inline int W5(Unit* u) { int x = StatDbl(u, 3); return x; }
static inline s16 W6(Unit* u, int i) { return StatDbl(u, i); }
static inline s16 W7(Unit* u) { return SD2(u); }
s8 fn_801252F8(Unit* u) {
    /*P*/
    Inv* base;
    int r;
    Inv* e;
    int i;
    
    /*E*/
    base = u->inv;
    r = 0;
    EQUIP_SUM(0x25)
    if (u->flags108 & 0x80) {
        r += StatDbl(u, 3) / 2;
    }
    r += fn_80124A4C(u, lbl_804CA65C, 0) * 5;
    if (AuraOn2(u)) {
        r += fn_8010F1F8();
    }
    if (UB(u)->a) {
        r -= StatDbl(u, 3) / 2;
    }
    if ((u->flags10C & 2) && !fn_8011B77C(u->skills, lbl_804CA6D8)) {
        r -= (r + StatDbl(u, 3)) / 2;
    }
    if (r > 0x7f) {
        r = 0x7f;
    }
    if (r < -0x80) {
        r = -0x80;
    }
    return r;
}
}
