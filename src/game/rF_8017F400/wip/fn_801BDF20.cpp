/* near misses from the unit info draw functions; helpers as in ../fn_801BDF20.cpp and ../drawinl.h */

void fn_801BE4E4(u8* d) {
    void* ec;
    void** ls;
    void* cl;
    u8* u = *(u8**)(d + 0x44);
    f32 ox = 0.0f;
    void* bs;
    char buf[0x40];
    f32 rk[6];
    ec = *(void**)(u + 0xEC);
    cl = *(void**)(u + 0xF0);
    if (!lbl_804CB9D8) lbl_804CB9D8 = 1;
    bs = lbl_803C8E80;
    ls = (void**)fn_80030CF4(bs);
    fn_8007E154();
    fn_8007E7DC(*(u8*)(d + 0x14));
    fn_8007E4E4(0.0f, 0.0f, 170.0f, 1.0f);
    fn_8007E164();
    Tile1(1, 0xFF, 0, 0, ox, ox, 1.0f);
    SetScale(-1.0f);
    if (*(RMdl**)(d + 0x4C) != 0) {
        fn_800E48AC(*(RMdl**)(d + 0x4C), 122.0f + ox, 40.0f + ox, 169.5f);
        MdlCol(*(RMdl**)(d + 0x4C), mk7F(*(u8*)(d + 0x14)));
    }
    {
GXColor2 c0 = G0(); GXColor2 c1 = G1();
    fn_80106F98(rk, 1.0f);
    {
    f32 v = fn_80127868(u);
    f32 ax = 70.0f + ox, ay = 80.0f + ox;
    if (v >= rk[0]) {
        TileC(7, c0, 2, ax, ay, 1.0f);
    } else if (v <= rk[4]) {
        TileC(7, c1, 0, ax, ay, 1.0f);
    } else if (v >= rk[1]) {
        TileC(8, c0, 2, ax, 25.0f + ay, 1.0f);
    } else if (v <= rk[3]) {
        TileC(8, c1, 0, ax, 25.0f + ay, 1.0f);
    }
    }
    }
    if (*(void**)(d + 0x48) != 0) {
        f32 fx = 197.0f + ox;
        f32 fy = 32.0f + ox;
        lbl_804CB9E0.w = 0x8C;
        lbl_804CB9E0.h = 0x80;
        lbl_804CB9E0.x = fx;
        lbl_804CB9E0.y = fy;
        fn_8007E154();
        fn_8007E74C((void*)fn_801BE28C, &lbl_804CB9E0);
        fn_8007E164();
        fn_800C4DDC((int)(76.0f + fx), (int)(128.0f + fy), 0xFF, *(void**)(d + 0x48));
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E164();
    }
    SetScale(-1.0f);
    FontReset();
    TextW(CX(fn_80118C44(ec), 116.0f + ox), 26.0f + ox, 8, fn_80118C44(ec));
    TextW(CX(fn_80118F00(cl), 112.0f + ox), 82.0f + ox, 8, fn_80118F00(cl));
    {
    strcpy(buf, fn_800D0864("MP_LV"));
    TextW(CX(buf, 55.0f + ox), 111.0f + ox, 8, buf);
    fn_80290DDC(buf, "%d", *(s8*)(u + 0xFE));
    TextW(CX(buf, 88.0f + ox), 111.0f + ox, 8, buf);
    strcpy(buf, fn_800D0864("MP_EX"));
    TextW(CX(buf, 130.0f + ox), 111.0f + ox, 8, buf);
    if ((u8)fn_80126B0C(u) == 0xFF) strcpy(buf, "\x81""|\x81""|");
    else fn_80290DDC(buf, "%d", (u8)fn_80126B0C(u));
    TextW(CX(buf, 163.0f + ox), 111.0f + ox, 8, buf);
    }
    {
    strcpy(buf, fn_800D0864("MP_HP"));
    TextW(CX(buf, 55.0f + ox), 139.0f + ox, 8, buf);
    fn_80290DDC(buf, "%d", *(s8*)(u + 0x114));
    TextW(CX(buf, 92.0f + ox), 139.0f + ox, 8, buf);
    TextW(112.0f + ox, 139.0f + ox, 8, "\x81""^");
    fn_80290DDC(buf, "%d", (s16)fn_801237EC(u));
    TextW(CX(buf, 148.0f + ox), 139.0f + ox, 0xC, buf);
    }
    {
    BOOL b = Chk(bs);
    fn_801BF50C("MP_ATK", *(s16*)((u8*)bs + 0x448), 0, b == 0, 440.0f + ox, 27.0f + ox);
    fn_801BF50C("MP_ATSPD", *(s16*)((u8*)bs + 0x44C), 0, 0, 549.0f + ox, 27.0f + ox);
    }
    {
    BOOL b = Chk(bs);
    fn_801BF50C("MP_HIT", *(s16*)((u8*)bs + 0x44E), 0, b == 0, 440.0f + ox, 55.0f + ox);
    fn_801BF50C("MP_AVO", *(s16*)((u8*)bs + 0x450), 0, 0, 549.0f + ox, 55.0f + ox);
    }
    {
    BOOL b = Chk(bs);
    fn_801BF50C("MP_CRIT", *(s16*)((u8*)bs + 0x454), 0, b == 0, 440.0f + ox, 83.0f + ox);
    fn_801BF50C("MP_CAVO", *(s16*)((u8*)bs + 0x456), 0, 0, 549.0f + ox, 83.0f + ox);
    }
    {
    BOOL b = Chk(bs);
    int p, q;
    if (*ls != 0) p = (u8)fn_801107C0(*ls, bs); else p = 0;
    if (*ls != 0) q = (u8)fn_801107A0(*ls, bs); else q = 0;
    fn_801BF50C("MP_RNG", q, p, b == 0, 440.0f + ox, 111.0f + ox);
    fn_801BF80C("MP_SFX", (u8*)bs + 0x45E, 430.0f + ox, 139.0f + ox);
    }
}

