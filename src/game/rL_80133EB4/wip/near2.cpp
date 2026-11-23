/* Near misses from round 8, not compiled. Start with fn_8014B650 at the bottom: only the position of li r26 differs. */
static inline u32 Pack(u32 v, u8* q) { int k; for (k = 0; k < 8; k++) { v <<= 4; v |= (q[k] >> 4) & 0xF; } return v; }
void fn_801478F4(u8* src) {
    if (src == 0) {
        fn_8017F464(lbl_80413F00[lbl_804CB871], 0, 0x2000);
    } else {
        int w = lbl_804CB872;
        int h = lbl_804CB874;
        u32* d = (u32*)lbl_80413F00[lbl_804CB871];
        u32 v = 0;
        int y;
        for (y = 0; y < h; y += 8) {
            int x;
            for (x = 0; x < w; x += 8) {
                u8* s = src + x;
/*X*/
            }
        }
    }
    DCFlushRange(lbl_80413F00[lbl_804CB871], 0x2000);
}

/* fn_8014531C: only lis r28,1 hoist is missing */
static inline ParticleList* NewPL(void) {
    ParticleList* l = (ParticleList*)fn_80078CCC(0x1C, lbl_804CA72C, 0);
    if (l) {
        l->a = 0;
        l->b = 0;
        l->c = 0;
        l->f = 0;
        l->d = 0;
        l->e = 0;
    }
    return l;
}
static inline void InitPL(ParticleList* l, /*N*/ int n) {
    l->g = n;
    /*K*/
    l->a = (Particle*)fn_80078CCC(sz, lbl_804CA728, 0);
    l->b = (Particle**)fn_80078CCC(n * 4 + 4, lbl_804CA724, 0);
    DCFlushRange(l->a, sz);
    DCFlushRange(l->b, n * 4 + 4);
    l->f = 0;
    {
        int i;
        for (i = 0; i < l->g; i++) {
            Particle* e = l->a + i;
            e->n = 0;
            e->p = 0;
            l->b[i] = &l->a[i];
        }
    }
    l->c = l->b;
    l->b[l->g] = 0;
    l->d = 0;
    l->e = 0;
}
void fn_8014531C(RainP* r) {
    WeatherP* w = (WeatherP*)fn_80083B84(s80386540);
    r->x38 = fn_8001D3B4(lbl_80369AF8);
    ParticleList* l = NewPL();
    r->x3c = l;
    InitPL(l, 0x800);
    r->x32 = 1;
    r->x31 = -1;
    switch (r->x30) {
    case 7:
        w->x33 = 10;
        w->x38 = 0.75f;
        w->x34 = 0xC0;
        w->dir.x = 0.025f;
        w->dir.y = -0.05f;
        w->dir.z = 0.025f;
        w->x78 = 0xFF;
        w->x79 = 0xFF;
        w->x7a = 0xFF;
        w->x36 = 300;
        break;
    case 8:
        w->x33 = 2;
        w->x38 = 0.5f;
        w->x34 = 0xC0;
        w->dir.x = 0.005f;
        w->dir.y = -0.025f;
        w->dir.z = 0.005f;
        w->x78 = 0xFF;
        w->x79 = 0xFF;
        w->x7a = 0xFF;
        w->x36 = 600;
        break;
    case 9:
    {
        WD* d;
        w->x33 = 0x32;
        w->x38 = 0.75f;
        w->x34 = 0xC0;
        w->dir.x = 0.5f;
        w->dir.y = -0.25f;
        w->dir.z = 0.05f;
        w->x78 = 0xFF;
        w->x79 = 0xFF;
        w->x7a = 0xFF;
        w->x36 = 100;
        d = (WD*)fn_80081050(s803864B4, r);
        d->x30 = 1;
        fn_80144888(d);
        break;
    }
    case 0x13:
        w->x33 = 3;
        w->x38 = 0.6f;
        w->x34 = 0xFF;
        w->dir.x = -0.025f;
        w->dir.y = 0.09999999f;
        w->dir.z = 0.025f;
        w->x78 = 0xFF;
        w->x79 = 0x6B;
        w->x7a = 0;
        w->x36 = 300;
        break;
    }
    {
        MapModel* mm = fn_8013B9A8();
        switch (w->x32) {
        case 0:
            {
{ f32 m = -8.0f; w->lo.x = m; { f32 s = mm->scale; w->lo.y = 20.0f * s; } w->lo.z = m; w->hi.x = mm->x4c + 8; { f32 s = mm->scale; w->hi.y = 40.0f * s; } w->hi.z = mm->x4d + 8; } }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            {
                        f32 a;
            f32 e;
            f32 d;
            f32 c;
            f32 b;
            f32 f;
            { f32 s = mm->scale; a=-80.0f; a *= s; w->lo.x = a; }
            b=10.0f;
            c=-60.0f;
            d=80.0f;
            e=20.0f;
            f=30.0f;
            { f32 s = mm->scale; b *= s; w->lo.y = b; }
            { f32 s = mm->scale; c *= s; w->lo.z = c; }
            { f32 s = mm->scale; d *= s; w->hi.x = d; }
            { f32 s = mm->scale; e *= s; w->hi.y = e; }
            { f32 s = mm->scale; f *= s; w->hi.z = f; }
            }
            break;
        }
        r->x34 = mm->scale;
        fn_803134A8(r->x34, &w->dir, &w->dir);
    }
    w->x3c = 0.0f;
}

