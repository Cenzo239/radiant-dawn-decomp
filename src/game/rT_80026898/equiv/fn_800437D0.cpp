/* fn_800437D0: end-of-phase clean-up of the map units (names guessed). Level:
   regs (the saved registers of the last list walks are assigned differently;
   20 words). From wip/fn_800437D0.cpp with three corrections:
   - REAL BUG in the draft: the first team list was {0,5,6,7,8,9,0xff}; the
     original constant (0x804CCE08) is {0,5,7,8,9,10,0xff};
   - lbl_804CA0A4 is a 7-byte .sdata string (addressed with li ...@sda21);
   - the final name test is an inline that takes the pointer and dereferences
     it inside (`mr r4,r3; li r3; lwz r4,0(r4)`), returning bool.
   The file also holds the matched fn_80043BAC. */
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
void fn_800434A0(void);


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

struct Group { Unit* head; u8 pad[8]; };




static inline u8* section(int i) {
    switch (i) {
    case 0: return lbl_803C8E80;
    case 1: return lbl_803C8E80 + 0x4a0;
    case 2: return lbl_803C8E80 + 0x940;
    }
    return 0;
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


void* fn_80081050(void*, void*);
void fn_800CD4A4(int);
extern u8 lbl_80379F58[];
void fn_8012D908(void);
void fn_8012FF30(void);
void fn_8011FDD8(Unit*, int);
void fn_8012AB70(Unit*);
void fn_8012CC80(void);
Unit* fn_8012CE54(const char*);
void fn_80067EE8(void);
char** fn_8006074C(void*);
int fn_80291188(const char*, const char*);
u8* fn_8024BCA0x(void);
extern void* lbl_804CA4D8;
extern char lbl_80361684[];
extern char lbl_804CA0A4[7];
static inline bool streq(const char* a, const char* const* b) { return fn_80291188(a, *b) == 0; }
extern char lbl_80361684[];
struct G2 { Unit* head; Unit* tail; u8 pad[4]; };
#pragma use_lmw_stmw on
#pragma push
#pragma opt_common_subs off
void fn_80043BAC(void) {
    u8 m[0x10];
    int i;
    Unit* u;
    u8 t[7] = {0, 5, 7, 8, 9, 0xa, 0xff};
    memset(m, (u8)lbl_804CA0A0, 0xb);
    markAll(m, t);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec && m[u->f4[8]]) {
            if ((u->f10c & 2) && !(u->f10c & 0x100000)) {
                fn_8011E300(u, u->x102, (s8)*(u8*)&u->y103, 0);
            }
            FLAGS(u) &= 0xFFFFFF92E688C53EULL;
            fn_80109078(u->x110);
            fn_80126D9C(u, fn_801237EC(u));
            fn_80128E14(u, 0);
            fn_801283F8(u);
        }
    }
    fn_80060580(lbl_803CAB38.x554, lbl_803CAB38.f9c);
    lbl_803CAB38.f12 = 1;
    lbl_803CAB38.side = 0;
}
#pragma pop
#pragma push
#pragma opt_common_subs off
void fn_800437D0(void) {
    u8 m[0xC];
    u8 m2[0xC];
    Unit* u;
    Unit* q;
    int i;
    int s;
    int o;
    Unit* p;
    Unit* e;
    int i2;
    Unit* u2;
    u8* b;
    Unit* h;
    Unit* w;
    Unit* nx;
    b = fn_8024BCA0();
    *(u32*)(b + 0x40) &= ~0x38;
    if ((*fn_80060728(&lbl_803CAB38) & 3) == 1) {
        fn_800CD4A4(0x24);
        return;
    }
    w = ((G2*)lbl_804CB814)[5].tail;
    w = *(Unit**)((u8*)lbl_804CB814 + 0x40);
    while (w) {
        nx = *(Unit**)((u8*)w + 0xE4);
        if ((w->f10c & 0x4000) && (w->f10c & 0x10000)) fn_8011FDD8(w, 0);
        w = nx;
    }
    {
        u8 t[7] = {0, 5, 7, 8, 9, 0xa, 0xff};
        memset(m, (u8)lbl_804CA0A0, 0xb);
        markAll(m, t);
    }
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec && m[u->f4[8]]) {
            if ((u->f10c & 2) && !(u->f10c & 0x100000)) {
                fn_8011E300(u, u->x102, (s8)*(u8*)&u->y103, 0);
            }
            FLAGS(u) &= 0xFFFFFF92E688C53EULL;
            fn_80109078(u->x110);
            fn_80126D9C(u, fn_801237EC(u));
            fn_80128E14(u, 0);
            fn_801283F8(u);
        }
    }
    {
        u8 t2[8] = {0, 5, 6, 7, 8, 9, 0xa, 0xff};
        memset(m2, (u8)lbl_804CA0A0, 0xb);
        markAll(m2, t2);
    }
    for (i2 = 1; i2 <= 0xfe; i2++) {
        u2 = unitAt(i2);
        if (u2->ec && m2[u2->f4[8]]) fn_8012AB70(u2);
    }
    fn_8012CC80();
    for (s = 0, o = 0; s < 0xB; s++, o += 0xC) {
        switch (s) {
        default:
            e = *(Unit**)(o + (int)lbl_804CB814);
            q = *(Unit**)((u8*)lbl_804CB814 + o + 4);
            while (q) {
                p = *(Unit**)((u8*)q + 0xE4);
                if (q->f10c & 0x400) fn_8011FDD8(q, s);
                if (q == e) break;
                q = p;
            }
            e = *(Unit**)(o + (int)lbl_804CB814);
            q = *(Unit**)((u8*)lbl_804CB814 + o + 4);
            while (q) {
                p = *(Unit**)((u8*)q + 0xE4);
                if (fn_8011B77C(q->x12c, lbl_804CA4D8)) fn_8011FDD8(q, s);
                if (q == e) break;
                q = p;
            }
            break;
        case 0: case 1: case 2: case 3: case 4: case 6:
            break;
        }
    }

    {
        Unit* z = fn_8012CE54(lbl_80361684);
        if (z) fn_8011FDD8(z, z->f4[8]);
    }
    fn_80060580(lbl_803CAB38.x554, 0);
    fn_80067EE8();
    if (streq(lbl_804CA0A4, fn_8006074C(&lbl_803CAB38))) fn_800434A0();
}
#pragma pop
}
