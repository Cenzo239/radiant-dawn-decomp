/* Round 21 draft of fn_800DC824, level `other`, now COMPLETE (the r20 file lacked the
   camera look-at block). What differs from the original: three `frsp`
   instructions (105 vs 108 instructions in fn_800DC824). The original copies the
   saved point to cam+0x44 and then stores frsp(x), frsp(y), frsp(z) to
   cam+0x38; this compiler drops the float->double->float round trip for every
   spelling tried (double parameters, long double, a double-returning inline,
   opt_propagation off, a double temporary struct). frsp of a single-precision
   value is the identity, so behaviour is the same. */
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
void fn_800DEF6C(MProc* p);

void fn_800DF250(MProc* p);

void fn_800E0024(TileFx* p);

int fn_800E02FC(HideProc* p, HideArg* a);

int fn_800E0394(int x, int y);

int fn_800E0604(int ia, int ib);


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

int fn_800E07B0(int id, int dir);

#pragma use_lmw_stmw off

int fn_800E0A40(int ia, int ib);

int fn_800E0CDC(int id, u8 r, u8 g, u8 b);

}

#pragma use_lmw_stmw off
/* ---- from rK_800CF8BC/wip/fn_800DC770.cpp ---- */
extern "C" {
/* Near misses from fn_800DC770.cpp. Same declarations as that file.
 * fn_800DC770 (CopyMapCamera): 5 words, f0/f2 colouring of two float loads.
 * fn_800DC824 (PastMapCamera), fn_800DC9D4 (InstantPastMapCamera): the look-at
 *   copy wants `lfs f1; frsp f3,f1; stfs f1,0x44; stfs f3,0x38`. No spelling tried
 *   emits the frsp, so they are 12 bytes short. camSet below is empty on purpose:
 *   its body was being varied by script.
 * fn_800DFD3C: 44 words, only the FIFO base: lis 0xCC01 should be r6 above the
 *   four colour bytes, but it lands in r5 and the alpha byte takes r6. */
#define WGF (*(volatile f32*)0xCC008000)
#define WGB (*(volatile u8*)0xCC008000)


/* Look-at: the point goes to +0x44 and, through a double-typed path, to +0x38. */
static inline void vset(Vec* d, f64 x, f64 y, f64 z) { d->x = x; d->y = y; d->z = z; }
static inline void camLook(Cam* c, const Vec& v) {
    c->v44 = v;
    vset(&c->v38, v.x, v.y, v.z);
}

#define RESTORE_A(c, s)                     \
    c->x4 = s->x4;                          \
    c->x10 = c->x4;                         \
    c->x8 = s->x8;                          \
    c->x14 = c->x8;                         \
    fn_8012F580(c, s->xC);                  \
    {                                       \
        Vec t = s->v;                       \
        camLook(c, t);                      \
    }                                       \
    fn_800620A8(&lbl_803CAB38, s->tx, s->ty);

static inline void restoreB(Cam* c, SavedCam* s) {
    c->x4 = s->x4;
    c->x8 = s->x8;
    c->xC = s->xC;
    {
        Vec t = s->v;
        c->v44 = t;
    }
    fn_800620A8(&lbl_803CAB38, s->tx, s->ty);
}

int fn_800DC824() {
    if (lbl_804CB700 & 0x8001) {
        if (lbl_803E8F78.valid) {
            Cam* c = fn_8012FCD0();
            if (c) {
                SavedCam* s = &lbl_803E8F78;
                RESTORE_A(c, s)
            }
        }
    } else {
        if (lbl_803E8F78.valid) {
            Cam* c = fn_8012FCD0();
            if (c) {
                restoreB(c, &lbl_803E8F78);
            }
        }
    }
    return 1;
}

static inline void pos3(f32 x, f32 y, f32 z) {
    WGF = x;
    WGF = y;
    WGF = z;
}
static inline void col4(TileFx* p) {}
}
