/* Round 23 (r23b), exact: fn_8002EB30. From equiv/fn_8002EB30.c with the two byte stores in the other source order
 * (x47c = uses, then x483 = 1); the scheduler puts them back in the original order with the original registers. */
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
void fn_8002E1C4(void* a, void* b);

void fn_8002E1D8(void* a, void* b);


/* The chain of null checks comes from inlined C++ base-class destructors. */
static inline void d6(BUnit* p) { if (p) { fn_8028C0D0(p->arr1bc, fn_80111C24, 0x28, 7); } }
static inline void d5(BUnit* p) { if (p) { d6(p); } }
static inline void d4(BUnit* p) { if (p) { d5(p); } }
static inline void d3(BUnit* p) { if (p) { d4(p); } }
static inline void d2(BUnit* p) { if (p) { d3(p); } }
static inline void d1(BUnit* p) { if (p) { d2(p); } }
static inline void d0(BUnit* p) { if (p) { d1(p); } }
BUnit* fn_8002E1EC(BUnit* p, int f);


static inline void bunit_dtor(BUnit* p)
{
    if (p) {
        fn_8002E3D4(p);
        fn_80111C24(&p->item2, -1);
        fn_80111C24(&p->item, -1);
        d0(p);
    }
}
BTrio* fn_8002E26C(BTrio* p, int f);

void fn_8002E3D4(BUnit* p);

BUnit* fn_8002E508(BUnit* p, BUnit* src);

void fn_8002E6FC(BUnit* p, BUnit* unit);


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
void fn_8002E738(Holder* h);


extern BattleState lbl_803C8E80;

void fn_80126D9C(BUnit* u, int a);
void fn_80110D00(Item* it, u8 a);
void fn_8012BC54(BUnit* u, u8 a, Item* it);
void fn_8012A850(BUnit* u);
void fn_80129CB8(BUnit* u, int a);
void fn_8002E7E0(BUnit* p);


extern Item lbl_803EC368; /* empty item */
ItemData* fn_801116B8(Item* it);

/* returns the unit's usable weapon, or the empty item when broken/none */
static inline Item* bunit_weapon(BUnit* u)
{
    if (u->x47c <= 0) return &lbl_803EC368;
    if (u->x47d != 0) return &lbl_803EC368;
    return &u->item;
}
void fn_8002E910(BUnit* p, BUnit* q);

void fn_8002EA20(BUnit* p, BUnit* q);



extern void* lbl_804CA6E4;
extern void* lbl_804CA6E8;
extern void* lbl_804CA6EC;
Item* fn_80127648(BUnit* p);
int fn_8011B77C(void* a, void* b);
void fn_8002EBF0(BUnit* p);


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
void fn_8002ED4C(BUnit* p, int range, s8 slot);

void fn_8002EF48(BUnit* p, int slot);

void fn_8002F05C(BUnit* p, Item* it);


typedef struct X460 {
    u8 pad[8];
    u8* x8;
} X460;
extern u8 lbl_803EC898[];
extern void* lbl_804CA500;
X460* fn_80118280(void* tbl, BUnit* p);
void fn_8002F14C(BUnit* p);

void fn_8002F20C(BUnit* p);


/* ---- from build/tmp/r19hpbs/frag_eb30.c ---- */
int fn_80128EDC(BUnit* p, int x);
/* BUnit: counter-equip at range 1 from the second item copy. */
void fn_8002EB30(BUnit* p, int x)
{
    if (fn_80128EDC(p, x) != 0) {
        if (item_min_range(&p->item2, p) > x || item_max_range(&p->item2, p) < x) return;
        if (x == 1) {
            fn_80111C78(&p->item, &p->item2);
            p->x47c = p->item.uses;
            p->x483 = 1;
            fn_8002EBF0(p);
        }
    }
}