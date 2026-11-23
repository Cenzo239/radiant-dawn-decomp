/* near misses; take the declarations from ../fn_801BCB08.cpp */
void fn_801BC88C(void* a, int b, GXColor2 c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8) {
    void** t = (void**)fn_80006A0C(a, b);
    if (fl & 1) { f32 s = f5; f5 = f7; f7 = s; }
    if (fl & 2) { f32 s = f6; f6 = f8; f8 = s; }
    fn_8007E154();
    if (t[1] != 0) {
        fn_8007E41C(a, (void*)b, 0, (u16)d);
    } else {
        fn_8007E374(a, (void*)b, (u16)d);
    }
    fn_8007E164();
    fn_800800D4(2);
    fn_8008031C(0.0f);
    fn_80080348(f1, f2, f5, f6);
    fn_80080368(f3, f4, f7, f8);
    fn_80080508(c);
    fn_80080578(0);
    if (fl & 4) fn_80080690();
    if (fl & 8) fn_800806E0();
    fn_80080308();
}

void fn_801C6114(BData* d) {
    Slot* s = (Slot*)(d->unit + 0x12C);
    int n;
    int i;
    d->items[0] = 0;
    d->items[1] = 0;
    d->items[2] = 0;
    d->items[3] = 0;
    d->items[4] = 0;
    d->items[5] = 0;
    n = 0;
    for (i = 0; i < 18; s++, i++) {
        if (s && s->p && s->p->x1F) {
            if (n >= 6) return;
            d->items[0] = s;
            d = (BData*)((u8*)d + 4);
            n++;
        }
    }
}

void fn_801C62D8(BData* d, int dir) {
    int old = d->sel;
    BPage* tbl = lbl_8038A038;
    int i;
    int cur = (s8)tbl[d->page].e[old].next[dir];
    if (cur != -1) {
        for (i = 0;; i++) {
            if (i >= 10) cur = old;
            if (fn_801C61F4(d, cur)) break;
            {
                int nx = (s8)tbl[d->page].e[cur].next[dir];
                if (nx == -1) nx = *(s8*)((u8*)tbl + (cur * 0x14 + d->page * 0x21C) + 0xC);
                cur = nx;
            }
        }
        d->sel = cur;
        fn_801C63F0(d, &lbl_8038A038[d->page].e[cur]);
        if (old != cur) fn_80253EE4(lbl_8036E118 + 0x2A2, 0.0f);
    }
}

void fn_801C63F0(BData* d, BLink* e) {
    BLink* e2 = e;
    u8 t = e->type;
    if (t >= 2 && t <= 8) {
        int want = t - 2;
        int n = 0;
        int k;
        for (k = 0; k < 7; k++) {
            u8* inv = d->unit + 0x1BC;
            if (*(u32*)(inv + k * 0x28) != 0) n++;
            if (n - 1 == want) {
                fn_801A1F64(lbl_8041EB20, inv + k * 0x28, e->x, e->y);
                return;
            }
        }
    } else if (t >= 10 && t <= 15) {
        fn_801A1DCC(lbl_8041EB20, fn_8011A0A8(d->items[t - 10]->p), e2->x, e2->y);
    } else if (t == 0x11) {
        fn_801A1DCC(lbl_8041EB20, fn_80118D1C(*(void**)(d->unit + 0xEC)), e2->x, e2->y);
    } else if (t == 0x12) {
        fn_801A1DCC(lbl_8041EB20, fn_80118F68(*(void**)(d->unit + 0xF0)), e2->x, e2->y);
    } else {
        fn_801A1DCC(lbl_8041EB20, e->help, e->x, e->y);
    }
}

