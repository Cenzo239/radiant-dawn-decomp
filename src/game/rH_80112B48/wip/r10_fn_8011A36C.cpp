/* NOT MATCHING, not compiled. fn_8011A36C: 27 words: walker and the item temp swapped. */
/* NOT MATCHING, not compiled. fn_8011A36C: 31 words, only the final add loop has walker and slot pointer swapped (want walker r6, slot r7). */
/* Item slot lists with the real slot class, 8011A36C..8011B958. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {

extern u8* fn_8010B23C(void*);

struct Slot {
    u8* item;
    u8 uses;
    u8 flags;
    Slot(u8* i, u8 u, u8 f) : item(i), uses(u), flags(f) {
        if (item) {
            flags |= item[0x20] == 0 ? 1 : 0;
        }
    }
    Slot& operator=(const Slot& o) {
        item = *(u8* volatile*)&o.item;
        uses = o.uses;
        flags = o.flags;
        return *this;
    }
};

struct SlotT {
    u8* item;
    u8 uses;
    u8 flags;
    SlotT() : item(0), uses(2), flags(0) {
        if (item) {
            flags |= item[0x20] == 0 ? 1 : 0;
        }
    }
};

struct SlotT2 { u8* item; u8 uses; u8 flags;
 SlotT2& operator=(const Slot& o) { item = *(u8* volatile*)&o.item; uses = o.uses; flags = o.flags; return *this; } };
struct SlotLess {
    char c;
    SlotLess() {}
};

extern void fn_8011BD2C(Slot*, Slot*, const SlotLess&);

static inline Slot* SlotFind(Slot* list, u8* item) { Slot* e; int i; if (item == 0) { return 0; } e = list; for (i = 0; i < 18; i++) { if (e && e->item && e->item == item) { return e; } e++; } return 0; }
static inline Slot* SlotFindR(Slot* list, const Slot& s) { Slot* e;u8* it;int i; it = s.item; if (it == 0) { return 0; } e = list; for (i = 0; i < 18; i++) { if (e && e->item && e->item == it) { return e; } e++; } return 0; }
static inline Slot* SlotEmpty(Slot* list) {
    int i;
    for (i = 0; i < 18; i++) {
        if (list[i].item == 0) {
            return &list[i];
        }
    }
    return 0;
}

static inline void SlotAdd(Slot* list, const Slot& s) {
    Slot* e = SlotFindR(list, s);
    if (e == 0) {
        e = SlotEmpty(list);
    }
    *e = s;
}

static inline u8 SlotCount(Slot* p) { Slot* q = p;u8 n = 0;int i; for (i = 0; i < 18; i++) { if (q && q->item) { n++; } q++; } return n; }
static inline void Srt(Slot* a, Slot* b, SlotLess c) { fn_8011BD2C(a, b, c); }
static inline void AddF(Slot* list, const Slot& v) {
    Slot* e = SlotFindR(list, v); Slot* f = e; if (f == 0) { f = SlotEmpty(list); } *f = v;
}
static inline void AddG(Slot* list, const Slot& v, Slot*& e, Slot*& f) {
    e = SlotFindR(list, v); f = e; if (f == 0) { f = SlotEmpty(list); } *f = v;
}
void fn_8011A36C(Slot* list) {
    /*P*/
    Slot* f;
    Slot* w;
    Slot* e;
    int i2;
    int k;
/*E*/
    SlotT t[18];
    k = 0;
    if (SlotCount(list) > 1) {
        Slot* p = list;
        int i;
        for (i = 0; i < 18; i++) {
            if (p && p->item && p->uses == 2) {
*(Slot*)&t[k++] = *p; p->item = 0;
            }
            p++;
        }
        if (SlotCount(list)) {
Srt(list, list + 18, SlotLess());
        }
w = (Slot*)t;
for (i2 = 0; i2 < k; i2++) { AddG(list, *w, e, f); w++; }
    }
}

}
