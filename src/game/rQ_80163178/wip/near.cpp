/* Attempts that compile but do not match yet. Not compiled by anything; helpers and prototypes are in the file named in each "from" comment. */

/* from fn_80163178.cpp */
Inv* fn_801633C0(Unit* u, Inv* a, Inv* b) {
    s8 va = ItemVal(u, a);
    s8 vb = ItemVal(u, b);
    if (va != vb) {
        s32 miss;
        int hp;
        if (va > vb) {
            Inv* t = a;
            s8 t2 = vb;
            a = b;
            b = t;
            vb = va;
            va = t2;
        }
        hp = u->hp;
        miss = fn_801237EC(u) - hp;
        if (fn_8028DB44(miss - va) > fn_8028DB44(miss - vb)) {
            return b;
        }
        return a;
    } else {
        if (a->uses < b->uses) {
            return a;
        }
        if (a->uses > b->uses) {
            return b;
        }
        return a;
    }
}

u32 fn_801635B8(Unit* u, int a) {
    Inv* best = 0;
    Inv* p;
    Inv* base = u->inv;
    int i;
    for (p = base, i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8012BC2C(u, p->item) && p->item[0x12] == 0xE && p->item[0x14] == 0x81) {
            best = !best ? p : fn_801633C0(u, best, p);
        }
    }
    if (best) {
        int idx = InvIdx(base, best);
        s16 x, y;
        x = u->x;
        y = u->y;
        if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
            fn_8016DF74(u, a, &x, &y);
        }
        fn_80160610(4, (s8)x, (s8)y, u, (s8)x, (s8)y, idx, 0, 0);
        u->h3BE = ItemVal(u, best);
    }
    return best != 0;
}

u8 fn_80163808(Unit* u, int a) {
    Map* m = &lbl_803EC898;
    Unit* tu;
    Inv* best;
    int n;
    int bi;
    if (fn_80129A8C(u) < 0) {
        return 0;
    }
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    {
        Filt f(lbl_80387328, u);
        fn_8016CB18(u, &f);
    }
    tu = 0;
    best = 0;
    for (n = 0; n < lbl_803E7320->n; n++) {
        Unit* v;
        Inv* p;
        int i;
        fn_800CFD18(lbl_803E7320, n);
        v = fn_800CFB0C();
        p = v->inv;
        for (i = 0; i < 7; i++, p++) {
            if (!p || !p->item) break;
            if (fn_8012BC2C(u, p->item)) {
                if (ItemB(p->item, 0x12) == 0xE && ItemB(p->item, 0x14) == 0x81) {
                    if (!best) {
                        best = p;
                        tu = v;
                        bi = i;
                    } else {
                        Inv* r = fn_801633C0(u, p, best);
                        if (r != best) {
                            best = r;
                            tu = v;
                            bi = i;
                        }
                    }
                }
            }
        }
    }
    if (tu) {
        Filt g(lbl_80387338, u);
        s16 x, y;
        fn_80169B20(u, a, tu->x, tu->y, &g, &x, &y);
        fn_80160610(0x35, (s8)x, (s8)y, tu, (s8)x, (s8)y, (s8)bi, 0, 0);
        u->h3BE = ItemVal(u, best);
    }
    return lbl_804183F0.done;
}

/* from fn_8016D070.cpp */
void fn_80172494(Unit* u, int x, int y) {
    struct G { void* vt; Unit* u; };
    G f;
    G* pf = &f;
    f.vt = lbl_803877B0;
    fn_800CFB34(lbl_803E7320);
    pf->u = u;
    if (y < 0) {
        y = u->y;
    }
    if (x < 0) {
        x = u->x;
    }
    fn_800392FC(pf, (s8)x, (s8)y);
}

int fn_80170664(Unit* u, Unit* v, Inv* p) {
    int dy = fn_8028DB44(u->y - v->y);
    int d = fn_8028DB44(u->x - v->x) + dy;
    int r = p->item ? fn_801107C0(p->item, u) : 0;
    int b = fn_8012408C(v);
    return d <= r + (fn_8012408C(u) + b);
}

