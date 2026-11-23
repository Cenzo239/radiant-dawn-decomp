/* Near misses of region rO: not compiled. Each block notes the words that differ when last tried. */

/* from fn_80065D64.cpp: 25 of 225 words differ */
void fn_800665E4(TrapList* l, int arg) {
    Pt pos[31];
    Pt* p = pos;
    int n = 0;
    int i;
    for (i = 0; i < l->n; i++) {
        Trap* t = At(l, i);
        int ext = (s8)((u8*)t)[3];
        switch (t->type) {
        case 0xF:
            if (lbl_803CAB38[0x11] == 0) {
                t->ext = --ext;
                if ((s8)ext == 0) {
                    n++;
                    p->x = t->x;
                    p->y = t->y;
                    p++;
                    Remove(&lbl_803CB770, i);
                    i--;
                }
            }
            break;
        case 0xC:
            if (ext > 0 && lbl_803CAB38[0x11] == t->d[0]) {
                t->ext = --ext;
                if ((s8)ext == 0) {
                    ClearActor(t, 0x3C);
                    Remove(&lbl_803CB770, i);
                    i--;
                }
            }
            break;
        }
    }
    if (n > 0) {
        Pt* q = pos;
        for (i = 0; i < n; i++) {
            arg = fn_8013C80C(q->x, q->y, -1, arg);
            q++;
        }
    }
    fn_80114D00(&lbl_803EC898);
}

/* from fn_80065D64.cpp: 8 of 49 words differ */
void fn_80066AC0(TrapList* l, void* f) {
    int i;
    for (i = 0; i < 0x80; i++) {
        TrapSave(At(l, i), f);
    }
    fn_8008A5E4(f, l->n);
    fn_8008A780(f, 0x200, l->strs);
    fn_8008A5E4(f, l->strn);
}

/* from fn_80065D64.cpp: 9 of 49 words differ */
void fn_80066B84(TrapList* l, void* f) {
    int i;
    for (i = 0; i < 0x80; i++) {
        TrapLoad(At(l, i), f);
    }
    l->n = fn_8008A1DC(f);
    fn_8008A43C(f, 0x200, l->strs);
    l->strn = fn_8008A1DC(f);
}

/* from fn_80065D64.cpp: 20 of 52 words differ */
void fn_80066C48(void) {
    int i;
    for (i = 0; i < lbl_803CB770.n; i++) {
        Trap* t = At(&lbl_803CB770, i);
        switch (t->type) {
        case 6:
            fn_80116CFC(&lbl_803EC898, t->x, t->y, t->ext);
            break;
        case 9: {
            u8* c = lbl_803EC898.ter[0] + t->x + (t->y << 6);
            if (*c == 0) {
                c[0x3000] |= 2;
            }
            break;
        }
        }
    }
}

/* from fn_80065D64.cpp: 30 of 166 words differ */
Trap* fn_80066E24(TrapList* l, int x, int y, int mode) {
    u32 tbl[] = {8, 2, 4, 2};
    u32* p = tbl;
    int i;
    for (i = 0; i < 4; i++) {
        int dx = DirX(*p);
        int dy = DirY(*p);
        int tx = (s8)(x + dx);
        int ty = (s8)(y + dy);
        Trap* t = FindType(&lbl_803CB770, tx, ty, 0xB);
        if (t != 0) {
            tx += dx;
            ty += dy;
            if (lbl_803EC898.ter[0][(s8)tx + ((s8)ty << 6)] == 0) {
                if (mode) {
                    f32 h = fn_80113F00(&lbl_803EC898, (s8)x, (s8)y);
                    if (fn_80113F00(&lbl_803EC898, (s8)tx, (s8)ty) > h) {
                        goto next;
                    }
                } else {
                    f32 h = fn_80113F00(&lbl_803EC898, (s8)x, (s8)y);
                    if (fn_80113F00(&lbl_803EC898, (s8)tx, (s8)ty) < h) {
                        goto next;
                    }
                }
                return t;
            }
        }
    next:
        p++;
    }
    return 0;
}

