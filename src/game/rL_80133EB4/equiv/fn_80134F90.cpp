/* fn_80134F90: functionally equal (regs level per tools/check_regs.py; registers differ from the original). From wip/near4.cpp. */
/* ===== fn_80134F90 (0x38C): 6 words, register swap only: the zero for the Vec stores must take r24 and the walker r23 (ours are reversed). Uses non-const statics and nested Hit inlines for slot order. Base must be checked as .rodata. ===== */
/* Map fade: applies distance fade to meshes flagged 0x4000000 from where they sit on screen. */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw off

static Vec sA = {10000.0f, 10000.0f, 10000.0f};
static Vec sB = {-10000.0f, -10000.0f, -10000.0f};
static Vec s0 = {-0.25f, -0.25f, 0.0f};
static Vec s1 = {0.25f, 0.25f, 0.0f};
static Vec s2 = {-1.0f, -1.0f, 0.0f};
static Vec s3 = {1.0f, 1.0f, 0.0f};

static inline void Put(Vec& q, const Vec& v) { q.x = v.x; q.y = v.y; q.z = v.z; }
extern "C" {
extern void* fn_8000F470(void);
extern void* fn_8000FB94(void);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void fn_803133E8(void*, Vec*, Vec*);
extern void fn_800215D4(Vec*, Vec*, Vec*, Vec*);
extern void fn_801CB3B4(Mesh*, void*, int);
extern void fn_801CB2CC(Mesh*, void*, int);

static inline int Hit(const Vec& mn, const Vec& mx, const Vec& lo0, const Vec& hi0) {
    Vec lo = lo0; Vec hi = hi0;
    if (mn.x > hi.x) return 0;
    if (mx.x < lo.x) return 0;
    if (mn.y > hi.y) return 0;
    return !(mx.y < lo.y);
}

static inline int Hit2(const Vec& mn, const Vec& mx, const Vec& lo, const Vec& hi0) {
    Vec hi = hi0;
    if (mn.x > hi.x) return 0;
    if (mx.x < lo.x) return 0;
    if (mn.y > hi.y) return 0;
    return !(mx.y < lo.y);
}
static inline int Hit3(const Vec& mn, const Vec& mx, const Vec& lo0, const Vec& hi0) {
    Vec lo = lo0;
    return Hit2(mn, mx, lo, hi0);
}
static inline int HitW(const Vec& mn, const Vec& mx, const Vec& lo0, const Vec& hi0) { return Hit3(mn, mx, lo0, hi0); }
static inline int HitX(const Vec& mn, const Vec& mx, const Vec& lo0, const Vec& hi0) { return HitW(mn, mx, lo0, hi0); }
static inline void Add(Vec* b, int& n, const Vec& v) { Put(*(Vec*)((u8*)b + n), v); n += 0xC; }
static inline void Add2(Vec* b, int n, const Vec& v) { Put(*(Vec*)((u8*)b + n), v); }
static inline int Hit4(const Vec& mn, const Vec& mx, Vec hi, Vec lo) {
    if (mn.x > hi.x) return 0;
    if (mx.x < lo.x) return 0;
    if (mn.y > hi.y) return 0;
    return !(mx.y < lo.y);
}
#define Hit5(a, b, c, d) Hit4(a, b, d, c)
static inline int Hit6(const Vec& mn, const Vec& mx, Vec lo, Vec hi) {
    if (mn.x > hi.x) return 0;
    if (mx.x < lo.x) return 0;
    if (mn.y > hi.y) return 0;
    return !(mx.y < lo.y);
}
static inline void Scan(MapModel*& w, Vec* box, Vec& v) {
    /*P*/
    int k;
    int n;
    u32 zero;
    MapModel* ww;
/*E*/
    ww = w;
    zero = 0;
    n = 0;
    for (k = 0; k < 4; k++) {
        Mesh* s = ww->x3c[0];
        if (s == 0) break;
        *(u32*)&v.x = zero;
        *(u32*)&v.y = zero;
        *(u32*)&v.z = zero;
        fn_80312DB4(&s->group, &v, &v);
        fn_803133E8(fn_8000FB94(), &v, &v);
        if (!(v.z > 0.0f) && !(v.z < -1.0f)) {
            Put(*(Vec*)((u8*)box + n), v); n = n + sizeof(Vec);
        }
        ww = (MapModel*)((u8*)ww + 4);
    }
}
void fn_80134F90(MapModel* mm) {
    /*P*/
    void* cam;
    Mesh* m;
    int i;
    MapModel* w;
/*E*/
    Vec box[4];
    Vec v;
    Vec mx;
    Vec mn;
    if (mm->x04 == 0) return;
    if (mm->xb1 == 0) return;
    fn_8000F470();
    cam = mm->x10;
    w = mm;
    Scan(w, box, v);
    m = mm->mesh;
    {
    f32 zero, mone, c075, c05, c025;
    c075 = -0.075f;
    c05 = -0.05f;
    c025 = -0.025f;
    mone = -1.0f;
    i = 0;
    zero = 0.0f;
    for (; i < mm->nMesh; i++, m++) {
        if (m->flags & 0x20) continue;
        u32 f = m->group->flags;
        if (f & 0x10) continue;
        if (!(f & 0x4000000)) continue;
        fn_800215D4((Vec*)&m->minx, (Vec*)&m->maxx, &mn, &mx);
        f32 d = mn.z;
        if (d < mone) d = mone;
        if (mx.z > zero) d = -1.0f;
        if (!Hit3(mn, mx, s0, s1) && d < c05) d = c05;
        if (!HitX(mn, mx, s2, s3) && d < c025) d = c025;
        if (d >= c025) fn_801CB3B4(m, cam, 0);
        if (d >= c05) fn_801CB3B4(m, cam, 0x10);
        if (d <= c075) fn_801CB2CC(m, cam, 0x10);
    }
    }
}
}