/* from fn_80165B48.cpp */
void fn_801662AC(int x, int y, u8* s, int k, u16 v) {
    Map* m = &lbl_803EC898;
    fn_80114888(m, k);
    m->cur[(s8)x + (s8)y * 0x40] = v;
    for (; *s; s++) {
        BOOL out;
        switch (*s) {
        case '4': x--; break;
        case '6': x++; break;
        case '8': y--; break;
        case '2': y++; break;
        }
        out = 0;
        if (x < m->x0 || m->x1 - 1 < x || y < m->y0 || m->y1 - 1 < y) {
            out = 1;
        }
        if (!out) {
            m->cur[(s8)x + (s8)y * 0x40] = v;
        }
    }
}

int fn_80167F5C(Unit* u) {
    int d = fn_801676D8(u->x, u->y) >> 4;
    int s;
    s8 v = fn_8012408C(u);
    s = -(v + d);
    if (fn_8011B77C(u->skills, lbl_804CA5C4)) {
        s += 0x78;
    } else if (fn_8011B77C(u->skills, lbl_804CA5C0)) {
        s += 0x50;
    } else {
        s += fn_80167E94(u);
    }
    if (u->b117) {
        s += u->b117 << 16;
        if (u == fn_80127CA0(u)) {
            s -= 0x4000;
        }
        s += (((s8*)u)[0x3A8] + 0x80) << 8;
    } else {
        s += (((s8*)u)[0x3A8] + 0x80) << 16;
    }
    return *(s < lbl_804CA7B0 ? &lbl_804CA7B0 : &s);
}

void fn_801689C8(f32* p) {
    BOOL b = 1;
    if (lbl_804CB830 != 1 && lbl_804CB830 != 2) {
        b = 0;
    }
    if (b && lbl_803CAB38[0x11] == 1 && lbl_803EC898.ter[2][lbl_803CA870.x + lbl_803CA870.y * 0x40] == 0) {
        return;
    }
    fn_801030B8(lbl_803CA870.unit, (int)p[12], (int)p[13], 0x10, 0);
}

void fn_80168A90(f32* p) {
    BOOL b = 1;
    if (lbl_804CB830 != 1 && lbl_804CB830 != 2) {
        b = 0;
    }
    if (b && lbl_803CAB38[0x11] == 1 && lbl_803EC898.ter[2][(s8)(int)p[12] + (s8)(int)p[13] * 0x40] == 0) {
        fn_80083DC4(p, 99);
        return;
    }
    fn_800620A8(lbl_803CAB38, p[12], p[13]);
}

BOOL fn_80169B20(Unit* u, u16 lim, s16 x, s16 y, Filter* f, s16* ox, s16* oy) {
    s16* d = lbl_8036B218;
    Map* m = &lbl_803EC898;
    s16 px, py;
    int best = 0x80000000;
    int i;
    for (i = 0; i < 4; i++, d += 2) {
        py = y + d[1];
        px = x + d[0];
        int idx = (s8)px + (s8)py * 0x40;
        if ((s16)m->cur[idx] >= 0 && m->b5[idx] == 0) {
            if ((m->ter[0][idx] == 0 || m->ter[0][idx] == u->tid) && f->at(0, px, py) && fn_801676D8((s8)px, (s8)py) <= lim) {
                int s = fn_8015804C(u, px, py);
                if (s > best) {
                    *ox = px;
                    *oy = py;
                    best = s;
                }
            }
        }
    }
    return best != 0x80000000;
}

int fn_80168098(void) {
    Unit* nx;
    int n = 0;
    Unit* v;
    int off = 0;
    for (v = lbl_804CB814[lbl_803CAB38[0x11]].head; v; v = nx) {
        nx = v->next;
        if (!MapOutU(&lbl_803EC898, v) && !fn_8010931C((u8*)v + 0x110) && !(v->flags10C & 0x9D) && (!fn_8016D0B0(v) || fn_80106E30(v->ai))) {
            *(int*)((u8*)v + 0x3AC) = fn_80167F5C(v);
            n++;
            ((AiCfg*)((u8*)&lbl_804183F0 + off))->order[0] = v;
            off += 4;
        }
    }
    return n;
}

void fn_80167E08(void) {
    AiCfg* c = &lbl_804183F0;
    int n;
    Unit** b;
    fn_80167704(&lbl_804CB814[lbl_803CAB38[0x11]]);
    n = fn_80168098();
    b = c->order;
    fn_801681E0(b, b + n, fn_801681C4);
    c->order[n] = 0;
    c->cursor = c->order;
}

