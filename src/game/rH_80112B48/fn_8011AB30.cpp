/* Item slot lists (8-byte slots: item, uses, flags), 8011AB30..8011AEA0. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {

extern u8* fn_8010B23C(void*);

struct Slot {
    u8* item;
    u8 uses;
    u8 flags;
};

u8 fn_8011AB30(Slot* p) {
    u8 n = 0;
    int i;
    for (i = 0; i < 18; i++) {
        if (p && p->item && p->item[0x1f]) {
            n++;
        }
        p++;
    }
    return n;
}

static inline Slot* SlotFind(Slot* list, u8* item) {
    Slot* e;
    int i;
    if (item == 0) {
        return 0;
    }
    e = list;
    for (i = 0; i < 18; i++) {
        if (e && e->item && e->item == item) {
            return e;
        }
        e++;
    }
    return 0;
}

static inline Slot* SlotEmpty(Slot* list) {
    int i;
    for (i = 0; i < 18; i++) {
        if (list[i].item == 0) {
            return &list[i];
        }
    }
    return 0;
}

struct SlotE {
    u8* item;
    u8 uses;
    u8 flags;
    SlotE& operator=(const SlotE& o) {
        item = o.item;
        uses = o.uses;
        flags = o.flags;
        return *this;
    }
};

static inline void SlotAdd(Slot* list, const SlotE& s) {
    SlotE* e = (SlotE*)SlotFind(list, s.item);
    if (e == 0) {
        e = (SlotE*)SlotEmpty(list);
    }
    *e = s;
}

static inline void SlotInit(Slot* s, u8* item, u8 uses, u8 flags) {
    s->item = item;
    s->uses = uses;
    s->flags = flags;
    if (item) {
        s->flags |= (item[0x20] == 0);
    }
}

}