/* from fn_80067168.cpp: 71 of 77 words differ */
void fn_8006758C(Unit* u) {
    Map* m = &lbl_803EC898;
    Inv* it = u->inv;
    s8 mn = 100;
    s8 mx = 0;
    int i = 0;
    int idx = u->x + (u->y << 6);
    u8 save = m->ter[0][idx];
    m->ter[0][idx] = 0;
    for (; i < 7; i++) {
        if (it == 0 || it->item == 0) {
            break;
        }
        if (fn_8012BA20(u, it->item)) {
            int a = RangeMin(it, u);
            int b = RangeMax(it, u);
            if (mn > a || b > mx) {
                if (a < mn) {
                    mn = a;
                }
                if (mx < b) {
                    mx = b;
                }
                fn_800673A0((s8)a, (s8)b);
            }
        }
        it++;
    }
    lbl_803EC898.ter[0][u->x + (u->y << 6)] = save;
}

/* from fn_80067168.cpp: 11 of 72 words differ */
void fn_8006746C(Unit* u) {
    int a;
    /*PERM*/
    Inv* it;
    s8 mn;
    s8 mx;
    int i;
    /*ENDPERM*/
    fn_80114B44(&lbl_803EC898, 6, -1);
    fn_80114B44(&lbl_803EC898, 9, 0);
    fn_80114888(&lbl_803EC898, 7);
    it = u->inv;
    mn = 100;
    mx = 0;
    for (i = 0; i < 7; i++) {
        if (it == 0 || it->item == 0) {
            break;
        }
        if (fn_8012BA20(u, it->item)) {
            int b;
            a = RangeMin(it, u);
            b = RangeMax(it, u);
            if (mn > a || b > mx) {
                if (a < mn) {
                    mn = a;
                }
                if (mx < b) {
                    mx = b;
                }
                fn_80115DEC(&lbl_803EC898, u->x, u->y, a, b);
            }
        }
        it++;
    }
}

/* from fn_800677E4.cpp: 2 of 99 words differ */
void fn_800679EC(Unit* u) {
    if (lbl_803CA870.f16) {
        fn_800453FC(&lbl_803CA870);
        u8 v = lbl_803CA870.f15;
        fn_80114B44(&lbl_803EC898, 9, 0);
        fn_80114888(&lbl_803EC898, 6);
        fn_801151BC(&lbl_803EC898, u);
        fn_8011567C(&lbl_803EC898, u->team);
        fn_80115764(&lbl_803EC898, u->x, u->y, v);
        fn_800310E4(fn_800D0864(lbl_803621D0), 0, 0x28, 0);
    } else {
        fn_80045120(&lbl_803CA870, u);
        ShowMove(u);
        fn_800310E4(fn_800D0864(lbl_803621D0 + 0xB), 0, 0x28, 0);
    }
    fn_8013F1C4();
}

/* from fn_800677E4.cpp: 4 of 64 words differ */
int fn_80067EE8(void) {
    int i;
    for (i = lbl_803CAB38[0x10] + 1; ChapterExists(i) && !ChapterOk(i); i++) {
    }
    fn_80061584(lbl_803CAB38, i);
    lbl_803CAB38[0x9C] = 4;
    return 1;
}

/* from fn_800677E4.cpp: 4 of 58 words differ */
u8 fn_80067FE8(int a) {
    int i;
    if (a > 0) {
        a--;
    }
    for (i = a; ChapterExists(i) && !ChapterOk(i); i--) {
    }
    return i;
}

