/* Attempts that do not match yet. Not compiled by anything: each block needs the externs of the file named in its comment. */
/* fn_8002742C: 57 of 83 words differ (from fn_80026950.cpp) */
void fn_8002742C(Battle* b, int a) {
    fn_800282A0(b, &b->a, &b->b, 0);
    fn_800275C4(b, a, 1);
    b->f15e4 = 0;
    fn_800282A0(b, &b->a, &b->b, 0);
    fn_80127868(&b->a);
    fn_801278B8(&b->a);
    fn_80127868(&b->b);
    fn_801278B8(&b->b);
    if (fn_8011B77C(b->b.u.x12c, lbl_804CA698)) {
        if (fn_80030CBC(&b->b)->data) {
            if (rollP(fn_80123AC4(&b->b)) == 0) {
                fn_80026324(b->log, 0x3e, 0x9b, 0);
                fn_8011B430(b->b.u.x12c, lbl_804CA698);
                fn_8011A36C(b->b.u.x12c);
            } else {
                fn_80026324(b->log, 0x3e, 0x3f, 0);
            }
        }
    }
    fn_8002600C(b->log, 0x72, 0);
}

/* fn_80026C44: 19 of 37 words differ (from fn_80026950.cpp) */
void fn_80026C44(Battle* bt, Unit* a, Unit* d) {
    Spec sa = {a, a->x102, a->y103, -1, 0, 0, 1};
    Spec sd = {d, d->x102, d->y103, -1, 0, 0, 1};
    fn_800269E4(bt, &sa, &sd);
}

/* fn_80026EE8: 54 of 104 words differ (from fn_80026950.cpp) */
void fn_80026EE8(Battle* b, Unit* u, Pos* p) {
    int x, y;
    fn_8002E3D4(&b->a);
    fn_8002E3D4(&b->b);
    fn_8002E3D4(&b->c);
    fn_80025FE0(b->log);
    b->f15e8 = 0;
    b->f15ec = 0;
    b->f15f0 = 0;
    b->f15f4 = 0;
    b->f15f8 = 0;
    b->f15fc = -1;
    b->f1604 = 0;
    fn_8002E6FC(b, u);
    fn_8002E738(&b->b);
    b->b.u.u3f0 = 0;
    fn_80114888(lbl_803EC898, 7);
    fn_80116098(lbl_803EC898, b->a.u.x102, (s8)*(u8*)&b->a.u.y103, 100, 0x28);
    y = p->y;
    x = p->x;
    b->f15e8 = (*(s16**)(lbl_803EC898 + 0x15190))[x + (y << 6)];
    *((u8*)&b->b + 0x119) = p->f5;
    fn_80126D9C(&b->b, p->f4);
    b->b.u.f8 = 0;
    fn_80126EB0(&b->b, p->x, (s8)*(u8*)&p->y);
    b->f15ec |= 0x101;
    fn_8002ED4C(b, b->f15e8, -1);
    fn_8002F14C(b);
    switch (fn_80118130(lbl_803EC898, x, y)) {
    case 0xb6:
        b->f15ec |= 0x80000;
        break;
    case 0xb1:
        b->f15ec |= 0x100000;
        break;
    case 0x71:
        b->f15ec |= 0x180000;
        break;
    }
}

/* fn_8002D218: 37 of 76 words differ (from fn_80026950.cpp) */
int fn_8002D218(Unit** t, Unit* p) {
    int c[3];
    s8 x = p->x102;
    s8 y = p->y103;
    Unit** q = t;
    int* o = c;
    int i;
    for (i = 0; i < 3; i++, q++, o++) {
        s8 ay = (*q)->y103;
        s8 ax = (*q)->x102;
        *o = (s8)(y - ay) * (s8)(t[(i + 1) % 3]->x102 - ax) - (s8)(x - ax) * (s8)(t[(i + 1) % 3]->y103 - ay);
    }
    if (c[0] == 0 && c[1] == 0) return 0;
    if (c[0] <= 0 && c[1] <= 0 && c[2] <= 0) return 1;
    if (c[0] < 0 || c[1] < 0 || c[2] < 0) return 0;
    return 1;
}

