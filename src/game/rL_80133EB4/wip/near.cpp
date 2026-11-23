/* Near misses for region rL. Not compiled and its externs are not complete: copy a function
 * back next to the structs and externs of the neighbouring matched file to retry it.
 * Closest (words differing, all register or stack-slot differences unless noted):
 *   fn_80135554: 3, loop counter r31 should be r29 in the lights loop (needs UpdateEnv-style inline)
 *   fn_8013A054-style block-scoped counters are the first thing to try on everything here.
 *   fn_80138E6C: 9, three trailing dead stores to a stack Vec at 0x8 are missing
 *   fn_8013B74C: 9, lim/i registers r26/r27 swapped
 *   fn_8014C8AC: 11 and fn_8014C64C: 27, array walker should be below the loop counter
 *   fn_8014B45C: 8, same walker/counter swap
 *   fn_8014C99C: 7, r3/r4 swapped and ori folding
 *   fn_8014C59C: 7, fn_80143374: 5, fn_8014B1D8: 5 (dead branch layout), fn_8014B4B4: 8
 *   fn_80135C44: 123, registers rotate through the inlined FindMesh; layout is right
 *   fn_80138000: 78, mostly one register rotation; corner writes need flat hgt[k*4+j]
 *   fn_801368DC, fn_80146A4C: a Color kept on the stack in the original is optimised out here
 *   fn_8013C380: 27, a dead word copy of a Vec is missing
 */
void fn_8013B8D0(H18* h) {
    O31* o = h->o;
    if (o) O31Draw(o, lbl_804CB834);
}

void fn_80143374(void* a, void* b, P14* c) {
    f32 x, y;
    u8* q;
    y = lbl_804CB858;
    x = lbl_804CB854;
    q = c->x14;
    *(f32*)(q + 8) = x;
    *(f32*)(q + 0xC) = -y;
}

void fn_80134ECC(Sc* sc, u32 need, u32 reject) {
    int k;
    int i;
    Vec unused;
    if (sc->flagsB4 & 0x40000000) {
        for (k = 0; k < 3; k++) {
            for (i = 0; i < sc->nMesh; i++) {
                Mesh* m = &sc->mesh[i];
                u8 fl = sc->mesh[i].flags;
                u8* o = m->owner;
                if (!(fl & 4) && !(fl & 0x40) && !(fl & 0x20)) {
                    u32 g = *(u32*)(o + 0xB8);
                    if (!(g & reject) && (need == 0 || need == (need & g))) fn_8001A218(k + 1, (u8*)m + 0x14);
                }
            }
        }
    }
}


int fn_80135C44(MapModel* mm, Mesh* m, Mesh** list, int n) {
    u32 f;
    int i;
    if (m == 0) return n;
    for (i = 0; i < n; i++) {
        if (list[i] == m) return n;
    }
    list[n++] = m;
    f = m->group->flags | 0x200000;
    n = fn_80135C44(mm, FindMesh(mm, m->x0 - 1, (m->y0 + m->y1) / 2, f, 0x10), list, n);
    n = fn_80135C44(mm, FindMesh(mm, m->x1 + 1, (m->y0 + m->y1) / 2, f, 0x10), list, n);
    n = fn_80135C44(mm, FindMesh(mm, (m->x0 + m->x1) / 2, m->y0 - 1, f, 0x10), list, n);
    n = fn_80135C44(mm, FindMesh(mm, (m->x0 + m->x1) / 2, m->y1 + 1, f, 0x10), list, n);
    return n;
}

void fn_801368DC(MapModel* mm) {
    Color c;
    u8* fog;
    f32 s;
    fn_80010968(0);
    fog = fn_80010960();
    fn_80010AB8();
    c.r = lbl_804CB83C.r;
    c.g = lbl_804CB83D;
    c.b = lbl_804CB83E;
    c.a = lbl_804CB83F;
    FogSet(fog, lbl_804CB839, (s8)lbl_804CB83A * (5.0f * mm->scale), (s8)lbl_804CB83B * (5.0f * mm->scale), c);
    fn_80010AE4();
}

