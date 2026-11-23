#ifndef RM_AI_H
#define RM_AI_H
#include "game/rM_8014C9F8/types.h"

/* Layout copied from rH_80112B48/unit.h, fields added as needed. */
struct Person;
struct Job;
struct Inv {
    u8* item;     /* 0x00 */
    u8 uses;      /* 0x04 */
    u8 pad5[0x28 - 5];
};

struct Unit {
    u8 pad0[0xE4];
    Unit* prev;     /* 0xE4 */
    Unit* next;     /* 0xE8 */
    Person* person; /* 0xEC */
    Job* job;       /* 0xF0 */
    u8* team;       /* 0xF4 */
    u8* actor;      /* 0xF8 */
    u8 padFC[6];
    s8 x;           /* 0x102 */
    s8 y;           /* 0x103 */
    u8 pad104[4];
    u32 flags108;   /* 0x108 */
    u32 flags10C;   /* 0x10C */
    u8 pad110[4];
    s8 hp;          /* 0x114 */
    u8 pad115[0x12C - 0x115];
    u8 skills[0x90]; /* 0x12C */
    Inv inv[7];     /* 0x1BC */
    u8 pad2D4[0x390 - 0x2D4];
    u8 ai[0x24];    /* 0x390 */
    u32 w3B4;       /* 0x3B4 */
    u8 pad3B8[4];
    u8 b3BC;        /* 0x3BC */
    u8 pad3BD;
    s16 h3BE;       /* 0x3BE */
    u8 pad3C0[0x3F0 - 0x3C0];
};

static inline Unit* UnitGet(int id);

/* lbl_803CA870: the action the AI will take. */
struct AiAct {
    Unit* unit;  /* 0x00 */
    u8 pad4[8];
    u8 action;   /* 0x0C */
    u8 padD[4];
    s8 x;        /* 0x11 */
    s8 y;        /* 0x12 */
    u8 pad13[0x130 - 0x13];
};

/* lbl_804183F0: AI state. */
struct AiCfg {
    u8 b0;       /* 0x00 */
    u8 b1;       /* 0x01 */
    u8 flags;    /* 0x02 */
    u8 pad3[5];
    int op;      /* 0x08 */
    int padC;
    int res[0x87]; /* 0x10 */

    u8 done;     /* 0x22C */
    u8 pad22D[0x250 - 0x22D];
};

/* The battle map, lbl_803EC898; layout from rH_80112B48/map.h. */
struct Map {
    s32 w;
    s32 h;
    s8 x0, y0, x1, y1;     /* 0x00008 */
    u8 padC;
    u8 ter[5][0x1000];     /* 0x0000D */
    u8 pad500D;
    u16 border[0x40];      /* 0x0500E */
    u16 flags[0x1000];     /* 0x0508E */
    u16 border2[0x40];     /* 0x0708E */
    union { u16 cost[0x1000]; s16 costS[0x1000]; }; /* 0x0710E */
    u16 border3[0x40];     /* 0x0910E */
    u16 cost2[0x1000];     /* 0x0918E */
    u16 g3[0x1000];        /* 0x0B18E */
    u16 g4[0x1000];        /* 0x0D18E */
    union { u16 g5[0x1000]; s8 b5S[0x2000]; }; /* 0x0F18E */
    u16 g6[0x1000];        /* 0x1118E */
    u16 g7[0x1000];        /* 0x1318E */
    u8 pad1518E[2];
    u16* cur;              /* 0x15190 */
};

/* One candidate action. */
struct AiBest {
    u8 x;       /* 0x0 */
    u8 y;       /* 0x1 */
    u16 item;   /* 0x2 */
    Unit* t;    /* 0x4 */
    int score;  /* 0x8 */
    u8 fl;      /* 0xC */
    u8 padD[3];
    AiBest& operator=(const AiBest& o) {
        x = o.x;
        y = o.y;
        item = o.item;
        t = o.t;
        score = o.score;
        fl = o.fl;
        return *this;
    }
};

class Filter {
public:
    virtual int check(Unit*);
};

struct Fn2 {
    void* vt;
    Unit* u;
};
struct Fn3 {
    void* vt;
    Unit* u;
    u8 b;
};

extern "C" {
extern Unit* lbl_804CB810;
extern Map lbl_803EC898;
void* memset(void*, int, u32);
int fn_8012BA20(Unit*, u8*);
void fn_8010E41C(u8*, int);
int fn_8028DB44(int);
int fn_801107C0(u8*, Unit*);
int fn_801107A0(u8*, Unit*);
s8 fn_8012408C(Unit*);
int fn_8011F1A8(Unit*, Unit*);
void fn_801663E0(int, int, u8, u8, int);
void fn_8012A088(Unit*, u16);
int fn_8016D070(void);
int fn_8016D090(void);
u8* fn_80158C98(void);
void fn_80114B44(Map*, int, int);
void fn_80114888(Map*, int);
void fn_80165F94(Unit*, int, int);
extern AiAct lbl_803CA870;
extern AiCfg lbl_804183F0;
extern u8 lbl_80387228[];
extern u8 lbl_80387238[];
extern u8 lbl_80387248[];
extern u8 lbl_80387308[];
extern u8 lbl_80387338[];
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80106F54(void*);
#else
void* fn_80106F54(void*);
#endif
s8 fn_80106ECC(void*);
s8 fn_80106F10(void*);
#if TARGET_PC
FE10_PROTO int fn_801699C8(Unit*, ptr32<const void>, ptr32<const void>);
#else
int fn_801699C8(Unit*, void*, void*);
#endif
int fn_8016CD04(Unit*, void*);
u32 fn_8016E50C(void*, Unit*, s16*, s16*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);
#if TARGET_PC
FE10_PROTO void fn_8016F9C0(ptr32<const void>, int, int, int, u16, int, int, int);
FE10_PROTO s8 fn_80172748(ptr32<const void>);
#else
void fn_8016F9C0(Unit*, int, int, int, u16, int, int, int);
s8 fn_80172748(Unit*);
#endif
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
void fn_800453B4(AiAct*, u8);
int fn_800A05B0(int, int, int);
u32 fn_8016DC30(Unit*, u16, s16*, s16*);
}

static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

static inline BOOL MapOut(Map* m, s8 y, s8 x) {
    BOOL r = 0;
    if (x < m->x0 || m->x1 - 1 < x || y < m->y0 || m->y1 - 1 < y) {
        r = 1;
    }
    return r;
}

static inline BOOL MapOutU(Map* m, Unit* v) {
    s8 x = v->x;
    s8 y = v->y;
    BOOL r = 0;
    if (x < m->x0 || m->x1 - 1 < x || y < m->y0 || m->y1 - 1 < y) {
        r = 1;
    }
    return r;
}

#endif
