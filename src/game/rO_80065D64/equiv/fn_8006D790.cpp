/* symcheck: r21 review, flag was an artefact. fn_8006D790: (a) block 1: same eight sums, leftovers in r14/r17/r18
   are dead (reassigned at ins 206-212 before any use); 5 blocks: jump tables unnamed in the original asm, all 9
   tables found byte-equal in the DOL. See docs/SCHED_REVIEW.md. */
/* Round 20, functionally equal (check_regs.py: sched): fn_8006D790. Self-contained. fn_8006C2D0.cpp with exported bodies removed plus the draft from wip/near2.cpp. Changed: a0 is read as *(u8*)&t instead of t.v[0], which makes the compiler hold it in a saved register (r28) like the original instead of reloading it from the stack at each switch. Moved (harmless): the same GrowOf block as fn_8006D380, byte loads and adds of base and growth stats interleaved differently. The six PickS jump tables are compiler generated and not reference-checked. */
/* Battle: experience, 8006C2D0..8006DE18. */
#include "game/rO_80065D64/trap.h"
#pragma auto_inline off

struct BU {
    Unit u;              /* 0 */
    Unit* real;          /* 3F0 */
    u8 pad3F4[0x47F - 0x3F4];
    u8 gain;             /* 47F */
    u8 pad480[0x484 - 0x480];
    u8 b484;             /* 484 */
    u8 pad485[0x492 - 0x485];
    u8 b492;             /* 492 */
    u8 b493[0x4A0 - 0x493]; /* 493 */
};

struct Battle {
    BU a;                /* 0 */
    BU b;                /* 4A0 */
    u8 pad940[0xDE0 - 0x940];
    u8 log[0x15EC - 0xDE0]; /* DE0 */
    u32 flags;           /* 15EC */
};

struct Mode2 { u32 pad : 30; u32 kind : 2; };

struct VB0 { u32 a; };
class VThing : public VB0 {
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
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual int v50();
    virtual int v54();
};

