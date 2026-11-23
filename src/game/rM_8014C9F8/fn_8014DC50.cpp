/* fn_8014DC50: particle emitter process step (moves along a Lissajous path, spawns and draws particles). */
#include "game/rM_8014C9F8/types.h"
struct Part {
    f32 x, y;
    u8 ang, spd, pad, b;
    s16 life, age;
};
struct Emit : Proc {
    Part* parts;  /* 0x30 */
    f32 x, y;     /* 0x34 */
    f32 px, py;   /* 0x3C */
    s16 a1, a2;   /* 0x44 */
    s8 d1, d2;    /* 0x48 */
    u8 dbg, n;    /* 0x4A */
    s8 s0, s1;    /* 0x4C */
    s8 s2, s3;    /* 0x4E */
};
extern "C" {
extern u8 lbl_80386D04[];
void* fn_800791B0(int);
double fn_80295534(double);
double fn_80295940(double);
double fn_802952C8(double);
u32 fn_80089ED0(void);
void fn_8007E154(void);
extern u8* lbl_804CB888;
#if TARGET_PC
FE10_PROTO void fn_8007E374(u8*, p32arg, int);
#else
void fn_8007E374(u8*, int, int);
#endif
void fn_800803F0(f32, f32, f32, f32);
void fn_800803C8(f32, f32, f32, f32);
void fn_800804F4(u8);
void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E164(void);
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_800804D4(int, int, int, int);
void fn_80080308(void);

static inline void Find2(Emit* p, Part*& out) {
    int j;
    for (j = 0; j < 0x400; j++) {
        if (p->parts[j].life == 0) {
            out = &p->parts[j];
            return;
        }
    }
    out = 0;
}
static inline void Spawn(Part* q, u8 ang, f32 x, f32 y, u8 spd) {
    q->x = x;
    q->y = y;
    q->ang = ang;
    q->spd = spd;
}

extern const f32 lbl_804CE1D8;
static inline void Set(Emit* p, f32 c1, f32 arg) { p->x = 296.0f * c1 + 304.0f; p->y = 216.0f * (f32)fn_80295940(arg) + 224.0f; }
static inline void Set2(Emit* p, f32 arg, f32 c1) { p->x = 296.0f * c1 + 304.0f; p->y = 216.0f * (f32)fn_80295940(arg) + 224.0f; }
static inline f32 Y(f32 arg) { return 216.0f * (f32)fn_80295940(arg) + 224.0f; }
static inline void Set3(Emit* p, f32 c1) { f32 arg = 0.0003834952f * p->a2; p->x = 296.0f * c1 + 304.0f; p->y = 216.0f * (f32)fn_80295940(arg) + 224.0f; }
static inline void Update(Part* q2) {
    if (q2->life != 0) {
        q2->age++;
        q2->life--;
        {
            f32 cc = fn_80295534(0.024543693f * (f32)q2->ang);
            f32 pr = (f32)q2->spd * cc;
            f32 arg = 0.024543693f * (f32)q2->ang;
            f32 vx = pr / 64.0f;
            f32 vy = (f32)q2->spd * (f32)fn_80295940(arg) / 64.0f;
            q2->x += vx;
            q2->y += vy;
        }
        q2->ang += (s8)(fn_80089ED0() % 9 - 4);
        if (q2->x < -64.0f || q2->x > 608.0f) {
            q2->life = 0;
        }
        if (q2->y < -64.0f || q2->y > 448.0f) {
            q2->life = 0;
        }
    }
}
static inline int Min(int a, int b) { return a < b ? a : b; }
static inline void Draw(Part* d) {
    if (d->life != 0) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 898.0f, 1.0f);
        fn_8007E374(lbl_804CB888, 9, 0x20);
        fn_8007E164();
        fn_800800D4(1);
        {
            int n = Min(d->spd, d->life);
            {
                f32 r = (f32)n; r /= 8.0f; r += 2.0f;
                fn_800803F0(d->x - r, d->y - r, d->x + r, d->y + r);
            }
        }
        fn_800803C8(0.0f, 0.0f, 1.0f, 1.0f);
        {
            int al = (s16)(d->age - 0x3C);
            if (al > 0xFF) {
                al = 0xFF;
            }
            if (al < 0) {
                al = 0;
            }
            fn_800804F4(al);
        }
        fn_80080308();
    }
}

static inline f32 Heading(Emit* p) {
    f32 dx = p->x - p->px;
    f32 tt = fn_802952C8((p->y - p->py) / dx);
    f32 a = tt * lbl_804CE1D8;
    if (dx < 0.0f) {
        a += 128.0f;
    }
    return a;
}
static inline void Heading2(Emit* p, f32& a) {
    f32 dx = p->x - p->px;
    f32 tt = fn_802952C8((p->y - p->py) / dx);
    a = tt * lbl_804CE1D8;
    if (dx < 0.0f) {
        a += 128.0f;
    }
}
void fn_8014DC50(Emit* p) {
    /*P*/
    f32 dx;
    Part* q;
    f32 c;
    s16 life;
    int ofs;
    Part* d;
    Part* q2;
    f32 ang;
    int i;
    f32 s;
    int j;
/*E*/
    p->px = p->x;
    p->py = p->y;
    {
        f32 fa2;
        f32 c1 = fn_80295534(0.0003834952f * p->a1);
        p->x = 296.0f * c1 + 304.0f;
        fa2 = 0.0003834952f * p->a2;
        p->y = 216.0f * (f32)fn_80295940(fa2) + 224.0f;
    }
    p->a1 += p->d1;
    p->a2 += p->d2;
    if (p->a1 >= 0x4000) {
        p->a1 -= 0x4000;
    }
    if (p->a2 >= 0x4000) {
        p->a2 -= 0x4000;
    }
    ang = Heading(p);
    for (i = 0; i < p->n; i++) {
        Find2(p, q);
        if (q == 0) {
            break;
        }
        life = fn_80089ED0() % 200 + 400;
        {u8 sp=p->s0 + fn_80089ED0() % p->s1; f32 yy=p->y; f32 xx=p->x; Spawn(q, ang, xx, yy, sp);}
        q->b = fn_80089ED0();
        q->life = life;
        q->age = 0;
    }
    if (p->dbg) {
        c = 32.0f * (f32)fn_80295534(0.024543693f * ang);
        s = 32.0f * (f32)fn_80295940(0.024543693f * ang);
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 300.0f, 1.0f);
        fn_8007E174(0, 0);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080388(p->x - 4.0f, p->y - 4.0f, 8.0f, 8.0f);
        fn_800804D4(0xFF, 0, 0, 0xFF);
        fn_80080308();
        fn_800800D4(4);
        fn_80080388(p->x, p->y, c, s);
        fn_800804D4(0xFF, 0xFF, 0, 0xFF);
        fn_80080308();
    }
    for (j = 0, ofs = 0; j < 0x400; j++, ofs += 0x10) {
        q2 = (Part*)((u8*)p->parts + ofs);
        if (q2->life != 0) {
            Update(q2);
            d = (Part*)((u8*)p->parts + ofs);
            Draw(d);
        }
    }
}
}
