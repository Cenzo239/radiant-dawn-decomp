#include "game/rP_80105B04/rp.h"
/* Deployment files: a header {count, kind, [x, id if kind == 7]} then records read by fn_8010BCBC. */
struct Rec {
    u16 a0, a2;
    void* p4, *p8;
    u8 xc, xd;
    s8 xe, xf;
    s8 x10, x11;
    u8 pad12[2];
    u8 w14[0x58 - 0x14];
    u8 x58[0x60 - 0x58];
    u8 x60[5];
    u8 x65, x66;
    u8 pad67;
};
struct DProc {
    u8 pad[0x30];
    u8 file[0x31];
    u8 x61;
    u8 x62;
    u8 idx;  /* 0x63 */
    u8 n;    /* 0x64 */
    u8 t65;  /* 0x65 */
    u16 x66;
    struct DEnt** list; /* 0x68 */
};
struct DEnt { u8 pad[4]; void* unit; };
extern "C" {
u8* fn_80076F54(const char* s);
u8 fn_80109A18(u8** s);
void fn_8010B478(Rec* r);
void fn_8010BCBC(u8** s, Rec* r, u8 id, int kind);
void fn_80083B78(void* p);
void fn_800F68DC(void* u, int k);
int fn_800F69E4(void* u);
void fn_800F6AEC(void* u, int k);

struct USlot { u8 pad[0xFC]; u8 id; };
struct SideL { USlot* head; USlot* tail; u8 idx; };
struct Roster { u8 lock; u8 pad; u16 n; u16 ids[0x100]; };
extern SideL* lbl_804CB814;
extern Roster lbl_803EC1D0;
void fn_8012D588();
USlot* fn_8012CE54(void* id);
void fn_8011FE74(USlot* u, int k);
void fn_8011D580(USlot* u, Rec* r);
void fn_8011E048(USlot* u, Rec* r);

static inline USlot* Spawn(Rec* r) {
    USlot* u;
    if (r->p4 == 0) return 0;
    u = lbl_804CB814[4].head;
    switch (r->xc) {
    case 4:
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        fn_8011FE74(u, r->xc);
        break;
    }
    fn_8011D580(u, r);
    if (u) lbl_803EC1D0.ids[lbl_803EC1D0.n++] = u->id;
    return u;
}
static inline u8* Hdr(const char* name, u8& count, u8& kind, u8& id) {
    u8* s = fn_80076F54(name);
    if (s == 0) return 0;
    count = fn_80109A18(&s);
    kind = fn_80109A18(&s);
    switch (kind) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    default:
        break;
    case 7:
        fn_80109A18(&s);
        id = fn_80109A18(&s);
        break;
    }
    s = (u8*)(((u32)s + 3) & ~3);
    return s;
}

#pragma use_lmw_stmw on
struct DEnt2 { u8 pad[4]; void* unit; u8 pad8[2]; s8 xa; s8 xb; u8 padC[5]; u8 x11; u8 path[1]; };
#if TARGET_PC
FE10_PROTO void fn_80103CE4(void* u, int k, p32arg, p32arg, void* p);
#else
void fn_80103CE4(void* u, int k, int x, int y, void* p);
#endif
void fn_80103410(void* u, u8* path, u16 m, void* p);
void fn_80114D00(void* m);
#if TARGET_PC
FE10_PROTO void fn_8010316C(void* u, u16 d, p32arg, p32arg, p32arg);
#else
void fn_8010316C(void* u, u16 d, int a, int b, int c);
#endif
void fn_80078E24(void* p);
struct UList { u8 pad[0xE8]; struct UList* next; };
struct UFull {
    u8 pad[0xEC];
    void* person;
    u8 padF0[4];
    SideL* side;
    u8 padF8[0x37E - 0xF8];
    u16 x37E;
    u8 pad380[0x3F0 - 0x380];
};
extern UFull* lbl_804CB810;
extern u8 lbl_804CB830;
struct MGrid { int w; int h; u8 pad[0x200D-8]; u8 g[64][64]; u8 pad2[0x15190-0x300D]; s16* cost; };
extern MGrid lbl_803EC898;
static inline u8 GridAt(MGrid* m, s8 x, s8 y) { return *((u8*)m + x + (y << 6) + 0x200D); }
void fn_8010E41C(u8* t, int mode);

