/* NOT MATCHING, not compiled. fn_801241F4: 6 words reachable (use Equip at site 1, Equip4 at site 2, Equip at site 3): the third counter and item want r28, get r27. */
/* Movement and HP bonus, adjacent-ally count, 801241F4..80124A4C. */
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
extern void* lbl_804CA65C;
extern void* lbl_804CA660;
extern void* lbl_804CA664;

struct Bonus {
    s8 v[7];
    Bonus() {}
    Bonus(const Bonus& o);
};
extern Bonus fn_80107864(u8*, f32);
extern int fn_80124A4C(Unit*, void*, void*);
extern s8 fn_8010F030(void);
extern void* fn_8010B228(const char*);
extern char lbl_80369088[];
extern void* lbl_804CA634;
extern int fn_80117A0C(void*, int, int);
extern void* lbl_803EC898;
extern s8 fn_8010F0C8(void);
extern s8 fn_8010F160(void);
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

struct UB2 { u16 pad : 11; u16 f : 3; u16 pad2 : 2; };
#define UBF(u) (((UB2*)&(u)->skills110[2])->f)

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

#define EQUIP_SUM22                                                     \
    {                                                                   \
        int idx = EquipIdx(u);                                          \
        if (idx < 0) {                                                  \
            e = 0;                                                      \
        } else {                                                        \
            e = &u->inv[idx];                                           \
        }                                                               \
    }                                                                   \
    if (e) {                                                            \
        r = *(s8*)(e->item + 0x22);                                     \
    }                                                                   \
    for (i = 0; i < 7; i++) {                                           \
        u32 t;                                                          \
        if (base == 0 || base->item == 0) {                             \
            break;                                                      \
        }                                                               \
        t = base->item ? base->item[0x12] : 0x13;                       \
        if (t == 0xe) {                                                 \
            if (base->equipped || (*(u32*)fn_801116B8(base) & 0x2000000)) { \
                r += (s8)base->item[0x22];                              \
            }                                                           \
        }                                                               \
        base++;                                                         \
    }

#define BONUS_A(name, off, sk, idx, fn)                                 \
s8 name(Unit* u) {                                                      \
    Inv* base = u->inv;                                                 \
    int r = 0;                                                          \
    Inv* e;                                                             \
    int i;                                                              \
    EQUIP_SUM(off)                                                      \
    r += fn_80124A4C(u, sk, 0) * 5;                                     \
    f32 bio = fn_801070A4(u);                                           \
    {                                                                   \
        Bonus b;                                                        \
        b = fn_80107864(u->skills, bio);                                \
        r += b.v[idx];                                                  \
    }                                                                   \
    if (AuraOn(u)) {                                                    \
        r += fn();                                                      \
    }                                                                   \
    if (r > 0x7f) {                                                     \
        r = 0x7f;                                                       \
    }                                                                   \
    if (r < -0x80) {                                                    \
        r = -0x80;                                                      \
    }                                                                   \
    return r;                                                           \
}


static inline int EqI(Inv* it) {
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

static inline int IsE(Inv* e) { return e != 0; }
static inline int EqI2(Inv* i0) { int i; Inv* it = i0; for (i = 0; i < 7; i++) { if (it->item == 0) { break; } if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) { return (s8)i; } it++; } return -1; }
static inline Inv* Equip2(Unit* u, Inv* base) { int idx = EqI2(base); if (idx < 0) { return 0; } return &u->inv[idx]; }
static inline Inv* Equip(Unit* u, Inv* base) {
    int idx = EqI(base);
    if (idx < 0) {
        return 0;
    }
    return &u->inv[idx];
}

static inline Inv* Equip3(Unit* u, Inv* base) { int i; Inv* it = base; int idx; for (i = 0; i < 7; i++) { if (it->item == 0) break; if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) { idx = (s8)i; goto f; } it++; } idx = -1; f: if (idx < 0) return 0; return &u->inv[idx]; }
static inline Inv* Equip4(Unit* u, Inv* base) { Inv* it = base; int i; int idx; for (i = 0; i < 7; i++) { if (it->item == 0) break; if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) { idx = (s8)i; goto f; } it++; } idx = -1; f: if (idx < 0) return 0; return &u->inv[idx]; }
static inline Inv* E8(Unit* u, Inv* base, int& i) { Inv* it = base; int idx; for (i = 0; i < 7; i++) { if (it->item == 0) break; if ((*(u32*)(fn_801116B8(it) + 4) & 0x11) && it->equipped) { idx = (s8)i; goto f; } it++; } idx = -1; f: if (idx < 0) return 0; return &u->inv[idx]; }
static inline Inv* E5(Unit* u, Inv* base, int& i) { int idx; for (i = 0; i < 7; i++) { if (base->item == 0) break; if ((*(u32*)(fn_801116B8(base) + 4) & 0x11) && base->equipped) { idx = (s8)i; goto f; } base++; } idx = -1; f: if (idx < 0) return 0; return &u->inv[idx]; }
#pragma push
#pragma use_lmw_stmw on
int fn_801241F4(Unit* u) {
    /*P*/
    Inv* base;
    s8 r;
    int i9;
    u8* it2;
    int i8;
/*E*/
    r = (s8)u->job->padF8[0];
    r += UBF(u);
    r += fn_8011B77C(u->skills, lbl_804CA634) ? 5 : 0;
base = u->inv;
    if (E8(u, base, i8) && (*(u32*)(fn_801116B8(Equip4(u, base)) + 4) & 0x10)) {
        it2 = E5(u, base, i9)->item;
        if (it2 == fn_8010B228(lbl_80369088)) {
            r += 2;
        }
    }
    if (r > 0x63) {
        r = 0x63;
    }
    if (r < 0) {
        r = 0;
    }
    return r;
}

s8 fn_801243F4(Unit* u) {
    Inv* base = u->inv;
    int r = 0;
    Inv* e;
    int i;
    EQUIP_SUM22
    if (AuraOn(u)) {
        r += fn_8010F030();
    }
    if (r > 0x7f) {
        r = 0x7f;
    }
    if (r < -0x80) {
        r = -0x80;
    }
    return r;
}
#pragma pop

}
