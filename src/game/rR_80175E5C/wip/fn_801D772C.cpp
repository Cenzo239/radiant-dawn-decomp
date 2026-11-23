/* fn_801DA184: 15 of 43 words differ */
void fn_801DA184(s16 x, s16 y, int, u16 fl) {
    int i;
    for (i = 0; i <= 0xB; i++) {
        SPR(i + 0x51);
        fn_801D60D0(x, y, RW(lbl_804CBCB8), RH(lbl_804CBCB8), fl, &lbl_804CBCB8, 0);
        x += RW(lbl_804CBCB8) + 4;
    }
}

/* fn_801D7D38: 36 of 237 words differ */
void fn_801D7D38(s16 x, s16 y, int unused, s16 w, s16 top, int bh, const Color& col, u16 fl) {
    void* st; f32 s; Rect* r;
    st = fn_8007E4C4(&s);
    SPRB(2);
    Alpha(-0.2f);
    fn_801D60D0(x, y - RH(lbl_804CBDE8), RW(lbl_804CBDE8), RH(lbl_804CBDE8), fl, &lbl_804CBDE8, 0);
    fn_801D60D0(x, y + w, RW(lbl_804CBDE8), RH(lbl_804CBDE8), fl, &lbl_804CBDE8, 2);
    Alpha(0.2f);
    SPRB(3);
    fn_801D620C(x - 4, y, RW(lbl_804CBDF0), w, fl, &lbl_804CBDF0, 0);
    Alpha(-0.1f);
    r = &lbl_804CBDD8;
    if (bh >= RH(lbl_804CBDD8) * 2) {
        SPRB(0);
        int by = y + top;
        int bx = x + 2;
        fn_801D68E4(bx, by, RW(*r), RH(*r), fl, r, Color(col), 0);
        fn_801D68E4(bx, bh + by - RH(*r), RW(*r), RH(*r), fl, r, Color(col), 2);
        SPRB(1);
        fn_801D6BC0(bx, by + RH(lbl_804CBDD8), RW(lbl_804CBDE0), bh - RH(lbl_804CBDD8) * 2, fl, &lbl_804CBDE0, Color(col), 0);
    } else {
        SPRB(0);
        int hh = bh >> 1;
        int by = y + top;
        int bx = x + 2;
        fn_801D6BC0(bx, by, RW(*r), hh, fl, r, Color(col), 0);
        fn_801D6BC0(bx, hh + by, RW(*r), hh, fl, r, Color(col), 2);
    }
    Alpha(0.1f);
    fn_8007E478(st, s);
}

/* fn_801DB3F4: 3 of 223 words differ */
void fn_801DB3F4(s16 x, s16 y, int w, int cur, int tot, int page, u16 fl) {
    s16 tw = RW(lbl_804CBC70) + 0x3E;
    s16 bar = (tot * (w - tw)) / page;
    SPR(0x46);
    fn_801D60D0(x - RW(lbl_804CBC60), y, RW(lbl_804CBC60), RH(lbl_804CBC60), fl, &lbl_804CBC60, 0);
    SPR(0x47);
    fn_801D620C(x, y, tw - RW(lbl_804CBC70), RH(lbl_804CBC68), fl, &lbl_804CBC68, 0);
    SPR(0x48);
    int bx = x + tw;
    fn_801D60D0(bx - RW(lbl_804CBC70), y, RW(lbl_804CBC70), RH(lbl_804CBC70), fl, &lbl_804CBC70, 0);
    SPR(0x49);
    fn_801D620C(bx, y, bar, RH(lbl_804CBC78), fl, &lbl_804CBC78, 0);
    SPR(0x4A);
    fn_801D60D0(bar + bx, y, RW(lbl_804CBC80), RH(lbl_804CBC80), fl, &lbl_804CBC80, 0);
    s16 fill = (bar * cur) / tot;
    if (fill != 0) {
        Alpha(-0.1f);
        int mid = (s16)(fill - (RW(lbl_804CBC48) + RW(lbl_804CBC58)));
        if (mid < 0) mid = 0;
        SPR(0x43);
        int by = y + 1;
        fn_801D60D0(bx, by, RW(lbl_804CBC48), RH(lbl_804CBC48), fl, &lbl_804CBC48, 0);
        if (mid > 0) {
            SPR(0x44);
            fn_801D620C(bx + RW(lbl_804CBC48), by, mid, RH(lbl_804CBC50), fl, &lbl_804CBC50, 0);
        }
        SPR(0x45);
        fn_801D60D0(RW(lbl_804CBC48) + mid + bx, by, RW(lbl_804CBC58), RH(lbl_804CBC58), fl, &lbl_804CBC58, 0);
        Alpha(0.1f);
    }
}

