/* Item slot lists with the real slot class, 8011ABCC..8011B958. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {

extern u8* fn_8010B23C(void*);

#if TARGET_PC
/* Host: 8-byte slot as on the Wii (18 of them sit at fixed offsets in the person/job
   structs), so the item pointer is a 32-bit window offset. */
struct Slot {
    FE10_P32(u8) item;
    u8 uses;
    u8 flags;
    Slot(u8* i, u8 u, u8 f) : item(i), uses(u), flags(f) {
        if (item) {
            flags |= item[0x20] == 0 ? 1 : 0;
        }
    }
    Slot& operator=(const Slot& o) {
        item = o.item;
        uses = o.uses;
        flags = o.flags;
        return *this;
    }
};
static_assert(sizeof(Slot) == 8, "Slot");
#else
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
        /* volatile only forces the reload the original has. */
        item = *(u8* volatile*)&o.item;
        uses = o.uses;
        flags = o.flags;
        return *this;
    }
};
#endif

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

void fn_8011ABCC(Slot* list, const Slot& s) {
    SlotAdd(list, s);
}

void fn_8011AD1C(Slot* list, u8* item, u8 uses, u8 flags) {
    if (item) {
SlotAdd(list, Slot(item, uses, flags));
    }
}

void fn_8011AEA0(Slot* list, void* id, u8 uses, u8 flags) {
    u8* item = fn_8010B23C(id);
    if (item) {
SlotAdd(list, Slot(item, uses, flags));
    }
}

void fn_8011B060(Slot* list, void* id, u8 uses, u8 flags) {
    if (SlotFind(list, fn_8010B23C(id)) == 0) {
        u8* item = fn_8010B23C(id);
        if (item) {
SlotAdd(list, Slot(item, uses, flags));
        }
    }
}

void fn_8011B958(Slot* list, Slot* src) {
    int i;
    for (i = 0; i < 18; i++) {
        if (src && src->item) {
            SlotAdd(list, *src);
        }
        src++;
    }
}

}
