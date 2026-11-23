/* fn_8006CE30: exact (round m7), from wip/r16_fn_8006CE30.cpp. Only the declaration order changed:
 * log, g, i first, then the stat differences as d8, d7, d9, d6..d1, d10. Register rank here is not
 * "first declared gets r31": the six longest-lived differences (d1..d6) are coloured first in reverse
 * declaration order, then b and the call temporary, then the short-lived d8, d7, d9 in declaration order. */
/* Battle: experience, 8006C2D0..8006DE18. */
#include "game/rO_80065D64/trap.h"
#pragma auto_inline off

struct BU {
    Unit u;              /* 0 */
    Unit* real;          /* 3F0 */
    u8 pad3F4[0x47F - 0x3F4];
    u8 gain;             /* 47F */
    u8 pad480[0x484 - 0x480];
    u8 b484;             /* 484 */
    u8 pad485[0x492 - 0x485];
    u8 b492;             /* 492 */
    u8 b493[0x4A0 - 0x493]; /* 493 */
};

struct Battle {
    BU a;                /* 0 */
    BU b;                /* 4A0 */
    u8 pad940[0xDE0 - 0x940];
    u8 log[0x15EC - 0xDE0]; /* DE0 */
    u32 flags;           /* 15EC */
};


extern "C" {
extern void fn_8002600C(void*, int, int);
struct BattleLog {
    u8 x[0x20];    /* 0 */
    s16 a[0x20];   /* 20 */
    s16 b[0x20];   /* 60 */
    u8 a0;
    u8 a1;
    u8 a2;
    u8 a3;
    u8 a4;
    s8 a5;
    u8 a6;
    u8 padA7[0xC8 - 0xA7];
    u32 c8;
    u32 cc;
};
extern BattleLog lbl_803C8DA0;
extern Battle lbl_803C8E80;
extern void fn_80026C44(Battle*, void*, void*);
extern void fn_8011FFD0(BU*);
extern void fn_8002ED4C(BU*, int, int);
extern int fn_80122720(BU*);
extern int fn_80122770(BU*);
extern int fn_80122880(BU*);
extern int fn_80122990(BU*);
extern int fn_80122AA0(BU*);
extern int fn_80122BB0(BU*);
extern int fn_80122C20(BU*);
extern int fn_80122D30(BU*);
extern int fn_8012408C(BU*);
extern int fn_8012401C(BU*);
extern void fn_8002CEB0(Battle*);

#pragma push
#pragma use_lmw_stmw on
void fn_8006CE30(Battle* b, void* x) {
    u8* log;
    BattleLog* g;
    int i;
    s8 d8;
    s8 d7;
    s8 d9;
    s8 d6;
    s8 d5;
    s8 d4;
    s8 d3;
    s8 d2;
    s8 d1;
    s8 d10;
    fn_80026C44(b, x, x);
    if (lbl_803C8DA0.a1) {
        b->flags |= 0x4000;
        lbl_803C8DA0.a1 = 0;
    }
    fn_8011FFD0(&b->b);
    b->flags |= 0x2000;
    fn_8002ED4C(&b->a, 0, -1);
    fn_8002ED4C(&b->b, 0, -1);
    d1 = fn_80122720(&b->b) - fn_80122720(&b->a);
    d2 = fn_80122770(&b->b) - fn_80122770(&b->a);
    d3 = fn_80122880(&b->b) - fn_80122880(&b->a);
    d4 = fn_80122990(&b->b) - fn_80122990(&b->a);
    d5 = fn_80122AA0(&b->b) - fn_80122AA0(&b->a);
    d6 = fn_80122BB0(&b->b) - fn_80122BB0(&b->a);
    d7 = fn_80122C20(&b->b) - fn_80122C20(&b->a);
    d8 = fn_80122D30(&b->b) - fn_80122D30(&b->a);
    d9 = fn_8012408C(&b->b) - fn_8012408C(&b->a);
    d10 = fn_8012401C(&b->b) - fn_8012401C(&b->a);
    log = b->log;
    fn_8002600C(log, 0x32, d1);
    fn_8002600C(log, 0x33, d2);
    fn_8002600C(log, 0x34, d3);
    fn_8002600C(log, 0x35, d4);
    fn_8002600C(log, 0x36, d5);
    fn_8002600C(log, 0x37, d6);
    fn_8002600C(log, 0x38, d7);
    fn_8002600C(log, 0x39, d8);
    fn_8002600C(log, 0x3A, d9);
    fn_8002600C(log, 0x3B, d10);
    fn_8002CEB0(b);
    g = &lbl_803C8DA0;
    g->a1 = 0;
    g->a2 = 0;
    g->a3 = 0;
    g->a4 = 0;
    g->a0 = 0;
    for (i = 0; i < 0x20; i++) {
        lbl_803C8DA0.x[i] = 0;
        lbl_803C8DA0.a[i] = 0;
        lbl_803C8DA0.b[i] = 12345;
    }
    lbl_803C8DA0.a5 = -1;
    lbl_803C8DA0.a6 = 0;
    lbl_803C8DA0.c8 = 0;
    lbl_803C8DA0.cc = 0;
}

#pragma pop
}
