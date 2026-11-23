/* r20: `regs` (check_regs.py; 5 words, volatile registers of one load). fn_8011D580: unit constructor.
   The `addi r3,r3,0x32; lhax` puzzle of rounds 14 to 19 is a pointer to data member: the person's weapon-rank row is
   read as `(p->*m)[i]` with `s16 (PF::*m)[12] = &PF::w` (inline Q10 below). Every plain spelling folds +0x32 into the
   `lha` displacement. With a `u32` index (Q14) the registers are the original's but the `lwz` of the person and the
   `clrlslwi` swap (`sched`, 1 word); with `int` the order is right and r3/r4/r0 rotate. `__ptmf_scall` is fn_8028C178
   (not in symbols.txt, not reference-checked). Earlier experiment inlines above the function are unused. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
struct Sl { u8* item; u8 uses; u8 flags; void clear(); };
typedef void (Sl::*SlMF)();
struct SlFn { SlMF f; SlFn() {} SlFn(SlMF x) : f(x) {} };
extern SlMF lbl_80385CE0;
static inline SlFn SlEach(Sl* a, Sl* e, SlFn f) {
    while (a != e) {
        (a->*f.f)();
        a++;
    }
    return f;
}
struct UDef {
    u8 pad0[2];
    u16 fl;       /* 2 */
    void* pid;    /* 4 */
    void* jid;    /* 8 */
    u8 padC;
    u8 gauge;     /* d */
    s8 x;         /* e */
    s8 y;         /* f */
    u8 pad10[0x58 - 0x10];
    u8 st[8];     /* 58 */
    s8 s60;       /* 60 */
    u8 pad61[3];
    u8 s64;       /* 64 */
    u8 s65;       /* 65 */
};
struct St8 { u8 v[8]; St8() { v[7] = 0; v[6] = 0; v[5] = 0; v[4] = 0; v[3] = 0; v[2] = 0; v[1] = 0; v[0] = 0; } };
struct Gr { u8 pad0[2]; s8 lv; u8 mask; u8 st[8]; u8 kind[8]; };
extern void* fn_8024BCA0(void);
extern void* fn_80079150(int);
extern void* fn_8026D01C(void*, void*);
extern void fn_80079210(void*);
extern void* fn_8010B1D8(void*);
extern void* fn_8010B200(void*);
extern void fn_80109078(void*);
extern int fn_80089C88(int);
extern int fn_80089C1C(void);
extern f32 fn_801075A4(Unit*, int);
extern void fn_80126EB0(Unit*, int, int);
extern void fn_8011B958(void*, void*);
extern void* fn_8010B6D8(UDef*, int);
extern u32 fn_8010B75C(UDef*, int);
extern void fn_8011AEA0(void*, void*, int, u8);
extern int fn_8011B77C(void*, void*);
extern void fn_801283F8(Unit*);
extern void fn_80128558(Unit*, int);
extern void fn_8011F70C(Unit*);
extern void fn_8011F9C4(Unit*);
extern void fn_801282F0(Unit*, void*);
extern Gr* fn_8026D02C(void*, char*);
extern char lbl_80369010[];
extern u8 fn_8012246C(Unit*);
extern u8 fn_801224BC(Unit*);
extern u8 fn_8012250C(Unit*);
extern u8 fn_8012255C(Unit*);
extern u8 fn_801225AC(Unit*);
extern u8 fn_801225FC(Unit*);
extern u8 fn_8012264C(Unit*);
extern u8 fn_8012269C(Unit*);
extern void fn_8012C448(Unit*);
extern s16 fn_8012C250(Unit*, u8);
extern s16 fn_8012C0A8(Unit*, u8, int);
extern void fn_80128D70(Unit*);
extern void fn_80111B34(Inv*);
extern void fn_80111C24(Inv*, int);
extern void* fn_8010B528(UDef*, int);
extern u32 fn_8010B5AC(UDef*, int);
extern u8 lbl_803CAB38[];
extern void fn_80110BFC(Inv*, void*);
extern void fn_8012AA8C(Unit*);
extern int fn_8012A9A4(Unit*);
extern void fn_8012A0F4(Unit*, Inv*);
extern void fn_8011FC88(Unit*);
extern void fn_8012ECF8(Unit*);
extern void fn_80129CB8(Unit*, int);
extern s16 fn_801237EC(Unit*);
extern void fn_80126D9C(Unit*, int);
extern int fn_8012CA88(Unit*);
extern void fn_801288D4(Unit*);
extern void fn_800F64D4(Unit*);
extern void fn_80129214(Unit*, UDef*);
extern u8 fn_80089CF4(int, int);
extern void* fn_8024BC94(void);
extern void fn_80245104(void*, void*);
extern void fn_800F3F38(Unit*, u8);
extern void fn_8011E048(Unit*, UDef*);
extern void fn_8011A36C(void*);
extern u8 fn_80126B0C(Unit*);
extern void fn_80126B80(Unit*, int);
extern void* lbl_804CA4E8;
extern f32 lbl_804CDCD8;
extern void* lbl_804CA4EC;
extern void* lbl_804CA4F8;
extern void* lbl_804CA594;
#define HASK(u, k) fn_8011B77C((u)->skills, k)
static inline BOOL CanPromote(Unit* u) {
    if (HASK(u, lbl_804CA4E8)) return 0;
    if (HASK(u, lbl_804CA594)) return 0;
    return u->job->p14 != 0;
}