extern "C" {
extern u8 lbl_803CAB38[];
extern f32 lbl_804CD008;
extern u32 lbl_803CB860[];
extern u8 lbl_8037FA70[];
extern u8 fn_8010E398(u8*, u8*);
extern Mode2* fn_80060728(void*);
extern u8 fn_801204E8(BU*);
extern int fn_8011B77C(void*, void*);
extern void* lbl_804CA4FC;
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;
extern int fn_80126B0C(BU*);
extern void fn_8002600C(void*, int, int);
extern void fn_8006D19C(BU*, int, u8*);
extern void fn_80062A7C(void*, u8);
extern void fn_80062A8C(void*, u8);
extern u8 fn_801207B4(BU*, u8);
extern u8 fn_8006CA04(BU*, BU*);
extern u8 fn_8006CB24(BU*, BU*);
extern u16** fn_80030CF4(BU*);
extern s16 fn_8010EA40(void);
extern s16 fn_8010ED38(void);
extern s16 fn_8010EB70(void);
extern s16 fn_8010E9AC(void);
extern s16 fn_8010EAD8(void);
extern u8 fn_80126BA4(BU*);
extern u8 fn_80126C28(BU*);
extern u8 fn_80126D28(BU*);
extern void fn_80126B80(Unit*, u8);
extern void fn_801282F0(Unit*, u8*);
extern void fn_80026CD8(Battle*, BU*, int);
extern void fn_80194524(void*);
void fn_8006C2D0(u8** p);

int fn_8006C2E4(VThing* t);

int fn_8006C2F4(void);

int fn_8006C2FC(void);


extern char lbl_804CA3A0[8];
char* fn_8006C304(void);


struct G { u32 f0; char* s4; u32 f8; char* sC; s16 hC_; };
struct G2 { u32 f0; char* s4; u32 f8; s16 hC; s16 hE; s16 h10; s16 h12; };
extern void* fn_800D0864(char*);
void* fn_8006C30C(G* g);

int fn_8006C314(G2* g);

int fn_8006C31C(void);

int fn_8006C324(void);

void* fn_8006C32C(G* g);

void* fn_8006C334(G* g);

int fn_8006C33C(G2* g);

int fn_8006C344(G2* g);

int fn_8006C34C(void);

int fn_8006C354(void);

int fn_8006C35C(G2* g);

int fn_8006C380(VThing* t);

int fn_8006C3B8(VThing* t);

int fn_8006C3F0(void);

int fn_8006C3F8(void);

int fn_8006C400(void);

int fn_8006C408(void);

int fn_8006C410(void);

int fn_8006C418(void);

f32 fn_8006C420(void);

int fn_8006C428(void);

int fn_8006C430(void);

int fn_8006C438(void);


static inline u8 CapExp(BU* u, u8 exp) {
    if (exp > (u8)fn_801204E8(u)) {
        exp = fn_801204E8(u);
    }
    return exp;
}

static inline BOOL ApplyExp(Battle* b, BU* u, u8 exp) {
    if (exp != 0) {
        switch (u->u.team[8]) {
        case 0:
        case 5:
            fn_8002600C(b->log, 0x2D, (u8)fn_80126B0C(u));
            fn_8002600C(b->log, 0x2E, exp);
            u->gain = exp;
            fn_8006D19C(u, exp, b->log);
            fn_80062A7C(lbl_803CAB38, exp);
            return 1;
        default:
            fn_8002600C(b->log, 0x2D, (u8)fn_80126B0C(u));
            fn_80062A8C(lbl_803CAB38, exp);
            return 0;
        }
    }
    return 0;
}

static inline u8 CalcExp(BU* w, BU* l) {
    u8 exp;
    if (fn_8011B77C(l->u.skills, lbl_804CA4FC)) {
        exp = 0;
    } else {
        u8 base;
        if (w->b492 == 0) {
            base = 1;
        } else {
            u8 v = fn_8006CB24(w, l);
            u8 r = fn_8006CA04(w, l);
            base = r + v;
        }
        exp = CapExp(w, fn_801207B4(w, base));
        w->gain = exp;
    }
    return exp;
}
void fn_8006C440(Battle* b);


void fn_8006C794(Battle* b);
void fn_8006C8E0(Battle* b, u8 x);

u8 fn_8006CA04(BU* w, BU* l);

u8 fn_8006CB24(BU* w, BU* l);

void fn_8006CC40(BU* u);

void fn_8006CCAC(Battle* b, BU* u, u8 x, void* o, int f);


struct BattleLog {
    u8 x[0x20];    /* 0 */
    s16 a[0x20];   /* 20 */
    s16 b[0x20];   /* 60 */
    u8 a0;
    u8 a1;
    u8 a2;
    u8 a3;
    u8 a4;
    s8 a5;
    u8 a6;
    u8 padA7[0xC8 - 0xA7];
    u32 c8;
    u32 cc;
};
extern BattleLog lbl_803C8DA0;
extern Battle lbl_803C8E80;
extern void fn_80026C44(Battle*, void*, void*);
extern void fn_8011FFD0(BU*);
extern void fn_8002ED4C(BU*, int, int);
extern int fn_80122720(BU*);
extern int fn_80122770(BU*);
extern int fn_80122880(BU*);
extern int fn_80122990(BU*);
extern int fn_80122AA0(BU*);
extern int fn_80122BB0(BU*);
extern int fn_80122C20(BU*);
extern int fn_80122D30(BU*);
extern int fn_8012408C(BU*);
extern int fn_8012401C(BU*);
extern void fn_8002CEB0(Battle*);
extern void fn_8006DCF0(BU*, u8*);
extern int fn_80089D68(int);
extern int fn_801D3DEC(void);
extern int fn_80058718(void);
extern void fn_8006D380(BU*, u8*);
extern void fn_8006D790(BU*, u8*);

#pragma push
#pragma use_lmw_stmw on
void fn_8006CE30(Battle* b, void* x);
#pragma pop

void fn_8006D19C(BU* u, int gain, u8* log);
int fn_8006D2C8(s16 v, int a);

void fn_8006DCF0(BU* u, u8* log);


struct Grow { u8 v[8]; };
extern s16 fn_80122F14(BU*, int);
extern s16 fn_80122E8C(BU*, int);
extern int fn_8006D2C8(s16, int);
extern void* lbl_804CA6C8;

static inline u8 GetS(const u8* s, int i) {
    switch (i) {
    case 0:
        return s[0];
    case 1:
        return s[1];
    case 2:
        return s[2];
    case 3:
        return s[3];
    case 4:
        return s[4];
    case 5:
        return s[5];
    case 6:
        return s[6];
    case 7:
        return s[7];
    default:
        return 0xFF;
    }
}

static inline u8 PickS(int i, u8 a0, u8 a1, u8 a2, u8 a3, u8 a4, u8 a5, u8 a6, u8 a7) {
    switch (i) {
    case 0:
        return a0;
    case 1:
        return a1;
    case 2:
        return a2;
    case 3:
        return a3;
    case 4:
        return a4;
    case 5:
        return a5;
    case 6:
        return a6;
    case 7:
        return a7;
    default:
        return 0xFF;
    }
}
#define PICK PickS(i, a0, a1, a2, a3, a4, a5, a6, a7)

static inline Grow MakeG(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h) {
    Grow r;
    r.v[0] = a;
    r.v[1] = b;
    r.v[2] = c;
    r.v[3] = d;
    r.v[4] = e;
    r.v[5] = f;
    r.v[6] = g;
    r.v[7] = h;
    return r;
}

static inline void SetD(u8* d, int i, u8 v) {
    switch (i) {
    case 0:
        d[0] = v;
        break;
    case 1:
        d[1] = v;
        break;
    case 2:
        d[2] = v;
        break;
    case 3:
        d[3] = v;
        break;
    case 4:
        d[4] = v;
        break;
    case 5:
        d[5] = v;
        break;
    case 6:
        d[6] = v;
        break;
    case 7:
        d[7] = v;
        break;
    }
}

static inline int GetD(const u8* d, int i) {
    switch (i) {
    case 0:
        return d[0];
    case 1:
        return d[1];
    case 2:
        return d[2];
    case 3:
        return d[3];
    case 4:
        return d[4];
    case 5:
        return d[5];
    case 6:
        return d[6];
    case 7:
        return d[7];
    default:
        return -1;
    }
}

static inline Grow GrowOf(BU* u) {
    Person* p = u->u.person;
    Grow r;
    u8 t0 = ((u8*)p)[0x2a];
    t0 += ((u8*)u)[0x121];
    u8 t1 = ((u8*)p)[0x2b];
    t1 += ((u8*)u)[0x122];
    u8 t2 = ((u8*)p)[0x2c];
    t2 += ((u8*)u)[0x123];
    u8 t3 = ((u8*)p)[0x2d];
    t3 += ((u8*)u)[0x124];
    u8 t4 = ((u8*)p)[0x2e];
    t4 += ((u8*)u)[0x125];
    u8 t5 = ((u8*)p)[0x2f];
    t5 += ((u8*)u)[0x126];
    u8 t6 = ((u8*)p)[0x30];
    t6 += ((u8*)u)[0x127];
    u8 t7 = ((u8*)p)[0x31];
    t7 += ((u8*)u)[0x128];
    r.v[0] = t0;
    r.v[1] = t1;
    r.v[2] = t2;
    r.v[3] = t3;
    r.v[4] = t4;
    r.v[5] = t5;
    r.v[6] = t6;
    r.v[7] = t7;
    return r;
}

#pragma push
#pragma use_lmw_stmw on
void fn_8006D380(BU* u, u8* d);
#pragma pop

extern void fn_80030D98(BU*);
extern void fn_80128558(Unit*, s8);
extern s8 fn_801284C4(BU*);
void fn_8006DE18(Battle* b);

void fn_8006DE7C(BU* u);


extern char lbl_803622BC[];
extern void fn_8023F1A0(const char*, int);
extern void fn_801C6EAC(const char*, const char*, char*);
extern void fn_800068A0(void*, const char*);
extern void fn_80006A2C(void*);
extern void* lbl_804CB580;
extern void* lbl_804CB584;
extern void* lbl_804CB588;
extern void* lbl_804CB58C;
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E720(f32);
extern void fn_8007E174(int, int);
void fn_8006DECC(void);

void fn_8006DF48(void);

void fn_8006DFC4(void);

void fn_8006E030(f32 v);

void fn_8006E068(void);

}