/* from fn_800677E4.cpp: 65 of 231 words differ */
BOOL fn_80068638(const BattleBgmEnt* e, Unit* a, Unit* b) {
    /*PERM*/
    char* na;
    char* nb;
    char* s;
    int v;
    /*ENDPERM*/
    na = a->person->name;
    {
    nb = b->person->name;
    if (e->chap != 0 && fn_80291188(e->chap, *fn_8006074C(lbl_803CAB38)) != 0) {
        return 0;
    }
    s = e->n1;
    if (s != 0 && fn_80291188(s, na) != 0) {
        if (!e->either) {
            return 0;
        }
        if (fn_80291188(s, nb) != 0) {
            return 0;
        }
    }
    v = (s8)e->t1;
    if (v >= 0 && v != a->team[8]) {
        if (!e->either) {
            return 0;
        }
        if (v != b->team[8]) {
            return 0;
        }
    }
    v = (s8)e->s1;
    if (v >= 0 && v != a->fd) {
        if (!e->either) {
            return 0;
        }
        if (v != b->fd) {
            return 0;
        }
    }
    s = e->n2;
    if (s != 0 && fn_80291188(s, nb) != 0) {
        if (!e->either) {
            return 0;
        }
        if (fn_80291188(s, na) != 0) {
            return 0;
        }
    }
    v = (s8)e->t2;
    if (v >= 0 && v != b->team[8]) {
        if (!e->either) {
            return 0;
        }
        if (v != a->team[8]) {
            return 0;
        }
    }
    v = (s8)e->s2;
    if (v >= 0 && v != b->fd) {
        if (!e->either) {
            return 0;
        }
        if (v != a->fd) {
            return 0;
        }
    }
    s = e->flag;
    if (s != 0 && !flagExists((FlagTable*)lbl_803CAB38, s)) {
        return 0;
    }
    s = e->flag;
    if (s != 0 && (e->val != 0) != flagGet((FlagTable*)lbl_803CAB38, s)) {
        return 0;
    }
    return 1;
    }
}

/* from fn_80068EC4.cpp: 6 of 130 words differ */
void fn_80069220(MenuBase* m, Widget* w) {
    int n = w->n;
    if (n <= 10) {
        w->x = 400;
        w->w = 0x78;
        m->cols = n;
        m->rows = 1;
        ClampY(w);
    } else {
        int dx, dy, x0, y0;
        int ox, oy, px, r, k, c;
        m->cols = (n + 1) >> 1;
        m->rows = 2;
        int t = 400 - m->v58();
        w->x = t + 0x20;
        w->w = m->v58() + 0x78;
        y0 = m->cols * m->v5C();
        int hh = m->v4C();
        w->h = hh + y0;
        dx = m->v58();
        dy = m->v5C();
        x0 = m->v48();
        y0 = m->v4C();
        ClampY(w);
        dy = (s16)dy;
        x0 = (s16)x0;
        dx = (s16)dx;
        r = 0;
        k = 0;
        ox = 0;
        for (; r < m->rows && k < n; r++) {
            px = x0 + ox;
            c = 0;
            oy = 0;
            for (; c < m->cols && k < n; c++) {
                Widget* it = (Widget*)fn_80085EF8(w->ids[k]);
                it->x = px;
                int yy = y0 + oy;
                oy += dy;
                k++;
                it->y = yy;
            }
            ox += dx;
        }
    }
}

