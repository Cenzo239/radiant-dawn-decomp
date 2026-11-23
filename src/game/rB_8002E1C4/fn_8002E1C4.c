#include "game/rB_8002E1C4/types.h"

void fn_8008A780(void* a, int n, void* b);
void fn_8008A43C(void* a, int n, void* b);
void fn_8028C0D0(void* arr, void* dtor, int size, int n); /* __destroy_arr */
void fn_80111C24(void* p, int f);                          /* Item::~Item */
void fn_80079210(void* p);                                 /* operator delete */
void fn_801221E8(void* p, int a);
void fn_80110D38(Item* p);                                 /* Item::clear */
void fn_80111C78(Item* dst, Item* src);                    /* Item::operator= */
void fn_80127134(void* dst, void* src);
void fn_8002E3D4(BUnit* p);

typedef struct BTrio { BUnit u[3]; } BTrio;

void fn_8002E1C4(void* a, void* b) { fn_8008A780(b, 0xc, (u8*)a + 4); }
void fn_8002E1D8(void* a, void* b) { fn_8008A43C(b, 0xc, (u8*)a + 4); }

/* The chain of null checks comes from inlined C++ base-class destructors. */
static inline void d6(BUnit* p) { if (p) { fn_8028C0D0(p->arr1bc, fn_80111C24, 0x28, 7); } }
static inline void d5(BUnit* p) { if (p) { d6(p); } }
static inline void d4(BUnit* p) { if (p) { d5(p); } }
static inline void d3(BUnit* p) { if (p) { d4(p); } }
static inline void d2(BUnit* p) { if (p) { d3(p); } }
static inline void d1(BUnit* p) { if (p) { d2(p); } }
static inline void d0(BUnit* p) { if (p) { d1(p); } }

/* deleting destructor of the unit base class */
BUnit* fn_8002E1EC(BUnit* p, int f)
{
    if (p != 0) {
        d1(p);
        if (f > 0) fn_80079210(p);
    }
    return p;
}

static inline void bunit_dtor(BUnit* p)
{
    if (p) {
        fn_8002E3D4(p);
        fn_80111C24(&p->item2, -1);
        fn_80111C24(&p->item, -1);
        d0(p);
    }
}

/* destructor of BUnit[3] holder (battle state) */
BTrio* fn_8002E26C(BTrio* p, int f)
{
    if (p != 0) {
        bunit_dtor(&p->u[2]);
        bunit_dtor(&p->u[1]);
        bunit_dtor(&p->u[0]);
        if (f > 0) fn_80079210(p);
    }
    return p;
}

/* BUnit::reset */
void fn_8002E3D4(BUnit* p)
{
    fn_801221E8(p, 0);
    p->unit = 0;
    fn_80110D38(&p->item);
    fn_80110D38(&p->item2);
    p->x445 = 0;
    p->x444 = -1;
    p->x446 = 0;
    p->x448[0] = 0;
    p->x448[1] = 0;
    p->x448[2] = 0;
    p->x448[3] = 0;
    p->x448[4] = 0;
    p->x448[5] = 0;
    p->x448[6] = 0;
    p->x448[7] = 0;
    p->x448[8] = 0;
    p->x448[9] = 0;
    p->x448[10] = 0;
    p->x45e = 0;
    p->x460 = 0;
    p->x464 = 0;
    p->x465 = 0;
    p->x466 = 0;
    p->x468[6] = 0;
    p->x468[7] = 0;
    p->x468[8] = 0;
    p->x47a = 0;
    p->x47b = 0;
    p->x47c = 0;
    p->x47d = 0;
    p->x47e = 0;
    p->x47f = 0;
    p->x480 = 0;
    p->x481 = 0;
    p->x482 = 0;
    p->x483 = 0;
    p->x484 = 0;
    p->x486 = 0;
    p->x488 = 0;
    p->x48a = 0;
    p->x48b = 0;
    p->x48c = 0;
    p->x490[0] = 0;
    p->x490[1] = 0;
    p->x490[2] = 0;
    p->x490[10] = 0;
    p->x490[9] = 0;
    p->x490[8] = 0;
    p->x490[7] = 0;
    p->x490[6] = 0;
    p->x490[5] = 0;
    p->x490[4] = 0;
    p->x490[3] = 0;
    p->x468[0] = -1;
    p->x468[1] = -1;
    p->x468[2] = -1;
    p->x468[3] = -1;
    p->x468[4] = -1;
    p->x468[5] = -1;
    p->x49c = 0;
}

