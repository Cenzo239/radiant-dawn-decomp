#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_800761F0(void*);
int fn_8012E9B4(Unit*, Unit*);
u8 fn_8012E8BC(Unit*, int);
void fn_8012E440(Unit*, int, int);
void fn_80250D64(int, f32, f32);
void fn_80031728(void*, void*, Unit*);
void fn_80031854(void*, void*, Unit*);
void fn_8006CCAC(void*, Unit*, int, void*, int);
void fn_8012A0F4(Unit*, void*);
void fn_8012A80C(Unit*, int);
void fn_8002BCC4(void*);
int fn_80030D84(void*);
void fn_80103D50(void*, int);
Cell* fn_800CFD18(void*, int);
Unit* fn_800CFB0C(Cell*);
void fn_8010904C(void*);
void* fn_8010B228(const char*);
void fn_8003A664(Unit*, void*);
void fn_8003A3BC(Unit*, void*);
void fn_80026CD8(void*, Unit*, int);
void fn_80026C44(void*, Unit*, Unit*);
void fn_8002C170(void*);
#if TARGET_PC
FE10_PROTO void fn_8002C1C4(ptr32<const void>, int);
#else
void fn_8002C1C4(void*, int);
#endif
void fn_800E8188(void*, void*);
void fn_800E81EC(void*, void*);
void fn_800E8048(void*, void*);
void fn_800E8098(void*, void*);
void fn_800E8428(void*, void*);
void fn_800E8478(void*, void*);
void fn_8011E3A0(Unit*, int);
u8 fn_80123998(Unit*);
void fn_80108A20(void*, Unit*, int);
#if TARGET_PC
FE10_PROTO void fn_800484AC(ptr32<const void>);
FE10_PROTO void fn_800485B8(ptr32<const void>);
#else
void fn_800484AC(void*);
void fn_800485B8(void*);
#endif
void fn_800CFB34(void*);
#if TARGET_PC
FE10_PROTO void fn_800CFC50(void*, int, int, int, p32arg);
#else
void fn_800CFC50(void*, int, int, int, u32);
#endif
Cell* fn_800CFCB4(void*, int, int);
void fn_8003B0F4(Unit*);
void fn_8003B148(Unit*);
f32 fn_801072E4(Unit*);
f32 fn_80107444(Unit*);