/* from fn_80068EC4.cpp: 79 of 259 words differ */
void fn_80069428(MenuBase* m, Widget* w) {
    u32 keys;
    int cols;
    int n;
    s16 row;
    s16 col;
    int rows;
    cols = m->cols;
    rows = m->rows;
    n = w->n;
    row = (s8)w->cur / cols;
    col = (s8)w->cur % cols;
    if (!Blocked()) {
        u32 trig;
        keys = lbl_804CB5B8->v3C();
        trig = lbl_804CB5B8->v48();
        w->prev = w->cur;
        if (rows > 1) {
            if (keys & 0x100001) {
                if (row == 0) {
                    if (keys == trig) {
                        w->cur += (rows - 1) * cols;
                        if ((s8)w->cur > n - 1) {
                            w->cur = n - 1;
                        }
                    }
                } else {
                    w->cur -= cols;
                }
            } else if (keys & 0x200002) {
                if (row == rows - 1) {
                    if (keys == trig) {
                        w->cur -= (rows - 1) * cols;
                    }
                } else {
                    w->cur += cols;
                    if ((s8)w->cur > n - 1) {
                        w->cur = n - 1;
                    }
                }
            }
        }
        if (keys & 0x800008) {
            if (col == 0) {
                if (keys == trig) {
                    w->cur += cols - 1;
                    if ((s8)w->cur > n - 1) {
                        w->cur = n - 1;
                    }
                }
            } else {
                w->cur--;
            }
        } else if (keys & 0x400004) {
            if (col == cols - 1) {
                if (keys == trig) {
                    w->cur -= cols - 1;
                }
            } else if ((s8)w->cur == n - 1) {
                if (keys == trig) {
                    w->cur -= col;
                }
            } else {
                w->cur++;
                if ((s8)w->cur > n - 1) {
                    w->cur = n - 1;
                }
            }
        }
        if ((s8)w->cur != (s8)w->prev) {
            Widget* it = (Widget*)fn_80085EF8(w->ids[(s8)w->prev]);
            it->obj->v48(w, it);
            it = (Widget*)fn_80085EF8(w->ids[(s8)w->cur]);
            it->obj->v44(w, it);
            if (fn_801A2224(lbl_8041EB20)) {
                it = (Widget*)fn_80085EF8(w->ids[(s8)w->cur]);
                f32 x = w->x + it->x;
                it = (Widget*)fn_80085EF8(w->ids[(s8)w->cur]);
                f32 y = w->y + it->y;
                void* p = ((Widget*)fn_80085EF8(w->ids[(s8)w->cur]))->obj->v10();
                if (p != 0) {
                    fn_801A1DCC(lbl_8041EB20, p, x, y);
                } else {
                    it = (Widget*)fn_80085EF8(w->ids[(s8)w->cur]);
                    fn_801A1F64(lbl_8041EB20, it->obj->v4C(it), x, y);
                }
            }
            if (m->v88()) {
                fn_80253EE4(m->v88(), 0.0f);
            }
        }
    }
}

/* from fn_80068EC4.cpp: 7 of 140 words differ */
void fn_80069CE4(MenuBase* m, Widget* w, int f) {
    f32 t = fn_800D58FC(w);
    int a = 0;
    w->x = a;
    w->y = a;
    int al = 255.0f * t;
    fn_8007E154();
    fn_8007E7DC(al);
    fn_8007E4E4(0.0f, 0.0f, m->v70(), 1.0f);
    fn_8007E164();
    fn_800720F4(((MenuUnit*)m)->unit, 16.0f * t + 16.0f, 0x23);
    fn_80069F14(m, w, ((MenuUnit*)m)->unit->team[8], 16.0f * t + 28.0f, 140.0f);
    if (w->s3A >= 5) {
        fn_8007E154();
        fn_8007E720(-0.1f);
        fn_8007E164();
        if (w->b2D == 0 && w->b2E == 0) {
            a = 1;
        }
        fn_80072ACC((s16)m->v50() / 2 + 0x2E, w->s3A + fn_800CB0FC(-1, 1.0f) / 2, (int)(f32)(s16)m->v50(), 0x18, 0x19, 0x4B, a);
        fn_8007E154();
        fn_8007E720(0.1f);
        fn_8007E164();
    }
    if (f != 0) {
        fn_8007309C(0, 312.0f, 282.0f);
        if (lbl_803C8E80 != 0) {
            void** p = fn_80030CF4(lbl_803C8E80);
            if (p != 0) {
                fn_800739A4(IdOf((u8*)*p), 500.0f, 200.0f);
            }
        }
    }
}

