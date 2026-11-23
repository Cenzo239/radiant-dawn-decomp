/* fn_801D5914: 90 of 136 words differ */
void fn_801D5914(Widget* w, void* a) {
    int ww;
    s16 pad;
    w->v2C();
    w->v18(a);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, F(w, int, 0x38) | 0x13);
    fn_8007E164();
    pad = F(w, s16, 0x5C);
    ww = F(w, s16, 0xE) - F(w, s16, 0xA);
    int x = F(w, s16, 0x58);
    int sh = !(F(w, u32, 0x40) >> 31);
    s16 room = (s16)ww - (x + pad);
    if (WIDSEL(w, sh) != NULL) {
        switch (F(w, int, 0x4C)) {
        case 0:
            break;
        case 1:
            x = (s16)(x + ((room - fn_800CA3DC(WIDSEL(w, sh), -1, F(w, f32, 0x54))) >> 1));
            break;
        case 2:
            x = (s16)((s16)ww - (pad + fn_800CA3DC(WIDSEL(w, sh), -1, F(w, f32, 0x54))));
            break;
        default:
            break;
        }
        int h = (s16)(F(w, s16, 0x10) - F(w, s16, 0xC));
        s16 vp = F(w, s16, 0x5A);
        int y = (vp + (h - fn_800CB0FC(-1, F(w, f32, 0x54)))) >> 1;
        fn_800800D4(5);
        fn_80080330((s16)x, y);
        fn_80080A94(F(w, f32, 0x54));
        fn_80080508(*(Color*)fn_800CD204(F(w, u8, 0x50)));
        fn_80080C24((F(w, u32, 0x40) >> 31) == 0 ? (char*)w + 0x41 : F(w, char*, 0x48));
    fn_80080308();
    }
}