/* fn_80144938: FP regs; 1.5f must be hoisted into f0 and 1/128 into f4 */
void fn_80144938(DP2* p) {
    WeatherP* w = (WeatherP*)fn_80083B84(s80386540);
    if (w->x30) {
        Vec a = {0.0f, 0.0f, 0.0f};
        Vec b = {0.0f, 0.0f, 0.0f};
        if (w->x32 == 0) {
            u8* cam;
            if (fn_80068D74() == 0) return;
            cam = fn_8000F470();
            fn_80011B90(0, (Vec*)(cam + 0xE0), &a);
            fn_80011B90(0, &p->cam, &b);
            a.x -= b.x;
            a.y -= b.y;
            p->cam = *(Vec*)(cam + 0xE0);
        }
        {
            /*P*/
            f32 k = 1.0f;
            f32 d = 0.0078125f;
            f32 m = 1.5f;
            int i;
/*E*/
            for (i = 0; i < 2; i++) {
                (&p->a0)[i] += w->x6c * k - a.x;
                (&p->b0)[i] += w->x70 * k - a.y;
                k *= m;
                (&p->a0)[i] -= (int)((&p->a0)[i] * d) << 7;
                (&p->b0)[i] -= (int)((&p->b0)[i] * d) << 7;
            }
        }
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 800.0f, 1.0f);
        fn_8007E374(p->tex, 5, 0x411);
        fn_8007E164();
        fn_800800D4(0xB);
        fn_80080910((void*)fn_801445E8, p);
        fn_80080308();
    }
}

/* fn_8013C380 needs a dead word copy of a Vec at 0x20 */
struct DoorProc { u8 pad0[0x18]; void* x18; u8 pad1c[0x38 - 0x1C]; Mesh* m38; Mesh* m3c; Mesh* m40; Mesh* m44; int t; };
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
            void* e = fn_800E3810((char*)lbl_803697B4, p);
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