/* fn_8002D348: 47 of 55 words differ (from fn_80026950.cpp) */
int fn_8002D348(Unit** t, int n, Unit* p) {
    Unit* q[4];
    int i, j, k;
    if (n == 3) return fn_8002D218(t, p);
    if (n > 2 && n < 5) {
        k = 0;
        for (i = 1; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i != j) q[k++] = t[j];
            }
            if (fn_8002D218(q, p)) {
                t[0] = q[0];
                t[1] = q[1];
                t[2] = q[2];
            }
        }
    }
    return 0;
}

/* fn_80046E9C: 5 of 40 words differ (from fn_80042914.cpp) */
void fn_80046E9C(u8* p) {
    s8 y = *(f32*)(p + 0x34);
    fn_80126EB0(lbl_803CA870.unit2, (s8)*(f32*)(p + 0x30), y);
    fn_8010354C(lbl_803CA870.unit, lbl_803CA870.unit2, *(f32*)(p + 0x30), *(f32*)(p + 0x34), p);
}

/* fn_80047B18: 8 of 173 words differ (from fn_80042914.cpp) */
void fn_80047B18(Yell* p) {
    char buf[0x80];
    int* d;
    p->a = 0;
    p->b = 0;
    d = fn_80077064(lbl_803619D0 + 0x97);
    p->base = (u8*)d;
    p->n = *d;
    p->base = (u8*)(d + 1);
    yellPath(p, lbl_803CA870.unit, buf);
    fn_8023F1A0(buf, 0x80);
    yellPath(p, lbl_803CA870.unit2, buf);
    fn_8023F1A0(buf, 0x80);
    fn_80250D64(6, 0.5f, 500.0f);
}

/* fn_80047DCC: 152 of 168 words differ (from fn_80042914.cpp) */
void fn_80047DCC(Yell* p) {
    CmdState* s = &lbl_803CA870;
    yellPath(p, s->unit, s->buf30);
    yellPath(p, s->pair.unit2, s->bufB0);
    if (!fn_8023F880(s->buf30) || !fn_8023F880(s->bufB0)) return;
    p->a = fn_80075FB4(s->buf30, 0x80);
    p->b = fn_80075FB4(s->bufB0, 0x80);
    fn_80083B78(p);
}

/* fn_80042C84: 33 of 36 words differ (from fn_80042914.cpp) */
void fn_80042C84(void) {
    u8 m[0x10];
    int i;
    Unit* u;
    fn_8010E41C((char*)m, 0);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec && m[u->f4[8]]) {
            FLAGS(u) &= ~0ULL;
            fn_80122460(u);
        }
    }
}

/* fn_80043078: 40 of 98 words differ (from fn_80042914.cpp) */
void fn_80043078(void* a) {
    GameState* t = &lbl_803CAB38;
    u8 o = t->side;
    if (t->sideOn[o]) {
        u8* c = (u8*)fn_80062A9C(t);
        switch (*fn_80060728(t) & 3) {
        case 0:
        case 1:
            switch (t->side) {
            case 0:
                fn_801657DC(a);
                break;
            case 3:
                if (c) {
                    if (c[4] == 1) fn_80165764(a);
                    else fn_801657DC(a);
                }
                break;
            case 1:
            case 2:
                if (t->sideOn[t->side] == 2) fn_80165764(a);
                break;
            }
            break;
        case 2:
            if (((fn_80060728(t)[1] >> 28) & 3) == 0) {
                switch (t->sideOn[t->side]) {
                case 0:
                    break;
                case 2:
                    fn_80165764(a);
                    break;
                case 1:
                    if (c) {
                        if (c[4] == 1) fn_80165764(a);
                        else fn_801657DC(a);
                    }
                    break;
                }
            } else if (t->sideOn[t->side] == 2) {
                fn_801657A0(a);
            }
            break;
        }
    }
}

/* fn_80043214: 2 of 36 words differ (from fn_80042914.cpp) */
void fn_80043214(void* p) {
    Unit* u = ((Group*)lbl_804CB814)[lbl_803CAB38.side].head;
    while (u) {
        s8* xp = &u->x102;
        s8* yp = &u->y103;
        u = u->next;
        if (fn_8011799C(lbl_803EC898, *xp, *yp)) return;
    }
    fn_80083DC4(p, 5);
}