static inline UFull* FindByTag(int tag) {
    u8 mask[0xB];
    UFull* found = 0;
    int i;
    if (tag) {
        fn_8010E41C(mask, 3);
        for (i = 1; i < 0xFF; i++) {
            u8 k = i;
            UFull* u = k ? lbl_804CB810 + (k - 1) : 0;
            if (u->person && mask[u->side->idx] && tag == u->x37E) found = u;
        }
    }
    return found;
}
static inline BOOL StOk() {
    BOOL ok = 1;
    u8 st = lbl_804CB830;
    if (st != 1 && st != 2) ok = 0;
    return ok;
}
int fn_8010CDB4(const char* name);
void fn_80126EB0(void* u, s8 x, s8 y);
void fn_800F39DC(void* u);
void fn_800F3F08(void* u, int k);
void fn_80129214(void* u, Rec* r);
struct DFile; int fn_8010C200(DFile* f);
extern void* lbl_804CA4D8;
int fn_8011B77C(void* s, void* id);

struct DFile {
    u8* cur;   /* 0 */
    USlot* unit; /* 4 */
    s8 x8, x9, xa, xb;
    u8 xc, xd, xe, xf;
};
struct UX {
    u8 pad[0xE8];
    UX* next;
    u8 padEC[8];
    SideL* side;
    u8 padF8[0x10C - 0xF8];
    u32 fl;
    u8 x110[0x12C - 0x110];
    u8 skills[0x37E - 0x12C];
    u16 x37E;
};
int fn_8010D018(const char* name);
void fn_8010D684(DProc* p);
void fn_8010D770(DProc* p);
#pragma use_lmw_stmw off
extern char lbl_80368054[];
extern u8 lbl_803CAB38[];
void* fn_80078D9C(int n, const char* s, int k);
void fn_80083DC4(void* p, int k);
void fn_800620A8(void* g, f32 x, f32 y);
struct DProc2 {
    u8 pad[0x30];
    char file[0x31];
    u8 x61, x62, idx, n, t65;
    u16 x66;
    void** list;
};
struct UFA { u8 pad[0x102]; s8 x; s8 y; };
static inline u8* Hdr2(const char* name, u8& count, u8& kind, u8& x, u8& id) {
    u8* s = fn_80076F54(name);
    if (s == 0) return 0;
    count = fn_80109A18(&s);
    kind = fn_80109A18(&s);
    switch (kind) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    default:
        break;
    case 7:
        x = fn_80109A18(&s);
        id = fn_80109A18(&s);
        break;
    }
    s = (u8*)(((u32)s + 3) & ~3);
    return s;
}
#pragma use_lmw_stmw on
struct DE {
    u8* cur;
    void* unit;
    s8 x8, x9, xa, xb;
    u8 xc, xd, xe, xf;
    u8 x10, x11, x12;
};
struct RecL { u16 a0, a2; void* p4, *p8; u8 xc, xd; s8 xe, xf; s8 x10, x11; u8 pad12[0x60-0x12]; u8 x60, x61;  };
#if TARGET_PC
FE10_PROTO char * fn_80291480(const char*, const char*);
#else
int fn_80291480(const char*, const char*);
#endif
extern char lbl_8036807C[];
extern s8 lbl_803EC89C_[];
#if TARGET_PC
FE10_PROTO struct Unit * fn_8012CF28(int, int);
#else
int fn_8012CF28(int, int);
#endif
int fn_8010BED8(const char* name, int mode, DE** list) {
    Rec r;
    u8* s;
    u8* cur;
    u8 count;
    u8 kind;
    u8 x;
    u8 id;
    DE** q;
    int m3;
    int m4;
    int n;
    u8 fl;
    int i;
    DE* e;
    USlot* u;
    int j;
    DE** w;
    int i2;
    fn_8010B478(&r);
    s = Hdr2(name, count, kind, x, id);
    cur = s;
    n = 0;
    fl = 0;
    if (fn_80291480(name, lbl_80368054 + 0x28)) fl |= 1;
    switch (x) {
    case 1: fl |= 2; break;
    case 2: fl |= 4; break;
    case 3: fl |= 8; break;
    }
    q = list;
    m3 = fl & 3;
    m4 = fl & 4;
    for (i = 0; i < count; i++) {
        e = *q;
        e->unit = 0;
        e->xd = 0;
        e->xe = 0;
        e->x12 = 0x40;
        e->x8 = -1;
        e->x9 = -1;
        e->xa = -1;
        e->xb = -1;
        e->cur = cur;
        e->xc = fl;
        e->xd = id;
        e->xf = kind;
        fn_8010BCBC(&cur, &r, id, kind);
        if (r.xe < lbl_803EC898.w && r.xf < lbl_803EC898.h && r.x10 < lbl_803EC898.w && r.x11 < lbl_803EC898.h) {
            if (m3 || fn_8012CF28(r.xe, r.xf) == 0) {
                u = fn_8012CE54(r.p4);
                if (u && ((UFull*)u)->side->idx != 6) {
                    if (m4) e->xc |= 0x10;
                    if (r.a2 & 0x800) e->xc |= 0x10;
                }
                if ((r.a2 & 8) && mode != 2) {
                    e->xc |= 0x20;
                    if (r.xc == 0 && u == 0) e->xc |= 0x10;
                }
                e->unit = 0;
                q++;
                n++;
                e->x8 = r.xe;
                e->x9 = r.xf;
                e->xa = r.x10;
                e->xb = r.x11;
                e->x10 = r.x65;
                e->x11 = r.x66;
            }
        }
    }
    if (fl & 1) {
        for (i2 = 0; i2 < n - 1; i2++) {
            w = list;
            for (j = 0; j < n - 1 - i2; j++) {
                DE* a = w[0];
                DE* b = w[1];
                if (!(a->xc & 0x10) && (b->xc & 0x10)) {
                    w[0] = b;
                    w[1] = a;
                }
                w++;
            }
        }
    }
    return n;
}