void fn_801BFB58(u8* d) {
    fn_8007E154();
    fn_8007E7DC(*(u8*)(d + 0x20));
    fn_8007E4E4(0.0f, 0.0f, 170.0f, 1.0f);
    fn_8007E164();
    SetScale(-5.0f);
    switch (*(s8*)(d + 0xA)) {
    case 0:
        fn_801BD780(0xFF, *(f32*)(d + 0x24), *(f32*)(d + 0x28), 576.0f, 240.0f, 237.0f);
        fn_801C0220(d);
        fn_801C0E94(d);
        break;
    case 1:
        fn_801BD780(0xFF, *(f32*)(d + 0x24), *(f32*)(d + 0x28), 576.0f, 240.0f, 237.0f);
        fn_801C13D0(d);
        fn_801C25D8(d);
        fn_801C2ED8(d);
        break;
    case 2: {
        f32 x, y;
        void* u;
        fn_801BD780(0xFF, *(f32*)(d + 0x24), *(f32*)(d + 0x28), 576.0f, 240.0f, 351.0f);
        fn_801C336C(d);
        x = *(f32*)(d + 0x24);
        y = *(f32*)(d + 0x28);
        u = *(void**)(d + 0x44);
        SetScale(-1.0f);
        Hdr(0x1D, 461.0f + x, 12.0f + y);
        { f32 q = 191.0f; Bar(0xA0, 361.0f + x, 49.0f + y, q, 9); }
        SetScale(-1.0f);
        FontReset();
        if (fn_8012E3A4(u)) {
            const char* r;
            void* m = fn_8012E3A4(u);
            fn_800CB3A8(1.0f, 0.0f, 367.0f + x, 31.0f + y, 1, 1, 0, fn_80118C44(*(void**)((u8*)m + 0xEC)));
            {
            u8 k = fn_8012E8BC(u, (s8)fn_8012E9B4(u, m));
            const char* tbl[4] = {"\x81\x7C", "\x82\x62", "\x82\x61", "\x82\x60"};
            r = tbl[k];
            fn_800CB3A8(1.0f, 0.0f, 540.0f + x - 0.5f * fn_800CA3DC(r, -1, 1.0f), 31.0f + y, 1, 1, 0, r);
            }
        }
        SetScale(2.0f);
        fn_801C4268(d);
        break;
    }
    case 3:
        fn_801BD780(0xFF, *(f32*)(d + 0x24), *(f32*)(d + 0x28), 576.0f, 240.0f, 312.0f);
        fn_801C4F0C(d);
        fn_801C5874(d);
        break;
    }
    SetScale(5.0f);
}

void fn_801C0638(const char* name, s8 a, s8 b, s8 c, s8 e, void* p, f32 x, f32 y) {
    SetScale(-1.0f);
    {
    f32 by = 16.0f + y;
    f32 bw = e * 134 / 50 - 2;
    GaugeBg(x, by, bw);
    }
    SetScale(-1.0f);
    if (b > 0) {
        f32 by = 18.0f + y;
        f32 bx = 67.0f + x;
        f32 bw = b * 134 / 50 - 6;
        Bar(0xFF, bx, by, bw, 0xC);
    }
    SetScale(-1.0f);
    FontReset();
    fn_800CB3A8(1.0f, 0.0f, 8.0f + x, y, 9, 1, 0, fn_800D0864(name));
    if (p != 0 && fn_80291188(name, "MP_LUCK") != 0) {
        fn_800CB3A8(0.75f, 0.0f, 84.0f + x, 5.0f + y, b < e ? 1 : 0x27, 1, 0, "%3d >>", a);
    }
    fn_800CB3A8(1.0f, 0.0f, 134.0f + x, y, b < e ? 1 : 0x27, 1, 0, "%3d", b);
    fn_801BD420(c - b, 0, 170.0f + x, y);
    SetScale(3.0f);
}

