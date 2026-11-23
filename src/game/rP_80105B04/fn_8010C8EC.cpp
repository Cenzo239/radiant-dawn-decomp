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
    u8 x60;
    u8 pad61[7];
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
void fn_8010D184(DEnt* e, int k, void* a, void* b);
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
int fn_8010C8EC(const char* name, s8 layer) {
    Rec r;
    u8 count, kind, id;
    u8* s;
    int i;
    USlot* u;
    fn_8010B478(&r);
    lbl_803EC1D0.lock = 0;
    lbl_803EC1D0.n = 0;
    fn_8012D588();
    s = Hdr(name, count, kind, id);
    if (s) {
        for (i = 0; i < count; i++) {
            fn_8010BCBC(&s, &r, id, kind);
            if (layer >= 0) r.xc = layer;
            u = fn_8012CE54(r.p4);
            if (u == 0) {
                Spawn(&r);
            } else {
                fn_8011E048(u, &r);
            }
        }
    }
    lbl_803EC1D0.lock = 1;
    fn_8012D588();
    return 1;
}
int fn_8010CC50(const char* name, s8* ox, s8* oy) {
    u8 count, kind, id;
    u8* s = Hdr(name, count, kind, id);
    Rec r;
    if (s && count) {
        int sx, sy, minx, miny, maxx, maxy, i;
        fn_8010B478(&r);
        sx = 0;
        sy = 0;
        minx = 1000;
        miny = 1000;
        maxx = -1000;
        maxy = -1000;
        for (i = 0; i < count; i++) {
            fn_8010BCBC(&s, &r, id, kind);
            sx += r.x10;
            sy += r.x11;
            if (minx > r.x10) minx = r.x10;
            if (miny > r.x11) miny = r.x11;
            if (maxx < r.x10) maxx = r.x10;
            if (maxy < r.x11) maxy = r.x11;
        }
        *ox = sx / count;
        *oy = sy / count;
        return 1;
    }
    return 0;
}
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
struct MGrid { u8 pad[0x200D]; u8 g[64][64]; };
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
void fn_8010CA94(const char* name) {
    Rec r;
    u8 count, kind, id;
    u8* s;
    int i;
    fn_8010B478(&r);
    s = Hdr(name, count, kind, id);
    if (s) {
        for (i = 0; i < count; i++) {
            UFull* u;
            fn_8010BCBC(&s, &r, id, kind);
            u = FindByTag(r.a0);
            if (u) fn_800F6AEC(u, 0);
        }
    }
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
int fn_8010C200(DFile* f) {
    Rec r;
    UX* u;
    UX* nx;
    fn_8010B478(&r);
    fn_8010BCBC(&f->cur, &r, f->xd, f->xf);
    u = (UX*)fn_8012CE54(r.p4);
    if (u == 0 && (f->xc & 0x20)) {
        u = (UX*)Spawn(&r);
        fn_8011FE74((USlot*)u, 5);
    }
    if (u) {
        switch (u->side->idx) {
        case 5:
        case 0:
            if ((f->xc & 0x10) || fn_8011B77C(u->skills, lbl_804CA4D8)) {
                fn_8011FE74((USlot*)u, 0);
                fn_8011E048((USlot*)u, &r);
                goto ok;
            }
            break;
        }
    }
    u = (UX*)lbl_804CB814[5].head;
    while (u) {
        nx = u->next;
        if (fn_8011B77C(u->skills, lbl_804CA4D8) == 0 && !(u->fl & 0x200000)) {
            fn_8011FE74((USlot*)u, 0);
            u->x37E = r.a0;
            goto ok;
        }
        u = nx;
    }
    f->unit = 0;
    return 0;
ok:
    fn_80126EB0(u, r.xe, r.xf);
    fn_800F39DC(u);
    fn_800F3F08(u, 0);
    fn_80129214(u, &r);
    f->unit = (USlot*)u;
    return 1;
}
int fn_8010D018(const char* name);
int fn_8010CF20(const char* name, s8* out) {
    Rec r;
    u8 count, kind, id;
    u8* s = Hdr(name, count, kind, id);
    int i;
    if (s == 0) return 0;
    fn_8010B478(&r);
    for (i = 0; i < count; i++) {
        fn_8010BCBC(&s, &r, id, kind);
        out[0] = r.x10;
        out[1] = r.x11;
        out += 2;
    }
    *out = -1;
    return count;
}
void fn_8010D684(DProc* p);
void fn_8010D770(DProc* p);
#pragma use_lmw_stmw off
extern char lbl_80368054[];
extern u8 lbl_803CAB38[];
void* fn_80078D9C(int n, const char* s, int k);
int fn_8010BED8(void* f, int k, void* list);
void fn_80083DC4(void* p, int k);
void fn_800620A8(void* g, f32 x, f32 y);
struct DProc2 {
    u8 pad[0x30];
    char file[0x31];
    u8 x61, x62, idx, n, t65;
    u16 x66;
    void** list;
};
void fn_8010D3BC(DProc2* p) {
    s8 ox, oy;
    int i;
    void** l;
    void** q;
    l = (void**)fn_80078D9C(-0x200, lbl_80368054 + 0x31, 0);
    q = l;
    for (i = 0; i < 0x80; i++) {
        *q = fn_80078D9C(-0x94, lbl_80368054 + 0x31, 0);
        q++;
    }
    p->list = l;
    p->n = fn_8010BED8(p->file, p->x61, l);
    p->idx = 0;
    p->x62 = 0;
    if (p->n == 0) {
        fn_80083DC4(p, 0x63);
    } else if ((p->x66 & 0x40) && fn_8010CDB4((const char*)p->file)) {
        fn_8010CC50((const char*)p->file, &ox, &oy);
        fn_800620A8(lbl_803CAB38, ox, oy);
    }
}
void fn_8010D574(DProc* p) {
    int i;
    if ((int)p->t65++ <= 0x2A30) {
        for (i = 0; i < p->n; i++) {
            if (p->list[i]->unit && fn_800F69E4(p->list[i]->unit) == 0) return;
        }
    }
    fn_80083B78(p);
}
void fn_8010D608(DProc* p) {
    int i;
    for (i = 0; i < p->n; i++) {
        if (p->list[i]->unit) fn_800F6AEC(p->list[i]->unit, 0);
    }
    fn_80083B78(p);
}
}