void* fn_8010B964(UFA* u, s8* x, u8* y, void* a, void* b);
void fn_8011800C(void* v, u8* o);
int fn_8010C408(DE* e);
void fn_8010D184(DE* e, int mode, void* a, void* b) {
    switch (mode) {
    case 0:
    case 3:
        if (fn_8010C408(e)) {
            fn_8011800C(fn_8010B964((UFA*)e->unit, &e->xa, (u8*)&e->xb, a, b), &e->x12);
        }
        break;
    case 1:
        if (fn_8010C408(e)) {
            e->xa = e->x8;
            e->xb = e->x9;
            e->x11 = e->x10;
            e->x12 = 0x40;
        }
        break;
    case 2: {
        Rec r;
        UX* u;
        fn_8010B478(&r);
        fn_8010BCBC(&e->cur, &r, e->xd, e->xf);
        u = (UX*)FindByTag(r.a0);
        if (u && (u->fl & 0x9D)) u = 0;
        e->unit = u;
        if (u) lbl_803EC1D0.ids[lbl_803EC1D0.n++] = ((USlot*)u)->id;
        if (u) {
            fn_8011800C(fn_8010B964((UFA*)e->unit, &e->xa, (u8*)&e->xb, a, b), &e->x12);
        }
        break;
    }
    }
    if (e->unit) fn_80126EB0(e->unit, e->xa, e->xb);
}
void fn_80126F80(USlot*, USlot*);
s16 fn_801237EC(USlot*);
void fn_80126D9C(USlot*, int);
void fn_8011E120(USlot*, Rec*);
void fn_8011FF10(USlot*, u8);
int fn_8010C408(DE* e) {
    Rec r;
    USlot* u;
    USlot* v;
    if (e->xc & 1) return fn_8010C200((DFile*)e);
    fn_8010B478(&r);
    fn_8010BCBC(&e->cur, &r, e->xd, e->xf);
    u = fn_8012CE54(r.p4);
    if (e->xc & 8) {
        if (u) {
            int k6 = ((UFull*)u)->side->idx;
            if (k6 == 6 && !(((UX*)u)->fl & 0x20)) {
                u = 0;
            } else if (((UX*)u)->fl & 0x20000000) {
                fn_8011FE74(u, r.xc);
                fn_80126EB0(u, r.xe, r.xf);
                ((UX*)u)->x37E = r.a0;
            } else {
                v = Spawn(&r);
                fn_80126F80(v, u);
                fn_80126D9C(v, fn_801237EC(v));
                u = v;
            }
        } else if (e->xc & 0x20) {
            u = Spawn(&r);
            ((UX*)u)->fl |= 0x20000000;
        }
    } else if (u == 0) {
        if (e->xc & 0x20) u = Spawn(&r);
    } else {
        u8 idx = ((UFull*)u)->side->idx;
        switch (idx) {
        case 6:
            if ((e->xc & 2) && (((UX*)u)->fl & 0x20)) {
                v = Spawn(&r);
                fn_80126F80(v, u);
                fn_80126D9C(v, fn_801237EC(u));
                u = v;
            } else {
                u = 0;
            }
            break;
        case 7: case 8: case 9: case 10:
            fn_8011FE74(u, r.xc);
            fn_8011E120(u, &r);
            fn_80126EB0(u, r.xe, r.xf);
            fn_8011FF10(u, r.pad67);
            fn_8011E048(u, &r);
            if (r.xc) *((u8*)u + 0x380) = idx;
            break;
        default:
            if (r.xc == 0) {
                fn_8011FE74(u, r.xc);
                fn_80126EB0(u, r.xe, r.xf);
                fn_8011E048(u, &r);
            } else {
                u = Spawn(&r);
            }
            break;
        }
    }
    if (u) {
        fn_800F39DC(u);
        fn_800F3F08(u, 0);
        fn_80129214(u, &r);
        e->unit = u;
        return 1;
    }
    return 0;
}