/* fn_8004333C: 3 of 55 words differ (from fn_80042914.cpp) */
void fn_8004333C(void) {
    if (lbl_803CAB38.side == 0 && !((*fn_80060728(&lbl_803CAB38) >> 14) & 1) && lbl_803CAB38.sideOn[lbl_803CAB38.side]) {
        Unit* u = fn_8012D2B0();
        if (u == 0) u = fn_8012D280(lbl_803CAB38.side);
        if (u && (u->f10c & 0x10000DC) == 0) {
            fn_800620A8(u->x102, u->y103, &lbl_803CAB38);
        }
    }
}

/* fn_80043BAC: 34 of 100 words differ (from fn_80042914.cpp) */
void fn_80043BAC(void) {
    u8 m[0x10];
    int i;
    Unit* u;
    u8 t[7] = {0, 5, 7, 8, 9, 0xa, 0xff};
    memset(m, (u8)lbl_804CA0A0, 0xb);
    markAll(m, t);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec && m[u->f4[8]]) {
            if ((u->f10c & 2) && !(u->f10c & 0x100000)) {
                fn_8011E300(u, u->x102, u->y103, 0);
            }
            FLAGS(u) &= 0xFFFFFF92E688C53EULL;
            fn_80109078(u->x110);
            fn_80126D9C(u, fn_801237EC(u));
            fn_80128E14(u, 0);
            fn_801283F8(u);
        }
    }
    fn_80060580(lbl_803CAB38.x554, lbl_803CAB38.f9c);
    lbl_803CAB38.f12 = 1;
    lbl_803CAB38.side = 0;
}

/* fn_80044284: 18 of 91 words differ (from fn_80044284.cpp) */
void fn_80044284(void) {
    const char* n = lbl_80361684 + 0x4d;
    if (!flagGet(&lbl_803CAB38, n)) {
        fn_802512C4(500.0f);
        fn_80250D64(0, 1.0f, 500.0f);
        fn_80250E38(0, 1.0f, 500.0f);
        fn_8025095C(0.0f, 500.0f);
        fn_80250A08(0.0f, 500.0f);
        fn_80250D64(6, 1.0f, 250.0f);
        fn_80250E38(6, 1.0f, 250.0f);
    }
}

/* fn_80044530: 1 of 22 words differ (from fn_80044284.cpp) */
void fn_80044530(void* a) {
    Scripts* b = (Scripts*)lbl_80379F58;
    void* p = fn_80081194(b->c, a);
    fn_80081194(b->b, fn_80081050(&b->a[0], p));
    fn_800CD4A4(0x13);
}

/* fn_80044588: 10 of 51 words differ (from fn_80044284.cpp) */
void fn_80044588(void* a) {
    void* p = fn_80081194(lbl_80379FA8, a);
    fn_80083DC4(p, 4);
    fn_80081050(lbl_80379F58, p);
    fn_800CD4A4(0x13);
    fn_80062380(&lbl_803CAB38, (u8*)&lbl_803CAB38 + 0x914);
    fn_8024BCAC();
    scale(&lbl_803CAB38);
    fn_8012FF30();
    fn_80062454(&lbl_803CAB38);
    fn_8012D620();
    fn_8012D908();
    fn_8012FF30();
}

/* fn_80047164: 66 of 84 words differ (from fn_80047164.cpp) */
void fn_80047164(Act* q, void* proc) {
    u8 b, c;
    int n;
    n = q->f18;
    fn_8011EED4(q->u1, q->u2, n, &b, &c);
    fn_80126EB0(q->u2, (s8)b, (s8)c);
    fn_800F39DC(q->u2);
    if (n > 0 && unitN(q->u2)) {
        int i;
        for (i = 0; i < n && unitN(q->u2); i++) {
            Hp* h = &q->u2->h;
            fn_80109094(h, 2, hpN(h) - 1);
        }
        if (fn_80109174(q->u2->x110) == 0 && (q->u2->f10c & 0x10000DC) == 0) {
            fn_80026CD8(lbl_803C8E80, q->u2, -1);
            fn_800E995C(proc, 0);
        }
    }
    switch (q->action) {
    case 0x13:
        fn_80119A88(q->u1, q->u2, 4);
        break;
    case 0x14:
        fn_80119A88(q->u1, q->u2, 5);
        break;
    }
}