/* from fn_80170F50.cpp */
void fn_801689C8(f32* p) {
    BOOL b = 1;
    Unit* a = lbl_803CA870.unit;
    u8 mode = lbl_804CB830;
    if (mode != 1 && mode != 2) {
        b = 0;
    }
    if (b && lbl_803CAB38[0x11] == 1 && lbl_803EC898.ter[2][lbl_803CA870.x + lbl_803CA870.y * 0x40] == 0) {
        return;
    }
    fn_801030B8(a, (int)p[12], (int)p[13], 0x10, 0);
}

void fn_80168BF0(u8* p) {
    p[0x34] = 1;
    {
        BOOL b = 1;
        u8 mode = lbl_804CB830;
        if (mode != 1 && mode != 2) {
            b = 0;
        }
        if (b && lbl_803CAB38[0x11] == 1) {
            if (lbl_803EC898.ter[2][lbl_803CA870.x0 + lbl_803CA870.y0 * 0x40] == 0 && lbl_803EC898.ter[2][lbl_803CA870.x + lbl_803CA870.y * 0x40] == 0) {
                p[0x34] = 0;
                if (lbl_803CA870.action == 0x26) {
                    fn_800620A8(lbl_803CAB38, lbl_803CA870.x0, lbl_803CA870.y0);
                }
            } else {
                fn_800620A8(lbl_803CAB38, lbl_803CA870.x0, lbl_803CA870.y0);
            }
        } else {
            fn_800620A8(lbl_803CAB38, lbl_803CA870.x0, lbl_803CA870.y0);
        }
    }
}

void fn_80171188(Unit* u) {
    Inv* p;
    Inv* base;
    int i;
    u->w3B4 &= 0xFAFFC02B;
    fn_80163178(u);
    base = u->inv;
    p = base;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8012BB48(u, p->item)) {
            u8* it = p->item;
            if ((u8)(it ? it[0x14] : 0x13) == 0x81 || (u8)(it ? it[0x14] : 0x13) == 0x82) {
                u->w3B4 |= 4;
            }
        }
    }
    i = 0;
    p = base;
    while (i < 7) {
        if (!p || !p->item) break;
        if (fn_8012BB48(u, p->item) && (u8)(p->item ? p->item[0x14] : 0x13) == 0x86) {
            u->w3B4 |= 0x10;
        }
        i++;
        p++;
    }
    if (fn_8011B77C(u->skills, lbl_804CA5C4)) {
        u->w3B4 |= 0x2000;
    }
    for (i = 0; i < 7; i++, base++) {
        if (!base || !base->item) break;
        if (fn_8012BA20(u, base->item) && (*(u32*)(fn_801116B8(base) + 4) & 2)) {
            u->w3B4 |= 0x40;
            break;
        }
    }
    fn_80170D64(u);
    fn_80170E60(u);
    if (fn_80109348((u8*)u + 0x110)) {
        u->w3B4 |= 0x1000000;
    }
}

/* from fn_80174C2C.cpp */
u8 fn_8016CDEC(Unit* u, void* f) {
    int m = 0x7FFFFFFF;
    int r;
    Unit* t;
    int n;
    s8 slot;
    if (!fn_8011B77C(u->skills, lbl_804CA5C0)) {
        return 0;
    }
    {
        F3 g(lbl_80387790, u, f);
        fn_800CFB34(lbl_803E7320);
        fn_800398E0(&g, 0);
    }
    for (n = 0; n < lbl_803E7320->n; n++) {
        Unit* v;
        fn_800CFD18(lbl_803E7320, n);
        v = fn_800CFB0C();
        if (fn_8011EFC8(u, v)) {
            s8 s = fn_8016CC18(u, v, &r);
            if (s >= 0 && r < m) {
                t = v;
                m = r;
                slot = s;
            }
        }
    }
    if (m != 0x7FFFFFFF) {
        s8 tx = t->x;
        s8 ty = t->y;
        Filt g;
        s16 x, y;
        g.u = u;
        g.vt = lbl_80387338;
        fn_80169B20(u, fn_8016D11C(u), tx, ty, &g, &x, &y);
        *(s16*)((u8*)u + 0x3B8) += 1;
        fn_80160610(0x11, (s8)x, (s8)y, t, tx, ty, slot, 0, 0);
    }
    return lbl_804183F0.done;
}

