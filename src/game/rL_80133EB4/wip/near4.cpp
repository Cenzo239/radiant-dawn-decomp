/* Near misses from round 14. */

/* ===== fn_80143908 (0x480): 33 lines, all in the output loop. Original keeps a dead `srawi r3,r9,2` (y>>2) hoisted in the outer loop, which shifts r5/r7/r8/r11; every form tried folds it. ===== */
/* Water surface: 32x32 height field step, written into the tiled IA8 texture. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off

struct Ripple {
    u8 pad0[0x48];
    u8* x48;
    u8* x4c;
    f32* x50;
    f32* x54;
    f32* x58;
    f32* x5c;
};
struct MM63 {
    u8 pad0[0x63];
    u8 x63;
};
extern "C" {
extern MM63* fn_8013B9A8(void);
extern void DCFlushRange(void*, u32);

void fn_80143908(Ripple* r) {
    /*P*/
    MM63* mm;
    int x;
    int y;
    /*E*/
    f32 a[0x400];
    f32 b[0x400];
    if (r->x48 == 0) return;
    mm = fn_8013B9A8();
    if (mm == 0) return;
    if (mm->x63 == 0) return;
    for (y = 0; y < 32; y++) {
        for (x = 0; x < 32; x++) {
            int i = x + y * 32;
            a[i] = r->x50[i];
            b[i] = r->x54[i];
        }
    }
    DCFlushRange(a, 0x1000);
    DCFlushRange(b, 0x1000);
    f32 k = 1.0f / (f32)mm->x63;
    for (y = 0; y < 32; y++) {
        for (x = 0; x < 32; x++) {
            f32 ax = 0.0f;
            f32 ay = ax;
            int ym = y - 1;
            int i = x + y * 32;
            if (ym < 0) ym = 31;
            int yp = y + 1;
            if (yp > 31) yp = 0;
            int xm = x - 1;
            if (xm < 0) xm = 31;
            int xp = x + 1;
            if (xp > 31) xp = 0;
            ax += k * a[x + ym * 32];
            ay += k * b[x + ym * 32];
            ax += k * a[xp + y * 32];
            ay += k * b[xp + y * 32];
            ax += k * a[xm + y * 32];
            ay += k * b[xm + y * 32];
            ax += k * a[x + yp * 32];
            ay += k * b[x + yp * 32];
            ax -= 4.0f * (k * a[i]);
            ay -= 4.0f * (k * b[i]);
            r->x58[i] += ax;
            r->x5c[i] += ay;
            r->x50[i] += k * r->x58[i];
            r->x54[i] += k * r->x5c[i];
            if (x == 0 || x == 31) r->x50[i] = 0.0f;
            if (y == 0 || y == 31) r->x54[i] = 0.0f;
        }
    }
    u8* old = r->x48;
    u8* tex = r->x4c;
    for (y = 0; y < 32; y++) {
        
        for (x = 0; x < 32; x++) {
            int i = x + y * 32; u8 h = 127.0f * (1.0f + r->x50[i]); u8 v = 127.0f * (1.0f + r->x54[i]); u8* d = tex + ((y >> 2) * 128 + (y & 3) * 4 + ((x >> 2) * 16 + (x & 3))) * 2; d[0] = h; d[1] = v;
        }
    }
    DCFlushRange(tex, 0x800);
    r->x4c = old;
    r->x48 = tex;
}
}

