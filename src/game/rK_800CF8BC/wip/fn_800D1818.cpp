/* fn_800D194C: ['DIFF fn_800D194C: 10 of 128 words differ'] */
void fn_800D194C(MovProc* p) {
    fn_8007E154();
    fn_8007E4E4((0x260 - p->w) / 2, (0x1C0 - p->h) / 2, 10.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E7E8(0x80);
    fn_8007E174(0, 0x12);
    fn_8007E164();
    if (fn_801D09F0() == 0 && p->b59) {
        Bars();
    }
    fn_8007E154();
    fn_8007E174(0, 0x410);
    fn_8007E164();
    fn_800800D4(0xC);
    fn_80080928(fn_800D1B4C, p);
    fn_80080308();
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    if (IsEnd(p)) {
        fn_80083B78(p);
    }
    if (fn_802373AC() == 5) {
        fn_80083B78(p);
    }
}

/* fn_800D1D14: ['DIFF fn_800D1D14: 18 of 114 words differ'] */
void fn_800D1D14(const char* name, u8 a, u8 b) {
    MovProc* p;
    if (fn_8023F9F4(name) == 0x40000) {
        name = lbl_80366474;
    }
    p = (MovProc*)fn_80081050(lbl_80383CC0, (void*)3);
    p->name = (char*)fn_800791B0(0x100);
    fn_802910CC(p->name, name, 0xFE);
    p->name[0xFF] = 0;
    CapCreate(p, p->name);
    p->o54 = 100;
    p->b58 = a;
    p->b59 = b;
    p->o30 = 0;
}

/* fn_800D1EDC: ['DIFF fn_800D1EDC: 18 of 114 words differ'] */
void fn_800D1EDC(const char* name, int vol, u8 a, u8 b) {
    MovProc* p;
    if (fn_8023F9F4(name) == 0x40000) {
        name = lbl_80366474;
    }
    p = (MovProc*)fn_80081050(lbl_80383CC0, (void*)3);
    p->name = (char*)fn_800791B0(0x100);
    fn_802910CC(p->name, name, 0xFE);
    p->name[0xFF] = 0;
    CapCreate(p, p->name);
    p->o54 = vol;
    p->b58 = a;
    p->b59 = b;
    p->o30 = 0;
}

