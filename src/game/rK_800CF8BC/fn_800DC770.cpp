/* Event commands not reached in fn_800D7D74.cpp: map camera save and restore,
 * rescue/drop/child-send, hide point, tile highlight and post effect colour. */
#include "game/rK_800CF8BC/types.h"

struct UColor {
    u8 r, g, b, a;
};
struct Mtx34 {
    f32 m[12];
};
struct Cam {
    u8 pad0[4];
    f32 x4, x8, xC;
    f32 x10, x14;
    u8 pad18[0x20];
    Vec v38;
    Vec v44;
};
struct SavedCam {
    u8 valid;
    u8 pad1[3];
    f32 x4, x8, xC;
    Vec v;
    s16 tx;
    s16 ty;
};
struct CurData {
    u8 pad[0x93C];
    f32 x;
    f32 y;
};
struct UX {
    u8 pad0[0x28];
    u8 o28[0x9C];
    s16 xC4;
    u8 padC6[0x32];
    UX* rescue;  /* 0xF8 */
    u8 padFC[6];
    s8 x;        /* 0x102 */
    s8 y;        /* 0x103 */
    u8 pad104[8];
    u32 fl;      /* 0x10C */
    u8 pad110[0x3F0 - 0x110];
};
struct MData {
    u8 pad[0x18];
    u32 flags;
    Vec pos;
    u8 pad28[0x40];
    Mtx34 m68;
    u8 pad98[0xC];
    UX* xA4;
    int xA8;
    int xAC;
};
struct MProc {
    u8 pad[0x30];
    MData* d;
};
struct XForm {
    u8 pad[0xD4];
    f32 xD4;
    f32 xD8;
};
struct HideArg {
    f32 x, y, z;
};
struct HideProc {
    u8 pad[0x30];
    s16 x;
    s16 y;
};
struct TileFx {
    u8 pad[0x30];
    s16 x;       /* 0x30 */
    s16 y;       /* 0x32 */
    u8 r, g, b, a; /* 0x34 */
    int t;       /* 0x38 */
    u8 on;       /* 0x3C */
    u8 pad3D[3];
    f32 h[4];    /* 0x40 */
};
struct Pair {
    u8 pad[0x54];
    UX* a;
    UX* b;
    UX* c;
};
struct PostD {
    u8 pad[0x2B];
    UColor c;
};
struct PostObj {
    u8 pad[0x30];
    PostD* d;
};

extern SavedCam lbl_803E8F78;
extern CurData lbl_803CAB38;
extern u32 lbl_804CB700;
extern UX* lbl_804CB810;
extern u8 lbl_803EC898[];
extern u8 lbl_80384030[];
extern u8 lbl_80384188[];
extern u8 lbl_803841E8[];
extern u8 lbl_80384200[];

