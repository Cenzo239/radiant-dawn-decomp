/* 2 of 209 words differ: the original has ori r26 before mr r24,r3 after the fn_800F760C call. Both statement orders and a temporary keep the mr first. */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

/* Plays an animation on a map unit: fn_80102928(unit, anim, blend, flags, parent). */
typedef struct Probe { u8 pad[0x30]; void* a; } Probe;
typedef struct R2928 {
    u8 pad[0x30];
    MapUnit* u;   /* 0x30 */
    s32 a;        /* 0x34 */
    s32 n;        /* 0x38 */
    s32 t;        /* 0x3C */
    u16 fl;       /* 0x40 */
} R2928;
typedef struct Anm { u8 pad[0x14]; s32 v14; s32 v18; } Anm;
typedef struct CF { u8 pad[0x10]; u8 b10; u8 pad11[5]; u8 b16; } CF;
typedef struct CD { u8 pad[0x10]; CF* v10; } CD;
typedef struct AE { u8 pad[8]; u8 b8; } AE;

extern u8 lbl_80385050[];
extern u8 lbl_80385070[];
extern void fn_80104A70(void* a, void* b);
extern void fn_80104AA4(void* a, void* b);
extern void* fn_800893E4(void*, void*, Probe*);
extern void* fn_800811E4(void*, void*);
extern void fn_80081A90(void*);
extern int fn_800FADA0(MapUnit*);
extern int fn_800F760C(MapUnit*);
extern int fn_800F4628(MapUnit*, int);
extern void fn_800F4B94(MapUnit*, int);
extern AE* fn_800F0AA8(int);
extern CD* fn_800F43F0(MapUnit*);
extern void* fn_800F446C(MapUnit*, int);
extern Anm* fn_8000BD3C(void*);
extern Anm* fn_80007F10(void*);
extern void fn_8000BE20(Anm*);
extern void fn_800F5088(MapUnit*, int);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_800088B0(void*, Anm*);
extern void fn_8000866C(void*, f32);
extern void fn_800FB258(MapUnit*, int);
extern void fn_800FB228(MapUnit*, int);
extern void fn_800FB288(MapUnit*, int);
extern void fn_800F3F14(MapUnit*, f32);
extern void fn_800FAF78(MapUnit*);

static inline void StopCls(u8* cls, MapUnit* u) {
    Probe s;
    s.a = u;
    fn_800893E4(cls, fn_80104A70, &s);
}
static inline void Cancel(MapUnit* u) {
    Probe s;
    R2928* q;
    s.a = u;
    q = fn_800893E4(lbl_80385050, fn_80104AA4, &s);
    if (q) {
        q->fl |= 0x100;
        fn_80081A90(q);
    }
}

void* fn_80102928(MapUnit* u, int a, int n, int fl, void* parent) {
    CD* d;
    AE* e;
    u8* m;
    Anm* an;
    f32 f;
    R2928* q;
    if (fn_800FADA0(u) == 0) return 0;
    if (a < 0) {
        a = fn_800F760C(u), fl |= 0x20;
    }
    if (fn_800F4628(u, a) == 0) return 0;
    if (*(u16*)((u8*)u + 0x110) & 1) return 0;
    if (n == 0) {
        StopCls(lbl_80385050, u);
        StopCls(lbl_80385070, u);
        fn_800F4B94(u, a);
        return 0;
    }
    e = fn_800F0AA8(a);
    d = fn_800F43F0(u);
    m = (u8*)u + 0x28;
    {
        void* x = fn_800F446C(u, a);
        Anm* cur;
        if (x == 0) return 0;
        an = fn_8000BD3C(x);
        cur = fn_80007F10(m);
        {
        int a14 = an->v14;
        f = (f32)a14;
        if ((fl & 0x20) && an == cur) {
            fn_8000BE20(an);
            fn_800F5088(u, a);
            return 0;
        }
        if (d) {
            n = n * d->v10->b16 / 100;
            if (n == 0) n = 1;
        }
        if (e->b8 && (d->v10->b10 & 4) && cur) {
            f32 c14 = (f32)cur->v14;
            f32 c18 = (f32)cur->v18;
            f = fn_8001EF30((f32)a14, (f32)an->v18, c18 - c14, *(f32*)(m + 0x58) - c14);
        }
        }
    }
    Cancel(u);
    StopCls(lbl_80385070, u);
    fn_800088B0(m, an);
    fn_8000866C(m, f);
    fn_800F5088(u, a);
    if (fl & 8) {
        fn_800FB258(u, 1);
        fn_800FB228(u, 1);
    }
    if (fl & 0x10) {
        fn_800FB288(u, 1);
    }
    if (fl & 0x200) {
        fn_800F3F14(u, 0.5f);
    }
    if (fl & 4) {
        fn_800FAF78(u);
    }
    q = fn_800811E4(lbl_80385050, parent);
    q->u = u;
    q->a = a;
    q->n = n;
    q->t = 0;
    q->fl = fl;
    return q;
}
