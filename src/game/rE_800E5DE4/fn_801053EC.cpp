#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct SlotEnt {
    void* key;
    u8 pad4[0x24];
} SlotEnt;
typedef struct SlotTbl {
    s32 count;
    SlotEnt* ents;
} SlotTbl;
typedef struct Item { u8 pad[5]; u8 fl : 1; u8 fl2 : 7; u8 pad6[0x22]; } Item;

extern "C" {
extern void fn_80110D38(SlotEnt*);
extern int fn_801116F4(SlotEnt*);
extern void fn_80111C78(SlotEnt*, Item*);
extern void fn_80111B34(Item*);
extern void fn_80110BFC(Item*, void*);
extern void fn_80111C24(Item*, int);

static inline int FreeSlot(SlotTbl* t) {
    int i;
    for (i = 0; i < t->count; i++) {
        if (t->ents[i].key == NULL) {
            return i;
        }
    }
    return -1;
}
static inline int Oldest(SlotTbl* t) {
    int m = 999999;
    int best = -1;
    int i;
    for (i = 0; i < t->count; i++) {
        if (t->ents[i].key) {
            int k = fn_801116F4(&t->ents[i]);
            if (m > k) {
                m = k;
                best = i;
            }
        }
    }
    return best;
}
static inline int Add(SlotTbl* t, Item* it) {
    int i;
    it->fl = 0;
    i = FreeSlot(t);
    if (i < 0) return 0;
    fn_80111C78(&t->ents[i], it);
    return 1;
}
#pragma use_lmw_stmw on
void fn_801053EC(SlotTbl* t, Item* it) {
    if (!Add(t, it)) {
        fn_80110D38(&t->ents[Oldest(t)]);
        Add(t, it);
    }
}
void fn_80105558(SlotTbl* t, void* a) {
    Item x;
    int r;
    fn_80111B34(&x);
    fn_80110BFC(&x, a);
    r = Add(t, &x);
    fn_80111C24(&x, -1);
    if (!r) {
        Item y;
        fn_80110D38(&t->ents[Oldest(t)]);
        fn_80111B34(&y);
        fn_80110BFC(&y, a);
        Add(t, &y);
        fn_80111C24(&y, -1);
    }
}
#pragma use_lmw_stmw off
}
