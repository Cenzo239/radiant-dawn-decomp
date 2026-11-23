/* fn_800D9AC8: ['DIFF fn_800D9AC8: 15 of 110 words differ'] */
int fn_800D9AC8(int id, int ax, int ay) {
    u16 fl;
    Unit* u = UnitId(id);
    void* path;
    s8 x;
    s8 y;
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (fn_8011F5B4(u) == 0) {
        return 0;
    }
    fl = OptFlags();
    x = ax;
    y = ay;
    path = fn_8010B964(u, &x, &y, 0, 0);
    if (path) {
        fn_80126EB0(u, (s8)*(u8*)&x, (s8)*(u8*)&y);
        if (lbl_804CB700 & 0x8001) {
            fn_800F4B94(u, OptX38());
            fn_8010316C(u, fl & 0xF, 0, 0, 0);
            fn_800F39DC(u);
        } else {
            fn_80103410(u, path, fl, Get30());
        }
    }
    fn_80114D00(&lbl_803EC898);
    return 1;
}

/* fn_800D9C80: ['DIFF fn_800D9C80: 2 of 26 words differ'] */
int fn_800D9C80(const char** ps, int def) {
    const char* s = *ps;
    int v = 0;
    while (*s) {
        if (*s == ',') {
            s++;
            break;
        }
        if (*s == '*') {
            v = def;
        }
        if (*s >= '0' && *s <= '9') {
            v *= 10;
            v += *s;
            v -= '0';
        }
        s++;
    }
    *ps = s;
    return v;
}

/* fn_800D9CE8: ['DIFF fn_800D9CE8: 15 of 116 words differ'] */
int fn_800D9CE8(int id, const char* s) {
    int fl;
    Unit* u = UnitId(id);
    u8* o;
    int x;
    int y;
    u8 buf[0x100];
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (fn_8011F5B4(u) == 0) {
        return 0;
    }
    fl = OptFlags() | 0x400;
    {
        x = u->x;
        y = u->y;
        o = buf + 2;
        buf[0] = x;
        buf[1] = y;
        while (*s) {
            x = fn_800D9C80(&s, x);
            y = fn_800D9C80(&s, y);
            o[0] = x;
            o[1] = y;
            o += 2;
        }
        *o = 0x40;
        fn_80126EB0(u, (s8)x, (s8)y);
    }
    if (lbl_804CB700 & 0x8001) {
        fn_800F4B94(u, OptX38());
        fn_8010316C(u, fl & 0xF, 0, 0, 0);
        fn_800F39DC(u);
    } else {
        fn_80103410(u, buf, fl, Get30());
    }
    fn_80114D00(&lbl_803EC898);
    return 1;
}

/* fn_800D9FA8: ['DIFF fn_800D9FA8: 37 of 149 words differ'] */
int fn_800D9FA8(int id, int dir, int dur) {
    Unit* u = UnitId(id);
    int a;
    UNIT_CHECK(u)
    switch ((u8)dir) {
    case 4:
        a = 0;
        break;
    case 6:
        a = 0x2D;
        break;
    case 2:
        a = 0x5A;
        break;
    case 10:
        a = 0x87;
        break;
    case 8:
        a = 0xB4;
        break;
    case 9:
        a = 0xE1;
        break;
    case 1:
        a = 0x10E;
        break;
    case 5:
        a = 0x13B;
        break;
    default:
        a = 0;
        break;
    }
    dur = TurnFrames(u, a, dur);
    dir = 0;
    if (TurnSnap(u)) {
        dir |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || dur == 0) {
        fn_80102E10(u, 0, dir, 0, a);
    } else {
        fn_80102E10(u, dur, dir, Get30(), a);
    }
    return 1;
}

/* fn_800DA1FC: ['DIFF fn_800DA1FC: 19 of 141 words differ'] */
int fn_800DA1FC(int id, int x, int y, int dur) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    y = fn_800FB100(u, 0.5f + x, 0.5f + y);
    dur = TurnFrames(u, y, dur);
    x = 0;
    if (TurnSnap(u)) {
        x |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || dur == 0) {
        fn_80102E10(u, 0, x, 0, y);
    } else {
        fn_80102E10(u, dur, x, Get30(), y);
    }
    return 1;
}

/* fn_800DA430: ['DIFF fn_800DA430: 17 of 123 words differ'] */
int fn_800DA430(int id, int a, int dur) {
    int fl;
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    dur = TurnFrames(u, a, dur);
    fl = 0;
    if (TurnSnap(u)) {
        fl |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || dur == 0) {
        fn_80102E10(u, 0, fl, 0, a);
    } else {
        fn_80102E10(u, dur, fl, Get30(), a);
    }
    return 1;
}

/* fn_800DADA0: ['DIFF fn_800DADA0: 10 of 117 words differ'] */
int fn_800DADA0(int id, int s, int scale, int dur, int x) {
    int k;
    Unit* u = UnitId(id);
    f32 f;
    void* q;
    UNIT_CHECK(u)
    if (s) {
        if ((u32)s < 0x64) {
            return 0;
        }
        k = fn_800F0994((const char*)s);
    } else {
        k = fn_800F760C(u);
    }
    if (fn_800F4628(u, k) == 0) {
        return 0;
    }
    if (scale < 0) {
        scale = 100;
    }
    f = scale / 100.0f;
    if (lbl_804CB700 & 0x8001) {
        dur = 0;
    } else if (dur < 0) {
        dur = 0x10;
    } else {
        dur = dur / 16.666666f;
    }
    q = 0;
    if (dur) {
        q = Get30();
    }
    fn_80104948(u, k, dur, x, q, f);
    return 1;
}

