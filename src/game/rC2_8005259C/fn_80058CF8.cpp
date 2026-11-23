#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on
extern "C" void fn_8011FDD8(void*, int); extern "C" void fn_8011FE74(void*, int);
typedef struct ULink { u8 pad[0xe4]; struct ULink* n4; struct ULink* n8; u8 padec[0x10c-0xec]; u32 flags; } ULink;
typedef struct UList { ULink* last; ULink* first; u8 pad[0x3c-8]; ULink* first2; ULink* last2; } UList;
#define L ((UList*)lbl_804CB814)
extern "C" void fn_80058CF8(void) {
        ULink* nx;
    ULink* end;
    ULink* u;
    ULink* u2;
    ULink* end2;
    ULink* u3;
    ULink* nx2;
    ULink* nx3;

    end = L->last;
    for (u = L->first; u; u = nx) {
        nx = u->n4;
        if (u->flags & 0x10000) fn_8011FDD8((Unit*)u, 0);
        if (u == end) break;
    }
    end2 = L->last2;
    for (u2 = L->first2; u2; u2 = nx2) {
        nx2 = u2->n8;
        if (u2->flags & 0x200000) fn_8011FE74((Unit*)u2, 5);
        if (u2 == end2) break;
    }
    for (u3 = L->first2; u3; u3 = nx3) {
        nx3 = u3->n8;
        fn_8011FE74((Unit*)u3, 0);
        u3->flags |= 0x10000dcULL;
    }
    fn_80114D00(lbl_803EC898);
    fn_801484B4(0);
}
