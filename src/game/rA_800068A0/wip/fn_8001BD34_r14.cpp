/* fn_8001BD34: 43 of 750 words differ (2 are rodata label names). Uses the fixed-address FIFO; i2 must be r26. */
/* fn_8001BD34: 46 of 750 words differ, registers only. Structure, stack and rodata templates are right (sPad places the templates at 0x8C). Left: i2 must be r26 and the last vertex loop's pa/fifo/template/zero r26/r27/r28/r29; the original seems to have r29 blocked in those regions, and declaration order and moving loop 2 into an inline did not reproduce that. */
#include "game/rA_800068A0/types.h"
typedef union WG { u8 u8; s8 s8; u16 u16; s16 s16; u32 u32; f32 f32; } WG;
volatile WG WGPIPE : 0xCC008000;
/* Ribbon/trail strip through a list of points, in three billboard modes. */
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct GNd { u8 x0[0xC]; u32 flags; } GNd;
extern char lbl_80360E30[];
extern char lbl_80360EEC[];
extern int fn_8001BB84(Vec* p, f32* s, u8* a, Vec* op, f32* os, u8* oa, int n, int mode);
extern void fn_8001E008(const char* file, int line, const char* msg);
extern void fn_803128AC(void* m, f32 x, f32 y, f32 z);
extern void fn_80312654(void* m, int axis, f32 a);
extern void fn_80312378(const void* a, const void* b, void* c);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void* fn_8000FB88(void);
extern void fn_80312444(const void* a, void* b);
extern void fn_8001E6AC(const void* a, void* b);
extern void fn_8001E694(const void* a, void* b);
extern void fn_8001E6D0(const void* a, void* b);
extern void fn_80312DB4(const void* m, const Vec* a, Vec* b);
extern void fn_80313484(const Vec* a, const Vec* b, Vec* c);
extern void fn_803134A8(f32 s, const Vec* a, Vec* b);
extern f32 fn_80313508(const Vec* v);
extern void fn_803134C4(const Vec* a, Vec* b);
extern void fn_8031356C(const Vec* a, const Vec* b, Vec* c);
extern f32 fn_8031354C(const Vec* a, const Vec* b);
extern void fn_80313460(const Vec* a, const Vec* b, Vec* c);
extern void fn_80304314(int, int, u16);
extern void fn_80312830(void* m, const Vec* axis, f32 a);
#define WGF (WGPIPE.f32)
#define WGB (WGPIPE.u8)
static const u32 sPad[35] = {0x3BA3D70A,0x3BA3D70A,0x3BA3D70A,0x00000000,0x00000000,0x3F800000,0x0000000D,0x0000000E,0x0000000F,0x00000010,0x00000011,0x00000012,0x00000013,0x00000014,0x00000000,0xBF800000,0x00000000,0x00000000,0x3F800000,0x00000000,0x00000000,0x00000000,0x3F800000,0x3F800000,0x00000000,0x00000000,0x00000000,0x3F800000,0x00000000,0x3F800000,0x00000000,0x00000000,0x00000000,0x00000000,0x3F800000};
void rodata_dummy(void) { fn_803031CC(); (void)sPad[0]; extern void dummy_use(const void*); dummy_use(sPad); }
static inline void tangent(const Vec* pos, const Vec* cur, int i, int cnt, Vec* dir) {
    if (i == 0) {
        fn_80313484(&pos[i + 1], cur, dir);
    } else if (i == cnt - 1) {
        fn_80313484(&pos[i - 1], cur, dir);
        fn_803134A8(-1.0f, dir, dir);
    } else {
        fn_80313484(&pos[i + 1], cur, dir);
    }
}
static inline void pos3(f32 x, f32 y, f32 z) {
    WGF = x;
    WGF = y;
    WGF = z;
}
static inline void col4(u8 r, u8 g, u8 b, u8 a) {
    WGB = r;
    WGB = g;
    WGB = b;
    WGB = a;
}
static inline void tex2(f32 u, f32 v) {
    WGF = u;
    WGF = v;
}
static inline void vtx2(const Vec* p, const Vec* o, u8* al, const Vec* a, const Vec* b) {
    pos3(p->x + o->x, p->y + o->y, p->z + o->z);
    col4(0xFF, 0xFF, 0xFF, *al);
    tex2(a->x, a->y);
    pos3(p->x - o->x, p->y - o->y, p->z - o->z);
    col4(0xFF, 0xFF, 0xFF, *al);
    tex2(b->x, b->y);
}
static inline Vec adj(const Vec* po, int i) {
    Vec r;
    if (i == 0) {
        r = po[1];
    } else {
        r = po[-1];
    }
    return r;
}
void fn_8001BD34(f32 ang, GNd* nd, const void* mtx, Vec* ipos, f32* isz, u8* ial, int icnt, int mode) {
    Vec off[129];
    Vec pos[129];
    f32 size[129];
    u8 alpha[129];
    Mtx m158;
    Mtx m128;
    Mtx m0F8;
    Mtx m0C8;
    Mtx m098;
    Vec out;
    Vec dir;
    Vec zero = {0.0f, 0.0f, 0.0f};
    Vec up = {0.0f, 0.0f, 1.0f};
/*P*/
    Vec* pp7;
    int cnt;
    Vec* po5;
    Vec* base;
    int i2;
    Vec* po7;
    f32 du;
    Vec* pp1;
    Vec* q;
    Vec* po1;
    f32 sign;
    int i1;
    u8* pa1;
    Vec* po2;
    Vec* pp2;
    f32* ps;
    u8* pa2;
    u8* pa3;
    Vec* po3;
    Vec* pp3;
    Vec* pp4;
    int i3;
    Vec* po4;
    int i4;
    u8* pa4;
    int n2;
    Vec* pp5;
    int i5;
    Vec* po6;
    Vec* pp6;
    int i6;
    u8* pa6;
    int i7;
    u8* pa7;
    Vec* po8;
    Vec* pp8;
    int i8;
    u8* pa8;
    u8* pa5;
/*E*/
    sign = 1.0f;
    cnt = fn_8001BB84(ipos, isz, ial, pos, size, alpha, icnt, mode);
    if (cnt >= 0x81) {
        fn_8001E008(lbl_80360EEC, 0x827, lbl_80360EEC + 0xAC);
    }
    base = pos;
    ps = size;
    fn_803128AC(m128, -0.5f, -0.5f, 0.0f);
    fn_80312654(m0F8, 0x7A, 0.017453292f * ang);
    fn_80312378(m0F8, m128, m0F8);
    fn_803128AC(m128, 0.5f, 0.5f, 0.0f);
    fn_80312378(m128, m0F8, m0F8);
    du = 1.0f / (f32)(cnt - 1);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    switch (nd->flags & 0xC00000) {
    case 0x400000:
        fn_80312444(fn_8000FB88(), m158);
        fn_8001E6AC(mtx, m128);
        fn_80312378(m128, m158, m158);
        fn_8001E694(mtx, m128);
        fn_80312378(m128, m158, m158);
        fn_80312DB4(m158, &up, &up);
        po1 = off;
        pp1 = base;
        for (i1 = 0; i1 < cnt; pp1++, po1++, i1++) {
            out = zero;
            tangent(base, pp1, i1, cnt, &dir);
            if (fn_80313508(&dir) > 0.0f) {
                fn_803134C4(&dir, &dir);
                fn_8031356C(&dir, &up, &out);
                if (fn_80313508(&out) > 0.0f) {
                    fn_803134C4(&out, &out);
                }
            }
            *po1 = out;
        }
        po2 = off;
        for (i2 = 0; i2 < cnt; po2++, i2++) {
            Vec b = i2 == 0 ? po2[1] : po2[-1];
            Vec a = *po2;
            fn_803134A8(sign, &a, &a);
            f32 d = fn_8031354C(&a, &b);
            if (d > 0.0f) {
                fn_80313460(&a, &b, &a);
                fn_803134C4(&a, &a);
            } else if (d < 0.0f) {
                sign *= -1.0f;
                fn_803134A8(sign, &a, &a);
            }
            fn_803134A8(*ps, &a, &a);
            ps++;
            *po2 = a;
        }
        fn_80304314(0x98, 0, cnt * 2);
        po3 = off;
        pp3 = base;
        for (i3 = 0, pa3 = alpha; i3 < cnt; pp3++, po3++, pa3++, i3++) {
            f32 t = (f32)i3 * du;
            Vec va = {0.0f, 0.0f, 0.0f};
            va.y = t;
            Vec vb = {1.0f, 0.0f, 0.0f};
            vb.y = t;
            if (0.0f != ang) {
                fn_80312DB4(m0F8, &va, &va);
                fn_80312DB4(m0F8, &vb, &vb);
            }
            vtx2(pp3, po3, pa3, &va, &vb);
        }
        break;
    case 0x800000:
        fn_8001E6D0(mtx, m098);
        fn_80312654(m0C8, 0x7A, 1.5707964f);
        fn_80312378(m0C8, m098, m0C8);
        po4 = off;
        pp4 = base;
        for (i4 = 0; i4 < cnt; pp4++, po4++, i4++) {
            out = zero;
            tangent(base, pp4, i4, cnt, &dir);
            if (fn_80313508(&dir) > 0.0f) {
                fn_80312DB4(m0C8, &dir, &out);
                if (fn_80313508(&dir) > 0.0f) {
                    fn_803134C4(&out, &out);
                }
            }
            fn_803134A8(*ps, &out, &out);
            ps++;
            *po4 = out;
        }
        n2 = cnt * 2;
        fn_80304314(0x98, 0, n2);
        po5 = off;
        pp5 = base;
        for (i5 = 0, pa5 = alpha; i5 < cnt; pp5++, po5++, pa5++, i5++) {
            f32 t = (f32)i5 * du;
            Vec va = {0.0f, 0.0f, 0.0f};
            va.y = t;
            Vec vb = {1.0f, 0.0f, 0.0f};
            vb.y = t;
            if (0.0f != ang) {
                fn_80312DB4(m0F8, &va, &va);
                fn_80312DB4(m0F8, &vb, &vb);
            }
            vtx2(pp5, po5, pa5, &va, &vb);
        }
        {
            po7 = off;
            zero = *po7;
            pp7 = base;
            q = po7;
            for (i7 = 0; i7 < cnt; pp7++, po7++, q++, i7++) {
                out = zero;
                tangent(base, pp7, i7, cnt, &dir);
                if (fn_80313508(&dir) > 0.0f) {
                    fn_803134C4(&dir, &dir);
                    fn_80312830(m158, &dir, 1.5707964f);
                    fn_80312DB4(m158, po7, &out);
                    zero = out;
                }
                *q = out;
            }
        }
        fn_80304314(0x98, 0, n2);
        po8 = off;
        pp8 = base;
        for (i8 = 0, pa8 = alpha; i8 < cnt; pp8++, po8++, pa8++, i8++) {
            f32 t = (f32)i8 * du;
            Vec va = {0.0f, 0.0f, 0.0f};
            va.y = t;
            Vec vb = {1.0f, 0.0f, 0.0f};
            vb.y = t;
            if (0.0f != ang) {
                fn_80312DB4(m0F8, &va, &va);
                fn_80312DB4(m0F8, &vb, &vb);
            }
            vtx2(pp8, po8, pa8, &va, &vb);
        }
        break;
    }
}
}