void fn_8016CF78(FF* f, s8 x, s8 y) {
    int i = x + y * 0x40;
    Map* m = &lbl_803EC898;
    if (m->b5S[i]) {
        return;
    }
    if ((f->u->w3B4 & 0x20000) && (m->ter[3][i] & 2)) {
        return;
    }
    f->x = x;
    f->y = y;
    if (m->ter[0][i] == 0 || f->u->tid == m->ter[0][i]) {
        fn_800392FC(f, x, y);
    }
}

void fn_8017293C(FF* f, s8 x, s8 y) {
    int i = x + y * 0x40;
    Map* m = &lbl_803EC898;
    if (m->b5S[i]) {
        return;
    }
    if ((f->u->w3B4 & 0x20000) && (m->ter[3][i] & 2)) {
        return;
    }
    f->x = x;
    f->y = y;
    if (m->ter[0][i] == 0 || f->u->tid == m->ter[0][i]) {
        fn_800392FC(f, x, y);
    }
}

u8 fn_80164330(Unit* u, u16 item) {
    if (!(lbl_804183F0.flags & 2) && !(u->w3B4 & 0x7000000)) {
        int m = 0x7FFFFFFF;
        u16 best = 0xFF;
        int y;
        int bx, by;
        fn_80165F94(u, 6, lbl_803EC898.w * lbl_803EC898.h);
        for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
            int x;
            for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
                int i = (s8)x + (s8)y * 0x40;
                if ((s16)lbl_803EC898.cost[i] >= 0 && lbl_803EC898.b5[i] == 0 && !fn_801658E4(0, (s8)x, (s8)y)) {
                    Unit* v = UnitGet(lbl_803EC898.ter[0][i]);
                    if (v && u != v && !SameT(u, v, 1)) {
                        Inv* p = v->inv;
                        int k = -1;
                        int j;
                        for (j = 0; j < 7; j++, p++) {
                            if (!p || !p->item) break;
                            if (!(*(u32*)(fn_801116B8(p) + 4) & 0x20) && (u8)(p->item ? p->item[0x12] : 0x13) == 0xE && (u8)(p->item ? p->item[0x14] : 0x13) == 0x81) {
                                k = j;
                                break;
                            }
                        }
                        if ((s8)k >= 0) {
                            Filt g;
                            int c;
                            g.u = u;
                            g.vt = lbl_80387308;
                            c = fn_80171378((s16)x, (s16)y, &g);
                            if (c <= m && (s16)lbl_803EC898.cur[i] < (s16)best) {
                                best = lbl_803EC898.cur[i] & 0xFF;
                                bx = (s16)x;
                                by = (s16)y;
                                m = c;
                            }
                        }
                    }
                }
            }
        }
        if (m != 0x7FFFFFFF && lbl_803EC898.ter[0][(s8)bx + (s8)by * 0x40] != u->tid) {
            fn_8016F94C(u, bx, by, 1, item, 0, 0, -1);
        }
        return lbl_804183F0.done;
    }
    return 0;
}