/* fn_800DC114: ['DIFF fn_800DC114: 7 of 39 words differ'] */
int fn_800DC114(int a, int b, int c, u8 r, u8 g, u8 bl) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    {
        UColor col = {r, g, bl, 0xFF};
        MapTint(a, b, c, col);
    }
    fn_801368DC(m);
    SceneDirty();
    return 1;
}

/* fn_800DC680: ['DIFF fn_800DC680: 4 of 60 words differ'] */
int fn_800DC680(int a, int b, int c) {
    FCam* m = fn_8012FCD0();
    if (m == 0) {
        return 0;
    }
    if (a <= -10000) {
        a = 0;
    }
    if (b <= -10000) {
        b = 0x28;
    }
    if (c <= -10000) {
        c = 0x10;
    }
    {
        m->f4 = m->f10 = a;
        m->f8 = m->f14 = b;
    }
    fn_8012F580(m, c);
    fn_8012F58C(m);
    fn_8012FF30();
    return 1;
}

/* fn_800DE044: ['DIFF fn_800DE044: 16 of 93 words differ'] */
int fn_800DE044(int x, int y) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        void* mm = fn_8013B9A8();
        if (mm) {
            void* e = fn_80135800(mm, x, y, 0x800, 0x10);
            if (e) {
                fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x22, 0);
                NotifyOpen(e);
                fn_801379F8(mm, 1);
                fn_8012D908();
            }
        }
        return 0;
    }
    {
        TileEv* e = (TileEv*)fn_80135800(m, x, y, 0x800, 0x10);
        if (e == 0) {
            return 0;
        }
        fn_8013DCF0(e, fn_8009E898());
        fn_800661A0(lbl_803CB770, e->x, (s8)*(u8*)&e->y, 0x22, 0);
    }
    SceneDirty();
    return 1;
}

/* fn_800DE1B8: ['DIFF fn_800DE1B8: 16 of 91 words differ'] */
int fn_800DE1B8(int x, int y) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        void* mm = fn_8013B9A8();
        if (mm) {
            void* e = fn_80135800(mm, x, y, 0x800, 0x10);
            if (e) {
                fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 0x22);
                NotifyClose(e);
                fn_801379F8(mm, 1);
                fn_8012D908();
            }
        }
        return 0;
    }
    {
        TileEv* e = (TileEv*)fn_80135800(m, x, y, 0x800, 0x10);
        if (e == 0) {
            return 0;
        }
        fn_8013DEF4(e, fn_8009E898());
        fn_8006625C(lbl_803CB770, e->x, (s8)*(u8*)&e->y, 0x22);
    }
    SceneDirty();
    return 1;
}

/* fn_800DE534: ['DIFF fn_800DE534: 9 of 50 words differ'] */
int fn_800DE534(int v) {
    int off;
    MapCtl2* m = (MapCtl2*)fn_8013B9A8();
    int i;
    if (m == 0) {
        return 0;
    }
    i = 0;
    off = 0;
    v = (u8)((-v | v) >> 31);
    for (; i < m->n; off += 0xD0, i++) {
        u8* e = m->tiles + off;
        if (((u32*)*(u32**)(e + 0x10))[0xB8 / 4] & 0x10000000) {
            fn_801CA33C(e, v, 0);
        }
    }
    fn_8013B2B8(m);
    fn_801364AC(m);
    fn_8013B8D0(m);
    return 1;
}

/* fn_800DE794: ['DIFF fn_800DE794: 13 of 48 words differ'] */
int fn_800DE794(int x, int y) {
    void* m = fn_8013B9A8();
    TileEv* e;
    if (m == 0) {
        return 0;
    }
    e = (TileEv*)fn_80135A54(m, x, y, 0x40000, 0x10);
    if (e == 0) {
        return 0;
    }
    y = -1;
    x = e->x;
    {
        int ey = e->y;
        if (lbl_804CB700 & 0x8001) {
            y = 0;
        }
        fn_8013C80C(x, ey, y, fn_8009E898());
    }
    SceneDirty();
    return 1;
}

/* fn_800DF0B8: ['DIFF fn_800DF0B8: 19 of 102 words differ'] */
int fn_800DF0B8(u32 id, int uid, int t, const char* s) {
    ObjH* o = (ObjH*)ObjGet(id);
    Unit* u;
    int k;
    if (o == 0) {
        return 0;
    }
    u = UnitId(uid);
    UNIT_CHECK(u)
    k = -1;
    if (s && s[0]) {
        k = fn_800F4284(u, s);
        if (k < 0) {
            k = fn_800F4394(u, s);
        }
    }
    if (k < 0) {
        fn_800E5878(o, u);
        fn_800E49AC(o, 0.015625f * ((UX*)u)->hC4);
    } else {
        o->d->o9C = fn_800DEF6C;
        fn_800E4904(o, 0, u);
        fn_800E48F0(o, 1, k);
        fn_800E48F0(o, 2, t);
    }
    return 1;
}

/* fn_800DF368: ['DIFF fn_800DF368: 15 of 52 words differ'] */
int fn_800DF368(u32 id, int v) {
    ObjH* o = (ObjH*)ObjGet(id);
    if (o == 0) {
        return 0;
    }
    {
        u32* q;
        u32* p;
        p = o->d->o0;
        q = &o->d->fl18;
        if (v) {
            if (q) {
                *q |= 4;
            }
            if (p) {
                *p |= 0x18;
            }
        } else {
            if (q) {
                *q &= ~4;
            }
            if (p) {
                *p &= ~0x18;
            }
        }
    }
    return 1;
}