void fn_801369BC(MapModel* mm) {
    char path[0x48];
    u8* r;
    Color e;
    Color c;
    Color t;
    u8* b = (u8*)mm;
    u8 ver;
    fn_80290DDC(path, lbl_803694D4 + 0xD0, mm->name);
    if (fn_80076F54(path)) {
        r = fn_80077064(path);
        ver = fn_80109A18(&r);
        b[0x54] = fn_80109A18(&r);
        b[0x55] = fn_80109A18(&r);
        b[0x56] = fn_80109A18(&r);
        b[0x57] = fn_80109A18(&r);
        *(f32*)(b + 0x58) = (u32)fn_80109A18(&r) / 100.0f;
        *(f32*)(b + 0x5C) = (s16)fn_80109A2C(&r) / 100.0f;
        b[0x64] = fn_80109A18(&r);
        b[0x65] = fn_80109A18(&r);
        {
            u8 c0 = fn_80109A18(&r);
            u8 c1 = fn_80109A18(&r);
            u8 c2 = fn_80109A18(&r);
            u8 c3 = fn_80109A18(&r);
            t.r = c0;
            t.g = c1;
            t.b = c2;
            t.a = c3;
            *(u32*)&c = *(u32*)&t;
            *(Color*)(b + 0x66) = c;
        }
        if (ver >= 1) {
            b[0x60] = fn_80109A18(&r);
            b[0x61] = fn_80109A18(&r);
            b[0x62] = fn_80109A18(&r);
            b[0x63] = fn_80109A18(&r);
        }
        if (ver >= 2) {
            u8 id = fn_80109A18(&r);
            u8 a0 = fn_80109A18(&r);
            u8 a1 = fn_80109A18(&r);
            u8 a2 = fn_80109A18(&r);
            u8 a3 = fn_80109A18(&r);
            e.b = fn_80109A18(&r);
            e.a = lbl_804CDE8C.a;
            e.r = a2;
            e.g = a3;
            if (id != 0) {
                u8* o = fn_8017C218((u8)(id - 1), mm->x10);
                *(u8*)(*(u8**)(o + 0x30) + 0x25) = a0;
                *(u16*)(*(u8**)(o + 0x30) + 0x28) = a1;
                SetColor((Color*)(*(u8**)(o + 0x30) + 0x2B), e);
            }
        }
    }
}

void fn_80136C34(MapModel* mm) {
    char path[0x48];
#define M ((MapLink*)lbl_803EC898)
    u8* r = 0;
    int i;
    fn_80290DDC(path, lbl_803694D4 + 0xDD, mm->name);
    if (fn_80076F54(path)) {
        int y;
        int x;
        int n;
        r = fn_80077064(path);
        fn_80109A18(&r);
        fn_80109A18(&r);
        n = fn_80109A2C(&r);
        for (i = 0; i < n; i++) {
            u8 v;
            x = (s8)fn_80109A18(&r);
            y = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            M->link[x + y * 0x40] = v;
        }
    }
    fn_80290DDC(path, lbl_803694D4 + 0xE8, mm->name);
    if (fn_80076F54(path)) {
        int n;
        int x;
        int y;
        r = fn_80077064(path);
        fn_80109A18(&r);
        fn_80109A18(&r);
        n = fn_80109A2C(&r);
        for (i = 0; i < n; i++) {
            u8 v;
            x = (s8)fn_80109A18(&r);
            y = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            M->link[x + y * 0x40] = (M->link[x + y * 0x40] & 0xF0FF) | (v << 8);
        }
    }
    fn_80290DDC(path, lbl_803694D4 + 0xF5, mm->name);
    if (fn_80076F54(path)) {
        int n;
        int x;
        int y;
        r = fn_80077064(path);
        fn_80109A18(&r);
        fn_80109A18(&r);
        n = fn_80109A2C(&r);
        for (i = 0; i < n; i++) {
            u8 v;
            x = (s8)fn_80109A18(&r);
            y = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            M->link[x + y * 0x40] = v + (~v & 0xF) * 0x10;
        }
    }
}