/* ===== fn_80136E74 (0x8B0): masked diff is 0, 100 lines of register ranks. The parameter must rank near the bottom (r22, wanted) but always takes r31 here, and hoisted 0, 6 and the map pointer must then move up. Wrappers, inlines and named copies do not move it. ===== */
/* Builds the display list of the terrain outline from the tile heights. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off

struct TileDef { u8 pad0[7]; u8 x7; u8 pad8[0x14 - 8]; s8 x14[23]; };
struct Tile { u8 pad0[8]; TileDef* def; };
struct Map {
    u8 pad0[8];
    s8 x0, y0, x1, y1;
    u8 padc[0x100 - 0xC];
};
struct Obj {
    u8 pad0[0xBC];
    void* dl;
    u32 dlSize;
};
extern "C" {
extern Map lbl_803EC898;
extern char lbl_803694D4[];
extern void* fn_80078D9C(int, char*, int);
extern void* fn_80078CCC(u32, char*, int);
extern void fn_80078E24(void*);
extern Tile* fn_801181E8(Map*, int, int);
extern f32 fn_801146A8(Map*, int, int, int);
extern void DCInvalidateRange(void*, u32);
extern void DCFlushRange(void*, u32);
extern void fn_803079FC(void*, u32);
extern u32 fn_80307AAC(void);
extern void fn_80304314(int, int, int);
extern void* memcpy(void*, const void*, u32);

static inline void V(int x, int y, f32 h) {
    volatile f32* fifo = (volatile f32*)0xCC008000;
    *fifo = (f32)x;
    *fifo = (f32)y;
    *fifo = h;
}
static inline s16 Lv(TileDef* d, int j) {
    s8 v = d->x14[j];
    return v < 0 ? 0x7FFF : v;
}

void fn_80136E74(Obj* o) {
    /*P*/
    int k2;
    int xx;
    int yy;
    u8* b;
    u8* q;
    int x;
    u8* p;
    int ky;
    u8* d;
    int y;
    Map* m2;
    Map* map;
/*E*/
    b = (u8*)fn_80078D9C(-0x4000, lbl_803694D4 + 0x103, 0);
    map = &lbl_803EC898;
    f32 lim = 0.01f;
    y = map->y0;
    ky = y * 0x80;
    for (; y < map->y1; y++) {
        x = map->x0;
        p = x + (b + ky);
        for (; x < map->x1; x++) {
            *p = 0;
            TileDef* t = fn_801181E8(&lbl_803EC898, (s8)x, (s8)y)->def;
            if ((t->x7 & 1) == 0) {
                for (int j = 0; j < 23; j++) {
                    if (Lv(t, j) != 0x7FFF) goto F;
                }
                goto N;
                F:
                    {
                        *p = 6;
                        if (x == map->x0) {
                            *p |= 1;
                        } else if (p[-1] == 0) {
                            *p |= 1;
                        } else {
                            f32 a = fn_801146A8(map, (s8)(x - 1), (s8)y, 1);
                            f32 dx = fn_801146A8(map, (s8)x, (s8)y, 0) - a;
                            a = fn_801146A8(map, (s8)(x - 1), (s8)y, 3);
                            f32 dy = fn_801146A8(map, (s8)x, (s8)y, 2) - a;
                            if (dx * dx + dy * dy >= lim) *p |= 1;
                        }
                        if (y == map->y0) {
                            *p |= 8;
                        } else if (p[-0x80] == 0) {
                            *p |= 8;
                        } else {
                            f32 a = fn_801146A8(map, (s8)x, (s8)(y - 1), 2);
                            f32 dx = fn_801146A8(map, (s8)x, (s8)y, 0) - a;
                            a = fn_801146A8(map, (s8)x, (s8)(y - 1), 3);
                            f32 dy = fn_801146A8(map, (s8)x, (s8)y, 1) - a;
                            if (dx * dx + dy * dy >= lim) *p |= 8;
                        }
                    }
                N: ;
            }
            p++;
        }
        ky += 0x80;
    }
    d = (u8*)fn_80078D9C(-0x40000, lbl_803694D4 + 0x103, 0);
    DCInvalidateRange(d, 0x40000);
    fn_803079FC(d, 0x40000);
    {
    yy = map->y0;
    m2 = &lbl_803EC898;
    k2 = yy * 0x80;
    for (; yy < m2->y1; yy++) {
        xx = m2->x0;
        q = xx + (b + k2);
        for (; xx < m2->x1; xx++) {
            if (*q) switch (*q) {
            case 6:
                fn_80304314(0xB0, 0, 3);
                V(xx + 1, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 1));
                V(xx + 1, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 3));
                V(xx, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 2));
                break;
            case 7:
                fn_80304314(0xB0, 0, 4);
                V(xx + 1, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 1));
                V(xx + 1, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 3));
                V(xx, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 2));
                V(xx, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 0));
                break;
            case 14:
                fn_80304314(0xB0, 0, 4);
                V(xx, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 0));
                V(xx + 1, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 1));
                V(xx + 1, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 3));
                V(xx, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 2));
                break;
            case 15:
                fn_80304314(0xB0, 0, 5);
                V(xx, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 0));
                V(xx + 1, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 1));
                V(xx + 1, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 3));
                V(xx, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 2));
                V(xx, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 0));
                break;
            }
            q++;
        }
        k2 += 0x80;
    }
    }
    u32 n = fn_80307AAC();
    if (o->dl) {
        fn_80078E24(o->dl);
        o->dl = 0;
    }
    o->dl = fn_80078CCC(n, lbl_803694D4 + 0x103, 0);
    o->dlSize = n;
    DCFlushRange(o->dl, n);
    memcpy(o->dl, d, n);
    DCFlushRange(o->dl, n);
    fn_80078E24(d);
    fn_80078E24(b);
}
}