/* BUnit::operator= */
BUnit* fn_8002E508(BUnit* p, BUnit* src)
{
    if (src != p) {
        fn_80127134(p, src);
        p->unit = src->unit;
        fn_80111C78(&p->item, &src->item);
        fn_80111C78(&p->item2, &src->item2);
        p->x444 = src->x444;
        p->x445 = src->x445;
        p->x446 = src->x446;
        p->x448[0] = src->x448[0];
        p->x448[1] = src->x448[1];
        p->x448[2] = src->x448[2];
        p->x448[3] = src->x448[3];
        p->x448[4] = src->x448[4];
        p->x448[5] = src->x448[5];
        p->x448[6] = src->x448[6];
        p->x448[7] = src->x448[7];
        p->x448[8] = src->x448[8];
        p->x448[9] = src->x448[9];
        p->x448[10] = src->x448[10];
        p->x45e = src->x45e;
        p->x460 = src->x460;
        p->x464 = src->x464;
        p->x465 = src->x465;
        p->x466 = src->x466;
        p->x468[0] = src->x468[0];
        p->x468[1] = src->x468[1];
        p->x468[2] = src->x468[2];
        p->x468[3] = src->x468[3];
        p->x468[4] = src->x468[4];
        p->x468[5] = src->x468[5];
        p->x468[6] = src->x468[6];
        p->x468[7] = src->x468[7];
        p->x468[8] = src->x468[8];
        p->x47a = src->x47a;
        p->x47b = src->x47b;
        p->x47c = src->x47c;
        p->x47d = src->x47d;
        p->x47e = src->x47e;
        p->x47f = src->x47f;
        p->x480 = src->x480;
        p->x482 = src->x482;
        p->x483 = src->x483;
        p->x486 = src->x486;
        p->x488 = src->x488;
        p->x48a = src->x48a;
        p->x490[2] = src->x490[2];
        p->x490[3] = src->x490[3];
        p->x490[4] = src->x490[4];
        p->x490[5] = src->x490[5];
        p->x490[6] = src->x490[6];
        p->x490[7] = src->x490[7];
        p->x490[8] = src->x490[8];
        p->x490[9] = src->x490[9];
        p->x490[10] = src->x490[10];
        p->x49c = src->x49c;
    }
    return p;
}

void fn_8002E6FC(BUnit* p, BUnit* unit)
{
    fn_80127134(p, unit);
    p->unit = unit;
}

typedef struct Obj4C8 { u8 pad[0xfc]; } Obj4C8;
typedef struct Obj5C4 {
    u8 pad0[0xee];
    u16 xee;
    u8 padf0[0x104 - 0xf0];
    u8 x104;
    u8 pad105[0x11c - 0x105];
} Obj5C4;
typedef struct Holder {
    u8 pad[0xec];
    Obj4C8* xec;
    Obj5C4* xf0;
    u32 xf4;
} Holder;

extern s8 lbl_804CB178;
extern s8 lbl_804CB179;
extern Obj4C8 lbl_803CA4C8;
extern Obj5C4 lbl_803CA5C4;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB814;
#else
extern u32 lbl_804CB814;
#endif
void fn_80118D24(Obj4C8* p);
void fn_80118DF4(Obj5C4* p);
void fn_800F3900(void);