/* fn_8013EED0: register/induction order */
void fn_8013EED0(EP* p) {
    if (fn_80068D74()) {
        /*P*/
        EP* q;
        u8* p16;
        int x;
        int y;
        BOOL any;
        u8* p8;
/*E*/
        any = 0; q = p;
        fn_8013E7FC();
        for (y = (s8)(((MapG*)lbl_803EC898)->h - 1); (s8)y >= 0; y--) {
            x = (s8)(((MapG*)lbl_803EC898)->w - 1);
            {
                u8* a = lbl_803EC898 + y * 0x40;
                u8* b = lbl_803EC898 + y * 0x80;
                p8 = (u8*)(x + (int)a);
                p16 = (u8*)(x * 2 + (int)b);
            }
            for (; (s8)x >= 0; x--, p8--, p16 -= 2) {
                if (p8[0x200D] == 0) {
                    any = 1;
                } else if (*(s8*)(p8 + 0xF18E)) {
                    if (*(s16*)(p16 + 0x710E) >= 0) {
                        fn_8013EA08(q->x34, (s8)x, (s8)y, sTab[3]);
                    }
                } else if (*(s16*)(p16 + 0x710E) >= 0) {
                    fn_8013EA08(q->x34, (s8)x, (s8)y, sTab[1]);
                } else if (*(u16*)(p16 + 0xD18E)) {
                    fn_8013EA08(q->x34, (s8)x, (s8)y, sTab[2]);
                }
            }
        }
        if (any) {
            fn_80021BA4(1, 4, 5, 0);
            for (y = (s8)(((MapG*)lbl_803EC898)->h - 1); (s8)y >= 0; y--) {
                x = (s8)(((MapG*)lbl_803EC898)->w - 1);
                {
                    u8* a = lbl_803EC898 + y * 0x40;
                    u8* b = lbl_803EC898 + y * 0x80;
                    p8 = (u8*)(x + (int)a);
                    p16 = (u8*)(x * 2 + (int)b);
                }
                for (; (s8)x >= 0; x--, p8--, p16 -= 2) {
                    if (p8[0x200D] == 0) {
                        if (*(s8*)(p8 + 0xF18E)) {
                            if (*(s16*)(p16 + 0x710E) >= 0) {
                                fn_8013EA08(q->x34, (s8)x, (s8)y, sTab[3]);
                            }
                        } else if (*(s16*)(p16 + 0x710E) >= 0) {
                            fn_8013EA08(q->x34, (s8)x, (s8)y, sTab[1]);
                        } else if (*(u16*)(p16 + 0xD18E)) {
                            fn_8013EA08(q->x34, (s8)x, (s8)y, sTab[2]);
                        }
                    }
                }
            }
        }
        fn_80011838(-1);
    }
}

/* fn_8013AE18 FP regs only */
void fn_8013AE18(MapModel* mm) {
    Env* e=(Env*)mm;
    /*P*/
    f32 a=e->x6a/127.0f;
    f32 b=e->x6b/127.0f;
    f32 s=5.0f*mm->scale;
    f32 x=e->x6c*s;
    f32 y=e->x70*s;
    f32 z=e->x74;
    f32 c=a-1.0f;
/*E*/
    fn_8025095C(c,0.0f);
    fn_80250A08(b,0.0f);
    fn_80257AC0(x,0.0f);
    fn_80257B6C(y,0.0f);
    fn_80257A14(z,0.0f);
}

/* fn_8013AC48: 14 words, register of name param */
static inline SndMap* FindSnd(const char* const& name) {
    /*P*/
    const char* f;
    int* d;
    int n;
    SndMap* e;
    int i;
/*E*/
    f = lbl_803694D4 + 0x1BA;
    if (fn_80076F54(f)) {
        d = fn_80077064(f);
        n = *d;
        e = (SndMap*)(d + 1);
        for (i = 0; i < n; i++, e++) {
            if (e->name && fn_80291188(e->name, name) == 0) return e;
        }
    }
    return 0;
}
void fn_8013AC48(MapModel* mm) {
    char* name = mm->name;
    if (name) {
        SndMap* e = FindSnd(name);
        if (e == 0) {
            switch (mm->xb1) {
            case 0:
                e = FindSnd(lbl_803694D4 + 0x1C7);
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                e = FindSnd(lbl_803694D4 + 0x1CE);
                break;
            }
        }
        if (e) {
            Env2* v = (Env2*)mm;
            v->a = e->a;
            v->b = e->b;
            v->x = e->x;
            v->y = e->y;
            v->z = e->z;
        }
    }
}

