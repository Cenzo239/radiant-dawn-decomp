/* EQUIVALENT (regs, round 19b): fn_8011C330, median-of-three step of the skill slot quicksort: orders *a, *b, *c so the median ends in *c (the pivot slot). The ordering predicate fn_8011A804 is inlined three times (local copy below).
 * Caveat: the swap goes through a plain three-member view `Raw` so the copy is member-wise; a port should use one SkillSlot type and std::swap. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off
extern "C" {
struct SF { u8 pad : 6; u8 hide : 1; u8 on : 1; };
struct SkillSlot { u8* item; u8 kind; SF f; };
struct SlotLess { char c; };
static inline u8 KB(BOOL h, u8* it) { if (h) { return 0; } return it[0x1e]; }

static inline BOOL SlotCmp(SF fa, SF fb, u8* ia, u8* ib) {
    BOOL hb;BOOL ha;u8 kb;u8 ka;hb = fb.hide; kb = KB(hb, ib); ha = fa.hide; ka = KB(ha, ia); if (ka != kb) {u8 k2 = KB(hb, ib); u8 k3 = KB(ha, ia); return k3 < k2;}
    return ia[0x1c] < ib[0x1c];
}
static inline BOOL SlotCmpP(SkillSlot* a, SkillSlot* b, u8* ia, u8* ib) {
    BOOL hb;BOOL ha;u8 kb;u8 ka;hb = b->f.hide; kb = KB(hb, ib); ha = a->f.hide; ka = KB(ha, ia); if (ka != kb) {u8 k2 = KB(hb, ib); u8 k3 = KB(ha, ia); return k3 < k2;}
    return ia[0x1c] < ib[0x1c];
}
/* Local inline copy of fn_8011A804: the original inlines it here. */
static inline BOOL SlotLessCall(SkillSlot* a, SkillSlot* b) {
    u8* ib = b->item; u8* ia;
    if (ib == 0) { return 1; }
    ia = a->item;
    if (ia == 0) { return 0; }
    if (a->kind == 0) {
        SF fa = a->f;
        if (fa.on) {
            if (b->f.on) { return SlotCmp(fa, b->f, ia, ib); }
            return 1;
        }
        if (b->kind == 0) { return SlotCmp(fa, b->f, ia, ib); }
        return 1;
    }
    if (b->kind == 0) { return 0; }
    if (a->kind == 1) {
        SF fa = a->f;
        if (fa.on) {
            if (b->f.on) { return SlotCmp(fa, b->f, ia, ib); }
            return 1;
        }
        if (b->kind == 1) { return SlotCmp(fa, b->f, ia, ib); }
        return 1;
    }
    if (b->kind == 1) { return 0; }
    return SlotCmpP(a, b, ia, ib);
}
struct Raw { u8* item; u8 kind; u8 fl; };
static inline void SwapSlot(SkillSlot* a, SkillSlot* b) {
    Raw t; t = *(Raw*)a;
    *(Raw*)a = *(Raw*)b;
    *(Raw*)b = t;
}
void fn_8011C330(SkillSlot* a, SkillSlot* b, SkillSlot* c, SlotLess* cmp) {
    BOOL x = !SlotLessCall(c, a);
    BOOL y = !SlotLessCall(b, c);
    if (x && y) {
        return;
    }
    if (!x && !y) {
        SwapSlot(a, b);
        return;
    }
    if (SlotLessCall(b, a)) {
        SwapSlot(a, b);
    }
    if (x) {
        SwapSlot(b, c);
    } else {
        SwapSlot(a, c);
    }
}
}