/* from fn_80068EC4.cpp: 5 of 133 words differ */
void fn_80069F14(MenuBase* m, Widget* w, int c, f32 x, f32 y) {
    f32 f;
    int i;
    int mx = 0;
    for (i = 0; i < w->n; i++) {
        Widget* it = (Widget*)fn_80085EF8(w->ids[i]);
        int r = it->b3B;
        if (r + 1 > mx) {
            mx = r + 1;
        }
        it->x = x + (f32)(s16)m->v48();
        f = r * (s16)m->v5C();
        f32 g = y + (f32)(s16)m->v4C();
        it->y = g + f;
    }
    u16 a = m->v50();
    u16 b = mx * m->v5C() + 0x18;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, m->v70(), 1.0f);
    fn_8007E164();
    fn_800718D0((int)x, (int)y, a, b, (u8)c, 0x9A);
}

/* from fn_80068EC4.cpp: 5 of 133 words differ */
void fn_8006A434(MenuBase* m, Widget* w, int c, f32 x, f32 y) {
    f32 f;
    int i;
    int mx = 0;
    for (i = 0; i < w->n; i++) {
        Widget* it = (Widget*)fn_80085EF8(w->ids[i]);
        int r = it->b3B;
        if (r + 1 > mx) {
            mx = r + 1;
        }
        it->x = x + (f32)(s16)m->v48();
        f = r * (s16)m->v5C();
        f32 g = y + (f32)(s16)m->v4C();
        it->y = g + f;
    }
    u16 a = m->v50();
    u16 b = mx * m->v5C() + 0x18;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, m->v70(), 1.0f);
    fn_8007E164();
    fn_800718D0((int)x, (int)y, a, b, (u8)c, 0x9A);
}

/* from fn_80068EC4.cpp: 22 of 71 words differ */
void fn_8006A834(MenuBase* m, Widget* w) {
    /*PERM*/
    u8* id;
    int n;
    int i;
    s16 sp;
    s16 px;
    int h;
    u8* id2;
    /*ENDPERM*/
    int k;
    m->cols = 0;
    for (i = 0; n = (s8)*(u8*)&w->n, i < n; i++) {
        id = &w->ids[i];
        Widget* it = (Widget*)fn_80085EF8(*id);
        s16 tw = fn_800CA3DC(((Widget*)fn_80085EF8(*id))->obj->v18(it), -1, 1.0f);
        if (tw >= m->cols) {
            m->cols = tw;
        }
    }
    sp = (s16)m->v50() / (n + 1);
    px = sp;
    h = m->v4C();
    for (k = 0; k < n; k++) {
        id2 = &w->ids[k];
        ((Widget*)fn_80085EF8(*id2))->x = px;
        ((Widget*)fn_80085EF8(*id2))->y = h;
        px += sp;
    }
}

/* from fn_8006AA70.cpp: 6 of 99 words differ */
void fn_8006AA70(MenuBase* m, Widget* w) {
    s16 x = ((Widget*)fn_80085EF8(w->ids[(s8)w->cur]))->x - (m->cols >> 1) - 0x10;
    s16 y = ((Widget*)fn_80085EF8(w->ids[(s8)w->cur]))->y;
    int h = (s16)m->v5C();
    y += (h - fn_800CB0FC(-1, 1.0f)) >> 1;
    if (w->s3A < 0) {
        w->s38 = x;
        w->s3A = y;
    } else {
        w->s38 = (w->s38 + x) / 2;
        w->s3A = (w->s3A + y) / 2;
    }
    fn_8007E154();
    fn_8007E720(-2.0f);
    fn_8007E164();
    int b = 0;
    if (w->b2D == 0 && w->b2E == 0) {
        b = 1;
    }
    fn_800712E8(w->s38, w->s3A, b);
    s16 ww = m->cols + 0x40;
    s16 hh = fn_800CB0FC(-1, 1.0f);
    fn_8007E154();
    fn_8007E720(2.9f);
    fn_8007E164();
    fn_80072ACC(w->s38 + (ww >> 1) - 0x10, w->s3A + (hh >> 1), ww, 0x18, 0x19, 0x4B, 1);
}

