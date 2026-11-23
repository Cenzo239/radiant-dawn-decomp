#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef union PSlot {
    s32 i;
    u32 u;
    f32 f;
    u16 h;
    GXColor c;
    void* p;
    MapUnit* m;
} PSlot;

typedef struct UProc {
    u8 pad0[0x30];
    MapUnit* unit; /* 0x30 */
    PSlot s34;     /* 0x34 */
    PSlot s38;     /* 0x38 */
    PSlot s3C;     /* 0x3C */
    PSlot s40;     /* 0x40 */
    PSlot s44;     /* 0x44 */
    PSlot s48;     /* 0x48 */
    PSlot s4C;     /* 0x4C */
    PSlot s50;     /* 0x50 */
} UProc;

typedef struct Probe { u8 pad[0x30]; void* a; } Probe;

extern u8 lbl_80367D50[];
extern u8 lbl_8038536C[];
extern u8 lbl_80385120[];
extern u8 lbl_80385148[];
extern void* fn_800811E4(void*, void*);
extern void* fn_800893E4(void*, void*, Probe*);
#if TARGET_PC
extern FE10_PROTO void* fn_80081050(void*, void *);
#else
extern void* fn_80081050(void*, int);
#endif
extern void fn_80104A70(void* a, void* b);
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
extern u32 fn_800F201C(int);
extern f32 fn_8001EDF8(int, f32, f32, f32, f32);
extern void fn_800F3B50(MapUnit*, f32, f32);
extern void fn_80083B78(void*);
extern void fn_80083DC4(void*, int);
extern f32 fn_800FB08C(MapUnit*, MapUnit*);
extern f32 fn_800FB100(MapUnit*, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_80102E10(MapUnit*, int, void *, f32, void*);
#else
extern void fn_80102E10(MapUnit*, int, int, f32, void*);
#endif
extern void fn_800F3F08(MapUnit*, int);
extern int fn_80008C98(void*, int);

void* fn_80100A04(MapUnit* u, s32 a, s32 b, void* parent) {
    UProc* p = fn_800811E4(lbl_8038536C, parent);
    p->unit = u;
    p->s40.i = a;
    p->s44.i = b;
    *(u8*)&p->s48 = 0;
    return p;
}

void fn_801006F0(UProc* p) {
    MapUnit* u;
    fn_800F6604(p->unit, (char*)lbl_80367D50 + 0x15);
    u = p->unit;
    p->s38.i = u->x;
    p->s3C.i = u->y;
    p->s34.i = 0;
}

static inline void U2C(GXColor* c, u32 v) {
    u32 t;
    c->a = v;
    t = v >> 24;
    c->r = t;
    t = v >> 16;
    c->g = t;
    t = v >> 8;
    c->b = t;
}
static inline void SpawnFade(MapUnit* u) {
    GXColor c;
    Probe s;
    UProc* q;
    s.a = u;
    fn_800893E4(lbl_80385120, fn_80104A70, &s);
    q = fn_80081050(lbl_80385120, 3);
    q->unit = u;
    q->s40.i = 2;
    U2C(&c, fn_800F201C(1));
    q->s38.c = c;
}
static inline void PA(MapUnit* u, char* name) {
    fn_80102928(u, fn_800F0994(name), 2, 0, 0);
}

void fn_80100834(UProc* p) {
    f32 x, y;
    p->s34.i++;
    x = fn_8001EDF8(2, 0.5f + (f32)p->s38.i, 0.5f + (f32)p->s40.i, 8.0f, (f32)p->s34.i);
    y = fn_8001EDF8(2, 0.5f + (f32)p->s3C.i, 0.5f + (f32)p->s44.i, 8.0f, (f32)p->s34.i);
    fn_800F3B50(p->unit, x, y);
    if (p->s34.i >= 8) {
        fn_80102928(p->unit, (void*)-1, 0x10, 0, 0);
        *(u8*)&p->s48 = 1;
        fn_80083B78(p);
    }
}

static inline void Face(MapUnit* a, MapUnit* b, void* p) {
    if (b) {
        fn_80102E10(a, 0x10, 0, (f32)(int)fn_800FB08C(a, b), p);
    }
}
void fn_80100FA4(UProc* p) {
    MapUnit* q;
    p->s44.f = 0.0f;
    q = p->s34.m;
    p->s38.f = q->x;
    p->s3C.f = q->y;
    Face(p->unit, q, p);
    Face(p->s34.m, p->unit, p);
    fn_800F3F08(p->s34.m, 0xFF);
}

static inline f32 L(f32 a, f32 b, int n, f32 t) { return fn_8001EDF8(2, a, b, (f32)n, t); }

void fn_801013EC(UProc* p) {
    int n = 0x10;
    int a;
    f32 x, y;
    p->s4C.f += 1.0f;
    a = fn_8001EDF8(2, 0.0f, 255.0f, (f32)n, p->s4C.f);
    x = fn_8001EDF8(2, p->s38.f, p->s44.f, (f32)n, p->s4C.f);
    y = fn_8001EDF8(2, p->s3C.f, p->s48.f, (f32)n, p->s4C.f);
    fn_800F3B50(p->s34.m, x, y);
    fn_800F3F08(p->s34.m, a);
    if (p->s4C.f == (f32)n) {
        fn_80083B78(p);
    }
}

void fn_80101268(UProc* p) {
    MapUnit* u;
    p->s4C.f = 0.0f;
    u = p->unit;
    p->s38.f = u->x;
    p->s3C.f = u->y;
    fn_800F3B50(p->s34.m, p->s38.f, p->s3C.f);
    u = p->unit;
    {
    int y = p->s48.f;
    int x = p->s44.f;
    fn_80102E10(u, 0x10, 0, (f32)(int)fn_800FB100(u, 0.5f + (f32)x, 0.5f + (f32)y), p);
    }
    p->s34.m->angle = 64.0f * fn_800FB100(p->s34.m, p->s44.f, p->s48.f);
    fn_800F3F08(p->s34.m, 0);
}

typedef struct MC { u8 pad[0x30]; MapUnit* u; } MC;

void fn_801016F8(UProc* p) {
    int n;
    int a;
    f32 x, y;
    int m = 8;
    p->s50.f += 1.0f;
    if (p->s50.f < (f32)m) {
        a = fn_8001EDF8(2, 0.0f, 255.0f, (f32)m, p->s50.f);
    } else {
        a = fn_8001EDF8(2, 255.0f, 0.0f, (f32)m, p->s50.f - (f32)m);
    }
    n = 0x10;
    x = fn_8001EDF8(2, p->s3C.f, p->s48.f, (f32)n, p->s50.f);
    y = fn_8001EDF8(2, p->s40.f, p->s4C.f, (f32)n, p->s50.f);
    fn_800F3B50(p->s34.m, x, y);
    fn_800F3F08(p->s34.m, a);
    if (p->s50.f == (f32)n) {
        fn_80083B78(p);
    }
}

void fn_801018BC(UProc* p) {
    switch (p->s34.h & 3) {
    case 0:
    case 2:
        fn_80083DC4(p, 0);
        return;
    case 1:
        fn_80083DC4(p, 1);
        return;
    }
}

extern void fn_800E24F8(char*);
extern int fn_8028DB44(int);
extern int fn_8011B77C(void*, void*);
extern void* lbl_804CA524;
extern void fn_800F6604(MapUnit*, char*);
extern void* fn_800E3A10(char*, void*);
extern void fn_800E48AC(void*, f32, f32, f32);
extern void fn_8017DB90(int, int, int, int, void*);
#if TARGET_PC
FE10_PROTO void fn_80101B80(void *);
#else
void fn_80101B80();
#endif

void fn_80100A68(UProc* p) {
    fn_800F6604(p->unit, (char*)lbl_80367D50 + 0x33);
    if (p->s34.m) {
        Face(p->unit, p->s34.m, p);
        fn_800F6604(p->s34.m, (char*)lbl_80367D50 + 0x15);
        {
            MapUnit* q = p->s34.m;
            p->s38.i = q->x;
            p->s3C.i = q->y;
        }
    } else {
        MapUnit* u = p->unit;
        fn_80102E10(u, 0x10, 0, (f32)(int)fn_800FB100(u, 0.5f + (f32)p->s40.i, 0.5f + (f32)p->s44.i), p);
        p->s38.i = p->s40.i;
        p->s3C.i = p->s44.i;
    }
    {
        int dx = fn_8028DB44(p->s40.i - p->s38.i);
        int d = dx + fn_8028DB44(p->s44.i - p->s3C.i);
        char* b = (char*)lbl_80367D50;
        char* n;
        n = b + 0x28;
        if (d >= 2) n = b + 0x1E;
        fn_800E24F8(n);
    }
    p->s48.f = 0.0f;
}

typedef struct EvC { u8 pad[0x30]; struct { u8 pad[0x9C]; void* cb; }* ctl; } EvC;
void fn_80101C60(UProc* p) {
    f32 x, y, z;
    MapUnit* u;
    char* n;
    EvC* c;
    fn_800F3B50(p->unit, 0.5f + (f32)p->s38.i, 0.5f + (f32)p->s3C.i);
    fn_800F3F08(p->unit, 0);
    u = p->unit;
    x = u->x;
    y = u->y;
    z = u->z;
    if (fn_8011B77C((u8*)u + 0x12C, lbl_804CA524)) {
        u8 k = *((u8*)u + 0x118);
        if ((s8)k == -1) k = *(*(u8**)((u8*)u + 0xEC) + 0xE1);
        switch ((s8)k) {
        case 1:
            n = (char*)lbl_80367D50 + 0xAD;
            break;
        case 2:
            n = (char*)lbl_80367D50 + 0xC1;
            break;
        case 3:
            n = (char*)lbl_80367D50 + 0xD5;
            break;
        default:
            n = (char*)lbl_80367D50 + 0xE9;
            break;
        }
    } else {
        n = (char*)lbl_80367D50 + 0xFB;
    }
    c = fn_800E3A10(n, p);
    if (c) {
        fn_800E48AC(c, x, y, z);
        c->ctl->cb = fn_80101B80;
        if (p->s34.h & 0x10) {
            fn_8017DB90(x, y, 0, 0, c);
        }
    }
}
