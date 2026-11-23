/* fn_80159124: exact (round m7, bonus). From equiv/fn_80159124.cpp with the opcode table search written like MSL
   lower_bound (LowerBound, see fn_80158CA0.cpp). */
/* Round 18, functionally equal (check_regs.py: renamed/regs): fn_80159124. Self-contained: fn_80158C8C.cpp with its exported fn_ bodies removed (originals the function inlines kept as static inline *_inl copies) plus the function. From wip/near.cpp. */
/* AI script: per-command handlers, table at lbl_804CB8B8. 80158C8C.. */
#include "game/rM_8014C9F8/ai.h"
#pragma auto_inline off

struct AiCmd {
    int op;      /* 0x00 */
    int a;       /* 0x04: often percent chance */
    int b;       /* 0x08 */
    int c;       /* 0x0C */
    int d;       /* 0x10 */
    u32 fl;      /* 0x14 */
    u32 x;       /* 0x18 */
    u32 y;       /* 0x1C */
    u32 z;       /* 0x20 */
    u32 w;       /* 0x24 */
};

struct Fn4 {
    void* vt;
    Unit* u;
    u32 x;
    u8 k;
};

static inline void Fn2Set(Fn2* f, void* vt, Unit* u) {
    f->u = u;
    f->vt = vt;
}
static inline void Fn4Set(Fn4* f, void* vt, Unit* u, u32 x, u8 k) {
    f->u = u;
    f->vt = vt;
    f->x = x;
    f->k = k;
}