/* from fn_8006AA70.cpp: 16 of 133 words differ */
void fn_8006B528(MenuBase* m) {
    int l;
    m->v90();
    fn_80072944(0, 0);
    int len = strlen(m->v08()) + 1;
    char* buf = fn_800791B0(len * 2 - len);
    char* line = buf;
    strcpy(buf, m->v08());
    l = 0;
    f32 x = m->lines[0];
    f32 y = 32.0f;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    char* p = buf;
    char c;
    while ((c = *p) != 0) {
        if (c == 0xA) {
            *p = 0;
            DrawLine(x, y, line);
            l++;
            x = m->lines[(s16)l];
            y += fn_800CB0FC(-1, 1.0f) + 2;
            line = p + 1;
        }
        p++;
    }
    DrawLine(x, y, line);
    fn_80079474(buf);
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}

/* from fn_8006AA70.cpp: 14 of 87 words differ */
void fn_8006B870(MenuBase* m, Widget* w) {
    /*PERM*/
    s8 n;
    s16 tot;
    int i;
    s16 y;
    int x;
    /*ENDPERM*/
    m->rows = 0;
    n = w->n;
    tot = n * m->v5C();
    for (i = 0; i < w->n; i++) {
        s16 tw = fn_800CA3DC(((Widget*)fn_80085EF8(w->ids[i]))->obj->v0C(), -1, 1.0f);
        if (tw >= m->rows) {
            m->rows = tw;
        }
    }
    m->sC = ((s16)m->v50() - m->rows) >> 1;
    y = ((s16)m->v54() - tot) >> 1;
    m->sE = y;
    x = m->sC;
    for (i = 0; i < w->n; ) {
        u8* id = &w->ids[i];
        ((Widget*)fn_80085EF8(*id))->x = x;
        ((Widget*)fn_80085EF8(*id))->y = y;
        i++;
        y += (s16)m->v5C();
    }
}

/* from fn_8006AA70.cpp: 17 of 24 words differ */
void fn_8006BDCC(const char* a, const char* b) {
    MsgTab* g = &lbl_803CB7B8m;
    MsgEnt* e = g->e;
    MsgEnt** t = g->t;
    e[0].s = a;
    t[0] = &e[0];
    t[1] = &e[1];
    e[1].s = b;
    t[2] = 0;
    fn_800D5448b(g->o88, fn_8009E898(), 0);
}

/* from fn_8006AA70.cpp: 19 of 27 words differ */
void fn_8006BE30(const char* a, const char* b, const char* c) {
    MsgTab* g = &lbl_803CB7B8m;
    MsgEnt* e = g->e;
    MsgEnt** t = g->t;
    e[0].s = a;
    t[0] = &e[0];
    t[1] = &e[1];
    e[1].s = b;
    t[2] = &e[2];
    e[2].s = c;
    t[3] = 0;
    fn_800D5448b(g->o88, fn_8009E898(), 0);
}

/* from fn_8006AA70.cpp: 36 of 48 words differ */
void fn_8006BEA0(const char* a, const char* b, const char* c, u8 d, u8 f, u8 g2) {
    MsgTab* g = &lbl_803CB7B8m;
    MsgEnt* e = g->e;
    MsgEnt** t = g->t;
    e[0].s = a;
    t[0] = &e[0];
    t[1] = &e[1];
    e[1].s = b;
    t[2] = &e[2];
    e[2].s = c;
    t[3] = 0;
    Widget* w = fn_800D5448b(g->o88, fn_8009E898(), 0);
    if (w != 0) {
        ((Widget*)fn_80085EF8(w->ids[0]))->b39 = d;
        ((Widget*)fn_80085EF8(w->ids[1]))->b39 = f;
        ((Widget*)fn_80085EF8(w->ids[2]))->b39 = g2;
    }
}

/* from fn_8006AA70.cpp: 21 of 30 words differ */
void fn_8006BF64(const char* a, const char* b, const char* c, const char* d) {
    MsgTab* g = &lbl_803CB7B8m;
    MsgEnt* e = g->e;
    MsgEnt** t = g->t;
    e[0].s = a;
    t[0] = &e[0];
    t[1] = &e[1];
    e[1].s = b;
    t[2] = &e[2];
    e[2].s = c;
    t[3] = &e[3];
    e[3].s = d;
    t[4] = 0;
    fn_800D5448b(g->o98, fn_8009E898(), 0);
}

