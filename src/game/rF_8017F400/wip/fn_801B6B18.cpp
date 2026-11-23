/* near miss: first case wants `li r4,0; ...; srawi r0,r4,31; rlwinm r3,r3,0,27,27; or. r0,r3,r0` for the flag test, an s64 mask whose high word is an unfolded zero; plus decl order of d and n. Declarations in ../fn_801B7644.cpp */
static inline void Count(int d, int n, const char* full, const char* rest) {
    fn_8007E154();
    fn_8007E720(5.0f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    if (d == n) {
        fn_800CB278(0x2C, 0x17, 0x33, fn_800D0864(full));
        fn_800CB278(0xE8, 0x17, 1, STR(0x12), d, n);
    } else {
        fn_800D0AE4(0, n - d);
        fn_800CB278(0x2C, 0x17, 0x33, fn_800D0864(rest));
        fn_800CB278(0xE8, 0x17, 1, STR(0x2F), d, n);
    }
}
void fn_801B6B18(LView* p) {
    switch (p->x6C) {
    case 1: {
        s16 d = 0;
        u8* u;
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E7DC(0xFF);
        fn_8007E164();
        for (u = lbl_804CB814[0].head; u != 0; ) {
            u64 f = *(u64*)(u + 0x108);
            u = *(u8**)(u + 0xE8);
            if ((f & 0x10) == 0) d++;
        }
        Count(d, (s16)lbl_803E7320[0], STR(0), STR(0x1F));
        break;
    }
    case 2: {
        s16 d = 0;
        u8* u;
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E7DC(0xFF);
        fn_8007E164();
        for (u = lbl_804CB814[5].head; u != 0; ) {
            u64 f = *(u64*)(u + 0x108);
            u = *(u8**)(u + 0xE8);
            if (f & 0x400000) d++;
        }
        Count(d, (s16)lbl_803E7320[0], STR(0x40), STR(0x56));
        break;
    }
    default:
        p->pages[p->x63]->draw(p->tex, 0.0f, 0.0f);
        break;
    }
}