/* fn_80134ECC: parameters must be below the loop locals */
static inline void DrawAll(MapModel* mm, u32 need, u32 reject) {
    /*P*/
    int k;
    int kk;
    int i;
    /*E*/
    if (mm->flags & 0x40000000) {
        for (k = 0; k < 3; k++) {
            kk = k + 1;
            for (i = 0; i < mm->nMesh; i++) {
                MapGroup* gr;
                u8 fl = mm->mesh[i].flags;
                Mesh* m = &mm->mesh[i];
                gr = m->group;
                if (!(fl & 4) && !(fl & 0x40) && !(fl & 0x20)) {
                    u32 g = gr->flags;
                    if (!(g & reject) && (need == 0 || need == (need & g))) fn_8001A218(kk, (u8*)m + 0x14);
                }
            }
        }
    }
}
void fn_80134ECC(MapModel* mm, u32 need, u32 reject) { DrawAll(mm, need, reject); }

/* fn_80134814: first draft, far */
struct Clr4 { Clr c[4]; };
extern Clr lbl_80413BF8[4], lbl_80413BE8[4];
extern const u8 lbl_804CDE4C[12];
extern Clr lbl_804CB834c;
extern u8 lbl_804CB835, lbl_804CB836, lbl_804CB837, lbl_804CB84C, lbl_804CB84D, lbl_804CB84E, lbl_804CB84F, lbl_804CB850, lbl_804CB851, lbl_804CB852;
extern s16 lbl_804CB840, lbl_804CB842, lbl_804CB844, lbl_804CB848, lbl_804CB84A;
extern s8 lbl_804CB846;
extern u32 lbl_804CB834w;
void fn_80134814(void) {
    Clr dA;
    Clr dB;
    Clr dF;
    u8 ar = lbl_804CDE4C[4], ag = lbl_804CDE4C[5], ab = lbl_804CDE4C[6], aa = lbl_804CDE4C[7];
    u8 br = lbl_804CDE4C[8], bg = lbl_804CDE4C[9], bb = lbl_804CDE4C[10], ba = lbl_804CDE4C[11];
    u8 fr = lbl_804CDE4C[0], fg = lbl_804CDE4C[1], fb = lbl_804CDE4C[2], fa = lbl_804CDE4C[3];
    {
        int i;
        for (i = 0; i < 4; i++) {
            lbl_80413BF8[i].r = ar;
            lbl_80413BE8[i].r = br;
            lbl_80413BF8[i].g = ag;
            lbl_80413BE8[i].g = bg;
            lbl_80413BF8[i].b = ab;
            lbl_80413BE8[i].b = bb;
            if (i == 3) break;
            lbl_80413BF8[i].a = aa;
            lbl_80413BE8[i].a = ba;
        }
    }
    lbl_804CB830 = 0;
    *(&lbl_804CB834) = 0;
    (&lbl_804CB834)[1] = 0;
    (&lbl_804CB834)[2] = 0;
    (&lbl_804CB834)[3] = 0;
    lbl_804CB839 = 0;
    lbl_804CB83A = 0;
    lbl_804CB83B = 0;
    lbl_804CB840 = -0x5A;
    lbl_804CB842 = 0;
    lbl_804CB844 = 0;
    lbl_804CB846 = -1;
    lbl_804CB848 = 0;
    lbl_804CB84A = 0;
    lbl_804CB838 = 0;
    lbl_804CB83C = fr;
    (&lbl_804CB83C)[1] = fg;
    (&lbl_804CB83C)[2] = fb;
    (&lbl_804CB83C)[3] = fa;
    lbl_80413BF8[3].a = aa;
    lbl_80413BE8[3].a = ba;
    lbl_804CB84C = 0;
    lbl_804CB84D = 0;
    lbl_804CB84E = 0;
    lbl_804CB84F = 0;
    lbl_804CB850 = 0;
    lbl_804CB851 = 0;
    lbl_804CB852 = 0;
    *(u8*)&dF.r = fr; *(u8*)&dF.g = fg; *(u8*)&dF.b = fb; *(u8*)&dF.a = fa;
    *(u8*)&dB.r = ar; *(u8*)&dB.g = ag; *(u8*)&dB.b = ab; *(u8*)&dB.a = aa;
    *(u8*)&dA.r = br; *(u8*)&dA.g = bg; *(u8*)&dA.b = bb; *(u8*)&dA.a = ba;
}