BOOL fn_801386AC(void* a, int x, int y, Vec* out) {
    f32 zero = 0.0f;
    MiniMap* m = lbl_804CB85C;
    f32 tw = m->tw;
    f32 s = tw / m->w;
    f32 fx = s * ((0.5f + x) - -(m->w * 0.5f - m->x));
    f32 fy = s * ((0.5f + y) - -(m->h * 0.5f - m->y));
    out->z = zero;
    out->x = fx;
    out->y = fy;
    if (fx < zero || fy < zero || fx > tw || fy > tw) return 0;
    return 1;
}

int fn_8013B664(MapModel* mm) {
    int n = 0;
    int c;
    int i;
    int r = 0;
    for (i = 0; i < mm->nMesh; i++) {
        u32 f = mm->mesh[i].group->flags;
        if ((f & 0x10) == 0 && (f & 0x10000000) == 0x10000000) n++;
    }
    if (n > 0) {
        c = 0;
        for (i = 0; i < n; i++) {
            Mesh* m = fn_80135934(mm, i, 0x10000000, 0x10);
            if (m && ((u8*)m)[0xCD]) c++;
        }
        r = c * 100 / n;
    }
    return r;
}

void fn_8013E77C(void) {
    if (lbl_804CB84C) {
        MapDim* d = (MapDim*)lbl_803EC898;
        lbl_804CB852 = 1;
        lbl_804CB84D = (lbl_804CB84D + (u8)d->w - lbl_804CB84F) % (u8)d->w;
        lbl_804CB84E = (lbl_804CB84E + (u8)d->h - lbl_804CB850) % (u8)d->h;
    }
}

WeatherProc* fn_80146A4C(void* parent) {
    WeatherProc* w = (WeatherProc*)fn_80081050(lbl_80386540, parent);
    Vec2I b;
    Vec2I a;
    Color4 c;
    w->x30 = 1;
    w->x7c = 0;
    w->x33 = 0;
    w->x34 = 0;
    w->x31 = 0;
    w->x38 = 0.0f;
    w->x3c = 0.0f;
    w->x40 = 0.0f;
    w->x36 = 300;
    a.x = 0;
    a.y = 0;
    a.z = 0;
    w->v54.x = a.fx();
    w->v54.y = a.fy();
    w->v54.z = a.fz();
    b.x = 0;
    b.y = 0;
    b.z = 0;
    w->v60.x = b.fx();
    w->v60.y = b.fy();
    w->v60.z = b.fz();
    c.r = lbl_804CA720.r;
    c.g = lbl_804CA721;
    c.b = lbl_804CA722;
    c.a = lbl_804CA723;
    SetC4(w, c);
    w->x32 = fn_8013B9A8()->xb1;
    return w;
}

int fn_8014B1D8(Talk* t, u8* a) {
    if (a == t->actor[0]) return 0;
    if (a == t->actor[1]) return 1;
    if (a == t->actor[2]) return 2;
    if (a == t->actor[3]) return 3;
    if (a == t->actor[4]) return 4;
    return -1;
}

void fn_8014B45C(void) {
    Talk* t = &lbl_804181AC;
    int i;
    for (i = 0; i < 9; i++) {
        if (t->x21c[i]) fn_80150F0C(t->x21c[i]);
    }
}

void fn_8014B4B4(void) {
    Talk* t = &lbl_804181AC;
    u8 v = 2;
    t->x1f2 = v;
    if (fn_800C7FE8() & 4) {
        t->x1f2 = v;
    } else if (fn_800C7FE8() & 8) {
        t->x1f2 = 5;
    } else {
        if (!(lbl_804CB878 & 0x80)) t->x1f2 = 0;
        fn_800C835C(3, lbl_804181AC.x204);
    }
}

