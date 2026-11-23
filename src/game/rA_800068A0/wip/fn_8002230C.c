/* fn_8002230C: near miss, 215 of 217 words differ. Depends on types and helpers from ../fn_80021754.c; goes there in address order. */
void fn_8002230C(void) {
    static const GXColor8 colors[2] = {{0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}};
    GXCache* g = &lbl_803B7878;
    int i;
    {
        u32* a = g->a8000;
        u32* b = g->a8080;
        u32* c = g->a80C0;
        u32* d = g->a8100;
        u32* e = g->a8140;
        u32* f = g->a8040;
        u32* h = g->a8220;
        for (i = 0; i < 16; i++) {
            a[i] = -1;
            b[i] = -1;
            c[i] = -1;
            d[i] = -1;
            e[i] = -1;
            f[i] = -1;
            h[i] = -1;
        }
    }
    for (i = 0; i < 8; i++) {
        g->a8180[i] = -1;
    }
    for (i = 0; i < 64; i++) {
        g->a8260[i] = -1;
    }
    lbl_804CB0B8 = -1;
    lbl_804CB0BC = -1;
    lbl_804CB0C0 = -1;
    lbl_804CB0C4 = -1;
    lbl_804CB0C8 = -1;
    lbl_804CB0CC = -1;
    lbl_804CB0DC = -1;
    lbl_804CB0E0 = -1;
    lbl_804CB0D0 = -1;
    lbl_804CB0D4 = -1;
    lbl_804CB0D8 = 0;
    lbl_804CB0E4 = 0;
    lbl_804CB0E5 = 0;
    lbl_804CB0E6 = 0;
    lbl_804CB0E7 = 0;
    lbl_804CB0E8 = 1;
    fn_803055E4(4, colors[0]);
    fn_803056BC(4, colors[1]);
    fn_803077C4(0);
    fn_80307798(1);
    lbl_804CB0EA = 1;
    lbl_804CB0E9 = 1;
    fn_800221BC();
    fn_800220B0();
}
