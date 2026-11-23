/* Skill slot lists and terrain name hashes, 8011B32C..8011D39C. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off

extern "C" {

extern u8* fn_8010B23C(void*);
extern u8* fn_8010B240(int);
extern u32 lbl_80413098[];
extern char* fn_800D0864(void*);
extern void fn_8008A5AC(void*, int);
extern void fn_8008A5C0(void*, int);

#if TARGET_PC
struct Slot {
    FE10_P32(u8) item; /* host: 32-bit window offset, see fn_8011ABCC.cpp */
    u8 uses;
    u8 flags;
};
#else
struct Slot {
    u8* item;
    u8 uses;
    u8 flags;
};
#endif

static inline Slot* SlotFind(Slot* e, u8* item) {
    int i;
    if (item == 0) {
        return 0;
    }
    for (i = 0; i < 18; i++) {
        if (e && e->item && e->item == item) {
            return e;
        }
        e++;
    }
    return 0;
}

void fn_8011B32C(Slot* list, u8* item) {
    if (item) {
        Slot* e = SlotFind(list, item);
        if (e) {
            e->item = 0;
        }
    }
}

void fn_8011B430(Slot* list, void* id) {
    u8* item = fn_8010B23C(id);
    if (item) {
        Slot* e = SlotFind(list, item);
        if (e) {
            e->item = 0;
        }
    }
}

Slot* fn_8011B560(Slot* list, void* id) {
    return SlotFind(list, fn_8010B23C(id));
}

BOOL fn_8011B680(Slot* list, u8* item) {
    return SlotFind(list, item) != 0;
}

BOOL fn_8011B77C(Slot* list, void* id) {
    return SlotFind(list, fn_8010B23C(id)) != 0;
}

int fn_8011B8A4(Slot* s) {
    int r = 0;
    int i;
    for (i = 0; i < 18; i++) {
        if (s && s->item) {
            r += (s->flags & 2) ? 0 : s->item[0x1e];
        }
        s++;
    }
    return r;
}

void fn_8011BD20(void** p) {
    *p = 0;
}

void fn_8011C2FC(Slot* a, Slot* b) {
    u8* item = a->item;
    u8 uses = a->uses;
    u8 flags = a->flags;
    a->item = b->item;
    a->uses = b->uses;
    a->flags = b->flags;
    b->item = item;
    b->uses = uses;
    b->flags = flags;
}

static inline u32 StrHash(const char* s) {
    u8 c;
    u32 h = 0;
    while ((s8)(c = *s) != 0) {
        h += c;
        s++;
        h <<= 4;
    }
    return h;
}

static inline u8 TerrainId(u32 h) {
    u32* d = lbl_80413098;
    int i;
    for (i = 0; i < 0xc7; i++) {
        if (h == *d) {
            switch (i) {
            case 0xb0:
            case 0xb6:
                return 0xb6;
            }
            return i;
        }
        d++;
    }
    return 0;
}

char* fn_8011D39C(void* p) {
    return fn_800D0864(*(void**)((u8*)p + 4));
}

}