void fn_8002E738(Holder* h)
{
    if (!lbl_804CB178) {
        fn_80118D24(&lbl_803CA4C8);
        lbl_804CB178 = 1;
    }
    if (!lbl_804CB179) {
        fn_80118DF4(&lbl_803CA5C4);
        lbl_804CB179 = 1;
    }
    lbl_803CA5C4.xee |= 0x1000;
    lbl_803CA5C4.x104 = 100;
    fn_800F3900();
    h->xf0 = &lbl_803CA5C4;
    h->xec = &lbl_803CA4C8;
    h->xf4 = lbl_804CB814;
}

extern BattleState lbl_803C8E80;

void fn_80126D9C(BUnit* u, int a);
void fn_80110D00(Item* it, u8 a);
void fn_8012BC54(BUnit* u, u8 a, Item* it);
void fn_8012A850(BUnit* u);
void fn_80129CB8(BUnit* u, int a);

/* BUnit::writeBack - copy battle results back to the real unit */
void fn_8002E7E0(BUnit* p)
{
    BUnit* u;
    fn_80126D9C(p->unit, p->x114);
    u = p->unit;
    u->x110 = p->x110;
    u->x112 = p->x112;
    if (p->x444 >= 0) {
        fn_80111C78(&p->item, &p->item2);
        fn_80110D00(&p->item, p->x47c);
        if (p->x47d != 0) {
            p->item.b5_7 = 0;
        }
        fn_8012BC54(p->unit, p->x444, &p->item);
        fn_8012A850(p->unit);
        u = p->unit;
        u->x2d4[0] = p->x2d4[0];
        u->x2d4[1] = p->x2d4[1];
        u->x2d4[2] = p->x2d4[2];
        u->x2d4[3] = p->x2d4[3];
        u->x2d4[4] = p->x2d4[4];
        u->x2d4[5] = p->x2d4[5];
        u->x2d4[6] = p->x2d4[6];
        u->x2d4[7] = p->x2d4[7];
        u->x2d4[8] = p->x2d4[8];
        u->x2d4[9] = p->x2d4[9];
        u->x2d4[10] = p->x2d4[10];
        u->x2d4[11] = p->x2d4[11];
        if (!(lbl_803C8E80.flags & 0x8000) && p->x47c <= 0) {
            fn_80129CB8(p->unit, -1);
        }
    }
}

extern Item lbl_803EC368; /* empty item */
ItemData* fn_801116B8(Item* it);

/* returns the unit's usable weapon, or the empty item when broken/none */
static inline Item* bunit_weapon(BUnit* u)
{
    if (u->x47c <= 0) return &lbl_803EC368;
    if (u->x47d != 0) return &lbl_803EC368;
    return &u->item;
}

void fn_8002E910(BUnit* p, BUnit* q)
{
    if (fn_801116B8(bunit_weapon(q))->flags & 0x1000) {
        fn_80110D38(&p->item);
    }
    if (fn_801116B8(bunit_weapon(p))->flags & 0x1000) {
        if (!(fn_801116B8(bunit_weapon(q))->flags & 0x1000)) {
            fn_80110D38(&p->item);
        }
    }
}

void fn_8002EA20(BUnit* p, BUnit* q)
{
    if (fn_801116B8(bunit_weapon(q))->flags & 0x80) {
        fn_80110D38(&p->item);
    }
    if (fn_801116B8(bunit_weapon(p))->flags & 0x80) {
        if (!(fn_801116B8(bunit_weapon(q))->flags & 0x80)) {
            fn_80110D38(&p->item);
        }
    }
}


extern void* lbl_804CA6E4;
extern void* lbl_804CA6E8;
extern void* lbl_804CA6EC;
Item* fn_80127648(BUnit* p);
int fn_8011B77C(void* a, void* b);

/* BUnit::updateWeaponEffects */
void fn_8002EBF0(BUnit* p)
{
    Item* it;
    p->x446 = 0;
    p->x45e = 0;
    if (bunit_weapon(p)->data != 0) {
        if (fn_801116B8(bunit_weapon(p))->x0 & 0x200) return;
    }
    if (p->item2.data != 0) {
        p->x45e |= p->item2.data->xc;
    }
    it = fn_80127648(p);
    if (it != 0 && it->data != 0) {
        p->x45e |= it->data->xc;
    }
    if (fn_8011B77C(p->x12c, lbl_804CA6E4)) p->x45e |= 0x40;
    if (fn_8011B77C(p->x12c, lbl_804CA6E8)) p->x45e |= 0x100;
    if (fn_8011B77C(p->x12c, lbl_804CA6EC)) p->x45e |= 0x80;
}

