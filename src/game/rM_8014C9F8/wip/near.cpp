/* from fn_8014C9F8.cpp */
void fn_8014CFEC(void) {
    u32 w;
    u16 h;
    w = lbl_804CB878.w;
    h = ((Saved*)&lbl_804CB878)->h;
    Proc* p;
    lbl_804CB700 |= 2;
    if (!(lbl_804CB878.w & 0x40)) {
        p = fn_80083B84(lbl_80386C80);
        if (p != NULL) {
            if (lbl_804CB700 & 3) {
                fn_80081A90(p);
            } else {
                fn_80083B78(p);
            }
        }
    }
    lbl_804CB878.w = w;
    lbl_804CB878.h = h;
}

/* from fn_8014D370.cpp */
void fn_8014D808(Snow* s) {
    while (1) {
        if (s->acc < 0.0f) {
            s->acc += s->rate;
            return;
        }
        if (0x100 - fn_800839DC() < 1) {
            return;
        }
        int i;
        FlakeProc* p = (FlakeProc*)fn_80081050(lbl_80386CD0, s);
        for (i = 0; i < 3; i++) {
            p->f[i].x = fn_80089ED0() % 0x2600000;
            p->f[i].y = -(fn_80089ED0() & 0x3FFFFF);
            FlakeInitRest(p, i, s);
        }
        s->acc -= 1.0f;
    }
}

/* from fn_8014D370.cpp */
void fn_8014D9FC(void* parent, u8* tint) {
    Snow* s = (Snow*)fn_80081050(lbl_80386CE0, parent);
    if (s != NULL) {
        lbl_804CB898 = 0x2000;
        lbl_804CB890 = 0x4000;
        lbl_804CB894 = 0xC000;
        lbl_804CB89C = 0x1000;
        lbl_804CB8A0 = 0x28;
        lbl_804CB8A1 = 0x80;
        s->rate = 0.2f;
        s->acc = 0.0f;
        s->tint = tint;
        while (1) {
            if (0x80 - fn_800839DC() < 1) {
                return;
            }
            int i;
            FlakeProc* p = (FlakeProc*)fn_80081050(lbl_80386CD0, s);
            for (i = 0; i < 3; i++) {
                p->f[i].x = fn_80089ED0() % 0x25F0000;
                p->f[i].y = fn_80089ED0() % 0x1F40000 - 0xC80000;
                FlakeInitRest(p, i, s);
            }
        }
    }
}

/* from fn_8014EABC.cpp */
void fn_8014EAC4(Fog* p) {
    int i;
    for (i = 0; i < 2; i++) {
        p->l[i].x += p->l[i].vx;
        p->l[i].y += p->l[i].vy;
        f32 z = p->z - (f32)i;
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, z, 1.0f);
        fn_8007E374(lbl_804CB888, 5, 0x11);
        fn_8007E164();
        fn_800800D4(3);
        fn_80080388(0.0f, 0.0f, 608.0f, 448.0f);
        fn_800803C8(p->l[i].x / 8, p->l[i].y / 8, 304.0f, 224.0f);
        {
            Color c3 = {0xFF, 0xFF, 0xFF, p->l[i].a1};
            Color c2 = {0xFF, 0xFF, 0xFF, p->l[i].a1};
            Color c1 = {0xFF, 0xFF, 0xFF, p->l[i].a0};
            Color c0 = {0xFF, 0xFF, 0xFF, p->l[i].a0};
            fn_80080940(c0, c1, c2, c3);
        }
        fn_80080578(0);
        fn_80080308();
    }
}

/* from fn_8014EABC.cpp */
void fn_801507EC(void) {
    char buf[0x50];
    fn_8006074C(lbl_803CAB38);
    fn_80290DDC(buf, lbl_80369FE8 + 0x27, fn_8009283C());
    MsgPutc(&lbl_80413F10, ' ');
    MsgEol(&lbl_80413F10);
    MsgPuts(&lbl_80413F10, buf);
}

/* from fn_80150AC0.cpp */
void fn_80150B20(Win* w, Color* c) {
    u8 a, b, g, r;
    r = c->r;
    a = c->a;
    g = c->g;
    b = c->b;
    w->col.r = r;
    w->col.g = g;
    w->col.b = b;
    w->col.a = a;
    c->a = 0xFF;
}

/* from fn_80150AC0.cpp */
void fn_801516AC(WinFade* f) {
    fn_8014D220(&lbl_804CB878);
    if ((lbl_804CB700.has(3)) || (lbl_804CB878.has(0x400))) {
        if (f->c != 0) {
            WinClear(f->win);
        } else {
            WinNext(f->win);
        }
        fn_80081A90(f);
    } else {
        f->win->reveal = fn_8017F68C(0, f->a, 0.0f, f->sleep, f->b);
    }
}

