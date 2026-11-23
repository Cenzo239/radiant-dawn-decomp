/* NOT MATCHING, not compiled. fn_8011A804: 41 words of volatile colouring only (want hb r7, kb r5, a flags r8). fn_8011CDC0 is the same comparator inlined into a selection sort, not attempted. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off
extern "C" {
struct SF { u8 pad : 6; u8 hide : 1; u8 on : 1; };
struct SkillSlot { u8* item; u8 kind; SF f; };
struct SlotLess { char c; };
static inline u8 KB(BOOL h, u8* it) { if (h) { return 0; } return it[0x1e]; }
static inline BOOL NE(u8 a, u8 b) { return a != b; }
static inline BOOL LT(u8 a, u8 b) { return a < b; }

static inline u8 KeyS(SF f, u8* it) { if (f.hide) { return 0; } return it[0x1e]; }
static inline BOOL SlotCmp(SF fa, SF fb, u8* ia, u8* ib) {
    BOOL hb;BOOL ha;u8 kb;u8 ka;hb = fb.hide; kb = KB(hb, ib); ha = fa.hide; ka = KB(ha, ia); if (ka != kb) {u8 k2 = KB(hb, ib); u8 k3 = KB(ha, ia); return k3 < k2;}
    return ia[0x1c] < ib[0x1c];
}
BOOL fn_8011A804(SlotLess* c, SkillSlot* a, SkillSlot* b) {
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
    return SlotCmp(a->f, b->f, ia, ib);
}
}
