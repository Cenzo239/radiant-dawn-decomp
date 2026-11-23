/* Not compiled. Near misses; each note says what is left. Externs live in the matched files. */

/* fn_80107DC4: 6 of 88 words, local register rotation (price r31, width r30, colour r29).
   fn_80107F24: flag local should be r31 with params r27..r30; ours gives it r27. */
#pragma use_lmw_stmw off
void fn_80107DC4(Slot* s, int a, int x, int y, f32 k) {
    char buf[0x10];
    int price, w, c;
    if (s->item == 0) return;
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_80290DDC(buf, lbl_80367F40 + 0x12, (int)(k * (f32)fn_80111074(s)));
    w = (s16)fn_800CA3DC(buf, -1, 1.0f);
    c = 0;
    if (a) c = 0x20;
    price = (int)(k * (f32)fn_80111074(s));
    if (fn_800626E0(lbl_803CAB38) < price) c = 0;
    fn_800CB278(x + (0x12C - w), y, c, buf);
    fn_80107AE0(s, a, x, y, 1, (char*)1);
}

static inline BOOL Flag14(Slot* s) {
    BOOL r = 1;
    if ((*fn_801116B8(s) & 0x0002000000000000ULL) == 0 && s->f10 == 0) r = 0;
    return r;
}
void fn_80107F24(Slot* s, int a, int x, int y) {
    char buf[0x10];
    if (s->item == 0) return;
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    if (Flag14(s)) {
        strcpy(buf, lbl_80367F40 + 0x17);
    } else {
        fn_80290DDC(buf, lbl_80367F40 + 0x12, fn_80111094(s));
    }
    fn_800CB278(x + (0x12C - (s16)fn_800CA3DC(buf, -1, 1.0f)), y, a != 0 ? 0x20 : 0, buf);
    fn_80107AE0(s, a, x, y, 1, (char*)1);
}

/* fn_80107AE0: 2 of 104 words, `addi r0,r26,0xA8` must come before `addi r29,r24,lbl_80367F40@l`. */
#pragma use_lmw_stmw on
void fn_80107AE0(Slot* s, int a, int x, int y, int icon, char* nums) {
    int c2;
    u32 hl = a != 0;
    u32 c;
    c2 = 0;
    if (a) c2 = 0xC;
    c = hl;
    if (hl == 1) {
        if (s->f20) c = 4;
        if (s->f10) c = 0x40;
    }
    if (s->f40) c = 3;
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800CB278(x + 0x18, y, c, lbl_80367F40, fn_80110F08(s));
    if ((*fn_801116B8(s) & 0x0001000000000040ULL) == 0 && !s->f10 && nums) {
        nums = lbl_80367F40;
        fn_800CB278(x + 0xA8, y, hl, nums + 5, s->uses);
        fn_800CB278(x + 0xCB, y, c2, nums + 0xC, s->item ? s->item->maxUses : 0);
    }
    if (icon) {
        ICONS->v4(x, y, (u8)(s->item ? s->item->icon : 0) + 0x81);
    }
}


/* fn_801116F4: 15 of 87 words, only a swap: the low flag word should load into r5 and the price into r4. */
static inline u64* FlagsOf(ItemE* it) { if (it) return (u64*)&it->fh; return (u64*)&lbl_804CB7F0; }
int fn_801116F4(FSlot* s) {
    ItemE* it;
    int v;
    u64* f;
    if (s->item == 0) return 0;
    v = 0;
    FlagGuard();
    it = s->item;
    if (it) f = (u64*)&it->fh;
    else f = (u64*)&lbl_804CB7F0;
    if (*f & 0xFFE00000ULL) v += 50000;
    if (s->f10) v += 50000;
    {
        u16 p = 0;
        if (it) p = it->price;
        v += p * s->uses;
    }
    if (*f & 0x10) v += 10000;
    if (*f & 0x40) v += 10000;
    if (*f & 0x80) v += 10000;
    if (*f & 0x20) v += 10000;
    if (*f & 0x100) v += 2000;
    if (*f & 0x400) v += 2000;
    if (*f & 0x200) v += 2000;
    if (*f & 0x1000) v += 2000;
    if (*f & 0x2000) v += 1000;
    if (*f & 0x10000) v += 1000;
    if (it == fn_8010B228(lbl_803680E8 + 0x64E)) v += 20000;
    return v;
}

