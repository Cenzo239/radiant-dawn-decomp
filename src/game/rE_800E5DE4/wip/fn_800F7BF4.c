/* fn_800F7BF4: 5 of 68 words differ (register swap only: the original keeps
 * `mdl` (m+0x28) in r5 and the low flags2 word of the inlined fn_800F7724 in
 * r7; MWCC gives the opposite). Tried: local declared/assigned separately,
 * static inline copy of fn_800F7724, Model* type, `!= 0`. Uses the MapUnit
 * struct from ../fn_800F3360.c, where fn_800F7724 precedes it. */
void fn_800F7BF4(MapUnit* m) {
    Model* mdl = (Model*)m->model;
    if (m->flags & 8) {
        return;
    }
    if (fn_800F7724(m)) {
        fn_80007C58(mdl);
    }
    if (m->flags2 & 1) {
        return;
    }
    if (m->unkF4->unk8 == lbl_803CAB38[0x11] || m->unk2 != 0) {
        m->unk2 = (m->unk2 + 4) % 360;
    }
}