/* ===== fn_80144324 (0x194): structure only, about 60 lines. Wants hoisted addi r9,r8,r7 = &tab[0], &tab[1], &tab[3], temporaries at 0x2C/0x38 copied by value to 0x8/0x14/0x20. ===== */
/* Cloud layer scroll: moves the texture offset and rebuilds its projection matrix. */
#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct Mtx44 { f32 m[12]; };
struct Cloud {
    u8 pad0[0x30];
    f32 x30, x34;
    u8 pad38[4];
    Mtx x3c;
};
struct WxP {
    u8 pad0[0x30];
    u8 x30;
    u8 pad31[0x3C - 0x31];
    f32 x3c;
    u8 pad40[8];
    f32 x48, x4c;
};
extern "C" {
extern const Vec lbl_80369A08[4];
extern u8 lbl_80386540[];
extern WxP* fn_80083B84(void*);
extern int fn_80068D74(void);
extern void fn_80312AC0(Mtx*, Vec*, Vec*, Vec*);
extern void fn_80312D2C(Mtx*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80312378(Mtx*, Mtx*, Mtx*);

static inline Vec Mk(const Vec& s, f32 x, f32 y) { Vec t = s; t.x = x; t.y = y; return t; }
static inline void Look(Mtx* m, Vec t, Vec e, Vec u) { fn_80312AC0(m, &e, &u, &t); }

static inline void Body(Cloud* c, WxP* w, const Vec& a, const Vec& b, const Vec& u) {
    Mtx mv;
    Mtx mp;
    f32 k;
    {
    c->x30 += w->x48 * w->x3c;
    k = 32.0f;
    //VIEW
    }
    fn_80312D2C(&mp, -k, k, -k, k, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_80312378(&mp, &mv, &c->x3c);
}
void fn_80144324(Cloud* c) {
    const Vec* tab = lbl_80369A08;
    WxP* w = fn_80083B84(lbl_80386540);
    if (w->x30 == 0) return;
    if (fn_80068D74() == 0) return;
    Body(c, w, tab[0], tab[1], tab[3]);
}
}

/* ===== fn_80138FF8 (0x96C): structure nearly right (2 lines in the adjacent-door search), about 120 lines of ranks. Target: hoists r31-r29, off0 r25, m r23, i r21, x r20, y r19, mm r18; the per-site loop counters and offsets (r22, r24) must rank above x, y and i. ===== */
/* Replays saved map events after a load: doors, roofs, breakable blocks and other switched meshes. */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw off

struct MapEv { s8 x, y; u8 kind; u8 pad[5]; };
struct MapEvVec { MapEv* p; u8 pad4[0x10]; };
struct Emit { u8 pad0[0x14]; Mesh* mesh; };

extern "C" {
extern MapEvVec lbl_803CB770;
extern u8 lbl_803EC898[];
extern int fn_800660E8(MapEvVec*);
extern void fn_80065E4C(MapEv*, int);
extern int fn_801CA274(Mesh*, int, int);
extern void fn_801CA300(Mesh*);
extern void fn_801CA4FC(Mesh*, int);
extern void fn_801CA444(Mesh*, int);
extern void fn_801CA3E4(Mesh*, int);
extern void fn_801CA33C(Mesh*, int, int);
extern int fn_80135C44(MapModel*, Mesh*, Mesh**, int);
extern int fn_8013599C(MapModel*, int, int, u32, u32, Mesh**);
extern void fn_80272624(Emit*, f32);
extern void fn_801379F8(MapModel*, int);
extern void fn_80114D00(void*);
extern void fn_8013A638(MapModel*);
extern void fn_8012D908(void);

#define FIND(COND, M, I, O, X, Y, L) \
    for (I = mm->nMesh - 1, O = I * 0xD0; I >= 0; O -= 0xD0, I--) { \
        M = (Mesh*)((u8*)mm->mesh + O); \
        u32 f = M->group->flags; \
        if (COND) { switch (fn_801CA274(M, X, Y)) { case 0: break; default: goto L; } } \
    } \
    M = 0; \
L:
#define A(K) ((f & 0x10) == 0 && (f & K) == K)
#define B(K) ((f & K) == K)
static inline int DirBit(int i) {
    switch (i) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    default: return 0x40;
    }
}
static inline int DirX(int d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    default: return 0;
    }
}
static inline int DirY(int d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    default: return 0;
    }
}
static inline Emit* FindEmit(MapModel* mm, Mesh* m) {
    if (m) {
        for (int i = 0; i < 16; i++) {
            if (((Emit*)&mm->lights[i])->mesh == m) return (Emit*)&mm->lights[i];
        }
    }
    return 0;
}
void fn_80138FF8(MapModel* mm) {
    /*P*/
    int ii1;
    int oo1;
    Mesh* mm1;
    int ii2;
    int oo2;
    Mesh* mm2;
    int ii3;
    int oo3;
    Mesh* mm3;
    int ii4;
    int oo4;
    Mesh* mm4;
    int ii5;
    int oo5;
    Mesh* mm5;
    int ii6;
    int oo6;
    Mesh* mm6;
    int ii7;
    int oo7;
    Mesh* mm7;
    int ii8;
    int oo8;
    Mesh* mm8;
    int ii9;
    int oo9;
    Mesh* mm9;
    int ii10;
    int oo10;
    Mesh* mm10;
    int ii11;
    int oo11;
    int ii12;
    int oo12;
    Mesh* mm12;
    int x3;
    int i3;
    Mesh* m2;
    int i2;
    int off2;
    int off0;
    int y;
    int off;
    Mesh* mm11;
    int x;
    int i;
/*E*/
    Mesh* buf[16];
    for (i = 0, off0 = 0; i < fn_800660E8(&lbl_803CB770); i++, off0 += 8) {
        MapEv* e = (MapEv*)((u8*)lbl_803CB770.p + off0);
        x = e->x;
        y = e->y;
        switch (e->kind) {
        case 0x24:
            FIND(A(0x40000), mm1, ii1, oo1, x, y, L1)
            if (mm1) fn_801CA300(mm1);
            break;
        case 0x21:
            FIND(B(0x1000), mm2, ii2, oo2, x, y, L2)
            if (mm2) {
                fn_801CA4FC(mm2, 0);
                FIND(B(0x800), m2, i2, off2, x, y, LA);
                if (m2 == 0) {
                    for (i3 = 0; i3 < 4; i3++) {
                        int d = DirBit(i3);
                        int dx = DirX(d);
                        int dy = DirY(d);
                        int yy = y + dy;
                        int xx = x + dx;
                        FIND(B(0x800), m2, x3, off, xx, yy, LB);
                        if (m2) goto LC;
                    }
                    m2 = 0;
                }
                LC:
                mm2 = m2;
                if (mm2) {
                    int n = fn_80135C44(mm, mm2, buf, 0);
                    Mesh** p = buf;
                    for (int k = 0; k < n; k++) {
                        fn_801CA444(*p, 0);
                        p++;
                    }
                }
            }
            break;
        case 0x22:
            FIND(A(0x800), mm3, ii3, oo3, x, y, L3)
            if (mm3) {
                int n = fn_80135C44(mm, mm3, buf, 0);
                Mesh** p = buf;
                for (int k = 0; k < n; k++) {
                    fn_801CA444(*p, 0);
                    p++;
                }
            }
            break;
        case 0x23:
            FIND(A(0x200), mm4, ii4, oo4, x, y, L4)
            if (mm4) fn_801CA300(mm4);
            break;
        case 0x25:
            FIND(((f & 0x20000) == 0 && (f & 0x800) == 0x800), mm5, ii5, oo5, x, y, L5)
            if (mm5) {
                fn_801CA3E4(mm5, 0);
                FIND(B(0x20000), mm6, ii6, oo6, x, y, L6)
                if (mm6) {
                    fn_801CA300(mm6);
                    fn_801CA3E4(mm6, 1);
                }
            }
            break;
        case 0x26:
            FIND(A(0x800), mm7, ii7, oo7, x, y, L7)
            if (mm7) fn_801CA444(mm7, 0);
            break;
        case 0x27:
            FIND(B(0x10000), mm8, ii8, oo8, x, y, L8)
            if (mm8) fn_801CA444(mm8, 0);
            break;
        case 0x28:
            FIND(A(0x200), mm9, ii9, oo9, x, y, L9)
            if (mm9) fn_801CA300(mm9);
            break;
        case 0x29:
            FIND(A(0x80000), mm10, ii10, oo10, x, y, L10)
            if (mm10) fn_801CA3E4(mm10, 0);
            break;
        case 6:
            FIND(A(0x10000000), mm11, ii11, oo11, x, y, L11)
            if (mm11) {
                fn_801CA33C(mm11, 0xFF, 0);
                Emit* s = FindEmit(mm, mm11);
                if (s) fn_80272624(s, 1.0f);
            }
            break;
        case 0x12: {
            int n = fn_8013599C(mm, x, y, 0x1004200, 0x10, buf);
            Mesh** p = buf;
            for (int k = 0; k < n; k++) {
                fn_801CA3E4(*p, 0);
                p++;
            }
            break;
        }
        case 0x13:
            FIND(A(0x40000000), mm12, ii12, oo12, x, y, L12)
            if (mm12) fn_801CA3E4(mm12, 1);
            break;
        }
    }
    fn_801379F8(mm, 1);
    fn_80114D00(lbl_803EC898);
    fn_8013A638(mm);
    fn_8012D908();
    for (int j = 0; j < fn_800660E8(&lbl_803CB770); j++) {
        fn_80065E4C(&lbl_803CB770.p[j], 0);
    }
}
}