void fn_8014C59C(void) {
    if (lbl_804181AC.proc == 0 || fn_80083B84(lbl_80386A98) == 0) return;
    fn_8014D350(&lbl_804CB878);
    fn_80083174(lbl_804181AC.proc);
    lbl_804CB878 &= ~0x30;
    lbl_804181AC.cur += 2;
    fn_80083DC4(lbl_804181AC.proc, 0);
    fn_8014D220(&lbl_804CB878);
    if (lbl_804CB700 & 1) {
        fn_8014B650(lbl_804181AC.proc);
    } else {
        fn_800C3558()[0x1C] = 1;
    }
}

void fn_8014C99C(void) {
    u32 g;
    u32 f;
    f = lbl_804CB878;
    g = lbl_804CB700;
    lbl_804CB878 = f & ~4;
    lbl_804CB700 = g | 2;
    if (f & 0x8000) lbl_804CB700 = (g | 2) | 0x8000;
}

void fn_8014C8AC(PT* p) {
    int i;
    Talk* t = p->t;
    if (t->x1e9 != 0 || (lbl_804CB878 & 0x8000)) {
        fn_800C900C(3, 0x85);
        fn_80083B78(p);
    } else {
        for (i = 0; i < 5; i++) {
            if (t->actor[i]) fn_800C7114(t->actor[i], p);
        }
        for (i = 0; i < 9; i++) {
            if (t->x21c[i]) fn_80151D28(t->x21c[i], p);
        }
        fn_8014CF98();
        if (t->x18) fn_800D3C90(fn_800D4228(t->x18), 8);
        fn_80083B78(p);
    }
}

void fn_80135554(MapModel* mm) {
    int i;
    Mesh* m;
    if ((mm->flags & 0x40000000) && !(mm->flags & 0x80000000)) {
        if (mm->x04) fn_8013450C(mm->quad, 0);
        if (IsShadowMode()) CullShadow(mm);
        fn_80134F90(mm);
        m = mm->mesh;
        for (i = 0; i < mm->nMesh; i++, m++) {
            fn_801CC2BC(m, 0, 0);
        }
        if (mm->x04 && !(mm->flags & 0x80000000) && mm->xb1 == 0) {
            fn_80010788(3, 0x90, fn_80137724, mm);
        }
        fn_8013531C(mm);
        {
            u8* cam = fn_8000F470();
            if (cam) {
                Vec c;
                Vec b;
                Vec a;
                c = *(Vec*)(cam + 0xEC);
                b = *(Vec*)(cam + 0xE0);
                a = *(Vec*)(cam + 0xD4);
                fn_80257948(&a, &b, &c);
            }
        }
        UpdateEnv(mm);
    }
}

void fn_80138E6C(u32* p) {
    MapModel* mm = (MapModel*)p;
    IVec v;
    IVec dead;
    int i;
    MapEntry18* e;
    *(volatile u32*)&p[0x2F] = 0;
    p[0x2D] = 0;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    mm->x4c = 8;
    mm->x4d = 8;
    mm->nGroup = 0;
    mm->nMesh = 0;
    mm->xab = 0;
    mm->xac = 0;
    mm->xad = 0;
    mm->xae = 0;
    mm->xaf = 0;
    mm->xb0 = 0;
    p[5] = 0;
    p[6] = 0;
    p[4] = 0;
    p[0x2F] = 0;
    *(s8*)&mm->x4e = -1;
    *(f32*)&p[0x31] = 1.0f;
    *(f32*)&p[0x32] = 1000.0f;
    fn_80134814();
    ((u8*)p)[0x6A] = 0;
    ((u8*)p)[0x6B] = 0;
    *(f32*)&p[0x1B] = 8.0f;
    *(f32*)&p[0x1C] = 8.0f;
    *(f32*)&p[0x1D] = 1.0f;
    e = mm->lights;
    for (i = 0; i < 16; i++, e++) fn_802729A8(e);
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0;
    p[0xB] = 0;
    p[0xC] = 0;
    p[0xD] = 0;
    p[0xE] = 0;
    p[0xF] = 0;
    p[0x10] = 0;
    p[0x11] = 0;
    p[0x12] = 0;
    ((u8*)p)[0x54] = 0xF8;
    ((u8*)p)[0x55] = 0;
    *(f32*)&p[0x16] = 1.0f;
    ((u8*)p)[0x56] = 0;
    ((u8*)p)[0x57] = 0;
    *(f32*)&p[0x17] = 0.0f;
    ((u8*)p)[0x64] = 0;
    ((u8*)p)[0x60] = 0;
    *(f32*)&p[0x1E] = 0.0f;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    *(f32*)&p[0x35] = *(f32*)&v.x;
    *(f32*)&p[0x36] = *(f32*)&v.y;
    *(f32*)&p[0x37] = *(f32*)&v.z;
    *(f32*)&p[0x38] = 0.0f;
    ((u8*)p)[0xCC] = 0;
    dead.x = 0;
    dead.y = 0;
    dead.z = 0;
    fn_keep(&dead);
}

