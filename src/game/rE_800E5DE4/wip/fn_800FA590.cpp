/* 800FA590: not close (24+ words). addi r4,r30,0x48 plus lwz 0x48(r30) means pooled file static const data at lbl_80367A58 (see 800F33A4 for the copy shape, which is solved). 800FB398 has the same shape. */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct W2 { u32 a, b; } W2;
typedef struct W3 { W2 ab; u32 c; } W3;
extern "C" {
extern const u8 lbl_80367A58[];
extern void fn_800076E8(Vec*, void*, int);
extern u32 fn_8017FA1C(void);
extern void fn_80312654(f32 (*)[4], int, f32);
extern void fn_80312AC0(f32 (*)[4], const Vec*, const Vec*, const Vec*);
extern void fn_80312D2C(f32 (*)[4], f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80312378(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern void fn_803128AC(f32 (*)[4], f32, f32, f32);
extern void fn_80307F10(f32 (*)[4], int, int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_800F280C(GXColor, void*, f32, f32);
extern void fn_800F3050(int, GXColor, void*, f32, f32);
void fn_800FA590(MapUnit* m, int k) {
    const u8* b = lbl_80367A58;
    f32 x = m->x;
    f32 y = m->y;
    Vec a;
    C4 c[4];
    Vec rt;
    Vec e0;
    Vec t0 = {0.0f, 0.0f, 0.0f};
    Vec up;
    Vec eye;
    Vec tgt;
    GXColor g;
    f32 v[3][4];
    f32 q[3][4];
    f32 r[3][4];
    f32 l[3][4];
    f32 o[3][4];
    if ((m->flags & 0x400) && m->unkC8 >= 0) {
        fn_800076E8(&rt, m->model, m->unkC8);
        *(W3*)&a = *(W3*)&rt;
        x = a.x;
        y = a.y;
    }
    f32 ang = m->unk2 + 0xB4;
    f32 s = 0.5f;
    fn_8017FA1C();
    t0.x = x;
    t0.y = y;
    *(W3*)&tgt = *(W3*)&t0;
    *(W3*)&e0 = *(W3*)(b + 0x48);
    e0.x = x;
    e0.y = y;
    *(W3*)&eye = *(W3*)&e0;
    *(W3*)&up = *(W3*)(b + 0x128);
    if (0.0f != ang) {
        fn_80312654(r, 0x5A, 0.017453292f * ang);
        fn_80312AC0(l, &eye, &up, &tgt);
        fn_80312D2C(o, -s, s, -s, s, 0.5f, 0.5f, 0.5f, 0.5f);
        fn_80312378(o, l, v);
        fn_803128AC(q, -0.5f, -0.5f, 0.0f);
        fn_80312378(r, q, r);
        fn_803128AC(q, 0.5f, 0.5f, 0.0f);
        fn_80312378(q, r, r);
        fn_80312378(r, v, v);
    } else {
        fn_80312AC0(l, &eye, &up, &tgt);
        fn_80312D2C(o, -s, s, -s, s, 0.5f, 0.5f, 0.5f, 0.5f);
        fn_80312378(o, l, v);
    }
    fn_80307F10(v, 0x1E, 0);
    fn_80021F7C(0, 0, 0, 0x1E);
    {
        u8 al = m->unk33;
        c[0] = ((const C4*)(b + 0x118))[0];
        c[1] = ((const C4*)(b + 0x118))[1];
        c[2] = ((const C4*)(b + 0x118))[2];
        c[3] = ((const C4*)(b + 0x118))[3];
        c[0].a = al;
        c[1].a = al;
        c[2].a = al;
        c[3].a = al;
        switch (m->unkF4->unk8) {
        case 0: g.r = c[0].r; g.g = c[0].g; g.b = c[0].b; g.a = al; break;
        case 1: g.r = c[1].r; g.g = c[1].g; g.b = c[1].b; g.a = al; break;
        case 2: g.r = c[2].r; g.g = c[2].g; g.b = c[2].b; g.a = al; break;
        case 3: g.r = c[3].r; g.g = c[3].g; g.b = c[3].b; g.a = al; break;
        }
        if ((u32)m->flags2 & 1) {
            g.r >>= 1;
            g.g >>= 1;
            g.b >>= 1;
        }
        if (k < 0) {
            fn_800F280C(g, 0, x, y);
        } else {
            fn_800F3050(k, g, 0, x, y);
        }
    }
}
}