/* ===== fn_80144324, later attempt: real file statics give the hoisted addi r9,r8,r7 (pooled .rodata). Now 74 lines: statement order of the t/e/u copies is still wrong. The earlier section above is superseded. ===== */
/* Cloud layer scroll: moves the texture offset and rebuilds its projection matrix. */
#include "game/rL_80133EB4/types.h"
struct Mtx { f32 m[12]; };
struct Mtx44 { f32 m[12]; };
struct Cloud {
    u8 pad0[0x30];
    f32 x30, x34;
    u8 pad38[4];
    Mtx x3c;
};
struct WxP {
    u8 pad0[0x30];
    u8 x30;
    u8 pad31[0x3C - 0x31];
    f32 x3c;
    u8 pad40[8];
    f32 x48, x4c;
};
static const Vec s0 = {0.0f, 0.0f, -10.0f};
static const Vec s1 = {0.0f, 0.0f, 10.0f};
static const Vec s2 = {0.0f, -1.0f, 0.0f};
static const Vec s3 = {0.0f, -1.0f, 0.0f};
extern "C" {
extern u8 lbl_80386540[];
extern WxP* fn_80083B84(void*);
extern int fn_80068D74(void);
extern void fn_80312AC0(Mtx*, Vec*, Vec*, Vec*);
extern void fn_80312D2C(Mtx*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80312378(Mtx*, Mtx*, Mtx*);

static inline const Vec& T(Vec& t, const Vec& s, f32 x, f32 y) { t = s; t.x = x; t.y = y; return t; }
static inline Vec Mk(const Vec& s, f32 x, f32 y) { Vec t = s; t.x = x; t.y = y; return t; }
static inline void Look(Mtx* m, Vec e, Vec u, Vec t) { fn_80312AC0(m, &e, &u, &t); }

void fn_80144324(Cloud* c) {
    WxP* w = fn_80083B84(lbl_80386540);
    if (w->x30 == 0) return;
    if (fn_80068D74() == 0) return;
    Mtx mv;
    Mtx mp;
    c->x30 += w->x48 * w->x3c;
    f32 k = 32.0f;
    f32 tx = k + c->x30;
    c->x34 += w->x4c * w->x3c;
    f32 ty = k + c->x34;
    Vec e, t; Look(&mv, T(e, s1, k + c->x30, k + c->x34), s3, T(t, s0, tx, ty));
    fn_80312D2C(&mp, -k, k, -k, k, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_80312378(&mp, &mv, &c->x3c);
}
}

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
const Vec* fn_dummy_0(void) { return &sA; }
const Vec* fn_dummy_1(void) { return &sB; }
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

/* ===== fn_8013EED0 (0x268): masked diff 4 lines, 66 lines of ranks. Parameter must be r23 but takes r31; lis base r31, g r30, p8 r28, p16 r29, offsets r27 and r22. ===== */
/* Draws the movement and attack range tiles over the map. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct EP { u8 pad[0x34]; f32 x34; };
struct C4 { u8 r, g, b, a; };
struct Map {
    int w;
    int h;
    u8 pad8[0x200D - 8];
    u8 mark[0x40][0x40];
    u8 pad300d[0x710E - 0x300D];
    s16 rng[0x40][0x40];
    u8 pad910e[0xD18E - 0x910E];
    u16 atk[0x40][0x40];
    u8 padf18e[0xF18E - 0xF18E];
    s8 sel[0x40][0x40];
};
struct Tab { C4 c[4]; };
extern "C" {
extern Map lbl_803EC898;
extern Tab lbl_803863A8[];
extern int fn_80068D74(void);
extern void fn_8013E7FC(void);
extern void fn_8013EA08(s8, s8, C4*, f32);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80011838(int);

#define G lbl_803EC898
#define CELL(CK, BODY) \
        for (y = (s8)(G2->h - 1); (s8)y >= 0; y--) { \
            x = (s8)(G.w - 1); \
            p8 = x + ((u8*)G2 + y * 0x40); \
            p16 = x * 2 + ((u8*)G2 + y * 0x80); \
            for (; (s8)x >= 0; x--, p8--, p16 -= 2) { BODY } \
        }
#define SHOW \
    if (*(s8*)(p8 + 0xF18E)) { \
        if (*(s16*)(p16 + 0x710E) >= 0) fn_8013EA08((s8)x, (s8)y, tab[3].c, p->x34); \
    } else if (*(s16*)(p16 + 0x710E) >= 0) { \
        fn_8013EA08((s8)x, (s8)y, tab[1].c, p->x34); \
    } else if (*(u16*)(p16 + 0xD18E)) { \
        fn_8013EA08((s8)x, (s8)y, tab[2].c, p->x34); \
    }
void fn_8013EED0(EP* p) {
    /*P*/
    Map* G2;
    u8* p16;
    int x;
    int y;
    BOOL any;
    u8* p8;
    Tab* tab;
/*E*/
    if (fn_80068D74()) {
        any = 0;
        fn_8013E7FC();
        G2 = &lbl_803EC898;
        tab = lbl_803863A8;
        CELL(0, if (p8[0x200D] == 0) { any = 1; } else SHOW)
        if (any) {
            fn_80021BA4(1, 4, 5, 0);
            G2 = &lbl_803EC898;
            tab = lbl_803863A8;
            CELL(0, if (p8[0x200D] == 0) SHOW)
        }
        fn_80011838(-1);
    }
}
}