void fn_80135554(MapModel* mm) {
    u8 mtxC[0x30];
    u8 mtxB[0x30];
    u8 mtxA[0x30];
    f32 s;
    Mesh* m;
    int i;
    if ((mm->flags & 0x40000000) && !(mm->flags & 0x80000000)) {
        if (mm->x04) fn_8013450C(mm->quad, 0);
        if (IsShadowMode()) {
            int j;
            for (j = 0; j < mm->nMesh; j++) {
                Mesh* m = MeshAt(mm, j);
                if ((m->group->flags & 0x20000000) && (lbl_803EC898 + 0x200D)[m->ty * 0x40 + m->tx] == 0) {
                    m->flags |= 0x20;
                }
            }
        }
        fn_80134F90(mm);
        {
            int i;
            Mesh* m = mm->mesh;
            for (i = 0; i < mm->nMesh; i++, m++) {
                fn_801CC2BC(m, 0, 0);
            }
        }
        if (mm->x04 && !(mm->flags & 0x80000000) && mm->xb1 == 0) {
            fn_80010788(3, 0x90, fn_80137724, mm);
        }
        fn_8013531C(mm);
        {
            u8* cam = fn_8000F470();
            if (cam) {
                Vec c;
                Vec b;
                Vec a;
                c = *(Vec*)(cam + 0xEC);
                b = *(Vec*)(cam + 0xE0);
                a = *(Vec*)(cam + 0xD4);
                fn_80257948(&a, &b, &c);
            }
        }
        s = 5.0f * mm->scale;
        fn_80312318(mtxA, 5.0f);
        fn_80312654(mtxB, 0x58, -4.712389f);
        fn_8031292C(mtxC, s, s, s);
        fn_80312344(mm->xe4, mtxA);
        fn_80312378(mtxA, mtxC, mtxA);
        fn_80312378(mtxA, mtxB, mtxA);
        LightsMul(mm, mtxA);
    }
}

void fn_80138000(MapModel* mm, int x0, int y0, int x1, int y1, int both) {
    char path[0x40];
    fn_80290DDC(path, lbl_803694D4 + 0x13B, mm->name);
    if (fn_80076F54(path)) {
        u8* panels = fn_80077064(path);
        u16* idx;
        int y;
        fn_80290DDC(path, lbl_803694D4 + 0x148, mm->name);
        idx = (u16*)fn_80077064(path);
        for (y = y0; y <= y1; y++) {
            int yy = (s8)y << 6;
            u16* q = idx + (x0 + y * mm->x4c);
            int x;
            for (x = x0; x <= x1; x++) {
                s16* pn = (s16*)(panels + *q++ * 0xC);
                s8 t = (s8)(u32)fn_8011D1E4(*(void**)(pn + 4));
                MapH* M = (MapH*)lbl_803EC898;
                int j;
                M->ter[(s8)x + yy] = t;
                for (j = 0; j < 4; j++) {
                    M->hgt[(((s8)x + yy) << 2) + j] = pn[j];
                    if (both) M->hgt2[(((s8)x + yy) << 2) + j] = pn[j];
                }
            }
        }
    }
}

