/* fn_801AC084: 55 words, register colouring only (the tile switch and terrain lookup probably are inlines). Declarations as in ../fn_801ACD98.cpp. */

void fn_801AC084(TileD* d, void* tex, int a, f32 x, f32 y) {
/*P*/
    int cx;
    int cy;
    int t;
    void* ter;
    int nob;
    const char* s;
/*E*/
    char buf[0x100];
    s = 0;
    fn_8007E154();
    fn_8007E4E4(x, y, 105.0f, 1.0f);
    fn_8007E7DC((u8)a);
    fn_8007E164();
    fn_8007E154();
    { int tt;     switch (lbl_803CAB38[0x92]) {
    case 1: tt = 2; break;
    case 3: tt = 3; break;
    case 2: tt = 4; break;
    case 4: tt = 5; break;
    case 7: tt = 6; break;
    case 8: tt = 7; break;
    case 6: tt = 8; break;
    case 5: tt = 9; break;
    }
 fn_8007E374(tex, tt, 0x11); }
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 48.0f, 40.0f);
    fn_80080578(0);
    fn_80080308();
    SetScale(-1.0f);
    fn_8007E154();
    fn_8007E374(tex, 0, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 184.0f, 72.0f);
    fn_80080578(0);
    fn_80080308();
    SetScale(-1.0f);
    cx = (s8)(int)*(f32*)(lbl_803CAB38 + 0x934);
    cy = (s8)(int)*(f32*)(lbl_803CAB38 + 0x938);
    t = TerAt(cx, cy);
    if (t < 0) {
        s = "????";
        fn_801ABC34(tex, 0, 0x30, 0x23);
    } else {
        ter = fn_8010B240(t);
        nob = 1;
        switch (fn_8011D260(t)) {
        case 0x71:
        case 0xB1:
        case 0xB6:
            {
            TUnit* q;
            s = fn_8011D39C(ter);
            q = fn_80066130(lbl_803CB770, cx, cy, 4);
            if (q != 0 && q->x4 != 0) {
                nob = 0;
                FontReset();
                fn_80290DDC(buf, "%s %d", fn_800D0864("MTERR_VIT"), q->x4);
                fn_800CB3A8(0.75f, 0.0f, 0x60 - fn_800CA3DC(buf, -1, 0.75f) / 2, 0x23, 6, 0, 0, buf);
            }
            }
            break;
        case 0x99:
        case 0x9A:
            {
            TUnit* w;
            w = fn_80066DA8(lbl_803CB770, cx, cy, 7);
            if (w != 0) {
                s16 w0;
                s16 w1;
                int w12;
                s16 w2;
                s16 px;
                nob = 0;
                FontReset();
                w0 = fn_800CA3DC(fn_800D0864("MP_POW"), -1, 0.75f);
                w1 = fn_800CA3DC("0", -1, 0.75f);
                {
                int r0 = fn_800CA3DC(fn_800D0864("MTERR_REST"), -1, 0.75f);
                int su;
                w12 = w1 * 2;
                su = w12 + (w1 + w0);
                w2 = r0;
                px = 0x60 - ((s16)(su + w2 + 0xC) >> 1);
                }
                fn_800CB3A8(0.75f, 0.0f, px, 0x23, 6, 0, 0, fn_800D0864("MP_POW"));
                px = px + w0 + 2;
                fn_80290DDC(buf, "%2d", (u8)fn_80110DA8(fn_80066D18(w)));
                fn_800CB3A8(0.75f, 0.0f, px, 0x23, 6, 0, 0, buf);
                px = px + w12 + 8;
                fn_800CB3A8(0.75f, 0.0f, px, 0x23, 6, 0, 0, fn_800D0864("MTERR_REST"));
                px = px + w2 + 2;
                fn_80290DDC(buf, "%d", w->x5);
                fn_800CB3A8(0.75f, 0.0f, px, 0x23, 6, 0, 0, buf);
                if (d->id[0] == 0) {
                    d->id[0] = fn_8010B228("IID_LONGARCH")->xE;
                    d->id[1] = fn_8010B228("IID_IRONARCH")->xE;
                    d->id[2] = fn_8010B228("IID_KILLERARCH")->xE;
                    d->id[3] = fn_8010B228("IID_ONAGER")->xE;
                    d->nm[0] = fn_800D0864("MT_\x83""A\x81""[\x83""`\x82""\xEB""");
                    d->nm[1] = fn_800D0864("MT_\x83""A\x81""[\x83""`\x82""\xA0""");
                    d->nm[2] = fn_800D0864("MT_\x83""A\x81""[\x83""`\x82""\xAB""");
                    d->nm[3] = fn_800D0864("MT_\x93""\x8A""\x90""\xCE""\x8A""\xED""");
                }
                {
                int i;
                for (i = 0; i < 4; i++) {
                    { u16 idv = d->id[i]; if (idv == w->x4) {
                        s = d->nm[i];
                        break;
                    } }
                }
                }
            } else {
                s = "\x83""V\x83""\x85""\x81""[\x83""^\x81""[\x96""\xA2""\x94""z\x92""u!";
            }
            }
            break;
        default:
            switch (fn_800A0644(cx, cy)) {
            case 9:
                s = fn_8011D39C(fn_8010B240(0x6B));
                break;
            case 0xD:
                s = fn_8011D39C(fn_8010B240(0x6C));
                break;
            case 0xE:
                s = fn_8011D39C(fn_8010B240(0x6E));
                break;
            case 0x2A:
                s = fn_8011D39C(fn_8010B240(0x6D));
                break;
            default:
                s = fn_8011D39C(ter);
                break;
            }
            {
            TUnit* q2 = fn_80066130(lbl_803CB770, cx, cy, 0x10);
            if (q2 != 0) s = fn_8011D39C(fn_8010B240(q2->x4));
            }
            break;
        }
        if (nob != 0) fn_801ABC34(tex, (TerP*)ter, 0x30, 0x23);
    }
    if (s != 0) {
        FontReset();
        fn_800CB3A8(0.8f, 0.0f, 0x60 - fn_800CA3DC(s, -1, 0.8f) / 2, 0xE, 1, 0, 0, s);
    }
    SetScale(1.0f);
    fn_8007E7F4();
}