/* fn_801D820C: 161 of 212 words differ */
void fn_801D820C(s16 x, s16 y, int idx, int on, int pulse, u16 fl) {
    ALPHAQ(on ? -1.0f : -0.0f);
    SPR(0xA);
    fn_801D60D0(x, y, RW(lbl_804CBAE0), RH(lbl_804CBAE0), fl, &lbl_804CBAE0, 0);
    Rect* r = &lbl_804CBAE8;
    ALPHAQ(on ? 1.0f : 0.0f);
    ALPHAQ(on ? -1.01f : -0.01f);
    Color c0;
    Color wc;
    if (on) {
        c0.r = lbl_804CF7FF[1];
        c0.g = lbl_804CF7FF[2];
        c0.b = lbl_804CF7FF[3];
        c0.a = lbl_804CF7FF[4];
    } else {
        c0.r = lbl_804CF7FF[5];
        c0.g = lbl_804CF7FF[6];
        c0.b = lbl_804CF7FF[7];
        c0.a = lbl_804CF7FF[8];
    }
    Color tmp;
    *(u32*)&wc = *(u32*)&c0;
    Color& c = wc;
    if (on && pulse) {
        f32 s = fn_80295940(6.2831855f * ((f32)fn_8028C764(fn_8028C634(fn_8028C418(OSGetTime(), (*(u32*)0x800000F8 / 4) / 1000), 1000)) / 1000.0f));
        u16 v = 255.0f * (0.5f * (1.0f + s) + 0.5f);
        if (v > 0xFF) v = 0xFF;
        tmp.r = v;
        tmp.a = lbl_804CF7FF[0];
        tmp.g = v;
        tmp.b = v;
        c.r = tmp.r;
        c.g = tmp.g;
        c.b = tmp.b;
        c.a = tmp.a;
    }
    fn_80006B84(lbl_804CBDF8, lbl_8041EF60, lbl_8041EF80, 0, idx);
    if (fn_801D09F0()) {
        fn_801D6D68(x + 6, y + 6, (s16)(0.7638191f * RW(*r)), RH(*r), fl, r, Color(c), 0);
    } else {
        fn_801D6A4C(x + 4, y + 4, RW(*r), RH(*r), fl, r, Color(c), 0);
    }
    ALPHAQ(on ? 1.01f : 0.01f);
}

