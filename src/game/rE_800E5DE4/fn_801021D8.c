#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct Probe { u8 pad[0x30]; void* a; } Probe;
typedef struct R21D8 { u8 pad[0x30]; MapUnit* u; u8 b34; u8 b35; u8 b36; } R21D8;

typedef struct Turn {
    u8 pad[0x30];
    MapUnit* u;  /* 0x30 */
    u8 pad34[4];
    s32 n;       /* 0x38 */
    s32 t;       /* 0x3C */
    u8 pad40[8];
    f32 from;    /* 0x48 */
    f32 to;      /* 0x4C */
    f32 target;  /* 0x50 */
} Turn;

/* Jump process (guessed), 8010403C..801045F4. */
typedef struct Jump {
    u8 pad[0x30];
    MapUnit* u; /* 0x30 */
    s16 dir;    /* 0x34 */
    u8 pad36[4];
    s16 x;      /* 0x3A */
    s16 y;      /* 0x3C */
    u8 pad3E[6];
    f32 f44;    /* 0x44 */
    f32 f48, f4C, f50; /* 0x48 */
    f32 f54, f58, f5C; /* 0x54 */
    f32 f60;    /* 0x60 */
    s16 t;      /* 0x64 */
    s16 dur;    /* 0x66 */
    s16 speed;  /* 0x68 */
    u8 b6A;
    u8 b6B;     /* 0x6B */
} Jump;

extern u8 lbl_80367D50[];
extern u8 lbl_80385090[];
extern u8 lbl_803850C8[];
extern void fn_80104A70(void* a, void* b);
extern void fn_80104AA4(void* a, void* b);
extern void* fn_800893E4(void*, void*, Probe*);
extern void* fn_80081050(void*, void*);
extern void* fn_800811E4(void*, void*);
extern int fn_801220A0(MapUnit*);
extern int fn_800F4700(MapUnit*, char*);
extern void fn_800F6604(MapUnit*, char*);
#if TARGET_PC
extern FE10_PROTO int fn_800F0994(char*);
#else
extern void* fn_800F0994(char*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, int, int, int, void *);
#else
extern void fn_80102928(MapUnit*, void*, int, int, int);
#endif
extern void fn_80083DC4(void*, int);
extern void fn_80083B78(void*);
extern void fn_800E24F8(char*);
extern void fn_800F68DC(MapUnit*, int);
extern int fn_800FC09C(MapUnit*, int, f32);
#if TARGET_PC
extern FE10_PROTO void fn_800FCA40(void*, MapUnit*, unsigned short);
#else
extern void fn_800FCA40(void*, MapUnit*, void*);
#endif
extern f32 fn_8001EF30(f32, f32, f32, f32);

static inline int State(R21D8* p) {
    if (p->b34 == 0) return 2;
    if (p->b36) {
        if (fn_801220A0(p->u) == 2) return 1;
    }
    return 0;
}

void fn_801021D8(R21D8* p) {
    if (State(p) == 0) {
        char* s = (char*)lbl_80367D50;
        if (fn_800F4700(p->u, s + 0x107)) {
            fn_800F6604(p->u, s + 0x107);
        }
    }
    switch (State(p)) {
    case 0:
    case 1:
        fn_800E24F8((char*)lbl_80367D50 + 0x10C);
        p->u->flags |= 4;
        fn_800F68DC(p->u, 0);
        p->u->flags &= ~4;
        break;
    }
}

static inline void PA(MapUnit* u, char* name, int a, int b, int c) {
    fn_80102928(u, fn_800F0994(name), a, b, c);
}
static inline void Fx(MapUnit* u, void* parent) {
    Probe s;
    R21D8* q;
    s.a = u;
    fn_800893E4(lbl_80385090, fn_80104A70, &s);
    if (parent == 0) parent = (void*)3;
    q = fn_80081050(lbl_80385090, parent);
    q->u = u;
}


void* fn_80102E10(MapUnit* u, int n, void* b, f32 ang, void* parent) {
    f32 f;
    int w;
    if (*(u16*)((u8*)u + 0x110) & 1) return 0;
    w = ang / 360.0f;
    f = ang - (f32)(w * 360);
    if (n < 0) n = fn_800FC09C(u, n, f);
    if (n == 0) {
        Probe s;
        s.a = u;
        fn_800893E4(lbl_803850C8, fn_80104A70, &s);
        u->angle = 64.0f * f;
        return 0;
    } else {
        Probe s;
        Turn* q;
        s.a = u;
        q = fn_800893E4(lbl_803850C8, fn_80104AA4, &s);
        if (q) {
            if (q->target == f) return 0;
        } else {
            if (f == 0.015625f * (f32)u->angle) return 0;
            q = fn_800811E4(lbl_803850C8, parent);
            fn_800FCA40(q, u, b);
        }
        q->t = 0;
        q->n = n;
        q->target = f;
        q->from = 0.015625f * (f32)q->u->angle;
        q->to = f;
        if ((f32)__fabs(q->from - f) > 180.0f) {
            if (q->from > q->to) {
                q->to += 360.0f;
            } else {
                q->from += 360.0f;
            }
        }
        return q;
    }
}

static inline int DirX(u8 d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}
static inline int DirY(u8 d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}
static inline int Scale(int t, f32 k) { return (f32)t * k; }


void fn_801044A8(Jump* p) {
    f32 x, y, z;
    MapUnit* u;
    if (p->b6B) {
        fn_80083B78(p);
        return;
    }
    p->t++;
    x = fn_8001EF30(p->f48, p->f54, (f32)p->dur, (f32)p->t);
    y = fn_8001EF30(p->f4C, p->f58, (f32)p->dur, (f32)p->t);
    z = fn_8001EF30(p->f50, p->f5C, (f32)p->dur, (f32)p->t);
    u = p->u;
    u->x = x;
    u->y = y;
    u->z = z;
    if (p->t >= p->dur) {
        fn_80083B78(p);
    }
}