void fn_801BD420(int v, int plus, f32 x, f32 y) {
/*P*/
    int fl;
    f32 f;
    int a;
    char* s;
    void* arch;
    int len;
    s16 py;
    int px;
    int i;
    int n;
/*E*/
    char buf[8];
    if (v != 0) {
        n = fn_8028DB44(v);
        arch = lbl_804CB588;
        f = 1.0f + (f32)fn_80295940(6.2831855f * (fn_8017F990(0, 3000) / 3000.0f));
        if (plus) a = 127.0f * f; else a = 0xFF;
        fl = 0x11;
        if (plus) fl = 0x51;
        {
s16 sv = v > 0 ? 0 : 0x14;
s16 u0 = 0;
s16 ix = x;
s16 iy = y;
GXColor2 c = {a, a, a, 0xFF};
        Digit(arch, c, fl, ix, iy, u0, sv);
        }
        fn_80290DDC(buf, "%d", n);
        len = strlen(buf);
        {
        s16 sv = v > 0 ? 0 : 0x14;
        py = 4.0f + y;
        px = 10.0f + x;
        s = buf;
        for (i = 0; i < len; i++, s++) {
            GXColor2 c = {a, a, a, 0xFF};
            s16 ix = px;
            s16 u = (*s - 0x2F) * 13;
            Digit(arch, c, fl, ix, py, u, sv);
            px = (s16)(px + 0xB);
        }
        }
    }
}



void fn_801C4F0C(u8* d) {
/*P*/
    int k;
    u8* u;
    f32 x;
    const char* v;
    int j;
    f32 ly;
    f32 by;
    f32 q;
    void* cl;
    int i;
    int n;
    f32 lx;
    const char* lab;
    f32 y;
/*E*/
    char buf[0x40];
    x = *(f32*)(d + 0x24);
    y = *(f32*)(d + 0x28);
    u = *(u8**)(d + 0x44);
    SetScale(-1.0f);
    Hdr(0x21, 160.0f + x, 12.0f + y);
    lx = 26.0f + x;
    ly = 30.0f + y;
    cl = fn_80127B68(u);
    by = 18.0f + ly;
    q = 269.0f;
    for (i = 0, k = 0; i < 7; i++, k += 0x1C) {
        Bar(0xA0, lx, by + k, q, 9);
    }
    FontReset();
    v = fn_80127B28(u);
    lab = "MD_BELONG";
    Pair(lab, v, lx, ly);
    ly += 28.0f;
    n = *(s8*)(*(u8**)(u + 0xEC) + 0x21);
    strcpy(buf, "");
    for (j = 0; j < n; j++) fn_80291110(buf, "\x81""\x9A"" ");
    lab = "MD_DIRECTION";
    Pair(lab, buf, lx, ly);
    ly += 28.0f;
    if (cl != 0) v = fn_80118C44(*(void**)((u8*)cl + 0xEC)); else v = 0;
    lab = "MD_COMMANDER";
    Pair(lab, v, lx, ly);
    ly += 28.0f;
    n = fn_80112F64(u);
    for (j = 0; j < 4; j++) {
        lab = 0;
        if (j == 0) lab = "MD_BOND";
        if (n >= j + 1) {
            void* e = fn_80112FFC(u, j);
            if (fn_8012CE54(*(void**)e) != 0) v = fn_80118C44(e); else v = 0;
        } else {
            v = 0;
        }
        Pair(lab, v, lx, ly);
        if (v != 0) ly += 28.0f;
    }
}