extern "C" {
Cam* fn_8012FCD0();
void fn_8012F580(Cam*, f32);
void fn_800620A8(CurData*, f32, f32);
void fn_800893E4(void*, void*, void*);
void fn_80081A90(void*);
void fn_80083B78(void*);
PostObj* fn_8017C2B0(u16);
XForm* fn_8000F470(MProc*);
void fn_800E48C8(MProc*, const Vec*);
void fn_800E49AC(MProc*, f32);
int fn_8011F5B4(UX*);
void* fn_800078E4(void*, int);
void fn_80007860(void*, int, Mtx34*);
void fn_8000F328(void*, Mtx34*);
void fn_80312378(const Mtx34*, const Mtx34*, Mtx34*);
void fn_80312344(const Mtx34*, Mtx34*);
int fn_800F432C(UX*, int, Vec*);
f32 fn_8001EF30(f32, f32, f32, f32);
f32 fn_8001EF44(int, int, f32, f32);
f32 fn_801146A8(void*, s8, s8, int);
void fn_800106AC(int, void*, void*);
extern u8 fn_800DFD3C[];
void fn_803031CC();
void fn_80302B80(int, int);
void fn_80303200(int, int, int, int, int);
void fn_80021B2C(int);
void fn_80021A08(int, int, int, int, int, int, int);
void fn_80021BF4(int);
void fn_80021EF8(int, int);
void fn_80021CB4(int, int, int, int);
void fn_80021C34(int);
void fn_80021F7C(int, int, int, int);
void fn_80021B68(int);
void fn_803128AC(Mtx34*, f32, f32, f32);
Mtx34* fn_8000FB88();
void fn_80307E48(Mtx34*, int);
void fn_80021784(int);
void fn_80021BA4(int, int, int, int);
void fn_80304314(int, int, int);
void fn_80011838(int);
f32 fn_800FB08C(UX*, UX*);
void fn_8011E294(UX*, UX*);
void fn_800F39DC(UX*);
void fn_80114D00(void*);
void* fn_80083B84(void*);
void* fn_800A237C();
void* fn_8009E898();
void* fn_80081050(void*, void*);
void* fn_80103684(UX*, UX*, void*);
void fn_8011EB4C(UX*, s8*, s8*);
void fn_8011E300(UX*, int, int, int);
void fn_801037D4(UX*, int, int, int, int, void*);
void fn_800F3F38(UX*, u8);
void fn_801036D0(UX*, UX*, int, int, void*);
void* fn_80103778(UX*, UX*, UX*, void*);

static inline UX* unitGet(u8 id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
static inline void* Get30() {
    void* p = fn_80083B84(lbl_80384030);
    if (p) {
        return p;
    }
    {
        void* q = fn_800A237C();
        if (!q) {
            q = fn_8009E898();
        }
        return fn_80081050(lbl_80384030, q);
    }
}

void fn_800DEF6C(MProc* p) {
    /*P*/
    u8* o;
    u32 has;
    UX* u;
    void* n;
    int k;
/*E*/
    MData* d = p->d;
    u = d->xA4;
    k = d->xA8;
    has = (u32)(-d->xAC | d->xAC) >> 31;
    if (u && fn_8011F5B4(u)) {
        if (has) {
            Mtx34 a;
            Mtx34 b;
            o = u->o28;
            n = fn_800078E4(o, k);
            fn_80007860(o, k, &a);
            fn_8000F328(n, &b);
            fn_80312378(&a, &b, &a);
            fn_80312344(&a, &p->d->m68);
            p->d->flags |= 0x10000;
        } else {
            Vec v;
            if (fn_800F432C(u, k, &v)) {
                Vec t = v;
                fn_800E48C8(p, &t);
            }
            fn_800E49AC(p, 0.015625f * u->xC4);
        }
    }
}

void fn_800DF250(MProc* p) {
    XForm* x = fn_8000F470(p);
    Vec t = p->d->pos;
    t.x = x->xD4;
    t.y = x->xD8;
    {
        Vec a = t;
        fn_800E48C8(p, &a);
    }
}

void fn_800E0024(TileFx* p) {
    int t = p->t + 1;
    u8 on = p->on;
    p->t = t;
    if (on) {
        int a = fn_8001EF30(0.0f, 96.0f, 60.0f, t);
        p->a = a;
        if (p->t >= 0x3C) {
            p->on = 0;
        }
    } else {
        p->t = t % 0x78;
        {
            int a = fn_8001EF44(0x78, p->t, 32.0f, 96.0f);
            p->a = a;
        }
    }
    p->h[0] = fn_801146A8(lbl_803EC898, p->x, p->y, 0);
    p->h[1] = fn_801146A8(lbl_803EC898, p->x, p->y, 1);
    p->h[2] = fn_801146A8(lbl_803EC898, p->x, p->y, 2);
    p->h[3] = fn_801146A8(lbl_803EC898, p->x, p->y, 3);
    fn_800106AC(3, fn_800DFD3C, p);
}

int fn_800E02FC(HideProc* p, HideArg* a) {
    if (a->x < 0.0f || ((f32)p->x == a->x && (f32)p->y == a->y)) {
        if (a->z < 0.0f) {
            fn_80081A90(p);
        } else {
            fn_80083B78(p);
        }
    }
    return 0;
}

int fn_800E0394(int x, int y) {
    HideArg a = {(f32)x, (f32)y, 1.0f};
    if (lbl_804CB700 & 0x8001) {
        a.z = -1.0f;
    }
    fn_800893E4(lbl_80384188, fn_800E02FC, &a);
    return 0;
}

int fn_800E0604(int ia, int ib) {
    UX* a = unitGet(ia);
    UX* b = unitGet(ib);
    if (!a || !fn_8011F5B4(a) || (a->fl & 6)) {
        return 0;
    }
    if (!b || !fn_8011F5B4(b) || (b->fl & 6)) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        int f = fn_800FB08C(a, b);
        a->xC4 = 64.0f * f;
        fn_8011E294(a, b);
        fn_800F39DC(b);
        fn_80114D00(lbl_803EC898);
    } else {
        Pair* q = (Pair*)fn_80081050(lbl_803841E8, fn_80103684(a, b, Get30()));
        q->a = a;
        q->b = b;
    }
    return 1;
}

static inline int dirX(u8 d) {
    switch (d) {
    case 1:
        return -1;
    case 2:
        return 1;
    }
    return 0;
}
static inline int dirY(u8 d) {
    switch (d) {
    case 4:
        return 1;
    case 8:
        return -1;
    }
    return 0;
}

#pragma use_lmw_stmw on
int fn_800E07B0(int id, int dir) {
    UX* u = unitGet(id);
    UX* r;
    if (!u || !fn_8011F5B4(u) || !(u->fl & 2)) {
        return 0;
    }
    r = u->rescue;
    if (dir < 0) {
        s8 x;
        s8 y;
        fn_8011EB4C(u, &x, &y);
        fn_8011E300(u, x, (s8)*(u8*)&y, 0);
        if (lbl_804CB700 & 0x8001) {
            fn_800F39DC(r);
        } else {
            fn_801037D4(r, r->x, r->y, x, y, Get30());
        }
    } else {
        int nx = (s8)(*(u8*)&u->x + dirX(dir));
        int ny = (s8)(*(u8*)&u->y + dirY(dir));
        fn_8011E300(u, nx, ny, 0);
        if (lbl_804CB700 & 0x8001) {
            fn_800F3F38(u, dir);
            fn_800F3F38(r, dir);
            fn_800F39DC(r);
        } else {
            fn_801036D0(u, r, nx, ny, Get30());
        }
    }
    fn_80114D00(lbl_803EC898);
    return 1;
}
#pragma use_lmw_stmw off

int fn_800E0A40(int ia, int ib) {
    UX* a = unitGet(ia);
    UX* b = unitGet(ib);
    UX* c;
    if (!a || !fn_8011F5B4(a) || !(a->fl & 2)) {
        return 0;
    }
    if (!b || !fn_8011F5B4(b) || (b->fl & 6)) {
        return 0;
    }
    c = a->rescue;
    fn_8011E300(a, a->x, (s8)*(u8*)&a->y, 0);
    if (lbl_804CB700 & 0x8001) {
        int f = fn_800FB08C(a, b);
        a->xC4 = 64.0f * f;
        fn_8011E294(b, c);
        fn_80114D00(lbl_803EC898);
    } else {
        Pair* q = (Pair*)fn_80081050(lbl_80384200, fn_80103778(a, b, c, Get30()));
        q->a = a;
        q->b = b;
        q->c = c;
    }
    return 1;
}

int fn_800E0CDC(int id, u8 r, u8 g, u8 b) {
    PostObj* o = fn_8017C2B0((u16)id);
    if (o) {
        UColor c = {r, g, b, 0xFF};
        PostD* d = o->d;
        UColor t = c;
        d->c.r = t.r;
        d->c.g = t.g;
        d->c.b = t.b;
        d->c.a = t.a;
        return 1;
    }
    return 0;
}
}