/* from fn_80150AC0.cpp */
void fn_80151DE8(void* a, void* parent, int t) {
    Proc* p;
    if (lbl_804CB878.has(0x200)) {
        return;
    }
    if (lbl_804CB700.has(3)) {
        return;
    }
    if (!(lbl_804CB700.has(0x6000)) && !(lbl_804CB878.has(0x40000))) {
        if ((*fn_80060728(lbl_803CAB38) >> 27 & 3) == 3) {
            return;
        }
    }
    if (((s8*)fn_80060728(lbl_803CAB38))[0x23] != 0) {
        t = t * ((s8*)fn_80060728(lbl_803CAB38))[0x23] / 4;
        if (t == 0) {
            t = 1;
        }
    }
    p = fn_80081194(lbl_80386E68, parent);
    p->sleep = t;
}

/* from fn_80150AC0.cpp */
void fn_801520C0(Win* w, void* parent) {
    if (!(lbl_804CB700.has(3))) {
        int i;
        w->col.a = 0xFF;
        w->alpha = 0xFF;
        Dissolve* d = (Dissolve*)fn_80081194(lbl_80386E8C, parent);
        lbl_804CB8A8 = d;
        d->left = 0x40;
        d->pos = 0;
        d->tex = (u8*)fn_800791B0(0x200);
        d->order = (s16*)fn_800791B0(0x400);
        for (i = 0; i < 0x200; i++) {
            d->order[i] = i;
            d->tex[i] = 0;
        }
        for (i = 0; i < 0x200; i++) {
            int j = fn_80089C88(0x200 - i) + i;
            s16 t = d->order[i];
            d->order[i] = d->order[j];
            d->order[j] = t;
        }
    }
}

/* from fn_80160728.cpp */
int fn_80161A54(Unit* u, AiCmd* c) {
    u8* p;
    int n = 0;
    FOR_SIDE0(n);
    if (n > 0x46) {
        return 0;
    }
    p = fn_80076F54(c->y);
    fn_80160610(0x5A, u->x, (s8)*(u8*)&u->y, NULL, 0, 0, -1, 0, 0);
    ((AiActX*)&lbl_803CA870)->arg[0] = p[0];
    return 0;
}

/* from fn_80152C20.cpp */
int fn_8015804C(Unit* u, int x, int y) {
    u8* t = fn_801181E8(&lbl_803EC898, (s8)x, (s8)y);
    int b = Terrain(u, t) >> 1;
    b += fn_80158208(u, x, y, 0);
    return b - ((fn_801676D8((s8)x, (s8)y) >> 4) & 0xFFF);
}

/* from fn_80152C20.cpp */
int fn_801586C8(Unit* a, Unit* d, int* pa, int* pd, void* w) {
    /*P*/
    int da;
    int dd;
    u32 r;
    int sa;
    int sd;
    BOOL ka;
    BOOL kd;
    /*E*/
    dd = 0;
    r = 0;
    sa = *(s16*)((u8*)a + 0x44C);
    sd = *(s16*)((u8*)d + 0x44C);
    ka = sa >= sd + 4;
    kd = sd >= sa + 4;
    da = fn_80158354(a, d, w, 1);
    if (d->hp <= da) {
        r |= 2;
    } else {
        dd = fn_80158354(d, a, w, 0);
        if (a->hp <= dd) {
            r |= 1;
        } else {
            if (ka) {
                da += fn_80158354(a, d, w, 1);
                if (d->hp <= da) {
                    r |= 2;
                    goto end;
                }
            }
            if (kd) {
                dd += fn_80158354(d, a, w, 0);
                if (a->hp <= dd) {
                    r |= 1;
                }
            }
        }
    }
end:
    if (da < 1) {
        r |= 8;
    }
    if (dd < 1) {
        r |= 4;
    }
    *pa = da;
    *pd = dd;
    return r;
}

/* from fn_80152C20.cpp */
int fn_8015897C(s8* w) {
    /*P*/
    Map* m = &lbl_803EC898;
    u8* b = lbl_803C8E80;
    int r = 0;
    s8* p = lbl_8036A0DC;
/*E*/
    for (; *p != 0x7F; p += 3) {
        s16 ty;
        s16 tx;
        BOOL out;
        tx = p[0] + *(s8*)(b + 0x102);
        out = 0;
        ty = p[1] + *(s8*)(b + 0x103);
        if (tx < m->x0 || m->x1 - 1 < tx || ty < m->y0 || m->y1 - 1 < ty) {
            out = 1;
        }
        if (!out && m->ter[0][(s8)tx + (s8)ty * 0x40] != 0) {
            if (IsFoeT(*(Unit**)(b + 0x3F0), UnitGet(m->ter[0][(s8)tx + (s8)ty * 0x40])) == 0) {
                r += p[2];
            }
        }
    }
    return 0.03125f * ((f32)r * (f32)w[7]);
}

/* from fn_80158C8C.cpp */
u8 fn_80158CA0(Unit* u) {
    lbl_804CB8B4 = 0;
    lbl_804CB8B8 = (AiCmd*)lbl_8036A128;
    lbl_804CB8B8 += fn_80129600(u, 0);
    lbl_804CB8B0 = 0;
    lbl_804183F0.op = lbl_804CB8B8->b;
    RunCmd(u);
    return lbl_804CB8B0;
}

