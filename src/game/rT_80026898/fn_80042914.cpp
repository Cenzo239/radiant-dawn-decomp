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
#if TARGET_PC
FE10_PROTO void fn_801030B8(Unit*, int, int, int, int, p32arg);
#else
void fn_801030B8(Unit*, int, int, int, int, int);
#endif
Unit* fn_800CFB0C(void*);
#if TARGET_PC
FE10_PROTO void fn_8010301C(Unit*, Unit*, int, int, p32arg);
#else
void fn_8010301C(Unit*, Unit*, int, int, int);
#endif
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

static inline void yellPath(Yell* p, Unit* u, char* out) {
    char* c;
    int k = (s8)fn_8012E9B4(u, u) * 0xc;
    strcpy(lbl_803CA9A0, *(char**)(p->base + k * (p->n + 1) + 8));
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



void fn_80042914(void* unused, u8* p) {
    void* c;
    Unit* u;
    fn_801030B8(lbl_803CA870.unit, *(s8*)(p + 0x3e), *(s8*)(p + 0x3f), 8, 0, 0);
    c = *(void**)(p + 0x40);
    if (c && fn_800CFB0C(c)) {
        fn_8010301C(fn_800CFB0C(c), lbl_803CA870.unit, 8, 0, 0);
        u = lbl_803CA870.unit;
        fn_80026C44(lbl_803C8E80, u, fn_800CFB0C(c));
        fn_8002C53C(lbl_803C8E80, (s8)lbl_803CA870.item);
        fn_8002742C(lbl_803C8E80, 0xf);
    }
}

static inline Unit* unitAt(u8 id) {
    return id ? (Unit*)(lbl_804CB810 + (id - 1) * 0x3f0) : 0;
}

static inline void markAll(u8* m, u8* q) {
    u8 c;
    while ((c = *q) != 0xff) {
        m[c] = 1;
        q++;
    }
}

void fn_80042AE8(void) {
    u8 m[0x10];
    int i;
    Unit* u;
    if (fn_80060914(&lbl_803CAB38) == 0) fn_8010E770(lbl_804CB814);
    fn_800610A4(&lbl_803CAB38);
    u8 t[8] = {0, 5, 6, 7, 8, 9, 0xa, 0xff};
    memset(m, (u8)lbl_804CA0A0, 0xb);
    markAll(m, t);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec && m[u->f4[8]]) {
            FLAGS(u) &= ~0x4400ULL;
            if (fn_8011B77C(u->x12c, lbl_804CA58C)) {
                fn_8011B430(u->x12c, lbl_804CA58C);
                fn_8011A36C(u->x12c);
            }
        }
    }
    {
        Unit* n;
        Unit* v;
        for (v = *lbl_804CB814; v;) {
            n = v->next;
            v->f38f++;
            v->f10c |= 0x400;
            v = n;
        }
    }
    fn_8012D620();
    fn_80068A58();
}


void fn_80043048(void* a) {
    if (lbl_803CAB38.sideOn[lbl_803CAB38.side] == 1) {
        fn_80081194(lbl_8037DB60, a);
    }
}

struct Group { Unit* head; u8 pad[8]; };




void fn_800434A0(void) {
    int total = 0;
    s64 sum = 0;
    int n = fn_8006041C(lbl_803CAB38.x554);
    int i;
    struct { u8 a[2]; u16 b; u32 c; } e;
    u16 v;
    void* s;
    u8* g;
    u8* f;
    for (i = 0; i < n; i++) {
        fn_80060528(lbl_803CAB38.x554, i, e.a, &e.b, &e.c);
        total += e.b;
        sum += e.c;
    }
    s = fn_80287358();
    v = s ? *(u16*)((u8*)s + 0x1c) : 0;
    g = fn_8024BC94();
    f = fn_8024BCA0();
    fn_80245614(g, f, *(u32*)(f + 0x10), *(u32*)(f + 0x14), (s8)f[0x35], f[0x34], v, total, sum);
}


void fn_8004361C(void) {
    u8 m[0x10];
    int i;
    Unit* u;
    lbl_803CAB38.fb4 = 0;
    lbl_803CAB38.fb0 = 0;
    lbl_803CAB38.fb8 = 0;
    lbl_803CAB38.fba = 0;
    lbl_803CAB38.fbc = 0;
    u8 t[8] = {0, 5, 6, 7, 8, 9, 0xa, 0xff};
    memset(m, (u8)lbl_804CA0A0, 0xb);
    markAll(m, t);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec && m[u->f4[8]]) {
            FLAGS(u) &= ~0x88000ULL;
            u->f386 = 0;
        }
    }
}


void fn_80043D6C(void) {
    fn_802512C4(500.0f);
    fn_80250D64(0, 1.0f, 500.0f);
    fn_80250E38(0, 1.0f, 500.0f);
    fn_8025095C(0.0f, 500.0f);
    fn_80250A08(0.0f, 500.0f);
    fn_80250D64(6, 1.0f, 250.0f);
    fn_80250E38(6, 1.0f, 250.0f);
}

void fn_8004357C(void) {
    if (fn_801059B0() && fn_80105158(lbl_803E9000) > 0) {
        int o;
        int i;
        for (i = 0, o = 0; i < fn_80105158(lbl_803E9000); i++) {
            fn_801053EC(fn_801059B0(), *(u8**)(lbl_803E9000 + 4) + o);
            o += 0x28;
        }
    }
    fn_80105704(lbl_803E9000);
}

static inline u8* section(int i) {
    switch (i) {
    case 0: return lbl_803C8E80;
    case 1: return lbl_803C8E80 + 0x4a0;
    case 2: return lbl_803C8E80 + 0x940;
    }
    return 0;
}

void fn_80044ED8(void* p) {
    int i;
    for (i = 0; i < 2; i++) {
        Unit* u = ((Unit*)section(i))->u3f0;
        if (u) (lbl_803EC898 + (u->x102 + ((s8)*(u8*)&u->y103 << 6)))[0xd] = u->fc;
    }
    if (*(u32*)(lbl_803C8E80 + 0x15ec) & 0x20000000) {
        fn_80083DC4(p, 1);
    } else {
        fn_80083DC4(p, 0);
    }
}

struct ObjBase { int x; };
class Obj : public ObjBase {
public:
    virtual void get(int*, int*, u32*);
};
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(u8);
void fn_80032FA8(Unit*);

void fn_800429F8(u8* o, u8* p) {
    int x, y;
    u32 c;
    if (*(void**)(p + 0x40)) {
        ((Obj*)o)->get(&x, &y, &c);
        fn_8007E154();
        fn_8007E4E4(x + 0x20, y + 0x30, 120.0f, 1.0f);
        fn_8007E7DC(c);
        fn_8007E164();
        fn_80032FA8(fn_800CFB0C(*(void**)(p + 0x40)));
        fn_8007E154();
        fn_8007E7DC(0xff);
        fn_8007E164();
    }
}
}
