#include "game/rA_800068A0/types.h"

/* GActor continuation: animation drivers, display-list hooks, and the
 * resource loaders that relocate GMatSet pointers. */

typedef struct GColor { u8 r, g, b, a; } GColor;

typedef struct GChan {
    f32 a, b;
    u8 pad[0xC];
} GChan;

typedef struct GAnimInfo {
    u8 pad[6];
    u16 n;
} GAnimInfo;

typedef struct GAnimState {
    u8 pad[0x30];
    GAnimInfo* info;
    GChan* chans;
} GAnimState;

typedef struct GA {
    u32 flags;       /* 0x00 */
    u32 x4;
    u8 r, g, b, a;   /* 0x08 */
    u8 pad0C[0x54 - 0xC];
    GAnimState* x54; /* 0x54 */
    u8 pad58[4];
    f32 x5C;         /* 0x5C */
    u8 pad60[0x7C - 0x60];
    void* x7C;       /* 0x7C */
    u8 pad80[2];
    u8 x82;          /* 0x82 */
} GA;

extern void fn_80010788(int, u8, void*, void*);
extern void fn_80017B08(GA*);

#pragma push
#pragma auto_inline off
void fn_80017D6C(GA* a) {
    if (a->x54 != 0) {
        fn_80010788(3, a->x82, fn_80017B08, a);
    }
}


void fn_80017D94(GA* a) {
    if (a->x54 != 0) {
        fn_80017B08(a);
    }
}
#pragma pop

void fn_80017DA8(GA* a, f32 v) {
    GAnimState* s = a->x54;
    int i;
    GAnimInfo* info;
    GChan* c;
    if (s == 0) {
        return;
    }
    c = s->chans;
    if (c == 0) {
        return;
    }
    info = s->info;
    for (i = 0; i < info->n; i++) {
        c->a = v;
        c->b = 0.0f;
        c++;
    }
}

typedef struct GRes44 {
    u8 x0[0x14];
    s32 start;
    s32 end;
} GRes44;

extern GRes44* fn_80007F10(GA*);
extern f32 fn_800081B4(GA*);
extern f32 fn_80006D08(GA*);
extern void fn_800081D4(GA*);
extern void fn_800158FC(GA*);
extern void fn_800088A0(GA*, f32);
extern void fn_8000866C(GA*, f32);

void fn_80017DF0(GA* a) {
    GRes44* r;
    f32 frame, scale;
    int i;
    u32 flags;
    int n;
    if (a->x54 == 0) {
        return;
    }
    r = fn_80007F10(a);
    if (r == 0) {
        return;
    }
    frame = fn_800081B4(a);
    scale = fn_80006D08(a);
    flags = a->flags;
    i = 0;
    n = r->end - r->start;
    a->flags = flags | 0x18;
    a->x5C = 4.0f;
    while (i < n) {
        fn_800081D4(a);
        fn_800158FC(a);
        i = (f32)i + a->x5C;
    }
    a->flags = flags;
    fn_800088A0(a, scale);
    fn_8000866C(a, frame);
}

typedef struct GReloc {
    u32 a, b;
} GReloc;

typedef struct GMatSet {
    u8 pad[0x34];
    u8* entries;
    u8 pad38[0x48 - 0x38];
    GReloc* reloc;
    u8 pad4C[0x54 - 0x4C];
    u16 count;
} GMatSet;

extern u32 fn_8023F7B8(void*);
extern GMatSet* fn_80075FB4(void*, int);
extern void fn_80012430(void*);
extern void fn_800150F4(GMatSet*);

GMatSet* fn_80017F10(void* id) {
    GReloc* rl;
    int i;
    GMatSet* m;
    int doit;
    int off;
    doit = 1;
    if (fn_8023F7B8(id) & 0x400000) {
        doit = 0;
    }
    m = fn_80075FB4(id, 0);
    if (doit) {
        for (i = 0, off = 0; i < m->count; off += 0x20, i++) {
            fn_80012430(m->entries + off);
        }
        rl = m->reloc;
        if (rl != 0) {
            rl->a += (u32)rl;
            rl->b += (u32)rl;
        }
    }
    fn_800150F4(m);
    return m;
}

GMatSet* fn_80017FD0(void* id, int f) {
    int doit = 1;
    GMatSet* m;
    if (fn_8023F7B8(id) & 0x400000) {
        doit = 0;
    }
    m = fn_80075FB4(id, f);
    if (doit) {
        int i;
        GReloc* rl;
        for (i = 0; i < m->count; i++) {
            fn_80012430(m->entries + i * 0x20);
        }
        rl = m->reloc;
        if (rl != 0) {
            rl->a += (u32)rl;
            rl->b += (u32)rl;
        }
    }
    fn_800150F4(m);
    return m;
}

typedef struct GRes48 {
    u8 pad[0x3C];
    void* x3C;
    void* x40;
    void* x44;
} GRes48;