/* fn_8010D4E8: 6 of 32 words; the list pointer loads into r6 and the count into r5, ours r3/r4. */
void fn_8010D4E8(DProc* p) {
    u8 n = p->n;
    u8 i = p->idx;
    if (i >= n) {
        fn_80083B78(p);
    } else {
        DEnt* e = p->list[i];
        fn_8010D184(e, p->x61);
        if (e->unit) fn_800F68DC(e->unit, 0);
        p->idx++;
    }
}

/* fn_8010CDB4: 6 of 91 words: count copy should be r30 and the map base r31, ours swapped */
int fn_8010CDB4(const char* name) {
    Rec r;
    if (StOk()) {
        MGrid* m;
        u8 count, kind, id;
        u8* s;
        fn_8010B478(&r);
        s = Hdr(name, count, kind, id);
        if (s && count) {
            int i;
            m = &lbl_803EC898;
            for (i = 0; i < count; i++) {
                fn_8010BCBC(&s, &r, id, kind);
                if (r.xc != 1) goto yes;
                if (GridAt(m, r.xe, r.xf)) goto yes;
                if (GridAt(m, r.x10, r.x11)) goto yes;
            }
        }
        return 0;
    }
yes:
    return 1;
}

/* fn_8010D684: 34 of 59 words: registers; mode lives in r29 and rewrites itself */
void fn_8010D684(DProc* p) {
    u32 mode = p->x66;
    int i;
    switch (p->x61) {
    case 0:
    case 1:
        mode |= 0x10;
        break;
    }
    {
        u32 m = mode & 0xFFBF;
        u16 hi = m;
        u32 lo = m & 0xF;
        for (i = 0; i < p->n; i++) {
            DEnt2* e = (DEnt2*)p->list[i];
            if (e->unit) {
                if (p->x61 == 3) {
                    fn_80103CE4(e->unit, 1, e->xa, e->xb, p);
                } else {
                    fn_80103410(e->unit, e->path, (u16)(hi | (lo ? lo : e->x11)), p);
                }
            }
        }
    }
    fn_80114D00(&lbl_803EC898);
    p->x62 = 1;
}

/* fn_8010D770: not finished; register allocation in the first loop is off */
void fn_8010D770(DProc* p) {
    int i;
    if (p->x62 == 0) {
        for (i = p->idx; i < p->n; i++) {
            fn_8010D184(p->list[i], p->x61);
        }
        for (i = 0; i < p->n; i++) {
            DEnt2* e = (DEnt2*)p->list[i];
            void* u = e->unit;
            if (u) {
                u32 d = p->x66 & 0xF;
                if (d == 0) d = e->x11;
                if ((u16)d == 0) {
                    u8* q = e->path;
                    d = 0x40;
                    while (*q != 0x40) {
                        d = *q;
                        q++;
                    }
                }
                fn_800F6AEC(u, 0);
                fn_8010316C(u, (u16)d, 0, 0, 0);
            }
        }
        fn_80114D00(&lbl_803EC898);
    }
    {
        void** l = (void**)p->list;
        void** q = l;
        for (i = 0; i < 0x80; i++) {
            fn_80078E24(*q);
            *q = 0;
            q++;
        }
        fn_80078E24(l);
    }
    lbl_803EC1D0.lock = 1;
    fn_8012D588();
}

/* fn_8010D018: 2 of 91 words: the copy of count in the last loop should be r28, ours coalesces with r27 */
int fn_8010D018(const char* name) {
    Rec r;
    u8 kind, id;
    int n;
    UX* nx;
    u8 count;
    u8* s;
    UX* u;
    fn_8010B478(&r);
    n = 0;
    s = Hdr(name, count, kind, id);
    if (s == 0) return 0;
    u = (UX*)lbl_804CB814[5].head;
    while (u) {
        nx = u->next;
        if (u->fl & 0x400000) {
            fn_8010BCBC(&s, &r, id, kind);
            fn_80126EB0(u, r.xe, r.xf);
            fn_800F39DC(u);
            fn_800F3F08(u, 0);
            n++;
            u->x37E = r.a0;
            if ((u8)n == count) break;
        }
        u = nx;
    }
    {
        int i;
        int m = count; for (i = n; (u8)i < m; i++) fn_8010BCBC(&s, &r, id, kind);
    }
    return (u8)n;
}

/* fn_80105EB0: 2 of 57 words: load of w8 and wC swapped. Correct logic, including the always-false u8 == -1 test */
void fn_80105EB0(SaveA* d, const SaveA* s) {
    int i;
    d->w0 = s->w0;
    d->w4 = s->w4;
    d->wC = s->wC;
    d->w8 = s->w8;
    d->x10 = s->x10;
    d->x44 = s->x44;
    d->x45 = s->x45;
    d->x46 = s->x46;
    d->x47 = s->x47;
    if (d->x48 == -1) d->x48 = s->x48;
    d->x4b = s->x4b;
    for (i = 0; i < 0x1E; i++) {
        d->s12[i] = s->s12[i];
    }
    d->w34 = 0;
    d->w38 = 0;
    d->w3c = 0;
    d->w40 = 0;
    d->w34 = s->w34;
    d->w38 = s->w38;
    d->w3c = s->w3c;
    d->w40 = s->w40;
}

