/* fn_80170664 (0xD4): functionally equal at `sched` level (tools/check_regs.py, round 20). AI: is `v` within
 * reach of `u` with weapon `p` (distance <= weapon range + both units' reach bonus; names guessed).
 * The declarations are those of fn_8016D070.cpp (bodies stripped by tools/equiv/mkself.py). Writing the function
 * as three inlines (Dist, Rng, Reach) gave the original's four saved registers; the plain form in wip/near.cpp
 * uses five. Moved instructions (dd.py): `mr r31,r4` one slot later in the prologue; in the tail one `add` of the
 * commutative sum and the `srwi` of the signed compare idiom are interleaved differently with the register restores.
 */
/* AI: small predicates and map helpers. */
#include "game/rQ_80163178/types.h"
#pragma use_lmw_stmw on
#define ABS(a) ((a) < 0 ? -(a) : (a))

class Filter {
public:
    virtual int check(Unit*);
};

struct ListHdr { int n; };
struct Side { Unit* head; Unit* tail; int n; };
struct B0 { int x; };
class Cls : public B0 {
public:
    virtual void v8(); virtual void vc(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual s16 v48(); virtual void v4c(); virtual s16 v50();
};
struct FF {
    void* vt;
    Unit* u;
    Filter* f;
    u8 x;
    u8 y;
};
struct F3 {
    void* vt;
    void* a;
    void* b;
    F3(void* v, void* x, void* y) {
        b = y;
        a = x;
        vt = v;
    }
};

extern "C" Unit* lbl_804CB810;
static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
extern "C" int fn_8010E398(void*, void*);
static inline BOOL Same0(Unit* a, Unit* b) {
    return (u8)fn_8010E398(a->team, b->team) == 0;
}
extern "C" {
extern ListHdr lbl_803E7320[];
extern Side* lbl_804CB814;
extern s16 lbl_8036B278[];
extern u8 lbl_80387790[];
extern u8 lbl_803CB770[];
extern u32 lbl_804CA500;
extern u32 lbl_804CA520;
u8* fn_80066130(u8*, int, int, int);
u8** fn_80077064(u8*);
int fn_8011F0E0(Unit*, Inv*);
int fn_80291188(const char*, u8*);
void fn_80116658(Map*, int, int);
int fn_80116A68(Map*, s8*, s8*, int, u8*);
extern Unit* lbl_804CB810;
extern u8 lbl_803CAB38[];
extern u8 lbl_8036B268[];
extern u8 lbl_80387800[];
extern u8 lbl_803877C0[];
extern u8 lbl_803877B0[];
extern u8 lbl_803877A0[];
extern u8 lbl_80387878[];
extern u8 lbl_80387928[];
extern u8 lbl_803879D4[];
extern void* lbl_803878F0[][2];
extern u32 lbl_804CA5C0;
int fn_800A05B0(int, int, int);
void fn_800CFB34(ListHdr*);
void fn_80039708(void*, int, int);
void fn_800398E0(void*, int);
void fn_800392FC(void*, int, int);
void fn_800394E0(void*, int, int);
void fn_800CFC50(ListHdr*, int, int, u8, int);
int fn_800CFCB4(ListHdr*, int, int);
int fn_8012BA20(Unit*, void*);
u8 fn_80110DA8(Inv*);
int fn_8010E398(void*, void*);
int fn_8028DB44(int);
u8 fn_801107C0(u8*, Unit*);
u8 fn_801107A0(u8*, Unit*);
u8 fn_801107B8(u8*, Unit*);
u8 fn_80110880(u8*, Unit*);
s8 fn_8012408C(Unit*);
void fn_80170738(Unit*, u8, u8);
void fn_80170998(Unit*, u8, u8);
int fn_8012BB48(Unit*, void*);
void fn_801151BC(Map*, Unit*);
int fn_801D09F0(void);
s8 fn_80244CDC(void);
void fn_8023F1A0(void*, int);
int fn_8023F880(void*);
int fn_80168BC0(void* p);
int fn_8011B77C(void*, u32);
void fn_80114888(Map*, int);
void fn_80114B44(Map*, int, int);
void fn_80165F94(Unit*, int, int);
u32 fn_8016CDEC(Unit*, void*);
u32 fn_8016D070(void);

u32 fn_8016D090(void);

u32 fn_8016D0B0(Unit* u);

int fn_8016D11C(Unit* u);

int fn_8016D144(Unit* u);

u32 fn_8016D1DC(s8 x, s8 y, int k, int a);

int fn_8017062C(int x, int y, int x2, int y2, int r);

void fn_80170910(Unit* u, Inv* p);

void fn_80170B70(Unit* u, Inv* p);

int fn_80170D64(Unit* u);

int fn_80170E60(Unit* u);

void fn_8017244C(void* a, void* b);


void fn_8016CD04_(void);
void fn_80174FAC(void);

void fn_8017504C(void* parent);

void fn_80175294(void);

void fn_801752E4(void* p);

void fn_80175DC0(void* p);

void fn_80175E04(void* p);

u32 fn_8016CD04(Unit* u, void* f);


u32 fn_80172494_(void);
void fn_8016CB18(void* a, void* b);

static inline void fn_8017244C_(void* p, void* vt, Unit* u) {
    struct G { void* vt; Unit* u; };
    ((G*)p)->vt = vt;
    ((G*)p)->u = u;
}
void fn_80172494(Unit* u, int x, int y);
void fn_8017252C(Unit* u, u8 k, s8 x, s8 y);

#pragma use_lmw_stmw off
int fn_80170664(Unit* u, Unit* v, Inv* p);
#pragma use_lmw_stmw on

u16 fn_80170C48(int x, int y, int x2, int y2);

int fn_80171378(s16 x, s16 y, Filter* f);

int fn_801725A0(Unit* u);

s32 fn_80172664(Unit* u, s8* ox, s8* oy);

void fn_80172D7C(void* a, s8 x, s8 y);

void fn_8016CFFC(FF* f, Unit* v);

void fn_8017505C(FF* f, Unit* v);

static inline int TblFind(Unit* u, Inv* p) {
    u8** t = fn_80077064(lbl_8036B268);
    int i;
    if (!fn_8011F0E0(u, p)) {
        return -1;
    }
    for (i = 0; *t; t++, i++) {
        char* s = p->item ? *(char**)p->item : 0;
        if (!fn_80291188(s, *t)) {
            return i;
        }
    }
    return -1;
}
BOOL fn_8016CB60(Unit* u, Inv* p);

int fn_8016CC18(Unit* u, Unit* v, int* out);

s16 fn_801751D8(Cls* c);

}

/* ---- from rQ_80163178/wip/near.cpp ---- */
extern "C" {


#pragma use_lmw_stmw off
static inline int Dist(Unit* u, Unit* v) { int dy = fn_8028DB44(u->y - v->y); return fn_8028DB44(u->x - v->x) + dy; }
static inline int Rng(Inv* p, Unit* u) { return p->item ? fn_801107C0(p->item, u) : 0; }
static inline int Reach(Unit* u, Unit* v, int r) { int b = fn_8012408C(v); return r + (fn_8012408C(u) + b); }
int fn_80170664(Unit* u, Unit* v, Inv* p) {
    int d = Dist(u, v);
    return d <= Reach(u, v, Rng(p, u));
}
}