/* fn_801D7014: 25 of 296 words differ, only cw/ch swapped between r16 and r17. Declaration order found by hill climbing. */
void fn_801D7014(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    s16 th;
    int y1;
    int y2;
    int hw;
    int x2;
    int ch;
    int rw;
    f32 s;
    int mx;
    s16 iw;
    int cw;
    int x1;
    s16 ih;
    void* st;
    int y3;

    cw = RW(lbl_804CBA90);
    iw = w - cw * 2;
    ch = RH(lbl_804CBA90);
    ih = h - ch * 2;
    th = RH(lbl_804CBAA0);

    st = fn_8007E4C4(&s);
    SPR(1);
    fn_801D60D0(x, y, RW(lbl_804CBA90), RH(lbl_804CBA90), fl, &lbl_804CBA90, 0);
    x2 = x + (w - cw);
    fn_801D60D0(x2, y, RW(lbl_804CBA90), RH(lbl_804CBA90), fl, &lbl_804CBA90, 1);
    y2 = y + (h - ch);
    fn_801D60D0(x, y2, RW(lbl_804CBA90), RH(lbl_804CBA90), fl, &lbl_804CBA90, 2);
    fn_801D60D0(x2, y2, RW(lbl_804CBA90), RH(lbl_804CBA90), fl, &lbl_804CBA90, 3);
    SPR(2);
    y1 = y + ch;
    fn_801D60D0(x, y1, RW(lbl_804CBA98), ih, fl, &lbl_804CBA98, 0);
    fn_801D60D0(x + (w - RW(lbl_804CBA98)), y1, RW(lbl_804CBA98), ih, fl, &lbl_804CBA98, 0);
    SPR(3);
    x1 = x + cw;
    fn_801D60D0(x1, y, iw, RH(lbl_804CBAA0), fl, &lbl_804CBAA0, 0);
    fn_801D60D0(x1, y + (h - RH(lbl_804CBAA0)), iw, RH(lbl_804CBAA0), fl, &lbl_804CBAA0, 2);
    Alpha(2.0f);
    SPR(4);
    y3 = y + th;
    fn_801D60D0(x, y3, RW(lbl_804CBAB8), RH(lbl_804CBAB8), fl, &lbl_804CBAB8, 0);
    fn_801D60D0(x2, y3, RW(lbl_804CBAB8), RH(lbl_804CBAB8), fl, &lbl_804CBAB8, 1);
    fn_801D60D0(x, y2, RW(lbl_804CBAB8), RH(lbl_804CBAB8), fl, &lbl_804CBAB8, 2);
    fn_801D60D0(x2, y2, RW(lbl_804CBAB8), RH(lbl_804CBAB8), fl, &lbl_804CBAB8, 3);
    fn_801D620C(x, y1, w, ih, fl, &lbl_804CBAA8, 0);
    SPR(5);
    hw = iw >> 1;
    fn_801D620C(x1, y3, hw, RH(lbl_804CBAB0), fl, &lbl_804CBAB0, 0);
    rw = iw - hw;
    mx = hw + x1;
    fn_801D620C(mx, y3, rw, RH(lbl_804CBAB0), fl, &lbl_804CBAB0, 1);
    fn_801D620C(x1, y2, hw, RH(lbl_804CBAB0), fl, &lbl_804CBAB0, 0);
    fn_801D620C(mx, y2, rw, RH(lbl_804CBAB0), fl, &lbl_804CBAB0, 1);
    Alpha(-2.0f);
    fn_8007E478(st, s);
}


/* fn_801DAEF4 (and the identical fn_801DC2B0): 270 of 320 words, frame 0x10 too large. The second half is the inlined nine-slice Inner(x + 0xC, y + 0xE0, w - 0x18, h - 0xEC, 0x10), which compiles to the right instructions, but the original reuses r25 for w and needs two fewer saved registers. */
void fn_801DAEF4(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    int ch; int cw; int iw; int ix; int ih; int iy;
    ch = RH(lbl_804CBD78);
    cw = RW(lbl_804CBD80);
    SPR(0x7F);
    iw = w - cw * 2;
    ix = x + cw;
    fn_801D620C(ix, y, iw, RH(lbl_804CBD78), fl, &lbl_804CBD78, 0);
    fn_801D620C(ix, y + h - RH(lbl_804CBD78), iw, RH(lbl_804CBD78), fl, &lbl_804CBD78, 2);
    SPR(0x80);
    ih = h - ch * 2;
    iy = y + ch;
    fn_801D620C(x, iy, RW(lbl_804CBD80), ih, fl, &lbl_804CBD80, 0);
    fn_801D620C(x + w - RW(lbl_804CBD80), iy, RW(lbl_804CBD80), ih, fl, &lbl_804CBD80, 1);
    Alpha(3.0f);
    Color a(lbl_804CF840[4], lbl_804CF840[5], lbl_804CF840[6], lbl_804CF840[7]);
    Color b(a);
    fn_801D6388(ix, iy, iw, ih, fl, b, 0);
    Alpha(-3.0f);
    Alpha(2.9f);
    Inner(x + 0xC, y + 0xE0, w - 0x18, h - 0xEC, 0x10);
    Alpha(-2.9f);
}