void fn_801C5874(u8* d) {
/*P*/
    f32 q;
    f32 bx;
    f32 by;
    u8* u;
    int t;
    f32 v;
    f32 x;
    int col;
    f32 gx2;
    f32* p;
    f32 gx;
    f32 ly;
    f32 s;
    int j;
    f32 y;
    const char* m;
    f32 k;
    f32 gy;
    f32 gy2;
    f32 y1;
    f32 k2;
    int i;
/*E*/
    char buf[0x20];
    f32 rk[6];
    lbl_804CB9EC = lbl_804CB9EC == 30 ? 0 : lbl_804CB9EC + 1;
    x = *(f32*)(d + 0x24);
    y = *(f32*)(d + 0x28);
    u = *(u8**)(d + 0x44);
    SetScale(-1.0f);
    Hdr(0x20, 435.0f + x, 12.0f + y);
    fn_80106F98(rk, 1.0f);
    v = fn_80127868(u);
    bx = 469.0f + x;
    q = 86.0f;
    by = 30.0f + y;
    Bar(0xA0, bx, 18.0f + by, q, 9);
    SetScale(-1.0f);
    FontReset();
    if (v >= rk[0]) { col = 0xA; strcpy(buf, "MD_BIO_BEST"); }
    else if (v <= rk[4]) { col = 0xB; strcpy(buf, "MD_BIO_WORST"); }
    else if (v >= rk[1]) { col = 0xA; strcpy(buf, "MD_BIO_GOOD"); }
    else if (v <= rk[3]) { col = 0xB; strcpy(buf, "MD_BIO_BAD"); }
    else { col = 1; strcpy(buf, "MD_BIO_NORMAL"); }
    m = fn_800D0864(buf);
    fn_800CB3A8(1.0f, 0.0f, 45.0f + bx - 0.5f * fn_800CA3DC(fn_800D0864(buf), -1, 1.0f), by, col, 1, 0, m);
    SetScale(1.0f);
    gx = 321.0f + x;
    k = 40.0f;
    gy = 80.0f + (64.0f + y);
    s = 240.0f;
    p = rk;
    for (i = 0; i < 5; i++, p++) {
        GXColor2 c;
        ly = k * -*p + gy;
        c = *(GXColor2*)fn_800CD204(IsTwo(i));
        fn_801BE154(c, gx, ly, s + gx, ly);
    }
    SetScale(-1.0f);
    gx2 = 321.0f + x;
    k2 = -40.0f;
    gy2 = 80.0f + (64.0f + y);
    j = 0;
    for (t = *(u16*)(u + 0x37C) - 0x78; t < *(u16*)(u + 0x37C) + 0x78; t++, j++) {
        GXColor2 c = *(GXColor2*)fn_800CD204(0x3D);
        y1 = k2 * fn_801071C4(u, t + 1) + gy2;
        fn_801BE154(c, gx2 + j, k2 * fn_801071C4(u, t) + gy2, gx2 + (j + 1), y1);
    }
    SetScale(-1.0f);
    fn_800E48AC(*(void**)(d + 0x68), 120.0f + gx2, k2 * fn_80127868(u) + gy2, 0.0f);
    (*(Rm**)(d + 0x68))->n->a = *(u8*)(d + 0x20);
    SetScale(3.0f);
}

void fn_801C336C(u8* d) {
/*P*/
    f32 x;
    f32 y;
    u8* u;
    f32 lx;
    f32 ly;
    f32 q;
    int i;
    int k;
    u8* dd;
    f32 tx;
    f32 ty;
    f32 ry;
    int j;
    int n;
    Sl* s;
/*E*/
    dd = d;
    x = *(f32*)(d + 0x24);
    y = *(f32*)(d + 0x28);
    u = *(u8**)(d + 0x44);
    SetScale(-1.0f);
    Hdr(0x1C, 182.0f + x, 12.0f + y);
    {
    void* pp = fn_80127A90(u);
    fn_801C3AB4(pp, 20.0f + x, 32.0f + y, fn_8011B8A4(u + 0x12C));
    }
    lx = 152.0f + x;
    ly = 34.0f + y;
    q = 171.0f;
    for (i = 0, k = 0; i < 6; i++, k += 0x20) {
        Bar(0xA0, 12.0f + lx, 19.0f + (ly + k), q, 9);
    }
    SetScale(-1.0f);
    FontReset();
    tx = 144.0f + x;
    ty = 34.0f + y;
    n = 0;
    for (j = 0; j < 6; j++, dd += 4) {
        s = *(Sl**)(dd + 0x2C);
        ry = ty + n;
        if (s != 0) {
            if (s->x5 & 1) {
                f32 ix;
                if (fn_801D09F0()) ix = 3.0f + tx; else ix = tx;
                ((IconFont*)lbl_803E7290)->draw((int)ix, (int)(2.0f + ry), 0x59);
            }
            ((IconFont*)lbl_803E72D8)->draw((int)(25.0f + tx), (int)ry, s->p[0x1F]);
            FontReset();
            fn_800CB3A8(1.0f, 0.0f, 60.0f + tx, 2.0f + ry, 1, 1, 0, fn_8011A054(s->p));
            {
            int q2 = (s->x5 >> 1) & 1;
            if ((q2 ? 0 : s->p[0x1E]) != 0) {
                fn_800CB3A8(1.0f, 0.0f, 166.0f + tx, 2.0f + ry, 1, 1, 0, "%2d", q2 ? 0 : s->p[0x1E]);
            }
            }
            n += 0x20;
        }
    }
    SetScale(2.0f);
}