void fn_800E84C8(void*, void*);
void fn_800E8518(void*, void*);
void fn_800E8568(void*, void*);
void fn_80128558(Unit*, int);
s16 fn_801237EC(Unit*);
void fn_80126D9C(Unit*, int);
Cell* fn_8002C738(void*);
Cell* fn_8002C590(void*);
#if TARGET_PC
FE10_PROTO void fn_80186DAC(void*, p32arg);
#else
void fn_80186DAC(void*, int);
#endif
int fn_800F7724(Unit*);
int fn_8011F428(Unit*);
#if TARGET_PC
FE10_PROTO void fn_80103A20(Unit*, p32arg);
FE10_PROTO void fn_801039E8(Unit*, p32arg);
#else
void fn_80103A20(Unit*, int);
void fn_801039E8(Unit*, int);
#endif
int fn_800D7D74(int);
int fn_800A026C(int);
#if TARGET_PC
FE10_PROTO void fn_8010301C(Unit*, Unit*, int, int, p32arg);
#else
void fn_8010301C(Unit*, Unit*, int, int, int);
#endif
void fn_80081194(void*, void*);
extern char lbl_8037AF80[];
extern u8 lbl_803CB770[];
struct Tile { u8 pad[4]; u8 b4; u8 b5; };
Tile* fn_80066130(void*, int, int, int);
void fn_80111B34(Item*);
void fn_80111C24(Item*, int);
void* fn_8010B204(int);
void fn_80110BB4(Item*, void*);
void fn_80027228(void*, Unit*, Item*);
int fn_8028DB44(int);
void fn_8005524C(void*);
void fn_80026E64(void*, Item*);
void fn_8002B2AC(void*, int, int);
void fn_8006C440(void*);
void fn_8006DE18(void*);
void fn_800262D8(void*);
void fn_800A04C8(void*, int, int, int);
void fn_80083DC4(void*, int);
void fn_8002BE64(void*, int);
#if TARGET_PC
FE10_PROTO void fn_800E9608(void*, p32arg);
#else
void fn_800E9608(void*, int);
#endif
void fn_8002BF40(void*, int);
void fn_8006C8E0(void*, int);
#if TARGET_PC
FE10_PROTO void fn_800E7DDC(void*, p32arg);
#else
void fn_800E7DDC(void*, int);
#endif
int fn_80121DEC(Unit*);
u8 fn_801209D0(Unit*, Unit*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80026950(u8);
#else
void* fn_80026950(u8);
#endif
#if TARGET_PC
FE10_PROTO void fn_8002C06C(void*, ptr32<const void>);
#else
void fn_8002C06C(void*, void*);
#endif
void fn_800E8B20(void*, void*);
void fn_80049CF4(void*);
void fn_801288D4(Unit*);
u8 fn_801107C0(void*, Unit*);
void fn_80055DD8(void*);
void fn_8011E414(Unit*);
void fn_8005627C(void*);
void* fn_8024BCA0(void);
u32 fn_8008A1A0(void*);
u32 fn_8008A1DC(void*);
void fn_8008A43C(void*, int, void*);
extern u8* lbl_804CB810;

void fn_80048260(void** p) {
    int r;
    if (p[0xc]) fn_800761F0(p[0xc]);
    if (p[0xd]) fn_800761F0(p[0xd]);
    r = (s8)fn_8012E9B4(lbl_803CA870.unit, lbl_803CA870.unit2);
    fn_8012E440(lbl_803CA870.unit, r, fn_8012E8BC(lbl_803CA870.unit, r));
    fn_80250D64(6, 1.0f, 1000.0f);
}

void fn_80048304(u8* p) {
    void* q = *(void**)(p + 0x54);
    if (lbl_803CA870.unit->f4[8] != 1) {
        fn_80031728(q, p, lbl_803CA870.unit);
    } else {
        fn_80031854(q, p, lbl_803CA870.unit);
    }
}

void fn_80048334(void* p) {
    fn_8006CCAC(lbl_803C8E80, lbl_803CA870.unit, 0xa, p, 1);
}

static inline u8* section(int i) {
    switch (i) {
    case 0: return lbl_803C8E80;
    case 1: return lbl_803C8E80 + 0x4a0;
    case 2: return lbl_803C8E80 + 0x940;
    }
    return 0;
}

void fn_80048354(u8* p) {
    int i;
    u8* s = *(u8**)(p + 0x54);
    Unit* u = lbl_803CA870.unit;
    Unit* u2 = lbl_803CA870.unit2;
    s[5] &= ~0x40;
    s[5] &= ~0xC;
    fn_8012A0F4(u, s);
    fn_8012A80C(u2, (s8)lbl_803CA870.item);
    fn_8002BCC4(lbl_803C8E80);
    for (i = 0; i < 2; i++) {
        u8* q = section(i);
        if (fn_80030D84(q) == 0 && *(void**)(q + 0x3f0)) {
            fn_80103D50(*(void**)(q + 0x3f0), 0x10);
        }
    }
}

void fn_8004844C(void) {
    int i;
    for (i = 0; i < *(int*)lbl_803E7320; i++) {
        fn_8010904C(fn_800CFB0C(fn_800CFD18(lbl_803E7320, i))->x110);
    }
}

void fn_800484B8(Unit** p, void* proc) {
    Unit* u = *p;
    fn_8003A664(u, fn_8010B228(lbl_803619D0 + 0x22));
    if (*(int*)lbl_803E7320) {
        fn_80026CD8(lbl_803C8E80, lbl_803CA870.unit, -1);
        fn_8002C170(lbl_803C8E80);
        fn_800E8188(proc, fn_800484AC);
    }
}

void fn_80048548(void) {
    int i;
    for (i = 0; i < *(int*)lbl_803E7320; i++) {
        Cell* c = fn_800CFD18(lbl_803E7320, i);
        fn_8011E3A0(fn_800CFB0C(c), c->b);
    }
}

void fn_800485C4(Unit** p, void* proc) {
    Unit* u = *p;
    Cell* c;
    u32 d;
    u8 e;
    u8 b;
    int i;
    fn_8003A3BC(u, fn_8010B228(lbl_803619D0 + 0x2b));
    if (*(int*)lbl_803E7320) {
        for (i = 0; i < *(int*)lbl_803E7320; i++) {
            c = fn_800CFD18(lbl_803E7320, i);
            d = c->d;
            e = c->c;
            b = fn_80123998(*p);
            c->a = 3;
            c->b = b;
            c->c = e;
            c->d = d;
        }
        fn_80026CD8(lbl_803C8E80, lbl_803CA870.unit, -1);
        fn_8002C170(lbl_803C8E80);
        fn_800E81EC(proc, fn_800485B8);
    }
}

void fn_8004869C(void) {
    Unit* u2 = lbl_803CA870.unit2;
    fn_80108A20(u2->x110, u2, 1);
    FLAGS(lbl_803CA870.unit) |= 0x1000ULL;
}

void fn_800486E8(void) {
    int i;
    for (i = 0; i < *(int*)lbl_803E7320; i++) {
        Unit* u = fn_800CFB0C(fn_800CFD18(lbl_803E7320, i));
        *(u64*)&u->f108 &= ~1ULL;
    }
}

void fn_80048770(void* proc) {
    fn_80026CD8(lbl_803C8E80, lbl_803CA870.unit, -1);
    fn_8002C170(lbl_803C8E80);
    fn_8002C1C4(lbl_803C8E80, 0xa);
    fn_800E8428(proc, fn_800486E8);
}


void fn_800489B4(void) {
    int i;
    for (i = 0; i < *(int*)lbl_803E7320; i++) {
        Unit* u = fn_800CFB0C(fn_800CFD18(lbl_803E7320, i));
        u->f37c = fn_801072E4(u);
    }
}

void fn_80048A2C(void* proc) {
    fn_80026CD8(lbl_803C8E80, lbl_803CA870.unit, -1);
    fn_8002C170(lbl_803C8E80);
    fn_8002C1C4(lbl_803C8E80, 0xa);
    fn_800E8478(proc, fn_800489B4);
}

#define WRAP(name, inner, tail) \
void name(void* proc) { \
    fn_80026CD8(lbl_803C8E80, lbl_803CA870.unit, -1); \
    fn_8002C170(lbl_803C8E80); \
    fn_8002C1C4(lbl_803C8E80, 0xa); \
    tail(proc, inner); \
}

void fn_80048C70(void) {
    int i;
    for (i = 0; i < *(int*)lbl_803E7320; i++) {
        Unit* u = fn_800CFB0C(fn_800CFD18(lbl_803E7320, i));
        u->f37c = fn_80107444(u);
    }
}

WRAP(fn_80048CE8, fn_80048C70, fn_800E84C8)

void fn_80048F2C(void) {
    int i;
    for (i = 0; i < *(int*)lbl_803E7320; i++) {
        fn_80128558(fn_800CFB0C(fn_800CFD18(lbl_803E7320, i)), 0x1e);
    }
}

WRAP(fn_80048F8C, fn_80048F2C, fn_800E8518)

void fn_800491D0(void) {
    int i;
    for (i = 0; i < *(int*)lbl_803E7320; i++) {
        Unit* u = fn_800CFB0C(fn_800CFD18(lbl_803E7320, i));
        fn_80126D9C(u, fn_801237EC(u));
        fn_8010904C(u->x110);
    }
}

WRAP(fn_8004924C, fn_800491D0, fn_800E8568)

void fn_80049490(void) {
    int i;
    for (i = 0; i < 2; i++) {
        Unit* u = *(Unit**)(section(i) + 0x3f0);
        if (u) FLAGS(u) &= ~0x10000000ULL;
    }
}

int fn_80049618(int a) {
    Cell* c = fn_8002C738(lbl_803C8E80);
    if (c == 0) return 0;
    fn_80186DAC(*(void**)((u8*)c + 0x3f0), a);
    return 1;
}

void fn_8004966C(int a) {
    Cell* c = fn_8002C590(lbl_803C8E80);
    if (c) {
        Unit* u = *(Unit**)((u8*)c + 0x3f0);
        if (u && fn_800F7724(u)) {
            if (fn_8011F428(u)) {
                fn_80103A20(u, a);
            } else {
                fn_801039E8(u, a);
            }
        }
    }
}

void fn_80049734(int a) {
    if (fn_800D7D74(a) == 0 && fn_800A026C(a)) {
        Unit* u1 = *(Unit**)(lbl_803C8E80 + 0x3f0);
        Unit* u2 = *(Unit**)(lbl_803C8E80 + 0x890);
        if (u1 && u2) {
            fn_8010301C(u1, u2, 0x18, 0, a);
            fn_8010301C(u2, u1, 0x18, 0, a);
        }
    }
}

void fn_8004984C(void* proc) {
    fn_80081194(lbl_8037AF80, proc);
}

void fn_8004985C(Act* q, void* proc) {
    Item it;
    Tile* t = fn_80066130(lbl_803CB770, (s8)lbl_803CA870.cx, (s8)lbl_803CA870.cy, 7);
    t->b5--;
    fn_80111B34(&it);
    fn_80110BB4(&it, fn_8010B204(t->b4));
    if (q->action == 0x32) {
        fn_80027228(lbl_803C8E80, q->u1, &it);
        *(int*)(lbl_803C8E80 + 0x15e8) = fn_8028DB44(q->x - q->cx) + fn_8028DB44(q->y - q->cy);
        fn_8005524C(proc);
        fn_80111C24(&it, -1);
    } else {
        fn_80026C44(lbl_803C8E80, q->u1, q->u2);
        fn_80026E64(lbl_803C8E80, &it);
        fn_8002B2AC(lbl_803C8E80, q->action, 0);
        fn_8006C440(lbl_803C8E80);
        fn_8006DE18(lbl_803C8E80);
        fn_800262D8(lbl_803C8E80 + 0xde0);
        fn_80081194(lbl_8037AF80, proc);
        fn_80111C24(&it, -1);
    }
}

void fn_800499D4(void* a) {
    if ((s8)lbl_803C8E80[0x5b4] == 0) {
        fn_800A04C8(a, 0, (s8)lbl_803CA870.x, (s8)lbl_803CA870.y);
    }
}

void fn_80049A18(u8* p) {
    if (*(int*)(p + 0x30) >= *(int*)lbl_803E7320) {
        fn_80083DC4(p, 0x63);
    } else {
        Unit* u;
        u = fn_800CFB0C(fn_800CFD18(lbl_803E7320, (*(int*)(p + 0x30))++));
        *(Unit**)(p + 0x34) = u;
        fn_80026CD8(lbl_803C8E80, u, -1);
        fn_8002C170(lbl_803C8E80);
        fn_8002BE64(lbl_803C8E80, -0xa);
        fn_800E9608(p, 0);
    }
}

static inline const int& minRef(const int& a, const int& b) {
    return b < a ? b : a;
}

void fn_80049C08(void* proc) {
    int a, b, s;
    fn_80026C44(lbl_803C8E80, lbl_803CA870.unit, lbl_803CA870.unit2);
    fn_8002C170(lbl_803C8E80);
    a = lbl_803CA870.unit->s114 - 1;
    s = lbl_803CA870.unit2->s114;
    b = fn_801237EC(lbl_803CA870.unit2) - s;
    a = minRef(a, b);
    fn_8002BF40(lbl_803C8E80, (s16)a);
    fn_8010904C(lbl_803C8E80 + 0x5b0);
    fn_8006C8E0(lbl_803C8E80, 0xa);
    fn_800262D8(lbl_803C8E80 + 0xde0);
    fn_800E7DDC(proc, 0);
}

void fn_80049D54(void* proc) {
    void* r;
    fn_80026C44(lbl_803C8E80, lbl_803CA870.unit, lbl_803CA870.unit2);
    fn_8002C170(lbl_803C8E80);
    r = 0;
    if (fn_80121DEC(lbl_803CA870.unit2) == 0) {
        r = fn_80026950(fn_801209D0(lbl_803CA870.unit, lbl_803CA870.unit2));
    }
    fn_8002C06C(lbl_803C8E80, r);
    fn_8006C8E0(lbl_803C8E80, r ? 0xa : 1);
    fn_800262D8(lbl_803C8E80 + 0xde0);
    fn_800E8B20(proc, fn_80049CF4);
}

void fn_80049E3C(void) {
    fn_801288D4(lbl_803CA870.unit);
    switch (lbl_803CA870.f18) {
    case 0:
        break;
    case 1:
        FLAGS(lbl_803CA870.unit) |= 0x08000000ULL;
        break;
    case 2:
        FLAGS(lbl_803CA870.unit) &= ~0x08000000ULL;
        FLAGS(lbl_803CA870.unit) &= ~0x100000000ULL;
        break;
    }
}

#define GIVE(off) fn_80110BB4(&it, fn_8010B228(lbl_803619D0 + off))

static inline u32 itemVal(Item* it, Unit* u) {
    return it->data ? fn_801107C0(it->data, u) : 0;
}

void fn_80049F8C(Act* q, void* proc) {
    Item it;
    u32 v;
    fn_80111B34(&it);
    switch (q->action) {
    case 0x50: GIVE(0xb3); break;
    case 0x51: GIVE(0xbe); break;
    case 0x52: GIVE(0xc9); break;
    case 0x5e: GIVE(0xd4); break;
    case 0x5f: GIVE(0xe8); break;
    default:
        fn_80111C24(&it, -1);
        return;
    }
    fn_80027228(lbl_803C8E80, q->u1, &it);
    v = itemVal(&it, q->u1);
    *(u32*)(lbl_803C8E80 + 0x15e8) = v;
    *(u32*)(lbl_803C8E80 + 0x15ec) |= 0x20000;
    fn_80055DD8(proc);
    fn_80111C24(&it, -1);
}

void fn_8004A110(Act* q, void* proc) {
    Item it;
    fn_80111B34(&it);
    switch (q->action) {
    case 0x53: GIVE(0xf8); break;
    case 0x54: GIVE(0x103); break;
    case 0x55: GIVE(0x10e); break;
    case 0x60: GIVE(0x119); break;
    default:
        fn_80111C24(&it, -1);
        return;
    }
    fn_80026C44(lbl_803C8E80, q->u1, q->u2);
    fn_80026E64(lbl_803C8E80, &it);
    fn_8002B2AC(lbl_803C8E80, 0xf, 0);
    fn_8006C440(lbl_803C8E80);
    fn_8006DE18(lbl_803C8E80);
    fn_800262D8(lbl_803C8E80 + 0xde0);
    fn_80081194(lbl_8037AF80, proc);
    fn_80111C24(&it, -1);
}

void fn_8004A288(void) {
    fn_80126D9C(lbl_803CA870.unit, 0);
    fn_8011E414(lbl_803CA870.unit);
}

void fn_8004A2C4(Act* q, void* proc) {
    Item it;
    fn_80111B34(&it);
    switch (q->action) {
    case 0x5b: GIVE(0x129); break;
    case 0x5c: GIVE(0x136); break;
    case 0x5d: GIVE(0x144); break;
    default:
        fn_80111C24(&it, -1);
        return;
    }
    fn_80027228(lbl_803C8E80, q->u1, &it);
    *(u32*)(lbl_803C8E80 + 0x15e8) = itemVal(&it, q->u1);
    fn_8005627C(proc);
    fn_80111C24(&it, -1);
}

static inline Unit* unitAt(u8 id) {
    return id ? (Unit*)(lbl_804CB810 + (id - 1) * 0x3f0) : 0;
}

struct Saved {
    Unit* a;
    Unit* b;
    u8 pad8[4];
    u8 c[11];
    u8 d;
    u32 e;
    u32 f;
    u8 pad20[8];
    u8 g;
};

void fn_8004A55C(Saved* s, void* r) {
    u8* h = (u8*)fn_8024BCA0();
    u8 id;
    id = fn_8008A1A0(r);
    if (id) s->a = unitAt(id); else s->a = 0;
    id = fn_8008A1A0(r);
    if (id) s->b = unitAt(id); else s->b = 0;
    s->c[0] = fn_8008A1A0(r);
    s->c[1] = fn_8008A1A0(r);
    s->c[2] = fn_8008A1A0(r);
    s->c[3] = fn_8008A1A0(r);
    s->c[4] = fn_8008A1A0(r);
    s->c[5] = fn_8008A1A0(r);
    s->c[6] = fn_8008A1A0(r);
    s->c[7] = fn_8008A1A0(r);
    s->c[8] = fn_8008A1A0(r);
    s->c[9] = fn_8008A1A0(r);
    s->c[10] = fn_8008A1A0(r);
    fn_8008A43C(r, 1, &s->d);
    if (*(u32*)(h + 0xc) < 10) {
        s->e = fn_8008A1DC(r);
        s->f = fn_8008A1DC(r);
    } else {
        fn_8008A43C(r, 0x10, &s->e);
    }
    fn_8008A43C(r, 1, &s->g);
}
}