void fn_8010D4E8(DProc* p) {
    u8 n = p->n;
    u8 i = p->idx;
    if (i >= n) {
        fn_80083B78(p);
    } else {
        DEnt* e = p->list[i];
        fn_8010D184((DE*)e, p->x61, (void*)n, p->list);
        if (e->unit) fn_800F68DC(e->unit, 0);
        p->idx++;
    }
}
void fn_8010D684(DProc* p) {
    int lo;
    u16 mode;
    int i;
    mode = p->x66;
    switch (p->x61) {
    case 0:
    case 1:
        mode |= 0x10;
        break;
    }
    mode &= ~0x40;
    lo = mode & 0xF;
    for (i = 0; i < p->n; i++) {
        DEnt2* e = (DEnt2*)p->list[i];
        if (e->unit) {
            if (p->x61 == 3) {
                fn_80103CE4(e->unit, 1, e->xa, e->xb, p);
            } else {
                int d = lo;
                if (d == 0) d = e->x11;
                fn_80103410(e->unit, e->path, (u16)(mode | d), p);
            }
        }
    }
    fn_80114D00(&lbl_803EC898);
    p->x62 = 1;
}
static inline u8 LastDir(u8* w) {
    u8 d = 0x40;
    while (*w != 0x40) {
        d = *w;
        w++;
    }
    return d;
}
void fn_8010D770(DProc* p) {
    u32 d;
    void** l;
    void* u;
    int i2;
    int i;
    int o2;
    int o;
    void** q;
    int j;
    if (p->x62 == 0) {
        i = p->idx;
        for (o = i * 4; i < p->n; o += 4, i++) {
            fn_8010D184(*(DE**)((u8*)p->list + o), p->x61, (void*)p->n, p->list);
        }
        for (i2 = 0, o2 = 0; i2 < p->n; o2 += 4, i2++) {
            DEnt2* e = *(DEnt2**)((u8*)p->list + o2);
            u = e->unit;
            if (u) {
                d = p->x66 & 0xF;
                if (d == 0) d = e->x11;
                if ((u16)d == 0) {
u8* w = e->path; d = 0x40; while (*w != 0x40) { d = *w++; }
                }
                fn_800F6AEC(u, 0);
                fn_8010316C(u, (u16)d, 0, 0, 0);
            }
        }
        fn_80114D00(&lbl_803EC898);
    }
    l = (void**)p->list;
    q = l;
    for (j = 0; j < 0x80; j++) {
        fn_80078E24(*q);
        *q = 0;
        q++;
    }
    fn_80078E24(l);
    lbl_803EC1D0.lock = 1;
    fn_8012D588();
}

