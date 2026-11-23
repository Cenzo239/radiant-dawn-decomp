/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_801629B4. Self-contained, complete source. Instruction count ours 105 orig 104. What differs: same as fn_8016281C with the name test negated (105 vs 104 instructions). */
/* AI: target filter functors; side test, name lists, 80161E04..80162E1C. */
#include "game/rM_8014C9F8/ai.h"

struct F {
    void* vt;
    Unit* u;   /* 0x4 */
    char** s;  /* 0x8 */
    u8 k;      /* 0xC */
};

struct G {
    void* vt;
    Unit* u;   /* 0x4 */
    u8 k;      /* 0x8 */
};

extern "C" {

extern int fn_8010E398(void*, void*);
extern int fn_80291188(const char*, const char*);
extern u8 lbl_803CAB38[];

static inline BOOL Same(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}

static inline BOOL SameB(Unit* a, Unit* b) {
    return (u8)fn_8010E398(a->team, b->team) == 1;
}

#pragma use_lmw_stmw off

int fn_80161E04(void);

#pragma use_lmw_stmw off

int fn_80161E0C(void);


#pragma use_lmw_stmw off

BOOL fn_80161E14(const F* f, Unit* v);


#pragma use_lmw_stmw off

int fn_80161E4C(const F* f, Unit* v);


#pragma use_lmw_stmw off

BOOL fn_80161ED8(const F* f, Unit* v);


static inline BOOL SideB(u8 k, Unit* me, Unit* v) {
    BOOL r = 0;
    switch (k) {
    case 0:
        r = (u8)fn_8010E398(me->team, v->team) == 0;
        break;
    case 1:
        r = (u8)fn_8010E398(me->team, v->team) == 1;
        break;
    case 2:
        r = (u8)fn_8010E398(me->team, v->team) == 2;
        break;
    case 3:
        r = 1;
        break;
    }
    return r;
}

static inline BOOL SideTest(Unit* me, u8 k, Unit* v) {
    BOOL r = 0;
    switch (k) {
    case 0:
        r = (u8)fn_8010E398(me->team, v->team) == 0;
        break;
    case 1:
        r = (u8)fn_8010E398(me->team, v->team) == 1;
        break;
    case 2:
        r = (u8)fn_8010E398(me->team, v->team) == 2;
        break;
    case 3:
        r = 1;
        break;
    }
    return r;
}

#pragma use_lmw_stmw off

int fn_80161FA4(const F* f, Unit* v);


#pragma use_lmw_stmw off

int fn_801620A0(const F* f, Unit* v);


static inline u32 NameEq(const char* a, const char* b) {
    return fn_80291188(a, b) == 0;
}

static inline u32 NameIn(const char* n, char** s) {
    u32 r = 0;
    while (*s != NULL) {
        r = NameEq(*s++, n);
        if (r == 1) {
            break;
        }
    }
    return r;
}

#pragma use_lmw_stmw off

BOOL fn_8016219C(const F* f, Unit* v);


#pragma use_lmw_stmw off

BOOL fn_801622AC(const F* f, Unit* v);


#pragma use_lmw_stmw off

BOOL fn_801623C4(const F* f, Unit* v);


#pragma use_lmw_stmw off

BOOL fn_801624D4(const F* f, Unit* v);


#pragma use_lmw_stmw off

int fn_801625EC(const G* f, Unit* v);


struct H {
    void* vt;
    Unit* u;   /* 0x4 */
    int r;     /* 0x8 */
    u8 k;      /* 0xC */
};

extern int fn_80121DEC(Unit*);

#pragma use_lmw_stmw off

int fn_80162D24(const G* f, Unit* v);


#pragma use_lmw_stmw off

int fn_80162E1C(const G* f, Unit* v);


#pragma use_lmw_stmw off

BOOL fn_80162FDC(void* f, Unit* unused, int x, int y);


#pragma use_lmw_stmw off

void fn_80163010(void);


struct Sv {
    u8 pad[0x22D];
    u8 b;       /* 0x22D */
    u8 pad22E[2];
    u32 p[5];   /* 0x230 */
    u32 fl;     /* 0x244 */
    u16 h;      /* 0x248 */
    u8 c[4];    /* 0x24A */
};

#pragma use_lmw_stmw off

void fn_80163014(Sv* s, Unit* u);


extern void fn_801293F0(Unit*, u32);
extern void fn_80129438(Unit*, u32);
extern void fn_80129480(Unit*, u32);
extern void fn_801294C8(Unit*, u32);
extern void fn_80129510(Unit*, u32);

#pragma use_lmw_stmw off

void fn_80163080(Sv* s, Unit* u);


struct J {
    void* vt;
    Unit* u;   /* 0x4 */
    char** s;  /* 0x8 */
    u32 r;     /* 0xC */
    u8 k;      /* 0x10 */
};

static inline BOOL NearT(const J* f, Unit* v) {
    Unit* me = f->u;
    BOOL r = v == *(Unit**)((u8*)me + 0x3C4);
    if (r == 0) {
        int dx = __abs(((s8*)me)[0x3CE] - v->x);
        int dy = __abs(((s8*)me)[0x3CF] - v->y);
        r = dx + dy <= f->r;
    }
    return r;
}

/* from fn_80161E04.cpp */
#pragma use_lmw_stmw off

/* from fn_80161E04.cpp */
#pragma use_lmw_stmw off

/* from fn_80161E04.cpp */
#pragma use_lmw_stmw off

/* from fn_80161E04.cpp */
#pragma use_lmw_stmw off

/* from fn_80161E04.cpp */
#pragma use_lmw_stmw off

/* from fn_80161E04.cpp */
#pragma use_lmw_stmw off

extern void fn_80167704(u8*);
extern void fn_8010CC50(void*, s8*, s8*);
extern u8* fn_80060728(u8*);
extern void fn_80166720(Unit*);
extern void* lbl_803870A8[][5];
extern int fn_80127520(Unit*);
extern int fn_8016D144(Unit*);
extern void fn_8002742C(u8*, int);
extern u8 lbl_803C8E80[];
struct BA { Unit* u; s8 x; s8 y; u8 p; u8 e; int a; int b; };
extern void fn_800269E4(u8*, const BA&, const BA&);
#pragma use_lmw_stmw on

void* fn_80161CD0(Unit* u);

#pragma use_lmw_stmw off

}

#pragma use_lmw_stmw off
/* ---- from build/tmp/r20small/rM/frag_fn_801629B4.cpp ---- */
extern "C" {
/* from fn_80161E04.cpp */
BOOL fn_801629B4(const J* f, Unit* v) {
    BOOL r = SideB(f->k, f->u, v);
    if (r != 0) {
        r = NameIn(*(char**)v->person, f->s) == 0;
    }
    if (r != 0) {
        r = NearT(f, v);
    }
    return r;
}
}
