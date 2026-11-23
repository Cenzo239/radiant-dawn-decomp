/* fn_801633C0: functionally equal (regs level per tools/check_regs.py; registers differ from the original). Pick the better of two healing items. */
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
u8* fn_80076F54(u32);
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
int fn_8011B77C(void*, u32);
extern u32 lbl_804CA5C0;
extern u32 lbl_804CA514;
void fn_80114888(Map*, int);
void fn_80114B44(Map*, int, int);
void fn_80165F94(Unit*, int, int);
u32 fn_8016CDEC(Unit*, Filt*);
u32 fn_801645D8(Unit*, int, int);
int fn_8016E29C(Unit*, int, s16*, s16*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);
void fn_80160508(u8, int, int, int, int, int, int);
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

u32 fn_80163178(Unit* u);

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

u32 fn_80164938(Unit* u, int a);

BOOL fn_80164A78(Unit* u);

u32 fn_80164BA8(Unit* u);

u32 fn_8016510C(Unit* u, u8* p, s16* ox, s16* oy);

u8 fn_80163AF0(Unit* u, u16 item);

u8 fn_80165670(Unit* u, s8 a);

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
void fn_80164CD0(void);
void fn_80165764(void* parent);
void fn_801657A0(void* parent);
void fn_801657DC(void* parent);
}


/* ---- fn_801633C0 ---- */
/* from fn_80163178.cpp */
Inv* fn_801633C0(Unit* u, Inv* a, Inv* b) {
    int va0 = ItemVal(u, a);
    s8 vb = ItemVal(u, b);
    s8 va = va0;
    if (va != vb) {
        s32 miss;
        int hp;
        if (va > vb) {
            Inv* t = a;
            s8 t2 = vb;
            a = b;
            b = t;
            vb = va;
            va = t2;
        }
        hp = u->hp;
        miss = fn_801237EC(u) - hp;
        if (fn_8028DB44(miss - va) <= fn_8028DB44(miss - vb)) {
            return a;
        }
        return b;
    } else {
        if (a->uses < b->uses) {
            return a;
        }
        if (a->uses > b->uses) {
            return b;
        }
        return a;
    }
}