/* from fn_80158C8C.cpp */
u8 fn_80158DB8(Unit* u) {
    lbl_804CB8B4 = 1;
    lbl_804CB8B8 = (AiCmd*)lbl_8036A178;
    lbl_804CB8B8 += fn_80129600(u, 1);
    lbl_804CB8B0 = 0;
    *((u8*)u + 0x3D0) = 0x40;
    lbl_804183F0.op = lbl_804CB8B8->b;
    RunCmd(u);
    return lbl_804CB8B0;
}

/* from fn_80158C8C.cpp */
u8 fn_80158EE0(Unit* u) {
    lbl_804CB8B4 = 2;
    lbl_804CB8B8 = (AiCmd*)lbl_8036A1C8;
    lbl_804CB8B8 += fn_80129600(u, 2);
    lbl_804CB8B0 = 0;
    *((u8*)u + 0x3D0) = 0x40;
    lbl_804183F0.op = lbl_804CB8B8->b;
    RunCmd(u);
    return lbl_804CB8B0;
}

/* from fn_80158C8C.cpp */
u8 fn_80159008(Unit* u) {
    lbl_804CB8B4 = 0;
    lbl_804CB8B8 = fn_80076F54(*(u32*)((u8*)u + 0x394));
    lbl_804CB8B8 += fn_80129600(u, lbl_804CB8B4);
    lbl_804CB8B0 = 0;
    lbl_804183F0.op = lbl_804CB8B8->b;
    RunCmd(u);
    return lbl_804CB8B0;
}

/* from fn_80158C8C.cpp */
u8 fn_80159124(Unit* u) {
    lbl_804CB8B4 = 1;
    lbl_804CB8B8 = fn_80076F54(*(u32*)((u8*)u + 0x398));
    lbl_804CB8B8 += fn_80129600(u, lbl_804CB8B4);
    lbl_804CB8B0 = 0;
    lbl_804183F0.op = lbl_804CB8B8->b;
    RunCmd(u);
    return lbl_804CB8B0;
}

/* from fn_80158C8C.cpp */
u8 fn_80159244(Unit* u) {
    lbl_804CB8B4 = 2;
    lbl_804CB8B8 = fn_80076F54(*(u32*)((u8*)u + 0x39C));
    lbl_804CB8B8 += fn_80129600(u, lbl_804CB8B4);
    lbl_804CB8B0 = 0;
    lbl_804183F0.op = lbl_804CB8B8->b;
    RunCmd(u);
    return lbl_804CB8B0;
}

