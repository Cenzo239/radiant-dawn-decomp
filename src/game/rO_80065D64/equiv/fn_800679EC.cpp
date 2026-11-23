/* Round 18, functionally equal (check_regs.py: renamed/regs): fn_800679EC. Self-contained: fn_800677E4.cpp with its exported fn_ bodies removed (originals the function inlines kept as static inline *_inl copies) plus the function. From wip/near.cpp. */
/* Cursor unit, turn helpers, BGM tables, music fade process, 800677E4..80068EC4. */
#include "game/rO_80065D64/trap.h"
#pragma auto_inline off

struct FlagTable {
    u8 pad0[0x144];
    char* names[0x80]; /* 0x144 */
    u32 hashes[0x80];  /* 0x344 */
    u8 bits[0x10];     /* 0x544 */
};

class Input {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual u32 v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual int v50();
    virtual int v54();
};

struct SideList { Unit* head; Unit* tail; int n; };
struct Mode { u32 pad : 25; u32 b6 : 1; u32 rest : 6; u8 pad4[0xD]; u8 f11; };
struct MoveState { Unit* unit; u8 pad4[0x11]; u8 f15; s8 f16; };

extern "C" {
extern u8 lbl_803CAB38[];
extern SideList* lbl_804CB814;
extern int fn_80109384(void*);
extern void fn_80114888(Map*, int);
extern void fn_801151BC(Map*, Unit*);
extern void fn_8011567C(Map*, u8*);
extern s8 fn_8012408C(Unit*);
extern void fn_80115764(Map*, s8, s8, u16);
extern void fn_80114B44(Map*, int, int);
extern void fn_800676C4(Unit*);
extern void fn_8006758C(Unit*);
extern MoveState lbl_803CA870;
extern void fn_800453FC(MoveState*);
extern void fn_80045120(MoveState*, Unit*);
extern void* fn_800D0864(const char*);
extern void fn_800310E4(void*, int, int, int);
extern void fn_8013F1C4(void);
extern void fn_8013F204(void);
extern char lbl_803621D0[];
extern Unit* lbl_804CB568;
extern Input* lbl_804CB5B8;
extern Mode* fn_80060728(void*);
extern void* fn_8010DD58(void*, int);
extern int fn_800767DC(void*);
extern void* fn_800769D0(void*, int);
extern int fn_8010DAC4(void*, void*);
extern u8* fn_8010B0CC(int);
extern int fn_80092C28(u8*, u8);
extern void fn_80061584(void*, u8);
extern u32* fn_80077064(const char*);
extern int fn_80291188(const char*, const char*);
extern u32 fn_80076D18(const char*);
extern int fn_80060914(void*);
extern int fn_80060960(void*);
extern int fn_80060988(void*);
extern int fn_800609B0(void*);
extern char** fn_8006074C(void*);
extern char lbl_804CB56C[1];
extern void fn_80252738(int, f32);
extern void fn_80252850(int, f32);
extern void* fn_8013B9A8(void);
extern void fn_8013AAB4(void*, int);
extern void fn_80250E38(int, f32, f32);
extern void fn_80010AE4(void*);
extern void fn_80021754(int*);
extern void fn_80131D38(void);
extern void fn_80140B58(void);
extern u8 lbl_8037F9D8[];
extern u8 lbl_8037A1E8[];
extern u8* fn_80083B84(void*);
extern void fn_80081050(void*, int);
extern void fn_800846BC(void*);
extern void fn_80193054(u8*);
extern void fn_80192FD4(u8*);

static inline Unit* UnitAt(s8 x, s8 y) {
    u8 id = lbl_803EC898.ter[0][x + (y << 6)];
    return UnitGet(id);
}

Unit* fn_800677E4(void);

int fn_80067858(int a, int b, int c);

static inline BOOL Usable(Unit* u) {
    if (u->flags10C & 5) {
        return 0;
    }
    return fn_80109384(u->skills110) == 0;
}

Unit* fn_80067880(Unit* cur);

static inline void ShowMove2(Unit* u) {
    s8 x;
    s8 y;
    y = u->y;
    x = u->x;
    fn_80115764(&lbl_803EC898, x, y, (s8)fn_8012408C(u));
}

static inline void ShowMove(Unit* u) {
    fn_80114888(&lbl_803EC898, 6);
    fn_801151BC(&lbl_803EC898, u);
    fn_8011567C(&lbl_803EC898, u->team);
    ShowMove2(u);
    fn_80114888(&lbl_803EC898, 7);
    fn_80114B44(&lbl_803EC898, 9, 0);
    fn_800676C4(u);
    fn_8006758C(u);
    fn_80114888(&lbl_803EC898, 6);
}

void fn_800679EC(Unit* u);

void fn_80067B78(void);

int fn_80067D74(s8 x, s8 y);

#pragma push
#pragma use_lmw_stmw on
void* fn_80067E20(void* key);
#pragma pop

static inline BOOL ChapterHas(u8* p) {
    BOOL r = 0;
    if (p != 0 && p[0x8D] != 0) {
        r = 1;
    }
    return r;
}

static inline int ChapterExists(int id) {
    return ChapterHas(fn_8010B0CC(id));
}

int fn_80067EA8(int id);

static inline BOOL ChapterOk(int id) {
    int r = 0;
    u8* p = fn_8010B0CC(id);
    if (ChapterHas(p)) {
        if (fn_80092C28(p, fn_80060728(lbl_803CAB38)->f11)) {
            r = 1;
        }
    }
    return r;
}

int fn_80067EE8(void);

u8 fn_80067FE8(int a);

/* Event flags, as in rC_8004BE18/decls.h */
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
static inline bool flagExists(FlagTable* t, const char* name) {
    if (name[0] == 0) {
        return false;
    }
    return flagFind(t, name) >= 0;
}

struct GroupEnt {
    char* chap;   /* 0 */
    char* flag;   /* 4 */
    u8 val;       /* 8 */
    u8 pad9[3];
    u32 result;   /* C */
};

static inline BOOL GroupMatch(GroupEnt* e, char** chap) {
    if (e->chap != 0 && fn_80291188(e->chap, *chap) != 0) {
        return 0;
    }
    if (e->flag != 0 && !flagExists((FlagTable*)lbl_803CAB38, e->flag)) {
        return 0;
    }
    if (e->flag != 0 && (e->val != 0) != flagGet((FlagTable*)lbl_803CAB38, e->flag)) {
        return 0;
    }
    return 1;
}

#pragma push
#pragma use_lmw_stmw on
u32 fn_800680D0(char** chap);
#pragma pop

struct BgmEnt {
    char* chap;   /* 0 */
    u8 cond;      /* 4 */
    u8 pad5[3];
    u32 a[4];     /* 8 */
    u32 b[4];     /* 18 */
    u32 f28;
    u32 f2C;
    u32 f30;
};

BOOL fn_800682C4(const BgmEnt* e, char** chap);


#pragma push
#pragma use_lmw_stmw on
u32 fn_80068398(char** chap, int k);

u32 fn_80068424(char** chap, int k);
#pragma pop

u32 fn_800684A0(char** chap);

u32 fn_80068528(char** chap);

u32 fn_800685B0(char** chap);

struct BattleBgmEnt {
    u32 result;   /* 0 */
    char* chap;   /* 4 */
    char* n1;     /* 8 */
    char* n2;     /* C */
    char* flag;   /* 10 */
    u8 t1;        /* 14 */
    u8 t2;        /* 15 */
    u8 s1;        /* 16 */
    u8 s2;        /* 17 */
    u8 val;       /* 18 */
    u8 either;    /* 19 */
};

#pragma push
#pragma use_lmw_stmw on
BOOL fn_80068638(const BattleBgmEnt* e, Unit* a, Unit* b);

u32 fn_800689D4(Unit* a, Unit* b);
#pragma pop

void fn_80068A4C(void);

void fn_80068A58(void);

u8 fn_80068A64(void);

void fn_80068A6C(int f);

void fn_80068AB4(int f);

void fn_80068AFC(int v);

struct Fade { u8 pad[0x60]; int v60; int v64; };

void fn_80068B38(Fade* p);

BOOL fn_80068B54(Fade* p);

void fn_80068BC4(void);

void fn_80068C08(void);

void fn_80068C58(void);

void fn_80068CBC(void);

int fn_80068CF8(void);

void fn_80068D34(int v);

static inline int FadeCount(void) {
    Fade* p = (Fade*)fn_80083B84(lbl_8037F9D8);
    if (p != 0) {
        return p->v60;
    }
    return 0;
}

BOOL fn_80068D74(void);

u8* fn_80068DE4(void);

void fn_80068DF0(void);

void fn_80068E00(void);

struct MenuItem { u8 pad[0x18]; u8* parent; u8 pad1C[0x32 - 0x1C]; s16 y; u8 pad34[2]; s16 h; };

void fn_80068E0C(void* x, MenuItem* m);

void fn_80068E5C(void* x, MenuItem* m);

void fn_80068E84(void* x, MenuItem* m);
}

extern "C" {
/* from fn_800677E4.cpp: 2 of 99 words differ */
void fn_800679EC(Unit* u) {
    if (lbl_803CA870.f16) {
        fn_800453FC(&lbl_803CA870);
        u8 v = lbl_803CA870.f15;
        fn_80114B44(&lbl_803EC898, 9, 0);
        fn_80114888(&lbl_803EC898, 6);
        fn_801151BC(&lbl_803EC898, u);
        fn_8011567C(&lbl_803EC898, u->team);
        fn_80115764(&lbl_803EC898, u->x, u->y, v);
        fn_800310E4(fn_800D0864(lbl_803621D0), 0, 0x28, 0);
    } else {
        fn_80045120(&lbl_803CA870, u);
        ShowMove(u);
        fn_800310E4(fn_800D0864(lbl_803621D0 + 0xB), 0, 0x28, 0);
    }
    fn_8013F1C4();
}


}
