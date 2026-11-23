#include "game/rE_800E5DE4/types.h"

/* Fixed table of 0x28-byte slots: +0 count, +4 entries; a slot is free when
 * its first word is NULL (guessed). */
typedef struct SlotEnt {
    void* key;
    u8 pad4[0x24];
} SlotEnt;

typedef struct SlotTbl {
    s32 count;
    SlotEnt* ents;
} SlotTbl;

typedef struct GameCfg {
    u8 pad0[0x8A];
    u8 unk8A; /* 0x8A */
} GameCfg;

extern void fn_80110D38(SlotEnt*);
extern u8 lbl_803CAB38[];
extern void* lbl_803856A0[];
extern GameCfg* fn_8006074C(void*);

void fn_80105154(void) {
}

int fn_80105158(SlotTbl* t) {
    int n = 0;
    int i;
    for (i = 0; i < t->count; i++) {
        if (t->ents[i].key) {
            n++;
        }
    }
    return n;
}

int fn_80105194(SlotTbl* t) {
    int i;
    for (i = 0; i < t->count; i++) {
        if (t->ents[i].key == NULL) {
            return i;
        }
    }
    return -1;
}

int fn_80105328(SlotTbl* t, void* key) {
    int i;
    for (i = 0; i < t->count; i++) {
        if (t->ents[i].key == key) {
            return i;
        }
    }
    return -1;
}

void fn_801053DC(SlotTbl* t, int i) {
    fn_80110D38(&t->ents[i]);
}

void* fn_8010599C(u8 i) {
    return lbl_803856A0[i];
}

void* fn_801059B0(void) {
    return lbl_803856A0[fn_8006074C(lbl_803CAB38)->unk8A];
}