/* fn_80105BBC: first attempt, nesting of the lookup not right */
int fn_80105BBC(FHdr* h) {
    int j;
    FHdr* g;
    if (!Valid(h)) return 0;
    if (h->x60 != 2) return 0;
    {
        u8* base = lbl_804CB778;
        u32 o2 = 0x1A000;
        g = 0;
        for (j = 0; j < 2; j++, o2 += 0x6000) {
            FHdr* c = (FHdr*)(base + o2);
            if (Valid(c)) {
                int want = c->x63;
                FHdr* f;
                int o = 0x2000;
                int i;
                for (i = 0; i < 6; o += 0x4000, i++) {
                    f = (FHdr*)(base + o);
                    if (Valid(f) && want == f->x62) break;
                }
                if (i < 6 && f) {
                    g = c;
                    break;
                }
            }
        }
    }
    if (g == 0) return 0;
    return g->x63 == h->x62;
}

/* fn_80111FE4: 5 of 55 words: the two int-to-float conversions come out in the wrong order */
void fn_80111FE4(char* p, const char* name) {
    int cap = fn_80077BE0() << 3;
    int w = fn_800CA3DC(name, -1, 1.0f);
    if (w <= cap) {
        fn_802910CC(p + 6, name, 0x11);
    } else {
        fn_80290D04(p + 6, 0x18, lbl_803680E8 + 0x65C, (u8)(int)(64.0f * ((f32)w / (f32)cap)), name);
    }
}

/* fn_80106190: 68 of 73 words: not solved. The constants are hoisted into r10..r12, r30 before the first block, so it probably stores them through locals */
void fn_80106190(void** p) {
    SFile* f;
    memset(*p, 0, 0x26000);
    f = SF(*p, 0x2000);
    f->magic = 0x4645384A;
    f->ver = 0x20050201;
    f->n = 1;
    f->x60 = 2;
    f->x62 = 0;
    f->x64 = 3;
    f->x65 = 4;
    f->x66 = 0;
    f->pad67 = 1;
    *(u64*)&f->tickHi = (u64)(*(u32*)0x800000F8 / 4) * 3600;
    f = SF(*p, 0x6000);
    f->magic = 0x4645384A;
    f->ver = 0x20050201;
    f->n = 2;
    f->x60 = 2;
    f->x62 = 1;
    f->x64 = 4;
    f->x65 = 4;
    f->x66 = 0;
    f->pad67 = 1;
    f = SF(*p, 0xA000);
    f->magic = 0x4645384A;
    f->ver = 0x20050201;
    f->n = 3;
    f->x60 = 2;
    f->x62 = 2;
    f->x64 = 5;
    f->x65 = 4;
    f->x66 = 0;
    f->pad67 = 1;
    fn_80079E70();
}

/* fn_801095FC: 12 of 82 words, or 5 with x9 written first: the constants 1 and 0x14 and the second word land in the wrong registers (want r5, r0, r6) */
void fn_801095FC(Opt* o) {
    o->a0 = 0;
    o->a3 = 1;
    o->a5 = 0;
    o->a8 = 0;
    o->a11 = 1;
    o->a12 = 1;
    o->a14 = 0;
    o->a19 = 1;
    o->a23 = 1;
    o->a24 = 1;
    o->a25 = 0;
    o->a27 = 1;
    o->a30 = 0;
    o->x9 = 0x14;
    o->b6 = 0;
    o->b5 = 1;
    o->b4 = 0;
    o->b8 = 1;
    o->a20 = Sound();
    o->xa = 0x40;
    o->xb = 0;
    o->xc = 0;
    o->xd = 100;
    o->xe = 100;
    o->xf = 100;
    o->x10 = 100;
    o->x11 = 0;
    o->x8 = 1;
    o->x20 = 0;
    o->x24 = 0;
    o->x21 = 0;
    o->x22 = 0;
    o->x28 = 0;
    o->x23 = 0;
    o->a28 = 0;
    o->a6 = 1;
    o->a7 = 0;
    o->x12 = 0;
    o->x14 = 0;
    o->x18 = 0;
    o->x1c = 0;
}
