// Near misses, see NOTES.md. Needs declarations from ../fn_800C9230.cpp.
void fn_800C91C8(P* p) {
    if (p->m2b == 0x7B) return;
    if (p->vt == lbl_803829D8) return;
    if (p->vt == lbl_80382930 + 0) return;
    if (p->vt == lbl_80382930 + 0x80) return;
    if (p->vt == lbl_80382930 + 0x70) return;
    if (p->m18 == 1) return;
    if (p->m18 == 7) return;
    fn_800893C4(p);
}
void fn_800C9FA4() {
    void** h = lbl_803E7260 + 1;
    char** s = lbl_80382A20[1];
    int i;
    for (i = 1; i < 6; i++, s += 2) {
        void* m = fn_80079150(0x10);
        if (m != NULL) m = fn_80077348(m);
        *h = m;
        fn_80077478(*h, s[fn_801D09F0()], 0x880, 0);
        h++;
    }
    RA->Load();
    RB->Load();
    lbl_804CB6F0 = RA;
}
void fn_800CA0A4() {
    void** h = lbl_803E7260;
    char** s = lbl_80382A20[0];
    int i;
    for (i = 0; i < 6; i++, s += 2) {
        fn_80077400(*h);
        fn_80077478(*h, s[fn_801D09F0()], 0x80, 0);
        h++;
    }
    RA->Unload();
    RA->Load();
    RB->Unload();
    RB->Load();
}
