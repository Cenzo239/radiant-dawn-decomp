#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct Cl4 { u8 r, g, b, a; };
extern u8 lbl_803EC898[];
extern MapModel* fn_8013B9A8(void);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021958(int, Cl4);
extern void fn_800218A8(int, Cl4);
extern void fn_80021BF4(int);
extern void fn_80021EF8(int, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021C34(int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_803128AC(void*, f32, f32, f32);
extern void* fn_8000FB88(void);
extern void fn_80312378(void*, void*, void*);
extern void fn_80307E48(void*, int);
extern void fn_80021784(int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80022158(int, int, int);
extern void fn_80306FD8(int, int, int, int, int);
void fn_8013F238(void) {
    u8 m[0x30];
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    {
        Cl4 c = {0xFF, 0x60, 0, 0xFF};
        fn_80021958(4, c);
    }
    {
        Cl4 c = {0xFF, 0xFF, 0xFF, 0xFF};
        fn_800218A8(4, c);
    }
    fn_80021BF4(1);
    fn_80021EF8(0, 0);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_803128AC(m, 0.0f, 0.0f, -0.0125f);
    fn_80312378(fn_8000FB88(), m, m);
    fn_80307E48(m, 0);
    fn_80021784(0);
    fn_80021BA4(1, 4, 5, 0);
    fn_80022158(0, 0, 3);
    fn_80306FD8(3, 0, 1, 2, 0);
}
struct Path { s8 x[0x40]; s8 y[0x40]; s8 cost[0x40]; s8 shape[0x40]; s8 n; };
void fn_8013FC20(Path* p, s8 c) {
    s8 d = c - p->cost[0];
    for (p->n = 0; p->n < 0x40; p->n++) {
        p->cost[p->n] += d;
        switch (p->shape[p->n]) {
        case 8:
        case 9:
        case 10:
        case 11:
            goto out;
        }
        if (p->cost[p->n] <= 0) break;
    }
out:
    {
        u8 v = p->shape[p->n];
        switch (v) {
        case 0:
        case 0x10:
        case 0x12:
            v = 8;
            break;
        case 3:
        case 0xD:
        case 0xF:
            v = 11;
            break;
        case 1:
        case 0xC:
        case 0x11:
            v = 9;
            break;
        case 2:
        case 0xE:
        case 0x13:
            v = 10;
            break;
        }
        p->shape[p->n] = v;
    }
}
extern u8* fn_8000F470(void);
extern void fn_80313484(Vec*, Vec*, Vec*);
extern void fn_8001E6D0(void*, void*);
extern void fn_80312494(void*, void*);
extern void fn_80312DB4(void*, Vec*, Vec*);
extern void fn_803134C4(Vec*, Vec*);
extern f32 fn_80313508(Vec*);
extern f32 fn_8031354C(Vec*, Vec*);
f32 fn_80140BA4(void) {
    u8 m[0x30];
    Vec v;
    Vec a;
    u8* c = fn_8000F470();
    f32 r;
    fn_80313484((Vec*)(c + 0xE0), (Vec*)(c + 0xD4), &v);
    fn_8001E6D0((u8*)fn_8013B9A8() + 0xE4, m);
    fn_80312494(m, m);
    fn_80312DB4(m, &v, &v);
    fn_803134C4(&v, &v);
    *(u32*)&a.x = 0;
    *(u32*)&a.z = 0;
    *(u32*)&a.y = 0;
    a.x = v.x;
    a.z = v.y;
    r = fn_80313508(&a);
    if (r == 0.0f) return 0.0f;
    fn_803134C4(&a, &a);
    r = __fabs(fn_8031354C(&v, &a));
    if (r > 1.0f) r = 1.0f;
    if (r < 0.0f) r = 0.0f;
    return r;
}
extern s8 fn_80115CD8(void*, int, int);
static inline u8 Dir(s8 x0, s8 y0, s8 x1, s8 y1) {
    if (x0 < x1) return 2;
    if (x0 > x1) return 1;
    if (y0 < y1) return 4;
    if (y0 > y1) return 8;
    return 0x40;
}
void fn_8013F820(Path* p, s8 x, s8 y) {
    int i;
    u32 d;
    p->n++;
    p->x[p->n] = x;
    p->y[p->n] = y;
    {
        s8 n = p->n;
        s8 c = fn_80115CD8(lbl_803EC898, x, y);
        p->cost[n] = p->cost[n - 1] - c;
    }
    d = Dir(p->x[0], p->y[0], p->x[1], p->y[1]);
    switch (d) {
    case 8: p->shape[0] = 7; break;
    case 4: p->shape[0] = 4; break;
    case 1: p->shape[0] = 5; break;
    case 2: p->shape[0] = 6; break;
    }
    for (i = 1; i < p->n; i++) {
        s8 cx = p->x[i];
        s8 cy = p->y[i];
        u8 a = Dir(p->x[i - 1], p->y[i - 1], cx, cy);
        switch (a * 0x10 + Dir(cx, cy, p->x[i + 1], p->y[i + 1])) {
        case 0x88: p->shape[i] = 3; break;
        case 0x44: p->shape[i] = 0; break;
        case 0x11: p->shape[i] = 1; break;
        case 0x22: p->shape[i] = 2; break;
        case 0x82: p->shape[i] = 0xD; break;
        case 0x14: p->shape[i] = 0xC; break;
        case 0x81: p->shape[i] = 0xF; break;
        case 0x24: p->shape[i] = 0xE; break;
        case 0x42: p->shape[i] = 0x10; break;
        case 0x18: p->shape[i] = 0x11; break;
        case 0x41: p->shape[i] = 0x12; break;
        case 0x28: p->shape[i] = 0x13; break;
        }
    }
    d = Dir(p->x[i - 1], p->y[i - 1], p->x[i], p->y[i]);
    switch (d) {
    case 8: p->shape[i] = 11; break;
    case 4: p->shape[i] = 8; break;
    case 1: p->shape[i] = 9; break;
    case 2: p->shape[i] = 10; break;
    }
}

extern int fn_80116DB8(void*, int, int, int, int);
extern void fn_80114888(void*, int);
extern void fn_80115764(void*, int, int, u16);
extern u8* fn_80116658(void*, int, int);
#define ABS(a) ((a) < 0 ? -(a) : (a))
static inline int FindOnPath(Path* p, int x, int y) {
    int i;
    for (i = 0; i < p->n; i++) {
        if (x == p->x[i] && y == p->y[i]) return (s8)i;
    }
    return -1;
}
static inline void Call(u8* m, s8 x, s8 y, s8 c) { fn_80115764(m, x, y, c); }
struct Pt { s8 x, y; };
static inline void Call2(u8* m, Path* p, int i, s8 c) { fn_80115764(m, p->x[i], p->y[i], c); }
static inline void Mark2(u8* m, Path* p, int i) {
    u8 x = p->x[i]; u8 y = p->y[i]; fn_80115764(m, (s8)x, (s8)y, p->cost[i]);
}
#define Mark(p) Mark2(lbl_803EC898, p, p->n)
static inline BOOL HasLoop(Path* p) {
    int i;
    for (i = p->n; i >= 0; i--) {
        int j;
        for (j = i - 1; j >= 0; j--) {
            if (p->x[i] == p->x[j] && p->y[i] == p->y[j]) return 1;
        }
    }
    return 0;
}
#define WALK(p, q)                                 \
    {                                              \
        s8 cx = p->x[p->n];                        \
        s8 cy = p->y[p->n];                        \
        for (;;) {                                 \
            switch (*q++) {                        \
            case 8: cy--; break;                   \
            case 4: cy++; break;                   \
            case 1: cx--; break;                   \
            case 2: cx++; break;                   \
            case 0x40: goto done;                  \
            }                                      \
            fn_8013F820(p, cx, cy);                \
        }                                          \
    }
#define WALKR(p, q)                                 \
    {                                              \
        s8 cx = p->x[p->n];                        \
        s8 cy = p->y[p->n];                        \
        for (;;) {                                 \
            switch (*q++) {                        \
            case 8: cy--; break;                   \
            case 4: cy++; break;                   \
            case 1: cx--; break;                   \
            case 2: cx++; break;                   \
            case 0x40: goto e;                  \
            }                                      \
            fn_8013F820(p, cx, cy);                \
        }                                          \
    }\
    e:;
static inline void ResetTo(Path* p, int x, int y) {
    u8* q;
    p->n = 0;
    fn_80114888(lbl_803EC898, 7);
    Mark(p);
    q = fn_80116658(lbl_803EC898, (s8)x, (s8)y);
    fn_80114888(lbl_803EC898, 6);
    WALKR(p, q);
}
struct MapG2 { u8 pad[0x710E]; s16 a[0x1000]; s16 b[0x1000]; };
void fn_8013FCE8(Path* p, int x, int y) {
    int k;
    int idx;
    if ((s8)x == p->x[p->n] && (s8)y == p->y[p->n]) return;
    {
    k = ((s8)x + (s8)y * 0x40) * 2;
    if (*(s16*)(lbl_803EC898 + k + 0x710E) < 0) return;
    idx = FindOnPath(p, (s8)x, (s8)y);
    if (idx >= 0) {
        p->n = idx - 1;
        if ((s8)p->n < 0) {
            p->x[0] = x;
            p->y[0] = y;
            p->shape[0] = 0x14;
            p->n = 0;
        } else {
            fn_8013F820(p, (s8)x, (s8)y);
        }
        return;
    }
    {
        s16 c = ((s16(*)(void*, int, int))fn_80115CD8)(lbl_803EC898, (s8)x, (s8)y);
        if (p->cost[p->n] >= c && ABS((s8)x - p->x[p->n]) + ABS((s8)y - p->y[p->n]) == 1 && fn_80116DB8(lbl_803EC898, (s8)x, (s8)y, p->x[p->n], p->y[p->n])) {
            fn_8013F820(p, (s8)x, (s8)y);
            return;
        }
    }
    fn_80114888(lbl_803EC898, 7);
    Mark(p);
    fn_80114888(lbl_803EC898, 6);
    if (*(s16*)(lbl_803EC898 + 0x918E + k) < 0) {
        ResetTo(p, x, y);
        return;
    } else {
        {
        s8 cx;
        s8 cy;
        u8* q;
        fn_80114888(lbl_803EC898, 7);
        q = fn_80116658(lbl_803EC898, (s8)x, (s8)y);
        fn_80114888(lbl_803EC898, 6);
        cx = p->x[p->n];
        cy = p->y[p->n];
        for (;;) {
            switch (*q++) {
            case 8: cy--; break;
            case 4: cy++; break;
            case 1: cx--; break;
            case 2: cx++; break;
            case 0x40: goto done;
            }
            fn_8013F820(p, cx, cy);
        }
        }
    done:
        if (HasLoop(p)) ResetTo(p, x, y);
    }
    }
}
}