void fn_8014C64C(void) {
    void* p = fn_80083B84(lbl_80386A98);
    if (p) {
        if (lbl_804181AC.proc) {
            {
                int i;
                Talk* t = &lbl_804181AC;
                for (i = 0; i < 9; i++) {
                    if (t->x21c[i]) fn_80150C68(t->x21c[i]);
                    t->x21c[i] = 0;
                }
            }
            {
                int i;
                Talk* t = &lbl_804181AC;
                for (i = 0; i < 5; i++) {
                    if (t->actor[i]) fn_800C4240(t->actor[i]);
                    t->actor[i] = 0;
                }
            }
            if (lbl_804CB880) fn_80006A2C(&lbl_804CB880);
            {
                Talk* t = &lbl_804181AC;
                if (t->x18) {
                    fn_800D42A0(t->x18);
                    t->x18 = 0;
                }
            }
            {
                Talk* t = &lbl_804181AC;
                if (t->x14) {
                    fn_80081A90(t->x14);
                    t->x14 = 0;
                }
            }
            {
                Talk* t = &lbl_804181AC;
                if ((t->str0 >> 31) == 0) {
                    ((u8*)&t->str0)[1] = 0;
                    *(u8*)&t->str0 &= ~0x7F;
                } else {
                    *t->strp = 0;
                    t->str1 = 0;
                }
            }
            lbl_804181AC.proc = 0;
            lbl_804181AC.cur = 0;
            fn_8014CFEC();
            if (lbl_804CB878 & 0x80) {
                fn_80068C08();
                lbl_804CB878 &= ~0x80;
            }
            lbl_804CB700 &= ~0x8002;
            fn_8014D364(&lbl_804CB878);
            {
                int i;
                Talk* t = &lbl_804181AC;
                for (i = 0; i < 8; i++) {
                    if (t->x1c4[i]) fn_800DF6C8(t->x1c4[i]);
                }
            }
        }
        fn_80081A90(p);
    }
}

void fn_8013C380(DoorProc* p) {
    p->t = 0;
    fn_801CA3DC(p->m38, 0xFF);
    fn_801CA3E4(p->m38, 1);
    if (p->m44) {
        fn_801CA3DC(p->m44, 0xFF);
        fn_801CA3E4(p->m44, 1);
    }
    if (p->m3c) {
        fn_801CA3DC(p->m3c, 0);
        fn_801CA3E4(p->m3c, 1);
        if (fn_801CA1D8(p->m3c)) fn_801CAA24(p->m3c, 0, 0);
        {
            void* e = fn_800E3810(lbl_803697B4, p);
            if (e) {
                Vec a;
                fn_801CA5D4(&a, p->m3c);
                Vec b = a;
                Vec c = b;
                fn_800E48C8(e, &c);
            }
        }
    }
    if (p->m40) fn_801CB5EC(p->m40, p->x18, 0, 0x3C);
}

BOOL fn_8013B74C(MapModel* mm, int pct) {
    int n = 0;
    int i;
    int lim;
    for (i = 0; i < mm->nMesh; i++) {
        u32 f = mm->mesh[i].group->flags;
        if ((f & 0x10) == 0 && (f & 0x10000000) == 0x10000000) n++;
    }
    if (n > 0) {
        lim = pct * n / 100;
        if (lim == 0 && pct > 0) lim = 1;
        if (lim > n) lim = n;
        for (i = 0; i < n; i++) {
            Mesh* m = fn_80135934(mm, i, 0x10000000, 0x10);
            if (m) {
                MapEntry18* e = FindEntry(mm, m);
                if (i < lim) {
                    fn_801CA33C(m, 0xFF, 0);
                    if (e) fn_80272624(e, 1.0f);
                } else {
                    fn_801CA33C(m, 0, 0);
                    if (e) fn_80272624(e, 0.0f);
                }
            }
        }
        return 1;
    }
    return 0;
}