extern "C" {

extern u8 lbl_803872B8[];
extern u8 lbl_803872C8[];
extern AiCmd* lbl_804CB8B8;
extern int lbl_804CB8B4;
extern u8 lbl_804CB8B0;
extern int fn_80089C88(int);
extern void fn_80129550(Unit*, int);
extern int fn_80152C20(void*, void*, u8);

#pragma use_lmw_stmw off
void fn_80158C8C(void);
#pragma use_lmw_stmw off
u8* fn_80158C98(void);

extern u8 lbl_8036A128[];
extern u8 lbl_8036A178[];
extern u8 lbl_8036A1C8[];
extern u8 lbl_8036A780[];
extern u8 fn_80129600(Unit*, int);
extern AiCmd* fn_80076F54(u32);
extern void* fn_80077064(u32);
extern void fn_801293F0(Unit*, u32);
extern void fn_80129438(Unit*, u32);
extern void fn_80129480(Unit*, u32);
extern void fn_801294C8(Unit*, u32);
extern void fn_801295B8(Unit*, int, u8);
extern int fn_8016D1DC(int, int, u32, u32);
extern char* fn_800CFD3C(void*);
extern u8 lbl_803E7320[];
extern void fn_80160508(u8, Unit*, int, int, int, int, int);
extern int fn_80169558(Unit*, void*, void*);
extern int fn_80154678(void*, void*, u8);
extern int fn_80154C44(u32, u8);
extern int fn_801557D0(void*, void*, u8);
extern int fn_8016C9C8(Unit*, void*, void*);
extern int fn_801540B0(void*, void*, u8);
extern int fn_80153A74(void*, void*, u8);
extern int fn_80153070(void*, void*, u8);
extern int fn_801534C0(void*, void*, u8);
extern u32 fn_80170BF8(u32);
extern u8* fn_8012CE54(u32);
extern u8 lbl_803872D8[];
extern u8 lbl_803872E8[];
extern u8 lbl_80387298[];
extern u8 lbl_803872A8[];
extern char lbl_804CE320[4];
extern void fn_8015960C(Unit*);

struct Entry {
    int key;
    void (*fn)(Unit*);
    int pad;
};

static inline Entry* LowerBound(Entry* first, int n, const int& key) {
    int k = key;
    int len = n;
    while (len > 0) {
        Entry* i = first;
        int len2 = len / 2;
        i += len2;
        if (i->key < k) { first = ++i; len -= len2 + 1; } else len = len2;
    }
    return first;
}
static inline Entry* FindOp(AiCmd* c) { return LowerBound((Entry*)lbl_8036A780, 0x52, c->op); }
static inline void RunCmd(Unit* u) {
    Entry* e;
    u32 old;
    e = FindOp(lbl_804CB8B8);
    old = *(volatile u32*)&u->w3B4;
    if (lbl_804CB8B8->fl & 0x20) {
        u->w3B4 |= 0x80000;
    }
    e->fn(u);
    if (old & 0x80000) {
        u->w3B4 |= 0x80000;
    } else {
        u->w3B4 &= ~0x80000;
    }
}

#pragma use_lmw_stmw off
void fn_80159364(Unit* u);
#pragma use_lmw_stmw off
void fn_8015936C(Unit* u);

#pragma use_lmw_stmw off
void fn_80159374(Unit* u);

#pragma use_lmw_stmw off
void fn_80159474(Unit* u);

#pragma use_lmw_stmw off
void fn_801594F0(Unit* u);

#pragma use_lmw_stmw off
void fn_8015960C(Unit* u);

#pragma use_lmw_stmw off
void fn_801597B8(Unit* u);

#pragma use_lmw_stmw off
void fn_801597F8(Unit* u);

#pragma use_lmw_stmw off
void fn_80159810(Unit* u);

#pragma use_lmw_stmw off
void fn_80159888(Unit* u);

#pragma use_lmw_stmw off
void fn_801599E0(Unit* u);

#pragma use_lmw_stmw off
void fn_80159AC8(Unit* u);

#pragma use_lmw_stmw off
void fn_80159AD0(Unit* u);

#pragma use_lmw_stmw off
void fn_80159BD8(Unit* u);

#pragma use_lmw_stmw off
void fn_80159CBC(Unit* u);

#pragma use_lmw_stmw off
void fn_80159DA4(Unit* u);

#pragma use_lmw_stmw off
void fn_80159F80(Unit* u);

#pragma use_lmw_stmw off
void fn_8015A074(Unit* u);

#pragma use_lmw_stmw off
void fn_8015A07C(Unit* u);

#pragma use_lmw_stmw off
void fn_8015A164(Unit* u);

#pragma use_lmw_stmw off
void fn_8015A274(Unit* u);

#pragma use_lmw_stmw off
void fn_8015A388(Unit* u);

#pragma use_lmw_stmw off
void fn_8015A470(Unit* u);

#pragma use_lmw_stmw off
void fn_8015A4B4(Unit* u);

#pragma use_lmw_stmw off
void fn_8015A59C(Unit* u);

extern u8 lbl_80387218[];
extern u8 lbl_80387208[];
extern u8 lbl_803871F8[];
extern u8 lbl_80387318[];
extern void fn_80129170(void*, void*);
extern void fn_80129160(void*);
extern int fn_8010B228(u32);
extern int fn_80155090(void*, void*, u32, u8);
extern int fn_80234954(void*, void*, u8);
extern int fn_80234C48(void*, void*, u8);
extern int fn_8016E3BC(u32, s16*, s16*, int*);
extern int fn_80170C48(int, int, int, int);
extern int fn_8016D11C(Unit*);
extern u32 fn_8016E67C(void*, Unit*, s16*, s16*);
extern int fn_80164F90(Unit*);
extern char* lbl_804CA508;
extern int fn_8011B77C(void*, void*);
extern int fn_80171A20(Unit*, int, s16*, s16*);
extern int fn_8016D944(Unit*, int, u32, s16*, s16*);
extern int fn_8016D27C(Unit*, int, u32, s16*, s16*);
extern void fn_80164938(Unit*, u32);
extern int fn_80163AF0(Unit*, u16);
extern void fn_80164A78(Unit*);

struct Fn3x {
    void* vt;
    Unit* u;
    int v;
};

static inline void Fn3Set(Fn3x* f, void* vt, Unit* u, int v) {
    f->u = u;
    f->vt = vt;
    f->v = v;
}

#pragma use_lmw_stmw off
void fn_8015AACC(Unit* u);

#pragma use_lmw_stmw off
void fn_8015ABBC(Unit* u);

#pragma use_lmw_stmw off
void fn_8015ACD0(Unit* u);

#pragma use_lmw_stmw off
void fn_8015ADC8(Unit* u);

#pragma use_lmw_stmw off
void fn_8015AEC0(Unit* u);

#pragma use_lmw_stmw off
void fn_8015AFE4(Unit* u);

#pragma use_lmw_stmw off
void fn_8015B0D4(Unit* u);

#pragma use_lmw_stmw on
void fn_8015B488(Unit* u);

#pragma use_lmw_stmw off
void fn_8015B598(Unit* u);

#pragma use_lmw_stmw off
void fn_8015B8B4(Unit* u);

#pragma use_lmw_stmw off
void fn_8015B95C(Unit* u);

#pragma use_lmw_stmw off
void fn_8015BA84(Unit* u);

#pragma use_lmw_stmw off
void fn_8015BBAC(Unit* u);

#pragma use_lmw_stmw off
void fn_8015BBB4(Unit* u);

#pragma use_lmw_stmw off
void fn_8015BF88(Unit* u);

#pragma use_lmw_stmw off
void fn_8015CA88(Unit* u);
#pragma use_lmw_stmw off
void fn_8015CA90(Unit* u);

extern u32 fn_8016E7FC(void*, Unit*, s16*, s16*);
extern u32 fn_8016E9A8(void*, Unit*, s16*, s16*);
extern u32 fn_8016EBD8(void*, Unit*, s16*, s16*);
extern u32 fn_8016EDE8(void*, Unit*, s16*, s16*);
extern u8* fn_800CFCB4(void*, int, int);
extern int fn_8009FF74(void);
extern void fn_80172494(Unit*, int, int);
extern void fn_8016EFC8(Unit*, int, int, int, u16, int, int, int);
extern char* fn_800CFD18(void*, int);
extern u32 fn_8016D5D4(Unit*, int, int, s16*, s16*);
extern s8 fn_8012C9BC(Unit*, u8*);
extern int fn_8012C8BC(Unit*, u8*);
extern s16 fn_801237EC(Unit*);
extern s8 fn_801284C4(Unit*);
extern char* lbl_804CA4EC;
extern char* lbl_804CA4E8;
extern char* lbl_804CA5E0;
extern char* lbl_804CA650;
extern char* lbl_804CA4F0;
extern char* lbl_804CA4F4;
extern void fn_8017252C(Unit*, int, int, int);

#pragma use_lmw_stmw off
void fn_8015D474(Unit* u);

#pragma use_lmw_stmw off
void fn_8015DA04(Unit* u);

#pragma use_lmw_stmw off
void fn_8015DB34(Unit* u);

#pragma use_lmw_stmw off
void fn_8015E61C(Unit* u);

#pragma use_lmw_stmw off
void fn_8015E8B4(Unit* u);

#pragma use_lmw_stmw off
void fn_8015ECEC(Unit* u);

#pragma use_lmw_stmw off
void fn_8015EDC8(Unit* u);

#pragma use_lmw_stmw off
void fn_8015EE6C(Unit* u);

extern int fn_801705A8(Unit*, int, int, void*, u8, int, u16, int, int, int);

#pragma use_lmw_stmw on
void fn_8015B738(Unit* u);

#pragma use_lmw_stmw off
void fn_8015D14C(Unit* u);

#pragma use_lmw_stmw off
void fn_8015D868(Unit* u);

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
static inline void ActAt(int v, Unit* u, s8 x, s8 y) {
    fn_80160508(v, u, x, y, -1, 0, 0);
}
#pragma use_lmw_stmw on

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off
void fn_80159EAC(Unit* u);

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw on

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off
void fn_8015E95C(Unit* u);

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw off
void fn_8015B614(Unit* u);

/* from fn_80158C8C.cpp */

static inline s8 ActFlag16(void) { return ((s8*)&lbl_803CA870)[0x16]; }

#pragma use_lmw_stmw on

/* from fn_80158C8C.cpp */
#pragma use_lmw_stmw on

extern int fn_801658E4(Unit*, s8, s8);
extern int fn_80171A30(Unit*, int, s16*, s16*);
extern int fn_8015C018(Unit*, int, int, s16*, s16*, s8*);
extern int fn_8015C468(Unit*, int, int, s16*, s16*, s8*);

#pragma use_lmw_stmw on
void fn_8015C8B8(Unit* u);

#pragma use_lmw_stmw on
void fn_8015CA98(Unit* u);

extern void fn_800CFB34(void*);

#pragma use_lmw_stmw on
void fn_8015EA68(Unit* u);
#ifndef ABS
#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif
extern u32 fn_801676D8(int,int);
extern void fn_80165E18(Unit*, int, int);
#pragma use_lmw_stmw on

extern int fn_8016E2AC(Unit*, s16*, s16*, int);
extern int fn_801723A8(void*, Unit*, u32, u32, BOOL, f32);
extern int fn_80171E5C(void*, Unit*, int, u32, u32, BOOL);
class FilterV { public: virtual int check(void*); };
#pragma use_lmw_stmw off
void fn_8015D290(Unit* u);

#pragma use_lmw_stmw off
void fn_8015E750(Unit* u);

#pragma use_lmw_stmw off
void fn_8015EF74(Unit* u);

#pragma use_lmw_stmw on

extern void fn_8016FA34(int, int, Unit*, int, int, int, u16, int, int, int);
extern void fn_80116BD0(Map*, int, int, int, int);
extern u8* fn_80116294(Map*, void*, int, int, int);
extern int fn_801107A0(u8*, Unit*);
static inline int InvRange(Unit* u, Inv* v) {
    if (v->item != NULL) {
        return (u8)fn_801107A0(v->item, u);
    }
    return 0;
}
#pragma use_lmw_stmw on

static inline void ActS(u8 a, s8 x, s8 y) { fn_80160610(a, x, y, NULL, x, y, -1, 0, 0); }
#pragma use_lmw_stmw on

}

extern "C" {
/* from fn_80158C8C.cpp */
u8 fn_80159124(Unit* u) {
    lbl_804CB8B4 = 1;
    lbl_804CB8B8 = fn_80076F54(*(u32*)((u8*)u + 0x398));
    lbl_804CB8B8 += fn_80129600(u, lbl_804CB8B4);
    lbl_804CB8B0 = 0;
    lbl_804183F0.op = lbl_804CB8B8->b;
    RunCmd(u);
    return lbl_804CB8B0;
}


}