u8 fn_80172E70(void) {
    //E70
    AiAct* act = &lbl_803CA870;
    bool x = IsNz(SideOn(0, 0x14));
    u8 tbl[0xB];
    int m;
    Unit* best;
    Unit* v;
    bool y;
    int id;
    Filt a1;
    Filt c1;
    Filt a;
    Filt c;
    Filt b1;
    Filt b;
    x = x | SideOn(3, 0x17);
    x = x | SideOn(1, 0x15);
    x = x | SideOn(2, 0x16);
    m = 0x80000000;
    best = 0;
    fn_8010E41C(tbl, 0);
    y = !x;
    for (id = 1; id <= 0xFE; id++) {
        v = UnitGet(id);
        if (v->person) {
            if (tbl[v->team[8]] && !(v->flags10C & 0x9D)) {
                v->m3D0[0] = 0x40;
                v->b3BC = 0;
                fn_80163010(&lbl_804183F0, v);
                lbl_804183F0.done = 0;
                memset(lbl_804183F0.res, 0, 0x14);
                fn_80045120(act, v);
                fn_80166720(v);
                {
                    Filt* s;
                    a1.u = v;
                    a1.vt = lbl_80387308;
                    c1.u = v;
                    c1.vt = lbl_803872F8;
                    s = &c1;
                    if (y) {
                        s = &a1;
                    }
                    b1.vt = lbl_80387338;
                    b1.u = v;
                    if (fn_80152C20(s, &b1, 0xF) && (v->b3BC & 2) && v->h3BE > m) {
                        m = v->h3BE;
                        best = v;
                    }
                }
                lbl_804183F0.done = 0;
                fn_80045548(act);
            }
        }
    }
    if (best) {
        Filt* s;
        best->m3D0[0] = 0x40;
        best->b3BC = 0;
        fn_80163010(&lbl_804183F0, best);
        lbl_804183F0.done = 0;
        memset(lbl_804183F0.res, 0, 0x14);
        fn_80045120(act, best);
        fn_80166720(best);
        a.u = best;
        a.vt = lbl_80387308;
        c.u = best;
        c.vt = lbl_803872F8;
        s = &c;
        if (y) {
            s = &a;
        }
        b.vt = lbl_80387338;
        b.u = best;
        fn_80152C20(s, &b, 0xF);
    }
    return lbl_804183F0.done;
}

BOOL fn_8016EDE8(Filter* f, Unit* u, s16* ox, s16* oy) {
    s16 best = 0x7FFF;
    s16 bx, by;
    int y;
    fn_80165E18(u, 6, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        int x;
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(0, (s8)x, (s8)y) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]) {
                Unit* v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                if (f->check(v) && fn_8011EFC8(u, v)) {
                    if (HasW(u, v) && lbl_803EC898.costS[(s8)x + (s8)y * 0x40] < best) {
                        bx = x;
                        by = y;
                        best = lbl_803EC898.costS[(s8)x + (s8)y * 0x40];
                    }
                }
            }
        }
    }
    if (best != 0x7FFF) {
        *ox = bx;
        *oy = by;
        return 1;
    }
    return 0;
}

/* from fn_801658E4.cpp */
void fn_801729C0(FF* f, Unit* v) {
    if (f->f->check(v) && fn_8011EE3C(f->u, v)) {
        s8 vx = v->x;
        s8 vy = v->y;
        s8 tx = vx * 2 - f->x;
        s8 ty = vy * 2 - f->y;
        int i;
        fn_801151BC(&lbl_803EC898, v);
        i = tx + ty * 0x40;
        if (lbl_803EC898.ter[0][i] == 0 && !(lbl_803EC898.ter[3][i] & 1) && fn_80115CD8(&lbl_803EC898, tx, ty) <= 0x7530) {
            if (fn_80116DB8(&lbl_803EC898, vx, vy, tx, ty) && lbl_803EC898.b5[i] == 0 && !fn_80066130(lbl_803CB770, tx, ty, 0xC)) {
                fn_800CFC50(lbl_803E7320, f->x, f->y, v->tid, 0);
            }
        }
    }
}

void fn_80175C3C(Tm* t) {
    if (1140.0f <= (f32)++t->a || (lbl_804CB5B8->v48() & 0xFFF0)) {
        t->a = 0;
        fn_80083B78(t);
    } else if (300.0f <= (f32)++t->b) {
        t->b = 0;
        t->c = t->d == 0;
        t->f = t->e;
    }
}