void fn_801BD780(u8 a, f32 x, f32 y, f32 w, f32 h, f32 s) {
    if (w < 64.0f) w = 64.0f;
    if (h < 80.0f) h = 80.0f;
    if (s < 48.0f) s = 48.0f;
    if (s > w - 48.0f) s = w - 48.0f;
    if (w < 96.0f) s = -1.0f;
    if (-1.0f == s) {
        f32 mw = w - 64.0f;
        fn_801BD170(1, a, 2, 0, x, y, 1.0f);
        fn_801BD2EC(1, a, 5, 8, 32.0f + x, y, mw, 8.0f);
        fn_801BD2EC(1, a, 1, 0, 32.0f + x, 8.0f + y, mw, 32.0f);
        fn_801BD170(1, a, 2, 1, mw + (32.0f + x), y, 1.0f);
        {
            f32 y2 = 40.0f + y;
            f32 mh = h - 80.0f;
            f32 w2 = w - 16.0f;
            fn_801BD2EC(1, a, 5, 0, x, y2, 8.0f, mh);
            fn_801BD2EC(1, a, 1, 0, 8.0f + x, y2, w2, mh);
            fn_801BD2EC(1, a, 5, 0, w2 + (8.0f + x), y2, 8.0f, mh);
            {
            f32 w3 = w - 64.0f;
            f32 y3 = mh + (40.0f + y);
            fn_801BD170(1, a, 2, 2, x, y3, 1.0f);
            fn_801BD2EC(1, a, 1, 0, 32.0f + x, y3, w3, 32.0f);
            fn_801BD2EC(1, a, 5, 8, 32.0f + x, 32.0f + y3, w3, 8.0f);
            fn_801BD170(1, a, 2, 3, w3 + (32.0f + x), y3, 1.0f);
            }
        }
    } else {
        f32 l = s - 48.0f;
        f32 r = (w - s) - 48.0f;
        fn_801BD170(1, a, 2, 0, x, y, 1.0f);
        fn_801BD2EC(1, a, 5, 8, 32.0f + x, y, l, 8.0f);
        fn_801BD2EC(1, a, 1, 0, 32.0f + x, 8.0f + y, l, 32.0f);
        fn_801BD170(1, a, 3, 0, l + (32.0f + x), y, 1.0f);
        fn_801BD2EC(1, a, 1, 0, l + (32.0f + x), 24.0f + y, 14.0f, 16.0f);
        fn_801BD2EC(1, a, 6, 0, 14.0f + (l + (32.0f + x)), 24.0f + y, 8.0f, 16.0f);
        fn_801BD2EC(1, a, 1, 0, 22.0f + (l + (32.0f + x)), 24.0f + y, 10.0f, 16.0f);
        fn_801BD2EC(1, a, 5, 8, 32.0f + (l + (32.0f + x)), y, r, 8.0f);
        fn_801BD2EC(1, a, 1, 0, 32.0f + (l + (32.0f + x)), 8.0f + y, r, 32.0f);
        fn_801BD170(1, a, 2, 1, r + (32.0f + (l + (32.0f + x))), y, 1.0f);
        {
            f32 l2 = (s - 8.0f) - 2.0f;
            f32 r2 = ((w - s) - 8.0f) - 6.0f;
            f32 y2 = 40.0f + y;
            f32 mh = h - 80.0f;
            fn_801BD2EC(1, a, 5, 0, x, y2, 8.0f, mh);
            fn_801BD2EC(1, a, 1, 0, 8.0f + x, y2, l2, mh);
            fn_801BD2EC(1, a, 6, 0, l2 + (8.0f + x), y2, 8.0f, mh);
            fn_801BD2EC(1, a, 1, 0, 8.0f + (l2 + (8.0f + x)), y2, r2, mh);
            fn_801BD2EC(1, a, 5, 0, r2 + (8.0f + (l2 + (8.0f + x))), y2, 8.0f, mh);
            {
            f32 l3 = s - 48.0f;
            f32 r3 = (w - s) - 48.0f;
            f32 y3 = mh + (40.0f + y);
            fn_801BD170(1, a, 2, 2, x, y3, 1.0f);
            fn_801BD2EC(1, a, 1, 0, 32.0f + x, y3, l3, 32.0f);
            fn_801BD2EC(1, a, 5, 8, 32.0f + x, 32.0f + y3, l3, 8.0f);
            fn_801BD2EC(1, a, 1, 0, l3 + (32.0f + x), y3, 14.0f, 16.0f);
            fn_801BD2EC(1, a, 6, 0, 14.0f + (l3 + (32.0f + x)), y3, 8.0f, 16.0f);
            fn_801BD2EC(1, a, 1, 0, 22.0f + (l3 + (32.0f + x)), y3, 10.0f, 16.0f);
            fn_801BD170(1, a, 4, 0, l3 + (32.0f + x), 16.0f + y3, 1.0f);
            fn_801BD2EC(1, a, 1, 0, 32.0f + (l3 + (32.0f + x)), y3, r3, 32.0f);
            fn_801BD2EC(1, a, 5, 8, 32.0f + (l3 + (32.0f + x)), 32.0f + y3, r3, 8.0f);
            fn_801BD170(1, a, 2, 3, r3 + (32.0f + (l3 + (32.0f + x))), y3, 1.0f);
            }
        }
    }
}