/* fn_8013C4A4: 12 words, f29/f31 swap for x and z */
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f64 fn_80295940(f32);
extern f64 fn_80295534(f32);
extern void fn_80312654(void*, int, f32);
void fn_8013C4A4(DoorProc* p) {
    u8 m0[0x30];
    u8 m1[0x30];
    u8 m2[0x30];
    u8 m3[0x30];
    Mesh* m = p->m38;
    
    /*P*/
    f32 x;
    f32 z;
    f32 rot;
    f32 ang;
    f32 y;
/*E*/
    x = m->tx;
    y = m->ty;
    z = *(f32*)((u8*)m + 0xC);
    ang = *(s16*)((u8*)m + 0xA);
    rot = 0.015625f * ang;
    p->t++;
    z += fn_8001EF30(0.0f, 1.0f, p->n, p->t);
    x = 0.01f * (f32)fn_80295940(p->t) + x;
    y = 0.01f * (f32)fn_80295534(p->t) + y;
    fn_8031292C(m0, 0.2f, 0.2f, 0.2f);
    fn_80312654(m1, 0x58, 4.712389f);
    fn_80312378(m1, m0, m3);
    fn_803128AC(m2, -0.5f, -0.5f, 0.0f);
    fn_80312378(m2, m3, m3);
    fn_80312654(m1, 0x5A, 0.017453292f * rot);
    fn_80312378(m1, m3, m3);
    fn_803128AC(m2, 0.5f, 0.5f, 0.0f);
    fn_80312378(m2, m3, m3);
    fn_803128AC(m2, x, y, z);
    fn_80312378(m2, m3, m3);
    {
        int a = fn_8001EF30(0.0f, 255.0f, p->n, p->t);
        u8 b = 0xFF - a;
        fn_801CA434(p->m38, m3);
        fn_801CA3DC(p->m38, b);
        if (p->m44) {
            fn_801CA434(p->m44, m3);
            fn_801CA3DC(p->m44, b);
        }
        if (p->m3c) fn_801CA3DC(p->m3c, (u8)a);
    }
    if (p->t >= p->n) fn_80083B78(p);
}