/* from fn_8006C2D0.cpp: 22 of 75 words differ */
void fn_8006D19C(BU* u, int gain, u8* log) {
    if (gain != 0) {
        gain += fn_80126B0C(u);
        lbl_803C8E80.flags |= 0x400;
        if ((u8)gain >= 100) {
            Job* j = u->u.job;
            gain = (u8)(gain - 100);
            u8 v = 0xFF;
            u8 q = ((u8*)j)[0xFA];
            if (q != 0) {
                v = q;
            }
            if (v != 0 && (s8)u->u.ugauge + 1 >= v) {
                u->u.flags10C |= 0x40000;
                lbl_803C8E80.flags |= 0x10;
            } else {
                u->u.ugauge++;
                fn_8002600C(log, 0x31, (s8)u->u.ugauge);
                fn_8006DCF0(u, log);
                lbl_803C8E80.flags |= 0x800;
            }
        }
        u->u.ff = gain;
        if (!fn_801204E8(u)) {
            u->u.ff = 0xFF;
        }
    }
}

/* from fn_8006C2D0.cpp: 6 of 83 words differ */
void fn_8006C794(Battle* b) {
    u8 e;
    if ((u8)fn_801204E8(&b->a)) {
        fn_8002600C(b->log, 0x2B, 0);
        u16 v = (*fn_80030CF4(&b->a))[8];
        e = fn_801207B4(&b->a, v / 20 + 10);
        e = CapExp(&b->a, e);
        ApplyExp(b, &b->a, e);
    }
}

/* from fn_8006C2D0.cpp: 156 of 219 words differ */
void fn_8006CE30(Battle* b, void* x) {
    s8 d9;
    s8 d6;
    s8 d5;
    s8 d4;
    s8 d3;
    s8 d2;
    s8 d1;
    s8 d8;
    s8 d7;
    s8 d10;
    u8* log;
    fn_80026C44(b, x, x);
    if (lbl_803C8DA0.a1) {
        b->flags |= 0x4000;
        lbl_803C8DA0.a1 = 0;
    }
    fn_8011FFD0(&b->b);
    b->flags |= 0x2000;
    fn_8002ED4C(&b->a, 0, -1);
    fn_8002ED4C(&b->b, 0, -1);
    d1 = fn_80122720(&b->b) - fn_80122720(&b->a);
    d2 = fn_80122770(&b->b) - fn_80122770(&b->a);
    d3 = fn_80122880(&b->b) - fn_80122880(&b->a);
    d4 = fn_80122990(&b->b) - fn_80122990(&b->a);
    d5 = fn_80122AA0(&b->b) - fn_80122AA0(&b->a);
    d6 = fn_80122BB0(&b->b) - fn_80122BB0(&b->a);
    d7 = fn_80122C20(&b->b) - fn_80122C20(&b->a);
    d8 = fn_80122D30(&b->b) - fn_80122D30(&b->a);
    d9 = fn_8012408C(&b->b) - fn_8012408C(&b->a);
    d10 = fn_8012401C(&b->b) - fn_8012401C(&b->a);
    log = b->log;
    fn_8002600C(log, 0x32, d1);
    fn_8002600C(log, 0x33, d2);
    fn_8002600C(log, 0x34, d3);
    fn_8002600C(log, 0x35, d4);
    fn_8002600C(log, 0x36, d5);
    fn_8002600C(log, 0x37, d6);
    fn_8002600C(log, 0x38, d7);
    fn_8002600C(log, 0x39, d8);
    fn_8002600C(log, 0x3A, d9);
    fn_8002600C(log, 0x3B, d10);
    fn_8002CEB0(b);
    BattleLog* g = &lbl_803C8DA0;
    g->a1 = 0;
    g->a2 = 0;
    g->a3 = 0;
    g->a4 = 0;
    g->a0 = 0;
    int i;
    for (i = 0; i < 0x20; i++) {
        g->x[i] = 0;
        g->a[i] = 0;
        g->b[i] = 12345;
    }
    lbl_803C8DA0.a5 = -1;
    lbl_803C8DA0.a6 = 0;
    lbl_803C8DA0.c8 = 0;
    lbl_803C8DA0.cc = 0;
}

