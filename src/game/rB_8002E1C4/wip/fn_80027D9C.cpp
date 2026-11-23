/* NEAR MISS: fn_80027D9C. Structure is right (317 of 321 words before register fixes); saved-register ranking is wrong: wants n r31, got r30, uses r29, params r24..r28, f r20. Wrapping the body in an inline moves the params down, but a head-level s8 f pushes them back up. */
#include "game/rB_8002E1C4/battle.h"

/* One combatant's strike sequence, repeated for Astra, Adept and doubling skills. */
struct Rec7 { s8 a, b, c, d, e, f, g; };
struct ItemF { u32 hi, lo; };
struct Roll {
    u8 x0[0x20];
    u16 x20[0x40];
    u8 xa0, xa1, xa2, xa3;
};
extern Roll lbl_803C8DA0;
extern void* lbl_804CA580;
extern void* lbl_804CA5E8;
extern void* lbl_804CA5E4;
extern void* lbl_804CA690;
extern "C" {
Slot* fn_80030CBC(BU* p);
int fn_8010931C(void* p);
int fn_8011B77C(void* l, void* k);
ItemF* fn_801116B8(Slot* s);
f32 fn_80127868(BU* p);
Rec7 fn_801278B8(BU* p, f32 bio);
s16 fn_80123AC4(BU* p);
s16 fn_80123BF0(BU* p);
int fn_80089D68(int n);
void fn_800263A0(Roll* r, int k);
void fn_80026360(Roll* r, int k);
void fn_80026440(Roll* r, int k);
void fn_8002FFDC(BU* p, Slot* s);
void fn_80025FD0(Roll* r);
void fn_8002600C(void* log, int code, int v);
void fn_800285CC(Battle* b, BU* a, BU* d, int i);
void fn_80027AE0(Battle* b, BU* a, BU* d);
#define BT ((Battle*)lbl_803C8E80)

static inline int rollP(int n) {
    if (BT->f15ec & 0x4000) {
        if (lbl_803C8DA0.xa3) return 1;
        return 0;
    }
    return fn_80089D68(n);
}
static inline int over(Battle* b) {
    if (b->a.u.s114 == 0) return 1;
    return b->b.u.s114 == 0;
}

#pragma use_lmw_stmw on
static inline void fn_80027D9C_b(Battle* b, BU* a, BU* d, u8 code, int follow) {
    a->x482 = 0;
    if (fn_80030CBC(a)->data && !fn_8010931C(a->u.x110) && !fn_8011B77C(a->u.x12c, lbl_804CA580)) {
    {
    int n = 1;
    if (fn_801116B8(fn_80030CBC(a))->lo & 0x100) n = 2;
    {
    int got = 0;
    int uses = 0;
    if (fn_80030CBC(a)->data) uses = fn_80030CBC(a)->uses;
    f32 bioA = fn_80127868(a);
    Rec7 r = fn_801278B8(a, bioA);
    s8 f = r.f;
    f32 bioB = fn_80127868(d);
    fn_801278B8(d, bioB);
    {
        int i;
        for (i = 0; i < n; i++) {
            int k = i + got;
            if (!(lbl_803C8DA0.x20[lbl_803C8DA0.xa0 + k] & 1)) {
                if (!fn_8011B77C(a->u.x12c, lbl_804CA5E8)) continue;
                if (b->f15ec & 0x100) continue;
                if (a->x48a) continue;
                if (!rollP(f + fn_80123AC4(a) / 2)) continue;
                if (uses < k + 5) continue;
            }
            fn_800263A0(&lbl_803C8DA0, k);
            got += 4;
        }
    }
    if (got > 0) {
        n += got;
    } else {
        int i;
        for (i = 0; i < n; i++) {
            int k = i + got;
            if (!(lbl_803C8DA0.x20[lbl_803C8DA0.xa0 + k] & 0x4000)) {
                if (!fn_8011B77C(a->u.x12c, lbl_804CA5E4)) continue;
                if (b->f15ec & 0x100) continue;
                if (a->x48a) continue;
                if (!rollP(f + fn_80123AC4(a) / 2)) continue;
                if (uses < k + 2) continue;
            }
            fn_80026360(&lbl_803C8DA0, k);
            got += 1;
        }
        if (got > 0) {
            n += got;
        } else if ((lbl_803C8DA0.x20[lbl_803C8DA0.xa0] & 8)
                   || (fn_8011B77C(a->u.x12c, lbl_804CA690) && rollP(f + fn_80123BF0(a)) && uses >= n * 2)) {
            fn_80026440(&lbl_803C8DA0, n);
            n *= 2;
        }
    }
    }
    fn_8002FFDC(a, fn_80030CBC(a));
    a->x486 = 0;
    a->x488 = 0;
    {
        int i;
        for (i = 0; i < n; i++) {
            u8 c = lbl_803C8DA0.x0[lbl_803C8DA0.xa0];
            if (c & 8) return;
            if (c & 0x10) {
                fn_80025FD0(&lbl_803C8DA0);
            } else {
                fn_8002600C(b->log, 0x24, 0);
                fn_8002600C(b->log, code, 0);
                if (follow) fn_8002600C(b->log, 0x29, 0);
                fn_800285CC(b, a, d, i);
                fn_8002600C(b->log, 0x2a, 0);
                if (over(b)) return;
                if (fn_80030CBC(a)->data == 0) break;
            }
        }
    }
    fn_80027AE0(b, a, d);
    }
    } else {
        fn_8002600C(b->log, 0x24, 0);
        fn_8002600C(b->log, code, 0);
        if (follow) fn_8002600C(b->log, 0x29, 0);
        fn_8002600C(b->log, 0x71, 0);
        fn_8002600C(b->log, 0x2a, 0);
    }
}
void fn_80027D9C(Battle* b, BU* a, BU* d, u8 code, int follow) {
    fn_80027D9C_b(b, a, d, code, follow);
}
#pragma use_lmw_stmw reset
}
