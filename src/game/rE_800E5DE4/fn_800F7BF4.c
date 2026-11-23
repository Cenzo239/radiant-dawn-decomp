/* fn_800F7BF4 (0x110): exact (round m8). Map unit per-frame update: steps the model while the unit is visible and
 * turns the unit (unk2 is an angle in degrees).
 * The visibility test is fn_800F7724 inlined, here with the two flag fields passed in as named locals. Register choice
 * needs the locals declared as mdl, f, f2 (model pointer r5, flags r6, low flags2 word r7); with the fields read inside
 * the inline (compiler temporaries) the model pointer and the flags2 word exchange registers. */
#include "game/rE_800E5DE4/mapunit.h"

extern u8 lbl_803CAB38[];
extern void fn_80007C58(void*);
void fn_800F7BF4(MapUnit* m);

static inline BOOL Visible(MapUnit* m, u16 f, u64 f2) {
    if (f2 & 0x40100009CULL) return 0;
    if ((f2 & 0x240) == 0x40) return 0;
    if ((f & 0x22U) != 2) return 0;
    return m->unk33 != 0;
}

void fn_800F7BF4(MapUnit* m) {
    Model* mdl;
    u16 f;
    u64 f2;
    mdl = (Model*)m->model;
    f = m->flags;
    if (f & 8) return;
    f2 = m->flags2;
    if (Visible(m, f, f2)) fn_80007C58(mdl);
    if (m->flags2 & 1) {
        return;
    }
    if (m->unkF4->unk8 == lbl_803CAB38[0x11] || m->unk2 != 0) {
        m->unk2 = (m->unk2 + 4) % 360;
    }
}