extern u8 lbl_803857A8[];
extern u32 lbl_804CB700;
u16 fn_800D8F4C(void);
void fn_8012D908(void);
void fn_801476E8(void);
void* fn_80081194(void* s, void* p);
char* strcpy(char*, const char*);
void fn_8010D8B4(const char* name, int mode, void* proc) {
    int k;
    int i;
    int j;
    void** l;
    void** q;
    u16 fade;
    int n;
    void** w;
    DEnt2* e;
    void* u;
    u32 d;
    lbl_803EC1D0.lock = 0;
    lbl_803EC1D0.n = 0;
    fn_8012D588();
    if (fn_80076F54(name) == 0) {
        lbl_803EC1D0.lock = 1;
        fn_8012D588();
        return;
    }
    if (lbl_804CB700 & 0x8001) proc = 0;
    if (proc == 0) {
        fade = fn_800D8F4C();
        l = (void**)fn_80078D9C(-0x200, lbl_80368054 + 0x31, 0);
        q = l;
        for (i = 0; i < 0x80; i++) {
            *q = fn_80078D9C(-0x94, lbl_80368054 + 0x31, 0);
            q++;
        }
        n = fn_8010BED8(name, mode, (DE**)l);
        if (n > 0) {
            w = l;
            for (k = 0; k < n; k++) {
                e = (DEnt2*)*w;
                fn_8010D184((DE*)e, mode, (void*)n, l);
                u = e->unit;
                if (u) {
                    d = fade & 0xF;
                    if (d == 0) d = e->x11;
                    if ((u16)d == 0) {
                        u8* p = e->path;
                        d = 0x40;
                        while (*(const u8*)p != 0x40) {
                            d = *p++;
                        }
                    }
                    fn_800F6AEC(u, 0);
                    fn_8010316C(u, (u16)d, 0, 0, 0);
                }
                w++;
            }
        }
        q = l;
        for (j = 0; j < 0x80; j++) {
            fn_80078E24(*q);
            *q = 0;
            q++;
        }
        fn_80078E24(l);
        fn_80114D00(&lbl_803EC898);
        fn_8012D908();
        fn_801476E8();
        lbl_803EC1D0.lock = 1;
        fn_8012D588();
    } else {
        DProc* r = (DProc*)fn_80081194(lbl_803857A8, proc);
        strcpy((char*)r->file, name);
        r->x61 = mode;
        r->x66 = fn_800D8F4C();
    }
}
struct Cost { u8 pad[0x15190]; s16* cost; };
void* fn_8013B9A8(void);
int fn_8013818C(void*, int, int);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80117A0C(void*, int, int);
#else
void* fn_80117A0C(void*, int, int);
#endif
void fn_80114888(void*, int);
void fn_800672B8(void*);
#if TARGET_PC
FE10_PROTO int fn_8010B7F8(void*, int, int, ptr32<const void>, ptr32<const void>, void*);
#else
int fn_8010B7F8(void*, int, int, void*, void*, void*);
#endif
u8* fn_80116658(void*, int, int);
void fn_80116A58(void*);
static inline s16 CostAt(void* u, int x, int y, void* m, void* a, void* b) {
    if (fn_8010B7F8(u, x, y, m, a, b) == 0) return -1;
    return lbl_803EC898.cost[(s8)x + (s8)y * 0x40];
}
void* fn_8010B964(UFA* u, s8* px, u8* py, void* a, void* b) {
    int x2;
    int y2;
    void* m;
    u8* path;
    u8* w;
    u8* last;
    int x;
    int y;
    int best;
    int ox;
    int oy;
    if (u == 0) return 0;
    if (fn_8013818C(fn_8013B9A8(), *px, *(s8*)py)) return 0;
    m = fn_80117A0C(&lbl_803EC898, *px, (s8)*py);
    fn_80114888(&lbl_803EC898, 6);
    fn_800672B8(u);
    if (CostAt(u, *px, *(s8*)py, m, 0, 0) >= 0) return fn_80116658(&lbl_803EC898, *px, (s8)*py);
    path = fn_80116658(&lbl_803EC898, *px, (s8)*py);
    x = u->x;
    y = u->y;
    last = 0;
    for (w = path; *w != 0x40;) {
        switch (*w) {
        case 1: x--; break;
        case 2: x++; break;
        case 8: y--; break;
        case 4: y++; break;
        }
        w++;
        if (CostAt(u, x, y, m, a, b) >= 0) {
            *px = x;
            *py = y;
            last = w;
        }
    }
    if (last) {
        *last = 0x40;
        return path;
    }
    ox = u->x;
    oy = u->y;
    fn_80126EB0(u, *px, (s8)*py);
    fn_80114888(&lbl_803EC898, 7);
    fn_800672B8(u);
    fn_80126EB0(u, ox, oy);
    best = 10000;
    for (y2 = 0; y2 < 0x40; y2++) {
        for (x2 = 0; x2 < 0x40; x2++) {
            int c = CostAt(u, x2, y2, m, a, b);
            if (c >= 0 && c < best) {
                *px = x2;
                *py = y2;
                best = c;
            }
        }
    }
    fn_80114888(&lbl_803EC898, 6);
    if (best < 10000) return fn_80116658(&lbl_803EC898, *px, (s8)*py);
    fn_80116A58(&lbl_803EC898);
    return 0;
}

void* fn_8012D000x(void);
int fn_8010CDB4(const char* name) {
    Rec r;
    if (StOk()) {
        u8 count;
        u8 kind;
        u8 id;
        u8* s;
        int i;
        fn_8010B478(&r);
        s = Hdr(name, count, kind, id);
        if (s && count) {
            for (i = 0; i < count; i++) {
                fn_8010BCBC(&s, &r, id, kind);
                if (r.xc != 1) goto yes;
                if (GridAt(&lbl_803EC898, r.xe, r.xf)) goto yes;
                if (GridAt(&lbl_803EC898, r.x10, r.x11)) goto yes;
            }
        }
        return 0;
    }
yes:
    return 1;
}
int fn_8010D018(const char* name) {
    Rec r;
    u8 kind;
    u8 id;
    int n;
    u32 m;
    UX* nx;
    u8 count;
    u8* s;
    UX* u;
    int i;
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
    m = count;
    for (i = n; (u8)i < m; i++) fn_8010BCBC(&s, &r, id, kind);
    return (u8)n;
}
}