/* fn_800474C8: 5 of 93 words differ (from fn_80047164.cpp) */
int fn_800474C8(void* proc) {
    char buf[0x80];
    Unit* s0 = (Unit*)lbl_803C8E80;
    Unit* s1 = (Unit*)(lbl_803C8E80 + 0x4a0);
    Unit* s = 0;
    Slot* it;
    u8* d;
    int v, w;
    u16 m;
    if (s0->f4[8] == 0) s = s0;
    if ((*(u32*)(lbl_803C8E80 + 0x15ec) & 5) == 0 && s1->f4[8] == 0) s = s1;
    if (s == 0 || s->s114 == 0 || ((u8*)s)[0x47b] == 0) return 0;
    it = fn_80030CF4(s);
    if (it == 0 || (d = it->data) == 0) return 0;
    if ((u8)(d ? d[0x12] : 0x13) == 0x10) return 0;
    m = d ? *(u16*)(d + 0x16) : 0;
    v = fn_80110F08(it);
    w = fn_801110C4(it, 1);
    fn_80290D04(buf, 0x80, lbl_803619D0 + 0x6f, w, v, (u8)m + 0x80);
    fn_800D0B38(0, buf);
    fn_801ABBA8(fn_800D08B4(lbl_803619D0 + 0x7a, fn_8011B77C(s->x12c, lbl_804CA4DC)), lbl_803619D0 + 0x85, proc, 1);
    return 1;
}

/* fn_800478B4: 4 of 48 words differ (from fn_80047164.cpp) */
int fn_800478B4(void* a) {
    Unit* u = fn_8002C590(lbl_803C8E80);
    Unit* v;
    u8 b, c;
    if (u == 0) return 0;
    if (!(u->f10c & 2)) return 0;
    v = u->u3f0;
    fn_8011EB4C(v, &b, &c);
    fn_801037D4(v->f8, v->f8->x102, v->f8->y103, (s8)b, (s8)c, a);
    fn_8011E300(v, (s8)b, (s8)c, 1);
    return 1;
}

/* fn_80047974: 6 of 34 words differ (from fn_80047164.cpp) */
void fn_80047974(void* a) {
    if (modeIs(lbl_804CB830)) {
        if ((lbl_803EC898 + ((s8)lbl_803CA870.cx + ((s8)lbl_803CA870.cy << 6)))[0x200d] == 0) return;
    }
    fn_800319F8(cmdItem(), a);
}

/* fn_8004806C: 14 of 63 words differ (from fn_80047164.cpp) */
void fn_8004806C(SeqTbl* p) {
    const char* t[4] = {lbl_804CCE88, lbl_804CCE8C, lbl_804CCE90, lbl_804CCE94};
    char buf[0x40];
    int k = fn_8012E8BC(lbl_803CA870.unit, (s8)fn_8012E9B4(lbl_803CA870.unit, lbl_803CA870.unit2));
    Unit* b = lbl_803CA870.unit2;
    Unit* a = lbl_803CA870.unit;
    s8 x = fn_8012E9B4(a, b);
    s8 y = fn_8012E9B4(b, a);
    strcpy(buf, *(char**)((u8*)&((Seq*)(p->base + y * 0xc * (p->n + 1)))[x] + 0x10));
    fn_80291110(buf, t[k]);
    fn_800D0B38(0, fn_80118C44(lbl_803CA870.unit2->ec));
    fn_8014BED4(buf, p);
}

/* fn_80048168: 16 of 62 words differ (from fn_80047164.cpp) */
void fn_80048168(SeqTbl* p) {
    const char* t[4] = {lbl_804CCE88, lbl_804CCE8C, lbl_804CCE90, lbl_804CCE94};
    char buf[0x40];
    int k = fn_8012E8BC(lbl_803CA870.unit2, (s8)fn_8012E9B4(lbl_803CA870.unit2, lbl_803CA870.unit));
    Unit* b = lbl_803CA870.unit2;
    Unit* a = lbl_803CA870.unit;
    s8 x = fn_8012E9B4(a, b);
    s8 y = fn_8012E9B4(b, a);
    strcpy(buf, *(char**)((u8*)&((Seq*)(p->base + x * 0xc * (p->n + 1)))[y] + 0x14));
    fn_80291110(buf, t[k]);
    fn_800D0B38(0, fn_80118C44(lbl_803CA870.unit->ec));
    fn_8014C2AC(buf);
}