#define RKF(n) *(volatile s16*)&u->s2D4[n] = *(s16*)((u8*)*(Job* volatile*)&u->job + 0xb8 + (n) * 2);
#define KIND(r, off) { s16* w = (s16*)(u->s2D4); u32 q = kq; int ix = (u8)q * 2; *(s16*)((u8*)w + ix) = fn_8012C0A8(u, (u8)q, (s16)(*(s16*)((u8*)w + ix) + off)); }
static inline void RkS(Unit* u, int n) { u->s2D4[n] = ((s16*)((u8*)u->job + 0xb8))[n]; }
static inline void RkT(Unit* u, Job* j, int n) { u->s2D4[n] = ((s16*)((u8*)j + 0xb8))[n]; }
static inline s16 Rk2(Unit* u, int i) { return ((s16*)((u8*)u->person + 0x32))[i]; }
static inline s16 Rk3(s16* q, int i) { return q[i]; }
static inline s16 Rk4(s16* const& q, int i) { return q[i]; }
struct PR { u8 pad[0x32]; s16 w32[12]; };
static inline s16 PRG(PR* p, u8 i) { return p->w32[i]; }
static inline s16 PRH(s16* q, u8 i) { return q[i]; }
static inline s16 PRI(s16* const& q, u8 i) { return q[i]; }
static inline s16 PRI2(Person* p, u8 i) { s16* q = (s16*)((u8*)p + 0x32); return *(q + i); }
static inline s16* A0(Person* p) { return (s16*)((u8*)p + 0x32); }
static inline s16 A1(Person* p, int i) { s16* q = A0(p); return q[i]; }
static inline s16 A2(s16* q, int o) { return *(s16*)((u8*)q + o); }
static inline s16 A3(u8* const& q, int o) { return *(s16*)(q + o); }
struct RK { s16 a[12]; s16 get(u8 i) const { return a[i]; } s16 get2(int i) const { return a[(u8)i]; } s16 get3(int o) const { return *(s16*)((u8*)a + o); } };
struct PR2 { u8 pad[0x32]; RK rk; };
static inline s16 Gk(const RK& r, u8 i) { return r.a[i]; }
static inline s16 Gl(const s16* a, u8 i) { return a[i]; }
struct KS { s16 v; };
struct PR3 { u8 pad[0x32]; KS k[12]; };
static inline s16 AA2(const KS* k, int i) { return k[i].v; }
static inline s16 AA3(const KS (&k)[12], u8 i) { return k[i].v; }
static inline s16 AA4(const KS (*k)[12], u8 i) { return (*k)[i].v; }
struct GP { void* p; GP() : p(0) {} ~GP() { fn_80079210(p); }
  void reset(void* q) { if (p != q) { fn_80079210(p); p = q; } }
};
struct PF { u8 pad[0x32]; s16 w[12]; };
typedef s16 Row12[12];
static inline s16 Q6(PF* p, u8 i) { s16 PF::* m = (s16 PF::*)&PF::w; return (&(p->*m))[i]; }
static inline s16 Q8(u8 i, PF* p) { s16 PF::* m = (s16 PF::*)&PF::w; return (&(p->*m))[i]; }
static inline s16 Q9(PF* p, u8 i) { Row12 PF::* m = &PF::w; return (p->*m)[i]; }
static inline s16 Q10(PF* p, int i) { Row12 PF::* m = &PF::w; return (p->*m)[i]; }
void fn_8011D580(Unit* u, UDef* d) {
    /*P*/
    int i1;
    int* tp;
    u32 b2;
    u32 f3;
    s16* rk;
    int n;
    void* p;
    void* it1;
    int i3;
    Gr* g;
    int i2;
    void* it3;
    Sl* se;
    Sl* sp;
/*E*/
    Inv inv;
    u8* o = (u8*)fn_8024BCA0();
    GP gg;
    {
        if (*(u32*)(o + 0x40) & 1) {
            p = fn_80079150(8);
            if (p) p = fn_8026D01C(p, o + 0x70);
            gg.reset(p);
        }
    }
    u->person = (Person*)fn_8010B1D8(d->pid);
    u->ff = 0;
    u->exp115 = 0;
    u->u116 = 0;
    u->flags = 0;
    fn_80109078(u->skills110);
    u->actor = 0;
    {
        SlFn sg(lbl_80385CE0);
        sp = (Sl*)u->skills;
        se = sp + 18;
        SlEach(sp, se, sg);
    }
    *(u16*)((u8*)u + 0x382) = 0;
    *(u16*)((u8*)u + 0x384) = 0;
    *(u16*)((u8*)u + 0x386) = 0;
    *(u16*)((u8*)u + 0x388) = 0;
    *(u16*)((u8*)u + 0x38a) = 0;
    *(u16*)((u8*)u + 0x38c) = 0;
    *((u8*)u + 0x38e) = 0;
    *((u8*)u + 0x38f) = 0;
    {
        int a = (s8)((u8*)u->person)[0xe4];
        if (a < 0) a = fn_80089C88(8);
        *((u8*)u + 0x378) = a;
    }
    {
        s8 a = ((u8*)u->person)[0xe3];
        f32 v;
        if (a < 0) v = (f32)fn_80089C1C() / 6.0f; else v = a;
        *((u8*)u + 0x379) = (int)v;
    }
    *(u16*)((u8*)u + 0x37a) = (u8)(int)fn_801075A4(u, (s8)((u8*)u->person)[0xe5]);
    *(u16*)((u8*)u + 0x37c) = 0;
    if (d->jid == 0) {
        u->job = (Job*)fn_8010B200(*(void**)((u8*)u->person + 0x14));
    } else {
        u->job = (Job*)fn_8010B200(d->jid);
    }
    fn_80126EB0(u, d->x, (s8)*(u8*)&d->y);
    fn_8011B958(u->skills, (u8*)u->person + 0x4c);
    fn_8011B958(u->skills, (u8*)u->job + 0x24);
    for (i1 = 0; i1 < 5; i1++) {
        u32 f;
        it1 = fn_8010B6D8(d, i1);
        f = fn_8010B75C(d, i1);
        if (it1) {
            u8 c = 0;
            if (f & 1) c |= 1;
            if (f & 2) c |= 2;
            fn_8011AEA0(u->skills, it1, 2, c);
        }
    }
    if (u->job != fn_8010B200(*(void**)((u8*)u->person + 0x14)) || d->gauge > ((s8*)u->person)[0x1e]) {
        int gv = d->gauge;
        if (gv > 20 && !HASK(u, lbl_804CA4E8)) gv = 20;
        u->gauge = gv;
    } else {
        u->gauge = ((s8*)u->person)[0x1e];
    }
    fn_801283F8(u);
    fn_80128558(u, (s8)*(u8*)&d->s60);
    if (d->fl & 1) fn_8011F70C(u);
    if (d->fl & 0x400) fn_8011F9C4(u);
    {
        St8 s;
        s.v[0] = d->st[0];
        s.v[1] = d->st[1];
        s.v[2] = d->st[2];
        s.v[3] = d->st[3];
        s.v[4] = d->st[4];
        s.v[5] = d->st[5];
        s.v[6] = d->st[6];
        s.v[7] = d->st[7];
        fn_801282F0(u, &s);
    }
    if (gg.p && fn_8026D02C(gg.p, u->person->name)) {
        St8 s;
        g = fn_8026D02C(gg.p, u->person->name);
        if (u->person != fn_8010B1D8(lbl_80369010)) {
            if (g->lv >= 40) {
                if (g->mask & 1) s.v[0] = 5;
                if (g->mask & 2) s.v[1] = 2;
                if (g->mask & 4) s.v[2] = 2;
                if (g->mask & 8) s.v[3] = 2;
                if (g->mask & 0x10) s.v[4] = 2;
                if (g->mask & 0x20) s.v[5] = 2;
                if (g->mask & 0x40) s.v[6] = 2;
                if (g->mask & 0x80) s.v[7] = 2;
            }
        } else if (g->lv >= 20) {
            s.v[0] = g->st[0] - fn_8012246C(u);
            s.v[1] = g->st[1] - fn_801224BC(u);
            s.v[2] = g->st[2] - fn_8012250C(u);
            s.v[3] = g->st[3] - fn_8012255C(u);
            s.v[4] = g->st[4] - fn_801225AC(u);
            s.v[5] = g->st[5] - fn_801225FC(u);
            s.v[6] = g->st[6] - fn_8012264C(u);
            s.v[7] = g->st[7] - fn_8012269C(u);
        }
        fn_801282F0(u, &s);
    }
    RKF(0) RKF(1) RKF(2) RKF(3) RKF(4) RKF(5) RKF(6) RKF(7) RKF(8) RKF(9) RKF(10) RKF(11)
    fn_8012C448(u);
    for (i2 = 0; (u32)i2 < 12; i2++) {
        if (fn_8012C250(u, i2)) {
            s16 v = Q10((PF*)u->person, (u8)i2);
            if (v) u->s2D4[(u8)i2] = v;
        }
    }
    if ((d->fl & 0x401) && HASK(u, lbl_804CA4E8)) {
        if (u->gauge >= 30) {
            u->s2D4[5] = 0x14b;
        } else {
            BOOL m = 0;
            if (u->gauge >= 15 && u->gauge < 30) m = 1;
            if (m && u->s2D4[5] < 0xfb) u->s2D4[5] = 0xfb;
        }
    }
    if (gg.p && fn_8026D02C(gg.p, u->person->name)) {
        g = fn_8026D02C(gg.p, u->person->name);
        int tb[8] = {0, 1, 2, 3, 6, 7, 8, 0xb};
        rk = u->s2D4;
        tp = tb;
        for (n = 0; n < 8; n++, tp++) {
            int kq = *tp;
            switch (g->kind[n]) {
            case 'C':
                rk[(u8)kq] = fn_8012C0A8(u, kq, (s16)(rk[(u8)kq] + 0x28));
                break;
            case 'B':
                rk[(u8)kq] = fn_8012C0A8(u, kq, (s16)(rk[(u8)kq] + 0x50));
                break;
            case 'A':
                rk[(u8)kq] = fn_8012C0A8(u, kq, (s16)(rk[(u8)kq] + 0x78));
                break;
            case 'S':
                rk[(u8)kq] = fn_8012C0A8(u, kq, (s16)(rk[(u8)kq] + 0xa0));
                break;
            }
        }
    }
    fn_80128D70(u);
    fn_80111B34(&inv);
    for (i3 = 0; i3 < 7; i3++) {
        it3 = fn_8010B528(d, i3);
        f3 = fn_8010B5AC(d, i3);
        if (it3 && (!(b2 = f3 & 2) || lbl_803CAB38[0x9f] != 1)) {
            fn_80110BFC(&inv, it3);
            if (f3 & 1) {
                if (b2) {
                    fn_8012AA8C(u);
                    inv.bit40 = 1;
                } else if (!fn_8012A9A4(u)) {
                    inv.bit40 = 1;
                }
            }
            if (f3 & 4) inv.bit4 = 1;
            if (HASK(u, lbl_804CA4F8) && (*(u32*)(inv.item + 0x3c) & 1)) inv.bit4 = 1;
            fn_8012A0F4(u, &inv);
        }
    }
    fn_8011FC88(u);
    fn_8012ECF8(u);
    fn_80129CB8(u, -1);
    fn_80126D9C(u, fn_801237EC(u));
    if (fn_8012CA88(u) && !HASK(u, lbl_804CA4EC)) fn_801288D4(u);
    fn_800F64D4(u);
    fn_80129214(u, d);
    {
        u8 a = d->s64;
        if ((s8)a != -1) {
            u->u118 = a;
        } else {
            a = ((u8*)u->person)[0xe1];
            if ((s8)a != -1) u->u118 = a;
            else u->u118 = fn_80089CF4(1, 5);
        }
    }
    fn_80245104(fn_8024BC94(), u->person);
    u->flags10C |= 0x80000;
    fn_800F3F38(u, d->s65);
    fn_8011E048(u, d);
    fn_8011A36C(u->skills);
    {
        int m = (((u8*)u->job)[0xfb] - 1) * 100;
        s8 c;
        if (CanPromote(u)) m += 100;
        c = u->gauge;
        {int e = fn_80126B0C(u); if (m - (e + (c - 1) * 100) <= 0) {
            fn_80126B80(u, 0xff);
        }}
    }
    fn_80111C24(&inv, -1);
}
}
