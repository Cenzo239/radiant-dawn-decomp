/*
 * fn_800FB398 (round 22, `sched`: two hoisted constant loads before the loop in the other order,
 * lfd of the int-to-float magic before lfs of `s` = 0.5f; symcheck --anon --xargs: 53 blocks, 0 differ).
 * Draws the map marks in the list lbl_804CB748 (a 16-byte node pool; head at +0xC, count at +0x14):
 * each mark is a textured quad at tile (x, y), rotated by `angle` degrees about Z, fading out over
 * 60 frames once its age passes 120 (alpha 0xC0 down to 0), drawn through fn_800F280C.
 *
 * Constants: the camera vectors are aggregate initialisers; the compiler emits them as anonymous
 * .rodata objects that are lbl_80367AA0 ({0,0,-1}) and lbl_80367B8C ({0,1,0}) in the original (part of
 * the file's pooled .rodata at lbl_80367A58; checked by value). The colour's r, g, b come from three
 * 1-byte .sdata globals lbl_804CA4B0..B2 (all 0xFF in the DOL), declared extern here.
 *
 * Shape notes: eye/target are built by inlines returning Vec by value (word copies through r1+0x10 and
 * r1+0x1C); declaration order tgt, eye, up sets their slots; the colour comes from an inline (slot below
 * its by-value argument copy); `fy` declared before `fx` gives f28/f27.
 * Tried for the last two loads: `s` before/after the fade, after the angle, after `up`, as const,
 * passed through an inline; operand orders of the angle multiply and compare. No change.
 */
#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef f32 Mtx34[3][4];
struct Mark {
    Mark* next;  /* 0x0 */
    Mark* prev;  /* 0x4 */
    u8 age;      /* 0x8 */
    u8 pad9;
    s16 angle;   /* 0xA */
    s16 x;       /* 0xC */
    s16 y;       /* 0xE */
};
struct MarkList { void* pool; void* st; void* top; Mark* head; Mark* tail; int count; int n; };
extern "C" {
extern void* lbl_804CB730;
extern MarkList* lbl_804CB748;
extern u8 lbl_804CA4B0, lbl_804CA4B1, lbl_804CA4B2;
extern void fn_80006A64(void*, void*, int);
extern void fn_80022254(void*, int);
extern void fn_80021B68(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021C34(int);
extern void fn_803128AC(f32*, f32, f32, f32);
extern f32* fn_8000FB88(void);
extern void fn_80312378(f32*, f32*, f32*);
extern void fn_80307E48(f32*, int);
extern void fn_80021784(int);
extern void fn_80021860(int, int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021808(int, int, int, int, int);
extern void fn_80021EF8(int, int);
extern f32 fn_8001E064(s32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_80312654(f32*, int, f32);
extern void fn_80312AC0(f32*, const Vec*, const Vec*, const Vec*);
extern void fn_80312D2C(f32*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80307F10(f32*, int, int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_800F280C(GXColor col, void* p, f32 x, f32 y);

static inline Mark* NextMark(MarkList* l, Mark* m)
{
    if (m == 0) {
        return l->head;
    }
    return m->next;
}

static inline int Fade(u8 age)
{
    int from = 0xc0;
    int a = 0xc0;
    if (age > 0x78) {
        a = fn_8001EF30(from, 0.0f, 60.0f, age - 0x78);
    }
    return a;
}

static inline Vec Eye(f32 x, f32 y)
{
    Vec v = {0.0f, 0.0f, -1.0f};
    v.x = x;
    v.y = y;
    return v;
}

static inline Vec Target(f32 x, f32 y)
{
    Vec v = {0.0f, 0.0f, 0.0f};
    v.x = x;
    v.y = y;
    return v;
}

static inline GXColor Col(int a)
{
    GXColor c = {lbl_804CA4B0, lbl_804CA4B1, lbl_804CA4B2, a};
    return c;
}

void fn_800FB398(void)
{
    Mtx34 view;
    Mtx34 trans;
    Mtx34 proj;
    Mtx34 look;
    Mtx34 rot;
    Mtx34 tmp;
    Mtx34 mv;
    u8 tex[0x20];
    Mark* m;
    if (lbl_804CB748->count == 0) {
        return;
    }
    fn_80021B68(2);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021C34(1);
    fn_803128AC(&trans[0][0], 0.0f, 0.0f, -0.015f);
    fn_80312378(fn_8000FB88(), &trans[0][0], &view[0][0]);
    fn_80307E48(&view[0][0], 0);
    fn_80021784(0);
    fn_80021860(1, 3, 0);
    fn_80021BA4(1, 4, 5, 7);
    fn_80021808(7, 0, 1, 7, 0);
    fn_80021EF8(0, 0);
    for (m = 0; (m = NextMark(lbl_804CB748, m)) != 0;) {
        f32 fy;
        f32 fx;
        fx = fn_8001E064(m->x);
        fy = fn_8001E064(m->y);
        int alpha = Fade(m->age);
        f32 s = 0.5f;
        fn_80006A64(lbl_804CB730, tex, 3);
        fn_80022254(tex, 0);
        f32 ang = m->angle;
        GXColor c = Col(alpha);
        Vec tgt = Target(fx, fy);
        Vec eye = Eye(fx, fy);
        Vec up = {0.0f, 1.0f, 0.0f};
        if (0.0f != ang) {
            fn_80312654(&rot[0][0], 0x5A, 0.017453292f * ang);
            fn_80312AC0(&look[0][0], &eye, &up, &tgt);
            fn_80312D2C(&proj[0][0], -s, s, -s, s, 0.5f, 0.5f, 0.5f, 0.5f);
            fn_80312378(&proj[0][0], &look[0][0], &mv[0][0]);
            fn_803128AC(&tmp[0][0], -0.5f, -0.5f, 0.0f);
            fn_80312378(&rot[0][0], &tmp[0][0], &rot[0][0]);
            fn_803128AC(&tmp[0][0], 0.5f, 0.5f, 0.0f);
            fn_80312378(&tmp[0][0], &rot[0][0], &rot[0][0]);
            fn_80312378(&rot[0][0], &mv[0][0], &mv[0][0]);
        } else {
            fn_80312AC0(&look[0][0], &eye, &up, &tgt);
            fn_80312D2C(&proj[0][0], -s, s, -s, s, 0.5f, 0.5f, 0.5f, 0.5f);
            fn_80312378(&proj[0][0], &look[0][0], &mv[0][0]);
        }
        fn_80307F10(&mv[0][0], 0x1E, 0);
        fn_80021F7C(0, 0, 0, 0x1E);
        fn_800F280C(c, 0, fx, fy);
    }
}
}