/* fn_8004AD18: 12 of 110 words differ (from fn_8004A70C.cpp) */
void fn_8004AD18(Unit* u, Slot* s, void* proc) {
    Slot* p;
    s->f80 = 0;
    s->f40 = 0;
    s->f08 = 0;
    s->f04 = 0;
    if (u->f4[8] == 1) {
        p = (Slot*)u;
        if (LOCKED((Slot*)((u8*)p + 0x1bc))) goto skip;
        p = (Slot*)((u8*)p + 0x1e4);
        if (LOCKED(p)) goto skip;
        if (LOCKED(p + 1)) goto skip;
        if (LOCKED(p + 2)) goto skip;
        if (LOCKED(p + 3)) goto skip;
        if (LOCKED(p + 4)) goto skip;
        if (LOCKED(p + 5)) goto skip;
        s->f40 = 1;
    }
skip:
    if (fn_8012A0F4(u, s)) {
        if (u->f4[8] != 1) {
            fn_800314CC(s, proc, u);
        } else {
            fn_800315F8(s, proc, u);
        }
    } else {
        switch (u->f4[8]) {
        case 0:
        case 5:
        case 7:
        case 8:
        case 9:
        case 10:
            lbl_804CB3D8 = u;
            fn_80111C78(&lbl_803CAAE0, s);
            fn_80081194(lbl_8037B428, proc);
            break;
        }
    }
}

/* fn_8004AF14: 5 of 41 words differ (from fn_8004A70C.cpp) */
void fn_8004AF14(void* proc) {
    Item a;
    Item b;
    Unit* u = lbl_804CB3E0;
    void* d;
    fn_8011B32C(u->x12c, lbl_804CB3E8);
    d = fn_8011A158(lbl_804CB3E8);
    if (d) {
        fn_80111B34(&a);
        fn_80110BB4(&a, d);
        fn_80111B64(&b, &a);
        fn_8004AD18(u, (Slot*)&b, proc);
        fn_80111C24(&b, -1);
        fn_80111C24(&a, -1);
    }
}

/* fn_8004B120: 26 of 98 words differ (from fn_8004A70C.cpp) */
void fn_8004B120(Unit* u, void* proc) {
    int i;
    int f;
    if (u == 0) return;
    if (fn_8011AB30(u->x12c) <= 6 && fn_80127A90(u) - fn_8011B8A4(u->x12c) >= 0) {
        fn_8011A36C(u->x12c);
        return;
    }
    f = 0;
    for (i = 0; i < 18; i++) {
        SkillEnt* e = (SkillEnt*)((u8*)u + i * 8 + 0x12c);
        if (e && e->d && e->d[0x1f] && !(e->b5 & 1)) {
            f = 1;
            break;
        }
    }
    if (f) {
        lbl_804CB3E8 = 0;
        lbl_804CB3E0 = u;
        fn_80083DC4(fn_80081194(lbl_8037B490, proc), 10);
    } else {
        fn_8011A36C(u->x12c);
    }
}

/* fn_800487DC: best 29 of 118 words with hill-climbed declarations, all register choices. Same body as fn_80048A98, fn_80048D54, fn_80048FF8, fn_800492B8. */
void fn_800487DC(Act* q, void* proc) {
    s8 cx = q->cx;
    s8 cy = q->cy;
    s8 x = q->x;
    s8 y = q->y;
    switch (lbl_803CA870.action) {
    case 0x12:
        fn_800CFB34(lbl_803E7320);
        fn_800CFC50(lbl_803E7320, x, y, q->u2->fc, 0);
        fn_80026C44(lbl_803C8E80, q->u1, q->u2);
        break;
    case 0x40: {
        Cell buf[3];
        Cell* c;
        Cell* e;
        fn_8003B0F4(q->u1);
        c = fn_800CFCB4(lbl_803E7320, x, y);
        buf[0] = *c;
        e = &buf[1];
        c = fn_800CFCB4(lbl_803E7320, (s8)(cx * 2 - x), (s8)(cy * 2 - y));
        if (c) {
            *e = *c;
            e++;
        }
        e->a = -1;
        fn_800CFB34(lbl_803E7320);
        for (e = buf; e->a >= 0; e++) {
            fn_800CFC50(lbl_803E7320, e->a, e->b, e->c, e->d);
        }
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    }
    case 0x2c:
        fn_8003B0F4(q->u1);
        fn_80026CD8(lbl_803C8E80, q->u1, -1);
        break;
    }
    fn_8002C170(lbl_803C8E80);
    fn_800E8048(proc, fn_80048770);
}
