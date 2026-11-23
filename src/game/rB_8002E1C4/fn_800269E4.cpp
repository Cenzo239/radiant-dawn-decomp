#include "game/rT_80026898/types.h"

/* Battle setup. A Spec names one combatant: the unit, its tile, and either an
 * inventory index or an explicit weapon. */
struct ItemD { u32 x0; u32 flags; };
typedef struct BU {
    Unit u;
    u8 pad3f4[0x4a0 - 0x3f4];
} BU;
struct Battle {
    BU a;     /* 0x000 */
    BU b;     /* 0x4A0 */
    BU c;     /* 0x940 */
    u8 log[0x15e4 - 0xde0]; /* 0xDE0 */
    u8 f15e4;
    u8 pad15e5[3];
    int f15e8;
    u32 f15ec;
    u32 f15f0;
    u32 f15f4;
    u32 f15f8;
    s8 f15fc;
    u8 pad15fd[0x1604 - 0x15fd];
    u8 f1604;
};
struct Spec {
    Unit* u;
    s8 x, y;
    s8 idx;
    u8 f7;
    Slot* item;
    u8 fc;
    u8 fd, fe, ff;
};
struct Pos { s8 x, y; u8 pad[2]; u8 f4, f5; };
extern u8 lbl_803EC898[];
extern void* lbl_804CA510;
extern "C" {
void fn_8002E3D4(BU* p);
void fn_80025FE0(void* log);
void fn_8002E6FC(BU* p, Unit* u);
void fn_8002E738(BU* p);
void fn_80126EB0(BU* p, s8 x, s8 y);
void fn_80114888(void* m, int n);
void fn_80115DEC(void* m, s8 x, s8 y, int a, int b);
#if TARGET_PC
FE10_PROTO void fn_80116098(void* m, s8 x, s8 y, p32arg, p32arg);
#else
void fn_80116098(void* m, s8 x, s8 y, int a, int b);
#endif
void fn_8002ED4C(BU* p, int dist, s8 idx);
void fn_8002EF48(BU* p, s8 idx);
void fn_8002F05C(BU* p, Slot* it);
ItemD* fn_801116B8(Slot* it);
int fn_8011B77C(void* list, void* key);
Slot* fn_80030CBC(BU* p);
void fn_80110D38(Slot* it);
void fn_8002E910(BU* a, BU* b);
void fn_8002EB30(BU* a, int d);
void fn_8002EA20(BU* a, BU* b);
void fn_8002F14C(BU* p);
void fn_800282A0(Battle* b, BU* a, BU* d, int k);
void fn_80126D9C(BU* p, int n);
u8 fn_80118130(void* m, s8 x, s8 y);

static inline void reset(Battle* b) {
    fn_8002E3D4(&b->a);
    fn_8002E3D4(&b->b);
    fn_8002E3D4(&b->c);
    fn_80025FE0(b->log);
    b->f15e8 = 0;
    b->f15ec = 0;
    b->f15f0 = 0;
    b->f15f4 = 0;
    b->f15f8 = 0;
    b->f15fc = -1;
    b->f1604 = 0;
}

static inline void useItem(Battle* b, Slot* it) {
    fn_8002F05C(&b->a, it);
    if ((fn_801116B8(it)->flags & 0x4000) && fn_8011B77C(b->a.u.x12c, lbl_804CA510)) {
        b->f15ec |= 0x200;
        fn_80110D38(fn_80030CBC(&b->b));
    }
    fn_8002E910(&b->b, &b->a);
}

void fn_800269E4(Battle* b, const Spec& sa, const Spec& sd) {
    reset(b);
    fn_8002E6FC(&b->a, sa.u);
    fn_8002E6FC(&b->b, sd.u);
    fn_80126EB0(&b->a, sa.x, sa.y);
    fn_80126EB0(&b->b, sd.x, sd.y);
    fn_80114888(lbl_803EC898, 7);
    fn_80115DEC(lbl_803EC898, b->a.u.x102, b->a.u.y103, 100, 0x28);
    b->f15e8 = (*(s16**)(lbl_803EC898 + 0x15190))[b->b.u.x102 + b->b.u.y103 * 64];
    {
        Slot* it = sa.item;
        if (it == 0) {
            if (sa.f7 == 0) fn_8002ED4C(&b->a, b->f15e8, sa.idx);
            else fn_8002EF48(&b->a, sa.idx);
        } else {
            useItem(b, it);
        }
    }
    {
        Slot* it = sd.item;
        if (it == 0) {
            if (sd.f7 == 0) fn_8002ED4C(&b->b, b->f15e8, sd.idx);
            else fn_8002EF48(&b->b, sd.idx);
        } else {
            fn_8002F05C(&b->b, it);
        }
    }
    fn_8002EB30(&b->b, b->f15e8);
    fn_8002E910(&b->b, &b->a);
    fn_8002EA20(&b->b, &b->a);
    if (sa.fc) fn_8002F14C(&b->a);
    if (sd.fc) fn_8002F14C(&b->b);
}

static inline void two(Battle* b, Unit* a, Unit* d) {
    Spec sd = {d, d->x102, d->y103, -1, 0, 0, 1};
    Spec sa = {a, a->x102, a->y103, -1, 0, 0, 1};
    fn_800269E4(b, sa, sd);
}
void fn_80026C44(Battle* b, Unit* a, Unit* d) {
    two(b, a, d);
}

static inline void setupOne(Battle* b, Spec& s) {
    reset(b);
    fn_8002E6FC(&b->a, s.u);
    fn_80126EB0(&b->a, s.x, s.y);
    b->f15ec |= 1;
    {
        Slot* it = s.item;
        if (it == 0) {
            if (s.f7 == 0) fn_8002ED4C(&b->a, b->f15e8, s.idx);
            else fn_8002EF48(&b->a, s.idx);
        } else {
            useItem(b, it);
        }
    }
    if (s.fc) fn_8002F14C(&b->a);
}

void fn_80026CD8(Battle* b, Unit* u, s8 n) {
    Spec s = {u, u->x102, u->y103, n, 0, 0, 1};
    setupOne(b, s);
}

void fn_80027088(Battle* b, Unit* u, s8 n) {
    Spec s = {u, u->x102, u->y103, n, 0, 0, 1};
    setupOne(b, s);
    fn_800282A0(b, &b->a, 0, 0);
}

void fn_80027228(Battle* b, Unit* u, Slot* it) {
    fn_80026CD8(b, u, -1);
    useItem(b, it);
    fn_800282A0(b, &b->a, 0, 0);
}

static inline void posBody(Battle* b, Unit* u, Pos* p) {
    int y;
    reset(b);
    fn_8002E6FC(&b->a, u);
    fn_8002E738(&b->b);
    b->b.u.u3f0 = 0;
    fn_80114888(lbl_803EC898, 7);
    fn_80116098(lbl_803EC898, b->a.u.x102, b->a.u.y103, 100, 0x28);
    {
        y = p->y;
        int x = p->x;
        b->f15e8 = (*(s16**)(lbl_803EC898 + 0x15190))[x + y * 64];
        *((u8*)&b->b + 0x119) = p->f5;
        fn_80126D9C(&b->b, p->f4);
        b->b.u.f8 = 0;
        fn_80126EB0(&b->b, p->x, p->y);
        b->f15ec |= 0x101;
        fn_8002ED4C(&b->a, b->f15e8, -1);
        fn_8002F14C(&b->a);
        switch (fn_80118130(lbl_803EC898, x, y)) {
        case 0xb6:
            b->f15ec |= 0x80000;
            break;
        case 0xb1:
            b->f15ec |= 0x100000;
            break;
        case 0x71:
            b->f15ec |= 0x180000;
            break;
        }
    }
}
#pragma use_lmw_stmw on
void fn_80026EE8(Battle* b, Unit* u, Pos* p) {
    posBody(b, u, p);
}
#pragma use_lmw_stmw reset
}
