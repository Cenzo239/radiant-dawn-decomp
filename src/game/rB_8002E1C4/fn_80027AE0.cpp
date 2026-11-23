#include "game/rB_8002E1C4/battle.h"

/* Status effect strike, and the battle stat recalculation. */
struct ItemF { u32 hi, lo; };
extern void* lbl_804CA6A0;
extern "C" {
void fn_8002600C(void* log, int code, int v);
void fn_80026208(void* log, int k);
void fn_80026288(void* log);
void fn_800282A0(Battle* b, BU* a, BU* d, int k);
Slot* fn_80030CBC(BU* p);
s16 fn_8012386C(BU* p);
void fn_80108A20(void* p, BU* u, int k);
void fn_80108C14(void* p, BU* u, int k);
int fn_8011B77C(void* list, void* key);
ItemF* fn_801116B8(Slot* s);
void fn_8002A780(Battle* b, BU* a, BU* d, int dmg, int code, int heal);
void fn_8002A8A4(Battle* b, BU* a, BU* d);
void fn_8002AFBC(Battle* b, BU* a, BU* d);
void fn_8002ABE0(Battle* b, BU* a, BU* d);
void fn_8002F220(BU* a, BU* d);
void fn_8002FAB0(BU* a);
void fn_8002FB78(BU* a);
void fn_8002FA8C(BU* a, BU* d);
void fn_8002FD84(BU* a, BU* d);
void fn_8002FEC0(BU* a);
int fn_801237EC(BU* a);
void fn_8003092C(BU* a);
#define BT ((Battle*)lbl_803C8E80)

void fn_80027AE0(Battle* b, BU* a, BU* d) {
    if (a->x486 == 0) return;
    if (a->x486 == 0x64) {
        if (a->x488 < 2) return;
        if (fn_80030CBC(d)->data == 0) return;
    }
    fn_8002600C(b->log, 0x24, 0);
    fn_8002600C(b->log, 0x28, 0);
    fn_800282A0(b, a, d, 0);
    fn_80026208(b->log, 0x74);
    switch (a->x486) {
    case 0x64:
        fn_8002600C(b->log, 0x64, 0);
        a->x488 /= 2;
        break;
    case 0x69:
        fn_8002600C(b->log, 0x69, 0);
        a->x488 /= 2;
        break;
    case 0x58:
    case 0x5a:
        fn_8002600C(b->log, (u8)a->x486, 0);
        { s16 v = a->x44a; a->x488 = fn_8012386C(d) - v; }
        break;
    case 0x57:
        fn_8002600C(b->log, 0x57, 0);
        fn_8002600C(b->log, 0x82, 0);
        fn_80108A20(a->u.x110, a, 1);
        a->x488 = 0;
        break;
    case 0x59:
        fn_8002600C(b->log, 0x59, 0);
        fn_8002600C(b->log, 0x87, 0);
        fn_80108C14(a->u.x110, a, 1);
        a->x488 = 0;
        break;
    }
    if (a->x488 < 0) a->x488 = 0;
    if (a->x488 > 0x7f) a->x488 = 0x7f;
    if (fn_8011B77C(d->u.x12c, lbl_804CA6A0) && !(fn_801116B8(fn_80030CBC(d))->lo & 0x4000) && a->x488 > a->u.s114 - 1) {
        a->x488 = a->u.s114 - 1;
    }
    if (a->x488 == 0) fn_8002600C(b->log, 0x6d, 0);
    fn_80026288(b->log);
    b->f15e4 = (b->f15e4 ^ 1) != 0;
    fn_80026208(b->log, 0x75);
    fn_8002A780(b, d, a, a->x488, 0x6e, 0);
    fn_80026288(b->log);
    fn_8002600C(b->log, 0x2a, 0);
}

static inline int ne(int a, int b) { return a != b; }
#define DIFF(U, c0, c1, c2, c3, c4, c5) \
    { int c = (s16)fn_801237EC(U) != U->x468; if (c) { int m = fn_801237EC(U); fn_8002600C(b->log, c0, (s16)m); } } \
    if (U->x46a != U->u.s114) fn_8002600C(b->log, c1, U->u.s114); \
    if (U->x46c != U->x448) fn_8002600C(b->log, c2, U->x448); \
    if (U->x46e != U->x44a) fn_8002600C(b->log, c3, U->x44a); \
    if (U->x470 != U->x452) fn_8002600C(b->log, c4, U->x452); \
    if (U->x472 != U->x458) fn_8002600C(b->log, c5, U->x458);

void fn_800282A0(Battle* b, BU* a, BU* d, int quiet) {
    if (!(b->f15ec & 1)) {
        fn_8002A8A4(b, a, d);
        fn_8002AFBC(b, a, d);
        fn_8002ABE0(b, a, d);
    }
    fn_8002F220(a, d);
    if (!(b->f15ec & 1)) fn_8002F220(d, a);
    if (!(a->u.f108 & 0x800)) {
        fn_8002FAB0(a);
        if (!(b->f15ec & 1)) fn_8002FAB0(d);
        fn_8002FB78(a);
        if (!(b->f15ec & 1)) fn_8002FB78(d);
    }
    if (!(b->f15ec & 1)) {
        fn_8002FA8C(a, d);
        fn_8002FA8C(d, a);
        fn_8002FD84(a, d);
        fn_8002FD84(d, a);
        fn_8002FEC0(a);
        fn_8002FEC0(d);
    }
    if (BT->f15ec & 0x100) {
        a->x452 = 100;
        a->x458 = 0;
    }
    if (quiet == 0) {
        fn_80026208(b->log, 0x73);
        DIFF(a, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e)
        if (!(b->f15ec & 1)) {
            DIFF(d, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95)
            fn_8003092C(d);
        }
        fn_8003092C(a);
        fn_80026288(b->log);
    }
}
}
