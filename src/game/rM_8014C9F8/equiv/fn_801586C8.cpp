/* fn_801586C8: battle forecast for the AI (damage each way, with follow-up
   attacks; result bits 1/2 = attacker/defender dies, 4/8 = no damage).
   Level: renamed. Body from wip/fn_801586C8_r20.cpp with the two final tests
   written `<= 0` (the draft had `< 1`, which compiles to cmpwi 1; bge). */
/* AI: pick the best attack over items and targets; 80152C20, 80153070, 801534C0. */
#include "game/rM_8014C9F8/ai.h"

extern "C" {

extern int fn_8010E398(void*, void*);
extern int fn_80155D2C(Unit*, AiBest*, void*);

#pragma use_lmw_stmw on

u8 fn_80152C20(Filter* f, void* arg, int act);

extern int fn_8015639C(Unit*, AiBest*, void*);

#pragma use_lmw_stmw on

u8 fn_80153070(Filter* f, void* arg, int act);

extern int fn_80156A18(Unit*, AiBest*, void*);

#pragma use_lmw_stmw on

u8 fn_801534C0(Filter* f, void* arg, int act);


static inline void Fn2Init(Fn2* f, Unit* u) {
    f->vt = lbl_80387338;
    f->u = u;
}

static inline BOOL SameSide(Unit* a, Unit* b) {
    return (u8)fn_8010E398(a->team, b->team) == 1;
}

struct Reach {
    u8 pad0[4];
    AiBest* a;   /* 0x4 */
    Unit* u;     /* 0x8 */
    AiBest* b;   /* 0xC */
};

#pragma use_lmw_stmw off

BOOL fn_80153910(Unit* u, Unit* v, u8** item);


#pragma use_lmw_stmw off

void fn_801539CC(Unit* u, Unit* v, u8** item);


extern int fn_80157548(Unit*, AiBest*, void*);
extern u8 lbl_803E7320[];
extern void fn_800CFC50(void*, int, int, u8, int);
extern u8* fn_800CFCB4(void*, int, int);
extern void fn_800392FC(void*, int, int);

#pragma use_lmw_stmw off

void fn_80153FBC(Reach* r, Unit* v);


struct Vis {
    void* vt;
    Filter* f;  /* 0x4 */
    s8 x;       /* 0x8 */
    s8 y;       /* 0x9 */
    virtual int visit(Unit*);
};

#pragma use_lmw_stmw off

void fn_80155A80(Vis* p, Unit* v);


#pragma use_lmw_stmw off

void fn_80155BCC(Vis* p, Unit* v);


#pragma use_lmw_stmw off

void fn_80155CA0(Vis* p, Unit* v);


extern u8* fn_801181E8(Map*, int, int);
extern int fn_8011B77C(void*, void*);
extern char* lbl_804CA500;
extern int fn_801676D8(int, int);
extern int fn_80158208(Unit*, int, int, int);
extern s8 lbl_8036A090[];
static inline u32 IsFoeT(Unit* a, Unit* b) { return (u8)fn_8010E398(a->team, b->team) == 1; }

static inline int Terrain(Unit* u, u8* t) {
    int a;
    if (fn_8011B77C((u8*)u + 0x12C, lbl_804CA500)) {
        s8* s = *(s8**)(t + 8);
        a = s[3] + s[4];
        a += s[5];
        a += (u8)s[6];
    } else {
        s8* s = *(s8**)(t + 8);
        a = s[0] + s[1];
        a += s[2];
        a += (u8)s[6];
    }
    return a;
}

#pragma use_lmw_stmw off

int fn_8015814C(Unit* u, s8 x, s8 y);


/* from fn_80152C20.cpp */
extern s8 lbl_8036A090[];
extern s8 lbl_8036A0DC[];
extern void fn_800392FC(void*, int, int);
extern int fn_80158354(Unit*, Unit*, void*, int);
static inline int TerrainH(Unit* u, u8* t) { return Terrain(u, t) >> 1; }
#pragma use_lmw_stmw on

int fn_80158208(Unit* u, int x, int y, int k);

extern u8 lbl_803C8E80[];
extern s8 lbl_8036A0DC[];
extern char* lbl_804CA4D8;
extern void fn_800392FC(void*, int, int);
extern int fn_80158354(Unit*, Unit*, void*, int);
#pragma use_lmw_stmw off

void fn_80155B20(Vis* p, s8 x, s8 y);


#pragma use_lmw_stmw off

int fn_80158B1C(u8* w);


#pragma use_lmw_stmw on

}

#pragma use_lmw_stmw on
/* ---- from build/tmp/r20small/rM/frag_fn_801586C8.cpp ---- */
extern "C" {
/* from fn_80152C20.cpp */
int fn_801586C8(Unit* a, Unit* d, int* pa, int* pd, void* w) {
    /*P*/
    int da;
    int dd;
    u32 r;
    int sa;
    int sd;
    BOOL ka;
    BOOL kd;
    /*E*/
    dd = 0;
    r = 0;
    sa = *(s16*)((u8*)a + 0x44C);
    sd = *(s16*)((u8*)d + 0x44C);
    ka = sa >= sd + 4;
    kd = sd >= sa + 4;
    da = fn_80158354(a, d, w, 1);
    if (d->hp <= da) {
        r |= 2;
    } else {
        dd = fn_80158354(d, a, w, 0);
        if (a->hp <= dd) {
            r |= 1;
        } else {
            if (ka) {
                da += fn_80158354(a, d, w, 1);
                if (d->hp <= da) {
                    r |= 2;
                    goto end;
                }
            }
            if (kd) {
                dd += fn_80158354(d, a, w, 0);
                if (a->hp <= dd) {
                    r |= 1;
                }
            }
        }
    }
end:
    if (da <= 0) {
        r |= 8;
    }
    if (dd <= 0) {
        r |= 4;
    }
    *pa = da;
    *pd = dd;
    return r;
}
}
