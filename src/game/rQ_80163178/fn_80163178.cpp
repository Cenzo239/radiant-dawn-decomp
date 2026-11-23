/* AI: healing and retreat decisions, 80163178.. */
#include "game/rQ_80163178/types.h"
#pragma use_lmw_stmw on

struct Filt {
    void* vt;
    Unit* u;
    Filt(void* v, Unit* w) {
        u = w;
        vt = v;
    }
};
struct Bf110 { u8 pad[0x110]; u16 st : 3; };

#define MAPW (lbl_803EC898.x1)

struct ListHdr { int n; };
static inline u8 ItemB(u8* it, int off) { return it ? it[off] : 0x13; }

extern "C" {
extern ListHdr lbl_803E7320[];
int fn_80129A8C(Unit*);
void fn_8016CB18(Unit*, Filt*);
void* fn_800CFD18(ListHdr*, int);
Unit* fn_800CFB0C(void* e);
void fn_80169B20(Unit*, int, int, int, Filt*, s16*, s16*);
s16 fn_801237EC(Unit*);
int fn_8016D090(void);
int fn_8016D0B0(Unit*);
#if TARGET_PC
FE10_PROTO u8* fn_80076F54(p32arg);
#else
u8* fn_80076F54(u32);
#endif
void* fn_8010B228(char*);
int fn_801C8858(void*);
int fn_8028DB44(int);
int fn_8012BC2C(Unit*, void*);
u32 fn_8016DF74(Unit*, int, void*, void*);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
extern char lbl_80387374[];
extern char lbl_80387364[];
extern char lbl_80387354[];
extern char lbl_80387348[];
extern u8 lbl_80387308[];
extern u8 lbl_80387328[];
extern u8 lbl_80387338[];
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5C0;
FE10_PROTO extern void *lbl_804CA514;
#else
extern u32 lbl_804CA5C0;
extern u32 lbl_804CA514;
#endif
void fn_80114888(Map*, int);
void fn_80114B44(Map*, int, int);
void fn_80165F94(Unit*, int, int);
u32 fn_8016CDEC(Unit*, Filt*);
u32 fn_801645D8(Unit*, int, int);
int fn_8016E29C(Unit*, int, s16*, s16*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);
#if TARGET_PC
FE10_PROTO void fn_80160508(u8, p32arg, int, int, int, int, int);
#else
void fn_80160508(u8, int, int, int, int, int, int);
#endif
int fn_800A05B0(int, int, int);
u8* fn_80158C98(void);
}

static inline s8 ItemVal(Unit* u, Inv* inv) {
    void* item = inv->item;
    int r = 0;
    if (item == fn_8010B228(lbl_80387374)) {
        r = fn_801C8858(item);
    } else if (item == fn_8010B228(lbl_80387364)) {
        r = fn_801C8858(item);
    } else if (item == fn_8010B228(lbl_80387354)) {
        r = fn_801C8858(item);
    } else if (item == fn_8010B228(lbl_80387348)) {
        r = fn_801237EC(u);
    }
    return r;
}

static inline int InvIdx(Inv* q, Inv* best) {
    int idx;
    for (idx = 0; idx < 7; idx++, q++) {
        if (best == q) break;
    }
    return idx;
}

extern "C" {

u32 fn_80163178(Unit* u) {
    u32 r = 0;
    if (fn_8016D0B0(u)) {
        int hp = u->hp;
        if ((f32)hp / (f32)fn_801237EC(u) <= 0.8f) {
            r = 1;
            u->w3B4 |= 1;
        } else {
            r = 0;
            u->w3B4 &= ~1;
        }
    } else if (fn_8016D090()) {
        int hp = u->hp;
        if ((f32)hp / (f32)fn_801237EC(u) <= 0.5f) {
            r = 1;
            u->w3B4 |= 1;
        } else {
            r = 0;
            u->w3B4 &= ~1;
        }
    } else {
        s16 max = fn_801237EC(u);
        u32 pct = 100.0f * (f32)u->hp / (f32)max;
        u8* d = fn_80076F54(u->w3A0);
        if (u->w3B4 & 1) {
            if (d[6] <= pct) {
                u->w3B4 &= ~1;
            } else {
                r = 1;
            }
        } else if (d[5] > pct) {
            r = 1;
            u->w3B4 |= 1;
        }
    }
    return r;
}

Inv* fn_801633C0(Unit* u, Inv* a, Inv* b);

}