extern GRes48* fn_80007F3C(GA*);
extern void fn_800183F0(GA*);
extern void fn_80018434(GA*);
extern void fn_80018478(GA*);

void fn_800180F0(GA* a) {
    int l0, l1, l2;
    GRes48* m;
    u32 fl;
    if (a->a == 0) {
        return;
    }
    m = fn_80007F3C(a);
    fl = a->flags;
    l0 = 1;
    l1 = 2;
    l2 = 3;
    if (fl & 0xE00273C0) {
        if (fl & 0x40) {
            l1 = 2;
            l0 = 2;
        }
        if (fl & 0x180) {
            l2 = 3;
            l1 = 3;
            l0 = 3;
        }
    }
    if (m->x3C != 0) {
        fn_80010788(l0, a->x82, fn_800183F0, a);
    }
    if (m->x40 != 0) {
        fn_80010788(l1, a->x82, fn_80018434, a);
    }
    if (m->x44 != 0) {
        fn_80010788(l2, a->x82, fn_80018478, a);
    }
    if (a->x54 != 0) {
        fn_80017D6C(a);
    }
}

extern void fn_8001A4E8(GA*);
extern void fn_8001A9B4(GA*);
extern void fn_8001B194(GA*);
extern int fn_80018208(GA*, int);
extern void fn_80018888(GA*, int);
extern void fn_8001A218(int, GA*);

void fn_8001A610(GA* a) {
    if (a->x7C != 0 && a->a != 0) {
        fn_80010788(3, a->x82, fn_8001A4E8, a);
    }
}

void fn_8001A9B4(GA* a) {
    GRes48* m = fn_80007F3C(a);
    u32 fl = a->flags;
    GColor c = *(GColor*)&a->r;
    a->flags = (fl & 0x200000) | 0x6001B800;
    a->r = 0x80;
    a->g = 0x80;
    a->b = 0x80;
    a->a = 0xFF;
    if (m->x40 != 0 && fn_80018208(a, 2) == 0) {
        fn_80018888(a, 2);
    }
    a->flags = fl;
    *(GColor*)&a->r = c;
}

void fn_8001AA84(GA* a) {
    if (a != 0 && a->a == 0xFF) {
        fn_80010788(2, a->x82, fn_8001A9B4, a);
    }
}

void fn_8001B194(GA* a) {
    if (a->a != 0) {
        u32 fl = a->flags;
        GColor c = *(GColor*)&a->r;
        a->flags = (fl & 0x200000) | 0xE0039000;
        a->r = 0x80;
        a->g = 0x80;
        a->b = 0x80;
        a->a = 0xFF;
        fn_8001A218(1, a);
        fn_8001A218(2, a);
        a->flags = fl;
        *(GColor*)&a->r = c;
    }
}

void fn_8001B254(GA* a) {
    if (a->a != 0 && a->a != 0xFF) {
        fn_80010788(3, a->x82, fn_8001B194, a);
    }
}

#if TARGET_PC
/* Host: mtspr GQR6 */
void fn_8001D014(u32 x) {
    fe10_gqr[6] = x;
}
#else
asm void fn_8001D014(u32 x) {
    nofralloc
    mtspr 0x396, r3
    blr
}
#endif

#if TARGET_PC
/* Host: mtspr GQR7 */
void fn_8001D01C(u32 x) {
    fe10_gqr[7] = x;
}
#else
asm void fn_8001D01C(u32 x) {
    nofralloc
    mtspr 0x397, r3
    blr
}
#endif

f32 fn_8001E010(s8 x) {
    return 0.0625f * x;
}

int fn_8001E044(f32 x) {
    return 16.0f * x;
}

int fn_8001E094(f32 x) {
    return 128.0f * x;
}

typedef struct FVec { f32 x, y, z; } FVec;
typedef struct SVec { s16 x, y, z; } SVec;

static inline f32 fx2f(s16 v) { return 0.0078125f * v; }

void fn_8001E0B4(FVec* o, const SVec* s) {
    FVec v;
    v.x = fx2f(s->x);
    v.y = fx2f(s->y);
    v.z = fx2f(s->z);
    *o = v;
}

typedef unsigned long long u64;
typedef union U { struct { s16 x, y, z; } s; u64 v; } U;
typedef struct S6 { s16 x, y, z; } S6;
static inline s16 f2fx(f32 v) { return 128.0f * v; }
S6 fn_8001E144(const FVec* p) {
    S6 u;
    u.x = f2fx(p->x);
    u.y = f2fx(p->y);
    u.z = f2fx(p->z);
    return u;
}

#if TARGET_PC
FE10_PROTO extern void *lbl_804CB0A8;
#else
extern int lbl_804CB0A8;
#endif
extern int lbl_804CB0AC;
extern int lbl_804CB0B0;
#if TARGET_PC
extern FE10_PROTO void fn_80079978(void *);
extern FE10_PROTO void * fn_80079940(int, int);
#else
extern void fn_80079978(int);
extern int fn_80079940(int, int);
#endif
extern void DCFlushRange(int, int);