/* fn_80136C34: 23 words, hoisted base register */
struct ML { u8 pad[0x508E]; u16 link[0x1000]; };
#define L(i) ((ML*)lbl_803EC898)->link[i]
#define HDR(off) fn_80290DDC(path, lbl_803694D4 + off, mm->name); if (fn_80076F54(path)) { r = fn_80077064(path); fn_80109A18(&r); fn_80109A18(&r);
void fn_80136C34(MapModel* mm) {
    char path[0x48];
    u8* r = 0;
    /*P*/
    int x1;
    int y1;
    int n1;
    int n3;
    int x2;
    int y2;
    int n2;
    int i2;
    int x3;
    int y3;
    int i1;
    int i3;
/*E*/
    HDR(0xDD)
        n1 = fn_80109A2C(&r);
        for (i1 = 0; i1 < n1; i1++) {
            u8 v;
            x1 = (s8)fn_80109A18(&r);
            y1 = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            L(x1 + y1 * 0x40) = v;
        }
    }
    HDR(0xE8)
        n2 = fn_80109A2C(&r);
        for (i2 = 0; i2 < n2; i2++) {
            u8 v;
            x2 = (s8)fn_80109A18(&r);
            y2 = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            L(x2 + y2 * 0x40) = (L(x2 + y2 * 0x40) & ~0xF00) | (v << 8);
        }
    }
    HDR(0xF5)
        n3 = fn_80109A2C(&r);
        for (i3 = 0; i3 < n3; i3++) {
            u8 v;
            x3 = (s8)fn_80109A18(&r);
            y3 = (s8)fn_80109A18(&r);
            v = fn_80109A18(&r);
            L(x3 + y3 * 0x40) = v + (~v & 0xF) * 0x10;
        }
    }
}
static inline void TalkClose(void) {
    void* p = fn_80083B84(lbl_80386A98);
    if (p) {
        TalkEnd();
        fn_80081A90(p);
    }
}
void fn_8014C64C(void) { TalkClose(); }
static inline u32 StrLen(Talk* t) { return (t->str0 >> 31) == 0 ? (*(u8*)&t->str0 & 0x7F) : t->str1; }
void fn_8014C2AC(void* a) {
    /*P*/
    const char* s;
    Talk* t;
    int i;
    u32 n;
/*E*/
    if (lbl_804CB878 & 0x100) TalkClose();
    s = ((const char*(*)(void*))fn_800D0864)(a);
    fn_80083174(lbl_804181AC.proc);
    t = &lbl_804181AC;
    for (i = 0; i < 16; i++) t->x19c[i] = -1;
    n = StrLen(t);
    fn_800250B0(&lbl_804181AC.str0, 0, n, s, s + strlen(s), Empty());
    lbl_804181AC.cur = (lbl_804181AC.str0 >> 31) == 0 ? (char*)&lbl_804181AC.str0 + 1 : lbl_804181AC.strp;
    lbl_804CB878 &= ~0x30;
    fn_80083DC4(lbl_804181AC.proc, 0);
    fn_8014D220(&lbl_804CB878);
    if (lbl_804CB700 & 1) {
        fn_8014B650(lbl_804181AC.proc);
    } else {
        u8* q = fn_800C3558();
        q[0x1C] = 1;
    }
}