/* ===== fn_801478F4 (0x204): the row loop must unroll 2x (ctr 4, r29 stepped twice) with the 8-step inner loop fully unrolled; plain forms do not unroll and hand-unrolled forms spill. ===== */
/* Packs an 8-bit shadow image into an I4 texture, one 8x8 tile at a time. */
#include "game/rL_80133EB4/types.h"
extern "C" {
extern u8 lbl_804CB871;
extern s16 lbl_804CB872;
extern s16 lbl_804CB874;
extern u8* lbl_80413F00[];
extern void fn_8017F464(void*, int, int);
extern void DCFlushRange(void*, u32);

static inline u32 Pack(u32 v, u8* q) { int k; for (k = 0; k < 8; k++) { v <<= 4; v |= (q[k] >> 4) & 0xF; } return v; }
static inline u32 Pk2(u32 v, u8* q) { for (int k = 0; k < 8; k++) { v = (v << 4) | ((q[k] >> 4) & 0xF); } return v; }
#define ROW(R) { u8* q = s + w * (y + R); v = Pack(v, q); *d = v; d++; }
void fn_801478F4(u8* src) {
    if (src == 0) {
        fn_8017F464(lbl_80413F00[lbl_804CB871], 0, 0x2000);
    } else {
        int w = lbl_804CB872;
        int h = lbl_804CB874;
        u32* d = (u32*)lbl_80413F00[lbl_804CB871];
        u32 v = 0;
        for (int y = 0; y < h; y += 8) {
            for (int x = 0; x < w; x += 8) {
                u8* s = src + x;
{ int r = 0; for (int n = 0; n < 4; n++) { { u8* q = s + w * (y + r); r++; v = Pack(v, q); *d++ = v; } { u8* q = s + w * (y + r); r++; v = Pack(v, q); d[0] = v; d++; } } }
            }
        }
    }
    DCFlushRange(lbl_80413F00[lbl_804CB871], 0x2000);
}
}