extern "C" {

u32 fn_801635B8(Unit* u, int a);

u8 fn_80163808(Unit* u, int a);

u32 fn_80164938(Unit* u, int a);
}
static inline u8 Slow(Map* m, Unit* u, int x, int y) {
    if (fn_8011B77C(u->skills, lbl_804CA5C0)) {
        fn_80114888(m, 6);
        fn_80114B44(m, 0xc, -1);
        m->cur[x + y * 0x40] = 0;
        {
            Filt f(lbl_80387308, u);
            if (fn_8016CDEC(u, &f)) {
                return lbl_804183F0.done;
            }
        }
    }
    return 0;
}
extern "C" {

u32 fn_80164938(Unit* u, int a) {
    Map* m;
    int x, y;
    if (fn_8016D090() || fn_8016D0B0(u)) {
        return 0;
    }
    if (a == lbl_803CA870.action) {
        return 0;
    }
    x = lbl_803CA870.x;
    m = &lbl_803EC898;
    y = lbl_803CA870.y;
    if (Slow(m, u, x, y)) {
        return 1;
    }
    return fn_801645D8(u, x, y);
}

BOOL fn_80164A78(Unit* u) {
    Map* m;
    int x, y;
    if (fn_8016D090() || fn_8016D0B0(u)) {
        return 0;
    }
    if (lbl_803CA870.action == 0x2D) {
        return 0;
    }
    x = lbl_803CA870.x;
    m = &lbl_803EC898;
    y = lbl_803CA870.y;
    if (Slow(m, u, x, y)) {
        return 1;
    }
    return 0;
}

u32 fn_80164BA8(Unit* u) {
    Map* m;
    int x, y;
    if (fn_8016D090() || fn_8016D0B0(u)) {
        return 0;
    }
    x = lbl_803CA870.x;
    m = &lbl_803EC898;
    y = lbl_803CA870.y;
    if (Slow(m, u, x, y)) {
        return 1;
    }
    return fn_801645D8(u, x, y);
}

u32 fn_8016510C(Unit* u, u8* p, s16* ox, s16* oy) {
    s16 x = u->x;
    s16 y = u->y;
    while (*p != 0x40) {
        switch (*p) {
        case 1: x--; break;
        case 2: x++; break;
        case 8: y--; break;
        case 4: y++; break;
        }
        {
            BOOL r = 0;
            if (x < lbl_803EC898.x0 || lbl_803EC898.x1 - 1 < x || y < lbl_803EC898.y0 || lbl_803EC898.y1 - 1 < y) {
                r = 1;
            }
            if (!r && fn_800A05B0(0xb, (s8)x, (s8)y)) {
                *ox = x;
                *oy = y;
                return 1;
            }
        }
        p++;
    }
    return 0;
}

u8 fn_80163AF0(Unit* u, u16 item) {
    s16 x, y;
    if (fn_8016E29C(u, 1, &x, &y)) {
        fn_8016F94C(u, x, y, 1, item, 1, 0, -1);
        if (lbl_804183F0.done && x == lbl_803CA870.x && y == lbl_803CA870.y) {
            fn_80160508(0x2d, 0, (s8)x, (s8)y, -1, 0, 0);
        }
        return lbl_804183F0.done;
    }
    if (fn_8016E29C(u, 0, &x, &y)) {
        fn_8016F94C(u, x, y, 1, item, 1, 0, -1);
        if (lbl_804183F0.done && x == lbl_803CA870.x && y == lbl_803CA870.y) {
            fn_80160508(0x2d, 0, (s8)x, (s8)y, -1, 0, 0);
        }
        return lbl_804183F0.done;
    }
    return 0;
}

u8 fn_80165670(Unit* u, s8 a) {
    s16 x, y;
    if (((Bf110*)u)->st == 0) {
        return 0;
    }
    if (fn_8016DF74(u, 0, &x, &y)) {
        fn_80160610(4, (s8)x, (s8)y, u, (s8)x, (s8)y, a, 0, 0);
    }
    return lbl_804183F0.done;
}

}
extern "C" {
extern u8 lbl_803873C8[];
extern u8 lbl_803873F0[];
struct SkillAct {
    char* name;
    void* item;
    void* func;
};
extern SkillAct lbl_80387380[];
void fn_80164CD0(void) {
    SkillAct* p = lbl_80387380;
    while (p->name) {
        p->item = fn_8010B228(p->name);
        p++;
    }
}
void fn_80165764(void* parent) {
    fn_80081194(lbl_803873C8, parent);
    lbl_804183F0.flags = 1;
}
void fn_801657A0(void* parent) {
    fn_80081194(lbl_803873F0, parent);
    lbl_804183F0.flags = 0x10;
}
void fn_801657DC(void* parent) {
    fn_80081194(lbl_803873C8, parent);
    lbl_804183F0.flags = 8;
}
}