void fn_80020E7C(int size);

#if TARGET_PC
extern FE10_PROTO void fn_80011C4C(void *, FVec*, FVec*);
#else
extern void fn_80011C4C(int, FVec*, FVec*);
#endif

int fn_800215D4(const FVec* a, const FVec* b, FVec* mn, FVec* mx) {
    FVec p[8];
    FVec o;
    FVec* q;
    int i;
    p[0].x = a->x; p[0].y = a->y; p[0].z = a->z;
    p[1].x = b->x; p[1].y = a->y; p[1].z = a->z;
    p[2].x = b->x; p[2].y = b->y; p[2].z = a->z;
    p[3].x = a->x; p[3].y = b->y; p[3].z = a->z;
    p[4].x = a->x; p[4].y = a->y; p[4].z = b->z;
    p[5].x = b->x; p[5].y = a->y; p[5].z = b->z;
    p[6].x = b->x; p[6].y = b->y; p[6].z = b->z;
    p[7].x = a->x; p[7].y = b->y; p[7].z = b->z;
    mn->x = 10000.0f;
    mn->y = 10000.0f;
    mn->z = 10000.0f;
    mx->x = -10000.0f;
    mx->y = -10000.0f;
    mx->z = -10000.0f;
    q = p;
    for (i = 0; i < 8; i++) {
        fn_80011C4C(0, q, &o);
        if (o.x < mn->x) mn->x = o.x;
        if (o.y < mn->y) mn->y = o.y;
        if (o.z < mn->z) mn->z = o.z;
        if (o.x > mx->x) mx->x = o.x;
        if (o.y > mx->y) mx->y = o.y;
        if (o.z > mx->z) mx->z = o.z;
        q++;
    }
    return 1;
}

extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021958(int, GColor);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80021C34(int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021C74(int);
extern void fn_80306B24(int);
extern void fn_80304314(int, int, int);

#define GXFIFO_S16 (*(volatile s16*)0xCC008000)

void fn_80022B54(s16 z, int w, int h) {
    static const GColor black = {0, 0, 0, 0xFF};
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80303200(0, 9, 1, 3, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    fn_80021958(4, black);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021EF8(0, 4);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021C74(0);
    fn_80306B24(0);
    fn_80304314(0x80, 0, 4);
    {
    int x;
    int y;
    int my;
    int mx;
    x = w >> 1;
    y = h >> 1;
    mx = -x;
    my = -y;
    GXFIFO_S16 = mx;
    GXFIFO_S16 = my;
    GXFIFO_S16 = z;
    GXFIFO_S16 = x;
    GXFIFO_S16 = my;
    GXFIFO_S16 = z;
    GXFIFO_S16 = x;
    GXFIFO_S16 = y;
    GXFIFO_S16 = z;
    GXFIFO_S16 = mx;
    GXFIFO_S16 = y;
    GXFIFO_S16 = z;
    }
}

typedef struct LinkList { u8 x0; u8 pad; u8 n; u8 pad3[5]; GA** items; } LinkList;
typedef struct GA7C { u8 pad[0x7C]; LinkList* list; } GA7C;
extern void fn_80015070(GRes48*, int, int);

#pragma use_lmw_stmw on
void fn_8001A4E8(GA* a) {
    GRes48* m;
    LinkList* l;
    int i;
    if (a->x7C == 0) {
        return;
    }
    m = fn_80007F3C(a);
    l = (LinkList*)a->x7C;
    if (!(l->x0 & 1)) {
        fn_80015070(m, 0x200, 0);
    }
    for (i = 0; i < l->n; i++) {
        GA* c = l->items[i];
        if (m->x3C != 0 && fn_80018208(c, 1) == 0) {
            fn_80018888(c, 1);
        }
        if (m->x40 != 0 && fn_80018208(c, 2) == 0) {
            fn_80018888(c, 2);
        }
        if (m->x44 != 0 && fn_80018208(c, 3) == 0) {
            fn_80018888(c, 3);
        }
        if (a->x54 != 0) {
            fn_80017D94(c);
        }
    }
    fn_80015070(m, 0, 4);
}
#pragma use_lmw_stmw off

extern u8* fn_80020E74(void);
extern int fn_8030585C(int, int, int, int, int);
extern int fn_80020EFC(void);
extern void fn_80304C74(GColor*, u32);
extern void fn_8001F4D8(int, int, int, int, int, int, void*, int, u8);
extern u32 fn_8002177C(void);

static inline void setClear(u32 v) {
    GColor c;
    c.a = v;
    c.r = v >> 24;
    c.g = v >> 16;
    c.b = v >> 8;
    fn_80304C74(&c, 0xFFFFFF);
}

int fn_8001AB10(void);