u8 fn_801107A0(ItemData* d, BUnit* u);
u8 fn_801107C0(ItemData* d, BUnit* u);
s8 fn_80127520(BUnit* p);
int fn_8012AD38(BUnit* p, ItemData* d);

static inline int item_min_range(Item* it, BUnit* u)
{
    return it->data ? fn_801107A0(it->data, u) : 0;
}
static inline int item_max_range(Item* it, BUnit* u)
{
    return it->data ? fn_801107C0(it->data, u) : 0;
}

/* BUnit::equip(range, slot) */
void fn_8002ED4C(BUnit* p, int range, s8 slot)
{
    if (slot < 0) {
        p->x444 = fn_80127520(p);
    } else {
        p->x444 = slot;
    }
    if (p->x444 < 0) {
        fn_80110D38(&p->item);
        fn_80110D38(&p->item2);
        return;
    }
    fn_80111C78(&p->item, &p->arr1bc[p->x444]);
    fn_80111C78(&p->item2, &p->arr1bc[p->x444]);
    p->x47c = p->item.uses;
    if (range != 0) {
        if (item_min_range(bunit_weapon(p), p) > range || item_max_range(bunit_weapon(p), p) < range) {
            fn_80110D38(&p->item);
        }
    }
    if (bunit_weapon(p)->data != 0) {
        if (!fn_8012AD38(p, bunit_weapon(p)->data)) {
            fn_80110D38(&p->item);
        }
    }
    fn_8002EBF0(p);
}

/* BUnit::equipSlot */
void fn_8002EF48(BUnit* p, int slot)
{
    p->x444 = slot;
    if (p->x444 < 0) {
        fn_80110D38(&p->item);
        fn_80110D38(&p->item2);
        return;
    }
    fn_80111C78(&p->item, &p->arr1bc[p->x444]);
    fn_80111C78(&p->item2, &p->arr1bc[p->x444]);
    p->x47c = p->item.uses;
    if (bunit_weapon(p)->data != 0) {
        if (!fn_8012AD38(p, bunit_weapon(p)->data)) {
            fn_80110D38(&p->item);
        }
    }
    fn_8002EBF0(p);
}

/* BUnit::equipItem */
void fn_8002F05C(BUnit* p, Item* it)
{
    p->x444 = -1;
    fn_80111C78(&p->item, it);
    fn_80111C78(&p->item2, it);
    p->x47c = it->uses;
    p->x45e = 0;
    if (bunit_weapon(p)->data != 0) {
        if (!fn_8012AD38(p, bunit_weapon(p)->data)) {
            fn_80110D38(&p->item);
        }
    }
    fn_8002EBF0(p);
}

typedef struct X460 {
    u8 pad[8];
    u8* x8;
} X460;
extern u8 lbl_803EC898[];
extern void* lbl_804CA500;
X460* fn_80118280(void* tbl, BUnit* p);

void fn_8002F14C(BUnit* p)
{
    p->x460 = fn_80118280(lbl_803EC898, p);
    if (p->x460 == 0) {
        p->x464 = 0;
        p->x465 = 0;
        p->x466 = 0;
    } else if (fn_8011B77C(p->x12c, lbl_804CA500)) {
        p->x464 = p->x460->x8[4];
        p->x465 = p->x460->x8[5];
        p->x466 = p->x460->x8[3];
    } else {
        p->x464 = p->x460->x8[1];
        p->x465 = p->x460->x8[2];
        p->x466 = p->x460->x8[0];
    }
}

void fn_8002F20C(BUnit* p)
{
    p->x464 = 0;
    p->x465 = 0;
    p->x466 = 0;
}
