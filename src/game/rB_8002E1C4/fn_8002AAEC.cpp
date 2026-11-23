#define lbl_803C8E80 lbl_unused
#include "game/rB_8002E1C4/battle.h"
#undef lbl_803C8E80

struct Rec7 { u8 a, b, c, d, e; s8 f; u8 g; };
struct MapS {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0xd18e - 0x100d];
    u16 xd18e[64 * 64];
};
struct Roll { u8 pad[0xa3]; u8 xa3; };
extern MapS lbl_803EC898;
#define M ((MapS*)&lbl_803EC898)
extern Roll lbl_803C8DA0;
extern const char lbl_80361338[];
extern u8* lbl_804CB810;
extern void* lbl_804CA590;
extern void* lbl_804CA6DC;
extern const f32 lbl_804CCCC8;
extern const f64 lbl_804CCCD8;
extern const f64 lbl_804CCCE0;
extern "C" {
u8* fn_80116A30(MapS* m, s8 x, s8 y);
f32 fn_80117200(MapS* m, s8 x, s8 y, u8 c);
int fn_801148D8(MapS* m, int n);
void* fn_80078D9C(int n, const char* s, int k);
void fn_80078E24(void* p);
void fn_80114944(MapS* m, int n, void* p);
void fn_80114A44(MapS* m, int n, void* p);
void fn_801148CC(MapS* m, void* p);
void fn_80114B44(MapS* m, int a, int b);
void fn_80114888(MapS* m, int n);
Slot* fn_80030CBC(BU* p);
ItemD* fn_801116B8(Slot* it);
int fn_801107C0(void* d, BU* u);
int fn_801107A0(void* d, BU* u);
void fn_80115DEC(MapS* m, s8 x, s8 y, u8 a, u8 b);
f32 fn_80114230(MapS* m, s8 x, s8 y);
int fn_8011799C(MapS* m, s8 x, s8 y);
int fn_8011B77C(void* list, void* key);
Unit* fn_80127B68(Unit* u);
Unit* fn_8012E3A4(Unit* u);
f32 fn_80127868(Unit* u);
Rec7 fn_801278B8(Unit* u, f32 bio);
int fn_8012E9B4(Unit* a, Unit* b);
u8 fn_8012E8BC(Unit* a, s8 k);
int fn_80089D68(int n);
int fn_800262A8(void* log, int k);
void fn_80126EB0(Unit* u, s8 x, s8 y);
void fn_800269E4(Battle* b, const Spec& a, const Spec& d);
void fn_8002E6FC(BU* p, Unit* u);
void fn_8002B2AC(Battle* b, int a, int k);
extern Battle lbl_803C8E80;
#define BT (&lbl_803C8E80)

int fn_8002AAEC(BU* a, BU* d) {
    u8* r = fn_80116A30(M, d->u.x102, d->u.y103);
    s8 x = a->u.x102;
    s8 y = a->u.y103;
    u8 c = *r;
    f32 k = lbl_804CCCC8;
    while (!(c & 0x40)) {
        if (k <= (f32)__fabs(fn_80117200(M, x, y, c))) return 1;
        if (c & 1) x--;
        else if (c & 2) x++;
        else if (c & 4) y++;
        else if (c & 8) y--;
        c = *++r;
    }
    return 0;
}

#pragma use_lmw_stmw on
Unit* fn_8002D8D8(Battle* b);
int fn_8002DBA0(Battle* b, int k) {
    if (fn_800262A8(b->log, 0x16)) {
    Unit* a = b->a.u.u3f0;
    Unit* t = b->b.u.u3f0;
    Unit* c = fn_8002D8D8(b);
    if (c) {
    int tx, ty, cx, cy;
    cx = c->x102;
    cy = c->y103;
    tx = t->x102;
    ty = t->y103;
    fn_80126EB0(t, cx, cy);
    fn_80126EB0(c, tx, ty);
    {
        Spec sd = {c, c->x102, c->y103, -1, 0, 0, 1};
        Spec sa = {a, a->x102, a->y103, -1, 0, 0, 1};
        fn_800269E4(BT, sa, sd);
    }
    BT->b.x481 = 1;
    fn_8002E6FC(&BT->c, t);
    BT->f15ec |= 0x40000;
    fn_8002B2AC(BT, k, 0);
    fn_80126EB0(t, tx, ty);
    fn_80126EB0(c, cx, cy);
    return 1;
    }
    }
    return 0;
}
#pragma use_lmw_stmw reset
}