/* ===== fn_8013AC48 (0x1D0): 7 lines, all at the first-tried default lookup: f must take r28 and the name r29 (ours reversed). Three per-site copies of the lookup inline, by-reference name. ===== */
/* Looks the map up in the environment sound table and copies its parameters. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct SndMap { const char* name; u8 a, b; u8 pad[2]; f32 x, y, z; };
struct Env2 { u8 pad[0x6A]; u8 a, b; f32 x, y, z; };
struct MA2 { u8 pad0[0x8A]; char name[0x27]; u8 xb1; };
#define MapModel MA2
extern "C" {
extern char lbl_803694D4[];
extern int fn_80076F54(const char*);
extern int* fn_80077064(const char*);
extern int fn_80291188(const char*, const char*);
static inline SndMap* FindA(const char* const& name) {
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
static inline SndMap* FindB(const char* const& name) {
    /*P*/
    const char* f;
    int i;
    int n;
    SndMap* e;
    int* d;
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
static inline SndMap* FindC(const char* const& name) {
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
    const char* nb;
    char* name = mm->name;
    if (name) {
        SndMap* e = FindA(name);
        if (e == 0) {
            switch (mm->xb1) {
            case 0:
                { const char* nb = lbl_803694D4 + 0x1C7; e = FindB(nb); }
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                { const char* nc = lbl_803694D4 + 0x1CE; e = FindC(nc); }
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

}