/* from fn_80158C8C.cpp */
void fn_801596C0(Unit* u) {
    /*P*/
    AiCfg* cfg = &lbl_804183F0;
    AiCmd* c = lbl_804CB8B8;
    int v;
    s16 x = lbl_803CA870.x;
    s16 y = lbl_803CA870.y;
    /*E*/
    cfg->res[c->a] = 0;
    v = c->c;
    if (fn_8016D1DC(x, y, v, (c->fl >> 4) & 1) != 0) {
        if (c->fl & 0x10) {
            x = fn_800CFD3C(lbl_803E7320)[0];
            y = fn_800CFD3C(lbl_803E7320)[1];
        }
        fn_80160508(v, u, (s8)x, (s8)y, -1, 0, 0);
    } else {
        cfg->res[c->a] = 9;
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
void fn_8015B1C4(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    lbl_804183F0.res[0] = 0;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        /*P*/
        u32 fl;
        int cx;
        int cy;
        int r;
        int x0;
        int x1;
        int y1;
        int x;
        int y;
        u32 p;
/*E*/
        fl = lbl_804CB8B8->fl;
        p = lbl_804CB8B8->c;
        cx = (s32)p >> 16;
        cy = (s16)(p & 0xFFFF);
        if (fl & 1) {
            fn_80165F94(u, 6, -1);
            r = (s16)c->a;
            x0 = cx - r;
            if (x0 < lbl_803EC898.x0) {
                x0 = lbl_803EC898.x0;
            }
            y = cy - r;
            if (y < lbl_803EC898.y0) {
                y = lbl_803EC898.y0;
            }
            x1 = cx + r;
            if (x1 > lbl_803EC898.x1 - 1) {
                x1 = lbl_803EC898.x1 - 1;
            }
            y1 = cy + r;
            if (y1 > lbl_803EC898.y1 - 1) {
                y1 = lbl_803EC898.y1 - 1;
            }
            for (; y <= y1; y++) {
                for (x = x0; x <= x1; x++) {
                    if (r >= ABS(cx - x) + ABS(cy - y)) {
                        if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 &&
                            lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 &&
                            fn_801658E4(u, x, y) == 0) {
                            lbl_803EC898.costS[(s8)x + (s8)y * 0x40] = -1;
                        }
                    }
                }
            }
            fl = c->fl;
            fn_8016EFC8(u, cx, cy, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        } else {
            fn_8016F94C(u, cx, cy, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        }
        if (lbl_804183F0.done != 0) {
            int dy = __abs(cy - lbl_803CA870.y);
            int dx = __abs(cx - lbl_803CA870.x);
            if (dx + dy <= c->a) {
                lbl_804183F0.res[0] = 8;
            } else if (fn_80170C48(cx, cy, lbl_803CA870.x, lbl_803CA870.y)) {
                lbl_804183F0.res[0] = 2;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
void fn_8015BD44(Unit* u) {
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        /*P*/
u16 m;
        s16 bx;
        s16 by;
        s16 best;
        int x0;
        int cx;
        int cy;
        int r;
        int y;
        int x1;
        int y1;
        int y0;
        int x;
/*E*/
        fn_80165F94(u, 6, -1);
        best = -1;
        cx = u->x;
        cy = u->y;
        r = fn_8012408C(u);
        x0 = cx - r;
        if (x0 < lbl_803EC898.x0) {
            x0 = lbl_803EC898.x0;
        }
        y0 = cy - r;
        if (y0 < lbl_803EC898.y0) {
            y0 = lbl_803EC898.y0;
        }
        x1 = cx + r;
        if (x1 > lbl_803EC898.x1 - 1) {
            x1 = lbl_803EC898.x1 - 1;
        }
        y1 = cy + r;
        if (y1 > lbl_803EC898.y1 - 1) {
            y1 = lbl_803EC898.y1 - 1;
        }
        for (y = y0; y <= y1; y++) {
            for (x = x0; x <= x1; x++) {
                if (r >= ABS(cx - x) + ABS(cy - y)) {
                    if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 &&
                        lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 &&
                        fn_801658E4(u, x, y) == 0 &&
                        lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40] == 0) {
                        m = fn_801676D8((s8)x, (s8)y);
                        if (fn_8016D11C(u) >= m) {
                            s16 v = fn_80089C88(0x7FFF);
                            if (v >= best) {
                                bx = x;
                                by = y;
                                best = v;
                            }
                        }
                    }
                }
            }
        }
        if (best != -1) {
            fn_80160610(1, (s8)bx, (s8)by, NULL, (s8)bx, (s8)by, -1, 0, 0);
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
void fn_8015CC24(Unit* u) {
    /*P*/
    u32 fl;
    AiCmd* c = lbl_804CB8B8;
    u8* path;
    s16* pts;
    BOOL moved;
    int x;
    int y;
    s16 mv;
    int tx;
    int ty;
/*E*/
    if (!(lbl_804183F0.flags & 2)) {
        if (!(u->w3B4 & 0x7000000)) {
            path = (u8*)u + 0x3D0;
            pts = (s16*)lbl_804CB8B8->x;
            int k = (s16)lbl_804CB8B8->c;
            if (k < 0) {
                k = fn_8012408C(u);
            }
            mv = k;
            moved = 0;
            x = u->x;
            y = u->y;
            for (;;) {
                u16 i = *(u16*)((u8*)u + 0x3B8);
                fl = c->fl;
                tx = pts[i * 2];
                ty = pts[i * 2 + 1];
                fn_8016FA34(x, y, u, tx, ty, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, mv);
                if (lbl_804183F0.done == 0) {
                    break;
                }
                {
                    int ox = x;
                    int oy = y;
                    AiAct* act = &lbl_803CA870;
                    x = act->x;
                    y = act->y;
                    moved = 1;
                    if ((s16)ox == x && (s16)oy == y) {
                        break;
                    }
                }
                fn_80116294(&lbl_803EC898, path, x, y, 0x20);
                while (*path != 0x40) {
                    path++;
                }
                int dy = __abs(ty - y);
                int dx = __abs(tx - x);
                if (dx + dy > c->a) {
                    break;
                }
                {
                    int n = *(u16*)((u8*)u + 0x3B8) + 1;
                    u16 v = n;
                    if (pts[(u16)n * 2] < 0) {
                        v = 0;
                    }
                    *(u16*)((u8*)u + 0x3B8) = v;
                }
                mv -= lbl_803EC898.costS[x + y * 0x40];
                if (mv <= 0) {
                    break;
                }
            }
            if (moved) {
                ActS(lbl_803CA870.action, x, y);
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
void fn_8015CE40(Unit* u) {
    /*P*/
    Inv* v;
    u32 fl;
    int best;
    int i;
    void* s;
/*E*/
    Fn4 g3;
    Fn4 g2;
    Fn4 f2;
    Fn4 f3;
    Fn2 g1;
    Fn2 f1;
    s16 x2;
    s16 y2;
    s16 y;
    s16 x;
    u32 w = u->w3B4;
    if (!(w & 0x1000)) {
        AiCmd* c = lbl_804CB8B8;
        if (!(lbl_804183F0.flags & 2) && !(w & 0x7000000)) {
            Fn2Set(&f1, lbl_80387308, u);
            Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
            Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
            if (lbl_804CB8B8->x == 0) {
                s = &f1;
            } else {
                s = &f3;
                if (lbl_804CB8B8->fl & 1) {
                    s = &f2;
                }
            }
            if (fn_8016E50C(s, u, &x, &y) == 1) {
                fl = c->fl;
                fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            }
        }
        fn_80129550(u, lbl_804CB8B4);
    } else {
        AiCmd* c = lbl_804CB8B8;
        if (!(lbl_804183F0.flags & 2) && !(w & 0x7000000)) {
            Fn2Set(&g1, lbl_80387308, u);
            Fn4Set(&g3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
            Fn4Set(&g2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
            if (lbl_804CB8B8->x == 0) {
                s = &g1;
            } else {
                s = &g3;
                if (lbl_804CB8B8->fl & 1) {
                    s = &g2;
                }
            }
            if (fn_8016E50C(s, u, &x2, &y2) == 1) {
                v = u->inv;
                best = 0x7FFF;
                i = 0;
                do {
                    if (v == NULL || v->item == NULL) {
                        break;
                    }
                    if (fn_8012BA20(u, v->item) != 0) {
                        if (InvRange(u, v) < (s16)best) {
                            best = InvRange(u, v);
                        }
                    }
                    i++;
                    v++;
                } while (i < 7);
                if ((s16)best < 0x7FFF && (s16)best > 1) {
                    fn_80165F94(u, 6, -1);
                    fn_80116BD0(&lbl_803EC898, (s8)x2, (s8)y2, (s8)(best - 1), (s16)-(fn_8012408C(u) + 1));
                    fl = c->fl;
                    fn_8016EFC8(u, x2, y2, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
                }
            }
        }
        fn_80129550(u, lbl_804CB8B4);
    }
}

/* from fn_80158C8C.cpp */
void fn_8015D59C(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        Fn4 f3;
        Fn4 f2;
        Fn2 f1;
        Fn3x g;
        /*P*/
        int m;
        void* s;
        s16 d;
        s8 x;
        s8 y;
        u32 fl;
        /*E*/
        Fn2Set(&f1, lbl_80387308, u);
        Fn4Set(&f3, lbl_803872C8, u, lbl_804CB8B8->x, 3);
        Fn4Set(&f2, lbl_803872B8, u, lbl_804CB8B8->x, 1);
        if (lbl_804CB8B8->x == 0) {
            s = &f1;
        } else {
            s = &f3;
            if (lbl_804CB8B8->fl & 1) {
                s = &f2;
            }
        }
        d = 0;
        {
            AiAct* a = &lbl_803CA870;
        if (((s8*)a)[0x16] != 0) {
            m = ((s8*)u)[0x3BB];
            d = fn_8012408C(u) - m;
            ((s8*)u)[0x116] = d + ((s8*)u)[0x116];
        }
        }
        Fn3Set(&g, lbl_80387208, u, c->c);
        fn_80152C20(s, &g, 0xF);
        {
            AiAct* a = &lbl_803CA870;
        if (((s8*)a)[0x16] != 0) {
            ((s8*)u)[0x116] -= d;
        }
        }
        if (lbl_804183F0.done != 0) {
            fl = c->fl;
            Unit* t = *(Unit**)((u8*)&lbl_803CA870 + 4);
            x = t->x;
            y = t->y;
            fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
            if (lbl_803CA870.action != 1) {
                lbl_804183F0.done = 0;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
void fn_8015D768(Unit* u) {
    AiCfg* cfg = &lbl_804183F0;
    AiAct* act;
    u32 fl;
    AiCmd* c = lbl_804CB8B8;
    cfg->res[0] = 0;
    if (!(cfg->flags & 2) && !(u->w3B4 & 0x7000000)) {
        fl = c->fl;
        int x = ((s8*)&lbl_803CA870)[0xF];
        int y = ((s8*)&lbl_803CA870)[0x10];
        fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        act = &lbl_803CA870;
        if (cfg->done != 0) {
            s8 ay = act->y;
            s8 ax = act->x;
            int dy = __abs(y - ay);
            int dx = __abs(x - ax);
            if (dx + dy <= c->a) {
                cfg->res[0] = 8;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
void fn_8015DC64(Unit* u) {
    /*P*/
    AiCmd* c = lbl_804CB8B8;
    int a;
    /*E*/
    s16 x;
    s16 y;
    s16 x2;
    s16 y2;
    lbl_804183F0.res[c->a] = 0;
    if (fn_8016D5D4(u, 0, c->c, &x, &y) != 0) {
        if (fn_8016D5D4(u, 1, c->c, &x2, &y2) != 0) {
            x = x2;
            y = y2;
        }
        u32 fl = c->fl;
        fn_8016F94C(u, x, y, 1, fn_8016D11C(u), !(fl & 4), (fl >> 1) & 1, -1);
        a = 0x3B;
        if (c->c != 0) {
            a = 0x37;
        }
        AiAct* act = &lbl_803CA870;
        if (x == act->x && y == act->y) {
            if (*(int*)lbl_803E7320 > 0) {
                lbl_804183F0.res[c->a] = 8;
                u8 b = fn_800CFD18(lbl_803E7320, 0)[1];
                fn_80160508(a, *(Unit**)((u8*)act + 4), fn_800CFD18(lbl_803E7320, 0)[0], (s8)b, -1, 0, 0);
            } else {
                lbl_804183F0.res[c->a] = 9;
            }
        } else {
            AiAct* b2 = &lbl_803CA870;
            if (b2->action == 1) {
                fn_80164938(u, a);
            }
        }
    } else {
        lbl_804183F0.res[c->a] = 9;
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
void fn_8015EC54(Unit* u) {
    int hp;
    AiCmd* c = lbl_804CB8B8;
    lbl_804183F0.res[c->c] = u->hp;
    int h = u->hp;
    lbl_804183F0.res[c->d] = h * 100 / fn_801237EC(u);
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_80158C8C.cpp */
void fn_8015F07C(Unit* u) {
    /*P*/
    s16 best;
    int cx;
    AiCmd* c = lbl_804CB8B8;
    int cy;
    u32 fm;
    int r;
    int x0;
    int x1;
    int y1;
    int y;
    int x;
    u32 f;
    u32 p;
/*E*/
    lbl_804183F0.res[c->b] = 0;
    f = u->w3B4;
    p = c->c;
    u->w3B4 = f & ~0x7000000;
    fm = f & 0x7000000;
    cx = (s32)p >> 16;
    cy = (s16)(p & 0xFFFF);
    if (c->fl & 4) {
        fn_80165F94(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    } else {
        fn_80165E18(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    }
    u->w3B4 |= fm;
    best = 0x7FFF;
    {
        r = (s16)c->a;
        x0 = cx - r;
        if (x0 < lbl_803EC898.x0) {
            x0 = lbl_803EC898.x0;
        }
        y = cy - r;
        if (y < lbl_803EC898.y0) {
            y = lbl_803EC898.y0;
        }
        x1 = cx + r;
        if (x1 > lbl_803EC898.x1 - 1) {
            x1 = lbl_803EC898.x1 - 1;
        }
        y1 = cy + r;
        if (y1 > lbl_803EC898.y1 - 1) {
            y1 = lbl_803EC898.y1 - 1;
        }
        for (; y <= y1; y++) {
            for (x = x0; x <= x1; x++) {
                if (r >= ABS(cx - x) + ABS(cy - y)) {
                    if (((s16*)lbl_803EC898.cur)[(s8)x + (s8)y * 0x40] >= 0 &&
                        lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 &&
                        fn_801658E4(NULL, x, y) == 0) {
                        s16 t = ((s16*)lbl_803EC898.cur)[(s8)x + (s8)y * 0x40];
                        if (t < best) {
                            best = t;
                        }
                    }
                }
            }
        }
    }
    {
        int k = -1;
        if (best != 0x7FFF) {
            k = best;
        }
        lbl_804183F0.res[c->b] = k;
    }
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_8015F2DC.cpp */
void fn_8015F2DC(Unit* u) {
    AiCmd* c = lbl_804CB8B8;
    int v;
    int t;
    lbl_804183F0.res[c->a] = 0;
    v = c->c;
    if (c->fl & 8) {
        if (fn_8012408C(u) < v) {
            v = fn_8012408C(u);
        } else if (v < 0) {
            v = 0;
        }
        v -= fn_8012408C(u);
    }
    if (v + fn_8012408C(u) < 0) {
        v = -fn_8012408C(u);
    }
    {
        int o = (s8)*((u8*)u + 0x3BA);
        int mm = ((u8*)u)[0x116];
        t = v + o;
        ((s8*)u)[0x116] = v + mm;
    }
    if (t > 0x7F) {
        t = 0x7F;
    }
    if (t < -0x80) {
        t = -0x80;
    }
    ((s8*)u)[0x3BA] = t;
    lbl_804183F0.res[c->a] = fn_8012408C(u);
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_8015F2DC.cpp */
void fn_8015F408(Unit* u) {
    /*P*/
    AiCmd* c = lbl_804CB8B8;
    int v;
    Unit* o;
    u32 b;
/*E*/
    lbl_804183F0.res[c->a] = 0;
    o = *(Unit**)((u8*)u + 0x3C0);
    b = (c->fl >> 7) & 1;
    if (o != NULL && (b != 0 || o == u)) {
        int t;
        v = fn_8012408C(u) - fn_801725A0(u);
        if (v + fn_8012408C(u) < 0) {
            v = fn_8012408C(u);
        }
        {
            int p = (s8)*((u8*)u + 0x3BA);
            int mm = ((u8*)u)[0x116];
            t = p - v;
            ((s8*)u)[0x116] = mm - v;
        }
        if (t > 0x7F) {
            t = 0x7F;
        }
        if (t < -0x80) {
            t = -0x80;
        }
        ((s8*)u)[0x3BA] = t;
    }
    lbl_804183F0.res[c->a] = fn_8012408C(u);
    fn_80129550(u, lbl_804CB8B4);
}

/* from fn_8015F2DC.cpp */
void fn_8015F680(void* p) {
    if (PickUnit() == NULL) {
        switch (lbl_804183F0.res[0x86]) {
        case 0:
            lbl_804183F0.res[0x85] = (int)&lbl_804183F0.res[5];
            lbl_804183F0.res[0x86]++;
            fn_80083DC4(p, 0);
            break;
        default:
            fn_80083DC4(p, 4);
            break;
        }
    }
}

/* from fn_8015F2DC.cpp */
void fn_8015F914(void* p) {
    AiAct* act = &lbl_803CA870;
    Unit* u = act->unit;
    if (u->hp == 0) {
        return;
    }
    if ((u->flags10C & 0x18) == 0) goto ok;
    return;
ok:
    if (u->flags10C & 1) {
        return;
    }
    if (lbl_803CAB38[0x11] != u->team[8]) {
        fn_800453B4(act, 1);
        return;
    }
    switch (act->action) {
    case 6:
    case 7:
    case 0x1C:
    case 0x1D:
    case 0x29:
    case 0x3D:
        (*(Unit***)&lbl_804183F0.res[0x85]) -= 1;
        u->w3B4 |= 0x4010000;
        fn_80083DC4(p, 1);
        return;
    default:
        u->w3B4 &= ~0x4000000;
        return;
    }
}

/* from fn_8015F2DC.cpp */
void fn_8015FAF8(void) {
    AiAct* a = &lbl_803CA870;
    Unit* u = a->unit;
    u->flags10C |= 1;
}

/* from fn_8015F2DC.cpp */
void fn_8015FCAC(void) {
    Unit* u = lbl_803CA870.unit;
    int d;
    u8 a;
    lbl_804183F0.done = 0;
    fn_800453CC(&lbl_803CA870);
    fn_800453FC(&lbl_803CA870);
    a = ((u8*)&lbl_803CA870)[0x15];
    d = a - fn_8012408C(u);
    ((s8*)u)[0x116] = d + ((s8*)u)[0x116];
    ((s8*)u)[0x3BB] = d;
    if (!(lbl_804183F0.flags & 4)) {
        if (fn_8016D0B0(u) != 0) {
            fn_80158EE0(u);
        } else {
            int i = 0;
            for (;;) {
                if (fn_80159244(u) == 1) {
                    break;
                }
                if (i > 0xFF) {
                    fn_80158EE0(u);
                    break;
                }
                i++;
            }
        }
    }
    ((s8*)u)[0x116] -= d;
    ((s8*)u)[0x3BB] = 0;
}

/* from fn_8015F2DC.cpp */
char fn_80160018(Unit* u) {
    AiCfg* cfg = &lbl_804183F0;
    int st = (s8)cfg->b1;
    fn_80163014(cfg, u);
    for (;;) {
        u8 d;
        if (cfg->flags & 4) {
            d = 0;
        } else {
            int i = 0;
            for (;;) {
                if (fn_80159008(u) == 1) {
                    break;
                }
                if (i > 0xFF) {
                    fn_80158CA0(u);
                    break;
                }
                i++;
            }
            d = lbl_804183F0.done;
        }
        if (d != 0) {
            if (u->b3BC & 2) {
                fn_80163080(cfg, NULL);
                return cfg->done;
            }
            cfg->done = 0;
            fn_80163080(cfg, u);
            return cfg->done;
        }
        if (st == cfg->b1) {
            fn_80163080(cfg, u);
            return cfg->done;
        }
        cfg->b1 = st;
    }
}

/* from fn_80161E04.cpp */
int fn_80161F14(const F* f, Unit* v) {
    Unit* me = f->u;
    BOOL t = 0;
    int r;
    switch (lbl_803CAB38[me->team[8] + 0x14]) {
    case 0:
    case 1:
        t = 1;
        break;
    }
    r = 0;
    if (t && SameB(me, v)) {
        r = 1;
    }
    return r;
}

/* from fn_80161E04.cpp */
int fn_801626D4(const H* f, Unit* v) {
    BOOL t = SideTest(f->u, f->k, v);
    int r = 0;
    if (t != 0) {
        Unit* me = f->u;
        BOOL n = 1;
        if (v != *(Unit**)((u8*)me + 0x3C4)) {
            int dy = __abs(((s8*)me)[0x3CF] - v->y);
            int dx = __abs(((s8*)me)[0x3CE] - v->x);
            if (dx + dy > f->r) {
                n = 0;
            }
        }
        if (n != 0) {
            r = 1;
        }
    }
    return r;
}

/* from fn_80161E04.cpp */
BOOL fn_8016281C(const J* f, Unit* v) {
    BOOL t = SideB(f->k, f->u, v);
    BOOL n = 0;
    BOOL r = 0;
    if (t != 0) {
        n = NameIn(*(char**)v->person, f->s);
    }
    if (n != 0) {
        r = NearT(f, v);
    }
    return r;
}

/* from fn_80161E04.cpp */
BOOL fn_801629B4(const J* f, Unit* v) {
    BOOL t = SideB(f->k, f->u, v);
    BOOL n = 0;
    BOOL r = 0;
    if (t != 0) {
        n = NameIn(*(char**)v->person, f->s) == 0;
    }
    if (n != 0) {
        r = NearT(f, v);
    }
    return r;
}

/* from fn_80161E04.cpp */
BOOL fn_80162B54(Fn3* f, Unit* v) {
    BOOL t = SideTest(f->u, f->b, v);
    if (t == 0) {
        return 0;
    }
    if (fn_8011F1A8(f->u, v) == 0) {
        return 0;
    }
    {
        BA b2 = {NULL, 0, 0, 0, 1, 0, 0};
        b2.u = v;
        b2.x = v->x;
        b2.y = v->y;
        b2.p = fn_80127520(v);
        {
            BA b1 = {NULL, 0, 0, 0, 1, 0, 0};
            b1.u = f->u;
            b1.x = b1.u->x;
            b1.y = b1.u->y;
            b1.p = fn_8016D144(b1.u);
            fn_800269E4(lbl_803C8E80, b1, b2);
        }
    }
    fn_8002742C(lbl_803C8E80, 0xF);
    u8* b = lbl_803C8E80;
    return (*(s16*)(b + 0x448) - *(s16*)(b + 0x8EA)) * (*(s16*)(b + 0x452) != 0) > 0;
}

/* from fn_80161E04.cpp */
BOOL fn_80162F04(H* f, Unit* unused, int x, int y) {
    Unit* o = *(Unit**)((u8*)f->u + 0x3C0);
    s8 ox;
    s8 oy;
    if (o == NULL) {
        return 1;
    }
    if (*(void**)((u8*)o + 0x3C4) != NULL) {
        ox = ((s8*)o)[0x3CC];
        oy = ((s8*)o)[0x3CD];
    } else {
        ox = o->x;
        oy = o->y;
    }
    int dy = __abs(oy - y);
    int dx = __abs(ox - x);
    return dx + dy <= f->r;
}

/* from fn_80161E04.cpp */
BOOL fn_80162F88(H* f, Unit* unused, int x, int y) {
    int dy = __abs(f->u->y - y);
    int dx = __abs(f->u->x - x);
    return dx + dy < f->r;
}

/* from fn_80150AC0.cpp: 9 words differ, only the stack slots of the first colour pair.
   Needs extern u8 lbl_804CA7A0..A6, a by-value fn_802291A8 and W1 from the attempt. */
static const Color kC0={0xe,0x12,0xe,0xff};static const Color kC1={0x1c,0x27,0x1c,0xff};
static inline void Back(Win* w){
if (w->b83 != 0) {
                u8 a = 0xB2;
                if (lbl_804CB878.has(0x1000)) {
                    a = 0xFF;
                }
                fn_802291A8(w->bx, w->by, w->bw, W1(lbl_804CA7A0,lbl_804CA7A1,lbl_804CA7A2,a), W1(lbl_804CA7A4,lbl_804CA7A5,lbl_804CA7A6,a));
            } else {
                fn_802291A8(w->bx, w->by, w->bw, kC0, kC1);
            }
}
void fn_80150F0C(Win* w) {
    int i;
    if (w->parentNo >= 0) {
        u8* o = (u8*)fn_800C409C(w->parentNo);
        if (o != NULL) {
            w->bright = o[0x41] + fn_8014C83C();
        }
        if (w->alpha != 0) {
            fn_8007E154();
            fn_8007E4E4(0.0f, 0.0f, w->bz, 1.0f);
            if (lbl_804CB878.has(0x200000)) {
                fn_8007E84C(1);
            }
            fn_8007E7DC(w->alpha);
            fn_8007E7E8(w->bright / 2);
            fn_8007E164();
            Back(w);
        }
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 61.0f, 1.0f);
    if (lbl_804CB8A8 != NULL) {
        fn_8007E780(fn_80150CC4, NULL);
        fn_8007E7DC(w->alpha);
    } else {
        fn_8007E174(NULL, 0x13);
        fn_8007E7DC(w->alpha);
        if (w->reveal != 0) {
            fn_8007E74C(fn_80151328, w->scissor);
            Rect4(w->scissor, w->x, w->y, w->x + w->w, w->y + w->h);
        }
    }
    fn_8007E164();
    for (i = 0; i < w->rows; i++) {
        int x;
        fn_800800D4(6);
        switch (w->style) {
        case 3:
            break;
        case 1:
            fn_80080ABC(1, 2.0f);
            fn_80080B70(0, 1.0f);
            break;
        case 2:
            fn_80080ABC(0, 2.0f);
            fn_80080B70(1, 1.0f);
            break;
        case 4:
            fn_80080B00(1, fn_800CD204(0x2A), 1.0f);
            fn_80080B70(0, 1.0f);
            break;
        }
        x = w->x;
        if (lbl_804CB878.has(0x200000)) {
            x = fn_8007E9BC(x);
        }
        fn_80080330(x, w->y + i * w->lineH - w->reveal);
        fn_800804D4(w->bright * w->col.r / 0xFF, w->bright * w->col.g / 0xFF, w->bright * w->col.b / 0xFF, w->col.a);
        fn_80080C24(w->lines[(w->head + i) % w->rows]->text);
        fn_80080308();
    }
    fn_8007E7F4();
}