#pragma use_lmw_stmw on
/* ---- from rO_80065D64/wip/near2.cpp ---- */
extern "C" {


/* Control flow right, 264 position differences from the GrowOf block at the start (one word extra). Same
   unsolved schedule as fn_8006D380: the original delays the sums of 0x123, 0x126, 0x127 and 0x128. */
void fn_8006D790(BU* u, u8* d) {
    fn_8006D380(u, d);
    Grow t = GrowOf(u);
    u8 a0 = *(u8*)&t;
    u8 a1 = t.v[1];
    u8 a2 = t.v[2];
    u8 a3 = t.v[3];
    u8 a4 = t.v[4];
    u8 a5 = t.v[5];
    u8 a6 = t.v[6];
    u8 a7 = t.v[7];
    int n = 0;
    int i;
    for (i = 0; i < 8; i++) {
        if ((s8)GetD(d, i)) {
            n++;
        }
    }
    if (n > 3) {
        for (; n > 3; n--) {
            int best = 0x7F;
            int idx = -1;
            for (int j = 0; j < 8; j++) {
                if ((s8)GetD(d, j)) {
                    int i = j;
                    if (PICK < best) {
                        best = PICK;
                        idx = j;
                    }
                }
            }
            SetD(d, idx, 0);
        }
    } else if (n < 3) {
        for (; n < 3; n++) {
            int best = -0x80;
            int idx = -1;
            for (int j = 0; j < 8; j++) {
                if (!(s8)GetD(d, j)) {
                    int i = j;
                    if (best < PICK && (s16)fn_80122E8C(u, j) < (s16)fn_80122F14(u, j)) {
                        best = PICK;
                        idx = j;
                    }
                }
            }
            if (idx < 0) {
                break;
            }
            SetD(d, idx, 1);
        }
    }
}
}