void fn_8014B4B4(void) {
    Talk* t = &lbl_804181AC;
    t->x1f2 = 2;
    if (fn_800C7FE8() & 4) {
        t->x1f2 = 2;
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
    {
        Talk* t = &lbl_804181AC;
        char* c = t->cur;
        lbl_804CB878 &= ~0x30;
        c += 2;
        t->cur = c;
        fn_80083DC4(lbl_804181AC.proc, 0);
    }
    fn_8014D220(&lbl_804CB878);
    if (lbl_804CB700 & 1) {
        fn_8014B650(lbl_804181AC.proc);
    } else {
        u8* q = fn_800C3558();
        q[0x1C] = 1;
    }
}
void fn_8014C8AC(PT* p) {
    Talk* q;
    Talk* t = p->t;
    int i;
    if (t->x1e9 != 0 || (lbl_804CB878 & 0x8000)) {
        fn_800C900C(3, 0x85);
        fn_80083B78(p);
    } else {
        {
            q=t;
            for (i = 0; i < 5; i++, q=(Talk*)((u8*)q+4)) {
                if (q->actor[0]) fn_800C7114(q->actor[0], p);
            }
        }
        {
            q=t;
            for (i = 0; i < 9; i++, q=(Talk*)((u8*)q+4)) {
                if (q->x21c[0]) fn_80151D28(q->x21c[0], p);
            }
        }
        fn_8014CF98();
        if (t->x18) fn_800D3C90(fn_800D4228(t->x18), 8);
        fn_80083B78(p);
    }
}

/* fn_80137... AF10: all but the AE18 FP block matches, draft below */
void fn_8013AF10(MapModel* mm) {
    u8 a[0x30];
    u8 s[0x30];
    u8 r[0x30];
    u8 t[0x30];
    u8 base[0x30];
    u8 mG[0x30];
    u8 mF[0x30];
    u8 mE[0x30];
    /*P*/
    Mesh* m;
    u8 mirror;
    int i;
/*E*/
    switch (mm->xb1) {
    case 0:
        fn_80312654(a, 0x58, 4.712389f);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        ((void(*)(void*))fn_80312318)(a);
        break;
    }
    {
        Vec v = ((Mx*)mm)->t;
        fn_803128AC(t, v.x, v.y, v.z);
    }
    { f32 q = ((Mx*)mm)->rot; fn_80312654(r, 0x79, 0.017453292f * q); }
    mirror = ((u8*)mm)[0xCC];
    if (mirror) {
        fn_8031292C(s, -1.0f, 1.0f, 1.0f);
    } else {
        ((void(*)(void*))fn_80312318)(s);
    }
    fn_80312378(r, t, base);
    fn_80312378(s, base, base);
    fn_80312378(a, base, base);
    fn_80312344(base, mm->xe4);
    {
        m = mm->mesh;
        for (i = 0; i < mm->nMesh; i++, m++) {
            fn_801CC5CC(m, 0.0f, 0.0f, 0.0f, 0.0f);
            fn_801CCC44(m, mirror);
            fn_801CCCA0(m);
        }
    }
    fn_8013826C(mm);
    fn_8013B5E4(mm);
    {
        Env3* e = (Env3*)mm;
        f32 sc = 5.0f * mm->scale;
        f32 b = e->b / 127.0f;
        f32 x = e->x * sc;
        f32 y = e->y * sc;
        f32 z = e->z;
        fn_8025095C(e->a / 127.0f - 1.0f, 0.0f);
        fn_80250A08(b, 0.0f);
        fn_80257AC0(x, 0.0f);
        fn_80257B6C(y, 0.0f);
        fn_80257A14(z, 0.0f);
    }
    {
        f32 sc = 5.0f * mm->scale;
        fn_80312318(mE, 5.0f);
        fn_80312654(mF, 0x58, -4.712389f);
        fn_8031292C(mG, sc, sc, sc);
        fn_80312344(mm->xe4, mE);
        fn_80312378(mE, mG, mE);
        fn_80312378(mE, mF, mE);
        {
            MapEntry18* w = mm->lights;
            int i;
            for (i = 0; i < 16; i++, w++) fn_802727A0(w, mE);
        }
    }
}

/* fn_8014B650: 4 score, li r26 order only. Needs talk.h plus the F18/F14/SB helpers */
struct TF { u32 f; u16 ctr; };
#define CUR (*(u8**)&lbl_804181AC.cur)
static inline BOOL IsSjisB(u8 c, const u8* p) {
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        c = p[1];
        if ((c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFC)) return 1;
    }
    return 0;
}
extern u8 lbl_80386B70[], lbl_80386B64[];
extern int fn_80149434(Talk*, char**);
extern int fn_80085708(void*);
extern int fn_801513E4(void*);
extern void fn_80151818(void*, void*);
extern void fn_80151CC4(void*, void*);
extern int fn_800CAB40(u8*);
extern void fn_8014EE28(void*, int);
extern void fn_80151360(void*, int);
extern void fn_8014EF58(void*);
static inline u8* CurP(Talk* t) {
    u8* r;
    if (t->x1e8) return (u8*)t->x21c[0];
    r = (u8*)t->x240;
    if (r == 0) r = (u8*)t->x21c[0];
    return r;
}
void fn_8014B650(void* proc) {
    /*P*/
    Talk* t1;
    Talk* t2;
    int i;
    int i3;
    Talk* t3;
    int i2;
    int i1;
    Talk* t;
    int n;
/*E*/
    u32 f;
    u32 a;
    while (a = *(volatile u32*)&lbl_804CB878, f = lbl_804CB878, !(a & 0x20)) {
    retry:
        ((TF*)&lbl_804CB878)->ctr++;
        switch (fn_80149434(&lbl_804181AC, &lbl_804181AC.cur)) {
        case 2:
        case 0:
            continue;
        case 1:
            goto retry;
        case 4:
        default:
            break;
        }
        if (fn_80085708(lbl_80386B70) || fn_80085708(lbl_80386B64)) continue;
        if (fn_801513E4(CurP(&lbl_804181AC))) {
            fn_80151818(CurP(&lbl_804181AC), lbl_804181AC.proc);
            continue;
        }
        if (!(lbl_804CB700 & 3) && CurP(&lbl_804181AC)[0x80] == 0) {
            fn_80151CC4(CurP(&lbl_804181AC), lbl_804181AC.proc);
            continue;
        }
        fn_8014B244(&lbl_804181AC);
        {
            u8 c = *CUR;
            if ((s32)c == 0x23) {
                n = fn_800CAB40(CUR);
                for (i = 0; i < n; i++) {
                    fn_8014EE28(lbl_80413F10, (s8)*CUR);
                    fn_80151360(CurP(&lbl_804181AC), (s8)*CUR++);
                }
            } else {
                if (!IsSjisB(c, CUR)) {
                    fn_80151360(CurP(&lbl_804181AC), (s8)c);
                    fn_8014EE28(lbl_80413F10, (s8)*CUR++);
                } else {
                    fn_80151360(CurP(&lbl_804181AC), (s8)c);
                    fn_8014EE28(lbl_80413F10, (s8)*CUR++);
                    fn_80151360(CurP(&lbl_804181AC), (s8)*CUR);
                    fn_8014EE28(lbl_80413F10, (s8)*CUR++);
                }
                *(u16*)&lbl_804181AC.x1ec = *(u16*)&lbl_804181AC.x1f0;
            }
        }
    }
    if (f & 0x10) {
        fn_80083DC4(proc, 3);
        return;
    }
    fn_8014EF58(lbl_80413F10);
    {
        a = *(volatile u32*)&lbl_804CB700;
        f = lbl_804CB700;
        if ((a & 2) && ((f & 0x8000) || lbl_804181AC.x1e9)) fn_800C900C(2, 0x85);
    }
    if (lbl_804CB700 & 3) {
        if (lbl_804181AC.x1e9) fn_800C835C(0, 0);
    if (lbl_804181AC.proc) {
        {
            t1 = &lbl_804181AC;
            for (i1 = 0; i1 < 9; i1++, t1 = (Talk*)((u8*)t1 + 4)) {
                if (t1->x21c[0]) fn_80150C68(t1->x21c[0]);
                t1->x21c[0] = 0;
            }
        }
        {
            t2 = &lbl_804181AC;
            for (i2 = 0; i2 < 5; i2++, t2 = (Talk*)((u8*)t2 + 4)) {
                if (t2->actor[0]) fn_800C4240(t2->actor[0]);
                t2->actor[0] = 0;
            }
        }
        if (lbl_804CB880) fn_80006A2C(&lbl_804CB880);
        F18(&lbl_804181AC);
        F14(&lbl_804181AC);
        {
            Talk* t = &lbl_804181AC;
            if ((t->str0 >> 31) == 0) {
                ((u8*)&t->str0)[1] = 0;
                ((SB*)&t->str0)->n = 0;
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
            t3 = &lbl_804181AC;
            for (i3 = 0; i3 < 8; i3++, t3 = (Talk*)((u8*)t3 + 4)) {
                if (t3->x1c4[0]) fn_800DF6C8(t3->x1c4[0]);
            }
        }
    }
        fn_80081A90(proc);
    } else if (lbl_804181AC.x1e9) {
        fn_80083DC4(proc, 2);
    } else {
        fn_8014CF98();
        {
            Talk* q = &lbl_804181AC;
            int i;
            for (i = 0; i < 9; i++, q = (Talk*)((u8*)q + 4)) {
                if (q->x21c[0]) fn_80151D28(q->x21c[0], proc);
            }
        }
        {
            Talk* q = &lbl_804181AC;
            int i;
            for (i = 0; i < 5; i++, q = (Talk*)((u8*)q + 4)) {
                if (q->actor[0]) {
                    if (lbl_804CB700 & 3) {
                        fn_800C4240(q->actor[0]);
                    } else {
                        fn_800C71CC(q->actor[0], proc);
                    }
                    q->actor[0] = 0;
                }
            }
        }
        if (lbl_804181AC.x18) fn_800D3C90(fn_800D4228(lbl_804181AC.x18), (u8)(lbl_804181AC.x204 * 0x3C / 1000));
    }
}
}