/* from fn_8006C2D0.cpp: 24 of 260 words differ */
void fn_8006D380(BU* u, u8* d) {
    d[7] = 0;
    d[6] = 0;
    d[5] = 0;
    d[4] = 0;
    d[3] = 0;
    d[2] = 0;
    d[1] = 0;
    d[0] = 0;
    Grow t = GrowOf(u);
    u8 a0 = t.v[0];
    u8 a1 = t.v[1];
    u8 a2 = t.v[2];
    u8 a3 = t.v[3];
    u8 a4 = t.v[4];
    u8 a5 = t.v[5];
    u8 a6 = t.v[6];
    u8 a7 = t.v[7];
    int bonus = fn_8011B77C(u->u.skills, lbl_804CA6C8);
    s8 best = -0x80;
    s8 idx = -1;
    int any = 0;
    int i;
    for (i = 0; i < 8; i++) {
        int room = (s16)fn_80122F14(u, i) - (s16)fn_80122E8C(u, i);
        if (room > 0) {
            int inc = fn_8006D2C8(PICK, bonus);
            if ((s8)inc > room) {
                inc = (s8)room;
            }
            SetD(d, i, inc);
            any = (any | ((s8)GetD(d, i) > 0)) != 0;
            if (best < PICK) {
                best = PICK;
                idx = i;
            }
        }
    }
    if (idx >= 0 && !any) {
        SetD(d, idx, 1);
    }
}

/* from fn_80075AC0.cpp: 7 of 131 words differ */
void fn_80076D48(const char* name, void* data) {
    /*PERM*/
    u32 h;
    Lock* l;
    Node** b;
    Node* q;
    /*ENDPERM*/
    const char* p;
    HK hk;
    h = 0;
    hk.g = 0;
    p = name;
    while (*p) {
        h = *p + h * 37;
        hk.g = *p + hk.g * 31;
        p++;
    }
    l = LOCK;
    l->lock();
    b = &lbl_803CB870.b[h % 0x7EB];
    q = *b;
    if (q == 0) {
        *b = NewNode(name, data);
    } else {
        Node* t = 0;
        while (q != 0) {
            t = q;
            q = q->next;
        }
        t->next = NewNode(name, data);
    }
    l->unlock();
}

/* from fn_80075AC0.cpp: 5 of 52 words differ */
void fn_80075AC0(Hdr* h) {
    u32* keys = Keys(h);
    char* strs;
    Sym* s = (Sym*)(keys + h->nKey);
    strs = (char*)(s + h->nSym) + h->nC * 8;
    if (h->reg) {
        u32 i = 0;
        if (h->nSym != 0 && h->nSym != 0)
        for (; i < h->nSym; i++) {
            u32* k = keys;
            const char* name = strs + s->off;
            u32 j;
            for (j = 0; j < h->nKey; j++) {
                if (s->key == *k) {
                    break;
                }
                k++;
            }
            fn_80077174(name);
            s++;
        }
        h->reg = 0;
    }
}

/* from fn_80075AC0.cpp: 10 of 150 words differ */
const char* fn_800769D0(Hdr* h, int idx) {
    h = GetHdr(h);
    u32 n = h->nKey;
    u32* k = Keys(h);
    Sym* tab = (Sym*)(k + n);
    Sym* e = &tab[idx];
    const char* name = (char*)(tab + h->nSym) + h->nC * 8 + e->off;
    u32 j;
    for (j = 0; j < n; j++) {
        if (e->key == *k) {
            return name;
        }
        k++;
    }
    return name;
}
