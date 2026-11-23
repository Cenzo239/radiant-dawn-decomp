/* fn_80175C3C: functionally equal (regs level per tools/check_regs.py; registers differ from the original).  */
/* symcheck: (a) block 6: temporaries in other volatile registers, all four stores equal; leftover r3 at blr of a void function (clean with --ret=none). */
/* AI: skill item actions, retreat, phase helpers. */
#include "game/rQ_80163178/common.h"
struct WW { u32 v; };
class Pad5B8 {
public:
    virtual void v8(); virtual void vc(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual u32 v48();
};
struct B4 { int x; };
class Cl4 : public B4 {
public:
    virtual void v8(); virtual void vc(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void vc8(); virtual void vcc();
};
struct Tm {
    u8 pad[0x34];
    int d;    /* 0x34 */
    int c;    /* 0x38 */
    u32 a;    /* 0x3C */
    u32 b;    /* 0x40 */
    int e;    /* 0x44 */
    int f;    /* 0x48 */
};
extern "C" {
extern Pad5B8* lbl_804CB5B8;
extern u8 lbl_803CB770[];
int fn_8011EE3C(Unit*, Unit*);
void fn_801151BC(Map*, Unit*);
s16 fn_80115CD8(Map*, int, int);
int fn_80116DB8(Map*, int, int, int, int);
void* fn_80066130(u8*, int, int, int);
void fn_800CFC50(ListHdr*, int, int, u8, int);
void fn_80165F94(Unit*, int, int);
void fn_8016FEE8(Unit*, int, int, int, int, int, int, int, u8, int);
extern ListHdr lbl_803E7320[];
extern u8 lbl_803CAB38[];
extern u8 lbl_80387308[];
extern u8 lbl_80387338[];
extern u8 lbl_803EC898_[];
extern u32 lbl_804CA514;
struct SkA { char* name; u8* item; int (*func)(Unit*, int); };
extern SkA lbl_80387380[];
extern SkillAct lbl_80387690[];
int fn_8012BC2C(Unit*, u8*);
int fn_8012BB48(Unit*, u8*);
u8 fn_801718FC(u8*);
int fn_8012C794(Unit*, int);
int fn_8011B77C(void*, u32);
int fn_80171988(Unit*, int, s16*, s16*);
int fn_801719A4(Unit*, int, s16*, s16*);
int fn_8016D11C(Unit*);
void fn_8016F94C(Unit*, int, int, int, u16, int, int, int);
s8* fn_800CFD18(ListHdr*, int);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
int fn_80165240(Unit*, s8);
u8* fn_80158C98(void);
int fn_800A05B0(int, int, int);
int fn_80170C48(int, int, int, int);
u32 fn_80079150(int);
void fn_80079210(u32);
void fn_8013BE90(int, int);
void fn_8013BED8(void);
u8* fn_80116294(Map*, u32, int, int, int);
int fn_8016510C(Unit*, u8*, s16*, s16*);
void fn_80045120(AiAct*, Unit*);
void fn_80168BC0(void*);
extern void* lbl_803878F0[][2];
int fn_801D09F0(void);
s8 fn_80244CDC(void);
void fn_800068EC(void*, void*, int);
void fn_8033111C(int);
void fn_8030818C(int, int);
void fn_80304C74(int*, int);
void* fn_802356B4(void);
void fn_80304EE4(void*, int);
void fn_80303CB4(void);
void fn_80330F9C(void);
void fn_80330018(void);

int fn_801658E4(Unit* u, s8 x, s8 y);

u8 fn_80165528(Unit* u, s8 a);

static inline SkA* FindSk(Unit* u, u8* it) {
    if (fn_8012BC2C(u, it)) {
        SkA* e;
        for (e = lbl_80387380; e->item; e++) {
            if (it == e->item && e->func) {
                return e;
            }
        }
    }
    return 0;
}

static inline u8 Sk1(Unit* u) {
    if (!fn_8011B77C(u->skills, lbl_804CA514)) {
        return 0;
    } else {
        u32 old = *(volatile u32*)&u->w3B4;
        u->w3B4 |= 0x30000000;
        fn_80165240(u, -1);
        u->w3B4 = old;
        return lbl_804183F0.done;
    }
}
static inline void Lp1(Unit* u) {
    int i;
    Inv* p = u->inv;
    u8* it;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8012BC2C(u, p->item) && fn_801718FC(p->item) == 1 && i == fn_8012C794(u, 1)) {
            SkA* e;
            it = p->item;
            e = FindSk(u, it);
            if (e && e->func(u, i)) break;
        }
    }
}
u8 fn_80164F90(Unit* u);
static inline u8 Sk0(Unit* u) {
    s16 y, x;
    if (!fn_8011B77C(u->skills, lbl_804CA514)) {
        return 0;
    } else {
        u32 old = *(volatile u32*)&u->w3B4;
        u->w3B4 |= 0x30000000;
        if (!fn_80165240(u, -1) && (u->w3B4 & 0x10000000) && fn_80171988(u, 0, &x, &y)) {
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), 0, 0, -1);
            if (lbl_804183F0.done && x == lbl_803CA870.x && y == lbl_803CA870.y) {
                s8 p0 = *fn_800CFD18(lbl_803E7320, 0);
                u8* q = (u8*)fn_800CFD18(lbl_803E7320, 0);
                fn_80160610(0xB, lbl_803CA870.x, lbl_803CA870.y, lbl_803CA870.unit2, p0, (s8)q[1], -1, 0, 0);
                lbl_804183F0.res[1] = 0xE;
            }
        }
        u->w3B4 = old;
        return lbl_804183F0.done;
    }
}
u8 fn_80164D18(Unit* u);
void fn_801729C0(FF* f, Unit* v);
void fn_80175C3C(Tm* t);
void fn_80175D38(Tm* t);
void fn_801705A8(Unit* u, int a, int b, int c, int d, int e, int f, int g, u8 h, int r);

int fn_8017517C(void* a, Cl4* c);
void fn_80174F90(void* p);
void fn_801751C0(Cl4* c);

void fn_8017534C(u8* p);
}


/* ---- fn_80175C3C ---- */
void fn_80175C3C(Tm* t) {
    if (1140.0f <= (f32)++t->a || (lbl_804CB5B8->v48() & 0xFFF0)) {
        t->a = 0;
        fn_80083B78(t);
    } else if (300.0f <= (f32)++t->b) {
        t->b = 0;
        t->c = t->d == 0;
        t->f = t->e;
    }
}
