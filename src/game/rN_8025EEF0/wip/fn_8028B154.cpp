/* fn_8028B154: 2 words. Original passes the object with addi r3, r31, 0 rather than mr r3, r31. */
struct TvTex { u8 d[0x20]; };
struct TvState { TvTex tex; u8 a[0x2C]; u8 c[4]; };
void fn_8028B154(void) {
    TvState* b = (TvState*)lbl_80430CE0;
    int z = 0;
    int i;
    u32 size;
    fn_8024DEF0(250.0f);
    fn_80256EE8(b->a);
    fn_8025704C(250.0f);
    fn_80256FA4(b->c);
    fn_802570D0(250.0f);
    fn_8029D3E8(fn_8029C7D8(), 2, 0xFA);
    if (fn_80085708(lbl_803932EC) != 0) {
        fn_8008939C();
    }
    for (i = 0; i < 4; i++) {
        fn_8030D688(i);
    }
    size = fn_8030585C(0x260, 0x1C0, 4, 0, 0);
    if (lbl_804CC0F0 == 0) {
        lbl_804CC0F0 = fn_80079958(size, 0x40);
    }
    DCInvalidateRange(lbl_804CC0F0, size);
    fn_80305A40((u8*)b + z, lbl_804CC0F0, 0x260, 0x1C0, 4, 0, 0, 0);
    fn_80305C94((u8*)b + z, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
}


