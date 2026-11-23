/* fn_80047DCC (round 17 near miss, 103 of 168 by position): structure right except the original never folds
 * s->buf30[0x7f] into a 0xaf(r31) store and keeps 'addi r3,r31,0' before reading s->pair.unit2; ours folds both and
 * reads s->unit through lbl@l(r4). Reference parameters, accessors and opt pragmas did not change it. */
#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
extern "C" {
extern GameState lbl_803CAB38;
extern u8 lbl_803EC898[];
extern u8 lbl_803CB770[];
extern u8* lbl_804CB810;
extern Unit** lbl_804CB814;
extern int lbl_804CA0A0;
extern void* lbl_804CA500;
extern void* lbl_804CA58C;
extern char lbl_8037AE18[];
extern char lbl_8037DB60[];
extern char lbl_803CA9A0[];
extern char lbl_804CA0B0[8];
extern char lbl_804CA0B8[8];
extern char lbl_804CA0C0[8];
extern char* lbl_8037AB10[];
extern u8 lbl_803E9000[];
void* memset(void*, int, int);
char* strcpy(char*, const char*);
void fn_80126EB0(Unit*, int, int);
void fn_8010354C(Unit*, Unit*, int, int, void*);
void fn_800F39DC(Unit*);
void* fn_80108A20(void*, Unit*, int);
int fn_8011B77C(void*, void*);
void fn_8011EED4(Unit*, Unit*, int, void*, void*);
void* fn_80066130(void*, int, int, int);
void* fn_80081194(void*, void*);
int* fn_80077064(const char*);
int fn_8012E9B4(Unit*, Unit*);
char* fn_80291314(const char*, int);
u8* fn_8024BC94(void);
u8* fn_8024BCA0(void);
int fn_80290D04(char*, int, const char*, ...);
void fn_8023F1A0(char*, int);
void fn_80250D64(int, f32, f32);
int fn_8023F880(char*);
void* fn_80075FB4(const char*, int);
void fn_80083B78(void*);
void fn_801030B8(Unit*, int, int, int, int, int);
Unit* fn_800CFB0C(void*);
void fn_8010301C(Unit*, Unit*, int, int, int);
void fn_80026C44(void*, Unit*, Unit*);
void fn_8002C53C(void*, int);
void fn_8002742C(void*, int);
int fn_80060914(void*);
void fn_8010E770(Unit**);
void fn_800610A4(void*);
void fn_8011B430(void*, void*);
void fn_8011A36C(void*);
void fn_8012D620(void);
void fn_80068A58(void);
void fn_8010E41C(char*, int);
void fn_80122460(Unit*);
void* fn_80062A9C(void*, u32 k);
u32* fn_80060728(void*);
void fn_801657DC(void*);
void fn_80165764(void*);
void fn_801657A0(void*);
void fn_80083DC4(void*, int);
int fn_8011799C(void*, int, int);
Unit* fn_8012D2B0(int k);
Unit* fn_8012D280(u8);
void fn_800620A8(f32, f32, void*);
int fn_8006041C(void*);
void fn_80060528(void*, int, u8*, u16*, u32*);
void* fn_80287358(void);
void fn_80245614(u8*, u8*, u32, u32, int, u8, u16, int, s64);
void* fn_801059B0(void);
int fn_80105158(void*);
void fn_801053EC(void*, u8*);
void fn_80105704(void*);
void fn_8011E300(Unit*, int, int, int);
void fn_80109078(void*);
s16 fn_801237EC(Unit*);
void fn_80126D9C(Unit*, int);
void fn_80128E14(Unit*, int);
void fn_801283F8(Unit*);
void fn_80060580(void*, u8);
void fn_802512C4(f32);
void fn_80250E38(int, f32, f32);
void fn_8025095C(f32, f32);
void fn_80250A08(f32, f32);


void fn_80046F80(void) {
    fn_800F39DC(lbl_803CA870.unit2);
    lbl_803CA870.action = 1;
    if ((s8)lbl_803CA870.f16 == 0) {
        lbl_803CA870.fd = 1;
    }
    fn_80108A20(lbl_803CA870.unit2->x110, lbl_803CA870.unit2, 1);
}

void fn_80046FE4(Act* q, void* proc, int n) {
    s8 x, y;
    u8* s;
    q->f18 = n;
    if (fn_8011B77C(q->u2->x12c, lbl_804CA500) == 0) {
        if (n >= 1) {
            fn_8011EED4(q->u1, q->u2, 1, &x, &y);
            if (fn_80066130(lbl_803CB770, x, (s8)*(u8*)&y, 9)) goto found;
        }
        if (n >= 2) {
            fn_8011EED4(q->u1, q->u2, 2, &x, &y);
            if (fn_80066130(lbl_803CB770, x, (s8)*(u8*)&y, 9)) goto found;
        }
    }
    fn_8011EED4(q->u1, q->u2, n, &x, &y);
    fn_8010354C(q->u1, q->u2, x, y, proc);
    return;
found:
    s = (u8*)fn_80081194(lbl_8037AE18, proc);
    *(f32*)(s + 0x30) = x;
    *(f32*)(s + 0x34) = y;
}

struct Yell {
    u8 pad[0x30];
    void* a;
    void* b;
    u8* base;
    int n;
};

static inline u8* cellY(Yell* p, s8 row) { int rr = row * 0xc; u8* r = p->base + rr * (p->n + 1); return r; }
static inline void yellPath(Yell* p, Unit* u, char* out) {
    char* c;
    s8 r = fn_8012E9B4(u, u);
    strcpy(lbl_803CA9A0, *(char**)(cellY(p, r) + 8));
    c = fn_80291314(lbl_803CA9A0, 0x2f);
    if (c == 0) c = fn_80291314(lbl_803CA9A0, 0x5c);
    if (c == 0) {
        s8 l = fn_8024BC94()[0x1bc8];
        fn_80290D04(out, 0x7f, lbl_804CA0B8, l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0, lbl_803CA9A0);
    } else {
        s8 l;
        *c++ = 0;
        l = fn_8024BC94()[0x1bc8];
        fn_80290D04(out, 0x7f, lbl_804CA0B0, lbl_803CA9A0, l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0, c);
    }
    out[0x7f] = 0;
}
static inline void yellName(Yell* p, Unit* u, char* out) {
    char* c;
    s8 r = fn_8012E9B4(u, u);
    strcpy(lbl_803CA9A0, *(char**)(cellY(p, r) + 8));
    c = fn_80291314(lbl_803CA9A0, 0x2f);
    if (c == 0) c = fn_80291314(lbl_803CA9A0, 0x5c);
    if (c == 0) {
        s8 l = fn_8024BC94()[0x1bc8];
        fn_80290D04(out, 0x7f, lbl_804CA0B8, l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0, lbl_803CA9A0);
    } else {
        s8 l;
        *c++ = 0;
        l = fn_8024BC94()[0x1bc8];
        fn_80290D04(out, 0x7f, lbl_804CA0B0, lbl_803CA9A0, l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0, c);
    }
}



void fn_80047B18(Yell* p) {
    char buf[0x80];
    int* d;
    p->a = 0;
    p->b = 0;
    d = fn_80077064(lbl_803619D0 + 0x97);
    p->base = (u8*)d;
    p->n = *d;
    p->base = (u8*)(d + 1);
    yellPath(p, lbl_803CA870.unit, buf);
    fn_8023F1A0(buf, 0x80);
    yellPath(p, lbl_803CA870.unit2, buf);
    fn_8023F1A0(buf, 0x80);
    fn_80250D64(6, 0.5f, 500.0f);
}

static inline void term(char* a) { a[0x7f] = 0; }
static inline void term2(char* const& a) { a[0x7f] = 0; }
static inline void yellPath2(Yell* p, Unit* u, char* out) { yellName(p, u, out); out[0x7f] = 0; }
static inline void yellPath3(Yell* p, Unit* u, char* const& out) { yellName(p, u, out); out[0x7f] = 0; }
struct UPair { Unit* unit; Unit* unit2; };
static inline UPair* pairOf(CmdState* s) { return (UPair*)&s->pair; }
static inline UPair& pairOf2(CmdState* s) { return *(UPair*)&s->pair; }
static inline CmdState* cmd() { return &lbl_803CA870; }
void fn_80047DCC(Yell* p) {
    CmdState* s = &lbl_803CA870;
    yellPath2(p, s->unit, s->buf30);
    char* a = s->buf30;
    yellPath2(p, s->pair.unit2, s->bufB0);
    char* b = s->bufB0;
    if (!fn_8023F880(a) || !fn_8023F880(b)) return;
    p->a = fn_80075FB4(a, 0x80);
    p->b = fn_80075FB4(b, 0x80);
    fn_80083B78(p);
}
}