/* from fn_8016A9BC.cpp */
BOOL fn_8016D27C(Unit* u, u32 fl, u32 k, s16* ox, s16* oy) {
    s16 best = 0x7FFF;
    s16 r = 0x7FFF;
    s16 bx, by;
    int y;
    fn_80165E18(u, 7, lbl_803EC898.w * lbl_803EC898.h);
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        int x;
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y) && (!(fl & 1) || lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40] == 0)) {
                if ((fl & 2) && lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]) {
                    Unit* v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                    if (SameT(u, v, 1)) continue;
                }
                if (fl & 4) {
                    Filt g;
                    int n = 0;
                    s16* d;
                    g.u = u;
                    g.vt = lbl_80387308;
                    for (d = lbl_8036B278; *d != 0x7FFF; d += 2) {
                        int px = (s16)x + d[0];
                        int py = (s16)y + d[1];
                        BOOL o = 0;
                        if (px < lbl_803EC898.x0 || lbl_803EC898.x1 - 1 < px || py < lbl_803EC898.y0 || lbl_803EC898.y1 - 1 < py) {
                            o = 1;
                        }
                        if (!o && lbl_803EC898.ter[0][(s8)px + (s8)py * 0x40] && ((Filter*)&g)->check(UnitGet(lbl_803EC898.ter[0][(s8)px + (s8)py * 0x40]))) {
                            n++;
                        }
                    }
                    if (n) continue;
                }
                {
                    Ar a;
                    a.vt = lbl_80387800;
                    fn_800CFB34(lbl_803E7320);
                    a.k = k;
                    fn_80039708(&a, (s8)x, (s8)y);
                    if (lbl_803E7320->n && lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40] < best) {
                        bx = x;
                        by = y;
                        best = lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40];
                        r = best;
                    }
                }
            }
        }
    }
    if (r != 0x7FFF) {
        Ar a;
        a.vt = lbl_80387800;
        fn_800CFB34(lbl_803E7320);
        a.k = k;
        fn_80039708(&a, (s8)bx, (s8)by);
        *ox = bx;
        *oy = by;
    } else {
        fn_800CFB34(lbl_803E7320);
    }
    return r != 0x7FFF;
}

u8 fn_80164064(Unit* u, u32 lim) {
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        return 0;
    } else {
        int m = 0x7FFFFFFF;
        u16 best = 0xFF;
        int bx, by;
        int y;
        fn_80165F94(u, 6, lbl_803EC898.w * lbl_803EC898.h);
        for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
            int x;
            for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
                if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y) && fn_801676D8((s8)x, (s8)y) <= lim) {
                    if (((u8**)fn_801181E8(&lbl_803EC898, (s8)x, (s8)y))[2][6]) {
                        Unit* v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                        if (v) {
                            if (SameT(u, v, 1) || ((v->w3B4 & 0x7000000) && !(v->w3B4 & 4))) {
                                continue;
                            }
                        }
                    } else {
                        Unit* v = UnitGet(lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40]);
                        if (!v || SameT(u, v, 1) || !(v->w3B4 & 4)) {
                            continue;
                        }
                    }
                    {
                        Filt g;
                        int c;
                        g.u = u;
                        g.vt = lbl_80387308;
                        c = fn_80171378((s16)x, (s16)y, &g);
                        if (c <= m && (s16)lbl_803EC898.cur[(s8)x + (s8)y * 0x40] < (s16)best) {
                            best = lbl_803EC898.cur[(s8)x + (s8)y * 0x40] & 0xFF;
                            bx = (s16)x;
                            by = (s16)y;
                            m = c;
                        }
                    }
                }
            }
        }
        if (m != 0x7FFFFFFF && lbl_803EC898.ter[0][(s8)bx + (s8)by * 0x40] != u->tid) {
            fn_8016F94C(u, bx, by, 1, 0xFFFF, 0, 0, -1);
        }
        return lbl_804183F0.done;
    }
}

BOOL fn_8016A280(Unit* u, Unit* t, Inv* p, Filter* f, s16* ox, s16* oy) {
    int best;
    int y;
    {
        u8 a = p->item ? fn_80110880(p->item, u) : 0;
        u8 b = p->item ? fn_801107B8(p->item, u) : 0;
        fn_801663E0(t->x, t->y, b, a, 7);
    }
    best = 0x80000000;
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        int x;
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (lbl_803EC898.costS[(s8)x + (s8)y * 0x40] >= 0 && lbl_803EC898.b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y) && lbl_803EC898.g4[(s8)x + (s8)y * 0x40] == 0 &&
                (lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40] == 0 || lbl_803EC898.ter[0][(s8)x + (s8)y * 0x40] == u->tid)) {
                if (f->at((int)t, (s16)x, (s16)y) && fn_8016D11C(u) >= fn_801676D8((s8)x, (s8)y)) {
                    int s = fn_8015814C(u, x, y, 0);
                    s += fn_80158208(u, x, y, 0);
                    s -= (fn_801676D8((s8)x, (s8)y) >> 4);
                    s -= lbl_803EC898.cost2S[(s8)x + (s8)y * 0x40];
                    if (s > best) {
                        *ox = x;
                        *oy = y;
                        best = s;
                    }
                }
            }
        }
    }
    return best != 0x80000000;
}
