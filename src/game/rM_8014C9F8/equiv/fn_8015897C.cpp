/* Round 20, functionally equal (check_regs.py: sched): fn_8015897C. Self-contained. Parent file with its exported fn_ bodies removed plus the fragment from wip/near.cpp, use_lmw_stmw set from the original. Moved (harmless): prologue only, two addi of different globals (lbl_803C8E80, lbl_803EC898) swapped. */
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

#pragma use_lmw_stmw off
/* ---- from build/tmp/r20small/rM/frag_fn_8015897C.cpp ---- */
extern "C" {
/* from fn_80152C20.cpp */
int fn_8015897C(s8* w) {
    /*P*/
    Map* m = &lbl_803EC898;
    u8* b = lbl_803C8E80;
    int r = 0;
    s8* p = lbl_8036A0DC;
/*E*/
    for (; *p != 0x7F; p += 3) {
        s16 ty;
        s16 tx;
        BOOL out;
        tx = p[0] + *(s8*)(b + 0x102);
        out = 0;
        ty = p[1] + *(s8*)(b + 0x103);
        if (tx < m->x0 || m->x1 - 1 < tx || ty < m->y0 || m->y1 - 1 < ty) {
            out = 1;
        }
        if (!out && m->ter[0][(s8)tx + (s8)ty * 0x40] != 0) {
            if (IsFoeT(*(Unit**)(b + 0x3F0), UnitGet(m->ter[0][(s8)tx + (s8)ty * 0x40])) == 0) {
                r += p[2];
            }
        }
    }
    return 0.03125f * ((f32)r * (f32)w[7]);
}
}
